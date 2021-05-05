#include <array>
#include <stdint.h>

struct TimeSyncEntry {
  uint32_t ms;
  uint32_t us;
};

constexpr size_t BufferSize = 8;

class TimeSync {
  std::array<TimeSyncEntry, BufferSize> left;
  std::array<TimeSyncEntry, BufferSize> right;
  uint8_t leftCount;
  uint8_t rightCount;

  static void registerTime(const TimeSyncEntry& tse,
                           std::array<TimeSyncEntry, BufferSize>& times,
                           uint8_t& count) {
    // TODO: Pick the right entry to remove
    uint8_t elem = (count == BufferSize) ? tse.us % BufferSize : count;
    times[elem] = tse;
  }

 public:
  TimeSync() : leftCount(0), rightCount(0) {}
  void RegisterTime(bool isLeft, const TimeSyncEntry& tse) {
    if (isLeft) {
      registerTime(tse, left, leftCount);
    } else {
      registerTime(tse, right, rightCount);
    }
  }

};