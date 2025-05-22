#include "gtest/gtest.h"

#include "utils/utils.hpp"

#include "validations/validation_pipeline.hpp"

using namespace ComputerClub;

struct ValidationTestsParams {
  std::filesystem::path filepath;
  bool is_ok;
  std::optional<std::string> line_with_error;
};

class ValidationTests : public testing::TestWithParam<ValidationTestsParams> {};

TEST_P(ValidationTests, validation) {
  auto params = GetParam();

  auto is = Utils::LoadAsStringStream(params.filepath);
  auto pipeline = Validation::ValidationPipeline::CreateWithBasicSteps(is);
  auto result = pipeline.Validate();

  EXPECT_EQ(result.is_ok, params.is_ok);
  if (!params.is_ok) {
    EXPECT_EQ(result.line_with_error, params.line_with_error);
  }
}

INSTANTIATE_TEST_SUITE_P(
    validation,
    ValidationTests,
    testing::Values(
        ValidationTestsParams{
            .filepath = Utils::kStaticFilesPath / "input/correct.txt",
            .is_ok = true,
            .line_with_error = std::nullopt},
        ValidationTestsParams{
            .filepath = Utils::kStaticFilesPath / "input/time_not_increasing.txt",
            .is_ok = false,
            .line_with_error = "00:00 1 roman"},
        ValidationTestsParams{
            .filepath = Utils::kStaticFilesPath / "input/table_id_out_of_range.txt",
            .is_ok = false,
            .line_with_error = "00:00 2 roman 2"},
        ValidationTestsParams{
            .filepath = Utils::kStaticFilesPath / "input/event_id_out_of_range.txt",
            .is_ok = false,
            .line_with_error = "00:00 5 roman"},
        ValidationTestsParams{
            .filepath = Utils::kStaticFilesPath / "input/invalid_client_name.txt",
            .is_ok = false,
            .line_with_error = "00:00 1 roman:roman"},
        ValidationTestsParams{
            .filepath = Utils::kStaticFilesPath / "input/invalid_event_body_1.txt",
            .is_ok = false,
            .line_with_error = "00:00 1 roman 1"},
        ValidationTestsParams{
            .filepath = Utils::kStaticFilesPath / "input/invalid_event_body_2.txt",
            .is_ok = false,
            .line_with_error = "00:00 2 roman"},
        ValidationTestsParams{
            .filepath = Utils::kStaticFilesPath / "input/invalid_event_body_3.txt",
            .is_ok = false,
            .line_with_error = "00:00 3 roman 1"},
        ValidationTestsParams{
            .filepath = Utils::kStaticFilesPath / "input/invalid_event_body_4.txt",
            .is_ok = false,
            .line_with_error = "00:00 4 roman 1"}));