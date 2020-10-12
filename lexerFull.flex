%option noyywrap

%{
#include "lexer.hpp"
#include<iostream>
TokenValue yylval;
// This is to work around an irritating bug in Flex
// https://stackoverflow.com/questions/46213840/get-rid-of-warning-implicit-declaration-of-function-fileno-in-flex
extern "C" int fileno(FILE *stream);
%}

NONDIGIT [a-z]|[A-Z]|"_"
DIGIT [0-9]
DATATYPE "int"|"double"|"bool"|"char"|"bool"|"void"
%%



[-]?[0-9]+[/][0-9]+         {
		/*fprintf(stderr, "Fraction : %s\n", yytext);*/
		std::string text(yytext);
		int fracPos = -1;
		bool notFound = true;
		while(notFound){
			fracPos++;
			if(text[fracPos] == '/'){
				notFound = false;
			}
		}
		double numerator = std::stod(text.substr(0,fracPos));
		double denominator = std::stod(text.substr(fracPos+1, (text.size()-(fracPos+1))));
		yylval.numberValue = numerator/denominator;
		return number;
	}
[-]?[0-9]+([.][0-9]*)? {yylval.numberValue = std::stod(yytext);  return number; }

"if" {fprintf(stderr, yytext); return condIf;}
"else" {fprintf(stderr, yytext); return condElse;}
"return" {fprintf(stderr, yytext); return ret;}
"*" {return times;}
"/" {return divide;}
"+" {return plus;}
"-" {return minus;}
"(" {return lBracket;}
")" {return rBracket;}
">" {return gThan;}
"<" {return lThan;}
">=" {return gThanEqu;}
"<=" {return lThanEqu;}
"==" {return equalTo;}
"while" {return loopWhile;}
"for" {return loopFor;}
"{" {return lCurlyBracket;}
"}" {return rCurlyBracket;}
"=" {return assign;}
";" { std::cout << "Colon "; return colon;}
{DATATYPE} {std::cout << "Data type "; return dataType;}
{NONDIGIT}({DIGIT}|{NONDIGIT})*	         { 	
	yylval.wordValue = new std::string(yytext);		
	std::cout << "Identifier ";
	return identifier;
	}
%%

/* Error handler. This will get called if none of the rules match. */
void yyerror (char const *s)
{
  fprintf (stderr, "Flex Error: %s\n", s); /* s is the text that wasn't matched */
  exit(1);
}
