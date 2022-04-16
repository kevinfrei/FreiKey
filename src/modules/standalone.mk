# Stuff to make the stand-alone module test beds easier

ifeq ($(OS),Windows_NT)
# Decide if we've got VC++ around, which on Windows is preferred
ifeq ($(VisualStudioVersion),)
CXX=clang++
else
CXX=cl.exe
endif
SFX=.exe
SEP=\\
# Chocolatey install winflexbison3 :)
BISON=win_bison
CLEANPATHS=$(subst /,${SEP},$1)
MKDIRPATH=$(subst /,${SEP},$1)
devnull=NUL
RM=del /s /q
else
SFX=
SEP=/
BISON=/opt/homebrew/opt/bison/bin/bison
CLEANPATHS=$(subst *,@,$1)
MKDIRPATH=-p $1
devnull=/dev/null
rm=rm -rf
endif

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

DESTDIR = ../../out/${MODNAME}/
IMAGE = ${DESTDIR}${MODNAME}${SFX}

${MODNAME}: out/${MODNAME} ${IMAGE}

.PHONY: clean ${MODNAME}

out/${MODNAME}:
	-@mkdir $(call MKDIRPATH,${DESTDIR}) > ${devnull} 2>&1

CPP_OBJS = $(addprefix ${DESTDIR}, $(patsubst %.cpp, %.${OSUFFIX}, ${CPP_SRC}))

${DESTDIR}%.${OSUFFIX} : %.cpp
	${CXX} ${OPTFLAGS} -I. -Iinclude -I../../include -DSTANDALONE ${STDNUM} -c  $< ${OBJFLAG}$@

clean: 
	-${RM} $(call CLEANPATHS, ${CPP_OBJS} ${MORE_CLEAN} ${IMAGE})

${IMAGE}: ${CPP_OBJS}
	${CXX} ${OPTFLAGS} ${IMGFLAG}$@ $^
