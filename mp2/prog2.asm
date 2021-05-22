;MP2 calls for 4 parts: receiving an input, evaluating the expression, mathematical calculations, and outputting the answer as hexadecimal. Luckily two
;out of the four were given to us in class and as a part of our last mp(part 1 and 4 respectively). In order to evaluate an expression, we made a
;subroutine that would check every type of value we would encounter in the input and ensure it was a valid input, if not, we would print out an “invalid
;expression” string to the monitor and halt the program. Since the input is postfix, it is much easier to check if the stack has underflow as there will
;always be two numbers pushed (checked) before any operations (if valid). For the operations, we would check by subtracting by its ASCII value and
;branching (checking for 0). If true, we would pop out two of the values in the stack, call the respective mathematical subroutine, and push the
;calculated value onto the stack. Checking for numbers was done nearly the exact same way but instead of having to do an operation we would just push
;the number to the stack if it was determined that the number was a valid input. To program the operations themselves, we thought about what each did at
;its most basic form. For example, division is just counting the number of times one number can be subtracted from another which could be implemented using
;a counter and subtracting a number until it reached a number less than or equal to 0. After going through the operations we would reach PRINT_HEX which
;would be our MP1 code that outputs the result to the screen in hexadecimal format.
;partners: ahchin2, iakella2

.ORIG x3000
INPUT
			LD R0, SPACE        			; Load R0 with the ascii character for " "    
			OUT            				; Output to the screen
			GETC            			; Allows user to input an expression
			OUT             			; Output to screen
			JSR EVALUATE         			; Get an input and start again
			BR INPUT        			; Get a new Input after evaluating
INVALID
			LEA R0, INVALID_INPUT     		; Loads R0 with the string if input is invalid
			PUTS              			; Output string to the screen
			HALT              			; Halts the program

PRINT_HEX
LOOP	 
        		LD R3, FOUR            			; Initializes R3 as a counter
           	 
BIG    
			ADD R3, R3, #0            		; Set cc
			BRnz DONE            			;                       	 
           	 
EXTRACT    
			AND R2, R2, #0            		; Clear destination register R2       	 
			AND R1, R1, #0            		; Clear bit counter R1
			ADD R1, R1, #4            		; Initialize bit counter to 4
           	 
YEET    
			ADD R2, R2, R2            		; Shift R2 to make space for next bit
			ADD R5, R5, #0        			;
			BRzp SKIP            			; Check if MSB of R5 is 0
			ADD R2, R2, #1            		; If MSB of R3 is 1, add 1 to R2
           	 
SKIP    
			ADD R5, R5, R5            		; Left shift R3
			ADD R1, R1, #-1            		; Decrement bit counter
			BRp YEET            			; If counter positive, repeat EXTRACT_LOOP
			ADD R3, R3, #-1            		; Decrement outer counter
			AND R0, R0, #0            		; Reset R0
			ADD R0, R2, #-9            		; R0 = R2 - 9
			BRnz NUMERICAL            		; If digit is between 0 and 9, go to NUMBERICAL loop
			LD R0, A            			; Otherise, load ASCII of 'A'
			ADD R0, R0, R2            		; R0 = R2 +'A'
			ADD R0, R0, #-10        		; R0 = R2 + 'A' - 10
			OUT                    			; Output to the screen
			BRnzp BIG            			;

NUMERICAL
			LD R0, ZERO            			; Load ASCII of '0'
			ADD R0, R0, R2       			; R0 <-- R2
			OUT                    			; Output to the screen
			BRnzp BIG            			; Return to 'BIG' loop

 	 
FIN    
        		BRnp LOOP             			; Loop back until counter is zero


;R0 - character input from keyboard
;R6 - current numerical output


EVALUATE

			AND R3, R3, #0          		; Clear R3
			AND R4, R4, #0             		; Clear R4
			AND R2, R2, #0            		; Clear R2
			ST R6, SAVER6         			; Save value of R6 by storing into blank space
			ST R7, SAVER7        			; Save value of R6 by storing into blank space
CHECK_EQUAL           	 

			LD R6, NEG_ASCII_EQUAL    		; Load R6 with the negative of the ascii value of equal sign
			ADD R2, R0, R6            		; Subtracting the ascii with that of '=' to see if it equals 0 store in R2
			BRnp CHECK_SPACE        		; If not equal to zero, jump to 'CHECK_SPACE' loop
			JSR POP                			; If zero, it is an equal sign so you must pop the most recent stack value for your result
			LD R3, STACK_TOP        		; Load R3 with the stack_top location
			LD R4, STACK_START        		; Load R4 with the stack_start location
			NOT R4, R4            			;
			ADD R4, R4, #1            		; 2s complement of R4
			ADD R3, R3, R4            		; R3 <-- R3 - R4
			BRnp INVALID            		; The stack is invalid
			AND R5, R5, #0            		; Clear R5
			ADD R5, R5, R0            		; Update R5 with the correct value	
AND R4, R4, #0			
ADD R4, R5, #0 			; hold original R5 value
			BRnzp PRINT_HEX            		; Go to 'PRINT_HEX' loop

CHECK_SPACE

			LD R6, NEG_ASCII_SPACE    		; Load R6 with the negative of the ascii value of space (" ")     	 
			ADD R2, R0, R6            		; Add R6 to the inputted character in R0 and save in R2
			BRz INPUT           			; If there is a space  ask for another input and go through evaluate again
    
    
CHECK_EXP

			LD R6, NEG_ASCII_EXP        		; Load R6 with the negative of the ascii value of '^'   
			ADD R2, R0, R6            		; Add R6 to the inputted character in R0 and save in R2
			BRnp CHECK_NUMBER        		; If it is not an exponent sign, jump to 'CHECK_NUMBER'
			JSR POP                			; If it is an exponent, pop from the stack
			ADD R5, R5, #0            		;
			BRp INVALID            			; Check for underflow, if true, go to 'INVALID'
			ADD R4, R4, R0            		; Copying popped value into R4
			JSR POP                			; Pop the next value for the math operation
			ADD R5, R5, #0            		;
			BRp INVALID            			; Check for underflow, if true, go to 'INVALID'
			ADD R3, R3, R0            		; Copy second popped value into R3
			JSR EXP                			; Go to 'EXP' loop to perform operation
			JSR PUSH            			; Push result to the stack
			BRnzp INPUT            			; Get another input

    
CHECK_NUMBER

			LD R6, NEG_ASCII_0        		; Load R6 with the negative of the ascii value of '0'          	 
			ADD R2, R0, R6             		; Add R6 to the inputted character in R0 and save in R2
			BRn CHECK_PLUS            		; If it is less than '0' go to 'CHECK_PLUS' loop
			LD R6, NEG_ASCII_9        		; Load R6 with the negative of the ascii value of '9'
			ADD R2, R2, R6            		; Add R6 to the inputted character in R0 and save in R2
			BRp CHECK_PLUS       			; If it is greater than '9' go to 'CHECK_PLUS' loop
			LD  R6, NEG_ASCII_0    			; Load R6 with the negative of the ascii value of '0'  
			ADD R0, R0, R6        			; Add R6 to the inputted character in R0 and save in R0
			JSR PUSH            			; Push number to stack
        		BRnzp INPUT            			; Get another input


CHECK_PLUS             	 

			LD R6, NEG_ASCII_PLUS    		; Load R6 with the negative of the ascii value of '+'  
			ADD R2, R0, R6            		; Add R6 to the inputted character in R0 and save in R2
			BRnp CHECK_MIN            		; If positive, branch to 'CHECK_MIN'
			JSR POP               		 	; If it is a plus sign, pop value from stack           	 
			ADD R5, R5, #0            		; Check the first value
			BRp INVALID            			; If R5 is positve, underflow occurred and expression is invalid        	 
			ADD R4, R4, R0            		; Copy popped value into R4
			JSR POP                			; Pop second value     	 
			ADD R5, R5, #0            		; Checking the second  value
			BRp INVALID            			; If R5 is positve, underflow occurred and expression is invalid
			ADD R3, R3, R0            		; Copy popped value into R3
			JSR PLUS            			; Call "PLUS" subroutine to perform math    	 
			JSR PUSH            			; Push result to stack
			BRnzp INPUT            			; Get another input
 
CHECK_MIN            	 
   	 
			LD R6, NEG_ASCII_MIN    		; Load R6 with the negative of the ascii value of '-'
			ADD R2, R0, R6            		; Add R6 to the inputted character in R0 and save in R2
			BRnp CHECK_MUL            		; If it is not a minus sign, go to 'CHECK_MUL'
			JSR POP                			; If it is, pop value from stack
			ADD R5, R5, #0            		;
			BRp INVALID            			; Check for underflow
			ADD R4, R4, R0            		; Copy value popped into R4
			JSR POP               		 	; Pop second value
			ADD R5, R5, #0            		;
			BRp INVALID            			; Check for underflow
			ADD R3, R3, R0            		; Copy value popped into R3
			JSR MIN               		 	; Call "MIN" subroutine to perform math
			JSR PUSH            			; Push result to stack
			BRnzp INPUT            			; Get another input

CHECK_MUL

			LD R6, NEG_ASCII_MUL       		; Load R6 with the negative of the ascii value of '*'
			ADD R2, R0, R6           		; Add R6 to the inputted character in R0 and save in R2
			BRnp CHECK_DIV           		; If it is not a multiply sign, go to 'CHECK_DIV'
			JSR POP               			; If it is, pop value from stack
			ADD R5, R5, #0           		;
			BRp INVALID           			; Check for underflow
			ADD R4, R4, R0           		; Copy value popped into R4
			JSR POP               			; Pop next value
			ADD R5, R5, #0           		;
			BRp INVALID           			; Check for underflow
			ADD R3, R3, R0           		; Copy value popped into R3
			JSR MUL               			; Call "MUL" subroutine to perform math
			JSR PUSH               			; Push result to stack
            		BRnzp INPUT           			; Get another input


CHECK_DIV

			LD R6, NEG_ASCII_DIV       		; Load R6 with the negative of the ascii value of '/'
			ADD R2, R0, R6           		; Add R6 to the inputted character in R0 and save in R2
			BRnp INVALID           			; If it is not a divison sign, go to 'INVALID' because input failed all valid checks
			JSR POP               			; If it is, pop value from stack
			ADD R5, R5, #0           		;
			BRp INVALID           			; Check for underflow
			ADD R4, R4, R0           		; Copy popped value into R4
			JSR POP               			; Pop second value
			ADD R5, R5, #0           		;
			BRp INVALID           			; Check for underflow
			ADD R3, R3, R0           		; Copy popped value into R3
			JSR DIV               			; Call "DIV" subroutine to perform math
			JSR PUSH               			; Push result to stack
			BRnzp INPUT        			; Get another input

FINISHED                    					; Restore register values and ends the subroutine
			LD R6, SAVER6          			; Reloads R6 with the saved value
			LD R7, SAVER7          			; Reloads R7 with saved value
			RET            				; Return

;
; Input R3,R4
; Output R0

PLUS    
            		ADD R3, R3, R4            		; R3 <-- R3 + R4
            		ADD R0, R3, #0           		; R0 <-- R3
         		RET                    			; Return

MIN    
			NOT R4, R4             			; Not R4
			ADD R4, R4, #1            		; Adds one to end up with 2s complement
			ADD R0, R4, R3            		; R0 <-- R3 + R4            	 
            		RET                   	 		; Return

MUL   	 
			ADD R4, R4, #-1           		; R4 <-- R4 - 1
			BRz #8               			; If zero, R4 = 1 initially
			BRn #10           			; If negative, R4 = 0 initially
			ADD R4, R4, #1           		; Revert R4 value
			AND R2, R2, #0           		; Clear R2
			ADD R2, R3, #0           		; R2 <-- R3
			ADD R4, R4, #-1           		; R4 <-- R4 - 1
			ADD R3, R3, R2           		; R3 <-- R3 + R2
			ADD R4, R4, #-1           		; R4 <-- R4 - 1
			BRp #-3               			; If positive, go back two steps
			AND R0, R0, #0           		; If R4 = 1 initially, clear R0
			ADD R0, R3, #0           		; R0 <-- R3
			RET                   			; Return to main function
			LD R0, ZER           			; If R4 = 0 initially, load '0' into R0
			RET               			; Return

DIV    
			ADD R4, R4, #-1       			; R4 <-- R4 - 1
			BRn INVALID           			; If negative, R4 = 0 initially and expression is invalid
			ADD R4, R4, #1       			; Revert R4 value
			NOT R4, R4          			;
			ADD R4, R4, #1          		; 2s complement of value in R4
			LD R2, NEGONE           		; Load '-1' into R2
			ADD R2, R2, #1           		; R2 <-- R2 + 1
			ADD R3, R4, R3           		; R3 <-- R3 + R4
			BRzp #-3               			; If not negative, branch
			ADD R0, R2, #0           		; R0 <-- R2
			RET                   			; Return

EXP
			ADD R3, R3, #-1				; Decrement R3 to check if expression is 1#^
			BRz #23					; If true, branch
			ADD R3, R3, #1				; Increment R3 back to initial value
			ADD R4, R4, #-1           		; R4 <-- R4 - 1
			BRn #18           			; If negative, R4 = 0 initially
			BRz #9               			; If zero, R4 = 1 initially
			AND R5, R5, #0           		; Clear R5
			AND R1, R1, #0           		; Clear R1
			AND R2, R2, #0           		; Clear R2
			ADD R5, R3, #0           		; R5 <-- R3
			ADD R1, R5, #0           		; R1 <-- R5
			ADD R2, R1, #0           		; R2 <-- R1
			ADD R2, R2, #-1         		; R2 <-- R2 - 1
			ADD R3, R3, R5           		; R3 <-- R3 + R5
			ADD R2, R2, #-1        			; R2 <-- R2 - 1
			BRp #-3               			; If positive, branch
			AND R5, R5, #0           		; Clear R5
			ADD R5, R3, #0           		; R5 <-- R3
			ADD R4, R4, #-1           		; R4 <-- R4 - 1
			BRp #-9               			; If positive, repeat loop
			AND R0, R0, #0          		; Clear R0
			ADD R0, R3, #0           		; R0 <-- R3
			RET                    			; Return to main function
			LD R0, ONE           			; If R4 = 0 initially, load '1' into R0
			RET               			; Return
			ADD R3, R3, #1				; Increment R3 to original value
			RET					; Return 

 

;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP

PUSH    
			ST R3, PUSH_SaveR3       		; Save R3
			ST R4, PUSH_SaveR4      		; Save R4
			AND R5, R5, #0          		; Clear R5
			LD R3, STACK_END       			; Load stack end address into R3
			LD R4, STACk_TOP       			; Load stack pointer address into R4
			ADD R3, R3, #-1          		; Decrement stack end
			NOT R3, R3           			;
			ADD R3, R3, #1           		; 2s complement of R3 value
			ADD R3, R3, R4           		; R3 <-- R3 + R4
			BRz OVERFLOW           			; Stack is full
			STR R0, R4, #0           		; No overflow, store value in the stack
			ADD R4, R4, #-1           		; Move top of the stack
			ST R4, STACK_TOP       			; Store top of stack pointer
			BRnzp DONE_PUSH          		;
OVERFLOW
			ADD R5, R5, #1           		; Increment R5
DONE_PUSH
			LD R3, PUSH_SaveR3      		; Resotre R3 value
			LD R4, PUSH_SaveR4       		; Restore R4 value
			RET               			; Return
       	 
PUSH_SaveR3    		.BLKW #1           			; Blank space to save R3 value
PUSH_SaveR4    		.BLKW #1           			; Blank space to save R4 value


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP

POP    
			ST R3, POP_SaveR3       		; Save R3
			ST R4, POP_SaveR4     			; Save R4
			AND R5, R5, #0           		; Clear R5
			LD R3, STACK_START      		; Load stack starting address to R3
			LD R4, STACK_TOP      			; Load stack pointer to R4
			NOT R3, R3              		;
			ADD R3, R3, #1           		; 2's complement of R3
			ADD R3, R3, R4           		; Add R3 and R4
			BRz UNDERFLOW           		;
			ADD R4, R4, #1         			; If not underflow, add 1 to stack pointer
			LDR R0, R4, #0         			; Load next value into the stack
			ST R4, STACK_TOP       			; Update stack pointer
			BRnzp DONE_POP          		; Done
UNDERFLOW
			ADD R5, R5, #1           		; Increment R5
DONE_POP
			LD R3, POP_SaveR3       		; Restore R3 value
			LD R4, POP_SaveR4       		; Restore R4 value
			RET            				; Return
			DONE
			ADD R5, R4, #0;    Setting R5 to solution
			HALT
SPACE       		.FILL X20           			; Holds the ASCII value for a space
INVALID_INPUT 		.STRINGZ "Invalid Expression" 		; Invalid input string that is outputted to the screen when necessary
FOUR           		.FILL #4          			; Label for the number '4'
A           		.FILL #65          			; ASCII number for 'A'


POP_SaveR3       	.BLKW #1           			; Blank space to save R3 value
POP_SaveR4       	.BLKW #1           			; Blank space to save R4 value
STACK_END       	.FILL x3FF0           			; Stack end
STACK_START       	.FILL x4000           			; Start of stack
STACK_TOP       	.FILL x4000           			; Stack pointer
NEGONE           	.FILL xFFFF             		; Holds '-1'

NEG_ASCII_EQUAL   	.FILL #-61           			; The additive inverse of ASCII '='
NEG_ASCII_SPACE   	.FILL #-32           			; The additive inverse of ASCII ' '
NEG_ASCII_0       	.FILL #-48           			; The additive inverse of ASCII '0'
NEG_ASCII_9       	.FILL #-57           			; The additive inverse of ASCII '9'
NEG_ASCII_PLUS  	.FILL #-43           			; The additive inverse of ASCII '+'    
NEG_ASCII_MIN   	.FILL #-45           			; The additive inverse of ASCII '-'
NEG_ASCII_MUL   	.FILL #-42           			; The additive inverse of ASCII '*'
NEG_ASCII_DIV   	.FILL #-47          			; The additive inverse of ASCII '/'
NEG_ASCII_EXP   	.FILL #-94          			; The additive inverse of ASCII '^'


NEG_AT       		.FILL xFFC0           			; The additive inverse of ASCII '@'
AT_MIN_Z       		.FILL xFFE6         			; The difference between ASCII '@' and 'Z'
AT_MIN_BQ      		.FILL xFFE0           			; The difference between ASCII '@' and '`'
HIST_ADDR       	.FILL x3F00          			; Histogram starting address
STR_START       	.FILL x4000           			; String starting address
BRUH           		.FILL x40           			; Holds the ASCII value for "@"
ZERO           		.FILL #48          			; ASCII number for '0'
ZER            		.FILL #0        			; Label for number '0'
ONE           		.FILL #1        			; Label for number '1'



SAVER6        		.BLKW   #1             			; Blank space to save R6 value
SAVER7        		.BLKW   #1             			; Blank space to save R7 value

.END








