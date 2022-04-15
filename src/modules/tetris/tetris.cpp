#include "Adafruit_ST7789.h"
#include <cstring>

#include "tetris.h"
#include "usbenums.h"

namespace tetris {
enum class GameFlowState {
  FirstTime,
  JustStarting,
  NotPlaying,
  InProgress,
  Completed
};

GameFlowState gameState = GameFlowState::FirstTime;
Adafruit_ST7789* dsp = nullptr;

uint8_t xW, xO, yW, yO;
uint8_t xN, yN;

void calcDisplayValues() {
  uint16_t height = dsp->height();
  uint16_t width = dsp->width();
  yW = (height - 1) / 24;
  xW = (width - 1) / 10;
  yW = std::min(xW, yW);
  xW = yW;
  xO = std::min(10, (width - xW * 10) / 2);
  yO = std::min(10, height - yW * 24);
  // This is only going to work for a landscape oriented display:
  xN = xO * 5 + (xW * 23) / 2;
  yN = (yW * 5) / 2;
}

uint16_t getDispX(uint8_t x) {
  return xO + xW * x;
}

uint16_t getDispY(uint8_t y) {
  return yO + yW * y;
}

uint16_t getDispW() {
  return xW;
}

uint16_t getDispH() {
  return yW;
}

uint16_t getPrevX(uint8_t x) {
  return xN + xW * x;
}

uint16_t getPrevY(uint8_t y) {
  return yN + yW * y;
}

uint16_t getPrevW() {
  return xW * 3;
}

uint16_t getPrevH() {
  return yW * 4;
}

uint16_t getColor(uint8_t blk) {
  switch (blk) {
    case 0:
      return ST77XX_BLACK;
    case 1:
      return ST77XX_RED;
    case 2:
      return ST77XX_BLUE;
    case 3:
      return ST77XX_GREEN;
    case 4:
      return ST77XX_YELLOW;
    case 5:
      return ST77XX_CYAN;
    case 6:
      return ST77XX_MAGENTA;
    case 7:
      return ST77XX_ORANGE;
    default:
      return blk << 8 | blk;
  }
}

// 0,0 is implied, and things are offset by 1, as "0" is empty block
constexpr int8_t pieces[7][6] = {
  {-1, 0, 1, 0, 0, -1}, // T
  {-1, 1, 0, 1, 1, 0}, // S
  {-1, 0, 0, 1, 1, 1}, // Z
  {-1, 0, -1, 1, 0, 1}, // O
  {-1, -1, 0, -1, 0, 1}, // L
  {1, -1, 0, -1, 0, 1}, // J
  {0, -2, 0, -1, 0, 1}, // I
};

class Board {
  uint8_t blocks[10 * 24];
  static const uint8_t offboard = 0xFF;
  uint8_t& pos(uint8_t x, uint8_t y) {
    if (x >= 10 || y >= 24)
      return const_cast<uint8_t&>(offboard);
    return blocks[y * 10 + x];
  }
  uint8_t& pos(uint8_t loc, uint8_t pn, uint8_t x, uint8_t y, uint8_t r) {
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
  uint8_t cur(uint8_t v) {
    return v & 0xF;
  }
  uint8_t nxt(uint8_t v) {
    return v >> 4;
  }
  uint8_t both(uint8_t c, uint8_t n) {
    return c | (n << 4);
  }
  // This should update the block array, but without rendering anything
  void drawBlock(uint8_t x, uint8_t y, uint8_t bn) {
    uint8_t& blk = pos(x, y);
    blk = both(cur(blk), nxt(bn));
  }

 public:
  void reset() {
    std::memset(blocks, 0, sizeof(blocks));
  }
  // Draw the piece at the given location,
  // returning true if it can be drawn there
  bool placePiece(uint8_t pn, uint8_t x, uint8_t y, uint8_t r) {
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
  void removePiece(uint8_t bn, uint8_t x, uint8_t y, uint8_t r) {
    uint8_t& p0 = pos(x, y);
    p0 = both(cur(p0), 0);
    uint8_t& p1 = pos(0, bn, x, y, r);
    p1 = both(cur(p1), 0);
    uint8_t& p2 = pos(1, bn, x, y, r);
    p2 = both(cur(p2), 0);
    uint8_t& p3 = pos(2, bn, x, y, r);
    p3 = both(cur(p3), 0);
  }
  // Draw the "preview" of the next piece to drop
  void drawNext(uint8_t bn) {
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
  void refresh() {
    // Walk the board and actually display any changes,
    // then clear the board of changes
    for (uint8_t x = 0; x < 10; x++) {
      for (uint8_t y = 0; y < 24; y++) {
        uint8_t& val = pos(x, y);
        uint8_t before = cur(val);
        uint8_t after = nxt(val);
        if (before != after) {
          dsp->fillRect(
            getDispX(x), getDispY(y), getDispW(), getDispH(), getColor(after));
          val = both(after, after);
        }
      }
    }
  }
};

class GameState {
  uint8_t curPiece;
  uint8_t nextPiece;
  uint8_t cx, cy, cr;
  uint32_t score;
  uint32_t level;
  Board board;

 public:
  void reset() {
    level = 0;
    score = 0;
  }
  void drawFullBoard() {
    dsp->fillScreen(ST77XX_BLACK);
    //
  }
};

void Initialize() {
  // Don't think I need anything here...
  gameState = GameFlowState::FirstTime;
}

void Begin(Adafruit_ST7789* tft) {
  gameState = GameFlowState::JustStarting;
  dsp = tft;
  calcDisplayValues();
}

void KeyDown(Keystroke k) {
  switch (gameState) {
    case GameFlowState::FirstTime:
      break;
    case GameFlowState::NotPlaying:
      break;
    case GameFlowState::JustStarting:
      break;
    case GameFlowState::InProgress:
      break;
    case GameFlowState::Completed:
      break;
  }
}

void Tick() {}

} // namespace tetris