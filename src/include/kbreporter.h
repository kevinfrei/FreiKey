#pragma once

#include "sysstuff.h"

class kb_reporter {
  // This is used by the scanner to build & send the key press signals
  uint8_t mods;
  uint8_t repsize;
  uint8_t report[6];

 public:
  kb_reporter();
  void set_modifier(uint8_t);
  void add_key_press(uint8_t);
  void consumer_press(uint16_t);
  void consumer_release(uint16_t);
  void send_keys();
};
