#ifndef YADRO_COMPUTER_CLUB_CONTEXT_HPP
#define YADRO_COMPUTER_CLUB_CONTEXT_HPP

#include "events/event_consumer.hpp"
#include "registries/accountant.hpp"
#include "registries/client_registry.hpp"
#include "registries/table_registry.hpp"

#include <ctime>

namespace ComputerClub::Events {
  class Context {
  public:
    struct Spec {
      time_t start_time;
      time_t end_time;
      size_t tables_count;
      size_t price_per_hour;
    };

  public:
    Context(const Spec& spec,
            EventConsumer* consumer,
            std::shared_ptr<Registries::Accountant>&& accountant,
            std::shared_ptr<Registries::ClientRegistry>&& client_registry,
            std::shared_ptr<Registries::TableRegistry>&& table_registry)
        : spec_(spec),
          consumer_(consumer),
          accountant_(accountant),
          client_registry_(client_registry),
          table_registry_(table_registry) {}

    [[nodiscard]] auto start_time() const -> TimePoint { return spec_.start_time; }
    [[nodiscard]] auto end_time() const -> TimePoint { return spec_.end_time; }
    [[nodiscard]] auto tables_count() const -> size_t { return spec_.tables_count; }
    [[nodiscard]] auto price_per_hour() const -> size_t { return spec_.price_per_hour; }

    [[nodiscard]] auto consumer() const -> EventConsumer* { return consumer_; }
    [[nodiscard]] auto accountant() const
        -> std::shared_ptr<Registries::Accountant> { return accountant_; }
    [[nodiscard]] auto client_registry() const
        -> std::shared_ptr<Registries::ClientRegistry> { return client_registry_; }
    [[nodiscard]] auto table_registry() const
        -> std::shared_ptr<Registries::TableRegistry> { return table_registry_; }

  private:
    const Spec& spec_;

    // TODO: make smart pointer
    EventConsumer* consumer_;
    std::shared_ptr<Registries::Accountant> accountant_;
    std::shared_ptr<Registries::ClientRegistry> client_registry_;
    std::shared_ptr<Registries::TableRegistry> table_registry_;
  };
}// namespace ComputerClub::Events

#endif// YADRO_COMPUTER_CLUB_CONTEXT_HPP
