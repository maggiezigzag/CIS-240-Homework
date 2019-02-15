/**
LC4.c
contains routines for decoding instructions 
**/

#include "loader.h"
#include "LC4.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void decode(unsigned short *memory, FILE *output)
{
	for(int index = 0; index <40960; index++){
		if(memory[index] != 0){
			unsigned short opcode = (unsigned short) memory[index]>>12;
			unsigned short value = (unsigned short)memory[index];
			printf("%d\n", memory[index]>>12);
			if(opcode == 0){
				branch_convert(index, value, output);
			}
			if(opcode == 1){
				arithmetic_convert(index, value, output);
			}
			if(opcode == 2){
				comparison_convert(index, value, output);
			}
			if(opcode == 4){
				jsr_r_convert(index, value, output);
			}
			if(opcode == 5){
				logic_convert(index, value, output);
			}
			if(opcode == 6){
				load_convert(index, value, output);
			}
			if(opcode == 7){
				store_convert(index, value, output);
			}
			if(opcode == 8){
				rti_convert(index, value, output);
			}
			if(opcode == 9){
				const_convert(index, value, output);
			}
			if(opcode == 10){
				mod_sll_sra_srl(index, value, output);
			}
			if(opcode == 12){
				jmp_r_convert(index, value, output);
			}
			if(opcode == 13){
				hiconst_convert(index, value, output);
			}
			if(opcode == 15){
				trap_convert(index, value, output);
			}
			// else if ((index >= 0 && index <= 8191) || (index >= 32768 && index <= 40960)){
			// 	fprintf(output, "%04X %s %04X %s\n", index, ":", value, "-> INVALID COMMAND"); //UNCOMMENT!!
			// }
		}
	}
	return;
}

void branch_convert(unsigned short index, unsigned short value, FILE *file)
{
	unsigned short branch_type = (unsigned short)(value<<4)>>13;
	//printf("%d\n", branch_type);

	if(branch_type == 0)	//NOP
	{
		if((index >= 0 && index <= 8191) || (index >= 32768 && index <= 40960)){
			fprintf(file, "%04X %s %04X %s\n", index, ":", value, "-> NOP");
		}
		else{
			fprintf(file, "%04X %s %04X\n", index, ":", value);
		}
	}
	if(branch_type == 1)	//BRp
	{
		short imm = (short)(value<<7)>>7;
		if((index >= 0 && index <= 8191) || (index >= 32768 && index <= 40960)){
			fprintf(file, "%04X %s %04X %s %d\n", index, ":", value, "-> BRp", imm);
		}
		else{
			fprintf(file, "%04X %s %04X\n", index, ":", value);
		}
	}
	if(branch_type == 2)	//BRz
	{
		short imm = (short)(value<<7)>>7;
		if((index >= 0 && index <= 8191) || (index >= 32768 && index <= 40960)){
			fprintf(file, "%04X %s %04X %s %d\n", index, ":", value, "-> BRz", imm);
		}
		else{
			fprintf(file, "%04X %s %04X\n", index, ":", value);
		}
	}
	if(branch_type == 3)	//BRzp
	{
		short imm = (short)(value<<7)>>7;
		if((index >= 0 && index <= 8191) || (index >= 32768 && index <= 40960)){
			fprintf(file, "%04X %s %04X %s %d\n", index, ":", value, "-> BRzp", imm);
		}
		else{
			fprintf(file, "%04X %s %04X\n", index, ":", value);
		}
	}
	if(branch_type == 4)	//BRn
	{
		short imm = (short)(value<<7)>>7;
		if((index >= 0 && index <= 8191) || (index >= 32768 && index <= 40960)){
			fprintf(file, "%04X %s %04X %s %d\n", index, ":", value, "-> BRn", imm);
		}
		else{
			fprintf(file, "%04X %s %04X\n", index, ":", value);
		}
	}
	if(branch_type == 5)	//BRnp
	{
		short imm = (short)(value<<7)>>7;
		if((index >= 0 && index <= 8191) || (index >= 32768 && index <= 40960)){
			fprintf(file, "%04X %s %04X %s %d\n", index, ":", value, "-> BRnp", imm);
		}
		else{
			fprintf(file, "%04X %s %04X\n", index, ":", value);
		}
	}
	if(branch_type == 6)	//BRnz
	{
		short imm = (short)(value<<7)>>7;
		if((index >= 0 && index <= 8191) || (index >= 32768 && index <= 40960)){
			fprintf(file, "%04X %s %04X %s %d\n", index, ":", value, "-> BRnz", imm);
		}
		else{
			fprintf(file, "%04X %s %04X\n", index, ":", value);
		}
	}
	if(branch_type == 7)	//BRnzp
	{
		short imm = (short)(value<<7)>>7;
		if((index >= 0 && index <= 8191) || (index >= 32768 && index <= 40960)){
			fprintf(file, "%04X %s %04X %s %d\n", index, ":", value, "-> BRnzp", imm);
		}
		else{
			fprintf(file, "%04X %s %04X\n", index, ":", value);
		}
	}
	else return;
}

void arithmetic_convert(unsigned short index, unsigned short value, FILE *file)
{
	unsigned short arith_type = (unsigned short)(value<<10)>>13;
	
	if(arith_type == 0)	//ADD
	{
		unsigned short rd = (unsigned short)(value<<4)>>13;
		unsigned short rs = (unsigned short)(value<<7)>>13;
		unsigned short rt = (unsigned short)(value<<13)>>13;
		if((index >= 0 && index <= 8191) || (index >= 32768 && index <= 40960)){
			fprintf(file, "%04X %s %04X %s %s%d %s%d %s%d\n", index, ":", value, "-> ADD", "R", rd, "R", rs, "R", rt);
		}
		else{
			fprintf(file, "%04X %s %04X\n", index, ":", value);
		}
	}
	if(arith_type == 1)	//MUL
	{
		unsigned short rd = (unsigned short)(value<<4)>>13;
		unsigned short rs = (unsigned short)(value<<7)>>13;
		unsigned short rt = (unsigned short)(value<<13)>>13;
		if((index >= 0 && index <= 8191) || (index >= 32768 && index <= 40960)){
			fprintf(file, "%04X %s %04X %s %s%d %s%d %s%d\n", index, ":", value, "-> MUL", "R", rd, "R", rs, "R", rt);
		}
		else{
			fprintf(file, "%04X %s %04X\n", index, ":", value);
		}
	}
	if(arith_type == 2)	//SUB
	{
		unsigned short rd = (unsigned short)(value<<4)>>13;
		unsigned short rs = (unsigned short)(value<<7)>>13;
		unsigned short rt = (unsigned short)(value<<13)>>13;
		if((index >= 0 && index <= 8191) || (index >= 32768 && index <= 40960)){
			fprintf(file, "%04X %s %04X %s %s%d %s%d %s%d\n", index, ":", value, "-> SUB", "R", rd, "R", rs, "R", rt);	
		}
		else{
			fprintf(file, "%04X %s %04X\n", index, ":", value);
		}
	}
	if(arith_type == 3)	//DIV
	{
		unsigned short rd = (unsigned short)(value<<4)>>13;
		unsigned short rs = (unsigned short)(value<<7)>>13;
		unsigned short rt = (unsigned short)(value<<13)>>13;
		if((index >= 0 && index <= 8191) || (index >= 32768 && index <= 40960)){
			fprintf(file, "%04X %s %04X %s %s%d %s%d %s%d\n", index, ":", value, "-> DIV", "R", rd, "R", rs, "R", rt);
		}
		else{
			fprintf(file, "%04X %s %04X\n", index, ":", value);
		}
	}
	if((unsigned short)(value<<10)>>15 == 1)	//ADD IMM
	{
		unsigned short rd = (unsigned short)(value<<4)>>13;
		unsigned short rs = (unsigned short)(value<<7)>>13;
		short imm = (short)(value<<11)>>11;
		if((index >= 0 && index <= 8191) || (index >= 32768 && index <= 40960)){
			fprintf(file, "%04X %s %04X %s %s%d %s%d %d\n", index, ":", value, "-> ADD", "R", rd, "R", rs, imm);
		}
		else{
			fprintf(file, "%04X %s %04X\n", index, ":", value);
		}
	}
	else return;
}

void comparison_convert(unsigned short index, unsigned short value, FILE *file)
{
	unsigned short comparison_type = (unsigned short)(value<<7)>>14;

	if(comparison_type == 0)	//CMP
	{
		unsigned short rs = (unsigned short)(value<<4)>>13;
		unsigned short rt = (unsigned short)(value<<13)>>13;
		if((index >= 0 && index <= 8191) || (index >= 32768 && index <= 40960)){
			fprintf(file, "%04X %s %04X %s %s%d %s%d\n", index, ":", value, "-> CMP", "R", rs, "R", rt);
		}
		else{
			fprintf(file, "%04X %s %04X\n", index, ":", value);
		}
	}
	if(comparison_type == 1)	//CMPU
	{
		unsigned short rs = (unsigned short)(value<<4)>>13;
		unsigned short rt = (unsigned short)(value<<13)>>13;
		if((index >= 0 && index <= 8191) || (index >= 32768 && index <= 40960)){
			fprintf(file, "%04X %s %04X %s %s%d %s%d\n", index, ":", value, "-> CMPU", "R", rs, "R", rt);
		}
		else{
			fprintf(file, "%04X %s %04X\n", index, ":", value);
		}
	}
	if(comparison_type == 2)	//CMPI
	{
		unsigned short rs = (unsigned short)(value<<4)>>13;
		short imm = (short)(value<<9)>>9;
		if((index >= 0 && index <= 8191) || (index >= 32768 && index <= 40960)){
			fprintf(file, "%04X %s %04X %s %s%d %d\n", index, ":", value, "-> CMPI", "R", rs, imm);
		}
		else{
			fprintf(file, "%04X %s %04X\n", index, ":", value);
		}
	}
	if(comparison_type == 3)	//CMPIU
	{
		unsigned short rs = (unsigned short)(value<<4)>>13;
		unsigned short uimm = (unsigned short)(value<<9)>>9;
		if((index >= 0 && index <= 8191) || (index >= 32768 && index <= 40960)){
			fprintf(file, "%04X %s %04X %s %s%d %d\n", index, ":", value, "-> CMPIU", "R", rs, uimm);
		}
		else{
			fprintf(file, "%04X %s %04X\n", index, ":", value);
		}
	}
	else return;
}

void jsr_r_convert(unsigned short index, unsigned short value, FILE *file)
{
	if((unsigned short)(value<<4)>>15 == 0)	//JSRR
	{
		unsigned short rs = (unsigned short)(value<<7)>>13;
		if((index >= 0 && index <= 8191) || (index >= 32768 && index <= 40960)){
			fprintf(file, "%04X %s %04X %s %s%d\n", index, ":", value, "-> JSRR", "R", rs);
		}
		else{
			fprintf(file, "%04X %s %04X\n", index, ":", value);
		}	
	}
	if((unsigned short)(value<<4)>>15 == 1)	//JSR
	{
		short imm = (short)(value<<5)>>5;
		if((index >= 0 && index <= 8191) || (index >= 32768 && index <= 40960)){
			fprintf(file, "%04X %s %04X %s %d\n", index, ":", value, "-> JSR", imm);
		}
		else{
			fprintf(file, "%04X %s %04X\n", index, ":", value);
		}	
	}
	else return;
}

void logic_convert(unsigned short index, unsigned short value, FILE *file)
{
	unsigned short logic_type = (unsigned short)(value<<10)>>13;

	if(logic_type == 0)	//AND
	{
		unsigned short rd = (unsigned short)(value<<4)>>13;
		unsigned short rs = (unsigned short)(value<<7)>>13;
		unsigned short rt = (unsigned short)(value<<13)>>13;
		if((index >= 0 && index <= 8191) || (index >= 32768 && index <= 40960)){
			fprintf(file, "%04X %s %04X %s %s%d %s%d %s%d\n", index, ":", value, "-> AND", "R", rd, "R", rs, "R", rt);
		}
		else{
			fprintf(file, "%04X %s %04X\n", index, ":", value);
		}	
	}
	if(logic_type == 1)	//NOT
	{
		unsigned short rd = (unsigned short)(value<<4)>>13;
		unsigned short rs = (unsigned short)(value<<7)>>13;
		if((index >= 0 && index <= 8191) || (index >= 32768 && index <= 40960)){
			fprintf(file, "%04X %s %04X %s %s%d %s%d\n", index, ":", value, "-> NOT", "R", rd, "R", rs);
		}
		else{
			fprintf(file, "%04X %s %04X\n", index, ":", value);
		}	
	}
	if(logic_type == 2)	//OR
	{
		unsigned short rd = (unsigned short)(value<<4)>>13;
		unsigned short rs = (unsigned short)(value<<7)>>13;
		unsigned short rt = (unsigned short)(value<<13)>>13;
		if((index >= 0 && index <= 8191) || (index >= 32768 && index <= 40960)){
			fprintf(file, "%04X %s %04X %s %s%d %s%d %s%d\n", index, ":", value, "-> OR", "R", rd, "R", rs, "R", rt);
		}
		else{
			fprintf(file, "%04X %s %04X\n", index, ":", value);
		}	
	}
	if(logic_type == 3)	//XOR
	{
		unsigned short rd = (unsigned short)(value<<4)>>13;
		unsigned short rs = (unsigned short)(value<<7)>>13;
		unsigned short rt = (unsigned short)(value<<13)>>13;
		if((index >= 0 && index <= 8191) || (index >= 32768 && index <= 40960)){
			fprintf(file, "%04X %s %04X %s %s%d %s%d %s%d\n", index, ":", value, "-> XOR", "R", rd, "R", rs, "R", rt);
		}
		else{
			fprintf(file, "%04X %s %04X\n", index, ":", value);
		}	
	if((unsigned short)(value<<10)>>15 == 1)	//AND IMMEDIATE
	{
		unsigned short rd = (unsigned short)(value<<4)>>13;
		unsigned short rs = (unsigned short)(value<<7)>>13;
		short imm = (short)(value<<11)>>11;
		if((index >= 0 && index <= 8191) || (index >= 32768 && index <= 40960)){
			fprintf(file, "%04X %s %04X %s %s%d %s%d %d\n", index, ":", value, "-> AND", "R", rd, "R", rs, imm);
		}
		else{
			fprintf(file, "%04X %s %04X\n", index, ":", value);
		}
	}
	else return;
	}
}

void load_convert(unsigned short index, unsigned short value, FILE *file)
{
	unsigned short rd = (unsigned short)(value<<4)>>13;
	unsigned short rs = (unsigned short)(value<<7)>>13;
	short imm = (short)(value<<10)>>10;
	if((index >= 0 && index <= 8191) || (index >= 32768 && index <= 40960)){
		fprintf(file, "%04X %s %04X %s %s%d %s%d %d\n", index, ":", value, "-> LDR", "R", rd, "R", rs, imm);
	}
	else{
		fprintf(file, "%04X %s %04X\n", index, ":", value);
	}	
}

void store_convert(unsigned short index, unsigned short value, FILE *file)
{
	unsigned short rt = (unsigned short)(value<<4)>>13;
	unsigned short rs = (unsigned short)(value<<7)>>13;
	short imm = (short)(value<<10)>>10;
	if((index >= 0 && index <= 8191) || (index >= 32768 && index <= 40960)){
		fprintf(file, "%04X %s %04X %s %s%d %s%d %d\n", index, ":", value, "-> STR", "R", rt, "R", rs, imm);
	}
	else{
		fprintf(file, "%04X %s %04X\n", index, ":", value);
	}
}

void rti_convert(unsigned short index, unsigned short value, FILE *file)
{
	if((index >= 0 && index <= 8191) || (index >= 32768 && index <= 40960)){
		fprintf(file, "%04X %s %04X %s\n", index, ":", value, "-> RTI");
	}
	else{
		fprintf(file, "%04X %s %04X\n", index, ":", value);
	}	
}

void const_convert(unsigned short index, unsigned short value, FILE *file)
{
	unsigned short rd = (unsigned short)(value<<4)>>13;
	short imm = (short)(value<<7)>>7;
	if((index >= 0 && index <= 8191) || (index >= 32768 && index <= 40960)){
		fprintf(file, "%04X %s %04X %s %s%d %d\n", index, ":", value, "-> CONST", "R", rd, imm);
	}
	else{
		fprintf(file, "%04X %s %04X\n", index, ":", value);
	}
}

void mod_sll_sra_srl(unsigned short index, unsigned short value, FILE *file)
{
	unsigned short ref = (unsigned short)(value<<10)>>14;

	if(ref == 3)	//MOD
	{
		unsigned short rd = (unsigned short)(value<<4)>>13;
		unsigned short rs = (unsigned short)(value<<7)>>13;
		unsigned short rt = (unsigned short)(value<<13)>>13;
		if((index >= 0 && index <= 8191) || (index >= 32768 && index <= 40960)){
			fprintf(file, "%04X %s %04X %s %s%d %s%d %s%d\n", index, ":", value, "-> MOD", "R", rd, "R", rs, "R", rt);
		}
		else{
			fprintf(file, "%04X %s %04X\n", index, ":", value);
		}
	}
	if(ref == 0)	//SLL
	{
		unsigned short rd = (unsigned short)(value<<4)>>13;
		unsigned short rs = (unsigned short)(value<<7)>>13;
		unsigned short uimm = (unsigned short)(value<<12)>>12;
		if((index >= 0 && index <= 8191) || (index >= 32768 && index <= 40960)){
			fprintf(file, "%04X %s %04X %s %s%d %s%d %d\n", index, ":", value, "-> SLL", "R", rd, "R", rs, uimm);
		}
		else{
			fprintf(file, "%04X %s %04X\n", index, ":", value);
		}
	}
	if(ref == 1)	//SRA
	{
		unsigned short rd = (unsigned short)(value<<4)>>13;
		unsigned short rs = (unsigned short)(value<<7)>>13;
		unsigned short uimm = (unsigned short)(value<<12)>>12;
		if((index >= 0 && index <= 8191) || (index >= 32768 && index <= 40960)){
			fprintf(file, "%04X %s %04X %s %s%d %s%d %d\n", index, ":", value, "-> SRA", "R", rd, "R", rs, uimm);
		}
		else{
			fprintf(file, "%04X %s %04X\n", index, ":", value);
		}
	}
	if(ref == 2)	//SRL
	{
		unsigned short rd = (unsigned short)(value<<4)>>13;
		unsigned short rs = (unsigned short)(value<<7)>>13;
		unsigned short uimm = (unsigned short)(value<<12)>>12;
		if((index >= 0 && index <= 8191) || (index >= 32768 && index <= 40960)){
			fprintf(file, "%04X %s %04X %s %s%d %s%d %d\n", index, ":", value, "-> SRL", "R", rd, "R", rs, uimm);
		}
		else{
			fprintf(file, "%04X %s %04X\n", index, ":", value);
		}
	}
	else return;
}

void jmp_r_convert(unsigned short index, unsigned short value, FILE *file)
{
	if((unsigned short)(value<<4)>>15 == 0)	//JMPR
	{
		unsigned short rs = (unsigned short)(value<<7)>>13;
		if((index >= 0 && index <= 8191) || (index >= 32768 && index <= 40960)){
			fprintf(file, "%04X %s %04X %s %s%d\n", index, ":", value, "-> JMPR", "R", rs);
		}
		else{
			fprintf(file, "%04X %s %04X\n", index, ":", value);
		}
	}
	if((unsigned short)(value<<4)>>15 == 1)	//JMP
	{
		short imm = (short)(value<<5)>>5;
		if((index >= 0 && index <= 8191) || (index >= 32768 && index <= 40960)){
			fprintf(file, "%04X %s %04X %s %d\n", index, ":", value, "-> JMP", imm);
		}
		else{
			fprintf(file, "%04X %s %04X\n", index, ":", value);
		}
	}
	else return;
}

void hiconst_convert(unsigned short index, unsigned short value, FILE *file)
{
	unsigned short rd = (unsigned short)(value<<4)>>13;
	unsigned short imm = (unsigned short)(value<<8)>>8;
	if((index >= 0 && index <= 8191) || (index >= 32768 && index <= 40960)){
		fprintf(file, "%04X %s %04X %s %s%d %d\n", index, ":", value, "-> HICONST", "R", rd, imm);
	}
	else{
		fprintf(file, "%04X %s %04X\n", index, ":", value);
	}
}

void trap_convert(unsigned short index, unsigned short value, FILE *file)
{
	unsigned short uimm = (unsigned short)(value<<8)>>8;
	if((index >= 0 && index <= 8191) || (index >= 32768 && index <= 40960)){
		fprintf(file, "%04X %s %04X %s %d\n", index, ":", value, "-> TRAP", uimm);
	}
	else{
		fprintf(file, "%04X %s %04X\n", index, ":", value);
	}
}
