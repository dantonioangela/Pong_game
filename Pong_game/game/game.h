#include <stdint.h>
/* padel definitions */ 
#define DIM_PADDLE 50 //larghezza paddel
#define ALT_PADDLE 278 //altezza paddel rispetto a MAX_Y (278)
#define MAX_SUP 5 
#define MAX_SX 5
#define MAX_DX 235
#define MAX_INF 320

void drawPaddle(uint8_t paddle_pos);
void clearPaddle(uint8_t paddle_pos);
void drawBall (int16_t x, int16_t y); 
void clearBall (int16_t x, int16_t y); 
void moveBall(int16_t pos[],uint8_t paddle_pos);
void initBall(void);
void drawRedWalls(void);
void clearText(void);

