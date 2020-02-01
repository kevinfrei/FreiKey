#include <string.h>

#include "boardio.h"
#include "mock.h"

#if defined(TEENSY)
extern "C" {
#endif
void setup();
void loop();
#if defined(TEENSY)
}
#endif

int main(int argc, const char* argv[]) {
  setup();
  while (1) {
    loop();
  }
}

void pinMode(uint16_t, uint8_t) {
  // TODO: Check to make sure we're using the pins right in
  // digital/analog/read/write
}

void digitalWrite(uint16_t pin, uint32_t val) {
  // TODO: check, record, report?
}

uint8_t digitalRead(uint16_t pin) {
  // TODO: Make this do some stuff?
  return 0;
}

void waitForEvent() {}

void delayMicroseconds(uint64_t us) {
  // TODO: Sleep here?
}

void delay(uint32_t ms) {
  delayMicroseconds(ms * 1000);
}

// TODO: Make this work for real?
uint32_t millis() {
  static uint32_t time = 0;
  return time++;
}

SerialMock Serial;
void SerialMock::begin(uint32_t) {}
void SerialMock::print(const char*) {}
void SerialMock::print(uint32_t, int) {}
void SerialMock::printf(const char*, ...) {}
void SerialMock::println(char const*) {}
void SerialMock::println(uint32_t, int) {}
SerialMock::operator bool() {
  return true;
}

void CentralMock::setConnectCallback(void (*)(uint16_t)) {}
void CentralMock::setDisconnectCallback(void (*)(uint16_t, uint8_t)) {}
void CentralMock::connect(bool) {}

void ScannerMock::filterUuid(uint8_t const*) {}
void ScannerMock::setInterval(uint16_t, uint16_t) {}
void ScannerMock::setRxCallback(void (*)(ble_gap_evt_adv_report_t*)) {}
void ScannerMock::useActiveScan(bool) {}
void ScannerMock::restartOnDisconnect(bool) {}
void ScannerMock::start(uint8_t) {}

void BLEClientUart::setRxCallback(void (*)(BLEClientUart&)) {}
char BLEClientUart::read() {
  return 0;
}
void BLEClientUart::begin() {}
void BLEClientUart::write(char const*, size_t) {}
void BLEClientUart::write(char) {}
bool BLEClientUart::discover(uint16_t) {
  return true;
}
bool BLEClientUart::available() {
  return true;
}
void BLEClientUart::enableTXD() {}

ConnectionMock connection;
// TODO: This needs to be used for both a left & right side to do stuff right
const char* mock_name = "name";
void ConnectionMock::getPeerName(char* name, size_t sz) {
  strcpy(name, mock_name);
}
void ConnectionMock::disconnect() {}

BluefruitMock Bluefruit;
void BluefruitMock::begin(uint32_t, uint32_t) {}
void BluefruitMock::autoConnLed(bool) {}
void BluefruitMock::setTxPower(uint8_t) {}
void BluefruitMock::setName(const char*) {}
void BluefruitMock::printInfo() {}
ConnectionMock* BluefruitMock::Connection(uint16_t) {
  return &connection;
}

void Adafruit_NeoPixel::begin() {}
void Adafruit_NeoPixel::setPixelColor(uint8_t, uint8_t, uint8_t, uint8_t) {}
void Adafruit_NeoPixel::show() {}

// Tiny USB stuff
void Adafruit_USBD_HID::setPollInterval(uint32_t) {}
void Adafruit_USBD_HID::setReportDescriptor(const uint8_t*, size_t) {}
void Adafruit_USBD_HID::begin() {}
bool Adafruit_USBD_HID::ready() {
  return true;
}
void Adafruit_USBD_HID::keyboardRelease(uint8_t) {}
void Adafruit_USBD_HID::keyboardReport(uint8_t, uint8_t, uint8_t*) {}
void Adafruit_USBD_HID::sendReport(uint8_t, uint16_t*, size_t) {}
void Adafruit_USBD_HID::setReportCallback(
    const char*,
    void (*func)(uint8_t, hid_report_type_t, const uint8_t*, uint16_t)) {}
// Adafruit graphics stuff

WireMock Wire;
Adafruit_SSD1306::Adafruit_SSD1306(uint16_t width,
                                   uint16_t height,
                                   void*,
                                   uint8_t resetPin) {}
void Adafruit_SSD1306::begin(uint32_t, uint8_t) {}
void Adafruit_SSD1306::display() {}

// Teensy stuff
KeyboardMock Keyboard;
void KeyboardMock::press(uint16_t) {}
void KeyboardMock::release(uint16_t) {}
void KeyboardMock::set_key1(uint8_t) {}
void KeyboardMock::set_key2(uint8_t) {}
void KeyboardMock::set_key3(uint8_t) {}
void KeyboardMock::set_key4(uint8_t) {}
void KeyboardMock::set_key5(uint8_t) {}
void KeyboardMock::set_key6(uint8_t) {}
void KeyboardMock::set_modifier(uint8_t) {}
void KeyboardMock::send_now() {}

BoardIO::bits BoardIO::Read() const {
  BoardIO::bits switches{};
  return switches;
}
