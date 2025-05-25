#include "gtest/gtest.h"

#include "utils/utils.hpp"

#include "io/parsing.hpp"
#include "root.hpp"

using namespace ComputerClub;

class DayProcessingTests : public testing::TestWithParam<
                               std::pair<std::filesystem::path, std::filesystem::path>> {};

TEST_P(DayProcessingTests, day_processing) {
  auto paths = GetParam();

  auto is = Utils::LoadAsStringStream(paths.first);
  std::stringstream os{};

  auto spec = IO::ParseSpec(is);
  auto root = Root(is, os, spec);
  root.Run();

  auto expected = Utils::LoadAsStringStream(paths.second);
  EXPECT_EQ(os.str(), expected.str());
}

INSTANTIATE_TEST_SUITE_P(
    day_processing,
    DayProcessingTests,
    testing::Values(
        std::pair{Utils::kStaticFilesPath / "input/1.txt", Utils::kStaticFilesPath / "output/1.txt"},
        std::pair{Utils::kStaticFilesPath / "input/2.txt", Utils::kStaticFilesPath / "output/2.txt"},
        std::pair{Utils::kStaticFilesPath / "input/3.txt", Utils::kStaticFilesPath / "output/3.txt"}));