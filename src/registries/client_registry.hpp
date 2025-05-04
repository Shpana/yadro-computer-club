#ifndef YADRO_COMPUTER_CLUB_CLIENT_REGISTRY_H
#define YADRO_COMPUTER_CLUB_CLIENT_REGISTRY_H

#include <queue>
#include <set>
#include <string>

class ClientRegistry {
public:
  bool has_client(const std::string& client_name);
  void add_client(const std::string& client_name);
  void remove_client(const std::string& client_name);

  bool has_any_waiter();
  void add_waiter(const std::string& client_name);
  std::string pop_first_waiter();
  [[nodiscard]] size_t get_waiters_count() const;

private:
  std::set<std::string> _arrived_clients{};
  std::queue<std::string> _waiting_clients_queue{};
};

#endif// YADRO_COMPUTER_CLUB_CLIENT_REGISTRY_H
