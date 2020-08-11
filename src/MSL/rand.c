#include "rand.h"

extern u32 lbl_804D5B50;

void srand(u32 seed)
{
    lbl_804D5B50 = seed;
}

s32 rand(void)
{
    lbl_804D5B50 = lbl_804D5B50 * 1103515245 + 12345;
	return ((lbl_804D5B50 >> 16) & 0x7FFF);
}
