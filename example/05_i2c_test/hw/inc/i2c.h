#include "stm32f407xx.h"

void set_i2c1();

void __i2c_start();
void __i2c_stop();

void i2c_write(uint8_t DeviceAddr, uint8_t regaddr, uint8_t data);
uint8_t i2c_read(uint8_t DeviceAddr, uint8_t regaddr);
