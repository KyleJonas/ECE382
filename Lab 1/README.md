ECE382 Lab1
===========
Assembly Language - "A Simple Calculator"

### Objectives

The goal of Lab 1 was to create a simple assembly language calculator that interprets a series of operands and operations and stores the results to memory.

Required Functionality:

* ADD_OP from value 0x11
* SUB_OP from value 0x22
* CLR_OP from value 0x44
* END_OP from value 0x55

B Functionality:

* If a result exceeds 255, it is set to the maximum value of 255. If a result is less than 0, it is set to the minimum value of 0

A Functionality:

Implement a multiply operation

* Mul_OP from value 0x33

### Preliminary Design

I used the inclass board work to help me create my inital design and to write psedocode for the calculator

![Prelim Design](https://github.com/KyleJonas/ECE382_Lab1/blob/master/Pictures/Prelim_Design.jpg?raw=true "Prelim Design")

![Pseudo Code](https://github.com/KyleJonas/ECE382_Lab1/blob/master/Pictures/Pseduo_Code.jpg?raw=true "Pseudo Code")

### Flow Chart

![Flow Chart](https://github.com/KyleJonas/ECE382_Lab1/blob/master/Pictures/Flow_Chart.jpg?raw=true "Flow Chart")

For B Functionality on the flow chart Add and Sub call the tooBig_tooSmall subroutine that check to make sure the answers are in the correct range.

### Code

##### Initialize Program
```
			; ALLWAYS LEAVE R5 POINTING TO AN OPPERATION

main:
	mov.w   #__STACK_END,SP			; BOILERPLATE	Initialize stackpointer
	mov.w   #WDTPW|WDTHOLD,&WDTCTL 		; BOILERPLATE	Stop watchdog timer

	mov.w	#store, R10			; Register 10 is a pointer to RAM

	mov.w	#testString, R5			; Register 5 is a pointer to the test string

						; Register 6 used as accumulator
	mov.b	0(R5),R6			; Initializes accumulator then points at operation
	inc.w	R5

```

Initialize Program uses sections of the lec6.asm code with modifications to meet my codes need.

* R10 is intalized and output area, "store" in RAM
* R5 refers to a test string to read the operations and operands
* R6 is used as and accumulator

The accumulator R6 is set with the first number in the test string so that R5 can then always be pointing to an opperation.

##### Check Operation
```
start:					; check which operation to perform
	cmp.b	#addOp, 0(R5)
	jeq		check11

	cmp.b	#subOp, 0(R5)
	jeq		check22

	cmp.b	#multOp, 0(R5)
	jeq		check33

	cmp.b	#clrOp, 0(R5)
	jeq		check44

	cmp.b	#endOp, 0(R5)
	jeq		check55

	jmp start
```

This section determines the operation that needs to be performed by comparing R5 to the value of each operation, and then jumps to the correct location in the code.

##### ADD_OP
```
check11:				; ADD
	inc.w	R5
	add.b	0(R5), R6		; Adds value from string 0(R5) to accumulator R6
	call	#tooBig_tooSmall	; check if larger than 255
	mov.b	R6, 0(R10)		; Performs operation, stores in output 0(R10)
	inc.w	R10
	inc.w	R5
	jmp		start
```

ADD_OP takes the next value from the test string and adds it with the accumulator value, and then stores the result in the output. The subroutine tooBig tooSmall is also called to see if the answer is larger than 255 for B functionality.

##### SUB_OP
```
check22:				; SUBTRACT
	inc.w	R5
	sub.b	0(R5), R6		; subtracts the 2nd operand 0(R5) from the first in the accumulator R6
	call	#tooBig_tooSmall	; check if smaller than 00
	mov.b	R6, 0(R10)
	inc.w	R10
	inc.w	R5
	jmp		start
```

SUB_OP takes the next value from the test string and subtracts it from the accumulator value, and then stores the result in the output. Again, tooBig tooSmall is also called to see if the answer is smaller than 0 for B functionality.

##### CLR_OP
```
check44:				; CLEAR
	mov.b	#0x00, R6
	mov.b	R6, 0(R10)		; Stores 00 into the output
	inc.w	R10
	inc.w	R5
	mov.b	0(R5), R6
	inc		R5
	jmp		start
```

ClR_OP clears the accumulator and then ouputs 00.

##### END_OP
```
check55:				; END
	jmp		wait

wait:
	jmp		wait
```

Performs and infinte loop to end the program

##### B Functionality
```
		; Subroutine for B Functionality
tooBig_tooSmall:
	tst		R6		; Check for B functionality
	jn		tooSmall	; If R6 negative, jmp too small
	cmp.b	#0x00FF, R6
	jhs		tooBig		; R6 larger than 255
	ret

tooSmall:
	mov.b	#0x00, R6
	ret

tooBig:
	mov.b	#0xFF, R6
	ret
```

The subroutine tooBig tooSmall is used to determine if the value of the add is larger than 255 or subtract is smaller than 0. If larger than 255 the code will ouput 255 to the string and if smaller than 0 the code will ouput 0 to the string By making this a subroutine I was able to avoide duplicating the code by having to write it in both add and subtract. This was my first subroutine that I have written in assembly so I had to verify my syntax with Cadet Bodins in order to fix my code. I had to use 00FF to compare with the accumulator to prevent losing information by just looking at it as a bit. For example 0x1100 is larger than 255 in decimal but the output would not be corrected since the code would look at 0x00 instead of using the whole word.

##### A Functionality - MUL_OP
```
check33:				; MULTIPLY
	inc.w	R5
	jmp		check44
	;inc.w	R5			; could't implement multiplication
	;mov.b				; used clear to skip over to the next opperation
	;jmp		start
```

I did not implement the A functionality so I incremented R5 and called CLR in order to skip over the multiply command.

### Debugging

The main issue I had with my code was implementig the subroutine tooBig tooSmall. I had to correct for sytnax mistakes messing up the return. Additionaly the tooBig determiniation was incorrect becuase I was using 0xFF instead of 0x00FF. This cut of the rest of the world and would not alow me to jump when I needed to since I was only using 0xFF. After I correct the tooBig check my code didnt have many debuging issues. Writing good psedudo helps eliminate some debugging.


### Test Methodology

Test the calculator I would input my own test string and perform the required opperations to make sure that I got the correct results. If I didnt get my expected value I whould know something was up with the code for that opperation and I could go back to that location to look in depth and fix the error.

### Conclusion

My main take-away from this lab was how to use and implement subroutines. This allowed me to minimize the overall code required and better format the program. It also tought me I need to learn how to multiply in assembly.

### Documentation

I referenced the ECE 382 Lab Notebook page and Taylor Bodin's write up as an example help me write my own report.I implemented the inclass board work for the pseducode and preliminary design. Cadet Bodin also helped me with the B Functionality and understanding subroutines and their syntax.
