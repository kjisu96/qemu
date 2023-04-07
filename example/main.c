#include "STM32FDiscovery.h"
#include <stdio.h>

void clk(void)
{
	RCC_CR = 0;
	RCC_PLLCFGR = 0;
	RCC_CFGR = 0;
		
	RCC_CR |= (1<<16); // HSE set
	while( (RCC_CR & ( 1<<17) ) == 0 ); // wait until HSE ready
	
	RCC_PLLCFGR |= 8;//0x00000008; // set PLLM
	RCC_PLLCFGR |= (336<<6);//|= (336<<6); // 		set PLLN
	RCC_PLLCFGR |= (0<<16); // set PLLP
	RCC_PLLCFGR |= (7<<24);//0x07000000; // set PLLQ

	RCC_PLLCFGR |= (1<<22); // set PLL src HSE

	RCC_CR |= (1<<24); // PLL ON
	while( (RCC_CR & (1<<25)) == 0); // wait until PLL ready
	
	FLASH_ACR |= 5;
	RCC_CFGR |= 2; // set PLL to system clock
		
	while( (RCC_CFGR & (12) ) != 8); // wait until PLL ready
	
	RCC_CFGR |= (1<<12) | (1<<10); // set APB1 div 4
	RCC_CFGR |= (1<<15); // set APB2 div2	    
}

void EXTI0_IRQHandler() {
    GPIOD_ODR ^= 1 << 13;
    GPIOD_ODR ^= 1 << 14;
    GPIOD_ODR ^= 1 << 15;

    EXTI_PR |= 1<<0;    // clear pending bit for EXTI0
}

void ADC1_IRQHandler(void) {
	    GPIOD_ODR ^= 1<<15 | 1<<14 | 1<<13 | 1<<12;    
    /*
    value = ADC1_DR & 0xFFF;
    DAC_DHR12R1 = value;
    ADC1_CR2 |= 1<<30;                  // [SWSTART] start conversion
    */
}

void set_adc1() {
    RCC_AHB1ENR |= 0x00000001;                      // RCC clock enable register
    GPIOA_MODER |= 3<<0;                            // PA0 Analog mode
    RCC_APB2ENR |= 1<<8;                            // ADC1 clock enable
	RCC_CFGR |= 1<<15 | 1<<13;                      // set APB2 div4 = 42 MHz	

    ADC1_CR2 |= 1<<0;                               // Enable ADC1, single conversion mode
    ADC1_SMPR2 |= 3<<0;                             // channel 0 sampling cycle 56 cycles
    ADC1_CR1 |= 0<<24 | 1<<5;                       // [RES] 12-bit resolution, [EOCIE] End-Of-Conversion interrupt enable
    ADC1_CCR |= 1<<16;                              // [ADCPRE] PCLK2 div 4
    ADC1_SQR1 |= 0;                                 // [L] num. of conv. : 1
    ADC1_SQR3 |= 0;                                 // [SQ1] 1st conversion : channel 0

    ADC1_CR2 |= 1<<30;                  // [SWSTART] start conversion
	NVIC_ISER0 |= (1<<18);    // enable interrupts
}

int main (void) {
    int value;

	clk();
	
	//RCC_CFGR |= 0x04600000;
	RCC_AHB1ENR |= 0x00000001; //RCC clock enable register	
	
	/* PORT A */  
	GPIOA_MODER |= 3<<8;                            // PA4 Analog mode

    /* button intr set */
    SYSCFG_EXTICR1  |= 0<<0; // EXTI0 connect to PA0
    EXTI_IMR        |= 1<<0; // Mask EXTI0
    EXTI_RTSR       |= 1<<0; // rising edge trigger enable
    EXTI_FTSR       |= 0<<0; // falling edge trigger disable
    NVIC_ISER0      |= 1<<6; // enable EXTI0 interrupt

    /* PORT D */
    RCC_AHB1ENR  |= 1<<3;		                    // PORTD enable
    GPIOD_MODER  |= 1<<24 | 1<<26 | 1<<28 | 1<<30;	// PD12,PD13,PD14,PD15 general output mode
    GPIOD_OTYPER |= 0x00000000;                     // output push-pull
    GPIOD_PUPDR	 |= 0x00000000;                     // no pull-up, pull-down

    //set_adc1();
    
    while(1) {
        ADC1_SR = 0;
        ADC1_CR2 |= 1<<30;                  // [SWSTART] start conversion
//        while( !(ADC1_SR & 0x00000002) );   // [EOC] end of conversion
        value = ADC1_DR & 0xFFF;
    }
}

