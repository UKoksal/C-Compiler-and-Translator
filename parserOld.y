%code requires{
  #include "ast.hpp"
  #include <iostream>
  #include <cassert>

  extern const Program *g_root;
  extern FILE *yyin;

int yylex(void);
  void yyerror(const char *);
}

// Represents the value associated with any kind of
// AST node.
%union{
  const Expression *expr;
  double number;
  std::string *string;
  const Program *prog;
}

%token times divide plus minus assign condIf condElse
%token lBracket rBracket lCurlyBracket rCurlyBracket
%token comma
%token number identifier dataType colon loopWhile
%token gt gte lt lte leftOp rightOp modulo ret

%type <expr> FACTOR RELATIONALEXPRESSION  SHIFTEXPRESSION ADDITIVEEXPRESSION MULTIPLICATIVEEXPRESSION 
%type <prog> PROG PROGELEMENT VARIABLEDECLARATION STATEMENT STATEMENTLIST LOOP RETURNSTATEMENT ASSIGNMENT
%type <prog> FUNCTIONDECLARATION FUNCTIONDEFINITION DECLARATIONLIST  CONDITIONAL
%type <number> number
%type <string> identifier

%start ROOT
%nonassoc "then"
%nonassoc condElse




%%

ROOT : PROG { g_root = $1;}
;

PROG: PROGELEMENT {$$ = $1;}
|PROGELEMENT PROG{$$ = new Program($1, $2);}
;

PROGELEMENT:  {std::cout << "END OF PROGRAM\n";}
|VARIABLEDECLARATION  {$$ = $1;}
| FUNCTIONDECLARATION {$$ = $1;}
| FUNCTIONDEFINITION  {$$ = $1;}
;

FUNCTIONDEFINITION: dataType identifier lBracket DECLARATIONLIST rBracket lCurlyBracket STATEMENTLIST rCurlyBracket {$$ = new FunctionDefinition($2[0], $4, $7);}
;

FUNCTIONDECLARATION: dataType identifier lBracket DECLARATIONLIST rBracket colon {$$ = new FunctionDeclaration($2[0], $4);}
;

VARIABLEDECLARATION: dataType identifier colon {$$ = new VariableDeclaration($2[0]);}
;

DECLARATIONLIST: dataType identifier comma DECLARATIONLIST {$$ = new DeclarationList($2[0], $4);} 
|dataType identifier {$$ = new DeclarationList($2[0]);}
| {$$ = new DeclarationList("");/*decided that we cannot have empty string as variable name when we accept nothing in the parameter list e.g. in a function with no parameters*/}
;

STATEMENTLIST: STATEMENT {$$ = new StatementList($1);}
| STATEMENT STATEMENTLIST {$$ = new StatementList($2, $1);}
;


STATEMENT: 
 LOOP {$$ = $1;} 
| ASSIGNMENT {$$ = $1;}
| CONDITIONAL {$$ = $1;}
| colon {;}
| VARIABLEDECLARATION {$$ = $1;}
| RELATIONALEXPRESSION {$$ = $1;}
| RETURNSTATEMENT {$$ = $1;}
;


ASSIGNMENT: identifier assign RELATIONALEXPRESSION colon {$$ = new Assignment($3, $1[0]);}
;

RETURNSTATEMENT: ret RELATIONALEXPRESSION colon {$$ = new ReturnStatement($2);}
;

LOOP: loopWhile lBracket RELATIONALEXPRESSION rBracket STATEMENTLIST {$$ = new WhileLoop($3, $5);}
|loopWhile lBracket RELATIONALEXPRESSION rBracket lCurlyBracket STATEMENTLIST rCurlyBracket {$$ = new WhileLoop($3, $6);}
;

CONDITIONAL: condIf lBracket RELATIONALEXPRESSION rBracket STATEMENTLIST %prec "then" {$$ = new IfStatement($3, $5);}
| condIf lBracket RELATIONALEXPRESSION rBracket STATEMENTLIST condElse STATEMENTLIST {$$ = new IfStatement($3, $5, $7);}
| condIf lBracket RELATIONALEXPRESSION rBracket lCurlyBracket STATEMENTLIST rCurlyBracket %prec "then" {$$ = new IfStatement($3, $6);}
| condIf lBracket RELATIONALEXPRESSION rBracket lCurlyBracket STATEMENTLIST rCurlyBracket condElse lCurlyBracket STATEMENTLIST rCurlyBracket {$$ = new IfStatement($3, $6, $10);}
;

RELATIONALEXPRESSION: SHIFTEXPRESSION {$$ = $1;}
| RELATIONALEXPRESSION lt SHIFTEXPRESSION {$$ = new ltOperator($1, $3);}
| RELATIONALEXPRESSION gt SHIFTEXPRESSION {$$ = new gtOperator($1, $3);}
| RELATIONALEXPRESSION lte SHIFTEXPRESSION {$$ = new lteOperator($1, $3);}
| RELATIONALEXPRESSION gte SHIFTEXPRESSION {$$ = new gteOperator($1, $3);}
;

SHIFTEXPRESSION: ADDITIVEEXPRESSION {$$ = $1;}
| SHIFTEXPRESSION leftOp ADDITIVEEXPRESSION {$$ = new lShiftOperator($1, $3);}
| SHIFTEXPRESSION rightOp ADDITIVEEXPRESSION {$$ = new rShiftOperator($1, $3);}
;

ADDITIVEEXPRESSION: MULTIPLICATIVEEXPRESSION				{$$ = $1;}
|ADDITIVEEXPRESSION plus MULTIPLICATIVEEXPRESSION { $$ = new AddOperator($1, $3); }
| ADDITIVEEXPRESSION minus MULTIPLICATIVEEXPRESSION  { $$ = new SubOperator($1, $3); }
;

MULTIPLICATIVEEXPRESSION: MULTIPLICATIVEEXPRESSION times FACTOR { $$ = new MulOperator($1, $3);}
| MULTIPLICATIVEEXPRESSION divide FACTOR {$$ = new DivOperator($1, $3);}
| MULTIPLICATIVEEXPRESSION modulo FACTOR {$$ = new moduloOperator($1, $3);}
| FACTOR {$$ = $1;}
;


FACTOR : number     {$$ = new Number( $1 ); }
| lBracket RELATIONALEXPRESSION rBracket { $$ = $2; }
| identifier {$$ = new Variable($1[0]);}
;



%%

const Program *g_root; // Definition of variable (to match declaration earlier)

const Program *parseAST(char* inputPath)
{
  g_root=0;
  yyin = fopen(inputPath, "r");
  yyparse();
  return g_root;
}
