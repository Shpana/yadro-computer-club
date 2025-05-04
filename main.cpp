#include <fstream>
#include <iostream>
#include <sstream>

#include "src/validation.hpp"
#include "src/times.hpp"
#include "src/events/context.hpp"
#include "src/events/event_handler.hpp"
#include "src/registries/client_registry.hpp"
#include "src/registries/table_registry.hpp"

void handle_computer_club(std::istream& input, std::ostream& output) {
  if (!is_valid(input, output))
    return;

  input.clear();
  input.seekg(0);

  std::string line;

  size_t tables_count;
  std::getline(input, line);
  tables_count = std::stoi(line);

  std::string raw_start_time, raw_end_time;
  std::getline(input, line);
  std::istringstream iss1{line};
  iss1 >> raw_start_time >> raw_end_time;

  size_t table_price_per_hour;
  std::getline(input, line);
  table_price_per_hour = std::stoi(line);

  auto context = Context{to_time(raw_start_time), to_time(raw_end_time), tables_count};

  std::shared_ptr<ClientRegistry> client_registry = std::make_shared<ClientRegistry>();

  std::shared_ptr<Accountant> accountant = std::make_shared<Accountant>(tables_count);
  std::shared_ptr<TableRegistry> table_registry = std::make_shared<TableRegistry>(tables_count, accountant);

  EventHandler handler(context, table_registry, client_registry);

  std::string event_line;
  while (std::getline(input, event_line)) {
    std::istringstream iss{event_line};
    std::string raw_created_at;
    size_t event_id;
    iss >> raw_created_at >> event_id;
    time_t created_at = to_time(raw_created_at);

    switch (event_id) {
      case 1: {
        std::string client_name;
        iss >> client_name;
        auto event = ClientArrivedEvent{event_id, created_at, client_name};
        auto result = handler.handle(event);
        if (!result.is_ok) {
          auto error_event = ErrorEvent{13, created_at, result.message};
          handler.handle(error_event);
        }
        break;
      }
      case 2: {
        std::string client_name;
        size_t table_id;
        iss >> client_name >> table_id;
        auto event = ClientTakeTableEvent{event_id, created_at, client_name, table_id};
        handler.handle(event);
        break;
      }
      case 3: {
        std::string client_name;
        iss >> client_name;
        auto event = ClientWaitingEvent{event_id, created_at, client_name};
        handler.handle(event);
        break;
      }
      case 4: {
        std::string client_name;
        iss >> client_name;
        auto event = ClientLeftEvent{event_id, created_at, client_name};
        handler.handle(event);
        break;
      }
      default:
        break;
    }
  }

  table_registry->unpin_all(to_time(raw_end_time));

  for (auto [key, value] : accountant->prepare_report(table_price_per_hour)) {
    std::cout << key
              << ' ' << value.revenue
              << ' ' << to_string_time(value.occupied_time) << '\n';
  }
  std::cout << std::endl;
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
    return 1;
  }

  std::fstream file;
  file.open(argv[1], std::ios::in);
  if (file.is_open()) {
    handle_computer_club(file, std::cout);
  } else {
    std::cerr << "Unable to open input file!" << std::endl;
    return 1;
  }
  file.close();
}
