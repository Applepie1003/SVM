#include "optab.h"

Optab OPTAB[] = {
    "LDA", 0x00, 1,
    "LDAW", 0x01, 1,
    "LDX", 0x04, 1,
    "LDU", 0x05, 1,
    "STA", 0x08, 1,
    "STAW", 0x09, 1,
    "STX", 0x0C, 1,
    "STU", 0x0D, 1,
    "ADD", 0x10, 1, "ADDW", 0x11, 1,
    "SUB", 0x14, 1, "SUBW", 0x15, 1,
    "AND", 0x18, 1,
    "OR", 0x19, 1,
    "SHL", 0x1C, 1,
    "SHR", 0x1D, 1,
    "CMP", 0x20, 1,
    "CMPW", 0x21, 1,
    "IXC", 0x24, 1,
    "JZ", 0x28, 1,
}

// Optab OPTAB[] = {
//     "LDA" , 0x00, 1, "LDAW", 0x01, 1, "LDAB", 
// }
Optab *see_OPTAB(char *opc);


