#include <stdio.h>
#include <string.h>
#include "asc2int.h"
#include "symtab.h"

int asc2int(char *ap) {
    int l = strlen(ap), v;
    if (ap[l - 1] != '\'') {return INV_VAL;}
    for (v = 0; *(ap + 1) != '\''; ap++) {
        v = (v << 8) | *(ap + 1);
    }
    return(v);
}