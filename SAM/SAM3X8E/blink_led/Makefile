# Makefile author Luca Zambuto, 13 December 2020
#
# targets:
#   all:    compiles the source code
#   clean:  removes all .hex, .elf, and .o files in the source code and library directories

# parameters (change this stuff accordingly)
# project name
PRJ = blink_led
# atmel sam mcu
MCU = __SAM3X8E__
# board model
BOARD = "ARDUINO_DUE_X"

F_CPU = 84000000

# program source files (not including external libraries)
SRC = $(PRJ).c

# atmel software framework path
ASF_PATH = /Users/luca/Documents/Embedded/atmel/sam/xdk-asf-3.48.0

# where to look for external libraries (consisting of .c/.cpp files and .h files)
EXT = $(ASF_PATH)/thirdparty/CMSIS/include \
			$(ASF_PATH)/common/utils \
			$(ASF_PATH)/common/boards \
			$(ASF_PATH)/common/services \
			$(ASF_PATH)/common/services/clock \
			$(ASF_PATH)/common/services/clock/sam3x/module_config \
			$(ASF_PATH)/sam/boards \
			$(ASF_PATH)/sam/utils \
			$(ASF_PATH)/sam/utils/preprocessor \
			$(ASF_PATH)/sam/utils/header_files \
		  $(ASF_PATH)/sam/utils/cmsis/sam3x/include \
			$(ASF_PATH)/sam/utils/cmsis/sam3x/source/templates \
			$(ASF_PATH)/sam/utils/cmsis/sam3x/source/templates/gcc \
			$(ASF_PATH)/sam/drivers \
			$(ASF_PATH)/sam/drivers/pmc

# external libraries .c files
EXTSRC = \
$(ASF_PATH)/sam/drivers/pmc/pmc.c\
$(ASF_PATH)/common/services/clock/sam3x/sysclk.c

# start-up files path
STARTUP_FILE = $(ASF_PATH)/sam/utils/cmsis/sam3x/source/templates/gcc/startup_sam3x.c
SYSTEM_FILE = $(ASF_PATH)/sam/utils/cmsis/sam3x/source/templates/system_sam3x.c
EXCEPETIONS_FILE = $(ASF_PATH)/sam/utils/cmsis/sam3x/source/templates/exceptions.c

# linker script
LDSCRIPT = $(ASF_PATH)/sam/utils/linker_scripts/sam3x/sam3x8/gcc/flash.ld

#################################################################################################
# \/ stuff nobody needs to worry about until such time that worrying about it is appropriate \/ #
#################################################################################################

# executables
CC=arm-none-eabi-gcc
LD=arm-none-eabi-gcc
AR=arm-none-eabi-ar
AS=arm-none-eabi-as
CP=arm-none-eabi-objcopy

# Include path
INCLUDE := $(foreach dir, $(EXT), -I$(dir))

# C flags
CFLAGS+= -mcpu=cortex-m0 -mthumb -g
CFLAGS+=  $(INCLUDE) -I .
CFLAGS+= -D$(MCU) -DBOARD=$(BOARD)

# Linker flags
LDFLAGS+= -T$(LDSCRIPT) -mthumb -mcpu=cortex-m0 -Wl,--gc-sections

#Directory name
BUILD_DIR = build
BOOT_DIR  = boot
BIN_DIR 	= bin

# generate list of boot objects files to build
BOOT_OBJS = ./$(BUILD_DIR)/$(BOOT_DIR)/startup_sam3x.o \
 						./$(BUILD_DIR)/$(BOOT_DIR)/system_sam3x.o \
						./$(BUILD_DIR)/$(BOOT_DIR)/exceptions.o

# generate list of app objects files to build
OBJS:= $(patsubst %.c, ./$(BUILD_DIR)/%.o, $(SRC))

# generate list of external libraries object files to build
EXTOBJS:= $(patsubst %.c, ./$(BUILD_DIR)/%.o, $(notdir $(EXTSRC)))

# user targets
# compile all files
all: ./$(BUILD_DIR)/$(BIN_DIR)/$(PRJ).bin

# remove build directory
clean:
	rm -r $(BUILD_DIR)

#create .bin file
./$(BUILD_DIR)/$(BIN_DIR)/$(PRJ).bin: 	./$(BUILD_DIR)/$(BIN_DIR)/$(PRJ).hex
	$(CP) -I ihex $< -O binary $@

#create .hex file
./$(BUILD_DIR)/$(BIN_DIR)/$(PRJ).hex: 	./$(BUILD_DIR)/$(BIN_DIR)/$(PRJ).elf
	$(CP) -O ihex $< $@

#create .elf file
./$(BUILD_DIR)/$(BIN_DIR)/$(PRJ).elf: BUILD_DIR BOOT_OBJS $(EXTOBJS) $(OBJS)
	@echo " "
	@echo "LINKING OBJECTS FILES"
	$(LD) $(LDFLAGS) -o $@ $(OBJS) $(BOOT_OBJS) $(EXTOBJS)

# create build directory
BUILD_DIR:
	@echo " "
	@echo "MK BUILD_DIR"
	mkdir -p ./$(BUILD_DIR)
	mkdir -p ./$(BUILD_DIR)/$(BOOT_DIR)
	mkdir -p ./$(BUILD_DIR)/$(BIN_DIR)

# build start-up files
BOOT_OBJS:
	@echo " "
	@echo "CC $@"
	$(CC) -c $(CFLAGS) $(STARTUP_FILE) -o ./$(BUILD_DIR)/$(BOOT_DIR)/startup_sam3x.o
	$(CC) -c $(CFLAGS) $(SYSTEM_FILE) -o ./$(BUILD_DIR)/$(BOOT_DIR)/system_sam3x.o
	$(CC) -c $(CFLAGS) $(EXCEPETIONS_FILE) -o ./$(BUILD_DIR)/$(BOOT_DIR)/exceptions.o

# compile and generate object file from .c file
./$(BUILD_DIR)/%.o:    %.c
	@echo " "
	@echo "CC $*"
	$(CC) -c $(CFLAGS) $< -o $@

# compile and generate object file from .s file
./$(BUILD_DIR)/%.o:    %.s
	$(AS) $< -o $@

#################################################################################################
# \/ 						Rules for building Atmel Software Framework library components							 \/ #
#################################################################################################

# compile pmc library
./$(BUILD_DIR)/pmc.o:
	@echo " "
	@echo "CC $*"
	$(CC) -c $(CFLAGS) $(ASF_PATH)/sam/drivers/pmc/pmc.c -o $@


# compile sysclk library
./$(BUILD_DIR)/sysclk.o:
	@echo " "
	@echo "CC $*"
	$(CC) -c $(CFLAGS) $(ASF_PATH)/common/services/clock/sam3x/sysclk.c -o $@
