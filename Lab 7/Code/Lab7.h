/*
 * Lab7.h
 * Kyle Jonas
 * Header file for IR sensor robot
 */

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


////////// METHODS //////////

void initMSP430();
int Right_Sensor();
int Left_Sensor();
int Center_Sensor();
int Average(unsigned short sample[]);
