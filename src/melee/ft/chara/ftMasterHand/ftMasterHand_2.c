#include <melee/ft/chara/ftMasterHand/ftMasterHand.h>

// 8014FDD0 0014C9B0
// https://decomp.me/scratch/HWef2
void ftMasterHand_LoadSpecialAttrs(HSD_GObj* gobj) {
    COPY_ATTRS(gobj, MasterHandAttributes);
}

// 8014FE10 0014C9F0
// https://decomp.me/scratch/JL2E5
void func_8014FE10(HSD_GObj* gobj) {
    if (Stage_80225194() == 0xFB) {
        func_80150144(gobj);
        return;
    }
    func_801510B0(gobj);
}

// 8014FE58 0014CA38
// https://decomp.me/scratch/kfqG6
void func_8014FE58(HSD_GObj* gobj) {
    return;
}

#pragma dont_inline on

// 8014FE5C 0014CA3C
// https://decomp.me/scratch/7T8fr
void func_8014FE5C(HSD_GObj* gobj) {
    Fighter* fp;

    fp = gobj->user_data;
    if ((fp->x10_action_state_index == 341) || (fp->x10_action_state_index == 342)) {
        fp->xB0_pos = fp->sa.masterhand.x2240_pos;
    } else {
        fp->sa.masterhand.x2240_pos = fp->xB0_pos;
    }
    if (fp->sa.masterhand.x2258 == 389) {
        Fighter_ActionStateChange_800693AC(gobj, 341, 0, 0, fp->x894_currentAnimFrame, 1.0f, 0.0f);
    } else {
        Fighter_ActionStateChange_800693AC(gobj, 341, 0, 0, 0.0f, 1.0f, 0.0f);
    }
    fp->sa.masterhand.x2258 = 341;
}

// 8014FF1C 0014CAFC
// https://decomp.me/scratch/cG41T
void func_8014FF1C(HSD_GObj* gobj) {
    Fighter* fp;

    fp = gobj->user_data;
    if ((fp->x10_action_state_index == 341) || (fp->x10_action_state_index == 342)) {
        fp->xB0_pos = fp->sa.masterhand.x2240_pos;
    } else {
        fp->sa.masterhand.x2240_pos = fp->xB0_pos;
    }
    if (fp->sa.masterhand.x2258 == 390) {
        Fighter_ActionStateChange_800693AC(gobj, 342, 0, 0, fp->x894_currentAnimFrame, 1.0f, 0.0f);
    } else {
        Fighter_ActionStateChange_800693AC(gobj, 342, 0, 0, 0.0f, 1.0f, 0.0f);
    }
    fp->sa.masterhand.x2258 = 342;
}

// 8014FFDC 0014CBBC
// https://decomp.me/scratch/0Gtar
void lbl_8014FFDC(HSD_GObj* gobj) {
    Fighter* r31_fp;
    u32 unk[4];

    r31_fp = gobj->user_data;
    if (r31_fp->sa.masterhand.x2258 == 0x186) {
        if ((r31_fp->x10_action_state_index == 0x155) || (r31_fp->x10_action_state_index == 0x156)) {
            r31_fp->xB0_pos = r31_fp->sa.masterhand.x2240_pos;
        } else {
            r31_fp->sa.masterhand.x2240_pos = r31_fp->xB0_pos;
        }
        if (r31_fp->sa.masterhand.x2258 == 0x186) {
            Fighter_ActionStateChange_800693AC(gobj, 0x156, 0, 0, r31_fp->x894_currentAnimFrame, 1.0f, 0.0f);
        } else {
            Fighter_ActionStateChange_800693AC(gobj, 0x156, 0, 0, 0.0f, 1.0f, 0.0f);
        }
        r31_fp->sa.masterhand.x2258 = 0x156;
        return;
    }
    if ((r31_fp->x10_action_state_index == 0x155) || (r31_fp->x10_action_state_index == 0x156)) {
        r31_fp->xB0_pos = r31_fp->sa.masterhand.x2240_pos;
    } else {
        r31_fp->sa.masterhand.x2240_pos = r31_fp->xB0_pos;
    }
    if (r31_fp->sa.masterhand.x2258 == 0x185) {
        Fighter_ActionStateChange_800693AC(gobj, 0x155, 0, 0, r31_fp->x894_currentAnimFrame, 1.0f, 0.0f);
    } else {
        Fighter_ActionStateChange_800693AC(gobj, 0x155, 0, 0, 0.0f, 1.0f, 0.0f);
    }
    r31_fp->sa.masterhand.x2258 = 0x155;
}

// 80150144 0014CD24
// https://decomp.me/scratch/S2AJH
void func_80150144(HSD_GObj* gobj) {
    MasterHandAttributes* r5_attributes;
    Fighter* fp;
    Fighter* fp_1; // todo: dup?
    Vec2 unusedPos;

    fp = gobj->user_data;
    r5_attributes = fp->x10C_ftData->ext_attr;
    fp->sa.masterhand.x2258 = 341;
    fp->x10_action_state_index = 343;
    fp->xB0_pos.x = r5_attributes->x30_pos2.x;
    fp->xB0_pos.y = r5_attributes->x30_pos2.y;
    fp_1 = gobj->user_data;
    if ((fp_1->x10_action_state_index == 341) || (fp_1->x10_action_state_index == 342)) {
        fp_1->xB0_pos = fp_1->sa.masterhand.x2240_pos;
    } else {
        fp_1->sa.masterhand.x2240_pos = fp_1->xB0_pos;
    }
    if (fp_1->sa.masterhand.x2258 == 389) {
        Fighter_ActionStateChange_800693AC(gobj, 341, 0, 0, fp_1->x894_currentAnimFrame, 1.0f, 0.0f);
    } else {
        Fighter_ActionStateChange_800693AC(gobj, 341, 0, 0, 0.0f, 1.0f, 0.0f);
    }
    fp_1->sa.masterhand.x2258 = 341;
}

#pragma dont_inline off

typedef struct {
    u8 a;
    u8 b;
} u8_pair;

struct MasterHandDataStuff {
    u32 x0[14];
    u8 x38[4*4];
    u8_pair x48[6];
    u8 x54[6*5];
};

struct MasterHandDataStuff lbl_803D40D0 = {
    {
        0x0000015D,
        0x0000015B,
        0x0000015F,
        0x00000163,
        0x00000166,
        0x00000167,
        0x00000162,
        0x00000172,
        0x00000173,
        0x0000016F,
        0x0000016A,
        0x0000016D,
        0x0000017B,
        0x0000017C
    },
    {
        0x00, 0x01, 0x02, 0x03,
        0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0A, 0x0B,
        0x0C, 0x0D, 0x00, 0x00
    },
    {
        {0x00, 0x03},
        {0x03, 0x04},
        {0x07, 0x03},
        {0x0A, 0x02},
        {0x0C, 0x02},
        {0x00, 0x00}
    },
    {
        0x01, 0x02, 0x03, 0x04, 0x00,
        0x00, 0x02, 0x03, 0x04, 0x00,
        0x00, 0x01, 0x03, 0x04, 0x00,
        0x00, 0x01, 0x02, 0x04, 0x00,
        0x00, 0x01, 0x02, 0x03, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00
    }
};

inline void lbl_80150230_inline_1(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    if (fp->x10_action_state_index == 0x155 || fp->x10_action_state_index == 0x156) {
        fp->xB0_pos = fp->sa.masterhand.x2240_pos;
    } else {
        fp->sa.masterhand.x2240_pos = fp->xB0_pos;
    }
    if (fp->sa.masterhand.x2258 == 0x186) {
        Fighter_ActionStateChange_800693AC(gobj, 0x156, 0, 0, fp->x894_currentAnimFrame, 1.0f, 0.0f);
    } else {
        Fighter_ActionStateChange_800693AC(gobj, 0x156, 0, 0, 0.0f, 1.0f, 0.0f);
    }
    fp->sa.masterhand.x2258 = 0x156;
}

inline void lbl_80150230_inline_2(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    if (fp->sa.masterhand.x2258 == 0x186) {
        func_8014FF1C(gobj);
    } else {
        func_8014FE5C(gobj);
    }
}

// 80150230 0014CE10
// https://decomp.me/scratch/NJIf7
void lbl_80150230(HSD_GObj* gobj) {
    // r31 = &lbl_803D40D0
    // r30 = fp
    // r29 = ft_inline / attr
    // r28 = gobj
    // r27 = tmp
    // r26 = tmp2?
    Fighter* fp = gobj->user_data;
    s32 unused[2];
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        func_80150894(gobj);
        if (ftAnim_IsFramesRemaining(gobj) == 0) {
            if (fp->x10_action_state_index == 0x155) {
                lbl_80150230_inline_1(gobj);
            } else if (fp->x10_action_state_index == 0x156) {
                lbl_80150230_inline_2(gobj);
            }
        }
    } else {
        if (--fp->sa.masterhand.x223C < 0.0f) {
            MasterHandAttributes* attr = fp->x10C_ftData->ext_attr;
            Vec3 vec;
            s32 unused[6];
            func_8015BD24(fp->x1A98, &fp->sa.masterhand.x223C, fp->sa.masterhand.x2238, attr->x18, attr->x20, attr->x1C);
            if (func_8015C44C(0x1C) == 0x180) {
                // Crazy Hand Combo Attack
                switch (func_8015C4C4()) {
                    case 0x179:
                        vec.x = attr->x124_pos.x;
                        vec.y = attr->x124_pos.y;
                        vec.z = 0.0f;
                        func_80150DC4(gobj, &lbl_80155194, &vec);
                        break;
                    case 0x17A:
                        vec.x = attr->x12C_pos.x;
                        vec.y = attr->x12C_pos.y;
                        vec.z = 0.0f;
                        func_80150DC4(gobj, &lbl_801552F8, &vec);
                        break;
                    case 0x17B:
                        vec.x = attr->x134_pos.x;
                        vec.y = attr->x134_pos.y;
                        vec.z = 0.0f;
                        func_80150DC4(gobj, &lbl_80155484, &vec);
                        break;
                    case 0x17C:
                        vec.x = attr->x13C_pos.x;
                        vec.y = attr->x13C_pos.y;
                        vec.z = 0.0f;
                        break;
                }
            } else {
                s32 tmp;
                s32 tmp2;
                u8_pair *qwe;
                f32 rand;
                if (fp->sa.masterhand.x2254 == attr->x24) {
                    fp->sa.masterhand.x2254 = 0;
                    tmp = 2;
                } else {
                    s32 qwe4 = lbl_803D40D0.x54[fp->sa.masterhand.x224C * 5 + HSD_Randi(5)];
                    tmp = qwe4;
                    if (qwe4 == 2) {
                        fp->sa.masterhand.x2254 = 0;
                    } else {
                        fp->sa.masterhand.x2254++;
                    }
                }
                // cast required, don't know why
                qwe = &((u8_pair*) lbl_803D40D0.x48)[tmp];
                tmp2 = lbl_803D40D0.x0[lbl_803D40D0.x38[qwe->a + HSD_Randi(qwe->b)]];

                fp->sa.masterhand.x224C = tmp;
                fp->sa.masterhand.x2250 = tmp2;
                if (fp->x221D_flag.bits.b4) {
                    tmp2 = 0x155;
                }
                switch(tmp2) {
                    case 0x15B: // Stage-Wide Slap
                        func_80053FF4(0, &vec);
                        vec.y = attr->x38;
                        func_80150DC4(gobj, &lbl_80151828, &vec);
                        break;
                    case 0x15D: // Sweep
                        func_80053FF4(0, &vec);
                        vec.y = attr->x50.y;
                        func_80150DC4(gobj, &lbl_80151BB8, &vec);
                        break;
                    case 0x15F: // Walk
                        vec.x = attr->x40_pos.x;
                        vec.y = attr->x40_pos.y;
                        vec.z = 0.0f;
                        func_80150DC4(gobj, &lbl_80151DC4, &vec);
                        break;
                    case 0x162: // Drill
                        vec.x = attr->x88_pos.x;
                        vec.y = attr->x88_pos.y;
                        vec.z = 0.0f;
                        func_80150DC4(gobj, &lbl_801521DC, &vec);
                        break;
                    case 0x163: // Punch
                        vec.x = attr->xA8_pos.x;
                        vec.y = attr->xA8_pos.y;
                        vec.z = 0.0f;
                        func_80150DC4(gobj, &lbl_80152370, &vec);
                        break;
                    case 0x166: // Ground Slap
                        vec.x = attr->xBC_pos.x;
                        vec.y = attr->xBC_pos.y;
                        vec.z = 0.0f;
                        func_80150DC4(gobj, &lbl_801526D8, &vec);
                        break;
                    case 0x167: // Poke
                        func_80152880(gobj);
                        break;
                    case 0x16F: // Jet
                        func_80153820(gobj);
                        break;
                    case 0x172: // Ram
                        func_801541C8(gobj, &lbl_80153B90);
                        break;
                    case 0x173: // Crush
                        func_801541C8(gobj, &lbl_80153D2C);
                        break;
                    case 0x16A: // Lasers
                        rand = HSD_Randf();
                        vec.x = attr->xCC_pos.x * rand * 2.0f + attr->xC4_pos.x - attr->xCC_pos.x;
                        rand = HSD_Randf();
                        vec.y = attr->xCC_pos.y * rand * 2.0f + attr->xC4_pos.y - attr->xCC_pos.y;
                        vec.z = 0.0f;
                        func_80150DC4(gobj, &lbl_80152BCC, &vec);
                        break;
                    case 0x16D: // Gun
                        func_801530A4(gobj);
                        break;
                    case 0x17B: // Grab
                        func_801542E0(gobj);
                        break;
                    case 0x17C: // Grab
                        func_801542E0(gobj);
                        break;
                }
            }
        } else if (ftAnim_IsFramesRemaining(gobj) == 0) {
            if (fp->x10_action_state_index == 0x155) {
                lbl_80150230_inline_1(gobj);
            } else if (fp->x10_action_state_index == 0x156) {
                lbl_80150230_inline_2(gobj);
            }
        }
    }
}

// 8015082C 0014D40C
// https://decomp.me/scratch/rgMOD
void lbl_8015082C(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        func_8015BD20(gobj);
    }
}

// 80150870 0014D450
// https://decomp.me/scratch/7A7RI
void lbl_80150870(HSD_GObj* gobj) {
    func_80085134(gobj);
}

// 80150890 0014D470
void lbl_80150890(HSD_GObj* gobj) {
    return;
}

// 80150894 0014D474
// https://decomp.me/scratch/nuumS
#define DPAD_LEFT 1
#define DPAD_RIGHT 2
#define DPAD_DOWN 4
#define DPAD_UP 8
#define BUTTON_Z 0x10
#define BUTTON_R 0x20
#define BUTTON_L 0x40
#define BUTTON_A 0x100
#define BUTTON_B 0x200
#define BUTTON_X 0x400
#define BUTTON_Y 0x800
#define BUTTON_START 0x1000
#define r6_button (HSD_PadMasterStatus[2].button)
#include <sysdolphin/baselib/controller.h>
extern HSD_PadStatus HSD_PadMasterStatus[4];
void func_80150894(HSD_GObj* gobj) {
    Fighter* r4_fp = gobj->user_data;
    MasterHandAttributes* r31_attributes = r4_fp->x10C_ftData->ext_attr;
    Vec3 sp10_pos;
    s32 unused;
    u32 l_pressed = r6_button & BUTTON_L;
    // why just l_pressed and not temps for the others?

    if (l_pressed && (r6_button & DPAD_UP)) {
        // Stage-Wide Slap
        func_80053FF4(0, &sp10_pos);
        sp10_pos.y = r31_attributes->x38;
        func_80150DC4(gobj, &lbl_80151828, &sp10_pos);
    } else if (l_pressed && (r6_button & DPAD_RIGHT)) {
        // Sweep
        func_80053FF4(0, &sp10_pos);
        sp10_pos.y = r31_attributes->x50.y;
        func_80150DC4(gobj, &lbl_80151BB8, &sp10_pos);
    } else if (l_pressed && (r6_button & DPAD_DOWN)) {
        // Walk
        sp10_pos.x = r31_attributes->x40_pos.x;
        sp10_pos.y = r31_attributes->x40_pos.y;
        sp10_pos.z = 0.0f;
        func_80150DC4(gobj, &lbl_80151DC4, &sp10_pos);
    } else if ((r6_button & BUTTON_R) && (r6_button & DPAD_UP)) {
        // Drill
        sp10_pos.x = r31_attributes->x88_pos.x;
        sp10_pos.y = r31_attributes->x88_pos.y;
        sp10_pos.z = 0.0f;
        func_80150DC4(gobj, &lbl_801521DC, &sp10_pos);
    } else if ((r6_button & BUTTON_R) && (r6_button & DPAD_RIGHT)) {
        // Punch
        sp10_pos.x = r31_attributes->xA8_pos.x;
        sp10_pos.y = r31_attributes->xA8_pos.y;
        sp10_pos.z = 0.0f;
        func_80150DC4(gobj, &lbl_80152370, &sp10_pos);
    } else if ((r6_button & BUTTON_R) && (r6_button & DPAD_DOWN)) {
        // Ground Slap
        sp10_pos.x = r31_attributes->xBC_pos.x;
        sp10_pos.y = r31_attributes->xBC_pos.y;
        sp10_pos.z = 0.0f;
        func_80150DC4(gobj, &lbl_801526D8, &sp10_pos);
    } else if ((r6_button & BUTTON_R) && (r6_button & DPAD_LEFT)) {
        // Poke
        func_80152880(gobj);
    } else if ((r6_button & BUTTON_A) && (r6_button & DPAD_UP)) {
        // Jet
        func_80153820(gobj);
    } else if ((r6_button & BUTTON_A) && (r6_button & DPAD_RIGHT)) {
        // Ram
        func_801541C8(gobj, &lbl_80153B90);
    } else if ((r6_button & BUTTON_A) && (r6_button & DPAD_DOWN)) {
        // Crush
        func_801541C8(gobj, &lbl_80153D2C);
    } else if ((r6_button & BUTTON_B) && (r6_button & DPAD_UP)) {
        // Lasers
        f32 rand;
        rand = HSD_Randf();
        sp10_pos.x = r31_attributes->xCC_pos.x * rand * 2.0f + r31_attributes->xC4_pos.x - r31_attributes->xCC_pos.x;
        rand = HSD_Randf();
        sp10_pos.y = r31_attributes->xCC_pos.y * rand * 2.0f + r31_attributes->xC4_pos.y - r31_attributes->xCC_pos.y;
        sp10_pos.z = 0.0f;
        func_80150DC4(gobj, &lbl_80152BCC, &sp10_pos);
    } else if ((r6_button & BUTTON_B) && ((r6_button & DPAD_RIGHT))) {
        // Gun
        func_801530A4(gobj);
    } else if ((r6_button & BUTTON_Z) && ((r6_button & DPAD_UP))) {
        // Grab
        r4_fp->sa.masterhand.x2250 = 0x17B;
        func_801542E0(gobj);
    } else if ((r6_button & BUTTON_Z) && ((r6_button & DPAD_RIGHT))) {
        // Grab
        r4_fp->sa.masterhand.x2250 = 0x17C;
        func_801542E0(gobj);
    } else if (((r6_button & BUTTON_Y)) && ((r6_button & DPAD_UP))) {
        // Crazy Hand Combo Attack
        switch (func_8015C4C4()) {
            case 0x179: {
                sp10_pos.x = r31_attributes->x124_pos.x;
                sp10_pos.y = r31_attributes->x124_pos.y;
                sp10_pos.z = 0.0f;
                func_80150DC4(gobj, &lbl_80155194, &sp10_pos);
                break;
            }
            case 0x17A: {
                sp10_pos.x = r31_attributes->x12C_pos.x;
                sp10_pos.y = r31_attributes->x12C_pos.y;
                sp10_pos.z = 0.0f;
                func_80150DC4(gobj, &lbl_801552F8, &sp10_pos);
                break;
            }   
            case 0x17B: {
                sp10_pos.x = r31_attributes->x134_pos.x;
                sp10_pos.y = r31_attributes->x134_pos.y;
                sp10_pos.z = 0.0f;
                func_80150DC4(gobj, &lbl_80155484, &sp10_pos);
                break;
            }
            case 0x17C: {
                sp10_pos.x = r31_attributes->x13C_pos.x;
                sp10_pos.y = r31_attributes->x13C_pos.y;
                sp10_pos.z = 0.0f;
                break;
            }
        }
    }
}
