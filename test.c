#include "lib/models/nfv_resource.h"
#include "lib/execution/nfv_execute.h"
#include "lib/models/nfv_symtab.h"
#include "lib/parse/y.tab.h"
#include <stdio.h>
#include <string.h>

nfv_resource *nfv_parse(int argc, char *argv[]);

int main(int argc, char *argv[])
{
  nfv_resource *nfv;
  FILE *outfile;
  char outputfilename[1024];

  if ( argc < 3 ) {
    printf("Usage: %s input_filename output_filename\n", argv[0]);
    return 0;
  }
  strcpy(outputfilename, argv[2]);
  nfv = nfv_parse(argc, argv);
  nfv_symtab_new(nfv);
  printf("\n\n");
  outfile = fopen(outputfilename, "w");
  nfv_execute(nfv, outfile);
  fclose(outfile);
  printf("\n");
  return 0;
}
