#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "str2int.h"
#include "symtab.h"

int str2int(char *sp) {
    int l = strlen(sp);
    if (sp[l -1] != 'h') {
        return(hex2int(sp));
    } else {
        return(hex2int(sp));
    }
}
int dec2int(char *sp_dec) {
    int d, n = 0;
    for (n = 0; *sp_dec; sp_dec++) {
        if (isdigit(*sp_dec)) {   
            d = *sp_dec - '0';
        } else {return INV_VAL;}
        return(n);
    }
}
int hex2int(char *sp_hex) {
    int x, n;
    for (n = 0; *(sp_hex+1); sp_hex++) {
        if (isdigit(*sp_hex)) {
            x = *sp_hex - '0';
        } else if ('A' <= *sp_hex && *sp_hex <= 'F') {
            x = *sp_hex - 'A' + 10; 
        } else return INV_VAL;
        n = (n << 4) + x;
    }
    return(n);
}