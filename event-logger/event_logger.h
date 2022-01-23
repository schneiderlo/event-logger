#include <algorithm>
#include <cassert>
#include <chrono>
#include <string>

#include <spdlog/spdlog.h>

namespace sl {

namespace internal {

// Equal std::true_type if D meets the requirements of std::chrono::duration
template <class D>
struct is_duration : std::false_type {};


template<class Rep, class Period>
struct is_duration<std::chrono::duration<Rep, Period>> : std::true_type {};

// Add space character to a string until it match a given width. It does nothing
// if the given width is less than the string length.
void pad_to_size_left(std::string& value, const size_t width) {
  if (value.size() >= width) {
    return;
  } else {
    const auto num_spaces = width - value.size();
    value.insert(0, num_spaces, ' ');
  }
}

// Add space character to a string until it match a given width. It does nothing
// if the given width is less than the string length.
void pad_to_size_right(std::string& value, const size_t width) {
  const auto src_size{value.size()};
  if (src_size >= width) {
    return;
  } else {
    const auto num_spaces = width - value.size();
    value.insert(src_size, num_spaces, ' ');
  }
}

void pad_to_max_size_right(std::vector<std::string>& values) {
  const auto max_size =
      std::max_element(values.cbegin(), values.cend(),
                       [](const std::string& lhs, const std::string& rhs) {
                         return lhs.size() < rhs.size();
                       })
          ->size();
  std::for_each(values.begin(), values.end(),
                [max_size](std::string& v) { pad_to_size_right(v, max_size); });
}

struct EventRecord {
  EventRecord(const std::string& name)
      : name_(name), time_stamp_(std::chrono::system_clock::now()) {}

  const std::string name_;
  const std::chrono::system_clock::time_point time_stamp_;
};

template <class Duration>
std::string timeSymbol() {
  static_assert(internal::is_duration<Duration>::value,
                "Duration requirements not met.");
  return "";
}

template <>
std::string timeSymbol<std::chrono::nanoseconds>() {
  return "ns";
}
template <>
std::string timeSymbol<std::chrono::microseconds>() {
  return "us";
}
template <>
std::string timeSymbol<std::chrono::milliseconds>() {
  return "ms";
}
template <>
std::string timeSymbol<std::chrono::seconds>() {
  return "s";
}

}  // namespace internal

// Record a series of events. The recording is output updon destruction.
//
// For instance the following example:
//
//  sl::EventLogger<std::chrono::milliseconds> el("Start of function");
//  step1();
//  el.add_event("Step 1");
//  step2();
//  el.add_event("Step 2");
//  step3();
//  el.add_event("Step 3");
//
// Will produce the following output:
//
//                    | Delta (ms) | Cumulative (ms)
//  Start of function | 0          | 0
//    Step 1          | 50         | 50
//    Step 2          | 708        | 759
//    Step 3          | 20         | 779
//    Total           | 0          | 779
template <class Duration>
class EventLogger {
 public:
  EventLogger(const std::string& name) { add_event(name); }

  ~EventLogger() {
    add_event("Total");

    const auto name_column = format_name_column();
    const auto delta_column = format_delta_column();
    const auto cumulative_column = format_cumul_column();

    for (int i = 0; i < name_column.size(); i++) {
      spdlog::info("{} | {} | {}", name_column[i], delta_column[i],
                  cumulative_column[i]);
    }
  }

  void add_event(const std::string& name) { entries_.emplace_back(name); }

 private:
  const std::string events_offset_ = std::string("  ");
  std::vector<internal::EventRecord> entries_;

  // Format the column containing the name of the events.
  std::vector<std::string> format_name_column() const {
    const std::string events_offset = events_offset_;
    std::vector<std::string> name_column{"", entries_[0].name_};
    std::transform(entries_.cbegin() + 1, entries_.cend(),
                   std::back_inserter(name_column),
                   [&events_offset](const internal::EventRecord& record) {
                     return events_offset + record.name_;
                   });

    internal::pad_to_max_size_right(name_column);
    return name_column;
  }

  // Format the column containing the delta between 2 events.
  std::vector<std::string> format_delta_column() const {
    std::vector<std::string> delta_column{
        "Delta (" + internal::timeSymbol<Duration>() + ")", "0"};
    std::transform(entries_.cbegin() + 1, entries_.cend(), entries_.cbegin(),
                   std::back_inserter(delta_column),
                   [](const internal::EventRecord& current,
                      const internal::EventRecord& prev) {
                     const auto delta =
                         std::chrono::duration_cast<Duration>(
                             current.time_stamp_ - prev.time_stamp_)
                             .count();
                     return std::to_string(delta);
                   });

    internal::pad_to_max_size_right(delta_column);
    return delta_column;
  }

  // Format the column containg the cumulative time.
  std::vector<std::string> format_cumul_column() const {
    std::vector<std::string> cumulative_column{
        "Cumulative (" + internal::timeSymbol<Duration>() + ")"};
    const auto start_time{entries_[0].time_stamp_};
    std::transform(entries_.cbegin(), entries_.cend(),
                   std::back_inserter(cumulative_column),
                   [start_time](const internal::EventRecord& current) {
                     const auto cumul = std::chrono::duration_cast<Duration>(
                                            current.time_stamp_ - start_time)
                                            .count();
                     return std::to_string(cumul);
                   });
    return cumulative_column;
  }
};

}  // namespace sl
