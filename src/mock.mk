ifeq ($(OS),Windows_NT)
# Decide if we've got VC++ around, which on Windows is preferred
ifeq ($(VisualStudioVersion),)
CXX=clang
else
CXX=cl.exe
endif
APP_SUFFIX=.exe
else
APP_SUFFIX=
endif

BUILD_PROJECT_NAME=${PROJ_NAME}${APP_SUFFIX}
# variables I might need:
# COMPILER_PATH
COMPILER_CPP_FLAGS=-std=c++17 -DMOCKING -DMOCK
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
		$(patsubst %.cpp, %.cpp.o, $(notdir ${USER_SRC})))
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
	-rm ${USER_OBJS}

allclean:
	-rm -rf ${BUILD_PATH}

# Make us rebuild user code if the makefile(s) change:
# Needs to be above the deps thing, I think
${USER_OBJS} : $(MAKEFILE_LIST)

# Let's start using the generated .d files...
-include $(ALL_OBJS:.o=.d)

# Next, the project name shortcut, because it's easier
${PROJ_NAME}: ${BUILD_PATH}/${BUILD_PROJECT_NAME}

# And finally, create the director
# TODO: This no worky on Windows fer sure
${BUILD_PATH}:
ifeq ($(OS),Windows_NT)
	-@mkdir "$@"
else
	@test -d "$@" || mkdir -p "$@"
endif

${BUILD_PATH}/%.cpp.o : %.cpp
	"${CXX}" -c ${COMPILER_CPP_FLAGS} ${SYS_INCLUDES} ${USER_INCLUDES} ${COMPILER_CPP_EXTRA_FLAGS} "$<" -o "$@"

${BUILD_PATH}/${BUILD_PROJECT_NAME} : ${USER_OBJS}
	"${CXX}" -o "$@" ${USER_OBJS} ${BUILD_FLAGS_LIBS}

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
