#include "nfv_execute.h"
#include <stdio.h>
#include <string.h>

int nfv_executeNode(nfv_resource *o, int level)
{
  int i;
  _indent(level);
  if ( o == NULL ) {
    printf("NULL\n");
    return 0;
  }
  if ( strcmp(o->label, "openstack") == 0 ) {
    /* _indent(level); */
  }
  if ( strcmp(o->label, "flavors") == 0 ) {
    /* _indent(level); */
  }
  printf("- %s[%s]\n", o->label, o->id);
  if ( o->assignments != NULL ) {
    for(i=0;i<o->assignments->size;i++) {
      _indent(level+1);
      printf("* %s = ", o->assignments->assignments[i]->variable);
      if ( o->assignments->assignments[i]->literal_value != NULL ) {
	printf("%s\n", o->assignments->assignments[i]->literal_value);
      } else {
	printf("%d\n", o->assignments->assignments[i]->int_value);
      }
    }
  }
  return 0;
}

int nfv_execute(nfv_resource *o, int level)
{
  if (o->child == NULL && o->sibling == NULL) {
    nfv_executeNode(o, level);
  }
  if ( o->child == NULL && o->sibling != NULL ) {
    nfv_executeNode(o, level);
    nfv_execute(o->sibling, level);
  }
  if ( o->child != NULL && o->sibling == NULL ) {
    nfv_executeNode(o, level);
    nfv_execute(o->child, level+1);
  }
  if ( o->child != NULL && o->sibling != NULL ) {
    nfv_executeNode(o, level);
    nfv_execute(o->child, level+1);
    nfv_execute(o->sibling, level);
  }
  return 0;
}

