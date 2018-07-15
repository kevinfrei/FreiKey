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
enum class header : uint8_t {
  status = 1, string, hex, uns, sign
};

struct data {
  header hdr;
  uint8_t numSeconds;
  data(header h, uint8_t time = 10);
  void send(); // This should send the data
};

struct status : public data {
  uint8_t leftBattery;
  uint8_t rightBattery;
  uint8_t leftCharging;
  uint8_t rightCharging;
  uint8_t leftState;
  uint8_t baseLayer;
  uint8_t layerStack[8];
  uint8_t hostName[32];
  static status create(const char *host, uint8_t lbat, uint8_t rbat,
    bool lchg, bool rchg, bool lstt, uint8_t base, uint8_t time = 10);
  void display();
};

struct string : public data{
  char data[46];
  static string create(const char *str, uint8_t time = 10);
};

struct value: public data{
  char data[42];
  uint32_t val;
  static value create(const char *str, uint32_t val, header type = header::uns, uint8_t time = 10);
};

}
#endif