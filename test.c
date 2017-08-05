#include "lib/models/nfv_resource.h"
#include "lib/execution/nfv_execute.h"
#include "lib/models/nfv_symtab.h"
#include "lib/parse/y.tab.h"
#include <stdio.h>

nfv_resource *nfv_parse(int argc, char *argv[]);

int main(int argc, char *argv[])
{
  nfv_resource *nfv;

  if ( argc < 2 ) {
    printf("Usage: %s input_filename\n", argv[0]);
    return 0;
  }
  nfv = nfv_parse(argc, argv);
  nfv_symtab_new(nfv);
  /* printf("SYMBOL TABLE FOR %s (\"adam\" is an openstack PoP)\n", nfv->child->id); */
  /* nfv_symtab_dump(nfv->child->st); */
  /* printf("SYMBOL TABLE FOR %s (\"adam\" is now a network)\n", nfv->child->child->child->id); */
  /* nfv_symtab_dump(nfv->child->child->child->st); */
  printf("\n\n");
  nfv_execute(nfv, 0);
  printf("\n");
  return 0;
}
