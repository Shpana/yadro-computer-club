#ifndef YADRO_COMPUTER_CLUB_EVENT_CONSUMER_HPP
#define YADRO_COMPUTER_CLUB_EVENT_CONSUMER_HPP

#include "events.hpp"

namespace ComputerClub::Events {
  class EventConsumer {
  public:
#define COMPUTER_CLUB_EVENT_EXTERNAL(Id, Name) \
  virtual auto Consume(const Name##Event& event) -> void = 0;
#define COMPUTER_CLUB_EVENT_INTERNAL(Id, Name) \
  virtual auto Consume(const Name##Event& event) -> void = 0;
#include "events.def"
  };
}// namespace ComputerClub::Events

#endif//YADRO_COMPUTER_CLUB_EVENT_CONSUMER_HPP
