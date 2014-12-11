ECE382_Lab7
===========
Robot Sensing

###Purpose   

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

###Debugging

###Observations/Conclusion

###Documentation
Josh Hayden helped me with my Methods.c file by showing me how to return the averages from the IR sensors to the main method to clean up my code and fix syntax mistakes
Kevin Cabusora helped me make a graph and table of my IR sensor values
