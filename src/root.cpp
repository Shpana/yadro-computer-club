#include "root.hpp"

#include "io/parsing.hpp"
#include "io/utils/time_converts.hpp"

#include <algorithm>

namespace ComputerClub {
  Root::Root(std::istream& is, std::ostream& os, const Events::Context::Spec& spec)
      : is_(is), os_(os), context_(spec,
                                   this,
                                   std::make_shared<Registries::Accountant>(spec.tables_count),
                                   std::make_shared<Registries::ClientRegistry>(),
                                   std::make_shared<Registries::TableRegistry>(spec.tables_count)) {}

  auto Root::Run() -> void {
    os_ << time_to_string(context_.start_time()) << '\n';
    ProcessDayCycle();
    os_ << time_to_string(context_.end_time()) << '\n';

    auto report = context_.accountant()->CompileReport(context_.price_per_hour());
    for (auto [key, value]: report) {
      os_ << key << ' '
          << value.revenue << ' '
          << time_to_string(value.occupied_time) << '\n';
    }
  }

  auto Root::ProcessDayCycle() -> void {
    std::string line;
    while (std::getline(is_, line)) {
      auto event_id = IO::ParseEventId(line);

      switch (event_id) {
#define COMPUTER_CLUB_EVENT_EXTERNAL(Id, Name) \
  case Id: {                                   \
    auto event = IO::Parse##Name##Event(line); \
    Consume(event);                            \
    break;                                     \
  }
#include "events/events.def"
        default: {
          std::cerr << "Unexpected event id" << std::endl;
          return;
        }
      }
    }

    // Unpin all clients after closing
    auto client_to_unpin = context_.table_registry()->GetAllPinnedClients();
    std::sort(client_to_unpin.begin(), client_to_unpin.end());

    for (const auto& client: client_to_unpin) {
      auto event = Events::ClientLeftInternalEvent{client, context_.end_time()};
      Consume(event);
    }
  }
}// namespace ComputerClub