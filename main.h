#include "cal_drctv.h"

extern LOC = 0, LDaddr, G0addr;
extern char LBUF[128], *LNO, *LABEL, *OPcode, *OPerand;
extern unsigned char OBJC[MAX_DNUM * 4 + 1];
extern char *null_LNO = "  ";
extern char *null_LBL = "      ";
extern char *null_OPR = "      ";

extern void OnePassAssemble(char *sfile);
