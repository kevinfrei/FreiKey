# roll-up make file. It doesn't do dependency checking for anything,
# it's just, perhaps, better than a shell script

# phony rules cust there are no dependencies
.PHONY: allclean karbon lk rk lkf rkf kflash lkflash rkflash fflash lfflash rfflash allk allf kf k lkf rkf laptype lt l ltf lf flaptype laptypef

# TODO: Need to turn this off for Windows GNUmake :(
# TODO: Make instead, use WSL for build, then Windows for flashing maybe?
flags=-j

# Now the default target
all: allk allf laptype

allclean:
ifeq ($(OS),Windows_NT)
	-rd /s /q out
else
	-rm -rf out
endif

allk k: karbon lk rk

karbon:
	make ${flags} -f karbon.mak all compile_commands

laptype lt l:
	make ${flags} -f laptype.mak all compile_commands

flaptype laptypef lf ltf:
	make ${flags} -f laptype.mak flash

lk:
	make ${flags} -f l-karbon.mak all compile_commands

rk:
	make ${flags} -f r-karbon.mak all compile_commands

kflash kf:
	make ${flags} -f karbon.mak flash

lkflash lkf:
	make ${flags} -f l-karbon.mak flash

rkflash rkf:
	make ${flags} -f r-karbon.mak flash
