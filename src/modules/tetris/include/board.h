#pragma once
#if !defined(TETRIS_BOARD_H)
#define TETRIS_BOARD_H

#include <array>
#include <cstdint>

namespace tetris {

class Board {
  static const uint8_t offboard = 0xFF;
  std::array<uint8_t, 10 * 24> blocks;
  uint8_t& pos(uint8_t x, uint8_t y);
  uint8_t& pos(uint8_t loc, uint8_t pn, uint8_t x, uint8_t y, uint8_t r);
  uint8_t cur(uint8_t v);
  uint8_t nxt(uint8_t v);
  uint8_t both(uint8_t c, uint8_t n);
  // This should update the block array, but without rendering anything
  void drawBlock(uint8_t x, uint8_t y, uint8_t bn);

 public:
  Board();
  void reset();
  // Draw the piece at the given location,
  // returning true if it can be drawn there
  bool placePiece(uint8_t pn, uint8_t x, uint8_t y, uint8_t r);
  // Delete the piece drawn at the given location
  // Draw the piece at the given location,
  // returning true if it can be drawn there
  void removePiece(uint8_t bn, uint8_t x, uint8_t y, uint8_t r);
  void render();
#if !defined(STANDALONE)
  // Draw the "preview" of the next piece to drop
  void drawNext(uint8_t bn);
#else
  void dump();
#endif
};

} // namespace tetris

#endif
