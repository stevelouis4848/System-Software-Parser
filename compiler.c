# include <stdlib.h>
# include <stdio.h>
# include <ctype.h>
# include <string.h>
# include"header.h"
# include"lexical.c"
# include"test.c"
# include"VM.c"

int main( int argc, char **argv){

	int i;

	for (i = 1;i < argc; i++){
		
		if(strcmp(argv[i], "-l") == 0){
			printf("-l print lexical\n");
			lexicalPrint++;
		}
		else if(strcmp(argv[i], "-a") == 0){
			printf("-a print parser\n");
			parserPrint++;
		}
		else if(strcmp(argv[i], "-v") == 0){
			printf("-v print vms\n");
			vmPrint++;
		}
		else{
			printf("running programs\n");
			scanner(argv[i]);
			program();
			//vm();
		}
	}
	printf("done\n");
	return 0;
}