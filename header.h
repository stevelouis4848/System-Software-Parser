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
int kind; 		
char nameHolder[10];

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
token getToken(enviroment *thisEnviroment);
void statement(enviroment *thisEnviroment, FILE *ofp);
void condition(enviroment *thisEnviroment, FILE *ofp);
void expression(enviroment *thisEnviroment, FILE *ofp);
void term(enviroment *thisEnviroment, FILE *ofp);
void factor(enviroment *thisEnviroment, FILE *ofp);
void error(int errorCode, FILE *ofp);
void symbolTablePush(int type, enviroment *thisEnviroment);
int symbolTableSearch(enviroment *thisEnviroment,char name[10]);
void emit(enviroment *thisEnviroment, int op, int register, int level, imt m)
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