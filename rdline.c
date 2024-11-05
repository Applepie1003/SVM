#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "main.h"
#include "rdline.h"
#include "optab.h"
#include "dctab.h"

char *cp;
void trim_whitespace(char *str) {
    char *end;
    // 시작 부분 공백 제거
    while (isspace((unsigned char)*str)) str++;
    // 문자열 끝으로 이동
    end = str + strlen(str) - 1;
    // 끝 부분 공백 제거
    while (end > str && isspace((unsigned char)*end)) end--;
    // 문자열 종료 문자 추가
    *(end + 1) = '\0';
    cp = str;
}

int read_line(FILE *fp) {
    static char buf[128];

    LNO = NULL, LABEL = NULL, OPcode = NULL, OPerand = NULL;

    do {
        if (!fgets(buf, sizeof(buf), fp)) return -1;
        strcpy(LBUF, buf); LBUF[strlen(LBUF)-1] = 0;
        if (cp = strstr(buf, "//")) *cp = '\0';
    } while (!(cp = strtok(buf, " \t\n\r")));

    if (isdigit(*cp)) {
        LNO = cp;
        cp = strtok(NULL, "\t\n\r");
        }
    trim_whitespace(cp); 
    if (strcmp(cp, "END") && strcmp(cp, "START") && !see_OPTAB(cp) && !see_DCTAB(cp)) {
        LABEL = cp;
        cp = strtok(NULL, " \t\n\r");
    }

    OPcode = cp;  // 다음 토큰을 OPcode로 설정
    OPerand = strtok(NULL, " \t\n\r");  // 다음 토큰을 OPerand로 설정
    return 1;
}
