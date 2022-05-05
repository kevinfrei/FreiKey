#include "tetrisboard.h"
#include "enumhelpers.h"

namespace tetris {

constexpr uint32_t msPerFrame = 50; // Try to render at 20 FPS, yeah?

uint16_t getColor(uint8_t);

constexpr bool validPiece(PieceName pn) {
  return pn != PieceName::NumElems && pn != PieceName::Empty;
}

uint16_t getColor(PieceName pn) {
  return getColor(validPiece(pn) ? (value_cast(pn) + 1) : 0);
}

// Stupid splash screen
struct LetterLoc {
  char letter;
  uint16_t x, y;
};
constexpr std::array<LetterLoc, 6> tetris{{{'T', 15, 40},
                                           {'E', 50, 55},
                                           {'T', 85, 70},
                                           {'R', 120, 85},
                                           {'I', 165, 100},
                                           {'S', 190, 115}}};

const enum_array<PieceName, std::array<std::array<int8_t, 6>, 4>> pieces{
  {PieceName::I,
   {{{0, -2, 0, -1, 0, 1},
     {2, 0, 1, 0, -1, 0},
     {0, -2, 0, -1, 0, 1},
     {2, 0, 1, 0, -1, 0}}}},
  {PieceName::L,
   {{{0, -1, 0, 1, 1, 1},
     {1, 0, -1, 0, -1, 1},
     {0, 1, 0, -1, -1, -1},
     {-1, 0, 1, 0, 1, -1}}}},
  {PieceName::J,
   {{{0, -1, 0, 1, -1, 1},
     {1, 0, -1, 0, -1, -1},
     {0, 1, 0, -1, 1, -1},
     {-1, 0, 1, 0, 1, 1}}}},
  {PieceName::O,
   {{{0, 1, 1, 0, 1, 1},
     {0, 1, 1, 0, 1, 1},
     {0, 1, 1, 0, 1, 1},
     {0, 1, 1, 0, 1, 1}}}},
  {PieceName::T,
   {{{0, -1, 1, 0, -1, 0},
     {1, 0, 0, 1, 0, -1},
     {0, 1, -1, 0, 1, 0},
     {-1, 0, 0, -1, 0, 1}}}},
  {PieceName::S,
   {{{-1, 0, 0, -1, 1, -1},
     {0, 1, -1, 0, -1, -1},
     {-1, 0, 0, -1, 1, -1},
     {0, 1, -1, 0, -1, -1}}}},
  {PieceName::Z,
   {{{-1, -1, 0, -1, 1, 0},
     {1, -1, 1, 0, 0, 1},
     {-1, -1, 0, -1, 1, 0},
     {1, -1, 1, 0, 0, 1}}}}};

Board::Board(Adafruit_GFX& dsp, uint8_t w, uint8_t h)
  : display(dsp),
    PieceWidth(w),
    PieceHeight(h),
    score(0),
    nextPiece(PieceName::Empty) {
  clearBoard();
}

void Board::addScore(uint8_t v) {
  score += v;
}

PieceName Board::getSpot(uint8_t x, uint8_t y) {
  return board[y * WIDTH + x];
}

void Board::setSpot(uint8_t x, uint8_t y, PieceName piece) {
  board[y * WIDTH + x] = piece;
}

void Board::clrSpot(uint8_t x, uint8_t y) {
  board[y * WIDTH + x] = PieceName::Empty;
}

void Board::newPiece() {
  uint8_t data = analogRead(A6) ^ micros();
  curPiece = nextPiece;
  nextPiece = enum_cast<PieceName>(data % numPieces);
  x = WIDTH / 2;
  y = TOP_BUFFER / 2;
  rot = 0;
}

bool Board::checkLoc(int8_t xx, int8_t yy) {
  if (xx < 0 || yy < 0 || xx >= WIDTH || yy >= HEIGHT)
    return true;
  return validPiece(getSpot(xx, yy));
}

bool Board::intersects() {
  // Check to see if the piece at the current position hits the board
  if (checkLoc(x, y)) {
    Serial.printf("%d %d hit\n", x, y);
    return true;
  }
  auto& loc = pieces[curPiece][rot];
  for (int8_t i = 0; i < numLocs; i += 2) {
    if (checkLoc(x + loc[i], y + loc[i + 1]))
      return true;
  }
  return false;
}

void Board::placePiece() {
  setSpot(x, y, curPiece);
  auto& loc = pieces[curPiece][rot];
  for (uint8_t i = 0; i < 6; i += 2) {
    setSpot(x + loc[i], y + loc[i + 1], curPiece);
  }
}

void Board::removeLines() {
  // remove complete lines add to score
  int rows = 0;
  for (int i = 23; rows < 4 && i >= 0; i--) {
    bool all = true;
    for (int j = 0; all && j < 10; j++) {
      all = checkLoc(j, i);
    }
    if (all) {
      rows++;
      for (int k = i; k > 0; k--) {
        for (int l = 0; l < 10; l++) {
          PieceName prv = getSpot(l, k - 1);
          setSpot(l, k, prv);
        }
      }
      // And now check the same line
      i++;
    }
  }
  addScore((1 << rows) - 1);
  dropSpeed = dropSpeed * 99 / 100;
}

bool Board::gameOver() {
  // Check to see if there are any hits above the top of the board
  for (int8_t x = 0; x < WIDTH; x++) {
    for (int8_t y = 0; y < TOP_BUFFER; y++) {
      if (checkLoc(x, y))
        return true;
    }
  }
  return false;
}

void Board::endGame() {
  // TODO: Stop the game, check for high scores, stop, whatever else
  curPiece = PieceName::Empty;
}

void Board::clearBoard() {
  for (int x = 0; x < WIDTH; x++) {
    for (int y = 0; y < HEIGHT; y++) {
      clrSpot(x, y);
    }
  }
}

bool Board::active() {
  return validPiece(curPiece);
}

void Board::splash() {
  display.fillScreen(Black);
  uint8_t v = 1;
  display.setTextSize(2);
  for (auto& loc : tetris) {
    char buf[2] = {loc.letter, 0};
    display.setTextColor(getColor(v++));
    display.setCursor(loc.x, loc.y);
    display.print(&buf[0]);
  }
  display.setTextSize(1);
  display.setTextColor(White);
  // display.display();
}

void Board::draw(uint32_t now) {
  if (!lastDraw || now - lastDraw > msPerFrame) {
    if (!lastDraw) {
      display.fillScreen(Black);
    }
    drawScore();
    drawNext();
    drawBoard();
    if (now - lastDropTime > dropSpeed) {
      down(now);
    }
    drawPiece(curPiece, rot, x, y);
    lastDraw = now;
    // display.display();
  }
}

void Board::drawPiece(PieceName piece, uint8_t rot, uint8_t xc, uint8_t yc) {
  auto& loc = pieces[piece][rot];
  drawDot(xc, yc, piece);
  for (uint8_t i = 0; i < numLocs; i += 2) {
    drawDot(xc + loc[i], yc + loc[i + 1], piece);
  }
}

void Board::drawDot(int8_t x, int8_t y, PieceName pieceNum) {
  display.fillRect(BOARD_LEFT_OFFSET + x * PieceWidth,
                   BOARD_TOP_OFFSET + y * PieceHeight,
                   PieceWidth,
                   PieceHeight,
                   getColor(pieceNum));
}

void Board::drawBoard() {
  // Board outline:
  display.drawFastVLine(BOARD_LEFT_OFFSET - 1,
                        TOP_BUFFER * PieceHeight + BOARD_TOP_OFFSET,
                        1 + (HEIGHT - TOP_BUFFER) * PieceHeight,
                        White);
  display.drawFastVLine(BOARD_LEFT_OFFSET + WIDTH * PieceWidth,
                        TOP_BUFFER * PieceHeight + BOARD_TOP_OFFSET,
                        1 + (HEIGHT - TOP_BUFFER) * PieceHeight,
                        White);
  display.drawFastHLine(BOARD_LEFT_OFFSET - 1,
                        BOARD_TOP_OFFSET + HEIGHT * PieceHeight,
                        WIDTH * PieceWidth + 2,
                        White);
  // Draw each of the spots that are set
  // TODO: Optimize this into larger rectangles
  for (int8_t x = 0; x < WIDTH; x++) {
    for (int8_t y = 0; y < HEIGHT; y++) {
      drawDot(x, y, getSpot(x, y));
    }
  }
}

void Board::drawNext() {
  if (validPiece(nextPiece) && lastDrawNextPiece != nextPiece) {
    display.setCursor(100, 40);
    int16_t xp, yp;
    uint16_t wp, hp;
    display.getTextBounds("Next:", 100, 40, &xp, &yp, &wp, &hp);
    display.print("Next:");
    xp = xp + wp + 20;
    yp = yp + hp - 10;
    if (lastDrawNextPiece != PieceName::Empty) {
      // Erase the old piece
      auto& pc = pieces[lastDrawNextPiece][0];
      display.fillRect(xp, yp, 10, 10, Black);
      for (size_t i = 0; i < 6; i += 2) {
        display.fillRect(xp + pc[i] * 10, yp + pc[i + 1] * 10, 10, 10, Black);
      }
    }
    auto& pc = pieces[nextPiece][0];
    display.fillRect(xp, yp, 10, 10, getColor(nextPiece));
    for (size_t i = 0; i < 6; i += 2) {
      display.fillRect(
        xp + pc[i] * 10, yp + pc[i + 1] * 10, 10, 10, getColor(nextPiece));
    }
    lastDrawNextPiece = nextPiece;
  }
}

void Board::drawScore() {
  if (score != lastDrawnScore) {
    display.setTextSize(1);
    display.setTextColor(White);
    int16_t xp, yp;
    uint16_t wp, hp;
    char buf[20] = {
      'S', 'c', 'o', 'r', 'e', ':', ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    itoa(score, &buf[7], 11);
    display.getTextBounds(buf, 100, 110, &xp, &yp, &wp, &hp);
    display.fillRect(xp - 5, yp - 5, wp + 10, hp + 10, Black);
    display.setCursor(100, 110);
    display.print(buf);
    lastDrawnScore = score;
  }
}

void Board::start(uint32_t now) {
  display.fillScreen(Black);
  clearBoard();
  uint8_t data = analogRead(A6) ^ micros();
  nextPiece = enum_cast<PieceName>((data >> 3) % numPieces);
  newPiece();
  lastDropTime = now;
  lastDraw = 0;
  lastDrawNextPiece = PieceName::Empty;
  totalRows = 0;
  dropSpeed = 1000;
  score = 0;
  lastDrawnScore = 0xFFFFFFFF;
  draw(now);
}

void Board::down(uint32_t now) {
  y++;
  if (intersects()) {
    y--;
    placePiece();
    removeLines();
    if (gameOver()) {
      endGame();
    } else {
      newPiece();
    }
  }
  lastDropTime = now;
}

void Board::left() {
  x--;
  if (intersects()) {
    x++;
  }
}

void Board::right() {
  x++;
  if (intersects()) {
    x--;
  }
}

void Board::rotCW() {
  rot = (rot + 1) & 3;
  if (intersects()) {
    rot = (rot - 1) & 3;
  }
}

void Board::rotCCW() {
  rot = (rot - 1) & 3;
  if (intersects()) {
    rot = (rot + 1) & 3;
  }
}

} // namespace tetris
