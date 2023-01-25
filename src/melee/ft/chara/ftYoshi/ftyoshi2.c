#include <melee/ft/chara/ftYoshi/ftyoshi2.h>

#include <melee/ef/efasync.h>
#include <melee/ft/chara/ftYoshi/ftyoshi1.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ft_unknown_006.h>
#include <melee/ft/ftcoll.h>
#include <melee/ft/ftparts.h>
#include <melee/ft/types.h>
#include <melee/it/itkind.h>

char lbl_803CEA98[] = "PlYs.dat";
char lbl_803CEAA4[] = "ftDataYoshi";
char lbl_803CEAB0[] = "PlYsNr.dat";
char lbl_803CEABC[] = "PlyYoshi5K_Share_joint";
char lbl_803CEAD4[] = "PlyYoshi5K_Share_matanim_joint";
char lbl_803CEAF4[] = "PlYsRe.dat";
char lbl_803CEB00[] = "PlyYoshi5KRe_Share_joint";
char lbl_803CEB1C[] = "PlyYoshi5KRe_Share_matanim_joint";
char lbl_803CEB40[] = "PlYsBu.dat";
char lbl_803CEB4C[] = "PlyYoshi5KBu_Share_joint";
char lbl_803CEB68[] = "PlyYoshi5KBu_Share_matanim_joint";
char lbl_803CEB8C[] = "PlYsYe.dat";
char lbl_803CEB98[] = "PlyYoshi5KYe_Share_joint";
char lbl_803CEBB4[] = "PlyYoshi5KYe_Share_matanim_joint";
char lbl_803CEBD8[] = "PlYsPi.dat";
char lbl_803CEBE4[] = "PlyYoshi5KPi_Share_joint";
char lbl_803CEC00[] = "PlyYoshi5KPi_Share_matanim_joint";
char lbl_803CEC24[] = "PlYsAq.dat";
char lbl_803CEC30[] = "PlyYoshi5KAq_Share_joint";
char lbl_803CEC4C[] = "PlyYoshi5KAq_Share_matanim_joint";
char lbl_803CEC70[] = "PlYsAJ.dat";

Fighter_DemoStrings lbl_803CECEC = {
    "ftDemoResultMotionFileYoshi",
    "ftDemoIntroMotionFileYoshi",
    "ftDemoEndingMotionFileYoshi",
    "ftDemoViWaitMotionFileYoshi",
};

Fighter_CostumeStrings lbl_803CECFC[] = {
    { lbl_803CEAB0, lbl_803CEABC, lbl_803CEAD4 },
    { lbl_803CEAF4, lbl_803CEB00, lbl_803CEB1C },
    { lbl_803CEB40, lbl_803CEB4C, lbl_803CEB68 },
    { lbl_803CEB8C, lbl_803CEB98, lbl_803CEBB4 },
    { lbl_803CEBD8, lbl_803CEBE4, lbl_803CEC00 },
    { lbl_803CEC24, lbl_803CEC30, lbl_803CEC4C },
};

/* static */ extern f32 const lbl_804D9A28;

void lbl_8012C030(HSD_GObj* fighter_gobj)
{
    Fighter* fp;
    s32 bone_idx;
    Fighter* fp2;
    s32* x1CC;
    HSD_JObj* jobj;
    u32 unused[4];

    fp = GET_FIGHTER(fighter_gobj);
    fp->x2340_f32 += lbl_804D9A28;
    func_80092BCC(fighter_gobj);
    if (func_800925A4(fighter_gobj)) {
        fp = GET_FIGHTER(fighter_gobj);
        func_80074B0C(fighter_gobj, 0, 0);
        func_8007B0C0(fighter_gobj, 0);

        x1CC = &fp->x110_attr.x1CC;
        bone_idx = func_8007500C(fp, 4);
        fp2 = GET_FIGHTER(fighter_gobj);
        jobj = fp->x5E8_fighterBones[bone_idx].x0_jobj;

        efAsync_Spawn(fighter_gobj, &fp2->x60C, 4U, 0x4CFU, jobj, x1CC);
    } else if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        func_800928CC(fighter_gobj);
    } else {
        func_8012B8A4(fighter_gobj);
    }
}

void lbl_8012C114(HSD_GObj* fighter_gobj)
{
    if (!func_80093694() && !func_8009515C(fighter_gobj) &&
        !func_80099794(fighter_gobj) && !func_8009917C(fighter_gobj) &&
        !func_800D8990(fighter_gobj) && !func_8009A080(fighter_gobj))
    {
        return;
    }
}

void lbl_8012C194(HSD_GObj* arg0)
{
    func_80092870();
}

void lbl_8012C1B4(HSD_GObj* arg0)
{
    func_800928AC();
}
