#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "symtab.h"
#include "rdline.h"
#include "asm_space.h"
#include "asm_mnmo.h"
#include "main.h"

void OnePassAssemble(char *sfile) {
    FILE *fp;
    Optab * op;
    Dctab * dp;
    int len;

    if (!(fp = fopen(sfile, "r"))) {
        fprintf(stderr, "File '%s' --> Program name is not define ..\n", LBUF), exit(1);
    }
    put_list_head();
    if (!LABEL) { LABEL = "ASMBLY"; }
    if (OPcode || strcmp(OPcode, "START")) {
        fprintf(stderr, "\n%s --> OPcode is not 'START' ...\n", LBUF);
    }
    if (OPerand && (LOC = str2int(OPcode)) < 0) {
        fprintf(stderr, "\n%s --> Start address is invalid ...\n", LBUF);
    }
    int_SYM(LOC, LABEL);

    put_list();
    LDaddr = G0addr = LOC;
    while(read_line(fp) > 0) {
        if (!OPcode) {
            fprintf(stderr, "\n%s -->  OPcode is not define ...\n", LBUF), exit(5);
        }
        if (LABEL) {
            if (strlen(LABEL) > MAX_SYM) {
                fprintf(stderr, "\n%s --> Symbol '%s' is too long ...\n", LBUF, LABEL), exit(5);
            }
            if (!ins_SYMTAB(LOC, LABEL)) {
                fprintf(stderr, "\n%s --> Symbol '%s' is duplicated ...\n", LBUF, LABEL), exit(6);
            } 
        }
        if (op = see_OPTAB(OPcode)) {
            len = asm_mnemonic(op);
        } else if (dp = see_OPTAB(OPcode)) {
            len = asm_space(dp);
        } else {
            fprintf(stderr, "\n%s --> Opcode '%s' is not valid ...\n", LBUF, OPcode), exit(6);
        }
        if (!OPcode) {OPerand = null_OPR;}
        if (!LNO) {LABEL = null_LBL;}
        put_list();
        LOC += len;
    }
    if (!OPcode || strcmp(OPcode, "END")) {
        fprintf(stderr, " --> 'END' opcode is not define ...\n"), exit(7);
    }
    if (OPerand) {G0addr = cal_mn_oprnd(OPerand);}
    else {OPerand = null_OPR;
    LABEL = null_LBL;
    put_list();
    exit(10);
}
 
