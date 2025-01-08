## Cross-compilation commands 
CC      = arm-none-eabi-gcc
LD      = arm-none-eabi-gcc
AS      = arm-none-eabi-as
OBJCOPY = arm-none-eabi-objcopy
SIZE    = arm-none-eabi-size

LINKERSCRIPT	= LinkerScript
#STARTUP			= startup_stm32f407vgtx
STARTUP			= startup

INCDIR	= -I../inc
INCDIR	+= -I../../CMSIS/Core/Include
INCDIR	+= -I../hw/inc

LDDIR	= -T../${LINKERSCRIPT}.ld

## Platform and optimization options
CFLAGS	= -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F407xx 
CFLAGS	+= -DDEBUG -DSTM32F407xx -DUSE_STDPERIPH_DRIVER -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP
CFLAGS	+= $(INCDIR)

LFLAGS	= -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 ${LDDIR} -Wl,-Map=out.map -Wl,--gc-sections -lm -specs=nano.specs -specs=nosys.specs

SRCDIR	= ../hw/src
VPATH	= $(SRCDIR) ..

SRCS	= $(foreach dir, .. $(SRCDIR) , $(wildcard $(dir)/*.c))
SRCS	:= $(notdir $(SRCS))

OBJS	= $(SRCS:.c=.o)
OBJS	+= ${STARTUP}.o		# Startup file (.s)

## Rules
all: out.elf out.bin size 
	mv *.elf *.bin ../bin

out.elf: $(OBJS) LinkerScript.ld
	$(LD) $(LFLAGS) $(INCDIR) -o out.elf $(OBJS)

%o: %c
	$(CC) $(CFLAGS) -c $< -o $@

out.bin: out.elf
	$(OBJCOPY) -O binary "out.elf" "out.bin"

size: out.elf
	$(SIZE) $< 

clean:
	rm *.o *.d *.map depend
	rm ../bin/*

depend: $(SRCS)
	$(CC) -M $(CFLAGS) $^ > $@

-include depend
