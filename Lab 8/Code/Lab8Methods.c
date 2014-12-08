/*
 * Lab8Methods.c
 * Kyle Jonas
 * Methods for the IR Robot
 */

#include "msp430g2553.h"
#include "Lab8.c"

unsigned short sample[16];

////////// IR //////////

int Left_Sensor() {
    // LEFT

            ADC10CTL0 = 0;                                          // Turn off ADC subsystem
            ADC10CTL1 = INCH_3 | ADC10DIV_3 ;                       // Channel 4, ADC10CLK/4
            ADC10AE0 = L_Sensor;                                        // Make P1.3 analog input
            ADC10CTL0 = SREF_0 | ADC10SHT_3 | ADC10ON | ENC;        // Vcc & Vss as reference

            int i=0;
            while (i<16){
                ADC10CTL0 |= ADC10SC;                                   // Start a conversion
                while(ADC10CTL1 & ADC10BUSY);                           // Wait for conversion to complete
                sample[i] = ADC10MEM;                                   // collect that 10-bit value
                i++;
            }

            int avg = Average(sample);
            return avg;
} // end Left_Sensor

int Center_Sensor() {
    // CENTER

            ADC10CTL0 = 0;                                          // Turn off ADC subsystem
            ADC10CTL1 = INCH_4 | ADC10DIV_3 ;                       // Channel 4, ADC10CLK/4
            ADC10AE0 = C_Sensor;                                        // Make P1.4 analog input
            ADC10CTL0 = SREF_0 | ADC10SHT_3 | ADC10ON | ENC;        // Vcc & Vss as reference

            int i=0;
            while (i<16){
                ADC10CTL0 |= ADC10SC;                                   // Start a conversion
                while(ADC10CTL1 & ADC10BUSY);                           // Wait for conversion to complete
                sample[i] = ADC10MEM;                                   // collect that 10-bit value
                i++;
            }

            int avg = Average(sample);
            return avg;
} // end Center_Sensor

int Right_Sensor() {
    // RIGHT

            ADC10CTL0 = 0;                                          // Turn off ADC subsystem
            ADC10CTL1 = INCH_5 | ADC10DIV_3 ;                       // Channel 4, ADC10CLK/4
            ADC10AE0 = R_Sensor;                                        // Make P1.5 analog input
            ADC10CTL0 = SREF_0 | ADC10SHT_3 | ADC10ON | ENC;        // Vcc & Vss as reference

            int i=0;
            while (i<16){
                ADC10CTL0 |= ADC10SC;                                   // Start a conversion
                while(ADC10CTL1 & ADC10BUSY);                           // Wait for conversion to complete
                sample[i] = ADC10MEM;                                   // collect that 10-bit value
                i++;
            }

            int avg = Average(sample);
            return avg;
} // end Right_Sensor

int Average(unsigned short sample[]){
    int avg = 0;
    int sum = 0;
    int i=0;

    while (i<16){
        sum += sample[0];
        i++;
    }
    avg = sum/16;
    return avg;
} // end Average



////////// MOTOR //////////

void Forward(){

    // left motor
    P2OUT |= BIT0;      // EN
    P2OUT |= BIT1;      // Forward
    TA1CCTL1 = OUTMOD_7;                    // set TACCTL1 to Reset / Set mode

    // right motor
    P2OUT |= BIT3;      // EN
    P2OUT &= ~BIT5;     // Forward
    TA1CCTL2 = OUTMOD_3;                    // set TACCTL2 to Set / Reset mode

}// end forward

void Reverse(){

    // left motor
    P2OUT |= BIT0;      // EN
    P2OUT &= ~BIT1;     // Reverse
    TA1CCTL1 = OUTMOD_3;                    // set TACCTL1 to Reset / Set mode

    // right motor
    P2OUT |= BIT3;      // EN
    P2OUT |= BIT5;      // Reverse
    TA1CCTL2 = OUTMOD_7;                    // set TACCTL2 to Set / Reset mode

}// end reverse

void Stop(){

    // left motor
    P2OUT &= ~BIT0;     // Turn motor off

    // right motor
    P2OUT &= ~BIT3;     // Turn motor off

}// end stop

void Left(){

    // left motor
    P2OUT |= BIT0;      // EN
    P2OUT &= ~BIT1;     // Reverse
    TA1CCTL1 = OUTMOD_3;                    // set TACCTL1 to Reset / Set mode

    // right motor
    P2OUT |= BIT3;      // EN
    P2OUT &= ~BIT5;     // Forward
    TA1CCTL2 = OUTMOD_3;                    // set TACCTL2 to Set / Reset mode

}// end left

void Right(){

    // left motor
    P2OUT |= BIT0;      // EN
    P2OUT |= BIT1;      // Forward
    TA1CCTL1 = OUTMOD_7;                    // set TACCTL1 to Reset / Set mode

    // right motor
    P2OUT |= BIT3;      // EN
    P2OUT |= BIT5;      // Reverse
    TA1CCTL2 = OUTMOD_7;                    // set TACCTL2 to Set / Reset mode

}// end right
