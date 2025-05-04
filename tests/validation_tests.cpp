#include "gtest/gtest.h"

#include "validation.hpp"

TEST(validation, time_format) {
  EXPECT_TRUE(is_valid_time_format("22:22"));
  EXPECT_TRUE(is_valid_time_format("02:50"));

  EXPECT_FALSE(is_valid_time_format("24:30"));
  EXPECT_FALSE(is_valid_time_format("00:60"));
  EXPECT_FALSE(is_valid_time_format("24:3"));
  EXPECT_FALSE(is_valid_time_format("2:30"));
  EXPECT_FALSE(is_valid_time_format("20;30"));
}

TEST(validation, username) {
  EXPECT_TRUE(is_valid_username("roman"));
  EXPECT_TRUE(is_valid_username("roman2025"));
  EXPECT_TRUE(is_valid_username("roman_2025"));
  EXPECT_TRUE(is_valid_username("roman-kozlov"));

  EXPECT_FALSE(is_valid_username("roman!"));
  EXPECT_FALSE(is_valid_username("rOman"));
  EXPECT_FALSE(is_valid_username("roman(shpana)"));
}

TEST(validation, positive_integer) {
  EXPECT_TRUE(is_valid_positive_integer("100"));
  EXPECT_TRUE(is_valid_positive_integer("505"));

  EXPECT_FALSE(is_valid_positive_integer("010"));
  EXPECT_FALSE(is_valid_positive_integer("-10"));
  EXPECT_FALSE(is_valid_positive_integer("0"));
}


TEST(validation, correct) {
  std::stringstream input, output;
  input << "10\n";
  input << "00:00 23:59\n";
  input << "10\n";
  input << "00:00 1 roman\n";
  input << "01:00 1 roman\n";
  input << "02:00 1 roman";

  EXPECT_TRUE(is_valid(input, output));
}

TEST(validation, time_not_inc) {
  std::stringstream input, output;
  input << "10\n";
  input << "00:00 23:59\n";
  input << "10\n";
  input << "01:00 1 roman\n";
  input << "00:00 1 roman\n";

  EXPECT_FALSE(is_valid(input, output));

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

  EXPECT_FALSE(is_valid(input, output));

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

  EXPECT_FALSE(is_valid(input, output));

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

  EXPECT_FALSE(is_valid(input, output));

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

  EXPECT_FALSE(is_valid(input, output));

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

  EXPECT_FALSE(is_valid(input, output));

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

  EXPECT_FALSE(is_valid(input, output));

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

  EXPECT_FALSE(is_valid(input, output));

  std::string expected_line;
  std::getline(output, expected_line);
  EXPECT_EQ(expected_line, "00:00 4 roman 1");
}
