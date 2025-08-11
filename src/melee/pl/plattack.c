#include "plattack.h"

u16 unk_804D6480;

void plAttack_80037590(void)
{
    unk_804D6480 = 1;
}

u16 plAttack_80037B08(void)
{
    u16 before = unk_804D6480;
    unk_804D6480 += 1;
    if (unk_804D6480 == 0) {
        unk_804D6480 = 1;
    }
    return before;
}
