#include "ftdevice.h"

#include <placeholder.h>

#include "ft/inlines.h"

#include <dolphin/os/OSError.h>
#include <baselib/debug.h>

/// @remarks MWCC lays out unreferenced .bss objects in reverse declaration
/// order after referenced objects, so ftDevice_CollThings must be declared
/// before ftDevice_BuryThings to place these tables at their retail addresses.
struct ftDeviceUnk3 ftDevice_WindThings[1];
struct ftDeviceUnk3 ftDevice_CollThings[1];
struct ftDeviceUnk5 ftDevice_BuryThings[2];
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
    int i;

    ft_804D6570 = 0;
    ftDevice_BuryThingCount = 0;
    ft_804D6578.x0 = 0;
    ftDevice_WindThings[0].ground = NULL;
    for (i = 0; i < 2; i++) {
        ftDevice_BuryThings[i].x0 = NULL;
    }
    ftDevice_CollThings[0].ground = NULL;
}

void ftCo_800C06E8(Ground_GObj* gobj, int arg1, void* func)
{
    int i;

    for (i = 0; i < 1; i++) {
        if (ftDevice_WindThings[i].ground == NULL) {
            ftDevice_WindThings[i].ground = gobj;
            ftDevice_WindThings[i].type = arg1;
            ftDevice_WindThings[i].active_cb = func;
            ft_804D6578.x0++;
            return;
        }
    }
    HSD_ASSERTREPORT(0x49, 0, "fighter chk device wind func num over!\n");
}

void ftCo_800C0764(Ground_GObj* arg0, u32 arg1, void* arg2)
{
    int i;

    for (i = 0; i < 2; i++) {
        if (ftDevice_BuryThings[i].x0 == NULL) {
            ftDevice_BuryThings[i].x0 = arg0;
            ftDevice_BuryThings[i].x4 = arg1;
            ftDevice_BuryThings[i].cb = arg2;
            ftDevice_BuryThingCount++;
            return;
        }
    }
    HSD_ASSERTREPORT(0x6FU, 0, "fighter chk device catch func num over!\n");
}

/// @todo pretty sure arg2 is a ftDevice callback, but unsure if its
/// always of type ftDevice_Callback0.
void ftCo_800C07F8(Ground_GObj* arg0, u32 arg1, void* arg2)
{
    int i;

    for (i = 0; i < 1; i++) {
        if (ftDevice_CollThings[i].ground == NULL) {
            ftDevice_CollThings[i].ground = arg0;
            ftDevice_CollThings[i].type = arg1;
            ftDevice_CollThings[i].active_cb = arg2;
            ft_804D6570++;
            return;
        }
    }
    HSD_ASSERTREPORT(0x95, 0, "fighter chk device coll func num over!\n");
}
