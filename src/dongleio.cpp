#include "mybluefruit.h"

#include "dbgcfg.h"
#include "dongleio.h"
#include "globals.h"

Adafruit_NeoPixel DongleIO::neopix{1, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800};

void DongleIO::Configure() {
  // This is the user switch
  pinMode(7, INPUT_PULLUP);
  // Blink the RGB light on the board
  neopix.begin();
  setRGB(7, 5, 0);
  delay(125);
  setRGB(0, 0, 0);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
}

void DongleIO::setRed(bool on) {
  digitalWrite(LED_RED, on ? HIGH : LOW);
}

void DongleIO::setBlue(bool on) {
  digitalWrite(LED_BLUE, on ? HIGH : LOW);
}

void DongleIO::setRGB(uint8_t r, uint8_t g, uint8_t b) {
  neopix.setPixelColor(0, r, g, b);
  neopix.show();
}


// Called when the system detects someone looking for a client
void DongleIO::scan(ble_gap_evt_adv_report_t* report) {
  // Connect to device with bleuart service in advertising
  Bluefruit.Central.connect(report);
}

uint32_t DongleIO::connect_time = 0;
bool DongleIO::black = true;

void DongleIO::updateClientStatus() {
  uint32_t theDelay = millis() - connect_time;
  if (theDelay < 10000) {
    uint32_t red = (rightHandle == BLE_CONN_HANDLE_INVALID) ? 0 : 0xFF;
    uint8_t blue = (leftHandle == BLE_CONN_HANDLE_INVALID) ? 0 : 0xFF;
    theDelay = (10000 - theDelay) / 100;
    theDelay = theDelay * theDelay * theDelay;
    DongleIO::setRGB(red * theDelay / 1000000, 0, blue * theDelay / 1000000);
    black = false;
  } else if (!black) {
    DongleIO::setRGB(0, 0, 0);
    black = true;
  }
}

void DongleIO::leftuart_rx_callback(BLEClientUart& uart_svc) {
  // TODO: Make this async
  // i.e. make it a state, and have the central loop
  // do the actual work...
  DongleIO::setRGB(0, 0, 5);
  black = false;
  delayMicroseconds(25);
  updateClientStatus();
}

void DongleIO::rightuart_rx_callback(BLEClientUart& uart_svc) {
  // TODO: Make this async
  // i.e. make it a state, and have the central loop
  // do the actual work...
  DongleIO::setRGB(1, 0, 0);
  black = false;
  delayMicroseconds(25);
  updateClientStatus();
}

// Called when we find a UART host to connect with
void DongleIO::cent_connect(uint16_t conn_handle) {
  // TODO: Maybe make this more secure? I haven't looked into how secure this
  // is in the documentation :/
  char peer_name[32] = {0};
  BLEClientUart* remoteUart = nullptr;
  Bluefruit.Connection(conn_handle)->getPeerName(peer_name, sizeof(peer_name));
  // I ought to at least make sure the peer_name is LHS_NAME, right?
  // TODO: Figure out if this is the left or right uart
  if (!strcmp(LTCL_NAME, peer_name) && leftUart.discover(conn_handle)) {
    remoteUart = &leftUart;
    leftHandle = conn_handle;
    connect_time = millis();
    updateClientStatus();
  } else if (!strcmp(RTCL_NAME, peer_name) && rightUart.discover(conn_handle)) {
    remoteUart = &rightUart;
    rightHandle = conn_handle;
    connect_time = millis();
    updateClientStatus();
  }  else {
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
  Bluefruit.Scanner.start(0);
  resetTheWorld();
}

// Called with a UART host disconnects
void DongleIO::cent_disconnect(uint16_t conn_handle, uint8_t reason) {
  // TODO: Disconnect the *correct* side
  if (conn_handle == leftHandle) {
    leftHandle = BLE_CONN_HANDLE_INVALID;
  } else if (conn_handle == rightHandle) {
    rightHandle = BLE_CONN_HANDLE_INVALID;
  }
  updateClientStatus();
  resetTheWorld();
}

// Output report callback for LED indicator such as Caplocks
void DongleIO::hid_report_callback(uint8_t report_id,
                         hid_report_type_t report_type,
                         uint8_t const* buffer,
                         uint16_t bufsize) {
  // LED indicator is output report with only 1 byte length
  if (report_type != HID_REPORT_TYPE_OUTPUT)
    return;

  // The LED bit map is as follows: (also defined by KEYBOARD_LED_* )
  // Kana (4) | Compose (3) | ScrollLock (2) | CapsLock (1) | Numlock (0)
  uint8_t ledIndicator = buffer[0];

  // turn on LED if caplock is set
  digitalWrite(LED_BUILTIN, ledIndicator & KEYBOARD_LED_CAPSLOCK);
}

void rtos_idle_callback(void) {}
