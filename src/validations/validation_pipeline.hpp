#ifndef YADRO_COMPUTER_CLUB_VALIDATION_PIPELINE_HPP
#define YADRO_COMPUTER_CLUB_VALIDATION_PIPELINE_HPP

#include <iostream>
#include <memory>
#include <optional>
#include <vector>

namespace ComputerClub::Validation {
  struct ValidationResult {
    bool is_ok{false};
    std::optional<std::string> line_with_error{std::nullopt};
  };

  class ValidationStep {
  public:
    virtual ~ValidationStep() = default;
    virtual auto Validate(std::istream& input) -> ValidationResult = 0;
  };

  class ValidationPipeline {
  public:
    static auto CreateWithBasicSteps(std::istream& is)
        -> ValidationPipeline;

    auto Validate() -> ValidationResult;
    auto AddStep(std::shared_ptr<ValidationStep>&& step) -> void;

  private:
    ValidationPipeline(std::istream& is) : is_(is) {}

  private:
    std::istream& is_;
    std::vector<std::shared_ptr<ValidationStep>> steps_;
  };
}// namespace ComputerClub::Validation

#endif// YADRO_COMPUTER_CLUB_VALIDATION_PIPELINE_HPP
