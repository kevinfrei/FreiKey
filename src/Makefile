# roll-up make file. It doesn't do dependency checking for anything,
# it's just, perhaps, better than a shell script

# phony rules cus there are no dependencies
.PHONY: allclean laptype lt l ltf lf flaptype laptypef 3 3p three threepiece 3f 3pf threef threepiecef f3 f3p fthree fthreepiece imgcomp img cmp comp

# TODO: Make instead, use WSL for build, then Windows for flashing maybe?
ifeq ($(OS),Windows_NT)
flags=
else
flags=-j
endif
# Now the default target
all: laptype threepiece mock img

clean:	
	$(MAKE) -C modules/calculator ${flags} clean
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

format: $(call rwildcard,include,*.h) $(wildcard *.cpp) $(wildcard bitmaps/*.cpp) $(wildcard bitmaps/*.h) $(call rwildcard,modules,*.cpp) $(call rwildcard,modules,*.h)
	clang-format -i $^

comp cmp img imgcomp: out out/imgenc out/imgenc/imagecomp${SFX}

out:
	-mkdir out

out/imgenc:
	-mkdir out${SEP}imgenc

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

calc:
	$(MAKE) -C modules/calculator ${flags}