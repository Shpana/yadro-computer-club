#ifndef RUN_TESTS_UTILS_HPP
#define RUN_TESTS_UTILS_HPP

#include <filesystem>
#include <fstream>
#include <sstream>

namespace Utils {
#ifdef STATIC_FILES_PATH
  static const std::filesystem::path kStaticFilesPath{STATIC_FILES_PATH};
#endif

  static auto LoadAsStringStream(const std::filesystem::path& filepath) -> std::stringstream {
    std::fstream expected_output;
    expected_output.open(filepath, std::ios::in);

    std::string line;
    std::stringstream expected_oss;
    while (std::getline(expected_output, line))
      expected_oss << line << '\n';

    expected_output.close();
    return expected_oss;
  }
}// namespace Utils

#endif// RUN_TESTS_UTILS_HPP