#include "ftdevice.h"

#include "ft/inlines.h"

#include <placeholder.h>
#include <dolphin/os/OSError.h>
#include <baselib/debug.h>

#pragma force_active on

/* literal */ extern char* ftDevice_803C6B18;
/* literal */ extern char* ftDevice_803C6B40;
/* literal */ extern char* ftDevice_803C6B4C;
/* literal */ extern char* ftDevice_803C6B78;
/* literal */ extern char* ftCo_804D3C18;

ftDeviceUnk2* ftCo_800C0658(Fighter* fp)
{
    return fp->x408.x28 != 0 ? &fp->x408 : &fp->x488;
}

ftDeviceUnk2* ftCo_800C0674(Fighter_GObj* gobj)
{
    return ftCo_800C0658(GET_FIGHTER(gobj));
}

enum_t ftCo_800C0694(Fighter* fp)
{
    return ftCo_800C0658(fp)->x28;
}

int ftCo_800C06B4(Fighter* fp)
{
    return (int) &fp->x530->x7B;
}

void ftCo_800C06C0(void)
{
    ft_804D6570 = 0;
    ft_804D6574 = 0;
    ft_804D6578 = 0;
    {
        int i;
        for (i = 0; i < 4; i++) {
            ft_80459A68[i].x = 0;
        }
    }
}

UNK_RET ftCo_800C06E8(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800C0764(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

void ftCo_800C07F8(int arg0, int arg1, int arg2)
{
    IntVec3* temp_r6;

    if ((u32) M2C_FIELD(ft_80459A68, u32*, 0x24) == 0U) {
        temp_r6 = &ft_80459A68[0];
        temp_r6->x = arg0;
        temp_r6->y = arg1;
        temp_r6->z = arg2;
        ft_804D6570 += 1;
    } else {
        OSReport("fighter chk device coll func num over!\n", ft_80459A68, 0);
        __assert("ftdevice.c", 149, "0");
    }
}
