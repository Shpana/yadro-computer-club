#ifndef YADRO_COMPUTER_CLUB_SERIALIZING_HPP
#define YADRO_COMPUTER_CLUB_SERIALIZING_HPP

#include "events/events.hpp"
#include "io/utils/time_converts.hpp"

#include <sstream>

namespace ComputerClub::IO {
#define COMPUTER_CLUB_EVENT_EXTERNAL(Id, Name) \
  template<size_t event_id>                    \
  auto Serialize##Name##Event(const Events::Name##Event& event)->std::string;
#define COMPUTER_CLUB_EVENT_INTERNAL(Id, Name) \
  template<size_t event_id>                    \
  auto Serialize##Name##Event(const Events::Name##Event& event)->std::string;
#include "events/events.def"
}// namespace ComputerClub::IO

namespace ComputerClub::IO {
  template<size_t event_id>
  auto SerializeClientArrivedEvent(const Events::ClientArrivedEvent& event)
      -> std::string {
    std::ostringstream oss;
    oss << time_to_string(event.created_at);
    oss << ' ';
    oss << event_id;
    oss << ' ';
    oss << event.client_name;
    return oss.str();
  }

  template<size_t event_id>
  auto SerializeClientTakeTableEvent(const Events::ClientTakeTableEvent& event)
      -> std::string {
    std::ostringstream oss;
    oss << time_to_string(event.created_at);
    oss << ' ';
    oss << event_id;
    oss << ' ';
    oss << event.client_name;
    oss << ' ';
    oss << event.table_id;
    return oss.str();
  }

  template<size_t event_id>
  auto SerializeClientWaitingEvent(const Events::ClientWaitingEvent& event)
      -> std::string {
    std::ostringstream oss;
    oss << time_to_string(event.created_at);
    oss << ' ';
    oss << event_id;
    oss << ' ';
    oss << event.client_name;
    return oss.str();
  }

  template<size_t event_id>
  auto SerializeClientLeftEvent(const Events::ClientLeftEvent& event)
      -> std::string {
    std::ostringstream oss;
    oss << time_to_string(event.created_at);
    oss << ' ';
    oss << event_id;
    oss << ' ';
    oss << event.client_name;
    return oss.str();
  }

  template<size_t event_id>
  auto SerializeClientTakeTableInternalEvent(const Events::ClientTakeTableInternalEvent& event)
      -> std::string {
    std::ostringstream oss;
    oss << time_to_string(event.created_at);
    oss << ' ';
    oss << event_id;
    oss << ' ';
    oss << event.client_name;
    oss << ' ';
    oss << event.table_id;
    return oss.str();
  }

  template<size_t event_id>
  auto SerializeClientLeftInternalEvent(const Events::ClientLeftInternalEvent& event)
      -> std::string {
    std::ostringstream oss;
    oss << time_to_string(event.created_at);
    oss << ' ';
    oss << event_id;
    oss << ' ';
    oss << event.client_name;
    return oss.str();
  }

  template<size_t event_id>
  auto SerializeErrorEvent(const Events::ErrorEvent& event)
      -> std::string {
    std::ostringstream oss;
    oss << time_to_string(event.created_at);
    oss << ' ';
    oss << event_id;
    if (event.message.has_value()) {
      oss << ' ';
      oss << event.message.value();
    }
    return oss.str();
  }
}// namespace ComputerClub::IO

#endif// YADRO_COMPUTER_CLUB_SERIALIZING_HPP
