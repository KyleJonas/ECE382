;-------------------------------------------------------------------------------
; MSP430 Assembler Code Template for use with TI Code Composer Studio
;
;	Name:		Kyle Jonas
;	Class:		ECE 382
;	MCU:		MSP430G2553
;	Lab 2		subroutine - cryptography
;
;-------------------------------------------------------------------------------
            .cdecls C,LIST,"msp430.h"       ; Include device header file

;-------------------------------------------------------------------------------
            .text						; BOILERPLATE	Assemble into program memory
			.retain						; BOILERPLATE	Override ELF conditional linking and retain current section
			.retainrefs					; BOILERPLATE	Retain any sections that have references to current section
			.global main				; BOILERPLATE	Project -> Properties and select the following in the pop-up
										; Build -> Linker -> Advanced -> Symbol Management
										;    enter main into the Specify program entry point... text box


testString:	.byte	0xf8,0xb7,0x46,0x8c,0xb2,0x46,0xdf,0xac,0x42,0xcb,0xba,0x03,0xc7,0xba,0x5a,0x8c,0xb3,0x46,0xc2,0xb8,0x57,0xc4,0xff,0x4a,0xdf,0xff,0x12,0x9a,0xff,0x41,0xc5,0xab,0x50,0x82,0xff,0x03,0xe5,0xab,0x03,0xc3,0xb1,0x4f,0xd5,0xff,0x40,0xc3,0xb1,0x57,0xcd,0xb6,0x4d,0xdf,0xff,0x4f,0xc9,0xab,0x57,0xc9,0xad,0x50,0x80,0xff,0x53,0xc9,0xad,0x4a,0xc3,0xbb,0x50,0x80,0xff,0x42,0xc2,0xbb,0x03,0xdf,0xaf,0x42,0xcf,0xba,0x50,0x8f
key:		.byte   0xac,0xdf,0x23

plainText:	.equ	0x0200

testLength:	.equ	0x52	; 82 in decimal, length of B functionality
keyLength:	.equ	0x03	; 3 parts to key

;-------------------------------------------------------------------------------
main:
			mov.w   #__STACK_END,SP				; BOILERPLATE	Initialize stackpointer
			mov.w   #WDTPW|WDTHOLD,&WDTCTL 		; BOILERPLATE	Stop watchdog timer

;-------------------------------------------------------------------------------
                                            ; Main loop here
;-------------------------------------------------------------------------------
            ; load registers with necessary info for decryptMessage here

            mov.w	#plainText, R14			; Register 14 is a pointer to RAM

            mov.w	#testString, R12		; Register 12 is a pointer to the test string
            mov.w	#testLength, R6			; register 6 pointer to test length

			; sets key and key length to beginning
keyBeginning:
            mov.w	#key, R13				; Register 13 pointer to key
            mov.w	#keyLength, R8			; Register 8 pointer to key length

            call    #decryptMessage

end:    jmp     end

;-------------------------------------------------------------------------------
                                            ; Subroutines
;-------------------------------------------------------------------------------

decryptMessage:		; performs decrption using xor

			mov.b	@R12+, R10				; move to next test string Byte
			mov.b	@R13+, R11				; move to next key Byte

			xor.b	R11, R10			; xor key with message

			call	#storeMessageByte

			inc.w	R14						; inc output location
			clrz							; makes sure zero not leftover
			dec.w	R6						; dec test length
			jz		end						; if no more left in test length, end program

			clrz
			dec.w	R8						; dec key length
			jz		keyBeginning			; return to start of the key
			jne		decryptMessage			; perform another decryption

            ret


storeMessageByte:	; saves byte to output

			mov.b	R10, 0(R14)				; moves byte to plain text location
            ret

;-------------------------------------------------------------------------------
;           Stack Pointer definition
;-------------------------------------------------------------------------------
            .global __STACK_END
            .sect    .stack

;-------------------------------------------------------------------------------
;           Interrupt Vectors
;-------------------------------------------------------------------------------
            .sect   ".reset"                ; MSP430 RESET Vector
            .short  main
