#if !defined(CALLBACKS_H)
#define CALLBACKS_H

#include <ble_gap.h>

#include "dbgcfg.h"

namespace callback {
void cent_connect(uint16_t conn_handle);
void cent_disconnect(uint16_t conn_handle, uint8_t reason);
void core_connect(uint16_t conn_handle);
void core_disconnect(uint16_t conn_handle, uint8_t reason);
void scan(ble_gap_evt_adv_report_t* report);
} // namespace callback

#endif
