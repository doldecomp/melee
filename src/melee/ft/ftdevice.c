#include "ftdevice.h"

#include <placeholder.h>

#include "ft/inlines.h"

#include <dolphin/os/OSError.h>
#include <baselib/debug.h>

#pragma force_active on

/* literal */ extern char* ftDevice_803C6B18;
/* literal */ extern char* ftDevice_803C6B40;
/* literal */ extern char* ftDevice_803C6B4C;
/* literal */ extern char* ftDevice_803C6B78;
/* literal */ extern char* ftCo_804D3C18;

struct ftDeviceUnk3 ft_80459A68[4];
static int ft_804D6570;
struct ftDeviceUnk4 ft_804D6578;
int ftDevice_BuryThingCount;

ftDeviceUnk2* ftCo_800C0658(Fighter* fp)
{
    return (int) fp->x408.x28 != 0 ? &fp->x408 : &fp->x488;
}

ftDeviceUnk2* ftCo_800C0674(Fighter_GObj* gobj)
{
    return ftCo_800C0658(GET_FIGHTER(gobj));
}

/// @todo Wrong return type. Union?
enum_t ftCo_800C0694(Fighter* fp)
{
    return (int) ftCo_800C0658(fp)->x28;
}

int ftCo_800C06B4(Fighter* fp)
{
    return (int) &fp->x508.x28->x7B;
}

void ftCo_800C06C0(void)
{
    ft_804D6570 = 0;
    ftDevice_BuryThingCount = 0;
    ft_804D6578.x0 = 0;
    {
        int i;
        for (i = 0; i < 4; i++) {
            ft_80459A68[i].x0 = 0;
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

void ftCo_800C07F8(UNK_T arg0, int arg1, int arg2)
{
    struct ftDeviceUnk3* temp_r6;

    if ((u32) M2C_FIELD(ft_80459A68, u32*, 0x24) == 0U) {
        temp_r6 = &ft_80459A68[0];
        temp_r6->x0 = arg0;
        temp_r6->x4 = arg1;
        temp_r6->active_cb = (UNK_T) arg2;
        ++ft_804D6570;
    } else {
        OSReport("fighter chk device coll func num over!\n", ft_80459A68, 0);
        __assert("ftdevice.c", 149, "0");
    }
}
