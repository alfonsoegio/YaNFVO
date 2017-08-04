#include "nfv_resource.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

nfv_resource *nfv_resource_new(char *label, char *id,
			       nfv_assignment_col *assignments)
{
  nfv_resource *res;
  res = (nfv_resource *)malloc(sizeof(nfv_resource));
  res->label = (char *)malloc(sizeof(char)*strlen(label));
  strcpy(res->label,  label);
  res->id = (char *)malloc(sizeof(char)*strlen(id));
  strcpy(res->id, id);
  res->child = NULL;
  res->sibling = NULL;
  res->parent = NULL;
  res->assignments = assignments;
  return res;
}

void _indent(int level)
{
  int i;
  for(i=0;i<level;i++) {
    printf(" ");
  }
}

int nfv_resource_dumpNode(nfv_resource *o, int level)
{
  int i;
  _indent(level);
  if ( o == NULL ) {
    printf("NULL\n");
    return 0;
  }
  printf("- %s[%s]\n", o->label, o->id);
  if ( o->assignments != NULL ) {
    for(i=0;i<o->assignments->size;i++) {
      _indent(level+1);
      printf("* %s = ", o->assignments->assignments[i]->variable);
      if ( o->assignments->assignments[i]->reference != NULL ) {
	printf("%s from %s\n",
	       o->assignments->assignments[i]->fcall,
	       o->assignments->assignments[i]->reference);
      } else {
	if ( o->assignments->assignments[i]->literal_value != NULL ) {
	  printf("%s\n", o->assignments->assignments[i]->literal_value);
	} else {
	  printf("%d\n", o->assignments->assignments[i]->int_value);
	}
      }
    }
  }
  return 0;
}

int nfv_resource_dump(nfv_resource *o, int level)
{
  if (o->child == NULL && o->sibling == NULL) {
    nfv_resource_dumpNode(o, level);
  }
  if ( o->child == NULL && o->sibling != NULL ) {
    nfv_resource_dumpNode(o, level);
    nfv_resource_dump(o->sibling, level);
  }
  if ( o->child != NULL && o->sibling == NULL ) {
    nfv_resource_dumpNode(o, level);
    nfv_resource_dump(o->child, level+1);
  }
  if ( o->child != NULL && o->sibling != NULL ) {
    nfv_resource_dumpNode(o, level);
    nfv_resource_dump(o->child, level+1);
    nfv_resource_dump(o->sibling, level);
  }
  return 0;
}
