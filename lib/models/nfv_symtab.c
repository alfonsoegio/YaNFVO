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
  root->st = NULL;
  return o;
}

nfv_symtab *nfv_symtab_copy(nfv_symtab *o)
{
  int i;
  nfv_symtab *st;
  st = (nfv_symtab *)malloc(sizeof(nfv_symtab));
  st->symbols = (char **)malloc(o->size*sizeof(char *));
  st->resources = (nfv_resource **)malloc(o->size*sizeof(nfv_resource *));
  for(i=0;i<o->size;i++) {
    st->symbols[i] = (char *)malloc(strlen(o->symbols[i])*sizeof(char));
    strcpy(st->symbols[i], o->symbols[i]);
    st->resources[i] = o->resources[i];
  }
  st->size = o->size;
  return st;
}

int nfv_symtab_append(nfv_symtab *o, nfv_resource *res)
{
  int i;
  for(i=0;i<o->size;i++) {
    if ( strcmp(res->id, o->symbols[i]) == 0 ) {
      o->resources[i] = res;
      return 0;
    }
  }
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
  res->st = nfv_symtab_copy(o);
  if ( res->child == NULL && res->sibling == NULL) {
    /* DO NOTHING */
  }
  if ( res->child == NULL && res->sibling != NULL ) {
    nfv_symtab_build(o, res->sibling);
    res->sibling->st = nfv_symtab_copy(o);
  }
  if ( res->child != NULL && res->sibling == NULL ) {
    nfv_symtab_build(o, res->child);
    res->child->st = nfv_symtab_copy(o);
  }
  if ( res->child != NULL && res->sibling != NULL ) {
    nfv_symtab_build(o, res->child);
    res->child->st = nfv_symtab_copy(o);
    nfv_symtab_build(o, res->sibling);
    res->sibling->st = nfv_symtab_copy(o);
  }
  return 0;
}

nfv_resource *nfv_symtab_searchByType(nfv_symtab *o, char *type)
{
  int i;
  for(i=o->size-1;i>=0;i--) {
    if ( strcmp(o->resources[i]->label, type) == 0 ){
      return o->resources[i];
    }
  }
  return NULL;
}

int nfv_symtab_dump(nfv_symtab *o)
{
  int i;
  if ( o == NULL ) {
    return 1;
  }
  for(i=0;i<o->size;i++) {
    printf("%s -> %s\n", o->symbols[i], o->resources[i]->label);
  }
  return 0;
}
