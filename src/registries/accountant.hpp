#ifndef YADRO_COMPUTER_CLUB_ACCOUNTANT_HPP
#define YADRO_COMPUTER_CLUB_ACCOUNTANT_HPP

#include <cstddef>
#include <cstdint>
#include <map>
#include <ctime>

class Accountant {
  struct StatisticsItem {
    size_t relative_revenue{0};
    time_t occupied_time{0};
    time_t updated_at{0};
  };

public:
  struct ReportItem {
    size_t revenue{0};
    time_t occupied_time{0};
  };

public:
  Accountant(size_t tables_count);

  void account_pin(size_t table_id, time_t processed_at);
  void account_unpin(size_t table_id, time_t processed_at);

  [[nodiscard]] std::map<size_t, ReportItem> prepare_report(size_t price_per_hour) const;

private:
  size_t _tables_count;
  std::map<size_t, StatisticsItem> _statistics;
};

#endif// YADRO_COMPUTER_CLUB_ACCOUNTANT_HPP
