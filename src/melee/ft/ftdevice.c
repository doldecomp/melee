#include "ftdevice.h"

#include <placeholder.h>

#include "ft/inlines.h"

#include <dolphin/os/OSError.h>
#include <baselib/debug.h>

struct ftDeviceUnk3 ft_80459A68[4];
struct ftDeviceUnk4 ft_804D6578;
int ftDevice_BuryThingCount;
int ft_804D6570;

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
            ft_80459A68[i].ground = NULL;
        }
    }
}

void ftCo_800C06E8(Ground_GObj* gobj, int arg1, void* func)
{
    int i;

    for (i = 0; i < 1; i++) {
        if (ft_80459A68[i].ground == NULL) {
            ft_80459A68[i].ground = gobj;
            ft_80459A68[i].type = arg1;
            ft_80459A68[i].active_cb = func;
            ft_804D6578.x0++;
            return;
        }
    }
    HSD_ASSERTREPORT(0x49, 0, "fighter chk device wind func num over!\n");
}

void ftCo_800C0764(Ground_GObj* arg0, u32 arg1, void* arg2)
{
    struct ftDeviceUnk3* base = ft_80459A68;
    struct ftDeviceUnk3* ptr;
    int i;

    ptr = base + 1;
    for (i = 0; i < 2; i++) {
        if (ptr->ground == NULL) {
            base[i + 1].ground = arg0;
            base[i + 1].type = arg1;
            base[i + 1].active_cb = arg2;
            ftDevice_BuryThingCount++;
            return;
        }
        ptr++;
    }
    HSD_ASSERTREPORT(0x6FU, 0, "fighter chk device catch func num over!\n");
}

/// @todo pretty sure arg2 is a ftDevice callback, but unsure if its
/// always of type ftDevice_Callback0.
void ftCo_800C07F8(Ground_GObj* arg0, u32 arg1, void* arg2)
{
    struct ftDeviceUnk3* base = ft_80459A68;
    struct ftDeviceUnk3* ptr;
    int i;

    ptr = base + 3;
    for (i = 0; i < 1; i++) {
        if (ptr->ground == NULL) {
            base[i + 3].ground = arg0;
            base[i + 3].type = arg1;
            base[i + 3].active_cb = arg2;
            ft_804D6570++;
            return;
        }
        ptr++;
    }
    HSD_ASSERTREPORT(0x95, 0, "fighter chk device coll func num over!\n");
}
