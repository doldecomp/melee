#include <platform.h>

struct lbMemory_UnkStruct1 {
    uintptr_t x0;
    uintptr_t x4;
    char x8[0x6F0 - 0x8];
};

static struct lbMemory_UnkStruct1 lbMemory_804318B0;

void lbMemory_800154BC(uintptr_t* arg0, uintptr_t* arg1)
{
    *arg0 = lbMemory_804318B0.x0;
    *arg1 = lbMemory_804318B0.x4;
}
