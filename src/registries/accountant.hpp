#ifndef YADRO_COMPUTER_CLUB_ACCOUNTANT_HPP
#define YADRO_COMPUTER_CLUB_ACCOUNTANT_HPP

#include <cstddef>
#include <cstdint>
#include <ctime>
#include <map>

namespace ComputerClub::Registries {
  class Accountant {
  public:
    struct ReportItem {
      size_t revenue{0};
      time_t occupied_time{0};
    };

  public:
    Accountant(size_t tables_count);

    auto AccountPinning(size_t table_id, time_t processed_at) -> void;
    auto AccountUnpinning(size_t table_id, time_t processed_at) -> void;
    [[nodiscard]] auto CompileReport(size_t price_per_hour) const
        -> std::map<size_t, ReportItem>;

  private:
    struct StatisticsItem {
      size_t relative_revenue{0};
      time_t occupied_time{0};
      time_t updated_at{0};
    };

    std::map<size_t, StatisticsItem> statistics_;
  };
}// namespace ComputerClub::Registries

#endif// YADRO_COMPUTER_CLUB_ACCOUNTANT_HPP
