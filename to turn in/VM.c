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