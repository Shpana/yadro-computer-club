#include "time_converts.hpp"

#include <iomanip>
#include <sstream>

time_t string_to_time(const std::string& time) {
  std::stringstream ss{time};
  std::string tmp;

  std::getline(ss, tmp, ':');
  time_t h = std::stoi(tmp);
  std::getline(ss, tmp);
  time_t m = std::stoi(tmp);
  return 60 * h + m;
}

std::string time_to_string(time_t time) {
  std::stringstream ss;
  time_t h = time / 60,
         m = time - 60 * h;
  ss << std::setfill('0') << std::setw(2) << h;
  ss << ':';
  ss << std::setfill('0') << std::setw(2) << m;
  return ss.str();
}