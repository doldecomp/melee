#ifndef MELEE_FT_CHARA_FTPURIN_FTPURIN_H
#define MELEE_FT_CHARA_FTPURIN_FTPURIN_H

#include "melee/ft/forward.h"
#include <melee/ft/ftcommon.h>
#include <melee/ft/types.h>
#include <melee/lb/lbvector.h>

typedef struct _ftPurinAttributes {
    f32 x0;
    f32 x4;
    f32 x8;
    f32 xC;
    f32 x10;
    s32 x14;
    f32 x18;
    s32 x1C;
    s32 x20;
    s32 x24;
    s32 x28;
    s32 x2C;
    u8 data_filler_1[0x100 - 0x30];
} ftPurinAttributes;

extern ActionState as_table_purin[];
extern char lbl_803D02F0[];
extern char lbl_803D02FC[];
extern Fighter_CostumeStrings lbl_803D0508[];
extern char lbl_803D047C[];
extern Fighter_DemoStrings lbl_803D04F8;

/// functions

void ftPurin_LoadSpecialAttrs(HSD_GObj* fighter_gobj);
void ftPurin_OnDeath(HSD_GObj* fighter_gobj);
void ftPurin_OnItemDrop(HSD_GObj* fighter_gobj, bool bool1);
void ftPurin_OnItemInvisible(HSD_GObj* fighter_gobj);
void ftPurin_OnItemPickup(HSD_GObj* fighter_gobj, bool bool);
void ftPurin_OnItemVisible(HSD_GObj* fighter_gobj);
void ftPurin_OnKnockbackEnter(HSD_GObj* fighter_gobj);
void ftPurin_OnKnockbackExit(HSD_GObj* fighter_gobj);
void ftPurin_OnLoad(HSD_GObj* fighter_gobj);
void ftPurin_OnUserDataRemove(HSD_GObj* fighter_gobj);
void ftPurin_SpecialAirHi_StartAction(HSD_GObj*);
void ftPurin_SpecialAirLw_StartAction(HSD_GObj*);
void ftPurin_SpecialAirN_StartAction(HSD_GObj*);
void ftPurin_SpecialAirS_StartAction(HSD_GObj*);
void ftPurin_SpecialHi_SetVars(HSD_GObj* fighter_gobj);
void ftPurin_SpecialHi_StartAction(HSD_GObj*);
void ftPurin_SpecialLw_StartAction(HSD_GObj*);
void ftPurin_SpecialN_StartAction(HSD_GObj*);
void ftPurin_SpecialS_StartAction(HSD_GObj*);
void func_800D7590(HSD_GObj*);
void func_800D7614(HSD_GObj*);
void func_800D7634(HSD_GObj*);
void func_800D767C(HSD_GObj*);
void func_8013C2F8(void);
void func_8013C360(HSD_GObj* fighter_gobj);
void func_8013C494(HSD_GObj* fighter_gobj);
void func_8013C4F0(HSD_GObj* fighter_gobj, int arg1, Mtx vmtx);
void func_8013C614(Fighter* fp, int arg1, bool arg2);
void func_8013CD34(HSD_GObj*);
void func_8013CDD8(HSD_GObj*);
void func_8013D104(HSD_GObj*);
void func_8013D19C(HSD_GObj*);
void func_8013D590(HSD_GObj*);
void func_8013D5F0(HSD_GObj*);
void func_8013D8E4(HSD_GObj*);
void func_8013DA24(HSD_GObj*);
void func_8013DC64(HSD_GObj*);
void func_8013DD54(HSD_GObj*);
void lbl_8013C94C(HSD_GObj*);
void lbl_8013CB68(HSD_GObj*);
void lbl_8013CBE4(HSD_GObj*);
void lbl_8013CC60(HSD_GObj*);
void lbl_8013CC64(HSD_GObj*);
void lbl_8013CC68(HSD_GObj*);
void lbl_8013CC88(HSD_GObj*);
void lbl_8013CCA8(HSD_GObj*);
void lbl_8013CCE4(HSD_GObj*);
void lbl_8013CE7C(HSD_GObj*);
void lbl_8013CFCC(HSD_GObj*);
void lbl_8013D008(HSD_GObj*);
void lbl_8013D044(HSD_GObj*);
void lbl_8013D048(HSD_GObj*);
void lbl_8013D04C(HSD_GObj*);
void lbl_8013D06C(HSD_GObj*);
void lbl_8013D08C(HSD_GObj*);
void lbl_8013D0C8(HSD_GObj*);
void lbl_8013D30C(HSD_GObj*);
void lbl_8013D348(HSD_GObj*);
void lbl_8013D384(HSD_GObj*);
void lbl_8013D388(HSD_GObj*);
void lbl_8013D38C(HSD_GObj*);
void lbl_8013D3AC(HSD_GObj*);
void lbl_8013D518(HSD_GObj*);
void lbl_8013D554(HSD_GObj*);
void lbl_8013D658(HSD_GObj*);
void lbl_8013D764(HSD_GObj*);
void lbl_8013D8B0(HSD_GObj*);
void lbl_8013E014(HSD_GObj*);
void lbl_8013E0F0(HSD_GObj*);
void lbl_8013E2A0(HSD_GObj*);
void lbl_8013E410(HSD_GObj*);
void lbl_8013E7E0(HSD_GObj*);
void lbl_8013EAD8(HSD_GObj*);
void lbl_8013EDB0(HSD_GObj*);
void lbl_8013EE84(HSD_GObj*);
void lbl_8013F034(HSD_GObj*);
void lbl_8013F1A4(HSD_GObj*);
void lbl_8013F708(HSD_GObj*);
void lbl_8013F9C0(HSD_GObj*);
void lbl_8013FCAC(HSD_GObj*);
void lbl_8013FF00(HSD_GObj*);
void lbl_8013FF04(HSD_GObj*);
void lbl_80140064(HSD_GObj*);
void lbl_801401C4(HSD_GObj*);
void lbl_80140344(HSD_GObj*);
void lbl_80140348(HSD_GObj*);
void lbl_8014034C(HSD_GObj*);
void lbl_80140350(HSD_GObj*);
void lbl_801404B0(HSD_GObj*);
void lbl_80140610(HSD_GObj*);
void lbl_80140614(HSD_GObj*);
void lbl_80140618(HSD_GObj*);
void lbl_8014061C(HSD_GObj*);
void lbl_80140620(HSD_GObj*);
void lbl_80140650(HSD_GObj*);
void lbl_80140680(HSD_GObj*);
void lbl_801406B0(HSD_GObj*);
void lbl_801408B8(HSD_GObj*);
void lbl_80140BAC(HSD_GObj*);
void lbl_80140BE8(HSD_GObj*);
void lbl_80140C18(HSD_GObj*);
void lbl_80140C48(HSD_GObj*);
void lbl_80140C78(HSD_GObj*);
void lbl_80140DF8(HSD_GObj*);
void lbl_80140F10(HSD_GObj*);
void lbl_80140F40(HSD_GObj*);
void lbl_80140FA4(HSD_GObj*);
void lbl_80141054(HSD_GObj*);
void lbl_80141154(HSD_GObj*);
void lbl_80141254(HSD_GObj*);
void lbl_801415F4(HSD_GObj*);
void lbl_801416D0(HSD_GObj*);
void lbl_80141730(HSD_GObj*);
void lbl_801417E0(HSD_GObj*);
void lbl_801418E0(HSD_GObj*);
void lbl_801419E0(HSD_GObj*);
void lbl_80141FB8(HSD_GObj*);
void lbl_80142070(HSD_GObj*);
void lbl_801420D0(HSD_GObj*);
void lbl_8014222C(HSD_GObj*);
void* func_8013C664(HSD_GObj* fighter_gobj);

#endif
