cmake_minimum_required(VERSION 3.12)

add_custom_module(menu . menu.cpp)
target_link_libraries(module_menu PUBLIC Adafruit_ST77XX_lib module_display)