/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:           Pong game developed at Politecnico di Torino by Angela D'Antonio (s281657)
**
**--------------------------------------------------------------------------------------------------------
 Includes ------------------------------------------------------------------*/
#include "LPC17xx.h"
#include "GLCD/GLCD.h" 
#include "timer/timer.h"
#include "game/game.h"
#include "adc/adc.h"
#include "RIT/RIT.h"
#include "button_EXINT/button.h"
#include <stdio.h>
#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif

int main(void)
{
  SystemInit();  												/* System Initialization (i.e., PLL)  */
	
  LCD_Initialization();
	LCD_Clear(Black);
	GUI_Text(40, 125, (uint8_t *)"Press KEY1 to start", White, Black);
	GUI_Text(90, 300,(uint8_t *)"Pong Game",White,Black);

	BUTTON_init();
	enable_KEY1();												/*abilito key1 per iniziare gioco*/
	
	init_RIT(0x004C4B40);									/* RIT Initialization 50 ms */

										
	
																				/* K = T*Fr = [s]*[Hz] = [s]*[1/s]	  */
																				/* Fr=25MHZ             							*/
	init_timer(0,0x00BEBC20); 					  /* Init timer 0 paddle T = 1/2 sec */
	init_timer(1,0x001312D0);						  /* init timer 1 pallina T = 50 ms */
																				
																				/* k=1/f'*f/n  k=f/(f'*n) k=25MHz/(f'*45) */
	init_timer(2,0x00006EBE); 						/* 1890*15 = 0x00012750  294Hz	k=1890 timer per suono paddle */
	init_timer(3,0x000041EB); 						/* 1125*15 = 0x0000AFC8 494Hz	k=1125 timer per suono muro */

	ADC_init();

	initBall();

	LPC_SC->PCON |= 0x1;									/* power-down	mode										*/
	LPC_SC->PCON &= ~(0x2);	


	LPC_PINCON->PINSEL1 |= (1<<21);   		/*loudspeaker */
	LPC_PINCON->PINSEL1 &= ~(1<<20);
	LPC_GPIO0->FIODIR |= (1<<26);
	
  while (1)	
  {
		__ASM("wfi");
  }
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
