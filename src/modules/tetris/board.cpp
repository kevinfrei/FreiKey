#include <array>
#include <cstdint>

#if defined(STANDALONE)
#include <iostream>
#else
#include "Adafruit_ST7789.h"
#endif

#include "include/board.h"
#include "include/tetris_details.h"

namespace tetris {

// 0,0 is implied, and things are offset by 1, as "0" is empty block
constexpr std::array<std::array<int8_t, 6>, 7> pieces{{
  {-1, 0, 1, 0, 0, -1}, // T
  {-1, 1, 0, 1, 1, 0}, // S
  {-1, 0, 0, 1, 1, 1}, // Z
  {-1, 0, -1, 1, 0, 1}, // O
  {-1, -1, 0, -1, 0, 1}, // L
  {1, -1, 0, -1, 0, 1}, // J
  {0, -2, 0, -1, 0, 1}, // I
}};

uint8_t const Board::offboard = 0xFF;

uint8_t& Board::pos(uint8_t x, uint8_t y) {
  if (x >= 10 || y >= 24)
    return const_cast<uint8_t&>(offboard);
  return blocks[y * 10 + x];
}

uint8_t& Board::pos(uint8_t loc, uint8_t pn, uint8_t x, uint8_t y, uint8_t r) {
  const int8_t* blkPos = &pieces[pn][0];
  switch (r) {
    default:
    case 0:
      return pos(x + blkPos[loc * 2], y + blkPos[loc * 2 + 1]);
    case 1:
      return pos(x + blkPos[loc * 2 + 1], y - blkPos[loc * 2]);
    case 2:
      return pos(x - blkPos[loc * 2], y - blkPos[loc * 2 + 1]);
    case 3:
      return pos(x - blkPos[loc * 2 + 1], y + blkPos[loc * 2]);
  }
}

uint8_t Board::cur(uint8_t v) {
  return v & 0xF;
}

uint8_t Board::nxt(uint8_t v) {
  return v >> 4;
}

uint8_t Board::both(uint8_t c, uint8_t n) {
  return c | (n << 4);
}

// This should update the block array, but without rendering anything
void Board::drawBlock(uint8_t x, uint8_t y, uint8_t bn) {
  uint8_t& blk = pos(x, y);
  blk = both(cur(blk), nxt(bn));
}

Board::Board() {
  blocks.fill(0);
}

void Board::reset() {
  blocks.fill(0);
}

// Draw the piece at the given location,
// returning true if it can be drawn there
bool Board::placePiece(uint8_t pn, uint8_t x, uint8_t y, uint8_t r) {
  uint8_t& p0 = pos(x, y);
  uint8_t& p1 = pos(0, pn, x, y, r);
  uint8_t& p2 = pos(1, pn, x, y, r);
  uint8_t& p3 = pos(2, pn, x, y, r);
  if (cur(p0) || cur(p1) || cur(p2) || cur(p3))
    return false;

  p0 = both(cur(p0), pn + 1);
  p1 = both(cur(p1), pn + 1);
  p2 = both(cur(p2), pn + 1);
  p3 = both(cur(p3), pn + 1);

  return true;
}

// Delete the piece drawn at the given location
// Draw the piece at the given location,
// returning true if it can be drawn there
void Board::removePiece(uint8_t bn, uint8_t x, uint8_t y, uint8_t r) {
  uint8_t& p0 = pos(x, y);
  p0 = both(cur(p0), 0);
  uint8_t& p1 = pos(0, bn, x, y, r);
  p1 = both(cur(p1), 0);
  uint8_t& p2 = pos(1, bn, x, y, r);
  p2 = both(cur(p2), 0);
  uint8_t& p3 = pos(2, bn, x, y, r);
  p3 = both(cur(p3), 0);
}

void Board::render() {
  // Walk the board and actually display any changes,
  // then clear the board of changes
  for (uint8_t x = 0; x < 10; x++) {
    for (uint8_t y = 0; y < 24; y++) {
      uint8_t& val = pos(x, y);
      uint8_t before = cur(val);
      uint8_t after = nxt(val);
      if (before != after) {
#if !defined(STANDALONE)
        dsp->fillRect(
          getDispX(x), getDispY(y), getDispW(), getDispH(), getColor(after));
#endif
        val = both(after, after);
      }
    }
  }
}

#if !defined(STANDALONE)

// Draw the "preview" of the next piece to drop
void Board::drawNext(uint8_t bn) {
  uint16_t h = getDispH();
  uint16_t w = getDispW();
  dsp->fillRect(
    getPrevX(-1), getPrevY(-2), getPrevW(), getPrevH(), ST77XX_BLACK);
  dsp->fillRect(getPrevX(0), getPrevY(0), w, h, getColor(bn));
  dsp->fillRect(
    getPrevX(pieces[bn][0]), getPrevY(pieces[bn][1]), w, h, getColor(bn));
  dsp->fillRect(
    getPrevX(pieces[bn][2]), getPrevY(pieces[bn][3]), w, h, getColor(bn));
  dsp->fillRect(
    getPrevX(pieces[bn][4]), getPrevY(pieces[bn][5]), w, h, getColor(bn));
}

#else

void Board::dump() {
  constexpr std::array<char, 16> syms{' ',
                                      'T',
                                      'S',
                                      'Z',
                                      'O',
                                      'L',
                                      'J',
                                      'I',
                                      '?',
                                      '?',
                                      '?',
                                      '?',
                                      '?',
                                      '?',
                                      '?',
                                      '?'};
  std::cout << "Current:        Next:" << std::endl;
  for (int8_t y = -1; y < 25; y++) {
    for (int8_t x = -1; x < 11; x++) {
      std::cout << syms[cur(pos(x, y))];
    }
    std::cout << " ";
    for (int8_t x = -1; x < 11; x++) {
      std::cout << syms[nxt(pos(x, y))];
    }
    std::cout << std::endl;
  }
}

#endif

} // namespace tetris

#if defined(STANDALONE)

int main(void) {
  std::cout << "Testing tetris" << std::endl;
  tetris::Board b;
  for (uint8_t pn = 0; pn < 7; pn++) {
    for (uint8_t rot = 0; rot < 4; rot++) {
      bool attempted = b.placePiece(pn, 5, 2, rot);
      if (!attempted) {
        std::cout << "placePiece " << static_cast<int>(pn) << ",t,2,"
                  << static_cast<int>(rot) << " failed" << std::endl;
      }
      b.render();
      b.removePiece(pn, 5, 2, rot);
      b.render();
    }
  }
  std::cout << "Tetris testing complete" << std::endl;
}

#endif