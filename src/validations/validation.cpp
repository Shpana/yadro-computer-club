#include "validation.hpp"

#include "io/utils/times.hpp"

#include <regex>
#include <sstream>

namespace {
  std::string reg_time_format = "(0[0-9]|1[0-9]|2[0-3]):[0-5][0-9]";
  std::string reg_username = "[a-z0-9_-]+";
  std::string reg_positive_integer = "[1-9][0-9]*";
}// namespace

bool is_valid_time_format(const std::string& raw_time) {
  std::ostringstream oss;
  oss << '^';
  oss << reg_time_format;
  oss << '$';
  return std::regex_match(raw_time, std::regex(oss.str()));
}

bool is_valid_username(const std::string& username) {
  std::ostringstream oss;
  oss << '^';
  oss << reg_username;
  oss << '$';
  return std::regex_match(username, std::regex(oss.str()));
}

bool is_valid_positive_integer(const std::string& raw) {
  std::ostringstream oss;
  oss << '^';
  oss << reg_positive_integer;
  oss << '$';
  return std::regex_match(raw, std::regex(oss.str()));
}

bool is_valid_tables_number_line(const std::string& line) {
  return is_valid_positive_integer(line);
}

bool is_valid_times_line(const std::string& line) {
  std::ostringstream oss;
  oss << '^';
  oss << reg_time_format;
  oss << ' ';
  oss << reg_time_format;
  oss << '$';
  return std::regex_match(line, std::regex(oss.str()));
}

bool is_valid_hour_cost_line(const std::string& line) {
  return is_valid_positive_integer(line);
}

bool is_valid_event_line(const std::string& line) {
  std::ostringstream oss;
  oss << '^';
  oss << reg_time_format;
  oss << ' ';
  oss << '(';
  oss << "[134]";
  oss << ' ';
  oss << reg_username;
  oss << '|';
  oss << "[2]";
  oss << ' ';
  oss << reg_username;
  oss << ' ';
  oss << reg_positive_integer;
  oss << ')';
  oss << '$';
  return std::regex_match(line, std::regex(oss.str()));
}

bool is_valid(std::istream& input, std::ostream& output) {
  std::string line;

  std::getline(input, line);
  if (!is_valid_tables_number_line(line)) {
    output << line;
    return false;
  }
  size_t tables_number = std::stoi(line);

  std::getline(input, line);
  if (!is_valid_times_line(line)) {
    output << line;
    return false;
  }

  std::getline(input, line);
  if (!is_valid_hour_cost_line(line)) {
    output << line;
    return false;
  }

  return is_valid_events(input, output, tables_number);
}

bool is_valid_events(
    std::istream& input, std::ostream& output, size_t tables_number) {
  std::string line;
  time_t previous_time = 0;

  while (std::getline(input, line)) {
    if (!is_valid_event_line(line)) {
      output << line;
      return false;
    }

    std::string raw_time;
    size_t event_id;
    std::string username;
    std::istringstream iss{line};
    iss >> raw_time >> event_id >> username;

    if (!is_valid_username(username)) {
      output << line;
      return false;
    }

    if (!(previous_time <= to_time(raw_time))) {
      output << line;
      return false;
    }
    previous_time = to_time(raw_time);

    if (!(1 <= event_id && event_id <= 4)) {
      output << line;
      return false;
    }

    if (event_id == 2) {
      size_t table_number;
      iss >> table_number;
      if (!(1 <= table_number && table_number <= tables_number)) {
        output << line;
        return false;
      }
    }
  }
  return true;
}
