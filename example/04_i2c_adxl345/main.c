//#include "STM32FDiscovery.h"
//#include "stm32f407xx.h"
#include "hw/hw.h"
#include <stdio.h>
#include <string.h>

#define SENDNUM 423

volatile uint8_t DeviceAddr = 0x1DU ;

void clk(void)
{
	RCC->CR = 0;
	RCC->PLLCFGR = 0;
	RCC->CFGR = 0;
		
	RCC->CR |= (1<<16);                      // HSE set
	while( (RCC->CR & ( 1<<17) ) == 0 );     // wait until HSE ready
	
	RCC->PLLCFGR |= 8;                       //0x00000008; // set PLLM
	RCC->PLLCFGR |= (336<<6);                //|= (336<<6); // 		set PLLN
	RCC->PLLCFGR |= (0<<16);                 // set PLLP
	RCC->PLLCFGR |= (7<<24);                 //0x07000000; // set PLLQ

	RCC->PLLCFGR |= (1<<22);                 // set PLL src HSE

	FLASH->ACR |= 5;
	RCC->CR |= (1<<24);                      // PLL ON
	while( (RCC->CR & (1<<25)) == 0);        // wait until PLL ready
	
	RCC->CFGR |= 2;                          // set PLL to system clock
		
	while( (RCC->CFGR & (12) ) != 8);        // wait until PLL ready
	
	RCC->CFGR |= (1<<12) | (1<<10);          // set APB1 div 4
}   // 168 MHz


void I2C1_ER_IRQHandler(){
    // error handler
}

/*
void I2C1_EV_IRQHandler() {
    // event handler
    GPIOD->ODR ^= (1 << 14); // red LED
}
*/

int main (void) {
    unsigned int count = 0, index = 0;

    uint8_t x_low = 0, x_high = 0;
    uint8_t y_low = 0, y_high = 0;
    uint8_t z_low = 0, z_high = 0;
    int16_t x, y, z;

    char buf[100];

	clk();
	
	//RCC->CFGR   |= 0x04600000;
	RCC->AHB1ENR  |= 0x00000001; //RCC clock enable register	

	/* PORT D (LED) */
	RCC->AHB1ENR  |= 1<<3;		    // PORTD GPIO clock enable
	GPIOD->MODER  |= 1<<24 | 1<<26 | 1<<28 | 1<<30;	// PD12,PD13 general output mode
	GPIOD->OTYPER |= 0x00000000;     // output push-pull
	GPIOD->PUPDR  |= 0x00000000;     // no pull-up, pull-down

    set_i2c1();
    set_usart2();

    while( count < SENDNUM ) {
        USART2->DR = uart_data[count++];
        while( !(USART2->SR &(1<<7)) );      // Transmit data register empty?
        while( !(USART2->SR &(1<<6)) );      // Transmission complete?
    }

    GPIOD->ODR |= 1<<12; 
    GPIOD->ODR |= 1<<13; 
    GPIOD->ODR |= 1<<14; 
    GPIOD->ODR |= 1<<15; 

    /*******************
      ***   SET UP   ***
      ***   SENSOR   ***
     *******************/

    // FifoControl Register
    i2c_write(DeviceAddr, 0x38, 0x80);

    /*
    1. Set power mode and data transfer rate
       Output Data Rate |   Bandwidth | Rate Core (bin)
       3200             |   1600      | 1111
       1600             |   800       | 1110
       800              |   400       | 1101
       400              |   200       | 1100
       200              |   100       | 1011
       100              |   50        | 1010
       50               |   25        | 1001
       25               |   12.5      | 1000
       ...
       */
    i2c_write(DeviceAddr, 0x2C, 0x08);

    /*
    2. Set the data format
       # of bit |   Set?
       -----------------------------------
       [7]      |   SELF_TEST enable
       [6]      |   3-wire SPI mode enable
       [5]      |   interrupt active low
       [4]      |   0
       [3]      |   full resolution mode
       [2]      |   left-jistified (MSB) mode
       [1:0]    |   g range (00 - 2g
                             01 - 4g
                             10 - 8g
                             11 - 16g)
       -----------------------------------
       */
    i2c_write(DeviceAddr, 0x31, 0x03);

    /*
    3. Activation mode
       # of bit |   Set?
       -----------------------------------
       [7]      |   0
       [6]      |   0
       [5]      |   activity and inactivity function serially linked
       [4]      |   auto-sleep enable
       [3]      |   measurement mode <-> standby mode
       [2]      |   sleep mode <-> normal mode
       [1:0]    |   wake-up (00 - 8 Hz
                             01 - 4 Hz
                             10 - 2 Hz
                             11 - 1 Hz)
       -----------------------------------
       */
    i2c_write(DeviceAddr, 0x2D, 0x08);

    /* 4. X, Y, Z Offsets */

    // X
    //i2c_write(DeviceAddr, 0x1E, 0xFD);
    // Y
    //i2c_write(DeviceAddr, 0x1F, 0x03);
    // Z
    //i2c_write(DeviceAddr, 0x20, 0xFE);

    while(1) {
/*        
        index++;

//        sprintf(buf, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",
//                i2c_read(DeviceAddr, 0x1D),
//                i2c_read(DeviceAddr, 0x1E),
//                i2c_read(DeviceAddr, 0x1F),
//                i2c_read(DeviceAddr, 0x20),
//                i2c_read(DeviceAddr, 0x21),
//                i2c_read(DeviceAddr, 0x22),
//                i2c_read(DeviceAddr, 0x23),
//                i2c_read(DeviceAddr, 0x24),
//                i2c_read(DeviceAddr, 0x25),
//                i2c_read(DeviceAddr, 0x26),
//                i2c_read(DeviceAddr, 0x27),
//                i2c_read(DeviceAddr, 0x28),
//                i2c_read(DeviceAddr, 0x29),
//                i2c_read(DeviceAddr, 0x2A),
//                i2c_read(DeviceAddr, 0x2B),
//                i2c_read(DeviceAddr, 0x2C),
//                i2c_read(DeviceAddr, 0x2D),
//                i2c_read(DeviceAddr, 0x2E),
//                i2c_read(DeviceAddr, 0x2F),
//                i2c_read(DeviceAddr, 0x30),
//                i2c_read(DeviceAddr, 0x31));
//
//        for(int i = 0; i < (int)strlen(buf); i++) {
//            USART2->DR = buf[i];
//            while( !(USART2->SR &(1<<7)) );      // Transmit data register empty?
//            while( !(USART2->SR &(1<<6)) );      // Transmission complete?
//        }




        x_low  = i2c_read(DeviceAddr, 0x32);
        x_high = i2c_read(DeviceAddr, 0x33);
        y_low  = i2c_read(DeviceAddr, 0x34);
        y_high = i2c_read(DeviceAddr, 0x35);
        z_low  = i2c_read(DeviceAddr, 0x36);
        z_high = i2c_read(DeviceAddr, 0x37);

        x = (x_high << 8) | x_low;
        y = (y_high << 8) | y_low;
        z = (z_high << 8) | z_low;

        //sprintf(buf, "%d: x_high(%d) x_low(%d) y_high(%d) y_low(%d) z_high(%d) z_low(%d) \n", index, x_high, x_low, y_high, y_low, z_high, z_low);
        sprintf(buf, "%d: x(%d) y(%d) z(%d) \n", index, x, y, z);
        for(int i = 0; i < (int)strlen(buf); i++) {
            USART2->DR = buf[i];
            while( !(USART2->SR &(1<<7)) );      // Transmit data register empty?
            while( !(USART2->SR &(1<<6)) );      // Transmission complete?
        }

        //for(int i = 0; i < 100000; i++) {};
        GPIOD->ODR ^= 1<<13;     // 1 LED ON

*/        
    }

    return 0;
}
