#include <stdio.h>
#include <string.h>
#include "cal_expr.h"
#include "cal_term.h"

int issign(char sign)
{
    if (sign == '+') {return 1;}
    else return 0;
}

int cal_one_expr(char *expr) {
    int expv, v1, v2, sign;
    char *pp = NULL, *mp = NULL, *v2p = NULL;

    if ((sign = issign(*expr)) != 0) expr++;
    else sign = 1;


    if (pp == strchr(expr, '+')) *pp = 0;
    else if(mp == strchr(expr, '-')) *mp = 0;

    if (pp) v2p = pp + 1;
    else if (mp) v2p = mp + 1;

    v1 = sign * cnv_one_term(v2p);
    if (v2p) v2 = cnv_one_term(v2p);
    if (pp)      expv = v1 + v2;
    else if (mp) expv = v1 - v2;
    else         expv = v1;
    return(expv);
}