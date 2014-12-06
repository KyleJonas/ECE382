//-----------------------------------------------------------------
// Name:	Kyle Jonas
// File:	lab7.c
// Date:	Fall 2014
// Purp:
//-----------------------------------------------------------------
#include "msp430g2553.h"

void initMSP430();

//----------------------------------------------------------------------
//----------------------------------------------------------------------
int main(void) {

    // P1.1 Left
    // P1.2 Center
    // P1.3 Right

	unsigned short L[16];									    // To analyze the values
//	unsigned short C[16];
	int test;
	unsigned short R[16];
	unsigned char i = 0;										// index into sample array

	IFG1=0; 													// clear interrupt flag1
	WDTCTL = WDTPW + WDTHOLD;									// disable WDT

	BCSCTL1 = CALBC1_8MHZ;										// 8MHz clock
	DCOCTL = CALDCO_8MHZ;

	P1DIR = BIT0;												// Set the red LED as output

//	_enable_interrupt();

	while(1) {
	    // Configure P1.4 to be the ADC input
	    ADC10CTL0 = 0;                                          // Turn off ADC subsystem
	    ADC10CTL1 = INCH_4 | ADC10DIV_3 ;                       // Channel 4, ADC10CLK/4
	    ADC10AE0 = BIT2;                                        // Make P1.2 analog input
	    ADC10CTL0 = SREF_0 | ADC10SHT_3 | ADC10ON | ENC;        // Vcc & Vss as reference

	    ADC10CTL0 |= ADC10SC;                                   // Start a conversion
	    while(ADC10CTL1 & ADC10BUSY);                           // Wait for conversion to complete
//	    C[i] = ADC10MEM;                                   // collect that 10-bit value
	    test = ADC10MEM;

	    if (test > 0x0041) P1OUT |= BIT0;                       // turn on LED when closer than 5 in
	    else               P1OUT &= ~BIT0;                      // turn off LED

	    i = (i+1) & 0xF;                            // This is a mod 16 increment
	}

} // end main

//#pragma vector = PORT2_VECTOR				// This is from the MSP430G2553.h file
//__interrupt void Port_2_ISR(void) {
//
//
//
//	switch ( Sensor ) {
//	case Left:
//	    // Configure P1.4 to be the ADC input
//	           ADC10CTL0 = 0;                                          // Turn off ADC subsystem
//	           ADC10CTL1 = INCH_4 | ADC10DIV_3 ;                       // Channel 4, ADC10CLK/4
//	           ADC10AE0 = BIT1;                                        // Make P1.1 analog input
//	           ADC10CTL0 = SREF_0 | ADC10SHT_3 | ADC10ON | ENC;        // Vcc & Vss as reference
//
//	           ADC10CTL0 |= ADC10SC;                                   // Start a conversion
//	           while(ADC10CTL1 & ADC10BUSY);                           // Wait for conversion to complete
//	           L[i] = ADC10MEM;                                   // collect that 10-bit value
//
//	           if (L[i] > 0x0200) P1OUT |= BIT0;                       // turn on LED
//               else               P1OUT &= ~BIT0;                      // turn off LED
//
//	           i = (i+1) & 0xF;                            // This is a mod 16 increment
//		Sensor = Center;
//	  break;
//
//	case Center:
//	    // Configure P1.4 to be the ADC input
//	           ADC10CTL0 = 0;                                          // Turn off ADC subsystem
//	           ADC10CTL1 = INCH_4 | ADC10DIV_3 ;                       // Channel 4, ADC10CLK/4
//	           ADC10AE0 = BIT2;                                        // Make P1.2 analog input
//	           ADC10CTL0 = SREF_0 | ADC10SHT_3 | ADC10ON | ENC;        // Vcc & Vss as reference
//
//	           ADC10CTL0 |= ADC10SC;                                   // Start a conversion
//	           while(ADC10CTL1 & ADC10BUSY);                           // Wait for conversion to complete
//	           C[i] = ADC10MEM;                                   // collect that 10-bit value
//
//	           if (C[i] > 0x0041) P1OUT |= BIT0;                       // turn on LED when closer than 5 in
//	           else               P1OUT &= ~BIT0;                      // turn off LED
//
//	           i = (i+1) & 0xF;                            // This is a mod 16 increment
//		Sensor = Right;
//	  break;
//	case Right:
//	    // Configure P1.4 to be the ADC input
//	           ADC10CTL0 = 0;                                          // Turn off ADC subsystem
//	           ADC10CTL1 = INCH_4 | ADC10DIV_3 ;                       // Channel 4, ADC10CLK/4
//	           ADC10AE0 = BIT3;                                        // Make P1.3 analog input
//	           ADC10CTL0 = SREF_0 | ADC10SHT_3 | ADC10ON | ENC;        // Vcc & Vss as reference
//
//	           ADC10CTL0 |= ADC10SC;                                   // Start a conversion
//	           while(ADC10CTL1 & ADC10BUSY);                           // Wait for conversion to complete
//	           R[i] = ADC10MEM;                                   // collect that 10-bit value
//
//	           if (R[i] > 0x0132) P1OUT |= BIT0;                       // turn on LED when closer than 5 in
//               else               P1OUT &= ~BIT0;                      // turn off LED
//
//	           i = (i+1) & 0xF;                            // This is a mod 16 increment
//	  break;
//	}
//}//end interupt



