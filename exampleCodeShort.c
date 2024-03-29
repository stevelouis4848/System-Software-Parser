void createTokenList() {
    //Open input file
    FILE *input = fopen("lexemetable.txt", "r");
    
    //Open output file
    FILE *output = fopen("tokenlist.txt", "w");
    char temp[14], temp2[14];
    
    //Skips over titles on page
    fscanf(input, "%s", temp);
    fscanf(input, "%s", temp);
    fscanf(input, "%s", temp);
    //Scans through entire file
    if(optionsArray[0] == 1){
        printf("\n\n ********** TOKEN LIST  ********** \n\n");
        while (strcmp(temp2, "19")) {
            fscanf(input, "%s", temp);
            fscanf(input, "%s", temp2);
            if (!strcmp(temp2, "2")) {
                fprintf(output, "%s ", temp2);
                printf( "%s ", temp2);
                fprintf(output, "%s ", temp);
                printf( "%s ", temp);
            }
            else if (!strcmp(temp2, "3")) {
                fprintf(output, "%s ", temp2);
                printf("%s ", temp2);
                fprintf(output, "%s ", temp);
                printf("%s ", temp);
            }
            else {
                fprintf(output, "%s ", temp2);
                printf("%s ", temp2);
            }
        }
    }
    else{
        while (strcmp(temp2, "19")) {
            fscanf(input, "%s", temp);
            fscanf(input, "%s", temp2);
            if (!strcmp(temp2, "2")) {
                fprintf(output, "%s ", temp2);
                fprintf(output, "%s ", temp);
            }
            else if (!strcmp(temp2, "3")) {
                fprintf(output, "%s ", temp2);
                fprintf(output, "%s ", temp);
            }
            else {
                fprintf(output, "%s ", temp2);
            }
        }
    }
    
    //Close files
    fclose(input);
    fclose(output);
}


void getToken() {
    
    fscanf(input, "%d ", &currToken);
    
    if (currToken == semicolonsym)
        curLine++;
    
}


void block() {
    
    int mCount = 4;
    int jmpCX = cx;
    emit(JMP, 0, -99);
    //Constant
    if (currToken == constsym) {
        do {
            //Scans in indent
            getToken();
            if (currToken != identsym)
                error(4);
            
            //Scans in variable name and adds it to Symbol Table
            symbolTable[sTableCount].kind = 1;
            fscanf(input, "%s", symbolTable[sTableCount].name);
            
            //Scans in equal symbol
            getToken();
            if (currToken != eqsym) {
                if (currToken == becomessym) {
                    error(1);
                }
                error(3);
            }
            
            //Scans in numbersym
            getToken();
            if (currToken != numbersym)
                error(2);
            
            //Adds the value to the symbol Table
            fscanf(input, "%d", &symbolTable[sTableCount].value);
            
            getToken();
            sTableCount++;
        } while (currToken == commasym);
        
        if (currToken != semicolonsym)
            error(5);
        
        getToken();
    }
    
    //Variable
    if (currToken == varsym) {
        do {
            getToken();
            if (currToken != identsym)
                error(4);
            
            symbolTable[sTableCount].kind = 2;
            fscanf(input, "%s", symbolTable[sTableCount].name);
            symbolTable[sTableCount].level = curLexLevel;
            symbolTable[sTableCount].addr = mCount;
            mCount++;
            
            getToken();
            sTableCount++;
        } while (currToken == commasym);
        
        if (currToken != semicolonsym)
            error(5);
        
        getToken();
    }
    
    //Procedure
    while (currToken == procsym) {
        
        getToken();
        if (currToken != identsym)
            error(4);
        
        symbolTable[sTableCount].kind = 3;
        fscanf(input, "%s", symbolTable[sTableCount].name);
        symbolTable[sTableCount].level = curLexLevel;
        symbolTable[sTableCount].addr = cx;
        sTableCount++;
        
        getToken();
        if (currToken != semicolonsym)
            error(5);
        
        getToken();
        curLexLevel++;
        block();
        curLexLevel--;
        emit(OPR, 0, OPR_RTN);
        
        if(currToken != semicolonsym)
            error(6);
        
        getToken();
    }
    
    codeList[jmpCX].m = cx;
    
    emit(INC, 0, mCount);
    
    statement();
}


void statement() {
    char temp[12];
    int result = 0;
    //Identsym
    if (currToken == identsym) {
        fscanf(input, "%s", temp);
        
        result = isInSymTable(temp);
        
        if (result == -1)
            error(11);
        else if (symbolTable[result].kind != 2)
            error(12);
        
        int tempM = symbolTable[result].addr;
        
        getToken();
        if (currToken != becomessym)
            error(13);
        
        getToken();
        expression();
        emit(STO, curLexLevel - symbolTable[result].level, tempM);
    }
    
    //Callsym
    else if (currToken == callsym) {
        getToken();
        if (currToken != identsym)
            error(14);
        
        fscanf(input, "%s", temp);
        result = isInSymTable(temp);
        emit(CAL, curLexLevel - symbolTable[result].level, symbolTable[result].addr);
        getToken();
    }
    
    //Beginsym
    else if (currToken == beginsym) {
        getToken();
        statement();
        
        while (currToken == semicolonsym) {
            getToken();
            statement();
        }
        
        if (currToken != endsym) {
            printf("\ntoken: %d\n", currToken);
            error(17);
        }
        else if(currToken == beginsym || currToken == identsym){
            error(10);
        }
        
        getToken();
    }
    
    //Ifsym
    else if (currToken == ifsym) {
        getToken();
        condition();
        
        int currCX = cx;
        emit(JPC, 0, -99);
        
        if (currToken != thensym)
            error(16);
        
        getToken();
        statement();
        
        if (currToken == elsesym) {
            int elseCX = cx;
            emit(JMP, 0, -99);
            codeList[currCX].m = cx;
            getToken();
            statement();
            codeList[elseCX].m = cx;
        }
        
        else {
            emit(JMP, 0, cx + 1);
            codeList[currCX].m = cx;
        }
    }
    
    //Whilesym
    else if (currToken == whilesym) {
        getToken();
        
        int aCX = cx;
        
        condition();
        
        int bCX = cx;
        emit(JPC, 0, -99);
        
        if (currToken != dosym)
            error(18);
        
        getToken();
        statement();
        emit(JPC, 0, aCX);
        codeList[bCX].m = cx;
    }
    
    //Writesym
    else if (currToken == writesym) {
        getToken();
        if (currToken != identsym)
            error(4);
        
        fscanf(input, "%s", temp);
        result = isInSymTable(temp);
        
        if (symbolTable[result].kind == 1)
            emit(LIT, 0, symbolTable[result].value);
        
        else if (symbolTable[result].kind == 2)
            emit(LOD, curLexLevel - symbolTable[result].level, symbolTable[result].addr);
        
        else
            error(11);
        
        emit(SIO, 0, 0);
        getToken();
    }
    
    //Readsym
    else if (currToken == readsym) {
        getToken();
        if (currToken != identsym)
            error(4);
        
        fscanf(input, "%s", temp);
        result = isInSymTable(temp);
        
        if (symbolTable[result].kind != 2)
            error(11);
        
        emit(SIO, 0, 1);
        emit(STO, curLexLevel - symbolTable[result].level, symbolTable[result].addr);
        
        getToken();
    }
    
    else{
        if(currToken == periodsym){
            error(17);
        }
        else if (currToken != endsym) {
            error(7);
        }
    }
}


void condition() {
    
    if (currToken == oddsym) {
        getToken();
        expression();
        emit(OPR, 0, OPR_ODD);
    }
    
    else {
        expression();
        
        if (currToken < 9 || currToken > 14 )
            error(20);
        
        int addOP = currToken;
        getToken();
        expression();
        emit(OPR, 0, addOP - 1);
    }
}


void expression() {
    int addOP;
    
    if(currToken != numbersym && currToken != identsym && currToken != lparentsym
       && currToken != minussym && currToken != plussym){
        error(24);
    }
    
    if (currToken == plussym || currToken == minussym) {
        addOP = currToken;
        
        getToken();
        term();
        
        if (addOP == minussym)
            emit(OPR, 0, OPR_NEG);
    }
    
    else {
        term();
    }
    
    while(currToken == plussym || currToken == minussym) {
        addOP = currToken;
        
        getToken();
        term();
        
        if (addOP == plussym)
            emit(OPR, 0, OPR_ADD);
        else
            emit(OPR, 0, OPR_SUB);
    }
}


void term() {
    int mulOP;
    
    factor();
    
    while (currToken == multsym || currToken == slashsym) {
        mulOP = currToken;
        
        getToken();
        factor();
        
        if(mulOP == multsym)
            emit(OPR, 0, OPR_MUL);
        else
            emit(OPR, 0, OPR_DIV);
    }
}


void factor() {
    int result;
    char tempName[12];
    
    if (currToken == identsym) {
        fscanf(input, "%s", tempName);
        result = isInSymTable(tempName);
        
        if (symbolTable[result].kind == 1) {
            emit(LIT, 0, symbolTable[result].value);
        }
        
        else if (symbolTable[result].kind == 2) {
            emit(LOD, curLexLevel - symbolTable[result].level, symbolTable[result].addr);
        }
        
        else if (symbolTable[result].kind == 0) {
            error(11);
        }
        
        else if (symbolTable[result].kind == 3) {
            error(21);
        }
        
        getToken();
    }
    
    else if (currToken == numbersym) {
        fscanf(input, "%d", &result);
        emit(LIT, 0, result);
        getToken();
    }
    
    else if (currToken == lparentsym) {
        getToken();
        expression();
        
        if (currToken != rparentsym)
            error(22);
        
        getToken();
    }
    
    else {
        error(23);
    }
}


int isInSymTable(char temp[12] ) {
    int i;
    for (i = 0; i < sTableCount; i++) {
        if (strcmp(temp, symbolTable[i].name) == 0) {
            return i;
        }
    }
    return -1;
}


void error(int errNumber){
    
    printf("Error Code %d on line %d: ", errNumber, curLine);
    switch(errNumber){
        case 1:
            printf("Use = instead of :=\n");
            break;
        case 2:
            printf("= must be followed by a number\n");
            break;
        case 3:
            printf("Identifier must be folowed by :=\n");
            break;
        case 4:
            printf("Const,Var,Procedure, must be followed by identifier\n");
            break;
        case 5:
            printf("Semicolon or comma missing.\n");
            break;
        case 6:
            printf("Incorrect symbol after procedure declaration.\n");
            break;
        case 7:
            printf("Statement Expected.\n");
            break;
        case 8:
            printf("Incorrect symbol after statement part in block.\n");
            break;
        case 9:
            printf("Period expected.\n");
            break;
        case 10:
            printf("Semicolon between statements missing.\n");
            break;
        case 11:
            printf("Undeclared Identifier\n");
            break;
        case 12:
            printf("Assignment to constant or procedure is not allowed.\n");
            break;
        case 13:
            printf("Assignment operator expected\n");
            break;
        case 14:
            printf("Call must be followed by an identifier.\n");
            break;
            // case 15:
            //     printf("Call of a constant or variable is meaningless.\n");
            //     break;
        case 16:
            printf("then expcted.\n");
            break;
        case 17:
            printf("Semicolon or } expected.\n");
            break;
        case 18:
            printf("do expected.\n");
            break;
            // case 19:
            //     printf("Incorrect symbol following statement.\n");
            //     break;
        case 20:
            printf("Relational operator expected.\n");
            break;
        case 21:
            printf("Expression must not contain a procedure identifier.\n");
            break;
        case 22:
            printf("Right Parenthesis is missing.\n");
            break;
        case 23:
            printf("The preceding factor cannot begin with this symbol.\n");
            break;
        case 24:
            printf("An expression canot begin with this symbol.\n");
            break;
        case 25:
            printf("This number is too large.\n");
            break;
        default:
            printf("Error. Not a valid code Error value.\n");
            break;
    }
    exit(errNumber);
}


void emit(int op, int l, int m) {
    if (cx > MAX_CODE_SIZE) {
        error(25);
    } else {
        codeList[cx].op = op; // opcode
        codeList[cx].l = l; // lexicographical level
        codeList[cx].m = m; // modifier
        cx++;
    }
}


void printCode() {
    FILE *mcode = fopen("mcode.txt", "w");
    int i;
    if(optionsArray[2] == 1){
        printf("\n\n ********** MCODE TEXT **********\n\n");
        for (i = 0; i < cx; i++) {
            fprintf(mcode, "%d %d %d\n", codeList[i].op, codeList[i].l, codeList[i].m);
            printf("%d %d %d\n", codeList[i].op, codeList[i].l, codeList[i].m);
            
        }
    }
    else{
        for (i = 0; i < cx; i++) {
            fprintf(mcode, "%d %d %d\n", codeList[i].op, codeList[i].l, codeList[i].m);
        }
    }
    fclose(mcode);
}

void printSymbolTable(){
    FILE *symTable = fopen("symboltable.txt", "w");
    int i;
    if(optionsArray[1] == 1){
        printf("\n\n\n ********** SYMBOL TABLE **********\n\n");
        fprintf(symTable,"Name \t Type \t Level \t Value\n");
        printf("Name \t Type \t Level \t Value\n");
    for(i = 0; i < sTableCount; i++){
        char type[6] = "";
        if(symbolTable[i].kind == 1){
            strcpy(type, "const");
            fprintf(symTable,"%s \t %s \t %d \t %d\n", symbolTable[i].name, type, symbolTable[i].level, symbolTable[i].value);
            printf("%s \t %s \t %d \t %d\n", symbolTable[i].name, type, symbolTable[i].level, symbolTable[i].value);
        }
        else if(symbolTable[i].kind == 2){
            strcpy(type, "var");
            fprintf(symTable,"%s \t %s \t %d \t %d\n", symbolTable[i].name, type, symbolTable[i].level, symbolTable[i].addr);
            printf("%s \t %s \t %d \t %d\n", symbolTable[i].name, type, symbolTable[i].level, symbolTable[i].addr);
        }
        else if(symbolTable[i].kind == 3){
            strcpy(type, "proc");
            fprintf(symTable,"%s \t %s \t %d \t %d\n", symbolTable[i].name, type, symbolTable[i].level, symbolTable[i].addr);
            printf("%s \t %s \t %d \t %d\n", symbolTable[i].name, type, symbolTable[i].level, symbolTable[i].addr);
        }
        
    }
    }
    else{
    fprintf(symTable,"Name \t Type \t Level \t Value\n");
            for(i = 0; i < sTableCount; i++){
                char type[6] = "";
                if(symbolTable[i].kind == 1){
                    strcpy(type, "const");
                    fprintf(symTable,"%s \t %s \t %d \t %d\n", symbolTable[i].name, type, symbolTable[i].level, symbolTable[i].value);
                }
                else if(symbolTable[i].kind == 2){
                    strcpy(type, "var");
                    fprintf(symTable,"%s \t %s \t %d \t %d\n", symbolTable[i].name, type, symbolTable[i].level, symbolTable[i].addr);
                }
                else if(symbolTable[i].kind == 3){
                    strcpy(type, "proc");
                    fprintf(symTable,"%s \t %s \t %d \t %d\n", symbolTable[i].name, type, symbolTable[i].level, symbolTable[i].addr);
                }
                
               }
        }
}



// End of Assignment 4