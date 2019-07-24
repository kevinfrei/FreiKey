#include "mybluefruit.h"

#include "callbacks.h"
#include "globals.h"
#include "right-master.h"

namespace callback {

#if !defined(USB_MASTER)
// This is registered to be called when you connect a computer
void core_connect(uint16_t handle) {
#if DBG
  DBG(dumpHex(handle, "Core Connected: "));
  char peer_name[501];
  Bluefruit.Connection(handle)->getPeerName(peer_name, sizeof(peer_name));
  DBG(Serial.println("Peer Name:"));
  DBG(Serial.println(peer_name));
#endif
  core_handle = handle;
  sleepState.EndForcedSleepMode();
#if 0 // The Bluetooth stuff isn't working for PC just yet...
  if (!strstr(buf, "mac")) {
    // If we're not on a mac, set the keyboard in Windows mode
    // This is *incredibly* low-tech, but it works for my purposes :/
    layer_push(LAYER_WIN_BASE);
  }
#endif
}

// Called when the host computer disconnects
void core_disconnect(uint16_t handle, uint8_t reason) {
  DBG(dumpHex(handle, "Core Disconnected: "));
  DBG(dumpHex(reason, "Reason: 0x"));
  core_handle = 0xFFFF;
  sleepState.BeginForcedSleepMode();
}
#endif

// Called when the system detects someone looking for a client
void scan(ble_gap_evt_adv_report_t* report) {
  // Connect to device with bleuart service in advertising
  Bluefruit.Central.connect(report);
}

uint32_t connect_time = 0;
bool black = true;
void updateClientStatus() {
  uint32_t theDelay = millis() - connect_time;
  if (theDelay < 10000) {
    uint32_t red = (rightHandle == BLE_CONN_HANDLE_INVALID) ? 0 : 0xFF;
    uint8_t blue = (leftHandle == BLE_CONN_HANDLE_INVALID) ? 0 : 0xFF;
    theDelay = (10000 - theDelay) / 100;
    theDelay = theDelay * theDelay * theDelay;
    neopix.setPixelColor(
        0, red * theDelay / 1000000, 0, blue * theDelay / 1000000);
    neopix.show();
    black = false;
  } else if (!black) {
    neopix.setPixelColor(0, 0, 0, 0);
    neopix.show();
    black = true;
  }
}

void leftuart_rx_callback(BLEClientUart& uart_svc) {
  // TODO: Make this async
  // i.e. make it a state, and have the central loop
  // do the actual work...
  neopix.setPixelColor(0, 0, 0, 5);
  neopix.show();
  black = false;
  delayMicroseconds(25);
  updateClientStatus();
}

void rightuart_rx_callback(BLEClientUart& uart_svc) {
  // TODO: Make this async
  // i.e. make it a state, and have the central loop
  // do the actual work...
  neopix.setPixelColor(0, 1, 0, 0);
  neopix.show();
  black = false;
  delayMicroseconds(25);
  updateClientStatus();
}

// Called when we find a UART host to connect with
void cent_connect(uint16_t conn_handle) {
  // TODO: Maybe make this more secure? I haven't looked into how secure this
  // is in the documentation :/
  char peer_name[32] = {0};
  BLEClientUart* remoteUart = nullptr;
  Bluefruit.Connection(conn_handle)->getPeerName(peer_name, sizeof(peer_name));
  // I ought to at least make sure the peer_name is LHS_NAME, right?
#if defined(USB_MASTER)
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
  }
#else
  if (!strcmp(LHS_NAME, peer_name) && clientUart.discover(conn_handle)) {
    remoteUart = &clientUart;
  }
#endif
  else {
    DBG(Serial.println("[Cent] Not connecting to the client: wrong name"));
    DBG(Serial.printf("Requester name: %s\n", peer_name));
    Bluefruit.Connection(conn_handle)->disconnect();
    return;
  }

  DBG(Serial.printf("[Cent] Connected to %s\n", peer_name));
  DBG(Bluefruit.printInfo());

  // Enable TXD's notify
  remoteUart->enableTXD();
#if defined(USB_MASTER)
  // Just keep scanning
  // I tried to detect if we've got both sides connected, but that
  // looks somewhat unreliable :(
  Bluefruit.Scanner.start(0);
#endif
  resetTheWorld();
}

// Called with a UART host disconnects
void cent_disconnect(uint16_t conn_handle, uint8_t reason) {
#if defined(USB_MASTER)
  // TODO: Disconnect the *correct* side
  if (conn_handle == leftHandle) {
    leftHandle = BLE_CONN_HANDLE_INVALID;
  } else if (conn_handle == rightHandle) {
    rightHandle = BLE_CONN_HANDLE_INVALID;
  }
  updateClientStatus();
#else
  DBG(dumpVal(conn_handle, "Connection Handle Disconnected: "));
  DBG(dumpVal(reason, " Reason #"));
  DBG(Serial.println("[Cent] Disconnected"));
#endif
  resetTheWorld();
}

#if defined(USB_MASTER)
// Output report callback for LED indicator such as Caplocks
void hid_report_callback(uint8_t report_id,
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
#endif
} // namespace callback

void rtos_idle_callback(void) {}
