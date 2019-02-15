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
#include <stdbool.h>

static unsigned short PC = 0x8200;
static unsigned short regFileWE = 0;
static unsigned short registers[8];
static unsigned short NZPWE = 0;
static unsigned short PSR = 0x8002;
static int NZP = 2;		//NZP bit
static unsigned short DATAWE = 0;
static unsigned short address = 0;
static unsigned short memVal = 0;

void decode(unsigned short *memory, FILE *output)
{
	while(PC != 0x80FF){
		//for(int index = 0; index <40960; index++){
			//if(memory[PC] != 0){
				unsigned short opcode = (unsigned short) memory[PC]>>12;
				unsigned short value = (unsigned short)memory[PC];

				if(opcode == 0){
					branch_convert(PC, value, output);
				}
				else if(opcode == 1){
					arithmetic_convert(PC, value, output, registers);
				}
				else if(opcode == 2){
					comparison_convert(PC, value, output);
				}
				else if(opcode == 4){
					jsr_r_convert(PC, value, output, registers);
				}
				else if(opcode == 5){
					logic_convert(PC, value, output, registers);
				}
				else if(opcode == 6){
					load_convert(PC, value, output, registers, memory);
				}
				else if(opcode == 7){
					store_convert(PC, value, output, memory);
				}
				else if(opcode == 8){
					rti_convert(PC, value, output);
				}
				else if(opcode == 9){
					const_convert(PC, value, output, registers);
				}
				else if(opcode == 10){
					mod_sll_sra_srl(PC, value, output, registers);
				}
				else if(opcode == 12){
					jmp_r_convert(PC, value, output);
				}
				else if(opcode == 13){
					hiconst_convert(PC, value, output, registers);
				}
				else if(opcode == 15){
					trap_convert(PC, value, output, registers);
				}
			//}
		}
		return;
}

void branch_convert(unsigned short index, unsigned short value, FILE *file)
{	
	regFileWE = 0;
	unsigned short regVal = 0;
	unsigned short reg = 0;
	NZPWE = 0;
	//DATAWE = 0;
	unsigned short branch_type = (unsigned short)(value<<4)>>13;
	//printf("%d\n", NZP);

	if(branch_type == 0)	//NOP
	{
		//printf("%s\n", "NOP");
		printPC(PC, file);
		hex2binary(value, file);
		printRFWE(regFileWE, file);
		printReg(reg, file);
		printRegVal(regVal, file);
		printNZPWE(NZPWE, file);
		printNZP(0, file);
		printDATAWE(0, file);
		printAddress(address, file);
		printMemVal(memVal, file);
		printR_PC(PC, registers);
		PC = PC + 1;
	}
	else if(branch_type == 1 && NZP == 1) 	//BRp 	&& NZP == 1)
	{
		short imm = (short)(value<<7)>>7;
		imm = signext(value, 9, 1);
		printPC(PC, file);
		hex2binary(value, file);
		printRFWE(regFileWE, file);
		printReg(reg, file);
		printRegVal(regVal, file);
		printNZPWE(NZPWE, file);
		printNZP(0, file);
		printDATAWE(0, file);
		printAddress(address, file);
		printMemVal(memVal, file);
		printR_PC(PC, registers);
		PC = PC + 1 + imm;
	}
	else if(branch_type == 2 && NZP == 2)	//BRz   && NZP == 2
	{
		short imm = (short)(value<<7)>>7;
		imm = signext(value, 9, 1);
		printPC(PC, file);
		hex2binary(value, file);
		printRFWE(regFileWE, file);
		printReg(reg, file);
		printRegVal(regVal, file);
		printNZPWE(NZPWE, file);
		printNZP(0, file);
		printDATAWE(0, file);
		printAddress(address, file);
		printMemVal(memVal, file);
		printR_PC(PC, registers);
		PC = PC + 1 + imm;
		//printf("%d\n", PC);
	}
	else if(branch_type == 3 && (NZP == 1 || NZP == 2))	//BRzp  //&& (NZP == 1 || NZP == 2) 
	{
		short imm = (short)(value<<7)>>7;
		imm = signext(value, 9, 1);
		printPC(PC, file);
		hex2binary(value, file);
		printRFWE(regFileWE, file);
		printReg(reg, file);
		printRegVal(regVal, file);
		printNZPWE(NZPWE, file);
		printNZP(0, file);
		printDATAWE(0, file);
		printAddress(address, file);
		printMemVal(memVal, file);
		printR_PC(PC, registers);
		PC = PC + 1 + imm;
	}
	else if(branch_type == 4 && NZP == 4)	//BRn    && NZP == 4
	{
		short imm = (short)(value<<7)>>7;
		imm = signext(value, 9, 1);
		printPC(PC, file);
		hex2binary(value, file);
		printRFWE(regFileWE, file);
		printReg(reg, file);
		printRegVal(regVal, file);
		printNZPWE(NZPWE, file);
		printNZP(0, file);
		printDATAWE(0, file);
		printAddress(address, file);
		printMemVal(memVal, file);
		printR_PC(PC, registers);
		PC = PC + 1 + imm;
	}
	else if(branch_type == 5 && (NZP == 4 || NZP == 1))	//BRnp    && (NZP == 4 || NZP == 1) TODOOOOOO!!!!!
	{
		short imm = (short)(value<<7)>>7;
		imm = signext(value, 9, 1);
		printPC(PC, file);
		hex2binary(value, file);
		printRFWE(regFileWE, file);
		printReg(reg, file);
		printRegVal(regVal, file);
		printNZPWE(NZPWE, file);
		printNZP(0, file);
		printDATAWE(0, file);
		printAddress(address, file);
		printMemVal(memVal, file);
		printR_PC(PC, registers);
		PC = PC + 1 + imm;
	}
	else if(branch_type == 6 && (NZP == 4 || NZP == 2))	//BRnz    
	{
		short imm = (short)(value<<7)>>7;
		imm = signext(value, 9, 1);
		printPC(PC, file);
		hex2binary(value, file);
		printRFWE(regFileWE, file);
		printReg(reg, file);
		printRegVal(regVal, file);
		printNZPWE(NZPWE, file);
		printNZP(0, file);
		printDATAWE(0, file);
		printAddress(address, file);
		printMemVal(memVal, file);
		printR_PC(PC, registers);
		PC = PC + 1 + imm;
	}
	else if(branch_type == 7)	//BRnzp
	{
		short imm = (short)(value<<7)>>7;
		imm = signext(value, 9, 1);
		printPC(PC, file);
		hex2binary(value, file);
		printRFWE(regFileWE, file);
		printReg(reg, file);
		printRegVal(regVal, file);
		printNZPWE(NZPWE, file);
		printNZP(0, file);
		printDATAWE(0, file);
		printAddress(address, file);
		printMemVal(memVal, file);
		printR_PC(PC, registers);
		PC = PC + 1 + imm;
	}
	else {
		printPC(PC, file);
		hex2binary(value, file);
		printRFWE(regFileWE, file);
		printReg(reg, file);
		printRegVal(regVal, file);
		printNZPWE(NZPWE, file);
		printNZP(0, file);
		printDATAWE(0, file);
		printAddress(address, file);
		printMemVal(memVal, file);
		printR_PC(PC, registers);
		PC = PC + 1;
	}
}

void arithmetic_convert(unsigned short index, unsigned short value, FILE *file, unsigned short *registers)
{
	regFileWE = 1;
	NZPWE = 1;
	unsigned short reg;
	short regVal;
	//DATAWE = 0;
	unsigned short arith_type = (unsigned short)(value<<10)>>13;
	
	if(arith_type == 0)	//ADD
	{
		unsigned short rd = (unsigned short)(value<<4)>>13;
		unsigned short rs = (unsigned short)(value<<7)>>13;
		unsigned short rt = (unsigned short)(value<<13)>>13;

		reg = rd;
		regVal = registers[rs]+registers[rt];
		//printf("%s %d\n", "ADD: ", regVal);
		NZP = NZPtest(regVal);
		//printf("%d\n", NZP);
		registers[reg] = regVal;

		printPC(PC, file);
		hex2binary(value, file);
		printRFWE(regFileWE, file);
		printReg(reg, file);
		printRegVal(regVal, file);
		printNZPWE(NZPWE, file);
		printNZP(NZP, file);
		printDATAWE(0, file);
		printAddress(address, file);
		printMemVal(memVal, file);
		printR_PC(PC, registers);
		PC = PC + 1;
	}
	else if(arith_type == 1)	//MUL
	{
		unsigned short rd = (unsigned short)(value<<4)>>13;
		unsigned short rs = (unsigned short)(value<<7)>>13;
		unsigned short rt = (unsigned short)(value<<13)>>13;

		reg = rd;
		regVal = registers[rs]*registers[rt];
		//printf("%s %d\n", "MUL: ", regVal);
		NZP = NZPtest(regVal);
		//printf("%d\n", NZP);

		registers[reg] = regVal;

		printPC(PC, file);
		hex2binary(value, file);
		printRFWE(regFileWE, file);
		printReg(reg, file);
		printRegVal(regVal, file);
		printNZPWE(NZPWE, file);
		printNZP(NZP, file);
		printDATAWE(0, file);
		printAddress(address, file);
		printMemVal(memVal, file);
		printR_PC(PC, registers);
		PC = PC + 1;
	}
	else if(arith_type == 2)	//SUB
	{
		unsigned short rd = (unsigned short)(value<<4)>>13;
		unsigned short rs = (unsigned short)(value<<7)>>13;
		unsigned short rt = (unsigned short)(value<<13)>>13;

		reg = rd;
		regVal = registers[rs]-registers[rt];
		//printf("%s %d\n", "SUB: ", regVal);
		NZP = NZPtest(regVal);
		//printf("%d\n", NZP);

		registers[reg] = regVal;

		printPC(PC, file);
		hex2binary(value, file);
		printRFWE(regFileWE, file);
		printReg(reg, file);
		printRegVal(regVal, file);
		printNZPWE(NZPWE, file);
		printNZP(NZP, file);
		printDATAWE(0, file);
		printAddress(address, file);
		printMemVal(memVal, file);
		printR_PC(PC, registers);
		PC = PC + 1;
	}
	else if(arith_type == 3)	//DIV
	{
		unsigned short rd = (unsigned short)(value<<4)>>13;
		unsigned short rs = (unsigned short)(value<<7)>>13;
		unsigned short rt = (unsigned short)(value<<13)>>13;

		reg = rd;
		regVal = registers[rs]/registers[rt];
		//printf("%s %d\n", "DIV: ", regVal);
		NZP = NZPtest(regVal);
		//printf("%d\n", NZP);

		registers[reg] = regVal;

		printPC(PC, file);
		hex2binary(value, file);
		printRFWE(regFileWE, file);
		printReg(reg, file);
		printRegVal(regVal, file);
		printNZPWE(NZPWE, file);
		printNZP(NZP, file);
		printDATAWE(0, file);
		printAddress(address, file);
		printMemVal(memVal, file);
		printR_PC(PC, registers);
		PC = PC + 1;
	}
	else if((unsigned short)(value<<10)>>15 == 1)	//ADD IMM
	{
		unsigned short rd = (unsigned short)(value<<4)>>13;
		unsigned short rs = (unsigned short)(value<<7)>>13;
		short imm = (short)(value<<11)>>11;
		imm = signext(value, 5, 2);

		reg = rd;

		regVal = (registers[rs]+imm);
		//printf("%s %d\n", "ADD imm: ", (short)regVal);

		NZP = NZPtest(regVal);
		//printf("%d\n", NZP);


		registers[reg] = (short)regVal;

		// for(int i = 0; i<8; i++){
		// 	printf("%d\n", (short)registers[i]);
		// }	

		printPC(PC, file);
		hex2binary(value, file);
		printRFWE(regFileWE, file);
		printReg(reg, file);
		printRegVal(regVal, file);
		printNZPWE(NZPWE, file);
		printNZP(NZP, file);
		printDATAWE(0, file);
		printAddress(address, file);
		printMemVal(memVal, file);
		printR_PC(PC, registers);
		PC = PC + 1;
	}
	else return;
}

void comparison_convert(unsigned short index, unsigned short value, FILE *file)
{
	regFileWE = 0;
	unsigned short regVal = 0;
	unsigned short reg = 0;
	NZPWE = 1;
	//DATAWE = 0;
	unsigned short comparison_type = (unsigned short)(value<<7)>>14;

	if(comparison_type == 0)	//CMP
	{
		unsigned short rs = (unsigned short)(value<<4)>>13;
		unsigned short rt = (unsigned short)(value<<13)>>13;
		NZP = NZPtest((short)registers[rs] - (short)registers[rt]);
		//printf("%d\n", NZP);
		printPC(PC, file);
		hex2binary(value, file);
		printRFWE(regFileWE, file);
		printReg(reg, file);
		printRegVal(regVal, file);
		printNZPWE(NZPWE, file);
		printNZP(NZP, file);
		printDATAWE(0, file);
		printAddress(address, file);
		printMemVal(memVal, file);
		printR_PC(PC, registers);
		PC = PC + 1;
	}
	else if(comparison_type == 1)	//CMPU
	{
		unsigned short rs = (unsigned short)(value<<4)>>13;
		unsigned short rt = (unsigned short)(value<<13)>>13;
		NZP = NZPtest(registers[rs] - registers[rt]);
		//printf("%d\n", NZP);
		printPC(PC, file);
		hex2binary(value, file);
		printRFWE(regFileWE, file);
		printReg(reg, file);
		printRegVal(regVal, file);
		printNZPWE(NZPWE, file);
		printNZP(NZP, file);
		printDATAWE(0, file);
		printAddress(address, file);
		printMemVal(memVal, file);
		printR_PC(PC, registers);
		PC = PC + 1;
	}
	else if(comparison_type == 2)	//CMPI
	{
		unsigned short rs = (unsigned short)(value<<4)>>13;
		//short imm = (short)(value<<9)>>9;
		short imm = signext(value, 7, 4);
		//printf("imm %d\n", signext(value, 7,4));
		NZP = NZPtest((registers[rs] - imm));
		printPC(PC, file);
		hex2binary(value, file);
		printRFWE(regFileWE, file);
		printReg(reg, file);
		printRegVal(regVal, file);
		printNZPWE(NZPWE, file);
		printNZP(NZP, file);
		printDATAWE(0, file);
		printAddress(address, file);
		printMemVal(memVal, file);
		printR_PC(PC, registers);
		PC = PC + 1;
	}
	else if(comparison_type == 3)	//CMPIU
	{
		unsigned short rs = (unsigned short)(value<<4)>>13;
		unsigned short uimm = (unsigned short)(value<<9)>>9;
		NZP = NZPtest(registers[rs] - uimm);
		printPC(PC, file);
		hex2binary(value, file);
		printRFWE(regFileWE, file);
		printReg(reg, file);
		printRegVal(regVal, file);
		printNZPWE(NZPWE, file);
		printNZP(NZP, file);
		printDATAWE(0, file);
		printAddress(address, file);
		printMemVal(memVal, file);
		printR_PC(PC, registers);
		PC = PC + 1;
	}
	else return;
}

void jsr_r_convert(unsigned short index, unsigned short value, FILE *file, unsigned short *registers)
{
	regFileWE = 1;
	NZPWE = 1;
	unsigned short reg;
	unsigned short regVal;

	if((unsigned short)(value<<4)>>15 == 0)	//JSRR
	{
		reg = 7;
		unsigned short rs = (unsigned short)(value<<7)>>13;	
		printPC(PC, file);

		printR_PC(PC, registers);
		regVal = PC + 1;
		PC = registers[rs];
		NZP = NZPtest(regVal);
		registers[7] = regVal;
		hex2binary(value, file);
		printRFWE(regFileWE, file);
		printReg(reg, file);
		printRegVal(regVal, file);
		printNZPWE(NZPWE, file);
		printNZP(NZP, file);
		printDATAWE(0, file);
		printAddress(address, file);
		printMemVal(memVal, file);
		
	}
	else if((unsigned short)(value<<4)>>15 == 1)	//JSR
	{
		reg = 7;
		regVal = PC + 1;
		registers[7] = regVal;
		NZP = NZPtest(regVal);
		short imm = (short)(value<<5)>>5;
		imm = signext(value, 11, 5);	
		printPC(PC, file);
		hex2binary(value, file);
		printRFWE(regFileWE, file);
		printReg(reg, file);
		printRegVal(regVal, file);
		printNZPWE(NZPWE, file);
		printNZP(NZP, file);
		printDATAWE(0, file);
		printAddress(address, file);
		printMemVal(memVal, file);

		printR_PC(PC, registers);
		PC = (PC & 0x8000) | (imm << 4);
	}
	else return;
}

void logic_convert(unsigned short index, unsigned short value, FILE *file, unsigned short *registers)
{
	regFileWE = 1;
	NZPWE = 1;
	unsigned short reg;
	unsigned short regVal;
	unsigned short logic_type = (unsigned short)(value<<10)>>13;

	if(logic_type == 0)	//AND
	{
		unsigned short rd = (unsigned short)(value<<4)>>13;
		unsigned short rs = (unsigned short)(value<<7)>>13;
		unsigned short rt = (unsigned short)(value<<13)>>13;

		reg = rd;
		regVal = registers[rs]&registers[rt];
		NZP = NZPtest(regVal);
		registers[reg] = regVal;

		printPC(PC, file);
		hex2binary(value, file);
		printRFWE(regFileWE, file);
		printReg(reg, file);
		printRegVal(regVal, file);
		printNZPWE(NZPWE, file);
		printNZP(NZP, file);
		printDATAWE(0, file);
		printAddress(address, file);
		printMemVal(memVal, file);

		printR_PC(PC, registers);
		PC = PC + 1;
	}
	else if(logic_type == 1)	//NOT
	{
		unsigned short rd = (unsigned short)(value<<4)>>13;
		unsigned short rs = (unsigned short)(value<<7)>>13;

		reg = rd;
		regVal = ~registers[rs];
		NZP = NZPtest(regVal);
		registers[reg] = regVal;
		printPC(PC, file);
		hex2binary(value, file);
		printRFWE(regFileWE, file);
		printReg(reg, file);
		printRegVal(regVal, file);
		printNZPWE(NZPWE, file);
		printNZP(NZP, file);
		printDATAWE(0, file);
		printAddress(address, file);
		printMemVal(memVal, file);

		printR_PC(PC, registers);
		PC = PC + 1;
	}
	else if(logic_type == 2)	//OR
	{
		unsigned short rd = (unsigned short)(value<<4)>>13;
		unsigned short rs = (unsigned short)(value<<7)>>13;
		unsigned short rt = (unsigned short)(value<<13)>>13;

		reg = rd;
		regVal = registers[rs]|registers[rt];
		NZP = NZPtest(regVal);
		registers[reg] = regVal;	
		printPC(PC, file);
		hex2binary(value, file);
		printRFWE(regFileWE, file);
		printReg(reg, file);
		printRegVal(regVal, file);
		printNZPWE(NZPWE, file);
		printNZP(NZP, file);
		printDATAWE(0, file);
		printAddress(address, file);
		printMemVal(memVal, file);

		printR_PC(PC, registers);
		PC = PC + 1;
	}
	else if(logic_type == 3)	//XOR
	{
		unsigned short rd = (unsigned short)(value<<4)>>13;
		unsigned short rs = (unsigned short)(value<<7)>>13;
		unsigned short rt = (unsigned short)(value<<13)>>13;

		reg = rd;
		regVal = registers[rs]^registers[rt];
		NZP = NZPtest(regVal);
		registers[reg] = regVal;
		printPC(PC, file);
		hex2binary(value, file);
		printRFWE(regFileWE, file);
		printReg(reg, file);
		printRegVal(regVal, file);
		printNZPWE(NZPWE, file);
		printNZP(NZP, file);
		printDATAWE(0, file);
		printAddress(address, file);
		printMemVal(memVal, file);

		printR_PC(PC, registers);
		PC = PC + 1;
	}
	if((unsigned short)(value<<10)>>15 == 1)	//AND IMMEDIATE
	{
		unsigned short rd = (unsigned short)(value<<4)>>13;
		unsigned short rs = (unsigned short)(value<<7)>>13;
		short imm = (short)(value<<11)>>11;
		imm = signext(value, 5, 2);
		reg = rd;
		regVal = registers[rs]&imm;
		NZP = NZPtest(regVal);
		registers[reg] = regVal;
		printPC(PC, file);
		hex2binary(value, file);
		printRFWE(regFileWE, file);
		printReg(reg, file);
		printRegVal(regVal, file);
		printNZPWE(NZPWE, file);
		printNZP(NZP, file);
		printDATAWE(0, file);
		printAddress(address, file);
		printMemVal(memVal, file);

		printR_PC(PC, registers);
		PC = PC + 1;
	}
	else return;
}

void load_convert(unsigned short index, unsigned short value, FILE *file, unsigned short *registers, unsigned short *memory)
{
	regFileWE = 1;
	NZPWE = 1;
	unsigned short rd = (unsigned short)(value<<4)>>13;
	unsigned short rs = (unsigned short)(value<<7)>>13;
	//short imm = (short)(value<<10)>>10;
	short imm = signext(value, 6, 3);
	//printf("function imm: %d\n", imm);
	if(PSR == 0 && (registers[rs]+imm >= 0xA000 && registers[rs]+imm <= 0xFFF)){
		exit(1);
	}
	if((registers[rs]+imm >= 0x0000 && registers[rs]+imm <= 0x1FFF) || (registers[rs]+imm >= 0x8000 && registers[rs]+imm <= 0x9FFF)){
		exit(1);
	}
	unsigned short reg = rd;
	unsigned short regVal = memory[registers[rs]+imm];
	unsigned short address = registers[rs]+imm;
	//printf("regVal: %04X\n", regVal);
	//printf("address: %04X\n", registers[rs]+imm);
	NZP = NZPtest(regVal);
	registers[rd] = regVal;
	
	printPC(PC, file);
	hex2binary(value, file);
	printRFWE(regFileWE, file);
	printReg(reg, file);
	printRegVal(regVal, file);
	printNZPWE(NZPWE, file);
	printNZP(NZP, file);
	printDATAWE(0, file);
	printAddress(address, file);
	printMemVal(regVal, file);

	printR_PC(PC, registers);
	PC = PC + 1;
	// printf("%04hX\n", PC);
}

void store_convert(unsigned short index, unsigned short value, FILE *file, unsigned short *memory)
{
	regFileWE = 0;
	NZPWE = 0;
	//NZP = 0;
	DATAWE = 1;
	unsigned short regVal = 0;
	unsigned short reg = 0;
	unsigned short rt = (unsigned short)(value<<4)>>13;
	unsigned short rs = (unsigned short)(value<<7)>>13;
	short imm = (short)(value<<10)>>10;
	imm = signext(value, 6, 3);
	//printf("%04X\n", registers[rs]+imm);
	if(PSR == 0 && (registers[rs]+imm >= 0xA000 && registers[rs]+imm <= 0xFFFF)){
		//printf("%s\n", "EXCEPTION");
		exit(1);
	}
	if((registers[rs]+imm >= 0x0000 && registers[rs]+imm <= 0x1FFF) || (registers[rs]+imm >= 0x8000 && registers[rs]+imm <= 0x9FFF)){
		exit(1);
	}
	memory[registers[rs]+imm] = registers[rt];	

	unsigned short address = registers[rs]+imm;
	unsigned short memVal = registers[rt];
	printPC(PC, file);
	hex2binary(value, file);
	printRFWE(regFileWE, file);
	printReg(reg, file);
	printRegVal(regVal, file);
	printNZPWE(NZPWE, file);
	printNZP(0, file);
	printDATAWE(DATAWE, file);
	printAddress(address, file);
	printMemVal(memVal, file);

	printR_PC(PC, registers);
	PC = PC + 1;
}

void rti_convert(unsigned short index, unsigned short value, FILE *file)
{
	regFileWE = 0;	
	unsigned short regVal = 0;
	unsigned short reg = 0;
	NZPWE = 0;
	//NZP = 0;
	printPC(PC, file);
	hex2binary(value, file);
	printRFWE(regFileWE, file);
	printReg(reg, file);
	printRegVal(regVal, file);
	printNZPWE(NZPWE, file);
	printNZP(0, file);
	printDATAWE(0, file);
	printAddress(address, file);
	printMemVal(memVal, file);

	printR_PC(PC, registers);
	PC = registers[7];
	PSR = 0;

		//printf("%d\n", PC);
	// for(int i = 0; i<8; i++){
	// 	printf("%d\n", registers[i]);
	// }
}

void const_convert(unsigned short index, unsigned short value, FILE *file, unsigned short *registers)
{
	regFileWE = 1;
	NZPWE = 1;
	unsigned short rd = (unsigned short)(value<<4)>>13;
	unsigned short imm = (unsigned short)((value<<7)>>7);
	//printf("%04X\n", imm);


	imm = signext(value, 9, 1);
	unsigned short reg = rd;
	short regVal = imm;
	//printf("%s %d\n", "CONST imm: ", imm);
	NZP = NZPtest(regVal);
	//printf("%d\n", NZP);
	registers[rd] = imm; 
	printPC(PC, file);
	hex2binary(value, file);
	printRFWE(regFileWE, file);
	printReg(reg, file);
	printRegVal(regVal, file);
	printNZPWE(NZPWE, file);
	printNZP(NZP, file);
	printDATAWE(0, file);
	printAddress(address, file);
	printMemVal(memVal, file);

	printR_PC(PC, registers);
	PC = PC + 1;

	

	// registers[rd] = imm;
	// for(int i = 0; i<8; i++){
	// 	printf("%d", registers[i]);
	// }
}

void mod_sll_sra_srl(unsigned short index, unsigned short value, FILE *file, unsigned short *registers)
{
	regFileWE = 1;
	NZPWE = 1;
	unsigned short reg;
	unsigned short regVal;
	unsigned short ref = (unsigned short)(value<<10)>>14;

	if(ref == 3)	//MOD
	{
		unsigned short rd = (unsigned short)(value<<4)>>13;
		unsigned short rs = (unsigned short)(value<<7)>>13;
		unsigned short rt = (unsigned short)(value<<13)>>13;

		reg = rd;
		regVal = registers[rs]%registers[rt];
		//printf("rs: %04hX\n", registers[rs]);
		//printf("rt: %04hX\n", registers[rt]);
		NZP = NZPtest(regVal);
		registers[rd] = regVal;

		printPC(PC, file);
		hex2binary(value, file);
		printRFWE(regFileWE, file);
		printReg(reg, file);
		printRegVal(regVal, file);
		printNZPWE(NZPWE, file);
		printNZP(NZP, file);
		printDATAWE(0, file);
		printAddress(address, file);
		printMemVal(memVal, file);

		printR_PC(PC, registers);
		PC = PC+1;
	}
	else if(ref == 0)	//SLL
	{
		unsigned short rd = (unsigned short)(value<<4)>>13;
		unsigned short rs = (unsigned short)(value<<7)>>13;
		unsigned short uimm = (unsigned short)(value<<12)>>12;

		reg = rd;
		regVal = registers[rs]<<uimm;
		NZP = NZPtest(regVal);
		registers[rd]=regVal;
		printPC(PC, file);
		hex2binary(value, file);
		printRFWE(regFileWE, file);
		printReg(reg, file);
		printRegVal(regVal, file);
		printNZPWE(NZPWE, file);
		printNZP(NZP, file);
		printDATAWE(0, file);
		printAddress(address, file);
		printMemVal(memVal, file);

		printR_PC(PC, registers);
		PC = PC+1;
	}
	else if(ref == 1)	//SRA
	{
		unsigned short rd = (unsigned short)(value<<4)>>13;
		unsigned short rs = (unsigned short)(value<<7)>>13;
		unsigned short uimm = (unsigned short)(value<<12)>>12;

		reg = rd;
		short val = (short)registers[rs];
		val = (short)val>>uimm;
		//printf("regVal: %04hX\n", val);
		//printf("rt: %04hX\n", registers[rt]);
		NZP = NZPtest(val);
		registers[rd]=val;
		printPC(PC, file);
		hex2binary(value, file);
		printRFWE(regFileWE, file);
		printReg(reg, file);
		printRegVal(val, file);
		printNZPWE(NZPWE, file);
		printNZP(NZP, file);
		printDATAWE(0, file);
		printAddress(address, file);
		printMemVal(memVal, file);

		printR_PC(PC, registers);
		PC = PC+1;
	}
	else if(ref == 2)	//SRL
	{
		unsigned short rd = (unsigned short)(value<<4)>>13;
		unsigned short rs = (unsigned short)(value<<7)>>13;
		unsigned short uimm = (unsigned short)(value<<12)>>12;

		reg = rd;
		regVal = registers[rs]>>uimm;
		NZP = NZPtest(regVal);
		registers[rd]=regVal;
		printPC(PC, file);
		hex2binary(value, file);
		printRFWE(regFileWE, file);
		printReg(reg, file);
		printRegVal(regVal, file);
		printNZPWE(NZPWE, file);
		printNZP(NZP, file);
		printDATAWE(0, file);
		printAddress(address, file);
		printMemVal(memVal, file);

		printR_PC(PC, registers);
		PC = PC+1;
	}
	else return;
}

void jmp_r_convert(unsigned short index, unsigned short value, FILE *file)
{
	regFileWE = 0;
	NZPWE = 0;
	NZP = 0;
	unsigned short regVal = 0;
	unsigned short reg = 0;
	if((unsigned short)(value<<4)>>15 == 0)	//JMPR
	{
		unsigned short rs = (unsigned short)(value<<7)>>13;
		printPC(PC, file);
		hex2binary(value, file);
		printRFWE(regFileWE, file);
		printReg(reg, file);
		printRegVal(regVal, file);
		printNZPWE(NZPWE, file);
		printNZP(0, file);
		printDATAWE(0, file);
		printAddress(address, file);
		printMemVal(memVal, file);

		printR_PC(PC, registers);
		PC = registers[rs];
	}
	else if((unsigned short)(value<<4)>>15 == 1)	//JMP
	{
		short imm = (short)(value<<5)>>5;
		imm = signext(value, 11, 5);
		printPC(PC, file);
		hex2binary(value, file);
		printRFWE(regFileWE, file);
		printReg(reg, file);
		printRegVal(regVal, file);
		printNZPWE(NZPWE, file);
		printNZP(0, file);
		printDATAWE(0, file);
		printAddress(address, file);
		printMemVal(memVal, file);

		printR_PC(PC, registers);
		PC = PC+1+imm;
	}
	else return;
}

void hiconst_convert(unsigned short index, unsigned short value, FILE *file, unsigned short *registers)
{
	regFileWE = 1;
	NZPWE = 1;
	unsigned short rd = (unsigned short)(value<<4)>>13;
	unsigned short uimm = (unsigned short)(value<<8)>>8;

	unsigned short reg = rd;
	unsigned short regVal = (registers[rd] & 0xFF) | (uimm<<8);
	NZP = NZPtest(regVal);
	registers[rd] = regVal;
	printPC(PC, file);
	hex2binary(value, file);
	printRFWE(regFileWE, file);
	printReg(reg, file);
	printRegVal(regVal, file);
	printNZPWE(NZPWE, file);
	printNZP(NZP, file);
	printDATAWE(0, file);
	printAddress(address, file);
	printMemVal(memVal, file);

	printR_PC(PC, registers);
	PC = PC+1;
}

void trap_convert(unsigned short index, unsigned short value, FILE *file, unsigned short *registers)
{
	regFileWE = 1;
	NZPWE = 1;
	unsigned short uimm = (unsigned short)(value<<8)>>8;

	unsigned short reg = 7;
	unsigned short regVal = PC + 1;
	registers[7] = regVal;
	NZP = NZPtest(regVal);
	//printf("%s %d\n", "TRAP: ", regVal);
	//printf("%d\n", NZP);
	printPC(PC, file);
	hex2binary(value, file);
	printRFWE(regFileWE, file);
	printReg(reg, file);
	printRegVal(regVal, file);
	printNZPWE(NZPWE, file);
	printNZP(NZP, file);
	printDATAWE(0, file);
	printAddress(address, file);
	printMemVal(memVal, file);

	printR_PC(PC, registers);
	PC = (0x8000 | uimm);
	//printf("%d\n", PC);
	PSR = 1;
}

void printPC(unsigned short PC, FILE *file){
	fprintf(file, "%04hX ", PC);
}
void hex2binary(unsigned short value, FILE *file){
	for(int i = 15; i >= 0; i--){
		if(((value >> i) & 0x0001) == 1){
			fprintf(file, "%d", 1);
		}
		else{
			fprintf(file, "%d", 0);
		}
	}
	fprintf(file, " ");
}
void printRFWE(unsigned short regFileWE, FILE *file){
	fprintf(file, "%01hX ", regFileWE);
}
int NZPtest(unsigned short regVal){
	//int NZP;
	if(((regVal>>15) & 0x0001) == 1){	//BRn
		return NZP = 4;
	}
	else if(regVal == 0x0000){	//BRz
		return NZP = 2;
	}
	else{	//BRp
		return NZP = 1;
	}
}
void printReg(unsigned short reg, FILE *file){
	fprintf(file, "%01hX ", reg);
}
void printRegVal(unsigned short regVal, FILE *file){
	fprintf(file, "%04hX ", regVal);
}
void printNZPWE(unsigned short NZPWE, FILE *file){
	fprintf(file, "%01hX ", NZPWE);
}
void printNZP(int NZP, FILE *file){
	fprintf(file, "%01X ", NZP);
}
void printDATAWE(unsigned short DATAWE, FILE *file){
	fprintf(file, "%01hX ", DATAWE);
}
void printAddress(unsigned short address, FILE *file){
	fprintf(file, "%04X ", address);
}
void printMemVal(unsigned short memVal, FILE *file){
	fprintf(file, "%04hX\n", memVal);
}
void printR_PC(unsigned short PC, unsigned short *registers){
	if(PC == 0x80FF){
		printf("%04hX\n", PC);
		for(int i = 0; i<8; i++){
			printf("%s %d %04hX\n", "R", i, registers[i]);
		}
	}
}

unsigned short signext(unsigned short value, int num, int type){
	unsigned short imm = value;
		switch(type){
			case 1: 	//IMM9
				imm = imm & 0x1FF;
				if(imm & 0x100){
					return imm = imm | 0xFE00;
				}
				else{
					return imm;
				}
				break;
			case 2:		//IMM5
				imm = imm & 0x1F;
				if(imm & 0x10){
					return imm = imm | 0xFFE0;
				}
				else{
					return imm;
				}
				break;
			case 3:		//IMM6

				imm = imm & 0x3F;
				if(imm & 0x20){
					
					imm = imm | 0xFFC0;
					//printf("negative imm: %04hX\n", imm);
					return imm;

				}
				else{
					//printf("Got here\n");
					//printf("imm: %04hX\n", imm);
					return imm;
				}
				break;
			case 4: 	//IMM7
				imm = imm & 0x7F;
				//printf("GOT HERE\n");
				//printf("old imm: %d\n", imm);
				if(imm & 0x40){
					imm = imm | 0xFF80;
					//printf("fake imm: %d\n", imm);
					return imm;
				}
				else{
					//printf("new IMM: %d\n", imm);
					return imm;
				}
				break;
			case 5: 	//IMM11
				imm = imm & 0x7FF;
				if(imm & 0x400){
					return imm = imm | 0xF800;
				}
				else{
					return imm;
				}
				break;
			default:
				return imm;
				break;
		}
}

