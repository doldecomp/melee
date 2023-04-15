#include "ftsamus1.h"

#include "ftsamus.h"
#include "ftsamus3.h"
#include "ftsamus4.h"
#include "types.h"

#include "ft/ft_0877.h"
#include "ft/ftcamera.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "lb/lb_00B0.h"

#include <dolphin/mtx/types.h>

MotionState ftSs_Init_MotionStateTable[] = {
    { 295, 0, 0x01000000, ftSs_Unk2_80128C04, ftSs_Unk2_80128D3C,
      ftSs_Unk2_80128E88, ftSs_Unk2_80128F60, ftCamera_UpdateCameraBox },
    { 296, 0, 0x01000000, ftSs_Unk2_80128CA0, ftSs_Unk2_80128E68,
      ftSs_Unk2_80128EF8, ftSs_Unk2_80128FD4, ftCamera_UpdateCameraBox },
    { 297, 0x00340111, 0x12000000, ftSs_Unk3_80129684, ftSs_Unk3_80129B18,
      ftSs_Unk3_80129C88, ftSs_Unk3_80129D48, ftCamera_UpdateCameraBox },
    { 298, 0x00340111, 0x12000000, ftSs_Unk3_80129774, ftSs_Unk3_80129B1C,
      ftSs_Unk3_80129CA8, ftSs_Unk3_80129DC8, ftCamera_UpdateCameraBox },
    { 299, 0x00340111, 0x12000000, ftSs_Unk3_80129940, ftSs_Unk3_80129C78,
      ftSs_Unk3_80129CC8, ftSs_Unk3_80129E68, ftCamera_UpdateCameraBox },
    { 300, 0x00340111, 0x12000000, ftSs_Unk3_801299D0, ftSs_Unk3_80129C7C,
      ftSs_Unk3_80129CE8, ftSs_Unk3_80129EE8, ftCamera_UpdateCameraBox },
    { 301, 0x00340511, 0x12000000, ftSs_Unk3_80129A14, ftSs_Unk3_80129C80,
      ftSs_Unk3_80129D08, ftSs_Unk3_80129F68, ftCamera_UpdateCameraBox },
    { 302, 0x00340511, 0x12000000, ftSs_Unk3_80129A98, ftSs_Unk3_80129C84,
      ftSs_Unk3_80129D28, ftSs_Unk3_80129FE8, ftCamera_UpdateCameraBox },
    { 303, 0x00340112, 0x13000000, ftSs_Unk4_8012A380, ftSs_Unk4_8012A3F8,
      ftSs_Unk4_8012A400, ftSs_Unk4_8012A468, ftCamera_UpdateCameraBox },
    { 304, 0x00340912, 0x13000000, ftSs_Unk4_8012A4E0, ftSs_Unk4_8012A558,
      ftSs_Unk4_8012A560, ftSs_Unk4_8012A5C8, ftCamera_UpdateCameraBox },
    { 305, 0x00340512, 0x13000000, ftSs_Unk4_8012A3BC, ftSs_Unk4_8012A3FC,
      ftSs_Unk4_8012A420, ftSs_Unk4_8012A4A4, ftCamera_UpdateCameraBox },
    { 306, 0x00340D12, 0x13000000, ftSs_Unk4_8012A51C, ftSs_Unk4_8012A55C,
      ftSs_Unk4_8012A580, ftSs_Unk4_8012A604, ftCamera_UpdateCameraBox },
    { 307, 0x00340213, 0x14000000, ftSs_Unk5_8012A81C, ftSs_Unk5_8012A96C,
      ftSs_Unk5_8012AB0C, ftSs_Unk5_8012AC00, ftCamera_UpdateCameraBox },
    { 308, 0x00340613, 0x14000000, ftSs_Unk5_8012A8C4, ftSs_Unk5_8012AA3C,
      ftSs_Unk5_8012ABB4, ftSs_Unk5_8012ACF8, ftCamera_UpdateCameraBox },
    { 309, 0x00340114, 0x15000000, ftSs_Unk6_8012B150, ftSs_Unk6_8012B358,
      ftSs_Unk6_8012B3A8, ftSs_Unk6_8012B488, ftCamera_UpdateCameraBox },
    { 310, 0x00340514, 0x15000000, ftSs_Unk6_8012B264, ftSs_Unk6_8012B3A4,
      ftSs_Unk6_8012B41C, ftSs_Unk6_8012B4FC, ftCamera_UpdateCameraBox },
    { 311, 0x00200000, 0x01000000, ftLk_0877_800C3D6C, ftLk_0877_800C4384,
      ftLk_0877_800C438C, ftLk_0877_800C447C, ftCamera_UpdateCameraBox },
    { 312, 0x00C00000, 0x01000000, ftLk_0877_800C4380, ftLk_0877_800C4388,
      ftLk_0877_800C4438, ftLk_80082B78, ftCamera_UpdateCameraBox },
};

char ftSs_Init_DatFilename[] = "PlSs.dat";
char ftSs_Init_DataName[] = "ftDataSamus";
char ftSs_Init_803CE528[] = "PlSsNr.dat";
char ftSs_Init_803CE534[] = "PlySamus5K_Share_joint";
char ftSs_Init_803CE54C[] = "PlSsPi.dat";
char ftSs_Init_803CE558[] = "PlySamus5KPi_Share_joint";
char ftSs_Init_803CE574[] = "PlSsBk.dat";
char ftSs_Init_803CE580[] = "PlySamus5KBk_Share_joint";
char ftSs_Init_803CE59C[] = "PlSsGr.dat";
char ftSs_Init_803CE5A8[] = "PlySamus5KGr_Share_joint";
char ftSs_Init_803CE5C4[] = "PlSsLa.dat";
char ftSs_Init_803CE5D0[] = "PlySamus5KLa_Share_joint";
char ftSs_Init_AnimDatFilename[] = "PlSsAJ.dat";

Fighter_DemoStrings ftSs_Init_DemoMotionFilenames = {
    "ftDemoResultMotionFileSamus",
    "ftDemoIntroMotionFileSamus",
    "ftDemoEndingMotionFileSamus",
    "ftDemoViWaitMotionFileSamus",
};

Fighter_CostumeStrings ftSs_Init_CostumeStrings[] = {
    { ftSs_Init_803CE528, ftSs_Init_803CE534, NULL },
    { ftSs_Init_803CE54C, ftSs_Init_803CE558, NULL },
    { ftSs_Init_803CE574, ftSs_Init_803CE580, NULL },
    { ftSs_Init_803CE59C, ftSs_Init_803CE5A8, NULL },
    { ftSs_Init_803CE5C4, ftSs_Init_803CE5D0, NULL },
};

void ftSs_Init_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftParts_80074A4C(gobj, 0, 0);
    fp->fv.ss.x222C = 0;
    fp->fv.ss.x2230 = 0;
    fp->fv.ss.x2238 = 0;
    fp->fv.ss.x2244 = 0;
    fp->fv.ss.x223C = 0;
    fp->fv.ss.x2240 = 0;
}

void ftSs_Init_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    void** item_list = fp->ft_data->x48_items;

    fp->x2224_flag.bits.b7 = 1;

    PUSH_ATTRS(fp, ftSamusAttributes);

    it_8026B3F8(item_list[0], 0x5DU);
    it_8026B3F8(item_list[1], 0x5EU);
    it_8026B3F8(item_list[2], 0x5FU);
    it_8026B3F8(item_list[3], 0x60U);
}

void ftSs_Init_80128428(HSD_GObj* gobj)
{
    ftSs_Unk3_80129258(gobj);
    ftSs_Unk4_8012A640(gobj);
    ft_800D9C98(gobj);
}

void ftSs_Init_OnItemPickup(HSD_GObj* gobj, bool bool)
{
    Fighter_OnItemPickup(gobj, bool, 0, 0);
}

void ftSs_Init_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 0);
}

void ftSs_Init_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 0);
}

void ftSs_Init_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    Fighter_OnItemDrop(gobj, bool1, 0, 0);
}

void ftSs_Init_UnkMotionStates4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSamusAttributes* attr = fp->x2D4_specialAttributes;
    s32 samus_x2230 = fp->fv.ss.x2230;
    if (samus_x2230 == attr->x18) {
        ft_800BFFD0(fp, 0x35, 0);
    }
}

void ftSs_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftSamusAttributes);
    if (fp->x34_scale.y != 1.0f) {
        sA2->x8 *= fp->x34_scale.y;
        sA2->x74_vec.y *= fp->x34_scale.y;
        sA2->x54 *= fp->x34_scale.y;
        sA2->x58 *= fp->x34_scale.y;
        SCALE_HEIGHT_ATTRS(6);
    }
}

void ftSs_Init_80128770(HSD_AObj* gobj, f32 rate)
{
    if (gobj && !(HSD_AObjGetFlags(gobj) & 0x20000000)) {
        HSD_AObjSetRate(gobj, rate);
    }
}

void ftSs_Init_CreateThrowGrappleBeam(HSD_GObj* gobj, s32 motion_state,
                                      f32 anim_speed)
{
    Fighter* fighter_copy;
    Vec3 scale;

    Fighter* fp = getFighter(gobj);
    void** item_list = fp->ft_data->x48_items;
    struct UNK_SAMUS_S1* beam = item_list[4];
    ftCommon_SetAccessory(fp, beam->x0_joint);

    scale.x = scale.y = scale.z = fp->x34_scale.y;
    HSD_JObjSetScale((fighter_copy = fp)->x20A0_accessory, &scale);

    HSD_JObjAddAnimAll(fighter_copy->x20A0_accessory, beam->x8_anim_joint,
                       beam->xC_matanim_joint, 0);
    HSD_JObjAddAnimAll(fighter_copy->x20A0_accessory,
                       beam->x4_anim_joints[motion_state - ftCo_MS_ThrowF], 0,
                       0);
    HSD_ForeachAnim(fighter_copy->x20A0_accessory, JOBJ_TYPE,
                    ALL_TYPE_MASK & ~TOBJ_MASK & ~MOBJ_MASK,
                    &ftSs_Init_80128770, AOBJ_ARG_AF, anim_speed);
    HSD_JObjReqAnimAll(fighter_copy->x20A0_accessory, 0.0f);
    HSD_JObjAnimAll(fighter_copy->x20A0_accessory);
    lb_8000C2F8(fighter_copy->x20A0_accessory,
                fighter_copy->ft_bones[ThrowN].x0_jobj);
}
