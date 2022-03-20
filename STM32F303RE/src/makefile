.SECONDARY:
ROOT   = /Users/luca/Documents/GitHub/Embedded-Software/Toolchain/Compilers
CC_DIR = $(ROOT)/gcc-arm-none-eabi/bin
CC     = $(CC_DIR)/arm-none-eabi-gcc
SIZE   = $(CC_DIR)/arm-none-eabi-size
OBJCOPY = $(CC_DIR)/arm-none-eabi-objcopy
OBJDUMP = $(CC_DIR)/arm-none-eabi-objdump
READELF = $(CC_DIR)/arm-none-eabi-readelf

CFLAGS += -mcpu=cortex-m4 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -flto \
		  -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op \
		  -Waggregate-return -Wfloat-equal -Wmissing-prototypes -Wstrict-prototypes -Wbad-function-cast -g3


CFLAGS += $(foreach file,$(INC),-I"$(file)")

LFLAGS = -L"./ldscript" -T mem.ld -nostartfiles -Xlinker --gc-sections -Wl,-Map=$(OUTPUT).map

BUILD_DIR = ./bin

TARGET    = test/test.c

STARTUP = system/startup.c

INC = \
./driver/inc

SRC += \
$(STARTUP) \
# driver/src/ADC.c \
# driver/src/GPIO.c \
# driver/src/I2C.c \
# driver/src/I2S.c \
# driver/src/RCC.c \
# driver/src/SPI.c \

OUTPUT    = $(foreach file, $(TARGET),$(BUILD_DIR)/$(file:%.c=%))
OBJS	  = $(foreach file, $(SRC),$(BUILD_DIR)/$(file:%.c=%.o))

all: $(BUILD_DIR) $(OUTPUT).elf $(OUTPUT).hex

%.hex: %.elf
	$(OBJCOPY) $^ $@

%.elf: %.o $(OBJS)
	$(CC) $^ $(CFLAGS) $(LFLAGS) -o $@

$(BUILD_DIR)/%.o: %.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	$(CC) $(CFLAGS) -c "$<" -o "$@" 
	@echo 'Finished building: $<'
	@echo ' '

$(BUILD_DIR):
	@echo 'Creating build directories'
	@mkdir -p $(BUILD_DIR)/driver/src
	@mkdir -p $(BUILD_DIR)/system
	@mkdir -p $(BUILD_DIR)/test
	@echo '$(BUILD_DIR) created'

.PHONY: clean
clean:
	rm -r $(BUILD_DIR)


.PHONY: size
size: $(OUTPUT).hex
	$(SIZE) $(OUTPUT).hex

.PHONY: symbol
symbol: $(OUTPUT).hex
	$(READELF) -s $^

.PHONY: sections
sections: $(OUTPUT).hex
	$(READELF) -S $^

.PHONY: foo
foo: $(OBJS)
	@echo $^
	@echo $@

	