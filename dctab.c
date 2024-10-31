#include <string.h>
#include "dctab.h"

Dctab DCTAB[] = {
    {"DD", DC_CNST, DC_DW}, {"DW", DC_CNST, DC_WD}, {"DB", DC_CNST, DC_BT},
    {"RD", DC_RESV, DC_DW}, {"BW", DC_RESV, DC_WD}, {"RE", DC_RESV, DC_BT}
};
Dctab *see_DCTAB(char *dcc)
{
    for (int i = 0; i < MAX_DCTAB; i++) {
        if (!strcmp(DCTAB[i].directive, dcc)) {
            return(&DCTAB[i]);
        }
    }
    return NULL;
}