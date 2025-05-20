#include "parsing.hpp"

#include "io/utils/time_converts.hpp"

namespace ComputerClub::IO {
  auto ParseSpec(std::istream& is) -> Events::Context::Spec {
    Events::Context::Spec spec{};

    std::string line;
    std::getline(is, line);
    spec.tables_count = std::stoi(line);

    std::getline(is, line);
    std::istringstream iss{line};
    std::string raw_start_time, raw_end_time;
    iss >> raw_start_time >> raw_end_time;
    spec.start_time = string_to_time(raw_start_time);
    spec.end_time = string_to_time(raw_end_time);

    std::getline(is, line);
    spec.price_per_hour = std::stoi(line);
    return spec;
  }

  auto ParseEventId(const std::string& line) -> size_t {
    std::istringstream iss{line};

    size_t event_id;
    std::string irrelevant;
    iss >> irrelevant >> event_id;
    return event_id;
  }

  auto ParseClientArrivedEvent(const std::string& line)
      -> Events::ClientArrivedEvent {
    std::istringstream iss{line};

    size_t event_id;
    std::string raw_created_at, client_name;
    iss >> raw_created_at >> event_id >> client_name;
    return Events::ClientArrivedEvent{std::move(client_name), string_to_time(raw_created_at)};
  }

  auto ParseClientTakeTableEvent(const std::string& line)
      -> Events::ClientTakeTableEvent {
    std::istringstream iss{line};


    size_t event_id, table_id;
    std::string raw_created_at, client_name;
    iss >> raw_created_at >> event_id >> client_name >> table_id;
    return Events::ClientTakeTableEvent{std::move(client_name), table_id, string_to_time(raw_created_at)};
  }

  auto ParseClientWaitingEvent(const std::string& line)
      -> Events::ClientWaitingEvent {
    std::istringstream iss{line};

    size_t event_id;
    std::string raw_created_at, client_name;
    iss >> raw_created_at >> event_id >> client_name;
    return Events::ClientWaitingEvent{std::move(client_name), string_to_time(raw_created_at)};
  }

  auto ParseClientLeftEvent(const std::string& line)
      -> Events::ClientLeftEvent {
    std::istringstream iss{line};

    size_t event_id;
    std::string raw_created_at, client_name;
    iss >> raw_created_at >> event_id >> client_name;
    return Events::ClientLeftEvent{std::move(client_name), string_to_time(raw_created_at)};
  }
}// namespace ComputerClub::IO