#include "table_registry.hpp"

#include <vector>

TableRegistry::TableRegistry(size_t tables_count,
                             const std::shared_ptr<Accountant>& accountant)
    : _tables_count(tables_count), _accountant(accountant) {
  for (size_t id = 1; id <= _tables_count; ++id) {
    _available_tables.insert(id);
  }
}

bool TableRegistry::has_available_tables() {
  return !_available_tables.empty();
}

bool TableRegistry::is_table_available(size_t table_id) {
  return _available_tables.find(table_id) != _available_tables.end();
}

bool TableRegistry::is_client_pinned(const std::string& client_name) {
  return _pinned_clients.find(client_name) != _pinned_clients.end();
}

void TableRegistry::pin_client(
    const std::string& client_name,
    size_t table_id, time_t processed_at) {
  if (is_client_pinned(client_name)) {
    unpin_client(client_name, processed_at);
  }
  _available_tables.erase(table_id);
  _pinned_clients[client_name] = table_id;
  _accountant->account_pin(table_id, processed_at);
}

void TableRegistry::unpin_client(
    const std::string& client_name, time_t processed_at) {
  size_t table_id = _pinned_clients[client_name];
  _available_tables.insert(table_id);
  _pinned_clients.erase(client_name);
  _accountant->account_unpin(table_id, processed_at);
}

size_t TableRegistry::get_pinned_table(const std::string& client_name) const {
  return _pinned_clients.at(client_name);
}

std::vector<std::string> TableRegistry::get_all_pinned_clients() const {
  std::vector<std::string> pinned_clients;
  pinned_clients.reserve(_pinned_clients.size());
  for (const auto& [key, value] : _pinned_clients) {
    pinned_clients.push_back(key);
  }
  return pinned_clients;
}

