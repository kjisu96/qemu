#!/bin/bash

gdb /home/jskwon/Work/qemu-arm-dev/linux-x64/install/qemu-arm/bin/qemu-system-gnuarmeclipse \
	-ex "b gpio.c:2804" \
	-ex "run -cpu cortex-m4 -machine STM32F4-Discovery --gdb tcp::3333 --image ./out.elf --verbose --verbose" 



#    -ex "target remote :3333" \
#    -s "./bin/out.elf" \
#	-ex "load" \
#	-ex "b main.c:80" \
#	-ex "set arc arm" \
#    -ex "monitor system_reset" \
#    -ex "continue" \
#    -ex "dashboard memory watch 0x40005400 128" \
#    -ex "dashboard memory watch 0x40004400 128" \
#    -ex "dashboard memory watch 0x40012000 128" 
