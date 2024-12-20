#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "asm_mnmo.h"
#include "cal_mnmo.h"

int asm_mnemonic(Optab *op) {
        // char *obp = OBJC;
        unsigned int obc;
        obc = (op->opcode << 24);
        if(op->n_operand) {
                if(!OPerand) {
			fprintf(stderr, "%s --> Operand is not defined ...\n", LBUF);
			exit(10);
		}
	}
	if(!strcmp(op->mnemonic, "DMPR")) {
                printf("Calculating DMPR operand\n");
		obc |= cal_nm_dmpr(OPerand);
        } else {
                printf("Calculating general operand\n");
		obc |= cal_nm_oprnd(OPerand);
	}

        OBJC[0] = 4;
        OBJC[1] = obc >> 24;
        OBJC[2] = obc >> 16;
        OBJC[3] = obc >> 8;
        OBJC[4] = obc >> 0;
        printf("OBJC values: %d %d %d %d %d\n", OBJC[0], OBJC[1], OBJC[2], OBJC[3], OBJC[4]);
        return(OBJC[0]);
}
