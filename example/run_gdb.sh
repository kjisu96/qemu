#!/bin/bash

gdb-multiarch \
	-ex "target remote :3333" \
	-s "out.elf" \
	-ex "load" \
	-ex "b main" \
	-ex "set arc arm" \
    -ex "monitor system_reset" \
    -ex "continue" \
    -ex "dashboard memory watch 0x40023800 32" \
    -ex "dashboard memory watch 0x40020c00 32" \
    -ex "dashboard memory watch 0x40012000 128"
