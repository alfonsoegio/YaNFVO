%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "../models/nfv_resource.h"
#include "../models/nfv_assignment.h"

  int yylex();
  int yyparse();
  extern FILE *yyin;
  extern FILE *yyout;
  int _line_number = 1;
  nfv_resource *_root;
  void yyerror ( const char *str ) {
    fprintf(stderr,"\nError: %s while processing line %d\n\n",str,_line_number);
  }

  int yywrap( void ) {
    return 1;
  }

  nfv_resource *nfv_parse(int argc,char *argv[]) {
    if ( (yyin = fopen(argv[1],"r")) == NULL ) {
      printf("\nFile %s not found\n\n",argv[1]);
      return 0;
    }
    yyout = fopen("/dev/null","w");
    yyparse();
    fclose(yyout);
    fclose(yyin);
    return _root;
  }
%}

%union {
  int number;
  double real;
  char string[1024];
  struct nfv_resource *nfv_resource;
  struct nfv_assignment *nfv_assignment;
  struct nfv_assignment_col *nfv_assignments;
}

%token <number> TRUE
%token <number> FALSE

%token <number> INTEGER
%token <real>   REAL
%token <string> VARIABLE
%token <string> STRING_LITERAL

%token MINUS
%token GT
%token EQUAL
%token LPAREN
%token RPAREN
%token SEMICOLON
%token LCBRACKET
%token RCBRACKET
%token LSBRACKET
%token RSBRACKET
%token COLON
%type <nfv_resource> resource
%type <nfv_resource> resources
%type <nfv_assignment> assignment
%type <nfv_assignments> assignments

%%
resources: /* EMPTY */
{
  $$ = NULL;
}
|
resource
{
  _root = $1;
  $$ = $1;
}
|
resources resource
{
  if ( $1 != NULL ) {
    $2->sibling = $1;
  }
  $$ = $2;
}

resource: VARIABLE LPAREN STRING_LITERAL RPAREN LCBRACKET assignments resources RCBRACKET
{
  $$ = nfv_resource_new($1, $3, $6);
  $$->child = $7;
}
|
VARIABLE LPAREN STRING_LITERAL RPAREN LCBRACKET resources RCBRACKET
{
  $$ = nfv_resource_new($1, $3, NULL);
  $$->child = $6;
}

assignments: assignment
{
  $$ = nfv_assignment_col_new($1);
}
|
assignments assignment
{
  $$ = nfv_assignment_col_push($1, $2);
}

assignment: VARIABLE EQUAL INTEGER SEMICOLON
{
  $$ = nfv_assignment_newInt($1, $3);
}
|
VARIABLE EQUAL STRING_LITERAL SEMICOLON
{
  $$ = nfv_assignment_newLiteral($1, $3);
}
|
VARIABLE EQUAL VARIABLE MINUS GT VARIABLE LPAREN RPAREN SEMICOLON
{
  $$ = nfv_assignment_newReference($1, $3, $6);
}

%%
