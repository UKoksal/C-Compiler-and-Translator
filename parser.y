%code requires{
  #include "ast.hpp"
  #include <iostream>
  #include <cassert>

  extern Program *g_root;
  extern FILE *yyin;

int yylex(void);
  void yyerror(const char *);
}

// Represents the value associated with any kind of
// AST node.
%union{
  Expression *expr;
  std::string *string;
  Program *prog;
}

%token times divide plus minus assign condIf condElse notEqualOp bitWiseAndOp bitWiseIorOp bitWiseEorOp logicalAndOp logicalOrOp
%token lBracket rBracket lCurlyBracket rCurlyBracket  plusEquals minusEquals timesEquals
%token comma breakT enumT divEquals modEquals andEquals orEquals xorEquals lShiftEquals logicalNotOp rShiftEquals
%token number identifier dataType colon loopWhile loopFor 
%token gt gte lt lte leftOp rightOp modulo ret equalsOp lSquareBracket rSquareBracket caseT defaultT condSwitch colonT continueT plusPlus minusMinus

%type <expr> FACTOR RELATIONALEXPRESSION  SHIFTEXPRESSION ADDITIVEEXPRESSION SUBSCRIPT FUNCTIONCALL MULTIPLICATIVEEXPRESSION  UNARYMINUS
%type <prog> PROG PROGELEMENT VARIABLEDECLARATION STATEMENT STATEMENTLIST LOOP ASSIGNMENT RETURNSTATEMENT CASE ARRAYDECLARATION FUNTIONDECLARATION
%type <prog> FUNCTIONDEFINITION PARAMETERLIST  CONDITIONAL CONCRETEPARAMETERLIST ENUMERATIONSPECIFIER ENUMERATORLIST ENUMERATOR CONTINUESTATEMENT CASELIST BREAKSTATEMENT 
%type <expr> EQUALITYEXPRESSION ANDEXPRESSION EXCLUSIVEOREXPRESSION INCLUSIVEOREXPRESSION LOGICALANDEXPRESSION LOGICALOREXPRESSION 

%type <string> identifier 
%type <string> dataType
%type <string> number

%start ROOT
%nonassoc "then"
%nonassoc condElse
	



%%

ROOT : PROG {g_root = $1;}
;

PROG: PROGELEMENT {$$ = $1;std::cerr << "HELLO THIS IS THE BEGINNING\n";}
|PROGELEMENT PROG{$$ = new Program($1, $2);}
;

PROGELEMENT:VARIABLEDECLARATION colon{$$ = $1;}
| ARRAYDECLARATION colon {$$ = $1;}
| ENUMERATIONSPECIFIER colon {$$ = $1;}
| FUNTIONDECLARATION colon {$$ = $1;}
| FUNCTIONDEFINITION {$$ = $1;}
;

FUNTIONDECLARATION: dataType identifier lBracket PARAMETERLIST rBracket {$$ = new FunctionDeclaration($2[0], $4);}
;

FUNCTIONDEFINITION: dataType identifier lBracket PARAMETERLIST rBracket lCurlyBracket STATEMENTLIST rCurlyBracket {$$ = new FunctionDefinition($1[0], $2[0], $4, $7);std::cerr<< "function definition " << $2[0] << "\n";}
| dataType identifier lBracket PARAMETERLIST rBracket lCurlyBracket rCurlyBracket {$$ = new FunctionDefinition($1[0], $2[0], $4);std::cerr<< "function definition " << $2[0] << "\n";}
;

VARIABLEDECLARATION: dataType identifier {$$ = new VariableDeclaration($1[0], $2[0]);}
| dataType identifier assign LOGICALOREXPRESSION {$$ = new VariableDeclaration($1[0], $2[0], $4);}
| identifier identifier  {$$ = new VariableDeclaration($2[0]);/*enum instantiation*/};

ARRAYDECLARATION:dataType identifier lSquareBracket LOGICALOREXPRESSION rSquareBracket  {std::cerr << "array declared\n";$$ = new ArrayDeclaration($1[0], $2[0], $4);}
;

PARAMETERLIST: dataType identifier comma PARAMETERLIST {$$ = new ParameterList($1[0], $2[0], $4);} 
|dataType identifier {$$ = new ParameterList($1[0], $2[0]);}
| {$$ = new ParameterList();}
;

STATEMENTLIST: STATEMENT {$$ = new StatementList($1);}
| STATEMENT STATEMENTLIST {$$ = new StatementList($2, $1);}
;

BREAKSTATEMENT: breakT {$$ = new BreakStatement();}
;

CONTINUESTATEMENT:continueT {$$ = new ContinueStatement();};

STATEMENT: 
 LOOP {$$ = $1;} 
| VARIABLEDECLARATION colon{$$ = $1;std::cerr << "whanew1\n";}
| ARRAYDECLARATION colon{$$ = $1;std::cerr << "whanew2\n";}
| ASSIGNMENT  colon{$$ = $1;std::cerr << "whanew3\n";}
| BREAKSTATEMENT colon {$$ = $1;std::cerr << "whanew4\n";}
| CONTINUESTATEMENT colon {$$ = $1;std::cerr << "whanew5\n";}
| CONDITIONAL {$$ = $1;std::cerr << "whanew6\n";}
| ENUMERATIONSPECIFIER colon{$$ = $1;std::cerr << "whanew7\n";}
| colon {;std::cerr << "whanew8\n";} 	
| RETURNSTATEMENT {$$ = $1;std::cerr << "whanew9\n";}
| FUNCTIONCALL colon{$$ = $1;std::cerr << "wnew10\n";}
| LOGICALOREXPRESSION colon {$$ = $1;std::cerr << "whanew11\n";}
//| SCOPE {$$ = $1; std::cerr << "scope\n";}
;

/*SCOPE: lCurlyBracket STATEMENTLIST rCurlyBracket {$$ = new Scope($2);}
| lCurlyBracket rCurlyBracket {$$ = new Scope();}
;*/

ASSIGNMENT: identifier assign ASSIGNMENT {$$ = new Assignment($1[0], $3); /*std::cerr << "the identifer found is " << $1[0] << "\n";*/}
| SUBSCRIPT assign LOGICALOREXPRESSION {$$ = new Assignment($1, $3);}
| FACTOR plusEquals FACTOR {$$ = new PlusEquals ($1, $3);}
| FACTOR minusEquals FACTOR {$$ = new MinusEquals ($1, $3);}
| FACTOR timesEquals FACTOR {$$ = new TimesEquals ($1, $3);}
| FACTOR divEquals FACTOR {$$ = new DivEquals ($1, $3);}
| FACTOR modEquals FACTOR {$$ = new ModEquals ($1, $3);}
| FACTOR andEquals FACTOR {$$ = new AndEquals ($1, $3);}
| FACTOR orEquals FACTOR {$$ = new OrEquals ($1, $3);}
| FACTOR xorEquals FACTOR {$$ = new XorEquals ($1, $3);}
| FACTOR lShiftEquals FACTOR {$$ = new LShiftEquals ($1, $3);}
| FACTOR rShiftEquals FACTOR {$$ = new RShiftEquals ($1, $3);}

|LOGICALOREXPRESSION {$$ = $1;}
;

ENUMERATIONSPECIFIER: enumT identifier lCurlyBracket ENUMERATORLIST rCurlyBracket{$$ = new EnumerationSpecifier($2[0], $4);}
;

ENUMERATORLIST: ENUMERATOR {$$ = new EnumeratorList($1);}
| ENUMERATOR comma {$$ = new EnumeratorList($1);}
| ENUMERATOR comma ENUMERATORLIST {$$ = new EnumeratorList($1, $3);}
;

ENUMERATOR: identifier assign LOGICALOREXPRESSION {$$ = new Enumerator($1[0], $3);}
| identifier {$$ = new Enumerator($1[0]);}
;

FUNCTIONCALL: identifier lBracket CONCRETEPARAMETERLIST rBracket{$$ = new FunctionCall($1[0], $3); std::cerr << "functioncall with identifier "<< $1[0] << "\n";}
;

CONCRETEPARAMETERLIST: LOGICALOREXPRESSION comma CONCRETEPARAMETERLIST {$$ = new ConcreteParameterList ($1, $3);}
| LOGICALOREXPRESSION {$$ = new ConcreteParameterList ($1);}
| {$$ = new ConcreteParameterList();}
; 

RETURNSTATEMENT: ret LOGICALOREXPRESSION colon {$$ = new ReturnStatement($2);}
;

LOOP: loopWhile lBracket LOGICALOREXPRESSION rBracket STATEMENTLIST {$$ = new WhileLoop($3, $5);}
|loopWhile lBracket LOGICALOREXPRESSION rBracket lCurlyBracket STATEMENTLIST rCurlyBracket {$$ = new WhileLoop($3, $6);}
|loopWhile lBracket LOGICALOREXPRESSION rBracket lCurlyBracket rCurlyBracket {$$ = new WhileLoop($3);}
| loopFor lBracket ASSIGNMENT colon LOGICALOREXPRESSION colon ASSIGNMENT rBracket STATEMENTLIST {$$ = new ForLoop($3, $5, $7, $9);}
| loopFor lBracket ASSIGNMENT colon LOGICALOREXPRESSION colon ASSIGNMENT rBracket lCurlyBracket STATEMENTLIST rCurlyBracket {$$ = new ForLoop($3, $5, $7, $10);}
| loopFor lBracket ASSIGNMENT colon LOGICALOREXPRESSION colon ASSIGNMENT rBracket lCurlyBracket rCurlyBracket {$$ = new ForLoop($3, $5, $7);}
;

CONDITIONAL: condIf lBracket LOGICALOREXPRESSION rBracket STATEMENTLIST %prec "then" {$$ = new IfStatement($3, $5);}
| condIf lBracket LOGICALOREXPRESSION rBracket STATEMENTLIST condElse STATEMENTLIST {$$ = new IfStatement($3, $5, $7);}
| condIf lBracket LOGICALOREXPRESSION rBracket lCurlyBracket STATEMENTLIST rCurlyBracket condElse STATEMENTLIST {$$ = new IfStatement($3, $6, $9);}
| condIf lBracket LOGICALOREXPRESSION rBracket STATEMENTLIST condElse lCurlyBracket STATEMENTLIST rCurlyBracket {$$ = new IfStatement($3, $5, $8);}
| condIf lBracket LOGICALOREXPRESSION rBracket lCurlyBracket STATEMENTLIST rCurlyBracket %prec "then" {$$ = new IfStatement($3, $6);}
| condIf lBracket LOGICALOREXPRESSION rBracket lCurlyBracket STATEMENTLIST rCurlyBracket condElse lCurlyBracket STATEMENTLIST rCurlyBracket {$$ = new IfStatement($3, $6, $10);}
| condSwitch lBracket LOGICALOREXPRESSION rBracket lCurlyBracket CASELIST rCurlyBracket {$$ = new SwitchStatement($3, $6);}
;

CASELIST: CASE {$$ = new CaseList($1, false);}
| CASE CASELIST {$$ = new CaseList($2, $1);}
| STATEMENTLIST CASELIST{$$ = new CaseList($2, true);/*we accept statementlists that will never be executed but they don't get put into the tree so they are never compiled*/;}
| {new CaseList();}
;

CASE: caseT LOGICALOREXPRESSION colonT STATEMENTLIST {$$ = new CaseNode($2, $4);}
| defaultT colonT STATEMENTLIST {$$ = new CaseNode($3);}
;

SUBSCRIPT: identifier lSquareBracket LOGICALOREXPRESSION rSquareBracket {$$ = new subscriptOperator($1[0], $3);}
;

EQUALITYEXPRESSION: RELATIONALEXPRESSION {$$ = $1;}
| EQUALITYEXPRESSION equalsOp RELATIONALEXPRESSION {$$ = new equalsOperator($1, $3);}
| EQUALITYEXPRESSION notEqualOp RELATIONALEXPRESSION {$$ = new notEqualOperator($1, $3);}
;

ANDEXPRESSION: EQUALITYEXPRESSION {$$ = $1;}
| ANDEXPRESSION bitWiseAndOp EQUALITYEXPRESSION {$$ = new bitWiseAndOperator($1, $3);} 
;

EXCLUSIVEOREXPRESSION: ANDEXPRESSION {$$ = $1;}
| EXCLUSIVEOREXPRESSION bitWiseEorOp ANDEXPRESSION {$$ = new bitWiseEorOperator($1, $3);} 
;

INCLUSIVEOREXPRESSION: EXCLUSIVEOREXPRESSION {$$ = $1;}
| INCLUSIVEOREXPRESSION bitWiseIorOp EXCLUSIVEOREXPRESSION {$$ = new bitWiseIorOperator($1, $3);} 
;

LOGICALANDEXPRESSION: INCLUSIVEOREXPRESSION {$$ = $1;}
| LOGICALANDEXPRESSION logicalAndOp INCLUSIVEOREXPRESSION {$$ = new logicalAndOperator($1, $3);} 
;

LOGICALOREXPRESSION: LOGICALANDEXPRESSION {$$ = $1;}
| LOGICALOREXPRESSION logicalOrOp LOGICALANDEXPRESSION {$$ = new logicalOrOperator($1, $3);} 
;

RELATIONALEXPRESSION: SHIFTEXPRESSION {$$ = $1;}
| RELATIONALEXPRESSION lt SHIFTEXPRESSION {$$ = new ltOperator($1, $3);}
| RELATIONALEXPRESSION gt SHIFTEXPRESSION {$$ = new gtOperator($1, $3);}
| RELATIONALEXPRESSION lte SHIFTEXPRESSION {$$ = new lteOperator($1, $3);}
| RELATIONALEXPRESSION gte SHIFTEXPRESSION {$$ = new gteOperator($1, $3);}
| RELATIONALEXPRESSION equalsOp SHIFTEXPRESSION {$$ = new equalsOperator($1, $3);}
;

SHIFTEXPRESSION: ADDITIVEEXPRESSION {$$ = $1;}
| SHIFTEXPRESSION leftOp ADDITIVEEXPRESSION {$$ = new lShiftOperator($1, $3);}
| SHIFTEXPRESSION rightOp ADDITIVEEXPRESSION {$$ = new rShiftOperator($1, $3);}
;

ADDITIVEEXPRESSION: MULTIPLICATIVEEXPRESSION				{$$ = $1;}
|ADDITIVEEXPRESSION plus MULTIPLICATIVEEXPRESSION {$$ = new AddOperator($1, $3); std::cerr << "PLUSPLUSPLUSPLUS\n\n\n\n\n\n\n\n\n";}
| ADDITIVEEXPRESSION minus MULTIPLICATIVEEXPRESSION  { std::cerr << "MINUSMINUSMINUS\n\n\n\n\n\n\n\n\n";$$ = new SubOperator($1, $3); }
;

MULTIPLICATIVEEXPRESSION: FACTOR plusPlus {$$ = new PostIncrement($1);}
| FACTOR minusMinus {$$ = new PostDecrement($1);}
| plusPlus FACTOR {$$ = new PreIncrement($2);}
| minusMinus FACTOR {$$ = new PreDecrement($2);}     
|MULTIPLICATIVEEXPRESSION times FACTOR { $$ = new MulOperator($1, $3);}
| MULTIPLICATIVEEXPRESSION divide FACTOR {$$ = new DivOperator($1, $3);}
| MULTIPLICATIVEEXPRESSION modulo FACTOR {$$ = new moduloOperator($1, $3);}
| FACTOR {$$ = $1;}
;

UNARYMINUS: minus FACTOR {$$ = new NegOperator($2); std::cerr << "unary minus\n";}
| logicalNotOp FACTOR  {$$ = new NotOperator($2); std::cerr << "notoperation\n";}
;

FACTOR : number     {$$ = new Number( $1[0] ); std::cerr << "number\n"; }
| lBracket RELATIONALEXPRESSION rBracket { $$ = $2; }
| identifier {$$ = new Variable($1[0]);}
| SUBSCRIPT {$$ = $1;}
| FUNCTIONCALL {std::cerr << "found a function call factor \n";$$ = $1;}
| UNARYMINUS {$$ = $1;}
;



%%

Program *g_root; // Definition of variable (to match declaration earlier)

Program *parseAST(char* inputPath)
{
  g_root=0;
  yyin = fopen(inputPath, "r");
  yyparse();
  return g_root;
}
