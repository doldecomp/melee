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

ColorOverlay* ftCo_800C0658(Fighter* fp)
{
    return (int) fp->x408.x28_colanim.ptr != 0 ? &fp->x408 : &fp->x488;
}

ColorOverlay* ftCo_800C0674(Fighter_GObj* gobj)
{
    return ftCo_800C0658(GET_FIGHTER(gobj));
}

/// @todo Wrong return type. Union?
enum_t ftCo_800C0694(Fighter* fp)
{
    return ftCo_800C0658(fp)->x28_colanim.i;
}

int ftCo_800C06B4(Fighter* fp)
{
    return (int) &fp->x508.x28_colanim.ptr->x7B;
}

void ftCo_800C06C0(void)
{
    ft_804D6570 = 0;
    ftDevice_BuryThingCount = 0;
    ft_804D6578.x0 = 0;
    {
        int i;
        for (i = 0; i < 4; i++) {
            ft_80459A68[i].ground = 0;
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

/// @todo pretty sure arg2 is a ftDevice callback, but unsure if its
// always of type ftDevice_Callback0.
void ftCo_800C07F8(Ground_GObj* arg0, u32 arg1, void* arg2)
{
    struct ftDeviceUnk3* temp_r6;
    /// @todo is supposed to load in ft_80459A8C, which is ft_80459A68[3]
    if (ft_80459A68[3].ground == NULL) {
        temp_r6 = &ft_80459A68[3];
        temp_r6->ground = arg0;
        temp_r6->type = arg1;
        temp_r6->active_cb = arg2;
        ft_804D6570++;
    }
    else {
        OSReport("fighter chk device coll func num over!\n", ft_80459A68);
        __assert("ftdevice.c", 0x95U, "0");
    }
}
