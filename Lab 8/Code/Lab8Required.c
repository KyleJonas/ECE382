//-----------------------------------------------------------------
// Name:    Kyle Jonas
// File:    Lab7.c
// Date:    Fall 2014
// Purp:    B Functionality for Lab7
//-----------------------------------------------------------------
#include "msp430g2553.h"
#include "Lab8.h"

void initMSP430();

// (1A)     P2.2
// (2A)     P2.1
// (1,2EN)  P2.0

// (3,4EN)  P2.3
// (3A)     P2.4
// (4A)     P2.5

// L_Sensor P1.3
// C_Sensor P1.4
// R_Sensor P1.5

////////// CONSANTS /////////

// Left
#define L_Sensor    BIT3
#define L_Close     0x01A2
#define L_Mid       0x0183
#define L_Far       0x0164
#define L_Test      0x0180

// Center
#define C_Sensor    BIT4
#define C_Close     0x01C1
#define C_Mid       0x0183
#define C_Far       0x0164
#define C_Test      0x0195

// Right
#define R_Sensor    BIT5
#define R_Close     0x01C1
#define R_Mid       0x0183
#define R_Far       0x0164
#define R_Test      0x0230

// Motor
#define run     0500000
#define delay   1000000
#define hTurn   0450000
#define Turn    0600000


////////// METHODS //////////

void initMSP430();

// IR
int Right_Sensor();
int Left_Sensor();
int Center_Sensor();
int Average(unsigned short sample[]);

// Motor
void Forward();
void Reverse();
void Stop();
void Left();
void Right();

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
