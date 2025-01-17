#!/bin/bash

# I2C1      -> 0x4000 5400
# USART2    -> 0x4000 4400
# ADC1      -> 0x4001 2000

gdb-multiarch \
    -ex "target remote :3333" \
    -s "./bin/out.elf" \
	-ex "load" \
	-ex "b main.c:48" \
	-ex "b main.c:55" \
	-ex "set arc arm" \
    -ex "monitor system_reset" \
    -ex "continue" \
    -ex "dashboard memory watch 0x40005400 128" \
    -ex "dashboard memory watch 0x40004400 128" \
    -ex "dashboard memory watch 0x40012000 128" 
