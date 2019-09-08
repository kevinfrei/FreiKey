#!/bin/bash
echo MASTER
make -f master.mak -j
echo LEFT
make -f left-btuart.mak -j
echo RIGHT
make -f right-btuart.mak -j
echo BETTERFLY
make -f betterfly.mak -j
