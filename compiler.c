# include <stdlib.h>
# include <stdio.h>
# include <ctype.h>
# include <string.h>
#include"header.h"
# include"lexical.c"
# include"test.c"
# include"VM.c"


int main( int argc, char **argv){

	int i;

	for (i = 1;i < argc; i++){
		/*
		if(strcmp(argv[i], "-l")){
			scannerVariable = 1;
		}
		if(strcmp(argv[i], "-a")){
			parserVariable = 0;
		}
		if(strcmp(argv[i], "-v")){
			vmVariable = 0;
		}
		*/
			printf("running programs\n");
			scanner(argv[i]);
			readFile();
			//vm();
	}
	printf("done\n");
	return 0;
}