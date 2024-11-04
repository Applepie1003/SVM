#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "cal_term.h"
#include "main.h"
#include "symtab.h"
#include "str2int.h"
#include "asc2int.h"

int cnv_one_term(char *term) {
    int val;
    if (isdigit(term[0]) || term[strlen(term) -1] == 'h') {
        if ((val = str2int(term)) == INV_VAL) {
            fprintf(stderr, "%s --> Operand number '%s' is not vaild...\n", LBUF, term);
            exit(11);
        }
    } else if (term[0] == '\'') {
        if ((val = asc2int(term)) == INV_VAL)
            fprintf(stderr, "%s --> Operand number '%s' is not vaild...\n", LBUF, term);
            exit(11);
    } else {
        if((val = see_SYMTAB(term)) == INV_VAL)
            fprintf(stderr, "%s --> Operand number '%s' is not vaild...\n", LBUF, term);
            exit(12);
    }
    return(val);
}
