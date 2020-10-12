/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "parser.y" /* yacc.c:1909  */

  #include "ast.hpp"
  #include <iostream>
  #include <cassert>

  extern Program *g_root;
  extern FILE *yyin;

int yylex(void);
  void yyerror(const char *);

#line 56 "parser.hpp" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    times = 258,
    divide = 259,
    plus = 260,
    minus = 261,
    assign = 262,
    condIf = 263,
    condElse = 264,
    notEqualOp = 265,
    bitWiseAndOp = 266,
    bitWiseIorOp = 267,
    bitWiseEorOp = 268,
    logicalAndOp = 269,
    logicalOrOp = 270,
    lBracket = 271,
    rBracket = 272,
    lCurlyBracket = 273,
    rCurlyBracket = 274,
    plusEquals = 275,
    minusEquals = 276,
    timesEquals = 277,
    comma = 278,
    breakT = 279,
    enumT = 280,
    divEquals = 281,
    modEquals = 282,
    andEquals = 283,
    orEquals = 284,
    xorEquals = 285,
    lShiftEquals = 286,
    logicalNotOp = 287,
    rShiftEquals = 288,
    number = 289,
    identifier = 290,
    dataType = 291,
    colon = 292,
    loopWhile = 293,
    loopFor = 294,
    gt = 295,
    gte = 296,
    lt = 297,
    lte = 298,
    leftOp = 299,
    rightOp = 300,
    modulo = 301,
    ret = 302,
    equalsOp = 303,
    lSquareBracket = 304,
    rSquareBracket = 305,
    caseT = 306,
    defaultT = 307,
    condSwitch = 308,
    colonT = 309,
    continueT = 310,
    plusPlus = 311,
    minusMinus = 312
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 15 "parser.y" /* yacc.c:1909  */

  Expression *expr;
  std::string *string;
  Program *prog;

#line 132 "parser.hpp" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_HPP_INCLUDED  */
