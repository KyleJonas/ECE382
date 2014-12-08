//-----------------------------------------------------------------
// Name:    Kyle Jonas
// File:    RequiredFunct.c
// Date:    Fall 2014
// Purp:    Required Functionalty for Lab 7
//-----------------------------------------------------------------
#include "msp430g2553.h"

void initMSP430();
void Right_Sensor();
void Left_Sensor();
void Center_Sensor();
//----------------------------------------------------------------------
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

//        Left_Sensor();
        Center_Sensor();
//        Right_Sensor();

    } // end infinite loop

} // end main

void Left_Sensor() {
    // LEFT
    static unsigned short L_val[16];
    static unsigned char x = 0;

            ADC10CTL0 = 0;                                          // Turn off ADC subsystem
            ADC10CTL1 = INCH_3 | ADC10DIV_3 ;                       // Channel 4, ADC10CLK/4
            ADC10AE0 = BIT3;                                        // Make P1.3 analog input
            ADC10CTL0 = SREF_0 | ADC10SHT_3 | ADC10ON | ENC;        // Vcc & Vss as reference

            ADC10CTL0 |= ADC10SC;                                   // Start a conversion
            while(ADC10CTL1 & ADC10BUSY);                           // Wait for conversion to complete
            L_val[x] = ADC10MEM;                                   // collect that 10-bit value
            if (L_val[x] > 0x0180) P1OUT |= BIT0;
            else                   P1OUT &= ~BIT0;

            x = (x+1) & 0xF;                            // This is a mod 16 increment
} // end Left_Sensor

void Center_Sensor() {
    // CENTER
    static unsigned short C_val[16];
    static unsigned char y = 0;

            ADC10CTL0 = 0;                                          // Turn off ADC subsystem
            ADC10CTL1 = INCH_4 | ADC10DIV_3 ;                       // Channel 4, ADC10CLK/4
            ADC10AE0 = BIT4;                                        // Make P1.4 analog input
            ADC10CTL0 = SREF_0 | ADC10SHT_3 | ADC10ON | ENC;        // Vcc & Vss as reference

            ADC10CTL0 |= ADC10SC;                                   // Start a conversion
            while(ADC10CTL1 & ADC10BUSY);                           // Wait for conversion to complete

            C_val[y] = ADC10MEM;                                   // collect that 10-bit value
            if (C_val[y] > 0x0195) P1OUT |= (BIT0|BIT6);
            else                   P1OUT &= ~(BIT0|BIT6);

            y = (y+1) & 0xF;                            // This is a mod 16 increment
} // end Center_Sensor

void Right_Sensor() {
    // RIGHT
    static unsigned short R_val[16];
    static unsigned char z = 0;

            ADC10CTL0 = 0;                                          // Turn off ADC subsystem
            ADC10CTL1 = INCH_5 | ADC10DIV_3 ;                       // Channel 4, ADC10CLK/4
            ADC10AE0 = BIT5;                                        // Make P1.5 analog input
            ADC10CTL0 = SREF_0 | ADC10SHT_3 | ADC10ON | ENC;        // Vcc & Vss as reference

            ADC10CTL0 |= ADC10SC;                                   // Start a conversion
            while(ADC10CTL1 & ADC10BUSY);                           // Wait for conversion to complete
            R_val[z] = ADC10MEM;                                   // collect that 10-bit value
            if (R_val[z] > 0x0230) P1OUT |= BIT6;
            else                   P1OUT &= ~BIT6;

            z = (z+1) & 0xF;                            // This is a mod 16 increment
} // end Right_Sensor
