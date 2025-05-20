#include "table_registry.hpp"

#include <vector>

namespace ComputerClub::Registries {
  TableRegistry::TableRegistry(size_t tables_count) {
    for (auto id = 1; id <= tables_count; ++id) {
      free_tables_.insert(id);
    }
  }

  auto TableRegistry::Pin(const std::string& client_name, size_t table_id) -> void {
    if (IsClientPinned(client_name)) {
      Unpin(client_name);
    }
    free_tables_.erase(table_id);
    pinned_clients_[client_name] = table_id;
  }

  auto TableRegistry::Unpin(const std::string& client_name) -> void {
    auto table_id = pinned_clients_[client_name];
    free_tables_.insert(table_id);
    pinned_clients_.erase(client_name);
  }

  auto TableRegistry::HasFreeTables() const -> bool {
    return !free_tables_.empty();
  }

  auto TableRegistry::IsTableFree(size_t table_id) const -> bool {
    return free_tables_.find(table_id) != free_tables_.end();
  }

  auto TableRegistry::IsClientPinned(const std::string& client_name) const -> bool {
    return pinned_clients_.find(client_name) != pinned_clients_.end();
  }

  auto TableRegistry::GetPinnedTable(const std::string& client_name) const -> size_t {
    return pinned_clients_.at(client_name);
  }

  auto TableRegistry::GetAllPinnedClients() const -> std::vector<std::string> {
    std::vector<std::string> pinned_clients;
    pinned_clients.reserve(pinned_clients_.size());
    for (const auto& [key, value]: pinned_clients_) {
      pinned_clients.push_back(key);
    }
    return pinned_clients;
  }
}// namespace ComputerClub::Registries