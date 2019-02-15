/*
contains routines needed for opening and loading object files
send loaded values to LC4.c
pass this pointer into LC4.c
*/

#include "loader.h"
#include "LC4.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

unsigned short *load(FILE* file)
{
	static unsigned short memory[65536];
	// for(int index = 0; index < (sizeof(memory)/sizeof(memory[0])); index++){
 //       	 memory[index] = 0;
	// }

	unsigned short value;
	unsigned char sym;
	unsigned int size = 0;
	unsigned short index = 0;
	unsigned short filename = 0;
	unsigned short symbol;
	unsigned short line_num = 0;
	unsigned short file_index = 0;
	unsigned short num_instructions = 0;
	unsigned short num_chars = 0;
	unsigned short i = 0;
	unsigned short instruction;

	while(fread(&value, 2, 1, file) > 0)
	{
		if((value == (unsigned short) 0xDECA) || (value == (unsigned short) 0xDADA))
		{
			fread(&value, 2, 1, file);
			index = (value << 8) | (value >> 8);
			fread(&value, 2, 1, file);
			num_instructions = (value << 8) | (value >> 8);

			for(i = 0; i < num_instructions; i++)
			{
				fread(&value, 2, 1, file);
				instruction = (value << 8) | (value >> 8);
				//printf("%s %hu\n", "CODE: ", instruction);
				memory[index] = instruction;
				index++;
				size++;
			}
		}
		if(value == (unsigned short) 0xB7C3)
		{
			fread(&value, 2, 1, file);
			index = (value << 8) | (value >> 8);

			fread(&value, 2, 1, file);
			num_chars = (value << 8) | (value >> 8);

			for(i = 0; i < num_chars; i++)
			{
				fread(&value, 1, 1, file);
				symbol = ((value & 0x0F)<<4 | (value & 0xF0)>>4);
				index++;
			}
		}
		if(value == (unsigned short) 0x7EF1)
		{
			fread(&value, 2, 1, file);
			num_chars = (value << 8) | (value >> 8);

			for(i = 0; i < num_chars; i++)
			{
				fread(&value, 1, 1, file);
				filename = ((value & 0x0F)<<4 | (value & 0xF0)>>4);
				index++;
			}
		}
		if(value == (unsigned short) 0x5E71)
		{
			fread(&value, 2, 1, file);
			index = (value << 8) | (value >> 8);
			fread(&value, 2, 1, file);
			line_num = (value << 8) | (value >> 8);
			fread(&value, 2, 1, file);
			file_index = (value << 8) | (value >> 8);

		}
		// for(int index = 0; index < (sizeof(memory)/sizeof(memory[0])); index++){
  //      	 	printf( "%hu\n", memory[index]);
		// }
}
return &memory[0];
}


