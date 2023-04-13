#include <platform.h>

#include <sysdolphin/baselib/random.h>
#include <melee/ft/chara/ftMario/ftmario.h>
#include <melee/ft/chara/ftMario/ftmario2.h>
#include <melee/ft/chara/ftMario/ftMario_SpecialN.h>
#include <melee/ft/ft_unknown_006.h>
#include <melee/ft/ftcamera.h>
#include <melee/ft/ftparts.h>
#include <melee/ft/types.h>
#include <melee/it/itkind.h>

ActionState ftMario_MotionStateTable[] = {
    { -1, 0, 0x01000000, NULL, NULL, NULL, NULL, NULL },
    { -1, 0, 0x01000000, NULL, NULL, NULL, NULL, NULL },
    { 295, 0x00340111, 0x12000000, ftMario_SpecialN_Anim,
      ftMario_SpecialN_IASA, ftMario_SpecialN_Phys, ftMario_SpecialN_Coll,
      ftCamera_UpdateCameraBox },
    { 296, 0x00340511, 0x12000000, ftMario_SpecialAirN_Anim,
      ftMario_SpecialAirN_IASA, ftMario_SpecialAirN_Phys,
      ftMario_SpecialAirN_Coll, ftCamera_UpdateCameraBox },
    { 297, 0x00341012, 0x13000000, ftMario_SpecialS_Anim,
      ftMario_SpecialS_IASA, ftMario_SpecialS_Phys, ftMario_SpecialS_Coll,
      ftCamera_UpdateCameraBox },
    { 298, 0x00341012, 0x13000000, ftMario_SpecialAirS_Anim,
      ftMario_SpecialAirS_IASA, ftMario_SpecialAirS_Phys,
      ftMario_SpecialAirS_Coll, ftCamera_UpdateCameraBox },
    { 299, 0x00340213, 0x14000000, ftMario_SpecialHi_Anim,
      ftMario_SpecialHi_IASA, ftMario_SpecialHi_Phys, ftMario_SpecialHi_Coll,
      ftCamera_UpdateCameraBox },
    { 300, 0x00340613, 0x14000000, ftMario_SpecialAirHi_Anim,
      ftMario_SpecialAirHi_IASA, ftMario_SpecialAirHi_Phys,
      ftMario_SpecialAirHi_Coll, ftCamera_UpdateCameraBox },
    { 301, 0x00340214, 0x15000000, ftMario_SpecialLw_Anim,
      ftMario_SpecialLw_IASA, ftMario_SpecialLw_Phys, ftMario_SpecialLw_Coll,
      ftCamera_UpdateCameraBox },
    { 302, 0x00340614, 0x15000000, ftMario_SpecialAirLw_Anim,
      ftMario_SpecialAirLw_IASA, ftMario_SpecialAirLw_Phys,
      ftMario_SpecialAirLw_Coll, ftCamera_UpdateCameraBox },
};

ActionState lbl_803C7260[] = {
    { 14, 0, 0x01000000, NULL, NULL, ft_800C7158, NULL, NULL },
    { 15, 0, 0x01000000, NULL, NULL, ft_800C7200, NULL, NULL },
};

void ftMario_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftParts_80074A4C(gobj, 0, 0);
    fp->ev.mr.x222C_vitaminCurr = 9;
    fp->ev.mr.x2230_vitaminPrev = 9;
    fp->ev.mr.x2234_tornadoCharge = false;
    fp->ev.mr.x2238_isCapeBoost = false;
    fp->ev.mr.x223C_capeGObj = NULL;
    fp->ev.mr.x2240 = 0;
}

void ftMario_OnLoadForDrMario(Fighter* fp)
{
    PUSH_ATTRS(fp, ftMarioAttributes);
}

void ftMario_OnLoad(HSD_GObj* gobj)
{
    ftData* ftDataInfo;
    void** items;
    ftMarioAttributes* sa;
    Fighter* fp = gobj->user_data;
    ftDataInfo = fp->x10C_ftData;
    items = ftDataInfo->x48_items;

    fp->x2224_flag.bits.b7 = 1;

    PUSH_ATTRS(fp, ftMarioAttributes);

    sa = (ftMarioAttributes*) fp->x2D4_specialAttributes;

    it_8026B3F8(items[0], It_Kind_Mario_Fire);
    it_8026B3F8(items[2], sa->x14_MARIO_CAPE_IT_KIND);
}

// 0x800E0A00
void ftMario_OnTakeDamage(HSD_GObj* gobj)
{
    ftMario_SpecialS_RemoveCape(gobj);
}

void ftMario_OnItemPickup(HSD_GObj* fighter_gobj, bool bool)
{
    Fighter_OnItemPickup(fighter_gobj, bool, 1, 1);
}

void ftMario_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 1);
}

void ftMario_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 1);
}

void ftMario_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    Fighter_OnItemDrop(gobj, bool1, 1, 1);
}

void ftMario_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftMarioAttributes);
}

void ftMario_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, 1);
}

void ftMario_OnKnockbackExit(HSD_GObj* gobj)
{
    Fighter_OnKnockbackExit(gobj, 1);
}

void ftMario_800E0CAC(s32 arg0, s32* arg1, s32* arg2)
{
    if (arg0 != 10) {
        if (arg0 >= 10) {
            return;
        }
        if (arg0 < 9) {
            return;
        }
        *arg2 = 0xe;
        *arg1 = 0xe;
    } else {
        *arg2 = 0xf;
        *arg1 = 0xf;
    }
}

unk_t ftMario_GetMotionFileString(enum_t arg0)
{
    int offset;

    switch (arg0) {
    case 9:
        offset = 14;
        break;
    case 10:
        offset = 15;
    }

    return ftMario_DemoViMotionFilenames[offset - 0xe];
}
