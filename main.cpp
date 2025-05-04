#include <fstream>
#include <iostream>
#include <optional>

#include "src/times.hpp"
#include "src/validation.hpp"

void read_next_event(std::istream& is) {
  std::string time_raw;
  is >> time_raw;
  size_t event_id;
  is >> event_id;
}

struct Event {
  time_t created_at;
  size_t id;
  std::string username;
  std::optional<size_t> table_id;
};

void handle_computer_club(std::istream& input, std::ostream& output) {
  if (!is_valid(input, output))
    return;
  input.seekg(0, std::ios::beg);
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
