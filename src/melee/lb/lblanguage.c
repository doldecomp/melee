#include "lblanguage.h"

u8 func_8000AD8C(void) {
    return lbl_804D3EE0[0];
}

int func_8000AD98(int language) {
    if(language >= 0 && language < 2) {
        lbl_804D3EE0[0] = language;
    }
}

int func_8000ADB4(void) {
    return (lbl_804D3EE0[0]) == 0 ? 1 : 0;
}

int func_8000ADD4(void) {
    return (lbl_804D3EE0[0]) == 1 ? 1 : 0;
}

// this matches, but it needs the correct epilogue patch
#pragma scheduling off
u8 func_8000ADF4() {
    return func_8015CC58()[0x16];
}
#pragma scheduling on

void func_8000AE18(int language) {
    if(language >= 0 && language < 2)
        func_8015CC58()[0x16] = language;
}

int func_8000AE58(void) {
    return (func_8015CC58()[0x16] == 0) ? 1 : 0;
}

int func_8000AE90(void) {
    return (func_8015CC58()[0x16] == 1) ? 1 : 0;
}
