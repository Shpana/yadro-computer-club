#include "context_validation.hpp"

#include <regex>

namespace ComputerClub::Validation {
  namespace {
    const std::string kTimeRegex = "(0[0-9]|1[0-9]|2[0-3]):[0-5][0-9]";
    const std::string kPositiveIntegerRegex = "^[1-9][0-9]*$";
  }// namespace

  static auto IsValidPositiveIntegerLine(const std::string& line) -> bool {
    std::ostringstream oss;
    oss << '^';
    oss << kPositiveIntegerRegex;
    oss << '$';
    return std::regex_match(line, std::regex(oss.str()));
  }

  static auto IsValidTimesLine(const std::string& line) -> bool {
    std::ostringstream oss;
    oss << '^';
    oss << kTimeRegex;
    oss << ' ';
    oss << kTimeRegex;
    oss << '$';
    return std::regex_match(line, std::regex(oss.str()));
  }

  auto ContextValidationStep::Validate(std::istream& input) -> ValidationResult {
    std::string line;

    // Tables count line
    std::getline(input, line);
    if (!IsValidPositiveIntegerLine(line))
      return ValidationResult{.is_ok = false, .line_with_error = line};

    // Times line
    std::getline(input, line);
    if (!IsValidTimesLine(line))
      return ValidationResult{.is_ok = false, .line_with_error = line};

    // Table price per hour
    std::getline(input, line);
    if (!IsValidPositiveIntegerLine(line))
      return ValidationResult{.is_ok = false, .line_with_error = line};

    return ValidationResult{.is_ok = true};
  }
}// namespace ComputerClub::Validation