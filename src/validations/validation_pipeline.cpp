#include "validation_pipeline.hpp"

#include "steps/context_validation.hpp"
#include "steps/events_validation.hpp"

namespace ComputerClub::Validation {
  auto ValidationPipeline::CreateWithBasicSteps(std::istream& is)
      -> ComputerClub::Validation::ValidationPipeline {
    auto pipeline = ValidationPipeline(is);
    pipeline.AddStep(std::make_shared<ContextValidationStep>());
    pipeline.AddStep(std::make_shared<EventsValidationStep>());
    return pipeline;
  }

  auto ValidationPipeline::Validate() -> ValidationResult {
    for (const auto& step: steps_) {
      auto result = step->Validate(is_);

      if (!result.is_ok && result.line_with_error.has_value()) {
        return result;
      }
    }
    return ValidationResult{.is_ok = true};
  }

  auto ValidationPipeline::AddStep(std::shared_ptr<ValidationStep>&& step) -> void {
    steps_.push_back(step);
  }
}// namespace ComputerClub::Validation