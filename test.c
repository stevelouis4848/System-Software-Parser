void codeGeneration(int type, enviroment *thisEnviroment){

	if(type == 0){

		if(thisEnviroment->thisSymbol[thisEnviroment->currentIndexSymbol].kind == 1){
			thisEnviroment->vmCode[thisEnviroment->currentIndexCode++] = 1;
		}
		else if(thisEnviroment->thisSymbol[thisEnviroment->currentIndexSymbol].kind == 2){

			thisEnviroment->vmCode[thisEnviroment->currentIndexCode++] = 4;
		}

		thisEnviroment->vmCode[thisEnviroment->currentIndexCode++] = thisSymbol[thisEnviroment->currentIndexSymbol].addr;
		
		thisEnviroment->vmCode[thisEnviroment->currentIndexCode++] = thisEnviroment->thisSymbol[thisEnviroment->currentIndexSymbol].level;


	]

	

}
void symbolTablePush(enviroment *thisEnviroment){

	thisEnviroment->thisSymbol[thisEnviroment->currentIndexSymbol].kind = symbolHolder.kind;
	sytcpy(symbolHolder.name, thisEnviroment->thisSymbol[thisEnviroment->currentIndexSymbol].name);
	thisEnviroment->thisSymbol[thisEnviroment->currentIndexSymbol].value = symbolHolder.value;
	thisEnviroment->thisSymbol[thisEnviroment->currentIndexSymbol].level = 0;
	thisEnviroment->thisSymbol[thisEnviroment->currentIndexSymbol].addr = thisEnviroment->currentRegister;
	thisEnviroment->thisSymbol[thisEnviroment->currentIndexSymbol].mark = 0; 

	codeGeneration(O, thisEnviroment);
	isEnviroment->currentIndexSymbol;
	thisEnviroment->currentRegister ++;
}

void symbolTableSearch(enviroment *thisEnviroment,int type, char value[10]){

}

void error(int errorCode,FILE *ofp){

	printf("error\n");

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

	printf("factor\n");

	if(tokenHolder.type == identsym || tokenHolder.type == numbersym){

		tokenHolder = getToken(thisEnviroment);
	}

	else if(tokenHolder.type == lparentsym){

		tokenHolder = getToken(thisEnviroment);
		expression(thisEnviroment, ofp);
		
		if(tokenHolder.type != rparentsym){
		error(22, ofp);
		}

		tokenHolder = getToken(thisEnviroment);
	}
	else{

		error(0, ofp);
	}

}

void term(enviroment *thisEnviroment, FILE *ofp){

	printf("term\n");

	factor(thisEnviroment, ofp);

	while(tokenHolder.type == multsym || tokenHolder.type == slashsym){
		tokenHolder = getToken(thisEnviroment);
		factor(thisEnviroment, ofp);
	}
}

void expression(enviroment *thisEnviroment, FILE *ofp){
	printf("expression\n");

	if(tokenHolder.type != plussym && tokenHolder.type != minussym){
		term(thisEnviroment, ofp);
	}
	while(tokenHolder.type == plussym || tokenHolder.type == minussym){	
		tokenHolder = getToken(thisEnviroment);
		term(thisEnviroment, ofp);		
	}
}	

void condition(enviroment *thisEnviroment, FILE *ofp){
	printf("condition\n");

	switch(tokenHolder.type){

		case(oddsym):
			
			tokenHolder = getToken(thisEnviroment);
			expression(thisEnviroment, ofp);
		break;
		default:
			expression(thisEnviroment, ofp);
			if((tokenHolder.type != eqlsym) && (tokenHolder.type != neqsym) && (tokenHolder.type != lessym) &&
				 (tokenHolder.type != leqsym) && (tokenHolder.type != gtrsym) && (tokenHolder.type != geqsym)){
				error(20, ofp);
			}
		tokenHolder = getToken(thisEnviroment);
		expression(thisEnviroment, ofp);			
	}

	tokenHolder = getToken(thisEnviroment);
	statement(thisEnviroment, ofp);
}


void statement(enviroment *thisEnviroment, FILE *ofp){

	printf("statement\n");

	switch(tokenHolder.type){

		case(identsym):
	
			tokenHolder = getToken(thisEnviroment);
			if(tokenHolder.type != becomessym){
				error(0, ofp);
			}
			tokenHolder = getToken(thisEnviroment);
			expression(thisEnviroment, ofp);
		break;
		case(beginsym):

			tokenHolder = getToken(thisEnviroment);
			statement(thisEnviroment, ofp);

			while(tokenHolder.type == semicolonsym){
				tokenHolder = getToken(thisEnviroment);
				statement(thisEnviroment, ofp);
			}
			
			if(tokenHolder.type != endsym){
				error(0, ofp);
			}
			tokenHolder = getToken(thisEnviroment);
		break;	
		case(ifsym):
			tokenHolder = getToken(thisEnviroment);
			condition(thisEnviroment, ofp);

			tokenHolder = getToken(thisEnviroment);
			if(tokenHolder.type != thensym){

				error(16, ofp);
			}
			tokenHolder = getToken(thisEnviroment);
			statement(thisEnviroment, ofp);
		break;
		case(whilesym):
			tokenHolder = getToken(thisEnviroment);
			condition(thisEnviroment, ofp);

			if(tokenHolder.type != dosym){
				error(18, ofp);
			} 

			tokenHolder = getToken(thisEnviroment);
			statement(thisEnviroment, ofp);
		break;
	}
}


void block(enviroment *thisEnviroment, FILE *ofp){

	printf("block token:%d\n",tokenHolder.type);

	switch(tokenHolder.type){

		case(constsym):

			symbolHolder.kind = 1;

			do{
				tokenHolder = getToken(thisEnviroment);
				if(tokenHolder.type != identsym){
					error(4, ofp);
				}
				strcpy(tokenHolder.value,symbolHolder.name);

				tokenHolder = getToken(thisEnviroment);
				if(tokenHolder.type != eqlsym){
					error(3, ofp);
				}

				tokenHolder = getToken(thisEnviroment);
				if(tokenHolder.type != numbersym){
					error(2, ofp);
				}
				symbolHolder.value = atoi(tokenHolder.value)

				symbolTablePush(thisEnviroment, symbolHolder);
				
			} while(tokenHolder.type == commasym);

			tokenHolder = getToken(thisEnviroment);

			if(tokenHolder.type != semicolonsym){
				error(5, ofp);
			}
		break;
		case(varsym):

			do{

				tokenHolder = getToken(thisEnviroment);

				if(tokenHolder.type != identsym){
				error(4, ofp);
				}

				tokenHolder = getToken(thisEnviroment);
			}while(tokenHolder.type == commasym);

			if(tokenHolder.type != semicolonsym){
				error(5, ofp);
			}
	}

	tokenHolder = getToken(thisEnviroment);
	statement(thisEnviroment, ofp);
}

token getToken(enviroment *thisEnviroment){

	tokenHolder = thisEnviroment->thisToken[thisEnviroment->currentIndexToken++];
	//thisEnviroment->currentIndexToken++;

	printf("getToken:\nToken:%d value:%s \n",tokenHolder.type, tokenHolder.value);

	return tokenHolder;
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
	thisEnviroment->vmCode = malloc((MAX_SYMBOL_TABLE_SIZE * 4) * sizeof (int));
	thisEnviroment->currentIndexToken = 0;
	thisEnviroment->currentIndexSymbol = 0;
	thisEnviroment->currentRegister = 4;
	thisEnviroment->currentIndexCode = 0;

	for(i = 0; fscanf(ifp, "%s", buffer) != EOF; i++){
		
		buffer2 = atoi(buffer);
		printf("buffer: %d\n", buffer2);
		
		thisEnviroment->thisToken[i].type = buffer2;
		strcpy(thisEnviroment->thisToken[i].value,"\0");

		if(buffer2 == 2 || buffer2 == 3){

			fscanf(ifp, "%s", buffer);
			printf("buffer: %s\n", buffer);
			strcpy(thisEnviroment->thisToken[i].value, buffer);
		}
	}

	tokenHolder = getToken(thisEnviroment);
	block(thisEnviroment, ofp);	

	if(tokenHolder.type != periodsym){

		error(9, ofp);
	}

	fclose(ifp);	
	fclose(ofp);
	fclose(ofp2);
}