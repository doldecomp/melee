#include <platform.h>
#include "ft/forward.h"
#include "it/forward.h"
#include <baselib/forward.h>

#include "ftPe_SpecialLw.h"

#include "ftPe_Init.h"

#include "ef/efsync.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftcommon.h"
#include "ft/types.h"
#include "ftPeach/types.h"
#include "it/it_27CF.h"
#include "lb/lb_00B0.h"

#include <placeholder.h>
#include <baselib/random.h>

/* 11CE48 */ static bool pickVeg(HSD_GObj* gobj);
/* 11D018 */ static void spawnVeg(HSD_GObj* gobj);
/* 11D214 */ static void handleAirColl(HSD_GObj* gobj);
/* 11D280 */ static void handleColl(HSD_GObj* gobj);

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
static asm bool pickVeg(HSD_GObj* gobj)
{
    // clang-format off
    nofralloc
/* 8011CE48 00119A28  7C 08 02 A6 */	mflr r0
/* 8011CE4C 00119A2C  38 E0 00 00 */	li r7, 0
/* 8011CE50 00119A30  90 01 00 04 */	stw r0, 4(r1)
/* 8011CE54 00119A34  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8011CE58 00119A38  93 E1 00 24 */	stw r31, 0x24(r1)
/* 8011CE5C 00119A3C  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 8011CE60 00119A40  38 60 00 00 */	li r3, 0
/* 8011CE64 00119A44  80 84 02 D4 */	lwz r4, 0x2d4(r4)
/* 8011CE68 00119A48  80 C4 00 10 */	lwz r6, 0x10(r4)
/* 8011CE6C 00119A4C  3B E4 00 00 */	addi r31, r4, 0
/* 8011CE70 00119A50  2C 06 00 00 */	cmpwi r6, 0
/* 8011CE74 00119A54  40 81 00 98 */	ble lbl_8011CF0C
/* 8011CE78 00119A58  2C 06 00 08 */	cmpwi r6, 8
/* 8011CE7C 00119A5C  38 86 FF F8 */	addi r4, r6, -8
/* 8011CE80 00119A60  40 81 00 E4 */	ble lbl_8011CF64
/* 8011CE84 00119A64  38 04 00 07 */	addi r0, r4, 7
/* 8011CE88 00119A68  54 00 E8 FE */	srwi r0, r0, 3
/* 8011CE8C 00119A6C  2C 04 00 00 */	cmpwi r4, 0
/* 8011CE90 00119A70  7C 09 03 A6 */	mtctr r0
/* 8011CE94 00119A74  38 BF 00 00 */	addi r5, r31, 0
/* 8011CE98 00119A78  40 81 00 CC */	ble lbl_8011CF64
lbl_8011CE9C:
/* 8011CE9C 00119A7C  80 85 00 18 */	lwz r4, 0x18(r5)
/* 8011CEA0 00119A80  38 E7 00 08 */	addi r7, r7, 8
/* 8011CEA4 00119A84  80 05 00 20 */	lwz r0, 0x20(r5)
/* 8011CEA8 00119A88  7C 63 22 14 */	add r3, r3, r4
/* 8011CEAC 00119A8C  80 85 00 28 */	lwz r4, 0x28(r5)
/* 8011CEB0 00119A90  7C 63 02 14 */	add r3, r3, r0
/* 8011CEB4 00119A94  80 05 00 30 */	lwz r0, 0x30(r5)
/* 8011CEB8 00119A98  7C 63 22 14 */	add r3, r3, r4
/* 8011CEBC 00119A9C  80 85 00 38 */	lwz r4, 0x38(r5)
/* 8011CEC0 00119AA0  7C 63 02 14 */	add r3, r3, r0
/* 8011CEC4 00119AA4  80 05 00 40 */	lwz r0, 0x40(r5)
/* 8011CEC8 00119AA8  7C 63 22 14 */	add r3, r3, r4
/* 8011CECC 00119AAC  80 85 00 48 */	lwz r4, 0x48(r5)
/* 8011CED0 00119AB0  7C 63 02 14 */	add r3, r3, r0
/* 8011CED4 00119AB4  80 05 00 50 */	lwz r0, 0x50(r5)
/* 8011CED8 00119AB8  7C 63 22 14 */	add r3, r3, r4
/* 8011CEDC 00119ABC  7C 63 02 14 */	add r3, r3, r0
/* 8011CEE0 00119AC0  38 A5 00 40 */	addi r5, r5, 0x40
/* 8011CEE4 00119AC4  42 00 FF B8 */	bdnz lbl_8011CE9C
/* 8011CEE8 00119AC8  48 00 00 7C */	b lbl_8011CF64
lbl_8011CEEC:
/* 8011CEEC 00119ACC  7C 07 30 50 */	subf r0, r7, r6
/* 8011CEF0 00119AD0  7C 07 30 00 */	cmpw r7, r6
/* 8011CEF4 00119AD4  7C 09 03 A6 */	mtctr r0
/* 8011CEF8 00119AD8  40 80 00 14 */	bge lbl_8011CF0C
lbl_8011CEFC:
/* 8011CEFC 00119ADC  80 04 00 18 */	lwz r0, 0x18(r4)
/* 8011CF00 00119AE0  38 84 00 08 */	addi r4, r4, 8
/* 8011CF04 00119AE4  7C 63 02 14 */	add r3, r3, r0
/* 8011CF08 00119AE8  42 00 FF F4 */	bdnz lbl_8011CEFC
lbl_8011CF0C:
/* 8011CF0C 00119AEC  48 26 36 75 */	bl HSD_Randi
/* 8011CF10 00119AF0  80 FF 00 18 */	lwz r7, 0x18(r31)
/* 8011CF14 00119AF4  7F E4 FB 78 */	mr r4, r31
/* 8011CF18 00119AF8  80 BF 00 10 */	lwz r5, 0x10(r31)
/* 8011CF1C 00119AFC  39 00 FF FF */	li r8, -1
/* 8011CF20 00119B00  38 C0 00 00 */	li r6, 0
/* 8011CF24 00119B04  48 00 00 20 */	b lbl_8011CF44
lbl_8011CF28:
/* 8011CF28 00119B08  7C 03 38 00 */	cmpw r3, r7
/* 8011CF2C 00119B0C  40 80 00 08 */	bge lbl_8011CF34
/* 8011CF30 00119B10  7C C8 33 78 */	mr r8, r6
lbl_8011CF34:
/* 8011CF34 00119B14  80 04 00 20 */	lwz r0, 0x20(r4)
/* 8011CF38 00119B18  38 84 00 08 */	addi r4, r4, 8
/* 8011CF3C 00119B1C  38 C6 00 01 */	addi r6, r6, 1
/* 8011CF40 00119B20  7C E7 02 14 */	add r7, r7, r0
lbl_8011CF44:
/* 8011CF44 00119B24  7C 06 28 00 */	cmpw r6, r5
/* 8011CF48 00119B28  40 80 00 0C */	bge lbl_8011CF54
/* 8011CF4C 00119B2C  2C 08 FF FF */	cmpwi r8, -1
/* 8011CF50 00119B30  41 82 FF D8 */	beq lbl_8011CF28
lbl_8011CF54:
/* 8011CF54 00119B34  55 00 18 38 */	slwi r0, r8, 3
/* 8011CF58 00119B38  7C 7F 02 14 */	add r3, r31, r0
/* 8011CF5C 00119B3C  80 63 00 1C */	lwz r3, 0x1c(r3)
/* 8011CF60 00119B40  48 00 00 10 */	b lbl_8011CF70
lbl_8011CF64:
/* 8011CF64 00119B44  54 E0 18 38 */	slwi r0, r7, 3
/* 8011CF68 00119B48  7C 9F 02 14 */	add r4, r31, r0
/* 8011CF6C 00119B4C  4B FF FF 80 */	b lbl_8011CEEC
lbl_8011CF70:
/* 8011CF70 00119B50  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8011CF74 00119B54  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 8011CF78 00119B58  38 21 00 28 */	addi r1, r1, 0x28
/* 8011CF7C 00119B5C  7C 08 03 A6 */	mtlr r0
/* 8011CF80 00119B60  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

bool pickVeg(HSD_GObj* gobj)
{
    int ret0;
    int var_r3 = 0;
    ftPe_DatAttrs* da0 = GET_FIGHTER(gobj)->dat_attrs;
    {
        {
            int da_x10 = da0->x10;
            if (da_x10 > 0) {
                int temp_r4_2 = da_x10 - 8;
                int var_r7 = 0;
                if (da_x10 > 8) {
                    {
                        u32 i = (u32) (temp_r4_2 + 7) >> 3U;
                        {
                            // ftPe_DatAttrs* da1 = da0;
                            if (temp_r4_2 > 0) {
                                do {
                                    var_r7 += 8;
                                    // var_r3 = var_r3 + da1->x18 +
                                    // da1->x20 +
                                    //          da1->x28 + da1->x30 +
                                    //          da1->x38 + da1->x40 +
                                    //          da1->x28 + da1->x50;
                                    // da1 += 0x40;
                                    i -= 1;
                                } while (i != 0);
                            }
                        }
                    }
                }
                {
                    M2C_UNK var_r4 = (M2C_UNK) (da0 + (var_r7 * 8));
                    {
                        int i = da_x10 - var_r7;
                        if (var_r7 < da_x10) {
                            do {
                                s32 temp_r0 = M2C_FIELD(var_r4, s32*, 0x18);
                                var_r4 += 8;
                                var_r3 += temp_r0;
                                i -= 1;
                            } while (i != 0);
                        }
                    }
                }
            }
        }
    }
    ret0 = HSD_Randi(var_r3);
    {
        s32 da_x18;
        da_x18 = da0->x18;
        {
            ftPe_DatAttrs* da2 = da0;
            {
                s32 var_r8;
                var_r8 = -1;
                {
                    int var_r6 = 0;
                    {
                    loop_11:
                        if ((var_r6 < da0->x10) && (var_r8 == -1)) {
                            if (ret0 < da_x18) {
                                var_r8 = var_r6;
                            }
                            {
                                s32 da_x20;
                                da_x20 = M2C_FIELD(da2, s32*, 0x20);
                                da2 += 8;
                                var_r6 += 1;
                                da_x18 += da_x20;
                            }
                            goto loop_11;
                        }
                    }
                }
                return M2C_FIELD((da0 + (var_r8 * 8)), s32*, 0x1C);
            }
        }
    }
}
#endif

void ftPe_SpecialLw_UnsetVeg(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.pe.veg_gobj != NULL) {
        fp->fv.pe.veg_gobj = NULL;
    }
}

void ftPe_SpecialLw_8011CFA0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_GObj* veg_gobj = fp->fv.pe.veg_gobj;
    if (veg_gobj != NULL) {
        HSD_GObj* item_gobj = fp->item_gobj;
        if (veg_gobj == item_gobj &&
            itGetKind(item_gobj) == It_Kind_Peach_Turnip)
        {
            it_802BD45C(fp->fv.pe.veg_gobj);
            ftPe_SpecialLw_UnsetVeg(gobj);
        }
    }
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
static asm void spawnVeg(HSD_GObj* gobj)
{ // clang-format off
    nofralloc
/* 8011D018 00119BF8  7C 08 02 A6 */	mflr r0
/* 8011D01C 00119BFC  90 01 00 04 */	stw r0, 4(r1)
/* 8011D020 00119C00  94 21 FF B0 */	stwu r1, -0x50(r1)
/* 8011D024 00119C04  93 E1 00 4C */	stw r31, 0x4c(r1)
/* 8011D028 00119C08  93 C1 00 48 */	stw r30, 0x48(r1)
/* 8011D02C 00119C0C  93 A1 00 44 */	stw r29, 0x44(r1)
/* 8011D030 00119C10  7C 7D 1B 78 */	mr r29, r3
/* 8011D034 00119C14  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 8011D038 00119C18  88 7E 22 10 */	lbz r3, 0x2210(r30)
/* 8011D03C 00119C1C  54 60 CF FF */	rlwinm. r0, r3, 0x19, 0x1f, 0x1f
/* 8011D040 00119C20  41 82 00 18 */	beq lbl_8011D058
/* 8011D044 00119C24  38 00 00 00 */	li r0, 0
/* 8011D048 00119C28  50 03 3E 30 */	rlwimi r3, r0, 7, 0x18, 0x18
/* 8011D04C 00119C2C  98 7E 22 10 */	stb r3, 0x2210(r30)
/* 8011D050 00119C30  38 00 00 01 */	li r0, 1
/* 8011D054 00119C34  48 00 00 08 */	b lbl_8011D05C
lbl_8011D058:
/* 8011D058 00119C38  38 00 00 00 */	li r0, 0
lbl_8011D05C:
/* 8011D05C 00119C3C  2C 00 00 00 */	cmpwi r0, 0
/* 8011D060 00119C40  41 82 00 A0 */	beq lbl_8011D100
/* 8011D064 00119C44  80 7E 05 E8 */	lwz r3, 0x5e8(r30)
/* 8011D068 00119C48  38 A1 00 34 */	addi r5, r1, 0x34
/* 8011D06C 00119C4C  38 80 00 00 */	li r4, 0
/* 8011D070 00119C50  80 63 06 D0 */	lwz r3, 0x6d0(r3)
/* 8011D074 00119C54  4B EE E1 59 */	bl lb_8000B1CC
/* 8011D078 00119C58  80 7D 00 2C */	lwz r3, 0x2c(r29)
/* 8011D07C 00119C5C  3B E0 00 63 */	li r31, 0x63
/* 8011D080 00119C60  80 63 02 D4 */	lwz r3, 0x2d4(r3)
/* 8011D084 00119C64  80 63 00 14 */	lwz r3, 0x14(r3)
/* 8011D088 00119C68  48 26 34 F9 */	bl HSD_Randi
/* 8011D08C 00119C6C  2C 03 00 00 */	cmpwi r3, 0
/* 8011D090 00119C70  40 82 00 10 */	bne lbl_8011D0A0
/* 8011D094 00119C74  7F A3 EB 78 */	mr r3, r29
/* 8011D098 00119C78  4B FF FD B1 */	bl pickVeg
/* 8011D09C 00119C7C  7C 7F 1B 78 */	mr r31, r3
lbl_8011D0A0:
/* 8011D0A0 00119C80  80 9E 01 0C */	lwz r4, 0x10c(r30)
/* 8011D0A4 00119C84  7F E6 FB 78 */	mr r6, r31
/* 8011D0A8 00119C88  C0 3E 00 2C */	lfs f1, 0x2c(r30)
/* 8011D0AC 00119C8C  7F A3 EB 78 */	mr r3, r29
/* 8011D0B0 00119C90  80 84 00 08 */	lwz r4, 8(r4)
/* 8011D0B4 00119C94  88 A4 00 10 */	lbz r5, 0x10(r4)
/* 8011D0B8 00119C98  38 81 00 34 */	addi r4, r1, 0x34
/* 8011D0BC 00119C9C  48 1A 03 F1 */	bl it_802BD4AC
/* 8011D0C0 00119CA0  90 7E 19 74 */	stw r3, 0x1974(r30)
/* 8011D0C4 00119CA4  28 03 00 00 */	cmplwi r3, 0
/* 8011D0C8 00119CA8  90 7E 22 48 */	stw r3, 0x2248(r30)
/* 8011D0CC 00119CAC  41 82 00 34 */	beq lbl_8011D100
/* 8011D0D0 00119CB0  38 7D 00 00 */	addi r3, r29, 0
/* 8011D0D4 00119CB4  38 80 00 00 */	li r4, 0
/* 8011D0D8 00119CB8  4B F7 77 41 */	bl ft_80094818
/* 8011D0DC 00119CBC  38 9D 00 00 */	addi r4, r29, 0
/* 8011D0E0 00119CC0  4C C6 31 82 */	crclr 6
/* 8011D0E4 00119CC4  38 BE 00 B0 */	addi r5, r30, 0xb0
/* 8011D0E8 00119CC8  38 60 04 D2 */	li r3, 0x4d2
/* 8011D0EC 00119CCC  4B F4 2C F1 */	bl efSync_Spawn
/* 8011D0F0 00119CD0  3C 60 80 12 */	lis r3, ftPe_Init_8011B704@ha
/* 8011D0F4 00119CD4  38 03 B7 04 */	addi r0, r3, ftPe_Init_8011B704@l
/* 8011D0F8 00119CD8  90 1E 21 E4 */	stw r0, 0x21e4(r30)
/* 8011D0FC 00119CDC  90 1E 21 DC */	stw r0, 0x21dc(r30)
lbl_8011D100:
/* 8011D100 00119CE0  80 01 00 54 */	lwz r0, 0x54(r1)
/* 8011D104 00119CE4  83 E1 00 4C */	lwz r31, 0x4c(r1)
/* 8011D108 00119CE8  83 C1 00 48 */	lwz r30, 0x48(r1)
/* 8011D10C 00119CEC  83 A1 00 44 */	lwz r29, 0x44(r1)
/* 8011D110 00119CF0  38 21 00 50 */	addi r1, r1, 0x50
/* 8011D114 00119CF4  7C 08 03 A6 */	mtlr r0
/* 8011D118 00119CF8  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

static HSD_GObj* getVeg(HSD_GObj* gobj, Vec3* pos)
{
    {
        ItemKind kind = It_Kind_Peach_Turnip;
        Fighter* fp = GET_FIGHTER(gobj);
        ftPe_DatAttrs* da = fp->dat_attrs;
        int da_x14 = da->x14;
        if (HSD_Randi(da_x14) == 0) {
            kind = pickVeg(gobj);
        }
        return it_802BD4AC(gobj, pos, fp->ft_data->x8->unk10, kind,
                           fp->facing_dir);
    }
}

static void spawnVeg(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ftCheckThrowB0(fp)) {
        Vec3 pos;
        lb_8000B1CC(fp->parts[FtPart_109].x0_jobj, NULL, &pos);
        {
            HSD_GObj* veg_gobj = getVeg(gobj, &pos);
            fp->item_gobj = veg_gobj;
            fp->fv.pe.veg_gobj = veg_gobj;
            if (veg_gobj != NULL) {
                ft_80094818(gobj, false);
                efSync_Spawn(1234, gobj, &fp->cur_pos);
                fp->cb.x21E4_callback_OnDeath2 = ftPe_Init_8011B704;
                fp->cb.x21DC_callback_OnTakeDamage = ftPe_Init_8011B704;
            }
        }
    }
}
#endif

static bool throwVegIfHeld(HSD_GObj* gobj, FtMotionId msid)
{
    HSD_GObj* igobj = GET_FIGHTER(gobj)->item_gobj;
    if (igobj != NULL) {
        if (itGetKind(igobj) == It_Kind_Peach_Turnip) {
            ft_800957F4(gobj, msid);
        }
        return true;
    } else {
        return false;
    }
}

void ftPe_SpecialLw_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (throwVegIfHeld(gobj, ftCo_MS_LightThrowF4) != true) {
        fp->throw_flags.flags = 0;
        Fighter_ChangeMotionState(gobj, ftPe_MS_SpecialLw, Ft_MF_None, NULL, 0,
                                  1, 0);
        ftAnim_8006EBA4(gobj);
        fp->cb.x21BC_callback_Accessory4 = spawnVeg;
    }
}

void ftPe_SpecialAirLw_Enter(HSD_GObj* gobj)
{
    throwVegIfHeld(gobj, ftCo_MS_LightThrowAirF4);
}

static MotionFlags const coll_mf = Ft_MF_SkipMatAnim | Ft_MF_SkipColAnim |
                                   Ft_MF_UpdateCmd | Ft_MF_SkipItemVis |
                                   Ft_MF_Unk19 | Ft_MF_SkipModelPartVis |
                                   Ft_MF_SkipModelFlags | Ft_MF_Unk27;

static void handleAirColl(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftPe_MS_SpecialAirLw, coll_mf, NULL,
                              fp->cur_anim_frame, 1, 0);
    fp->cb.x21BC_callback_Accessory4 = spawnVeg;
}

static void handleColl(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftPe_MS_SpecialLw, coll_mf, NULL,
                              fp->cur_anim_frame, 1, 0);
    fp->cb.x21BC_callback_Accessory4 = spawnVeg;
}

static void doAnim(HSD_GObj* gobj, HSD_GObjEvent cb)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        cb(gobj);
        ftPe_SpecialLw_UnsetVeg(gobj);
    }
}

void ftPe_SpecialLw_Anim(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif
    doAnim(gobj, ft_8008A2BC);
}

void ftPe_SpecialAirLw_Anim(HSD_GObj* gobj)
{
    doAnim(gobj, ft_800CC730);
}

void ftPe_SpecialLw_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftPe_SpecialAirLw_Phys(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftPe_SpecialLw_Coll(HSD_GObj* gobj)
{
    ft_8008403C(gobj, handleAirColl);
}

void ftPe_SpecialAirLw_Coll(HSD_GObj* gobj)
{
    ft_80082C74(gobj, handleColl);
}
