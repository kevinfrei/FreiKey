cmake_minimum_required(VERSION 3.12)

add_custom_module(
  images
  .
  image.cpp
  imgdec_pal.cpp
  imgdec_prle.cpp
  imgdec_rle.cpp
  bitmaps/amy.cpp
  bitmaps/batman.cpp
  bitmaps/calc.cpp
  bitmaps/haha.cpp
  bitmaps/hug.cpp
  bitmaps/keyb.cpp
  bitmaps/like.cpp
  bitmaps/linux.cpp
  bitmaps/love.cpp
  bitmaps/mac.cpp
  bitmaps/mad.cpp
  bitmaps/sad.cpp
  bitmaps/win.cpp
  bitmaps/wow.cpp
)
target_include_directories(
  module_images
  PUBLIC
  include
)
target_link_libraries(module_images PUBLIC Adafruit_ST77XX_lib module_display)