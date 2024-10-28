#include <stdio.h>
#include <string.h>
#include "dctab.h"

Dctab DCTAB[] = {
    "DINT", DC_CNST, DC_DW, "DWRD", DC_CNST, DC_WD, "DBYT", DC_CNST, DC_BT,
    "RINT", DC_RESV, DC_DW, "RWRD", DC_RESV, DC_WD, "RBYT", DC_RESV, DC_BT
};
Dctab *see_DCTAB(char *dcc) {
    int i;
    for (i = 0; i < MAX_DCTAB; i++) {
        if (!strcmp(DCTAB[i].directive, dcc)) {
            return(&DCTAB[i]);
        }
    }
}