# BUILD_VERBOSE = 1

ifdef BOARD
else
BOARD ?= fr8008gp
endif
BOARD_DIR = boards/$(BOARD)

PROJECT_NAME := $(BOARD)_micropython

# Include the core environment definitions; this will set $(TOP).
include ../../py/mkenv.mk

-include mpconfigprot.mk
include $(BOARD_DIR)/mpconfigboard.mk

MCU_DIR = mcu/$(MCU_SERIES)
include $(MCU_DIR)/mpconfigmcu.mk

# Include py core make definitions.
include $(TOP)/py/py.mk
include $(TOP)/extmod/extmod.mk

# Set CFLAGS and libraries.
CFLAGS += -I. -I$(BUILD) -I$(TOP)
LIBS += -lm

CROSS_COMPILE ?= arm-none-eabi-
OBJDUMP ?= $(CROSS_COMPILE)objdump

# Define the required source files.
SRC_C += \
	main.c \
	mphalport.c \
	help.c \
	$(MCU_DIR)/freqchip_main.c \
	shared/readline/readline.c \
	shared/runtime/gchelper_generic.c \
	shared/runtime/pyexec.c \
	shared/runtime/stdout_helpers.c \

# components/modules/platform/src/gcc/exception_handlers.c \

# Define source files containung qstrs.
SRC_QSTR += shared/readline/readline.c shared/runtime/pyexec.c

# MicroPython feature configurations
MICROPY_ROM_TEXT_COMPRESSION ?= 1

# include header files
INC += -I. \
	-I$(TOP) \
	-I$(BUILD) \
	-I$(BOARD_DIR) \
	-I$(MCU_DIR) \

# Debugging/Optimization
ifeq ($(DEBUG), 1)
CFLAGS += -g
COPT = -O0
else
COPT += -Os -DNDEBUG
endif

# Define the required object files.
OBJ = $(PY_CORE_O) $(addprefix $(BUILD)/, $(SRC_C:.c=.o))

Target_OBJS : $(OBJ)

$(BUILD)/%.o : %.c
	$(info Bulid: compiling $^)
	$(NO_ECHO)$(CC) $(CFLAGS) $(INC) -c -o  $@ $<

$(BUILD)/%.o : %.s
	$(info Bulid: compiling $^)
	$(NO_ECHO)$(CC) $(CFLAGS) $(INC) -c -o  $@ $<


# Define the top-level target, the main firmware.
# all: $(BUILD)/$(PROJECT_NAME).elf
all: $(BUILD)/$(PROJECT_NAME).bin

# Define how to build the firmware.
$(BUILD)/$(PROJECT_NAME).elf: $(OBJ)
	$(Q)$(CC) $(LDFLAGS) -Wl,-Map,"$(PROJECT_NAME).map" -o $(BUILD)/$(PROJECT_NAME).elf $^ $(LIBS)
	$(NO_ECHO)$(OBJCOPY) -O binary -S $(BUILD)/$(PROJECT_NAME).elf $(PROJECT_NAME).bin
	$(NO_ECHO)$(OBJCOPY) -O ihex   -S $(BUILD)/$(PROJECT_NAME).elf $(PROJECT_NAME).hex
	$(NO_ECHO)$(OBJDUMP) -D $(BUILD)/$(PROJECT_NAME).elf > $(PROJECT_NAME).dis


$(BUILD)/$(PROJECT_NAME).bin: $(BUILD)/$(PROJECT_NAME).elf
	$(Q)$(OBJCOPY) -O binary $^ $(BUILD)/$(PROJECT_NAME).bin
	
# $(Q)$(OBJDUMP) -D $(BUILD)/$(PROJECT_NAME).elf > $(PROJECT_NAME).dis

# Include remaining core make rules.
include $(TOP)/py/mkrules.mk
