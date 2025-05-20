#include <fstream>
#include <iostream>

#include "src/io/parsing.hpp"
#include "validations/validation_pipeline.hpp"
#include "root.hpp"

using namespace ComputerClub;

auto RunComputerClub(std::istream& input, std::ostream& output) -> void {
  auto pipeline = Validation::ValidationPipeline::CreateWithBasicSteps(input);
  auto result = pipeline.Validate();
  if (!result.is_ok) {
    if (result.line_with_error.has_value()) {
      output << result.line_with_error.value();
      return;
    }
  }

  input.clear();
  input.seekg(0);

  auto spec = IO::ParseSpec(input);
  auto root = Root(input, output, spec);
  root.Run();
}

auto main(int argc, char* argv[]) -> int {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
    return 1;
  }

  std::fstream file;
  file.open(argv[1], std::ios::in);
  if (file.is_open()) {
    RunComputerClub(file, std::cout);
  } else {
    std::cerr << "Unable to open input file!" << std::endl;
    return 1;
  }
  file.close();
}
