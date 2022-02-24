/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 T1 T2 and T3 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <string.h>
#include "lpc17xx.h"
#include "timer.h"
#include "../GLCD/GLCD.h" 
#include "../game/game.h"
#include "../GLCD/AsciiLib.h" 
#include "../adc/adc.h"

extern int16_t	pos[];
extern uint8_t paddle_pos;
uint16_t SinTable[45] =                            
{
    410, 467, 523, 576, 627, 673, 714, 749, 778,
    799, 813, 819, 817, 807, 789, 764, 732, 694, 
    650, 602, 550, 495, 438, 381, 324, 270, 217,
    169, 125, 87 , 55 , 30 , 12 , 2  , 0  , 6  ,   
    20 , 41 , 70 , 105, 146, 193, 243, 297, 353
};

/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

void TIMER0_IRQHandler (void)
{

	ADC_start_conversion(); /* conversione potenziometro associato al paddle */

  LPC_TIM0->IR = 1;			/* clear interrupt flag */
  return;
}


/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER1_IRQHandler (void)
{

	moveBall(pos, paddle_pos); /*movimento pallina*/
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}
/******************************************************************************
** Function name:		Timer2_IRQHandler
**
** Descriptions:		Timer/Counter 2 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER2_IRQHandler (void) /* Timer per gestire paddle */
{
	static uint8_t ticks=0;
	/* DAC management */	
	LPC_DAC->DACR = SinTable[ticks]<<6;
	ticks++;
	if(ticks==45){ 
		ticks=0;
		disable_timer(2);
		reset_timer(2);
	}

  LPC_TIM2->IR = 1;			/* clear interrupt flag */
  return;
}
/******************************************************************************
** Function name:		Timer3_IRQHandler
**
** Descriptions:		Timer/Counter 3 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER3_IRQHandler (void)  /* Timer per gestire muri */
{
	static uint8_t ticks=0;
	/* DAC management */	
	LPC_DAC->DACR = SinTable[ticks]<<6;
	ticks++;
	if(ticks==45){ 		
		ticks=0;
		disable_timer(3);
		reset_timer(3);

	}

  LPC_TIM3->IR = 1;			/* clear interrupt flag */
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
