ifeq ($(OS),Windows_NT)
CXX=clang++
SFX=.exe
SEP=\\
MKDIRPATH=$(subst /,${SEP},$1)
else
SFX=
SEP=/
ifeq ($(shell uname -p), i386)
	BISON=/usr/local/opt/bison/bin/bison
else
	BISON=/opt/homebrew/opt/bison/bin/bison
endif
MKDIRPATH=-p $1
endif

# Size is larger than -O3 lame lame lame, clang
# OPTFLAGS=-flto -Oz
# Speed:
# OPTFLAGS=-flto -O3
# Debug:
ifeq (${CXX},cl.exe)
OBJFLAG=/Fo:
IMGFLAG=/Fe:
OPTFLAGS=/Od /Zi /EHsc
STDNUM=/std:c++20
OSUFFIX=obj
ONLYCOMPILE=/c
else
OBJFLAG=-o
IMGFLAG=-o
OPTFLAGS=-g
STDNUM=-std=c++20
OSUFFIX=o
ONLYCOMPILE=-c
endif

BUILD_PROJECT_NAME=${PROJ_NAME}${APP_SUFFIX}
# variables I might need:
# COMPILER_PATH
COMPILER_CPP_FLAGS=${STDNUM} -DMOCKING
COMPILER_CPP_CMD=clang++
COMPILER_C_ELF_CMD=clang++
# COMPILER_CPP_EXTRA_FLAGS
# COMPILER_LDFLAGS
# COMPILER_PATH

USER_SRC=${USER_C_SRCS} ${USER_CPP_SRCS} ${USER_S_SRCS}
ALL_SRC=${USER_SRC}
VPATH:=${VPATH}:${VPATH_MORE}:${VPATH_CORE}:${VPATH_VAR}

USER_OBJS=\
  $(addprefix ${BUILD_PATH}/, \
		$(patsubst %.cpp, %.cpp.${OSUFFIX}, $(notdir ${USER_SRC})))
ALL_OBJS=${USER_OBJS}
USER_JSON=\
  $(addprefix ${BUILD_PATH}/, \
    $(patsubst %.c, %.c.json, \
      $(patsubst %.cpp, %.cpp.json, \
        $(patsubst %.S, %.S.json, $(notdir ${USER_SRC})))))

# And now the build rules!

# First, the phony rules that don't product things
.PHONY: ${PROJ_NAME} clean allclean

# Now the default target
all: ${BUILD_PATH} ${PROJ_NAME}

# Some house keeping
clean:
ifeq ($(OS),Windows_NT)
	-@del ${USER_OBJS}
else
	-rm ${USER_OBJS}
endif

# Make us rebuild user code if the makefile(s) change:
# Needs to be above the deps thing, I think
${USER_OBJS} : $(MAKEFILE_LIST)

# Let's start using the generated .d files...
-include $(ALL_OBJS:.o=.d)

# Next, the project name shortcut, because it's easier
${PROJ_NAME}: ${BUILD_PATH}/${BUILD_PROJECT_NAME}${SFX}

# And finally, create the director
# TODO: This no worky on Windows fer sure
${BUILD_PATH}:
ifeq ($(OS),Windows_NT)
	-@mkdir "$@"
else
	@test -d "$@" || mkdir -p "$@"
endif

${BUILD_PATH}/%.cpp.${OSUFFIX} : %.cpp
	"${CXX}" ${ONLYCOMPILE} ${COMPILER_CPP_FLAGS} ${SYS_INCLUDES} ${USER_INCLUDES} ${OPTFLAGS} ${COMPILER_CPP_EXTRA_FLAGS} "$<" ${OBJFLAG} "$@"

${BUILD_PATH}/${BUILD_PROJECT_NAME}${SFX} : ${USER_OBJS}
	"${CXX}" ${USER_OBJS} ${BUILD_FLAGS_LIBS} ${IMGFLAG} "$@"

${BUILD_PATH}/%.cpp.json : %.cpp
ifeq ($(OS),Windows_NT)
	@echo { "directory":"$(<D)", "file":"$(<F)", "command": > $@
	@echo "\"${CXX}\" -c ${COMPILER_CPP_FLAGS}  ${SYS_INCLUDES} ${USER_INCLUDES} ${COMPILER_CPP_EXTRA_FLAGS} \"$<\" -o \"$@\"" >> $@
	@echo }, >> $@
else
	@echo "{ \"directory\": \"$(<D)\",\"file\":\"$(<F)\"," > $@
	@echo "\"command\":\"\\\"${CXX}\\\" -c ${COMPILER_CPP_FLAGS} ${SYS_INCLUDES} ${USER_INCLUDES} ${COMPILER_CPP_EXTRA_FLAGS} \\\"$<\\\" -o \\\"$@\\\"\"}," >> $@
endif

${BUILD_PATH}/compile_commands.json: ${USER_JSON}
ifeq ($(OS),Windows_NT)
	@echo [ > $@
	@sed -e "s/ / /" $^ >> $@
	@echo {}] >> $@
else
	@echo "[" > $@.tmp
	@sed -e "s/ / /" $^ >> $@.tmp
	@echo "]" >> $@.tmp
	@sed -e ':a' -e 'N' -e '$$!ba' -e 's/},\n]/}]/g' $@.tmp > $@
endif

compile_commands: ${BUILD_PATH} ${BUILD_PATH}/compile_commands.json
