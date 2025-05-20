#include "events_validation.hpp"

#include "io/parsing.hpp"

#include <regex>

namespace {
  namespace regex {
    std::string correct_time_format = "(0[0-9]|1[0-9]|2[0-3]):[0-5][0-9]";
    std::string correct_client_name = "[a-z0-9_-]+";
    std::string correct_positive_int = "[1-9][0-9]*";

    template<class TEvent>
    [[nodiscard]] std::string get_event_regex_str();

    template<>
    [[nodiscard]] std::string get_event_regex_str<ClientArrivedEvent>() {
      std::ostringstream oss;
      oss << '^';
      oss << correct_time_format;
      oss << ' ';
      oss << '1';
      oss << ' ';
      oss << correct_client_name;
      oss << '$';
      return oss.str();
    }

    template<>
    [[nodiscard]] std::string get_event_regex_str<ClientTakeTableEvent>() {
      std::ostringstream oss;
      oss << '^';
      oss << correct_time_format;
      oss << ' ';
      oss << '2';
      oss << ' ';
      oss << correct_client_name;
      oss << ' ';
      oss << correct_positive_int;
      oss << '$';
      return oss.str();
    }

    template<>
    [[nodiscard]] std::string get_event_regex_str<ClientWaitingEvent>() {
      std::ostringstream oss;
      oss << '^';
      oss << correct_time_format;
      oss << ' ';
      oss << '3';
      oss << ' ';
      oss << correct_client_name;
      oss << '$';
      return oss.str();
    }

    template<>
    [[nodiscard]] std::string get_event_regex_str<ClientLeftEvent>() {
      std::ostringstream oss;
      oss << '^';
      oss << correct_time_format;
      oss << ' ';
      oss << '4';
      oss << ' ';
      oss << correct_client_name;
      oss << '$';
      return oss.str();
    }
  }// namespace regex

  bool valid_event_line(const std::string& line) {
    std::ostringstream oss;
    oss << '^';
    oss << '(';
    oss << regex::get_event_regex_str<ClientArrivedEvent>();
    oss << '|';
    oss << regex::get_event_regex_str<ClientTakeTableEvent>();
    oss << '|';
    oss << regex::get_event_regex_str<ClientWaitingEvent>();
    oss << '|';
    oss << regex::get_event_regex_str<ClientLeftEvent>();
    oss << ')';
    oss << '$';
    return std::regex_match(line, std::regex(oss.str()));
  }
}// namespace

ValidationResult EventsValidationStep::validate(std::istream& input) {
  std::string line;
  time_t previous_created_at = 0;

  input.clear();
  input.seekg(0);
  ContextDepr context = parse_context(input);

  while (std::getline(input, line)) {
    if (!valid_event_line(line)) {
      return {false, line};
    }

    auto event_id = parse_event_id_from_line(line);
    switch (event_id) {
      case 1: {
        auto event = parse_event_from_line<ClientArrivedEvent>(line);
        if (event.created_at < previous_created_at) {
          return {false, line};
        }
        previous_created_at = event.created_at;
        break;
      }
      case 2: {
        auto event = parse_event_from_line<ClientTakeTableEvent>(line);
        if (event.created_at < previous_created_at) {
          return {false, line};
        }
        previous_created_at = event.created_at;
        if (!(1 <= event.table_id && event.table_id <= context.tables_count)) {
          return {false, line};
        }
        break;
      }
      case 3: {
        auto event = parse_event_from_line<ClientWaitingEvent>(line);
        if (event.created_at < previous_created_at) {
          return {false, line};
        }
        previous_created_at = event.created_at;
        break;
      }
      case 4: {
        auto event = parse_event_from_line<ClientLeftEvent>(line);
        if (event.created_at < previous_created_at) {
          return {false, line};
        }
        previous_created_at = event.created_at;
        break;
      }
      default:
        break;
    }
  }
  return {true};
}
