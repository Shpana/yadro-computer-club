#ifndef YADRO_COMPUTER_CLUB_SERIALIZING_HPP
#define YADRO_COMPUTER_CLUB_SERIALIZING_HPP

#include "events/event.hpp"

#include <string>

template<class TEvent>
std::string serialize_event(const TEvent& event);

#endif// YADRO_COMPUTER_CLUB_SERIALIZING_HPP
