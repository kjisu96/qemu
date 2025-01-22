OBJDIR=./obj
QEMU_DIR=/home/jskwon/Work/qemu-arm-dev/linux-x64/install/qemu-arm/bin
OUT_DIR=./bin

all:
	cd $(OBJDIR) && make

clean:
	cd $(OBJDIR) && make clean

depend:
	cd $(OBJDIR) && make depend

qemu: 
	$(QEMU_DIR)/qemu-system-gnuarmeclipse \
		-cpu cortex-m4 -machine STM32F4-Discovery \
		--gdb tcp::3333 --image $(OUT_DIR)/out.elf \
		--verbose --verbose #-nographic

gdb_qemu:
	./run_gdb_qemu.sh

gdb_elf:
	./run_gdb.sh
