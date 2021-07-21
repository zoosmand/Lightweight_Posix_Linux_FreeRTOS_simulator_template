CC := gcc
TARGET = posix_demo
DEBUG = 1
OPT = -O1

BUILD_DIR := build

CORE_DIR_REL := ./Core
CORE_DIR := $(abspath $(CORE_DIR_REL))

FREERTOS_DIR_REL := ./FreeRTOS
FREERTOS_DIR := $(abspath $(FREERTOS_DIR_REL))

FREERTOS_PLUS_DIR_REL := ./FreeRTOS-Plus
FREERTOS_PLUS_DIR := $(abspath $(FREERTOS_PLUS_DIR_REL))

INCLUDE_DIRS := -I.
INCLUDE_DIRS += -I${CORE_DIR}/Inc
INCLUDE_DIRS += -I${FREERTOS_DIR}/include
INCLUDE_DIRS += -I${FREERTOS_DIR}/portable/ThirdParty/GCC/Posix
INCLUDE_DIRS += -I${FREERTOS_DIR}/portable/ThirdParty/GCC/Posix/utils
INCLUDE_DIRS += -I${FREERTOS_PLUS_DIR}/FreeRTOS-Plus-Trace/Include

SOURCE_FILES := $(wildcard ${CORE_DIR}/Src/*.c)
SOURCE_FILES += $(wildcard ${FREERTOS_DIR}/*.c)
# Memory manager (use malloc() / free() )
SOURCE_FILES += ${FREERTOS_DIR}/portable/MemMang/heap_4.c
# posix port
SOURCE_FILES += ${FREERTOS_DIR}/portable/ThirdParty/GCC/Posix/utils/wait_for_event.c
SOURCE_FILES += ${FREERTOS_DIR}/portable/ThirdParty/GCC/Posix/port.c

# Trace library.
SOURCE_FILES += ${FREERTOS_PLUS_DIR}/FreeRTOS-Plus-Trace/trcKernelPort.c
SOURCE_FILES += ${FREERTOS_PLUS_DIR}/FreeRTOS-Plus-Trace/trcSnapshotRecorder.c
SOURCE_FILES += ${FREERTOS_PLUS_DIR}/FreeRTOS-Plus-Trace/trcStreamingRecorder.c
SOURCE_FILES += ${FREERTOS_PLUS_DIR}/FreeRTOS-Plus-Trace/streamports/File/trcStreamingPort.c



C_DEFS = \
-DDEBUG \
-DprojCOVERAGE_TEST=0 \
-D_WINDOWS_


CFLAGS := -ggdb3 ${OPT} $(C_DEFS)

ifeq ($( DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif


LDFLAGS := -ggdb3 -O0 -pthread -lpcap

OBJ_FILES = $(SOURCE_FILES:%.c=$(BUILD_DIR)/%.o)

DEP_FILE = $(OBJ_FILES:%.o=%.d)

${TARGET} : $(BUILD_DIR)/$(TARGET)

${BUILD_DIR}/${TARGET} : ${OBJ_FILES}
	-mkdir -p ${@D}
	$(CC) $^ $(CFLAGS) $(INCLUDE_DIRS) ${LDFLAGS} -o $@

-include ${DEP_FILE}

${BUILD_DIR}/%.o : %.c
	-mkdir -p $(@D)
	$(CC) $(CFLAGS) ${INCLUDE_DIRS} -MMD -c $< -o $@

.PHONY: clean

clean:
	-rm -rf $(BUILD_DIR)







