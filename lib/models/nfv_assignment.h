#ifndef NFV_ASSIGNMENT_H
#define NFV_ASSIGNMENT_H

#include <stdlib.h>

typedef struct nfv_assignment nfv_assignment;
typedef struct nfv_assignment_col nfv_assignment_col;

struct nfv_assignment {
  int int_value;
  char *variable;
  char *literal_value;
  char **array_value;
  int array_size;
};

struct nfv_assignment_col {
  nfv_assignment **assignments;
  int size;
};

nfv_assignment_col *nfv_assignment_col_push(nfv_assignment_col *o, nfv_assignment *next);
nfv_assignment_col *nfv_assignment_col_new(nfv_assignment *first);
nfv_assignment *nfv_assignment_newArray(char *variable, char **strings, int nstrings);
nfv_assignment *nfv_assignment_newInt(char *variable, int value);
nfv_assignment *nfv_assignment_newLiteral(char *variable, char *value);
int nfv_assignment_free(nfv_assignment *o);

#endif
