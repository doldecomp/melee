#ifndef MELEE_FT_CHARA_FTLINK_FTLINK_H
#define MELEE_FT_CHARA_FTLINK_FTLINK_H

#include <platform.h>

#include "ft/ftcommon.h"
#include "ft/types.h"

#include <baselib/gobj.h>

typedef struct _ftLinkAttributes {
    s32 x0;
    s32 x4;
    s32 x8;
    s32 xC;
    s32 x10;
    u8 x14_filler[0x2C - 0x18];
    f32 x28;
    s32 x2C;
    u8 x30_filler[0x48 - 0x30];
    s32 x48;
    s32 x4C;
    s32 x50;
    f32 x54;
    u8 x58_filler[0xBC - 0x58];
    s32 xBC;
    u8 xC0_filler[0xD8 - 0xC0];
    f32 xD8;
} ftLinkAttributes;

extern MotionState ftLk_Init_MotionStateTable[];
extern char ftLk_Init_DatFilename[];
extern char ftLk_Init_DataName[];
extern Fighter_CostumeStrings ftLk_Init_CostumeStrings[];
extern char ftLk_Init_AnimDatFilename[];
extern Fighter_DemoStrings ftLk_Init_DemoMotionFilenames;

void ftLk_Init_OnItemDrop(HSD_GObj* gobj, bool arg1);
void ftLk_Init_OnItemPickup(HSD_GObj* gobj, bool bool);
void ftLk_800EC06C(void);
void ftLk_800ECD04(HSD_GObj*);
void ftLk_800ECD58(HSD_GObj*);
void ftLk_OnLoadForCLink(Fighter* fp);
void ftLk_Init_LoadSpecialAttrs(HSD_GObj* gobj);
void ftLk_800EAF58(HSD_GObj*);
bool ftLk_800EAD64(HSD_GObj* gobj);
void ftLk_Init_OnKnockbackEnter(HSD_GObj* gobj);
void ftLk_Init_OnKnockbackExit(HSD_GObj* gobj);
void ftLk_800EB334(HSD_GObj* gobj);
void ftLk_Init_OnDeath(HSD_GObj* gobj);
void ftLk_Init_OnLoad(HSD_GObj* gobj);
void ftLk_800EAF38(void);
void ftLk_Init_OnItemPickupExt(HSD_GObj* gobj, int arg1);
void ftLk_Init_OnItemInvisible(HSD_GObj* gobj);
void ftLk_Init_OnItemVisible(HSD_GObj* gobj);
void ftLk_Init_OnItemDropExt(HSD_GObj* gobj, bool arg1);
void ftLk_800EDFD8(HSD_GObj*);
void ftLk_800EE098(HSD_GObj*);
void ftLk_800ED15C(HSD_GObj*);
void ftLk_800ED480(HSD_GObj*);
void ftLk_800EDE30(HSD_GObj*);
void ftLk_800EDEAC(HSD_GObj*);
void ftLk_800ED5B4(HSD_GObj*);
void ftLk_800EE1A8(HSD_GObj*);
void ftLk_800EE018(HSD_GObj*);
void ftLk_800EDFF8(HSD_GObj*);
void ftLk_800EE120(HSD_GObj*);
void ftLk_800ED72C(HSD_GObj*);
void ftLk_800EE038(HSD_GObj*);
void ftLk_800EE2E0(HSD_GObj*);
void ftLk_800EDA58(HSD_GObj*);
void ftLk_800EE058(HSD_GObj*);
void ftLk_800EE368(HSD_GObj*);
void ftLk_800EDB8C(HSD_GObj*);
void ftLk_800EDFD4(HSD_GObj*);
void ftLk_800EE078(HSD_GObj*);
void ftLk_800EE3F0(HSD_GObj*);
void ftLk_800EC54C(HSD_GObj*);
void ftLk_800EC88C(HSD_GObj*);
void ftLk_800EC94C(HSD_GObj*);
void ftLk_800EC588(HSD_GObj*);
void ftLk_800EC71C(HSD_GObj*);
void ftLk_800EC8AC(HSD_GObj*);
void ftLk_800EC9C4(HSD_GObj*);
void ftLk_800EC5F8(HSD_GObj*);
void ftLk_800EDF58(HSD_GObj*);
void ftLk_800EDEB0(HSD_GObj*);
void ftLk_800EDD88(HSD_GObj*);
void ftLk_800EC8CC(HSD_GObj*);
void ftLk_800EC8EC(HSD_GObj*);
void ftLk_800EC634(HSD_GObj*);
void ftLk_800ECA1C(HSD_GObj*);
void ftLk_800ECA88(HSD_GObj*);
void ftLk_800EC670(HSD_GObj*);
void ftLk_800EC810(HSD_GObj*);
void ftLk_800EC90C(HSD_GObj*);
void ftLk_800ECB00(HSD_GObj*);
void ftLk_800EC6E0(HSD_GObj*);
void ftLk_800EC92C(HSD_GObj*);
void ftLk_800ECB58(HSD_GObj*);
void ftLk_800EBC10(HSD_GObj*);
void ftLk_800EBCAC(HSD_GObj*);
void ftLk_800EBD30(HSD_GObj*);
void ftLk_800EBDC0(HSD_GObj*);
void ftLk_800EBC4C(HSD_GObj*);
void ftLk_800EBCB0(HSD_GObj*);
void ftLk_800EBCB4(HSD_GObj*);
void ftLk_800EBDFC(HSD_GObj*);
void ftLk_800EB8A4(HSD_GObj*);
void ftLk_800EB91C(HSD_GObj*);
void ftLk_800EB95C(HSD_GObj*);
void ftLk_800EB8E0(HSD_GObj*);
void ftLk_800EB93C(HSD_GObj*);
void ftLk_800EB9D4(HSD_GObj*);
void ftLk_SpecialS_StartMotion(HSD_GObj*);
void ftLk_SpecialAirHi_StartMotion(HSD_GObj*);
void ftLk_SpecialAirLw_StartMotion(HSD_GObj*);
void ftLk_SpecialAirS_StartMotion(HSD_GObj*);
void ftLk_SpecialAirN_StartMotion(HSD_GObj*);
void ftLk_SpecialN_StartMotion(HSD_GObj*);
void ftLk_SpecialN_StartMotion(HSD_GObj*);
void ftLk_SpecialLw_StartMotion(HSD_GObj*);
void ftLk_SpecialHi_StartMotion(HSD_GObj*);

#endif
