# roll-up make file. It doesn't do dependency checking for anything,
# it's just, perhaps, better than a shell script

# phony rules cus there are no dependencies
.PHONY: clean laptype lt l ltf lf flaptype laptypef 3 3p three threepiece 3f 3pf threef threepiecef f3 f3p fthree fthreepiece img calc edit test testf ftest tf ft t sd sdf fsd 41 41f f41

flags=-j
THIS_DIR := $(dir $(abspath $(firstword $(MAKEFILE_LIST))))

# Now the default target
all: laptype threepiece mock img calc edit test

clean:
	-$(MAKE) -C modules/calculator ${flags} clean
	-$(MAKE) -C modules/images ${flags} clean
ifeq ($(OS),Windows_NT)
	-cmd /c rd /s /q $(subst /,\,${THIS_DIR}out)
	-cmd /c mkdir $(subst /,\,${THIS_DIR}out)
else
	-rm -rf out
	mkdir out
endif

laptype lt l:
	$(MAKE) ${flags} -f make-laptype.mak all compile_commands

flaptype laptypef lf ltf:
	$(MAKE) ${flags} -f make-laptype.mak flash

threepiece three 3 3p:
	$(MAKE) ${flags} -f make-3piece.mak all compile_commands

fthreepiece fthree f3 f3p threepiecef threef 3f 3pf:
	$(MAKE) ${flags} -f make-3piece.mak flash

test t:
	$(MAKE) ${flags} -f make-test.mak all

testf tf ftest ft:
	$(MAKE) ${flags} -f make-test.mak flash

big bigscreen:
	$(MAKE) ${flags} -f make-bigscreen.mak all

bigf bigscreenf:
	$(MAKE) ${flags} -f make-bigscreen.mak flash

sd:
	$(MAKE) ${flags} -f make-sd.mak all

sdf fds:
	$(MAKE) ${flags} -f make-sd.mak flash

41:
	$(MAKE) ${flags} -f make-41.mak all

41f f41:
	$(MAKE) ${flags} -f make-41.mak flash

mock m:
	$(MAKE) ${flags} -f make-mock.mak all compile_commands

rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))

format: $(call rwildcard,include,*.h) $(wildcard *.cpp) $(wildcard bitmaps/*.cpp) $(wildcard bitmaps/*.h) $(call rwildcard,modules,*.cpp) $(call rwildcard,modules,*.h)
	clang-format -i $^

img:
	$(MAKE) -C modules/images ${flags}

calc:
	$(MAKE) -C modules/calculator ${flags}

edit:
	$(MAKE) -C modules/editline ${flags}

