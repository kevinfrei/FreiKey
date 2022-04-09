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
MKDIRPATH=$(subst /,${SEP},$1)
devnull=NUL
else
SFX=
SEP=/
BISON=/opt/homebrew/opt/bison/bin/bison
MKDIRPATH=-p $1
devnull=/dev/null
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

