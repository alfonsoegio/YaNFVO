#include "lib/models/nfv_resource.h"
#include "lib/execution/nfv_execute.h"
#include "lib/models/nfv_symtab.h"
#include "lib/parse/y.tab.h"
#include <stdio.h>

nfv_resource *nfv_parse(int argc, char *argv[]);

int main(int argc, char *argv[])
{
  nfv_resource *nfv;
  nfv_symtab *st;

  if ( argc < 2 ) {
    printf("Usage: %s input_filename\n", argv[0]);
    return 0;
  }
  nfv = nfv_parse(argc, argv);
  /* build the global st */
  st = nfv_symtab_new(nfv);
  nfv_symtab_dump(st);
  /* nfv_resource_dump(nfv, 0); */
  /* nfv_resource_dump(nfv->child->child->child, 0); */
  /* printf("\n"); */
  printf("FIRST %s\n", nfv->child->child->child->id);
  nfv_symtab_dump(nfv->child->child->child->st);
  printf("SECOND %s\n", nfv->child->child->id);
  nfv_symtab_dump(nfv->child->child->st);
  printf("LAST %s\n", nfv->child->id);
  nfv_symtab_dump(nfv->child->st);

  return 0;
}
