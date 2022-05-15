#pragma once
#include <cstdint>

#include "bitmaps/amy.h"
#include "bitmaps/batman.h"
#include "bitmaps/calc.h"
#include "bitmaps/haha.h"
#include "bitmaps/hug.h"
#include "bitmaps/keyb.h"
#include "bitmaps/like.h"
#include "bitmaps/linux.h"
#include "bitmaps/love.h"
#include "bitmaps/mac.h"
#include "bitmaps/mad.h"
#include "bitmaps/sad.h"
#include "bitmaps/win.h"
#include "bitmaps/wow.h"

struct image_descriptor;

void drawImage(const image_descriptor* id, uint16_t x, uint16_t y);
void ShowImage(const image_descriptor* img);