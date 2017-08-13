#ifndef EXECUTE_H
#define EXECUTE_H

#include "../models/nfv_resource.h"
#include "../models/nfv_assignment.h"
#include "../models/nfv_symtab.h"
#include <stdio.h>

int nfv_execute(nfv_resource *nfv, FILE *outfile);

#endif
