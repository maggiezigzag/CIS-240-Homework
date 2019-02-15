;; Sorting Program

	.DATA
	.ADDR x4000

global_array
	.FILL #-2
	.FILL #7
	.FILL #6
	.FILL #2
	.FILL #-5
	.FILL #-2
	.FILL #3
	.FILL #17
	.FILL #4
	.FILL #-100

	.CODE
	.ADDR 0x0000

INIT	LEA R0, global_array
		CONST R1, #0
		CONST R2, #9	; Swap counter
		CONST R5, #0
		CONST R6, #9	; Pass counter

LOOP	LDR R3, R0, #0	; Loads first val of array into R3
		LDR R4, R0, #1	; Loads second val of array into R4

		CMP R3, R4		; If R3>R4, SWAP
		BRp SWAP

		ADD R0, R0, #1	; Else, increment address
		ADD R2, R2, #-1	; Decrement counter

		CMPI R2, #0		; If R2>0, keep LOOP
		BRnz PASS		; If R2=0, start new PASS at beginning of array
		BRp LOOP

SWAP	ADD R5, R3, #0	; Stores value of R3 into temp R5
		STR R4, R0, #0	; Stores second val into first val
		STR R5, R0, #1	; Stores temp into second val
		ADD R2, R2, #-1	; Decrement counter
		ADD R0, R0, #1	; Increments address
		CMPI R2, #0		; If R2=0, start new PASS
		BRnz PASS
		JMP LOOP

PASS	ADD R6, R6, #-1	; Decrement pass counter
		CMPI R6, #0		; If R6=0, END
		BRz END	
		ADD R0, R0, #-9	; change address of R0 back to first value of array
		ADD R2, R2, #9	; change incrementer to 9 again
		JMP LOOP		; start LOOP again

END NOP