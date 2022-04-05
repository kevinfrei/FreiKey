# roll-up make file. It doesn't do dependency checking for anything,
# it's just, perhaps, better than a shell script

# phony rules cus there are no dependencies
.PHONY: allclean laptype lt l ltf lf flaptype laptypef 3 3p three threepiece 3f 3pf threef threepiecef f3 f3p fthree fthreepiece imgcomp img cmp comp

# TODO: Need to turn this off for Windows GNUmake :(
# TODO: Make instead, use WSL for build, then Windows for flashing maybe?
ifeq ($(OS),Windows_NT)
flags=
SEP=\\
# Chocolatey install winflexbison3 :)
FLEX=win_flex
FLEXFLAGS=-wincompat
BISON=win_bison
else
flags=-j
SEP=/
FLEX=flex
BISON=bison
endif
# Now the default target
all: laptype threepiece mock img

clean:
ifeq ($(OS),Windows_NT)
	-@rd /s /q out > NUL 2>&1
else
	-rm -rf out
endif

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

rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))

format: $(call rwildcard,include,*.h) $(wildcard *.cpp) $(wildcard bitmaps/*.cpp) $(wildcard bitmaps/*.h)
	clang-format -i $^

ifeq ($(OS),Windows_NT)
# Decide if we've got VC++ around, which on Windows is preferred
ifeq ($(VisualStudioVersion),)
CXX=clang++
else
CXX=cl.exe
endif
SFX=.exe
else
SFX=
endif

comp cmp img imgcomp: out out/imgenc out/imgenc/imagecomp${SFX}

out:
	-mkdir out

out/imgenc:
	-mkdir out${SEP}imgenc

# Size is larger than -O3 lame lame lame, clang
# OPTFLAGS=-flto -Oz
# Speed:
# OPTFLAGS=-flto -O3
# Debug:
ifeq (${CXX},cl.exe)
OBJFLAG=/FS /Fo
IMGFLAG=/FS /Fe
OPTFLAGS=/Od /Zi /EHsc
STDNUM=/std:c++20
OSUFFIX=obj
else
OBJFLAG=-o
IMGFLAG=-o
OPTFLAGS=-g
STDNUM=-std=c++20
OSUFFIX=o
endif

# Set up rules for local binaries
out/imgenc/%.${OSUFFIX}: bitmaps/%.cpp
	${CXX} ${OPTFLAGS} -c -DCOMPRESSOR -Iinclude ${STDNUM} $< ${OBJFLAG}$@

out/imgenc/%.${OSUFFIX} : %.cpp
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
 
IMGOBJS = $(addprefix out/imgenc/, $(patsubst %.cpp, %.${OSUFFIX}, ${IMGSRC}))

out/imgenc/imagecomp${SFX}: ${IMGOBJS}
	${CXX} ${OPTFLAGS} ${IMGFLAG}$@ $^

calc: out out/calc out/calc/calculator${SFX}

out/calc:
	-mkdir out${SEP}calc

out/calc/%.${OSUFFIX} : %.cpp
	${CXX} ${OPTFLAGS} -c -DCALC_TEST -Iinclude -I. ${STDNUM} $< ${OBJFLAG}$@

CALCSRC = CalcParsing.cpp CalcTokenization.cpp

CALCOBJS = $(addprefix out/calc/, $(patsubst %.cpp, %.${OSUFFIX}, ${CALCSRC}))

out/calc/calculator${SFX}: ${CALCOBJS}
	${CXX} ${OPTFLAGS} ${IMGFLAG}$@ $^
