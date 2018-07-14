int MAX_STACK_HEIGHT = 2000;
int MAX_CODE_LENGTH = 500;
int MAX_LEXI_LEVELS = 3;
int MAX_NUM_TOKENS = 500;
int MAX_TOKEN_LENGTH = 11;
int IDENTIFIER_MAX_LENGTH = 11;
int NUMBER_MAX_LENGTH = 5;
int TABLE_SIZE = 34;
int error_halt = 0;

typedef struct listyString{
							int c;
							struct listyString *next;						
}listyString;

char *table[] = {"0", "\0", "2", "3", "+", "-", "*", "/", "odd", "=", "!=", "<", "<=", ">", ">=",
					"(", ")", ",", ";", ".", ":=", "begin", "end", "if", "then", "while", "do",
					"call", "const", "var", "procedure", "write", "read", "else"
				};

typedef enum{
				nulsym = 1, identsym , numbersym, plussym, minussym,
				 multsym,  slashsym, oddsym,  eqlsym, neqsym, 
				 lessym, leqsym, gtrsym, geqsym, lparentsym, 
				 rparentsym, commasym, semicolonsym, periodsym, 
				 becomessym, beginsym, endsym, ifsym, thensym,
				  whilesym, dosym, callsym, constsym, varsym, 
				  procsym, writesym, readsym, elsesym
}tokenNames;


typedef struct token{

				int type;
				char value[11];
}token;

typedef struct enviroment{

				token *thisToken;
				int currentIndexToken;
				int arrayLength;
}enviroment;

token tokenHolder;
				
				
char *opCode[] = {"NULL", "LIT", "RTN", "LOD", "STO", "CAL", "INC", "JMP","JPC", "SIO",
					"NEG", "ADD", "SUB", "MUL", "DIV", "ODD","MOD", "EQL", "NEQ",
					"LSS", "LEQ", "GTR", "GEQ"};

typedef struct instruction{
							int op; // opcode
							int r; // reg
							int l; // L
							int m; // M
						}instruction;

typedef struct enviroment2{
							int pc; // pc
							int pcPrev; //previous pc
							int bp; // base pointer
							int sp; // stack pointer
							int *R;   //Register
							instruction ir; // current instruction
							
					}enviroment2;
void program();
void condition(enviroment *thisEnviroment, FILE *ofp);
void block(enviroment *thisEnviroment, FILE *ofp);
token getToken(enviroment *thisEnviroment);
void statement(enviroment *thisEnviroment, FILE *ofp);
void condition(enviroment *thisEnviroment, FILE *ofp);
void expression(enviroment *thisEnviroment, FILE *ofp);
void term(enviroment *thisEnviroment, FILE *ofp);
void factor(enviroment *thisEnviroment, FILE *ofp);
void error(int errorCode, FILE *ofp);
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