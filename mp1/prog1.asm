; Partners: iakella2 and Ahchin2
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming lab, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000

;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
  LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z     ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop



PRINT_HIST
Partners: Iakella2 and Ahchin2


 Paragraph: The machine program asks us to print out a histogram. We are given the numbers of ASCII values starting at memory x3F00. These addresses
;contain hexadecimal values. Upon first look, it appears we could just take out these values and print them out. The problem arises when one realizes that
;taking the values as is will print out ASCII values. To remedy this, we must print out hexadecimal. A way to accomplish was given to us in the lab. Given
;a value, we copy the first four bits with a loop (extract) and copy those numbers into the last four bits of another register. With this, we can
;print out one of the digits in hexadecimal. Since a hexadecimal value in LC3 holds 16 bits where each bit holds 4 binary digits, we create
;a loop to repeat the process 4 times clearing the register we used to print everytime we go through the loop. This code will print out the hexadecimal value
;put in the memory. Before this however, we need to print the value it represents with a space. This can be done by putting in an ASCII value and incrementing it everyline.
;Now that we have printed out a line, we can repeat this process using a register to hold the memory value and incrementing it by 1 and repeating 27 times. 

;Table of registers used in this part of the code
;    R0 intermittently holds any value that is to be outputted.
;    R1 is used as a bit counter to count down in segments of 4 and as a bin counter to make sure the code runs 27 times displaying '@' to 'Z'.
;    R2 holds the data of the histogram that is to be outputted to the screen.
;    R3 serves as a counter for the 'BIG' loop to ensure the inner loops run four times for the four hex values that are outputted. 
;    R4 holds the starting address of the histogram and is incremented throughout the code.
;    R5 holds the value at the memory location held in R4.
;    R6 is holds the ASCII value for '@'.
         			  
	LD R4, HIST_ADDR	;
	LD R6, BRUH 		;Loads R6 with the ASCII value for '@'
	LD R1, NUM_BINS 	;Initializes counter to 27	
        LDR R5, R4, #0 		;
                
LOOP 	ADD R0, R0, R6 		;Copies value of R6 into R0
	OUT 			;Prints to screen
     	LD R0, SPACE 		;Load the Hex value of A space
     	OUT  			; 			
        LD R3, FOUR		; A counter
                
BIG	ADD R3, R3, #0		; Set cc
	BRnz FIN		;
                
EXTRACT	AND R2, R2, #0		;Clear destination register R2			
	AND R1, R1, #0		;Clear bit counter R1
	ADD R1, R1, #4		;Initialize bit counter to 4
                
YEET	ADD R2, R2, R2		;Shift R2 to make space for next bit
  	ADD R5, R5, #0
  	BRzp SKIP		;Check if MSB of R3 is 0
  	ADD R2, R2, #1		;If MSB of R3 is 1, add 1 to R2
                
SKIP	ADD R5, R5, R5		;Left shift R3
	ADD R1, R1, #-1		;Decrement bit counter
	BRp YEET		;If counter positive, repeat EXTRACT_LOOP
        ADD R3, R3, #-1		; Decrement outer counter
        AND R0, R0, #0		; Reset R0
	ADD R0, R2, #-9		;R0 = R2 - 9
	BRnz NUMERICAL		;If digit is between 0 and 9, go to NUMBERICAL loop
	LD R0, A					;Otherise, load ASCII of 'A'
	ADD R0, R0, R2		;R0 = R2 +'A' 
	ADD R0, R0, #-10	;R0 = R2 + 'A' - 10
	OUT			;
        BRnzp BIG		;
                
NUMERICAL LD R0, ZERO		;Load ASCII of '0'
	ADD R0, R0, R2    	;R0 <-- R2
        OUT			;
        BRnzp BIG		;

FIN	ADD R4, R4, #1		;Increment memory address
	LDR R5, R4, #0		;Load Value at memory address into R5
        AND R0, R0, #0 		;Clear R0
	LD R0, NEWLINE 		;Places new line feed in R0
	OUT 			;Prints to screen 
        AND  R0, R0, #0 	;Clears R0
	ADD R6, R6, #1  	;Increment R6 to point to next ASCII character
	ST R6, BRUH 		;Reroute R6 to memory 
	LD R1,NUM_BINS		;Call our counter into R1
	ADD R1, R1, #-1		;Subtract it by 1
	ST R1, NUM_BINS		;Store it back in memory
	ADD R1, R1, #0		;Setcc
	BRnp LOOP 		;Loop back until counter is zero
		 				
	DONE	HALT		;Done


; the data needed by the program
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00     ; histogram starting address
STR_START	.FILL x4000	; string starting address
BRUH		.FILL x40	; Holds the ASCII value for "@"
SPACE		.FILL x20	;
NEWLINE		.FILL x000A 	; New line feed
ZERO 		.FILL #48	;
A		.FILL #65	;
FOUR		.FILL #4	;
;
; 
; the directive below tells the assembler that the program is done
; (so do not write any code below it!)

	.END

