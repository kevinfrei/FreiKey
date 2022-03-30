#pragma once

#include "sysstuff.h"
#include "usbenums.h"

class kb_reporter {
  // This is used by the scanner to build & send the key press signals
  uint8_t mods;
  uint8_t repsize;
  uint8_t report[6];

 public:
  kb_reporter();
  void set_modifier(Modifiers);
  void add_key_press(Keystroke);
  void consumer_press(Consumer);
  void consumer_release(Consumer);
  void send_keys();
};
