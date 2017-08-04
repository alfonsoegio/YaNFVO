#include "nfv_symtab.h"
#include <string.h>
#include <stdio.h>

nfv_symtab *nfv_symtab_new(nfv_resource *root)
{
  nfv_symtab *o;
  o = (nfv_symtab *)malloc(sizeof(nfv_symtab));
  o->symbols = (char **)malloc(sizeof(char *));
  o->symbols[0] = (char *)malloc(sizeof(char)*strlen(root->id));
  strcpy(o->symbols[0], root->id);
  o->resources = (nfv_resource **)malloc(sizeof(nfv_resource *));
  o->resources[0] = root;
  o->size = 1;
  nfv_symtab_build(o, root->child);
  return o;
}

int nfv_symtab_append(nfv_symtab *o, nfv_resource *res)
{
  o->symbols = (char **)realloc(o->symbols, (o->size+1)*sizeof(char *));
  o->symbols[o->size] = (char *)malloc(sizeof(char)*strlen(res->id));
  strcpy(o->symbols[o->size], res->id);
  o->resources = (nfv_resource **)realloc(o->resources, (o->size+1)*sizeof(nfv_resource *));
  o->resources[o->size] = res;
  o->size++;
  return 0;
}

int nfv_symtab_build(nfv_symtab *o, nfv_resource *res)
{
  nfv_symtab_append(o, res);
  if ( res->child == NULL && res->sibling == NULL) {
    /* DO NOTHING */
  }
  if ( res->child == NULL && res->sibling != NULL ) {
    nfv_symtab_build(o, res->sibling);
  }
  if ( res->child != NULL && res->sibling == NULL ) {
    nfv_symtab_build(o, res->child);
  }
  if ( res->child != NULL && res->sibling != NULL ) {
    nfv_symtab_build(o, res->child);
    nfv_symtab_build(o, res->sibling);
  }
  return 0;
}

int nfv_symtab_dump(nfv_symtab *o)
{
  int i;
  for(i=0;i<o->size;i++) {
    printf("%s -> %s\n", o->symbols[i], o->resources[i]->label);
  }
  return 0;
}
