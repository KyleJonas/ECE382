ECE382_Lab3
===========
Kyle Jonas   <br />
M6 Dr Coulston   <br />
Lab3 SPI - "I/O"

##Mega-Prelab

####Nokia 1202 LCD BoosterPack v4-5

|    Name    |    Pin #    |    Type       |    PxDIR    |    PxREN    |    PxOUT    |
|------------|-------------|---------------|-------------|-------------|-------------|
|    GND     |    20       |    power      |    N/A      |    N/A      |    N/A      |
|    RST     |    8        |    output     |    1        |    0        |    1        |
|    P1.4    |    6        |    output     |    1        |    0        |    1        |
|    MOSI    |    15       |    output     |    1        |    0        |    1        |
|    SCLK    |    7        |    output     |    1        |    0        |    1        |
|    VCC     |    1        |    power      |    N/A      |    N/A      |    N/A      |
|    S1      |    9        |    input      |    0        |    1        |    1        |
|    S2      |    10       |    input      |    0        |    1        |    1        |
|    S3      |    11       |    input      |    0        |    1        |    1        |
|    S4      |    12       |    input      |    0        |    1        |    1        |
MS430 Family Guide p328-329

####Configure the MSP430 

|    Mystery Label    |    Register    |
|---------------------|----------------|
|    A                |    P1DIR       |
|    B                |    P1OUT       |
|    C                |    P2DIR       |
|    D                |    P2OUT       |
MSP430 p328-329

|    ID          |    Bit    |    Function as   set in the Code                             |
|----------------|-----------|--------------------------------------------------------------|
|    UCCKPH      |    7      |    Clock Phase select                                        |
|    UCMSB       |    5      |    Control direction receive & transmit shift   registers    |
|    UCMST       |    3      |    Master mode select                                        |
|    UCSYNCH     |    0      |    Synchronous mode enabled                                  |
|    UCSSEL_2    |    7-6    |    Select SMCLK as source clk in master mode                 |
|    UCSWRST     |    0      |    Software reset enabled                                    |
MSP430 Family Guide p445

####Configure the Nokia 1202 Display

|    Symbolic   Constant             |    Hex    |    Function                                               |
|------------------------------------|-----------|-----------------------------------------------------------|
|    #STE2007_RESET                  |    E2     |    Internal reset                                         |
|    #STE2007_DISPLAYALLPOINTSOFF    |    A4     |    Sets on chip power supply                              |
|    #STE2007_POWERCONTROL           |    N/A    |    Normal LCS display                                     |
|    #STE2007_POWERCTR_ALL_ON        |    2F     |    Voltage regulator, voltage follower, and booster on    |
|    #STE2007_DISPLAYNORMAL          |    A6     |    Normal LCD display                                     |
|    #STE2007_DISPLAYON              |    AF     |    Turns display on                                       |
STE2007 p41


##Lab

####Logic Analyzer

| Line | R12    | R13    | Purpose                                                                                                    |
|------|--------|--------|------------------------------------------------------------------------------------------------------------|
| 66   | `0x01` | `0xE7` | R12 Parameter to writeNokiaByte specifying data, R13 Holds the data for the 8-bit vertical bar `1110 0111` |
| 276  | `0x00` | `0xB0` | R12 specifies command, R13 sets page (aka row) address to `0xB0`                                           |
| 288  | `0x00` | `0x10` | R12 specifies command, R13 `0x10` is the prefix for upper 4-bits in the column                             |
| 294  | `0x00` | `0x00` | R12 specifies command, R13`0x00` is the prefix for lower 4-bits in the column                               |

####Waveforms

| Line | Command/Data | 8-bit Packet |
|------|--------------|--------------|
| 66   | Data         | 1110 0111    |
| 276  | Command      | 1011 0001    |
| 288  | Command      | 0001 0000    |
| 294  | Command      | 0000 0001    |

Line 66
![Line 66](https://github.com/KyleJonas/ECE382_Lab3/blob/master/Pictures/Line%2066.png?raw=true "Line 66")

Line 276
![Line 276](https://github.com/KyleJonas/ECE382_Lab3/blob/master/Pictures/Line%20276.png?raw=true "Line 276")

Line 288
![Line 288](https://github.com/KyleJonas/ECE382_Lab3/blob/master/Pictures/Line%20288.png?raw=true "Line 288")

Line 294
![Line 294](https://github.com/KyleJonas/ECE382_Lab3/blob/master/Pictures/Line%20294.png?raw=true "Line 294")

The duration of the reset can be found from code lines 93-100. This code performs a dec and a jne, each of which take 2 clock cycles. The code is iterated from 0xFFFF to 0 which is 65535 in decimal times 4 clock cycles each iteration gives us 262140 clock cycles total. With a 1 microseconds clock cycle the reset takes 262.14 miliseconds.

####Writing Modes

![Writing Modes](https://github.com/KyleJonas/ECE382_Lab3/blob/master/Pictures/Writing%20Modes.png?raw=true "Writing Modes")

####Functionality

##Documentation

####Mega-Prelab

The following cadets worked together and discussed Lab 3 Mega Prelab on Sunday night in order to understand the questions and bounce ideas off each other.

C2C Nathan Ruprecht   
C2C Eric Thompson   
C2C Austin Bolinger   
C2C Sabin Park   
C2C Kyle Jonas   
C2C Jermy Gruszka   
C2C Kevin Cabusora   
C2C Taylor Bodin   
C2C Jarrod Wooden   
C2C Sean Bapty   
C2C Erica Lewandowski   
C2C Chris Kiernan   
C2C J.P. Terragnoli   
C2C Hunter Her   
C2C Gytenis Borusas   

####Lab

I worked with C2C Kevin Cabusora in the lab to set up and measure the waveforms.
