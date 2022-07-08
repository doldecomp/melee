#ifndef _ftmars_h_
#define _ftmars_h_

#include <global.h>
#include <dolphin/types.h>
#include "sysdolphin/baselib/gobj.h"
#include "melee/ft/fighter.h"

typedef struct _MarsAttributes {
    s32 x0;
    s32 x4;
    s32 x8;
    f32 xC;
    f32 x10;
    f32 x14;
    f32 x18;
    f32 x1C;
    f32 x20;
    f32 x24;
    f32 x28;
    f32 x2C;
    f32 x30;
    f32 x34;
    f32 x38;
    f32 x3C;
    f32 x40;
    f32 x44;
    f32 x48;
    f32 x4C;
    f32 x50;
    f32 x54;
    f32 x58;
    f32 x5C;
    f32 x60;
    f32 x64;
    u8 data_filler_68[0x98 - 0x68];
} MarsAttributes;

void ftMars_OnDeath(HSD_GObj* gobj);
void ftMars_OnItemPickup(HSD_GObj* gobj, BOOL arg1);
void ftMars_OnItemInvisible(HSD_GObj* gobj);
void ftMars_OnItemVisible(HSD_GObj* gobj);
void ftMars_OnItemDrop(HSD_GObj* gobj, BOOL arg1);
void ftMars_OnLoadForRoy(Fighter* ft);
void ftMars_OnLoad(HSD_GObj* gobj);
void func_801364E8(HSD_GObj* gobj);
void ftMars_OnKnockbackEnter(HSD_GObj* gobj);
void ftMars_OnKnockbackExit(HSD_GObj* gobj);
void lbl_801365A8(HSD_GObj* gobj);
void lbl_8013666C(HSD_GObj* gobj);
void lbl_80136730(HSD_GObj* gobj);

void ftMars_SpecialN_StartAction(HSD_GObj* gobj);
void ftMars_SpecialNAir_StartAction(HSD_GObj* gobj);
void lbl_80136844(HSD_GObj* gobj);
void lbl_801368AC(HSD_GObj* gobj);
void lbl_80136914(HSD_GObj* gobj);
void lbl_80136918(HSD_GObj* gobj);
void lbl_8013691C(HSD_GObj* gobj);
void lbl_8013695C(HSD_GObj* gobj);
void lbl_801369A4(HSD_GObj* gobj);
void lbl_801369E0(HSD_GObj* gobj);
void func_80136A1C(HSD_GObj* gobj);
void func_80136A7C(HSD_GObj* gobj);
void lbl_80136ADC(HSD_GObj* gobj);
void lbl_80136BB4(HSD_GObj* gobj);
void lbl_80136C8C(HSD_GObj* gobj);
void lbl_80136CC4(HSD_GObj* gobj);
void lbl_80136CFC(HSD_GObj* gobj);
void lbl_80136D1C(HSD_GObj* gobj);
void lbl_80136D3C(HSD_GObj* gobj);
void lbl_80136D78(HSD_GObj* gobj);
void func_80136DB4(HSD_GObj* gobj);
void func_80136E14(HSD_GObj* gobj);
void func_80136E74(HSD_GObj* gobj);
void func_80136EAC(HSD_GObj* gobj);
void lbl_80136EE4(HSD_GObj *gobj);
void lbl_80137010(HSD_GObj* gobj);
void lbl_8013713C(HSD_GObj* gobj);
void lbl_80137140(HSD_GObj* gobj);
void lbl_80137144(HSD_GObj *gobj);
void lbl_80137164(HSD_GObj *gobj);
void lbl_80137184(HSD_GObj* gobj);
void lbl_801371C0(HSD_GObj* arg0);
void func_801371FC(HSD_GObj* gobj);
void func_801372A8(HSD_GObj* gobj);
void func_80137354(HSD_GObj* gobj);
void func_801373B8(HSD_GObj* gobj);

void ftMars_SpecialS_StartAction(HSD_GObj* gobj);
void ftMars_SpecialSAir_StartAction(HSD_GObj* gobj);
void lbl_80137558(HSD_GObj* gobj);
void lbl_801375B8(HSD_GObj* gobj);
void lbl_80137618(HSD_GObj* gobj);
void lbl_8013767C(HSD_GObj* gobj);
void func_801376E8(HSD_GObj* gobj);
void func_80137748(HSD_GObj* gobj);
void lbl_801377B0(HSD_GObj* gobj);
void lbl_80137810(HSD_GObj* gobj);
void lbl_80137870(HSD_GObj* gobj);
void lbl_801378D4(HSD_GObj* gobj);
void func_80137940(HSD_GObj* gobj);
void func_801379D0(HSD_GObj* gobj);
void lbl_80137A68(HSD_GObj* gobj);
void func_80137A9C(HSD_GObj* gobj);
void lbl_80137B34(HSD_GObj* gobj);
void lbl_80137B94(HSD_GObj* gobj);
void lbl_80137BF4(HSD_GObj* gobj);
void lbl_80137C50(HSD_GObj* gobj);
void func_80137CBC(HSD_GObj* gobj);
void func_80137D60(HSD_GObj* gobj);
void func_80137E0C(HSD_GObj* gobj);
void lbl_80137ECC(HSD_GObj* gobj);
void lbl_80137F2C(HSD_GObj* gobj);
void lbl_80137F30(HSD_GObj* gobj);
void lbl_80137F8C(HSD_GObj* gobj);
void func_80137FF8(HSD_GObj* gobj);
void func_8013809C(HSD_GObj* gobj);
void func_80138148(HSD_GObj* gobj);

void ftMars_SpecialHi_StartAction(HSD_GObj* gobj);
void ftMars_SpecialHiAir_StartAction(HSD_GObj* gobj);
void lbl_801382E8(HSD_GObj* gobj);
void lbl_80138348(HSD_GObj* gobj);
void lbl_801383A8(HSD_GObj* gobj);
void lbl_801384F0(HSD_GObj* gobj);
void lbl_80138638(HSD_GObj* gobj);
void lbl_8013873C(HSD_GObj* gobj);
void lbl_80138884(HSD_GObj* gobj);
void lbl_801388B4(HSD_GObj* gobj);
void lbl_80138940(HSD_GObj* gobj);

void ftMars_SpecialLw_StartAction(HSD_GObj* gobj);
void ftMars_SpecialLwAir_StartAction(HSD_GObj* gobj);
void lbl_80138AA8(HSD_GObj* gobj);
void lbl_80138B64(HSD_GObj* gobj);
void lbl_80138C20(HSD_GObj* gobj);
void lbl_80138C24(HSD_GObj* gobj);
void lbl_80138C28(HSD_GObj* gobj);
void lbl_80138C5C(HSD_GObj* gobj);
void lbl_80138CC0(HSD_GObj* gobj);
void lbl_80138CFC(HSD_GObj* gobj);
void func_80138D38(HSD_GObj* gobj);
void func_80138DD0(HSD_GObj* gobj);
void lbl_80138E68(HSD_GObj* gobj);
void lbl_80138F14(HSD_GObj* gobj);
void lbl_80138FC0(HSD_GObj* gobj);
void lbl_80138FC4(HSD_GObj* gobj);
void lbl_80138FC8(HSD_GObj* gobj);
void lbl_80138FE8(HSD_GObj* gobj);
void lbl_80139008(HSD_GObj* gobj);
void lbl_80139044(HSD_GObj* gobj);
void func_80139080(HSD_GObj* gobj);
void func_801390E0(HSD_GObj* gobj);
void lbl_80139140(HSD_GObj* gobj);

#endif
