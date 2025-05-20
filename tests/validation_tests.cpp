#include "gtest/gtest.h"

#include "validations/steps/context_validation.hpp"
#include "validations/steps/events_validation.hpp"
#include "validations/validation_pipeline.hpp"

using namespace ComputerClub;

TEST(validation, correct) {
  std::stringstream input;
  input << "10\n";
  input << "00:00 23:59\n";
  input << "10\n";
  input << "00:00 1 roman\n";
  input << "01:00 1 roman\n";
  input << "02:00 1 roman";

  auto pipeline = Validation::ValidationPipeline::CreateWithBasicSteps(input);
  EXPECT_TRUE(pipeline.Validate().is_ok);
}

TEST(validation, time_not_inc) {
  std::stringstream input;
  input << "10\n";
  input << "00:00 23:59\n";
  input << "10\n";
  input << "01:00 1 roman\n";
  input << "00:00 1 roman\n";

  auto pipeline = Validation::ValidationPipeline::CreateWithBasicSteps(input);
  auto result = pipeline.Validate();
  EXPECT_FALSE(result.is_ok);
  EXPECT_EQ(result.line_with_error, "00:00 1 roman");
}

TEST(validation, table_number_out_of_range) {
  std::stringstream input, output;
  input << "1\n";
  input << "00:00 23:59\n";
  input << "1\n";
  input << "00:00 2 roman 2\n";

  auto pipeline = Validation::ValidationPipeline::CreateWithBasicSteps(input);
  auto result = pipeline.Validate();
  EXPECT_FALSE(result.is_ok);
  EXPECT_EQ(result.line_with_error, "00:00 2 roman 2");
}

TEST(validation, event_id_out_of_range) {
  std::stringstream input, output;
  input << "1\n";
  input << "00:00 23:59\n";
  input << "1\n";
  input << "00:00 5 roman\n";

  auto pipeline = Validation::ValidationPipeline::CreateWithBasicSteps(input);
  auto result = pipeline.Validate();
  EXPECT_FALSE(result.is_ok);
  EXPECT_EQ(result.line_with_error, "00:00 5 roman");
}

TEST(validation, invalid_username) {
  std::stringstream input, output;
  input << "1\n";
  input << "00:00 23:59\n";
  input << "1\n";
  input << "00:00 1 roman:roman\n";

  auto pipeline = Validation::ValidationPipeline::CreateWithBasicSteps(input);
  auto result = pipeline.Validate();

  EXPECT_FALSE(result.is_ok);
  EXPECT_EQ(result.line_with_error, "00:00 1 roman:roman");
}

TEST(validation, invalid_event_body_1) {
  std::stringstream input, output;
  input << "1\n";
  input << "00:00 23:59\n";
  input << "1\n";
  input << "00:00 1 roman 1\n";

  auto pipeline = Validation::ValidationPipeline::CreateWithBasicSteps(input);
  auto result = pipeline.Validate();
  EXPECT_FALSE(result.is_ok);
  EXPECT_EQ(result.line_with_error, "00:00 1 roman 1");
}

TEST(validation, invalid_event_body_2) {
  std::stringstream input, output;
  input << "1\n";
  input << "00:00 23:59\n";
  input << "1\n";
  input << "00:00 2 roman\n";


  auto pipeline = Validation::ValidationPipeline::CreateWithBasicSteps(input);
  auto result = pipeline.Validate();
  EXPECT_FALSE(result.is_ok);
  EXPECT_EQ(result.line_with_error, "00:00 2 roman");
}

TEST(validation, invalid_event_body_3) {
  std::stringstream input, output;
  input << "1\n";
  input << "00:00 23:59\n";
  input << "1\n";
  input << "00:00 3 roman 1\n";

  auto pipeline = Validation::ValidationPipeline::CreateWithBasicSteps(input);
  auto result = pipeline.Validate();
  EXPECT_FALSE(result.is_ok);
  EXPECT_EQ(result.line_with_error, "00:00 3 roman 1");
}


TEST(validation, invalid_event_body_4) {
  std::stringstream input, output;
  input << "1\n";
  input << "00:00 23:59\n";
  input << "1\n";
  input << "00:00 4 roman 1\n";

  auto pipeline = Validation::ValidationPipeline::CreateWithBasicSteps(input);
  auto result = pipeline.Validate();
  EXPECT_FALSE(result.is_ok);
  EXPECT_EQ(result.line_with_error, "00:00 4 roman 1");
}
