#include <melee/ft/chara/ftSamus/ftsamus6.h>

#include <melee/ft/chara/ftSamus/ftsamus.h>
#include <melee/ft/code_80081B38.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ft_unknown_006.h>
#include <melee/ft/ftcoll.h>
#include <melee/lb/lbunknown_001.h>

void ftSamus_8012ADF0(HSD_GObj* fighter_gobj)
{
    Vec3 vec;
    bool bool1;
    Fighter* fp = getFighter(fighter_gobj);
    ftSamusAttributes* samus_attr = fp->x2D4_specialAttributes;

/// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused[8];
#endif

    if (fp->x2210_ThrowFlags.b0) {
        fp->x2210_ThrowFlags.b0 = 0;
        bool1 = 1;
    } else {
        bool1 = 0;
    }
    if (bool1) {
        f32 vec_x;
        func_8000B1CC(fp->x5E8_fighterBones[0].x0_jobj, NULL, &vec);
        vec_x = samus_attr->x74_vec.x;
        vec.x += (vec_x * fp->facing_dir);
        vec.y += samus_attr->x74_vec.y;
        vec.z += samus_attr->x74_vec.z;
        func_802B4AC8(fighter_gobj, &vec, fp->facing_dir, vec_x);
        fp->cb.x21BC_callback_Accessory4 = 0;
    }
}

void ftSamus_8012AEBC(HSD_GObj* fighter_gobj)
{
    struct UNK_SAMUS_S2 unk_struct;
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    func_8007B0C0(fighter_gobj, 2);

    unk_struct.intvec.x = 2;
    unk_struct.intvec.y = 1;
    unk_struct.intvec.z = 0;
    unk_struct.vec1.x = unk_struct.vec1.y = unk_struct.vec1.z = 0.0f;
    unk_struct.vec2.x = unk_struct.vec2.y = unk_struct.vec2.z = 0.0f;
    unk_struct.single_float = 3.0f;
    func_8007B5AC(fp, &fp->x11A0_fighterHurtbox[0], &unk_struct);
}

void ftSamus_8012AF38(HSD_GObj* fighter_gobj)
{
    func_8007B0C0(fighter_gobj, 0);
}

void ftSamus_SpecialLw_StartAction_inner(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    fp->x2208_ftcmd_var2 = 0;
    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;
    fp->x2210_ThrowFlags.b0 = 0;
    fp->x2340_stateVar1 = 0;
    if (fp->x894_currentAnimFrame == 3.0f) {
        fp->x2204_ftcmd_var1 = 1;
    }
    fp->cb.x21BC_callback_Accessory4 = &ftSamus_8012ADF0;
}

void ftSamus_SpecialLw_StartAction(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    ftSamusAttributes* samus_attr = fp->x2D4_specialAttributes;

    fp->xEC_ground_vel *= samus_attr->x6C;
    if (fp->action_id == 0x28) {
        Fighter_ActionStateChange_800693AC(fighter_gobj, 0x163, 0, NULL, 3.0f,
                                           1.0f, 0.0f);
        ftSamus_SpecialLw_StartAction_inner(fighter_gobj);
        fp->x2204_ftcmd_var1 = 2;
        ftSamus_8012B5F0(fighter_gobj);
        return;
    }
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x163, 0, NULL, 0.0f, 1.0f,
                                       0.0f);
    func_8006EBA4(fighter_gobj);
    ftSamus_SpecialLw_StartAction_inner(fighter_gobj);
}

void ftSamus_SpecialAirLw_StartAction(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftSamusAttributes* samus_attr = fp->x2D4_specialAttributes;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused[8];
#endif

    fp->x80_self_vel.x *= samus_attr->x70;
    fp->x80_self_vel.y = samus_attr->x58;

    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x164, 0, NULL, 0.0f, 1.0f,
                                       0.0f);
    func_8006EBA4(fighter_gobj);
    ftSamus_SpecialLw_StartAction_inner(fighter_gobj);
}

inline void checkStateVar1(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if ((fp->x2200_ftcmd_var0) && (!fp->x2340_stateVar1)) {
        ftSamus_8012AEBC(fighter_gobj);
        fp->x2340_stateVar1 = 1;
    }
    if ((!fp->x2200_ftcmd_var0) && (fp->x2340_stateVar1)) {
        func_8007B0C0(fighter_gobj, 0);
        fp->x2340_stateVar1 = 0;
    }
}

#ifdef MUST_MATCH
#pragma push
asm void ftSamus_8012B150(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 8012B150 00000000  7C 08 02 A6 */	mflr r0
/* 8012B154 00000004  90 01 00 04 */	stw r0, 0x4(r1)
/* 8012B158 00000008  94 21 FF A8 */	stwu r1, -0x58(r1)
/* 8012B15C 0000000C  93 E1 00 54 */	stw r31, 0x54(r1)
/* 8012B160 00000010  93 C1 00 50 */	stw r30, 0x50(r1)
/* 8012B164 00000014  93 A1 00 4C */	stw r29, 0x4c(r1)
/* 8012B168 00000018  7C 7D 1B 78 */	mr r29, r3
/* 8012B16C 0000001C  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 8012B170 00000020  80 1E 22 04 */	lwz r0, 0x2204(r30)
/* 8012B174 00000024  28 00 00 01 */	cmplwi r0, 0x1
/* 8012B178 00000028  40 82 00 18 */	bne lbl_8012B190
/* 8012B17C 0000002C  38 00 00 02 */	li r0, 0x2
/* 8012B180 00000030  90 1E 22 04 */	stw r0, 0x2204(r30)
/* 8012B184 00000034  7F A3 EB 78 */	mr r3, r29
/* 8012B188 00000038  48 00 04 69 */	bl ftSamus_8012B5F0
/* 8012B18C 0000003C  48 00 00 BC */	b lbl_8012B248
lbl_8012B190:
/* 8012B190 00000040  80 1E 22 00 */	lwz r0, 0x2200(r30)
/* 8012B194 00000044  28 00 00 00 */	cmplwi r0, 0x0
/* 8012B198 00000048  41 82 00 6C */	beq lbl_8012B204
/* 8012B19C 0000004C  80 1E 23 40 */	lwz r0, 0x2340(r30)
/* 8012B1A0 00000050  2C 00 00 00 */	cmpwi r0, 0x0
/* 8012B1A4 00000054  40 82 00 60 */	bne lbl_8012B204
/* 8012B1A8 00000058  38 7D 00 00 */	addi r3, r29, 0x0
/* 8012B1AC 0000005C  38 80 00 02 */	li r4, 0x2
/* 8012B1B0 00000060  4B F4 FF 11 */	bl func_8007B0C0
/* 8012B1B4 00000064  38 00 00 02 */	li r0, 0x2
/* 8012B1B8 00000068  C0 22 A0 28 */	lfs f1, 0.0F
/* 8012B1BC 0000006C  90 01 00 20 */	stw r0, 0x20(r1)
/* 8012B1C0 00000070  3B E0 00 01 */	li r31, 0x1
/* 8012B1C4 00000074  38 00 00 00 */	li r0, 0x0
/* 8012B1C8 00000078  C0 02 A0 2C */	lfs f0, 3.0F
/* 8012B1CC 0000007C  93 E1 00 24 */	stw r31, 0x24(r1)
/* 8012B1D0 00000080  7F C3 F3 78 */	mr r3, r30
/* 8012B1D4 00000084  90 01 00 28 */	stw r0, 0x28(r1)
/* 8012B1D8 00000088  38 9E 11 A0 */	addi r4, r30, 0x11a0
/* 8012B1DC 0000008C  38 A1 00 20 */	addi r5, r1, 0x20
/* 8012B1E0 00000090  D0 21 00 34 */	stfs f1, 0x34(r1)
/* 8012B1E4 00000094  D0 21 00 30 */	stfs f1, 0x30(r1)
/* 8012B1E8 00000098  D0 21 00 2C */	stfs f1, 0x2c(r1)
/* 8012B1EC 0000009C  D0 21 00 40 */	stfs f1, 0x40(r1)
/* 8012B1F0 000000A0  D0 21 00 3C */	stfs f1, 0x3c(r1)
/* 8012B1F4 000000A4  D0 21 00 38 */	stfs f1, 0x38(r1)
/* 8012B1F8 000000A8  D0 01 00 44 */	stfs f0, 0x44(r1)
/* 8012B1FC 000000AC  4B F5 03 B1 */	bl func_8007B5AC
/* 8012B200 000000B0  93 FE 23 40 */	stw r31, 0x2340(r30)
lbl_8012B204:
/* 8012B204 000000B4  80 1E 22 00 */	lwz r0, 0x2200(r30)
/* 8012B208 000000B8  28 00 00 00 */	cmplwi r0, 0x0
/* 8012B20C 000000BC  40 82 00 24 */	bne lbl_8012B230
/* 8012B210 000000C0  80 1E 23 40 */	lwz r0, 0x2340(r30)
/* 8012B214 000000C4  2C 00 00 00 */	cmpwi r0, 0x0
/* 8012B218 000000C8  41 82 00 18 */	beq lbl_8012B230
/* 8012B21C 000000CC  38 7D 00 00 */	addi r3, r29, 0x0
/* 8012B220 000000D0  38 80 00 00 */	li r4, 0x0
/* 8012B224 000000D4  4B F4 FE 9D */	bl func_8007B0C0
/* 8012B228 000000D8  38 00 00 00 */	li r0, 0x0
/* 8012B22C 000000DC  90 1E 23 40 */	stw r0, 0x2340(r30)
lbl_8012B230:
/* 8012B230 000000E0  7F A3 EB 78 */	mr r3, r29
/* 8012B234 000000E4  4B F4 40 05 */	bl ftAnim_IsFramesRemaining
/* 8012B238 000000E8  2C 03 00 00 */	cmpwi r3, 0x0
/* 8012B23C 000000EC  40 82 00 0C */	bne lbl_8012B248
/* 8012B240 000000F0  7F A3 EB 78 */	mr r3, r29
/* 8012B244 000000F4  4B F5 F0 79 */	bl func_8008A2BC
lbl_8012B248:
/* 8012B248 000000F8  80 01 00 5C */	lwz r0, 0x5c(r1)
/* 8012B24C 000000FC  83 E1 00 54 */	lwz r31, 0x54(r1)
/* 8012B250 00000100  83 C1 00 50 */	lwz r30, 0x50(r1)
/* 8012B254 00000104  83 A1 00 4C */	lwz r29, 0x4c(r1)
/* 8012B258 00000108  38 21 00 58 */	addi r1, r1, 0x58
/* 8012B25C 0000010C  7C 08 03 A6 */	mtlr r0
/* 8012B260 00000110  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#else

void ftSamus_8012B150(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (fp->x2204_ftcmd_var1 == 1) {
        fp->x2204_ftcmd_var1 = 2;
        ftSamus_8012B5F0(fighter_gobj);
        return;
    }

    checkStateVar1(fighter_gobj);

    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        func_8008A2BC(fighter_gobj);
    }
}

#endif

#ifdef MUST_MATCH
#pragma push
asm void ftSamus_8012B264(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 8012B264 00000000  7C 08 02 A6 */	mflr r0
/* 8012B268 00000004  90 01 00 04 */	stw r0, 0x4(r1)
/* 8012B26C 00000008  94 21 FF A0 */	stwu r1, -0x60(r1)
/* 8012B270 0000000C  93 E1 00 5C */	stw r31, 0x5c(r1)
/* 8012B274 00000010  93 C1 00 58 */	stw r30, 0x58(r1)
/* 8012B278 00000014  93 A1 00 54 */	stw r29, 0x54(r1)
/* 8012B27C 00000018  7C 7D 1B 78 */	mr r29, r3
/* 8012B280 0000001C  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 8012B284 00000020  80 1E 22 00 */	lwz r0, 0x2200(r30)
/* 8012B288 00000024  28 00 00 00 */	cmplwi r0, 0x0
/* 8012B28C 00000028  41 82 00 6C */	beq lbl_8012B2F8
/* 8012B290 0000002C  80 1E 23 40 */	lwz r0, 0x2340(r30)
/* 8012B294 00000030  2C 00 00 00 */	cmpwi r0, 0x0
/* 8012B298 00000034  40 82 00 60 */	bne lbl_8012B2F8
/* 8012B29C 00000038  38 7D 00 00 */	addi r3, r29, 0x0
/* 8012B2A0 0000003C  38 80 00 02 */	li r4, 0x2
/* 8012B2A4 00000040  4B F4 FE 1D */	bl func_8007B0C0
/* 8012B2A8 00000044  38 00 00 02 */	li r0, 0x2
/* 8012B2AC 00000048  C0 22 A0 28 */	lfs f1, 0.0F
/* 8012B2B0 0000004C  90 01 00 20 */	stw r0, 0x20(r1)
/* 8012B2B4 00000050  3B E0 00 01 */	li r31, 0x1
/* 8012B2B8 00000054  38 00 00 00 */	li r0, 0x0
/* 8012B2BC 00000058  C0 02 A0 2C */	lfs f0, 3.0F
/* 8012B2C0 0000005C  93 E1 00 24 */	stw r31, 0x24(r1)
/* 8012B2C4 00000060  7F C3 F3 78 */	mr r3, r30
/* 8012B2C8 00000064  90 01 00 28 */	stw r0, 0x28(r1)
/* 8012B2CC 00000068  38 9E 11 A0 */	addi r4, r30, 0x11a0
/* 8012B2D0 0000006C  38 A1 00 20 */	addi r5, r1, 0x20
/* 8012B2D4 00000070  D0 21 00 34 */	stfs f1, 0x34(r1)
/* 8012B2D8 00000074  D0 21 00 30 */	stfs f1, 0x30(r1)
/* 8012B2DC 00000078  D0 21 00 2C */	stfs f1, 0x2c(r1)
/* 8012B2E0 0000007C  D0 21 00 40 */	stfs f1, 0x40(r1)
/* 8012B2E4 00000080  D0 21 00 3C */	stfs f1, 0x3c(r1)
/* 8012B2E8 00000084  D0 21 00 38 */	stfs f1, 0x38(r1)
/* 8012B2EC 00000088  D0 01 00 44 */	stfs f0, 0x44(r1)
/* 8012B2F0 0000008C  4B F5 02 BD */	bl func_8007B5AC
/* 8012B2F4 00000090  93 FE 23 40 */	stw r31, 0x2340(r30)
lbl_8012B2F8:
/* 8012B2F8 00000094  80 1E 22 00 */	lwz r0, 0x2200(r30)
/* 8012B2FC 00000098  28 00 00 00 */	cmplwi r0, 0x0
/* 8012B300 0000009C  40 82 00 24 */	bne lbl_8012B324
/* 8012B304 000000A0  80 1E 23 40 */	lwz r0, 0x2340(r30)
/* 8012B308 000000A4  2C 00 00 00 */	cmpwi r0, 0x0
/* 8012B30C 000000A8  41 82 00 18 */	beq lbl_8012B324
/* 8012B310 000000AC  38 7D 00 00 */	addi r3, r29, 0x0
/* 8012B314 000000B0  38 80 00 00 */	li r4, 0x0
/* 8012B318 000000B4  4B F4 FD A9 */	bl func_8007B0C0
/* 8012B31C 000000B8  38 00 00 00 */	li r0, 0x0
/* 8012B320 000000BC  90 1E 23 40 */	stw r0, 0x2340(r30)
lbl_8012B324:
/* 8012B324 000000C0  7F A3 EB 78 */	mr r3, r29
/* 8012B328 000000C4  4B F4 3F 11 */	bl ftAnim_IsFramesRemaining
/* 8012B32C 000000C8  2C 03 00 00 */	cmpwi r3, 0x0
/* 8012B330 000000CC  40 82 00 0C */	bne lbl_8012B33C
/* 8012B334 000000D0  7F A3 EB 78 */	mr r3, r29
/* 8012B338 000000D4  4B FA 13 F9 */	bl func_800CC730
lbl_8012B33C:
/* 8012B33C 000000D8  80 01 00 64 */	lwz r0, 0x64(r1)
/* 8012B340 000000DC  83 E1 00 5C */	lwz r31, 0x5c(r1)
/* 8012B344 000000E0  83 C1 00 58 */	lwz r30, 0x58(r1)
/* 8012B348 000000E4  83 A1 00 54 */	lwz r29, 0x54(r1)
/* 8012B34C 000000E8  38 21 00 60 */	addi r1, r1, 0x60
/* 8012B350 000000EC  7C 08 03 A6 */	mtlr r0
/* 8012B354 000000F0  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#else

void ftSamus_8012B264(HSD_GObj* fighter_gobj)
{
    checkStateVar1(fighter_gobj);
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        func_800CC730(fighter_gobj);
    }
}
#endif

void ftSamus_8012B358(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftSamusAttributes* samus_attr = fp->x2D4_specialAttributes;
    if ((fp->x2208_ftcmd_var2) && (fp->input.x624_lstick_y < samus_attr->x80)) {
        fp->x2208_ftcmd_var2 = 0;
        func_800D638C(fighter_gobj);
    }
}

void ftSamus_8012B3A4(HSD_GObj* fighter_gobj) {}

void ftSamus_8012B3A8(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    ftSamusAttributes* samus_attr = getFtSpecialAttrs(fp);
    attr* ft_attr = &fp->x110_attr;

    if (fp->x2200_ftcmd_var0) {
        func_8007CADC(fp, 0.0f,
                      ft_attr->x110_WalkInitialVelocity * samus_attr->x64,
                      ft_attr->x118_WalkMaximumVelocity * samus_attr->x5C);
        func_8007CB74(fighter_gobj);
    } else {
        func_80084F3C(fighter_gobj);
    }
}

void ftSamus_8012B41C(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftSamusAttributes* samus_attr = fp->x2D4_specialAttributes;
    attr* ft_attr = &fp->x110_attr;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused[8];
#endif
    func_8007D4B8(fp);
    func_8007D3A8(fp, 0.0f,
                  ft_attr->x174_AerialDriftStickMult * samus_attr->x68,
                  ft_attr->x17C_AerialDriftMax * samus_attr->x60);
}

void ftSamus_8012B488(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftSamusAttributes* samus_attr = fp->x2D4_specialAttributes;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused[8];
#endif

    if (fp->x2200_ftcmd_var0) {
        /// @todo Remove cast
        if (!func_80082888(fighter_gobj,
                           (ftCollisionBox*) &samus_attr->height_attributes))
        {
            ftSamus_8012B570(fighter_gobj);
        }
    } else if (!func_800827A0(fighter_gobj)) {
        ftSamus_8012B570(fighter_gobj);
    }
}

void ftSamus_8012B4FC(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftSamusAttributes* samus_attr = fp->x2D4_specialAttributes;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused[8];
#endif

    if (fp->x2200_ftcmd_var0) {
        /// @todo Remove cast
        if (func_800824A0(fighter_gobj,
                          (ftCollisionBox*) &samus_attr->height_attributes))
        {
            ftSamus_8012B668(fighter_gobj);
        }
    } else if (func_80081D0C(fighter_gobj)) {
        ftSamus_8012B668(fighter_gobj);
    }
}

void ftSamus_UnkSetStateAndCb(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    fp->x2204_ftcmd_var1 = 2;
    fp->x2340_stateVar1 = 0;
    fp->cb.x21BC_callback_Accessory4 = &ftSamus_8012ADF0;
}

void ftSamus_8012B570(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    func_8007D5D4(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x164, 0x0C4C509C, NULL,
                                       fp->x894_currentAnimFrame, 1.0f, 0.0f);
    ftSamus_UnkSetStateAndCb(fighter_gobj);
}

void ftSamus_8012B5F0(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftSamusAttributes* samus_attr = getFtSpecialAttrs(fp);
    fp->x80_self_vel.y = samus_attr->x54;
    func_8007D5D4(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x164, 0x0C4C509C, NULL,
                                       fp->x894_currentAnimFrame, 1.0f, 0.0f);
    fp->cb.x21BC_callback_Accessory4 = ftSamus_8012ADF0;
}

void ftSamus_8012B668(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    func_8007D7FC(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x163, 0x0C4C509C, NULL,
                                       fp->x894_currentAnimFrame, 1.0f, 0.0f);
    ftSamus_UnkSetStateAndCb(fighter_gobj);
}
