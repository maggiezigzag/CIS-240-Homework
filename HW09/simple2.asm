.CODE
.FALIGN

main
	; PROLOGUE
	STR R7, R6, #-2;
	STR R5, R6, #-3;
	ADD R6, R6, #-3;
	ADD R5, R6, #0;
	; FUNCTION BODY
	LDR R0, R6, #0; GREATER THAN
	LDR R1, R6, #1;
	CMP R0, R1;
	BRp END_GT;
	CONST R0, #0;
	BRnzp GT;
GT
	CONST R0, #1
END_GT
	ADD R6, R6, #1
	STR R0, R6, #0

	JSR printnum ; JSR to printnum

	JSR endl ; JSR to endl

	LDR R0, R6, #0; LESS THAN
	LDR R1, R6, #1;
	CMP R0, R1;
	BRn END_LT;
	CONST R0, #0;
	BRnzp LT;
LT
	CONST R0, #1
END_LT
	ADD R6, R6, #1
	STR R0, R6, #0

	JSR printnum ; JSR to printnum

	JSR endl ; JSR to endl

	; EPILOGUE
	LDR R0, R6, #0;
	STR R0, R5, #2
	ADD R6, R5, #0
	ADD R6, R6, #2
	LDR R7, R5, #1
	LDR R5, R5, #0
	RET

