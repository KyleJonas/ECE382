#include <msp430g2553.h>

extern void init();
extern void initNokia();
extern void clearDisplay();
extern void delayDraw();

extern void drawPaddle(unsigned char yPaddle, unsigned char xPaddle);

extern void drawBlock(unsigned char row, unsigned char col);

#define		TRUE			1
#define		FALSE			0
#define		BLACK			1
#define		WHITE			0
#define		UP_BUTTON		(P2IN & BIT5)
#define		DOWN_BUTTON		(P2IN & BIT4)
#define		AUX_BUTTON		(P2IN & BIT3)
#define		LEFT_BUTTON		(P2IN & BIT2)
#define		RIGHT_BUTTON	(P2IN & BIT1)


void main() {

	unsigned char	x, y, xVel, yVel, xPaddle, yPaddle, button_press;

	// === Initialize system ================================================
		IFG1=0; /* clear interrupt flag1 */
		WDTCTL=WDTPW+WDTHOLD; /* stop WD */
		button_press = FALSE;

		init();
		initNokia();
		clearDisplay();
		x=4;	y=4;	xVel=1;		yVel=1;		xPaddle=1;		yPaddle=4;
		drawBlock(y,x);

		while(1) {

					// MOVING THE BALL ================================================

					if (y <= yPaddle && x<=1) xVel=1;  // if ball hits paddle

					// if (x == 0) draw lose;

					if (xVel == 1) {
						x++;
						if (x>=11) xVel=0;
					}

					if (yVel == 1) {
						y++;
						if (y>=7) yVel=0;
					}

					if (yVel == 0) {
						y--;
						if (y<=0) yVel=1;
					}


					// MOVE PADDLE ================================================

					if (UP_BUTTON == 0) {				// Up
						while(UP_BUTTON == 0);
						if (yPaddle>=1) yPaddle-=1;
						button_press = TRUE;

					} else if (DOWN_BUTTON == 0) {		// Down
						while(DOWN_BUTTON == 0);
						if (yPaddle<=7) yPaddle+=1;
						button_press = TRUE;
					}

					if (button_press) {
						button_press = FALSE;
						clearDisplay();

						drawPaddle(yPaddle, xPaddle);
						drawBlock(y,x);
						delayDraw();
					}

					// RESET SCREEN ================================================

						clearDisplay();
						drawPaddle(yPaddle, xPaddle);
						drawBlock(y,x);
						delayDraw();
				}
		}

