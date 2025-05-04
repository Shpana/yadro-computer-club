#ifndef YADRO_COMPUTER_CLUB_EVENT_HANDLER_H
#define YADRO_COMPUTER_CLUB_EVENT_HANDLER_H

#include "context.hpp"
#include "event.hpp"
#include "registries/client_registry.hpp"
#include "registries/table_registry.hpp"

#include <memory>
#include <optional>
#include <string>

struct EventResult {
  bool is_ok;
  std::optional<std::string> message;

  EventResult() = delete;
  EventResult(bool _is_ok, const std::string& _message)
      : is_ok(_is_ok), message(_message) {}
  EventResult(bool _is_ok)
      : is_ok(_is_ok), message(std::nullopt) {}
};

class EventHandler {
public:
  EventHandler(const Context& context,
               const std::shared_ptr<TableRegistry>& table_registry,
               const std::shared_ptr<ClientRegistry>& client_registry)
      : _context(context),
        _table_registry(table_registry), _client_registry(client_registry) {}

  template<class TEvent>
  EventResult handle(const TEvent& event) {
    throw std::runtime_error("Handle is not implemented!");
  }

private:
  const Context& _context;
  const std::shared_ptr<TableRegistry>& _table_registry;
  const std::shared_ptr<ClientRegistry>& _client_registry;
};

template<>
EventResult EventHandler::handle<ClientArrivedEvent>(
    const ClientArrivedEvent& event) {
  const auto& client_name = event.client_name;

  if (_client_registry->has_client(client_name)) {
    return EventResult{false, "YouShallNotPass"};
  }
  if (!(_context.start_time <= event.created_at && event.created_at <= _context.end_time)) {
    return EventResult{false, "NotOpenYet"};
  }
  _client_registry->add_client(client_name);
  return EventResult{true};
}

template<>
EventResult EventHandler::handle<ClientTakeTableEvent>(
    const ClientTakeTableEvent& event) {
  const auto& client_name = event.client_name;
  auto table_id = event.table_id;

  if (!_table_registry->is_table_available(table_id)) {
    return EventResult{false, "PlaceIsBusy"};
  }
  if (!_client_registry->has_client(client_name)) {
    return EventResult{false, "ClientUnknown"};
  }
  _table_registry->pin_client(client_name, table_id);
  return EventResult{true};
}

template<>
EventResult EventHandler::handle<ClientWaitingEvent>(
    const ClientWaitingEvent& event) {
  const auto& client_name = event.client_name;

  if (_table_registry->has_available_tables()) {
    return EventResult{false, "ICanWaitNoLonger!"};
  }
  if (_client_registry->get_waiters_count() > _context.tables_count) {
    // TODO: Produce event
    return EventResult{true};
  }
  _client_registry->add_waiter(event.client_name);
  return EventResult{true};
}

template<>
EventResult EventHandler::handle<ClientLeftEvent>(
    const ClientLeftEvent& event) {
  const auto& client_name = event.client_name;

  if (!_client_registry->has_client(client_name)) {
    return EventResult{false, "ClientUnknown"};
  }
  _client_registry->remove_client(client_name);
  if (_table_registry->is_client_pinned(client_name)) {
    auto table_id = _table_registry->get_pinned_table(client_name);
    _table_registry->unpin_client(client_name);
    // TODO: Produce event
    const auto& waiter = _client_registry->pop_first_waiter();
    _table_registry->pin_client(waiter, table_id);
  }
  return EventResult{true};
}

template<>
EventResult EventHandler::handle<ErrorEvent>(
    const ErrorEvent& event) {
  return EventResult{true};
}

#endif// YADRO_COMPUTER_CLUB_EVENT_HANDLER_H
