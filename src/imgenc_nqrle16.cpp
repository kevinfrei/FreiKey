#include <stdint.h>
#include <stdio.h>

/*
This should spit out the encoded source array
*/
void dumpCount(bool repeat, uint32_t count, void (*print)(uint8_t byte)) {
  if (count == 0 || count > UINT32_MAX / 2) {
    fprintf(stderr, "Derp\n");
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

uint16_t getVal(const uint8_t* data, uint32_t pos) {
  return (data[pos] << 8) | data[pos + 1];
}

// it should work better for stuff that has strings of unique stuff along with
// strings of repeated stuff
bool encode_nqrle16(const uint8_t* data,
                       uint32_t bytes,
                       void (*print)(uint8_t byte)) {
  if (bytes & 1) {
    return false;
  }
  for (uint32_t pos = 0; pos < bytes;) {
    // First, check to see if this is unique, or dupe:
    uint16_t val = getVal(data, pos);
    if (pos + 2 == bytes) {
      // Special case last unique word
      dumpCount(false, 1, print);
      print(data[pos++]);
      print(data[pos++]);
      break;
    }
    uint16_t nxt = getVal(data, pos + 2);
    if (val == nxt) {
      // Scan forward to see how long the repeat goes
      uint32_t count = 2;
      while (pos + count * 2 < bytes) {
        nxt = getVal(data, pos + 2 * count);
        if (nxt != val) {
          break;
        } else {
          count++;
        }
      }
      // We've got the count, dump the sequence
      dumpCount(true, count, print);
      print(data[pos]);
      print(data[pos + 1]);
      pos += count * 2;
    } else {
      // Scan forward to see how long the uniqueness goes
      uint32_t count = 1;
      val = nxt;
      while (pos + count * 2 < bytes) {
        nxt = getVal(data, pos + 2 * count + 2);
        if (nxt == val) {
          break;
        }
        count++;
        val = nxt;
      }
      dumpCount(false, count, print);
      while (count--) {
        print(data[pos++]);
        print(data[pos++]);
      }
    }
  }
  return true;
}
