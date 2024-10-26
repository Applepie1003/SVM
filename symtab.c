#include <string.h>
#include "symtab.h"


int ins_SYMTAB(int value, char *sym) {
    if (see_SYMTAB(sym) != INV_VAL) {
        return 0;
    }
    strcpy(SYMTAB[SYMCNT].symbol, sym);
    SYMTAB[SYMCNT].value = value;
    SYMCNT++;
    return 1;
}

int see_SYMTAB(char *sym) {
    int i;
    for (i = 0; i < SYMTAB; i++) {
        if (!strcmp(SYMTAB[i].symbol, sym)) {
            return(SYMTAB[i].value);
        }
    } 
    return INV_VAL;
}