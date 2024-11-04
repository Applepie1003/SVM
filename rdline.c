#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "main.h"
#include "rdline.h"
#include "optab.h"
#include "dctab.h"

int read_line(FILE *fp) {
    static char buf[128];
    char *cp;

    LNO = NULL, LABEL = NULL, OPcode = NULL, OPerand = NULL;

    do {
        if (!fgets(buf, sizeof(buf), fp)) return -1;
        strcpy(LBUF, buf); LBUF[strlen(LBUF)-1] = 0;
        if (cp = strstr(buf, "//")) *cp = '\0';
    } while (!(cp = strtok(buf, " \t\n\r")));

    int i, len;
    if (isdigit(*cp)) {
        i = 0, len = strlen(cp) -1;
        while(isdigit(cp[i])) {
                i++;
        }
        if(i == len) {
                LNO = cp;
                cp = strtok(NULL, " \t\n\r");
        } else {
                fprintf(stderr, "\n%s --> LNO must ne composed of numbers only\n", LBUF);
                exit(4);
        }
        // LNO = cp;
        // cp = strtok(NULL, " \t\n\r");
    }
    if (isdigit(*cp)) {
        LNO = cp;
        cp = strtok(NULL, "\t\n\r");
        }

    if (strcmp(cp, "END") && strcmp(cp, "START") && !see_OPTAB(cp) && !see_DCTAB(cp)) {
        LABEL = cp;
        cp = strtok(NULL, " \t\n\r");
    }

    OPcode = cp;  // 다음 토큰을 OPcode로 설정
    OPerand = strtok(NULL, " \t\n\r");  // 다음 토큰을 OPerand로 설정
    return 1;
}
