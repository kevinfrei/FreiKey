# roll-up make file. It doesn't do dependency checking for anything,
# it's just, perhaps, better than a shell script

# phony rules cust there are no dependencies
.PHONY: allclean karbon lk rk lkf rkf kflash lkflash rkflash fflash lfflash rfflash allk allf kf k lkf rkf laptype lt l ltf lf flaptype laptypef 3 3p three threepiece 3f 3pf threef threepiecef f3 f3p fthree fthreepiece imgcomp img cmp comp

# TODO: Need to turn this off for Windows GNUmake :(
# TODO: Make instead, use WSL for build, then Windows for flashing maybe?
ifeq ($(OS),Windows_NT)
flags=
else
flags=-j
endif
# Now the default target
all: allk allf laptype mock

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

threepiece three 3 3p:
	make ${flags} -f threepiece.mak all compile_commands

fthreepiece fthree f3 f3p threepiecef threef 3f 3pf:
	make ${flags} -f threepiece.mak flash

mock m:
	make ${flags} -f mock.mak all compile_commands

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
# Decide if we've got VC++ around, which on Windows is preferred
ifeq ($(VisualStudioVersion),)
CXX=clang
else
CXX=cl.exe
endif
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
ifeq (${CXX},cl.exe)
OBJFLAG=/FS /Fo
IMGFLAG=/FS /Fe
OPTFLAGS=/Od /ZI /EHsc
STDNUM=/std:c++20
OSUFFIX=obj
else
OBJFLAG="-o "
IMGFLAG="-o "
OPTFLAGS=-g
STDNUM=-std=c++20
OSUFFIX=o
endif

# Set up rules for local binaries
out/%.${OSUFFIX}: bitmaps/%.cpp
	${CXX} ${OPTFLAGS} -c -DCOMPRESSOR -Iinclude ${STDNUM} $< ${OBJFLAG}$@

out/%.${OSUFFIX} : %.cpp
	${CXX} ${OPTFLAGS} -c -DCOMPRESSOR -Iinclude ${STDNUM} $< ${OBJFLAG}$@

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
 
OBJS = $(addprefix out/, $(patsubst %.cpp, %.${OSUFFIX}, ${IMGSRC}))

out/imagecomp${SFX}: ${OBJS}
	${CXX} ${OPTFLAGS} ${IMGFLAG}$@ $^
