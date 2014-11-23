;-------------------------------------------------------------------------------
;	Name:		Kyle Jonas
;	Class:		ECE 382
;	MCU:		MSP430G2553
;	Lab 1		Calculator
;
;	Documentation: In class board work for pseducode help.
;				   I referenced Taylor Bodin min_max code for help with the B Functionality and implementing a subroutine
;
;	Code completes B functionality with add, subtract, clear, and end
;
;	Skipped over multiplication by using inc and then performing clear
;
;-------------------------------------------------------------------------------
	.cdecls C,LIST,"msp430.h"	; BOILERPLATE	Include device header file
 	.text						; BOILERPLATE	Assemble into program memory
	.retain						; BOILERPLATE	Override ELF conditional linking and retain current section
	.retainrefs					; BOILERPLATE	Retain any sections that have references to current section
	.global main				; BOILERPLATE	Project -> Properties and select the following in the pop-up
								; Build -> Linker -> Advanced -> Symbol Management
								;    enter main into the Specify program entry point... text box

	.data
	.bss	store, 0x40			; 40 (hex) free bytes in data memory, access the the "store" label
	.text


				; Calculator String
testString:	.byte	0x03,0x11,0x06,0x22,0x05,0x44,0x02,0x33,0x03,0x55


addOp:		.equ	0x11
subOp:		.equ	0x22
multOp:		.equ	0x33
clrOp:		.equ	0x44
endOp:		.equ	0x55

;-------------------------------------------------------------------------------
;           						main
;-------------------------------------------------------------------------------
				; ALLWAYS LEAVE R5 POINTING TO AN OPPERATION

main:
	mov.w   #__STACK_END,SP				; BOILERPLATE	Initialize stackpointer
	mov.w   #WDTPW|WDTHOLD,&WDTCTL 		; BOILERPLATE	Stop watchdog timer

	mov.w	#store, R10					; Register 10 is a pointer to RAM

	mov.w	#testString, R5				; Register 5 is a pointer to the test string

										; Register 6 used as accumulator
	mov.b	0(R5),R6					; Initializes accumulator then points at operation
	inc.w	R5

start:									; check which operation to perform
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

check11:								; ADD
	inc.w	R5
	add.b	0(R5), R6					; Adds value from string 0(R5) to accumulator R6
	call	#tooBig_tooSmall			; check if larger than 255
	mov.b	R6, 0(R10)					; Performs operation, stores in output 0(R10)
	inc.w	R10
	inc.w	R5
	jmp		start

check22:								; SUBTRACT
	inc.w	R5
	sub.b	0(R5), R6					; subtracts the 2nd operand 0(R5) from the first in the accumulator R6
	call	#tooBig_tooSmall			; check if smaller than 00
	mov.b	R6, 0(R10)
	inc.w	R10
	inc.w	R5
	jmp		start

check33:								; MULTIPLY - A Functionality
	inc.w	R5
	jmp		check44
	;inc.w	R5							; could't implement multiplication
	;mov.b								; used clear to skip over to the next opperation
	;jmp		start

check44:								; CLEAR
	mov.b	#0x00, R6
	mov.b	R6, 0(R10)					; Stores 00 into the output
	inc.w	R10
	inc.w	R5
	mov.b	0(R5), R6
	inc		R5
	jmp		start

check55:								; END
	jmp		wait

				; Subroutine for B Functionality
tooBig_tooSmall:
	tst		R6							; Check for B functionality
	jn		tooSmall					; If R6 negative, jmp too small
	cmp.b	#0x00FF, R6
	jhs		tooBig						; R6 larger than 255
	ret

tooSmall:
	mov.b	#0x00, R6
	ret

tooBig:
	mov.b	#0xFF, R6
	ret

				; End Loop
wait:
	jmp		wait




;-------------------------------------------------------------------------------
;           System Initialization
;-------------------------------------------------------------------------------
	.global __STACK_END				; BOILERPLATE
	.sect 	.stack					; BOILERPLATE
	.sect   ".reset"				; BOILERPLATE		MSP430 RESET Vector
	.short  main					; BOILERPLATE

