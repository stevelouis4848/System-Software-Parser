void error(int errorCode,FILE *ofp){

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

void factor(enviroment *thisEnviroment, FILE *ofp){

	token tokenHolder = getToken(thisEnviroment);
	
	if(tokenHolder.type == identsym || tokenHolder.type == numbersym){

		return;
	}

	else if(tokenHolder.type == lparentsym){

		expression(thisEnviroment, ofp);
		
		if(tokenHolder.type != rparentsym){
		error(22, ofp);
		}
	}
	else{

		error(1, ofp);
	}

}

void term(enviroment *thisEnviroment, FILE *ofp){

	token tokenHolder = getToken(thisEnviroment);
	factor(thisEnviroment, ofp);

	tokenHolder = getToken(thisEnviroment);
	while(tokenHolder.type == multsym || tokenHolder.type == slashsym){
		factor(thisEnviroment, ofp);
	}
}

void expression(enviroment *thisEnviroment, FILE *ofp){

	token tokenHolder = getToken(thisEnviroment);

	while(tokenHolder.type == plussym || tokenHolder.type == minussym){
		term(thisEnviroment, ofp);
	}
}	

void condition(enviroment *thisEnviroment, FILE *ofp){

	token tokenHolder = getToken(thisEnviroment);

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

	statement(thisEnviroment, ofp);
}


void statement(enviroment *thisEnviroment, FILE *ofp){


	token tokenHolder = getToken(thisEnviroment);

	switch(tokenHolder.type){

		case(identsym):
	
			tokenHolder = getToken(thisEnviroment);
			if(tokenHolder.type != becomessym){
				/*error(3);*/
			}
			expression(thisEnviroment, ofp);
		break;
		case(beginsym):

			
				statement(thisEnviroment, ofp);

			while(tokenHolder.type == semicolonsym){

				tokenHolder = getToken(thisEnviroment);
				statement(thisEnviroment, ofp);
			}
			tokenHolder = getToken(thisEnviroment);

			if(tokenHolder.type != endsym){

				/*error(9);*/
			}
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

	token tokenHolder = getToken(thisEnviroment);

	switch(tokenHolder.type){

		case(constsym):
			do{
				tokenHolder = getToken(thisEnviroment);
				if(tokenHolder.type != identsym){
					error(4, ofp);
				}

				tokenHolder = getToken(thisEnviroment);
				if(tokenHolder.type != eqlsym){
					error(3, ofp);
				}

				tokenHolder = getToken(thisEnviroment);
				if(tokenHolder.type != numbersym){
					error(2, ofp);
				}
				

			} while(tokenHolder.type == commasym);

			tokenHolder = getToken(thisEnviroment);

			if(tokenHolder.type != semicolonsym){
				error(5, ofp);
			}
		break;
		case(identsym):

			do{
				tokenHolder = getToken(thisEnviroment);
			}while(tokenHolder.type == commasym);

			tokenHolder = getToken(thisEnviroment);
			if(tokenHolder.type != semicolonsym){
				error(5, ofp);
			}
	}

	statement(thisEnviroment, ofp);
}

token getToken(enviroment *thisEnviroment){

	token tokenHolder = thisEnviroment->thisToken[thisEnviroment->currentIndexToken];
	thisEnviroment->currentIndexToken++;

	return tokenHolder;
}

void readFile(){

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
	thisEnviroment->currentIndexToken = 0;
	thisEnviroment->arrayLength = MAX_NUM_TOKENS;

	for(i = 0; fscanf(ifp, "%s", buffer) != EOF; i++){
		
		

		buffer2 = atoi(buffer);
		printf("buffer: %d\n", buffer2);
		
		thisEnviroment->thisToken[i].type = buffer2;

		if(buffer2 == 2 || buffer2 == 3){

			fscanf(ifp, "%s", buffer);
			printf("buffer: %s\n", buffer);
			strcpy(thisEnviroment->thisToken[i].value, buffer);
		}
	}

	block(thisEnviroment, ofp);	

	fclose(ifp);	
	fclose(ofp);
	fclose(ofp2);
}


