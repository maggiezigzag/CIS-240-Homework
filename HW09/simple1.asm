.CODE
.FALIGN

main
	; PROLOGUE
	STR R7, R6, #-2;
	STR R5, R6, #-3;
	ADD R6, R6, #-3;
	ADD R5, R6, #0;

	; FUNCTION BODY
	ADD R6, R6, #-1
	CONST R0, #5;
	HICONST R0, #0;
	STR R0, R6, #0

	ADD R6, R6, #-1
	CONST R0, #3;
	HICONST R0, #0;
	STR R0, R6, #0

	ADD R6, R6, #-1
	CONST R0, #2;
	HICONST R0, #0;
	STR R0, R6, #0

	LDR R0, R6, #0;
	LDR R1, R6, #1;
	ADD R6, R6, #1;
	MUL R0, R0, R1;
	STR R0, R6, #0;

	LDR R0, R6, #0;
	LDR R1, R6, #1;
	ADD R6, R6, #1;
	ADD R0, R0, R1;
	STR R0, R6, #0;

	JSR printnum

	JSR endl

	ADD R6, R6, #-1
	CONST R0, #3;
	HICONST R0, #0;
	STR R0, R6, #0

	ADD R6, R6, #-1
	CONST R0, #4;
	HICONST R0, #0;
	STR R0, R6, #0

	ADD R6, R6, #-1
	CONST R0, #5;
	HICONST R0, #0;
	STR R0, R6, #0

	LDR R0, R6, #0;
	LDR R1, R6, #1;
	STR R1, R6, #0;
	LDR R1, R6, #0;
	STR R1, R6, #1;
	STR R0, R6, #0;

	LDR R0, R6, #0;
	LDR R1, R6, #1;
	ADD R6, R6, #1;
	MUL R0, R0, R1;
	STR R0, R6, #0;

	LDR R0, R6, #0;
	LDR R1, R6, #1;
	ADD R6, R6, #1;
	ADD R0, R0, R1;
	STR R0, R6, #0;

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

