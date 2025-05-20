#include <fstream>
#include <iostream>

#include "src/io/parsing.hpp"
#include "root.hpp"

auto RunComputerClub(
    std::istream& input, std::ostream& output) -> void {
  auto spec = ComputerClub::IO::ParseSpec(input);
  auto root = ComputerClub::Root(input, output, spec);
  root.Run();
}

int main(int argc, char* argv[]) {
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
