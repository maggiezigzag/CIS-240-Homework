/*
* token.c
*/

#include "token.h"
//#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1000*sizeof(char)

void *init_program(program *p){
	p = malloc(sizeof(p));

	// Initializes program
	p->top = NULL;
	p->bottom = NULL;

	return p;
}

void push_token(program *p, char *arg){
  token *token;	
  p->size++;
  // Allocate a token element with malloc
  token = malloc(sizeof(*token));

  // Allocate a space for the argument
  token->arg = malloc(strlen(arg)+1);
  strcpy(token->arg, arg);
  
  // If malloc fails end the program
  if (token == NULL) {
    printf("Couldn't allocate a new token element\n");
    exit (1);
  }

  // Makes bottom of stack NULL
  token->next = NULL;

  if(p->top == NULL){
  	p->bottom->next = token;
  	p->bottom = token;
  	return;
  }
  else{
  	p->top = token;
  	p->bottom = token;
  }
}

char *remove_token(program *p){
  token *token;
  char *removed_token = NULL;

  if(p->top == NULL){
    p->bottom = NULL;
  }
  else{
    token = p->top;
    p->top = token->next;
    token = malloc(strlen(token->arg));
    strcpy(removed_token, token->arg);
    free(token);
    free(token->arg);
  }
    if(p->size > 0){
      p->size--;
    }
    return removed_token;
}

 void print_program(program *p)
{
  token *token = p->top;
  if(p->size > 0){
    printf("%s\n", token->arg);
    token = token->next;
  }
}