#ifndef YADRO_COMPUTER_CLUB_ROOT_HPP
#define YADRO_COMPUTER_CLUB_ROOT_HPP

#include "events/context.hpp"
#include "events/event_consumer.hpp"
#include "events/events.hpp"
#include "events/handle_events.hpp"

#include "io/serializing.hpp"

#include <iostream>

namespace ComputerClub {
  class Root {
  public:
    Root(std::istream& is, std::ostream& os, const Events::Context::Spec& spec);
    auto Run() -> void;

  private:
    auto ProcessDayCycle() -> void;

  private:
    std::istream& is_;
    std::ostream& os_;
    Events::Context context_;
  };
}// namespace ComputerClub

#endif//YADRO_COMPUTER_CLUB_ROOT_HPP
