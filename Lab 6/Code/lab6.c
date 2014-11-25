/*
 * 		lab6.c
 * 		Kyle Jonas
 * 		23 Nov 2014
 * 		Robot Motion
 */


#include <msp430.h>

#define run 	1000000
#define delay 	3000000
#define hTurn	0025000
#define	Turn	0500000

// (1A)		P2.2
// (2A)		P2.1
// (1,2EN)	P2.0

// (3,4EN)	P2.3
// (3A)		P2.4
// (4A)		P2.5


void main(void) {

	WDTCTL = WDTPW|WDTHOLD;                 // stop the watchdog timer

	P1DIR &= ~BIT3;
	P1REN |= BIT3;

	// Left Motor Pins
	P2DIR |= BIT0;	// 1,2EN as OUT
	P2DIR |= BIT1;  // Left motor direction
	P2DIR |= BIT2;							// P2.2 is associated with TA1CCR1
	P2SEL |= BIT2;							// P2.2 is associated with TA1CCTL1

	// Right Motor Pins
	P2DIR |= BIT3;  // 3,4EN as OUT
	P2DIR |= BIT5;  // Right motor direction
	P2DIR |= BIT4;							// P2.4 is associated with TA1CCR2
	P2SEL |= BIT4;							// P2.4 is associated with TA1CCTL2

	// Timers
	TA1CTL = ID_3 | TASSEL_2 | MC_1;		// Use 1:8 presclar off MCLK
	TA1CCR0 = 0x0100;							// set signal period

	TA1CCR1 = 0x0020;
	TA1CCTL1 = OUTMOD_7;					// set TACCTL1 to Reset / Set mode

	TA1CCR2 = 0x0020;
	TA1CCTL2 = OUTMOD_3;					// set TACCTL1 to Reset / Set mode


    while(1){

    	forward();
    	__delay_cycles(run);
    	stop();
    	__delay_cycles(delay);

  	    reverse();
 	    __delay_cycles(run);
   	    stop();
   	    __delay_cycles(delay);

   	    left();
 	    __delay_cycles(hTurn);
   	    stop();
   	    __delay_cycles(delay);

   	    right();
 	    __delay_cycles(hTurn);
   	    stop();
   	    __delay_cycles(delay);

   	    left();
 	    __delay_cycles(Turn);
   	    stop();
   	    __delay_cycles(delay);

   	    right();
 	    __delay_cycles(Turn);
   	    stop();
   	    __delay_cycles(delay);


    }// end while


} // end main

// (1A)		P2.2
// (2A)		P2.1
// (1,2EN)	P2.0

// (3A)		P2.5
// (4A)		P2.4
// (3,4EN)	P2.3

void forward(){

	// left motor
	P2OUT |= BIT0;		// EN
	P2OUT |= BIT1;		// Forward
	TA1CCTL1 = OUTMOD_7;					// set TACCTL1 to Reset / Set mode

	// right motor
	P2OUT |= BIT3;		// EN
	P2OUT &= ~BIT5;		// Forward
	TA1CCTL2 = OUTMOD_3;					// set TACCTL2 to Set / Reset mode

}// end forward

void reverse(){

	// left motor
	P2OUT |= BIT0;		// EN
	P2OUT &= ~BIT1;		// Reverse
	TA1CCTL1 = OUTMOD_3;					// set TACCTL1 to Reset / Set mode

	// right motor
	P2OUT |= BIT3;		// EN
	P2OUT |= BIT5;		// Reverse
	TA1CCTL2 = OUTMOD_7;					// set TACCTL2 to Set / Reset mode

}// end reverse

void stop(){

	// left motor
	P2OUT &= ~BIT0;		// Turn motor off

	// right motor
	P2OUT &= ~BIT3;		// Turn motor off

}// end stop

void left(){

	// left motor
	P2OUT |= BIT0;		// EN
	P2OUT &= ~BIT1;		// Reverse
	TA1CCTL1 = OUTMOD_3;					// set TACCTL1 to Reset / Set mode

	// right motor
	P2OUT |= BIT3;		// EN
	P2OUT &= ~BIT5;		// Forward
	TA1CCTL2 = OUTMOD_3;					// set TACCTL2 to Set / Reset mode

}// end left

void right(){

	// left motor
	P2OUT |= BIT0;		// EN
	P2OUT |= BIT1;		// Forward
	TA1CCTL1 = OUTMOD_7;					// set TACCTL1 to Reset / Set mode

	// right motor
	P2OUT |= BIT3;		// EN
	P2OUT |= BIT5;		// Reverse
	TA1CCTL2 = OUTMOD_7;					// set TACCTL2 to Set / Reset mode

}// end right
