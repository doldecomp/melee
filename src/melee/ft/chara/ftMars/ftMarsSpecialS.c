#include <melee/ft/chara/ftMars/ftMars.h>

// 8013741C 00133FFC
// https://decomp.me/scratch/DLE90
void ftMars_SpecialS_StartAction(HSD_GObj* gobj) {
    Fighter* fp;
    s32 thing;
    s32 unused1, unused2, unused3, unused4;

    ((Fighter*)gobj->user_data)->x80_self_vel.y = 0.0f;
    fp = gobj->user_data;
    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;
    fp->x2340_stateVar1 = 0;

    if (fp->xE0_ground_or_air == GA_Ground) {
        thing = 0x15D;
    } else {
        thing = 0x166;
    }

    Fighter_ActionStateChange_800693AC(gobj, thing, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(gobj);
}

// 801374A0 00134080
// https://decomp.me/scratch/vI96P
void ftMars_SpecialAirS_StartAction(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    Fighter* ft2;
    MarsAttributes* attr = fp->x2D4_specialAttributes;
    s32 thing;
    s32 unused1, unused2;

    fp->x80_self_vel.x = fp->x80_self_vel.x / attr->x14;
    if ((s32)fp->sa.mars.x222C == 0) {
        fp->sa.mars.x222C = 1;
        fp->x80_self_vel.y = attr->x1C;
    } else {
        fp->x80_self_vel.y = 0.0f;
    }

    ft2 = gobj->user_data;
    ft2->x2204_ftcmd_var1 = 0;
    ft2->x2200_ftcmd_var0 = 0;
    ft2->x2340_stateVar1 = 0;

    if (ft2->xE0_ground_or_air == GA_Ground) {
        thing = 0x15D;
    } else {
        thing = 0x166;
    }

    Fighter_ActionStateChange_800693AC(gobj, thing, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(gobj);
}

// 80137558 00134138
// https://decomp.me/scratch/jDGXt
void lbl_80137558(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    s32 thing = ftAnim_IsFramesRemaining(gobj);
    if (thing == 0) {
        if (fp->xE0_ground_or_air == GA_Ground) {
            func_8008A2BC(gobj);
        } else {
            func_800CC730(gobj);
        }
    }
}

// 801375B8 00134198
// https://decomp.me/scratch/tqS1E
void lbl_801375B8(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    if (fp->x2200_ftcmd_var0 != 0) {
        if (fp->x2204_ftcmd_var1 == 0 && (fp->input.x668 & 0x300) != 0) {
            func_80137A9C(gobj);
        }
    } else {
        if ((fp->input.x668 & 0x300) != 0) {
            fp->x2204_ftcmd_var1 = 1;
        }
    }
}

// 80137618 001341F8
// https://decomp.me/scratch/BqYoF
void lbl_80137618(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    MarsAttributes* attr = fp->x2D4_specialAttributes;
    s32 unused1, unused2, unused3, unused4;

    if (fp->xE0_ground_or_air == GA_Ground) {
        // Physics_Friction
        func_80084F3C(gobj);
    } else {
        // subtractF1FromVerticalVelocityAndCheckForTerminalVelocity
        func_8007D494(fp, attr->x20, attr->x24);
        func_8007CE94(fp, attr->x18);
    }
}

// 8013767C 0013425C
// Collision_MarthSideBAir
// https://decomp.me/scratch/GBmCn
void lbl_8013767C(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    s32 unused1, unused2;

    if (fp->xE0_ground_or_air == GA_Ground) {
        // EnvironmentCollision_StopAtLedge
        if (func_800827A0(gobj) == 0) {
            func_801376E8(gobj);
        }
    } else {
        // EnvironmentCollision_CheckForGroundOnly(NoLedgeGrab)
        if (func_80081D0C(gobj) != 0) {
            // MarthSideBAir->Ground
            func_80137748(gobj);
        }
    }
}

// 801376E8 001342C8
// https://decomp.me/scratch/wulEU
void func_801376E8(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    // Air_StoreBool_LoseGroundJump_NoECBfor10Frames
    func_8007D5D4(fp);
    // ActionStateChange
    Fighter_ActionStateChange_800693AC(gobj, 0x166, 0x0C4E508C, 0, fp->x894_currentAnimFrame, 1.0f, 0.0f);
}

// 80137748 00134328
// MarthSideBAirToGround
// https://decomp.me/scratch/fpZ5r
void func_80137748(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    fp->sa.mars.x222C = 0;
    // Air_SetAsGrounded2
    func_8007D7FC(fp);
    // ActionStateChange
    Fighter_ActionStateChange_800693AC(gobj, 0x15D, 0x0C4E508C, 0, fp->x894_currentAnimFrame, 1.0f, 0.0f);
}

// 801377B0 00134390
// https://decomp.me/scratch/baBIS
void lbl_801377B0(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    // FrameTimerCheck
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        if (fp->xE0_ground_or_air == GA_Ground) {
            // AS_014_Wait_PlayerCheck
            func_8008A2BC(gobj);
        } else {
            // AS_029_Fall
            func_800CC730(gobj);
        }
    }
}

// 80137810 001343F0
// https://decomp.me/scratch/wl5uM
void lbl_80137810(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    if (fp->x2200_ftcmd_var0 != 0) {
        if (fp->x2204_ftcmd_var1 == 0 && (fp->input.x668 & 0x300) != 0) {
            func_80137E0C(gobj);
        }
    } else {
        if ((fp->input.x668 & 0x300) != 0) {
            fp->x2204_ftcmd_var1 = 1;
        }
    }
}

// 80137870 00134450
// https://decomp.me/scratch/iRZdQ
void lbl_80137870(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    MarsAttributes* attr = fp->x2D4_specialAttributes;
    s32 unused1, unused2, unused3, unused4;

    if (fp->xE0_ground_or_air == GA_Ground) {
        // Physics_Friction
        func_80084F3C(gobj);
    } else {
        // subtractF1FromVerticalVelocityAndCheckForTerminalVelocity
        func_8007D494(fp, attr->x20, attr->x24);
        func_8007CE94(fp, attr->x18);
    }
}

// 801378D4 001344B4
// Collision_MarthSideB2Air
// https://decomp.me/scratch/MqEA1
void lbl_801378D4(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    s32 unused1, unused2;

    if (fp->xE0_ground_or_air == GA_Ground) {
        // EnvironmentCollision_StopAtLedge
        if (func_800827A0(gobj) == 0) {
            func_80137940(gobj);
        }
    // EnvironmentCollision_CheckForGroundOnly(NoLedgeGrab)
    } else if (func_80081D0C(gobj) != 0) {
        // MarthSideB2Air->Ground
        func_801379D0(gobj);
    }
}

// 80137940 00134520
// https://decomp.me/scratch/HjsYm
void func_80137940(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    s32 thing;

    func_8007D5D4(fp);
    switch (fp->x10_action_state_index) {
        case 0x15E:
            thing = 0x167;
            break;
        case 0x15F:
            thing = 0x168;
            break;
        // default:
        // thing uninitialized
    }
    Fighter_ActionStateChange_800693AC(gobj, thing, 0x0C4E508C, 0, fp->x894_currentAnimFrame, 1.0f, 0.0f);
}

// 801379D0 001345B0
// MarthSideB2AirToGround
// https://decomp.me/scratch/711pp
void func_801379D0(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    s32 thing;

    fp->sa.mars.x222C = 0;
    func_8007D7FC(fp);
    switch (fp->x10_action_state_index) {
        case 0x167:
            thing = 0x15E;
            break;
        case 0x168:
            thing = 0x15F;
            break;
        // default:
        // thing uninitialized
    }
    Fighter_ActionStateChange_800693AC(gobj, thing, 0x0C4E508C, 0, fp->x894_currentAnimFrame, 1.0f, 0.0f);
}

// 80137A68 00134648
// https://decomp.me/scratch/5NC31
void lbl_80137A68(HSD_GObj* gobj) {
    func_80089824(gobj);
    func_800892A0(gobj);
}

// 80137A9C 0013467C
// https://decomp.me/scratch/CVXJ2
void func_80137A9C(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    s32 thing;

    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;
    fp->cb.x21EC_callback = &lbl_80137A68;

    if (fp->input.x624_lstick_y > p_ftCommonData->x21C) {
        if (fp->xE0_ground_or_air == GA_Ground) {
            thing = 0x15E;
        } else {
            thing = 0x167;
        }
    } else {
        if (fp->xE0_ground_or_air == GA_Ground) {
            thing = 0x15F;
        } else {
            thing = 0x168;
        }
    }
    Fighter_ActionStateChange_800693AC(gobj, thing, 0x02000000, 0, 0.0f, 1.0f, 0.0f);
}

// 80137B34 00134714
// https://decomp.me/scratch/nDoR1
void lbl_80137B34(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    // FrameTimerCheck
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        if (fp->xE0_ground_or_air == GA_Ground) {
            // AS_014_Wait_PlayerCheck
            func_8008A2BC(gobj);
        } else {
            // AS_029_Fall
            func_800CC730(gobj);
        }
    }
}

// 80137B94 00134774
// https://decomp.me/scratch/5TRaz
void lbl_80137B94(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;

    if (fp->x2200_ftcmd_var0 != 0) {
        if (fp->x2204_ftcmd_var1 == 0 && (fp->input.x668 & 0x300) != 0) {
            func_80138148(gobj);
        }
    } else {
        if ((fp->input.x668 & 0x300) != 0) {
            fp->x2204_ftcmd_var1 = 1;
        }
    }
}

// 80137BF4 001347D4
// https://decomp.me/scratch/vI7hc
void lbl_80137BF4(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    MarsAttributes* attr = fp->x2D4_specialAttributes;
    s32 unused1, unused2, unused3, unused4;

    if (fp->xE0_ground_or_air == GA_Ground) {
        // somethingFriction
        func_80084FA8(gobj);
    } else {
        // subtractF1FromVerticalVelocityAndCheckForTerminalVelocity
        func_8007D494(fp, attr->x20, attr->x24);
        func_80085204(gobj);
    }
}

// 80137C50 00134830
// https://decomp.me/scratch/uvl0U
void lbl_80137C50(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    s32 unused1, unused2;
    if (fp->xE0_ground_or_air == GA_Ground) {
        // EnvironmentCollision_StopAtLedge
        if (func_800827A0(gobj) == 0) {
            func_80137CBC(gobj);
        }
    } else {
        // EnvironmentCollision_CheckForGroundOnly_NoLedgeGrab
        if (func_80081D0C(gobj) != 0) {
            func_80137D60(gobj);
        }
    }
}

// 80137CBC 0013489C
// https://decomp.me/scratch/vJNoz
void func_80137CBC(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    s32 thing;

    // Air_StoreBool_LoseGroundJump_NoECBfor10Frames
    func_8007D5D4(fp);
    switch (fp->x10_action_state_index) {
        case 0x160:
            thing = 0x169;
            break;
        case 0x162:
            thing = 0x16B;
            break;
        case 0x161:
            thing = 0x16A;
            break;
        // default:
        // thing uninitialized
    }
    // ActionStateChange
    Fighter_ActionStateChange_800693AC(gobj, thing, 0x0C4E508C, 0, fp->x894_currentAnimFrame, 1.0f, 0.0f);
}

// 80137D60 00134940
// https://decomp.me/scratch/yYIRO
void func_80137D60(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    s32 thing;
    fp->sa.mars.x222C = 0;
    // // Air_SetAsGrounded2
    func_8007D7FC(fp);
    switch (fp->x10_action_state_index) {
        case 0x169:
            thing = 0x160;
            break;
        case 0x16B:
            thing = 0x162;
            break;
        case 0x16A:
            thing = 0x161;
            break;
    }
    // ActionStateChange
    Fighter_ActionStateChange_800693AC(gobj, thing, 0x0C4E508C, 0, fp->x894_currentAnimFrame, 1.0f, 0.0f);
}

// 80137E0C 001349EC
// https://decomp.me/scratch/zlWGu
void func_80137E0C(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    s32 thing;

    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;
    fp->cb.x21EC_callback = &lbl_80137A68;

    if (fp->input.x624_lstick_y > p_ftCommonData->x21C) {
        if (fp->xE0_ground_or_air == GA_Ground) {
            thing = 0x160;
        } else {
            thing = 0x169;
        }
    } else {
        if (fp->input.x624_lstick_y < -p_ftCommonData->x21C) {
            if (fp->xE0_ground_or_air == GA_Ground) {
                thing = 0x162;
            } else {
                thing = 0x16B;
            }
        } else {
            if (fp->xE0_ground_or_air == GA_Ground) {
                thing = 0x161;
            } else {
                thing = 0x16A;
            }
        }
    }
    Fighter_ActionStateChange_800693AC(gobj, thing, 0x02000000, 0, 0.0f, 1.0f, 0.0f);
}

// 80137ECC 00134AAC
// https://decomp.me/scratch/5uXTE
void lbl_80137ECC(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    // FrameTimerCheck
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        if (fp->xE0_ground_or_air == GA_Ground) {
            // AS_014_Wait_PlayerCheck
            func_8008A2BC(gobj);
        } else {
            // AS_029_Fall
            func_800CC730(gobj);
        }
    }
}

// 80137F2C 00134B0C
void lbl_80137F2C(HSD_GObj* gobj) {
}

// 80137F30 00134B10
// https://decomp.me/scratch/zDuRP
void lbl_80137F30(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    MarsAttributes* attr = fp->x2D4_specialAttributes;
    s32 unused[4];

    if (fp->xE0_ground_or_air == GA_Ground) {
        // somethingFriction
        func_80084FA8(gobj);
    } else {
        // subtractF1FromVerticalVelocityAndCheckForTerminalVelocity
        func_8007D494(fp, attr->x20, attr->x24);
        func_80085204(gobj);
    }
}

// 80137F8C 00134B6C
// https://decomp.me/scratch/qwYn8
void lbl_80137F8C(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    s32 unused[2];

    if (fp->xE0_ground_or_air == GA_Ground) {
        // EnvironmentCollision_StopAtLedge
        if (func_800827A0(gobj) == 0) {
            func_80137FF8(gobj);
        }
    } else {
        // EnvironmentCollision_CheckForGroundOnly(NoLedgeGrab)
        if (func_80081D0C(gobj) != 0) {
            func_8013809C(gobj);
        }
    }
}

// 80137FF8 00134BD8
// https://decomp.me/scratch/9o4hn
void func_80137FF8(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    s32 thing;
    // Air_StoreBool_LoseGroundJump_NoECBfor10Frames
    func_8007D5D4(fp);
    switch (fp->x10_action_state_index) {
        case 0x163:
            thing = 0x16C;
            break;
        case 0x165:
            thing = 0x16E;
            break;
        case 0x164:
            thing = 0x16D;
            break;
        // default:
        // thing uninitialized
    }
    // ActionStateChange
    Fighter_ActionStateChange_800693AC(gobj, thing, 0x0C4E508C, 0, fp->x894_currentAnimFrame, 1.0f, 0.0f);
}

// 8013809C 00134C7C
// https://decomp.me/scratch/qwafK
void func_8013809C(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    s32 thing;

    fp->sa.mars.x222C = 0;
    // Air_SetAsGrounded2
    func_8007D7FC(fp);
    switch (fp->x10_action_state_index) {
        case 0x16C:
            thing = 0x163;
            break;
        case 0x16E:
            thing = 0x165;
            break;
        case 0x16D:
            thing = 0x164;
            break;
        // default:
        // thing uninitialized
    }
    // ActionStateChange
    Fighter_ActionStateChange_800693AC(gobj, thing, 0x0C4E508C, 0, fp->x894_currentAnimFrame, 1.0f, 0.0f);
}

// 80138148 00134D28
// https://decomp.me/scratch/V6aHf
void func_80138148(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    s32 thing;

    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;
    fp->cb.x21EC_callback = &lbl_80137A68;

    if (fp->input.x624_lstick_y > p_ftCommonData->x21C) {
        if (fp->xE0_ground_or_air == GA_Ground) {
            thing = 0x163;
        } else {
            thing = 0x16C;
        }
    } else {
        if (fp->input.x624_lstick_y < -p_ftCommonData->x21C) {
            if (fp->xE0_ground_or_air == GA_Ground) {
                thing = 0x165;
            } else {
                thing = 0x16E;
            }
        } else {
            if (fp->xE0_ground_or_air == GA_Ground) {
                thing = 0x164;
            } else {
                thing = 0x16D;
            }
        }
    }
    Fighter_ActionStateChange_800693AC(gobj, thing, 0x02000000, 0, 0.0f, 1.0f, 0.0f);
}
