#!/bin/bash
echo FreiKeys-Master
make -f freikeys.mak -j all compile_commands
echo FreiKeys-Left
make -f l-freikeys.mak -j all compile_commands
echo FreiKeys-Right
make -f r-freikeys.mak -j all compile_commands
echo Karbon-Master
make -f karbon.mak -j all compile_commands
echo Karbon-Left
make -f l-karbon.mak -j all compile_commands
echo Karbon-Right
make -f r-karbon.mak -j all compile_commands
echo BetterFly
make -f betterfly.mak -j all compile_commands
