#include "board.h"

namespace tetris {

Board::Board(Adafruit_GFX& dsp, uint8_t w, uint8_t h)
  : display(dsp), PieceWidth(w), PieceHeight(h) {}

void Board::addScore(uint8_t v) {
  score += v;
}

bool Board::getSpot(uint8_t x, uint8_t y) {
  return board[y * WIDTH + x];
}

void Board::setSpot(uint8_t x, uint8_t y) {
  board[y * WIDTH + x] = true;
}

void Board::clrSpot(uint8_t x, uint8_t y) {
  board[y * WIDTH + x] = false;
}

void Board::drawDot(int8_t x, int8_t y, bool set, int16_t xo, int16_t yo) {
  display.drawRect(xo + x * PieceWidth,
                   yo + y * PieceHeight,
                   PieceWidth,
                   PieceHeight,
                   set ? White : Black);
}

void Board::drawBoard() {
  // Board outline:
  display.drawFastVLine(0,
                        TOP_BUFFER * PieceHeight,
                        1 + (HEIGHT - TOP_BUFFER) * PieceHeight,
                        White);
  display.drawFastVLine(1 + WIDTH * PieceWidth,
                        TOP_BUFFER * PieceHeight,
                        1 + (HEIGHT - TOP_BUFFER) * PieceHeight,
                        White);
  display.drawFastHLine(1, HEIGHT * PieceHeight, WIDTH * PieceWidth, White);
  // Draw each of the spots that are set
  for (int8_t x = 0; x < WIDTH; x++) {
    for (int8_t y = 0; y < HEIGHT; y++) {
      drawDot(x, y, getSpot(x, y));
    }
  }
}

void Board::drawNext() {
  if (nextPiece >= 0) {
    display.setCursor(4, 76);
    display.print("Next");
    drawPiece(nextPiece, 0, 15, 92);
  }
}

void Board::drawScore() {
  display.setCursor(1, 100);
  display.println("Score");
  // Center the score:
  int offset = 1;
  if (score > 9)
    offset++;
  if (score > 99)
    offset++;
  if (score > 999)
    offset++;
  if (score > 9999)
    offset++;
  display.setCursor(16 - 3 * offset, 112);
  display.print(score);
}

void Board::newPiece() {
  uint8_t data = analogRead(A6) ^ micros();
  curPiece = nextPiece;
  nextPiece = data % numPieces;
  x = WIDTH / 2;
  y = TOP_BUFFER / 2;
  rot = 0;
}

bool Board::checkLoc(int8_t xx, int8_t yy) {
  if (xx < 0 || yy < 0 || xx >= WIDTH || yy >= HEIGHT)
    return true;
  return getSpot(xx, yy);
}

bool Board::intersects() {
  // Check to see if the piece at the current position hits the board
  if (checkLoc(x, y)) {
    Serial.printf("%d %d hit\n", x, y);
    return true;
  }
  const int8_t* loc = &pieces[curPiece][rot * numLocs];
  for (int8_t i = 0; i < numLocs; i += 2) {
    if (checkLoc(x + loc[i], y + loc[i + 1]))
      return true;
  }
  return false;
}

void Board::placePiece() {
  setSpot(x, y);
  const int8_t* loc = &pieces[curPiece][rot * numLocs];
  for (uint8_t i = 0; i < 6; i += 2) {
    setSpot(x + loc[i], y + loc[i + 1]);
  }
}

void Board::removeLines() {
  // remove complete lines add to score
  int rows = 0;
  for (int i = 23; rows < 4 && i >= 0; i--) {
    bool all = true;
    for (int j = 0; all && j < 10; j++) {
      all = getSpot(j, i);
    }
    if (all) {
      rows++;
      for (int k = i; k > 0; k--) {
        for (int l = 0; l < 10; l++) {
          if (getSpot(l, k - 1))
            setSpot(l, k);
          else
            clrSpot(l, k);
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
    for (int8_t y = 0; y < 4; y++) {
      if (getSpot(x, y))
        return true;
    }
  }
  return false;
}

void Board::endGame() {
  // TODO: Stop the game, check for high scores, stop, whatever else
  curPiece = -1;
}

void Board::clearBoard() {
  for (int x = 0; x < WIDTH; x++) {
    for (int y = 0; y < HEIGHT; y++) {
      clrSpot(x, y);
    }
  }
}

bool Board::active() {
  return curPiece >= 0;
}

void Board::splash() {
  display.setTextSize(3);
  display.setTextColor(White);
  display.fillScreen(Black);
  for (auto& loc : tetris) {
    char buf[2] = {loc.letter, 0};
    display.setCursor(loc.x, loc.y);
    display.print(&buf[0]);
  }
  // display.display();
}

void Board::draw(uint32_t now) {
  display.fillScreen(Black);
  display.setTextSize(1);
  display.setTextColor(White);
  drawBoard();
  drawNext();
  drawScore();
  if (now > lastDropTime + dropSpeed) {
    down(now);
  }
  drawPiece(curPiece, rot, 1 + x * 3, y * 3);
  // display.display();
}

void Board::drawPiece(uint8_t piece, uint8_t rot, uint8_t xo, uint8_t yo) {
  const int8_t* loc = &pieces[piece][rot * numLocs];
  drawDot(0, 0, true, xo, yo);
  for (uint8_t i = 0; i < numLocs; i += 2) {
    drawDot(loc[i], loc[i + 1], true, xo, yo);
  }
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

void Board::start(uint32_t now) {
  clearBoard();
  uint8_t data = analogRead(A6) ^ micros();
  nextPiece = (data >> 3) % numPieces;
  newPiece();
  lastDropTime = now;
  totalRows = 0;
  dropSpeed = 1000;
  score = 0;
}

} // namespace tetris
