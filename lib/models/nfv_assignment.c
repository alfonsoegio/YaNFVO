#include "nfv_assignment.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

nfv_assignment_col *nfv_assignment_col_new(nfv_assignment *first)
{
  nfv_assignment_col *ac;
  ac = (nfv_assignment_col *)malloc(sizeof(nfv_assignment_col));
  ac->size = 1;
  ac->assignments = (nfv_assignment **)malloc(sizeof(nfv_assignment *));
  ac->assignments[0] = first;
  return ac;
}

nfv_assignment_col *nfv_assignment_col_push(nfv_assignment_col *o, nfv_assignment *next)
{
  o->assignments = (nfv_assignment **)realloc(o->assignments, (o->size+2)*sizeof(nfv_assignment *));
  o->assignments[o->size] = next;
  o->size++;
  return o;
}

nfv_assignment *nfv_assignment_newReference(char *variable, char *ref, char *fcall)
{
  nfv_assignment *o;
  o = (nfv_assignment *)malloc(sizeof(nfv_assignment));
  o->variable = (char *)malloc(sizeof(char)*strlen(variable));
  strcpy(o->variable, variable);
  o->array_size = 0;
  o->int_value = 0;
  o->literal_value = NULL;
  o->reference = (char *)malloc(sizeof(char)*strlen(ref));
  strcpy(o->reference, ref);
  o->fcall = (char *)malloc(sizeof(char)*strlen(fcall));
  strcpy(o->fcall, fcall);
  return o;
}

nfv_assignment *nfv_assignment_newInt(char *variable, int value)
{
  nfv_assignment *o;
  o = (nfv_assignment *)malloc(sizeof(nfv_assignment));
  o->variable = (char *)malloc(sizeof(char)*strlen(variable));
  strcpy(o->variable, variable);
  o->array_size = 0;
  o->int_value = value;
  o->literal_value = NULL;
  o->reference = NULL;
  o->fcall = NULL;
  return o;
}

nfv_assignment *nfv_assignment_newLiteral(char *variable, char *value)
{
  nfv_assignment *o;
  o = (nfv_assignment *)malloc(sizeof(nfv_assignment));
  o->variable = (char *)malloc(sizeof(char)*strlen(variable));
  strcpy(o->variable, variable);
  o->array_size = 0;
  o->int_value = 0;
  o->literal_value = (char *)malloc(sizeof(char)*strlen(value));
  strcpy(o->literal_value, value);
  o->reference = NULL;
  o->fcall = NULL;
  return o;
}

int nfv_assignment_free(nfv_assignment *o)
{
  int i;
  printf("FREEING %s\n", o->variable);
  if ( o->array_size != 0 ) {
    for(i=0;i<o->array_size;i++) {
      printf("FREEING\n");
      /* free(o->array_value[i]); */
    }
    /* free(o->array_value); */
  }
  if ( o->literal_value != NULL ) {
    printf("FREEING LITERAL\n");
    /* free(o->literal_value); */
  }
  return 0;
}

nfv_assignment *nfv_assignment_newArray(char *variable, char **strings, int nstrings)
{
  int i;
  nfv_assignment *o;
  o = (nfv_assignment *)malloc(sizeof(nfv_assignment));
  o->variable = (char *)malloc(sizeof(char)*strlen(variable));
  strcpy(o->variable, variable);
  o->array_size = nstrings;
  o->array_value = (char **)malloc(nstrings*sizeof(char *));
  for(i=0;i<nstrings;i++) {
    o->array_value[i] = (char *)malloc(strlen(strings[i])*sizeof(char));
    strncpy(o->array_value[i], strings[i], strlen(strings[i])*sizeof(char));
  }
  o->int_value = 0;
  o->literal_value = NULL;
  o->reference = NULL;
  o->fcall = NULL;
  return o;
}
