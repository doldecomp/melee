#include "plbonus.h"
#include "types.h"

unsigned int pl_800386D8(plActionStats* arg0, ssize_t arg1)
{
    return arg0->by_attack_hi[arg1];
}

int pl_800386E8(pl_800386E8_arg0_t* arg0)
{
    int temp = arg0->unk_190 + arg0->unk_5AC;
    return temp + arg0->unk_5B0;
}

int fn_80038700(const int* arg0, int arg1, int arg2)
{
    int sum = 0;
    int i;

    for (i = arg1; i <= arg2; i++) {
        sum += arg0[i + 1];
    }
    return sum;
}
