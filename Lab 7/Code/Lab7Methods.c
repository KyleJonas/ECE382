/*
 * Methods.c
 * Kyle Jonas\
 * Methods for the sensors
 */

#include "msp430g2553.h"
#include "Lab7.c"

unsigned short sample[16];

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
