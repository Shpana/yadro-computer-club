#ifndef YADRO_COMPUTER_CLUB_EVENT_HPP
#define YADRO_COMPUTER_CLUB_EVENT_HPP

#include <ctime>
#include <string>
#include <optional>

struct Event {
  size_t id;
  time_t created_at;

  Event() = delete;
  Event(size_t _id, time_t _created_at)
      : id(_id), created_at(_created_at) {}
};

struct ClientArrivedEvent : public Event {
  const std::string& client_name;

  ClientArrivedEvent(size_t _id, time_t _created_at,
                     const std::string& _client_name)
      : Event(_id, _created_at), client_name(_client_name) {}
};

struct ClientTakeTableEvent : public Event {
  const std::string& client_name;
  size_t table_id;

  ClientTakeTableEvent(size_t _id, time_t _created_at,
                       const std::string& _client_name, size_t _table_id)
      : Event(_id, _created_at), client_name(_client_name), table_id(_table_id) {}
};

struct ClientWaitingEvent : public Event {
  const std::string& client_name;

  ClientWaitingEvent(size_t _id, time_t _created_at,
                     const std::string& _client_name)
      : Event(_id, _created_at), client_name(_client_name) {}
};

struct ClientLeftEvent : public Event {
  const std::string& client_name;

  ClientLeftEvent(size_t _id, time_t _created_at,
                  const std::string& _client_name)
      : Event(_id, _created_at), client_name(_client_name) {}
};

struct ErrorEvent : public Event {
  const std::optional<std::string>& message;

  ErrorEvent(size_t _id, time_t _created_at,
             const std::optional<std::string>& _message)
      : Event(_id, _created_at), message(_message) {}
};

#endif// YADRO_COMPUTER_CLUB_EVENT_HPP
