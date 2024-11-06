#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "cal_mnmo.h"
#include "cal_expr.h"
#include "main.h"

int cal_nm_dmpr(char *oprnd) {
    int opr;
    if (!strcmp(oprnd, "PC")) opr = 0x000000;
    else if (!strcmp(oprnd, "U")) opr = 0x000001;
    else if (!strcmp(oprnd, "X")) opr = 0x000002;
    else if (!strcmp(oprnd, "A")) opr = 0x000003;
    else fprintf(stderr, "%s --> Operand is not vaild ...\n", LBUF), exit(10);
    return(opr);
}

int cal_nm_oprnd(char *oprnd) {
    char buf[128];
    char *xp;
    int opr;

    // 디버깅 메시지: 전달된 oprnd 값 확인
    printf("cal_nm_oprnd called with operand: %s\n", oprnd ? oprnd : "NULL");

    // oprnd가 NULL이 아닌지 확인
    if (!oprnd) {
        fprintf(stderr, "Error: Operand is NULL.\n");
        exit(10);
    }

    // buf에 oprnd 복사
    strncpy(buf, oprnd, sizeof(buf) - 1);
    buf[sizeof(buf) - 1] = '\0'; // 버퍼 오버플로우 방지

    // '[X]'가 포함된 경우 분리하여 처리
    if ((xp = strstr(buf, "[X]"))) { // "[X]"가 있는지 확인
        if (strcmp(xp, "[X]") != 0) { // "[X]" 외의 값은 에러 처리
            fprintf(stderr, "%s --> Operand is not valid ...\n", LBUF);
            exit(10);
        }
        *xp = '\0'; // '[X]' 부분 제거
    }

    // 남은 값이 있는 buf로 숫자 계산
    opr = cal_one_expr(buf); // 예: "8" 값을 처리
    opr &= 0x007FFFFF; // 23비트 사용 (기본 주소 공간 제한)

    // '[X]'가 있으면 X 비트 설정
    if (xp) {
        opr |= OP_XBIT; // X 비트 설정
    }

    // 결과 디버깅 메시지
    printf("cal_nm_oprnd result: %08X\n", opr);

    return opr;
}


/*
int cal_nm_oprnd(char *oprnd) {
    char buf[128], *xp;
    int opr;
    strcpy(buf, oprnd);

    if (xp = strchr(buf, '[')) {
        if (strcmp(xp, "[X]")) {
            fprintf(stderr, "%s --> Operand is not vaild ...\n", LBUF);
            exit(10);
        }
        *xp = 0;
    }
    opr = cal_one_expr(buf);
    opr &= 0x007fffff;
    if (xp) {
        opr |= OP_XBIT;
    }
    printf("cal_nm_oprnd result: %08X\n", opr);
    return(opr);
}
*/