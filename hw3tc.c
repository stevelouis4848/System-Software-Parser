// Name: Steve Louis
// Class: COP 3402 summer 2018
// Assignment: Homework #3 (Parser)
// 07/14/2018

# include <stdio.h>
# include <stdlib.h>

int const MAX_NUM_TOKENS = 500;
int const TOKEN_LENGTH = 11;
	
typedef enum{
				nulsym = 1, identsym = 2, numbersym = 3, plussym = 4, minussym = 5,
				 multsym = 6,  slashsym = 7, oddsym = 8,  eqlsym = 9, neqsym = 10, 
				 lessym = 11, leqsym = 12, 	gtrsym = 13, geqsym = 14, lparentsym = 15, 
				 rparentsym = 16, commasym = 17, semicolonsym = 18, periodsym = 19, 
				 becomessym = 20, beginsym = 21, endsym = 22, ifsym = 23, thensym = 24,
				  whilesym = 25, dosym = 26, callsym = 27, constsym = 28, varsym = 29, 
				  procsym = 30, writesym = 31, readsym = 32, elsesym = 33
}tokenNames;


typedef struct token{

				int type;
				char value[MAX_NUM_TOKENS];
}token;

typedef struct enviroment{

				token thisToken;
				int currentIndex;
				int arrayLength;
}token;

void readFile(){

	int i;
	char buffer[MAX_NUM_TOKENS];
	int buffer2;
	enviroment *thisEnviroment;

	FILE * ifp;
 	ifp = fopen("","r");

	printf("fileName:%s\n",fileName);

	enviroment = malloc(500 * sizeof(token));

	thisEnviroment->arrayLength = MAX_NUM_TOKENS;
	thisEnviroment->currentIndex = 0;


	for(i = 0; fscanf(ifp, "%s", buffer) != EOF; i++){
		
		printf("buffer: %s\n", buffer);

		buffer2 = atoi(buffer);
		thisEnviroment[i]->thisToken.type = buffer;

		if(buffer2 == 2 || buffer == 3){

			fscanf(ifp, "%s", buffer);
			strcopy(thisEnviroment[i]-> = thisToken.value, buffer);
	}

	block();		
}

char* getToken(enviroment *thisEnviroment){

	token = thisEnviroment->

	return Token;
}

void Block(){


}

void statements(){}


void condition(){}

void expression(){}

void term(){}

void factor(){}