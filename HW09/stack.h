/*
 * stack.h
 */

typedef struct stack_elt_tag {
  int val;
  struct stack_elt_tag *next;
} stack_elt;

typedef struct {
  stack_elt *top;
  int size;
} stack;

void init_stack (stack *s);
void push (stack *s, int val);
int pop (stack *s);
int peek(stack *s);
void quit (stack *s);
void print_stack (stack *s);

void add (stack *s);
void subtract (stack *s);
void multiply (stack *s);
void divide (stack *s);
void modulo (stack *s);
void dup (stack *s);
void swap (stack *s);