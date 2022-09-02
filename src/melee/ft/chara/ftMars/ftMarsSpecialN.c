#include <melee/ft/chara/ftMars/ftMars.h>

// 80136744 00133324
// ftMars_SpecialN
// https://decomp.me/scratch/i9Tn0
void ftMars_SpecialN_StartAction(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    MarsAttributes* attrs = fp->x2D4_specialAttributes;
    u32 unused, unused2; // need to eat more stack

    fp->cb.x21EC_callback = &lbl_80136730;

    fp->xEC_ground_vel /= attrs->xC;
    Fighter_ActionStateChange_800693AC(gobj, 0x155, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(gobj);
}

// 801367B8 00133398
// ftMars_SpecialNAir
// https://decomp.me/scratch/4vPWj
void ftMars_SpecialAirN_StartAction(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    MarsAttributes* attrs = fp->x2D4_specialAttributes;
    u32 unused, unused2; // need to eat more stack

    fp->cb.x21EC_callback = &lbl_80136730;

    fp->x80_self_vel.x /= attrs->xC;

    if (fp->x80_self_vel.y <= 0.0f) {
        fp->x80_self_vel.y = 0.0f;
    }

    Fighter_ActionStateChange_800693AC(gobj, 0x159, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(gobj);
}

// 80136844 00133424
// https://decomp.me/scratch/Go6FC
void lbl_80136844(HSD_GObj* gobj) {
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        func_80136E74(gobj);
        if (((Fighter*)gobj->user_data)->x4_fighterKind == FTKIND_MARS) {
            func_800BFFD0(gobj->user_data, 0x63, 0);
        } else {
            func_800BFFD0(gobj->user_data, 0x64, 0);
        }
    }
}

// 801368AC 0013348C
// https://decomp.me/scratch/XBFKN
void lbl_801368AC(HSD_GObj* gobj) {
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        func_80136EAC(gobj);
        if (((Fighter*)gobj->user_data)->x4_fighterKind == FTKIND_MARS) {
            func_800BFFD0(gobj->user_data, 0x63, 0);
        } else {
            func_800BFFD0(gobj->user_data, 0x64, 0);
        }
    }
}

// 80136914 001334F4
void lbl_80136914(HSD_GObj* gobj) {
}

// 80136918 001334F8
void lbl_80136918(HSD_GObj* gobj) {
}

// 8013691C 001334FC
// https://decomp.me/scratch/rfZA7
void lbl_8013691C(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    MarsAttributes* attr = fp->x2D4_specialAttributes;
    u32 unused, unused2; // gobble stack space

    func_8007C930(fp, attr->x10);
    func_8007CB74(gobj);
}

// 8013695C 0013353C
// https://decomp.me/scratch/dKnHk
void lbl_8013695C(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    MarsAttributes* attr = fp->x2D4_specialAttributes;
    u32 unused, unused2;

    func_8007D4B8(fp);
    func_8007CE94(fp, attr->x10);
}

// 801369A4 00133584
// https://decomp.me/scratch/bR5HF
void lbl_801369A4(HSD_GObj* gobj) {
    if (func_80082708(gobj) == 0) {
        func_80136A1C(gobj);
    }
}

// 801369E0 001335C0
// https://decomp.me/scratch/cCPAH
void lbl_801369E0(HSD_GObj* gobj) {
    if (func_80081D0C(gobj) != 0) {
        func_80136A7C(gobj);
    }
}

// 80136A1C 001335FC
// https://decomp.me/scratch/9GhD1
void func_80136A1C(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;

    func_8007D5D4(fp);
    Fighter_ActionStateChange_800693AC(gobj, 0x159, 0x0C4C5084, 0, fp->x894_currentAnimFrame, 1.0f, 0.0f);
}

// 80136A7C 0013365C
// https://decomp.me/scratch/GU6fn
void func_80136A7C(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;

    func_8007D7FC(fp);
    Fighter_ActionStateChange_800693AC(gobj, 0x155, 0x0C4C5084, 0, fp->x894_currentAnimFrame, 1.0f, 0.0f);
}

// 80136ADC 001336BC
// Animation_MarthNeutralBCharge
// https://decomp.me/scratch/jR5uM
void lbl_80136ADC(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    s32* specialAttrs = fp->x2D4_specialAttributes;
    Vec3 sp28;
    s32 unused[7];

    if ((s32)fp->x2340_stateVar1 % 30 == 0) {
        func_8000B1CC(fp->x5E8_fighterBones[func_8007500C(fp, 4)].x0_jobj, 0, &sp28);
        func_800119DC(&sp28, 10, 0.5f, 0.05f, 1.0471975803375244f);
    }
    fp->x2340_stateVar1++;
    if ((s32)fp->x2340_stateVar1 > *specialAttrs * 30) {
        fp->x2200_ftcmd_var0 = 1;
        func_80137354(gobj);
    }
}


// 80136BB4 00133794
// https://decomp.me/scratch/3bMh4
void lbl_80136BB4(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    MarsAttributes* attrs = fp->x2D4_specialAttributes;
    Vec3 sp28;
    s32 unused[7];

    if ((s32)fp->x2340_stateVar1 % 30 == 0) {
        func_8000B1CC(fp->x5E8_fighterBones[func_8007500C(fp, 4)].x0_jobj, 0, &sp28);
        func_800119DC(&sp28, 10, 0.5f, 0.05f, 1.0471975803375244f);
    }
    fp->x2340_stateVar1++;
    if ((s32)fp->x2340_stateVar1 > attrs->x0 * 30) {
        fp->x2200_ftcmd_var0 = 1;
        func_801373B8(gobj);
    }
}

// 80136C8C 0013386C
// Interrupt_MarthNeutralBCharge
// https://decomp.me/scratch/zR8Hv
void lbl_80136C8C(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    if ((fp->input.x65C_heldInputs & 0x200) == 0) {
        fp->x2200_ftcmd_var0 = 0;
        func_80137354(gobj);
    }
}

// 80136CC4 001338A4
// https://decomp.me/scratch/ykJFN
void lbl_80136CC4(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    if ((fp->input.x65C_heldInputs & 0x200) == 0) {
        fp->x2200_ftcmd_var0 = 0;
        func_801373B8(gobj);
    }
}

// 80136CFC 001338DC
// https://decomp.me/scratch/Q3NsK
void lbl_80136CFC(HSD_GObj* gobj) {
    func_80084F3C(gobj);
}

// 80136D1C 001338FC
// https://decomp.me/scratch/LVDnG
void lbl_80136D1C(HSD_GObj* gobj) {
    func_80084EEC(gobj);
}

// 80136D3C 0013391C
// https://decomp.me/scratch/XmmUv
void lbl_80136D3C(HSD_GObj* gobj) {
    if (func_80082708(gobj) == 0) {
        func_80136DB4(gobj);
    }
}

// 80136D78 00133958
// https://decomp.me/scratch/tjkA9
void lbl_80136D78(HSD_GObj* gobj) {
    if (func_80081D0C(gobj) != 0) {
        func_80136E14(gobj);
    }
}

// 80136DB4 00133994
// https://decomp.me/scratch/eJxjC
void func_80136DB4(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;

    func_8007D5D4(gobj->user_data);
    Fighter_ActionStateChange_800693AC(gobj, 0x15A, 0x0C4C5A86, 0, fp->x894_currentAnimFrame, 1.0f, 0.0f);
}

// 80136E14 001339F4
// https://decomp.me/scratch/mzQdp
void func_80136E14(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;

    func_8007D7FC(fp);
    Fighter_ActionStateChange_800693AC(gobj, 0x156, 0x0C4C5A86, 0, fp->x894_currentAnimFrame, 1.0f, 0.0f);
}

// 80136E74 00133A54
// https://decomp.me/scratch/M7HBN
void func_80136E74(HSD_GObj* gobj) {
    Fighter_ActionStateChange_800693AC(gobj, 0x156, 0x1200, 0, 0.0f, 1.0f, 0.0f);
}

// 80136EAC 00133A8C
// https://decomp.me/scratch/RkI7l
void func_80136EAC(HSD_GObj* gobj) {
    Fighter_ActionStateChange_800693AC(gobj, 0x15A, 0x1200, 0, 0.0f, 1.0f, 0.0f);
}

// 80136EE4 00133AC4
// https://decomp.me/scratch/e4mhD
void lbl_80136EE4(HSD_GObj *gobj) {
    s32 ndx;
    MarsAttributes *attr;
    Fighter *fp;

    fp = gobj->user_data;
    attr = fp->x2D4_specialAttributes;
    if (fp->x2200_ftcmd_var0 == 0) {
        s32 hb = (s32)fp;
        ndx = 0;
        while (ndx < 4) {
            if (*(s32*)(hb+0x914) == 1) {
                func_8007ABD0((Hitbox*)(hb+0x914), (f32) (attr->x4 + (s32)fp->x2340_stateVar1 / 30 * attr->x8), gobj);
            }
            ndx++;
            hb += 0x138;
        }
    }
    if (fp->x894_currentAnimFrame == 9.0f) {
        Vec3 position;
        s32 unused1, unused2, unused3, unused4, unused5;
        // JObj_GetWorldPos(r3=JObj,r4=UnkPointer,r5=StoreResult)
        //         Fighter_BonePersonalToCommon
        func_8000B1CC(fp->x5E8_fighterBones[func_8007500C(fp, 4)].x0_jobj, 0, &position);
        // AestheticWindEffect(r3=sourcelocation,r4=duration,f1=radiusSize,f2=effectdegradation,f3=unk)
        func_800119DC(&position, 120, 0.9f, 0.02f, 1.0471975803375244f);
    }
    // FrameTimerCheck
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        // AS_014_Wait_PlayerCheck
        func_8008A2BC(gobj);
    }
    return;
}

// 80137010 00133BF0
// https://decomp.me/scratch/pIor0
void lbl_80137010(HSD_GObj *gobj) {
    s32 ndx;
    MarsAttributes *attr;
    Fighter *fp;

    fp = gobj->user_data;
    attr = fp->x2D4_specialAttributes;
    if (fp->x2200_ftcmd_var0 == 0) {
        // register swap:
        // s32 ndx;
        // for (ndx = 0; ndx < 4; ndx++) {
        //     if (fp->x914[ndx].x0 == 1) {
        //         // Hitbox_ApplyDamageStalingAndMore
        //         func_8007ABD0(&fp->x914[ndx], (f32) (attr->x4 + (s32)fp->x2340_stateVar1 / 30 * attr->x8), gobj);
        //     }
        // }

        // matches but gross:
        s32 hb = (s32)fp;
        ndx = 0;
        while (ndx < 4) {
            if (*(s32*)(hb+0x914) == 1) {
                func_8007ABD0((Hitbox*)(hb+0x914), (f32) (attr->x4 + (s32)fp->x2340_stateVar1 / 30 * attr->x8), gobj);
            }
            ndx++;
            hb += 0x138;
        }
    }
    if (fp->x894_currentAnimFrame == 9.0f) {
        Vec3 position;
        s32 unused1, unused2, unused3, unused4, unused5;
        // JObj_GetWorldPos(r3=JObj,r4=UnkPointer,r5=StoreResult)
        //         Fighter_BonePersonalToCommon
        func_8000B1CC(fp->x5E8_fighterBones[func_8007500C(fp, 4)].x0_jobj, 0, &position);
        // AestheticWindEffect(r3=sourcelocation,r4=duration,f1=radiusSize,f2=effectdegradation,f3=unk)
        func_800119DC(&position, 120, 0.9f, 0.02f, 1.0471975803375244f);
    }
    // FrameTimerCheck
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        // AS_029_Fall
        func_800CC730(gobj);
    }
    return;
}

// 8013713C 00133D1C
void lbl_8013713C(HSD_GObj* gobj) {
}

// 80137140 00133D20
void lbl_80137140(HSD_GObj* gobj) {
}

// 80137144 00133D24
// https://decomp.me/scratch/ZIl0O
void lbl_80137144(HSD_GObj *gobj) {
    // Physics_Friction
    func_80084F3C(gobj);
}

// 80137164 00133D44
// https://decomp.me/scratch/8OwY9
void lbl_80137164(HSD_GObj *gobj) {
    func_80084EEC(gobj);
}

// 80137184 00133D64
// https://decomp.me/scratch/cIi5D
void lbl_80137184(HSD_GObj* gobj) {
    if (func_80082708(gobj) == 0) {
        func_801371FC(gobj);
    }
}

// 801371C0 00133DA0
// https://decomp.me/scratch/rpVpQ
void lbl_801371C0(HSD_GObj* arg0) {
    if (func_80081D0C(arg0) != 0) {
        func_801372A8(arg0);
    }
}

// 801371FC 00133DDC
// https://decomp.me/scratch/5lf3a
void func_801371FC(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    s32 thing;

    if (fp->x2200_ftcmd_var0 == 0) {
        thing = 0x15B;
    } else {
        thing = 0x15C;
    }

    // Air_StoreBool_LoseGroundJump_NoECBfor10Frames
    func_8007D5D4(fp);
    // ActionStateChange
    Fighter_ActionStateChange_800693AC(gobj, thing, 0x0C4C508E, 0, fp->x894_currentAnimFrame, 1.0f, 0.0f);

    if (fp->x2219_flag.bits.b0 == 1) {
        fp->cb.x21D4_callback_EnterHitlag = &efLib_PauseAll;
        fp->cb.x21D8_callback_ExitHitlag = &efLib_ResumeAll;
    }
}

// 801372A8 00133E88
// AS_MarthNeutralBHitAir->Ground
// https://decomp.me/scratch/IV8RT
void func_801372A8(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    s32 thing;

    if (fp->x2200_ftcmd_var0 == 0) {
        thing = 0x157;
    } else {
        thing = 0x158;
    }

    // Air_SetAsGrounded2
    func_8007D7FC(fp);
    // ActionStateChange
    Fighter_ActionStateChange_800693AC(gobj, thing, 0x0C4C508E, 0, fp->x894_currentAnimFrame, 1.0f, 0.0f);

    if (fp->x2219_flag.bits.b0 == 1) {
        fp->cb.x21D4_callback_EnterHitlag = &efLib_PauseAll;
        fp->cb.x21D8_callback_ExitHitlag = &efLib_ResumeAll;
    }
}

// 80137354 00133F34
// AS_RoyNeutralBSwing
// https://decomp.me/scratch/4CbiS
void func_80137354(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    s32 thing;

    if (fp->x2200_ftcmd_var0 == 0) {
        thing = 0x157;
    } else {
        thing = 0x158;
    }

    Fighter_ActionStateChange_800693AC(gobj, thing, 0, 0, 1.0f, 1.0f, 0.0f);
    fp->cb.x21BC_callback_Accessory4 = &lbl_801365A8;
}

// 801373B8 00133F98
// https://decomp.me/scratch/mXbi4
void func_801373B8(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    s32 thing;

    if (fp->x2200_ftcmd_var0 == 0) {
        thing = 0x15B;
    } else {
        thing = 0x15C;
    }

    Fighter_ActionStateChange_800693AC(gobj, thing, 0, 0, 1.0f, 1.0f, 0.0f);
    fp->cb.x21BC_callback_Accessory4 = &lbl_8013666C;
}
