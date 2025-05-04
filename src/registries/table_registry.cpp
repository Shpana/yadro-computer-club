#include "table_registry.hpp"

TableRegistry::TableRegistry(size_t tables_count)
    : _tables_count(tables_count) {
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
    const std::string& client_name, size_t table_id) {
  if (is_client_pinned(client_name)) {
    unpin_client(client_name);
  }
  _available_tables.erase(table_id);
  _pinned_clients[client_name] = table_id;
}

void TableRegistry::unpin_client(const std::string& client_name) {
  size_t table_id = _pinned_clients[client_name];
  _available_tables.insert(table_id);
  _pinned_clients.erase(client_name);
}

size_t TableRegistry::get_pinned_table(const std::string& client_name) const {
  return _pinned_clients.at(client_name);
}
