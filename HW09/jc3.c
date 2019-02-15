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
	// Initialize input/output files
	FILE *input;
	FILE *output; 
	char *input_name = argv[1];
	char output_name[MAX_TOKEN_LENGTH] = "";
	int i = 0;
	int t;
	input = fopen(input_name, "r");
	
	// While the file name doesn't reach tag, copy the file name
	while(input_name[i] != '.'){
		output_name[i] = input_name[i];
		i++;
	} 

	strcat(output_name, ".asm");
	//printf("%s\n", output_name);
	output = fopen(output_name, "w");

	fprintf(output, "%s\n", ".CODE");
	fprintf(output, "%s\n\n", ".FALIGN");

	while (1) {
		t = read_token(theToken, input) ;
		if (t != 0) {
			break ; 
		} 
			switch(theToken->type){
		// DEFUN & PROLOGUE
		case 0: 
			read_token(theToken, input);
			fprintf(output, "%s\n", theToken->str);
			fprintf(output, "\t%s\n", "; PROLOGUE");
			fprintf(output, "\t%s\n", "STR R7, R6, #1;");
			fprintf(output, "\t%s\n", "STR R5, R6, #0;");
			fprintf(output, "\t%s\n", "ADD R6, R6, #-3;");
			fprintf(output, "\t%s\n", "ADD R5, R6, #0;");
			fprintf(output, "\t%s\n\n", "; FUNCTION BODY");
			break;
		// IDENT
		case 1:
			fprintf(output, "\t%s %s %s %s\n\n", "JSR", theToken->str, "  ; JSR to", theToken->str);
			break;
		// RETURN & EPILOGUE
		case 2: 
			fprintf(output, "\t%s\n", "; EPILOGUE");
			fprintf(output, "\t%s\n", "LDR R7, R5, #-2;");
			fprintf(output, "\t%s\n", "STR R7, R5, #2");
			fprintf(output, "\t%s\n", "ADD R6, R5, #0");
			fprintf(output, "\t%s\n", "LDR R5, R6, #0");
			fprintf(output, "\t%s\n", "LDR R7, R6, #1");
			fprintf(output, "\t%s\n\n", "ADD R6, R6, #3");
			break;
		// PLUS
		case 3: 
			fprintf(output, "\t%s\n", "LDR R0, R6, #0; ADD");
			fprintf(output, "\t%s\n", "LDR R1, R6, #1;");
			fprintf(output, "\t%s\n", "ADD R6, R6, #1;");
			fprintf(output, "\t%s\n\n", "STR R7, R6, #0;");
			break;
		// MINUS
		case 4:
			fprintf(output, "\t%s\n", "LDR R0, R6, #0; SUBTRACT");
			fprintf(output, "\t%s\n", "LDR R1, R6, #1;");
			fprintf(output, "\t%s\n", "ADD R6, R6, #1;");
			fprintf(output, "\t%s\n", "SUB R7, R0, R1;");
			fprintf(output, "\t%s\n\n", "STR R7, R6, #0;");
			break;
		// MUL
		case 5: 
			fprintf(output, "\t%s\n", "LDR R0, R6, #0; MULTIPLY");
			fprintf(output, "\t%s\n", "LDR R1, R6, #1;");
			fprintf(output, "\t%s\n", "ADD R6, R6, #1;");
			fprintf(output, "\t%s\n", "MUL R7, R0, R1;");
			fprintf(output, "\t%s\n\n", "STR R7, R6, #0;");
			break;
		// DIV
		case 6: 
			fprintf(output, "\t%s\n", "LDR R0, R6, #0; division");
			fprintf(output, "\t%s\n", "LDR R1, R6, #1;");
			fprintf(output, "\t%s\n", "ADD R6, R6, #1;");
			fprintf(output, "\t%s\n", "DIV R7, R0, R1;");
			fprintf(output, "\t%s\n\n", "STR R7, R6, #0;");
			break;
		// MOD
		case 7:
			fprintf(output, "\t%s\n", "LDR R0, R6, #0; MOD");
			fprintf(output, "\t%s\n", "LDR R1, R6, #1;");
			fprintf(output, "\t%s\n", "ADD R6, R6, #1;");
			fprintf(output, "\t%s\n", "MOD R7, R0, R1;");
			fprintf(output, "\t%s\n\n", "STR R7, R6, #0;");
			break;
		// AND
		case 8:
			fprintf(output, "\t%s\n", "LDR R0, R6, #0; AND");
			fprintf(output, "\t%s\n", "LDR R1, R6, #1;");
			fprintf(output, "\t%s\n", "ADD R6, R6, #1;");
			fprintf(output, "\t%s\n", "AND R7, R0, R1;");
			fprintf(output, "\t%s\n\n", "STR R7, R6, #0;");
			break;
		// OR
		case 9:
			fprintf(output, "\t%s\n", "LDR R0, R6, #0; OR");
			fprintf(output, "\t%s\n", "LDR R1, R6, #1;");
			fprintf(output, "\t%s\n", "ADD R6, R6, #1;");
			fprintf(output, "\t%s\n", "OR R7, R0, R1;");
			fprintf(output, "\t%s\n\n", "STR R7, R6, #0;");
			break;
		// NOT
		case 10: 
			fprintf(output, "\t%s\n", "LDR R0, R6, #0; NOT");
			fprintf(output, "\t%s\n", "NOT R7, R0;");
			fprintf(output, "\t%s\n\n", "STR R7, R6, #0;");
			break;
		// LT
		case 11:
			fprintf(output, "\t%s\n", "LDR R0, R6, #0; LESS THAN");
			fprintf(output, "\t%s\n", "LDR R1, R6, #1;");
			fprintf(output, "\t%s\n", "ADD R6, R6, #1;");
			break;
		default:
		break;
	}
}
	fclose(input) ;  
	fclose(output) ; 
}