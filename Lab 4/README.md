ECE382_Lab4
===========

Etch-a-Sketch and Pong   
Kyle Jonas   

##Prelab

####Data Types

| Size   | Signed/Unsigned | Type           | Min value                  | Max value                  |
|--------|-----------------|----------------|----------------------------|----------------------------|
| 8-bit  | unsigned        | ASCII          | 0 or -128                  | 255 or 127                 |
| 8-bit  | signed          | Binary         | -128                       | 127                        |
| 16-bit | unsigned        | unsigned short | 0                          | 65,535                     |
| 16-bit | signed          | 2's Complement | -32,768                    | 32,768                     |
| 32-bit | unsigned        | Binary         | 0                          | 4,294,967,295              |
| 32-bit | signed          | 2s complement  | -2,147,483,648             | 2,147,483,647              |
| 64-bit | unsigned        | Binary         | 0                          | 18,446,744,073,709,551,615 |
| 64-bit | signed          | 2s complement  | -9,223,372,036,854,775,808 | 9,223,372,036,854,775,808  |


| Type   | Meaning               | C typedef declaration             |
|--------|-----------------------|-----------------------------------|
| int8   | unsigned 8-bit value  | typedef unsigned char int8;       |
| sint8  | signed 8-bit value    | typedef signed char sint8;        |
| int16  | unsigned 16-bit value | typedef unsigned short int16;     |
| sint16 | signed 16-bit value   | typedef signed short sint16;      |
| int32  | unsigned 32-bit value | typedef unsigned long int32;      |
| sint32 | signed 32-bit value   | typedef signed long int32;        |
| int64  | unsigned 64-bit value | typedef unsigned long long int64; |
| sint64 | signed 64-bit value   | typedef signed long long sint64;  |
      

####Calling/Return Convention

| Iteration | a  | b  | c  | d  | e  |
|-----------|----|----|----|----|----|
| 1st       | 10 | 9  | 8  | 7  | 2  |
| 2nd       | 16 | 15 | 14 | 13 | 13 |
| 3rd       | 22 | 21 | 20 | 19 | 14 |
| 4th       | 28 | 27 | 26 | 25 | 20 |
| 5th       | 34 | 33 | 32 | 31 | 26 |


| Parameter                     | Value Sought |
|-------------------------------|--------------|
| Starting address of func      | 0xC2CC       |
| Ending address of func        | 0xC2D8       |
| Register holding w            | R12          |
| Register holding x            | R13          |
| Register holding y            | R14          |
| Register holding z            | R15          |
| Register holding return value | R12          |


####Cross language build constructs

What is the role of the extern directive in a .c file? Hint: check out the external variable Wikipedia page.   

The extern directive in a .c file tells the complier the name of the function, return type, and parameters of the function that is located in a different area of the build path.   

What is the role of the .global directive in an .asm file (used in lines 28-32)? Hint: reference section 2.6.2 in the MSP 430 Assembly Language Tools v4.3 User's Guide.   

The .global directive in an .asm file lets the assembler know th make the label in memory global so that it can be used anywhere throughout the build path.    


##Lab 4

####Required Functionality

Required functionality involved creating an etch-a-sketch program using the directional buttons of the LCD. Pressing the auxiliary button (SW3) toggled the paint mode between solid squares and filled squared. To do this I created a C program I created a C program that took in the button input and adjusted the etch-a-sketch accordingly. To implement the auxiliary button I created another parameter called color to deterine if the block should be solid or clear. I adjusted the assembly so thata color value of 1 would draw a solid block (#0xFF) while a color value of 0 would draw a clear block (#0x00). 

```
else if (AUX_BUTTON == 0) {		// Aux
	while(AUX_BUTTON == 0);
	button_press = TRUE;
	if (color == BLACK) color = WHITE;
	else if(color == WHITE) color = BLACK;
}
```

####B Functionality

B Functionality required creating a box that would bounce around the screen. I implemented this by removing the button inputs and replacing them with if statments to change the direction of the box when it hits the edge of the screen. An example of the if statement is shown bellow:

```
if (xVel == 1) {
	x++;
	if (x>=11) xVel=0;
}
if (xVel == 0) {
      x--;
	if (x<=0) xVel=1;
}
```

####A Functionality

Afunctionality required creating a basic pong game with 1 paddle and a bouncing ball. The user can control the paddle, moving it up and down. To implement the A functionality I added a draw paddle method in both the code and the assembly. This allowed the player to move his paddle up and down on the screen. Additionally the draw block method in assembly was changed so that it would draw a ball instead of a block. I did this by removing the block loop and hard coding the hex necessary to make a ball. I also adjusted the if statements so that ball would change x direction only if it hit the paddle. However, I did not completly finish all of A funcationality.

####Debugging

My main problem in lab 4 was when I would go to test my B and A functionality I would get an error saying that that drawBlock method had to few argumetns. I think this has something to do with that Required function had a 3rd argument color while A and B did not. I fixed the code by removing an extra comma in the extern void drawBlock command. I then experenced the problem where my code would move the ball around too fast. I fixed this problem by implementing a drawDellay method to slow down the draw code.

###Documentation

I did not recieve any help on the nab

