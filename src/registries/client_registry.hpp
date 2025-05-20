#ifndef YADRO_COMPUTER_CLUB_CLIENT_REGISTRY_H
#define YADRO_COMPUTER_CLUB_CLIENT_REGISTRY_H

#include <queue>
#include <set>
#include <string>

namespace ComputerClub::Registries {
  class ClientRegistry {
  public:
    ClientRegistry() = default;

    auto AddClient(const std::string& client_name) -> void;
    auto RemoveClient(const std::string& client_name) -> void;
    [[nodiscard]] auto HasClient(const std::string& client_name) const -> bool;

    auto AddWaiter(const std::string& client_name) -> void;
    auto RemoveFirstWaiter() -> std::string;
    [[nodiscard]] auto HasAnyWaiter() const -> bool;
    [[nodiscard]] auto waiters_count() const -> size_t;

  private:
    std::set<std::string> arrived_clients_{};
    std::queue<std::string> waiting_clients_queue_{};
  };
}// namespace ComputerClub::Registries

#endif// YADRO_COMPUTER_CLUB_CLIENT_REGISTRY_H
