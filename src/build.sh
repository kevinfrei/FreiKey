#!/bin/bash
make -f wire-master.mak -j
make -f left-btuart.mak -j
make -f right-btuart.mak -j

