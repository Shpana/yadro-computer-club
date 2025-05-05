#include "validation_pipeline.hpp"

ValidationPipeline::ValidationPipeline(
    std::istream& input, std::ostream& output)
    : _input(input), _output(output) {}

bool ValidationPipeline::run() {
  for (const auto& step: _steps) {
    auto result = step->validate(_input);

    if (!result.is_ok && result.line_with_error.has_value()) {
      _output << result.line_with_error.value();
      return false;
    }
  }
  return true;
}

void ValidationPipeline::add_step(
    const std::shared_ptr<ValidationStep>& step) {
  _steps.push_back(step);
}
