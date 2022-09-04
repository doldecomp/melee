#include <melee/ft/chara/ftKoopa/ftkoopa.h>
#include <melee/ft/chara/ftGigaKoopa/ftgigakoopa.h>

#include <melee/it/itkind.h>

void ftGKoopa_OnDeath(HSD_GObj* fighter_gobj) {
    s32 unused[2];
    Fighter* fp = fighter_gobj->user_data;
    ftKoopaAttributes* koopaAttr = fp->x2D4_specialAttributes;

    func_80074A4C(fighter_gobj, 0, 0);
    fp->dmg.x18B0 = koopaAttr->x0;
    fp->sa.gkoopa.x222C = koopaAttr->x10;
    fp->sa.gkoopa.x2230 = koopaAttr->x18;
}

#pragma peephole on

void func_8014F698(HSD_GObj* gobj)
{
    func_80132A64(gobj);
}

void ftGKoopa_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftData* ftdata = fp->x10C_ftData;
    void** items = ftdata->x48_items;

    ftKoopa_OnLoadForGKoopa(fp);
    func_8026B3F8(items[0], It_Kind_Koopa_Flame);

    fp->x2226_flag.bits.b1 = 1;
    fp->x222A_flag.bits.b0 = 1;
}

void ftGKoopa_OnItemPickup(HSD_GObj* fighter_gobj, BOOL bool) {
    Fighter_OnItemPickup(fighter_gobj, bool, 1, 1);
}

void ftGKoopa_OnItemInvisible(HSD_GObj* gobj) {
    Fighter_OnItemInvisible(gobj, 1);
}

void ftGKoopa_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 1);
}

void ftGKoopa_OnItemDrop(HSD_GObj* gobj, BOOL bool1)
{
    Fighter_OnItemDrop(gobj, bool1, 1, 1);
}

void ftGKoopa_LoadSpecialAttrs(HSD_GObj* gobj)
{
    ftKoopa_LoadSpecialAttrs(gobj);
}

void ftGKoopa_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, 1);
}

void ftGKoopa_OnKnockbackExit(HSD_GObj* gobj)
{
    Fighter_OnKnockbackExit(gobj, 1);
}

void func_8014F98C(s32 arg0, s32* arg1, s32* arg2)
{
    if (arg0 == 0xF) {
        *arg2 = 0xE;
        *arg1 = 0xE;
    }
}

// UB warning: this function may use offset uninitialized
s32 func_8014F9A4(s32 arg0)
{
    int offset;
    const s32* ret;

    switch (arg0) {
        case 0xf:
            offset = 0xe;
    }

    return lbl_803D3984[offset - 0xe];
}
