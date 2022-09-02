#include <melee/ft/chara/ftDrMario/ftdrmario.h>

void func_80149954(HSD_GObj* gobj)
{
    Vec3 sp18;
    Fighter* fp;
    u32 tmp;
    int unused2[3];

    fp = gobj->user_data;
    if (fp->x2200_ftcmd_var0 == 1 && fp->sa.mario.x2240 == 0U) {
        func_8000B1CC(fp->x5E8_fighterBones->x0_jobj, 0, &sp18);
        tmp = ftMario_SpecialN_VitaminRandom(gobj);
        tmp = func_802C0850(gobj, &sp18, tmp, 0x31, fp->x2C_facing_direction);
        fp->sa.mario.x2240 = tmp;
        if (tmp != 0) {
            fp->cb.x21E4_callback_OnDeath2 = func_80149540;
            fp->cb.x21DC_callback_OnTakeDamage = func_80149540;
        }
    } else if (fp->x2200_ftcmd_var0 == 2) {
        func_801497CC(gobj);
    }
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        if (gobj != NULL) {
            fp = gobj->user_data;
            if (fp != NULL && fp->sa.mario.x2240 != 0) {
                func_802C0DBC(fp->sa.mario.x2240);
                fp->sa.mario.x2240 = 0;
            }
        }
        if (gobj != NULL) {
            fp = gobj->user_data;
            if (fp != NULL) {
                fp->cb.x21DC_callback_OnTakeDamage = 0;
                fp->cb.x21E4_callback_OnDeath2 = 0;
            }
        }
        func_8008A2BC(gobj);
    }
}

void func_80149A6C(HSD_GObj* gobj)
{
    func_800DED30(gobj);
}

void func_80149A8C(HSD_GObj* gobj)
{
    func_80084F3C(gobj);
}

void func_80149AAC(HSD_GObj* gobj)
{
    func_80084280(gobj);
}
