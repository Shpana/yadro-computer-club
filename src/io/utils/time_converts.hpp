#ifndef YADRO_COMPUTER_CLUB_TIME_CONVERTS_HPP
#define YADRO_COMPUTER_CLUB_TIME_CONVERTS_HPP

#include <string>

time_t string_to_time(const std::string& time);
std::string time_to_string(time_t time);

#endif// YADRO_COMPUTER_CLUB_TIME_CONVERTS_HPP
