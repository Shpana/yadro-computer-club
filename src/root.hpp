#ifndef YADRO_COMPUTER_CLUB_ROOT_HPP
#define YADRO_COMPUTER_CLUB_ROOT_HPP

#include "events/context.hpp"
#include "events/event_consumer.hpp"
#include "events/events.hpp"
#include "events/handle_events.hpp"

#include "io/serializing.hpp"

#include <iostream>

namespace ComputerClub {
  class Root : public Events::EventConsumer {
  public:
    Root(std::istream& is, std::ostream& os, const Events::Context::Spec& spec);
    auto Run() -> void;

#define COMPUTER_CLUB_EVENT_EXTERNAL(Id, Name)                      \
  auto Consume(const Events::Name##Event& event) -> void override { \
    os_ << IO::Serialize##Name##Event<Id>(event) << '\n';           \
    Handle##Name##Event(context_, event);                           \
  }
#define COMPUTER_CLUB_EVENT_INTERNAL(Id, Name)                      \
  auto Consume(const Events::Name##Event& event) -> void override { \
    os_ << IO::Serialize##Name##Event<Id>(event) << '\n';           \
    Handle##Name##Event(context_, event);                           \
  }
#include "events/events.def"
  private:
    auto ProcessDayCycle() -> void;

  private:
    std::istream& is_;
    std::ostream& os_;
    Events::Context context_;
  };
}// namespace ComputerClub

#endif//YADRO_COMPUTER_CLUB_ROOT_HPP
