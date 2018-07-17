
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

		ifp = fopen(fileName,"r");
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