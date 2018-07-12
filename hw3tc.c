// Name: Steve Louis
// Class: COP 3402 summer 2018
// Assignment: Homework #3 (Parser)
// 07/14/2018

# include <stdio.h>
# include <stdlib.h>

int const MAX_NUM_TOKENS = 500;
int const MAX_TOKEN_LENGTH = 11;
	
typedef enum{
				nulsym = 1, identsym , numbersym, plussym, minussym,
				 multsym,  slashsym, oddsym,  eqlsym, neqsym, 
				 lessym, leqsym, 	gtrsym, geqsym, lparentsym, 
				 rparentsym, commasym, semicolonsym, periodsym, 
				 becomessym, beginsym, endsym, ifsym, thensym,
				  whilesym, dosym, callsym, constsym, varsym, 
				  procsym, writesym, readsym, elsesym
}tokenNames;


typedef struct token{

				int type;
				char value[MAX_NUM_TOKENS];
}token;

typedef struct enviroment{

				token thisToken[MAX_NUM_TOKENS];
				symbolTable thisSymbolTable[MAX_NUM_TOKENS];
				int currentIndexToken = 0;
				int currentIndexTable = 0;
				int arrayLength = MAX_NUM_TOKENS;
}token;

typedef struct symbolTable{

							int type;
							char name[MAX_TOKEN_LENGTH];
							int value;
}

void readFile(){

	int i;
	char buffer[MAX_NUM_TOKENS];
	int buffer2;
	enviroment *thisEnviroment;

	FILE * ifp;
 	ifp = fopen("","r");

	printf("fileName:%s\n",fileName);

	enviroment = malloc(sizeof(enviroment));

	for(i = 0; fscanf(ifp, "%s", buffer) != EOF; i++){
		
		printf("buffer: %s\n", buffer);

		buffer2 = atoi(buffer);
		thisEnviroment->thisToken[i]->type = buffer;

		if(buffer2 == 2 || buffer == 3){

			fscanf(ifp, "%s", buffer);
			strcopy(thisEnviroment-> = thisToken[i]->value, buffer);
	}

	block(thisEnviroment);		
}

token *getToken(enviroment *thisEnviroment){

	thisEnviroment->currentIndexToken++;

	return thisEnviroment->thisToken[(thisEnviroment->currentIndexToken - 1)];
}

void Block(enviroment *thisEnviroment){

	token tokenHolder = getToken(thisEnviroment);

	switch(tokenHolder->type){

		case(constsym):
			do{
				tokenHolder = getToken(thisEnviroment);
				if(tokenHolder->type != identsym){
					error(4);
				}

				tokenHolder = getToken(thisEnviroment);
				if(tokenHolder->type != eqlsym){
					error(3);
				}

				tokenHolder = getToken(thisEnviroment);
				if(tokenHolder->type != numbersym){
					error(2);
				}

			} while(tokenHolder->type == commasym);

			tokenHolder = getToken(thisEnviroment);

			if(tokenHolder->type != semicolonsym){
				error(5);
			}
		break;
		case(identsym):

			do{
				tokenHolder = getToken(thisEnviroment);
			}while(token == commasym);

			tokenHolder = getToken(thisEnviroment);
			if(tokenHolder->type != semicolonsym){
				error(5);
			}
	}

	statement();
}


void statement(){


	token tokenHolder = getToken(thisEnviroment);

	switch(tokenHolder->type){

		case(identsym):
	
			tokenHolder = getToken(thisEnviroment);
			if(tokenHolder->type != becomessym){
				/*error(3);*/
			}
			expression();
			} 
		break;
		case(beginsym):

			
				statement();

			while(token == semicolonsym){

				tokenHolder = getToken(thisEnviroment);
				statement();
			}
			tokenHolder = getToken(thisEnviroment);

			if(token != endsym){

				/*error(9);*/
			}
		case(ifsym):
			tokenHolder = getToken(thisEnviroment);
			condition();

			tokenHolder = getToken(thisEnviroment);
			if(tokenHolder != thensym){

				error(16);
			}
			tokenHolder = getToken(thisEnviroment);
			statement();
		break;
		case(whilesym):
			tokenHolder = getToken(thisEnviroment);

			condition();

			if(token != dosym){
				error(18);
			} 

			tokenHolder = getToken(thisEnviroment);
			statement();
		break;
}

void condition(){

	token tokenHolder = getToken(thisEnviroment);

	switch(tokenHolder->type){

		case(oddsym):
			
			tokenHolder = getToken(thisEnviroment);
			expression();
		break;
		default:
			expression();
			if((token != eqlsym) && (token != neqsym) && (token != lessym) &&
				 (token != leqsym) && (token != gtrsym) && (token != geqsym) ){
				error(20);
			}
		tokenHolder = getToken(thisEnviroment);
		expression();			
	}

	statement();
}

void expression(){

	tokenHolder = getToken(thisEnviroment);

	while(tokenHolder == plussym || tokenHolder == minussym){
		term();
	}
}	

void term(){

	tokenHolder = getToken(thisEnviroment);
	factor();

	tokenHolder = getToken(thisEnviroment);
	while(tokenHolder == multsym || tokenHolder == slashsym){
		factor();
	}
}

void factor(){

	tokenHolder = getToken(thisEnviroment);
	
	if(tokenHolder == identsym || tokenHolder == numbersym){

		return;
	}

	else if(tokenHolder == lparentsym){

		expression();
		
		if(tokenHolder != rparentsym){
		error(22);
	}

	else{

		error();
	}

}

void error(int errorCode){

	switch(errorCode){

		case 1:
			printf("Use = instead of :=.\n");
			exit(0);
		break;
		case 2:
			printf("= must be followed by a number.\n");
			exit(0);
		break;
		case 3:
			printf("Identifier must be followed by =.\n");
			exit(0);
		break;
		case 4:
			printf("const, var, procedure must be followed by identifier.\n");
			exit(0);
		break;
		case 5:
			printf("semicolon or comma missing.\n");
			exit(0);
		break;
		case 6:
			printf("Incorrect symbol after procedure decleration.\n");
			exit(0);
		break;
		case 7:
			printf("Statement expected.\n");
			exit(0);
		break;
		case 8:
			printf("Incorrect symbol after statement part in block.\n");
			exit(0);
		break;
		case 9:
			printf("Period expected.\n");		
			exit(0);
		break;
		case 10:
			printf("semicolon between statements missing.\n");
			exit(0);
		break;
		case 11:
			printf("Undeclared identifier.\n");
			exit(0);
		break;
		case 12:
			printf("Assignment to constant or procedure is not allowed.\n");
			exit(0);
		break;
		case 13:
			printf("Assignment operator expected.\n");
			exit(0);
		break;
		case 14:
			printf("call must be folowed by an identifier.\n");
			exit(0);
		break;

		case 15:
			printf("call of a constant or variable is meaningless.\n");
			exit(0);
		break;
		case 16:
			printf("then exoected.\n");
			exit(0);
		break;
		case 17:
			printf("semicolon or } expected.\n");
			exit(0);
		break;

		case 18:
			printf("do expected.\n");
			exit(0);
		break;
		case 19:
			printf("Incorrect symbol following statement.\n");
			exit(0);
		break;
		case 20:
			printf("Relational operator expected.\n");
			exit(0);
		break;

		case 21:
			printf("Expression must no contain a procedure identi.\n");
			exit(0);
		break;
		case 22:
			printf("Right parantheses missing.\n");
			exit(0);
		break;

		case 23:
			printf("The preceding factor cannot begin with this symbol.\n");
			exit(0);
		break;
		case 24:
			printf("An expression cannot begin with this symbol.\n");
			exit(0);
		break;
		case 25:
			printf("This number is too large.\n");
			exit(0);
		break;
		case 26:
			printf("Identifier too long.\n");
			exit(0);
		break;
		case 27:
			printf("Invalid symbol.\n");
			exit(0);
		break;
	}
}

void symbolTable(enviroment *thisEnviroment, int op, int index){

	switch(op){

		case 1:

			strcopy(thisEnviroment->thisToken[currentIndexToken]->name, thisEnviroment->thisSymbolTable[thisEnviroment->currentIndexTable].name);

		break;
		case 2:
			thisEnviroment->thisSymbolTable[currentIndexTable].type = thisEnviroment->thisToken[currentIndexToken].type
			thisEnviroment->thisSymbolTable[currentIndexTable].value = thisEnviroment->thisToken[currentIndexToken].vlaue

		break;
		case 3:
		break;
		case 4:
		break;
	}

}