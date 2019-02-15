/*
* token.c
*/

#include "token.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int read_token (token *theToken, FILE *input) {
  char val = fgetc(input);
  int i = 0;

  while (1) {
    // REACHED END OF FILE
    if(val== EOF){
      printf("REACHED END OF FILE\n");
      return 1;
      break;
    } 
    // COMMENT HANDLING
    else if(val == ';'){
      while(val != '\n'){
        val = fgetc(input);
      } 
        val = fgetc(input);
        continue;
    } 
    // WHITESPACE HANDLING
    else if(val == '\n' || val == '\t' || val == ' ' || val == '\r'){
      while(val == '\n' || val == '\t' || val == ' ' || val == '\r'){
        val = fgetc(input) ; 
      }
      continue;
    }
    // STRINGS 
    else{
      for(i = 0 ; i < MAX_TOKEN_LENGTH; i++){
        if(val == '\n' || val == '\t' || val == ' ' || val == '\r'|| val== EOF){
          theToken -> str[i] = '\0'; 
          //print_token(theToken);
          token_type(theToken);
          break; 
        }
        else if(val == EOF){
          return 1;
          break;
        }
        else{
          theToken -> str[i] = val; 
          val= fgetc(input);
          continue;
        }
      }
      break; 
    }  
  }
  // CHECK FOR HEX LITERAL
  if(theToken->str[0] == '0' && theToken->str[1] == 'x'){
    for (i = 2; i<strlen(theToken->str); i++) {
      if(!isalnum(theToken->str[i])){
          return 1; 
      }
    }
    // HEX LITERAL
    theToken->type = LITERAL; 
    theToken->literal_value = (int)strtol(theToken->str, NULL, 16);
    print_token(theToken);
    return 0; 
  } 
  // CHECK POSITIVE & NEGATIVE DECIMAL LITERALS
  else if((theToken->str[0] == '-' && isdigit(theToken->str[1])) || isdigit(theToken->str[0])){
      for(i = 1; i<strlen(theToken->str); i++){
        if(!isdigit(theToken->str[i])){
        return 1 ; 
      }
    }
    // DECIMAL LITERAL
    theToken->type = LITERAL;
    theToken->literal_value = atoi(theToken->str);
    print_token(theToken);
    return 0; 
    }
  // CHECK FOR ARGS
  else if(theToken->str[0] == 'a' && theToken->str[1] == 'r' && theToken->str[2] == 'g'){
    //printf("GOT HERE, ARG!\n");
    theToken->type = ARG; 
    sscanf(theToken->str, "arg%d", &(theToken->arg_no)); 
    return 0;
  }  
  // CHECK ENUM TYPE
  else if(strcmp(theToken->str, "defun") == 0){
    //printf("GOT HERE");
    theToken->type = DEFUN;
    printf("GOT HERE, DEFUN!\n");
    print_token(theToken);
    return 0;
  }
  else if(strcmp(theToken->str, "return") == 0){
    //printf("GOT HERE, RETURN!\n");
    theToken->type = RETURN;
    print_token(theToken);
    return 0;
  }
  else if(strcmp(theToken->str, "+") == 0){
    //printf("GOT HERE, PLUS!\n");
    theToken->type = PLUS;
    print_token(theToken);
    return 0;
  }
  else if(strcmp(theToken->str, "-") == 0){
    //printf("GOT HERE, MINUS!\n");
    theToken->type = MINUS;
    print_token(theToken);
    return 0;
  }
  else if(strcmp(theToken->str, "*") == 0){
    //printf("GOT HERE, MUL!\n");
    theToken->type = MUL;
    print_token(theToken);
    return 0;
  }
  else if(strcmp(theToken->str, "/") == 0){
    //printf("GOT HERE, DIV!\n");
    theToken->type = DIV;
    print_token(theToken);
    return 0;
  }
  else if(strcmp(theToken->str, "%") == 0){
    //printf("GOT HERE, MOD!\n");
    theToken->type = MOD;
    print_token(theToken);
    return 0;
  }
  else if(strcmp(theToken->str, "and") == 0){
    //printf("GOT HERE, AND!\n");
    theToken->type = AND;
    print_token(theToken);
    return 0;
  }
  else if(strcmp(theToken->str, "or") == 0){
    //printf("GOT HERE, OR!\n");
    theToken->type = OR;
    print_token(theToken);
    return 0;
  }
  else if(strcmp(theToken->str, "not") == 0){
    //printf("GOT HERE, NOT!\n");
    theToken->type = NOT;
    print_token(theToken);
    return 0;
  }
  else if(strcmp(theToken->str, "lt") == 0){
    //printf("GOT HERE, LT!\n");
    theToken->type = LT;
    print_token(theToken);
    return 0;
  }
  else if(strcmp(theToken->str, "le") == 0){
    //printf("GOT HERE, LE!\n");
    theToken->type = LE;
    print_token(theToken);
    return 0;
  }
  else if(strcmp(theToken->str, "eq") == 0){
    //printf("GOT HERE, EQ!\n");
    theToken->type = EQ;
    print_token(theToken);
    return 0;
  }
  else if(strcmp(theToken->str, "ge") == 0){
    //printf("GOT HERE, GE!\n");
    theToken->type = GE;
    print_token(theToken);
    return 0;
  }
  else if(strcmp(theToken->str, "gt") == 0){
    //printf("GOT HERE, GT!\n");
    theToken->type = GT;
    print_token(theToken);
    return 0;
  }
  else if(strcmp(theToken->str, "if") == 0){
    //printf("GOT HERE, IF!\n");
    theToken->type = IF;
    print_token(theToken);
    return 0;
  }
  else if(strcmp(theToken->str, "else") == 0){
    //printf("GOT HERE, ELSE!\n");
    theToken->type = ELSE;
    print_token(theToken);
    return 0;
  }
  else if(strcmp(theToken->str, "endif") == 0){
    //printf("GOT HERE, ENDIF!\n");
    theToken->type = ENDIF;
    print_token(theToken);
    return 0;
  }
  else if(strcmp(theToken->str, "drop") == 0){
    //printf("GOT HERE, DROP!\n");
    theToken->type = DROP;
    print_token(theToken);
    return 0;
  }
  else if(strcmp(theToken->str, "dup") == 0){
    //printf("GOT HERE, DUP!\n");
    theToken->type = DUP;
    print_token(theToken);
    return 0;
  }
  else if(strcmp(theToken->str, "swap") == 0){
    //printf("GOT HERE, SWAP!\n");
    theToken->type = SWAP;
    print_token(theToken);
    return 0;
  }
  else if(strcmp(theToken->str, "rot") == 0){
    //printf("GOT HERE, ROT!\n");
    theToken->type = ROT;
    print_token(theToken);
    return 0;
  }
  else{
    for(i = 0; i<strlen(theToken->str); i++){
      //printf("GOT HERE, IDENT!\n");
      if(!(isalnum(theToken->str[i])||(theToken->str[i]=='_'))){
        printf("IMPROPER IDENT\n");
        return 1;
      }
    }
    theToken->type = IDENT;
    print_token(theToken);
    return 0;
  }
  return 0 ; 
}

int token_type(token *theToken){
  return 0;
}

void print_token (token *theToken) {
  printf("Token type: %u\n",theToken -> type) ;
  printf("Token string: %s\n", theToken -> str) ;  
}