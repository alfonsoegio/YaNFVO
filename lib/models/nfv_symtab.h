#ifndef NFV_SYMTAB_H
#define NFV_SYMTAB_H

#include "nfv_resource.h"

typedef struct nfv_symtab nfv_symtab;

struct nfv_symtab {
  char **symbols;
  nfv_resource **resources;
  int size;
};

nfv_symtab *nfv_symtab_new(nfv_resource *root);
int nfv_symtab_build(nfv_symtab *o, nfv_resource *res);
int nfv_symtab_append(nfv_symtab *o, nfv_resource *res);
nfv_resource *nfv_symtab_lookup(nfv_symtab *o, char *symbol);
int nfv_symtab_dump(nfv_symtab *o);

#endif
