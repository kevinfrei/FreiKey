#if !defined(RIGHT_ENTRY_POINTS_H)
#define RIGHT_ENTRY_POINTS_H

#include "dbgcfg.h"

void startAdv();
void cent_connect_callback(uint16_t conn_handle);
void cent_disconnect_callback(uint16_t conn_handle, uint8_t reason);
void core_connect_callback(uint16_t conn_handle);
void core_disconnect_callback(uint16_t conn_handle, uint8_t reason);
void scan_callback(ble_gap_evt_adv_report_t* report);

#endif
