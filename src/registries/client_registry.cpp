#include "client_registry.hpp"

bool ClientRegistry::has_client(const std::string& client_name) {
  return _arrived_clients.find(client_name) != _arrived_clients.end();
}

void ClientRegistry::add_client(const std::string& client_name) {
  _arrived_clients.insert(client_name);
}

void ClientRegistry::remove_client(const std::string& client_name) {
  _arrived_clients.erase(client_name);
}

bool ClientRegistry::has_any_waiter() {
  return !_waiting_clients_queue.empty();
}

void ClientRegistry::add_waiter(const std::string& client_name) {
  _waiting_clients_queue.push(client_name);
}

std::string ClientRegistry::pop_first_waiter() {
  std::string client_name = _waiting_clients_queue.front();
  _waiting_clients_queue.pop();
  return client_name;
}

size_t ClientRegistry::get_waiters_count() const {
  return _waiting_clients_queue.size();
}
