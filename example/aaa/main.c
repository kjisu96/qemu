#include "STM32FDiscovery.h"

#define SENDNUM 423

char rec;
unsigned int uart_data[423]= {
32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 
32, 95, 95, 95, 95, 95, 32, 32, 32, 32, 
32, 32, 95, 95, 95, 95, 95, 32, 95, 95, 
95, 32, 32, 32, 32, 32, 32, 32, 32, 95, 
95, 95, 95, 95, 32, 32, 32, 95, 32, 32, 
32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 
32, 32, 32, 95, 95, 95, 95, 32, 32, 10, 
32, 32, 32, 32, 32, 47, 92, 32, 32, 32, 
124, 95, 32, 32, 32, 95, 124, 32, 32, 32, 
32, 47, 32, 95, 95, 95, 95, 124, 95, 95, 
32, 92, 32, 32, 32, 32, 32, 32, 47, 32,
95, 95, 95, 95, 124, 32, 124, 32, 124, 32, 
32, 32, 32, 32, 32, 32, 32, 47, 92, 32,
32, 32, 124, 32, 32, 95, 32, 92, 32, 10, 
32, 32, 32, 32, 47, 32, 32, 92, 32, 32,
32, 32, 124, 32, 124, 95, 95, 95, 95, 95,
124, 32, 40, 95, 95, 95, 32, 32, 32, 32,
41, 32, 124, 95, 95, 95, 32, 124, 32, 124, 
32, 32, 32, 32, 32, 32, 124, 32, 124, 32, 
32, 32, 32, 32, 32, 32, 47, 32, 32, 92, 
32, 32, 124, 32, 124, 95, 41, 32, 124, 10, 
32, 32, 32, 47, 32, 47, 92, 32, 92, 32, 
32, 32, 124, 32, 124, 95, 95, 95, 95, 95,
95, 92, 95, 95, 95, 32, 92, 32, 32, 47, 
32, 47, 47, 32, 95, 32, 92, 124, 32, 124, 
32, 32, 32, 32, 32, 32, 124, 32, 124, 32, 
32, 32, 32, 32, 32, 47, 32, 47, 92, 32, 
92, 32, 124, 32, 32, 95, 32, 60, 32, 10, 
32, 32, 47, 32, 95, 95, 95, 95, 32, 92, 
32, 95, 124, 32, 124, 95, 32, 32, 32, 32, 
32, 95, 95, 95, 95, 41, 32, 124, 47, 32, 
47, 124, 32, 40, 95, 41, 32, 124, 32, 124, 
95, 95, 95, 95, 32, 32, 124, 32, 124, 95, 
95, 95, 95, 32, 47, 32, 95, 95, 95, 95, 
32, 92, 124, 32, 124, 95, 41, 32, 124, 10, 
32, 47, 95, 47, 32, 32, 32, 32, 92, 95, 
92, 95, 95, 95, 95, 95, 124, 32, 32, 32, 
124, 95, 95, 95, 95, 95, 47, 124, 95, 95, 
95, 95, 92, 95, 95, 95, 47, 32, 92, 95, 
95, 95, 95, 95, 124, 32, 124, 95, 95, 95, 
95, 95, 95, 47, 95, 47, 32, 32, 32, 32, 
92, 95, 92, 95, 95, 95, 95, 47, 32, 10,
10, 10, 10};

void clk(void)
{
	RCC_CR = 0;
	RCC_PLLCFGR = 0;
	RCC_CFGR = 0;
		
	RCC_CR |= (1<<16);                      // HSE set
	while( (RCC_CR & ( 1<<17) ) == 0 );     // wait until HSE ready
	
	RCC_PLLCFGR |= 8;                       //0x00000008; // set PLLM
	RCC_PLLCFGR |= (336<<6);                //|= (336<<6); // 		set PLLN
	RCC_PLLCFGR |= (0<<16);                 // set PLLP
	RCC_PLLCFGR |= (7<<24);                 //0x07000000; // set PLLQ

	RCC_PLLCFGR |= (1<<22);                 // set PLL src HSE

	RCC_CR |= (1<<24);                      // PLL ON
	while( (RCC_CR & (1<<25)) == 0);        // wait until PLL ready
	
	FLASH_ACR |= 5;
	RCC_CFGR |= 2;                          // set PLL to system clock
		
	while( (RCC_CFGR & (12) ) != 8);        // wait until PLL ready
	
	RCC_CFGR |= (1<<12) | (1<<10);          // set APB1 div 4
	RCC_CFGR |= (1<<15);                    // set APB2 div2	
}

void set_usart2() {
    // USART port set PA2, PA3
    RCC_AHB1ENR     |= 0x00000001;          // PORTA GPIO clock enable
    GPIOA_MODER     |= (1<<5) | (1<<7);     // A2 AF set, A3 AF set
    GPIOA_AFRL      |= (7<<8) | (7<<12);    // AF7

    // Set USART2
   	RCC_APB1ENR     |= (1<<17);             // [USART2 EN] usart2 clk enable
	USART2_CR1      |= (0<<12);             // word length 0-> 1start 8data nstop
	USART2_CR2      |= (0<<13) | (0<<12);   // 1 stop bit

	USART2_BRR       = (unsigned int)(42000000/115200);
    //364;//0x016C;//0x0000016C; // set baud rate;
    // 115200 bps // APB1 div 4 (168 MHz / 4 = 42 MHz)
    
	USART2_CR1      |= (1<<3) | (1<<2);     // set transmitter, receiver enable
	USART2_CR1      |= (1<<5);              // RXNE (RX Not Empty) interrupt enable
	USART2_CR1      |= (1<<13);             // set UE(usart enable) bit	

    NVIC_ISER1      |= 1<<6;                // enable USART2 interrupt
}

void USART2_IRQHandler() {
    // reception interrupt check
    if( USART2_SR & (1<<5) ) {
        rec = USART2_DR;
	    GPIOD_ODR ^= 1<<12;

        // LOOPBACK
        USART2_DR = rec;
        while( !(USART2_SR &(1<<7)) );      // Transmit data register empty?
        while( !(USART2_SR &(1<<6)) );      // Transmission complete?

        USART2_CR1 |= (1<<5);               // Enable RXNE interrupt
    }
}

void EXTI0_IRQHandler() {
    GPIOD_ODR ^= 1 << 13;
    GPIOD_ODR ^= 1 << 14;
    GPIOD_ODR ^= 1 << 15;

    EXTI_PR |= 1<<0;    // clear pending bit for EXTI0
}

int main (void)
{
    unsigned int count = 0;

	clk();
	
	RCC_CFGR |= 0x04600000;

    /* PORT A */
	RCC_AHB1ENR  |= 1<<0; // RCC clock enable register	
    GPIOA_MODER  |= 0<<0; // input mode
    GPIOA_OTYPER |= 0<<0; // output push-pull
    GPIOA_PUPDR  |= 0<<0; // no pull-up, pull-down

    /* button intr set */
    SYSCFG_EXTICR1  |= 0<<0; // EXTI0 connect to PA0
    EXTI_IMR        |= 1<<0; // Mask EXTI0
    EXTI_RTSR       |= 1<<0; // rising edge trigger enable
    EXTI_FTSR       |= 0<<0; // falling edge trigger disable
    NVIC_ISER0      |= 1<<6; // enable EXTI0 interrupt
	
	/* PORT D */
	RCC_AHB1ENR  |= 1<<3;		// PORTD enable
	GPIOD_MODER  |= 1<<24;		// PORTD 12 general output mode
	GPIOD_MODER  |= 1<<26;		// PORTD 13 general output mode
	GPIOD_MODER  |= 1<<28;		// PORTD 14 general output mode
	GPIOD_MODER  |= 1<<30;		// PORTD 15 general output mode
	GPIOD_OTYPER |= 0x00000000;
	GPIOD_PUPDR	 |= 0x00000000;

    set_usart2();
	
    while( count < SENDNUM ) {
        USART2_DR = uart_data[count++];
        while( !(USART2_SR &(1<<7)) );      // Transmit data register empty?
        while( !(USART2_SR &(1<<6)) );      // Transmission complete?
    }

	GPIOD_ODR |= 1<<12;

	while(1) {

	}
}
