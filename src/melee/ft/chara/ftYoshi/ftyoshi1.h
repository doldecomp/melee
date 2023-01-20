#ifndef MELEE_FT_CHARA_FTYOSHI_FTYOSHI1_H
#define MELEE_FT_CHARA_FTYOSHI_FTYOSHI1_H

#include <melee/ft/ftcommon.h>
#include <melee/ft/types.h>
#include <melee/lb/lbvector.h>
#include <sysdolphin/baselib/dobj.h>
#include <sysdolphin/baselib/mobj.h>

typedef struct _ftYoshiAttributes {
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
    u8 data_filler1[0xEF];
    f32 x120;
    u8 data_filler2[0x14];
} ftYoshiAttributes;

struct S_UNK_YOSHI2 {
    s32 x0;
    s32 x4;
    s32 x8_end_index;
    u8* xC_start_index;
};

struct S_UNK_YOSHI1 {
    s32 x0;
    struct S_UNK_YOSHI2* unk_struct;
};

extern ActionState as_table_yoshi[];

void func_8012B8A4(HSD_GObj* fighter_gobj);
void func_8012B6E8(Fighter* fp, struct S_UNK_YOSHI1* unk_struct_arg);
void func_8012B804(Fighter* fp, struct S_UNK_YOSHI1* unk_struct_arg,
                   f32 start_frame);

unk_t func_8012BECC(void);
void func_8012C850(HSD_GObj* fighter_gobj);

void func_8012B918(HSD_GObj* fighter_gobj);
void ftYoshi_OnDeath(HSD_GObj* fighter_gobj);
void ftYoshi_OnLoad(HSD_GObj* fighter_gobj);
void ftYoshi_8012BA8C(HSD_GObj* fighter_gobj);
f32 ftYoshi_8012BAC0(Fighter* fp);
void ftYoshi_OnItemPickup(HSD_GObj* fighter_gobj, bool bool);
void ftYoshi_OnItemInvisible(HSD_GObj* fighter_gobj);
void ftYoshi_OnItemVisible(HSD_GObj* fighter_gobj);
void ftYoshi_OnItemDrop(HSD_GObj* fighter_gobj, bool bool1);
void ftYoshi_LoadSpecialAttrs(HSD_GObj* fighter_gobj);
void ftYoshi_OnKnockbackEnter(HSD_GObj* fighter_gobj);
void ftYoshi_OnKnockbackExit(HSD_GObj* fighter_gobj);
unk_t func_8012BDA0(void);
void func_8012BE3C(HSD_GObj* fighter_gobj);

void lbl_8012C030(HSD_GObj*);
void lbl_8012C114(HSD_GObj*);
void lbl_8012C194(HSD_GObj*);
void lbl_8012C1B4(HSD_GObj*);
void lbl_8012C2F4(HSD_GObj*);
void lbl_8012C3EC(HSD_GObj*);
void lbl_8012C45C(HSD_GObj*);
void lbl_8012C47C(HSD_GObj*);
void lbl_8012C54C(HSD_GObj*);
void lbl_8012C59C(HSD_GObj*);
void lbl_8012C5C0(HSD_GObj*);
void lbl_8012C5E0(HSD_GObj*);
void lbl_8012C7A4(HSD_GObj*);
void lbl_8012C80C(HSD_GObj*);
void lbl_8012C810(HSD_GObj*);
void lbl_8012C830(HSD_GObj*);
void lbl_8012CAD0(HSD_GObj*);
void lbl_8012CBBC(HSD_GObj*);
void lbl_8012CBDC(HSD_GObj*);
void lbl_8012CBFC(HSD_GObj*);
void lbl_8012D550(HSD_GObj*);
void lbl_8012DC30(HSD_GObj*);
void lbl_8012DD70(HSD_GObj*);
void lbl_8012D658(HSD_GObj*);
void lbl_8012DC90(HSD_GObj*);
void lbl_8012DDE8(HSD_GObj*);
void lbl_8012D5C8(HSD_GObj*);
void lbl_8012DC70(HSD_GObj*);
void lbl_8012DDC0(HSD_GObj*);
void lbl_8012D948(HSD_GObj*);
void lbl_8012DD10(HSD_GObj*);
void lbl_8012DE88(HSD_GObj*);
void lbl_8012D7D8(HSD_GObj*);
void lbl_8012DCF0(HSD_GObj*);
void lbl_8012DE60(HSD_GObj*);
void lbl_8012D58C(HSD_GObj*);
void lbl_8012DC50(HSD_GObj*);
void lbl_8012DD98(HSD_GObj*);
void lbl_8012D760(HSD_GObj*);
void lbl_8012DCD0(HSD_GObj*);
void lbl_8012DE38(HSD_GObj*);
void lbl_8012D6D0(HSD_GObj*);
void lbl_8012DCB0(HSD_GObj*);
void lbl_8012DE10(HSD_GObj*);
void lbl_8012DB74(HSD_GObj*);
void lbl_8012DD50(HSD_GObj*);
void lbl_8012DED8(HSD_GObj*);
void lbl_8012DA04(HSD_GObj*);
void lbl_8012DD30(HSD_GObj*);
void lbl_8012DEB0(HSD_GObj*);
void lbl_8012F654(HSD_GObj*);
void lbl_80130DB8(HSD_GObj*);
void lbl_801310C4(HSD_GObj*);
void lbl_801317DC(HSD_GObj*);
void lbl_8012F750(HSD_GObj*);
void lbl_80130DBC(HSD_GObj*);
void lbl_801310E8(HSD_GObj*);
void lbl_8013187C(HSD_GObj*);
void lbl_8012FAC4(HSD_GObj*);
void lbl_80130F7C(HSD_GObj*);
void lbl_801312EC(HSD_GObj*);
void lbl_80131B60(HSD_GObj*);
void lbl_8012FFF4(HSD_GObj*);
void lbl_80130FD8(HSD_GObj*);
void lbl_80131618(HSD_GObj*);
void lbl_80131E74(HSD_GObj*);
void lbl_80130368(HSD_GObj*);
void lbl_80130FDC(HSD_GObj*);
void lbl_80131654(HSD_GObj*);
void lbl_80131ED4(HSD_GObj*);
void lbl_80130428(HSD_GObj*);
void lbl_80130FEC(HSD_GObj*);
void lbl_8013168C(HSD_GObj*);
void lbl_80131F80(HSD_GObj*);
void lbl_801306A8(HSD_GObj*);
void lbl_80131050(HSD_GObj*);
void lbl_80131718(HSD_GObj*);
void lbl_8013245C(HSD_GObj*);
void lbl_80130A24(HSD_GObj*);
void lbl_801310B4(HSD_GObj*);
void lbl_801317A4(HSD_GObj*);
void lbl_801328F0(HSD_GObj*);
void lbl_8012E4DC(HSD_GObj*);
void lbl_8012E594(HSD_GObj*);
void lbl_8012E5D4(HSD_GObj*);
void lbl_8012E538(HSD_GObj*);
void lbl_8012E5B4(HSD_GObj*);
void lbl_8012E5FC(HSD_GObj*);
void lbl_8012E814(HSD_GObj*);
void lbl_8012E88C(HSD_GObj*);
void lbl_8012E924(HSD_GObj*);
void lbl_8012EA40(HSD_GObj*);
void lbl_8012EA7C(HSD_GObj*);
void lbl_8012EA9C(HSD_GObj*);
void lbl_8012E850(HSD_GObj*);
void lbl_8012E8CC(HSD_GObj*);
void func_8012E944(HSD_GObj*);
void func_8012C1D4(HSD_GObj*);
void lbl_8012C2F4(HSD_GObj* fighter_gobj);
void lbl_8012C3EC(HSD_GObj*);
void lbl_8012C45C(HSD_GObj*);
void lbl_8012C47C(HSD_GObj*);

#endif
