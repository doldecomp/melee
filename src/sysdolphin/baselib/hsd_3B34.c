#include "hsd_3B34.h"

//hsd_803B5C2C
static int lbl_804D6398 = 3;

void hsd_803B5C2C(int mode){
    lbl_804D6398 = mode;
    if ((mode < 1) || (mode > 10)) {
        lbl_804D6398 = 3;
    }
}