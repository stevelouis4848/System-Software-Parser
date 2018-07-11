# include<stdlib.h>
# include<stdio.h>
# include <string.h>
# include <ctype.h>

void readFile(char *fileName);

int main(int argc, char **argv){

	int i;

	for(i = 1; i < argc; i++){
		
		readFile(argv[i]);
	}
	return 0;
}


void readFile(char *fileName){

	int i;
	char buffer[1024];

	 FILE * ifp;

	 ifp = fopen(fileName,"r");

	 printf("fileName:%s\n",fileName);


	while (fscanf(ifp, "%s", buffer) != EOF){
		
		printf("buffer: %s\n", buffer);
	}
		
}