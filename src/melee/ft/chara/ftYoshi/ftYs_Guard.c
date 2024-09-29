#include <placeholder.h>

#include "ft/forward.h"
#include "ftCommon/forward.h"
#include <baselib/forward.h>

#include "ftYs_Guard.h"

#include "ftYs_Init.h"
#include "ftYs_SpecialN.h"

#include "ef/efasync.h"
#include "ft/fighter.h"
#include "ft/ft_0892.h"
#include "ft/ft_0D14.h"
#include "ft/ftanim.h"
#include "ft/ftcoll.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Escape.h"
#include "ftCommon/ftCo_Guard.h"
#include "ftCommon/ftCo_ItemThrow.h"
#include "ftCommon/ftCo_Pass.h"
#include "ftYoshi/types.h"

char ftYs_Init_DatFilename[] = "PlYs.dat";
char ftYs_Init_DataName[] = "ftDataYoshi";
char ftYs_Unk2_803CEAB0[] = "PlYsNr.dat";
char ftYs_Unk2_803CEABC[] = "PlyYoshi5K_Share_joint";
char ftYs_Unk2_803CEAD4[] = "PlyYoshi5K_Share_matanim_joint";
char ftYs_Unk2_803CEAF4[] = "PlYsRe.dat";
char ftYs_Unk2_803CEB00[] = "PlyYoshi5KRe_Share_joint";
char ftYs_Unk2_803CEB1C[] = "PlyYoshi5KRe_Share_matanim_joint";
char ftYs_Unk2_803CEB40[] = "PlYsBu.dat";
char ftYs_Unk2_803CEB4C[] = "PlyYoshi5KBu_Share_joint";
char ftYs_Unk2_803CEB68[] = "PlyYoshi5KBu_Share_matanim_joint";
char ftYs_Unk2_803CEB8C[] = "PlYsYe.dat";
char ftYs_Unk2_803CEB98[] = "PlyYoshi5KYe_Share_joint";
char ftYs_Unk2_803CEBB4[] = "PlyYoshi5KYe_Share_matanim_joint";
char ftYs_Unk2_803CEBD8[] = "PlYsPi.dat";
char ftYs_Unk2_803CEBE4[] = "PlyYoshi5KPi_Share_joint";
char ftYs_Unk2_803CEC00[] = "PlyYoshi5KPi_Share_matanim_joint";
char ftYs_Unk2_803CEC24[] = "PlYsAq.dat";
char ftYs_Unk2_803CEC30[] = "PlyYoshi5KAq_Share_joint";
char ftYs_Unk2_803CEC4C[] = "PlyYoshi5KAq_Share_matanim_joint";
char ftYs_Init_AnimDatFilename[] = "PlYsAJ.dat";

Fighter_DemoStrings ftYs_Init_DemoMotionFilenames = {
    "ftDemoResultMotionFileYoshi",
    "ftDemoIntroMotionFileYoshi",
    "ftDemoEndingMotionFileYoshi",
    "ftDemoViWaitMotionFileYoshi",
};

Fighter_CostumeStrings ftYs_Init_CostumeStrings[] = {
    { ftYs_Unk2_803CEAB0, ftYs_Unk2_803CEABC, ftYs_Unk2_803CEAD4 },
    { ftYs_Unk2_803CEAF4, ftYs_Unk2_803CEB00, ftYs_Unk2_803CEB1C },
    { ftYs_Unk2_803CEB40, ftYs_Unk2_803CEB4C, ftYs_Unk2_803CEB68 },
    { ftYs_Unk2_803CEB8C, ftYs_Unk2_803CEB98, ftYs_Unk2_803CEBB4 },
    { ftYs_Unk2_803CEBD8, ftYs_Unk2_803CEBE4, ftYs_Unk2_803CEC00 },
    { ftYs_Unk2_803CEC24, ftYs_Unk2_803CEC30, ftYs_Unk2_803CEC4C },
};

/* static */ extern float const ftYs_Init_804D9A28;

static inline void spawnEffect(HSD_GObj* gobj)
{
    HSD_JObj* jobj;
    Fighter_Part part;
    Fighter* fp2;
    ftCo_DatAttrs_xBC_t* co_xBC;
    Fighter* fp;
    fp = GET_FIGHTER(gobj);
    ftParts_80074B0C(gobj, 0, 0);
    ftColl_8007B0C0(gobj, 0);

    co_xBC = &fp->co_attrs.xBC;
    part = ftParts_8007500C(fp, FtPart_HipN);
    fp2 = GET_FIGHTER(gobj);
    jobj = fp->parts[part].joint;

    efAsync_Spawn(gobj, &fp2->x60C, FtPart_HipN, 1231, jobj, co_xBC);
}

void ftYs_GuardOn_0_Anim(HSD_GObj* gobj)
{
    u8 _[8];
    Fighter* fp = GET_FIGHTER(gobj);

    fp->mv.ys.unk2.x0 += ftYs_Init_804D9A28;
    ftCo_80092BCC(gobj);
    if (ftCo_800925A4(gobj)) {
        spawnEffect(gobj);
    } else if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_800928CC(gobj);
    } else {
        ftYs_Init_8012B8A4(gobj);
    }
}

void ftYs_GuardOn_0_IASA(HSD_GObj* gobj)
{
    RETURN_IF(ftCo_80093694(gobj));
    RETURN_IF(ftCo_8009515C(gobj));
    RETURN_IF(ftCo_80099794(gobj));
    RETURN_IF(ftCo_8009917C(gobj));
    RETURN_IF(ftCo_Catch_CheckInput(gobj));
    RETURN_IF(ftCo_8009A080(gobj));
}

void ftYs_GuardOn_0_Phys(HSD_GObj* arg0)
{
    ftCo_GuardOn_Phys(arg0);
}

void ftYs_GuardOn_0_Coll(HSD_GObj* arg0)
{
    ftCo_GuardOn_Coll(arg0);
}

static inline void inlineA0(Fighter_GObj* gobj)
{
    FORCE_PAD_STACK(4 * 4);
    {
        Fighter* fp = GET_FIGHTER(gobj);
        struct UNK_SAMUS_S2 foo;
        ftColl_8007B0C0(gobj, Intangible);
        foo.parts[0] = fp->ft_data->x8->x11;
        foo.parts[1] = FtPart_TransN;
        foo.parts[2] = FtPart_TransN;
        foo.vec1 = foo.vec2 = ftYs_Unk1_803B75C0;
        foo.scale = 1;
        ftColl_8007B5AC(fp, fp->hurt_capsules, &foo);
    }
}

void ftYs_Shield_8012C1D4(ftYs_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(4 * 2);
    Fighter_ChangeMotionState(gobj, ftYs_MS_GuardHold, Ft_MF_None, 0, 1, 0,
                              NULL);
    ftAnim_8006FA58(fp, 1, fp->x108_costume_joint->child);
    ftParts_80074B0C(gobj, 0, 1);
    inlineA0(gobj);
    ftCo_80092450(gobj);
    fp->x221E_b4 = false;
    ftYs_Init_8012B8A4(gobj);
    ftCo_80091D58(fp);
}

void ftYs_GuardHold_Anim(HSD_GObj* gobj)
{
    u8 _[12];

    Fighter* fp = GET_FIGHTER(gobj);

    fp->mv.ys.unk2.x0 += ftYs_Init_804D9A28;
    ftCo_80092BCC(gobj);

    if (ftCo_800925A4(gobj)) {
        spawnEffect(gobj);
    } else if (fp->mv.ys.unk2.xC != 0 ||
               (!(fp->x221B_b0 & 1) && !(fp->x2218_b3)))
    {
        ftCo_80092BE8(gobj);
    } else {
        ftYs_Init_8012B8A4(gobj);
    }
}

void ftYs_GuardHold_IASA(HSD_GObj* gobj)
{
    if (!ftCo_8009515C(gobj) && !ftCo_80099794(gobj) && !ftCo_8009917C(gobj) &&
        !ftCo_Catch_CheckInput(gobj) && !ftCo_8009A080(gobj))
    {
        return;
    }
}

void ftYs_GuardHold_Phys(HSD_GObj* arg0)
{
    ftCo_Guard_Phys(arg0);
}

void ftYs_GuardHold_Coll(HSD_GObj* arg0)
{
    ftCo_Guard_Coll(arg0);
}

void ftYs_Shield_8012C49C(HSD_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, 343, 0, 0, ftYs_Init_804D9A28, 0, NULL);

    {
        Fighter* fp0 = GET_FIGHTER(gobj);
        ftParts_80074B0C(gobj, 0, 0);
        ftColl_8007B0C0(gobj, 0);

        {
            u8 _[8];

            ftCo_DatAttrs_xBC_t* co_xBC = &fp0->co_attrs.xBC;

            ssize_t bone_idx = ftParts_8007500C(fp0, 4);
            Fighter* fp1 = GET_FIGHTER(gobj);

            /// @todo Why is this still using @c fp0?
            HSD_JObj* jobj = fp0->parts[bone_idx].joint;

            efAsync_Spawn(gobj, &fp1->x60C, 4U, 1231, jobj, co_xBC);
        }
    }
}

void ftYs_GuardOff_Anim(HSD_GObj* gobj)
{
    u8 _[8];

    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.ys.unk2.x0 = fp->mv.ys.unk2.x0 + ftYs_Init_804D9A28;

    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ft_8008A2BC(gobj);
    }
}

void ftYs_GuardOff_IASA(HSD_GObj* gobj)
{
    RETURN_IF(ftCo_80099794(gobj));
}

void ftYs_GuardOff_Phys(HSD_GObj* arg0)
{
    ftCo_GuardOff_Phys(arg0);
}

void ftYs_GuardOff_Coll(HSD_GObj* arg0)
{
    ftCo_GuardOff_Coll(arg0);
}

/// #ftYs_Shield_8012C600

void ftYs_GuardDamage_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCo_80093BC0(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (fp->mv.ys.unk2.xC) {
            ftCo_80092BE8(gobj);
        } else {
            ftCo_800928CC(gobj);
        }
    }
}

void ftYs_GuardDamage_IASA(HSD_GObj* arg0) {}

/// #ftYs_GuardDamage_Phys

/// #ftYs_GuardDamage_Coll

void ftYs_Shield_8012C850(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftYs_MS_GuardOn_1, 16, fp->cur_anim_frame,
                              1, 0, NULL);
    fp->x672_input_timer_counter = 254;
    fp->x221A_b7 = false;
    fp->x221B_b0 = false;
    fp->x221C_b3 = true;
    fp->x221C_b1 = true;
    fp->x221C_b2 = true;

    fp->mv.ys.unk2.x14 = p_ftCommonData->x2A4;
    fp->mv.ys.unk2.x18 = p_ftCommonData->x2B4;
    ftCo_8009370C(gobj, ftYs_Shield_8012CACC);
}

/// #ftYs_Shield_8012C914

void ftYs_Shield_8012CACC(HSD_GObj* arg0) {}

/// #ftYs_GuardOn_1_Anim

/// #ftYs_GuardOn_1_IASA

/// #ftYs_GuardOn_1_Phys

/// #ftYs_GuardOn_1_Coll

bool ftYs_Shield_8012CC1C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if ((fp->input.held_inputs & 0x80000000) && (fp->shield_health >= 0)) {
        ftCo_800928CC(gobj);
        return true;
    }

    return false;
}

Fighter_Part ftYs_Shield_8012CC6C(ftYs_GObj* gobj)
{
    return ftParts_8007500C(GET_FIGHTER(gobj), 52);
}

void ftYs_Shield_8012CC94(HSD_GObj* gobj, Vec3* out)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* da = fp->dat_attrs;
    out->x = (-fp->facing_dir * da->x10);
    out->y = da->x14;
    out->z = 0;
}

float ftYs_Shield_8012CCC4(HSD_GObj* gobj)
{
    return GET_FIGHTER(gobj)->facing_dir;
}

float ftYs_Shield_8012CCD0(HSD_GObj* gobj)
{
    ftYoshiAttributes* da = GET_FIGHTER(gobj)->dat_attrs;
    return da->x18;
}

float ftYs_Shield_8012CCE0(HSD_GObj* gobj)
{
    ftYoshiAttributes* da = GET_FIGHTER(gobj)->dat_attrs;
    return da->x1C;
}

float ftYs_Shield_8012CCF0(HSD_GObj* gobj)
{
    ftYoshiAttributes* da = GET_FIGHTER(gobj)->dat_attrs;
    return da->x20;
}

float ftYs_Shield_8012CD00(HSD_GObj* gobj)
{
    ftYoshiAttributes* da = GET_FIGHTER(gobj)->dat_attrs;
    return da->x24;
}
