/*
* stack.c
*/

#include "stack.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>


void init_stack (stack *s)
{
  s->top = NULL;		//initializing first locations of stack
  s->size = 0;
}

void push(stack *s, int x)
{
  stack_elt *elt;	

  // Allocate a new stack element with malloc
  elt = malloc(sizeof(*elt));	//makes a stack element

  // If malloc fails end the program
  if (elt == NULL) {
    printf("Couldn't allocate a new stack element\n");
    exit (1);
  }

  elt->val = x;    // assign pushed value into elt.val
  elt->next = s->top; // assign current top val to next val
  s->top = elt;       // assign new elt to top
  s->size++;          // increase size
  //print_stack(s);
  }

void pop(stack *s)
{
  stack_elt *elt;
  //int n;

  if(s->top == NULL){
    printf("STACK ERROR\n");
  }
  if (s->top) {
    elt = s->top;
    s->top = elt->next;
  }
    //n = elt->val;

    free(elt);
    if(s->size > 0){
      s->size--;
    }
    //return n;
}

void add(stack *s){
  if(s->size > 1){
    int num1 = s->top->val;
    pop(s);
    int num2 = s->top->val;
    pop(s);
    push(s, num1+num2);
    print_stack(s);
  }
  else{
    printf("STACK ERROR\n");
  }
} 

void subtract(stack *s){
  if(s->size > 1){
    int num1 = s->top->val;
    pop(s);
    int num2 = s->top->val;
    pop(s);
    push(s, num2-num1);
    print_stack(s);
  }
  else{
    printf("STACK ERROR\n");
  }
}

void multiply(stack *s){
  if(s->size > 1){
    int num1 = s->top->val;
    pop(s);
    int num2 = s->top->val;
    pop(s);
    push(s, num1*num2);
    print_stack(s);
  }
  else{
    printf("STACK ERROR\n");
  }
}

void divide(stack *s){
  if(s->size > 1){
    int num1 = s->top->val;
    pop(s);
    if(num1 == 0){
      printf("DIVIDE BY ZERO\n");
      exit(1);
    }
    else{
      int num2 = s->top->val;
      pop(s);
      push(s, num2/num1);
      print_stack(s);
    }
  }
  else{
    printf("STACK ERROR\n");
  }
}

void modulo(stack *s){
  if(s->size > 1){
    int num1 = s->top->val;
    pop(s);
    if(num1 == 0){
      printf("DIVIDE BY ZERO\n");
      exit(1);
    }
    else{
      int num2 = s->top->val;
      pop(s);
      push(s, num2%num1);
      print_stack(s);
    }
  }
  else{
    printf("STACK ERROR\n");
  }
}

void dup(stack *s){
  if(s->size < 1){
    printf("STACK ERROR\n");
  }
  push(s, s->top->val);
  print_stack(s);
}

void swap(stack *s){
  if(s->size > 1){
    int num1 = s->top->val;
    pop(s);
    int num2 = s->top->val;
    pop(s);
    push(s, num1);
    push(s, num2);
    print_stack(s);
  }
  else{
    printf("STACK ERROR\n");
  }
}

void quit(stack *s)
{
  while (s->top) {
    pop(s);
  }
}

void print_stack (stack *s)
{
  stack_elt *elt = s->top;
  if(s->size > 0){
    printf ("%d\n", elt->val);
  }
}
