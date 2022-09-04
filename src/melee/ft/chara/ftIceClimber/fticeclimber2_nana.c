#include <melee/ft/chara/ftIceClimber/fticeclimber.h>

/// TODO remove float externs when file is finished and float data is removed from asm
extern f32 lbl_804D9898;


void ftNana_OnLoad(HSD_GObj* fighter_gobj) {
    s32 unused[4];
    Fighter* fp = fighter_gobj->user_data;
    fp->x2222_flag.bits.b4 = 1;
    ftIceClimber_OnLoadForNana(fp);

    {
        ftIceClimberAttributes* attr = fp->x2D4_specialAttributes;
        fp->x40 = attr->xC4;
    }

}

void ftNana_OnDeath(HSD_GObj* fighter_gobj) {
    s32 unused;
    Fighter* fp = fighter_gobj->user_data;
    ftIceClimberAttributes* attr = fp->x2D4_specialAttributes;
    fp->dmg.x18B0 = attr->xC8;
    func_80074A4C(fighter_gobj, 0U, 0);
    func_80074A4C(fighter_gobj, 1U, 0);
    fp->sa.nana.x2234 = 0;
    fp->sa.nana.x222C = 0;
    fp->sa.nana.x2230.bits.b0 = 0;
    fp->sa.nana.x2238 = 0;
    fp->sa.nana.x224C = 0;
    fp->sa.nana.x2250 = lbl_804D9898;
}

void ftNana_80122FAC(HSD_GObj* fighter_gobj) {
    func_801238E4(fighter_gobj);
}

void ftNana_LoadSpecialAttrs(HSD_GObj* fighter_gobj) {
    COPY_ATTRS(fighter_gobj, ftIceClimberAttributes);
}
