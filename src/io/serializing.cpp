#include "serializing.hpp"

#include "io/utils/times.hpp"

#include <sstream>

template<>
std::string serialize_event(const ClientArrivedEvent& event) {
  std::ostringstream oss;
  oss << to_string_time(event.created_at);
  oss << ' ';
  oss << event.id;
  oss << ' ';
  oss << event.client_name;
  return oss.str();
}

template<>
std::string serialize_event(const ClientTakeTableEvent& event) {
  std::ostringstream oss;
  oss << to_string_time(event.created_at);
  oss << ' ';
  oss << event.id;
  oss << ' ';
  oss << event.client_name;
  oss << ' ';
  oss << event.table_id;
  return oss.str();
}

template<>
std::string serialize_event(const ClientWaitingEvent& event) {
  std::ostringstream oss;
  oss << to_string_time(event.created_at);
  oss << ' ';
  oss << event.id;
  oss << ' ';
  oss << event.client_name;
  return oss.str();
}

template<>
std::string serialize_event(const ClientLeftEvent& event) {
  std::ostringstream oss;
  oss << to_string_time(event.created_at);
  oss << ' ';
  oss << event.id;
  oss << ' ';
  oss << event.client_name;
  return oss.str();
}


template<>
std::string serialize_event(const ErrorEvent& event) {
  std::ostringstream oss;
  oss << to_string_time(event.created_at);
  oss << ' ';
  oss << event.id;
  if (event.message.has_value()) {
    oss << ' ';
    oss << event.message.value();
  }
  return oss.str();
}