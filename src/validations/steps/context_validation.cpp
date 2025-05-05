#include "context_validation.hpp"

#include <regex>

namespace {
  namespace regex {
    std::string correct_time_format = "(0[0-9]|1[0-9]|2[0-3]):[0-5][0-9]";
  }

  bool valid_positive_int(const std::string& line) {
    auto pattern = std::regex("^[1-9][0-9]*$");
    return std::regex_match(line, pattern);
  }

  bool valid_times_line(const std::string& line) {
    std::ostringstream oss;
    oss << '^';
    oss << regex::correct_time_format;
    oss << ' ';
    oss << regex::correct_time_format;
    oss << '$';
    return std::regex_match(line, std::regex(oss.str()));
  }
}

ValidationResult ContextValidationStep::validate(std::istream& input) {
  std::string line;

  std::getline(input, line);
  if (!valid_positive_int(line)) {
    return {false, line};
  }

  std::getline(input, line);
  if (!valid_times_line(line)) {
    return {false, line};
  }

  std::getline(input, line);
  if (!valid_positive_int(line)) {
    return {false, line};
  }
  return {true};
}