#include <algorithm>
#include <vector>

#include "Adafruit_SPITFT.h"
#include "display.h"
#include "enumhelpers.h"
#include "enumtypes.h"
#include "menu.h"
#include "usbenums.h"

namespace menu {

enum_array<KeyboardMode, const char*> names{
  {KeyboardMode::Normal, "Keyboard"},
  {KeyboardMode::Menu, "Menu"},
  {KeyboardMode::Calculator, "Calculator"},
  {KeyboardMode::Tetris, "Tetris (WIP)"},
  {KeyboardMode::Snake, "Snake (NYI)"},
  {KeyboardMode::MediaBrowse, "Media Browser (NYI)"},
  {KeyboardMode::Apple2, "Apple //e (WIP)"},
  {KeyboardMode::Diagnostics, "Diagnostics"}};

namespace impl {

std::vector<KeyboardMode> modes;
std::size_t curSel;

uint16_t mw, mh;
uint8_t fontSize;
int8_t yoffset;

void CalcMenuDimension() {
  Adafruit_SPITFT* d = disp::raw();
  uint16_t w = d->width();
  uint16_t h = d->height();
  size_t elems = modes.size();
  mw = 0;
  mh = 0;
  fontSize = 0;
  yoffset = 0;
  uint16_t lh = 1;
  uint16_t lw = 1;
  do {
    fontSize++;
    mw = lw;
    mh = lh;
    d->setTextSize(fontSize);
    uint16_t maxw = 0, maxh = 0;
    for (auto& m : modes) {
      // Calculate the size for the element selected
      int16_t xp, yp;
      d->getTextBounds(names[m], 0, 0, &xp, &yp, &lh, &lw);
      yoffset = -yp;
      maxw = std::max((int)maxw, lw - xp);
      maxh = std::max((int)maxh, lh - yp);
    }
    lw = maxw;
    lh = maxh;
  } while (lh * elems < h && lw < w);
  fontSize--;
}

void DrawScreen(std::size_t newSel = 0xFFFFFF) {
  Adafruit_SPITFT* d = disp::raw();
  uint16_t vPad = (d->height() - modes.size() * mh) / modes.size();
  int16_t startY = vPad / 3;
  if (newSel == 0xFFFFFF) {
    d->fillScreen(0);
  }
  d->setTextSize(fontSize);
  uint8_t border = 3;
  uint16_t highlight = 0xFFF0;
  for (std::size_t c = 0; c < modes.size(); c++) {
    auto m = modes[c];
    int16_t xp, yp;
    uint16_t lh, lw;
    d->getTextBounds(names[m], 0, startY + yoffset, &xp, &yp, &lw, &lh);
    d->setCursor((d->width() - lw) / 2, startY + yoffset);
    if (c == newSel || c == curSel) {
      d->getTextBounds(
        names[m], (d->width() - lw) / 2, startY + yoffset, &xp, &yp, &lw, &lh);
      d->fillRoundRect(xp - border,
                       yp - border,
                       lw + border * 2,
                       lh + border * 2,
                       border,
                       (c == newSel || newSel == 0xFFFFFF) ? highlight : 0);
      d->setTextColor(
        (c == newSel || (newSel == 0xFFFFff && c == curSel)) ? 0 : 0xFFFF);
    } else {
      d->setTextColor(0xFFFF);
    }
    if (newSel == 0xFFFFFF || c == newSel || c == curSel) {
      d->print(names[m]);
    }
    // Draw a box around the current selection
    startY += mh + vPad;
  }
  if (newSel != 0xFFFFFF) {
    curSel = newSel;
  }
}

// This is the final "We've set up the menu, please display it" function
void SelectHelper() {
  // TODO: Continue here
  curSel = 0;
  CalcMenuDimension();
  DrawScreen();
}

} // namespace impl

KeyboardMode Handler(Keystroke ks, Modifiers mods, bool pressed, uint32_t now) {
  if (pressed) {
    switch (ks) {
      case Keystroke::A:
      case Keystroke::J:
      case Keystroke::Left:
      case Keystroke::Home:
        impl::DrawScreen(0);
        break;
      case Keystroke::D:
      case Keystroke::L:
      case Keystroke::Right:
      case Keystroke::End:
        impl::DrawScreen(impl::modes.size() - 1);
        break;
      case Keystroke::PageUp:
      case Keystroke::Up:
      case Keystroke::I:
      case Keystroke::W:
        impl::DrawScreen((impl::curSel + impl::modes.size() - 1) %
                         impl::modes.size());
        break;
      case Keystroke::PageDown:
      case Keystroke::Down:
      case Keystroke::K:
      case Keystroke::S:
        impl::DrawScreen((impl::curSel + 1) % impl::modes.size());
        break;
      case Keystroke::Esc:
        return KeyboardMode::Normal;
      case Keystroke::Enter:
      case Keystroke::Space:
        return impl::modes[impl::curSel];
      default:
        return KeyboardMode::Menu;
    }
  }
  return KeyboardMode::Menu;
}

} // namespace menu