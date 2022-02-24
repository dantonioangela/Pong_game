	/*********************************************************************************************************
	**--------------File Info---------------------------------------------------------------------------------
	** File name:           IRQ_RIT.c
	** Last modified Date:  2014-09-25
	** Last Version:        V1.00
	** Descriptions:        functions to manage T0 and T1 interrupts
	** Correlated files:    RIT.h
	**--------------------------------------------------------------------------------------------------------
	*********************************************************************************************************/
	#include "lpc17xx.h"
	#include "RIT.h"
	#include "../button_EXINT/button.h"
	#include "../timer/timer.h"
	#include "../GLCD/GLCD.h"
	#include "../game/game.h"
	/******************************************************************************
	** Function name:		RIT_IRQHandler
	**
	** Descriptions:		REPETITIVE INTERRUPT TIMER handler
	**
	** parameters:			None
	** Returned value:		None
	**
	******************************************************************************/
	volatile uint8_t key1 = 0;
	volatile uint8_t key2 = 0; 
	volatile uint8_t int0 = 0;

	uint8_t walls = 1; 
	int16_t x;
	int16_t y;

	extern uint16_t score;
	extern char text_score[sizeof(score)];
	extern uint16_t record;
	extern char text_record[sizeof(record)];
	extern int16_t pos[];

	//handles INT0 pressure to init the game after Game Over. Only called by RIT IRQHandler

	void INT0_down(void){
		if((LPC_GPIO2->FIOPIN & (1<<10)) == 0){
				int0++;
		} else{//actions performed when released button start game
				 if(int0 >= 1){
					score=0;
					x = pos[0];
					y = pos[1];
					clearBall(x,y);
					clearText();
					initBall();
					walls=0;
			}
			disable_RIT();
			reset_RIT();
			int0 = 0;
		  disable_INT0(); /* INT0 è attivato dopo il game over in game.c*/
		  enable_KEY1(); /* Ri-abilito key1 dopo aver premuto INT0 */
		} 

	}


	//handles key1 pressure to start the game. Only called by RIT IRQHandler
	void KEY1_down(void){
		if((LPC_GPIO2->FIOPIN & (1<<11)) == 0) {	
				 key1++;	
		} else{//actions performed when released button start game
				if(key1 >= 1) { 			
					//parte timer gestione paddle
				 enable_timer(0);
				 clearText();
				
				 //prima partita disegno muri
				 if (walls){
					drawRedWalls();
				 }
				 //stampa score
				 sprintf(text_score, "%d", score);
				 GUI_Text(5, 160,(uint8_t*) text_score, White, Black);
				 //stampa record
				 sprintf(text_record, "%d", record);
				 GUI_Text(210, 10,(uint8_t*) text_record, White, Black);
				 
				 //parte timer pallina
				 enable_timer(1);
				}
				disable_RIT();
				reset_RIT();
				key1 = 0;
				disable_KEY1(); /* key1 sarà riattivato solo dopo il game over e aver premuto int0 */
				enable_KEY2();  /* abilito pulsante di pausa durante il gioco */
			}
	}




	//handles key2 pressure to pause the game. Only called by RIT IRQHandler
	void KEY2_down(void){
	 static int count=0;

		if((LPC_GPIO2->FIOPIN & (1<<12)) == 0){
			 key2++;
		} else{
			 count++;
			 if(key2++){
				 if (count%2 != 0){ //pausa se count dispari
					
					 disable_timer(1);
					 disable_timer(0);
				
					 } else{ //resume se count pari
					 
							enable_timer(1);
							enable_timer(0);
						 }
				}
				
				disable_RIT();
				reset_RIT();
				key2 = 0;
				enable_KEY2();
		 } 

	}




	void RIT_IRQHandler (void)
	{	
			
		//handling int0
		if(int0) INT0_down();
		// handling key1
		if(key1) KEY1_down();
		// handling key2
		if(key2) KEY2_down();
		
		LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	} 

	/******************************************************************************
	**                            End Of File
	******************************************************************************/
