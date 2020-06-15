#include <array>
#include <initializer_list>

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

template <typename T, uint8_t nCols, uint8_t nRows, uint8_t... cols_then_rows>
class KeyMatrix {
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

// clang-format off
using LeftKarbonMatrix = KeyMatrix<AdafruitNRF52,
  // Cols, Rows
  6, 6,
  // Column pins:
  15, 30, 27, A4, SCK, MOSI, // From 'outer' to 'inner'
  // Row pins:
  A1, A0, A2, 11, 7, 16>;

using RightKarbonMatrix = KeyMatrix<AdafruitNRF52,
  // Cols, Rows
  6, 6,
  // Column pins:
  16, 27, 30, MOSI, SCK, A0, // from 'inner' to 'outer'
  // Row pins:
  A2, 15, A1, A5, A4, A3>;

class TheBoard : public LeftKarbonMatrix {
 public:
  static void Configure() {
    ConfigMatrix();
  }
};

extern "C" void trigger();

volatile bool intEnabled = false;

void enableInterrupt() {
  if (!intEnabled) {
    TheBoard::setInterrupts(trigger);
    intEnabled = true;
  }
}

void disableInterrupt() {
  if (intEnabled) {
    Serial.println("Disabling Interrupts");
    TheBoard::disableInterrupts();
    intEnabled = false;
  }
}

volatile bool triggered;

void trigger() {
  triggered = true;
}

using bits = TheBoard::bits;

bits prev;
uint32_t lastDelta;
bool notified;

void setup() {
  Serial.begin(115200);
  TheBoard::Configure();
  triggered = false;
  notified = true;
  lastDelta = millis();
  enableInterrupt();
}

uint32_t lastBattery = 0;

// We should scan whenever any keys are held down,
// and up to 100 ms after the last change
void loop() {
  uint32_t now = millis();
  if (triggered || ((now - lastDelta) < 100) || prev.any()) {
    disableInterrupt();
    bits cur = TheBoard::Read();
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
