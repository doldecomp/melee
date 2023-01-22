#include <melee/ft/chara/ftPurin/ftpurin.h>

#include <melee/ft/chara/ftPurin/ftpurin.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ft_unknown_005.h>
#include <melee/ft/ft_unknown_006.h>
#include <melee/ft/ftcamera.h>
#include <melee/ft/ftparts.h>
#include <melee/ft/types.h>
#include <melee/it/item2.h>

ActionState as_table_purin[] = {
    { 295, FLAGS_ZERO, 0x01000000, func_800D7590, func_800D7614, func_800D7634,
      func_800D767C, func_800761C8 },
    { 296, FLAGS_ZERO, 0x01000000, func_800D7590, func_800D7614, func_800D7634,
      func_800D767C, func_800761C8 },
    { 297, FLAGS_ZERO, 0x01000000, func_800D7590, func_800D7614, func_800D7634,
      func_800D767C, func_800761C8 },
    { 298, FLAGS_ZERO, 0x01000000, func_800D7590, func_800D7614, func_800D7634,
      func_800D767C, func_800761C8 },
    { 299, FLAGS_ZERO, 0x01000000, func_800D7590, func_800D7614, func_800D7634,
      func_800D767C, func_800761C8 },
    { 300, 0x00340211, 0x12000000, lbl_8013E014, lbl_8013FF00, lbl_80140620,
      lbl_80140FA4, func_800761C8 },
    { 301, 0x00340211, 0x12000000, lbl_8013E014, lbl_8013FF00, lbl_80140620,
      lbl_80140FA4, func_800761C8 },
    { 302, 0x003C0211, 0x12000000, lbl_8013E0F0, lbl_8013FF04, lbl_80140650,
      lbl_80141054, func_800761C8 },
    { 303, 0x003C0211, 0x12000000, lbl_8013E2A0, lbl_80140064, lbl_80140680,
      lbl_80141154, func_800761C8 },
    { 304, 0x00340211, 0x12000000, lbl_8013E410, lbl_801401C4, lbl_801406B0,
      lbl_80141254, func_800761C8 },
    { 305, 0x00340211, 0x12000000, lbl_8013E7E0, lbl_80140344, lbl_801408B8,
      lbl_801415F4, func_800761C8 },
    { 306, 0x00340211, 0x12000000, lbl_8013EAD8, lbl_80140348, lbl_80140BAC,
      lbl_801416D0, func_800761C8 },
    { 307, 0x00340211, 0x12000000, lbl_8013EAD8, lbl_80140348, lbl_80140BAC,
      lbl_801416D0, func_800761C8 },
    { 308, 0x00340611, 0x12000000, lbl_8013EDB0, lbl_8014034C, lbl_80140BE8,
      lbl_80141730, func_800761C8 },
    { 309, 0x00340611, 0x12000000, lbl_8013EDB0, lbl_8014034C, lbl_80140BE8,
      lbl_80141730, func_800761C8 },
    { 310, 0x003C0611, 0x12000000, lbl_8013EE84, lbl_80140350, lbl_80140C18,
      lbl_801417E0, func_800761C8 },
    { 311, 0x003C0611, 0x12000000, lbl_8013F034, lbl_801404B0, lbl_80140C48,
      lbl_801418E0, func_800761C8 },
    { 312, 0x00340611, 0x12000000, lbl_8013F1A4, lbl_80140610, lbl_80140C78,
      lbl_801419E0, func_800761C8 },
    { 313, 0x00340211, 0x12000000, lbl_8013F708, lbl_80140614, lbl_80140DF8,
      lbl_80141FB8, func_800761C8 },
    { 314, 0x00340611, 0x12000000, lbl_8013F9C0, lbl_80140618, lbl_80140F10,
      lbl_80142070, func_800761C8 },
    { 315, 0x00340611, 0x12000000, lbl_8013F9C0, lbl_80140618, lbl_80140F10,
      lbl_80142070, func_800761C8 },
    { 316, 0x00340611, 0x12000000, lbl_8013FCAC, lbl_8014061C, lbl_80140F40,
      lbl_801420D0, func_800761C8 },
    { 317, 0x00340212, 0x13000000, lbl_8013D30C, lbl_8013D384, lbl_8013D38C,
      lbl_8013D518, func_800761C8 },
    { 318, 0x00340612, 0x13000000, lbl_8013D348, lbl_8013D388, lbl_8013D3AC,
      lbl_8013D554, func_800761C8 },
    { 319, 0x00340013, 0x14000000, lbl_8013CB68, lbl_8013CC60, lbl_8013CC68,
      lbl_8013CCA8, func_800761C8 },
    { 320, 0x00340413, 0x14000000, lbl_8013CBE4, lbl_8013CC64, lbl_8013CC88,
      lbl_8013CCE4, func_800761C8 },
    { 321, 0x00340013, 0x14000000, lbl_8013CB68, lbl_8013CC60, lbl_8013CC68,
      lbl_8013CCA8, func_800761C8 },
    { 322, 0x00340413, 0x14000000, lbl_8013CBE4, lbl_8013CC64, lbl_8013CC88,
      lbl_8013CCE4, func_800761C8 },
    { 323, 0x00340014, 0x15000000, lbl_8013CFCC, lbl_8013D044, lbl_8013D04C,
      lbl_8013D08C, func_800761C8 },
    { 324, 0x00340414, 0x15000000, lbl_8013D008, lbl_8013D048, lbl_8013D06C,
      lbl_8013D0C8, func_800761C8 },
    { 325, 0x00340014, 0x15000000, lbl_8013CFCC, lbl_8013D044, lbl_8013D04C,
      lbl_8013D08C, func_800761C8 },
    { 326, 0x00340414, 0x15000000, lbl_8013D008, lbl_8013D048, lbl_8013D06C,
      lbl_8013D0C8, func_800761C8 },
};

char lbl_803D02F0[] = "PlPr.dat";
char lbl_803D02FC[] = "ftDataPurin";
char lbl_803D0308[] = "PlPrNr.dat";
char lbl_803D0314[] = "PlyPurin5K_Share_joint";
char lbl_803D032C[] = "PlyPurin5K_Share_matanim_joint";
char lbl_803D034C[] = "PlPrRe.dat";
char lbl_803D0358[] = "PlyPurin5KRe_Share_joint";
char lbl_803D0374[] = "PlyPurin5KRe_Share_matanim_joint";
char lbl_803D0398[] = "PlPrBu.dat";
char lbl_803D03A4[] = "PlyPurin5KBu_Share_joint";
char lbl_803D03C0[] = "PlyPurin5KBu_Share_matanim_joint";
char lbl_803D03E4[] = "PlPrGr.dat";
char lbl_803D03F0[] = "PlyPurin5KGr_Share_joint";
char lbl_803D040C[] = "PlyPurin5KGr_Share_matanim_joint";
char lbl_803D0430[] = "PlPrYe.dat";
char lbl_803D043C[] = "PlyPurin5KYe_Share_joint";
char lbl_803D0458[] = "PlyPurin5KYe_Share_matanim_joint";
char lbl_803D047C[] = "PlPrAJ.dat";

Fighter_DemoStrings lbl_803D04F8 = {
    "ftDemoResultMotionFilePurin",
    "ftDemoIntroMotionFilePurin",
    "ftDemoEndingMotionFilePurin",
    "ftDemoViWaitMotionFilePurin",
};

Fighter_CostumeStrings lbl_803D0508[] = {
    { lbl_803D0308, lbl_803D0314, lbl_803D032C },
    { lbl_803D034C, lbl_803D0358, lbl_803D0374 },
    { lbl_803D0398, lbl_803D03A4, lbl_803D03C0 },
    { lbl_803D03E4, lbl_803D03F0, lbl_803D040C },
    { lbl_803D0430, lbl_803D043C, lbl_803D0458 },
};

char* lbl_803D05B4[] = {
    NULL,
    "PlyPurinReHat_TopN_joint",
    "PlyPurinBuHat_TopN_joint",
    "PlyPurinGrHat_TopN_joint",
    "PlyPurinYeHat_TopN_joint",
};

Vec4 lbl_803D05C8 = { 0.65, 0.7, 0.8, 1 };
Vec4 lbl_803D05D8 = { 1.1, 1.35, 1.3, 1.2 };

char ftPurin_assert_msg_0[] = "!(jobj->flags & JOBJ_USE_QUATERNION)";

Vec3 lbl_803D0610[] = {
    { +8, +0, -4 },
    { +4, +4, +4 },
};

/* static */ extern char* lbl_803D05B4[5];

void func_8013C2F8(void)
{
    lbl_8045A1E0[0] = NULL;
    lbl_8045A1E0[1] = NULL;
    lbl_8045A1E0[2] = NULL;
    lbl_8045A1E0[3] = NULL;
    lbl_8045A1E0[4] = NULL;
}

void ftPurin_OnDeath(HSD_GObj* fighter_gobj)
{
    func_80074A4C(fighter_gobj, 0, 0);
}

void ftPurin_OnUserDataRemove(HSD_GObj* fighter_gobj)
{
    func_8013C494(fighter_gobj);
}

void func_8013C360(HSD_GObj* fighter_gobj)
{
    s32 unused;

    HSD_Joint** joint_list = lbl_8045A1E0;
    Fighter* fp = fighter_gobj->user_data;

    if (lbl_803D05B4[fp->x619_costume_id]) {
        void** item_list = fp->x10C_ftData->x48_items;
        void** item_list_shifted = item_list[1];
        if (!joint_list[fp->x619_costume_id]) {
            UnkCostumeStruct* costume_list =
                CostumeListsForeachCharacter[fp->x4_fighterKind].costume_list;
            joint_list[fp->x619_costume_id] = HSD_ArchiveGetPublicAddress(
                costume_list[fp->x619_costume_id].x14_archive,
                lbl_803D05B4[fp->x619_costume_id]);
        }

        fp->sa.purin.x2244 = HSD_ObjAlloc(&lbl_80459080);
        func_80074148();
        fp->sa.purin.x223C = HSD_JObjLoadJoint(joint_list[fp->x619_costume_id]);
        fp->x2225_flag.bits.b2 = 1;
        func_80074170();
        func_80075650(fighter_gobj, fp->sa.purin.x223C, &fp->sa.purin.x2240);

        func_8007487C(&item_list_shifted[1], &fp->sa.purin.x2248,
                      fp->x619_costume_id, &fp->sa.purin.x2240,
                      &fp->sa.purin.x2240);
        func_8009DC54(fp);
        return;
    }

    fp->sa.purin.x223C = 0;
}

void func_8013C494(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    HSD_JObj* jobj = fp->sa.purin.x223C;

    if (jobj) {
        HSD_JObjRemoveAll(fp->sa.purin.x223C);
        fp->sa.purin.x223C = NULL;
        HSD_ObjFree(&lbl_80459080, fp->sa.purin.x2244);
        fp->sa.purin.x2244 = NULL;
    }
}

void func_8013C4F0(HSD_GObj* fighter_gobj, s32 arg1, Mtx vmtx)
{
    s32 unused[2];

    Fighter* fp = fighter_gobj->user_data;

    if (fp->sa.purin.x223C && fp->x2225_flag.bits.b2) {
        Mtx* mtx;
        HSD_JObj* jobj;
        HSD_JObj* bone_jobj = fp->x5E8_fighterBones[6].x0_jobj;
        HSD_JObjGetMtx(fp->x5E8_fighterBones[6].x0_jobj);
        mtx = (0, &bone_jobj->mtx);
        jobj = fp->sa.purin.x223C;
        HSD_JObjCopyMtx(fp->sa.purin.x223C, *mtx);
        jobj->flags |= 0x03800000;
        HSD_JObjSetMtxDirty(jobj);

        HSD_JObjDispAll(fp->sa.purin.x223C, vmtx, func_80390EB8(arg1), 0);
    }
}

void func_8013C614(Fighter* fp, s32 arg1, s32 arg2)
{
    if (fp->sa.purin.x223C) {
        if (arg2) {
            func_80074CA0(&fp->sa.purin.x2248, arg1, &fp->sa.purin.x2240);
            return;
        }

        func_80074D7C(&fp->sa.purin.x2248, arg1, &fp->sa.purin.x2240);
    }
}

void* func_8013C664(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (fp->sa.purin.x223C)
        return fp->sa.purin.x223C;

    return fighter_gobj;
}

void ftPurin_OnLoad(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    PUSH_ATTRS(fp, ftPurinAttributes);
    fp->x2222_flag.bits.b1 = 1;
    fp->x2D0 = fp->x2D4_specialAttributes;
    func_8013C360(fighter_gobj);
}

void ftPurin_OnItemPickup(HSD_GObj* fighter_gobj, bool bool)
{
    Fighter* fp = getFighter(fighter_gobj);
    if (!func_8026B2B4(fp->x1974_heldItem)) {
        switch (func_8026B320(fp->x1974_heldItem)) {
        case 1:
            break;
        case 2:
            break;
        case 3:
            func_80070FB4(fighter_gobj, 0, 0);
            break;
        case 4:
            func_80070FB4(fighter_gobj, 0, 1);
            break;
        }
        if (bool) {
            func_80070C48(fighter_gobj, 0);
        }
    }
}

void ftPurin_OnItemInvisible(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    if (fp->x1974_heldItem) {
        if (!func_8026B2B4(fp->x1974_heldItem)) {
            func_80070CC4(fighter_gobj, 0);
        }
    }
}

void ftPurin_OnItemVisible(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    if (fp->x1974_heldItem) {
        if (!func_8026B2B4(fp->x1974_heldItem)) {
            func_80070C48(fighter_gobj, 0);
        }
    }
}

void ftPurin_OnItemDrop(HSD_GObj* fighter_gobj, bool bool1)
{
    Fighter_OnItemDrop(fighter_gobj, bool1, 0, 0);
}

void ftPurin_LoadSpecialAttrs(HSD_GObj* fighter_gobj)
{
    COPY_ATTRS(fighter_gobj, ftPurinAttributes);
}

void ftPurin_OnKnockbackEnter(HSD_GObj* fighter_gobj)
{
    Fighter_OnKnockbackEnter(fighter_gobj, 1);
}

void ftPurin_OnKnockbackExit(HSD_GObj* fighter_gobj)
{
    Fighter_OnKnockbackExit(fighter_gobj, 1);
}
