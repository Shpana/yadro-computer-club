#ifndef YADRO_COMPUTER_CLUB_EVENTS_VALIDATION_HPP
#define YADRO_COMPUTER_CLUB_EVENTS_VALIDATION_HPP

#include "events/event.hpp"
#include "validations/validation_pipeline.hpp"

class EventsValidationStep : public ValidationStep {
public:
  ValidationResult validate(std::istream& input) override;
};

#endif// YADRO_COMPUTER_CLUB_EVENTS_VALIDATION_HPP
