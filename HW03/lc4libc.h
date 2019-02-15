/*
 * lc4libc.h
 */

typedef int lc4int; 
typedef unsigned int lc4uint;
typedef char lc4char;

#define TRUE  1
#define FALSE 0

#define NULL (void*)0

#define BLACK  0x0000U
#define WHITE  0xFFFFU
#define GRAY8  0x2108U
#define YELLOW 0x7FF0U
#define RED    0x7C00U
#define ORANGE 0xF600U
#define BLUE   0x001FU
#define GREEN  0x3E00U
#define CYAN   0x0770U


void lc4_puts(lc4uint *str);
void lc4_draw_hline (lc4int row, lc4int col, lc4int width, lc4uint color);

void lc4_halt();
void lc4_reset_vmem();
void lc4_blt_vmem();

// If there is no character returns a -ve value else returns the ASCII code in the lower 7 bits
lc4int lc4_getc();

void lc4_set_timer(lc4uint timer_value);

// Returns the Timer status register value which is -ve if timer has gone off
lc4int lc4_check_timer();
