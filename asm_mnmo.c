#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "asm_mnmo.h"
#include "cal_mnmo.h"


int asm_mnemonic(Optab *op) {
    // char *obp = OBJC;
    unsigned int obc = (op->n_operand << 24);
    if (op->n_operand) {
        if (!OPerand) {
            fprintf(stderr, "%s ==> Operand is not define ...\n", LBUF), exit(10);
        }
        if (!strcmp(op->mneminic, "DMPR")) {
            obc |= (cal_nm_dmpr(OPerand));
        } else {
            obc |= cal_nm_oprnd(OPerand);
        }
    }
    OBJC[0] = 4;
    OBJC[1] = obc >> 24;
    OBJC[2] = obc >> 16;
    OBJC[3] = obc >> 8;
    OBJC[4] = obc >> 0;
    return(OBJC[0]);
}