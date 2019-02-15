#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void decode(unsigned short *memory, FILE *output);

void branch_convert(unsigned short index, unsigned short memory, FILE *file);
void const_convert(unsigned short index, unsigned short memory, FILE *file);
void arithmetic_convert(unsigned short index, unsigned short memory, FILE *file);
void mod_sll_sra_srl(unsigned short index, unsigned short value, FILE *file);
void logic_convert(unsigned short index, unsigned short value, FILE *file);
void load_convert(unsigned short index, unsigned short value, FILE *file);
void store_convert(unsigned short index, unsigned short value, FILE *file);
void hiconst_convert(unsigned short index, unsigned short value, FILE *file);
void comparison_convert(unsigned short index, unsigned short value, FILE *file);
void jsr_r_convert(unsigned short index, unsigned short value, FILE *file);
void rti_convert(unsigned short index, unsigned short value, FILE *file);
void jmp_r_convert(unsigned short index, unsigned short value, FILE *file);
void trap_convert(unsigned short index, unsigned short value, FILE *file);