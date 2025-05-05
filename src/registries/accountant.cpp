#include "accountant.hpp"

#include <cmath>

Accountant::Accountant(size_t tables_count)
    : _tables_count(tables_count) {
  for (size_t id = 1; id <= tables_count; ++id) {
    _statistics[id] = {};
  }
}

void Accountant::account_pin(size_t table_id, time_t processed_at) {
  auto& item = _statistics[table_id];
  item.updated_at = processed_at;
}

void Accountant::account_unpin(size_t table_id, time_t processed_at) {
  auto& item = _statistics[table_id];
  item.relative_revenue += std::ceil(static_cast<double>(processed_at - item.updated_at) / 60.0);
  item.occupied_time += (processed_at - item.updated_at);
  item.updated_at = processed_at;
}

std::map<size_t, Accountant::ReportItem> Accountant::prepare_report(
    size_t price_per_hour) const {
  std::map<size_t, Accountant::ReportItem> report;
  for (const auto& [key, statistic]: _statistics) {
    report[key] = {
        statistic.relative_revenue * price_per_hour,
        statistic.occupied_time};
  }
  return report;
}