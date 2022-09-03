cmake_minimum_required(VERSION 3.12)

add_custom_module(display . display.cpp)
target_link_libraries(module_display PUBLIC Adafruit_ST77XX_lib)