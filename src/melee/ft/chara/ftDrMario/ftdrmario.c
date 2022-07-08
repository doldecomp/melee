#include "ftdrmario.h"

void ftDrMario_OnDeath(HSD_GObj* gobj)
{
    Fighter* ft = (Fighter*)gobj->user_data;
    func_80074A4C(gobj, 0, 0);
    ft->sa.mario.x2234 = 0;
    ft->sa.mario.x2238 = 0;
    ft->sa.mario.x223C = 0;
    ft->sa.mario.x2240 = 0;
}

void ftDrMario_OnLoad(HSD_GObj* gobj)
{
    Fighter* ft;
    void** items;
    ftDrMarioAttributes* sa;
    int unused[2];

    ft = gobj->user_data;
    items = ft->x10C_ftData->x48_items;
    ftMario_OnLoadForDrMario(ft);
    sa = ft->x2D4_specialAttributes;
    func_8026B3F8(items[1], 0x31);
    func_8026B3F8(items[3], sa->x14);
}

void func_80149540(HSD_GObj* gobj)
{
    func_801497CC(gobj);
}

void ftDrMario_OnItemPickup(HSD_GObj* fighterObj, BOOL bool) {
    Fighter_OnItemPickup(fighterObj, bool, 1, 1);
}

void ftDrMario_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 1);
}

void ftDrMario_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 1);
}

void ftDrMario_OnItemDrop(HSD_GObj* gobj, BOOL bool1)
{
    Fighter_OnItemDrop(gobj, bool1, 1, 1);
}

void func_80149724(HSD_GObj* gobj)
{
    ftMario_func_800E0BE4(gobj);
}

void ftDrMario_OnKnockbackEnter(HSD_GObj* gobj)
{
    func_800704F0(gobj, 1, 3.0f);
    func_800704F0(gobj, 0, 3.0f);
}

void ftdrMario_OnKnockbackExit(HSD_GObj* gobj)
{
    func_800704F0(gobj, 1, 0.0f);
    func_800704F0(gobj, 0, 0.0f);
}

void func_801497CC(HSD_GObj* gobj)
{
    Fighter* ft;
    int unused[2];

    if (gobj != NULL) {
        ft = gobj->user_data;
        if (ft != NULL && ft->sa.mario.x2240 != 0) {
            func_802C0DBC(ft->sa.mario.x2240);
            ft->sa.mario.x2240 = 0;
        }
    }

    if (gobj != NULL) {
        ft = gobj->user_data;
        if (ft != NULL) {
            ft->cb.x21DC_callback_OnTakeDamage = 0;
            ft->cb.x21E4_callback_OnDeath2 = 0;
        }
    }
}

BOOL func_80149844(HSD_GObj* gobj)
{
    s32 tmp;
    Fighter* ft;

    if (gobj == NULL) {
        return TRUE;
    }
    ft = gobj->user_data;
    if (ft == NULL) {
        return TRUE;
    }
    tmp = ft->x10_action_state_index;
    if (tmp != 0x155 && tmp != 0x156) {
        return TRUE;
    }
    if (ft->sa.mario.x2240 == 0) {
        return TRUE;
    }
    return FALSE;
}

void func_801498A0(HSD_GObj* gobj)
{
    Fighter* ft;

    if (gobj != NULL) {
        ft = gobj->user_data;
        if (ft != NULL && ft->sa.mario.x2240 != 0) {
            ft->sa.mario.x2240 = 0;
        }
    }
    if (gobj != NULL) {
        ft = gobj->user_data;
        if (ft != NULL) {
            ft->cb.x21DC_callback_OnTakeDamage = 0;
            ft->cb.x21E4_callback_OnDeath2 = 0;
        }
    }
}

u32 func_801498EC(HSD_GObj* gobj)
{
    Fighter* ft;

    if (gobj != NULL) {
        ft = gobj->user_data;
        if (ft != NULL) {
            return ft->x2204_ftcmd_var1;
        }
    }

    return 0;
}

void func_80149910(HSD_GObj* gobj)
{
    Fighter* ft = gobj->user_data;

    func_800DEAE8(gobj, 0x155, 0x156);
    ft->x2200_ftcmd_var0 = 1;
    ft->x2204_ftcmd_var1 = 0;
}
