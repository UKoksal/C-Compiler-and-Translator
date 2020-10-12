#ifndef lexer_hpp
#define lexer_hpp

#include <string>
enum tokenType{
    None   = 0, // This indicates there are no more tokens
    identifier = 1, // token codes must be positive
    number = 2,
    dataType = 3,//may need to have different datatypes
    times = 258,
    divide = 259,
    plus = 260,
    minus = 261,
    lBracket = 263,
    rBracket = 264,
    gThan = 265,
    lThan = 266,
    gThanEqu = 267,
    lThanEqu = 268,
    condIf = 269,
    condElse = 270,
    ret = 271,
    loopWhile = 272,
    loopFor = 273,
    lCurlyBracket = 274,
    rCurlyBracket = 275,
    assign = 276,
    equalTo = 277,
    colon = 278
    
};

union TokenValue{
    double numberValue;
    std::string *wordValue;
};

// This is a global variable used to move the
// attribute value from the lexer back to the
// main program.
// By convention it is called yylval, as that is
// the name that will be automatically generated
// by Bison (see next lab).
extern TokenValue yylval;

// This is the lexer function defined by flex. Each
// time it is called, a token type value will be
// returned.
extern int yylex();

#endif
