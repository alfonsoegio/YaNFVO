%{
#include <stdio.h>
#include "y.tab.h"
#include "../models/nfv_resource.h"
int comment_c();
int new_line();
%}

%option nounput

INTEGER [-|+]*[0-9]+
REAL -*[0-9]*\.*[0-9]+([e|E][-|+]*[0-9]*)*
TRUE "true"
FALSE "false"
VARIABLE [a-zA-Z][a-zA-Z0-9_]*
LSBRACKET \[
RSBRACKET \]
LPAREN \(
RPAREN \)
LCBRACKET \{
RCBRACKET \}
EQUAL =
SEMICOLON ;
COLON ,
WS [\t]+
CR [\n]
ANYTHING .*
COMMENT \/\*
STRING_LITERAL L?\"(\\.|[^\\"])*\"
%%

{INTEGER}  yylval.number = atoi(yytext); return INTEGER;
{REAL}     yylval.real   = atof(yytext); return REAL;

{TRUE} {
  return 1;
}

{FALSE} {
  return 0;
}

{VARIABLE} {
  strcpy(yylval.string, yytext);
  return VARIABLE;
}

{STRING_LITERAL} {
  strcpy(yylval.string, yytext);
  return(STRING_LITERAL);
}

{COMMENT}         comment_c();
{EQUAL}           return EQUAL;
{SEMICOLON}       return SEMICOLON;
{COLON}           return COLON;
{LPAREN}          return LPAREN;
{RPAREN}          return RPAREN;
{LCBRACKET}       return LCBRACKET;
{RCBRACKET}       return RCBRACKET;
{LSBRACKET}       return LSBRACKET;
{RSBRACKET}       return RSBRACKET;
{WS}              /* Ignore */
{CR}              new_line();

%%

int new_line(void) {
  extern int _line_number;
  _line_number++;
  return _line_number;
}

int comment_c() {
  char c,d;
  int finished;
  finished=0;
  while (finished==0) {
    c = input();
    while (c != '*' ) {
      d = input();
      if (d == '/') {
	finished = 1;
	return 0;
      }
    }
  }
  return 0;
}
