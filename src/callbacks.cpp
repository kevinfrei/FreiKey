#include <bluefruit.h>

#include "callbacks.h"
#include "globals.h"
#include "right-master.h"

namespace callback {

// This is registered to be called when you connection a computer
void core_connect(uint16_t handle) {
  DBG(dumpHex(handle, "Core Connected: "));
  char buf[501];
  Bluefruit.Gap.getPeerName(handle, buf, 500);
  DBG(Serial.println("Peer Name:"));
  DBG(Serial.println(buf));
  core_handle = handle;
#if 0 // The Bluetooth stuff isn't working for PC just yet...
  if (!strstr(buf, "mac")) {
    // If we're not on a mac, set the keyboard in Windows mode
    // This is *incredibly* low-tech, but it works for my purposes :/
    layer_push(LAYER_WIN_BASE);
  }
#endif
}

void core_disconnect(uint16_t handle, uint8_t reason) {
  DBG(dumpHex(handle, "Core Disconnected: "));
  DBG(dumpHex(reason, "Reason: 0x"));
  core_handle = 0xFFFF;
}

void cent_connect(uint16_t conn_handle) {
  // TODO: Maybe make this more secure? I haven't looked into how secure this
  // is in the documentation :/
  char peer_name[32] = {0};
  Bluefruit.Gap.getPeerName(conn_handle, peer_name, sizeof(peer_name));
  // I ought to at least make sure the peer_name is LHS_NAME, right?
  if (!strcmp(LHS_NAME, peer_name) && clientUart.discover(conn_handle)) {
    DBG(Serial.print("[Cent] Connected to "));
    DBG(Serial.println(peer_name));
    DBG(Bluefruit.printInfo());
    // Enable TXD's notify
    clientUart.enableTXD();
  } else {
    DBG(Serial.println("[Cent] Not connecting to the other side: wrong name"));
    DBG(Serial.print("Was expecting: "));
    DBG(Serial.println(LHS_NAME));
    DBG(Serial.print("Actual name: "));
    DBG(Serial.println(peer_name));
    Bluefruit.Central.disconnect(conn_handle);
  }

  resetTheWorld();
}

void cent_disconnect(uint16_t conn_handle, uint8_t reason) {
  DBG(dumpVal(conn_handle, "Connection Handle Disconnected: "));
  DBG(dumpVal(reason, " Reason #"));
  DBG(Serial.println("[Cent] Disconnected"));
  resetTheWorld();
}

void scan(ble_gap_evt_adv_report_t* report) {
  // Check if advertising contain BleUart service
  if (Bluefruit.Scanner.checkReportForService(report, clientUart)) {
    // Connect to device with bleuart service in advertising
    Bluefruit.Central.connect(report);
  }
}

} // namespace callback
