#!/bin/bash
make -f master.mak -j
make -f left-btuart.mak -j
make -f right-btuart.mak -j
make -f betterfly.mak -j
