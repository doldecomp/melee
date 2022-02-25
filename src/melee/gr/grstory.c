#include "grstory.h"

extern StageInfo stage_info;

void* lbl_804D69B8;

void func_801E302C(void)
{
}

void func_801E3030(void)
{
    lbl_804D69B8 = func_801C49F8();
    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 1;
    func_801E30D8(0);
    func_801E30D8(1);
    func_801E30D8(3);
    func_801E30D8(2);
    func_801C39C0();
    func_801C3BB4();
}

void lbl_801E30A8(void)
{
}

void lbl_801E30AC(void)
{
    func_801CAE04(0);
}

s32 lbl_801E30D0(void)
{
    return 0;
}
