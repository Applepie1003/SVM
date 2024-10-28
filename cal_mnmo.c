#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cal_mnmo.h"
#include "cal_expr.h"
#include "main.h"

int cal_mn_dmpr(char *oprnd) {
    int opr;
    if (!strcmp(oprnd, "PC")) opr = 0x000000;
    else if (!strcmp(oprnd, "U")) opr = 0x000001;
    else if (!strcmp(oprnd, "X")) opr = 0x000002;
    else if (!strcmp(oprnd, "A")) opr = 0x000003;
    else fprintf(stderr, "%s --> Operand is not vaild ...\n", LBUF), exit(10);
    return(opr);
}

int cal_mn_oprnd(char *oprnd) {
    char buf[128], *xp;
    int opr;
    strcpy(buf, oprnd); // oprnd를 buf에 초기화
    xp = strchr(buf, '['); // 문자를 찾으면 찾은 문자열 포인터를 반환, 찾지 못하면
    if (xp != NULL) {
        if (strcmp(xp, "[X]"))
            fprintf(stderr, "%s --> Operand is not vaild ...\n", LBUF), exit(10);
        *xp = 0;
    }
    opr = cal_one_expr(buf);
    opr &= 0x007fffff;
    if (xp) opr |= OP_XBIT;
    return(opr);
}