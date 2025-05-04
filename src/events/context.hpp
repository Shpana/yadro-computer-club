#ifndef YADRO_COMPUTER_CLUB_CONTEXT_HPP
#define YADRO_COMPUTER_CLUB_CONTEXT_HPP

#include <ctime>

struct Context {
  time_t start_time{0};
  time_t end_time{0};
  size_t tables_count{0};
  size_t price_per_hour{0};
};

#endif// YADRO_COMPUTER_CLUB_CONTEXT_HPP
