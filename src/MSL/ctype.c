#include <dolphin/types.h>

extern u8 LowercaseTable[];
extern u8 UppercaseTable[];

int toupper(int c){
    if(c == -1) return -1;
    return UppercaseTable[c & 0xFF];
}

int tolower(int c){
    if(c == -1) return -1;
    return LowercaseTable[c & 0xFF];
}
