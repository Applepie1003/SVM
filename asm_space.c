#include <stdio.h>
#include <string.h>
#include "main.h"
#include "dctab.h"
#include "symtab.h"

int asm_space(Dctab *dp) {
    int len;
    if(!OPerand) {
        if ((!isdigit(OPerand[0]) && OPerand[strlen(OPerand) - 1] != 'h') || (len = str2int(OPerand)) == INV_VAL) {
            fprintf(stderr, "%s --> Operand is not define...\n", LBUF), exit(10);
        }
        len *= dp->unit;
        OBJC[0] = 0;
        return(len);
    }
    if (dp->unit == 1 && OPerand[0] == '\"') {
        len = cal_dc_oprnd_string(OPerand, OBJC);
    } else {
        len = cal_dc_oprnd(OPerand, dp->unit, OBJC);
    }
    return(len);
}