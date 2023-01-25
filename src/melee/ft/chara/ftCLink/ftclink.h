#ifndef MELEE_FT_CHARA_FTCLINK_FTCLINK_H
#define MELEE_FT_CHARA_FTCLINK_FTCLINK_H

#include <melee/ft/fighter.h>
#include <melee/it/code_8027CF30.h>
#include <sysdolphin/baselib/gobj.h>

/// @todo this is #ftLinkAttributes.
typedef struct _CLinkAttributes {
    s32 x0_pad[(0xC - 0x0) / 4];
    s32 xC;
    s32 x10;
    s32 x14_pad[(0x2C - 0x14) / 4];
    s32 x2C;
    s32 x30_pad[(0x48 - 0x30) / 4];
    s32 x48;
    s32 x4C;
    s32 x50;
    f32 x54;
    s32 x58_pad[(0xBC - 0x58) / 4];
    s32 xBC;
    s32 xC0;
    f32 xC4;
    s32 xC8_pad[(0xD8 - 0xC8) / 4];
    f32 xD8;
} CLinkAttributes;

extern ActionState as_table_clink[];
extern char lbl_803D1240[];
extern char lbl_803D124C[];
extern Fighter_CostumeStrings lbl_803D1458[];
extern char lbl_803D13CC[];
extern Fighter_DemoStrings lbl_803D1448;

void ftCLink_OnItemPickup(HSD_GObj*, bool);
void ftCLink_OnItemDrop(HSD_GObj*, bool);
void func_80149268(HSD_GObj*);
void ftCLink_OnKnockbackExit(HSD_GObj* gobj);
void func_80149114(HSD_GObj* gobj);
void func_8014919C(HSD_GObj* gobj);
void ftCLink_OnDeath(HSD_GObj* gobj);
bool func_8014920C(HSD_GObj* gobj);
void func_801492C4(HSD_GObj* gobj);
u32 func_801492F4(HSD_GObj* gobj);
void func_80149318(HSD_GObj* gobj);
void ftCLink_OnLoad(HSD_GObj* gobj);
void ftCLink_OnItemPickupExt(HSD_GObj* gobj, bool arg1);
void ftCLink_OnItemInvisible(HSD_GObj* gobj);
void ftCLink_OnItemVisible(HSD_GObj* gobj);
void ftCLink_OnItemDropExt(HSD_GObj* gobj, bool arg1);
void ftCLink_LoadSpecialAttrs(HSD_GObj* gobj);
void ftCLink_OnKnockbackEnter(HSD_GObj* gobj);
void func_800CEDE0(HSD_GObj*);
void func_800CEE00(HSD_GObj*);
void func_800CEE30(HSD_GObj*);
void func_800CEE50(HSD_GObj*);
void func_80149354(HSD_GObj*);
void func_8014943C(HSD_GObj*);
void func_8014945C(HSD_GObj*);
void func_8014947C(HSD_GObj*);
void func_80149354(HSD_GObj*);
void func_8014943C(HSD_GObj*);
void func_8014945C(HSD_GObj*);
void func_8014947C(HSD_GObj*);
void func_800ED15C(HSD_GObj*);
void func_800EDD88(HSD_GObj*);
void func_800EDFD8(HSD_GObj*);
void func_800EE098(HSD_GObj*);
void func_800ED480(HSD_GObj*);
void func_800EDE30(HSD_GObj*);
void func_800EDFF8(HSD_GObj*);
void func_800EE120(HSD_GObj*);
void func_800ED5B4(HSD_GObj*);
void func_800EDEAC(HSD_GObj*);
void func_800EE018(HSD_GObj*);
void func_800EE1A8(HSD_GObj*);
void func_800ED72C(HSD_GObj*);
void func_800EDEB0(HSD_GObj*);
void func_800EE038(HSD_GObj*);
void func_800EE2E0(HSD_GObj*);
void func_800EDA58(HSD_GObj*);
void func_800EDF58(HSD_GObj*);
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
void func_800EC8CC(HSD_GObj*);
void func_800ECA1C(HSD_GObj*);
void func_800EC634(HSD_GObj*);
void func_800EC8EC(HSD_GObj*);
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
void func_800C3D6C(HSD_GObj*);
void func_800C4384(HSD_GObj*);
void func_800C438C(HSD_GObj*);
void func_800C447C(HSD_GObj*);
void func_800C4380(HSD_GObj*);
void func_800C4388(HSD_GObj*);
void func_800C4438(HSD_GObj*);
void func_80082B78(HSD_GObj*);

static inline void checkFighter2244(HSD_GObj* gobj)
{
    Fighter* fp;

    if (gobj == NULL)
        return;

    fp = gobj->user_data;
    if (fp != NULL && fp->sa.clink.x2244 != 0) {
        func_802C8C34(fp->sa.clink.x2244);
        fp->sa.clink.x2244 = 0;
    }

    if (gobj == NULL)
        gobj == NULL;
}

#endif
