/* File contenete logica di gioco*/
/* Includes ------------------------------------------------------------------*/
#include "../GLCD/GLCD.h"
#include "../timer/timer.h"
#include "game.h"
#include "../button_EXINT/button.h"

volatile int16_t pos[4]; //variabile passo attuale
/*
		pos[0] = actual x
		pos[1] = actual y
		pos[2] = actual x offset (-5,....,+5)
		pos[3] = actual y offset (-5,....,+5)
*/

extern uint8_t paddle_pos;
volatile uint16_t score = 0;;
char text_score[sizeof(score)];
volatile uint16_t record = 100;
char text_record[sizeof(record)];

void initBall(){
	pos[0]=120; 
  pos[1]=20; 
  pos[2]=5;
  pos[3]=5;
}

// disegna movimento pallina aggiornando posizione e direzione
void moveBall(int16_t pos[], uint8_t paddle_pos){
		
 //ridisegno punteggio se pallina ci passa sopra
	if(pos[0] >= 3 && pos[0] <=33 && pos[1]>=159 && pos[1] <= 176){ 
		
		sprintf(text_score, "%d", score);
		GUI_Text(5, 160,(uint8_t*) text_score, White, Black);
	}
	 //ridisegno record se pallina ci passa sopra
	if(pos[0] >= 200 && pos[0] <=235 && pos[1]>=4 && pos[1] <= 25){ 
		
		sprintf(text_record, "%d", record);
		GUI_Text(210, 10,(uint8_t*) text_record, White, Black);
	}	

	//Check bordo superiore 
	if(pos[1]-6 <= MAX_SUP ){ 
		//attivo suono muro
		enable_timer(3);
		pos[3] *= -1;
		
	}
	// Check bordo sx and dx
	if(pos[0]-6 <= MAX_SX || pos[0]+6 >= MAX_DX  ){ 
		//attivo suono muro
		enable_timer(3);
		pos[2] *= -1;

	}
	// Check bordo inferiore
	/*
		pos[1] > ALT_PADDLE supera il paddle
		pos[0]+2 < paddle_pos-DIM_PADDLE/2 : è a sx del paddle, quindi non deve rimbalzare su di lui
		pos[0]-2 > paddle_pos+DIM_PADDLE/2 : è a dx del paddle, quindi non deve rimbalzare su di lui
	*/	
	if(pos[1] > ALT_PADDLE && (pos[0]+2 < paddle_pos-DIM_PADDLE/2 || pos[0]-2 > paddle_pos+DIM_PADDLE/2)){ 
		//Game over: disabilito timer per stoppare il gioco
		enable_INT0();
		GUI_Text(95, 125, (uint8_t *)"YOU LOSE!", White, Black);
		disable_timer(1);
		reset_timer(1);
		disable_timer(0);
		reset_timer(0);

		}
	// Check paddle 
	/*
		pos[1]+3 >= ALT_PADDLE : è alla stessa altezza del paddle o più in basso
		pos[0]+2 >= paddle_pos-DIM_PADDLE/2 && pos[0]-2 <= paddle_pos+DIM_PADDLE/2 : la palla cade dentro il paddle per cui deve rimbalzare
	*/	
	if(pos[1]+3 >= ALT_PADDLE && (pos[0]+2 >= paddle_pos-DIM_PADDLE/2 && pos[0]-2 <= paddle_pos+DIM_PADDLE/2)){ 
		//attivo suono paddle
		enable_timer(2);
		//Devo calcolare la direzione di uscita in base a al punto in cui ho toccato il paddle
		if(pos[0] >= paddle_pos-5 && pos[0] < paddle_pos){ //se tocco al centro torno su verticalmente leggermente verso sx 
			 
			pos[2] = -1;
			pos[3] *= -1;
			
		} else if(pos[0] >= paddle_pos && pos[0] <= paddle_pos+5 ){ //se tocco al centro torno su verticalmente leggermente verso dx
				
				pos[2] = 1;
			  pos[3] *= -1;

		 } else if(pos[0] > paddle_pos+5 && pos[0] <= paddle_pos+15 ){ //se tocco dx centrale 
				
				pos[2] = 4;
			  pos[3] = -5;

		 }	else if(pos[0] > paddle_pos+15 ){ //se tocco estrema dx 
				
					pos[2] = 5;
					pos[3] = -2;

				} else if(pos[0] < paddle_pos-5 && pos[0] >= paddle_pos-15){ //se tocco sx centrale
						pos[2] = -4;
						pos[3] = -5;
				
					} else if(pos[0] < paddle_pos-15){ //se tocco estrema sx 
							pos[2] = -5;
							pos[3] = -2;
				
						}
					
		//gestisco punteggi
		 if (score >= 100){
			score += 10;
		 }else{
			 score += 5; 
			 }
		 	sprintf(text_score, "%d", score);
			GUI_Text(5, 160,(uint8_t*) text_score, White, Black);
			 
			 if(score > record){
				 record = score;
				 sprintf(text_record, "%d", record);
				 GUI_Text(210, 10,(uint8_t*) text_record, White, Black);
				 
			 } 

		 
		}
	//cancello pallina in posizione vecchia
	clearBall(pos[0],pos[1]); 
	
	//aggiorno posizione pallina
	pos[0] = pos[0] + pos[2];
	pos[1] = pos[1] + pos[3];
	
		//disegno pallina
	drawBall(pos[0], pos[1]);

}


void drawPaddle(uint8_t paddle_pos){
	
		 LCD_DrawLine(paddle_pos-25, 288, paddle_pos+25, 288, Green);
	   LCD_DrawLine(paddle_pos-25, 287, paddle_pos+25, 287, Green);
		 LCD_DrawLine(paddle_pos-25, 286, paddle_pos+25, 286, Green);
		 LCD_DrawLine(paddle_pos-25, 285, paddle_pos+25, 285, Green);
		 LCD_DrawLine(paddle_pos-25, 284, paddle_pos+25, 284, Green);
		 LCD_DrawLine(paddle_pos-25, 283, paddle_pos+25, 283, Green);
		 LCD_DrawLine(paddle_pos-25, 282, paddle_pos+25, 282, Green);
		 LCD_DrawLine(paddle_pos-25, 281, paddle_pos+25, 281, Green);
		 LCD_DrawLine(paddle_pos-25, 280, paddle_pos+25, 280, Green);
		 LCD_DrawLine(paddle_pos-25, 279, paddle_pos+25, 279, Green);
		 LCD_DrawLine(paddle_pos-25, 278, paddle_pos+25, 278, Green);
}

void clearPaddle (uint8_t paddle_pos){
		 LCD_DrawLine(paddle_pos-25, 288, paddle_pos+25, 288,Black);
		 LCD_DrawLine(paddle_pos-25, 287, paddle_pos+25, 287, Black);
		 LCD_DrawLine(paddle_pos-25, 286, paddle_pos+25, 286, Black);
		 LCD_DrawLine(paddle_pos-25, 285, paddle_pos+25, 285, Black);
		 LCD_DrawLine(paddle_pos-25, 284, paddle_pos+25, 284, Black);
		 LCD_DrawLine(paddle_pos-25, 283, paddle_pos+25, 283, Black);
		 LCD_DrawLine(paddle_pos-25, 282, paddle_pos+25, 282, Black);
		 LCD_DrawLine(paddle_pos-25, 281, paddle_pos+25, 281, Black);
		 LCD_DrawLine(paddle_pos-25, 280, paddle_pos+25, 280, Black);
		 LCD_DrawLine(paddle_pos-25, 279, paddle_pos+25, 279, Black);
		 LCD_DrawLine(paddle_pos-25, 278, paddle_pos+25, 278, Black);

}
void clearBall (int16_t x, int16_t y){
	//prima riga
	LCD_SetPoint(x-2, y+2, Black);
	LCD_SetPoint(x-1, y+2, Black);
	LCD_SetPoint(x-0, y+2, Black);
	LCD_SetPoint(x+1, y+2, Black);
	LCD_SetPoint(x+2, y+2, Black);
	//seconda riga
	LCD_SetPoint(x-2, y+1, Black);
	LCD_SetPoint(x-1, y+1, Black);
	LCD_SetPoint(x-0, y+1, Black);
	LCD_SetPoint(x+1, y+1, Black);
	LCD_SetPoint(x+2, y+1, Black);
	//terza riga
	LCD_SetPoint(x-2, y+0, Black);
	LCD_SetPoint(x-1, y+0, Black);
	LCD_SetPoint(x-0, y+0, Black); //punto centrale
	LCD_SetPoint(x+1, y+0, Black);
	LCD_SetPoint(x+2, y+0, Black);
	//quarta riga
	LCD_SetPoint(x-2, y-1, Black);
	LCD_SetPoint(x-1, y-1, Black);
	LCD_SetPoint(x-0, y-1, Black);
	LCD_SetPoint(x+1, y-1, Black);
	LCD_SetPoint(x+2, y-1, Black);
	//quinta riga
	LCD_SetPoint(x-2, y-2, Black);
	LCD_SetPoint(x-1, y-2, Black);
	LCD_SetPoint(x-0, y-2, Black);
	LCD_SetPoint(x+1, y-2, Black);
	LCD_SetPoint(x+2, y-2, Black);
}
void drawBall (int16_t x, int16_t	y){

	//prima riga
	LCD_SetPoint(x-2, y+2, Green);
	LCD_SetPoint(x-1, y+2, Green);
	LCD_SetPoint(x-0, y+2, Green);
	LCD_SetPoint(x+1, y+2, Green);
	LCD_SetPoint(x+2, y+2, Green);
	//seconda riga
	LCD_SetPoint(x-2, y+1, Green);
	LCD_SetPoint(x-1, y+1, Green);
	LCD_SetPoint(x-0, y+1, Green);
	LCD_SetPoint(x+1, y+1, Green);
	LCD_SetPoint(x+2, y+1, Green);
	//terza riga
	LCD_SetPoint(x-2, y+0, Green);
	LCD_SetPoint(x-1, y+0, Green);
	LCD_SetPoint(x-0, y+0, Green); //punto centrale
	LCD_SetPoint(x+1, y+0, Green);
	LCD_SetPoint(x+2, y+0, Green);
	//quarta riga
	LCD_SetPoint(x-2, y-1, Green);
	LCD_SetPoint(x-1, y-1, Green);
	LCD_SetPoint(x-0, y-1, Green);
	LCD_SetPoint(x+1, y-1, Green);
	LCD_SetPoint(x+2, y-1, Green);
	//quinta riga
	LCD_SetPoint(x-2, y-2, Green);
	LCD_SetPoint(x-1, y-2, Green);
	LCD_SetPoint(x-0, y-2, Green);
	LCD_SetPoint(x+1, y-2, Green);
	LCD_SetPoint(x+2, y-2, Green);
}

void drawRedWalls(){
	//lato sinistro

	LCD_DrawLine(0,278, 0, 0,Red);
	LCD_DrawLine(1,278, 1, 0,Red);
	LCD_DrawLine(2,278, 2, 0,Red);
	LCD_DrawLine(3,278, 3, 0,Red);
	LCD_DrawLine(4,278, 4, 0,Red);
	//lato alto
	LCD_DrawLine(4,0,236, 0,Red);
	LCD_DrawLine(4,1,236, 1,Red);
	LCD_DrawLine(4,2,236, 2,Red);
	LCD_DrawLine(4,3,236, 3,Red);
	LCD_DrawLine(4,4,236, 4,Red);
	//lato destro 
	LCD_DrawLine(240,0, 240, 278,Red);
	LCD_DrawLine(239,0, 239, 278,Red);
	LCD_DrawLine(238,0, 238, 278,Red);
	LCD_DrawLine(237,0, 237, 278,Red);
	LCD_DrawLine(236,0, 236, 278,Red);

	
}

void clearText(){

 //clear center of the screen
	LCD_DrawLine(5,136, 235, 136,Black);
	LCD_DrawLine(5,135, 235, 135,Black);
	LCD_DrawLine(5,134, 235, 134,Black);
	LCD_DrawLine(5,133, 235, 133,Black);
	LCD_DrawLine(5,132, 235, 132,Black);
	LCD_DrawLine(5,131, 235, 131,Black);
	LCD_DrawLine(5,130, 235, 130,Black);
	LCD_DrawLine(5,129, 235, 129,Black);
	LCD_DrawLine(5,128, 235, 128,Black);
	LCD_DrawLine(5,127, 235, 127,Black);
	LCD_DrawLine(5,126, 235, 126,Black);
	
	//clear points

	LCD_DrawLine(5,162, 30, 162,Black);
	LCD_DrawLine(5,163, 30, 163,Black);
	LCD_DrawLine(5,164, 30, 164,Black);
	LCD_DrawLine(5,165, 30, 165,Black);
	LCD_DrawLine(5,166, 30, 166,Black);
	LCD_DrawLine(5,167, 30, 167,Black);
	LCD_DrawLine(5,168, 30, 168,Black);
	LCD_DrawLine(5,169, 30, 169,Black);
	LCD_DrawLine(5,170, 30, 170,Black);
	LCD_DrawLine(5,171, 30, 171,Black);
	LCD_DrawLine(5,172, 30, 172,Black);
	LCD_DrawLine(5,173, 30, 173,Black);
	
}
/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
