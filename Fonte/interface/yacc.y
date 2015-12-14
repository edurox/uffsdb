%{
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "../buffend.h"
#include "parser.h"

extern char* yytext[];
extern FILE * yyin;
extern FILE* outFile_p;

int yywrap() {
    return 1;
}

%}

%union {
    int intval;
    double floatval;
    int subtok;
    char *strval;
}

%%

%token  INSERT      INTO        VALUES      SELECT      FROM    WHERE   EQUALS   NEQUALS   BIGGER   LESS   BEQUALS   LEQUALS 
        CREATE      TABLE       INTEGER     VARCHAR     DOUBLE    AND     OR
        CHAR        PRIMARY     KEY         REFERENCES  DATABASE
        DROP        OBJECT      NUMBER      VALUE       QUIT
        LIST_TABLES LIST_TABLE  ALPHANUM    CONNECT     HELP
        LIST_DBASES CLEAR;

start: insert | select | create_table | create_database | drop_table | drop_database
     | table_attr | list_tables | connection | exit_program | semicolon {GLOBAL_PARSER.consoleFlag = 1; return 0;}
     | parentesis_open | parentesis_close| help_pls | list_databases | clear
     | qualquer_coisa | /*nothing*/;

/*--------------------------------------------------*/
/**************** GENERAL FUNCTIONS *****************/
/*--------------------------------------------------*/

/* CONNECTION */
connection: CONNECT OBJECT {connect(*yytext); GLOBAL_PARSER.consoleFlag = 1; return 0;};

qualquer_coisa: OBJECT {GLOBAL_PARSER.consoleFlag = 1; GLOBAL_PARSER.noerror = 0; return 0;};

/* EXIT */
exit_program: QUIT {exit(0);};

clear: CLEAR {clear(); GLOBAL_PARSER.consoleFlag = 1; return 0;};

parentesis_open: '(' {GLOBAL_PARSER.parentesis++;};

parentesis_close: ')' {GLOBAL_PARSER.parentesis--;};

/* TABLE ATTRIBUTES */
table_attr: LIST_TABLE OBJECT {
    if(connected.conn_active) {
        printTable(yylval.strval);
        GLOBAL_PARSER.consoleFlag = 1;
    } else
        notConnected();
    return 0;
};

/* LIST TABLES */
list_tables: LIST_TABLES {
    if(connected.conn_active) {
        printTable(NULL);
        GLOBAL_PARSER.consoleFlag = 1;
    } else
        notConnected();
    return 0;
};

/* LIST DATABASES */
list_databases: LIST_DBASES {
    showDB();
    GLOBAL_PARSER.consoleFlag = 1;
    return 0;
}

/* HELP */
help_pls: HELP {help(); GLOBAL_PARSER.consoleFlag = 1; return 0;}

/*--------------------------------------------------*/
/****************** SQL STATEMENTS ******************/
/*--------------------------------------------------*/

/* INSERT */
insert: INSERT INTO {setMode(OP_INSERT);} table opt_column_list VALUES parentesis_open value_list parentesis_close semicolon {
    if (GLOBAL_PARSER.col_count == GLOBAL_PARSER.val_count || GLOBAL_DATA.columnName == NULL)
        GLOBAL_DATA.N = GLOBAL_PARSER.val_count;
    else {
        printf("ERROR: The column counter doesn't match the value counter.\n");
        GLOBAL_PARSER.noerror=0;
    }
    return 0;
};

semicolon: ';';

table: OBJECT {setObjName(yytext);};

opt_column_list: /*optional*/ | parentesis_open column_list parentesis_close;

column_list: column | column ',' column_list;

column: OBJECT {setColumnInsert(yytext);};

value_list: value | value ',' value_list;

value: VALUE {setValueInsert(yylval.strval, 'D');}
     | NUMBER {setValueInsert(yylval.strval, 'I');}
     | ALPHANUM {setValueInsert(yylval.strval, 'S');};

/* CREATE TABLE */
create_table: CREATE TABLE {setMode(OP_CREATE_TABLE);} table parentesis_open table_column_attr parentesis_close semicolon {
    GLOBAL_DATA.N = GLOBAL_PARSER.col_count;

    return 0;
};

table_column_attr: column_create type attribute | column_create type attribute ',' table_column_attr;

type: INTEGER {setColumnTypeCreate('I');}
    | VARCHAR {setColumnTypeCreate('S');} parentesis_open NUMBER parentesis_close {setColumnSizeCreate(yylval.strval);}
    | DOUBLE {setColumnTypeCreate('D');};
    | CHAR {setColumnTypeCreate('C');};

column_create: OBJECT {setColumnCreate(yytext);};

attribute: /*optional*/
         | PRIMARY KEY {setColumnPKCreate();}
         | REFERENCES table_fk '(' column_fk ')';

table_fk: OBJECT {setColumnFKTableCreate(yytext);};

column_fk: OBJECT {setColumnFKColumnCreate(yytext);};

/* DROP TABLE */
drop_table: DROP TABLE {setMode(OP_DROP_TABLE);} OBJECT {setObjName(yytext);} semicolon  {return 0;};

/* CREATE DATABASE */
create_database: CREATE DATABASE {setMode(OP_CREATE_DATABASE);} OBJECT {setObjName(yytext);} semicolon {return 0;};

/* DROP DATABASE */
drop_database: DROP DATABASE {setMode(OP_DROP_DATABASE);} OBJECT {setObjName(yytext);} semicolon {return 0;};

/* SELECT */
select: SELECT {setMode(OP_SELECT_ALL);} selecter FROM table_select wheres semicolon {
	
	
return 0;};



selecter: '*' {GLOBAL_DATA.imprimeTudo = 1;};
	| column_list {GLOBAL_DATA.imprimeTudo = 0;};

table_select: OBJECT {setObjName(yytext);};

wheres:  
	 | WHERE {GLOBAL_WHERE.where = 1;} column_where oper valueWhere andOr column_where2 oper2 valueWhere2;

valueWhere: VALUE {setValueWhere(yylval.strval, 'D');}
     | NUMBER {setValueWhere(yylval.strval, 'I');}
     | ALPHANUM {setValueWhere(yylval.strval, 'S');};

column_where: OBJECT {setColumnWhere(yylval.strval, 'S');};

oper: EQUALS {GLOBAL_WHERE.oper = 1;}
      | BIGGER {GLOBAL_WHERE.oper = 2;}
      | LESS {GLOBAL_WHERE.oper = 3;}
      | NEQUALS {GLOBAL_WHERE.oper = 4;}
      | BEQUALS {GLOBAL_WHERE.oper = 5;}
      | LEQUALS {GLOBAL_WHERE.oper = 6;};

valueWhere2: |VALUE {setValueWhere2(yylval.strval, 'D');}
     | NUMBER {setValueWhere2(yylval.strval, 'I');}
     | ALPHANUM {setValueWhere2(yylval.strval, 'S');};

column_where2: |OBJECT {setColumnWhere2(yylval.strval, 'S');};

oper2: |EQUALS {GLOBAL_WHERE.oper2 = 1; }
      | BIGGER {GLOBAL_WHERE.oper2 = 2;}
      | LESS {GLOBAL_WHERE.oper2 = 3;}
      | NEQUALS {GLOBAL_WHERE.oper2 = 4;}
      | BEQUALS {GLOBAL_WHERE.oper2 = 5;}
      | LEQUALS {GLOBAL_WHERE.oper2 = 6;};

andOr: /*vazio*/ {GLOBAL_WHERE.andOr = 0;}
	|AND {GLOBAL_WHERE.andOr = 1;}
	|OR {GLOBAL_WHERE.andOr = 2;};


/* END */
%%
