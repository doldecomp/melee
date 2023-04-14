#include "ft/forward.h"

#include "ft/chara/ftDonkey/ftdonkey_callbacks.h"

#include "ft/chara/ftDonkey/ftdonkey.h"
#include "ft/chara/ftDonkey/ftdonkey1.h"
#include "ft/chara/ftDonkey/ftdonkey4.h"
#include "ft/chara/ftDonkey/ftdonkey5.h"
#include "ft/chara/ftDonkey/ftdonkey6.h"
#include "ft/chara/ftDonkey/ftdonkey7.h"
#include "ft/chara/ftDonkey/ftdonkey8.h"
#include "ft/chara/ftDonkey/ftdonkey9.h"
#include "ft/chara/ftDonkey/ftdonkey_SpecialHi.h"
#include "ft/chara/ftDonkey/ftdonkey_SpecialLw.h"
#include "ft/chara/ftDonkey/ftdonkey_SpecialN.h"
#include "ft/chara/ftDonkey/ftdonkey_SpecialS.h"
#include "ft/chara/ftDonkey/ftdonkey_walk.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftcamera.h"
#include "ft/ftcoll.h"
#include "ft/ftdata.h"
#include "ft/ftparts.h"
#include "lb/lbmthp.h"
#include "mp/mplib.h"

MotionState ftDonkey_MotionStateTable[] = {
    { 295, 0x00480000, 0x35400000, NULL, ftDonkey_800DF9F0, ftDonkey_800DFA50,
      ftDonkey_800DFA70, ftCamera_UpdateCameraBox },
    { 296, 0x00484066, 0x35000000, ftDonkey_800DFB34, ftDonkey_800DFB54,
      ftDonkey_800DFBB8, ftDonkey_800DFBD8, ftCamera_UpdateCameraBox },
    { 297, 0x00484066, 0x35000000, ftDonkey_800DFB34, ftDonkey_800DFB54,
      ftDonkey_800DFBB8, ftDonkey_800DFBD8, ftCamera_UpdateCameraBox },
    { 298, 0x00484066, 0x35000000, ftDonkey_800DFB34, ftDonkey_800DFB54,
      ftDonkey_800DFBB8, ftDonkey_800DFBD8, ftCamera_UpdateCameraBox },
    { 299, 0x00482064, 0x35000000, ftDonkey_800E01BC, ftDonkey_800E0200,
      ftDonkey_800E0254, ftDonkey_800E0274, ftCamera_UpdateCameraBox },
    { 300, 0x00480000, 0x35000000, ftDonkey_800E0518, ftDonkey_800E0568,
      ftDonkey_800E05A4, ftDonkey_800E05C4, ftCamera_UpdateCameraBox },
    { 301, 0x00480000, 0x35000000, NULL, ftDonkey_800E030C, ftDonkey_800E0330,
      ftDonkey_800E0350, ftCamera_UpdateCameraBox },
    { 302, 0x00488069, 0x35000000, NULL, ftDonkey_800E0440, ftDonkey_800E0464,
      ftDonkey_800E0484, ftCamera_UpdateCameraBox },
    { 303, 0x00480000, 0x35400000, ftDonkey_800E0648, NULL, ftDonkey_800E0698,
      ftDonkey_800E06B8, ftCamera_UpdateCameraBox },
    { 304, 0x004A0000, 0x35000000, ftDonkey_800E07E4, NULL, ftDonkey_800E0848,
      ftDonkey_800E0868, ftCamera_UpdateCameraBox },
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
    { 319, 0x00340211, 0x12000000, ftDonkey_8010E7B4, ftDonkey_8010F094,
      ftDonkey_8010F328, ftDonkey_8010F468, ftCamera_UpdateCameraBox },
    { 320, 0x00340211, 0x12000000, ftDonkey_8010E840, ftDonkey_8010F098,
      ftDonkey_8010F348, ftDonkey_8010F50C, ftCamera_UpdateCameraBox },
    { 321, 0x00340211, 0x12000000, ftDonkey_8010E8E0, ftDonkey_8010F1D8,
      ftDonkey_8010F368, ftDonkey_8010F5B0, ftCamera_UpdateCameraBox },
    { 322, 0x00340211, 0x12000000, ftDonkey_8010E930, ftDonkey_8010F1DC,
      ftDonkey_8010F388, ftDonkey_8010F654, ftCamera_UpdateCameraBox },
    { 323, 0x00340211, 0x12000000, ftDonkey_8010EB0C, ftDonkey_8010F1E0,
      ftDonkey_8010F3A8, ftDonkey_8010F6F8, ftCamera_UpdateCameraBox },
    { 324, 0x00340611, 0x12000000, ftDonkey_8010EC5C, ftDonkey_8010F1E4,
      ftDonkey_8010F3C8, ftDonkey_8010F79C, ftCamera_UpdateCameraBox },
    { 325, 0x00340611, 0x12000000, ftDonkey_8010ECE8, ftDonkey_8010F1E8,
      ftDonkey_8010F3E8, ftDonkey_8010F840, ftCamera_UpdateCameraBox },
    { 326, 0x00340611, 0x12000000, ftDonkey_8010ED88, ftDonkey_8010F31C,
      ftDonkey_8010F408, ftDonkey_8010F8E4, ftCamera_UpdateCameraBox },
    { 327, 0x00340611, 0x12000000, ftDonkey_8010EDD8, ftDonkey_8010F320,
      ftDonkey_8010F428, ftDonkey_8010F988, ftCamera_UpdateCameraBox },
    { 328, 0x00340611, 0x12000000, ftDonkey_8010EF7C, ftDonkey_8010F324,
      ftDonkey_8010F448, ftDonkey_8010FA2C, ftCamera_UpdateCameraBox },
    { 329, 0x00340212, 0x13000000, ftDonkey_8010E2BC, ftDonkey_8010E334,
      ftDonkey_8010E33C, ftDonkey_8010E3BC, ftCamera_UpdateCameraBox },
    { 330, 0x00340612, 0x13000000, ftDonkey_8010E2F8, ftDonkey_8010E338,
      ftDonkey_8010E35C, ftDonkey_8010E428, ftCamera_UpdateCameraBox },
    { 331, 0x00340213, 0x14000000, ftDonkey_8010FCD4, ftDonkey_8010FD9C,
      ftDonkey_8010FDA4, ftDonkey_8010FE60, ftCamera_UpdateCameraBox },
    { 332, 0x00340613, 0x14000000, ftDonkey_8010FD10, ftDonkey_8010FDA0,
      ftDonkey_8010FDEC, ftDonkey_8010FF14, ftCamera_UpdateCameraBox },
    { 333, 0x00340214, 0x15000000, ftDonkey_8010DCD8, ftDonkey_8010DD14,
      ftDonkey_8010DD18, ftDonkey_8010DD38, ftCamera_UpdateCameraBox },
    { 334, 0x003C0214, 0x15000000, ftDonkey_8010DD74, ftDonkey_8010DDDC,
      ftDonkey_8010DDF8, ftDonkey_8010DE18, ftCamera_UpdateCameraBox },
    { 335, 0x00340214, 0x15000000, ftDonkey_8010DF5C, ftDonkey_8010DF98,
      ftDonkey_8010DF9C, ftDonkey_8010DFBC, ftCamera_UpdateCameraBox },
    { 336, 0x00340614, 0x15000000, ftDonkey_8010E030, ftDonkey_8010E06C,
      ftDonkey_8010E070, ftDonkey_8010E090, ftCamera_UpdateCameraBox },
};

char lbl_803CBDF8[] = "PlDk.dat";
char lbl_803CBE04[] = "ftDataDonkey";
char lbl_803CBE14[] = "PlDkNr.dat";
char lbl_803CBE20[] = "PlyDonkey5K_Share_joint";
char lbl_803CBE38[] = "PlyDonkey5K_Share_matanim_joint";
char lbl_803CBE58[] = "PlDkBk.dat";
char lbl_803CBE64[] = "PlyDonkey5KBk_Share_joint";
char lbl_803CBE80[] = "PlyDonkey5KBk_Share_matanim_joint";
char lbl_803CBEA4[] = "PlDkRe.dat";
char lbl_803CBEB0[] = "PlyDonkey5KRe_Share_joint";
char lbl_803CBECC[] = "PlyDonkey5KRe_Share_matanim_joint";
char lbl_803CBEF0[] = "PlDkBu.dat";
char lbl_803CBEFC[] = "PlyDonkey5KBu_Share_joint";
char lbl_803CBF18[] = "PlyDonkey5KBu_Share_matanim_joint";
char lbl_803CBF3C[] = "PlDkGr.dat";
char lbl_803CBF48[] = "PlyDonkey5KGr_Share_joint";
char lbl_803CBF64[] = "PlyDonkey5KGr_Share_matanim_joint";
char lbl_803CBF88[] = "PlDkAJ.dat";

Fighter_DemoStrings lbl_803CC010 = {
    "ftDemoResultMotionFileDonkey",
    "ftDemoIntroMotionFileDonkey",
    "ftDemoEndingMotionFileDonkey",
    "ftDemoViWaitMotionFileDonkey",
};

Fighter_CostumeStrings lbl_803CC020[] = {
    { lbl_803CBE14, lbl_803CBE20, lbl_803CBE38 },
    { lbl_803CBE58, lbl_803CBE64, lbl_803CBE80 },
    { lbl_803CBEA4, lbl_803CBEB0, lbl_803CBECC },
    { lbl_803CBEF0, lbl_803CBEFC, lbl_803CBF18 },
    { lbl_803CBF3C, lbl_803CBF48, lbl_803CBF64 },
};

void ftDonkey_OnDeath(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->ev.dk.x222C = 0;
    ftParts_80074A4C(gobj, 0, 0);
}

void ftDonkey_8010D774(HSD_GObj* gobj)
{
    ftDonkey_DestroyAllEffectsPlus(gobj);
    ftDonkey_DestroyAllEffects_SpecialHi(gobj);
}

void ftDonkey_OnItemPickup(HSD_GObj* gobj, bool bool)
{
    Fighter_OnItemPickup(gobj, bool, 1, 1);
}

void ftDonkey_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 1);
}

void ftDonkey_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, 1);
}

void ftDonkey_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    Fighter_OnItemDrop(gobj, bool1, 1, 1);
}

void ftDonkey_8010D96C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftDonkeyAttributes* attr = fp->x2D4_specialAttributes;

    if (fp->ev.dk.x222C == attr->SpecialN.x2C_MAX_ARM_SWINGS) {
        ft_800BFFD0(fp, 0x39, 0);
    }
}

void ftDonkey_OnLoad(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftData* ftdata = fp->x10C_ftData;
    ftDonkeyAttributes* ftData_attr = ftdata->ext_attr;

    ftData_attr->x8 = lbMthp_8001E8F8(ftData_80085E50(fp, 0x128U));
    ftData_attr->xC = lbMthp_8001E8F8(ftData_80085E50(fp, 0x129U));
    ftData_attr->x10 = lbMthp_8001E8F8(ftData_80085E50(fp, 0x12AU));
    PUSH_ATTRS(fp, ftDonkeyAttributes);

    fp->x2222_flag.bits.b0 = 1;
    fp->x2CC = fp->x2D4_specialAttributes;
}

void ftDonkey_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftDonkeyAttributes);
}

void ftDonkey_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, 1);
}

void ftDonkey_OnKnockbackExit(HSD_GObj* gobj)
{
    Fighter_OnKnockbackExit(gobj, 1);
}

void ftDonkey_8010DB3C(HSD_GObj* gobj)
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

            if (!mpLib_80056C54(colldata->x14C_ground.index, &fp->xB0_pos, 0,
                                &vec_list[i], 0, 0, temp_f6,
                                donkey_attr->SpecialLw.x70,
                                donkey_attr->SpecialLw.x68 * 1.5f,
                                donkey_attr->SpecialLw.x68))
            {
                vec_list[i] = fp->xB0_pos;
            }

            vec_list[i].y += 2.0f;
            ftColl_8007B8A8(&fp->x914[i], &vec_list[i]);
        }
    }
}
