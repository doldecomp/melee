#ifndef _ftunk006_h_
#define _ftunk006_h_

#include <dolphin/types.h>

#include <melee/ft/chara/ftLink/ftlink.h>
#include <sysdolphin/baselib/gobj.h>

#include <common_structs.h>
#include <melee/ft/fighter.h>

s32 func_800877F8(HSD_GObj* fighter_gobj, s32 arg1);
s32 func_80087818(HSD_GObj* fighter_gobj, s32 arg1);
s32 func_80087838(HSD_GObj* fighter_gobj);
s32 func_80087858(HSD_GObj* fighter_gobj);
s32 func_80087878(HSD_GObj* fighter_gobj, s32 arg1);
s32 func_800878BC(HSD_GObj* fighter_gobj);
s32 func_80087900(HSD_GObj* fighter_gobj);
s32 func_80087944(HSD_GObj* fighter_gobj);
s32 func_80087988(HSD_GObj* fighter_gobj);
s32 func_800879D8(HSD_GObj* fighter_gobj);
s32 func_800879F8(HSD_GObj* fighter_gobj);
s32 func_80087A18(HSD_GObj* fighter_gobj);
u8 func_80087A80(HSD_GObj* fighter_gobj);
f32 func_80087A8C(HSD_GObj* fighter_gobj);
s32 func_80087A98(HSD_GObj* fighter_gobj);
u8 func_80087AA4(HSD_GObj* fighter_gobj);
u8 func_80087AB4(HSD_GObj* fighter_gobj);
void func_80087AC0(HSD_GObj* fighter_gobj, s32 arg1);
s32 func_80087AEC(HSD_GObj* fighter_gobj);
s32 func_80087B34(HSD_GObj* fighter_gobj);
void func_80087BAC(HSD_GObj* fighter_gobj, s32 arg1);
void func_80087BC0(HSD_GObj* fighter_gobj, s8 arg1);
void func_80087BEC(HSD_GObj* fighter_gobj, u8 arg1);
s32 func_80087C1C();
s32 func_80087C58(HSD_GObj* fighter_gobj);
void func_80087C64(HSD_GObj* fighter_gobj, s32 arg1);
s32 func_80087C70(Fighter* fp, s32 arg1);
s32 func_80087D0C(Fighter* fighter, s32 arg1);
void func_8008805C(Fighter* arg0, s32 arg1);
void func_80088080(Fighter* fp);
void func_800880AC(Fighter* fp);
void func_800880D8(Fighter* fp);
void func_80088110(Fighter* fp);
void func_800D5BF8(HSD_GObj* fighter_gobj);
unk_t func_800D0EC8();
unk_t func_8009A3C8();
unk_t func_8004B4B0();
unk_t func_8009EDA4();
unk_t func_8009F39C();
unk_t func_800C703C();
void func_800887CC(Fighter* fp);
void func_80088884(Fighter* fp);
void func_800888E0(Fighter* fp);
void func_80088A50(Fighter* fp);
void func_80088C5C(HSD_GObj* fighter_gobj);
void func_800890BC(Fighter* fp);
void func_800890D0(Fighter* fp, u8 move_id);
void func_800892A0(HSD_GObj* fighter_gobj);
void func_800892D4(Fighter* fp);
void func_800895E0(Fighter* fp, s32 flags);
void func_80089824(HSD_GObj* fighter_gobj);
void func_80089B08(HSD_GObj* pPlayerEntityStruct);
void func_8008A2BC(HSD_GObj* fighter_gobj);
void func_8008A324(HSD_GObj* fighter_gobj);
BOOL func_8008A9F8(HSD_GObj* fighter_gobj);
BOOL func_8008B658(HSD_GObj* fighter_gobj);
BOOL func_8008B980(HSD_GObj* fighter_gobj);
BOOL func_8008BB44(HSD_GObj* fighter_gobj);
void func_800D638C(HSD_GObj* fighter_gobj);
BOOL func_800D5F58(HSD_GObj* fighter_gobj);
BOOL func_8008BFC4(HSD_GObj* fighter_gobj);
BOOL func_8008C830(HSD_GObj* fighter_gobj);
BOOL func_8008CB44(HSD_GObj* fighter_gobj);
s32 func_8008CE68(Fighter* fp);
void func_8008CFAC(HSD_GObj* fighter_gobj, s32 asid);
BOOL func_800CB870(HSD_GObj* fighter_gobj);
void func_8008D708(HSD_GObj* fighter_gobj, s32 asid, f32 lag);
void func_800D5D3C(HSD_GObj* fighter_gobj);
void func_800D5F18(HSD_GObj* fighter_gobj);
void func_800D5F38(HSD_GObj* fighter_gobj);
f32 func_8008D7F0(Fighter* fp);
f32 scaleBy154_8008D8D8(f32 force);
BOOL func_8008D8E8(f32 force);
void func_8008DCE0(HSD_GObj* fighter_gobj, s32 asid, f32);
void func_8008E908(HSD_GObj* fighter_gobj, f32);
BOOL func_8008E984(Fighter* fp);
void func_8008E9D0(HSD_GObj* fighter_gobj);
void func_8008EB58(HSD_GObj* fighter_gobj);
void func_8008EC90(HSD_GObj* fighter_gobj);
void func_80090780(HSD_GObj* fighter_gobj);
void func_800CCAAC(HSD_GObj* fighter_gobj);
void func_80097D40(HSD_GObj* fighter_gobj);
unk_t func_80090828();
func_80090594(Fighter* fp, s32 damage_dealt, BOOL bool, s32 action_state_index, GroundOrAir ground_or_air, f32 vibrate_mult);
u32 func_80090690(Fighter* fp, Vec2* shift);
void func_80090718(Fighter* fp);
BOOL func_80082888(HSD_GObj* fighter_gobj, ftCollisionBox*);
BOOL func_80081D0C(HSD_GObj* fighter_gobj);
void func_800928CC(HSD_GObj* fighter_gobj);
BOOL func_8009917C(HSD_GObj* fighter_gobj);
unk_t func_80092BE8();
void func_80092BCC(HSD_GObj* fighter_gobj);
f32 func_80092ED8(s32, ftLinkAttributes*, f32);
unk_t func_80093240();
unk_t func_800932DC();
unk_t func_80093BC0();
BOOL func_80093694();
BOOL func_8009515C(HSD_GObj* fighter_gobj);
BOOL func_80099794(HSD_GObj* fighter_gobj);
BOOL func_800D8990(HSD_GObj* fighter_gobj);
BOOL func_8009A080(HSD_GObj* fighter_gobj);
void func_800C88D4(HSD_GObj* dst_gobj, s32 src_x2030, BOOL);
BOOL func_80094790(HSD_GObj* fighter_gobj);
void func_80095744(HSD_GObj* fighter_gobj, BOOL);
BOOL func_800964FC(Fighter* fp);
BOOL func_80096540(HSD_GObj* fighter_gobj);
void func_800968C8(HSD_GObj* fighter_gobj);
void func_80096900(HSD_GObj* fighter_gobj, BOOL, BOOL, BOOL is_interruptible, f32 freefall_mobility, f32 landing_lag);

#endif
