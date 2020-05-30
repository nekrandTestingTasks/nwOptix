#include "Counter.h"
#include <chrono>

std::string Counter::count(int val) {
  std::unique_lock<std::mutex> l(m);
  while (!requests.empty() &&
         requests.front().time <
             std::chrono::system_clock::now() - std::chrono::seconds(period)) {
    counter -= requests.front().val;
    requests.pop();
  }
  requests.emplace(Request{std::chrono::system_clock::now(), val});
  counter += val;
  int cur_counter = counter;
  l.unlock();
  std::cerr << std::to_string(cur_counter);

  return std::to_string(cur_counter) + "\r\n";
}
