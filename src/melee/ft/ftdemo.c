#include "pl/forward.h"

#include "ftdemo.h"

#include "cm/camera.h"
#include "ef/efasync.h"
#include "ft/fighter.h"
#include "ft/ft_0BEC.h"
#include "ft/ft_0BEF.h"
#include "ft/ft_0BF0.h"
#include "ft/ft_0C31.h"
#include "ft/ft_0C88.h"
#include "ft/ftcoll.h"
#include "ft/ftdata.h"
#include "ft/ftdrawcommon.h"
#include "ft/ftlib.h"
#include "ft/ftparts.h"
#include "ftCommon/ftCo_09CB.h"
#include "ftCommon/ftCo_09F4.h"
#include "ftCommon/ftCo_DemoCallback0.h"
#include "ftCommon/ftCo_Init.h"
#include "lb/lbshadow.h"

#include <math.h>
#include <placeholder.h>
#include <baselib/debug.h>

static HSD_GObjEvent on_create_fighter[16] = {
    ftCo_800BECB0, ftCo_800BED88, ftCo_800BEF04, NULL,
    ftCo_800BEFD4, ftCo_800BF034, ftCo_800BF108, ftCo_800C6150,
    ftCo_800C7070, ftCo_800C70D0, ftCo_800C7178, ftCo_800C7220,
    ftCo_800C7294, ftCo_800C7308, ftCo_800C739C, ftCo_800C7434
};

ASM Fighter_GObj* ftDemo_CreateFighter(plAllocInfo2* alloc_info)
#if !defined(MUST_MATCH) || defined(WIP)
{
    Fighter_GObj* gobj = GObj_Create(4, 8, 0);
    GObj_SetupGXLink(gobj, ftDrawCommon_80080E18, 5, 0);
    {
        Fighter* fp = HSD_ObjAlloc(&fighter_alloc_data);
        fp->x2D8_specialAttributes2 = HSD_ObjAlloc(&Fighter_80458FFC);
        GObj_InitUserData(gobj, 4, Fighter_Unload_8006DABC, fp);
        ftData_8008572C(alloc_info->internal_id);
        {
            struct S_TEMP1 temp1;
            temp1.fighterKind = alloc_info->internal_id;
            temp1.playerID = alloc_info->slot;
            temp1.flags_b0 = alloc_info->bits.b0;
            Fighter_UnkInitLoad_80068914(gobj, &temp1);
        }
        fp->x18 = 14;
        fp->x1C_actionStateList = ftData_803C52A0;
        fp->x20_actionStateList = ftData_UnkMotionStates0[fp->kind];
        fp->x24 = fp->ft_data->x14;
        fp->x28 = fp->ft_data->x18;
        efAsync_8006737C(ftData_UnkBytePerCharacter[fp->kind]);
        if (!alloc_info->bits.b0) {
            ftData_80085820(fp->kind, fp->x619_costume_id);
        } else {
            ftData_800858E4(fp->kind, fp->x619_costume_id);
        }
        Fighter_UnkUpdateCostumeJoint_800686E4(gobj);
        {
            enum_t alloc_unk8 = alloc_info->unk8;
            enum_t a, b;
            if (alloc_unk8 >= 9) {
                ftData_UnkDemoCallbacks0[fp->kind](alloc_unk8, &a, &b);
            } else if (alloc_unk8 >= 8) {
                b = 13;
                a = 13;
            } else if (alloc_unk8 >= 7) {
                b = 12;
                a = 12;
            } else if (alloc_unk8 >= 5) {
                a = 10;
                b = 11;
            } else {
                a = 0;
                b = 9;
            }
            ftData_80085B98(fp, a, b);
        }
        ftParts_80074E58(fp);
        ftParts_SetupParts(gobj);
        ftAnim_80070308(gobj);
        ftCo_800C884C(gobj);
        Fighter_80068E64(gobj);
        ftParts_800749CC(gobj);
        ftAnim_8007077C(gobj);
        ftCo_8009CF84(fp);
        ftAnim_8006FE48(gobj);
        Fighter_UnkUpdateVecFromBones_8006876C(fp);
        ftCo_8009F578(fp);
        if (ftData_OnLoad[fp->kind] != NULL) {
            ftData_OnLoad[fp->kind](gobj);
        }
        ftColl_8007B320(gobj);
        fp->x890_cameraBox = Camera_80029020();
        lbShadow_8000ED54(&fp->x20A4, gobj->hsd_obj);
    }
    HSD_GObjProc_8038FD54(gobj, Fighter_8006A360, 1);
    HSD_GObjProc_8038FD54(gobj, Fighter_procUpdate, 4);
    HSD_GObjProc_8038FD54(gobj, Fighter_8006C27C, 5);
    HSD_GObjProc_8038FD54(gobj, Fighter_8006C80C, 9);
    HSD_GObjProc_8038FD54(gobj, Fighter_8006D9AC, 16);
    Fighter_UnkProcessDeath_80068354(gobj);
    if (on_create_fighter[alloc_info->unk8] != NULL) {
        on_create_fighter[alloc_info->unk8](gobj);
    }
    ftLib_800867E8(gobj);
    return gobj;
}

#else /* clang-format off */
{ nofralloc
/* 800BE7E0 000BB3C0  7C 08 02 A6 */	mflr r0
/* 800BE7E4 000BB3C4  38 80 00 08 */	li r4, 8
/* 800BE7E8 000BB3C8  90 01 00 04 */	stw r0, 4(r1)
/* 800BE7EC 000BB3CC  38 A0 00 00 */	li r5, 0
/* 800BE7F0 000BB3D0  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 800BE7F4 000BB3D4  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 800BE7F8 000BB3D8  93 C1 00 28 */	stw r30, 0x28(r1)
/* 800BE7FC 000BB3DC  93 A1 00 24 */	stw r29, 0x24(r1)
/* 800BE800 000BB3E0  3B A3 00 00 */	addi r29, r3, 0
/* 800BE804 000BB3E4  38 60 00 04 */	li r3, 4
/* 800BE808 000BB3E8  48 2D 19 E9 */	bl GObj_Create
/* 800BE80C 000BB3EC  3C 80 80 08 */	lis r4, ftDrawCommon_80080E18@ha
/* 800BE810 000BB3F0  3B E3 00 00 */	addi r31, r3, 0
/* 800BE814 000BB3F4  38 84 0E 18 */	addi r4, r4, ftDrawCommon_80080E18@l
/* 800BE818 000BB3F8  38 A0 00 05 */	li r5, 5
/* 800BE81C 000BB3FC  38 C0 00 00 */	li r6, 0
/* 800BE820 000BB400  48 2D 1E 7D */	bl GObj_SetupGXLink
/* 800BE824 000BB404  3C 60 80 46 */	lis r3, fighter_alloc_data@ha
/* 800BE828 000BB408  38 63 8F D0 */	addi r3, r3, fighter_alloc_data@l
/* 800BE82C 000BB40C  48 2B C3 9D */	bl HSD_ObjAlloc
/* 800BE830 000BB410  3C 80 80 46 */	lis r4, Fighter_80458FFC@ha
/* 800BE834 000BB414  38 04 8F FC */	addi r0, r4, Fighter_80458FFC@l
/* 800BE838 000BB418  3B C3 00 00 */	addi r30, r3, 0
/* 800BE83C 000BB41C  7C 03 03 78 */	mr r3, r0
/* 800BE840 000BB420  48 2B C3 89 */	bl HSD_ObjAlloc
/* 800BE844 000BB424  3C 80 80 07 */	lis r4, Fighter_Unload_8006DABC@ha
/* 800BE848 000BB428  90 7E 02 D8 */	stw r3, 0x2d8(r30)
/* 800BE84C 000BB42C  38 A4 DA BC */	addi r5, r4, Fighter_Unload_8006DABC@l
/* 800BE850 000BB430  38 7F 00 00 */	addi r3, r31, 0
/* 800BE854 000BB434  38 DE 00 00 */	addi r6, r30, 0
/* 800BE858 000BB438  38 80 00 04 */	li r4, 4
/* 800BE85C 000BB43C  48 2D 23 0D */	bl GObj_InitUserData
/* 800BE860 000BB440  80 7D 00 00 */	lwz r3, 0(r29)
/* 800BE864 000BB444  4B FC 6E C9 */	bl ftData_8008572C
/* 800BE868 000BB448  80 1D 00 00 */	lwz r0, 0(r29)
/* 800BE86C 000BB44C  38 7F 00 00 */	addi r3, r31, 0
/* 800BE870 000BB450  38 81 00 0C */	addi r4, r1, 0xc
/* 800BE874 000BB454  90 01 00 0C */	stw r0, 0xc(r1)
/* 800BE878 000BB458  88 1D 00 04 */	lbz r0, 4(r29)
/* 800BE87C 000BB45C  98 01 00 10 */	stb r0, 0x10(r1)
/* 800BE880 000BB460  88 BD 00 0C */	lbz r5, 0xc(r29)
/* 800BE884 000BB464  88 01 00 12 */	lbz r0, 0x12(r1)
/* 800BE888 000BB468  50 A0 0E 30 */	rlwimi r0, r5, 1, 0x18, 0x18
/* 800BE88C 000BB46C  98 01 00 12 */	stb r0, 0x12(r1)
/* 800BE890 000BB470  4B FA A0 85 */	bl Fighter_UnkInitLoad_80068914
/* 800BE894 000BB474  38 00 00 0E */	li r0, 0xe
/* 800BE898 000BB478  3C 60 80 3C */	lis r3, ftData_803C52A0@ha
/* 800BE89C 000BB47C  90 1E 00 18 */	stw r0, 0x18(r30)
/* 800BE8A0 000BB480  38 03 52 A0 */	addi r0, r3, ftData_803C52A0@l
/* 800BE8A4 000BB484  90 1E 00 1C */	stw r0, 0x1c(r30)
/* 800BE8A8 000BB488  3C 80 80 3C */	lis r4, ftData_UnkMotionStates0@ha
/* 800BE8AC 000BB48C  3C 60 80 3C */	lis r3, ftData_UnkBytePerCharacter@ha
/* 800BE8B0 000BB490  80 BE 00 04 */	lwz r5, 4(r30)
/* 800BE8B4 000BB494  38 84 13 64 */	addi r4, r4, ftData_UnkMotionStates0@l
/* 800BE8B8 000BB498  38 03 26 FC */	addi r0, r3, ftData_UnkBytePerCharacter@l
/* 800BE8BC 000BB49C  54 A3 10 3A */	slwi r3, r5, 2
/* 800BE8C0 000BB4A0  7C 64 1A 14 */	add r3, r4, r3
/* 800BE8C4 000BB4A4  80 63 00 00 */	lwz r3, 0(r3)
/* 800BE8C8 000BB4A8  90 7E 00 20 */	stw r3, 0x20(r30)
/* 800BE8CC 000BB4AC  80 7E 01 0C */	lwz r3, 0x10c(r30)
/* 800BE8D0 000BB4B0  80 63 00 14 */	lwz r3, 0x14(r3)
/* 800BE8D4 000BB4B4  90 7E 00 24 */	stw r3, 0x24(r30)
/* 800BE8D8 000BB4B8  80 7E 01 0C */	lwz r3, 0x10c(r30)
/* 800BE8DC 000BB4BC  80 63 00 18 */	lwz r3, 0x18(r3)
/* 800BE8E0 000BB4C0  90 7E 00 28 */	stw r3, 0x28(r30)
/* 800BE8E4 000BB4C4  80 7E 00 04 */	lwz r3, 4(r30)
/* 800BE8E8 000BB4C8  7C 60 1A 14 */	add r3, r0, r3
/* 800BE8EC 000BB4CC  88 63 00 00 */	lbz r3, 0(r3)
/* 800BE8F0 000BB4D0  4B FA 8A 8D */	bl efAsync_8006737C
/* 800BE8F4 000BB4D4  88 1D 00 0C */	lbz r0, 0xc(r29)
/* 800BE8F8 000BB4D8  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 800BE8FC 000BB4DC  40 82 00 14 */	bne lbl_800BE910
/* 800BE900 000BB4E0  80 7E 00 04 */	lwz r3, 4(r30)
/* 800BE904 000BB4E4  88 9E 06 19 */	lbz r4, 0x619(r30)
/* 800BE908 000BB4E8  4B FC 6F 19 */	bl ftData_80085820
/* 800BE90C 000BB4EC  48 00 00 10 */	b lbl_800BE91C
lbl_800BE910:
/* 800BE910 000BB4F0  80 7E 00 04 */	lwz r3, 4(r30)
/* 800BE914 000BB4F4  88 9E 06 19 */	lbz r4, 0x619(r30)
/* 800BE918 000BB4F8  4B FC 6F CD */	bl ftData_800858E4
lbl_800BE91C:
/* 800BE91C 000BB4FC  7F E3 FB 78 */	mr r3, r31
/* 800BE920 000BB500  4B FA 9D C5 */	bl Fighter_UnkUpdateCostumeJoint_800686E4
/* 800BE924 000BB504  80 7D 00 08 */	lwz r3, 8(r29)
/* 800BE928 000BB508  2C 03 00 09 */	cmpwi r3, 9
/* 800BE92C 000BB50C  41 80 00 30 */	blt lbl_800BE95C
/* 800BE930 000BB510  80 BE 00 04 */	lwz r5, 4(r30)
/* 800BE934 000BB514  3C 80 80 3C */	lis r4, ftData_UnkDemoCallbacks0@ha
/* 800BE938 000BB518  38 04 25 70 */	addi r0, r4, ftData_UnkDemoCallbacks0@l
/* 800BE93C 000BB51C  54 A4 10 3A */	slwi r4, r5, 2
/* 800BE940 000BB520  7C 80 22 14 */	add r4, r0, r4
/* 800BE944 000BB524  81 84 00 00 */	lwz r12, 0(r4)
/* 800BE948 000BB528  38 81 00 18 */	addi r4, r1, 0x18
/* 800BE94C 000BB52C  38 A1 00 14 */	addi r5, r1, 0x14
/* 800BE950 000BB530  7D 88 03 A6 */	mtlr r12
/* 800BE954 000BB534  4E 80 00 21 */	blrl
/* 800BE958 000BB538  48 00 00 60 */	b lbl_800BE9B8
lbl_800BE95C:
/* 800BE95C 000BB53C  2C 03 00 08 */	cmpwi r3, 8
/* 800BE960 000BB540  41 80 00 14 */	blt lbl_800BE974
/* 800BE964 000BB544  38 00 00 0D */	li r0, 0xd
/* 800BE968 000BB548  90 01 00 14 */	stw r0, 0x14(r1)
/* 800BE96C 000BB54C  90 01 00 18 */	stw r0, 0x18(r1)
/* 800BE970 000BB550  48 00 00 48 */	b lbl_800BE9B8
lbl_800BE974:
/* 800BE974 000BB554  2C 03 00 07 */	cmpwi r3, 7
/* 800BE978 000BB558  41 80 00 14 */	blt lbl_800BE98C
/* 800BE97C 000BB55C  38 00 00 0C */	li r0, 0xc
/* 800BE980 000BB560  90 01 00 14 */	stw r0, 0x14(r1)
/* 800BE984 000BB564  90 01 00 18 */	stw r0, 0x18(r1)
/* 800BE988 000BB568  48 00 00 30 */	b lbl_800BE9B8
lbl_800BE98C:
/* 800BE98C 000BB56C  2C 03 00 05 */	cmpwi r3, 5
/* 800BE990 000BB570  41 80 00 18 */	blt lbl_800BE9A8
/* 800BE994 000BB574  38 60 00 0A */	li r3, 0xa
/* 800BE998 000BB578  38 00 00 0B */	li r0, 0xb
/* 800BE99C 000BB57C  90 61 00 18 */	stw r3, 0x18(r1)
/* 800BE9A0 000BB580  90 01 00 14 */	stw r0, 0x14(r1)
/* 800BE9A4 000BB584  48 00 00 14 */	b lbl_800BE9B8
lbl_800BE9A8:
/* 800BE9A8 000BB588  38 60 00 00 */	li r3, 0
/* 800BE9AC 000BB58C  38 00 00 09 */	li r0, 9
/* 800BE9B0 000BB590  90 61 00 18 */	stw r3, 0x18(r1)
/* 800BE9B4 000BB594  90 01 00 14 */	stw r0, 0x14(r1)
lbl_800BE9B8:
/* 800BE9B8 000BB598  80 81 00 18 */	lwz r4, 0x18(r1)
/* 800BE9BC 000BB59C  7F C3 F3 78 */	mr r3, r30
/* 800BE9C0 000BB5A0  80 A1 00 14 */	lwz r5, 0x14(r1)
/* 800BE9C4 000BB5A4  4B FC 71 D5 */	bl ftData_80085B98
/* 800BE9C8 000BB5A8  7F C3 F3 78 */	mr r3, r30
/* 800BE9CC 000BB5AC  4B FB 64 8D */	bl ftParts_80074E58
/* 800BE9D0 000BB5B0  7F E3 FB 78 */	mr r3, r31
/* 800BE9D4 000BB5B4  4B FB 5A 0D */	bl ftParts_SetupParts
/* 800BE9D8 000BB5B8  7F E3 FB 78 */	mr r3, r31
/* 800BE9DC 000BB5BC  4B FB 19 2D */	bl ftAnim_80070308
/* 800BE9E0 000BB5C0  7F E3 FB 78 */	mr r3, r31
/* 800BE9E4 000BB5C4  48 00 9E 69 */	bl ftCo_800C884C
/* 800BE9E8 000BB5C8  7F E3 FB 78 */	mr r3, r31
/* 800BE9EC 000BB5CC  4B FA A4 79 */	bl Fighter_80068E64
/* 800BE9F0 000BB5D0  7F E3 FB 78 */	mr r3, r31
/* 800BE9F4 000BB5D4  4B FB 5F D9 */	bl ftParts_800749CC
/* 800BE9F8 000BB5D8  7F E3 FB 78 */	mr r3, r31
/* 800BE9FC 000BB5DC  4B FB 1D 81 */	bl ftAnim_8007077C
/* 800BEA00 000BB5E0  7F C3 F3 78 */	mr r3, r30
/* 800BEA04 000BB5E4  4B FD E5 81 */	bl ftCo_8009CF84
/* 800BEA08 000BB5E8  7F E3 FB 78 */	mr r3, r31
/* 800BEA0C 000BB5EC  4B FB 14 3D */	bl ftAnim_8006FE48
/* 800BEA10 000BB5F0  7F C3 F3 78 */	mr r3, r30
/* 800BEA14 000BB5F4  4B FA 9D 59 */	bl Fighter_UnkUpdateVecFromBones_8006876C
/* 800BEA18 000BB5F8  7F C3 F3 78 */	mr r3, r30
/* 800BEA1C 000BB5FC  4B FE 0B 5D */	bl ftCo_8009F578
/* 800BEA20 000BB600  80 9E 00 04 */	lwz r4, 4(r30)
/* 800BEA24 000BB604  3C 60 80 3C */	lis r3, ftData_OnLoad@ha
/* 800BEA28 000BB608  38 03 11 54 */	addi r0, r3, ftData_OnLoad@l
/* 800BEA2C 000BB60C  54 83 10 3A */	slwi r3, r4, 2
/* 800BEA30 000BB610  7C 60 1A 14 */	add r3, r0, r3
/* 800BEA34 000BB614  81 83 00 00 */	lwz r12, 0(r3)
/* 800BEA38 000BB618  28 0C 00 00 */	cmplwi r12, 0
/* 800BEA3C 000BB61C  41 82 00 10 */	beq lbl_800BEA4C
/* 800BEA40 000BB620  7D 88 03 A6 */	mtlr r12
/* 800BEA44 000BB624  38 7F 00 00 */	addi r3, r31, 0
/* 800BEA48 000BB628  4E 80 00 21 */	blrl
lbl_800BEA4C:
/* 800BEA4C 000BB62C  7F E3 FB 78 */	mr r3, r31
/* 800BEA50 000BB630  4B FB C8 D1 */	bl ftColl_8007B320
/* 800BEA54 000BB634  4B F6 A5 CD */	bl Camera_80029020
/* 800BEA58 000BB638  90 7E 08 90 */	stw r3, 0x890(r30)
/* 800BEA5C 000BB63C  38 7E 20 A4 */	addi r3, r30, 0x20a4
/* 800BEA60 000BB640  80 9F 00 28 */	lwz r4, 0x28(r31)
/* 800BEA64 000BB644  4B F5 02 F1 */	bl lbShadow_8000ED54
/* 800BEA68 000BB648  3C 60 80 07 */	lis r3, Fighter_8006A360@ha
/* 800BEA6C 000BB64C  38 83 A3 60 */	addi r4, r3, Fighter_8006A360@l
/* 800BEA70 000BB650  38 7F 00 00 */	addi r3, r31, 0
/* 800BEA74 000BB654  38 A0 00 01 */	li r5, 1
/* 800BEA78 000BB658  48 2D 12 DD */	bl HSD_GObjProc_8038FD54
/* 800BEA7C 000BB65C  3C 60 80 07 */	lis r3, Fighter_procUpdate@ha
/* 800BEA80 000BB660  38 83 B8 2C */	addi r4, r3, Fighter_procUpdate@l
/* 800BEA84 000BB664  38 7F 00 00 */	addi r3, r31, 0
/* 800BEA88 000BB668  38 A0 00 04 */	li r5, 4
/* 800BEA8C 000BB66C  48 2D 12 C9 */	bl HSD_GObjProc_8038FD54
/* 800BEA90 000BB670  3C 60 80 07 */	lis r3, Fighter_8006C27C@ha
/* 800BEA94 000BB674  38 83 C2 7C */	addi r4, r3, Fighter_8006C27C@l
/* 800BEA98 000BB678  38 7F 00 00 */	addi r3, r31, 0
/* 800BEA9C 000BB67C  38 A0 00 05 */	li r5, 5
/* 800BEAA0 000BB680  48 2D 12 B5 */	bl HSD_GObjProc_8038FD54
/* 800BEAA4 000BB684  3C 60 80 07 */	lis r3, Fighter_8006C80C@ha
/* 800BEAA8 000BB688  38 83 C8 0C */	addi r4, r3, Fighter_8006C80C@l
/* 800BEAAC 000BB68C  38 7F 00 00 */	addi r3, r31, 0
/* 800BEAB0 000BB690  38 A0 00 09 */	li r5, 9
/* 800BEAB4 000BB694  48 2D 12 A1 */	bl HSD_GObjProc_8038FD54
/* 800BEAB8 000BB698  3C 60 80 07 */	lis r3, Fighter_8006D9AC@ha
/* 800BEABC 000BB69C  38 83 D9 AC */	addi r4, r3, Fighter_8006D9AC@l
/* 800BEAC0 000BB6A0  38 7F 00 00 */	addi r3, r31, 0
/* 800BEAC4 000BB6A4  38 A0 00 10 */	li r5, 0x10
/* 800BEAC8 000BB6A8  48 2D 12 8D */	bl HSD_GObjProc_8038FD54
/* 800BEACC 000BB6AC  7F E3 FB 78 */	mr r3, r31
/* 800BEAD0 000BB6B0  4B FA 98 85 */	bl Fighter_UnkProcessDeath_80068354
/* 800BEAD4 000BB6B4  80 9D 00 08 */	lwz r4, 8(r29)
/* 800BEAD8 000BB6B8  3C 60 80 3C */	lis r3, on_create_fighter@ha
/* 800BEADC 000BB6BC  38 03 69 08 */	addi r0, r3, on_create_fighter@l
/* 800BEAE0 000BB6C0  54 83 10 3A */	slwi r3, r4, 2
/* 800BEAE4 000BB6C4  7C 60 1A 14 */	add r3, r0, r3
/* 800BEAE8 000BB6C8  81 83 00 00 */	lwz r12, 0(r3)
/* 800BEAEC 000BB6CC  28 0C 00 00 */	cmplwi r12, 0
/* 800BEAF0 000BB6D0  41 82 00 10 */	beq lbl_800BEB00
/* 800BEAF4 000BB6D4  7D 88 03 A6 */	mtlr r12
/* 800BEAF8 000BB6D8  38 7F 00 00 */	addi r3, r31, 0
/* 800BEAFC 000BB6DC  4E 80 00 21 */	blrl
lbl_800BEB00:
/* 800BEB00 000BB6E0  7F E3 FB 78 */	mr r3, r31
/* 800BEB04 000BB6E4  4B FC 7C E5 */	bl ftLib_800867E8
/* 800BEB08 000BB6E8  7F E3 FB 78 */	mr r3, r31
/* 800BEB0C 000BB6EC  80 01 00 34 */	lwz r0, 0x34(r1)
/* 800BEB10 000BB6F0  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 800BEB14 000BB6F4  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 800BEB18 000BB6F8  83 A1 00 24 */	lwz r29, 0x24(r1)
/* 800BEB1C 000BB6FC  38 21 00 30 */	addi r1, r1, 0x30
/* 800BEB20 000BB700  7C 08 03 A6 */	mtlr r0
/* 800BEB24 000BB704  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

void ftDemo_ObjAllocInit(void)
{
    Fighter_800679B0();
    HSD_ObjAllocInit(&Fighter_804590AC, 0xB000, 0x20);
}

void ftDemo_SetArchiveData(int pairs_idx, HSD_Archive* archive, int arr_idx)
{
    static int ints[5] = { 9, 10, 11, 14, 15 };
    ftData_UnkCountStruct* pair = &ftData_UnkIntPairs[pairs_idx];
    if (pair->data == NULL) {
        if (arr_idx >= 4) {
            pair->data = HSD_ArchiveGetPublicAddress(
                archive,
                ftDemo_GetMotionFileString(pairs_idx, ints[arr_idx - 4]));
        } else {
            pair->data = HSD_ArchiveGetPublicAddress(
                archive, ((char***) ftData_803C2468)[pairs_idx][arr_idx]);
        }
    }
}

char* ftDemo_GetMotionFileString(int cb_idx, int cb_arg)
{
    if (ftData_803C24EC[cb_idx] != NULL) {
        return ftData_803C24EC[cb_idx](cb_arg);
    } else {
        OSReport("no demo vi anim! %d\n", cb_arg);
        __assert("ftdemo.c", 296, "0");
    }
}

void ftDemo_SetFacingDirection(Fighter_GObj* gobj, float facing_dir)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->facing_dir = facing_dir;
    ftParts_80075AF0(fp, 0, M_PI_2 * fp->facing_dir);
}
