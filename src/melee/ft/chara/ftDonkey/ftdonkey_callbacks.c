#include <melee/ft/chara/ftDonkey/ftdonkey.h>

void ftDonkey_OnDeath(HSD_GObj* fighter_gobj) {
    Fighter* fp = fighter_gobj->user_data;
    fp->sa.dk.x222C = 0;
    func_80074A4C(fighter_gobj, 0, 0);
}

void ftDonkey_8010D774(HSD_GObj* fighter_gobj) {
    ftDonkey_DestroyAllEffectsPlus(fighter_gobj);
    ftDonkey_DestroyAllEffects_SpecialHi(fighter_gobj);
}

void ftDonkey_OnItemPickup(HSD_GObj* fighter_gobj, BOOL bool) {
    Fighter_OnItemPickup(fighter_gobj, bool, 1, 1);
}

void ftDonkey_OnItemInvisible(HSD_GObj* fighter_gobj) {
    Fighter_OnItemInvisible(fighter_gobj, 1);
}

void ftDonkey_OnItemVisible(HSD_GObj* fighter_gobj) {
    Fighter_OnItemVisible(fighter_gobj, 1);
}

void ftDonkey_OnItemDrop(HSD_GObj* gobj, BOOL bool1)
{
    Fighter_OnItemDrop(gobj, bool1, 1, 1);
}

void func_8010D96C(HSD_GObj* fighter_gobj) {
    Fighter* fp = fighter_gobj->user_data;
    ftDonkeyAttributes* attr = fp->x2D4_specialAttributes;
    if (fp->sa.dk.x222C == attr->SpecialN.x2C_MAX_ARM_SWINGS) {
        func_800BFFD0(fp, 0x39, 0);
    }
}


void ftDonkey_OnLoad(HSD_GObj* fighter_gobj) {
    Fighter* fp = fighter_gobj->user_data;
    ftData* ftdata = fp->x10C_ftData;
    ftDonkeyAttributes* ftData_attr = ftdata->ext_attr;
    
    ftData_attr->x8 = func_8001E8F8(func_80085E50(fp, 0x128U));
    ftData_attr->xC = func_8001E8F8(func_80085E50(fp, 0x129U));
    ftData_attr->x10 = func_8001E8F8(func_80085E50(fp, 0x12AU));
    PUSH_ATTRS(fp, ftDonkeyAttributes);
    
    fp->x2222_flag.bits.b0 = 1;
    fp->x2CC = fp->x2D4_specialAttributes;
}

void ftDonkey_LoadSpecialAttrs(HSD_GObj* fighter_gobj) {
    COPY_ATTRS(fighter_gobj, ftDonkeyAttributes);
}

void ftDonkey_OnKnockbackEnter(HSD_GObj* fighter_gobj) {
    Fighter_OnKnockbackEnter(fighter_gobj, 1);
}

void ftDonkey_OnKnockbackExit(HSD_GObj* fighter_gobj) {
    Fighter_OnKnockbackExit(fighter_gobj, 1);
}

void ftDonkey_8010DB3C(HSD_GObj* fighter_gobj) { 
    s32 unused[2]; /// can't remove with get inlines
    BOOL bool1;
    Fighter* fp = fighter_gobj->user_data;
    ftDonkeyAttributes* donkey_attr = fp->x2D4_specialAttributes;
    CollData* colldata = &fp->x6F0_collData; 

    if (fp->x2210_ThrowFlags.b3) {
        fp->x2210_ThrowFlags.b3 = 0;
        bool1 = 1;
    } else {
        bool1 = 0;
    }
    
    if ((bool1) && ((colldata->x134_envFlags & 0x18000))) {
        Vec vec_list[4];

        s32 i;
        for (i = 0; i < 4; i++) {

            f32 temp_f5 = (donkey_attr->SpecialLw.x68 * i) - (donkey_attr->SpecialLw.x68 * 1.5f);
            f32 temp_f3 = donkey_attr->SpecialLw.x6C * fp->x2C_facing_direction;
            f32 temp_f6 = temp_f5 + temp_f3;

            if (!func_80056C54(
                    colldata->x14C_ground.index, 
                    &fp->xB0_pos, 
                    0, 
                    &vec_list[i], 
                    0, 
                    0, 
                    temp_f6,
                    donkey_attr->SpecialLw.x70, 
                    donkey_attr->SpecialLw.x68 * 1.5f, 
                    donkey_attr->SpecialLw.x68
                )) {

                vec_list[i] = fp->xB0_pos;
            }

            vec_list[i].y += 2.0f; 
            func_8007B8A8(&fp->x914[i], &vec_list[i]);
        }
    }
}
