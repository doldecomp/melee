#include <melee/ft/chara/ftMario/ftmario.h>
#include <sysdolphin/baselib/random.h>

#include <melee/it/itkind.h>

extern s32 lbl_803C5A20[];

void ftMario_OnDeath(HSD_GObj* gobj) {
    Fighter* fp = getFighter(gobj);
    func_80074A4C(gobj, 0, 0);
    fp->sa.mario.x222C_vitaminCurr = 9;
    fp->sa.mario.x2230_vitaminPrev = 9;
    fp->sa.mario.x2234_tornadoCharge = FALSE;
    fp->sa.mario.x2238_isCapeBoost = FALSE;
    fp->sa.mario.x223C_capeGObj = NULL;
    fp->sa.mario.x2240 = 0;
}

void ftMario_OnLoadForDrMario(Fighter* fp) {
	PUSH_ATTRS(fp, ftMarioAttributes);
}

void ftMario_OnLoad(HSD_GObj* gobj) {
    ftData* ftDataInfo;
    void** items;
    ftMarioAttributes *sa;
    Fighter* fp = gobj->user_data;
    ftDataInfo = fp->x10C_ftData;
    items = ftDataInfo->x48_items;

    fp->x2224_flag.bits.b7 = 1;

    PUSH_ATTRS(fp, ftMarioAttributes);

    sa = (ftMarioAttributes*)fp->x2D4_specialAttributes;

    func_8026B3F8(items[0], It_Kind_Mario_Fire);
    func_8026B3F8(items[2], sa->x14_MARIO_CAPE_IT_KIND);
}

// 0x800E0A00
void ftMario_OnTakeDamage(HSD_GObj* gobj)
{
    ftMario_SpecialS_RemoveCape(gobj);
}

void ftMario_OnItemPickup(HSD_GObj* fighter_gobj, BOOL bool) {
    Fighter_OnItemPickup(fighter_gobj, bool, 1, 1);
}

void ftMario_OnItemInvisible(HSD_GObj* gobj) {
    Fighter_OnItemInvisible(gobj, 1);
}

void ftMario_OnItemVisible(HSD_GObj* gobj) {
    Fighter_OnItemVisible(gobj, 1);
}

void ftMario_OnItemDrop(HSD_GObj* gobj, BOOL bool1)
{
    Fighter_OnItemDrop(gobj, bool1, 1, 1);
}

void ftMario_LoadSpecialAttrs(HSD_GObj* gobj) {
    COPY_ATTRS(gobj, ftMarioAttributes);
}

void ftMario_OnKnockbackEnter(HSD_GObj* gobj) {
    Fighter_OnKnockbackEnter(gobj, 1);
}

void ftMario_OnKnockbackExit(HSD_GObj* gobj) {
    Fighter_OnKnockbackExit(gobj, 1);
}

void ftMario_func_800E0CAC(s32 arg0, u32* arg1, u32* arg2) {
    if (arg0 != 10) {
        if (arg0 >= 10)
            return;
        if (arg0 < 9)
            return;
        *arg2 = 0xe;
        *arg1 = 0xe;
    } else {
        *arg2 = 0xf;
        *arg1 = 0xf;
    }
}

s32 ftMario_func_800E0CE0(s32 arg0) {
    int offset;

    switch (arg0) {
        case 9:
            offset = 0xe;
            break;
        case 10:
            offset = 0xf;
    }

    return lbl_803C5A20[offset - 0xe];
}
