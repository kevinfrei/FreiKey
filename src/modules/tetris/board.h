#pragma once
#if !defined(TETRIS_BOARD_H)
#define TETRIS_BOARD_H

#include "Adafruit_GFX.h"

#include <cstdint>
namespace tetris {

// Splash screen
struct LetterLoc {
  char letter;
  uint8_t x, y;
};
constexpr LetterLoc tetris[6] = {{'T', 0, 0},
                                 {'e', 3, 19},
                                 {'t', 6, 42},
                                 {'r', 11, 63},
                                 {'i', 12, 84},
                                 {'s', 14, 105}};
constexpr int8_t pieces[7][24] =
  // clang-format off
{{ // I
   0, -2,  0, -1,  0,  1,
   2,  0,  1,  0, -1,  0,
   0,  2,  0,  1,  0, -1,
  -2,  0, -1,  0,  1,  0
}, { // L
   0, -1,  0,  1,  1,  1,
   1,  0, -1,  0, -1,  1,
   0,  1,  0, -1, -1, -1,
  -1,  0,  1,  0,  1, -1
}, { // J
   0, -1,  0,  1, -1,  1,
   1,  0, -1,  0, -1, -1,
   0,  1,  0, -1,  1, -1,
  -1,  0,  1,  0,  1,  1
}, { // O
   0,  1,  1,  0,  1,  1,
  -1,  0,  0,  1, -1,  1,
   0, -1, -1,  0, -1, -1,
   1,  0,  0, -1,  1, -1
}, { // T
   0, -1,  1,  0, -1,  0,
   1,  0,  0,  1,  0, -1,
   0,  1, -1,  0,  1,  0,
  -1,  0,  0, -1,  0,  1
}, { // S
  -1,  0,  0, -1,  1, -1, 
   0,  1, -1,  0, -1, -1,
   1,  0,  0,  1, -1,  1,
   0, -1,  1,  0,  1,  1
}, { // Z
  -1, -1,  0, -1,  1,  0,
   1, -1,  1,  0,  0,  1,
   1,  1,  0,  1, -1,  0,
  -1,  1, -1,  0,  0, -1
}};
// clang-format on
class Board {
  // Constants
  static constexpr uint16_t White = 0xFFFF;
  static constexpr uint16_t Black = 0;

  static constexpr uint8_t numPieces = 7;
  static constexpr uint8_t numLocs = 6;

  static constexpr int8_t WIDTH = 10;
  static constexpr int8_t HEIGHT = 24;
  static constexpr int8_t TOP_BUFFER = 4;

  Adafruit_GFX& display;
  uint16_t PieceWidth;
  uint16_t PieceHeight;

  // data
  bool board[WIDTH * HEIGHT];
  uint32_t score;
  int8_t curPiece, nextPiece;
  uint8_t rot, x, y;
  uint32_t lastDropTime;
  uint32_t dropSpeed;
  uint16_t totalRows;

  void addScore(uint8_t v);
  bool getSpot(uint8_t x, uint8_t y);
  void setSpot(uint8_t x, uint8_t y);
  void clrSpot(uint8_t x, uint8_t y);
  void drawDot(int8_t x, int8_t y, bool set, int16_t xo = 1, int16_t yo = 0);
  void drawBoard();
  void drawNext();
  void drawScore();
  void newPiece();
  bool checkLoc(int8_t xx, int8_t yy);
  bool intersects();
  void placePiece();
  void removeLines();
  bool gameOver();
  void endGame();
  void clearBoard();

 public:
  Board(Adafruit_GFX& dsp, uint8_t w, uint8_t h);
  bool active();
  void splash();
  void draw(uint32_t now);
  void drawPiece(uint8_t piece, uint8_t rot, uint8_t xo, uint8_t yo);
  void down(uint32_t now);
  void left();
  void right();
  void rotCW();
  void rotCCW();
  void start(uint32_t now);
};

} // namespace tetris

#endif
