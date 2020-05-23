#!/bin/bash
echo FreiKeys-Master
make -f master.mak -j all out-master/compile_commands.json
echo FreiKeys-Left
make -f left-btuart.mak -j all out-lclient/compile_commands.json
echo FreiKeys-Right
make -f right-btuart.mak -j all out-rclient/compile_commands.json
echo Karbon-Master
make -f karbon.mak -j all out-karbon/compile_commands.json
echo Karbon-Left
make -f l-karbon.mak -j all out-lkarbon/compile_commands.json
echo Karbon-Right
make -f r-karbon.mak -j all out-rkarbon/compile_commands.json
echo BetterFly
make -f betterfly.mak -j all out-betterfly/compile_commands.json
