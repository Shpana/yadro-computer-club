#ifndef YADRO_COMPUTER_CLUB_HANDLE_EVENTS_HPP
#define YADRO_COMPUTER_CLUB_HANDLE_EVENTS_HPP

#include "context.hpp"

namespace ComputerClub::Events {
#define COMPUTER_CLUB_EVENT_EXTERNAL(Id, Name) \
  auto Handle##Name##Event(Context& context, const Name##Event& event)->void;
#define COMPUTER_CLUB_EVENT_INTERNAL(Id, Name) \
  auto Handle##Name##Event(Context& context, const Name##Event& event)->void;
#include "events.def"
}// namespace ComputerClub::Events

#endif// YADRO_COMPUTER_CLUB_HANDLE_EVENTS_HPP
