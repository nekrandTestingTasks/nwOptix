#include <chrono>
#include <mutex>
#include <queue>

#include <iostream>

struct Request {
  std::chrono::system_clock::time_point time;
  int val;
};

class Counter {
public:
  Counter(int p) : period(p), counter(0) { };

  std::string count(int val);

private:
  std::queue<Request> requests;
  std::mutex m;
  std::atomic<int> counter;
  int period;
};
