#ifndef YADRO_COMPUTER_CLUB_TABLE_REGISTRY_HPP
#define YADRO_COMPUTER_CLUB_TABLE_REGISTRY_HPP

#include <map>
#include <set>
#include <string>

class TableRegistry {
public:
  TableRegistry(size_t tables_count);

  bool has_available_tables();
  bool is_table_available(size_t table_id);
  bool is_client_pinned(const std::string& client_name);

  void pin_client(const std::string& client_name, size_t table_id);
  void unpin_client(const std::string& client_name);
  [[nodiscard]] size_t get_pinned_table(const std::string& client_name) const;

private:
  size_t _tables_count;

  std::set<size_t> _available_tables;
  std::map<std::string, size_t> _pinned_clients;
};

#endif// YADRO_COMPUTER_CLUB_TABLE_REGISTRY_HPP
