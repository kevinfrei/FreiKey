#pragma once

#include "adafruit_nrf52/mpu.h"
#include "battery.h"
#include "keymatrix.h"
#include "leds.h"

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

// clang-format on

struct LeftBoard : public LeftKarbonMatrix,
                   public Digital_LEDs<LED_RED, LED_BLUE>,
                   public No_Analog_LED,
                   public Battery<PIN_VBAT> {
  static void Configure() {
    ConfigMatrix();
    ConfigLEDs();
    ConfigBattery();
  }
};

struct RightBoard : public RightKarbonMatrix,
                    public Digital_LEDs<LED_RED, LED_BLUE>,
                    public No_Analog_LED,
                    public Battery<PIN_VBAT> {
  static void Configure() {
    ConfigMatrix();
    ConfigLEDs();
    ConfigBattery();
  }
};
