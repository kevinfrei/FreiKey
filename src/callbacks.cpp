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

// Called when we find a UART host to connect with
void cent_connect(uint16_t conn_handle) {
  // TODO: Maybe make this more secure? I haven't looked into how secure this
  // is in the documentation :/
  char peer_name[32] = {0};
  BLEClientUart *remoteUart = nullptr;
  Bluefruit.Connection(conn_handle)->getPeerName(peer_name, sizeof(peer_name));
  // I ought to at least make sure the peer_name is LHS_NAME, right?
#if defined(USB_MASTER)
  // TODO: Figure out if this is the left or right uart
  if (!strcmp(LTCL_NAME, peer_name) && leftUart.discover(conn_handle)) {
    remoteUart = &leftUart;
    for (int i = 0; i < 10; i++) {
      digitalWrite(LED_RED, (i & 1) ? LOW : HIGH);
      delay(100);
    }
  } else if (!strcmp(RTCL_NAME, peer_name) && rightUart.discover(conn_handle)) {
    remoteUart = &rightUart;
    for (int i = 0; i < 4; i++) {
      digitalWrite(LED_RED, (i & 1) ? LOW : HIGH);
      delay(250);
    }
  }
#else
  if (!strcmp(LHS_NAME, peer_name) && clientUart.discover(conn_handle)) {
    remoteUart = &clientUart;
  }
#endif
  else {
    DBG(Serial.println("[Cent] Not connecting to the other side: wrong name"));
    DBG(Serial.print("Was expecting: "));
    DBG(Serial.println(LHS_NAME));
    DBG(Serial.print("Actual name: "));
    DBG(Serial.println(peer_name));
    Bluefruit.Connection(conn_handle)->disconnect();
    return;
  }

  DBG(Serial.print("[Cent] Connected to "));
  DBG(Serial.println(peer_name));
  DBG(Bluefruit.printInfo());
  // Enable TXD's notify
  remoteUart->enableTXD();
  resetTheWorld();
}

// Called with a UART host disconnects
void cent_disconnect(uint16_t conn_handle, uint8_t reason) {
#if defined(USB_MASTER)
  // TODO: Disconnect the *correct* side
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
