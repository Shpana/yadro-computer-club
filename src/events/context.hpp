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
            std::unique_ptr<EventConsumer>&& consumer,
            std::unique_ptr<Registries::Accountant>&& accountant,
            std::unique_ptr<Registries::ClientRegistry>&& client_registry,
            std::unique_ptr<Registries::TableRegistry>&& table_registry)
        : spec_(spec),
          consumer_(std::move(consumer)),
          accountant_(std::move(accountant)),
          client_registry_(std::move(client_registry)),
          table_registry_(std::move(table_registry)) {}

    [[nodiscard]] auto start_time() const -> TimePoint { return spec_.start_time; }
    [[nodiscard]] auto end_time() const -> TimePoint { return spec_.end_time; }
    [[nodiscard]] auto tables_count() const -> size_t { return spec_.tables_count; }
    [[nodiscard]] auto price_per_hour() const -> size_t { return spec_.price_per_hour; }

    [[nodiscard]] auto consumer() const
        -> std::unique_ptr<EventConsumer> const& { return consumer_; }
    [[nodiscard]] auto accountant() const
        -> std::unique_ptr<Registries::Accountant> const& { return accountant_; }
    [[nodiscard]] auto client_registry() const
        -> std::unique_ptr<Registries::ClientRegistry> const& { return client_registry_; }
    [[nodiscard]] auto table_registry() const
        -> std::unique_ptr<Registries::TableRegistry> const& { return table_registry_; }

  private:
    const Spec& spec_;

    std::unique_ptr<EventConsumer> consumer_;
    std::unique_ptr<Registries::Accountant> accountant_;
    std::unique_ptr<Registries::ClientRegistry> client_registry_;
    std::unique_ptr<Registries::TableRegistry> table_registry_;
  };
}// namespace ComputerClub::Events

#endif// YADRO_COMPUTER_CLUB_CONTEXT_HPP
