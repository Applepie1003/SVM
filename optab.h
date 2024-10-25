#include "symtab.h"

#define MAX_OLEN 8
#define MAX_OPTAB (sizeof(OPTAB) / sizeof(struct optab))

typedef struct optab {
    char mneminic[MAX_OLEN];
    unsigned char opcode;
    unsigned char n_operand;
} Optab;

Optab OPTAB[];

Optab *see_OPTAB(char *opc);