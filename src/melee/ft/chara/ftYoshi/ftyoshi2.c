#include <melee/ft/chara/ftYoshi/ftyoshi2.h>

#include <melee/ef/efasync.h>
#include <melee/ft/chara/ftYoshi/ftyoshi1.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ft_unknown_006.h>
#include <melee/ft/ftcoll.h>
#include <melee/ft/ftparts.h>
#include <melee/it/itkind.h>

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

void lbl_8012C194(void)
{
    func_80092870();
}

void lbl_8012C1B4(void)
{
    func_800928AC();
}
