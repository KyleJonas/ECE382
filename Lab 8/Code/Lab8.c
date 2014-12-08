//-----------------------------------------------------------------
// Name:    Kyle Jonas
// File:    Lab7.c
// Date:    Fall 2014
// Purp:    B Functionality for Lab7
//-----------------------------------------------------------------
#include "msp430g2553.h"
#include "Lab8.h"

void initMSP430();

//----------------------------------------------------------------------
int main(void) {

    IFG1=0;                                                     // clear interrupt flag1
    WDTCTL = WDTPW + WDTHOLD;                                   // disable WDT

    ////////// IR //////////

    BCSCTL1 = CALBC1_8MHZ;                                      // 8MHz clock
    DCOCTL = CALDCO_8MHZ;

    P1DIR = BIT0|BIT6;                                          // Set the red LED as output

    P1OUT = BIT0|BIT6;
    P1OUT &= ~(BIT0|BIT6);

    P1DIR &= ~BIT3;
    P1REN |= BIT3;

    ////////// MOTOR //////////

    // Left Motor Pins
    P2DIR |= BIT0;  // 1,2EN as OUT
    P2DIR |= BIT1;  // Left motor direction
    P2DIR |= BIT2;                          // P2.2 is associated with TA1CCR1
    P2SEL |= BIT2;                          // P2.2 is associated with TA1CCTL1

    // Right Motor Pins
    P2DIR |= BIT3;  // 3,4EN as OUT
    P2DIR |= BIT5;  // Right motor direction
    P2DIR |= BIT4;                          // P2.4 is associated with TA1CCR2
    P2SEL |= BIT4;                          // P2.4 is associated with TA1CCTL2

    // Timers
    TA1CTL = ID_3 | TASSEL_2 | MC_1;        // Use 1:8 presclar off MCLK
    TA1CCR0 = 0x0100;                           // set signal period

    TA1CCR1 = 0x0020;
    TA1CCTL1 = OUTMOD_7;                    // set TACCTL1 to Reset / Set mode

    TA1CCR2 = 0x0020;
    TA1CCTL2 = OUTMOD_3;                    // set TACCTL1 to Reset / Set mode



    __delay_cycles(delay);                  // Inital delay for sensor to catch up

    while(1) {

        if (Center_Sensor() < C_Test) {         // No front wall

            Forward();
            __delay_cycles(run);
            Stop();
            __delay_cycles(delay);

        }else if (Center_Sensor() > C_Test) {   // Hit front wall

            if ( (Left_Sensor() > L_Test) && (Right_Sensor() > R_Test) ) {   // Yes L, Yes R
                // Stop, in corner
                Reverse();
                __delay_cycles(run);
                Stop();
                __delay_cycles(delay);
            }// end stop in corner

            if ( (Left_Sensor() < L_Test) && (Right_Sensor() > R_Test) ) {   // No L, Yes R
                // Turn L
                Left();
                __delay_cycles(Turn);

            }// end left turn

            if ( (Left_Sensor() > L_Test) && (Right_Sensor() < R_Test) ) {   // Yes L, No R
                // Turn R
                Right();
                __delay_cycles(Turn);
            }// end right turn

            if ( (Left_Sensor() < L_Test) && (Right_Sensor() < R_Test) ) {   // No L, No R
                // Turn L
                Left();
                __delay_cycles(Turn);

            }// end defult left turn when no wall L or R

        }// end hit front wall

    } // end infinite loop

} // end main
