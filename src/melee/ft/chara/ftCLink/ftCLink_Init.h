#ifndef MELEE_FT_CHARA_FTCLINK_FTCLINK_H
#define MELEE_FT_CHARA_FTCLINK_FTCLINK_H

#include "ft/fighter.h"
#include "it/it_27CF.h"

#include <baselib/gobj.h>

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

extern MotionState ftCl_Init_MotionStateTable[];
extern char ftCl_Init_DatFilename[];
extern char ftCl_Init_DataName[];
extern Fighter_CostumeStrings ftCl_Init_CostumeStrings[];
extern char ftCl_Init_AnimDatFilename[];
extern Fighter_DemoStrings ftCl_Init_DemoMotionFilenames;

void ftCl_Init_OnItemPickup(HSD_GObj*, bool);
void ftCl_Init_OnItemDrop(HSD_GObj*, bool);
void ftCl_Init_80149268(HSD_GObj*);
void ftCl_Init_OnKnockbackExit(HSD_GObj* gobj);
void ftCl_Init_80149114(HSD_GObj* gobj);
void ftCl_Init_8014919C(HSD_GObj* gobj);
void ftCl_Init_OnDeath(HSD_GObj* gobj);
bool ftCl_Init_8014920C(HSD_GObj* gobj);
void ftCl_Init_801492C4(HSD_GObj* gobj);
u32 ftCl_Init_801492F4(HSD_GObj* gobj);
void ftCl_Init_80149318(HSD_GObj* gobj);
void ftCl_Init_OnLoad(HSD_GObj* gobj);
void ftCl_Init_OnItemPickupExt(HSD_GObj* gobj, bool arg1);
void ftCl_Init_OnItemInvisible(HSD_GObj* gobj);
void ftCl_Init_OnItemVisible(HSD_GObj* gobj);
void ftCl_Init_OnItemDropExt(HSD_GObj* gobj, bool arg1);
void ftCl_Init_LoadSpecialAttrs(HSD_GObj* gobj);
void ftCl_Init_OnKnockbackEnter(HSD_GObj* gobj);
void ftLk_0877_800CEDE0(HSD_GObj*);
void ftLk_0877_800CEE00(HSD_GObj*);
void ftLk_0877_800CEE30(HSD_GObj*);
void ftLk_0877_800CEE50(HSD_GObj*);
void ftCl_Unk2_80149354(HSD_GObj*);
void ftCl_Unk2_8014943C(HSD_GObj*);
void ftCl_Unk2_8014945C(HSD_GObj*);
void ftCl_Unk2_8014947C(HSD_GObj*);
void ftCl_Unk2_80149354(HSD_GObj*);
void ftCl_Unk2_8014943C(HSD_GObj*);
void ftCl_Unk2_8014945C(HSD_GObj*);
void ftCl_Unk2_8014947C(HSD_GObj*);
void ftLk_800ED15C(HSD_GObj*);
void ftLk_800EDD88(HSD_GObj*);
void ftLk_800EDFD8(HSD_GObj*);
void ftLk_800EE098(HSD_GObj*);
void ftLk_800ED480(HSD_GObj*);
void ftLk_800EDE30(HSD_GObj*);
void ftLk_800EDFF8(HSD_GObj*);
void ftLk_800EE120(HSD_GObj*);
void ftLk_800ED5B4(HSD_GObj*);
void ftLk_800EDEAC(HSD_GObj*);
void ftLk_800EE018(HSD_GObj*);
void ftLk_800EE1A8(HSD_GObj*);
void ftLk_800ED72C(HSD_GObj*);
void ftLk_800EDEB0(HSD_GObj*);
void ftLk_800EE038(HSD_GObj*);
void ftLk_800EE2E0(HSD_GObj*);
void ftLk_800EDA58(HSD_GObj*);
void ftLk_800EDF58(HSD_GObj*);
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
void ftLk_800EC8CC(HSD_GObj*);
void ftLk_800ECA1C(HSD_GObj*);
void ftLk_800EC634(HSD_GObj*);
void ftLk_800EC8EC(HSD_GObj*);
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
void ftLk_0877_800C3D6C(HSD_GObj*);
void ftLk_0877_800C4384(HSD_GObj*);
void ftLk_0877_800C438C(HSD_GObj*);
void ftLk_0877_800C447C(HSD_GObj*);
void ftLk_0877_800C4380(HSD_GObj*);
void ftLk_0877_800C4388(HSD_GObj*);
void ftLk_0877_800C4438(HSD_GObj*);
void ftLk_80082B78(HSD_GObj*);

static inline void checkFighter2244(HSD_GObj* gobj)
{
    Fighter* fp;

    if (gobj == NULL) {
        return;
    }

    fp = gobj->user_data;
    if (fp != NULL && fp->fv.cl.x2244 != 0) {
        it_802C8C34(fp->fv.cl.x2244);
        fp->fv.cl.x2244 = 0;
    }

    if (gobj == NULL) {
        gobj == NULL;
    }
}

#endif
