#include <platform.h>
#include "ftCommon/forward.h"
#include "it/forward.h"
#include <dolphin/mtx/forward.h>
#include <baselib/forward.h>

#include "ftPe_SpecialLw.h"

#include "ftPe_Init.h"

#include "ef/efsync.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ft_0C88.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/types.h"
#include "ftCommon/ftCo_ItemGet.h"
#include "ftCommon/ftCo_ItemThrow.h"
#include "ftPeach/types.h"
#include "it/it_26B1.h"
#include "it/items/it_27CF.h"
#include "lb/lb_00B0.h"

#include <baselib/gobj.h>
#include <baselib/random.h>

/* 11CE48 */ static ItemKind pickVeg(HSD_GObj* gobj);
/* 11D018 */ static void spawnVeg(HSD_GObj* gobj);
/* 11D214 */ static void handleAirColl(HSD_GObj* gobj);
/* 11D280 */ static void handleColl(HSD_GObj* gobj);

ItemKind pickVeg(HSD_GObj* gobj)
{
    ftPe_DatAttrs* a = GET_FIGHTER(gobj)->dat_attrs;
    u8 _[8];
    ssize_t randi, idx;
    {
        int odds;
        for (idx = 0, odds = 0; idx < a->speciallw_item_table_count; idx++) {
            odds += a->speciallw_item_table[idx].randi_max;
        }
        randi = HSD_Randi(odds);
    }
    {
        ssize_t randi_max, result;
        for (result = -1, idx = 0,
            randi_max = a->speciallw_item_table[0].randi_max;
             idx < a->speciallw_item_table_count && result == -1; idx++)
        {
            if (randi < randi_max) {
                result = idx;
            }
            randi_max += a->speciallw_item_table[idx + 1].randi_max;
        }
        return a->speciallw_item_table[result].kind;
    }
}

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

#ifdef MUST_MATCH
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
/* 8011D0D8 00119CB8  4B F7 77 41 */	bl ftCo_80094818
/* 8011D0DC 00119CBC  38 9D 00 00 */	addi r4, r29, 0
/* 8011D0E0 00119CC0  4C C6 31 82 */	crclr 6
/* 8011D0E4 00119CC4  38 BE 00 B0 */	addi r5, r30, 0xb0
/* 8011D0E8 00119CC8  38 60 04 D2 */	li r3, 0x4d2
/* 8011D0EC 00119CCC  4B F4 2C F1 */	bl efSync_Spawn
/* 8011D0F0 00119CD0  3C 60 80 12 */	lis r3, ftPe_Init_OnDeath2@ha
/* 8011D0F4 00119CD4  38 03 B7 04 */	addi r0, r3, ftPe_Init_OnDeath2@l
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

static void spawnVeg(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ftCheckThrowB0(fp)) {
        Vec3 pos;
        lb_8000B1CC(fp->parts[FtPart_109].joint, NULL, &pos);
        {
            Fighter* fp = GET_FIGHTER(gobj);

            ftPe_DatAttrs* da = GET_FIGHTER(gobj)->dat_attrs;
            int da_x14 = da->x14;

            ItemKind kind = It_Kind_Peach_Turnip;
            if (HSD_Randi(da_x14) == 0) {
                kind = pickVeg(gobj);
            }

            {
                HSD_GObj* veg_gobj = it_802BD4AC(
                    gobj, &pos, fp->ft_data->x8->unk10, kind, fp->facing_dir);
                fp->item_gobj = veg_gobj;
                fp->fv.pe.veg_gobj = veg_gobj;
                if (veg_gobj != NULL) {
                    ftCo_80094818(gobj, false);
                    efSync_Spawn(1234, gobj, &fp->cur_pos);
                    fp->death2_cb = ftPe_Init_OnDeath2;
                    fp->take_dmg_cb = ftPe_Init_OnDeath2;
                }
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
            ftCo_800957F4(gobj, msid);
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
        fp->throw_flags = 0;
        Fighter_ChangeMotionState(gobj, ftPe_MS_SpecialLw, Ft_MF_None, 0, 1, 0,
                                  NULL);
        ftAnim_8006EBA4(gobj);
        fp->accessory4_cb = spawnVeg;
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
    Fighter_ChangeMotionState(gobj, ftPe_MS_SpecialAirLw, coll_mf,
                              fp->cur_anim_frame, 1, 0, NULL);
    fp->accessory4_cb = spawnVeg;
}

static void handleColl(HSD_GObj* gobj)
{
    /// @todo #GET_FIGHTER
    Fighter* fp = gobj->user_data;
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftPe_MS_SpecialLw, coll_mf,
                              fp->cur_anim_frame, 1, 0, NULL);
    fp->accessory4_cb = spawnVeg;
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
    u8 _[4];
    doAnim(gobj, ft_8008A2BC);
}

void ftPe_SpecialAirLw_Anim(HSD_GObj* gobj)
{
    doAnim(gobj, ftCo_800CC730);
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
