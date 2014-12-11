//-----------------------------------------------------------------
// Name:    Kyle Jonas
// File:    lab5.h Required Funct
// Date:    Fall 2014
// Purp:    header file
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Page 76 : MSP430 Optimizing C/C++ Compiler v 4.3 User's Guide
//-----------------------------------------------------------------
typedef     unsigned char       int8;
typedef     unsigned short      int16;
typedef     unsigned long       int32;
typedef     unsigned long long  int64;

#define     TRUE                1
#define     FALSE               0

//-----------------------------------------------------------------
// Function prototypes found in lab5.c
//-----------------------------------------------------------------
void initMSP430();
__interrupt void pinChange (void);
__interrupt void timerOverflow (void);


//-----------------------------------------------------------------
// Each PxIES bit selects the interrupt edge for the corresponding I/O pin.
//  Bit = 0: The PxIFGx flag is set with a low-to-high transition
//  Bit = 1: The PxIFGx flag is set with a high-to-low transition
//-----------------------------------------------------------------

#define     IR_PIN          (P2IN & BIT6)
#define     HIGH_2_LOW      P2IES |= BIT6
#define     LOW_2_HIGH      P2IES &= ~BIT6


#define     averageLogic0Pulse  594
#define     averageLogic1Pulse  1633
#define     averageStartPulse   4437
#define     minLogic0Pulse      averageLogic0Pulse - 220
#define     maxLogic0Pulse      averageLogic0Pulse + 220
#define     minLogic1Pulse      averageLogic1Pulse - 220
#define     maxLogic1Pulse      averageLogic1Pulse + 220
#define     minStartPulse       averageStartPulse - 220
#define     maxStartPulse       averageStartPulse + 220


#define     PWR     0x61A0F00F

#define		ONE		0x61A000FF
#define		TWO		0x61A0807F
#define		THR		0x61A0408F

