#include "parsing.hpp"

#include "events/event.hpp"
#include "io/utils/times.hpp"

Context parse_context(std::istream& input) {
  Context context;

  std::string line;
  std::getline(input, line);
  context.tables_count = std::stoi(line);

  std::getline(input, line);
  std::istringstream iss{line};
  std::string raw_start_time, raw_end_time;
  iss >> raw_start_time >> raw_end_time;
  context.start_time = to_time(raw_start_time);
  context.end_time = to_time(raw_end_time);

  std::getline(input, line);
  context.price_per_hour = std::stoi(line);
  return context;
}

size_t parse_event_id_from_line(const std::string& line) {
  std::istringstream iss{line};

  size_t event_id;
  std::string irrelevant;
  iss >> irrelevant >> event_id;
  return event_id;
}

template<>
ClientArrivedEvent parse_event_from_line(const std::string& line) {
  std::istringstream iss{line};

  size_t event_id;
  std::string raw_created_at, client_name;
  iss >> raw_created_at >> event_id >> client_name;
  return ClientArrivedEvent{
      event_id, to_time(raw_created_at), std::move(client_name)};
}

template<>
ClientTakeTableEvent parse_event_from_line(const std::string& line) {
  std::istringstream iss{line};

  size_t event_id, table_id;
  std::string raw_created_at, client_name;
  iss >> raw_created_at >> event_id >> client_name >> table_id;
  return ClientTakeTableEvent{
      event_id, to_time(raw_created_at), std::move(client_name), table_id};
}

template<>
ClientWaitingEvent parse_event_from_line(const std::string& line) {
  std::istringstream iss{line};

  size_t event_id;
  std::string raw_created_at, client_name;
  iss >> raw_created_at >> event_id >> client_name;
  return ClientWaitingEvent{
      event_id, to_time(raw_created_at), std::move(client_name)};
}

template<>
ClientLeftEvent parse_event_from_line(const std::string& line) {
  std::istringstream iss{line};

  size_t event_id;
  std::string raw_created_at, client_name;
  iss >> raw_created_at >> event_id >> client_name;
  return ClientLeftEvent{
      event_id, to_time(raw_created_at), std::move(client_name)};
}
