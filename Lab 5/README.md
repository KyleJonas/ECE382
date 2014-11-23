ECE381_Lab5
===========
Remote Control Decoding

##Purpose
The purpose of Lab 5 is to use a IR Remote to control functionality on the MSP430.   

##Objectives
Lab day 1: learn the timing and bit patterns for your remote control   
Lab day 2: demonstrate your code can receive and decode button presses from the remote control (Required Functionality)   
Lab day 3: implement etch-a-sketch or pong (A Functionality)   

##Day 1
For day 1 our goal was to connect the IR sensor and collect the timer counts and duration for our remote based on the provded test.c code. I used both code composer and the logic analyzer in order find the duration and timer counts. For duration I ran a button press on the logic anayler or O-scope and would measure the time of each pulse. I then used Code Composer for timer counts taking the values in variable timer arrays.

![Duration](https://github.com/KyleJonas/ECE382_Lab5/blob/master/Images/LogicAnalyzer.jpg?raw=true "Duration")   

![Timer Count](https://github.com/KyleJonas/ECE382_Lab5/blob/master/Images/TimeCounts.PNG?raw=true "Timer Count")   

I used the data to complete the table bellow:   

| Pulse                     | Duration (ms) | Timer A counts |
|---------------------------|---------------|----------------|
| Start logic 0 half-pulse  | 2.44          | 2401           |
| Start logic 1 half-pulse  | 0.56          | 564            |
| Data 1 logic 0 half-pulse | 1.24          | 1216           |
| Data 1 logic 1 half-pulse | 0.56          | 559            |
| Data 0 logic 0 half-pulse | 0.62          | 621            |
| Data 0 logic 1 half-pulse | 0.56          | 561            |
| Stop logic 0 half-pulse   | 0.68          | 673            |
| Stop logic 1 half-pulse   | 21.94         | 21690          |

In order to find the hex code for each of my buttons pressed I again used the logic analyzer to give me a visual output of the button press. I then took the combined pulses to find the binary code and covereted it to hex for the .C code. Since 
I did not have all of the sampled buttons on my remote I included other button values.   

| Button | Code (Binary)       | Code (Hex) |
|--------|---------------------|------------|
| Up     | 0001111000010000100 | F084       |
| Down   | 1001111000010000100 | 4F084      |
| Left   | 0101111000010000100 | 2F084      |
| Right  | 1101111000010000100 | 6F084      |
| Power  | 10101000000101      | 2A05       |
| VOL +  | 01001000000101      | 1205       |
| VOL -  | 11001000000101      | 3205       |

####Questions from Day 1   

1) How long will it take the timer to roll over?   
It will take 66.5 ms for the timer to roll over.   

2) How long does each timer count last?   
Each timer lasts 1 us.   

3) Annotate the picture below to indicate which line of the for loop in the program is executed at which part of the pulse. You should show a total of 6 lines of code (lines 32-34 and lines 36-38).   

![Day 1 Wave](https://github.com/KyleJonas/ECE382_Lab5/blob/master/Images/Day1Wave.PNG?raw=true "Day 1 Wave")   

##Basic Functionality
Turn an LED on and off with one button on the remote. Turn another LED on and off with a different button.   

To compete basic functionality I started by completing my header file with the hex values for my remotes buttons and the average logic pulses. I then used the schematic to fill in the missin sections of the RequiredFunct.C file.   

![Required Schematic](https://github.com/KyleJonas/ECE382_Lab5/blob/master/Images/RequiredFunct.jpg?raw=true "Required Schematic")   

To do this I created the main loop to check for a IR Packet and then toggle the LEDs if the UP and DOWN buttons were pressed. I added code in the PORT2_VECTOR sift the bit into IrPacket and to store TAR into Packet data for the falling edge, and to turn the Timer A on for the rising edge. For TIMER0-A1-VECTOR I had to tune the timer off.   

##Debugging
My debugging for the required functionality was an adventure due to my remote being special. The first catch in debugging was that I was not setting the newIrPacktet to TRUE and FALSE when I was recieve a IR Signal, causing my main code never to see button press and toggle the LED. This was an easy 2 line fix, setting TRUE when the button was pressed and FALSE values after the LED was toggled. The largest problem with my code was that the remote signal was inverted. for my Data 1 and Data 0 logic the signal would remain longer at low a 1 logic instead of remaining at high longer. Addtionally there was not much time speration between logic 1 and logic 2. These two problems combined caused issues when completing the header file. I was unable to debug this problem to test my code so I tried using another remote and their average logic pulse values. Using another remote I was able to sucessfully implement my required functionality. I am intriugued why my inverted remote did not work and I would like to figure out if there is a way in the code to fix for this error.

##A Functionality
Use the buttons on a remote control to either control your lab #4 etch-a-sketch (up, down, right, left, color) or your pong game.   
Becuase of my remote problems taking up my time I did not implement A functionality.   

##Documentatin:
I had Eric Thompson check over my RequiredFunct.c to look for mistakes since my remote and code were not working, he sugested that I try a different remote sicne my IR signal from my remote was inverted and we both could not figure out how to correct for this. I adjusting my header file to test my RequiredFunct.C  using Eric's remote which demonstrated that I correctly implemented my .C file.   
I also worked with Kevin Cabusora to work the logic analyzer. He helped me set up the analyzer and coppied down the binary string for each button as I read it out to him.
