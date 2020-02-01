APP_SUFFIX=
#APP_SUFFIX=.exe
BUILD_PROJECT_NAME=${PROJ_NAME}${APP_SUFFIX}
# variables I might need:
# COMPILER_PATH
COMPILER_CPP_FLAGS=-std=c++17 -DMOCKING
COMPILER_CPP_CMD=clang++
COMPILER_C_ELF_CMD=clang++
# COMPILER_CPP_EXTRA_FLAGS
# COMPILER_LDFLAGS
# COMPILER_PATH

SYS_SRC=mock.cpp
USER_SRC=${USER_C_SRCS} ${USER_CPP_SRCS} ${USER_S_SRCS}
ALL_SRC=${SYS_SRC} ${USER_SRC}
VPATH:=${VPATH}:${VPATH_MORE}:${VPATH_CORE}:${VPATH_VAR}

SYS_OBJS=\
  $(addprefix ${BUILD_PATH}/, \
		$(patsubst %.cpp, %.cpp.o, $(notdir ${SYS_SRC})))
USER_OBJS=\
  $(addprefix ${BUILD_PATH}/, \
		$(patsubst %.cpp, %.cpp.o, $(notdir ${USER_SRC})))
ALL_OBJS=${USER_OBJS} ${SYS_OBJS}

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
	test -d "$@" || mkdir "$@"

# Now, on to the actual rules
# I don't think I even need the C compiler: Only C++
#${BUILD_PATH}/%.c.o : %.c
#	"${COMPILER_PATH}${COMPILER_C_CMD}" ${COMPILER_C_FLAGS} -DF_CPU=${BUILD_F_CPU} -DARDUINO=${RUNTIME_IDE_VERSION} -DARDUINO_${BUILD_BOARD} -DARDUINO_ARCH_${BUILD_ARCH} '-DARDUINO_BSP_VERSION="${VERSION}"' ${COMPILER_C_EXTRA_FLAGS} ${BUILD_EXTRA_FLAGS} ${BUILD_FLAGS_NRF} ${SYS_INCLUDES} ${USER_INCLUDES} "$<" -o "$@"
#
#${BUILD_PATH}/c_compile_commands.json: $(USER_C_SRCS) $(C_SYS_SRCS)
#	echo > $@
#	for i in $^ ; do \
#	echo "{ \"directory\": \"${PWD}\",\"file\":\"$$i\",\"command\":" >> $@ ; \
#	echo "\"\\\"${COMPILER_PATH}${COMPILER_C_CMD}\\\" ${COMPILER_C_FLAGS} -DF_CPU=${BUILD_F_CPU} -DARDUINO=${RUNTIME_IDE_VERSION} -DARDUINO_${BUILD_BOARD} -DARDUINO_ARCH_${BUILD_ARCH} -DARDUINO_BSP_VERSION=\\\"${VERSION}\\\" ${COMPILER_C_EXTRA_FLAGS} ${BUILD_EXTRA_FLAGS} ${BUILD_FLAGS_NRF} ${SYS_INCLUDES} ${USER_INCLUDES} \\\"$$i\\\" -o \\\"$$i.o\\\"\"}," >> $@ ;\
	done

${BUILD_PATH}/%.cpp.o : %.cpp
	"${COMPILER_PATH}${COMPILER_CPP_CMD}" ${COMPILER_CPP_FLAGS} ${COMPILER_CPP_EXTRA_FLAGS} \
	${BUILD_EXTRA_FLAGS} ${SYS_INCLUDES} ${USER_INCLUDES} -O0 -g -c "$<" -o "$@"

${BUILD_PATH}/cpp_compile_commands.json: $(USER_CPP_SRCS) $(CPP_SYS_SRCS)
	echo > $@
	for i in $^ ; do \
	echo "{ \"directory\": \"${PWD}\",\"file\":\"$$i\",\"command\":" >> $@ ; \
	echo "\"\\\"${COMPILER_PATH}${COMPILER_CPP_CMD}\\\" ${COMPILER_CPP_FLAGS} ${COMPILER_CPP_EXTRA_FLAGS} ${BUILD_EXTRA_FLAGS} ${SYS_INCLUDES} ${USER_INCLUDES} \\\"$$i\\\" -o \\\"$$i.o\\\"\"}," >> $@ ;\
	done

${BUILD_PATH}/${BUILD_PROJECT_NAME} : ${USER_OBJS} ${SYS_OBJS}
	"${COMPILER_PATH}${COMPILER_C_ELF_CMD}"  "-L${BUILD_PATH}" ${COMPILER_C_ELF_FLAGS} \
	${COMPILER_C_ELF_EXTRA_FLAGS}  ${COMPILER_LDFLAGS} \
	-o "$@" ${USER_OBJS} ${SYS_OBJS}

${BUILD_PATH}/compile_commands.json: ${BUILD_PATH}/cpp_compile_commands.json
	echo "[" > $@.tmp
	cat $^ >> $@.tmp
	echo "]" >> $@.tmp
	sed -e ':a' -e 'N' -e '$$!ba' -e 's/},\n]/}]/g' $@.tmp > $@

compile_commands: ${BUILD_PATH}/compile_commands.json
