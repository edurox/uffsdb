/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INSERT = 258,
    INTO = 259,
    VALUES = 260,
    SELECT = 261,
    FROM = 262,
    WHERE = 263,
    EQUALS = 264,
    NEQUALS = 265,
    BIGGER = 266,
    LESS = 267,
    BEQUALS = 268,
    LEQUALS = 269,
    CREATE = 270,
    TABLE = 271,
    INTEGER = 272,
    VARCHAR = 273,
    DOUBLE = 274,
    AND = 275,
    OR = 276,
    CHAR = 277,
    PRIMARY = 278,
    KEY = 279,
    REFERENCES = 280,
    DATABASE = 281,
    DROP = 282,
    OBJECT = 283,
    NUMBER = 284,
    VALUE = 285,
    QUIT = 286,
    LIST_TABLES = 287,
    LIST_TABLE = 288,
    ALPHANUM = 289,
    CONNECT = 290,
    HELP = 291,
    LIST_DBASES = 292,
    CLEAR = 293
  };
#endif
/* Tokens.  */
#define INSERT 258
#define INTO 259
#define VALUES 260
#define SELECT 261
#define FROM 262
#define WHERE 263
#define EQUALS 264
#define NEQUALS 265
#define BIGGER 266
#define LESS 267
#define BEQUALS 268
#define LEQUALS 269
#define CREATE 270
#define TABLE 271
#define INTEGER 272
#define VARCHAR 273
#define DOUBLE 274
#define AND 275
#define OR 276
#define CHAR 277
#define PRIMARY 278
#define KEY 279
#define REFERENCES 280
#define DATABASE 281
#define DROP 282
#define OBJECT 283
#define NUMBER 284
#define VALUE 285
#define QUIT 286
#define LIST_TABLES 287
#define LIST_TABLE 288
#define ALPHANUM 289
#define CONNECT 290
#define HELP 291
#define LIST_DBASES 292
#define CLEAR 293

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 19 "yacc.y" /* yacc.c:1909  */

    int intval;
    double floatval;
    int subtok;
    char *strval;

#line 137 "y.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
