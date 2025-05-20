#ifndef YADRO_COMPUTER_CLUB_VALIDATE_FORMAT_HPP
#define YADRO_COMPUTER_CLUB_VALIDATE_FORMAT_HPP

#include "validations/validation_pipeline.hpp"

namespace ComputerClub::Validation {
  class FormatValidationStep : public ValidationStep {
  public:
    auto Validate(std::istream& input) -> ValidationResult override {
      return ValidationResult{.is_ok = true};
    }
  };
}// namespace ComputerClub::Validation

#endif// YADRO_COMPUTER_CLUB_VALIDATE_FORMAT_HPP
