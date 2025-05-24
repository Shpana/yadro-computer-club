#ifndef YADRO_COMPUTER_CLUB_EVENTS_HPP
#define YADRO_COMPUTER_CLUB_EVENTS_HPP

#include <ctime>
#include <optional>
#include <string>

namespace ComputerClub::Events {
  using TimePoint = time_t;

  struct Event {
    TimePoint created_at;

    Event(TimePoint created_at_)
        : created_at(created_at_) {}
  };

  struct ClientArrivedEvent : public Event {
    std::string client_name;

    ClientArrivedEvent(const std::string& client_name_,
                       TimePoint created_at_)
        : Event(created_at_), client_name(client_name_) {}
    ClientArrivedEvent(std::string&& client_name_,
                       TimePoint created_at_)
        : Event(created_at_), client_name(std::move(client_name_)) {}
  };

  struct ClientTakeTableEvent : public Event {
    std::string client_name;
    size_t table_id;

    ClientTakeTableEvent(const std::string& client_name_, size_t table_id_,
                         TimePoint created_at_)
        : Event(created_at_), client_name(client_name_), table_id(table_id_) {}
    ClientTakeTableEvent(std::string&& client_name_, size_t table_id_,
                         TimePoint created_at_)
        : Event(created_at_), client_name(std::move(client_name_)), table_id(table_id_) {}
  };

  struct ClientWaitingEvent : public Event {
    std::string client_name;

    ClientWaitingEvent(const std::string& client_name_,
                       TimePoint created_at_)
        : Event(created_at_), client_name(client_name_) {}
    ClientWaitingEvent(std::string&& client_name_,
                       TimePoint created_at_)
        : Event(created_at_), client_name(std::move(client_name_)) {}
  };

  struct ClientLeftEvent : public Event {
    std::string client_name;

    ClientLeftEvent(const std::string& client_name_,
                    TimePoint created_at_)
        : Event(created_at_), client_name(client_name_) {}
    ClientLeftEvent(std::string&& client_name_,
                    TimePoint created_at_)
        : Event(created_at_), client_name(std::move(client_name_)) {}
  };

  struct ClientLeftInternalEvent : public Event {
    std::string client_name;

    ClientLeftInternalEvent(const std::string& client_name_,
                            TimePoint created_at_)
        : Event(created_at_), client_name(client_name_) {}
    ClientLeftInternalEvent(std::string&& client_name_,
                            TimePoint created_at_)
        : Event(created_at_), client_name(std::move(client_name_)) {}
  };

  struct ClientTakeTableInternalEvent : public Event {
    std::string client_name;
    size_t table_id;

    ClientTakeTableInternalEvent(const std::string& client_name_, size_t table_id_,
                                 TimePoint created_at_)
        : Event(created_at_), client_name(client_name_), table_id(table_id_) {}
    ClientTakeTableInternalEvent(std::string&& client_name_, size_t table_id_,
                                 TimePoint created_at_)
        : Event(created_at_), client_name(std::move(client_name_)), table_id(table_id_) {}
  };

  struct ErrorEvent : public Event {
    std::optional<std::string> message;

    ErrorEvent(const std::optional<std::string>& message_,
               TimePoint created_at_)
        : Event(created_at_), message(message_) {}
  };
}// namespace ComputerClub::Events

#endif// YADRO_COMPUTER_CLUB_EVENTS_HPP
