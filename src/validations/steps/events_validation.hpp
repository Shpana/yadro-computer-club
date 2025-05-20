#ifndef YADRO_COMPUTER_CLUB_EVENTS_VALIDATION_HPP
#define YADRO_COMPUTER_CLUB_EVENTS_VALIDATION_HPP

#include "validations/validation_pipeline.hpp"

namespace ComputerClub::Validation {
  class EventsValidationStep : public ValidationStep {
  public:
    auto Validate(std::istream& input) -> ValidationResult override;
  };
}

#endif// YADRO_COMPUTER_CLUB_EVENTS_VALIDATION_HPP
