#pragma once

#include "sysstuff.h"

template <uint8_t batPin>
struct Battery {
  // pin 31 on the 832, pin 30 on the 840, is available for sampling the battery
  static constexpr uint8_t VBAT_PIN = batPin;

  static void ConfigBattery() {
    analogReference(AR_INTERNAL);
    analogReadResolution(12);
    delay(1);
  }

  // I ran the Adafruit 500mah LiPo battery down, logging values until it died
  // this is a general linear approximation, cuz I'm not good enough at math
  // anymore to do anything fancier :/
  static uint8_t getBatteryPercent() {
    uint32_t bat = analogRead(VBAT_PIN);
    if (bat > 3460) {
      return 100;
    } else if (bat > 3255) {
      return 70 + 30 * (bat - 3255) / 205;
    } else if (bat > 3175) {
      return 45 + 25 * (bat - 3175) / 80;
    } else if (bat > 3110) {
      return 30 + 15 * (bat - 3110) / 65;
    } else if (bat > 3050) {
      return 10 * (bat - 3050) / 20;
    } else {
      return 0;
    }
  }
};
