#pragma once
#if !defined(TETRIS_BOARD_H)
#define TETRIS_BOARD_H

#include "Adafruit_GFX.h"

#include "enumhelpers.h"
#include <cstdint>

namespace tetris {

enum class PieceName : uint8_t { I, L, J, O, T, S, Z, NumElems, Empty };

class Board {
  // Constants
  static constexpr uint16_t White = 0xFFFF;
  static constexpr uint16_t Black = 0;

  static constexpr uint8_t numPieces = value_cast(PieceName::NumElems);
  static constexpr uint8_t numLocs = 6;

  static constexpr int8_t WIDTH = 10;
  static constexpr int8_t HEIGHT = 24;
  static constexpr int8_t TOP_BUFFER = 4;
  static constexpr uint8_t BOARD_LEFT_OFFSET = 20;
  static constexpr uint8_t BOARD_TOP_OFFSET = 0;

  Adafruit_GFX& display;
  uint16_t PieceWidth;
  uint16_t PieceHeight;

  // data
  PieceName board[WIDTH * HEIGHT];
  uint32_t score;
  uint32_t lastDrawnScore;

  PieceName curPiece, nextPiece;
  PieceName lastDrawNextPiece;

  uint8_t rot, x, y;
  uint32_t lastDropTime;
  uint32_t lastDraw;
  uint32_t dropSpeed;
  uint16_t totalRows;

  void addScore(uint8_t v);
  PieceName getSpot(uint8_t x, uint8_t y);
  void setSpot(uint8_t x, uint8_t y, PieceName piece);
  void clrSpot(uint8_t x, uint8_t y);
  void drawDot(
    int8_t x, int8_t y, PieceName piece);
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
  void drawPiece(PieceName piece, uint8_t rot, uint8_t xc, uint8_t yc);
  void down(uint32_t now);
  void left();
  void right();
  void rotCW();
  void rotCCW();
  void start(uint32_t now);
};

} // namespace tetris

#endif
