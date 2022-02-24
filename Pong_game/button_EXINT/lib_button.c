#include "button.h"
#include "lpc17xx.h"

/**
 *  Function that initializes Buttons
 */
void BUTTON_init(void) {  
  LPC_GPIO2->FIODIR      &= ~(1 << 10);    /* PORT2.10 defined as input          */

  LPC_GPIO2->FIODIR      &= ~(1 << 11);    /* PORT2.11 defined as input          */
  
  LPC_GPIO2->FIODIR      &= ~(1 << 12);    /* PORT2.12 defined as input          */

  LPC_SC->EXTMODE = 0x7;

}

void enable_INT0(){
	LPC_PINCON->PINSEL4    |= (1 << 20);		 /* External interrupt 0 pin selection */
	NVIC_EnableIRQ(EINT0_IRQn);              /* enable irq in nvic                 */
}

void enable_KEY1(){
	LPC_PINCON->PINSEL4    |= (1 << 22);     /* External interrupt 0 pin selection */	
	NVIC_EnableIRQ(EINT1_IRQn);              /* enable irq in nvic                 */
}

void enable_KEY2(){
	 LPC_PINCON->PINSEL4    |= (1 << 24);     /* External interrupt 0 pin selection */	
   NVIC_EnableIRQ(EINT2_IRQn);              /* enable irq in nvic                 */
}

void disable_INT0(){
	NVIC_DisableIRQ(EINT0_IRQn);							 /* enable Button interrupts			*/
	LPC_PINCON->PINSEL4    &= ~(1 << 20);     /* External interrupt 0 pin selection */	
}

void disable_KEY1(){
	NVIC_DisableIRQ(EINT1_IRQn);							 /* enable Button interrupts			*/
	LPC_PINCON->PINSEL4    &= ~(1 << 22);     /* External interrupt 0 pin selection */	
}

void disable_KEY2(){
	NVIC_DisableIRQ(EINT2_IRQn);							 /* enable Button interrupts			*/
	LPC_PINCON->PINSEL4    &= ~(1 << 24);     /* External interrupt 0 pin selection */	
}

