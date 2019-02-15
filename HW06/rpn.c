/*
 * rpn.c
 */

#include "stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 100

int main ()
{
  char input[MAX_LINE_LENGTH];
  char stack_val[MAX_LINE_LENGTH];
  int stack_num[MAX_LINE_LENGTH];

  stack theStack;

  init_stack(&theStack);
  
  while (1) {
    fgets(input, MAX_LINE_LENGTH, stdin); // scanning for keyboard input

    // non-digit count
    int count = 0;
    int nums_in_input = 0;
    for(int i = 0; i<strlen(input); i++){
      if(input[i] != ' ' && !isdigit(input[i])){
        count++;
      }
      if(isdigit(input[i])){
        nums_in_input++;
      }
    }
  
    sscanf(input, "%s", stack_val);   // scanning for string, eliminating white spaces
    //sscanf(input, "%d", stack_num);

    //printf("%d\n", nums_in_input);
    //printf("%d\n", count);


    // PUSH
    if (sscanf(input, "%d", stack_num) == 1 && (count >= 1 && count <= 2) && (strlen(stack_val)-nums_in_input) <= 1){ 
      if(count == 2 && stack_val[0] == '-'){
        push(&theStack, stack_num[0]);
        //print_stack (&theStack);
      } 
      else if(count == 1){
        push(&theStack, stack_num[0]);
        //print_stack (&theStack);
      }
      else{
        printf("INVALID COMMAND\n");
      }
    }
    // QUIT
    else if (strlen(stack_val) == 4 && tolower(stack_val[0]) == 'q' && tolower(stack_val[1])== 'u' && tolower(stack_val[2])== 'i' && tolower(stack_val[3])== 't' && count == 5 && nums_in_input == 0) {
      quit (&theStack);
      exit(0);
    }
    // ADD
    else if(strlen(stack_val) == 1 && stack_val[0] == '+' && count == 2 && nums_in_input == 0){
      add(&theStack);
      //print_stack(&theStack);
    }
    // SUBTRACT
    else if(strlen(stack_val) == 1 && stack_val[0] == '-' && count == 2 && nums_in_input == 0){
      subtract(&theStack);
      //print_stack(&theStack);
    }
    // MULTIPLY
    else if(strlen(stack_val) == 1 && stack_val[0] == '*' && count == 2 && nums_in_input == 0){
      multiply(&theStack);
      //print_stack(&theStack);
    }
    // DIVIDE
    else if(strlen(stack_val) == 1 && stack_val[0] == '/' && count == 2 && nums_in_input == 0){
      divide(&theStack);
      //print_stack(&theStack);
    }
    // MODULO
    else if(strlen(stack_val) == 1 && stack_val[0] == '%' && count == 2 && nums_in_input == 0){
      modulo(&theStack);
      //print_stack(&theStack);
    }
    // DUPLICATE
    else if(strlen(stack_val) == 3 && tolower(stack_val[0]) == 'd' && tolower(stack_val[1])=='u' && tolower(stack_val[2]) =='p' && count == 4 && nums_in_input == 0){
      dup(&theStack);
      //print_stack(&theStack);
    }
    // SWAP
    else if(strlen(stack_val) == 4 && tolower(stack_val[0]) == 's' && tolower(stack_val[1])=='w' && tolower(stack_val[2])=='a' && tolower(stack_val[3]) =='p' && count == 5 && nums_in_input == 0){
      swap(&theStack);
      //print_stack(&theStack);
    }
    else{
      printf("%s", "INVALID COMMAND\n");
    }
    
  }
  
  return 0;
}


