#include <ctype.h>
#include <iostream>
#include <stdio.h>

#include "imgencoder.h"

/*
This should spit out the encoded source array
*/

void dumpRLECount(bool repeat, uint32_t count, byte_printer print) {
  if (count == 0 || count > 0x800000) {
    std::cerr << "Derp" << std::endl;
    return;
  }
  // A count instruction is a number encoded with a high stop bit
  // The low bit is true if it's a repeat
  count = count * 2 + !!repeat;
  while (count) {
    uint8_t byte = count & 0x7f;
    count = count >> 7;
    print(byte | (count ? 0 : 0x80));
  }
}

// it should work better for stuff that has strings of unique stuff along with
// strings of repeated stuff
bool encode_rle(bytestream data, uint32_t bytes, byte_printer print) {
  std::function<void(uint16_t)> print2 = [&](uint16_t val) {
    print(val & 0xFF);
    print((val >> 8) & 0xFF);
  };
  return dump_rle(data, bytes, print, print2);
}

bool dump_rle(bytestream data,
              uint32_t bytes,
              byte_printer print,
              word_printer print2) {
  if (bytes & 1) {
    return false;
  }
  const uint16_t* colors = reinterpret_cast<const uint16_t*>(data);
  const uint32_t cbytes = bytes / 2;
  for (uint32_t pos = 0; pos < cbytes;) {
    // First, check to see if this is unique, or dupe:
    uint16_t val = colors[pos];
    if (pos + 1 == bytes) {
      // Special case last unique word
      dumpRLECount(false, 1, print);
      print2(colors[pos]);
      break;
    }
    uint16_t nxt = colors[pos + 1];
    if (val == nxt) {
      // Scan forward to see how long the repeat goes
      uint32_t count = 1;
      while (pos + count < cbytes) {
        nxt = colors[pos + count];
        if (nxt != val) {
          break;
        } else {
          count++;
        }
      }
      // We've got the count, dump the sequence
      dumpRLECount(true, count, print);
      print2(colors[pos]);
      pos += count;
    } else {
      // Scan forward to see how long the uniqueness goes
      uint32_t count = 1;
      val = nxt;
      while (pos + count < cbytes) {
        nxt = colors[pos + count + 1];
        if (nxt == val) {
          break;
        }
        count++;
        val = nxt;
      }
      dumpRLECount(false, count, print);
      while (count--) {
        print2(colors[pos++]);
      }
    }
  }
  return true;
}
