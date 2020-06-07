#include "sysstuff.h"

// Taken from https://github.com/madleech/Button
// Reduced debounce time to 20 ms, and made it configurable
// Adding "repeat" capability

// If code size is less important than data size,
// You can bit-pack the booleans, the pin, delay and repeat values to save
// a couple bytes
class Button {
  // The time when we should pay attention to switch values again (debounce)
  uint32_t _ignore_until;
  // How frequently to tap a key if it's being held down
  uint8_t _repeat;
  bool _state;
  bool _has_changed;
  const uint8_t _pin;
  const uint8_t _delay;

  // This is to trigger a quick "key up" which will be immediately followed
  // by a "key down"
  bool timesUp(uint32_t now) {
    return (_repeat && now - (_ignore_until - _delay) > _repeat);
  }

 public:
  constexpr static bool PRESSED = LOW;
  constexpr static bool RELEASED = HIGH;

  Button(uint8_t pin, uint16_t repeat = 0, uint8_t bounceTime = 20)
      : _pin(pin),
        _delay(bounceTime),
        _state(HIGH),
        _has_changed(false),
        _ignore_until(0),
        _repeat(repeat) {}

  void begin() const {
    pinMode(_pin, INPUT_PULLUP);
  }

  bool read() {
    // ignore pin changes until after this delay time
    auto ms = millis();
    if (_ignore_until <= ms) {
      if (digitalRead(_pin) != _state) {
        _ignore_until = ms + _delay;
        _state = !_state;
        _has_changed = true;
      } else if (_state == PRESSED && timesUp(ms)) {
        _state = !_state;
        _has_changed = true;
      }
    }
    // These things are pullup's, so high = "open" and low = "closed"
    return !_state;
  }

  // has the button been toggled from on -> off, or vice versa
  bool toggled() {
    read();
    return has_changed();
  }

  // mostly internal, tells you if a button has changed after calling the read()
  // function
  bool has_changed() {
    if (_has_changed == true) {
      _has_changed = false;
      return true;
    }
    return false;
  }

  // has the button gone from off -> on
  bool pressed() {
    return (read() == PRESSED && has_changed() == true);
  }

  // has the button gone from on -> off
  bool released() {
    return (read() == RELEASED && has_changed() == true);
  }
};
