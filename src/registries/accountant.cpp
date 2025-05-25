#include "accountant.hpp"

#include <cmath>

namespace ComputerClub::Registries {
  Accountant::Accountant(size_t tables_count) {
    for (size_t id = 1; id <= tables_count; ++id) {
      statistics_[id] = {};
    }
  }

  auto Accountant::AccountPinning(size_t table_id, time_t processed_at) -> void {
    auto& item = statistics_[table_id];
    item.updated_at = processed_at;
  }

  auto Accountant::AccountUnpinning(size_t table_id, time_t processed_at) -> void {
    auto& item = statistics_[table_id];
    item.relative_revenue += std::ceil(static_cast<double>(processed_at - item.updated_at) / 60.0);
    item.occupied_time += (processed_at - item.updated_at);
    item.updated_at = processed_at;
  }

  auto Accountant::CompileReport(size_t price_per_hour) const
      -> std::map<size_t, Accountant::ReportItem> {
    std::map<size_t, Accountant::ReportItem> report;
    for (const auto& [key, statistic]: statistics_) {
      report[key] = {
          .revenue = statistic.relative_revenue * price_per_hour,
          .occupied_time = statistic.occupied_time};
    }
    return report;
  }
}// namespace ComputerClub::Registries