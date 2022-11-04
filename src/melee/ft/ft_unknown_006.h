#ifndef MELEE_FT_FT_UNKNOWN_006_H
#define MELEE_FT_FT_UNKNOWN_006_H

#include <ctypes.h>
#include <melee/ft/enums.h>

#include <sysdolphin/baselib/gobj.h>

#include <melee/ft/ftcommon.h>

#include <common_structs.h>
#include <melee/ft/fighter.h>

typedef struct _ftCLinkAttributes ftCLinkAttributes;

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
void func_80090594(Fighter* fp, s32 damage_dealt, BOOL bool, s32 action_state_index, GroundOrAir ground_or_air, f32 vibrate_mult);
u32 func_80090690(Fighter* fp, Vec2* shift);
void func_80090718(Fighter* fp);
BOOL func_80082888(HSD_GObj* fighter_gobj, ftCollisionBox*);
BOOL func_80081D0C(HSD_GObj* fighter_gobj);
void func_800928CC(HSD_GObj* fighter_gobj);
BOOL func_8009917C(HSD_GObj* fighter_gobj);
unk_t func_80092BE8();
void func_80092BCC(HSD_GObj* fighter_gobj);
f32 func_80092ED8(s32, ftCLinkAttributes*, f32);
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
BOOL func_80096CC8(HSD_GObj* fighter_gobj);
void func_8009750C(HSD_GObj* fighter_gobj);
unk_t func_8009F834();
void func_80098B20(HSD_GObj* fighter_gobj);
void func_80098C9C(HSD_GObj* fighter_gobj);
void func_80099D9C(HSD_GObj* fighter_gobj);
void func_8009A804(HSD_GObj* fighter_gobj);
BOOL func_800C97A8(HSD_GObj* fighter_gobj);
void func_800CB59C(HSD_GObj* fighter_gobj);
void func_800CB438(HSD_GObj* fighter_gobj);
void func_8009CF84(Fighter* fp);
void func_8009E0A8(HSD_GObj* fighter_gobj);
void func_8009E0D4(Fighter* fp);
void func_8009E7B4(Fighter* fp, u8*);
BOOL func_8009EF68(HSD_GObj* fighter_gobj);
void func_8009F4A4(void);
void func_8009F578(Fighter* fp);
unk_t func_800C0658();
void func_800A0DA4(Fighter* fp);
void func_800A101C(Fighter* fp, s8 cpu_type, s8 cpu_level, BOOL);
f32 func_800A17E4(Fighter* fp);
f32 func_800A1874(Fighter* fp);
f32 func_800A1904(Fighter* fp);
f32 func_800A1948(Fighter* fp);
s32 func_800A198C(Fighter* fp);
f32 func_800A1994(Fighter* fp);
f32 func_800A1A24(Fighter* fp);
BOOL func_800A2040(Fighter* fp);
void func_800B3900(HSD_GObj* fighter_gobj);
void func_800BFD04(HSD_GObj* fighter_gobj);
void func_800BFFAC(Fighter* fp);
void func_800BFFD0(Fighter* fp, s32 anim_id, BOOL);
void func_800C0074(Fighter* fp);
void func_800C0134(Fighter* fp);
void func_800C0200(Fighter* fp, s32);
void func_800C0408(HSD_GObj* fighter_gobj);
s32 func_800C0694(Fighter* fp);
s32 func_800C06B4(Fighter* fp);
extern unk_t lbl_80459A68;
extern unk_t lbl_804D6570;
extern unk_t lbl_804D6574;
extern unk_t lbl_804D6578;
void func_800C09B4(HSD_GObj* fighter_gobj);
void func_800C0A98(HSD_GObj* fighter_gobj);
void func_800C1E64(HSD_GObj* pPlayerEntityStruct, s32, s32, u8, f32);
void func_800C2FD8(HSD_GObj* fighter_gobj);
void func_800C37A0(HSD_GObj* fighter_gobj);
void func_800C511C(HSD_GObj* fighter_gobj);
BOOL func_800C5240(HSD_GObj* fighter_gobj);
void func_800C61B0(HSD_GObj* fighter_gobj);
void func_800C8064(void);
void func_800C8348(HSD_GObj* fighter_gobj, BOOL, s32);
void func_800C8438(HSD_GObj* fighter_gobj);
void func_800C8540(HSD_GObj* fighter_gobj);
void func_800C884C(HSD_GObj* fighter_gobj);
void func_800C88A0(Fighter* fp);
void func_80088510(Fighter* fp, s32, u8, u8);
u32 func_800DEEE8(Fighter* fp, Vec2*);
void func_800DEF38(HSD_GObj* fighter_gobj);
void func_800DF0D0(HSD_GObj* fighter_gobj);
void func_800DEEA8(HSD_GObj* fighter_gobj);
void func_80088148(Fighter* fp, u32, u32, u32);
void func_800C89A0(HSD_GObj* fighter_gobj);
void func_800C8A64(HSD_GObj* fighter_gobj);
s32 func_800C8B2C(Fighter* fp, u32, BOOL);
s32 func_800C8C84(HSD_GObj* fighter_gobj);
void func_800C8D00(HSD_GObj* fighter_gobj);
void func_800C8F6C(void);
void func_800C8FC4(HSD_GObj* fighter_gobj);
void func_800C9034(HSD_GObj* fighter_gobj);
void func_800C9840(HSD_GObj* fighter_gobj, s32 action_state, BOOL, f32, f32 turn_speed, f32);

/* TODO
 * Inconsistent signature at call sites. Should be:
 * BOOL func_800CAE80(HSD_GObj* fighter_gobj);
 */
BOOL func_800CAE80();

void func_800CB110(HSD_GObj* fighter_gobj, BOOL, f32);
void func_800CC730(HSD_GObj* fighter_gobj);
void func_800D105C(HSD_GObj* dst_fighter_gobj);
void func_800D14E4(HSD_GObj* fighter_gobj);
void func_800D1A8C(HSD_GObj* fighter_gobj);
void func_800D1E80(HSD_GObj* fighter_gobj);
void func_800D237C(HSD_GObj* fighter_gobj);
void func_800D3158(HSD_GObj* fighter_gobj);
void func_800D4F24(HSD_GObj* fighter_gobj, BOOL);
void func_800D5AEC(HSD_GObj* fighter_gobj, s32 action_state, BOOL, BOOL, Fighter* fp, f32, f32);
void func_800D5CB0(HSD_GObj* fighter_gobj, BOOL, f32 landing_lag);
BOOL func_800D67C4(Fighter* fp);
BOOL func_800D688C(Fighter* fp);
BOOL func_800D6928(Fighter* fp);
void func_800D71D8(HSD_GObj* fighter_gobj);
void func_800D94D8(HSD_GObj* fighter_gobj);
void func_800DA824(Fighter* victim_fp);
void func_800DB368(Fighter* victim_fp, Fighter* self_fp);
void func_800DB464(HSD_GObj* fighter_gobj);
void func_800DC750(HSD_GObj* interacted_fighter_gobj);

#endif
