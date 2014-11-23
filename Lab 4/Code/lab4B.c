#include <msp430g2553.h>

extern void init();
extern void initNokia();
extern void clearDisplay();
extern void delayDraw();
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

	unsigned char	x, y, xVel, yVel;

	// === Initialize system ================================================
		IFG1=0; /* clear interrupt flag1 */
		WDTCTL=WDTPW+WDTHOLD; /* stop WD */


		init();
		initNokia();
		clearDisplay();
		x=4;	y=4;	xVel=1;		yVel=1;
		drawBlock(y,x);

		while(1) {

					// Vel = 1 going right/down
					// Vel = 0 going left/up

					if (xVel == 1) {
						x++;
						if (x>=11) xVel=0;
					}

					if (xVel == 0) {
						x--;
						if (x<=0) xVel=1;
					}

					if (yVel == 1) {
						y++;
						if (y>=7) yVel=0;
					}

					if (yVel == 0) {
						y--;
						if (y<=0) yVel=1;
					}

						clearDisplay();
						drawBlock(y,x);
						delayDraw();
				}
		}

