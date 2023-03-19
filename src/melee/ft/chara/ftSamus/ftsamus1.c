#include <melee/ft/chara/ftSamus/ftsamus1.h>

#include <melee/ft/chara/ftSamus/ftsamus.h>
#include <melee/ft/chara/ftSamus/ftsamus3.h>
#include <melee/ft/chara/ftSamus/ftsamus4.h>
#include <melee/ft/ft_unknown_006.h>
#include <melee/ft/ftcamera.h>
#include <melee/ft/ftparts.h>
#include <melee/ft/types.h>
#include <melee/lb/lbunknown_001.h>

ActionState as_table_samus[] = {
    { 295, 0, 0x01000000, ftSamus_80128C04, ftSamus_80128D3C, ftSamus_80128E88,
      ftSamus_80128F60, func_800761C8 },
    { 296, 0, 0x01000000, ftSamus_80128CA0, ftSamus_80128E68, ftSamus_80128EF8,
      ftSamus_80128FD4, func_800761C8 },
    { 297, 0x00340111, 0x12000000, ftSamus_80129684, ftSamus_80129B18,
      ftSamus_80129C88, ftSamus_80129D48, func_800761C8 },
    { 298, 0x00340111, 0x12000000, ftSamus_80129774, ftSamus_80129B1C,
      ftSamus_80129CA8, ftSamus_80129DC8, func_800761C8 },
    { 299, 0x00340111, 0x12000000, ftSamus_80129940, ftSamus_80129C78,
      ftSamus_80129CC8, ftSamus_80129E68, func_800761C8 },
    { 300, 0x00340111, 0x12000000, ftSamus_801299D0, ftSamus_80129C7C,
      ftSamus_80129CE8, ftSamus_80129EE8, func_800761C8 },
    { 301, 0x00340511, 0x12000000, ftSamus_80129A14, ftSamus_80129C80,
      ftSamus_80129D08, ftSamus_80129F68, func_800761C8 },
    { 302, 0x00340511, 0x12000000, ftSamus_80129A98, ftSamus_80129C84,
      ftSamus_80129D28, ftSamus_80129FE8, func_800761C8 },
    { 303, 0x00340112, 0x13000000, ftSamus_8012A380, ftSamus_8012A3F8,
      ftSamus_8012A400, ftSamus_8012A468, func_800761C8 },
    { 304, 0x00340912, 0x13000000, ftSamus_8012A4E0, ftSamus_8012A558,
      ftSamus_8012A560, ftSamus_8012A5C8, func_800761C8 },
    { 305, 0x00340512, 0x13000000, ftSamus_8012A3BC, ftSamus_8012A3FC,
      ftSamus_8012A420, ftSamus_8012A4A4, func_800761C8 },
    { 306, 0x00340D12, 0x13000000, ftSamus_8012A51C, ftSamus_8012A55C,
      ftSamus_8012A580, ftSamus_8012A604, func_800761C8 },
    { 307, 0x00340213, 0x14000000, ftSamus_8012A81C, ftSamus_8012A96C,
      ftSamus_8012AB0C, ftSamus_8012AC00, func_800761C8 },
    { 308, 0x00340613, 0x14000000, ftSamus_8012A8C4, ftSamus_8012AA3C,
      ftSamus_8012ABB4, ftSamus_8012ACF8, func_800761C8 },
    { 309, 0x00340114, 0x15000000, ftSamus_8012B150, ftSamus_8012B358,
      ftSamus_8012B3A8, ftSamus_8012B488, func_800761C8 },
    { 310, 0x00340514, 0x15000000, ftSamus_8012B264, ftSamus_8012B3A4,
      ftSamus_8012B41C, ftSamus_8012B4FC, func_800761C8 },
    { 311, 0x00200000, 0x01000000, func_800C3D6C, func_800C4384, func_800C438C,
      func_800C447C, func_800761C8 },
    { 312, 0x00C00000, 0x01000000, func_800C4380, func_800C4388, func_800C4438,
      func_80082B78, func_800761C8 },
};

char lbl_803CE510[] = "PlSs.dat";
char lbl_803CE51C[] = "ftDataSamus";
char lbl_803CE528[] = "PlSsNr.dat";
char lbl_803CE534[] = "PlySamus5K_Share_joint";
char lbl_803CE54C[] = "PlSsPi.dat";
char lbl_803CE558[] = "PlySamus5KPi_Share_joint";
char lbl_803CE574[] = "PlSsBk.dat";
char lbl_803CE580[] = "PlySamus5KBk_Share_joint";
char lbl_803CE59C[] = "PlSsGr.dat";
char lbl_803CE5A8[] = "PlySamus5KGr_Share_joint";
char lbl_803CE5C4[] = "PlSsLa.dat";
char lbl_803CE5D0[] = "PlySamus5KLa_Share_joint";
char lbl_803CE5EC[] = "PlSsAJ.dat";

Fighter_DemoStrings lbl_803CE668 = {
    "ftDemoResultMotionFileSamus",
    "ftDemoIntroMotionFileSamus",
    "ftDemoEndingMotionFileSamus",
    "ftDemoViWaitMotionFileSamus",
};

Fighter_CostumeStrings lbl_803CE678[] = {
    { lbl_803CE528, lbl_803CE534, NULL }, { lbl_803CE54C, lbl_803CE558, NULL },
    { lbl_803CE574, lbl_803CE580, NULL }, { lbl_803CE59C, lbl_803CE5A8, NULL },
    { lbl_803CE5C4, lbl_803CE5D0, NULL },
};

void ftSamus_OnDeath(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    func_80074A4C(fighter_gobj, 0, 0);
    fp->ev.ss.x222C = 0;
    fp->ev.ss.x2230 = 0;
    fp->ev.ss.x2238 = 0;
    fp->ev.ss.x2244 = 0;
    fp->ev.ss.x223C = 0;
    fp->ev.ss.x2240 = 0;
}

void ftSamus_OnLoad(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    void** item_list = fp->x10C_ftData->x48_items;

    fp->x2224_flag.bits.b7 = 1;

    PUSH_ATTRS(fp, ftSamusAttributes);

    func_8026B3F8(item_list[0], 0x5DU);
    func_8026B3F8(item_list[1], 0x5EU);
    func_8026B3F8(item_list[2], 0x5FU);
    func_8026B3F8(item_list[3], 0x60U);
}

void ftSamus_80128428(HSD_GObj* fighter_gobj)
{
    ftSamus_80129258(fighter_gobj);
    ftSamus_8012A640(fighter_gobj);
    func_800D9C98(fighter_gobj);
}

void ftSamus_OnItemPickup(HSD_GObj* fighter_gobj, bool bool)
{
    Fighter_OnItemPickup(fighter_gobj, bool, 0, 0);
}

void ftSamus_OnItemInvisible(HSD_GObj* fighter_gobj)
{
    Fighter_OnItemInvisible(fighter_gobj, 0);
}

void ftSamus_OnItemVisible(HSD_GObj* fighter_gobj)
{
    Fighter_OnItemVisible(fighter_gobj, 0);
}

void ftSamus_OnItemDrop(HSD_GObj* fighter_gobj, bool bool1)
{
    Fighter_OnItemDrop(fighter_gobj, bool1, 0, 0);
}

void ftSamus_80128628(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftSamusAttributes* attr = fp->x2D4_specialAttributes;
    s32 samus_x2230 = fp->ev.ss.x2230;
    if (samus_x2230 == attr->x18) {
        func_800BFFD0(fp, 0x35, 0);
    }
}

void ftSamus_LoadSpecialAttrs(HSD_GObj* fighter_gobj)
{
    COPY_ATTRS(fighter_gobj, ftSamusAttributes);
    if (fp->x34_scale.y != 1.0f) {
        sA2->x8 *= fp->x34_scale.y;
        sA2->x74_vec.y *= fp->x34_scale.y;
        sA2->x54 *= fp->x34_scale.y;
        sA2->x58 *= fp->x34_scale.y;
        SCALE_HEIGHT_ATTRS(6);
    }
}

void ftSamus_80128770(HSD_AObj* fighter_gobj, f32 rate)
{
    if (fighter_gobj && !(HSD_AObjGetFlags(fighter_gobj) & 0x20000000)) {
        HSD_AObjSetRate(fighter_gobj, rate);
    }
}

void ftSamus_CreateThrowGrappleBeam(HSD_GObj* fighter_gobj, s32 action_state,
                                    f32 anim_speed)
{
    Fighter* fighter_copy;
    Vec3 scale;

    Fighter* fp = getFighter(fighter_gobj);
    void** item_list = fp->x10C_ftData->x48_items;
    struct UNK_SAMUS_S1* beam = item_list[4];
    Fighter_SetAccessory(fp, beam->x0_joint);

    scale.x = scale.y = scale.z = fp->x34_scale.y;
    HSD_JObjSetScale((fighter_copy = fp)->x20A0_accessory, &scale);

    HSD_JObjAddAnimAll(fighter_copy->x20A0_accessory, beam->x8_anim_joint,
                       beam->xC_matanim_joint, 0);
    HSD_JObjAddAnimAll(fighter_copy->x20A0_accessory,
                       beam->x4_anim_joints[action_state - ASID_THROWF], 0, 0);
    HSD_ForeachAnim(fighter_copy->x20A0_accessory, JOBJ_TYPE,
                    ALL_TYPE_MASK & ~TOBJ_MASK & ~MOBJ_MASK, &ftSamus_80128770,
                    AOBJ_ARG_AF, anim_speed);
    HSD_JObjReqAnimAll(fighter_copy->x20A0_accessory, 0.0f);
    HSD_JObjAnimAll(fighter_copy->x20A0_accessory);
    func_8000C2F8(fighter_copy->x20A0_accessory,
                  fighter_copy->x5E8_fighterBones[ThrowN].x0_jobj);
}
