#include <melee/ft/chara/ftDrMario/ftdrmario.h>

void ftDrMario_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = (Fighter*)gobj->user_data;
    func_80074A4C(gobj, 0, 0);
    fp->sa.mario.x2234_tornadoCharge = 0;
    fp->sa.mario.x2238_isCapeBoost = FALSE;
    fp->sa.mario.x223C_capeGObj = NULL;
    fp->sa.mario.x2240 = 0;
}

void ftDrMario_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp;
    void** items;
    ftDrMarioAttributes* sa;
    int unused[2];

    fp = gobj->user_data;
    items = fp->x10C_ftData->x48_items;
    ftMario_OnLoadForDrMario(fp);
    sa = fp->x2D4_specialAttributes;
    func_8026B3F8(items[1], 0x31);
    func_8026B3F8(items[3], sa->x14);
}

void func_80149540(HSD_GObj* gobj)
{
    func_801497CC(gobj);
}

void ftDrMario_OnItemPickup(HSD_GObj* fighter_gobj, BOOL bool) {
    Fighter_OnItemPickup(fighter_gobj, bool, 1, 1);
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

void ftDrMario_LoadSpecialAttrs(HSD_GObj* gobj)
{
    ftMario_LoadSpecialAttrs(gobj);
}

void ftDrMario_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, 1);
}

void ftDrMario_OnKnockbackExit(HSD_GObj* gobj)
{
    Fighter_OnKnockbackExit(gobj, 1);
}

void func_801497CC(HSD_GObj* gobj)
{
    Fighter* fp;
    int unused[2];

    if (gobj != NULL) {
        fp = gobj->user_data;
        if (fp != NULL && fp->sa.mario.x2240 != 0) {
            func_802C0DBC(fp->sa.mario.x2240);
            fp->sa.mario.x2240 = 0;
        }
    }

    if (gobj != NULL) {
        fp = gobj->user_data;
        if (fp != NULL) {
            fp->cb.x21DC_callback_OnTakeDamage = 0;
            fp->cb.x21E4_callback_OnDeath2 = 0;
        }
    }
}

BOOL func_80149844(HSD_GObj* gobj)
{
    s32 tmp;
    Fighter* fp;

    if (gobj == NULL) {
        return TRUE;
    }
    fp = gobj->user_data;
    if (fp == NULL) {
        return TRUE;
    }
    tmp = fp->x10_action_state_index;
    if (tmp != 0x155 && tmp != 0x156) {
        return TRUE;
    }
    if (fp->sa.mario.x2240 == 0) {
        return TRUE;
    }
    return FALSE;
}

void func_801498A0(HSD_GObj* gobj)
{
    Fighter* fp;

    if (gobj != NULL) {
        fp = gobj->user_data;
        if (fp != NULL && fp->sa.mario.x2240 != 0) {
            fp->sa.mario.x2240 = 0;
        }
    }
    if (gobj != NULL) {
        fp = gobj->user_data;
        if (fp != NULL) {
            fp->cb.x21DC_callback_OnTakeDamage = 0;
            fp->cb.x21E4_callback_OnDeath2 = 0;
        }
    }
}

u32 func_801498EC(HSD_GObj* gobj)
{
    Fighter* fp;

    if (gobj != NULL) {
        fp = gobj->user_data;
        if (fp != NULL) {
            return fp->x2204_ftcmd_var1;
        }
    }

    return 0;
}

void func_80149910(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    func_800DEAE8(gobj, 0x155, 0x156);
    fp->x2200_ftcmd_var0 = 1;
    fp->x2204_ftcmd_var1 = 0;
}
