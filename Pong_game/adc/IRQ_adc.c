	/*********************************************************************************************************
	**--------------File Info---------------------------------------------------------------------------------
	** File name:           IRQ_adc.c
	** Last modified Date:  20184-12-30
	** Last Version:        V1.00
	** Descriptions:        functions to manage A/D interrupts
	** Correlated files:    adc.h
	**--------------------------------------------------------------------------------------------------------       
	*********************************************************************************************************/

	#include "lpc17xx.h"
	#include "adc.h"
	#include "../GLCD/GLCD.h"
	#include "../game/game.h"
	
	/*----------------------------------------------------------------------------
	A/D IRQ: Executed when A/D Conversion is ready (signal from ADC peripheral)
	*----------------------------------------------------------------------------*/

	unsigned short AD_current;   
	unsigned short AD_last = 0xFF;     /* Last converted value               */
	volatile uint8_t paddle_pos;             /*variabile per tracciare il paddle   */

	void ADC_IRQHandler(void) {
	static uint8_t first = 0;	
	AD_current = ((LPC_ADC->ADGDR>>4) & 0xFFF);/* Read Conversion Result             */

	if( AD_current != AD_last){
		
		paddle_pos = AD_current * 240/4096; 
		
		// solo se prima volta che disegno il paddle 
		if( first==0  &&(paddle_pos > 25 && paddle_pos < 215)){ 
			
			drawPaddle( AD_current * 240/4096);
			first++;
			AD_last = AD_current;
		} 
		//prima condizione per stoppare la draw del paddle quando tocca il muro 
		//seconda condizione per non fare la draw ogni volta che viene campionato un nuovo valore di AD_current
		//disegno solo quando il cambiamento è signficativo e dato dall'user 
		if (paddle_pos > 25 && paddle_pos < 215 && (AD_current <= AD_last-200 || AD_current >= AD_last+200)){
		
				clearPaddle(AD_last * 240/4096);
				drawPaddle(AD_current * 240/4096);
			
			
			AD_last = AD_current;
			
		}else { 
		
			 /*non disegna niente*/
		 }
	}	

}
