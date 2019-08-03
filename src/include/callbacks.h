#pragma once

#if !defined(USB_MASTER)

#include <ble_gap.h>

#include "dbgcfg.h"

namespace callback {
void cent_connect(uint16_t conn_handle);
void cent_disconnect(uint16_t conn_handle, uint8_t reason);
void core_connect(uint16_t conn_handle);
void core_disconnect(uint16_t conn_handle, uint8_t reason);
} // namespace callback

#endif
