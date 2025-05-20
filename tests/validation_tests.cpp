#include "gtest/gtest.h"

#include "validations/steps/context_validation.hpp"
#include "validations/steps/events_validation.hpp"
#include "validations/validation_pipeline.hpp"

TEST(validation, correct) {
  std::stringstream input, output;
  input << "10\n";
  input << "00:00 23:59\n";
  input << "10\n";
  input << "00:00 1 roman\n";
  input << "01:00 1 roman\n";
  input << "02:00 1 roman";

  auto pipeline = ValidationPipeline(input, output);
  pipeline.add_step(std::make_shared<ContextValidationStep>());
  pipeline.add_step(std::make_shared<EventsValidationStep>());
  EXPECT_TRUE(pipeline.run());
}

TEST(validation, time_not_inc) {
  std::stringstream input, output;
  input << "10\n";
  input << "00:00 23:59\n";
  input << "10\n";
  input << "01:00 1 roman\n";
  input << "00:00 1 roman\n";

  auto pipeline = ValidationPipeline(input, output);
  pipeline.add_step(std::make_shared<ContextValidationStep>());
  pipeline.add_step(std::make_shared<EventsValidationStep>());
  EXPECT_FALSE(pipeline.run());

  std::string expected_line;
  std::getline(output, expected_line);
  EXPECT_EQ(expected_line, "00:00 1 roman");
}

TEST(validation, table_number_out_of_range) {
  std::stringstream input, output;
  input << "1\n";
  input << "00:00 23:59\n";
  input << "1\n";
  input << "00:00 2 roman 2\n";

  auto pipeline = ValidationPipeline(input, output);
  pipeline.add_step(std::make_shared<ContextValidationStep>());
  pipeline.add_step(std::make_shared<EventsValidationStep>());
  EXPECT_FALSE(pipeline.run());

  std::string expected_line;
  std::getline(output, expected_line);
  EXPECT_EQ(expected_line, "00:00 2 roman 2");
}

TEST(validation, event_id_out_of_range) {
  std::stringstream input, output;
  input << "1\n";
  input << "00:00 23:59\n";
  input << "1\n";
  input << "00:00 5 roman\n";

  auto pipeline = ValidationPipeline(input, output);
  pipeline.add_step(std::make_shared<ContextValidationStep>());
  pipeline.add_step(std::make_shared<EventsValidationStep>());
  EXPECT_FALSE(pipeline.run());

  std::string expected_line;
  std::getline(output, expected_line);
  EXPECT_EQ(expected_line, "00:00 5 roman");
}

TEST(validation, invalid_username) {
  std::stringstream input, output;
  input << "1\n";
  input << "00:00 23:59\n";
  input << "1\n";
  input << "00:00 1 roman:roman\n";

  auto pipeline = ValidationPipeline(input, output);
  pipeline.add_step(std::make_shared<ContextValidationStep>());
  pipeline.add_step(std::make_shared<EventsValidationStep>());
  EXPECT_FALSE(pipeline.run());

  std::string expected_line;
  std::getline(output, expected_line);
  EXPECT_EQ(expected_line, "00:00 1 roman:roman");
}

TEST(validation, invalid_event_body_1) {
  std::stringstream input, output;
  input << "1\n";
  input << "00:00 23:59\n";
  input << "1\n";
  input << "00:00 1 roman 1\n";

  auto pipeline = ValidationPipeline(input, output);
  pipeline.add_step(std::make_shared<ContextValidationStep>());
  pipeline.add_step(std::make_shared<EventsValidationStep>());
  EXPECT_FALSE(pipeline.run());

  std::string expected_line;
  std::getline(output, expected_line);
  EXPECT_EQ(expected_line, "00:00 1 roman 1");
}

TEST(validation, invalid_event_body_2) {
  std::stringstream input, output;
  input << "1\n";
  input << "00:00 23:59\n";
  input << "1\n";
  input << "00:00 2 roman\n";

  auto pipeline = ValidationPipeline(input, output);
  pipeline.add_step(std::make_shared<ContextValidationStep>());
  pipeline.add_step(std::make_shared<EventsValidationStep>());
  EXPECT_FALSE(pipeline.run());

  std::string expected_line;
  std::getline(output, expected_line);
  EXPECT_EQ(expected_line, "00:00 2 roman");
}

TEST(validation, invalid_event_body_3) {
  std::stringstream input, output;
  input << "1\n";
  input << "00:00 23:59\n";
  input << "1\n";
  input << "00:00 3 roman 1\n";

  auto pipeline = ValidationPipeline(input, output);
  pipeline.add_step(std::make_shared<ContextValidationStep>());
  pipeline.add_step(std::make_shared<EventsValidationStep>());
  EXPECT_FALSE(pipeline.run());

  std::string expected_line;
  std::getline(output, expected_line);
  EXPECT_EQ(expected_line, "00:00 3 roman 1");
}


TEST(validation, invalid_event_body_4) {
  std::stringstream input, output;
  input << "1\n";
  input << "00:00 23:59\n";
  input << "1\n";
  input << "00:00 4 roman 1\n";

  auto pipeline = ValidationPipeline(input, output);
  pipeline.add_step(std::make_shared<ContextValidationStep>());
  pipeline.add_step(std::make_shared<EventsValidationStep>());
  EXPECT_FALSE(pipeline.run());

  std::string expected_line;
  std::getline(output, expected_line);
  EXPECT_EQ(expected_line, "00:00 4 roman 1");
}
