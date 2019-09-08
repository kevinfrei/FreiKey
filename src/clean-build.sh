#!/bin/bash
make -f wire-master.mak -j allclean
make -f left-btuart.mak -j allclean
make -f right-btuart.mak -j allclean
make -f betterfly.mak -j allclean
./build.sh


