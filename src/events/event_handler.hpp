#ifndef YADRO_COMPUTER_CLUB_EVENT_HANDLER_HPP
#define YADRO_COMPUTER_CLUB_EVENT_HANDLER_HPP

#include "context.hpp"
#include "event.hpp"
#include "registries/client_registry.hpp"
#include "registries/table_registry.hpp"

#include <stdexcept>
#include <memory>
#include <optional>
#include <string>

struct EventResult {
  bool is_ok;
  std::optional<std::string> message;
  time_t created_at;

  EventResult() = delete;
  EventResult(bool _is_ok, const std::string& _message, time_t _created_at)
      : is_ok(_is_ok), message(_message), created_at(_created_at) {}
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
  EventResult handle(const TEvent& event);

private:
  const Context& _context;
  const std::shared_ptr<TableRegistry>& _table_registry;
  const std::shared_ptr<ClientRegistry>& _client_registry;
};

#endif// YADRO_COMPUTER_CLUB_EVENT_HANDLER_HPP
