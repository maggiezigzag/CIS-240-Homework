#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

void decode(unsigned short *memory, FILE *output);

void branch_convert(unsigned short index, unsigned short value, FILE *file);
void const_convert(unsigned short index, unsigned short value, FILE *file, unsigned short *registers);
void arithmetic_convert(unsigned short index, unsigned short value, FILE *file, unsigned short *registers);
void mod_sll_sra_srl(unsigned short index, unsigned short value, FILE *file, unsigned short *registers);
void logic_convert(unsigned short index, unsigned short value, FILE *file, unsigned short *registers);
void load_convert(unsigned short index, unsigned short value, FILE *file, unsigned short *registers, unsigned short *memory);
void store_convert(unsigned short index, unsigned short value, FILE *file, unsigned short *memory);
void hiconst_convert(unsigned short index, unsigned short value, FILE *file, unsigned short *registers);
void comparison_convert(unsigned short index, unsigned short value, FILE *file);
void jsr_r_convert(unsigned short index, unsigned short value, FILE *file, unsigned short *registers);
void rti_convert(unsigned short index, unsigned short value, FILE *file);
void jmp_r_convert(unsigned short index, unsigned short value, FILE *file);
void trap_convert(unsigned short index, unsigned short value, FILE *file, unsigned short *registers);

//bool canWrite(unsigned short index);
//void writeFile(FILE *file, unsigned short index, unsigned short value, char* string, unsigned short num);

//unsigned short updatePC(unsigned short PC);
void printPC(unsigned short PC, FILE *file);
void hex2binary(unsigned short value, FILE *file);
void printRFWE(unsigned short regFileWE, FILE *file);
int NZPtest(unsigned short regVal);
void printRegVal(unsigned short regVal, FILE *file);
void printReg(unsigned short reg, FILE *file);
void printNZPWE(unsigned short NZPWE, FILE *file);
void printNZP(int NZP, FILE *file);
void printDATAWE(unsigned short DATAWE, FILE *file);
void printAddress(unsigned short address, FILE *file);
void printMemVal(unsigned short memVal, FILE *file);

void printR_PC(unsigned short PC, unsigned short *registers);
unsigned short signext(unsigned short value, int num, int type);