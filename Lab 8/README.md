ECE382_Lab8
===========
Robot Maze

###Purpose   
Combine the previous laboratory assignments and program your robot to autonomously navigate through a maze.   

###Prelab
Hard copy.   

###Functionality
Door 1 - Required Functionality
Door 2 - B Functionality
Door 3 - A Functionality (No wall hits)
Bonus! Navigate from the A door back to the entrance using the same algorithm. (No wall hits)

Required Functionality:   
<a href="http://www.youtube.com/watch?feature=player_embedded&v=fcVTbYYNM64
" target="_blank"><img src="http://img.youtube.com/vi/fcVTbYYNM64/0.jpg" 
alt="Required functionality" width="240" height="180" border="10" /></a>   

###Code
Similar to Lab 7 I had 3 code files. A header file, main method file, and a file containing all of the methods. Lab 8 basically is combining the robot movement from Lab 6 with the IR from Lab 7.    

For the H file I declaired all of the constatnts for the sensors and motors as well as declairing the methods that will be used throught the code.   
```
    while(1) {

    	///// Display LED /////
        if (Left_Sensor() > L_Far) P1OUT |= BIT0;
        else               P1OUT &= ~BIT0;

        if (Center_Sensor() > C_Far) P1OUT |= (BIT0|BIT6);
        else                 P1OUT &= ~(BIT0|BIT6);

        if (Right_Sensor() > R_Far) P1OUT |= BIT6;
        else                P1OUT &= ~BIT6;

        ///// Drive /////
        if (Center_Sensor() < C_Far) {         // No front wall

//        	if ( Left_Sensor() > L_Close) {	// to far left
//					Right();
//                	__delay_cycles(hTurn);
//            		Stop();
//            		__delay_cycles(delay);
//					Forward();
//            		__delay_cycles(run);
//            		Stop();
//            		__delay_cycles(delay);
//					Left();
//                	__delay_cycles(hTurn);
//
//        	} // end to far left
//
//        	if ( Right_Sensor() > R_Close) {	// to far right
//					Left();
//                	__delay_cycles(hTurn);
//            		Stop();
//            		__delay_cycles(delay);
//					Forward();
//            		__delay_cycles(run);
//            		Stop();
//            		__delay_cycles(delay);
//					Right();
//                	__delay_cycles(hTurn);
//        	} // end to far right
//
//        	if ( (Left_Sensor() < L_Close) && (Right_Sensor() < R_Close) ) {	// in the middle
        			Forward();
            		__delay_cycles(run);
            		Stop();
            		__delay_cycles(delay);
//        	}// end in the middle

        }else if (Center_Sensor() > C_Far) {   // Hit front wall

            if ( (Left_Sensor() > L_Far) && (Right_Sensor() > R_Far) ) {   // Yes L, Yes R
                // Stop, in corner
                Reverse();
                __delay_cycles(run);
                Stop();
                __delay_cycles(delay);
            }// end stop in corner

            if ( (Left_Sensor() < L_Far) && (Right_Sensor() > R_Far) ) {   // No L, Yes R
                // Turn L
                Stop();
                __delay_cycles(delay);
                Left();
                __delay_cycles(Turn);
            }// end left turn

            if ( (Left_Sensor() > L_Far) && (Right_Sensor() < R_Far) ) {   // Yes L, No R
                // Turn R
                Stop();
                __delay_cycles(delay);
                Right();
                __delay_cycles(Turn);
            }// end right turn

            if ( (Left_Sensor() < L_Far) && (Right_Sensor() < R_Far) ) {   // No L, No R
                // Turn L
                Stop();
                __delay_cycles(delay);
                Left();
                __delay_cycles(Turn);
            }// end defult left turn when no wall L or R
            
        }// end hit front wall
    } // end infinite loop
} // end main

```

For the methods.c file it was basically just adding the previous methods in from Lab 6 and Lab 7. the file containied the methods to drive the robot as well as the code for the IR sensors. An example of some of the Motor and IR method code are shown below.

```
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
```

```
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
```

###Debugging
There was not a lot of debugging on the code side of this lab. The hardest part of the lab wsa just getting my CCS to work properly. I ultimatly had to reinstal CCS which took up a lot of time. The main parts of the code I did have to work on was getting the algorithm to determine what walls you could see and what way you needed to turn. While coding this wasnt hard my sensors did not like to agree with me. My left sensor was unable to get reading when I ran my robot. This made it hard determine when I needed to turn and prohibited me from being able to do A or B functionality. For most of the sensors I had to add more shielding in order to get better ADC values without interference. To overcome some of these issues I retook IR sensor data but I still was having issues with the left sensor. The final problem I had was implementing the course corrections code. When I would try to run the course corrections it promarily resulted in the robot contantly teurning in circles. I tried to fix this code but I found that for the most part my robot drove straight so I wouldnt need the course corrections as bad.

###Observations/Conclusion
This lab showed me the importance of implementing good files and methods. Because I broke the code out into methods, header, and main it was easy to copy in my code from the last 2 labs in to the necessarry responce. This took the bulk of the work away from creating the IR and motor driving code and moved it on developing the algorithm to deterimine which way you need to turn.

###Documentation
I did not reveive any help on my code. I did get help from Capt Trimble and Kevin Cabusora in troubleshooting errors I was having with my CCS and then installing CCS. Austin Bolinger and Kevin Cabusora did lend me their computers so that I could run my own Lab 8 code while my CCS was reinstalling. 
