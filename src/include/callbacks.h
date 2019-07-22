#if !defined(CALLBACKS_H)
#define CALLBACKS_H

#include <ble_gap.h>

#include "dbgcfg.h"

namespace callback {
void cent_connect(uint16_t conn_handle);
void cent_disconnect(uint16_t conn_handle, uint8_t reason);
void scan(ble_gap_evt_adv_report_t* report);
#if defined(USB_MASTER)
void hid_report_callback(uint8_t report_id,
                         hid_report_type_t report_type,
                         uint8_t const* buffer,
                         uint16_t bufsize);
void leftuart_rx_callback(BLEClientUart& uart_svc);
void rightuart_rx_callback(BLEClientUart& uart_svc);
void updateClientStatus();
#else
void core_connect(uint16_t conn_handle);
void core_disconnect(uint16_t conn_handle, uint8_t reason);
#endif
} // namespace callback

#endif
