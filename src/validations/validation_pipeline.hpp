#ifndef YADRO_COMPUTER_CLUB_VALIDATION_PIPELINE_HPP
#define YADRO_COMPUTER_CLUB_VALIDATION_PIPELINE_HPP

#include <iostream>
#include <memory>
#include <optional>
#include <vector>

struct ValidationResult {
  bool is_ok;
  std::optional<std::string> line_with_error;
};

class ValidationStep {
public:
  ~ValidationStep() = default;

  virtual ValidationResult validate(std::istream& input) = 0;
};

class ValidationPipeline {
public:
  ValidationPipeline(std::istream& input, std::ostream& output);

  bool run();
  void add_step(const std::shared_ptr<ValidationStep>& step);

private:
  std::istream& _input;
  std::ostream& _output;
  std::vector<std::shared_ptr<ValidationStep>> _steps;
};

#endif// YADRO_COMPUTER_CLUB_VALIDATION_PIPELINE_HPP
