#ifndef YADRO_COMPUTER_CLUB_CONTEXT_HPP
#define YADRO_COMPUTER_CLUB_CONTEXT_HPP

#include <ctime>

struct Context {
  time_t start_time{0};
  time_t end_time{0};
  size_t tables_count{0};

  Context() = default;
  Context(time_t _start_time, time_t _end_time, size_t _tables_count)
      : start_time(_start_time), end_time(_end_time), tables_count(_tables_count) {}
};

#endif// YADRO_COMPUTER_CLUB_CONTEXT_HPP
