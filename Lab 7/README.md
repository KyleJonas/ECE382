ECE382_Lab7
===========
Robot Sensing

###Purpose   
This lab is designed to assist you in learning the concepts associated with the analog-to-digital converter (ADC) for your MSP430. A set of three infrared (IR) emitter and detector pairs on your robot is used to bring in analog voltage values for the ADC. You will program your MSP430 to interpret these incoming voltages to determine whether your mobile robot is approaching a wall in front or on one of its sides.   

###Prelab   
To set up the lab I created an outline of the lab desing and measured the IR sensor voltage and converted them into ADC values.   

![Pg 1](https://github.com/KyleJonas/ECE382/blob/master/Lab%207/Images/2014-12-03%2013.51.47.jpg "Pg 1")   
![Pg 2](https://github.com/KyleJonas/ECE382/blob/master/Lab%207/Images/2014-12-03%2013.52.04.jpg "Pg 2")   
![IR Table](https://github.com/KyleJonas/ECE382/blob/master/Lab%207/Images/IR.PNG "IR Table")   
   
###Functionality   
Required Functionality:   
Use the ADC subsystem to light LEDs based on the presence of a wall.   

I was sucessful in completeing required functionality. When I would try to ligh up the LEDs occasionally my right sensor would display a slight red led along with the green. I tried changing the pins, covering up other sensors, and running the code with just the left and right sensor so that it would only ouput all red or all green however I was still unable to get fix this problem. Ultimatly I was able to get the sensors to read each wall, I will try to fix this for the next parts of the lab.   
<a href="http://www.youtube.com/watch?feature=player_embedded&v=LmoOwsTxcB4
" target="_blank"><img src="http://img.youtube.com/vi/LmoOwsTxcB4/0.jpg" 
alt="Required Functionality" width="240" height="180" border="10" /></a>  

B Functionality:   
Create a standalone library for your ATD code.   

I completed B functionality using 3 different files. A Lab7.h header file that held my constants and method declorations, a Methods.c file that contorlled all of the IR sesnor commands and methods, and a Lab7.c file that was a main method, running the Methods.c calls and turning on the LEDs if the robot was close to a wall.

A Functionality:   
Create a table and graphical plot that shows the ATD values for a variety of distances from a maze wall.   
![IR Table](https://github.com/KyleJonas/ECE382/blob/master/Lab%207/Images/IR.PNG "IR Table")  

###Code   
 I started out by creating a header file to declair constatns and initalize methods to be called throught the code.   
```
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
```

My main method for Lab 7 cleared the interrupt flag, deisabled the watch dog timer, enables the LEDs, and then runs a while loop to check and see if the sensor vlaues are within a range. If the robot is too close to one of the walls a LED will light up. Right = green, left = red, front = both red and green. This code will call all of the necessary methods from the Methods.c file.   
```
int main(void) {

    IFG1=0;                                                     // clear interrupt flag1
    WDTCTL = WDTPW + WDTHOLD;                                   // disable WDT

    BCSCTL1 = CALBC1_8MHZ;                                      // 8MHz clock
    DCOCTL = CALDCO_8MHZ;

    P1DIR = BIT0|BIT6;                                          // Set the red LED as output

    P1OUT = BIT0|BIT6;
    P1OUT &= ~(BIT0|BIT6);

    while(1) {
        // LEFT
        if (Left_Sensor() > L_Test) P1OUT |= BIT0;
        else               P1OUT &= ~BIT0;
        // CENTER
        if (Center_Sensor() > C_Test) P1OUT |= (BIT0|BIT6);
        else                 P1OUT &= ~(BIT0|BIT6);
        // Right
        if (Right_Sensor() > R_Test) P1OUT |= BIT6;
        else                P1OUT &= ~BIT6;

    } // end infinite loop
} // end main
```

For my Methods.c file I created a method for each IR sensor to enable the sensor and then collcet 16 reading and sotred them into an array. After all the reading were completed I called the Average method in order to return the average of all 16 reading back to the main method. Bellow is an example of one of the sensor methods.   
```
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
```

The Average method is shown below.
```
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

###Debugging   
Origionally I supplied the IR sensors with 5V from the rail. This caused problems where the IR values would come in larger then 3.3V and the MSP430 would not be able to fully work with the values. The largest problem I faced in the lab was getting the sensor values to return properly from the methods file into the main loop. To solve this Josh Hayden helped me change the return values to int and create a average method to decrease the impace of outlier IR values. The final problem I was facing was having both the red and green LED come on for the right sensor instead of just a green LED. A few of us in the lab were not able to solve this issue. We believe it has something to do with how the LEDs are called or a pull up or pull down resistor.   

###Observations/Conclusion   
This lab allowed me to implement the IR sensor in order to measure distances in voltages and convert these values into hex code. Not only will this be handy for Lab 8 but this has also helped me understand the IR robot we use for the Robotic Club. Throught the labe I found that the sensors were verry finicky and changing th light or using new batteries would have a large impact on the IR readings. While IR can be handy to measure distances you just have to be mindful of the potential dificulties.   

###Documentation
Josh Hayden helped me with my Methods.c file by showing me how to return the averages from the IR sensors to the main method to clean up my code and fix syntax mistakes.   
Kevin Cabusora helped me make a graph and table of my IR sensor values
