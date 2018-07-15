
void emit(enviroment *thisEnviroment, int op, int reg, int level, int m){

	printf("emitn\n");

	thisEnviroment->thisVmCode[thisEnviroment->currentIndexCode].op = op;
	thisEnviroment->thisVmCode[thisEnviroment->currentIndexCode].r = reg; 
	thisEnviroment->thisVmCode[thisEnviroment->currentIndexCode].l = level;
	thisEnviroment->thisVmCode[thisEnviroment->currentIndexCode].m = m;

	thisEnviroment->currentIndexCode;
}

void symbolTablePush(int type, enviroment *thisEnviroment){

	printf("symbolTablePush type:%d\n",type);
	if(type == 1){

		printf("type 1\n");
		if(symbolTableSearch(thisEnviroment, symbolHolder.name) == -1){

			thisEnviroment->thisSymbol[thisEnviroment->currentIndexSymbol].kind = symbolHolder.kind;
			strcpy(symbolHolder.name, thisEnviroment->thisSymbol[thisEnviroment->currentIndexSymbol].name);
			thisEnviroment->thisSymbol[thisEnviroment->currentIndexSymbol].val = symbolHolder.val;
			thisEnviroment->thisSymbol[thisEnviroment->currentIndexSymbol].level = 0;
			thisEnviroment->thisSymbol[thisEnviroment->currentIndexSymbol].addr = 0;
			thisEnviroment->thisSymbol[thisEnviroment->currentIndexSymbol].mark = 0; 

			thisEnviroment->currentIndexSymbol;
		}
	}

	if(type == 2){
		printf("type 2\n");

			if(symbolTableSearch(thisEnviroment, symbolHolder.name) == -1){
				thisEnviroment->thisSymbol[thisEnviroment->currentIndexSymbol].kind = symbolHolder.kind;
				strcpy(symbolHolder.name, thisEnviroment->thisSymbol[thisEnviroment->currentIndexSymbol].name);
				thisEnviroment->thisSymbol[thisEnviroment->currentIndexSymbol].val = 0;
				thisEnviroment->thisSymbol[thisEnviroment->currentIndexSymbol].level = 0;
				thisEnviroment->thisSymbol[thisEnviroment->currentIndexSymbol].addr = thisEnviroment->numOfVariables + 4;
				thisEnviroment->thisSymbol[thisEnviroment->currentIndexSymbol].mark = 0; 

				thisEnviroment->currentIndexSymbol;
				thisEnviroment->numOfVariables++;
			}
	}
}

int symbolTableSearch(enviroment *thisEnviroment, char name[10]){

	printf("symbolTableSearch\n");
	int i; 

	for(i = 0; i < thisEnviroment->currentIndexSymbol; i++ ){

		if(strcpy(thisEnviroment->thisSymbol[i].name, name) == 0){
  
			return i;
		}
	}

	return -1;
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
	int tableSearch,input;


	if (tokenHolder.type == identsym) {
        
        tableSearch = symbolTableSearch(thisEnviromennt, tokenHolder.value);
        
        if (thisEnviroment->thisSymbol[tableSearch].kind == 1) {
            emit(thisEnviroment, LIT,thisEnviroment->currentIndexRegister++, 0, thisEnviroment->thisSymbol[tableSearch].value);
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
        
        tokenHolder = getToken(thisEnviroment);
    }

    else if (tokenHolder.type == numbersym) {
        fscanf(input, "%d", &tableSearch);
        emit(thisEnviroment, LIT,thisEnviroment->currentIndexRegister++ ,0, tableSearch);
        getToken();

	else if(tokenHolder.type == lparentsym){

		tokenHolder = getToken(thisEnviroment);
		expression(thisEnviroment, ofp);
		
		if(tokenHolder.type != rparentsym){
		error(22, ofp);
		}

		tokenHolder = getToken(thisEnviroment);
	}
	else{

		error(23, ofp);
	}

}

void term(enviroment *thisEnviroment, FILE *ofp){

	printf("term\n");

	factor(thisEnviroment, ofp);

	while(tokenHolder.type == multsym || tokenHolder.type == slashsym){

		tempToken = tokenHolder.type;
		tokenHolder = getToken(thisEnviroment);
		factor(thisEnviroment, ofp);

		if(tempToken == multsym){
			emit(thisEnviroment, MUL, 0, 0, );
		}
		else{
			emit(thisEnviroment, DIV,0,0,0);
		}
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
			//stuck
			emit(thisEnviroment, ODD,thisEnviroment->currentIndexRegister, 0, );
		break;
		default:
			expression(thisEnviroment, ofp);
			if((tokenHolder.type != eqlsym) && (tokenHolder.type != neqsym) && (tokenHolder.type != lessym) &&
				 (tokenHolder.type != leqsym) && (tokenHolder.type != gtrsym) && (tokenHolder.type != geqsym)){
				error(20, ofp);
			}
		tokenHolder = getToken(thisEnviroment);
		expression(thisEnviroment, ofp);	
		emit(thisEnviroment, );		
	}

	tokenHolder = getToken(thisEnviroment);
	statement(thisEnviroment, ofp);
}


void statement(enviroment *thisEnviroment, FILE *ofp){

	printf("statement\n");
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

			tokenHolder = getToken(thisEnviroment);
			if(tokenHolder.type != becomessym){
				error(13, ofp);
			}
			tokenHolder = getToken(thisEnviroment);
			expression(thisEnviroment, ofp);
			tempRegister = thisEnviroment->currentIndexRegister--;
			emit(thisEnviroment, STO, tempRegister ,thisEnviroment->thisSymbol[tableSearch].level, tempM);
		break;
		case(beginsym):

			tokenHolder = getToken(thisEnviroment);
			statement(thisEnviroment, ofp);

			while(tokenHolder.type == semicolonsym){
				tokenHolder = getToken(thisEnviroment);
				statement(thisEnviroment, ofp);
			}
			
			if(tokenHolder.type != endsym){
				error(17, ofp);
			}
			else if(tokenHolder == beginsym || tokenHolder == identsym){
            	error(10, ofp);
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
		case(writesym)

			tokenHolder = getToken(thisEnviroment);
			if(tokenHolder.type != identsym){

				error(4, ofp);
			}

			tableSearch = symbolTableSearch(thisEnviroment, tokenHolder.value);

			if(thisEnviroment->thisSymbol[tableSearch].kind == 1){

				emit(thisEnviroment, LIT, thisEnviroment->currentIndexRegister, thisEnviroment->thisSymbol[tableSearch].level, thisEnviroment->thisSymbol[tableSearch].value);
			}

			else if(thisEnviroment->thisSymbol[tableSearch].kind == 2){

				emit(thisEnviroment, STO, thisEnviroment->currentIndexRegister, thisEnviroment->thisSymbol[tableSearch].level,thisEnviroment->thisSymbol[tableSearch].addr);
			}
			else{

				error(11, ofp);
				emit(thisEnviroment, SIO, 0, 0, 1);
				tokenHolder = getToken(thisEnviroment);
			}
		break;
		case(readsym):

			tokenHolder = getToken(thisEnviroment);
			if(tokenHolder != identsym){
				error(4, ofp);
			}


			tableSearch = symbolTableSearch(thisEnviroment, tokenHolder.value);

			if(thisEnviroment->thisSymbol[tableSearch].kind != 2){
				error(11, ofp);
			}
			emit(thisEnviroment, SIO,thisEnviroment->currentIndexRegister ,0 , 1);
			emit(thisEnviroment, STO,thisEnviroment->currentIndexRegister ,thisEnviroment->thisSymbol[tableSearch].level,thisEnviroment->thisSymbol[tableSearch].addr);
			tokenHolder = getToken(thisEnviroment);
		break;
		default:

		   if(tokenHolder.type == periodsym){
		            error(17, ofp);
		     }
		     else if (tokenHolder.type != endsym) {
		            error(7, ofp);
		      }
	

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
				symbolHolder.val = atoi(tokenHolder.value);

				symbolTablePush(1, thisEnviroment);
				numVariables++;

			} while(tokenHolder.type == commasym);

			tokenHolder = getToken(thisEnviroment);

			if(tokenHolder.type != semicolonsym){
				error(5, ofp);
			}
		break;
		case(varsym):

			symbolHolder.kind = 2;

			do{

				tokenHolder = getToken(thisEnviroment);

				if(tokenHolder.type != identsym){
				error(4, ofp);
				}

				strcpy(tokenHolder.value,symbolHolder.name);
				symbolTablePush(2, thisEnviroment);
				numVariables++;

				tokenHolder = getToken(thisEnviroment);
			}while(tokenHolder.type == commasym);

			if(tokenHolder.type != semicolonsym){
				error(5, ofp);
			}

	}

	emit(thisEnviroment, thisEnviroment, 6, 0, dx);
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
	thisEnviroment->thisVmCode = malloc(MAX_SYMBOL_TABLE_SIZE * sizeof (instruction));
	thisEnviroment->currentIndexToken = 0;
	thisEnviroment->currentIndexSymbol = 0;
	thisEnviroment->currentIndexRegister = 4;
	thisEnviroment->currentIndexCode = 0;
	thisEnviroment->numOfVariables = 0;

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

	//halts program.
	emit(thisEnviroment, sio, 0,0,3);

	printf("code size:%d\n", thisEnviroment->currentIndexCode);

	fprintf(ofp2,"OP\tR\tL\tM\n");
	printf("OP\tR\tL\tM\n");

	for(i = 0; i < thisEnviroment->currentIndexCode; i++){

		printf("index:%d\n"i);

		fprintf(ofp2, "%d ",thisEnviroment->thisVmCode[i].op);
		fprintf(ofp2, "%d ",thisEnviroment->thisVmCode[i].r);
		fprintf(ofp2, "%d ",thisEnviroment->thisVmCode[i].l);
		fprintf(ofp2, "%d ",thisEnviroment->thisVmCode[i].m);
		
		printf("%d ",thisEnviroment->thisVmCode[i].op);
		printf("%d ",thisEnviroment->thisVmCode[i].r);
		printf("%d ",thisEnviroment->thisVmCode[i].l);
		printf("%d ",thisEnviroment->thisVmCode[i].m);
	}
	fprintf(ofp2,"\n");
	printf("\n");

	fprintf(ofp,"parsed with no error\n");
	printf("parsed with no error\n");
	fclose(ifp);	
	fclose(ofp);
	fclose(ofp2);
}