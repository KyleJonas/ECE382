ECE382_Lab2
===========
Kyle Jonas M6

Subroutines - "Cryptography"

### Objectives

The objective of Lab 2 is to practice writing subroutines, and then implement them in creating a program that decrypts an encrypted message using a simple encryption technique.

Required Functionality

* Message will be of arbitrary length, but the key will be one byte long
* Key and encrypted message will be given to you

B Functionality

* Program must decrypt messages with arbitrarily long keys

A Functionality

* Decrypt a message without knowledge of its key

### Preliminary Design

The goal of the lab is to xor the test string with the key and then output the answer into a plainText location.

![Prelim Design](https://github.com/KyleJonas/ECE382_Lab2/blob/master/Images/2014-09-19%2001.41.20.jpg?raw=true "Prelim Design")

### Flow Chart

![Flow Chart](https://github.com/KyleJonas/ECE382_Lab2/blob/master/Images/2014-09-19%2002.10.15.jpg?raw=true "Flow Chart")

For B Functionality on the flow chart key length is used to determine when to jump back to the start of the key. Test length is also used in order to detrmine when to jump to the end of the program.

### Code

##### Variables
```
testString:	.byte	0xf8,0xb7,0x46,0x8c ; ...continues for B Functionality
key:		.byte   0xac,0xdf,0x23

plainText:	.equ	0x0200

testLength:	.equ	0x52	; 82 in decimal, length of B functionality
keyLength:	.equ	0x03	; 3 parts to key
```
The initial variables are set for the test string, plain text loacation, length og the test string, key, and the length of the key.

##### Main/Load Registers
```
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
```
The main code loads the registers with the variables valuse. It also sets the key location and length in order to give a call location when then key needs to be reset back to the begining.

##### Subroutines
```
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
```
The subroutines Xor the key with the test string, stores the byte to the output, checks the test string length to see if you are at the end of the funcationalityl, and resets the key after the last byte xor'ed.

### Debugging

By creating good pseducode and a preliminary design I was able to avoid the bulk of debugging. The only issue 
I had to resolve was jumping to the correct location when the Key resets. By removing the KeyBeginning section out the subroutines I was able to correctly reset the key after it has reached the end of its length, instead of resetting the key after every test.

### Test Methodology

To test the decryptor I entered the testStrng and would perform the required decryption. I would then check the memory location looking at the values as ASCII to see if they displayed english instead of jumbled valuses.  

### Conclusion

Lab 2 was verry similar to Lab 1 in the initial code and setting up the registers. The lab differed by relying on more code used in the subroutine. The main take-away from the lab was that I can use subroutines to protect my code and to make implementing additional functionality easier. For example, implemnting 

### Documentation

I used the lab templet given to us in class as well as implementing the preliminary design as a starting point for my code.
