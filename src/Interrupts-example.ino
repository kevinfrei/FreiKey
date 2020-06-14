#include <Adafruit_LittleFS.h>
#include <InternalFileSystem.h>

#include <array>
#include <initializer_list>

using namespace Adafruit_LittleFS_Namespace;

// Shamelessly stolen from
// https://www.fluentcpp.com/2017/05/19/crtp-helper/

template <typename T>
struct crtp {
  T& underlying() {
    return static_cast<T&>(*this);
  }
  T const& underlying() const {
    return static_cast<T const&>(*this);
  }

 private:
  crtp() {}
};

void dumpVal(uint32_t v, const char* header) {
  if (header)
    Serial.print(header);
  Serial.println(v);
}

void dumpHex(uint32_t v, const char* header) {
  if (header)
    Serial.print(header);
  Serial.println(v, HEX);
}

void dumpHex(uint16_t v, const char* header) {
  dumpHex(static_cast<uint32_t>(v), header);
}

void dumpHex(uint8_t v, const char* header) {
  dumpHex(static_cast<uint32_t>(v), header);
}

void dumpHex(bool v, const char* header) {
  dumpHex(static_cast<uint32_t>(v), header);
}

void dumpHex(uint64_t v, const char* header) {
  if (header)
    Serial.print(header);
  Serial.printf("0x%08x|0x%08x\n",
                static_cast<uint32_t>(v >> 32),
                static_cast<uint32_t>(v));
}

template <int T>
struct bit_array {
  constexpr static uint32_t num_bits = T;
  constexpr static uint32_t num_bytes = (T + 7) / 8;
  std::array<uint8_t, num_bytes> value;
  bit_array() : value{0} {}
  bit_array(std::initializer_list<uint8_t> init) : value{0} {
    size_t i = 0;
    for (auto& v : init) {
      value[i++] = v;
      if (i >= value.size())
        break;
    }
  }
  bit_array(const bit_array& m) : value{m.value} {}
  bool operator==(const bit_array& m) const {
    return value == m.value;
  }
  bool operator!=(const bit_array& m) const {
    return value != m.value;
  }
  bit_array<T> delta(const bit_array& compare) const {
    bit_array<T> v{};
    for (size_t i = 0; i < sizeof(value); i++) {
      v.value[i] = value[i] ^ compare.value[i];
    }
    return v;
  }
  bool any() const {
    for (uint8_t i : value) {
      if (i)
        return true;
    }
    return false;
  }
  uint8_t pull_a_bit() {
    for (uint8_t i = 0; i < sizeof(value); i++) {
      if (value[i]) {
        uint8_t bit_num = get_a_set_bit(value[i]);
        value[i] ^= (1 << bit_num);
        return bit_num + i * 8;
      }
    }
    return 0xFF;
  }
  void flip_bit(uint8_t bitnum) {
    value[bitnum >> 3] ^= 1 << (bitnum & 7);
  }
  void set_bit(uint8_t bitnum) {
    value[bitnum >> 3] |= 1 << (bitnum & 7);
  }
  void clear_bit(uint8_t bitnum) {
    value[bitnum >> 3] &= ~(1 << (bitnum & 7));
  }
  bool get_bit(uint8_t bitnum) const {
    return !!(value[bitnum >> 3] & (1 << (bitnum & 7)));
  }
  void write(const uint8_t* buffer) {
    memcpy(value.data(), buffer, num_bytes);
  }
  void read(uint8_t* buffer) const {
    memcpy(buffer, value.data(), num_bytes);
  }
  void dumpHex(const char* prf) const {
    Serial.print(prf);
    for (uint8_t i : this->value) {
      Serial.printf("%02X", i);
    }
    Serial.println();
  }
};

template <uint8_t pinLED>
class Analog_LED {
 public:
  static void ConfigLED() {
    pinMode(pinLED, OUTPUT);
    delay(1);
    analogWrite(pinLED, 0);
  }
  static void setLED(uint32_t brightness) {
    analogWrite(pinLED, brightness);
  }
};

template <uint8_t tRED, uint8_t tBLUE>
class Digital_LEDs {
 public:
  static void ConfigLEDs() {
    pinMode(tRED, OUTPUT);
    pinMode(tBLUE, OUTPUT);
  }
  static void setRed(bool on) {
    digitalWrite(tRED, on ? HIGH : LOW);
  }
  static void setBlue(bool on) {
    digitalWrite(tBLUE, on ? HIGH : LOW);
  }
};

template <uint8_t batPin = PIN_VBAT>
class Battery {
 public:
  // pin 31 on the 832, pin 30 on the 840, is available for sampling the battery
  static constexpr uint8_t VBAT_PIN = batPin;

  // 3.0V ADC range and 12-bit ADC resolution = 3000mV/4096
  static constexpr uint32_t VBAT_NUM = 3000;
  static constexpr uint32_t VBAT_DEN = 4096;

  static void ConfigBattery() {
    analogReference(AR_INTERNAL_3_0);
    analogReadResolution(12);
    delay(1);
  }

  static uint32_t getBatteryLevel() {
    return analogRead(VBAT_PIN) * VBAT_NUM / VBAT_DEN;
  }
  // This stuff shamelessly stolen from the AdaFruit example
  static uint8_t getBatteryPercent() {
    uint32_t bat = getBatteryLevel();
    if (bat >= 3000) {
      return 100;
    } else if (bat > 2900) {
      return 100 - ((3000 - bat) * 58) / 100;
    } else if (bat > 2740) {
      return 42 - ((2900 - bat) * 24) / 160;
    } else if (bat > 2440) {
      return 18 - ((2740 - bat) * 12) / 300;
    } else if (bat > 2100) {
      return 6 - ((2440 - bat) * 6) / 340;
    } else {
      return 0;
    }
  }
};

template <typename T, uint8_t nCols, uint8_t nRows, uint8_t... cols_then_rows>
class KeyMatrix : crtp<T> {
 public:
  static constexpr uint8_t numcols = nCols;
  static constexpr uint8_t numrows = nRows;
  static constexpr uint8_t matrix_size = numcols * numrows;
  typedef bit_array<matrix_size> bits;
  static constexpr uint8_t byte_size = bits::num_bytes;

  static void ConfigMatrix() {
    // For my wiring, the columns are output, and the rows are input...
    std::array<uint8_t, nCols + nRows> c_r{cols_then_rows...};
    for (uint8_t pn = 0; pn < nCols + nRows; pn++) {
      if (pn < nCols) {
        dumpVal(c_r[pn], "Output Pin ");
        T::configOutputPin(c_r[pn]);
      } else {
        dumpVal(c_r[pn], "Input Pullup ");
        T::configInputPin(c_r[pn]);
      }
    }
  };

  // This is the core place to simulate the keyboard for mocking
  // (at least in the betterfly config)
  static bits Read() {
    std::array<uint8_t, nCols + nRows> c_r{cols_then_rows...};
    bits switches{};
    for (uint64_t colNum = 0; colNum < numcols; ++colNum) {
      T::prepPinForRead(c_r[colNum]);
      delay(1); // TODO: Make this faster (which it microseconds)
      for (uint64_t rowNum = 0; rowNum < numrows; ++rowNum) {
        if (!digitalRead(c_r[nCols + rowNum])) {
          switches.set_bit(rowNum * numcols + colNum);
        }
      }
      T::completePin(c_r[colNum]);
    }
    return switches;
  }

  static void setInterrupts(void (*handler)()) {
    std::array<uint8_t, nCols + nRows> c_r{cols_then_rows...};

    Serial.println("Enabling Interrupts");
    for (uint8_t colNum = 0; colNum < numcols; colNum++) {
      digitalWrite(c_r[colNum], LOW);
    }
    delay(1);
    for (uint8_t rowNum = 0; rowNum < numrows; rowNum++) {
      attachInterrupt(
          digitalPinToInterrupt(c_r[nCols + rowNum]), handler, CHANGE);
    }
  }

  static void disableInterrupts() {
    std::array<uint8_t, nCols + nRows> c_r{cols_then_rows...};

    for (uint8_t rowNum = 0; rowNum < numrows; rowNum++) {
      detachInterrupt(digitalPinToInterrupt(c_r[nCols + rowNum]));
    }
    delay(1);
    for (uint8_t colNum = 0; colNum < numcols; colNum++) {
      digitalWrite(c_r[colNum], HIGH);
    }
  }
};

class AdafruitNRF52 {
 public:
  static void configOutputPin(uint8_t pin) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH);
  }
  static void configInputPin(uint8_t pin) {
    pinMode(pin, INPUT_PULLUP);
  }
  static void prepPinForRead(uint8_t pin) {
    digitalWrite(pin, LOW);
  }
  static void completePin(uint8_t pin) {
    digitalWrite(pin, HIGH);
  }
};

// clang-format off
using RightMatrix = KeyMatrix<AdafruitNRF52,
      // Cols:
      7,
      // Rows:
      6,
      // Column Pins:
      29, 16, 15, 7, 27, 11, 30,
      // Row Pins:
      13, 4, 2, 3, 5, 12>;
//}, 28};
// clang-format on

class RightBoard : public RightMatrix,
                   public Digital_LEDs<LED_RED, LED_BLUE>,
                   public Analog_LED<28>,
                   public Battery<> {
 public:
  static void Configure() {
    ConfigMatrix();
    ConfigLEDs();
    ConfigLED();
    ConfigBattery();
  }
};

extern "C" void trigger();

volatile bool intEnabled = false;

void enableInterrupt() {
  if (!intEnabled) {
    RightBoard::setInterrupts(trigger);
    intEnabled = true;
  }
  RightBoard::setBlue(!intEnabled);
  RightBoard::setRed(intEnabled);
}

void disableInterrupt() {
  if (intEnabled) {
    Serial.println("Disabling Interrupts");
    RightBoard::disableInterrupts();
    intEnabled = false;
  }
  RightBoard::setBlue(!intEnabled);
  RightBoard::setRed(intEnabled);
}

volatile bool triggered;

void trigger() {
  triggered = true;
}

using bits = RightBoard::bits;

bits prev;
uint32_t lastDelta;
bool notified;

File file(InternalFS);

void setup() {
  Serial.begin(115200);
  // Initialize Internal File System
  InternalFS.begin();
  RightBoard::Configure();
  triggered = false;
  notified = true;
  lastDelta = millis();
  enableInterrupt();
  if (file.open("/battery.txt", FILE_O_READ)) {
    char buffer[100];
    file.read(buffer, 99);
    Serial.print(buffer);
    file.close();
  } else {
    Serial.println("Unable to open the battery file for reading.");
  }
}

uint32_t lastBattery = 0;

// We should scan whenever any keys are held down,
// and up to 100 ms after the last change
void loop() {
  uint32_t now = millis();
  if (triggered || ((now - lastDelta) < 100) || prev.any()) {
    disableInterrupt();
    bits cur = RightBoard::Read();
    notified = false;
    triggered = false;
    if (prev != cur) {
      cur.dumpHex("New Bits:");
      prev = cur;
      lastDelta = now;
    }
  } else if (!notified) {
    Serial.printf("Halting scans for now\n");
    notified = true;
    enableInterrupt();
  }
  waitForEvent();
}
