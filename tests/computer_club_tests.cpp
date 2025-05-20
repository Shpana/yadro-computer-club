#include "gtest/gtest.h"

#include "io/parsing.hpp"
#include "root.hpp"

#include <filesystem>
#include <fstream>

namespace {
#ifdef STATIC_FILES_PATH
  std::filesystem::path static_files_path{STATIC_FILES_PATH};
#endif
}// namespace

std::ostringstream load_expected_output(
    const std::filesystem::path& filepath) {
  std::fstream expected_output;
  expected_output.open(filepath, std::ios::in);

  std::string line;
  std::ostringstream expected_oss;
  while (std::getline(expected_output, line))
    expected_oss << line << '\n';
  expected_output.close();

  return expected_oss;
}

TEST(computer_club, demo) {
  std::fstream input;
  input.open(static_files_path / "input_1.txt", std::ios::in);
  std::ostringstream output;

  auto spec = ComputerClub::IO::ParseSpec(input);
  auto root = ComputerClub::Root(input, output, spec);
  root.Run();

  input.close();

  auto expected =
      load_expected_output(static_files_path / "expected_output_1.txt");
  EXPECT_EQ(output.str(), expected.str());
}

TEST(computer_club, waiters_overflow) {
  std::fstream input;
  input.open(static_files_path / "input_2.txt", std::ios::in);

  std::ostringstream output;

  auto spec = ComputerClub::IO::ParseSpec(input);
  auto root = ComputerClub::Root(input, output, spec);
  root.Run();

  input.close();

  auto expected =
      load_expected_output(static_files_path / "expected_output_2.txt");
  EXPECT_EQ(output.str(), expected.str());
}

TEST(computer_club, unknown_clients) {
  std::fstream input;
  input.open(static_files_path / "input_3.txt", std::ios::in);

  std::ostringstream output;

  auto spec = ComputerClub::IO::ParseSpec(input);
  auto root = ComputerClub::Root(input, output, spec);
  root.Run();

  input.close();

  auto expected =
      load_expected_output(static_files_path / "expected_output_3.txt");
  EXPECT_EQ(output.str(), expected.str());
}