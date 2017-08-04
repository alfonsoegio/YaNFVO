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
  st = nfv_symtab_new(nfv);
  nfv_symtab_dump(st);
  return 0;
}
