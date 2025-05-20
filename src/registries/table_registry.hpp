#ifndef YADRO_COMPUTER_CLUB_TABLE_REGISTRY_HPP
#define YADRO_COMPUTER_CLUB_TABLE_REGISTRY_HPP

#include "accountant.hpp"

#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>

namespace ComputerClub::Registries {
  class TableRegistry {
  public:
    TableRegistry(size_t tables_count);

    auto Pin(const std::string& client_name, size_t table_id) -> void;
    auto Unpin(const std::string& client_name) -> void;

    [[nodiscard]] auto HasFreeTables() const -> bool;
    [[nodiscard]] auto IsTableFree(size_t table_id) const -> bool;

    [[nodiscard]] auto IsClientPinned(const std::string& client_name) const -> bool;
    [[nodiscard]] auto GetPinnedTable(const std::string& client_name) const -> size_t;
    [[nodiscard]] auto GetAllPinnedClients() const -> std::vector<std::string>;

  private:
    std::set<size_t> free_tables_;
    std::map<std::string, size_t> pinned_clients_;
  };
}// namespace ComputerClub::Registries

#endif// YADRO_COMPUTER_CLUB_TABLE_REGISTRY_HPP
