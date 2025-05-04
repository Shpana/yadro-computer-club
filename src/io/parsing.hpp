#ifndef YADRO_COMPUTER_CLUB_PARSING_HPP
#define YADRO_COMPUTER_CLUB_PARSING_HPP

#include "events/context.hpp"

#include <sstream>
#include <string>

Context parse_context(std::istream& input);
size_t parse_event_id_from_line(const std::string& line);

template<class TEvent>
TEvent parse_event_from_line(const std::string& line);

#endif// YADRO_COMPUTER_CLUB_PARSING_HPP
