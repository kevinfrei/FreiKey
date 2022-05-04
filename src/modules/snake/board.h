#pragma once
#if !defined(TETRIS_BOARD_H)
#define TETRIS_BOARD_H

#include "Adafruit_GFX.h"

#include "enumhelpers.h"
#include <array>
#include <cstdint>

namespace snake {

template <std::size_t WIDTH, std::size_t HEIGHT>
class Board {
  static constexpr uint16_t BK = 0x0000;
  static constexpr uint16_t LG = 0x07E0;
  static constexpr uint16_t MG = 0x0400;
  static constexpr uint16_t DG = 0x0200;
  static constexpr uint16_t LR = 0xF800;
  static constexpr uint16_t MR = 0x8000;
  static constexpr uint16_t DR = 0x4000;
  static constexpr uint16_t BL = 0x001F;
  using Bitmap = std::array<uint16_t, 7 * 7>;
  // clang-format off
  static constexpr Bitmap NS {
    BK, DG, MG, LG, MG, DG, BK,
    BK, DG, MG, LG, MG, DG, BK,
    BK, DG, MG, LG, MG, DG, BK,
    BK, DG, MG, LG, MG, DG, BK,
    BK, DG, MG, LG, MG, DG, BK,
    BK, DG, MG, LG, MG, DG, BK,
    BK, DG, MG, LG, MG, DG, BK,
  };
  static constexpr Bitmap EW {
    BK, BK, BK, BK, BK, BK, BK,
    DG, DG, DG, DG, DG, DG, DG,
    MG, MG, MG, MG, MG, MG, MG,
    LG, LG, LG, LG, LG, LG, LG,
    MG, MG, MG, MG, MG, MG, MG,
    DG, DG, DG, DG, DG, DG, DG,
    BK, BK, BK, BK, BK, BK, BK,
  };
  static constexpr Bitmap NE {
    BK, DG, MG, LG, MG, DG, BK,
    BK, DG, MG, LG, MG, DG, DG,
    BK, DG, MG, LG, MG, MG, MG,
    BK, DG, MG, LG, LG, LG, LG,
    BK, DG, MG, MG, MG, MG, MG,
    BK, DG, DG, DG, DG, DG, DG,
    BK, BK, BK, BK, BK, BK, BK,
  };
  static constexpr Bitmap SE {
    BK, BK, BK, BK, BK, BK, BK,
    BK, DG, DG, DG, DG, DG, DG,
    BK, DG, MG, MG, MG, MG, MG,
    BK, DG, MG, LG, LG, LG, LG,
    BK, DG, MG, LG, MG, MG, MG,
    BK, DG, MG, LG, MG, DG, DG,
    BK, DG, MG, LG, MG, DG, BK,
  };
  static constexpr Bitmap NW {
    BK, DG, MG, LG, MG, DG, BK,
    DG, DG, MG, LG, MG, DG, BK,
    MG, MG, MG, LG, MG, DG, BK,
    LG, LG, LG, LG, MG, DG, BK,
    MG, MG, MG, MG, MG, DG, BK,
    DG, DG, DG, DG, DG, DG, BK,
    BK, BK, BK, BK, BK, BK, BK,
  };
  static constexpr Bitmap SW {
    BK, BK, BK, BK, BK, BK, BK,
    DG, DG, DG, DG, DG, DG, BK,
    MG, MG, MG, MG, MG, DG, BK,
    LG, LG, LG, LG, MG, DG, BK,
    MG, MG, MG, LG, MG, DG, BK,
    DG, DG, MG, LG, MG, DG, BK,
    BK, DG, MG, LG, MG, DG, BK,
  };
  static constexpr Bitmap NT {
    BK, DG, MG, LG, MG, DG, BK,
    BK, DG, MG, LG, MG, DG, BK,
    BK, DG, MG, LG, MG, DG, BK,
    BK, DG, MG, LG, MG, DG, BK,
    BK, DG, MG, LG, MG, DG, BK,
    BK, BK, DG, MG, DG, BK, BK,
    BK, BK, BK, DG, BK, BK, BK,
  };
  static constexpr Bitmap ST {
    BK, BK, BK, DG, BK, BK, BK,
    BK, BK, DG, MG, DG, BK, BK,
    BK, DG, MG, LG, MG, DG, BK,
    BK, DG, MG, LG, MG, DG, BK,
    BK, DG, MG, LG, MG, DG, BK,
    BK, DG, MG, LG, MG, DG, BK,
    BK, DG, MG, LG, MG, DG, BK,
  };
  static constexpr Bitmap ET {
    BK, BK, BK, BK, BK, BK, BK,
    BK, BK, DG, DG, DG, DG, DG,
    BK, DG, MG, MG, MG, MG, MG,
    DG, MG, LG, LG, LG, LG, LG,
    BK, DG, MG, MG, MG, MG, MG,
    BK, BK, DG, DG, DG, DG, DG,
    BK, BK, BK, BK, BK, BK, BK,
  };
  static constexpr Bitmap WT {
    BK, BK, BK, BK, BK, BK, BK,
    DG, DG, DG, DG, DG, BK, BK,
    MG, MG, MG, MG, MG, DG, BK,
    LG, LG, LG, LG, LG, MG, DG,
    MG, MG, MG, MG, MG, DG, BK,
    DG, DG, DG, DG, DG, BK, BK,
    BK, BK, BK, BK, BK, BK, BK,
  };
  static constexpr Bitmap SH {
    BK, DG, MG, LG, MG, DG, BK,
    BK, DG, MG, LG, MG, DG, BK,
    BK, DG, MG, LG, MG, DG, BK,
    BK, DG, MG, LG, MG, DG, BK,
    BK, MG, BL, MR, BL, MG, BK,
    BK, BK, BK, MR, BK, BK, BK,
    BK, BK, MR, BK, MR, BK, BK,
  };
  static constexpr Bitmap NH {
    BK, BK, MR, BK, MR, BK, BK,
    BK, BK, BK, MR, BK, BK, BK,
    BK, MG, BL, MR, BL, MG, BK,
    BK, DG, MG, LG, MG, DG, BK,
    BK, DG, MG, LG, MG, DG, BK,
    BK, DG, MG, LG, MG, DG, BK,
    BK, DG, MG, LG, MG, DG, BK,
  };
  static constexpr Bitmap WH {
    BK, BK, BK, BK, BK, BK, BK,
    BK, BK, MG, DG, DG, DG, DG,
    MR, BK, BL, MG, MG, MG, MG,
    BK, MR, MG, LG, LG, LG, LG,
    MR, BK, BL, MG, MG, MG, MG,
    BK, BK, MG, DG, DG, DG, DG,
    BK, BK, BK, BK, BK, BK, BK,
  };
  static constexpr Bitmap EH {
    BK, BK, BK, BK, BK, BK, BK,
    DG, DG, DG, DG, MG, BK, BK,
    MG, MG, MG, MG, BL, BK, MR,
    LG, LG, LG, LG, MG, MR, BK,
    MG, MG, MG, MG, BL, BK, MR,
    DG, DG, DG, DG, MG, BK, BK,
    BK, BK, BK, BK, BK, BK, BK,
  };
  static constexpr Bitmap Apple {
    BK, BK, BK, MG, MG, BK, BK,
    BK, BK, DR, MG, DR, BK, BK,
    BK, DR, MR, LR, MR, DR, BK,
    BK, DR, LR, LR, LR, DR, BK,
    BK, DR, MR, LR, MR, DR, BK,
    BK, BK, DR, DR, DR, BK, BK,
    BK, BK, DR, BK, DR, BK, BK,
  };

  enum class Piece : uint8_t {
    Empty    = 0,
    FromN    = 0b0000001,
    FromE    = 0b0000011,
    FromS    = 0b0000101,
    FromW    = 0b0000111,
    FromMask = 0b0000111,
    HasFrom  = 0b0000001,
    ToN      = 0b0001000,
    ToE      = 0b0011000,
    ToS      = 0b0101000,
    ToW      = 0b0111000,
    ToMask   = 0b0111000,
    HasTo    = 0b0001000,
    DirMask  = 0b0001001,
    Apple    = 0b1000000,
    Border   = 0b1110110,
    MASK     = 0b1111111 // Light up my enum mask helpers :)
  };
  // clang-format on
  enum class Dir : uint8_t { N = 0, E = 1, S = 2, W = 3 };
  static Dir FromDir(Piece p) {
    return enum_cast<Dir>(value_cast(p & Piece::FromMask) >> 1);
  }
  static Dir ToDir(Piece p) {
    return enum_cast<Dir>(value_cast(p & Piece::ToMask) >> 4);
  }
  static const Bitmap& BitmapForPiece(Piece p) {
    if (p == Piece::Apple) {
      return Apple;
    }
    if (p == Piece::Border || p == Piece::Empty) {
      return TODO;
    }
    if (p & Piece::ToMask != Piece::Empty &&
        p & Piece::FromMask != Piece::Empty) {
      // Not a head or tail
      Dir f = FromDir(p);
      Dir t = ToDir(p);
      switch (f) {
        case Dir::N:
          switch (t) {
            case Dir::N:
            case Dir::E:
              return NE;
            case Dir::S:
              return NS;
            case Dir::W:
              return NW;
          }
        case Dir::S:
          switch (t) {
            case Dir::N:
              return NS;
            case Dir::E:
              return SE;
            case Dir::S:
            case Dir::W:
              return SW;
          }
        case Dir::E:
          switch (t) {
            case Dir::N:
              return NE;
            case Dir::E:
            case Dir::S:
              return SE;
            case Dir::W:
              return EW;
          }
        case Dir::W:
          switch (t) {
            case Dir::N:
              return NW;
            case Dir::E:
              return EW;
            case Dir::S:
            case Dir::W:
              return SW;
          }
      }
    } else if (p & piece::ToMask) {
      // This is the tail
      switch (ToDir(p)) {
        case Dir::N:
          return NT;
        case Dir::E:
          return ET;
        case Dir::S:
          return ST;
        case Dir::W:
          return WT;
      }
    } else {
      // This is the head
      switch (FromDir(p)) {
        case Dir::N:
          return NH;
        case Dir::E:
          return EH;
        case Dir::S:
          return SH;
        case Dir::W:
          return WH;
      }
    }
  }
  std::array<Piece, (WIDTH + 2) * (HEIGHT * 2)> field;
  Adafruit_GFX& display;

  // data
  std::vector<uint16_t> board;

  uint32_t score;
  uint32_t lastDrawnScore;
  uint8_t snakeLength;
  Dir head;
  uint8_t headx, heady, tailx, taily;

  static void movePosition(Dir d, uint8_t& x, uint8_t& y) {
    switch (d) {
      case Dir::N:
        y--;
        break;
      case Dir::S:
        y++;
        break;
      case Dir::E:
        x++;
        break;
      case Dir::W:
        x--;
        break;
    }
  }

  void drawBoard();
  void moveHead(bool moveTail);
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

} // namespace snake

#endif
