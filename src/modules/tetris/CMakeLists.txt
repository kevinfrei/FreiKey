cmake_minimum_required(VERSION 3.12)

add_custom_module(tetris . tetris.cpp tetrisboard.cpp disp_stuff.cpp)
target_link_libraries(module_tetris PUBLIC module_display)