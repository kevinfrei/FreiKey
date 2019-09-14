#!/bin/bash
make -f master.mak -j allclean
make -f left-btuart.mak -j allclean
make -f right-btuart.mak -j allclean
make -f betterfly.mak -j allclean
./build.sh
make -f master.mak compile_commands
make -f left-btuart.mak compile_commands
make -f right-btuart.mak compile_commands
make -f betterfly.mak compile_commands



