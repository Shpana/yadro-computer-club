#include "events_validation.hpp"

#include "io/parsing.hpp"

#include <regex>

namespace ComputerClub::Validation {
  namespace {
    const std::string kTimeRegex = "(0[0-9]|1[0-9]|2[0-3]):[0-5][0-9]";
    const std::string kPositiveIntegerRegex = "[1-9][0-9]*";
    const std::string kClientNameRegex = "[a-z0-9_-]+";
  }// namespace

  static auto GetClientArrivedEventRegex() -> std::string {
    std::ostringstream oss;
    oss << '^';
    oss << kTimeRegex;
    oss << ' ';
    oss << '1';
    oss << ' ';
    oss << kClientNameRegex;
    oss << '$';
    return oss.str();
  }

  static auto GetClientTakeTableEventRegex() -> std::string {
    std::ostringstream oss;
    oss << '^';
    oss << kTimeRegex;
    oss << ' ';
    oss << '2';
    oss << ' ';
    oss << kClientNameRegex;
    oss << ' ';
    oss << kPositiveIntegerRegex;
    oss << '$';
    return oss.str();
  }

  static auto GetClientWaitingEventRegex() -> std::string {
    std::ostringstream oss;
    oss << '^';
    oss << kTimeRegex;
    oss << ' ';
    oss << '3';
    oss << ' ';
    oss << kClientNameRegex;
    oss << '$';
    return oss.str();
  }

  static auto GetClientLeftEventRegex() -> std::string {
    std::ostringstream oss;
    oss << '^';
    oss << kTimeRegex;
    oss << ' ';
    oss << '4';
    oss << ' ';
    oss << kClientNameRegex;
    oss << '$';
    return oss.str();
  }

  static auto IsValidEventLine(const std::string& line) -> bool {
    std::ostringstream oss;
    oss << '^';
    oss << '(';
    oss << GetClientArrivedEventRegex();
    oss << '|';
    oss << GetClientTakeTableEventRegex();
    oss << '|';
    oss << GetClientWaitingEventRegex();
    oss << '|';
    oss << GetClientLeftEventRegex();
    oss << ')';
    oss << '$';
    return std::regex_match(line, std::regex(oss.str()));
  }

  ValidationResult EventsValidationStep::Validate(std::istream& input) {
    input.clear();
    input.seekg(0);

    std::string line;
    Events::Context::Spec spec = IO::ParseSpec(input);
    time_t previous_created_at = 0;

    while (std::getline(input, line)) {
      if (!IsValidEventLine(line))
        return ValidationResult{.is_ok = false, .line_with_error = line};

      auto event_id = IO::ParseEventId(line);
      switch (event_id) {
        case 1: {
          auto event = IO::ParseClientArrivedEvent(line);
          if (event.created_at < previous_created_at)
            return ValidationResult{.is_ok = false, .line_with_error = line};
          previous_created_at = event.created_at;
          break;
        }
        case 2: {
          auto event = IO::ParseClientTakeTableEvent(line);
          if (event.created_at < previous_created_at)
            return ValidationResult{.is_ok = false, .line_with_error = line};
          if (!(1 <= event.table_id && event.table_id <= spec.tables_count))
            return ValidationResult{.is_ok = false, .line_with_error = line};
          previous_created_at = event.created_at;
          break;
        }
        case 3: {
          auto event = IO::ParseClientWaitingEvent(line);
          if (event.created_at < previous_created_at)
            return ValidationResult{.is_ok = false, .line_with_error = line};
          previous_created_at = event.created_at;
          break;
        }
        case 4: {
          auto event = IO::ParseClientLeftEvent(line);
          if (event.created_at < previous_created_at)
            return ValidationResult{.is_ok = false, .line_with_error = line};
          previous_created_at = event.created_at;
          break;
        }
        default:
          break;
      }
    }
    return ValidationResult{.is_ok = true};
  }
}