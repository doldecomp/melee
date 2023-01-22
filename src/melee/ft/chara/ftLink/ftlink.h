#ifndef MELEE_FT_CHARA_FTLINK_FTLINK_H
#define MELEE_FT_CHARA_FTLINK_FTLINK_H

#include <melee/ft/ftcommon.h>
#include <melee/ft/types.h>
#include <Runtime/platform.h>
#include <sysdolphin/baselib/gobj.h>

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

extern ActionState as_table_link[];

void ftLink_OnItemDrop(HSD_GObj* fighter_gobj, bool arg1);
void ftLink_OnItemPickup(HSD_GObj* fighter_gobj, bool bool);
void func_800EC06C(void);
void func_800ECD04(HSD_GObj*);
void func_800ECD58(HSD_GObj*);
void ftLink_OnLoadForCLink(Fighter* fp);
void ftLink_LoadSpecialAttrs(HSD_GObj* fighter_gobj);
void func_800EAF58(HSD_GObj*);

bool func_800EAD64(HSD_GObj* fighter_gobj);
void ftLink_OnKnockbackEnter(HSD_GObj* fighter_gobj);
void ftLink_OnKnockbackExit(HSD_GObj* fighter_gobj);
void ftLink_800EB334(HSD_GObj* fighter_gobj);
void ftLink_OnDeath(HSD_GObj* fighter_gobj);
void ftLink_OnLoad(HSD_GObj* fighter_gobj);
void func_800EAF38(void);
void ftLink_OnItemPickupExt(HSD_GObj* fighter_gobj, int arg1);
void ftLink_OnItemInvisible(HSD_GObj* fighter_gobj);
void ftLink_OnItemVisible(HSD_GObj* fighter_gobj);
void ftLink_OnItemDropExt(HSD_GObj* fighter_gobj, bool arg1);
void func_800EDFD8(HSD_GObj*);
void func_800EE098(HSD_GObj*);
void func_800ED15C(HSD_GObj*);
void func_800ED480(HSD_GObj*);
void func_800EDE30(HSD_GObj*);
void func_800EDEAC(HSD_GObj*);
void func_800ED5B4(HSD_GObj*);
void func_800EE1A8(HSD_GObj*);
void func_800EE018(HSD_GObj*);
void func_800EDFF8(HSD_GObj*);
void func_800EE120(HSD_GObj*);
void func_800ED72C(HSD_GObj*);
void func_800EE038(HSD_GObj*);
void func_800EE2E0(HSD_GObj*);
void func_800EDA58(HSD_GObj*);
void func_800EE058(HSD_GObj*);
void func_800EE368(HSD_GObj*);
void func_800EDB8C(HSD_GObj*);
void func_800EDFD4(HSD_GObj*);
void func_800EE078(HSD_GObj*);
void func_800EE3F0(HSD_GObj*);
void func_800EC54C(HSD_GObj*);
void func_800EC88C(HSD_GObj*);
void func_800EC94C(HSD_GObj*);
void func_800EC588(HSD_GObj*);
void func_800EC71C(HSD_GObj*);
void func_800EC8AC(HSD_GObj*);
void func_800EC9C4(HSD_GObj*);
void func_800EC5F8(HSD_GObj*);
void func_800EDF58(HSD_GObj*);
void func_800EDEB0(HSD_GObj*);
void func_800EDD88(HSD_GObj*);
void func_800EC8CC(HSD_GObj*);
void func_800EC8EC(HSD_GObj*);
void func_800EC634(HSD_GObj*);
void func_800ECA1C(HSD_GObj*);
void func_800ECA88(HSD_GObj*);
void func_800EC670(HSD_GObj*);
void func_800EC810(HSD_GObj*);
void func_800EC90C(HSD_GObj*);
void func_800ECB00(HSD_GObj*);
void func_800EC6E0(HSD_GObj*);
void func_800EC92C(HSD_GObj*);
void func_800ECB58(HSD_GObj*);
void func_800EBC10(HSD_GObj*);
void func_800EBCAC(HSD_GObj*);
void func_800EBD30(HSD_GObj*);
void func_800EBDC0(HSD_GObj*);
void func_800EBC4C(HSD_GObj*);

void func_800EBCB0(HSD_GObj*);
void func_800EBCB4(HSD_GObj*);
void func_800EBDFC(HSD_GObj*);
void func_800EB8A4(HSD_GObj*);
void func_800EB91C(HSD_GObj*);
void func_800EB95C(HSD_GObj*);
void func_800EB8E0(HSD_GObj*);
void func_800EB93C(HSD_GObj*);
void func_800EB9D4(HSD_GObj*);

#endif
