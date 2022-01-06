#!/bin/bash
echo Karbon-Master
make -f karbon.mak -j all 
#compile_commands
echo Karbon-Left
make -f l-karbon.mak -j all
#compile_commands
echo Karbon-Right
make -f r-karbon.mak -j all
#compile_commands
