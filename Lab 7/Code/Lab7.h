/*
 * Lab7.h
 * Kyle Jonas
 * Header file for IR sensor robot
 */

////////// CONSANTS /////////

// Left
#define L_Sensor    BIT3
#define L_2in
#define L_4in
#define L_10in
#define L_Test      0x0180

// Center
#define C_Sensor    BIT4
#define C_2in
#define C_4in
#define C_10in
#define C_Test      0x0195

// Right
#define R_Sensor    BIT5
#define R_2in
#define R_4in
#define R_10in
#define R_Test      0x0230


////////// METHODS //////////

void initMSP430();
int Right_Sensor();
int Left_Sensor();
int Center_Sensor();
int Average(unsigned short sample[]);
