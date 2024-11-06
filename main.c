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

void OnePassAssemble(char *sfile);

int main(int argc, char* argv[]) {
        char *filename = argv[1];
        OnePassAssemble((char *)filename);
        return 0;
}


void OnePassAssemble(char *sfile)
{
    FILE  *fp;
    Optab *op;
    Dctab *dp;
    int   len;

    fp = fopen(sfile, "r");
    if (!(fp)) {
        fprintf(stderr, "File '%s' --> Program name is not define ..\n", LBUF), exit(1);
    }
    put_list_head();
    read_line(fp);
    if (!LABEL) {
        LABEL = "ASMBLY";
    }
    if (!OPcode || strcmp(OPcode, "START")) {
        fprintf(stderr, "\n%s --> OPcode is not 'START' ...\n", LBUF);
        exit(2);
    }

    if (OPerand && (LOC = str2int(OPerand)) < 0) {
        fprintf(stderr, "\n%s --> Start address is invalid ...\n", LBUF);
        exit(3);
    }
    ins_SYMTAB(LOC, LABEL);
    if (!LNO) LNO = null_LNO;
    if (!OPerand) OPerand = null_OPR;
    put_list();
    LDaddr = G0addr = LOC;

    while(read_line(fp) > 0) {
        printf("LBUF: %s\nLNO: %s, LABEL: %s, OPcode: %s, OPerand: %s\n", LBUF, LNO ? LNO: "NULL",LABEL ? LABEL : "NULL", OPcode ? OPcode : "NULL", OPerand ? OPerand : "NULL\n");
        if (!OPcode) {
            fprintf(stderr, "\n%s -->  OPcode is not define ...\n", LBUF);
            exit(5);
        }

        if(!strcmp(OPcode, "END")){
                 break; // OPcode가 END면 반복문 탈출
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

        // op, dp 값 출력
        if (op == NULL && dp != NULL) {
            printf("op: NULL dp: %s\n", dp); 
        } else if(op != NULL && dp == NULL ) {
            printf("op: %s dp: NULL\n", op); 
        } else {
            printf("op: NULL dp: NULL\n"); 
        }
	    

        if (op) {
            len = asm_mnemonic(op);
            printf("len mnemonic 초기화\n");
        } else if (dp) {
            len = asm_space(dp);
            printf("len space 초기화\n");
        } else {
            fprintf(stderr, "\n%s --> Opcode '%s' is not valid ...\n", LBUF, OPcode);
            exit(6);
        }

        if (!OPcode) {
            OPerand = null_OPR;
            printf("OPerand = null_OPR\n");
            }
        if (!LNO) {
            LABEL = null_LBL;
            printf("LABEL = null_LBL\n");
        }
        put_list();
        LOC += len;
        printf("\n");
    }
        if(!(strcmp(OPcode, "END"))) printf("OPcode is END\n");
    if (!OPcode || strcmp(OPcode, "END")) {
        fprintf(stderr, " --> 'END' opcode is not define ...\n");
        exit(7);
    }
    if (OPerand) {G0addr = cal_nm_oprnd(OPerand);}
    else {
        OPerand = null_OPR;
        LABEL = null_LBL;
        if(!LNO) LNO = null_LNO;
        put_list();
        exit(10);
    }
        fclose(fp);
}
