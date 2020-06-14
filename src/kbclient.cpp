#include "sysstuff.h"

#include "boardio.h"
#include "client-comm.h"
#include "hardware.h"
#include "kbclient.h"

BLEDis KBClient::bledis;
uint32_t KBClient::stateTime = 0;
SleepState KBClient::sleepState{0, false};
state::hw KBClient::lastRead{};
BLEUart KBClient::bleuart;
bool KBClient::notified;
uint32_t KBClient::lastDelta = 0;

volatile bool KBClient::interruptsEnabled = false;
volatile bool KBClient::interruptTriggered = false;

void KBClient::enableInterrupts() {
  if (!KBClient::interruptsEnabled) {
    DBG(Serial.println("Enabling Interrupts"));
    BoardIO::setInterrupts(KBClient::interruptHandler);
    KBClient::interruptsEnabled = true;
  }
  DBG(Serial.println("Enabled Interrupts"));
}

void KBClient::disableInterrupts() {
  if (KBClient::interruptsEnabled) {
    DBG(Serial.println("Disabling Interrupts"));
    BoardIO::disableInterrupts();
    KBClient::interruptsEnabled = false;
  }
  DBG(Serial.println("Disabled Interrupts"));
}

void KBClient::interruptHandler() {
  KBClient::interruptTriggered = true;
}

void KBClient::setup(const char* name) {
  DBG(Serial.begin(115200));
  Bluefruit.begin(1, 0);
  // Don't use the Bluetooth LED
  Bluefruit.autoConnLed(false);
  // I had turned this all the way down. Given that my receiver is less than
  // 20 cm away, I didn't know if it would be enough. I bumped it up to 20,
  // because it seemed like I was occasionally seeing weirdness that I wasn't
  // when it was set at 0. If you spread your keyboards apart greater
  // distance, you may want to try higher power. Acceptable values are -40,
  // -30, -20, -16, -12, -8, -4, 0, 4
  Bluefruit.setTxPower(0);
  Bluefruit.setName(name);

  bledis.setManufacturer(MANUFACTURER);
  bledis.setModel(MODEL);
  bledis.begin();

  bleuart.begin();
  bleuart.setRxCallback(comm::recv::data);

  // Start Advertising the UART service to talk to the other half...
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addService(bleuart);
  Bluefruit.ScanResponse.addName();
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244); // in unit of 0.625 ms
  Bluefruit.Advertising.setFastTimeout(30); // number of seconds in fast mode
  // I should probably stop advertising after a while if that's possible. I
  // have switches now, so if I need it to advertise, I can just punch the
  // power.
  Bluefruit.Advertising.start(0); // 0 = Don't stop advertising after n
                                  // seconds
  BoardIO::Configure();
  KBClient::lastDelta = millis();
  KBClient::interruptTriggered = false;
  KBClient::notified = true;
  enableInterrupts();
}

// TODO: Add bidirectional communication, so the master can ask for info or set
// TODO: an LED state somehow
// TODO: Also make this thing use interrupts to 'wake from sleep' instead of the
// TODO: current 'reduce scan speed and miss keystrokes until they're held down
// TODO: for .25s' malarkey
void KBClient::loop() {
  uint32_t now = millis();
  state::hw down{now, KBClient::lastRead};

  if (KBClient::sleepState.CheckForSleeping(down.switches, now)) {
    // I'm assuming this saves power. If it doesn't, there's no point...
    delay(250);
  } else if (down != KBClient::lastRead) {
    if (KBClient::lastRead.battery_level != down.battery_level) {
      comm::send::battery(KBClient::bleuart, down.battery_level);
    }
    KBClient::lastRead = down;
    DBG2(down.dump());
    comm::send::scan(KBClient::bleuart, lastRead.switches);
  }
  waitForEvent(); // Request CPU enter low-power mode until an event occurs
}

void setup() {
  KBClient::setup(CLIENT_NAME);
}

void loop() {
  KBClient::loop();
}
