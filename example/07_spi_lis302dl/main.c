#include <stdio.h>
#include <string.h>

#include "stm32f407xx.h"
#include "lis302dl.h"

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

/*
 * write spi function customized for lis302dl
 */
void spi_write(uint8_t reg, uint8_t data)
{
    GPIOE->ODR &= ~(1U << 3); // enable
    // bit 15 is 0 for write for lis302dl
    uint32_t frame = 0;
    frame = data;
    frame |= (uint16_t)(reg << 8);
    // Send data
    SPI1->DR = frame;
    // wait until transmit is done (TXE flag)
    while (!(SPI1->SR & (1 << 1)));
    // wait until rx buf is not empty (RXNE flag)
    while (!(SPI1->SR & (1 << 0)));

    GPIOE->ODR |= (1 << 3); // disable
    (void)SPI1->DR; // dummy read
}

/*
 * read spi function customized for lis302dl
 */
uint8_t spi_read(uint8_t reg)
{
    GPIOE->ODR &= ~(1U << 3); // enable
    // bit 15 is 1 for read for lis302dl
    uint16_t frame = 0;
    frame |= (uint16_t)(reg << 8);
    frame |= (1 << 15); // read bit
    // Send data
    SPI1->DR = frame;
    // wait until tx buf is empty (TXE flag)
    while (!(SPI1->SR & (1 << 1)));
    // wait until rx buf is not empty (RXNE flag)
    while (!(SPI1->SR & (1 << 0)));

    uint8_t b = (uint8_t)SPI1->DR;
    GPIOE->ODR |= (1 << 3); // disable
    return b;
}

void spi_init(void) {
        // enable GPIOA clock, bit 0 on AHB1ENR
    RCC->AHB1ENR |= (1 << 0);
    // enable SPI1 clock, bit 12 on APB2ENR
    RCC->APB2ENR |= (1 << 12);

    // set pin modes as alternate mode
    GPIOA->MODER &= 0xFFFF03FF; // Reset bits 10-15 to clear old values
    GPIOA->MODER |= 0x0000A800; // Set pin 5/6/7 to alternate func. mode (0b10)

    // set pin modes as very high speed
    GPIOA->OSPEEDR |= 0x0000FC00; // Set pin 5/6/7 to very high speed mode (0b11)

    // choose AF5 for SPI1 in Alternate Function registers
    GPIOA->AFR[0] |= (0x5 << 20); // for pin 5
    GPIOA->AFR[0] |= (0x5 << 24); // for pin 6
    GPIOA->AFR[0] |= (0x5 << 28); // for pin 7

    // Disable SPI1 and set the rest (no OR'ing)

    // baud rate - BR[2:0] is bit 5:3
    // fPCLK/2 is selected by default
    SPI1->CR1 = (0x4 << 3); // set baud rate to fPCLK/32

    // 8/16-bit mode - DFF is bit 11
    SPI1->CR1 |= (1 << 11); // 1 - 16-bit mode

    // motion sensor expects clk to be high and
    //  transmission happens on the falling edge
    // clock polarity - CPOL bit 1
    SPI1->CR1 |= (0 << 1); // clk goes 1 when idle
    // clock phase - CPHA bit 0
    SPI1->CR1 |= (0 << 0); // first clock transaction

    // frameformat - LSBFIRST bit 7, msb/lsb transmit first
    // 0 - MSB transmitted first
    //SPI1->CR1 |= (0 << 7); // 1 - LSB transmitted first

    // frame format - FRF bit 4 on CR2
    // 0 - Motorola mode, 1 - TI mode
    //   TI Mode autosets a lot of things
    //   so do not enable it, unless that is what you want
    //SPI1->CR2 |= (1 << 4); // 1 - SPI TI mode

    // software slave management - SSM bit 9
    SPI1->CR1 |= (1 << 9); // 1- ssm enabled
    // internal slave select - SSI bit 8
    SPI1->CR1 |= (1 << 8); // set ssi to 1

    // master config - MSTR bit 2
    SPI1->CR1 |= (1 << 2); // 1 - master mode

    // enable SPI - SPE bit 6
    SPI1->CR1 |= (1 << 6);
}

int main (void) {

    int16_t rbuf[3];

	clk();
	
	//RCC->CFGR   |= 0x04600000;
	RCC->AHB1ENR  |= 0x00000001; //RCC clock enable register	

	/* PORT D (LED) */
	RCC->AHB1ENR  |= 1<<3;		    // PORTD GPIO clock enable
	GPIOD->MODER  |= 1<<24 | 1<<26 | 1<<28 | 1<<30;	// PD12,PD13 general output mode

    GPIOD->ODR |= 1<<12; 
    GPIOD->ODR |= 1<<13; 
    GPIOD->ODR |= 1<<14; 
    GPIOD->ODR |= 1<<15; 

    spi_init();

    // reboot memory
    spi_write(LIS302_REG_CTRL_REG2, 0x40);
    // active mode, +/-2g
    spi_write(LIS302_REG_CTRL_REG1, 0x47);
    // wait
//    for(int i=0; i<10000000; i++);
    // read who am i
    rbuf[0] = (int8_t)spi_read(LIS302_REG_WHO_AM_I);

    while(1) {
        rbuf[0] = (int8_t)spi_read(LIS302_REG_OUT_X);
        rbuf[1] = (int8_t)spi_read(LIS302_REG_OUT_Y);
        rbuf[2] = (int8_t)spi_read(LIS302_REG_OUT_Z);

        if (rbuf[0] > 16) {
            GPIOD->ODR &= (uint16_t)~0x2000;
            GPIOD->ODR |= 0x8000;
        } else if (rbuf[0] < -16 ) {
            GPIOD->ODR &= (uint16_t)~0x8000;
            GPIOD->ODR |= 0x2000;
        } else {
            GPIOD->ODR &= (uint16_t)~0xA000;
        }

        if (rbuf[1] > 16) {
            GPIOD->ODR &= (uint16_t)~0x1000;
            GPIOD->ODR |= 0x4000;
        } else if (rbuf[1] < -16 ) {
            GPIOD->ODR &= (uint16_t)~0x4000;
            GPIOD->ODR |= 0x1000;
        } else {
            GPIOD->ODR &= (uint16_t)~0x5000;
        }

//        for(int i=0; i<10000; i++);
    }

    return 0;
}
