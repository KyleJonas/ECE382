ECE382_Lab6
===========
Robot Motion

##Purpose

The purpose of Lab 6 is to gain experience using the pulse-width modulation features of the MSP430. We will program the MSP430 to generate pulse-width-modulated waveforms to control the speed / direction of the robot's motors.   

##Prelab

To set up the lab I created a outline of the motor layout and the wiring for the MSP430 to create the pwm wave.

![PWM](https://github.com/KyleJonas/ECE382/blob/master/Lab%206/Pictures/2014-11-18%2014.14.36.jpg "PWM")
![Wiring](https://github.com/KyleJonas/ECE382/blob/master/Lab%206/Pictures/2014-11-18%2014.14.57.jpg "Wiring")
![Motor](https://github.com/KyleJonas/ECE382/blob/master/Lab%206/Pictures/2014-11-18%2014.15.08.jpg "Motor")

##Robot Design

Following the prelab I wired the robot up, shown bellow:

![Robot](https://github.com/KyleJonas/ECE382/blob/master/Lab%206/Pictures/Robot.jpg "Robot")

##Functionality

Required Functionality:   
Demonstrate movement forward, backward, a small (< 45 degree) turn left and right, and a large (> 45 dgree) turn left and right. The robot should perform these movements sequentially, completely disconnected from a computer (no USB cord).   

[Required Functionality Video](http://youtu.be/17MfBPkFUA0)   

A Functionality:   
Control your robot with your remote! You should use at least four different buttons on the remote: one each to indicate motion directions of forward, backward, left, and right.   

(Did not complete)   

##Code

To code to the robot I controlled each motor seperatly. For example, to go forward I set both the left and right motor forward, to go left I set the left motor in reverse and the right motor forward.

For easy commands I set constants for turn times and the run times for each motor. I also coppied the motor diagram into the comments for easy access.
```
#include <msp430.h>

#define run 	1000000
#define delay 	3000000
#define hTurn	0500000
#define	Turn	0750000

// (1A)		P2.2
// (2A)		P2.1
// (1,2EN)	P2.0

// (3,4EN)	P2.3
// (3A)		P2.4
// (4A)		P2.5
```

In the main method I inatilized the motor pins and the timers.
```
  WDTCTL = WDTPW|WDTHOLD;                 // stop the watchdog timer

	P1DIR &= ~BIT3;
	P1REN |= BIT3;

	// Left Motor Pins
	P2DIR |= BIT0;	// 1,2EN as OUT
	P2DIR |= BIT1;  // Left motor direction
	P2DIR |= BIT2;							// P2.2 is associated with TA1CCR1
	P2SEL |= BIT2;							// P2.2 is associated with TA1CCTL1

	// Right Motor Pins
	P2DIR |= BIT3;  // 3,4EN as OUT
	P2DIR |= BIT5;  // Right motor direction
	P2DIR |= BIT4;							// P2.4 is associated with TA1CCR2
	P2SEL |= BIT4;							// P2.4 is associated with TA1CCTL2

	// Timers
	TA1CTL = ID_3 | TASSEL_2 | MC_1;		// Use 1:8 presclar off MCLK
	TA1CCR0 = 0x0100;							// set signal period

	TA1CCR1 = 0x0020;
	TA1CCTL1 = OUTMOD_7;					// set TACCTL1 to Reset / Set mode

	TA1CCR2 = 0x0020;
	TA1CCTL2 = OUTMOD_3;					// set TACCTL1 to Reset / Set mode
```

I then ran a while loop for the robot commands.
```
while(1){

    	forward();
    	__delay_cycles(run);
    	stop();
    	__delay_cycles(delay);

  	    reverse();
 	    __delay_cycles(run);
   	    stop();
   	    __delay_cycles(delay);

   	    left();
 	    __delay_cycles(hTurn);
   	    stop();
   	    __delay_cycles(delay);

   	    right();
 	    __delay_cycles(hTurn);
   	    stop();
   	    __delay_cycles(delay);

   	    left();
 	    __delay_cycles(Turn);
   	    stop();
   	    __delay_cycles(delay);

   	    right();
 	    __delay_cycles(Turn);
   	    stop();
   	    __delay_cycles(delay);


    }// end while
```

The folowing methods are the robot direction controlls. They are called from the main method and control the motors so that the that the user only has to call, forward, reverse, left turn, right turn, and stop.

The forward method, both motors forward.
```
void forward(){

	// left motor
	P2OUT |= BIT0;		// EN
	P2OUT |= BIT1;		// Forward
	TA1CCTL1 = OUTMOD_7;					// set TACCTL1 to Reset / Set mode

	// right motor
	P2OUT |= BIT3;		// EN
	P2OUT &= ~BIT5;		// Forward
	TA1CCTL2 = OUTMOD_3;					// set TACCTL2 to Set / Reset mode

}// end forward
```

Reverse Method, both motors reverse.
```
void reverse(){

	// left motor
	P2OUT |= BIT0;		// EN
	P2OUT &= ~BIT1;		// Reverse
	TA1CCTL1 = OUTMOD_3;					// set TACCTL1 to Reset / Set mode

	// right motor
	P2OUT |= BIT3;		// EN
	P2OUT |= BIT5;		// Reverse
	TA1CCTL2 = OUTMOD_7;					// set TACCTL2 to Set / Reset mode

}// end reverse
```

Stop method, shuts off both motors
```
void stop(){

	// left motor
	P2OUT &= ~BIT0;		// Turn motor off

	// right motor
	P2OUT &= ~BIT3;		// Turn motor off

}// end stop
```

Left method, left motor reverse and right motor forward
```
void left(){

	// left motor
	P2OUT |= BIT0;		// EN
	P2OUT &= ~BIT1;		// Reverse
	TA1CCTL1 = OUTMOD_3;					// set TACCTL1 to Reset / Set mode

	// right motor
	P2OUT |= BIT3;		// EN
	P2OUT &= ~BIT5;		// Forward
	TA1CCTL2 = OUTMOD_3;					// set TACCTL2 to Set / Reset mode

}// end left
```

Right method, right motor reverse and left motor forward
```
void right(){

	// left motor
	P2OUT |= BIT0;		// EN
	P2OUT |= BIT1;		// Forward
	TA1CCTL1 = OUTMOD_7;					// set TACCTL1 to Reset / Set mode

	// right motor
	P2OUT |= BIT3;		// EN
	P2OUT |= BIT5;		// Reverse
	TA1CCTL2 = OUTMOD_7;					// set TACCTL2 to Set / Reset mode

}// end right
```

##Debugging

My first issue resulted in not correctly initalizing the motor pins. I founds out I was try to include some parts of the motor before I actually initalized it. I fixed this by compltly redoing my initalizatoin and completeing it in full for both motors instead of one at a time throught the code. The majority of my debuggin was spent getting the motors to go in their correct direction for each method. I was able to get one motor to work however the other motor was not responding correctly. it was quite frustrating and redid my drive code, commenting for each motor. Ultimately I redid the wiring for the motor controlls, finiding that two wires were switched.

###Documentation
I referenced Jasper Arneberg's code to help me fix a syntax error in initalizing the motor pins.
I worked with Kevin Cabusora to help debugg my lab 6 code. He also helped my shoot my required functionality video.
Sean Bapty also gave me the idea to use constants for the run times and turn lengths.
