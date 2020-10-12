%option noyywrap

%{
#include "parser.hpp"
#include<iostream>
#include <string.h>
// This is to work around an irritating bug in Flex
// https://stackoverflow.com/questions/46213840/get-rid-of-warning-implicit-declaration-of-function-fileno-in-flex
extern "C" int fileno(FILE *stream);
%}

NONDIGIT [a-z]|[A-Z]|"_"
DIGIT [0-9]
DATATYPE "int"|"double"|"bool"|"char"|"bool"|"void"|"unsigned"|"float"
%%



[0-9]+([.][0-9]*[f]?)? {yylval.string = new std::string(yytext);  return number; }

"*" {return times;}
"/" {return divide;}
"+" {return plus;}
"-" {std::cerr << "Lexer found a minus\n";return minus;}
"(" {return lBracket;}
")" {return rBracket;}
"{" {return lCurlyBracket;}
"}" {return rCurlyBracket;}
"while" {return loopWhile;}
"for" {return loopFor;}
";" { std::cout << "Colon "; return colon;}
"," {return comma;}
"=" {return assign;}
"if" {return condIf;}
"else" {return condElse;}
"<" 	{return lt;}
"<="	{return lte;}
">"	{return gt;}


"+="    {return plusEquals;}
"-="    {return minusEquals;}
"*="    {return timesEquals;}
"/=" 	{return divEquals;}
"%="	{return modEquals;}
"&=" 	{return andEquals;}
"|=" 	{return orEquals;}
"^="	{return xorEquals;}
"<<="	{return lShiftEquals;}
">>=" 	{return rShiftEquals;}

"!" {return logicalNotOp;}
">="	{return gte;}
"<<" {return leftOp;}
">>" {return rightOp;}
"%" {return modulo;}
"==" {return equalsOp;}
"!=" {return notEqualOp;}
"return" {return ret;}
"[" {return lSquareBracket;}
"]" {return rSquareBracket;}
"default" {return defaultT;}
"case" {return caseT;}
"break" {return breakT;}
"continue" {return continueT;}
"enum" {return enumT;}
":" {return colonT;}
"++" {return plusPlus;}
"--" {return minusMinus;}
"&" {return bitWiseAndOp;}
"|" {return bitWiseIorOp;}
"^" {return bitWiseEorOp;}
"&&" {return logicalAndOp;}
"||" {return logicalOrOp;}
"or" {return logicalOrOp;}
"switch" {return condSwitch;}
{DATATYPE} {yylval.string = new std::string(yytext); std::cerr << "datatype\n";return dataType; }
{NONDIGIT}({DIGIT}|{NONDIGIT})*	         { 
	yylval.string = new std::string(yytext);
	if(!strcmp(yytext, "int") || !strcmp(yytext, "double")|| !strcmp(yytext, "float")|| !strcmp(yytext, "float")|| !strcmp(yytext, "float")){
	std::cout << "type found in lexer: " << yytext << "\n";
		return dataType;
	}	
	std::cout << "identifier found in lexer: " << yytext << "\n";
	return identifier;
	
	}

. {}
%%

/* Error handler. This will get called if none of the rules match. */
void yyerror (char const *s)
{
  fprintf (stderr, "Flex Error: %s\n", s); /* s is the text that wasn't matched */
  exit(1);
}
