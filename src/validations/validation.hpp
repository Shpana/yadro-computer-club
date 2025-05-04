#ifndef YADRO_COMPUTER_CLUB_VALIDATION_HPP
#define YADRO_COMPUTER_CLUB_VALIDATION_HPP

#include <iostream>
#include <string>

bool is_valid_time_format(const std::string& raw_time);
bool is_valid_username(const std::string& username);
bool is_valid_positive_integer(const std::string& raw);

bool is_valid_tables_number_line(const std::string& line);
bool is_valid_times_line(const std::string& line);
bool is_valid_hour_cost_line(const std::string& line);
bool is_valid_event_line(const std::string& line);

bool is_valid(std::istream& input, std::ostream& output);
bool is_valid_events(std::istream& input, std::ostream& output, size_t tables_number);

#endif// YADRO_COMPUTER_CLUB_VALIDATION_HPP
