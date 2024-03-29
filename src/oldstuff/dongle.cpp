#include "sysstuff.h"

#include "dbgcfg.h"
#include "debounce.h"
#include "dongle.h"
#include "general.h"
#include "globals.h"
#include "hardware.h"
#include "host-comm.h"

#if defined(MACRO_PAD)

constexpr std::array<uint8_t, 6> padPins = {A5, A4, A3, A2, A1, A0};
Debouncer<MacroBits> debouncer{};
#endif

// Report ID's
constexpr uint8_t RID_KEYBOARD = 1;
constexpr uint8_t RID_CONSUMER = 2;

// Composite HID report including both a keyboard and consumer device
// Necessary to support the consumer keys (volume/play/pause, etc...)
uint8_t const desc_hid_report[] = {
  TUD_HID_REPORT_DESC_KEYBOARD(HID_REPORT_ID(RID_KEYBOARD)),
  TUD_HID_REPORT_DESC_CONSUMER(HID_REPORT_ID(RID_CONSUMER))};

Adafruit_NeoPixel Dongle::neopix{1, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800};
BLEClientUart Dongle::leftUart;
BLEClientUart Dongle::rightUart;
uint16_t Dongle::leftHandle = BLE_CONN_HANDLE_INVALID;
uint16_t Dongle::rightHandle = BLE_CONN_HANDLE_INVALID;
Adafruit_USBD_HID Dongle::usb_hid(
  desc_hid_report, sizeof(desc_hid_report), HID_ITF_PROTOCOL_NONE, 2, false);

void Dongle::blink(bool leaveOn) {
  for (int i = 0; i < 10; i++) {
    Dongle::setRed(true);
    Dongle::setBlue(false);
    delay(25);
    Dongle::setRed(false);
    Dongle::setBlue(true);
    delay(25);
  }
  if (leaveOn) {
    // Leave on:
    Dongle::setRed(true);
  } else {
    // Leave off:
    Dongle::setBlue(false);
  }
}

void initSerial() {
  // 5 seconds until we resume
  DBG(Serial.begin(115200));
  uint32_t wait = millis();
  while (!Serial) {
    delay(50);
    if (millis() - wait > 1000)
      break;
  }
  if (!!Serial) {
    Serial.println("Here we are");
  }
  // Don't do this: it makes the thing wait until you're actively watching
  // data on the Serial port, which is *not* what I generally want...
}

// Configure all the non-BLE hardware
void Dongle::Configure() {
  // This is the user switch
  pinMode(7, INPUT_PULLUP);
  // Blink the RGB light on the board
  neopix.begin();
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  // Setup the USB stuff
  usb_hid.setReportCallback(nullptr, Dongle::hid_report_callback);
  usb_hid.begin();
  DBG(initSerial());
  for (int j = 0; j < 50 && !TinyUSBDevice.mounted(); j++) {
    blinkRGB(255, 255, 255, 25);
    delay(25);
  }
  setRGB(0, 127, 127);
  delay(250);
#if defined(MACRO_PAD)
  for (auto pin : padPins) {
    pinMode(pin, INPUT_PULLUP);
  }
#endif
}

// Light up the Bluetooth stack
void Dongle::StartListening() {
  // No central and 2 peripheral
  Bluefruit.begin(0, 2);
  Bluefruit.autoConnLed(false);
  // Acceptable values: -40, -30, -20, -16, -12, -8, -4, 0, 4
  Bluefruit.setTxPower(4);
  Bluefruit.setName(BT_NAME);

  leftUart.begin();
  leftUart.setRxCallback(comm::recv::data);
  rightUart.begin();
  rightUart.setRxCallback(comm::recv::data);

  Bluefruit.Central.setConnectCallback(Dongle::cent_connect);
  Bluefruit.Central.setDisconnectCallback(Dongle::cent_disconnect);

  /* Start Central Scanning
   * - Enable auto scan if disconnected
   * - Interval = 100 ms, window = 80 ms
   * - Filter only accept bleuart service
   * - Don't use active scan
   * - Start(timeout) with timeout = 0 will scan forever (until connected)
   */
  Bluefruit.Scanner.setRxCallback(Dongle::scan);
  Bluefruit.Scanner.restartOnDisconnect(true);
  Bluefruit.Scanner.setInterval(160, 80); // in unit of 0.625 ms
  Bluefruit.Scanner.filterUuid(BLEUART_UUID_SERVICE);
  Bluefruit.Scanner.useActiveScan(false);
  Bluefruit.Scanner.start(0); // 0 = Don't stop scanning after n seconds
}

bool Dongle::Ready() {
  return usb_hid.ready();
}

bool Dongle::BothSides() {
  return (rightHandle != BLE_CONN_HANDLE_INVALID) &&
         (leftHandle != BLE_CONN_HANDLE_INVALID);
}

void Dongle::Reset() {
  /*
  usb_hid.keyboardRelease(RID_KEYBOARD);
  Dongle::ConsumerRelease();
  */
}

void Dongle::ReportKeys(uint8_t mods, uint8_t* report) {
#if defined(DEBUG) && DEBUG > 1
  Serial.printf("mods=%x: ", mods);
  for (int i = 0; i < 6; i++) {
    Serial.print(" ");
    Serial.print(report[i], HEX);
  }
  Serial.println("");
#endif
  usb_hid.keyboardReport(RID_KEYBOARD, mods, report);
}

void Dongle::ConsumerPress(uint16_t key) {
  DBG2(dumpHex(key, "Consumer Press: "));
  usb_hid.sendReport(RID_CONSUMER, &key, sizeof(key));
}

void Dongle::ConsumerRelease() {
  DBG2(Serial.println("Consumer Release"));
  uint16_t zero = 0;
  usb_hid.sendReport(RID_CONSUMER, &zero, sizeof(zero));
}

void Dongle::setRed(bool on) {
  digitalWrite(LED_RED, on ? HIGH : LOW);
}

void Dongle::setBlue(bool on) {
  digitalWrite(LED_BLUE, on ? HIGH : LOW);
}

void Dongle::setRGB(uint8_t r, uint8_t g, uint8_t b) {
  neopix.setPixelColor(0, r, g, b);
  neopix.show();
}

void Dongle::setRGB(uint32_t rgb) {
  Dongle::setRGB((rgb >> 16) & 0xff, (rgb >> 8) & 0xff, rgb & 0xff);
}

void Dongle::blinkRGB(uint8_t r, uint8_t g, uint8_t b, uint16_t length) {
  setRGB(r, g, b);
  delay(length);
  setRGB(0, 0, 0);
}

// Called when the system detects someone looking for a client
void Dongle::scan(ble_gap_evt_adv_report_t* report) {
  // Connect to device with bleuart service in advertising
  Bluefruit.Central.connect(report);
}

uint32_t Dongle::connect_time = 0;
bool Dongle::black = true;

// This updates the RGB LED to show something when the left & right sides
// connect to the dongle
uint8_t lastLBat = 0xff;
uint8_t lastRBat = 0xff;
uint8_t vals[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 7, 6, 5, 4, 3, 2, 1};
void Dongle::updateClientStatus(uint32_t now,
                                uint8_t batLeft,
                                uint8_t batRight) {
  uint32_t theDelay = now - connect_time;
  if (theDelay < 10000) {
    uint32_t red = (rightHandle == BLE_CONN_HANDLE_INVALID) ? 0 : 0xFF;
    uint8_t blue = (leftHandle == BLE_CONN_HANDLE_INVALID) ? 0 : 0xFF;
    theDelay = (10000 - theDelay) / 100;
    theDelay = theDelay * theDelay * theDelay;
    Dongle::setRGB(red * theDelay / 1000000, 0, blue * theDelay / 1000000);
    black = false;
  } else if (!black) {
    Dongle::setRGB(0, 0, 0);
    black = true;
  } else {
    uint8_t g = vals[(now >> 16) & 15];
    uint8_t b = vals[(now >> 13) & 15];
    uint8_t r = vals[(now >> 10) & 15];
    Dongle::setRGB(r, g, b);
  }
}

// Called when we find a UART host to connect with
void Dongle::cent_connect(uint16_t conn_handle) {
  // TODO: Maybe make this more secure? I haven't looked into how secure this
  // is in the documentation :/
  char peer_name[32] = {0};
  BLEClientUart* remoteUart = nullptr;
  Bluefruit.Connection(conn_handle)->getPeerName(peer_name, sizeof(peer_name));
  // Figure out if this is the left or right uart
  if (!strcmp(LTCL_NAME, peer_name) && leftUart.discover(conn_handle)) {
    remoteUart = &leftUart;
    leftHandle = conn_handle;
    curState.left.connected = true;
    connect_time = millis();
    updateClientStatus(connect_time, lastLBat, lastRBat);
  } else if (!strcmp(RTCL_NAME, peer_name) && rightUart.discover(conn_handle)) {
    remoteUart = &rightUart;
    rightHandle = conn_handle;
    curState.right.connected = true;
    connect_time = millis();
    updateClientStatus(connect_time, lastLBat, lastRBat);
  } else {
    DBG(Serial.println("[Cent] Not connecting to the client: wrong name"));
    DBG(Serial.printf("Requester name: %s\n", peer_name));
    Bluefruit.Connection(conn_handle)->disconnect();
    return;
  }

  DBG(Serial.printf("[Cent] Connected to %s\n", peer_name));
  DBG(Bluefruit.printInfo());

  // Enable TXD's notify
  remoteUart->enableTXD();
  // Just keep scanning
  // I tried to detect if we've got both sides connected, but that
  // looks somewhat unreliable :(
  if (leftHandle == BLE_CONN_HANDLE_INVALID ||
      rightHandle == BLE_CONN_HANDLE_INVALID) {
    Bluefruit.Scanner.start(0);
  }
  resetTheWorld();
}

// Called when a UART host disconnects
void Dongle::cent_disconnect(uint16_t conn_handle, uint8_t reason) {
  // TODO: Disconnect the *correct* side
  if (conn_handle == leftHandle) {
    leftHandle = BLE_CONN_HANDLE_INVALID;
    curState.left.connected = false;
    Bluefruit.Scanner.start(0);
  } else if (conn_handle == rightHandle) {
    rightHandle = BLE_CONN_HANDLE_INVALID;
    curState.right.connected = false;
    Bluefruit.Scanner.start(0);
  }
  updateClientStatus(millis(), lastLBat, lastRBat);
  resetTheWorld();
}

// Output report callback for LED indicator such as Caplocks
void Dongle::hid_report_callback(uint8_t report_id,
                                 hid_report_type_t report_type,
                                 uint8_t const* buffer,
                                 uint16_t bufsize) {
  // LED indicator is output report with only 1 byte length
  if (report_type != HID_REPORT_TYPE_OUTPUT)
    return;

  // The LED bit map is as follows: (also defined by KEYBOARD_LED_* )
  // Kana (4) | Compose (3) | ScrollLock (2) | CapsLock (1) | Numlock (0)
  // turn on LED if caplock is set
  digitalWrite(LED_BUILTIN, (buffer[0] & KEYBOARD_LED_CAPSLOCK) ? HIGH : LOW);
}

#if defined(MACRO_PAD)

MacroBits Dongle::key_scan(uint32_t now) {
  // This should handle anything related to the buttons themselves
  // rb(A0, 150), cb(A1, 150), lb(A2, 150), rt(A3), ct(A4), lt(A5);
  MacroBits res{0};
  uint8_t bit = 0;
  for (auto pin : padPins) {
    if (digitalRead(pin) == HIGH) {
      res.clear_bit(bit);
    } else {
      res.set_bit(bit);
    }
    bit++;
  }
  return debouncer.update(res, now);
}

#endif

void rtos_idle_callback(void) {}
