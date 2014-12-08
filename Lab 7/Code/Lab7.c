//-----------------------------------------------------------------
// Name:    Kyle Jonas
// File:    Lab7.c
// Date:    Fall 2014
// Purp:    B Functionality for Lab7
//-----------------------------------------------------------------
#include "msp430g2553.h"
#include "Lab7.h"

void initMSP430();

//----------------------------------------------------------------------
int main(void) {

    IFG1=0;                                                     // clear interrupt flag1
    WDTCTL = WDTPW + WDTHOLD;                                   // disable WDT

    BCSCTL1 = CALBC1_8MHZ;                                      // 8MHz clock
    DCOCTL = CALDCO_8MHZ;

    P1DIR = BIT0|BIT6;                                               // Set the red LED as output

    P1OUT = BIT0|BIT6;
    P1OUT &= ~(BIT0|BIT6);

    while(1) {

        // LEFT
        if (Left_Sensor() > L_Test) P1OUT |= BIT0;
        else               P1OUT &= ~BIT0;

        // CENTER
        if (Center_Sensor() > C_Test) P1OUT |= (BIT0|BIT6);
        else                 P1OUT &= ~(BIT0|BIT6);

        // Right
        if (Right_Sensor() > R_Test) P1OUT |= BIT6;
        else                P1OUT &= ~BIT6;


    } // end infinite loop

} // end main
