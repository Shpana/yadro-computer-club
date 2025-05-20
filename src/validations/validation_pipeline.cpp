#include "validation_pipeline.hpp"

#include "validations/steps/validate_content.hpp"
#include "validations/steps/validate_format.hpp"

namespace ComputerClub::Validation {
  auto ValidationPipeline::CreateWithBasicSteps(std::istream& is)
      -> ComputerClub::Validation::ValidationPipeline {
    auto pipeline = ValidationPipeline(is);
    pipeline.AddStep(std::make_shared<FormatValidationStep>());
    pipeline.AddStep(std::make_shared<ContentValidationStep>());
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