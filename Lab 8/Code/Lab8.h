/*
 * Lab8.h
 * Kyle Jonas
 * Header file for IR Robot
 */

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
#define delay   0750000
#define hTurn   0450000
#define Turn    1500000		//0600000


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
