#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_drctv.h"

int LOC = 0, LDaddr, G0addr;
char LBUF[128], *LNO, *LABEL, *OPcode, OPerand;
unsigned char OBJC[MAX_DNUM * 4 + 1];
char *null_LNO = "  ";
char *null_LBL = "      ";
char *null_OPR = "      ";

extern void OnePassAssemble(char *sfile) {}
