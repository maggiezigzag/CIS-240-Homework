/*
* tc.c
*/

#include "token.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main (int argc, char *argv[]) {

	// Initialize token size 250
	token *theToken = malloc(MAX_TOKEN_LENGTH);
	// Initialize stack
	stack s;
  	init_stack(&s);
  	// Initialize variables
  	int i = 0;
	int t;					// Token variable
	int ifs = 0;			// Number of ifs
	int elses = 0;			// Number of elses
	int endifs = 0;			// Number of endifs
	int comparisons = 0;	// Number of comparisons
	int imm9 = 0;			// CONST
	int uimm8 = 0;			// HICONST
	// Initialize input/output files
	FILE *input;
	FILE *output; 
	char *input_name = argv[1];
	char output_name[MAX_TOKEN_LENGTH] = "";
	input = fopen(input_name, "r");
	
	// While the file name doesn't reach tag, copy the file name
	while(input_name[i] != '.'){
		output_name[i] = input_name[i];
		i++;
	} 

	strcat(output_name, ".asm");
	output = fopen(output_name, "w");

	fprintf(output, "%s\n", ".CODE");

	while (1) {
		t = read_token(theToken, input) ;
		if (t != 0) {
			break ; 
		} 
		switch(theToken->type){
		// DEFUN & PROLOGUE
		case 0: 
			fprintf(output, "%s\n\n", ".FALIGN");
			read_token(theToken, input);
			fprintf(output, "%s\n", theToken->str);
			fprintf(output, "\t%s\n", "; PROLOGUE");
			fprintf(output, "\t%s\n", "STR R7, R6, #-2;");
			fprintf(output, "\t%s\n", "STR R5, R6, #-3;");
			fprintf(output, "\t%s\n", "ADD R6, R6, #-3;");
			fprintf(output, "\t%s\n\n", "ADD R5, R6, #0;");
			fprintf(output, "\t%s\n", "; FUNCTION BODY");
			break;
		// IDENT
		case 1:
			fprintf(output, "\t%s %s\n\n", "JSR", theToken->str);
			break;
		// RETURN & EPILOGUE
		case 2: 
			fprintf(output, "\t%s\n", "; EPILOGUE");
			fprintf(output, "\t%s\n", "LDR R0, R6, #0;");
			fprintf(output, "\t%s\n", "STR R0, R5, #2;");
			fprintf(output, "\t%s\n", "ADD R6, R5, #0;");
			fprintf(output, "\t%s\n", "ADD R6, R6, #2;");
			fprintf(output, "\t%s\n", "LDR R7, R5, #1;");
			fprintf(output, "\t%s\n", "LDR R5, R5, #0;");
			fprintf(output, "\t%s\n\n", "RET");
			break;
		// PLUS
		case 3: 
			fprintf(output, "\t%s\n", "LDR R0, R6, #0;");
			fprintf(output, "\t%s\n", "LDR R1, R6, #1;");
			fprintf(output, "\t%s\n", "ADD R6, R6, #1;");
			fprintf(output, "\t%s\n", "ADD R0, R0, R1;");
			fprintf(output, "\t%s\n\n", "STR R0, R6, #0;");
			break;
		// MINUS
		case 4:
			fprintf(output, "\t%s\n", "LDR R0, R6, #0;");
			fprintf(output, "\t%s\n", "LDR R1, R6, #1;");
			fprintf(output, "\t%s\n", "ADD R6, R6, #1;");
			fprintf(output, "\t%s\n", "SUB R0, R0, R1;");
			fprintf(output, "\t%s\n\n", "STR R0, R6, #0;");
			break;
		// MUL
		case 5: 
			fprintf(output, "\t%s\n", "LDR R0, R6, #0;");
			fprintf(output, "\t%s\n", "LDR R1, R6, #1;");
			fprintf(output, "\t%s\n", "ADD R6, R6, #1;");
			fprintf(output, "\t%s\n", "MUL R0, R0, R1;");
			fprintf(output, "\t%s\n\n", "STR R0, R6, #0;");
			break;
		// DIV
		case 6: 
			fprintf(output, "\t%s\n", "LDR R0, R6, #0;");
			fprintf(output, "\t%s\n", "LDR R1, R6, #1;");
			fprintf(output, "\t%s\n", "ADD R6, R6, #1;");
			fprintf(output, "\t%s\n", "DIV R0, R0, R1;");
			fprintf(output, "\t%s\n\n", "STR R0, R6, #0;");
			break;
		// MOD
		case 7:
			fprintf(output, "\t%s\n", "LDR R0, R6, #0;");
			fprintf(output, "\t%s\n", "LDR R1, R6, #1;");
			fprintf(output, "\t%s\n", "ADD R6, R6, #1;");
			fprintf(output, "\t%s\n", "MOD R0, R0, R1;");
			fprintf(output, "\t%s\n\n", "STR R0, R6, #0;");
			break;
		// AND
		case 8:
			fprintf(output, "\t%s\n", "LDR R0, R6, #0;");
			fprintf(output, "\t%s\n", "LDR R1, R6, #1;");
			fprintf(output, "\t%s\n", "ADD R6, R6, #1;");
			fprintf(output, "\t%s\n", "AND R0, R0, R1;");
			fprintf(output, "\t%s\n\n", "STR R0, R6, #0;");
			break;
		// OR
		case 9:
			fprintf(output, "\t%s\n", "LDR R0, R6, #0;");
			fprintf(output, "\t%s\n", "LDR R1, R6, #1;");
			fprintf(output, "\t%s\n", "ADD R6, R6, #1;");
			fprintf(output, "\t%s\n", "OR R6, R0, R1;");
			fprintf(output, "\t%s\n\n", "STR R0, R6, #0;");
			break;
		// NOT
		case 10: 
			fprintf(output, "\t%s\n", "LDR R0, R6, #0;");
			fprintf(output, "\t%s\n", "NOT R0, R0;");
			fprintf(output, "\t%s\n\n", "STR R0, R6, #0;");
			break;
		// LT
		case 11:
			fprintf(output, "\t%s\n", "LDR R0, R6, #0;");
			fprintf(output, "\t%s\n", "LDR R1, R6, #1;");
			fprintf(output, "\t%s\n", "CMP R0, R1;");
			fprintf(output, "\t%s %s%d%c\n", "BRn", "END_LT", comparisons, ';');
			fprintf(output, "\t%s\n", "CONST R3, #0;");
			fprintf(output, "\t%s %s%d%c\n", "BRnzp", "LT", comparisons, ';');
			fprintf(output, "%s%d\n", "LT", comparisons);
			fprintf(output, "\t%s\n", "CONST R3, #1");
			fprintf(output, "%s%d\n", "END_LT", comparisons);
			fprintf(output, "\t%s\n", "ADD R6, R6, #1");
			fprintf(output, "\t%s\n\n", "STR R3, R6, #0");
			comparisons++;
			break;
		// LE
		case 12:
			fprintf(output, "\t%s\n", "LDR R0, R6, #0;");
			fprintf(output, "\t%s\n", "LDR R1, R6, #1;");
			fprintf(output, "\t%s\n", "CMP R0, R1;");
			fprintf(output, "\t%s %s%d%c\n", "BRnz", "END_LE", comparisons, ';');
			fprintf(output, "\t%s\n", "CONST R3, #0;");
			fprintf(output, "\t%s %s%d%c\n", "BRnzp", "LE", comparisons, ';');
			fprintf(output, "%s%d\n", "LE", comparisons);
			fprintf(output, "\t%s\n", "CONST R3, #1");
			fprintf(output, "%s%d\n", "END_LE", comparisons);
			fprintf(output, "\t%s\n", "ADD R6, R6, #1");
			fprintf(output, "\t%s\n\n", "STR R3, R6, #0");
			comparisons++;
			break;
		// EQ
		case 13:
			fprintf(output, "\t%s\n", "LDR R0, R6, #0;");
			fprintf(output, "\t%s\n", "LDR R1, R6, #1;");
			fprintf(output, "\t%s\n", "CMP R0, R1;");
			fprintf(output, "\t%s %s%d%c\n", "BRz", "END_EQ", comparisons, ';');
			fprintf(output, "\t%s\n", "CONST R3, #0;");
			fprintf(output, "\t%s %s%d%c\n", "BRnzp", "EQ", comparisons, ';');
			fprintf(output, "%s%d\n", "EQ", comparisons);
			fprintf(output, "\t%s\n", "CONST R3, #1");
			fprintf(output, "%s%d\n", "END_EQ", comparisons);
			fprintf(output, "\t%s\n", "ADD R6, R6, #1");
			fprintf(output, "\t%s\n\n", "STR R3, R6, #0");
			comparisons++;
			break;
		// GE
		case 14:
			fprintf(output, "\t%s\n", "LDR R0, R6, #0;");
			fprintf(output, "\t%s\n", "LDR R1, R6, #1;");
			fprintf(output, "\t%s\n", "CMP R0, R1;");
			fprintf(output, "\t%s %s%d%c\n", "BRzp", "END_GE", comparisons, ';');
			fprintf(output, "\t%s\n", "CONST R3, #0;");
			fprintf(output, "\t%s %s%d%c\n", "BRnzp", "GE", comparisons, ';');
			fprintf(output, "%s%d\n", "GE", comparisons);
			fprintf(output, "\t%s\n", "CONST R3, #1");
			fprintf(output, "%s%d\n", "END_GE", comparisons);
			fprintf(output, "\t%s\n", "ADD R6, R6, #1");
			fprintf(output, "\t%s\n\n", "STR R3, R6, #0");
			comparisons++;
			break;
		// GT
		case 15: 
			fprintf(output, "\t%s\n", "LDR R0, R6, #0;");
			fprintf(output, "\t%s\n", "LDR R1, R6, #1;");
			fprintf(output, "\t%s\n", "CMP R0, R1;");
			fprintf(output, "\t%s %s%d%c\n", "BRp", "END_GT", comparisons, ';');
			fprintf(output, "\t%s\n", "CONST R3, #0;");
			fprintf(output, "\t%s %s%d%c\n", "BRnzp", "GT", comparisons, ';');
			fprintf(output, "%s%d\n", "GT", comparisons);
			fprintf(output, "\t%s\n", "CONST R3, #1;");
			fprintf(output, "%s%d\n", "END_GT", comparisons);
			fprintf(output, "\t%s\n", "ADD R6, R6, #1;");
			fprintf(output, "\t%s\n\n", "STR R3, R6, #0;");
			comparisons++;
			break;
		// IF
		case 16:
			fprintf(output, "\t%s\n", "ADD R6, R6, #1;");
			fprintf(output, "\t%s\n", "LDR R0, R6, #-1;");
			push(&s, ifs);
			fprintf(output, "%s%d\n", "IF", ifs);
			fprintf(output, "\t%s%d\n", "BRz ELSE", ifs);
			printf("IFS: %d\n", ifs);
			ifs++;
			break;
		// ELSE
		case 17:
			elses = peek(&s);
			push(&s, elses);
			fprintf(output, "\t%s%d\n", "JMP ENDIF", ifs-1);
			fprintf(output, "%s%d\n", "ELSE", elses);
			printf("ELSES: %d\n", elses);
			//elses++;
			break;
		// END IF
		case 18:
			endifs = peek(&s);
			push(&s, endifs);
			fprintf(output, "%s%d\n", "ENDIF", endifs);
			pop(&s);
			pop(&s);
			pop(&s);
			printf("ENDIFS: %d\n", endifs);
			//endifs++;
			break;
		// DROP
		case 19:
			fprintf(output, "\t%s\n", "ADD R6, R6, #1;");
			break;
		// DUP
		case 20:
			fprintf(output, "\t%s\n", "LDR R0, R6, #0;");
			fprintf(output, "\t%s\n", "ADD R0, R6, #-1;");
			fprintf(output, "\t%s\n\n", "STR R0, R6, #0;");
			break;
		// SWAP
		case 21:
			fprintf(output, "\t%s\n", "LDR R0, R6, #0;");
			fprintf(output, "\t%s\n", "LDR R1, R6, #1;");
			fprintf(output, "\t%s\n", "STR R1, R6, #0;");
			fprintf(output, "\t%s\n\n", "STR R0, R6, #1;");
			break;
		// ROT
		case 22:
			fprintf(output, "\t%s\n", "LDR R0, R6, #0;");
			fprintf(output, "\t%s\n", "LDR R1, R6, #1;");
			fprintf(output, "\t%s\n", "STR R1, R6, #0;");
			fprintf(output, "\t%s\n", "LDR R1, R6, #0;");
			fprintf(output, "\t%s\n", "STR R1, R6, #1;");
			fprintf(output, "\t%s\n\n", "STR R0, R6, #0;");
			break;
		// ARG
		case 23:
			fprintf(output, "\t%s%d%s\n", "LDR R0, R5, #", theToken->arg_no + 2, ";");
			fprintf(output, "\t%s\n", "ADD R6, R6, #-1;");
			fprintf(output, "\t%s\n\n", "STR R0, R6, #0;");
			break;
		// LITERAL
		case 24:
			imm9 = (int)((theToken->literal_value) & 0xFF);
			uimm8 = (int)((theToken->literal_value) & 0xFF00)>>8;
			fprintf(output, "\t%s\n", "ADD R6, R6, #-1");
			fprintf(output, "\t%s%d%s\n", "CONST R0, #", imm9, ";");
			fprintf(output, "\t%s%d%s\n", "HICONST R0, #", uimm8, ";");
			fprintf(output, "\t%s\n\n", "STR R0, R6, #0");
			break;
		default:
			break;
	}
}
	free(theToken);
	fclose(input);  
	fclose(output); 
}