#ifndef YADRO_COMPUTER_CLUB_TABLE_REGISTRY_HPP
#define YADRO_COMPUTER_CLUB_TABLE_REGISTRY_HPP

#include "accountant.hpp"

#include <map>
#include <memory>
#include <set>
#include <string>

class TableRegistry {
public:
  TableRegistry(size_t tables_count,
                const std::shared_ptr<Accountant>& accountant);

  bool has_available_tables();
  bool is_table_available(size_t table_id);
  bool is_client_pinned(const std::string& client_name);

  void pin_client(const std::string& client_name, size_t table_id, time_t processed_at);
  void unpin_client(const std::string& client_name, time_t processed_at);
  void unpin_all(time_t processed_at);
  [[nodiscard]] size_t get_pinned_table(const std::string& client_name) const;

private:
  std::shared_ptr<Accountant> _accountant;
  size_t _tables_count;
  std::set<size_t> _available_tables;
  std::map<std::string, size_t> _pinned_clients;
};

#endif// YADRO_COMPUTER_CLUB_TABLE_REGISTRY_HPP
