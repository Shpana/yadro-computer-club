#ifndef YADRO_COMPUTER_CLUB_CONTEXT_VALIDATION_HPP
#define YADRO_COMPUTER_CLUB_CONTEXT_VALIDATION_HPP

#include "validations/validation_pipeline.hpp"

namespace ComputerClub::Validation {
  class ContextValidationStep : public ValidationStep {
  public:
    auto Validate(std::istream& is) -> ValidationResult override;
  };
}// namespace ComputerClub::Validation

#endif// YADRO_COMPUTER_CLUB_CONTEXT_VALIDATION_HPP
