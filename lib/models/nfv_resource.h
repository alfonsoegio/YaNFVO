#ifndef NFV_RESOURCE_H
#define NFV_RESOURCE_H

#include <stdlib.h>
#include "nfv_assignment.h"

typedef struct nfv_resource nfv_resource;
typedef struct nfv_symtab nfv_symtab;

#define STRING_SIZE 1024

struct nfv_resource {
  int size;
  nfv_resource *parent;
  nfv_resource *sibling;
  nfv_resource *child;
  char *label;
  char *id;
  nfv_assignment_col *assignments;
  nfv_symtab *st;
};

void _indent(int level);
nfv_resource *nfv_resource_new(char *label, char *id,
			       nfv_assignment_col *assignments);
int nfv_resource_dump(nfv_resource *o, int level);

#endif
