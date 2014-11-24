/*
 * 		lab6.c
 * 		Kyle Jonas
 * 		23 Nov 2014
 * 		Robot Motion
 */


#include <msp430.h>

#define Period 100;
#define Speed 60;

// (1A)		P2.2
// (2A)		P2.1
// (1,2EN)	P2.0

// (3,4EN)	P2.3
// (3A)		P2.4
// (4A)		P2.5

void main(void) {

	WDTCTL = WDTPW|WDTHOLD;                 // stop the watchdog timer

	// Initalize PWM

	P2DIR |= BIT2;							// P2.2 is associated with TA1CCR1
	P2SEL |= BIT2;							// P2.2 is associated with TA1CCTL1

	P2DIR |= BIT4;							// P2.4 is associated with TA1CCR2
	P2SEL |= BIT4;							// P2.4 is associated with TA1CCTL2

	// Timers
	TA1CTL = ID_3 | TASSEL_2 | MC_1;		// Use 1:8 presclar off MCLK
	TA1CCR0 = 100;							// set signal period

	TA1CCR1 = 50;
	TA1CCTL1 = OUTMOD_7;					// set TACCTL1 to Reset / Set mode

	TA1CCR2 = 50;
	TA1CCTL2 = OUTMOD_3;					// set TACCTL2 to Set / Reset mode

    while(1){

    	forward();
    	__delay_cycles(1000000);
    	stop();
    	__delay_cycles(1000000);

//  	    reverse();
// 	    __delay_cycles(1000000);
//   	    stop();
//   	    __delay_cycles(1000000);
//
//   	    left();
// 	    __delay_cycles(1000000);
//   	    stop();
//   	    __delay_cycles(1000000);
//
//   	    right();
// 	    __delay_cycles(1000000);
//   	    stop();
//   	    __delay_cycles(1000000);
    }


} // end main

void forward(){

	// left motor
	P2DIR |= BIT2;
	P2SEL |= BIT2;

	// right motor
	P2DIR |= BIT4;
	P2SEL |= BIT4;

}// end forward

void reverse(){

	// left motor
	P2DIR |= BIT1;
	P2SEL |= BIT1;

	// right motor
	P2DIR |= BIT5;
	P2SEL |= BIT5;

}// end reverse

void stop(){

	// left motor
	P2DIR &= ~BIT2;
	P2SEL &= ~BIT2;

	// right motor
	P2DIR &= ~BIT4;
	P2SEL &= ~BIT4;

}// end stop

void left(){

	// left motor
	P2DIR |= BIT1;		// reverse w/ left
	P2SEL |= BIT1;

	// right motor
	P2DIR |= BIT4;		// forward w/ right
	P2SEL |= BIT4;

}// end left

void right(){

	// left motor
	P2DIR |= BIT2;		// forward w/ left
	P2SEL |= BIT2;

	// right motor
	P2DIR |= BIT5;		// reverse w/ right
	P2SEL |= BIT5;

}// end right
