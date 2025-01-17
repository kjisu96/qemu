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


int main (void) {

	clk();
	
	//RCC->CFGR   |= 0x04600000;
	RCC->AHB1ENR  |= 0x00000001; //RCC clock enable register	

	/* PORT D (LED) */
	RCC->AHB1ENR  |= 1<<3;		    // PORTD GPIO clock enable
	GPIOD->MODER  |= 1<<24 | 1<<26 | 1<<28 | 1<<30;	// PD12,PD13 general output mode

    set_i2c1();

    GPIOD->ODR |= 1<<12; 
    GPIOD->ODR |= 1<<13; 
    GPIOD->ODR |= 1<<14; 
    GPIOD->ODR |= 1<<15; 

    i2c_write(DeviceAddr, 0x38, 0x80);

    GPIOD->ODR ^= 1<<12; 
    GPIOD->ODR ^= 1<<13; 
    GPIOD->ODR ^= 1<<14; 
    GPIOD->ODR ^= 1<<15; 

    uint8_t x_low  = i2c_read(DeviceAddr, 0x32);


    while(1) {
    }

    return 0;
}
