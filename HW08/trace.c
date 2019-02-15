/*
contains main routine and any routines needed to run program/parse command line arguments
set memory up using malloc
*/
#include "loader.h"
#include "LC4.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int main(int argc, char* argv[])
{	

	FILE *input;
	FILE *output;

	for(int i = 2; i < argc; i++){
		input = fopen(argv[i], "r");
		load(input); 
	}
	output = fopen(argv[1], "w");

	decode(load(input), output);

	for(int i = 0; i < argc; i++){
		fclose(input);
	}
	fclose(output);

	return 0;
}