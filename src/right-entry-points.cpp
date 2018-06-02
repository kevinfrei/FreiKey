#include <bluefruit.h>

#include "dbgcfg.h"
#include "globals.h"
#include "shared.h"

void startAdv();
void resetKeyMatrix();
void cent_connect_callback(uint16_t conn_handle);
void cent_disconnect_callback(uint16_t conn_handle, uint8_t reason);
void core_connect_callback(uint16_t conn_handle);
void core_disconnect_callback(uint16_t conn_handle, uint8_t reason);
void scan_callback(ble_gap_evt_adv_report_t* report);

// In Arduino world the 'setup' function is called to initialize the device.
// The 'loop' function is called over & over again, after setup completes.
void setup() {
  shared_setup();
  resetKeyMatrix();

  // Central and peripheral
  Bluefruit.begin(true, true);
  // Bluefruit.clearBonds();
  Bluefruit.autoConnLed(true);

  battery.begin();

  // I'm assuming that by dropping this power down, I'll save some battery life.
  // I should experiment to see how low I can get it and still communicate with
  // both my Mac and my PC reliably. They're each within a meter of the
  // keyboard... Acceptable values: -40, -30, -20, -16, -12, -8, -4, 0, 4
  Bluefruit.setTxPower(4);
  Bluefruit.setName(BT_NAME);

  Bluefruit.Central.setConnectCallback(cent_connect_callback);
  Bluefruit.Central.setDisconnectCallback(cent_disconnect_callback);

  dis.setManufacturer(MANUFACTURER);
  dis.setModel(MODEL);
  dis.setHardwareRev(HW_REV);
  dis.setSoftwareRev(__DATE__);
  dis.begin();

  clientUart.begin();
  Bluefruit.setConnectCallback(core_connect_callback);
  Bluefruit.setDisconnectCallback(core_disconnect_callback);
  // clientUart.setRxCallback(cent_bleuart_rx_callback);

  /* Start Central Scanning
   * - Enable auto scan if disconnected
   * - Interval = 100 ms, window = 80 ms
   * - Filter only accept bleuart service
   * - Don't use active scan
   * - Start(timeout) with timeout = 0 will scan forever (until connected)
   */
  Bluefruit.Scanner.setRxCallback(scan_callback);
  Bluefruit.Scanner.restartOnDisconnect(true);
  Bluefruit.Scanner.setInterval(160, 80); // in unit of 0.625 ms
  Bluefruit.Scanner.filterUuid(BLEUART_UUID_SERVICE);
  Bluefruit.Scanner.useActiveScan(false);
  // I should probably stop advertising after a while if that's possible. I have
  // switches now, so if I need it to advertise, I can just punch the power.
  Bluefruit.Scanner.start(0); // 0 = Don't stop scanning after n seconds

  hid.begin();
  // delay(5000);
  // Bluefruit.printInfo();

  startAdv();
}

void startAdv(void) {
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addAppearance(BLE_APPEARANCE_HID_KEYBOARD);
  Bluefruit.Advertising.addService(hid);

  Bluefruit.ScanResponse.addService(battery);

  Bluefruit.Advertising.addName();
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244); // in unit of 0.625 ms
  Bluefruit.Advertising.setFastTimeout(30); // number of seconds in fast mode
  Bluefruit.Advertising.start(0); // 0 = Don't stop advertising after n seconds
}

void cent_connect_callback(uint16_t conn_handle) {
  // TODO: Maybe make this more secure? I haven't looked into how secure this
  // is in the documentation :/
  char peer_name[32] = {0};
  Bluefruit.Gap.getPeerName(conn_handle, peer_name, sizeof(peer_name));
  // TODO:
  // I ought to at least make sure the peer_name is LHS_NAME, right?
  DBG(Serial.print("[Cent] Connected to "));
  DBG(Serial.println(peer_name));
  DBG(Bluefruit.printInfo());

  if (clientUart.discover(conn_handle)) {
    // Enable TXD's notify
    clientUart.enableTXD();
  } else {
    Bluefruit.Central.disconnect(conn_handle);
  }

  resetKeyMatrix();
}

void cent_disconnect_callback(uint16_t conn_handle, uint8_t reason) {
  DBG(dumpVal(conn_handle, "Connection Handle Disconnected: "));
  DBG(dumpVal(reason, " Reason #"));
  DBG(Serial.println("[Cent] Disconnected"));
  resetKeyMatrix();
}

void scan_callback(ble_gap_evt_adv_report_t* report) {
  // Check if advertising contain BleUart service
  if (Bluefruit.Scanner.checkReportForService(report, clientUart)) {
    // Connect to device with bleuart service in advertising
    Bluefruit.Central.connect(report);
  }
}
