#ifndef MELEE_FT_CHARA_FTCRAZYHAND_FTCRAZYHAND_H
#define MELEE_FT_CHARA_FTCRAZYHAND_FTCRAZYHAND_H

#include "ft/ftcommon.h"
#include "ft/types.h"
#include "lb/lbvector.h"

typedef struct _ftCrazyHandAttributes {
    s32 x0;
    s32 x4;
    s32 x8;
    s32 xC;
    s32 x10;
    f32 x14;
    f32 x18;
    f32 x1C;
    s32 x20;
    s32 x24;
    f32 x28;
    f32 x2C;
    Vec2 x30_pos2;
    f32 x38;
    f32 x3C;
    Vec3 x40_pos;
    f32 x4C;
    Vec2 x50;
    f32 x58;
    f32 x5C;
    f32 x60;
    f32 x64;
    f32 x68;
    s32 x6C;
    s32 x70;
    s32 x74;
    f32 x78;
    s32 x7C;
    f32 x80;
    s32 x84;
    Vec2 x88_pos;
    s32 x90;
    s32 x94;
    f32 x98;
    f32 x9C;
    s32 xA0;
    f32 xA4;
    Vec2 xA8_pos;
    s32 xB0;
    s32 xB4;
    f32 xB8;
    Vec2 xBC_pos;
    Vec2 xC4_pos;
    Vec2 xCC_pos;
    f32 xD4;
    f32 xD8;
    f32 xDC;
    f32 xE0;
    f32 xE4;
    f32 xE8;
    s32 xEC;
    s32 xF0;
    f32 xF4;
    f32 xF8;
    f32 xFC;
    f32 x100;
    f32 x104;
    f32 x108;
    f32 x10C;
    Vec2 x110_pos;
    Vec2 x118_pos;
    f32 x120;
    Vec2 x124_pos;
    Vec2 x12C_pos;
    Vec2 x134_pos;
    Vec2 x13C_pos;
} ftCrazyHandAttributes;

extern ActionState as_table_crazyhand[];
extern char lbl_803D4818[];
extern char lbl_803D4824[];
extern Fighter_CostumeStrings lbl_803D4868[];
extern char lbl_803D485C[];

void ftCrazyhand_OnDeath(HSD_GObj* fighter_gobj);
void ftCrazyhand_OnLoad(HSD_GObj* fighter_gobj);
void ftCrazyHand_LoadSpecialAttrs(HSD_GObj* gobj);
void func_80155FCC(HSD_GObj*);
void func_80156014(HSD_GObj*);
void func_8015A2B0(HSD_GObj*);
void func_8015A3F4(HSD_GObj*);
void func_8015A560(HSD_GObj*);
void lbl_80156404(HSD_GObj*);
void lbl_80156A70(HSD_GObj*);
void lbl_80156AB4(HSD_GObj*);
void lbl_80156AD4(HSD_GObj*);
void lbl_80156404(HSD_GObj*);
void lbl_80156A70(HSD_GObj*);
void lbl_80156AB4(HSD_GObj*);
void lbl_80156AD4(HSD_GObj*);
void lbl_80156FDC(HSD_GObj*);
void lbl_80157018(HSD_GObj*);
void lbl_8015705C(HSD_GObj*);
void lbl_8015707C(HSD_GObj*);
void lbl_801570CC(HSD_GObj*);
void lbl_80157108(HSD_GObj*);
void lbl_8015714C(HSD_GObj*);
void lbl_8015716C(HSD_GObj*);
void lbl_80157204(HSD_GObj*);
void lbl_801572D4(HSD_GObj*);
void lbl_80157318(HSD_GObj*);
void lbl_80157378(HSD_GObj*);
void lbl_801573C8(HSD_GObj*);
void lbl_80157424(HSD_GObj*);
void lbl_80157404(HSD_GObj*);
void lbl_80157468(HSD_GObj*);
void lbl_801574B8(HSD_GObj*);
void lbl_801574F4(HSD_GObj*);
void lbl_80157538(HSD_GObj*);
void lbl_80157558(HSD_GObj*);
void lbl_801575A8(HSD_GObj*);
void lbl_801575E4(HSD_GObj*);
void lbl_80157628(HSD_GObj*);
void lbl_80157648(HSD_GObj*);
void lbl_801576B0(HSD_GObj*);
void lbl_80157724(HSD_GObj*);
void lbl_80157768(HSD_GObj*);
void lbl_801578E4(HSD_GObj*);
void lbl_80157844(HSD_GObj*);
void lbl_80157880(HSD_GObj*);
void lbl_801578C4(HSD_GObj*);
void lbl_801578E4(HSD_GObj*);
void lbl_80157934(HSD_GObj*);
void lbl_8015798C(HSD_GObj*);
void lbl_801579D0(HSD_GObj*);
void lbl_801579F0(HSD_GObj*);
void lbl_80157A40(HSD_GObj*);
void lbl_80157ABC(HSD_GObj*);
void lbl_80157B00(HSD_GObj*);
void lbl_80157B54(HSD_GObj*);
void lbl_80157BAC(HSD_GObj*);
void lbl_80157BE8(HSD_GObj*);
void lbl_80157C2C(HSD_GObj*);
void lbl_80157C4C(HSD_GObj*);
void lbl_80157CB0(HSD_GObj*);
void lbl_80157CEC(HSD_GObj*);
void lbl_80157D30(HSD_GObj*);
void lbl_80157DF4(HSD_GObj*);
void lbl_80157EA0(HSD_GObj*);
void lbl_80157F84(HSD_GObj*);
void lbl_80157FC8(HSD_GObj*);
void lbl_80158140(HSD_GObj*);
void lbl_80157F48(HSD_GObj*);
void lbl_80157F84(HSD_GObj*);
void lbl_80157FC8(HSD_GObj*);
void lbl_80158140(HSD_GObj*);
void lbl_801581A4(HSD_GObj*);
void lbl_801581E0(HSD_GObj*);
void lbl_80158224(HSD_GObj*);
void lbl_801582D4(HSD_GObj*);
void lbl_80158340(HSD_GObj*);
void lbl_8015837C(HSD_GObj*);
void lbl_801583C0(HSD_GObj*);
void lbl_801583E0(HSD_GObj*);
void lbl_80158450(HSD_GObj*);
void lbl_801584CC(HSD_GObj*);
void lbl_80158510(HSD_GObj*);
void lbl_80158530(HSD_GObj*);
void lbl_8015870C(HSD_GObj*);
void lbl_80158748(HSD_GObj*);
void lbl_8015878C(HSD_GObj*);
void lbl_801587AC(HSD_GObj*);
void lbl_80158814(HSD_GObj*);
void lbl_80158850(HSD_GObj*);
void lbl_80158894(HSD_GObj*);
void lbl_801588B4(HSD_GObj*);
void lbl_80158BBC(HSD_GObj*);
void lbl_80158C44(HSD_GObj*);
void lbl_80158C88(HSD_GObj*);
void lbl_80158DF8(HSD_GObj*);
void lbl_80158E7C(HSD_GObj*);
void lbl_80158ECC(HSD_GObj*);
void lbl_80158F10(HSD_GObj*);
void lbl_80158F30(HSD_GObj*);
void lbl_80159134(HSD_GObj*);
void lbl_801591C0(HSD_GObj*);
void lbl_80159204(HSD_GObj*);
void lbl_80159264(HSD_GObj*);
void lbl_8015ACD0(HSD_GObj*);
void lbl_8015AD28(HSD_GObj*);
void lbl_8015AD6C(HSD_GObj*);
void lbl_8015ADCC(HSD_GObj*);
void lbl_8015ACD0(HSD_GObj*);
void lbl_8015AD28(HSD_GObj*);
void lbl_8015AD6C(HSD_GObj*);
void lbl_8015ADCC(HSD_GObj*);
void lbl_80159388(HSD_GObj*);
void lbl_8015940C(HSD_GObj*);
void lbl_80159450(HSD_GObj*);
void lbl_801594B0(HSD_GObj*);
void lbl_80159534(HSD_GObj*);
void lbl_80159608(HSD_GObj*);
void lbl_8015964C(HSD_GObj*);
void lbl_8015966C(HSD_GObj*);
void lbl_801596D0(HSD_GObj*);
void lbl_80159788(HSD_GObj*);
void lbl_801597CC(HSD_GObj*);
void lbl_801597EC(HSD_GObj*);
void lbl_80158FB4(HSD_GObj*);
void lbl_80158FF0(HSD_GObj*);
void lbl_80159034(HSD_GObj*);
void lbl_80159094(HSD_GObj*);
void lbl_80159858(HSD_GObj*);
void lbl_801598A0(HSD_GObj*);
void lbl_801598E4(HSD_GObj*);
void lbl_80159904(HSD_GObj*);
void lbl_801599C0(HSD_GObj*);
void lbl_80159A08(HSD_GObj*);
void lbl_80159A4C(HSD_GObj*);
void lbl_80159AA0(HSD_GObj*);
void lbl_80159D04(HSD_GObj*);
void lbl_80159E8C(HSD_GObj*);
void lbl_80159ED0(HSD_GObj*);
void lbl_80159F3C(HSD_GObj*);
void lbl_80159F8C(HSD_GObj*);
void lbl_80159FC8(HSD_GObj*);
void lbl_8015A00C(HSD_GObj*);
void lbl_8015A02C(HSD_GObj*);
void lbl_8015A0C4(HSD_GObj*);
void lbl_8015A10C(HSD_GObj*);
void lbl_8015A150(HSD_GObj*);
void lbl_8015A180(HSD_GObj*);
void lbl_8015A20C(HSD_GObj*);
void lbl_8015A248(HSD_GObj*);
void lbl_8015A28C(HSD_GObj*);
void lbl_8015A2AC(HSD_GObj*);
void lbl_8015A318(HSD_GObj*);
void lbl_8015A38C(HSD_GObj*);
void lbl_8015A3D0(HSD_GObj*);
void lbl_8015A3F0(HSD_GObj*);
void lbl_8015A464(HSD_GObj*);
void lbl_8015A4F8(HSD_GObj*);
void lbl_8015A53C(HSD_GObj*);
void lbl_8015A55C(HSD_GObj*);
void lbl_8015A5D0(HSD_GObj*);
void lbl_8015A664(HSD_GObj*);
void lbl_8015A6A8(HSD_GObj*);
void lbl_8015A6C8(HSD_GObj*);
void lbl_8015A6CC(HSD_GObj*);
void lbl_8015A750(HSD_GObj*);
void lbl_8015A794(HSD_GObj*);
void lbl_8015A7B4(HSD_GObj*);
void lbl_8015A7B8(HSD_GObj*);
void lbl_8015A820(HSD_GObj*);
void lbl_8015A864(HSD_GObj*);
void lbl_8015A884(HSD_GObj*);
void lbl_8015A8D4(HSD_GObj*);
void lbl_8015A910(HSD_GObj*);
void lbl_8015A954(HSD_GObj*);
void lbl_8015A974(HSD_GObj*);
void lbl_8015A978(HSD_GObj*);
void lbl_8015AA00(HSD_GObj*);
void lbl_8015AA44(HSD_GObj*);
void lbl_8015AAA4(HSD_GObj*);
void lbl_8015AB04(HSD_GObj*);
void lbl_8015AB84(HSD_GObj*);
void lbl_8015ABC8(HSD_GObj*);
void lbl_8015ABCC(HSD_GObj*);
void lbl_8015AF04(HSD_GObj*);
void lbl_8015B0FC(HSD_GObj*);
void lbl_8015B140(HSD_GObj*);
void lbl_8015B170(HSD_GObj*);
void lbl_8015B000(HSD_GObj*);
void lbl_8015B0FC(HSD_GObj*);
void lbl_8015B140(HSD_GObj*);
void lbl_8015B170(HSD_GObj*);
void lbl_8015B22C(HSD_GObj*);
void lbl_8015B274(HSD_GObj*);
void lbl_8015B2B8(HSD_GObj*);
void lbl_8015B2BC(HSD_GObj*);
void lbl_8015BB70(HSD_GObj*);
void lbl_8015BBD8(HSD_GObj*);
void lbl_8015BC38(HSD_GObj*);
void lbl_8015BB70(HSD_GObj*);
void lbl_8015BBD8(HSD_GObj*);
void lbl_8015BC38(HSD_GObj*);
void func_8015B660(HSD_GObj*);
void func_8015B664(HSD_GObj*);
void func_8015B668(HSD_GObj*);
void func_8015B66C(HSD_GObj*);
void func_8015B704(HSD_GObj*);
void func_8015B76C(HSD_GObj*);
void func_8015B770(HSD_GObj*);
void func_8015B774(HSD_GObj*);
void func_8015B840(HSD_GObj*);
void func_8015B844(HSD_GObj*);
void func_8015B848(HSD_GObj*);
void func_8015B84C(HSD_GObj*);
void func_8015B8EC(HSD_GObj*);
void func_8015B8F0(HSD_GObj*);
void func_8015B8F4(HSD_GObj*);
void func_8015B8F8(HSD_GObj*);

#endif
