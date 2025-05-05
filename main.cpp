#include <fstream>
#include <iostream>

#include "src/io/parsing.hpp"
#include "src/processor.hpp"

#include "src/validations/validation_pipeline.hpp"
#include "validations/steps/context_validation.hpp"
#include "validations/steps/events_validation.hpp"

void handle_computer_club(
    std::istream& input, std::ostream& output) {
  auto pipeline = ValidationPipeline(input, output);
  pipeline.add_step(std::make_shared<ContextValidationStep>());
  pipeline.add_step(std::make_shared<EventsValidationStep>());

  if (!pipeline.run())
    return;

  input.clear();
  input.seekg(0);

  auto context = parse_context(input);
  auto processor = Processor(context, input, output);
  processor.run();
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
    return 1;
  }

  std::fstream file;
  file.open(argv[1], std::ios::in);
  if (file.is_open()) {
    handle_computer_club(file, std::cout);
  } else {
    std::cerr << "Unable to open input file!" << std::endl;
    return 1;
  }
  file.close();
}
