#pragma once

#include "adafruit_nrf52/mpu.h"
#include "battery.h"
#include "keymatrix.h"
#include "leds.h"

// clang-format off

using LeftMatrix = KeyMatrix<AdafruitNRF52,
  // Cols, Rows
  7, 6,
  // Column Pins:
  15, A0, 16, 7, A6, 27, 11,
  // Row Pins:
  A3, 12, 13, A4, A2, A1>;

using RightMatrix = KeyMatrix<AdafruitNRF52,
  // Cols, Rows
  7, 6,
  // Column Pins:
  29, 16, 15, 7, 27, 11, 30,
  // Row Pins:
  13, 4, 2, 3, 5, 12>;

// clang-format on

struct LeftBoard : public LeftMatrix,
                   public Digital_LEDs<LED_RED, LED_BLUE>,
                   public Analog_LED<A5>,
                   public Battery<PIN_VBAT> {
  static void Configure() {
    ConfigMatrix();
    ConfigLEDs();
    ConfigLED();
    ConfigBattery();
  }
};

struct RightBoard : public RightMatrix,
                    public Digital_LEDs<LED_RED, LED_BLUE>,
                    public Analog_LED<28>,
                    public Battery<PIN_VBAT> {
  static void Configure() {
    ConfigMatrix();
    ConfigLEDs();
    ConfigLED();
    ConfigBattery();
  };
};
