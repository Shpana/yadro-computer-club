#include <fstream>
#include <iostream>
#include <sstream>

#include "src/validation.hpp"
#include "src/times.hpp"
#include "src/events/context.hpp"

#include "src/processor.hpp"

void handle_computer_club(std::istream& input, std::ostream& output) {
  if (!is_valid(input, output))
    return;

  input.clear();
  input.seekg(0);

  std::string line;

  size_t tables_count;
  std::getline(input, line);
  tables_count = std::stoi(line);

  std::string raw_start_time, raw_end_time;
  std::getline(input, line);
  std::istringstream iss1{line};
  iss1 >> raw_start_time >> raw_end_time;

  size_t table_price_per_hour;
  std::getline(input, line);
  table_price_per_hour = std::stoi(line);

  auto context = Context{
      to_time(raw_start_time),
      to_time(raw_end_time),
      tables_count,
      table_price_per_hour
  };
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
