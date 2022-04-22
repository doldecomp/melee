#include "ftpeach.h"

#include <melee/it/id.h>

typedef struct _PairStruct {
    f32 unk0;
    f32 unk4;
    u8 padding[0xB8];
} PairStruct;

void ftPeach_OnDeath(HSD_GObj* gobj)
{
    Fighter* ft;

    ft = gobj->user_data;
    ft->sa.peach.x222C = 1;
    ft->sa.peach.x2234 = -1;
    ft->sa.peach.x2240 = 0;
    ft->sa.peach.x223C = 0;
    ft->sa.peach.x2238 = 0;
    ft->sa.peach.x2244 = 0;
    ft->sa.peach.x2248 = 0;
    func_80074A4C(gobj, 0, 0);
    func_80074A4C(gobj, 2, 0);
    func_80074A4C(gobj, 3, -1);
    func_80074A4C(gobj, 4, 0);

    switch (ft->x619_costume_id)
    {
        case 1:
            func_80074A4C(gobj, 1, -1);
            func_80074A4C(gobj, 5, 0);
            func_80074A4C(gobj, 6, -1);
            break;

        default:
            func_80074A4C(gobj, 1, 0);
            func_80074A4C(gobj, 5, -1);
            func_80074A4C(gobj, 6, 0);
            break;
    }
}

void ftPeach_OnLoad(HSD_GObj* gobj)
{
    Fighter* player = gobj->user_data;
    ftData* ftDataInfo = player->x10C_ftData;
    PairStruct* extAtrrs = (PairStruct*)ftDataInfo->ext_attr;
    void** items = ftDataInfo->x48_items;

    extAtrrs->unk0 = func_8001E8F8(func_80085E50(player, 18));
    extAtrrs->unk4 = func_8001E8F8(func_80085E50(player, 19));

    {
        PairStruct *dest = (PairStruct *)player->x2D8_specialAttributes2;
        PairStruct *src = (PairStruct *)player->x10C_ftData->ext_attr;
        u32 *attr = (u32 *)&player->x2D4_specialAttributes;
        *dest = *src;
        *attr = (u32)dest;
    }
    
    func_8026B3F8(items[0], It_Kind_PeachUnk);
    func_8026B3F8(items[1], It_Kind_PeachTurnip);
    func_8026B3F8(items[2], It_Kind_PeachParasol);
    func_8026B3F8(items[3], It_Kind_PeachToad);
    func_8026B3F8(items[4], It_Kind_PeachToadSpore);
}
