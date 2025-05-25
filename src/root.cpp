#include "root.hpp"

#include "io/parsing.hpp"
#include "io/utils/time_converts.hpp"

#include <algorithm>

namespace ComputerClub {
  namespace {
    class RootConsumer final : public Events::EventConsumer {
    public:
      RootConsumer(std::ostream& os, Events::Context& context)
          : os_(os), context_(context) {}

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
      std::ostream& os_;
      Events::Context& context_;
    };
  }// namespace

  Root::Root(std::istream& is, std::ostream& os, const Events::Context::Spec& spec)
      : is_(is), os_(os), context_(spec,
                                   std::make_shared<RootConsumer>(os_, context_),
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
    context_.consumer()->Consume(event);       \
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
      context_.consumer()->Consume(event);
    }
  }
}// namespace ComputerClub