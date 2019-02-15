#include "token.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>


int read_token (FILE *file, token *theToken) {
	// int line_number = 0;
	int i = 0;
	int is_literal = 1;
	int is_ident = 1;
	int is_arg = 1;
	char c = fgetc(file);

	while (1) {		
		if (c == EOF) {
			return 1;
			break;
		}
		// Skip over comments
		if (c == ';') {
			while (1) {
				c = fgetc(file);
				//printf("%c\n", c);
				if (c == '\n' || c == '\r'){
					read_token(file, theToken);
					return 0;
					break;
				} 
			}
			read_token(file, theToken);
			return 0;
		}

		if (c == '\n' || c == '\r') {
			read_token(file, theToken);
			return 0;
		}

		// Skip over whitespace
		if (c == ' ' || c == '\t') {
			while (c == ' ' || c == '\t') {
				read_token(file, theToken);
				return 0;
				//c = fgetc(file);
			}
			// read_token(file, theToken);
			// return 0;
		}

		//printf("%s %c\n", "Alphanum found:", c);
		if (!(c == '\n' || c == '\t' || c == ' ' || c == '\r')) {
			if (c != ';') {
				theToken->str[i] = c;
				i++;
			}
		}

		while (1) {
			c = fgetc(file);
			if (c == '\n' || c == '\r' || c == ' ' || c == '\t') {
				break;
			}
			if (c == EOF || i >= MAX_TOKEN_LENGTH) {
				theToken->str[i] = '\0'; // Marks end of string
				break;
			}
			theToken->str[i] = c;
			i++;
		}
		theToken->str[i] = '\0'; // Marks end of string

		//printf("Token is: %s\n", theToken->str);
		// printf("Ran loop %d times",j);
		// j++;
		

		// Now, check whether the token is an identifier or invalid or literal
		// or hex
		if (theToken->str[0] == '0' && theToken->str[1] == 'x') {
			for (i = 2; i < strlen(theToken->str); i++) {
				if (!isalnum(theToken->str[i])) {
					printf("%c\n", theToken->str[i]);
					is_literal = 0; // Not a literal
					break;
				}
			}
			if (is_literal) {
				theToken->literal_value = (int) strtol(theToken->str, NULL, 16);
				theToken->type = LITERAL;
				return 0;
			}
			else {
				theToken->type = BROKEN_TOKEN;
				return 0;
			}
		}

		// Literal can be decimal
		else if (isdigit(theToken->str[0])) {
			for (i = 0; i < strlen(theToken->str); i++) {
				if (!isdigit(theToken->str[i])) {
					printf("%s\n", "why");
					is_literal = 0; // Not a literal
					break;
				}
			}
			if (is_literal) { // Is a literal
				theToken->literal_value = atoi(theToken->str);
				//theToken->is_hex = 0;
				print_token(theToken);
				theToken->type = LITERAL;
				return 0;
			}
			else {
				theToken->type = BROKEN_TOKEN;
				return 0;
			}
		}

		// or negative decimals
		else if ((theToken->str[0] == '-') && isdigit(theToken->str[1])) {	

			for (i = 2; i < strlen(theToken->str); i++) {
				if (!isdigit(theToken->str[i])) {
					is_literal = 0; // Not a literal
					break;
				}
			}
			if (is_literal) { // If it is a literal
				theToken->literal_value = atoi(theToken->str);
				print_token(theToken);
				theToken->type = LITERAL;
				return 0;
			}
			else {
				theToken->type = BROKEN_TOKEN;
				return 0;
			}
		}

		// If not literal, parse what enum it is
		else {
			if (!strcmp(theToken->str, "defun")) {
				int j = 0;
				while (1) {
					c = fgetc(file);
					if (isspace(c) || c == '\t') {
						break;
					}
					theToken->str[j] = c;
					j++;
				}
				theToken->str[j] = '\0';
				theToken->type = DEFUN;
				return 0;
			}
			// arg argument
			else if (theToken->str[0] == 'a' && theToken->str[1] == 'r' && theToken->str[2] == 'g') {
				char argno[3];
				for (i = 3; i < strlen(theToken->str); i++) {
					if (strlen(theToken->str) > 6) {
						theToken->type = BROKEN_TOKEN;
						is_arg = 0;
						break;
					}
					if (!isdigit(theToken->str[i])) {
						theToken->type = BROKEN_TOKEN;
						is_arg = 0;
						break;
					}
					if (strlen(theToken->str) == 6) {
						if (!(theToken->str[3] == '1' || theToken->str[3] == '2')) {
							theToken->type = BROKEN_TOKEN;
							is_arg = 0;
							break;
						}
					}
					argno[i - 3] = theToken->str[i];
				}
				if (is_arg) {
					argno[i - 3] = '\0';
					theToken->type = ARG;
					int argno_int = atoi(argno);
					theToken->arg_no = argno_int;
				}
				return 0;
				//free(argno);
			}
			else if (!strcmp(theToken->str, "return")) {
				theToken->type = RETURN;
				return 0;
			}
			else if (!strcmp(theToken->str, "+")) {
				theToken->type = PLUS;
				return 0;
			} 
			else if (!strcmp(theToken->str, "-")) {
				theToken->type = MINUS;
				return 0;
			}
			else if (!strcmp(theToken->str, "*")) {
				theToken->type = MUL;
				return 0;
			} 
			else if (!strcmp(theToken->str, "/")) {
				theToken->type = DIV;
				return 0;
			}
			else if (!strcmp(theToken->str, "%")) {
				theToken->type = MOD;
				return 0;
			} 
			else if (!strcmp(theToken->str, "and")) {
				theToken->type = AND;
				return 0;
			}
			else if (!strcmp(theToken->str, "or")) {
				theToken->type = OR;
				return 0;
			} 
			else if (!strcmp(theToken->str, "not")) {
				theToken->type = NOT;
				return 0;
			} 
			else if (!strcmp(theToken->str, "lt")) {
				theToken->type = LT;
				return 0;
			}
			else if (!strcmp(theToken->str, "le")) {
				theToken->type = LE;
				return 0;
			} 
			else if (!strcmp(theToken->str, "eq")) {
				theToken->type = EQ;
				return 0;
			}
			else if (!strcmp(theToken->str, "ge")) {
				theToken->type = GE;
				return 0;
			} 
			else if (!strcmp(theToken->str, "gt")) {
				theToken->type = GT;
				return 0;
			}
			else if (!strcmp(theToken->str, "if")) {
				theToken->type = IF;
				return 0;
			}
			else if (!strcmp(theToken->str, "else")) {
				theToken->type = ELSE;
				return 0;
			} 
			else if (!strcmp(theToken->str, "endif")) {
				theToken->type = ENDIF;
				return 0;
			}
			else if (!strcmp(theToken->str, "drop")) {
				theToken->type = DROP;
				return 0;
			} 
			else if (!strcmp(theToken->str, "dup")) {
				theToken->type = DUP;
				return 0;
			}
			else if (!strcmp(theToken->str, "swap")) {
				theToken->type = SWAP;
				return 0;
			} 
			// Ident
			else {
				for (i = 0; i < strlen(theToken->str); i++) {
					if (!(isalnum(theToken->str[i]) || (theToken->str[i] == '_'))) {
						theToken->type = BROKEN_TOKEN;
						is_ident = 0;
						break;
					}
				}
				if (is_ident) {
					theToken->type = IDENT;
					return 0;
				}
				return 0;
			}
		}
	}
	return 0;
}

void print_token(token *theToken) {
	printf("Token: %s... ", theToken->str);
	printf("\tCurrent token type: %d\n", theToken->type);
}