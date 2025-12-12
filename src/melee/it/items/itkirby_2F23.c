#include "itkirby_2F23.h"

#include <placeholder.h>
#include <platform.h>

#include "it/inlines.h"
#include "ft/chara/ftKirby/ftKb_Init.h"

double it_802F23AC(int* obj, float* pos)
{
    float dz;
    float dy;
    float dx;
    unsigned char* r3;

    r3 = *(unsigned char**) ((unsigned char*) obj + 0x2C);

    dx = *(float*) (r3 + 0x4C) - pos[0]; // dx 4:  lfs f2,0(r4)    -> pos[0]
    dy = *(float*) (r3 + 0x50) -
         pos[1]; // dy 8:  lfs f3,0x4c(r3) -> *(temp_r3 + 0x4C)
    dz = *(float*) (r3 + 0x54) -
         pos[2]; // dz c:  lfs f1,0x50(r3) -> *(temp_r3 + 0x50)
    {
        float dx2 = dx * dx; // 24: fmuls f1,f4,f4
        float dy2 = dy * dy; // 2c: fmuls f0,f3,f3
        float dz2 = dz * dz; // 30: fmuls f2,f2,f2

        // 34: fadds f0,f1,f0
        // 38: fadds f1,f2,f0
        return (double) (dz2 + (dx2 + dy2));
    }
}

/// #it_802F23EC

bool itKirby_2F23_UnkMotion0_Anim(Item_GObj* gobj)
{
    return false;
}

void itKirby_2F23_UnkMotion0_Phys(Item_GObj* gobj) {}

bool itKirby_2F23_UnkMotion0_Coll(Item_GObj* gobj)
{
    return false;
}

/// #it_802F258C

/// #it_802F2810

bool itKirby_2F23_UnkMotion1_Anim(Item_GObj* gobj)
{
    return false;
}

void itKirby_2F23_UnkMotion1_Phys(Item_GObj* gobj) {}

bool itKirby_2F23_UnkMotion1_Coll(Item_GObj* gobj)
{
    return false;
}

void it_802F289C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ftKb_SpecialN_800F5800(ip->grab_victim, &ip->pos);
}
