#include "hardware.h"
#include "boardio.h"
#include "debounce.h"

#if defined(HAS_BATTERY)
// Some globals used by each half
// The last time we reported the battery
uint32_t last_bat_time = 0;
constexpr uint8_t num_reads = 8;
uint8_t last_8_reads[num_reads] = {0};
int8_t cur_bat_loc = -1 - num_reads;

uint8_t readBattery(uint32_t now, uint8_t prev) {
  if (prev && now - last_bat_time <= 30000) {
    // There's a lot of variance in the reading, so no need to over-report it.
    return prev;
  }
  uint8_t bat_percentage = BoardIO::getBatteryPercent();
#if defined(DEBUG)
  dumpVal(bat_percentage, "Battery level: ");
#endif
  last_bat_time = now;
  cur_bat_loc++;
  uint8_t bounds = num_reads;
  if (cur_bat_loc < 0) {
    bounds = 8 + cur_bat_loc + 1;
    last_8_reads[bounds - 1] = bat_percentage;
  } else {
    cur_bat_loc = cur_bat_loc % bounds;
    last_8_reads[cur_bat_loc] = bat_percentage;
  }
  uint32_t total = 0;
  for (uint8_t i = 0; i < bounds; i++)
    total += last_8_reads[i];
  return total / bounds;
}
#endif

namespace state {

#if defined(DEBUG)
uint32_t scans_since_last_time = 0;
#endif

hw::hw(uint8_t bl) : switches {}
#if !defined(TEENSY)
, battery_level(bl)
#endif
{
}
hw::hw(const hw& c)
    : switches(c.switches)
#if !defined(TEENSY)
      ,
      battery_level(c.battery_level)
#endif
{
}

#if !defined(USB_MASTER) && !defined(KARBON)
hw::hw(uint32_t now, const hw& prev)
    : switches(prev.switches)
#if defined(HAS_BATTERY)
      ,
      battery_level(readBattery(now, prev.battery_level))
#endif
{
  readSwitches(now);
}
#endif

#if defined(UART_CLIENT)
// Send the relevant data over the wire
void hw::send(BLEUart& bleuart, const hw& prev) const {
  uint8_t buffer[data_size];
  this->switches.read(buffer);
  buffer[MatrixBits::num_bytes] = this->battery_level;
  bleuart.write(buffer, data_size);
}
#endif

#if defined(USB_MASTER) || defined(KARBON)
std::queue<incoming> data_queue;

hw::hw(BLEClientUart& clientUart, const hw& prev) {
  if (!receive(clientUart, prev))
    memcpy(reinterpret_cast<uint8_t*>(this),
           reinterpret_cast<const uint8_t*>(&prev),
           sizeof(hw));
}
#endif

#if !defined(USB_MASTER) && !defined(KARBON)
void hw::readSwitches(uint32_t now) {
#if defined(DEBUG)
  scans_since_last_time++;
#endif
  // Read & debounce the current key matrix
  this->switches = debounce(BoardIO::Read(), now);
}
#else // defined(USB_MASTER)
// Try to receive any relevant switch data from the wire.
// Returns true if something was received
#if defined(TEST_MASTER)
constexpr uint8_t INIT = 0;
constexpr uint8_t WAIT = 1;
constexpr uint8_t PRESSED = 2;
constexpr uint8_t FLIPSIDES = 3;
hw *turn, *newBit;
uint32_t lastPress = 0;
uint8_t bitNum = 0;
uint8_t state = 0;
#endif

bool hw::receive(BLEClientUart& clientUart, const hw& prev) {
#if defined(TEST_MASTER)
  // This is my little 'fake hitting buttons' to test the dongle by itself
  uint32_t now = millis();
  switch (state) {
    case INIT:
      lastPress = now;
      turn = this;
      newBit = this;
      state = WAIT;
      return false;
    case WAIT:
      if (now - lastPress < 1000 || turn != this) {
        return false;
      }
      state = PRESSED;
      lastPress = now;
      this->switches = BoardIO::bits{};
      this->switches.set_bit(bitNum);
      return true;
    case PRESSED:
      if (now - lastPress < 15 || turn != this) {
        return false;
      }
      state = FLIPSIDES;
      lastPress = now;
      this->switches = BoardIO::bits{};
      return true;
    case FLIPSIDES:
      if (turn == this) {
        return false;
      }
      state = WAIT;
      turn = this;
      if (newBit == this) {
        bitNum = (bitNum + 1) % BoardIO::matrix_size;
      }
      return false;
    default:
      return false;
  }
#else
  if (!data_queue.empty() && data_queue.front().which == &clientUart) {
    memcpy(
        reinterpret_cast<uint8_t*>(this), data_queue.front().what, data_size);
    delete data_queue.front().what;
    data_queue.pop();
    return true;
  } else {
    return false;
  }
#endif
}
#endif

bool hw::operator==(const hw& o) const {
  return
#if defined(HAS_BATTERY)
      o.battery_level == battery_level &&
#endif
      o.switches == switches;
}

bool hw::operator!=(const hw& o) const {
  return !((*this) == o);
}

#if defined(DEBUG)
void hw::dump() const {
#if defined(HAS_BATTERY)
  dumpVal(battery_level, "Battery Level:");
#endif
  switches.dumpHex("Integer value: ");
  Serial.println("");
  for (int64_t r = 0; r < BoardIO::numrows; r++) {
    for (int64_t c = BoardIO::numcols - 1; c >= 0; c--) {
      if (switches.get_bit(r * BoardIO::numcols + c)) {
        Serial.print("X ");
      } else {
        Serial.print("- ");
      }
    }
    Serial.println("");
  }
}
#endif
} // namespace state
