# include <stdlib.h>
# include <stdio.h>
# include <ctype.h>
# include <string.h>

int MAX_STACK_HEIGHT = 2000;
int MAX_CODE_LENGTH = 500;
int MAX_LEXI_LEVELS = 3;
int MAX_NUM_TOKENS = 500;
int MAX_TOKEN_LENGTH = 11;
int IDENTIFIER_MAX_LENGTH = 11;
int NUMBER_MAX_LENGTH = 5;
int MAX_SYMBOL_TABLE_SIZE = 500;
int TABLE_SIZE = 34;
int error_halt = 0;
int lexicalPrint= 0;
int parserPrint = 0;
int vmPrint = 0;
char nameHolder[10];

typedef struct listyString{
							int c;
							struct listyString *next;
}listyString;

typedef enum {
			    LIT = 1, RTN, LOD, STO, CAL, INC, JMP, JPC, SIO, NEG, ADD, SUB,
			    MUL, DIV, ODD, MOD, EQL, NEQ, LSS, LEQ, GTR, GEQ
} opCodes;

char *table[] = {"0", "\0", "2", "3", "+", "-", "*", "/", "odd", "=", "!=", "<", "<=", ">", ">=",
					"(", ")", ",", ";", ".", ":=", "begin", "end", "if", "then", "while", "do",
					"call", "const", "var", "procedure", "write", "read", "else"
				};

typedef enum{
				nulsym = 1, identsym , numbersym, plussym, minussym,
				 multsym,  slashsym, oddsym,  eqlsym, neqsym,
				 lessym, leqsym, gtrsym, geqsym, lparentsym,
				 rparentsym, commasym, semicolonsym, periodsym,becomessym,
				  beginsym, endsym, ifsym, thensym,whilesym,
				  dosym, callsym, constsym, varsym,procsym,
				   writesym, readsym, elsesym
}tokenNames;


typedef struct token{

				int type;
				char value[10];
}token;

typedef struct{
				int kind; 		// const = 1, var = 2, proc = 3
				char name[10];	// name up to 11 chars
				int val; 		// number (ASCII value)
				int level; 		// L level
				int addr; 		// M address
				int mark;		// to indicate that code has been generated already for a block.
} symbol;

typedef struct instruction{
							int op; // opcode
							int r; // reg
							int l; // L
							int m; // M
						}instruction;

typedef struct enviroment{

				token *thisToken;
				symbol *thisSymbol;
				instruction *thisVmCode;
				int currentIndexToken;
				int currentIndexSymbol;
				int currentIndexRegister;
				int currentIndexCode;
				int numOfVariables;

}enviroment;

char *opCode[] = {"NULL", "LIT", "RTN", "LOD", "STO", "CAL", "INC", "JMP","JPC", "SIO",
					"NEG", "ADD", "SUB", "MUL", "DIV", "ODD","MOD", "EQL", "NEQ",
					"LSS", "LEQ", "GTR", "GEQ"};

typedef struct enviroment2{
							int pc; // pc
							int pcPrev; //previous pc
							int bp; // base pointer
							int sp; // stack pointer
							int *R;   //Register
							instruction ir; // current instruction

					}enviroment2;

token tokenHolder;
symbol symbolHolder;
void program();
void condition(enviroment *thisEnviroment, FILE *ofp);
void block(enviroment *thisEnviroment, FILE *ofp);
void getToken(enviroment *thisEnviroment);
void statement(enviroment *thisEnviroment, FILE *ofp);
void condition(enviroment *thisEnviroment, FILE *ofp);
void expression(enviroment *thisEnviroment, FILE *ofp);
void term(enviroment *thisEnviroment, FILE *ofp);
void factor(enviroment *thisEnviroment, FILE *ofp);
void error(int errorCode, FILE *ofp);
void symbolTablePush(enviroment *thisEnviroment);
int symbolTableSearch(enviroment *thisEnviroment,char name[10]);
void emit(enviroment *thisEnviroment, int op, int register, int level, int m);
/*
void scanner(char *fileName);
void encoder(listyString* inputHead, FILE *ofp, FILE *ofp2);
listyString *intEncoder(listyString *inputHead,FILE *ofp, FILE *ofp2);
listyString *wordVarEncoder(listyString *inputHead, FILE *ofp, FILE *ofp2);
listyString *symEncoder(listyString *inputHead, FILE *ofp, FILE *ofp2);
int base(int l, int base,int *stack);
void vm ();
void fetch(enviroment2 *env, instruction *irList, FILE *ofp);
void execute(enviroment2 *env,int *stack,int *halt);
void opr(enviroment2 *env, int *stack);
void printStack(int printvalue,enviroment2 *env,int sp,int bp,int* stack,int l,FILE *ofp);
*/

int main() {

	//int i;

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
			vm();
		}
	}
	printf("done\n");
	return 0;

}

listyString *symEncoder(listyString *inputHead, FILE *ofp, FILE *ofp2, FILE *ofp3){

	int i = 0;
	char *bufferSym, *nextBufferSym;;
	listyString *temporaryHead;

	temporaryHead = inputHead;

	bufferSym = malloc(2 * sizeof(char));
	nextBufferSym = malloc(2 * sizeof(char));

	bufferSym[0] = temporaryHead->c;
	bufferSym[1] = '\0';

	if(isspace(*bufferSym) != 0){

		return temporaryHead->next;
	}

	else if(temporaryHead->next != NULL && strcmp(bufferSym,":") == 0 || strcmp(bufferSym,"<") == 0
				|| strcmp(bufferSym,">") == 0 || strcmp(bufferSym,"!") == 0){

		nextBufferSym[0] = temporaryHead->next->c;
		nextBufferSym[1] = '\0';


		if(strcmp(nextBufferSym,"=") == 0){

			bufferSym[1] = nextBufferSym[0];
			temporaryHead = temporaryHead->next;
		}
	}

	else if((temporaryHead->next != NULL) && strcmp(bufferSym,"/") == 0){

		nextBufferSym[0] = temporaryHead->next->c;

		if(strcmp(nextBufferSym,"*") == 0){

			temporaryHead = temporaryHead->next;

			while(temporaryHead->next != NULL){

				bufferSym[0] = temporaryHead->next->c;
				bufferSym[1] = '\0';


				if((strcmp(bufferSym, "*") == 0) && (temporaryHead->next != NULL)){

					temporaryHead = temporaryHead->next;

					bufferSym[1] = temporaryHead->next->c;

					if(strcmp(bufferSym, "*/") == 0){

						temporaryHead = temporaryHead->next;

						return temporaryHead->next;

					}
				}
				temporaryHead = temporaryHead->next;
			}
			fprintf(ofp, "Error: Invalid symbol.");
			error_halt = 1;
			return NULL;
		}
	}

	for(i = 0; i < TABLE_SIZE; i++){

		if(strcmp(bufferSym,table[i]) == 0){

			fprintf(ofp, "%s\t\t%d\n",bufferSym, i);
			fprintf(ofp2, "%d ", i);
			fprintf(ofp3, "%d ", i);
			return temporaryHead->next;
		}
	}
	fprintf(ofp, "Error: Invalid symbol.");
	error_halt = 1;
	return NULL;
}

listyString *intEncoder(listyString *inputHead, FILE *ofp, FILE *ofp2, FILE *ofp3){

	int i, j,strLength;

	char *bufferInt;
	listyString *temporaryHead;

	if(inputHead == NULL){

		return NULL;
	}

	temporaryHead = inputHead;

	strLength = 0;

	while((isdigit(temporaryHead->c) != 0) || (isalpha(temporaryHead->c ) != 0)){


			temporaryHead = temporaryHead->next;

			strLength++;

			if(temporaryHead == NULL){
				break;
			}
	}

	if(strLength == 0){

		return NULL;
	}

	temporaryHead = inputHead;

	bufferInt = malloc(strLength * sizeof(char));

	for( i = 0; i < strLength; i++){

		bufferInt[i] = temporaryHead->c;
		temporaryHead = temporaryHead->next;
	}

	for(i = 0; i < strLength; i++){

		if (isdigit(bufferInt[i]) ==  0){

			fprintf(ofp, "Error: Invalid symbol.");
			error_halt = 1;
			return NULL;
		}
	}

	if(strLength <= NUMBER_MAX_LENGTH){

		fprintf(ofp2, "3 ");
		fprintf(ofp3, "3 ");

		for(i = 0;i < strLength; i++){

			fprintf(ofp, "%c", bufferInt[i]);
			fprintf(ofp2, "%c", bufferInt[i]);
			fprintf(ofp3, "%c", bufferInt[i]);
		}
		fprintf(ofp2, " ");
		fprintf(ofp3, " ");
		fprintf(ofp, "\t\t3\n");

		return temporaryHead;
	}

	else{

		fprintf(ofp, "Error: Invalid symbol.");
		error_halt = 1;
		return NULL;
	}

	return temporaryHead;
}

listyString *wordVarEncoder(listyString *inputHead, FILE *ofp, FILE *ofp2, FILE *ofp3){

	int i = 0, j = 0, strLength;

	char *bufferChar;
	listyString *temporaryHead;

	if(inputHead == NULL){

		return NULL;
	}

	temporaryHead = inputHead;

	strLength = 0;

	while((isdigit(temporaryHead->c) != 0) || (isalpha(temporaryHead->c ) != 0)){

			temporaryHead = temporaryHead->next;
			strLength++;

			if(temporaryHead == NULL){
				break;
			}
	}

	if(strLength == 0){

		return NULL;
	}

	bufferChar = malloc(strLength * sizeof(char));
	temporaryHead = inputHead;


	for( i = 0; i < strLength; i++){

		bufferChar[i] = temporaryHead->c;
		temporaryHead = temporaryHead->next;
	}

	if(strLength <= IDENTIFIER_MAX_LENGTH){
		for(i = 0;i < TABLE_SIZE; i++){

			if(strcmp(bufferChar,table[i]) == 0){

				fprintf(ofp, "%s\t\t%d\n", bufferChar, i);
				fprintf(ofp2, "%d ", i);
				fprintf(ofp3, "%d ", i);
				return temporaryHead;
			}
		}

		fprintf(ofp, "%s\t\t2\n", bufferChar);
		fprintf(ofp2, "2 %s ", bufferChar);
		fprintf(ofp3, "2 %s ", bufferChar);
		return temporaryHead;

	}
	else{
			fprintf(ofp, "error:Identifier too long %s", bufferChar);
			error_halt = 1;
			return NULL;
	}
}

void encoder(listyString* inputHead, FILE *ofp, FILE *ofp2, FILE *ofp3){

	int i, j;
	char *bufferChar, *prevBufferChar;
	int *bufferInt, *prevbufferInt;

	if(inputHead == NULL){

			remove("outputFile2.txt");
			return;
		}

	while(inputHead != NULL){

		if(isalpha(inputHead->c ) != 0){

			inputHead = wordVarEncoder(inputHead, ofp, ofp2, ofp3);
		}
		else if(isdigit(inputHead->c ) != 0){

			inputHead = intEncoder(inputHead, ofp, ofp2, ofp3);
		}

		else{

			inputHead = symEncoder(inputHead, ofp, ofp2, ofp3);
		}
	}
}

void scanner(char *fileName){

	FILE *ifp, *ofp, *ofp2, *ofp3;
	int buffer;
	listyString *inputHead, *newNode, *prevNode, *temporaryHead;

	inputHead = malloc(sizeof(listyString));

	ifp = fopen(fileName, "r");

	if(ifp == NULL){

		printf("Invalid file name");
		fprintf(ofp,"Invalid file name");
		exit(0);
	}

	ofp = fopen("lexicalOutput.txt","w");
	ofp2 = fopen("outputFile2.txt","w");
	ofp3 = fopen("parserInput.txt","w");

	if (ifp == NULL || ofp == NULL){

		fprintf(ofp, "Invalid file pointers");
		remove("outputFile2.txt");
		exit(0);
	}

	fprintf(ofp, "Source Program:inputLexical\n");

	if ((buffer = fgetc(ifp)) != EOF){

		inputHead->c = buffer;
		prevNode = inputHead;
		fprintf(ofp, "%c", buffer);
	}
	while((buffer = fgetc(ifp)) != EOF){

		newNode = malloc(sizeof(listyString));

		newNode->c = buffer;

		prevNode->next = newNode;
		prevNode = newNode;
		newNode = NULL;
		fprintf(ofp, "%c", buffer);
	}

	fprintf(ofp,"\n\nLexeme Table:\nlexeme\t\ttoken type\n" );

	encoder(inputHead, ofp, ofp2, ofp3);

	if(error_halt == 0){

		fclose(ofp2);

		ofp2 = fopen("outputFile2.txt","r");

		fprintf(ofp,"\nLexeme List:\n" );

		while((buffer = fgetc(ofp2)) != EOF){

				fprintf(ofp,"%c",buffer);
		}
		fprintf(ofp,"\n");

		if(lexicalPrint != 0){
			fclose(ofp);
			ofp = fopen("lexicalOutput.txt", "r");

				while((buffer = fgetc(ofp)) != EOF){

						printf("%c",buffer);
				}
		}
	}

	else{

		fclose(ifp);
		fclose(ofp);
		remove("lexicalOutput.txt");
		remove("parserInput.txt");

		ifp = fopen("inputLexical.c","r");
		ofp = fopen("lexicalOutput.txt","w");

		ifp = fopen(fileName,"r");

		fprintf(ofp, "Source Program:inputLexical.c\n");

		while((buffer = fgetc(ifp)) != EOF){

			fprintf(ofp, "%c", buffer);
		}

		fprintf(ofp,"\nError: Invalid symbol.");

		if(lexicalPrint != 0){
			fclose(ofp);
			ofp = fopen("lexicalOutput.txt", "r");

				while((buffer = fgetc(ofp)) != EOF){

						printf("%c",buffer);
				}
		}
		fclose(ifp);
		fclose(ofp);
		fclose(ofp2);
		fclose(ofp3);
		remove("parserInput.txt");
		remove("outputFile2.txt");
	exit(0);

	}

	fclose(ifp);
	fclose(ofp);
	fclose(ofp2);
	fclose(ofp3);

	remove("outputFile2.txt");
}


void emit(enviroment *thisEnviroment, int op, int reg, int level, int m){

	//printf("emit op:%d reg:%d, level:%d, m:%d\n", op, reg,level, m);

	thisEnviroment->thisVmCode[thisEnviroment->currentIndexCode].op = op;
	thisEnviroment->thisVmCode[thisEnviroment->currentIndexCode].r = reg;
	thisEnviroment->thisVmCode[thisEnviroment->currentIndexCode].l = level;
	thisEnviroment->thisVmCode[thisEnviroment->currentIndexCode].m = m;

	thisEnviroment->currentIndexCode++;
}

void symbolTablePush(enviroment *thisEnviroment){

	//printf("symbolTablePush type:%d name:%s\n",symbolHolder.kind, symbolHolder.name);
	if(symbolHolder.kind == 1){
		//printf("type 1\n");
		if(symbolTableSearch(thisEnviroment, symbolHolder.name) == -1){

            thisEnviroment->thisSymbol[thisEnviroment->currentIndexSymbol].kind = symbolHolder.kind;
			strcpy(thisEnviroment->thisSymbol[thisEnviroment->currentIndexSymbol].name, symbolHolder.name);
			thisEnviroment->thisSymbol[thisEnviroment->currentIndexSymbol].val = symbolHolder.val;
			thisEnviroment->thisSymbol[thisEnviroment->currentIndexSymbol].level = 0;
			thisEnviroment->thisSymbol[thisEnviroment->currentIndexSymbol].addr = 0;
			thisEnviroment->thisSymbol[thisEnviroment->currentIndexSymbol].mark = 0;

			thisEnviroment->currentIndexSymbol++;
		}
	}

	else if(symbolHolder.kind  == 2){
		//printf("type 2\n");

			if(symbolTableSearch(thisEnviroment, symbolHolder.name) == -1){
				thisEnviroment->thisSymbol[thisEnviroment->currentIndexSymbol].kind = symbolHolder.kind;
				strcpy(thisEnviroment->thisSymbol[thisEnviroment->currentIndexSymbol].name, symbolHolder.name);
				thisEnviroment->thisSymbol[thisEnviroment->currentIndexSymbol].val = 0;
				thisEnviroment->thisSymbol[thisEnviroment->currentIndexSymbol].level = 0;
				thisEnviroment->thisSymbol[thisEnviroment->currentIndexSymbol].addr = thisEnviroment->numOfVariables + 4;
				thisEnviroment->thisSymbol[thisEnviroment->currentIndexSymbol].mark = 0;

				thisEnviroment->currentIndexSymbol++;
				thisEnviroment->numOfVariables++;
			}
	}

	//printf("symbol table size:%d\n", thisEnviroment->currentIndexSymbol);

}

int symbolTableSearch(enviroment *thisEnviroment, char name[10]){

	//printf("symbolTableSearch\n");
	int i, index = -1;

	//printf("symbol table size:%d\n", thisEnviroment->currentIndexSymbol);

    //printf("symbol table\n");
	for(i = 0; i < thisEnviroment->currentIndexSymbol; i++ ){

    //printf("%d\t%s\n", thisEnviroment->thisSymbol[i].kind, thisEnviroment->thisSymbol[i].name);
		if(strcmp(thisEnviroment->thisSymbol[i].name, name) == 0){
            index = i;
		}
	}
	//printf("search return:%d\n", index);

	return index;
}

void error(int errorCode,FILE *ofp){

	//printf("error\n");

	switch(errorCode){

		case 0:
			printf("***** Error number 0, unknown error.\n");
			exit(0);
		case 1:
			printf("***** Error number 1, use = instead of :=.\n");
			exit(0);
		break;
		case 2:
			printf("***** Error number 2, = must be followed by a number.\n");
			exit(0);
		break;
		case 3:
			printf("***** Error number 3, identifier must be followed by =.\n");
			exit(0);
		break;
		case 4:
			printf("***** Error number 4, const, var, procedure must be followed by identifier.\n");
			exit(0);
		break;
		case 5:
			printf("***** Error number 5, semicolon or comma missing.\n");
			exit(0);
		break;
		case 6:
			printf("***** Error number 6, incorrect symbol after procedure decleration.\n");
			exit(0);
		break;
		case 7:
			printf("***** Error number 7, statement expected.\n");
			exit(0);
		break;
		case 8:
			printf("***** Error number 8, incorrect symbol after statement part in block.\n");
			exit(0);
		break;
		case 9:
			printf("***** Error number 9, period expected.\n");
			exit(0);
		break;
		case 10:
			printf("***** Error number 10, semicolon between statements missing.\n");
			exit(0);
		break;
		case 11:
			printf("***** Error number 11, undeclared identifier.\n");
			exit(0);
		break;
		case 12:
			printf("***** Error number 12, assignment to constant or procedure is not allowed.\n");
			exit(0);
		break;
		case 13:
			printf("***** Error number 13, assignment operator expected.\n");
			exit(0);
		break;
		case 14:
			printf("***** Error number 14, call must be folowed by an identifier.\n");
			exit(0);
		break;

		case 15:
			printf("***** Error number 15, call of a constant or variable is meaningless.\n");
			exit(0);
		break;
		case 16:
			printf("***** Error number 16, then exoected.\n");
			exit(0);
		break;
		case 17:
			printf("***** Error number 17, semicolon or } expected.\n");
			exit(0);
		break;

		case 18:
			printf("***** Error number 18, do expected.\n");
			exit(0);
		break;
		case 19:
			printf("***** Error number 19, incorrect symbol following statement.\n");
			exit(0);
		break;
		case 20:
			printf("***** Error number 20, relational operator expected.\n");
			exit(0);
		break;

		case 21:
			printf("***** Error number 21, expression must no contain a procedure identi.\n");
			exit(0);
		break;
		case 22:
			printf("***** Error number 22, right parantheses missing.\n");
			exit(0);
		break;

		case 23:
			printf("***** Error number 23, the preceding factor cannot begin with this symbol.\n");
			exit(0);
		break;
		case 24:
			printf("***** Error number 24, an expression cannot begin with this symbol.\n");
			exit(0);
		break;
		case 25:
			printf("***** Error number 25, this number is too large.\n");
			exit(0);
		break;
		case 26:
			printf("***** Error number 26, identifier too long.\n");
			exit(0);
		break;
		case 27:
			printf("***** Error number 27, invalid symbol.\n");
			exit(0);
		break;
	}
}

void factor(enviroment *thisEnviroment, FILE *ofp){

	//printf("factor\n");
	int tableSearch;


	if (tokenHolder.type == identsym) {

        tableSearch = symbolTableSearch(thisEnviroment, tokenHolder.value);

        if (thisEnviroment->thisSymbol[tableSearch].kind == 1) {
            emit(thisEnviroment, LIT,thisEnviroment->currentIndexRegister++, 0, thisEnviroment->thisSymbol[tableSearch].val);
        }

        else if (thisEnviroment->thisSymbol[tableSearch].kind == 2) {
            emit(thisEnviroment, LOD,thisEnviroment->currentIndexRegister++, thisEnviroment->thisSymbol[tableSearch].level, thisEnviroment->thisSymbol[tableSearch].addr);
        }

        else if (thisEnviroment->thisSymbol[tableSearch].kind == 0) {
            error(11, ofp);
        }

        else if (thisEnviroment->thisSymbol[tableSearch].kind == 3) {
            error(21, ofp);
        }

        getToken(thisEnviroment);
    }

    else if (tokenHolder.type == numbersym) {

        tableSearch = atoi(tokenHolder.value);
        emit(thisEnviroment, LIT,thisEnviroment->currentIndexRegister++ ,0, tableSearch);
        getToken(thisEnviroment);
    }

	else if(tokenHolder.type == lparentsym){

		getToken(thisEnviroment);
		expression(thisEnviroment, ofp);

		if(tokenHolder.type != rparentsym){
		error(22, ofp);
		}

		getToken(thisEnviroment);
	}
	else{

		error(23, ofp);
	}

}

void term(enviroment *thisEnviroment, FILE *ofp){

	int tempToken;

	//printf("term\n");

	factor(thisEnviroment, ofp);

	while(tokenHolder.type == multsym || tokenHolder.type == slashsym){

		tempToken = tokenHolder.type;
		getToken(thisEnviroment);
		factor(thisEnviroment, ofp);

		if(tempToken == multsym){
			emit(thisEnviroment, MUL, 0, 0, 0);
		}
		else{
			emit(thisEnviroment, DIV,0,0,0);
		}
	}
}

void expression(enviroment *thisEnviroment, FILE *ofp){
	//printf("expression\n");

	if(tokenHolder.type != plussym && tokenHolder.type != minussym){
		term(thisEnviroment, ofp);
	}
	while(tokenHolder.type == plussym || tokenHolder.type == minussym){
		getToken(thisEnviroment);
		term(thisEnviroment, ofp);
	}
}

void condition(enviroment *thisEnviroment, FILE *ofp){
	//printf("condition\n");

	switch(tokenHolder.type){

		case(oddsym):

			getToken(thisEnviroment);
			expression(thisEnviroment, ofp);
			//stuck
			emit(thisEnviroment, ODD,thisEnviroment->currentIndexRegister, 0, 0);
		break;
		default:
			expression(thisEnviroment, ofp);
			if((tokenHolder.type != eqlsym) && (tokenHolder.type != neqsym) && (tokenHolder.type != lessym) &&
				 (tokenHolder.type != leqsym) && (tokenHolder.type != gtrsym) && (tokenHolder.type != geqsym)){
				error(20, ofp);
			}
		getToken(thisEnviroment);
		expression(thisEnviroment, ofp);
		emit(thisEnviroment,0,0,0,0);
	}

	getToken(thisEnviroment);
	statement(thisEnviroment, ofp);
}

void statement(enviroment *thisEnviroment, FILE *ofp){

	//printf("statement\n");
	int tableSearch, tempM, tempRegister;

	switch(tokenHolder.type){

		case(identsym):
			tableSearch = symbolTableSearch(thisEnviroment, tokenHolder.value) ;

			if(tableSearch == -1){

				error(11, ofp);
			}
			else if (thisEnviroment->thisSymbol[tableSearch].kind != 2){
           	 error(12, ofp);
			}

			tempM = thisEnviroment->thisSymbol[tableSearch].addr;

			getToken(thisEnviroment);
			if(tokenHolder.type != becomessym){
				error(13, ofp);
			}
			getToken(thisEnviroment);
			expression(thisEnviroment, ofp);
			tempRegister = thisEnviroment->currentIndexRegister--;
			emit(thisEnviroment, STO, tempRegister ,thisEnviroment->thisSymbol[tableSearch].level, tempM);
		break;
		case(beginsym):

			getToken(thisEnviroment);
			statement(thisEnviroment, ofp);

			while(tokenHolder.type == semicolonsym){
				getToken(thisEnviroment);
				statement(thisEnviroment, ofp);
			}

			if(tokenHolder.type != endsym){
				error(17, ofp);
			}
			else if(tokenHolder.type == beginsym || tokenHolder.type == identsym){
            	error(10, ofp);
        	}
			getToken(thisEnviroment);
		break;
		case(ifsym):
			getToken(thisEnviroment);
			condition(thisEnviroment, ofp);

			getToken(thisEnviroment);
			if(tokenHolder.type != thensym){

				error(16, ofp);
			}
			getToken(thisEnviroment);
			statement(thisEnviroment, ofp);
		break;
		case(whilesym):
			getToken(thisEnviroment);
			condition(thisEnviroment, ofp);

			if(tokenHolder.type != dosym){
				error(18, ofp);
			}

			getToken(thisEnviroment);
			statement(thisEnviroment, ofp);
		break;
		case(writesym):

			getToken(thisEnviroment);
			if(tokenHolder.type != identsym){

				error(4, ofp);
			}

			tableSearch = symbolTableSearch(thisEnviroment, tokenHolder.value);

			if(thisEnviroment->thisSymbol[tableSearch].kind == 1){

				emit(thisEnviroment, LIT, thisEnviroment->currentIndexRegister, thisEnviroment->thisSymbol[tableSearch].level, thisEnviroment->thisSymbol[tableSearch].val);
			}

			else if(thisEnviroment->thisSymbol[tableSearch].kind == 2){

				emit(thisEnviroment, STO, thisEnviroment->currentIndexRegister, thisEnviroment->thisSymbol[tableSearch].level,thisEnviroment->thisSymbol[tableSearch].addr);
			}
			else{

				error(11, ofp);
				emit(thisEnviroment, SIO, 0, 0, 1);
				getToken(thisEnviroment);
			}
		break;
		case(readsym):

			getToken(thisEnviroment);
			if(tokenHolder.type != identsym){
				error(4, ofp);
			}


			tableSearch = symbolTableSearch(thisEnviroment, tokenHolder.value);

			if(thisEnviroment->thisSymbol[tableSearch].kind != 2){
				error(11, ofp);
			}
			emit(thisEnviroment, SIO,thisEnviroment->currentIndexRegister ,0 , 1);
			emit(thisEnviroment, STO,thisEnviroment->currentIndexRegister ,thisEnviroment->thisSymbol[tableSearch].level,thisEnviroment->thisSymbol[tableSearch].addr);
			getToken(thisEnviroment);
		break;
		default:

		   if(tokenHolder.type == periodsym){
		            error(17, ofp);
		     }
	     	else if (tokenHolder.type != endsym){
		            error(7, ofp);
		     }
	}

}
void block(enviroment *thisEnviroment, FILE *ofp){

	//printf("block token:%d\n",tokenHolder.type);

	switch(tokenHolder.type){

		case(constsym):

			symbolHolder.kind = 1;

			do{
				getToken(thisEnviroment);
				if(tokenHolder.type != identsym){
					error(4, ofp);
				}
				strcpy(symbolHolder.name, tokenHolder.value);
				//printf("name transfer token:%s symbol:%s\n", tokenHolder.value,symbolHolder.name);

				getToken(thisEnviroment);
				if(tokenHolder.type != eqlsym){
					error(3, ofp);
				}

				getToken(thisEnviroment);
				if(tokenHolder.type != numbersym){
					error(2, ofp);
				}
				symbolHolder.val = atoi(tokenHolder.value);

				symbolTablePush(thisEnviroment);
				thisEnviroment->numOfVariables++;

			} while(tokenHolder.type == commasym);

			getToken(thisEnviroment);

			if(tokenHolder.type != semicolonsym){
				error(5, ofp);
			}
		break;
		case(varsym):

			symbolHolder.kind = 2;

			do{

				getToken(thisEnviroment);

				if(tokenHolder.type != identsym){
				error(4, ofp);
				}

				strcpy(symbolHolder.name, tokenHolder.value);
				//printf("name transfer token:%s symbol:%s\n", tokenHolder.value,symbolHolder.name);
				symbolTablePush(thisEnviroment);
				thisEnviroment->numOfVariables++;

				getToken(thisEnviroment);
			}while(tokenHolder.type == commasym);

			if(tokenHolder.type != semicolonsym){
				error(5, ofp);
			}

	}

	emit(thisEnviroment, 6, 0, 0, 0);
	getToken(thisEnviroment);
	statement(thisEnviroment, ofp);
}

void getToken(enviroment *thisEnviroment){

	tokenHolder = thisEnviroment->thisToken[thisEnviroment->currentIndexToken++];
	//thisEnviroment->currentIndexToken++;

	//printf("getToken:\nToken:%d value:%s \n",tokenHolder.type, tokenHolder.value);
}

void program(){

	int i;
	char buffer[MAX_NUM_TOKENS];
	int buffer2;
	enviroment *thisEnviroment;

	FILE *ifp, *ofp, *ofp2;
 	ifp = fopen("parserInput.txt", "r");
 	ofp = fopen("parserOutput.txt", "w");
 	ofp2 = fopen("vmInput.txt", "w");

	thisEnviroment = malloc(sizeof(enviroment));
	thisEnviroment->thisToken = malloc(MAX_NUM_TOKENS * sizeof (token));
	thisEnviroment->thisSymbol = malloc(MAX_SYMBOL_TABLE_SIZE * sizeof (symbol));
	thisEnviroment->thisVmCode = malloc(MAX_SYMBOL_TABLE_SIZE * sizeof (instruction));
	thisEnviroment->currentIndexToken = 0;
	thisEnviroment->currentIndexSymbol = 0;
	thisEnviroment->currentIndexRegister = 4;
	thisEnviroment->currentIndexCode = 0;
	thisEnviroment->numOfVariables = 0;

	for(i = 0; fscanf(ifp, "%s", buffer) != EOF; i++){

		buffer2 = atoi(buffer);
		//printf("buffer: %d\n", buffer2);

		thisEnviroment->thisToken[i].type = buffer2;
		strcpy(thisEnviroment->thisToken[i].value,"\0");

		if(buffer2 == 2 || buffer2 == 3){

			fscanf(ifp, "%s", buffer);
			//printf("buffer: %s\n", buffer);
			strcpy(thisEnviroment->thisToken[i].value, buffer);
		}
	}

	getToken(thisEnviroment);
	block(thisEnviroment, ofp);

	if(tokenHolder.type != periodsym){

		error(9, ofp);
	}

	//halts program.
	emit(thisEnviroment, SIO, 0,0,3);

	fprintf(ofp,"parsed with no error\n");
    if(vmPrint != 0){
        printf("parsed with no error\n");
    }

	//printf("code size:%d\n", thisEnviroment->currentIndexCode);

	//fprintf(ofp2,"OP\tR\tL\tM\n");


	if(vmPrint != 0){

        printf("Parser Output/VM Input\nOP R L M\n");
	}

	for(i = 0; i < thisEnviroment->currentIndexCode; i++){

		//printf("index:%d\n", i);

		fprintf(ofp2, "%d ",thisEnviroment->thisVmCode[i].op);
		fprintf(ofp2, "%d ",thisEnviroment->thisVmCode[i].r);
		fprintf(ofp2, "%d ",thisEnviroment->thisVmCode[i].l);
		fprintf(ofp2, "%d ",thisEnviroment->thisVmCode[i].m);
		fprintf(ofp2, "\n ");

		if(vmPrint != 0){

            printf("%d ",thisEnviroment->thisVmCode[i].op);
            printf("%d ",thisEnviroment->thisVmCode[i].r);
            printf("%d ",thisEnviroment->thisVmCode[i].l);
            printf("%d ",thisEnviroment->thisVmCode[i].m);
            printf("\n");

		}
	}
	fclose(ifp);
	fclose(ofp);
	fclose(ofp2);
}
void printStack(int printValue,enviroment2 *env,int sp,int bp,int* stack,int l,FILE *ofp){
     int i;

	switch(printValue){

		case 1:
		    if(vmPrint != 0){
			printf("%d %s %d %d %d %d %d %d",env->pcPrev,opCode[env->ir.op],env->ir.r,env->ir.l,
						env->ir.m, env->pc, env->bp, env->sp);
		    }

			fprintf(ofp,"%d %s %d %d %d %d %d %d",env->pcPrev,opCode[env->ir.op],env->ir.r,env->ir.l,
						env->ir.m, env->pc, env->bp, env->sp);

			break;
		case 2:
			if (bp == 1) {
				if (l > 0) {
                    if(vmPrint != 0){
                        printf("|");
                    }
					fprintf(ofp,"|");
				}
			 }
			else {
				//Print the lesser lexical level
				printStack(2,env,bp-1, stack[bp + 2], stack, l-1,ofp);
				if(vmPrint != 0){
                    printf("|");
				}
				fprintf(ofp,"|");
			}
				//Print the stack contents - at the current level
			for (i = bp; i <= sp; i++){
                if(vmPrint != 0){
                    printf("%3d ", stack[i]);
                }
				fprintf(ofp,"%3d ", stack[i]);
			}
			break;
		case 3:
		     if(vmPrint != 0){
                printf("\tR[");
		     }
			fprintf(ofp,"\tR[");

			for(i=0;i<16;i++){
                 if(vmPrint != 0){
                    printf("%d ",env->R[i]);
                 }
				fprintf(ofp,"%d ",env->R[i]);
			}
            if(vmPrint != 0){
                printf("]\n");
            }
			fprintf(ofp,"]\n");
			break;
	}
}

int base(int l, int base,int *stack) // l stand for L in the instruction format
{
	int b1 = base;; //find base L levels down

	while (l > 0){
			b1 = stack[b1 + 1];
			l--;
	}
			return b1;
}

void opr(enviroment2 *env, int *stack){

	switch(env->ir.op){
		case 10: //NEG
			env->R[env->ir.r] = -env->R[env->ir.r];
			break;
		case 11: //ADD
			env->R[env->ir.r] = env->R[env->ir.l] + env->R[env->ir.m];
			break;
		case 12: //SUB
			env->R[env->ir.r] = env->R[env->ir.l] - env->R[env->ir.m];
			break;
		case 13: //MUL
			env->R[env->ir.r] = env->R[env->ir.l] * env->R[env->ir.m];
			break;
		case 14: //DIV
			env->R[env->ir.r] = env->R[env->ir.l] / env->R[env->ir.m];
			break;
		case 15: //ODD
			env->R[env->ir.r] = env->R[env->ir.r] % 2;
			break;
		case 16: //MOD
			env->R[env->ir.r] = env->R[env->ir.l] % env->R[env->ir.m];
			break;
		case 17: //EQL
			env->R[env->ir.r] = env->R[env->ir.l] == env->R[env->ir.m];
			break;
		case 18: //NEQ
			env->R[env->ir.r] = env->R[env->ir.l] != env->R[env->ir.m];
			break;
		case 19: //LSS
			env->R[env->ir.r] = env->R[env->ir.l] < env->R[env->ir.m];
			break;
		case 20: //LEQ
			env->R[env->ir.r] = env->R[env->ir.l] <= env->R[env->ir.m];
			break;
		case 21: //GTR
			env->R[env->ir.r] = env->R[env->ir.l] > env->R[env->ir.m];
			break;
		case 22: //GEQ
			env->R[env->ir.r] = env->R[env->ir.l] >= env->R[env->ir.m];
			break;
		default:
			printf("2 Invalid op");
		}
}

void execute(enviroment2 *env,int *stack, int *halt){

	if(env->ir.op >= 10){
		opr(env,stack);
		return;
	}

	switch (env->ir.op) {
		case 1: //LIT
			env->R[env->ir.r] = env->ir.m;
			break;
		case 2: //RTN
			env->sp = env->bp - 1;
			env->bp = stack[env->sp + 3];
			env->pc = stack[env->sp + 4];
			break;
		case 3: //LOD
			env->R[env->ir.r] = stack[base(env->ir.l, env->bp, stack) + env->ir.m];
			break;
		case 4: //STO
			stack[base(env->ir.l, env->bp, stack) + env->ir.m] = env->R[env->ir.r];
			break;
		case 5: //CAL
		    printf(" 1 Invalid op! CAL not implemented yet\n");
			break;
		case 6: //INC
			env->sp = env->sp + env->ir.m;
			break;
		case 7: //JMP
			env->pc = env->ir.m;
			break;
		case 8: //JPC
			if (env->R[env->ir.r] == 0) {
				env->pc = env->ir.m;
			}
			break;
		case 9: //SIO
			switch (env->ir.m) {
				case 1://SIO1
                        printf("%d\n", env->R[env->ir.r]);
					break;
				case 2://SIO2
					scanf("%d", &stack[env->sp]);
					break;
				case 3://SIO3
					*halt = 1;
                    if(vmPrint!=0){
                        //printf("PROGRAM HALTED\n");
                    }
					break;
				default:
				printf("Invalid m for SIO\n");
			}
			break;
		default:
			printf(" 1 Invalid op!\n");
	}
}

void fetch(enviroment2 *env, instruction *irList, FILE *ofp){
	int i =0;

	env->ir = irList[env->pc];

    if(vmPrint != 0){
        printf("%d %s %d %d %d \n",env->pc,opCode[env->ir.op],env->ir.r,env->ir.l,
					env->ir.m);
    }

	fprintf(ofp,"%d %s %d %d %d \n",env->pc,opCode[env->ir.op],env->ir.r,env->ir.l,
					env->ir.m);

	env->pcPrev = env->pc;
	env->pc++;

}

void vm (){

	instruction *irList;
	enviroment2 *env;
	int *stack,i = 0, buff[3],*halt;
	FILE *ifp, *ofp, *ofp2, *ofp3;

	irList = malloc( MAX_CODE_LENGTH * sizeof(instruction));
	env = malloc(sizeof(enviroment2));
	env->R = calloc(16,sizeof(int));
	stack = calloc(MAX_STACK_HEIGHT,sizeof(int));
	halt = malloc(sizeof(int));

	env->sp = 0;
	env->bp = 1;
	env->pc = 0;
	*halt = 0;

	ifp = fopen("vmInput.txt", "r");
	ofp = fopen("factOpPrint.txt", "w");
	ofp2 = fopen("stackTracePrint.txt", "w");
	ofp3 = fopen("factPrint.txt", "w");

	if(ifp == NULL || ofp == NULL){
		printf("Invalid file pointer");
		return;
	}

	fprintf(ofp,"Factorial Op Printout:\n");
	fprintf(ofp2,"Factorial Stack Trace:\n");
	fprintf(ofp3,"Factorial Output:\n");

	while( fscanf(ifp, "%d %d %d %d",&buff[0],
					&buff[1],&buff[2],&buff[3]) != EOF){

		irList[i].op = buff[0];
		irList[i].r = buff[1];
		irList[i].l = buff[2];
		irList[i].m = buff[3];

		i++;
	}

	i = 0;
	while (*halt != 1 ){

		if(i == 0 && vmPrint != 0){
			printf("Factorial Op Printout:\n");
			i++;
		}
		fetch(env, irList, ofp);
		execute(env, stack, halt);
		printStack(1,env,env->sp,env->bp,stack,env->ir.l,ofp2);
		printStack(2,env,env->sp,env->bp,stack,env->ir.l,ofp2);
		printStack(3,env,env->sp,env->bp,stack,env->ir.l,ofp2);
	}

	fclose(ifp);
	fclose(ofp);
	fclose(ofp2);
	fclose(ofp3);
}



