.CODE
.FALIGN

gcd
	; PROLOGUE
	STR R7, R6, #-2;
	STR R5, R6, #-3;
	ADD R6, R6, #-3;
	ADD R5, R6, #0;

	; FUNCTION BODY
	LDR R0, R5, #4;
	ADD R6, R6, #-1;
	STR R0, R6, #0;

	ADD R6, R6, #-1
	CONST R0, #0;
	HICONST R0, #0;
	STR R0, R6, #0

	LDR R0, R6, #0;
	LDR R1, R6, #1;
	CMP R0, R1;
	BRz END_EQ0;
	CONST R3, #0;
	BRnzp EQ0;
EQ0
	CONST R3, #1
END_EQ0
	ADD R6, R6, #1
	STR R3, R6, #0

	ADD R6, R6, #1;
	LDR R0, R6, #-1;
IF0
	BRz ELSE0
	LDR R0, R5, #3;
	ADD R6, R6, #-1;
	STR R0, R6, #0;

	JMP ENDIF0
ELSE0
	LDR R0, R5, #4;
	ADD R6, R6, #-1;
	STR R0, R6, #0;

	LDR R0, R5, #3;
	ADD R6, R6, #-1;
	STR R0, R6, #0;

	LDR R0, R6, #0;
	LDR R1, R6, #1;
	ADD R6, R6, #1;
	MOD R0, R0, R1;
	STR R0, R6, #0;

	LDR R0, R5, #4;
	ADD R6, R6, #-1;
	STR R0, R6, #0;

	JSR gcd

ENDIF0
	; EPILOGUE
	LDR R0, R6, #0;
	STR R0, R5, #2;
	ADD R6, R5, #0;
	ADD R6, R6, #2;
	LDR R7, R5, #1;
	LDR R5, R5, #0;
	RET

.FALIGN

main
	; PROLOGUE
	STR R7, R6, #-2;
	STR R5, R6, #-3;
	ADD R6, R6, #-3;
	ADD R5, R6, #0;

	; FUNCTION BODY
	ADD R6, R6, #-1
	CONST R0, #206;
	HICONST R0, #1;
	STR R0, R6, #0

	ADD R6, R6, #-1
	CONST R0, #47;
	HICONST R0, #4;
	STR R0, R6, #0

	JSR gcd

	JSR printnum

	JSR endl

	; EPILOGUE
	LDR R0, R6, #0;
	STR R0, R5, #2;
	ADD R6, R5, #0;
	ADD R6, R6, #2;
	LDR R7, R5, #1;
	LDR R5, R5, #0;
	RET

