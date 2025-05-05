#include "processor.hpp"

#include "io/parsing.hpp"
#include "io/serializing.hpp"
#include "io/utils/time_converts.hpp"

#include <algorithm>
#include <iostream>

Processor::Processor(const Context& context, std::istream& input, std::ostream& output)
    : _context(context), _input(input), _output(output) {
  _accountant = std::make_shared<Accountant>(context.tables_count);
  _client_registry = std::make_shared<ClientRegistry>();
  _table_registry = std::make_shared<TableRegistry>(context.tables_count, _accountant);
  _handler = std::make_shared<EventHandler>(_context, _table_registry, _client_registry, this);
}

void Processor::run() {
  _output << time_to_string(_context.start_time) << '\n';
  _process_events();

  auto client_to_unpin = _table_registry->get_all_pinned_clients();
  std::sort(client_to_unpin.begin(), client_to_unpin.end());
  for (const auto& client: client_to_unpin) {
    _table_registry->unpin_client(client, _context.end_time);

    auto event = ClientLeftEvent{11, _context.end_time, client};
    process_event(event);
  }

  _output << time_to_string(_context.end_time) << '\n';

  auto report = _accountant->prepare_report(_context.price_per_hour);
  for (auto [key, value]: report) {
    _output << key << ' '
            << value.revenue << ' '
            << time_to_string(value.occupied_time) << '\n';
  }
}

template<class TEvent>
void Processor::process_event(const TEvent& event) {
  _output << serialize_event(event) << '\n';
  auto result = _handler->handle<TEvent>(event);

  if (!result.is_ok) {
    auto error_event = ErrorEvent{13, result.created_at, result.message};
    process_event(error_event);
  }
}

void Processor::_process_events() {
  std::string line;
  while (std::getline(_input, line)) {
    _process_event_line(line);
  }
}

void Processor::_process_event_line(const std::string& line) {
  auto event_id = parse_event_id_from_line(line);

  switch (event_id) {
    case 1: {
      auto event = parse_event_from_line<ClientArrivedEvent>(line);
      process_event(event);
      break;
    }
    case 2: {
      auto event = parse_event_from_line<ClientTakeTableEvent>(line);
      process_event(event);
      break;
    }
    case 3: {
      auto event = parse_event_from_line<ClientWaitingEvent>(line);
      process_event(event);
      break;
    }
    case 4: {
      auto event = parse_event_from_line<ClientLeftEvent>(line);
      process_event(event);
      break;
    }
    default: {
      std::cerr << "Unexpected event id" << std::endl;
      return;
    }
  }
}
