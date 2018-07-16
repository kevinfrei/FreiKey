#if !defined(DISPLAY_H)
#define DISPLAY_H

// The keyboard can send three messages, each of which also includes a
// length of time (in seconds) to display the message
// Status:
//  Layer State, Left/Right battery values. Charging status
//  Slave state, bluetooth host name
// String: print something out (45 bytes max)
//  Primarily useful for debugging, right?
// Prefixed number: a string (41 bytes max), a format (hex, uns, signed)
//  and a 32 bit value

namespace uart {

uint8_t encodeBatteryValue(uint8_t chargeRemaining,
                           bool isCharging,
                           bool isPresent);

enum class header : uint8_t { status = 1, string, value };

template <typename T, header V>
struct data {
  header hdr;
  uint8_t numSeconds;
  data(uint8_t time = 10) : hdr(V), numSeconds(time) {}
  void send(); // This should send the data
};

struct status : public data<status, header::status> {
  uint8_t layerStack[8];
  uint8_t hostName[38];
  uint8_t leftBattery;
  uint8_t rightBattery;
  static status create(const char* host,
                       uint8_t lbat,
                       uint8_t rbat,
                       uint8_t time = 10);
  void display();
};

struct string : public data<string, header::string> {
  char data[46];
  static string create(const char* str, uint8_t time = 10);
};

struct value : public data<value, header::value> {
  char data[42];
  uint32_t val;
  static value create(const char* str,
                      uint32_t val,
                      uint8_t time = 10);
};

} // namespace uart
#endif
