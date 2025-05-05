#include "event_handler.hpp"
#include "processor.hpp"

template<class TEvent>
EventResult EventHandler::handle(const TEvent& event) {
  throw std::runtime_error("Not implemented!");
}

template<>
EventResult EventHandler::handle<ClientArrivedEvent>(
    const ClientArrivedEvent& event) {
  const auto& client_name = event.client_name;

  if (_client_registry->has_client(client_name)) {
    return EventResult{false, "YouShallNotPass", event.created_at};
  }
  if (!(_context.start_time <= event.created_at && event.created_at <= _context.end_time)) {
    return EventResult{false, "NotOpenYet", event.created_at};
  }
  _client_registry->add_client(client_name);
  return EventResult{true};
}

template<>
EventResult EventHandler::handle<ClientTakeTableEvent>(
    const ClientTakeTableEvent& event) {
  if (event.id == 12) {
    return EventResult{true};
  }

  const auto& client_name = event.client_name;
  auto table_id = event.table_id;

  if (!_table_registry->is_table_available(table_id)) {
    return EventResult{false, "PlaceIsBusy", event.created_at};
  }
  if (!_client_registry->has_client(client_name)) {
    return EventResult{false, "ClientUnknown", event.created_at};
  }
  _table_registry->pin_client(client_name, table_id, event.created_at);
  return EventResult{true};
}

template<>
EventResult EventHandler::handle<ClientWaitingEvent>(
    const ClientWaitingEvent& event) {
  const auto& client_name = event.client_name;

  if (_table_registry->has_available_tables()) {
    return EventResult{false, "ICanWaitNoLonger!", event.created_at};
  }
  if (_client_registry->get_waiters_count() > _context.tables_count) {
    _processor->process_event(
        ClientLeftEvent{11, event.created_at, client_name});

    if (_client_registry->has_client(client_name)) {
      _client_registry->remove_client(client_name);
    }
    return EventResult{true};
  }
  _client_registry->add_waiter(event.client_name);
  return EventResult{true};
}

template<>
EventResult EventHandler::handle<ClientLeftEvent>(
    const ClientLeftEvent& event) {
  if (event.id == 11) {
    return EventResult{true};
  }

  const auto& client_name = event.client_name;

  if (!_client_registry->has_client(client_name)) {
    return EventResult{false, "ClientUnknown", event.created_at};
  }

  _client_registry->remove_client(client_name);
  if (_table_registry->is_client_pinned(client_name)) {
    auto table_id = _table_registry->get_pinned_table(client_name);
    _table_registry->unpin_client(client_name, event.created_at);

    if (_client_registry->has_any_waiter()) {
      const auto& waiter = _client_registry->pop_first_waiter();
      _table_registry->pin_client(waiter, table_id, event.created_at);

      _processor->process_event(
          ClientTakeTableEvent{12, event.created_at, waiter, table_id});
    }
  }
  return EventResult{true};
}

template<>
EventResult EventHandler::handle<ErrorEvent>(
    const ErrorEvent& event) {
  return EventResult{true};
}
