#include "client_registry.hpp"

namespace ComputerClub::Registries {
  auto ClientRegistry::AddClient(const std::string& client_name) -> void {
    arrived_clients_.insert(client_name);
  }

  auto ClientRegistry::RemoveClient(const std::string& client_name) -> void {
    arrived_clients_.erase(client_name);
  }

  auto ClientRegistry::HasClient(const std::string& client_name) const -> bool {
    return arrived_clients_.find(client_name) != arrived_clients_.end();
  }

  auto ClientRegistry::AddWaiter(const std::string& client_name) -> void {
    waiting_clients_queue_.push(client_name);
  }

  auto ClientRegistry::RemoveFirstWaiter() -> std::string {
    std::string client_name = waiting_clients_queue_.front();
    waiting_clients_queue_.pop();
    return client_name;
  }

  auto ClientRegistry::HasAnyWaiter() const -> bool {
    return !waiting_clients_queue_.empty();
  }

  auto ClientRegistry::waiters_count() const -> size_t {
    return waiting_clients_queue_.size();
  }
}// namespace ComputerClub::Registries