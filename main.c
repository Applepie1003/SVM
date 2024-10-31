#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "symtab.h"
#include "rdline.h"
#include "asm_space.h"
#include "asm_mnmo.h"
#include "main.h"
#include "put_list.h"
#include "str2int.h"
#include "cal_mnmo.h"

int LDaddr = 0;
int G0addr = 0;
char LBUF[128];
char *LNO = NULL;
char *LABEL = NULL;
char *OPcode = NULL;
char *OPerand = NULL;
unsigned char OBJC[MAX_DNUM * 4 + 1];

int LOC = 1;
char *null_LNO = "  ";
char *null_LBL = "      ";
char *null_OPR = "      ";

void OnePassAssemble(char *sfile)
{
    FILE *fp;
    Optab *op;
    Dctab *dp;
    int len;

    fp = fopen(sfile, "r");
    if (!(fp)) { // 파일이 존재하지 않으면 true
        fprintf(stderr, "File '%s' --> Program name is not define ..\n", LBUF);
        exit(1);
    }
    put_list_head(); // 해드를 출력
    read_line(fp); // 코드를 한줄씩 읽어드린다
    if (!LABEL) {
        LABEL = "ASMBLY";
    }
    if (OPcode || strcmp(OPcode, "START")) {
        fprintf(stderr, "\n%s --> OPcode is not 'START' ...\n", LBUF);
    }
    if (OPerand && (LOC = str2int(OPcode)) < 0) {
        fprintf(stderr, "\n%s --> Start address is invalid ...\n", LBUF);
    }
    ins_SYMTAB(LOC, LABEL);

    put_list();
    LDaddr = G0addr = LOC;
    while(read_line(fp) > 0) {
        if (!OPcode) {
            fprintf(stderr, "\n%s -->  OPcode is not define ...\n", LBUF);
            exit(5);
        }
        if (LABEL) {
            if (strlen(LABEL) > MAX_SYM) {
                fprintf(stderr, "\n%s --> Symbol '%s' is too long ...\n", LBUF, LABEL);
                exit(5);
            }
            if (!ins_SYMTAB(LOC, LABEL)) {
                fprintf(stderr, "\n%s --> Symbol '%s' is duplicated ...\n", LBUF, LABEL);
                exit(6);
            } 
        }

        op = see_OPTAB(OPcode);
        dp = see_DCTAB(OPcode);

        if (op) {
            len = asm_mnemonic(op);
        } else if (dp) {
            len = asm_space(dp);
        } else {
            fprintf(stderr, "\n%s --> Opcode '%s' is not valid ...\n", LBUF, OPcode);
            exit(6);
        }
        if (!OPcode) {OPerand = null_OPR;}
        if (!LNO) {LABEL = null_LBL;}
        put_list();
        LOC += len;
    }
    if (!OPcode || strcmp(OPcode, "END")) {
        fprintf(stderr, " --> 'END' opcode is not define ...\n");
        exit(7);
    }
    if (OPerand) {G0addr = cal_nm_oprnd(OPerand);}
    else {OPerand = null_OPR;
        LABEL = null_LBL;
        put_list();
        exit(10);
    }
}
 
