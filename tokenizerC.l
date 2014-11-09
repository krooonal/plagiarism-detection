DIGITS [0-9]
LETTERS [A-Za-z]
SPACE [ \t\n]+
%{
	#include <stdio.h>
	#define __IDEN 258
	#define __CONS 259
	#define __STR  260
	#define __KEYW 261
	#define __PUNC 262
	#define __OPER 263
	#define __LOOP 264
	#define __COND 265
	
	/*
	V -> VARDEC
	R -> RETURN
	C -> COND
	L -> LOOP
	I -> Identifier
	B -> BEGIN
	E -> END
	c -> Constant
	S -> STRING
	O -> Operator
	[ and ] -> as it is
	*/
%}

%%
	/*Match Keywords*/
"int"{SPACE} |
"void"{SPACE} | 
"char"{SPACE} | 
"long"{SPACE} |
"double"{SPACE} |
"float"{SPACE} 	{
			printf("V");//printf("VARDEC %s\n" , yytext);
			return __KEYW;
		}
"return"{SPACE}	{ 
			printf("R");//printf("RETURN %s\n" , yytext) ; 
			return __KEYW; 
		}
"if"{SPACE}? | 
"case"{SPACE} | 
"else"{SPACE} | 
"switch"{SPACE}	{
			printf("C");//printf("COND %s\n" , yytext);
			return __COND;
		}
"for" |
"while" 	{
			printf("L");//printf("LOOP %s\n" , yytext);
			return __LOOP;
		}
	/*Match Identifier*/
{LETTERS}({LETTERS}|{DIGITS})*		{ printf("I"); return __IDEN; }
	/*{LETTERS}({LETTERS}|{DIGITS})*\((.*\))?	{ printf("FUNCTION %s\n" , yytext); return __IDEN; }*/
\{					{ printf("B"); return 1; }
\}					{ printf("E"); return 1; }
\( |
\)					{/*simple braces Do nothing*/}
{DIGITS}+				{ printf("c") ; return __CONS; }
\".*\"					{ printf("S") ; return __STR; }
[-+\*\/=&\|~><^] | 
"=="					{ printf("O"); return __OPER; }
[ \n,.;]				{ /*printf("PUNC %s\n" , yytext); return __PUNC;*/ }
"#"{SPACE}?"include".*">"		{ /*library do nothing*/}
%%

int yywrap() { return 1; }

int main()
{
	while(yylex());
	return 0;
}
