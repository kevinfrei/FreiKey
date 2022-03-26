#!/bin/sh
# Use clang-format for c/c++ files
git ls-files *.cpp *.ino testing/*.cpp *.h */*.h testing/*/*.h | xargs clang-format -i
# Use prettier for other stuff
# npx prettier -w README.md