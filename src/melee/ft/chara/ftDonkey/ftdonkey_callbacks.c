#include "ft/forward.h"

#include "ftDonkey/ftdonkey_callbacks.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftcamera.h"
#include "ft/ftcoll.h"
#include "ft/ftdata.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ftDonkey/ftdonkey.h"
#include "ftDonkey/ftdonkey1.h"
#include "ftDonkey/ftdonkey4.h"
#include "ftDonkey/ftdonkey5.h"
#include "ftDonkey/ftdonkey6.h"
#include "ftDonkey/ftdonkey7.h"
#include "ftDonkey/ftdonkey8.h"
#include "ftDonkey/ftdonkey9.h"
#include "ftDonkey/ftdonkey_SpecialHi.h"
#include "ftDonkey/ftdonkey_SpecialLw.h"
#include "ftDonkey/ftdonkey_SpecialN.h"
#include "ftDonkey/ftdonkey_SpecialS.h"
#include "ftDonkey/ftdonkey_walk.h"
#include "lb/lbmthp.h"
#include "mp/mplib.h"

#include <dolphin/mtx/types.h>

MotionState ftDk_Init_MotionStateTable[] = {
    { 295, 0x00480000, 0x35400000, NULL, ftDk_Init_800DF9F0,
      ftDk_Init_800DFA50, ftDk_Init_800DFA70, ftCamera_UpdateCameraBox },
    { 296, 0x00484066, 0x35000000, ftDk_Walk_800DFB34, ftDk_Walk_800DFB54,
      ftDk_Walk_800DFBB8, ftDk_Walk_800DFBD8, ftCamera_UpdateCameraBox },
    { 297, 0x00484066, 0x35000000, ftDk_Walk_800DFB34, ftDk_Walk_800DFB54,
      ftDk_Walk_800DFBB8, ftDk_Walk_800DFBD8, ftCamera_UpdateCameraBox },
    { 298, 0x00484066, 0x35000000, ftDk_Walk_800DFB34, ftDk_Walk_800DFB54,
      ftDk_Walk_800DFBB8, ftDk_Walk_800DFBD8, ftCamera_UpdateCameraBox },
    { 299, 0x00482064, 0x35000000, ftDk_Unk5_800E01BC, ftDk_Unk5_800E0200,
      ftDk_Unk5_800E0254, ftDk_Unk5_800E0274, ftCamera_UpdateCameraBox },
    { 300, 0x00480000, 0x35000000, ftDk_Unk7_800E0518, ftDk_Unk8_800E0568,
      ftDk_Unk8_800E05A4, ftDk_Unk8_800E05C4, ftCamera_UpdateCameraBox },
    { 301, 0x00480000, 0x35000000, NULL, ftDk_Unk6_800E030C,
      ftDk_Unk6_800E0330, ftDk_Unk6_800E0350, ftCamera_UpdateCameraBox },
    { 302, 0x00488069, 0x35000000, NULL, ftDk_Unk7_800E0440,
      ftDk_Unk7_800E0464, ftDk_Unk7_800E0484, ftCamera_UpdateCameraBox },
    { 303, 0x00480000, 0x35400000, ftDk_Unk8_800E0648, NULL,
      ftDk_Unk9_800E0698, ftDk_Unk9_800E06B8, ftCamera_UpdateCameraBox },
    { 304, 0x004A0000, 0x35000000, ftDk_Unk9_800E07E4, NULL,
      ftDk_Unk9_800E0848, ftDk_Unk9_800E0868, ftCamera_UpdateCameraBox },
    { 305, 0x00A80035, 0x35400000, ft_8009B5C0, ft_8009B5C4, ft_8009B634,
      ft_8009B654, ftCamera_UpdateCameraBox },
    { 306, 0x00A84035, 0x35000000, ft_8009B744, ft_8009B764, ft_8009B7D8,
      ft_8009B7F8, ftCamera_UpdateCameraBox },
    { 307, 0x00A84035, 0x35000000, ft_8009B744, ft_8009B764, ft_8009B7D8,
      ft_8009B7F8, ftCamera_UpdateCameraBox },
    { 308, 0x00A84035, 0x35000000, ft_8009B744, ft_8009B764, ft_8009B7D8,
      ft_8009B7F8, ftCamera_UpdateCameraBox },
    { 309, 0x00A82035, 0x35000000, ft_8009B8B4, ft_8009B948, ft_8009B988,
      ft_8009B9A8, ftCamera_UpdateCameraBox },
    { 310, 0x00A80035, 0x35000000, ft_8009BA50, ft_8009BAA0, ft_8009BADC,
      ft_8009BAFC, ftCamera_UpdateCameraBox },
    { 311, 0x00A80035, 0x35000000, ft_8009BCDC, ft_8009BCE0, ft_8009BD04,
      ft_8009BD24, ftCamera_UpdateCameraBox },
    { 312, 0x00A88035, 0x35000000, ft_8009BBF0, ft_8009BBF4, ft_8009BC18,
      ft_8009BC38, ftCamera_UpdateCameraBox },
    { 313, 0x00A80035, 0x35400000, ft_8009BDC4, NULL, ft_8009BE14, ft_8009BE34,
      ftCamera_UpdateCameraBox },
    { 314, 0x00AA0035, 0x35000000, ft_8009BE54, NULL, ft_8009BEB8, ft_8009BED8,
      ftCamera_UpdateCameraBox },
    { 315, 0x00A40039, 0x39000000, ft_8009C0EC, ft_8009C130, ft_8009C150,
      ft_8009C20C, ftCamera_UpdateCameraBox },
    { 316, 0x00A4003A, 0x3A000000, ft_8009C234, ft_8009C254, ft_8009C274,
      ft_8009C294, ftCamera_UpdateCameraBox },
    { 317, 0x00A4003B, 0x3B000000, ft_8009C2BC, ft_8009C2DC, ft_8009C2FC,
      ft_8009C31C, ftCamera_UpdateCameraBox },
    { 318, 0x00A4003C, 0x3C000000, ft_8009C344, ft_8009C364, ft_8009C384,
      ft_8009C3A4, ftCamera_UpdateCameraBox },
    { 315, 0x00A40039, 0x39000000, ft_8009C3CC, ft_8009C410, ft_8009C414,
      ft_8009C434, ftCamera_UpdateCameraBox },
    { 316, 0x00A4003A, 0x3A000000, ft_8009C3CC, ft_8009C410, ft_8009C414,
      ft_8009C434, ftCamera_UpdateCameraBox },
    { 317, 0x00A4003B, 0x3B000000, ft_8009C3CC, ft_8009C410, ft_8009C414,
      ft_8009C434, ftCamera_UpdateCameraBox },
    { 318, 0x00A4003C, 0x3C000000, ft_8009C3CC, ft_8009C410, ft_8009C414,
      ft_8009C434, ftCamera_UpdateCameraBox },
    { 319, 0x00340211, 0x12000000, ftDk_SpecialN_8010E7B4,
      ftDk_SpecialN_8010F094, ftDk_SpecialN_8010F328, ftDk_SpecialN_8010F468,
      ftCamera_UpdateCameraBox },
    { 320, 0x00340211, 0x12000000, ftDk_SpecialN_8010E840,
      ftDk_SpecialN_8010F098, ftDk_SpecialN_8010F348, ftDk_SpecialN_8010F50C,
      ftCamera_UpdateCameraBox },
    { 321, 0x00340211, 0x12000000, ftDk_SpecialN_8010E8E0,
      ftDk_SpecialN_8010F1D8, ftDk_SpecialN_8010F368, ftDk_SpecialN_8010F5B0,
      ftCamera_UpdateCameraBox },
    { 322, 0x00340211, 0x12000000, ftDk_SpecialN_8010E930,
      ftDk_SpecialN_8010F1DC, ftDk_SpecialN_8010F388, ftDk_SpecialN_8010F654,
      ftCamera_UpdateCameraBox },
    { 323, 0x00340211, 0x12000000, ftDk_SpecialN_8010EB0C,
      ftDk_SpecialN_8010F1E0, ftDk_SpecialN_8010F3A8, ftDk_SpecialN_8010F6F8,
      ftCamera_UpdateCameraBox },
    { 324, 0x00340611, 0x12000000, ftDk_SpecialN_8010EC5C,
      ftDk_SpecialN_8010F1E4, ftDk_SpecialN_8010F3C8, ftDk_SpecialN_8010F79C,
      ftCamera_UpdateCameraBox },
    { 325, 0x00340611, 0x12000000, ftDk_SpecialN_8010ECE8,
      ftDk_SpecialN_8010F1E8, ftDk_SpecialN_8010F3E8, ftDk_SpecialN_8010F840,
      ftCamera_UpdateCameraBox },
    { 326, 0x00340611, 0x12000000, ftDk_SpecialN_8010ED88,
      ftDk_SpecialN_8010F31C, ftDk_SpecialN_8010F408, ftDk_SpecialN_8010F8E4,
      ftCamera_UpdateCameraBox },
    { 327, 0x00340611, 0x12000000, ftDk_SpecialN_8010EDD8,
      ftDk_SpecialN_8010F320, ftDk_SpecialN_8010F428, ftDk_SpecialN_8010F988,
      ftCamera_UpdateCameraBox },
    { 328, 0x00340611, 0x12000000, ftDk_SpecialN_8010EF7C,
      ftDk_SpecialN_8010F324, ftDk_SpecialN_8010F448, ftDk_SpecialN_8010FA2C,
      ftCamera_UpdateCameraBox },
    { 329, 0x00340212, 0x13000000, ftDk_SpecialS_8010E2BC,
      ftDk_SpecialS_8010E334, ftDk_SpecialS_8010E33C, ftDk_SpecialS_8010E3BC,
      ftCamera_UpdateCameraBox },
    { 330, 0x00340612, 0x13000000, ftDk_SpecialS_8010E2F8,
      ftDk_SpecialS_8010E338, ftDk_SpecialS_8010E35C, ftDk_SpecialS_8010E428,
      ftCamera_UpdateCameraBox },
    { 331, 0x00340213, 0x14000000, ftDk_SpecialN_8010FCD4,
      ftDk_SpecialHi_8010FD9C, ftDk_SpecialHi_8010FDA4,
      ftDk_SpecialHi_8010FE60, ftCamera_UpdateCameraBox },
    { 332, 0x00340613, 0x14000000, ftDk_SpecialHi_8010FD10,
      ftDk_SpecialHi_8010FDA0, ftDk_SpecialHi_8010FDEC,
      ftDk_SpecialHi_8010FF14, ftCamera_UpdateCameraBox },
    { 333, 0x00340214, 0x15000000, ftDk_SpecialLw_8010DCD8,
      ftDk_SpecialLw_8010DD14, ftDk_SpecialLw_8010DD18,
      ftDk_SpecialLw_8010DD38, ftCamera_UpdateCameraBox },
    { 334, 0x003C0214, 0x15000000, ftDk_SpecialLw_8010DD74,
      ftDk_SpecialLw_8010DDDC, ftDk_SpecialLw_8010DDF8,
      ftDk_SpecialLw_8010DE18, ftCamera_UpdateCameraBox },
    { 335, 0x00340214, 0x15000000, ftDk_SpecialLw_8010DF5C,
      ftDk_SpecialLw_8010DF98, ftDk_SpecialLw_8010DF9C,
      ftDk_SpecialLw_8010DFBC, ftCamera_UpdateCameraBox },
    { 336, 0x00340614, 0x15000000, ftDk_SpecialLw_8010E030,
      ftDk_SpecialLw_8010E06C, ftDk_SpecialLw_8010E070,
      ftDk_SpecialLw_8010E090, ftCamera_UpdateCameraBox },
};

char ftDk_Init_DatFilename[] = "PlDk.dat";
char ftDk_Init_DataName[] = "ftDataDonkey";
char ftDk_Init_803CBE14[] = "PlDkNr.dat";
char ftDk_Init_803CBE20[] = "PlyDonkey5K_Share_joint";
char ftDk_Init_803CBE38[] = "PlyDonkey5K_Share_matanim_joint";
char ftDk_Init_803CBE58[] = "PlDkBk.dat";
char ftDk_Init_803CBE64[] = "PlyDonkey5KBk_Share_joint";
char ftDk_Init_803CBE80[] = "PlyDonkey5KBk_Share_matanim_joint";
char ftDk_Init_803CBEA4[] = "PlDkRe.dat";
char ftDk_Init_803CBEB0[] = "PlyDonkey5KRe_Share_joint";
char ftDk_Init_803CBECC[] = "PlyDonkey5KRe_Share_matanim_joint";
char ftDk_Init_803CBEF0[] = "PlDkBu.dat";
char ftDk_Init_803CBEFC[] = "PlyDonkey5KBu_Share_joint";
char ftDk_Init_803CBF18[] = "PlyDonkey5KBu_Share_matanim_joint";
char ftDk_Init_803CBF3C[] = "PlDkGr.dat";
char ftDk_Init_803CBF48[] = "PlyDonkey5KGr_Share_joint";
char ftDk_Init_803CBF64[] = "PlyDonkey5KGr_Share_matanim_joint";
char ftDk_Init_AnimDatFilename[] = "PlDkAJ.dat";

Fighter_DemoStrings ftDk_Init_DemoMotionFilenames = {
    "ftDemoResultMotionFileDonkey",
    "ftDemoIntroMotionFileDonkey",
    "ftDemoEndingMotionFileDonkey",
    "ftDemoViWaitMotionFileDonkey",
};

Fighter_CostumeStrings ftDk_Init_CostumeStrings[] = {
    { ftDk_Init_803CBE14, ftDk_Init_803CBE20, ftDk_Init_803CBE38 },
    { ftDk_Init_803CBE58, ftDk_Init_803CBE64, ftDk_Init_803CBE80 },
    { ftDk_Init_803CBEA4, ftDk_Init_803CBEB0, ftDk_Init_803CBECC },
    { ftDk_Init_803CBEF0, ftDk_Init_803CBEFC, ftDk_Init_803CBF18 },
    { ftDk_Init_803CBF3C, ftDk_Init_803CBF48, ftDk_Init_803CBF64 },
};

void ftDk_Init_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->fv.dk.x222C = 0;
    ftParts_80074A4C(gobj, 0, 0);
}

void ftDk_Init_8010D774(HSD_GObj* gobj)
{
    ftDk_SpecialN_DestroyAllEffectsPlus(gobj);
    ftDk_SpecialHi_DestroyAllEffects_SpecialHi(gobj);
}

void ftDk_Init_OnItemPickup(HSD_GObj* gobj, bool bool)
{
    Fighter_OnItemPickup(gobj, bool, 1, 1);
}

void ftDk_Init_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 1);
}

void ftDk_Init_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 1);
}

void ftDk_Init_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    Fighter_OnItemDrop(gobj, bool1, 1, 1);
}

void ftDk_Init_UnkMotionStates4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftDonkeyAttributes* attr = fp->x2D4_specialAttributes;

    if (fp->fv.dk.x222C == attr->SpecialN.x2C_MAX_ARM_SWINGS) {
        ft_800BFFD0(fp, 0x39, 0);
    }
}

void ftDk_Init_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftData* ftdata = fp->ft_data;
    ftDonkeyAttributes* ftData_attr = ftdata->ext_attr;

    ftData_attr->x8 = lbMthp_8001E8F8(ftData_80085E50(fp, 0x128U));
    ftData_attr->xC = lbMthp_8001E8F8(ftData_80085E50(fp, 0x129U));
    ftData_attr->x10 = lbMthp_8001E8F8(ftData_80085E50(fp, 0x12AU));
    PUSH_ATTRS(fp, ftDonkeyAttributes);

    fp->x2222_flag.bits.b0 = 1;
    fp->x2CC = fp->x2D4_specialAttributes;
}

void ftDk_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftDonkeyAttributes);
}

void ftDk_Init_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, 1);
}

void ftDk_Init_OnKnockbackExit(HSD_GObj* gobj)
{
    Fighter_OnKnockbackExit(gobj, 1);
}

void ftDk_Init_8010DB3C(HSD_GObj* gobj)
{
    bool bool1;
    Fighter* fp = gobj->user_data;
    ftDonkeyAttributes* donkey_attr = fp->x2D4_specialAttributes;
    CollData* colldata = &fp->x6F0_collData;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (fp->x2210_ThrowFlags.b3) {
        fp->x2210_ThrowFlags.b3 = false;
        bool1 = true;
    } else {
        bool1 = false;
    }

    if (bool1 && (colldata->x134_envFlags & 0x18000)) {
        Vec3 vec_list[4];

        int i;
        for (i = 0; i < 4; i++) {
            f32 temp_f5 = (donkey_attr->SpecialLw.x68 * i) -
                          (donkey_attr->SpecialLw.x68 * 1.5f);
            f32 temp_f3 = donkey_attr->SpecialLw.x6C * fp->facing_dir;
            f32 temp_f6 = temp_f5 + temp_f3;

            if (!mpLib_80056C54(colldata->x14C_ground.index, &fp->cur_pos, 0,
                                &vec_list[i], 0, 0, temp_f6,
                                donkey_attr->SpecialLw.x70,
                                donkey_attr->SpecialLw.x68 * 1.5f,
                                donkey_attr->SpecialLw.x68))
            {
                vec_list[i] = fp->cur_pos;
            }

            vec_list[i].y += 2.0f;
            ftColl_8007B8A8(&fp->x914[i], &vec_list[i]);
        }
    }
}
