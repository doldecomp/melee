#include "ftpikachu.h"

s32 func_801275CC(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;

    s32 value = fighter->x2071_alt.b0_3;

    switch (value) {
        case 1: 
        case 2: 
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
            return 1;
        default:
            return 0;

    }

}

void func_80127608(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    func_80030E44(2, &fighter->xB0_pos);
    func_8007EBAC(fighter, 0xB, 0);
}

void func_8012764C(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    fighter->x2344_stateVar2 = 3;
}


inline f32 nested_sum_fabs(f32 fighter_pos_y, f32 pika_attr_xBC, f32 pika_attr_xBC_abs, f32 vec_y) {
    if (fighter_pos_y + pika_attr_xBC_abs - vec_y < 0.0f) {
        return -(fighter_pos_y + fabs_inline(pika_attr_xBC) - vec_y);
    } else {
        return fighter_pos_y + fabs_inline(pika_attr_xBC) - vec_y;
    }
}

s32 func_8012765C(HSD_GObj* fighterObj) {
    Vec vec;
    Fighter* fighter = fighterObj->user_data;
    ftPikachuAttributes* pika_attr = fighter->x2D4_specialAttributes;
    u32 state_var = fighter->x2340_stateVar1_u32;

    if (!fighter->x2344_stateVar2_s32) {
        return 0;
    }

    if (state_var) {
        func_802B1FE8(state_var, &vec);
    } else {
        return 0;
    }
    

    if (fabs_inline(fighter->xB0_pos.x - vec.x) < fabs_inline(pika_attr->xC4)) {

        f32 final_y_pos = nested_sum_fabs(fighter->xB0_pos.y, pika_attr->xBC, fabs_inline(pika_attr->xBC), vec.y);

        if (
            (final_y_pos < pika_attr->xC8) 
            && 
            fighter->x2340_stateVar1_u32 
            && 
            !func_802B1DEC(fighter->x2340_stateVar1_u32)
        )
        {
            func_802B1FC8(fighter->x2340_stateVar1_u32);
            return 1;
        }
    }
    

    return 0;
}

void func_8012779C(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    fighter->x2344_stateVar2 = 0;
}

void func_801277AC(HSD_GObj* fighterObj) {
    s32 unused;
    Vec vec1;
    Vec vec2;
    Vec vec3;
    s32 unused2[2];
    
    Fighter* fighter;
    ftPikachuAttributes* pika_attr;
    BOOL flag_check;

    fighter = fighterObj->user_data;
    pika_attr = fighter->x2D4_specialAttributes;
    
    if (fighter->x2210_ThrowFlags.b0) {
        fighter->x2210_ThrowFlags.b0 = 0;
        flag_check = 1;
    } else {
        flag_check = 0;
    }
    if (flag_check && !fighter->x2340_stateVar1_u32) {
        vec1 = fighter->xB0_pos;

        vec1.y += pika_attr->xD0;
        vec2 = vec1;
        vec2.y += pika_attr->xCC;
        ef_Spawn(0x4C3, fighterObj, &vec2);
        {
            vec3.z = 0.0f;
            vec3.x = 0.0f;
            vec3.y = pika_attr->xC0;
            fighter->x2340_stateVar1 = func_802B1DF8(fighterObj, &vec1, &vec3, pika_attr->xD4, pika_attr->xD8, pika_attr->xDC);
    
        }
    }
}