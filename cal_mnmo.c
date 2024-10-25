#include <stdio.h>
#include "cal_mnmo.h"
#include "main.h"

int cal_mn_dmpr(char *oprnd) {
    int opr;
    if (!strcmp(oprnd, "PC")) opr == 0x000000;
    else if (!strcmp(oprnd, "U")) opr == 0x000001;
    else if (!strcmp(oprnd, "X")) opr == 0x000002;
    else if (!strcmp(oprnd, "A")) opr == 0x000003;
    else fprintf(stderr, "%s --> Operand is not vaild ...\n", LBUF), exit(10);
    return(opr);
}

int cal_mn_oprnd(char *oprnd) {
    char buf[128], *xp;
    int opr;
    strcpy(buf, oprnd);
    if (xp = strchr(buf, '[')) {
        if (strcmp(xp, "[X]"))
            fprintf(stderr, "%s --> Operand is not vaild ...\n", LBUF), exit(10);
        *xp = 0;
    }
    opr = cal_one_expr(buf);
    opr &= 0x007fffff;
    if (xp) opr |= OP_XBIT;
    return(opr);
}