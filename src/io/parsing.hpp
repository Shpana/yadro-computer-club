#ifndef YADRO_COMPUTER_CLUB_PARSING_HPP
#define YADRO_COMPUTER_CLUB_PARSING_HPP

#include <sstream>
#include <string>

#include "events/context.hpp"
#include "events/events.hpp"

namespace ComputerClub::IO {
  auto ParseSpec(std::istream& is) -> Events::Context::Spec;
  auto ParseEventId(const std::string& line) -> size_t;

#define COMPUTER_CLUB_EVENT_EXTERNAL(Id, Name) \
  auto Parse##Name##Event(const std::string& line)->Events::Name##Event;
#include "events/events.def"
}// namespace ComputerClub::IO

#endif// YADRO_COMPUTER_CLUB_PARSING_HPP
