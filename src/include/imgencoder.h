#pragma once

bool encode_nqrle16(const uint8_t* data,
                    uint32_t bytes,
                    void (*print)(uint8_t byte));

bool encode_palette(const uint8_t* data,
                    uint32_t bytes,
                    void (*print)(uint8_t byte));
