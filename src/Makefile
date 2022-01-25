# roll-up make file. It doesn't do dependency checking for anything,
# it's just, perhaps, better than a shell script

# phony rules cust there are no dependencies
.PHONY: allclean karbon lk rk lkf rkf kflash lkflash rkflash fflash lfflash rfflash allk allf kf k lkf rkf laptype lt l ltf lf flaptype laptypef imgcomp img cmp comp

# TODO: Need to turn this off for Windows GNUmake :(
# TODO: Make instead, use WSL for build, then Windows for flashing maybe?
ifeq ($(OS),Windows_NT)
flags=
else
flags=-j
endif
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

ifeq ($(OS),Windows_NT)
CXX=clang
SFX=.exe
else
SFX=
endif

comp cmp img imgcomp: out out/imagecomp${SFX}

out:
	-mkdir out

# Size is larger than -O3 lame lame lame, clang
# OPTFLAGS=-flto -Oz
# Speed:
# OPTFLAGS=-flto -O3
# Debug:
OPTFLAGS=-g

# Set up rules for local binaries
out/%.o: bitmaps/%.cpp
	${CXX} ${OPTFLAGS} -c -DCOMPRESSOR -Iinclude -DPROGMEM=" " -std=c++17 $< -o $@

out/%.o : %.cpp
	${CXX} ${OPTFLAGS} -c -DCOMPRESSOR -Iinclude -std=c++17 $< -o $@

IMGSRC = imgencoder.cpp \
 img_cmdln.cpp \
 imgenc_rle.cpp \
 imgdec_rle.cpp \
 imgenc_pal.cpp \
 imgdec_pal.cpp \
 imgenc_prle.cpp \
 imgdec_prle.cpp \
 amy.cpp \
 batman.cpp \
 win.cpp \
 mac.cpp \
 linux.cpp
 
OBJS = $(addprefix out/, $(patsubst %.cpp, %.o, ${IMGSRC}))

out/imagecomp${SFX}: ${OBJS}
	${CXX} ${OPTFLAGS} -o $@ $^