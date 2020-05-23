#pragma once

#include "sysstuff.h"

template <uint8_t batPin>
struct Battery {
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

  // This stuff shamelessly stolen from the AdaFruit example
  static uint8_t getBatteryPercent() {
    uint32_t bat = analogRead(VBAT_PIN) * VBAT_NUM / VBAT_DEN;
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