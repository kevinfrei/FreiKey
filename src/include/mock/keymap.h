#pragma once

#include "boardio.h"
#include "keyhelpers.h"

#if defined(STATUS_DUMP)
// For the status dumper thingamajig
const char* layer_names[] = {
  "Base/Mac", "Win", "Fn", "MacCaps", "WinCaps", "WinCtrl"};
#endif

const action_t keymap[][BoardIO::matrix_size] = {
  {action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6)},
  {action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6)},
  {action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6)},
  {action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6)},
  {action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6)},
  {action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6)},
  {action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6),
   action_t::Keypress(Keystroke::_1), action_t::Keypress(Keystroke::_2),
   action_t::Keypress(Keystroke::_3), action_t::Keypress(Keystroke::_4),
   action_t::Keypress(Keystroke::_5), action_t::Keypress(Keystroke::_6)},
};
