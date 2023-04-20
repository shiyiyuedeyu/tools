#pragma once
#include <chrono>
#include <cstdint>
#include <ctime>
#include <string>

namespace time_util {

struct TimeUtil {
  // needs -lrt (real-time lib)
  // 1970-01-01 epoch UTC time, 1 mcs resolution (divide by 1M to get time_t)
  static uint64_t ClockGetTimeMicro() {
    timespec ts{};
    clock_gettime(CLOCK_REALTIME, &ts);
    return (uint64_t)ts.tv_sec * 1000000LL + (uint64_t)ts.tv_nsec / 1000LL;
  }
  static uint64_t ClockGetTimeMilli() {
    timespec ts{};
    clock_gettime(CLOCK_REALTIME, &ts);
    return (uint64_t)ts.tv_sec * 1000LL + (uint64_t)ts.tv_nsec / 1000000LL;
  }

  static void ClockGetTimeSpec(struct timespec* ts) {
    clock_gettime(CLOCK_REALTIME, ts);
  }

  static void ms2timespec(struct timespec* ts, uint64_t ms) {
    ts->tv_sec = static_cast<int64_t>(ms / (uint64_t)1000);
    ts->tv_nsec = static_cast<int64_t>((ms % 1000) * (uint64_t)1000000);
  }

  static void us2timespec(struct timespec* ts, uint64_t us) {
    ts->tv_sec = static_cast<int64_t>(us / (uint64_t)1000000);
    ts->tv_nsec = static_cast<int64_t>(us % (uint64_t)1000000 * (uint64_t)1000);
  }

  static void ns2timespec(struct timespec* timespec, uint64_t nsec) {
    timespec->tv_sec = static_cast<int64_t>(nsec / (uint64_t)1000000000);
    timespec->tv_nsec = static_cast<int64_t>(nsec % (uint64_t)1000000000);
  }

  static uint64_t timespec2ms(const timespec& timespec) {
    return timespec.tv_sec * 1000 + (timespec.tv_nsec) / 1000000;
  }

  static uint64_t timespec2ms(const time_t& sec, const int64_t& nsec) {
    return sec * 1000 + nsec / 1000000;
  }

  static uint64_t timespec2us(const timespec& timespec) {
    return timespec.tv_sec * 1000000 + (timespec.tv_nsec) / 1000;
  }

  static uint64_t timespec2us(const time_t& sec, const int64_t& nsec) {
    return sec * 1000000 + nsec / 1000;
  }

  static uint64_t timespec2ns(const timespec& timespec) {
    return timespec.tv_sec * 1000000000 + timespec.tv_nsec;
  }

  static uint64_t timespec2ns(const time_t& sec, const int64_t& nsec) {
    return sec * 1000000000 + nsec;
  }

  static std::string GetLocalTimeFromSec(time_t sec) {
    char buff[80];
    strftime(buff, sizeof buff, "%D %T", localtime(&sec));
    return buff;
  }
  static inline uint64_t GetTimeNano() {
    struct timespec t {};
    clock_gettime(CLOCK_REALTIME, &t);
    return (uint64_t)(t.tv_sec * 1000 * 1000 * 1000) + (uint64_t)(t.tv_nsec);
  }

  static inline uint64_t GetTimeMicro() {
    struct timespec t {};
    clock_gettime(CLOCK_REALTIME, &t);
    return (uint64_t)(t.tv_sec * 1000 * 1000) + (uint64_t)(t.tv_nsec / 1000);
  }

  static inline uint64_t GetTimeMilli() {
    struct timespec t {};
    clock_gettime(CLOCK_REALTIME, &t);
    return (uint64_t)(t.tv_sec * 1000) + (uint64_t)(t.tv_nsec / 1000 / 1000);
  }

  typedef std::chrono::high_resolution_clock Clock;

  static inline uint64_t GetMicroseconds(
      const std::chrono::high_resolution_clock::time_point& start) {
    return std::chrono::duration_cast<std::chrono::microseconds>(
               std::chrono::high_resolution_clock::now() - start)
        .count();
  }

  static inline uint64_t GetMilliseconds(
      const std::chrono::high_resolution_clock::time_point& start) {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
               std::chrono::high_resolution_clock::now() - start)
        .count();
  }
};

}  // namespace time_util
