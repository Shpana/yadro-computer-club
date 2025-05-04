#ifndef YADRO_COMPUTER_CLUB_PARSING_HPP
#define YADRO_COMPUTER_CLUB_PARSING_HPP

#include "event.hpp"
#include "times.hpp"

#include <string>
#include <sstream>

size_t parse_event_id_from_line(const std::string& line) {
  std::istringstream iss{line};

  size_t event_id;
  std::string irrelevant;
  iss >> irrelevant >> event_id;
  return event_id;
}

template<class TEvent>
TEvent parse_from_line(const std::string& line);

template<>
ClientArrivedEvent parse_from_line(const std::string& line) {
  std::istringstream iss{line};

  size_t event_id;
  std::string raw_created_at, client_name;
  iss >> raw_created_at >> event_id >> client_name;
  return ClientArrivedEvent{
      event_id, to_time(raw_created_at), std::move(client_name)};
}

template<>
ClientTakeTableEvent parse_from_line(const std::string& line) {
  std::istringstream iss{line};

  size_t event_id, table_id;
  std::string raw_created_at, client_name;
  iss >> raw_created_at >> event_id >> client_name >> table_id;
  return ClientTakeTableEvent{
      event_id, to_time(raw_created_at), std::move(client_name), table_id};
}

template<>
ClientWaitingEvent parse_from_line(const std::string& line) {
  std::istringstream iss{line};

  size_t event_id;
  std::string raw_created_at, client_name;
  iss >> raw_created_at >> event_id >> client_name;
  return ClientWaitingEvent{
      event_id, to_time(raw_created_at), std::move(client_name)};
}

template<>
ClientLeftEvent parse_from_line(const std::string& line) {
  std::istringstream iss{line};

  size_t event_id;
  std::string raw_created_at, client_name;
  iss >> raw_created_at >> event_id >> client_name;
  return ClientLeftEvent{
      event_id, to_time(raw_created_at), std::move(client_name)};
}

#endif// YADRO_COMPUTER_CLUB_PARSING_HPP
