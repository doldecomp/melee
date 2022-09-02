#include <melee/ft/chara/ftMars/ftMars.h>

// 801389CC 001355AC
// https://decomp.me/scratch/r3Of5
void ftMars_SpecialLw_StartAction(HSD_GObj* gobj) {
    Fighter* fp;
    u32 unused[2];

    ((Fighter*)gobj->user_data)->x80_self_vel.y = 0.0f;
    Fighter_ActionStateChange_800693AC(gobj, 0x171, 0, NULL, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(gobj);
    fp = gobj->user_data;
    fp->x2204_ftcmd_var1 = 0;
    fp->x2340_stateVar1 = 0;
}

// 80138A30 00135610
// https://decomp.me/scratch/dhCgH
void ftMars_SpecialAirLw_StartAction(HSD_GObj* gobj) {
    Fighter* fp;
    Fighter* ft2;
    MarsAttributes* attr;
    u32 unused[4];

    fp = gobj->user_data;
    attr = fp->x2D4_specialAttributes;
    fp->x80_self_vel.x /= attr->x4C;
    fp->x80_self_vel.y = 0.0f;
    Fighter_ActionStateChange_800693AC(gobj, 0x173, 0, NULL, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(gobj);
    ft2 = gobj->user_data;
    ft2->x2204_ftcmd_var1 = 0;
    ft2->x2340_stateVar1 = 0;
}

// 80138AA8 00135688
// https://decomp.me/scratch/cZhES
void lbl_80138AA8(HSD_GObj* gobj) {
    MarsAttributes* attr;
    Fighter* fp = gobj->user_data;
    u32 unused[4];

    attr = fp->x2D4_specialAttributes;

    if (fp->x2204_ftcmd_var1 == 1) {
        fp->x2204_ftcmd_var1 = 2;
        func_8007B1B8(gobj, &attr->x64, &lbl_80139140);
        fp->x221B_flag.bits.b1 = 1;
        fp->x19B4_shieldUnk = attr->x60;
        fp->x19B8_shieldUnk = attr->x60;
    } else if (fp->x2204_ftcmd_var1 == 0) {
        fp->x221B_flag.bits.b0 = 0;
    }
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        func_8008A2BC(gobj);
    }
}

// 80138B64 00135744
// https://decomp.me/scratch/cXGg1
void lbl_80138B64(HSD_GObj* gobj) {
    MarsAttributes* attr;
    Fighter* fp = gobj->user_data;
    u32 unused[4];

    attr = fp->x2D4_specialAttributes;

    if (fp->x2204_ftcmd_var1 == 1) {
        fp->x2204_ftcmd_var1 = 2;
        func_8007B1B8(gobj, &attr->x64, &lbl_80139140);
        fp->x221B_flag.bits.b1 = 1;
        fp->x19B4_shieldUnk = attr->x60;
        fp->x19B8_shieldUnk = attr->x60;
    } else if (fp->x2204_ftcmd_var1 == 0) {
        fp->x221B_flag.bits.b0 = 0;
    }
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        func_800CC730(gobj);
    }
}


// 80138C20 00135800
void lbl_80138C20(HSD_GObj* gobj) {
}

// 80138C24 00135804
void lbl_80138C24(HSD_GObj* gobj) {
}

// 80138C28 00135808
// https://decomp.me/scratch/14xar
void lbl_80138C28(HSD_GObj* gobj) {
    func_80084F3C(gobj);
    func_8007AEE0(gobj);
}

// 80138C5C 0013583C
// https://decomp.me/scratch/mO6jh
void lbl_80138C5C(HSD_GObj* gobj) {
    Fighter* fp;
    MarsAttributes* attr;
    u32 unused[4];

    fp = gobj->user_data;
    attr = fp->x2D4_specialAttributes;
    func_8007D494(fp, attr->x54, attr->x58);
    func_8007CE94(fp, attr->x50);
    func_8007AEE0(gobj);
}

// 80138CC0 001358A0
// https://decomp.me/scratch/PQPYD
void lbl_80138CC0(HSD_GObj* gobj) {
    if (func_800827A0(gobj) == 0) {
        func_80138D38(gobj);
    }
}

// 80138CFC 001358DC
// https://decomp.me/scratch/ZAAJM
void lbl_80138CFC(HSD_GObj* gobj) {
    if (func_80081D0C(gobj) != 0) {
        func_80138DD0(gobj);
    }
}

// 80138D38 00135918
// https://decomp.me/scratch/Oy4iP
void func_80138D38(HSD_GObj* gobj) {
    Fighter* fp;
    Fighter* ft_2;
    MarsAttributes* attr;
    u32 unused[4];

    fp = gobj->user_data;
    func_8007D5D4(fp);
    Fighter_ActionStateChange_800693AC(gobj, 0x173, 0x0C4C508C, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
    ft_2 = gobj->user_data;
    attr = ft_2->x2D4_specialAttributes;
    if (ft_2->x2204_ftcmd_var1 == 2) {
        func_8007B1B8(gobj, &attr->x64, &lbl_80139140);
        ft_2->x221B_flag.bits.b1 = 1;
    }
}

// 80138DD0 001359B0
// https://decomp.me/scratch/1GmaW
void func_80138DD0(HSD_GObj* gobj) {
    Fighter* fp;
    Fighter* ft_2;
    MarsAttributes* attr;
    s32 unused[4];

    fp = gobj->user_data;
    func_8007D7FC(fp);
    Fighter_ActionStateChange_800693AC(gobj, 0x171, 0x0C4C508C, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
    ft_2 = gobj->user_data;
    attr = ft_2->x2D4_specialAttributes;
    if (ft_2->x2204_ftcmd_var1 == 2) {
        func_8007B1B8(gobj, &attr->x64, &lbl_80139140);
        ft_2->x221B_flag.bits.b1 = 1;
    }
}

// 80138E68 00135A48
// https://decomp.me/scratch/OGvxj
void lbl_80138E68(HSD_GObj* gobj) {
    s32 ndx, hb;
    Fighter* fp;
    s32 sv1;
    s32 unused[2];

    fp = gobj->user_data;
    sv1 = fp->x2340_stateVar1;

    fp->x2340_stateVar1; // required for some reason

    if (sv1 > 0 && func_800872A4(gobj) == FTKIND_EMBLEM) {
        // register swap:
        // for (ndx = 0; ndx < 4; ndx++) {
        //     if (fp->x914[ndx].x0 == 1) {
        //         func_8007ABD0(&fp->x914[ndx], fp->x2340_stateVar1, gobj);
        //     }
        // }

        // matches but gross:
        ndx = 0;
        hb = (s32)fp;
        while (ndx < 4) {
            if (*(s32*)(hb+0x914) == 1) {
                func_8007ABD0((Hitbox*)(hb+0x914), fp->x2340_stateVar1, gobj);
            }
            ndx++;
            hb += 0x138;
        }
    }
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        func_8008A2BC(gobj);
    }
}

// 80138F14 00135AF4
// https://decomp.me/scratch/Jx7Ov
void lbl_80138F14(HSD_GObj* gobj) {
    s32 ndx, hb;
    Fighter* fp;
    s32 sv1;
    s32 unused[2];

    fp = gobj->user_data;
    sv1 = fp->x2340_stateVar1;

    fp->x2340_stateVar1; // required for some reason

    if (sv1 > 0 && func_800872A4(gobj) == FTKIND_EMBLEM) {
        // register swap:
        // for (ndx = 0; ndx < 4; ndx++) {
        //     if (fp->x914[ndx].x0 == 1) {
        //         func_8007ABD0(&fp->x914[ndx], fp->x2340_stateVar1, gobj);
        //     }
        // }

        // matches but gross:
        ndx = 0;
        hb = (s32)fp;
        while (ndx < 4) {
            if (*(s32*)(hb+0x914) == 1) {
                func_8007ABD0((Hitbox*)(hb+0x914), fp->x2340_stateVar1, gobj);
            }
            ndx++;
            hb += 0x138;
        }
    }
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        func_800CC730(gobj);
    }
}

// 80138FC0 00135BA0
void lbl_80138FC0(HSD_GObj* gobj) {
}

// 80138FC4 00135BA4
void lbl_80138FC4(HSD_GObj* gobj) {
}

// 80138FC8 00135BA8
// https://decomp.me/scratch/u66PG
void lbl_80138FC8(HSD_GObj* gobj) {
    func_80084F3C(gobj);
}

// 80138FE8 00135BC8
// https://decomp.me/scratch/QnjxB
void lbl_80138FE8(HSD_GObj* gobj) {
    func_80084EEC(gobj);
}

// 80139008 00135BE8
// https://decomp.me/scratch/2SGFK
void lbl_80139008(HSD_GObj* gobj) {
    if (func_80082708(gobj) == 0) {
        func_80139080(gobj);
    }
}

// 80139044 00135C24
// https://decomp.me/scratch/3W48X
void lbl_80139044(HSD_GObj* gobj) {
    if (func_80081D0C(gobj) != 0) {
        func_801390E0(gobj);
    }
}

// 80139080 00135C60
// https://decomp.me/scratch/w0qtf
void func_80139080(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    func_8007D5D4(fp);
    Fighter_ActionStateChange_800693AC(gobj, 0x174, 0x0C4C508E, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
}

// 801390E0 00135CC0
// https://decomp.me/scratch/qAmn3
void func_801390E0(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    func_8007D7FC(fp);
    Fighter_ActionStateChange_800693AC(gobj, 0x172, 0x0C4C508E, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
}

// 80139140 00135D20
// https://decomp.me/scratch/8uP2v
void lbl_80139140(HSD_GObj* gobj) {
    Fighter* fp;
    Fighter* ft_2;
    MarsAttributes* attr;
    s32 temp_r0;
    s32 thing;
    s32 unused1[1];
    Vec3 sp18;
    s32 unused2[3];

    fp = gobj->user_data;
    attr = fp->x2D4_specialAttributes;
    fp->x2C_facing_direction = fp->x19AC;
    temp_r0 = (s32) fp->x19A4;
    if (temp_r0 > 0) {
        fp->x2340_stateVar1 = (s32) (temp_r0 * attr->x5C);
    }
    func_8000B1CC(fp->x5E8_fighterBones[func_8007500C(fp, 4)].x0_jobj, 0, &sp18);
    func_800119DC(&sp18, 0x78, 0.9f, 0.02f, 1.0471975803375244f);
    if (fp->xE0_ground_or_air == GA_Ground) {
        thing = 0x172;
    } else {
        thing = 0x174;
    }
    Fighter_ActionStateChange_800693AC(gobj, thing, 0, NULL, 0.0f, 1.0f, 0.0f);
    ft_2 = gobj->user_data;
    ft_2->x2219_flag; // required for regalloc
    if (ft_2->x2219_flag.bits.b0 == 0) {
        switch (func_800872A4(gobj)) {
            case 0x12:
                ef_Spawn(0x4F1, gobj, ft_2->x5E8_fighterBones[func_8007500C(ft_2, 0x23)].x0_jobj, &ft_2->x2C_facing_direction);
                break;
            case 0x1A:
                ef_Spawn(0x510, gobj, ft_2->x5E8_fighterBones[func_8007500C(ft_2, 0x23)].x0_jobj, &ft_2->x2C_facing_direction);
                break;
        }
        ft_2->x2219_flag.bits.b0 = 1;
    }
    ft_2->cb.x21D4_callback_EnterHitlag = 0;
    ft_2->cb.x21D8_callback_ExitHitlag = 0;
    ft_2->cb.x21BC_callback_Accessory4 = 0;
}
