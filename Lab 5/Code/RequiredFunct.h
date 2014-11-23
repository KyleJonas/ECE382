//-----------------------------------------------------------------
// Name:	Kyle Jonas
// File:	lab5.h Required Funct
// Date:	Fall 2014
// Purp:	header file
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Page 76 : MSP430 Optimizing C/C++ Compiler v 4.3 User's Guide
//-----------------------------------------------------------------
typedef		unsigned char		int8;
typedef		unsigned short		int16;
typedef		unsigned long		int32;
typedef		unsigned long long	int64;

#define		TRUE				1
#define		FALSE				0

//-----------------------------------------------------------------
// Function prototypes found in lab5.c
//-----------------------------------------------------------------
void initMSP430();
__interrupt void pinChange (void);
__interrupt void timerOverflow (void);


//-----------------------------------------------------------------
// Each PxIES bit selects the interrupt edge for the corresponding I/O pin.
//	Bit = 0: The PxIFGx flag is set with a low-to-high transition
//	Bit = 1: The PxIFGx flag is set with a high-to-low transition
//-----------------------------------------------------------------

#define		IR_PIN			(P2IN & BIT6)
#define		HIGH_2_LOW		P2IES |= BIT6
#define		LOW_2_HIGH		P2IES &= ~BIT6


#define		averageLogic0Pulse	621
#define		averageLogic1Pulse	1216
#define		averageStartPulse	2401
#define		minLogic0Pulse		averageLogic0Pulse - 100
#define		maxLogic0Pulse		averageLogic0Pulse + 100
#define		minLogic1Pulse		averageLogic1Pulse - 100
#define		maxLogic1Pulse		averageLogic1Pulse + 100
#define		minStartPulse		averageStartPulse - 100
#define		maxStartPulse		averageStartPulse + 100


#define		UP			0xF084
#define		DOWN		0x4F084
#define		LEFT		0x2F084
#define		RIGHT		0x6F084

#define		PWR			0x2A05

#define		VOL_UP		0x1205
#define		VOL_DW		0x3205

#define		TEST		0x20DF10EF

//#define		PWR		0x02FD48B7
//#define		ONE		0x02FD807F
//#define		TWO		0x02FD40BF
//#define		THR		0x02FDC03F

//#define		CH_UP	0x02FDD827
//#define		CH_DW	0x02FDF807
