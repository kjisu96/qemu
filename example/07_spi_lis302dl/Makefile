## Cross-compilation commands 
CC      = arm-none-eabi-gcc
LD      = arm-none-eabi-gcc
AS      = arm-none-eabi-as
OBJCOPY = arm-none-eabi-objcopy
SIZE    = arm-none-eabi-size

LINKERSCRIPT	= LinkerScript
STARTUP			= startup

INCDIR	= -I./inc
INCDIR	+= -I../CMSIS_5/CMSIS/Core/Include

LDDIR	= -T./${LINKERSCRIPT}.ld

## Platform and optimization options
CFLAGS	= -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F407xx 
CFLAGS	+= -DDEBUG -DSTM32F407xx -DUSE_STDPERIPH_DRIVER -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP
CFLAGS	+= $(INCDIR)

LFLAGS	= -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 ${LDDIR} -Wl,-Map=out.map -Wl,--gc-sections -lm -specs=nano.specs -specs=nosys.specs

SRCDIR	= .
VPATH	= $(SRCDIR) 

SRCS	= $(foreach dir, .. $(SRCDIR) , $(wildcard $(dir)/*.c))
SRCS	:= $(notdir $(SRCS))

OBJS	= $(SRCS:.c=.o)
OBJS	+= ${STARTUP}.o		# Startup file (.s)


QEMU_DIR=/home/jskwon/Work/qemu-arm-dev/linux-x64/install/qemu-arm/bin

## Rules
all: out.elf out.bin size 

out.elf: $(OBJS) LinkerScript.ld
	$(LD) $(LFLAGS) -o out.elf $(OBJS)

out.bin: out.elf
	$(OBJCOPY) -O binary "out.elf" "out.bin"

size: out.elf
	$(SIZE) $< 

qemu: 
	$(QEMU_DIR)/qemu-system-gnuarmeclipse \
		-cpu cortex-m4 -machine STM32F4-Discovery \
		--gdb tcp::3333 --image out.elf \
		--verbose --verbose #-nographic

gdb:
	./run_gdb.sh

clean:
	rm *.o *.d *.elf *.bin *.map
