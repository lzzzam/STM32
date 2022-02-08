.SECONDARY:
ROOT   = ../..
CC_DIR = $(ROOT)/Toolchain/gcc-arm-none-eabi
#CC     = $(CC_DIR)/bin/arm-none-eabi-gcc
CC = arm-none-eabi-gcc

CFLAGS += -mcpu=cortex-m4 -mthumb -Og -fmessage-length=0 \
		  -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -flto -fno-move-loop-invariants 
		 
CFLAGS += -Wuninitialized -Wall -Wextra -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -Wbad-function-cast

#CFLAGS += -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wunused -Werror -Wpadded -Wconversion 

CFLAGS += $(foreach file,$(INC),-I"$(file)")

CFLAGS += -D__NO_SYSTEM_INIT

# Link for code size
GC=-Wl,--gc-sections

# Create map file
MAP=-Wl,-Map=$(BUILD_DIR)/out.map

# Use newlib-nano. To disable it, specify USE_NANO=
USE_NANO=--specs=nano.specs

# Use seimhosting or not
USE_SEMIHOST=--specs=rdimon.specs
USE_NOHOST=--specs=nosys.specs

LDSCRIPTS=-L. -L./system -T mem.ld

LFLAGS=$(USE_NANO) $(USE_NOHOST) $(LDSCRIPTS) $(GC) $(MAP)

STARTUP = ./system/startup.S

INC = \
./driver/inc

SRC += \
driver/src/ADC.c \
driver/src/GPIO.c \
driver/src/I2C.c \
driver/src/I2S.c \
driver/src/RCC.c \
driver/src/SPI.c \


BUILD_DIR = ./bin

PROJECTS = test/GPIO_01_Read_UserButton.c


OUTPUTS   = $(foreach file, $(PROJECTS),$(BUILD_DIR)/$(file:%.c=%))
OBJS	  = $(foreach file, $(SRC),$(BUILD_DIR)/$(file:%.c=%.o))

all: $(BUILD_DIR) $(OUTPUTS).elf

%.elf: %.o $(OBJS)
	$(CC) $(STARTUP) $^ $(CFLAGS) $(LFLAGS) -o $@

$(BUILD_DIR)/%.o: %.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	$(CC) $(CFLAGS) -c "$<" -o "$@" 
	@echo 'Finished building: $<'
	@echo ' '

$(BUILD_DIR):
	@echo 'Creating build directories'
	@mkdir -p $(BUILD_DIR)/driver/src
	@mkdir -p $(BUILD_DIR)/test
	@echo '$(BUILD_DIR) created'
	@echo 'Creating sub-directories'

.PHONY: clean
clean:
	rm -r $(BUILD_DIR)

.PHONY: foo
foo:
	@echo $(OBJS)

	