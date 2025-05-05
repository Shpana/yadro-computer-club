#ifndef YADRO_COMPUTER_CLUB_CONTEXT_VALIDATION_HPP
#define YADRO_COMPUTER_CLUB_CONTEXT_VALIDATION_HPP

#include "validations/validation_pipeline.hpp"

class ContextValidationStep : public ValidationStep {
public:
  ValidationResult validate(std::istream& input) override;
};

#endif// YADRO_COMPUTER_CLUB_CONTEXT_VALIDATION_HPP
