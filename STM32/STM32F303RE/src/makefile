ROOT   = ../..
CC_DIR = $(ROOT)/toolchain/gcc-arm-none-eabi-10-2020-q4-major
#CC     = $(CC_DIR)/bin/arm-none-eabi-gcc
CC = arm-none-eabi-gcc

CFLAGS += -mcpu=cortex-m4 -mthumb -Og -fmessage-length=0 \
		  -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -flto -fno-move-loop-invariants 
		 
CFLAGS += -Wstrict-prototypes -Wuninitialized -Wall -Wextra -Wmissing-declarations \
		  -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -Wmissing-prototypes  \
		  -Wbad-function-cast

#CFLAGS += -Wunused -Werror -Wpadded -Wconversion 

CFLAGS += $(foreach file,$(INC),-I"$(file)")

INC = \
./inc

SRC += \
./src/ADC.c \
./src/GPIO.c \
./src/I2C.c \
./src/I2S.c \
./src/RCC.c \
./src/SPI.c 

BUILD_DIR = ./out
TARGETS  += $(foreach file, $(SRC),$(notdir $(file)))
OBJS      = $(foreach file, $(TARGETS),$(BUILD_DIR)/$(file:%.c=%.o))

DEPS += \
./src/ADC.d \
./src/GPIO.d \
./src/I2C.d \
./src/I2S.d \
./src/RCC.d \
./src/SPI.d 

all: $(BUILD_DIR) $(OBJS)

# Each subdirectory must supply rules for building sources it contributes
$(BUILD_DIR)/%.o: ./src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	$(CC) $(CFLAGS) $(CWARN) $(CINC) -c "$<" -o "$@" 
	@echo 'Finished building: $<'
	@echo ' '

$(BUILD_DIR):
	@echo 'Creating build directory'
	@mkdir -p $(BUILD_DIR)
	@echo '$(BUILD_DIR) created'
	@echo ' '

clean:
	rm -f ./out/*.o

foo:
	@echo $(OBJS)

	