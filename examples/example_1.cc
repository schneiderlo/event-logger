#include <chrono>
#include <thread>

#include "event-logger/event_logger.h"

int main() {
  sl::EventLogger<std::chrono::milliseconds> el("Start of function");
  std::this_thread::sleep_for(std::chrono::milliseconds{50});
  el.add_event("Step 1");
  std::this_thread::sleep_for(std::chrono::milliseconds{708});
  el.add_event("Step 2");
  std::this_thread::sleep_for(std::chrono::milliseconds{20});
  el.add_event("Step 3");
}
