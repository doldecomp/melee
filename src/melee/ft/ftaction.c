#include <platform.h>
#include "lb/forward.h"

#include "ftaction.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0C88.h"
#include "ft/ft_0D14.h"
#include "ft/ftcolanim.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "ftCommon/ftCo_09CB.h"
#include "ftCommon/ftCo_09F7.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbcommand.h"

#include <placeholder.h>
#include <baselib/gobj.h>

static FtCmd ftAction_803C06E8[] = {
    ftAction_80071028, ftAction_8007121C, ftAction_8007162C, ftAction_8007169C,
    ftAction_80071708, ftAction_80071784, ftAction_800717D8, ftAction_80071B50,
    ftAction_80071CCC, ftAction_80071820, ftAction_800718A4, ftAction_80071908,
    ftAction_8007192C, ftAction_80071950, ftAction_80071974, ftAction_80071998,
    ftAction_80071A14, ftAction_80071A58, ftAction_80071A9C, ftAction_80071AE8,
    ftAction_80071B28, ftAction_80071D40, ftAction_80071D94, ftAction_80071DCC,
    ftAction_80071E04, ftAction_80071F34, ftAction_80071F78, ftAction_80071FA0,
    ftAction_80071FC8, ftAction_80072320, ftAction_800726F4, ftAction_800727C8,
    ftAction_80072894, ftAction_800728F8, ftAction_8007297C, ftAction_800729D4,
    ftAction_80072A5C, ftAction_80072ABC, ftAction_80072B14, ftAction_80072B3C,
    ftAction_80072B94, ftAction_80072BF4, ftAction_80072C6C, ftAction_80072CB0,
    ftAction_80072CD8, ftAction_80072E4C, ftAction_80073008, ftAction_800730B8,
    ftAction_80073118,
};

/* static */ FtCmd ftAction_803C07AC[] = {
    ftAction_800711DC, ftAction_800715EC, ftAction_8007168C, ftAction_800716F8,
    ftAction_80071774, ftAction_800717C8, ftAction_80071810, ftAction_80071CA4,
    ftAction_80071D30, ftAction_80071820, ftAction_800718A4, ftAction_80071908,
    ftAction_8007192C, ftAction_80071950, ftAction_80071974, ftAction_80071998,
    ftAction_80071A14, ftAction_80071A58, ftAction_80071A9C, ftAction_80071AE8,
    ftAction_80071B28, ftAction_80071D40, ftAction_80071D94, ftAction_80071DCC,
    ftAction_80071F0C, ftAction_80071F34, ftAction_80071F78, ftAction_80071FA0,
    ftAction_800722C8, ftAction_800726C0, ftAction_800726F4, ftAction_8007283C,
    ftAction_80072894, ftAction_8007296C, ftAction_800729C4, ftAction_80072A4C,
    ftAction_80072AAC, ftAction_80072B04, ftAction_80072B14, ftAction_80072B84,
    ftAction_80072BE4, ftAction_80072C5C, ftAction_80072C6C, ftAction_80072CB0,
    ftAction_80072E24, ftAction_80072FE0, ftAction_8007309C, ftAction_80073108,
    ftAction_8007320C,
};

/* static */ u8 ftAction_803C0870[] = {
    05, 05, 01, 01, 01, 01, 01, 03, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01,
    01, 01, 01, 01, 01, 01, 03, 01, 01, 01, 07, 04, 01, 01, 01, 01, 01, 01,
    01, 01, 01, 01, 01, 01, 01, 01, 03, 03, 02, 01, 04, 00, 00, 00,
};

#ifdef MWERKS_GEKKO
float const ftAction_804D82A0 = 0.0039059999398887157440185546875;
double const ftAction_804D82A8 = 4503599627370496;
double const ftAction_804D82B0 = 4503601774854144;
float const ftAction_804D82B8 = 0;
float const ftAction_804D82BC = 1;
float const ftAction_804D82C0 = -1;
float const ftAction_804D82C4 = F32_MAX;
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftAction_80071028(Fighter_GObj* gobj, FtCmdState* cmd)
{
    // clang-format off
    nofralloc
/* 80071028 0006DC08  7C 08 02 A6 */	mflr r0
/* 8007102C 0006DC0C  7C 8A 23 78 */	mr r10, r4
/* 80071030 0006DC10  90 01 00 04 */	stw r0, 4(r1)
/* 80071034 0006DC14  94 21 FF 98 */	stwu r1, -0x68(r1)
/* 80071038 0006DC18  80 A3 00 2C */	lwz r5, 0x2c(r3)
/* 8007103C 0006DC1C  88 05 22 1E */	lbz r0, 0x221e(r5)
/* 80071040 0006DC20  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 80071044 0006DC24  40 82 01 80 */	bne lbl_800711C4
/* 80071048 0006DC28  80 CA 00 08 */	lwz r6, 8(r10)
/* 8007104C 0006DC2C  88 06 00 02 */	lbz r0, 2(r6)
/* 80071050 0006DC30  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 80071054 0006DC34  41 82 00 14 */	beq lbl_80071068
/* 80071058 0006DC38  80 85 01 0C */	lwz r4, 0x10c(r5)
/* 8007105C 0006DC3C  80 84 00 08 */	lwz r4, 8(r4)
/* 80071060 0006DC40  88 A4 00 12 */	lbz r5, 0x12(r4)
/* 80071064 0006DC44  48 00 00 0C */	b lbl_80071070
lbl_80071068:
/* 80071068 0006DC48  A0 A6 00 00 */	lhz r5, 0(r6)
/* 8007106C 0006DC4C  54 A5 F6 3E */	rlwinm r5, r5, 0x1e, 0x18, 0x1f
lbl_80071070:
/* 80071070 0006DC50  38 E6 00 01 */	addi r7, r6, 1
/* 80071074 0006DC54  80 8A 00 08 */	lwz r4, 8(r10)
/* 80071078 0006DC58  88 C6 00 01 */	lbz r6, 1(r6)
/* 8007107C 0006DC5C  3C 00 43 30 */	lis r0, 0x4330
/* 80071080 0006DC60  88 E7 00 00 */	lbz r7, 0(r7)
/* 80071084 0006DC64  38 84 00 04 */	addi r4, r4, 4
/* 80071088 0006DC68  54 C6 FF FE */	rlwinm r6, r6, 0x1f, 0x1f, 0x1f
/* 8007108C 0006DC6C  90 8A 00 08 */	stw r4, 8(r10)
/* 80071090 0006DC70  54 E7 07 FE */	clrlwi r7, r7, 0x1f
/* 80071094 0006DC74  39 21 00 14 */	addi r9, r1, 0x14
/* 80071098 0006DC78  81 0A 00 08 */	lwz r8, 8(r10)
/* 8007109C 0006DC7C  C8 82 88 C8 */	lfd f4, ftAction_804D82A8
/* 800710A0 0006DC80  A1 88 00 02 */	lhz r12, 2(r8)
/* 800710A4 0006DC84  A0 88 00 00 */	lhz r4, 0(r8)
/* 800710A8 0006DC88  39 08 00 04 */	addi r8, r8, 4
/* 800710AC 0006DC8C  91 81 00 64 */	stw r12, 0x64(r1)
/* 800710B0 0006DC90  91 0A 00 08 */	stw r8, 8(r10)
/* 800710B4 0006DC94  39 01 00 20 */	addi r8, r1, 0x20
/* 800710B8 0006DC98  81 6A 00 08 */	lwz r11, 8(r10)
/* 800710BC 0006DC9C  90 01 00 60 */	stw r0, 0x60(r1)
/* 800710C0 0006DCA0  A9 6B 00 00 */	lha r11, 0(r11)
/* 800710C4 0006DCA4  C8 01 00 60 */	lfd f0, 0x60(r1)
/* 800710C8 0006DCA8  6D 6B 80 00 */	xoris r11, r11, 0x8000
/* 800710CC 0006DCAC  C8 42 88 D0 */	lfd f2, ftAction_804D82B0
/* 800710D0 0006DCB0  91 61 00 5C */	stw r11, 0x5c(r1)
/* 800710D4 0006DCB4  EC 20 20 28 */	fsubs f1, f0, f4
/* 800710D8 0006DCB8  C0 62 88 C0 */	lfs f3, ftAction_804D82A0
/* 800710DC 0006DCBC  90 01 00 58 */	stw r0, 0x58(r1)
/* 800710E0 0006DCC0  C8 01 00 58 */	lfd f0, 0x58(r1)
/* 800710E4 0006DCC4  EC 00 10 28 */	fsubs f0, f0, f2
/* 800710E8 0006DCC8  EC 03 00 32 */	fmuls f0, f3, f0
/* 800710EC 0006DCCC  D0 01 00 20 */	stfs f0, 0x20(r1)
/* 800710F0 0006DCD0  81 6A 00 08 */	lwz r11, 8(r10)
/* 800710F4 0006DCD4  A9 6B 00 02 */	lha r11, 2(r11)
/* 800710F8 0006DCD8  6D 6B 80 00 */	xoris r11, r11, 0x8000
/* 800710FC 0006DCDC  91 61 00 54 */	stw r11, 0x54(r1)
/* 80071100 0006DCE0  90 01 00 50 */	stw r0, 0x50(r1)
/* 80071104 0006DCE4  C8 01 00 50 */	lfd f0, 0x50(r1)
/* 80071108 0006DCE8  EC 00 10 28 */	fsubs f0, f0, f2
/* 8007110C 0006DCEC  EC 03 00 32 */	fmuls f0, f3, f0
/* 80071110 0006DCF0  D0 01 00 24 */	stfs f0, 0x24(r1)
/* 80071114 0006DCF4  81 6A 00 08 */	lwz r11, 8(r10)
/* 80071118 0006DCF8  39 6B 00 04 */	addi r11, r11, 4
/* 8007111C 0006DCFC  91 6A 00 08 */	stw r11, 8(r10)
/* 80071120 0006DD00  81 6A 00 08 */	lwz r11, 8(r10)
/* 80071124 0006DD04  A9 6B 00 00 */	lha r11, 0(r11)
/* 80071128 0006DD08  6D 6B 80 00 */	xoris r11, r11, 0x8000
/* 8007112C 0006DD0C  91 61 00 4C */	stw r11, 0x4c(r1)
/* 80071130 0006DD10  90 01 00 48 */	stw r0, 0x48(r1)
/* 80071134 0006DD14  C8 01 00 48 */	lfd f0, 0x48(r1)
/* 80071138 0006DD18  EC 00 10 28 */	fsubs f0, f0, f2
/* 8007113C 0006DD1C  EC 03 00 32 */	fmuls f0, f3, f0
/* 80071140 0006DD20  D0 01 00 28 */	stfs f0, 0x28(r1)
/* 80071144 0006DD24  81 6A 00 08 */	lwz r11, 8(r10)
/* 80071148 0006DD28  A1 6B 00 02 */	lhz r11, 2(r11)
/* 8007114C 0006DD2C  91 61 00 44 */	stw r11, 0x44(r1)
/* 80071150 0006DD30  90 01 00 40 */	stw r0, 0x40(r1)
/* 80071154 0006DD34  C8 01 00 40 */	lfd f0, 0x40(r1)
/* 80071158 0006DD38  EC 00 20 28 */	fsubs f0, f0, f4
/* 8007115C 0006DD3C  EC 03 00 32 */	fmuls f0, f3, f0
/* 80071160 0006DD40  D0 01 00 14 */	stfs f0, 0x14(r1)
/* 80071164 0006DD44  81 6A 00 08 */	lwz r11, 8(r10)
/* 80071168 0006DD48  39 6B 00 04 */	addi r11, r11, 4
/* 8007116C 0006DD4C  91 6A 00 08 */	stw r11, 8(r10)
/* 80071170 0006DD50  81 6A 00 08 */	lwz r11, 8(r10)
/* 80071174 0006DD54  A1 6B 00 00 */	lhz r11, 0(r11)
/* 80071178 0006DD58  91 61 00 3C */	stw r11, 0x3c(r1)
/* 8007117C 0006DD5C  90 01 00 38 */	stw r0, 0x38(r1)
/* 80071180 0006DD60  C8 01 00 38 */	lfd f0, 0x38(r1)
/* 80071184 0006DD64  EC 00 20 28 */	fsubs f0, f0, f4
/* 80071188 0006DD68  EC 03 00 32 */	fmuls f0, f3, f0
/* 8007118C 0006DD6C  D0 01 00 18 */	stfs f0, 0x18(r1)
/* 80071190 0006DD70  81 6A 00 08 */	lwz r11, 8(r10)
/* 80071194 0006DD74  A1 6B 00 02 */	lhz r11, 2(r11)
/* 80071198 0006DD78  91 61 00 34 */	stw r11, 0x34(r1)
/* 8007119C 0006DD7C  90 01 00 30 */	stw r0, 0x30(r1)
/* 800711A0 0006DD80  C8 01 00 30 */	lfd f0, 0x30(r1)
/* 800711A4 0006DD84  EC 00 20 28 */	fsubs f0, f0, f4
/* 800711A8 0006DD88  EC 03 00 32 */	fmuls f0, f3, f0
/* 800711AC 0006DD8C  D0 01 00 1C */	stfs f0, 0x1c(r1)
/* 800711B0 0006DD90  81 6A 00 08 */	lwz r11, 8(r10)
/* 800711B4 0006DD94  38 0B 00 04 */	addi r0, r11, 4
/* 800711B8 0006DD98  90 0A 00 08 */	stw r0, 8(r10)
/* 800711BC 0006DD9C  48 02 E6 79 */	bl ftCo_8009F834
/* 800711C0 0006DDA0  48 00 00 0C */	b lbl_800711CC
lbl_800711C4:
/* 800711C4 0006DDA4  7D 44 53 78 */	mr r4, r10
/* 800711C8 0006DDA8  48 00 00 15 */	bl ftAction_800711DC
lbl_800711CC:
/* 800711CC 0006DDAC  80 01 00 6C */	lwz r0, 0x6c(r1)
/* 800711D0 0006DDB0  38 21 00 68 */	addi r1, r1, 0x68
/* 800711D4 0006DDB4  7C 08 03 A6 */	mtlr r0
/* 800711D8 0006DDB8  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

/*
SubactionEvent 10 GFXSpawn

https://github.com/Ploaj/HSDLib/blob/939cc10be5a9f76fdcf3ca8ff4a54e35e545fe4a/HSDRawViewer/Scripts/command_fighter.yml#L35

Bone ID
Use Common Bone IDs
Destroy on State Change
Unk1
GFX ID
Unk2
Offset Z
Offset Y
Offset X
Range Z
Range Y
Range X



ftCo_8009F834 args:

gobj
gfx_id
bone
use_common_bone_id
destroy_on_state_change
offset
range
*/

struct test1 {
    u32 opcode : 6;
    u32 boneId : 8;
    u32 useCommonBoneIDs : 1;
    u32 destroyOnStateChange : 1;
    u32 useUnkBone : 1;
    u32 unk1 : 15;
};
struct test2 {
    u32 gfxID : 16;
    u32 unkFloat : 16;
};
struct test3 {
    s16 offsetZ : 16;
    s16 offsetY : 16;
};
struct test4 {
    s16 offsetX : 16;
    u16 rangeZ : 16;
};
struct test5 {
    u16 rangeY : 16;
    u16 rangeX : 16;
};

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunsequenced"
#endif
void ftAction_80071028(Fighter_GObj* gobj, FtCmdState* cmd)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4] = { 0 };
#endif
    Fighter* fp = gobj->user_data;
    int gfx_id;
    int bone;
    int use_common_bone_id;
    int destroy_on_state_change;
    Vec3 offset;
    Vec3 range;
    float unk;
    // permuter jank?
    FtCmdState* new_var;
    // if !invisible
    if (!fp->x221E_b0) {
        if (gmScriptEventCast(cmd->x8, struct test1)->useUnkBone) {
            bone = fp->ft_data->x8->unk12;
        } else {
            bone = gmScriptEventCast(cmd->x8, struct test1)->boneId;
        }
        use_common_bone_id =
            gmScriptEventCast(cmd->x8, struct test1)->useCommonBoneIDs;
        destroy_on_state_change =
            gmScriptEventCast(cmd->x8, struct test1)->destroyOnStateChange;
        gmScriptEventUpdatePtr((new_var = cmd)->x8, struct test1);
        gfx_id = gmScriptEventCast(new_var->x8, struct test2)->gfxID;
        unk = gmScriptEventCast(new_var->x8, struct test2)->unkFloat;
        gmScriptEventUpdatePtr(new_var->x8, struct test2);
        offset.z = (1 / 256.0f) *
                   gmScriptEventCast(new_var->x8, struct test3)->offsetZ;
        offset.y = (1 / 256.0f) *
                   gmScriptEventCast(new_var->x8, struct test3)->offsetY;
        gmScriptEventUpdatePtr(new_var->x8, struct test3);
        offset.x = (1 / 256.0f) *
                   gmScriptEventCast(new_var->x8, struct test4)->offsetX;
        range.z = (1 / 256.0f) *
                  gmScriptEventCast(new_var->x8, struct test4)->rangeZ;
        gmScriptEventUpdatePtr(new_var->x8, struct test4);
        range.y = (1 / 256.0f) *
                  gmScriptEventCast(new_var->x8, struct test5)->rangeY;
        range.x = (1 / 256.0f) *
                  gmScriptEventCast(new_var->x8, struct test5)->rangeX;
        gmScriptEventUpdatePtr(new_var->x8, struct test5);
        ftCo_8009F834(gobj, gfx_id, bone, use_common_bone_id,
                      destroy_on_state_change, &offset, &range, unk);
    } else {
        // skip the gfxspawn event
        ftAction_800711DC(gobj, cmd);
    }
}
#ifdef __clang__
#pragma clang diagnostic pop
#endif
#endif

/// Skip GFX Spawn
void ftAction_800711DC(Fighter_GObj* gobj, FtCmdState* cmd)
{
    cmd->x8 += 4;
    cmd->x8 += 4;
    cmd->x8 += 4;
    cmd->x8 += 4;
    cmd->x8 += 4;
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftAction_8007121C(Fighter_GObj* gobj, FtCmdState* cmd)
{
    // clang-format off
    nofralloc
/* 8007121C 0006DDFC  7C 08 02 A6 */	mflr r0
/* 80071220 0006DE00  90 01 00 04 */	stw r0, 4(r1)
/* 80071224 0006DE04  94 21 FF B0 */	stwu r1, -0x50(r1)
/* 80071228 0006DE08  93 E1 00 4C */	stw r31, 0x4c(r1)
/* 8007122C 0006DE0C  93 C1 00 48 */	stw r30, 0x48(r1)
/* 80071230 0006DE10  93 A1 00 44 */	stw r29, 0x44(r1)
/* 80071234 0006DE14  7C 9D 23 78 */	mr r29, r4
/* 80071238 0006DE18  93 81 00 40 */	stw r28, 0x40(r1)
/* 8007123C 0006DE1C  7C 7C 1B 78 */	mr r28, r3
/* 80071240 0006DE20  80 84 00 08 */	lwz r4, 8(r4)
/* 80071244 0006DE24  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80071248 0006DE28  88 04 00 0F */	lbz r0, 0xf(r4)
/* 8007124C 0006DE2C  54 00 EF FF */	rlwinm. r0, r0, 0x1d, 0x1f, 0x1f
/* 80071250 0006DE30  41 82 00 20 */	beq lbl_80071270
/* 80071254 0006DE34  80 1F 11 98 */	lwz r0, 0x1198(r31)
/* 80071258 0006DE38  28 00 00 00 */	cmplwi r0, 0
/* 8007125C 0006DE3C  40 82 00 14 */	bne lbl_80071270
/* 80071260 0006DE40  38 7C 00 00 */	addi r3, r28, 0
/* 80071264 0006DE44  38 9D 00 00 */	addi r4, r29, 0
/* 80071268 0006DE48  48 00 03 85 */	bl ftAction_800715EC
/* 8007126C 0006DE4C  48 00 03 58 */	b lbl_800715C4
lbl_80071270:
/* 80071270 0006DE50  A0 04 00 00 */	lhz r0, 0(r4)
/* 80071274 0006DE54  88 84 00 01 */	lbz r4, 1(r4)
/* 80071278 0006DE58  54 00 CF 7E */	rlwinm r0, r0, 0x19, 0x1d, 0x1f
/* 8007127C 0006DE5C  1C 60 01 38 */	mulli r3, r0, 0x138
/* 80071280 0006DE60  3B C3 09 14 */	addi r30, r3, 0x914
/* 80071284 0006DE64  7F DF F2 14 */	add r30, r31, r30
/* 80071288 0006DE68  80 1E 00 00 */	lwz r0, 0(r30)
/* 8007128C 0006DE6C  54 84 E7 7E */	rlwinm r4, r4, 0x1c, 0x1d, 0x1f
/* 80071290 0006DE70  2C 00 00 00 */	cmpwi r0, 0
/* 80071294 0006DE74  41 82 00 10 */	beq lbl_800712A4
/* 80071298 0006DE78  80 1E 00 04 */	lwz r0, 4(r30)
/* 8007129C 0006DE7C  7C 00 20 40 */	cmplw r0, r4
/* 800712A0 0006DE80  41 82 00 28 */	beq lbl_800712C8
lbl_800712A4:
/* 800712A4 0006DE84  90 9E 00 04 */	stw r4, 4(r30)
/* 800712A8 0006DE88  38 A0 00 01 */	li r5, 1
/* 800712AC 0006DE8C  38 7F 00 00 */	addi r3, r31, 0
/* 800712B0 0006DE90  90 BE 00 00 */	stw r5, 0(r30)
/* 800712B4 0006DE94  7F C4 F3 78 */	mr r4, r30
/* 800712B8 0006DE98  88 1F 22 19 */	lbz r0, 0x2219(r31)
/* 800712BC 0006DE9C  50 A0 26 F6 */	rlwimi r0, r5, 4, 0x1b, 0x1b
/* 800712C0 0006DEA0  98 1F 22 19 */	stb r0, 0x2219(r31)
/* 800712C4 0006DEA4  48 00 55 DD */	bl ftColl_800768A0
lbl_800712C8:
/* 800712C8 0006DEA8  80 7D 00 08 */	lwz r3, 8(r29)
/* 800712CC 0006DEAC  88 03 00 02 */	lbz r0, 2(r3)
/* 800712D0 0006DEB0  80 83 00 00 */	lwz r4, 0(r3)
/* 800712D4 0006DEB4  54 00 F7 FF */	rlwinm. r0, r0, 0x1e, 0x1f, 0x1f
/* 800712D8 0006DEB8  54 84 AE 3E */	rlwinm r4, r4, 0x15, 0x18, 0x1f
/* 800712DC 0006DEBC  41 82 00 20 */	beq lbl_800712FC
/* 800712E0 0006DEC0  7F E3 FB 78 */	mr r3, r31
/* 800712E4 0006DEC4  48 00 3D 29 */	bl ftParts_8007500C
/* 800712E8 0006DEC8  80 9F 05 E8 */	lwz r4, 0x5e8(r31)
/* 800712EC 0006DECC  54 60 20 36 */	slwi r0, r3, 4
/* 800712F0 0006DED0  7C 04 00 2E */	lwzx r0, r4, r0
/* 800712F4 0006DED4  90 1E 00 48 */	stw r0, 0x48(r30)
/* 800712F8 0006DED8  48 00 00 14 */	b lbl_8007130C
lbl_800712FC:
/* 800712FC 0006DEDC  80 7F 05 E8 */	lwz r3, 0x5e8(r31)
/* 80071300 0006DEE0  54 80 20 36 */	slwi r0, r4, 4
/* 80071304 0006DEE4  7C 03 00 2E */	lwzx r0, r3, r0
/* 80071308 0006DEE8  90 1E 00 48 */	stw r0, 0x48(r30)
lbl_8007130C:
/* 8007130C 0006DEEC  80 9D 00 08 */	lwz r4, 8(r29)
/* 80071310 0006DEF0  38 7E 00 00 */	addi r3, r30, 0
/* 80071314 0006DEF4  38 BC 00 00 */	addi r5, r28, 0
/* 80071318 0006DEF8  A0 84 00 02 */	lhz r4, 2(r4)
/* 8007131C 0006DEFC  54 84 05 BE */	clrlwi r4, r4, 0x16
/* 80071320 0006DF00  48 00 98 B1 */	bl ftColl_8007ABD0
/* 80071324 0006DF04  80 9D 00 08 */	lwz r4, 8(r29)
/* 80071328 0006DF08  3C C0 43 30 */	lis r6, 0x4330
/* 8007132C 0006DF0C  38 7E 00 00 */	addi r3, r30, 0
/* 80071330 0006DF10  38 04 00 04 */	addi r0, r4, 4
/* 80071334 0006DF14  90 1D 00 08 */	stw r0, 8(r29)
/* 80071338 0006DF18  7F 85 E3 78 */	mr r5, r28
/* 8007133C 0006DF1C  80 9D 00 08 */	lwz r4, 8(r29)
/* 80071340 0006DF20  C8 22 88 C8 */	lfd f1, ftAction_804D82A8
/* 80071344 0006DF24  A0 04 00 00 */	lhz r0, 0(r4)
/* 80071348 0006DF28  C0 42 88 C0 */	lfs f2, ftAction_804D82A0
/* 8007134C 0006DF2C  90 01 00 3C */	stw r0, 0x3c(r1)
/* 80071350 0006DF30  90 C1 00 38 */	stw r6, 0x38(r1)
/* 80071354 0006DF34  C8 01 00 38 */	lfd f0, 0x38(r1)
/* 80071358 0006DF38  EC 00 08 28 */	fsubs f0, f0, f1
/* 8007135C 0006DF3C  EC 02 00 32 */	fmuls f0, f2, f0
/* 80071360 0006DF40  D0 1E 00 1C */	stfs f0, 0x1c(r30)
/* 80071364 0006DF44  80 9D 00 08 */	lwz r4, 8(r29)
/* 80071368 0006DF48  C8 22 88 D0 */	lfd f1, ftAction_804D82B0
/* 8007136C 0006DF4C  A8 04 00 02 */	lha r0, 2(r4)
/* 80071370 0006DF50  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 80071374 0006DF54  90 01 00 34 */	stw r0, 0x34(r1)
/* 80071378 0006DF58  90 C1 00 30 */	stw r6, 0x30(r1)
/* 8007137C 0006DF5C  C8 01 00 30 */	lfd f0, 0x30(r1)
/* 80071380 0006DF60  EC 00 08 28 */	fsubs f0, f0, f1
/* 80071384 0006DF64  EC 02 00 32 */	fmuls f0, f2, f0
/* 80071388 0006DF68  D0 1E 00 10 */	stfs f0, 0x10(r30)
/* 8007138C 0006DF6C  80 9D 00 08 */	lwz r4, 8(r29)
/* 80071390 0006DF70  38 04 00 04 */	addi r0, r4, 4
/* 80071394 0006DF74  90 1D 00 08 */	stw r0, 8(r29)
/* 80071398 0006DF78  80 9D 00 08 */	lwz r4, 8(r29)
/* 8007139C 0006DF7C  A8 04 00 00 */	lha r0, 0(r4)
/* 800713A0 0006DF80  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 800713A4 0006DF84  90 01 00 2C */	stw r0, 0x2c(r1)
/* 800713A8 0006DF88  90 C1 00 28 */	stw r6, 0x28(r1)
/* 800713AC 0006DF8C  C8 01 00 28 */	lfd f0, 0x28(r1)
/* 800713B0 0006DF90  EC 00 08 28 */	fsubs f0, f0, f1
/* 800713B4 0006DF94  EC 02 00 32 */	fmuls f0, f2, f0
/* 800713B8 0006DF98  D0 1E 00 14 */	stfs f0, 0x14(r30)
/* 800713BC 0006DF9C  80 9D 00 08 */	lwz r4, 8(r29)
/* 800713C0 0006DFA0  A8 04 00 02 */	lha r0, 2(r4)
/* 800713C4 0006DFA4  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 800713C8 0006DFA8  90 01 00 24 */	stw r0, 0x24(r1)
/* 800713CC 0006DFAC  90 C1 00 20 */	stw r6, 0x20(r1)
/* 800713D0 0006DFB0  C8 01 00 20 */	lfd f0, 0x20(r1)
/* 800713D4 0006DFB4  EC 00 08 28 */	fsubs f0, f0, f1
/* 800713D8 0006DFB8  EC 02 00 32 */	fmuls f0, f2, f0
/* 800713DC 0006DFBC  D0 1E 00 18 */	stfs f0, 0x18(r30)
/* 800713E0 0006DFC0  80 9D 00 08 */	lwz r4, 8(r29)
/* 800713E4 0006DFC4  38 04 00 04 */	addi r0, r4, 4
/* 800713E8 0006DFC8  90 1D 00 08 */	stw r0, 8(r29)
/* 800713EC 0006DFCC  80 9D 00 08 */	lwz r4, 8(r29)
/* 800713F0 0006DFD0  A0 84 00 00 */	lhz r4, 0(r4)
/* 800713F4 0006DFD4  54 84 CD FE */	rlwinm r4, r4, 0x19, 0x17, 0x1f
/* 800713F8 0006DFD8  48 00 98 A5 */	bl ftColl_8007AC9C
/* 800713FC 0006DFDC  80 7D 00 08 */	lwz r3, 8(r29)
/* 80071400 0006DFE0  38 A0 00 01 */	li r5, 1
/* 80071404 0006DFE4  38 80 00 00 */	li r4, 0
/* 80071408 0006DFE8  80 03 00 00 */	lwz r0, 0(r3)
/* 8007140C 0006DFEC  54 00 95 FE */	rlwinm r0, r0, 0x12, 0x17, 0x1f
/* 80071410 0006DFF0  90 1E 00 24 */	stw r0, 0x24(r30)
/* 80071414 0006DFF4  80 7D 00 08 */	lwz r3, 8(r29)
/* 80071418 0006DFF8  A0 03 00 02 */	lhz r0, 2(r3)
/* 8007141C 0006DFFC  54 00 DD FE */	rlwinm r0, r0, 0x1b, 0x17, 0x1f
/* 80071420 0006E000  90 1E 00 28 */	stw r0, 0x28(r30)
/* 80071424 0006E004  80 7D 00 08 */	lwz r3, 8(r29)
/* 80071428 0006E008  88 1E 00 43 */	lbz r0, 0x43(r30)
/* 8007142C 0006E00C  88 63 00 03 */	lbz r3, 3(r3)
/* 80071430 0006E010  50 60 1E 30 */	rlwimi r0, r3, 3, 0x18, 0x18
/* 80071434 0006E014  98 1E 00 43 */	stb r0, 0x43(r30)
/* 80071438 0006E018  80 7D 00 08 */	lwz r3, 8(r29)
/* 8007143C 0006E01C  88 1E 00 43 */	lbz r0, 0x43(r30)
/* 80071440 0006E020  88 63 00 03 */	lbz r3, 3(r3)
/* 80071444 0006E024  50 60 26 72 */	rlwimi r0, r3, 4, 0x19, 0x19
/* 80071448 0006E028  98 1E 00 43 */	stb r0, 0x43(r30)
/* 8007144C 0006E02C  80 7D 00 08 */	lwz r3, 8(r29)
/* 80071450 0006E030  88 1E 00 40 */	lbz r0, 0x40(r30)
/* 80071454 0006E034  88 63 00 03 */	lbz r3, 3(r3)
/* 80071458 0006E038  50 60 36 30 */	rlwimi r0, r3, 6, 0x18, 0x18
/* 8007145C 0006E03C  98 1E 00 40 */	stb r0, 0x40(r30)
/* 80071460 0006E040  80 7D 00 08 */	lwz r3, 8(r29)
/* 80071464 0006E044  88 1E 00 40 */	lbz r0, 0x40(r30)
/* 80071468 0006E048  88 63 00 03 */	lbz r3, 3(r3)
/* 8007146C 0006E04C  50 60 36 72 */	rlwimi r0, r3, 6, 0x19, 0x19
/* 80071470 0006E050  98 1E 00 40 */	stb r0, 0x40(r30)
/* 80071474 0006E054  80 7D 00 08 */	lwz r3, 8(r29)
/* 80071478 0006E058  38 03 00 04 */	addi r0, r3, 4
/* 8007147C 0006E05C  90 1D 00 08 */	stw r0, 8(r29)
/* 80071480 0006E060  80 7D 00 08 */	lwz r3, 8(r29)
/* 80071484 0006E064  A0 03 00 00 */	lhz r0, 0(r3)
/* 80071488 0006E068  54 00 CD FE */	rlwinm r0, r0, 0x19, 0x17, 0x1f
/* 8007148C 0006E06C  90 1E 00 2C */	stw r0, 0x2c(r30)
/* 80071490 0006E070  80 7D 00 08 */	lwz r3, 8(r29)
/* 80071494 0006E074  88 03 00 01 */	lbz r0, 1(r3)
/* 80071498 0006E078  54 00 F6 FE */	rlwinm r0, r0, 0x1e, 0x1b, 0x1f
/* 8007149C 0006E07C  90 1E 00 30 */	stw r0, 0x30(r30)
/* 800714A0 0006E080  80 7D 00 08 */	lwz r3, 8(r29)
/* 800714A4 0006E084  80 03 00 00 */	lwz r0, 0(r3)
/* 800714A8 0006E088  54 00 70 10 */	rlwinm r0, r0, 0xe, 0, 8
/* 800714AC 0006E08C  7C 00 C6 70 */	srawi r0, r0, 0x18
/* 800714B0 0006E090  90 1E 00 34 */	stw r0, 0x34(r30)
/* 800714B4 0006E094  80 7D 00 08 */	lwz r3, 8(r29)
/* 800714B8 0006E098  A0 03 00 02 */	lhz r0, 2(r3)
/* 800714BC 0006E09C  54 00 CF 7E */	rlwinm r0, r0, 0x19, 0x1d, 0x1f
/* 800714C0 0006E0A0  90 1E 00 38 */	stw r0, 0x38(r30)
/* 800714C4 0006E0A4  80 7D 00 08 */	lwz r3, 8(r29)
/* 800714C8 0006E0A8  88 03 00 03 */	lbz r0, 3(r3)
/* 800714CC 0006E0AC  54 00 F6 FE */	rlwinm r0, r0, 0x1e, 0x1b, 0x1f
/* 800714D0 0006E0B0  90 1E 00 3C */	stw r0, 0x3c(r30)
/* 800714D4 0006E0B4  80 7D 00 08 */	lwz r3, 8(r29)
/* 800714D8 0006E0B8  88 1E 00 40 */	lbz r0, 0x40(r30)
/* 800714DC 0006E0BC  88 63 00 03 */	lbz r3, 3(r3)
/* 800714E0 0006E0C0  50 60 2E B4 */	rlwimi r0, r3, 5, 0x1a, 0x1a
/* 800714E4 0006E0C4  98 1E 00 40 */	stb r0, 0x40(r30)
/* 800714E8 0006E0C8  80 7D 00 08 */	lwz r3, 8(r29)
/* 800714EC 0006E0CC  88 1E 00 40 */	lbz r0, 0x40(r30)
/* 800714F0 0006E0D0  88 63 00 03 */	lbz r3, 3(r3)
/* 800714F4 0006E0D4  50 60 1E F6 */	rlwimi r0, r3, 3, 0x1b, 0x1b
/* 800714F8 0006E0D8  98 1E 00 40 */	stb r0, 0x40(r30)
/* 800714FC 0006E0DC  80 7D 00 08 */	lwz r3, 8(r29)
/* 80071500 0006E0E0  38 03 00 04 */	addi r0, r3, 4
/* 80071504 0006E0E4  90 1D 00 08 */	stw r0, 8(r29)
/* 80071508 0006E0E8  88 1E 00 42 */	lbz r0, 0x42(r30)
/* 8007150C 0006E0EC  50 A0 17 7A */	rlwimi r0, r5, 2, 0x1d, 0x1d
/* 80071510 0006E0F0  98 1E 00 42 */	stb r0, 0x42(r30)
/* 80071514 0006E0F4  88 1E 00 42 */	lbz r0, 0x42(r30)
/* 80071518 0006E0F8  50 A0 07 FE */	rlwimi r0, r5, 0, 0x1f, 0x1f
/* 8007151C 0006E0FC  98 1E 00 42 */	stb r0, 0x42(r30)
/* 80071520 0006E100  88 1E 00 41 */	lbz r0, 0x41(r30)
/* 80071524 0006E104  50 80 1F 38 */	rlwimi r0, r4, 3, 0x1c, 0x1c
/* 80071528 0006E108  98 1E 00 41 */	stb r0, 0x41(r30)
/* 8007152C 0006E10C  88 1E 00 41 */	lbz r0, 0x41(r30)
/* 80071530 0006E110  50 80 0F BC */	rlwimi r0, r4, 1, 0x1e, 0x1e
/* 80071534 0006E114  98 1E 00 41 */	stb r0, 0x41(r30)
/* 80071538 0006E118  88 1E 00 41 */	lbz r0, 0x41(r30)
/* 8007153C 0006E11C  50 80 17 7A */	rlwimi r0, r4, 2, 0x1d, 0x1d
/* 80071540 0006E120  98 1E 00 41 */	stb r0, 0x41(r30)
/* 80071544 0006E124  88 1E 00 42 */	lbz r0, 0x42(r30)
/* 80071548 0006E128  50 80 3E 30 */	rlwimi r0, r4, 7, 0x18, 0x18
/* 8007154C 0006E12C  98 1E 00 42 */	stb r0, 0x42(r30)
/* 80071550 0006E130  88 1E 00 42 */	lbz r0, 0x42(r30)
/* 80071554 0006E134  50 80 1F 38 */	rlwimi r0, r4, 3, 0x1c, 0x1c
/* 80071558 0006E138  98 1E 00 42 */	stb r0, 0x42(r30)
/* 8007155C 0006E13C  88 1E 00 41 */	lbz r0, 0x41(r30)
/* 80071560 0006E140  50 80 07 FE */	rlwimi r0, r4, 0, 0x1f, 0x1f
/* 80071564 0006E144  98 1E 00 41 */	stb r0, 0x41(r30)
/* 80071568 0006E148  80 7D 00 08 */	lwz r3, 8(r29)
/* 8007156C 0006E14C  88 1E 01 34 */	lbz r0, 0x134(r30)
/* 80071570 0006E150  88 63 00 01 */	lbz r3, 1(r3)
/* 80071574 0006E154  50 60 26 30 */	rlwimi r0, r3, 4, 0x18, 0x18
/* 80071578 0006E158  98 1E 01 34 */	stb r0, 0x134(r30)
/* 8007157C 0006E15C  88 1E 00 42 */	lbz r0, 0x42(r30)
/* 80071580 0006E160  50 A0 36 72 */	rlwimi r0, r5, 6, 0x19, 0x19
/* 80071584 0006E164  98 1E 00 42 */	stb r0, 0x42(r30)
/* 80071588 0006E168  88 1E 00 42 */	lbz r0, 0x42(r30)
/* 8007158C 0006E16C  50 80 2E B4 */	rlwimi r0, r4, 5, 0x1a, 0x1a
/* 80071590 0006E170  98 1E 00 42 */	stb r0, 0x42(r30)
/* 80071594 0006E174  88 1E 00 43 */	lbz r0, 0x43(r30)
/* 80071598 0006E178  50 80 2E B4 */	rlwimi r0, r4, 5, 0x1a, 0x1a
/* 8007159C 0006E17C  98 1E 00 43 */	stb r0, 0x43(r30)
/* 800715A0 0006E180  80 6D C1 98 */	lwz r3, HSD_GObj_804D7838
/* 800715A4 0006E184  28 03 00 00 */	cmplwi r3, 0
/* 800715A8 0006E188  41 82 00 1C */	beq lbl_800715C4
/* 800715AC 0006E18C  88 03 00 0C */	lbz r0, 0xc(r3)
/* 800715B0 0006E190  28 00 00 09 */	cmplwi r0, 9
/* 800715B4 0006E194  40 81 00 10 */	ble lbl_800715C4
/* 800715B8 0006E198  38 7F 00 00 */	addi r3, r31, 0
/* 800715BC 0006E19C  38 9E 00 00 */	addi r4, r30, 0
/* 800715C0 0006E1A0  48 00 97 59 */	bl ftColl_8007AD18
lbl_800715C4:
/* 800715C4 0006E1A4  7F E3 FB 78 */	mr r3, r31
/* 800715C8 0006E1A8  48 00 EE BD */	bl ftCommon_80080484
/* 800715CC 0006E1AC  80 01 00 54 */	lwz r0, 0x54(r1)
/* 800715D0 0006E1B0  83 E1 00 4C */	lwz r31, 0x4c(r1)
/* 800715D4 0006E1B4  83 C1 00 48 */	lwz r30, 0x48(r1)
/* 800715D8 0006E1B8  83 A1 00 44 */	lwz r29, 0x44(r1)
/* 800715DC 0006E1BC  83 81 00 40 */	lwz r28, 0x40(r1)
/* 800715E0 0006E1C0  38 21 00 50 */	addi r1, r1, 0x50
/* 800715E4 0006E1C4  7C 08 03 A6 */	mtlr r0
/* 800715E8 0006E1C8  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftAction_8007121C(Fighter_GObj* gobj, FtCmdState* cmd)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    HitCapsule* hit;
    char* temp_r3;
    char part;
    u32 temp_r4_2;
    char* cmd_x8 = cmd->x8;
    ftCo_Fighter* fp = gobj->user_data;
    if ((((u8) M2C_FIELD(cmd_x8, u8*, 0xF) >> 3U) & 1) &&
        ((u32) M2C_FIELD(fp, u32*, 0x1198) == 0U))
    {
        ftAction_800715EC(gobj, cmd);
    } else {
        hit = &fp->x914[(((u16) M2C_FIELD(cmd_x8, u16*, 0) >> 7U) & 7)];
        temp_r4_2 = ((u8) M2C_FIELD(cmd_x8, u8*, 1) >> 4U) & 7;
        if (((int) hit->state == HitCapsule_Disabled) ||
            ((u32) hit->x4 != temp_r4_2))
        {
            hit->x4 = temp_r4_2;
            hit->state = HitCapsule_Enabled;
            M2C_FIELD(fp, u8*, 0x2219) =
                (u8) (M2C_FIELD(fp, u8*, 0x2219) | 0x10);
            ftColl_800768A0();
        }
        temp_r3 = cmd->x8;
        part = (s8) ((u32) M2C_FIELD(temp_r3, u32*, 0) >> 0xBU);
        if (((u8) M2C_FIELD(temp_r3, u8*, 2) >> 2U) & 1) {
            M2C_FIELD(hit, HSD_JObj**, 0x48) =
                fp->parts[ftParts_8007500C(fp, part)].joint;
        } else {
            M2C_FIELD(hit, HSD_JObj**, 0x48) = fp->parts[(int) part].joint;
        }
        ftColl_8007ABD0(hit, (u16) M2C_FIELD(cmd->x8, u8*, 2) & 0x3FF, gobj);
        cmd->x8 += 4;
        hit->scl = 0.003906f * (float) (u16) M2C_FIELD(cmd->x8, u32*, 0);
        hit->b_offset.x = 0.003906f * (float) (s16) M2C_FIELD(cmd->x8, u8*, 2);
        cmd->x8 += 4;
        hit->b_offset.y =
            0.003906f * (float) (s16) M2C_FIELD(cmd->x8, u32*, 0);
        hit->b_offset.z = 0.003906f * (float) (s16) M2C_FIELD(cmd->x8, u8*, 2);
        cmd->x8 += 4;
        ftColl_8007AC9C(hit, ((u16) M2C_FIELD(cmd->x8, u32*, 0) >> 7U) & 0x1FF,
                        gobj);
        hit->x24 = ((u32) M2C_FIELD(cmd->x8, u32*, 0) >> 0xEU) & 0x1FF;
        hit->x28 = ((u16) M2C_FIELD(cmd->x8, u8*, 2) >> 5U) & 0x1FF;
        hit->x43 =
            (hit->x43 & ~0x80) | ((M2C_FIELD(cmd->x8, u8*, 3) << 3) & 0x80);
        hit->x43 =
            (hit->x43 & ~0x40) | ((M2C_FIELD(cmd->x8, u8*, 3) << 4) & 0x40);
        M2C_FIELD(hit, u8*, 0x40) =
            (u8) ((M2C_FIELD(hit, u8*, 0x40) & ~0x80) |
                  ((M2C_FIELD(cmd->x8, u8*, 3) << 6) & 0x80));
        M2C_FIELD(hit, u8*, 0x40) =
            (u8) ((M2C_FIELD(hit, u8*, 0x40) & ~0x40) |
                  ((M2C_FIELD(cmd->x8, u8*, 3) << 6) & 0x40));
        cmd->x8 += 4;
        hit->x2C = ((u16) M2C_FIELD(cmd->x8, u32*, 0) >> 7U) & 0x1FF;
        hit->element = ((u8) M2C_FIELD(cmd->x8, u8*, 1) >> 2U) & 0x1F;
        M2C_FIELD(hit, int*, 0x34) =
            (int) ((int) ((M2C_FIELD(cmd->x8, u32*, 0) << 0xE) & 0xFF800000) >>
                   0x18);
        hit->sfx_severity = ((u16) M2C_FIELD(cmd->x8, u8*, 2) >> 7U) & 7;
        hit->sfx_kind = ((u8) M2C_FIELD(cmd->x8, u8*, 3) >> 2U) & 0x1F;
        M2C_FIELD(hit, u8*, 0x40) =
            (u8) ((M2C_FIELD(hit, u8*, 0x40) & ~0x20) |
                  ((M2C_FIELD(cmd->x8, u8*, 3) << 5) & 0x20));
        M2C_FIELD(hit, u8*, 0x40) =
            (u8) ((M2C_FIELD(hit, u8*, 0x40) & ~0x10) |
                  ((M2C_FIELD(cmd->x8, u8*, 3) << 3) & 0x10));
        cmd->x8 += 4;
        M2C_FIELD(hit, u8*, 0x42) = (u8) (M2C_FIELD(hit, u8*, 0x42) | 4);
        M2C_FIELD(hit, u8*, 0x42) = (u8) (M2C_FIELD(hit, u8*, 0x42) | 1);
        M2C_FIELD(hit, u8*, 0x41) = (u8) (M2C_FIELD(hit, u8*, 0x41) & ~8);
        M2C_FIELD(hit, u8*, 0x41) = (u8) (M2C_FIELD(hit, u8*, 0x41) & ~2);
        M2C_FIELD(hit, u8*, 0x41) = (u8) (M2C_FIELD(hit, u8*, 0x41) & ~4);
        M2C_FIELD(hit, u8*, 0x42) = (u8) (M2C_FIELD(hit, u8*, 0x42) & ~0x80);
        M2C_FIELD(hit, u8*, 0x42) = (u8) (M2C_FIELD(hit, u8*, 0x42) & ~8);
        M2C_FIELD(hit, u8*, 0x41) = (u8) (M2C_FIELD(hit, u8*, 0x41) & ~1);
        M2C_FIELD(hit, u8*, 0x134) =
            (u8) ((M2C_FIELD(hit, u8*, 0x134) & ~0x80) |
                  ((M2C_FIELD(cmd->x8, u8*, 1) << 4) & 0x80));
        M2C_FIELD(hit, u8*, 0x42) = (u8) (M2C_FIELD(hit, u8*, 0x42) | 0x40);
        M2C_FIELD(hit, u8*, 0x42) = (u8) (M2C_FIELD(hit, u8*, 0x42) & ~0x20);
        hit->x43 &= ~0x20;
        if (((HSD_GObjProc*) HSD_GObj_804D7838 != NULL) &&
            ((u8) HSD_GObj_804D7838->s_link > 9U))
        {
            ftColl_8007AD18(fp, hit);
        }
    }
    ftCommon_80080484(fp);
}
#endif

void ftAction_800715EC(Fighter_GObj* gobj, FtCmdState* cmd)
{
    cmd->x8 += 4;
    cmd->x8 += 4;
    cmd->x8 += 4;
    cmd->x8 += 4;
    cmd->x8 += 4;
}

/*
- code: 12
  name: Adjust Hitbox Damage
  parameters:
  - name: Hitbox ID
    bitCount: 3
  - name: Damage
    bitCount: 23
*/
/// Adjust Hitbox Damage
void ftAction_8007162C(Fighter_GObj* gobj, FtCmdState* cmd)
{
    int hitbox_id = *(u16*) cmd->x8 >> 7 & 7;
    HitCapsule* hitbox = &getFighter(gobj)->x914[hitbox_id];
    int damage = *(u32*) cmd->x8;
    // why does this have to be on a separate line?
    damage = damage & 0x7FFFFF;
    ftColl_8007ABD0(hitbox, damage, gobj);
    cmd->x8 += 4;
}

void ftAction_8007168C(Fighter_GObj* gobj, FtCmdState* cmd)
{
    cmd->x8 += 4;
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftAction_8007169C(Fighter_GObj* gobj, FtCmdState* cmd)
{ // clang-format off
    nofralloc
/* 8007169C 0006E27C  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 800716A0 0006E280  3C E0 43 30 */	lis r7, 0x4330
/* 800716A4 0006E284  80 C4 00 08 */	lwz r6, 8(r4)
/* 800716A8 0006E288  C8 22 88 C8 */	lfd f1, ftAction_804D82A8
/* 800716AC 0006E28C  80 A6 00 00 */	lwz r5, 0(r6)
/* 800716B0 0006E290  A0 06 00 00 */	lhz r0, 0(r6)
/* 800716B4 0006E294  54 A5 02 7E */	clrlwi r5, r5, 9
/* 800716B8 0006E298  C0 42 88 C0 */	lfs f2, ftAction_804D82A0
/* 800716BC 0006E29C  90 A1 00 24 */	stw r5, 0x24(r1)
/* 800716C0 0006E2A0  54 00 CF 7E */	rlwinm r0, r0, 0x19, 0x1d, 0x1f
/* 800716C4 0006E2A4  1C A0 01 38 */	mulli r5, r0, 0x138
/* 800716C8 0006E2A8  80 C3 00 2C */	lwz r6, 0x2c(r3)
/* 800716CC 0006E2AC  90 E1 00 20 */	stw r7, 0x20(r1)
/* 800716D0 0006E2B0  C8 01 00 20 */	lfd f0, 0x20(r1)
/* 800716D4 0006E2B4  38 05 09 30 */	addi r0, r5, 0x930
/* 800716D8 0006E2B8  EC 00 08 28 */	fsubs f0, f0, f1
/* 800716DC 0006E2BC  EC 02 00 32 */	fmuls f0, f2, f0
/* 800716E0 0006E2C0  7C 06 05 2E */	stfsx f0, r6, r0
/* 800716E4 0006E2C4  80 64 00 08 */	lwz r3, 8(r4)
/* 800716E8 0006E2C8  38 03 00 04 */	addi r0, r3, 4
/* 800716EC 0006E2CC  90 04 00 08 */	stw r0, 8(r4)
/* 800716F0 0006E2D0  38 21 00 28 */	addi r1, r1, 0x28
/* 800716F4 0006E2D4  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftAction_8007169C(Fighter_GObj* gobj, FtCmdState* cmd)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    char* cmd_x8 = cmd->x8;
    ftCo_Fighter* fp = gobj->user_data;
    *(float*) (fp + (((((u16) *cmd_x8 >> 7U) & 7) * 0x138) + 0x930)) =
        0.003906f * (float) (*cmd_x8 & 0x7FFFFF);
    cmd->x8 += 4;
}
#endif

void ftAction_800716F8(Fighter_GObj* gobj, FtCmdState* cmd)
{
    cmd->x8 += 4;
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftAction_80071708(Fighter_GObj* gobj, FtCmdState* cmd)
{ // clang-format off
    nofralloc
/* 80071708 0006E2E8  80 A4 00 08 */	lwz r5, 8(r4)
/* 8007170C 0006E2EC  80 C3 00 2C */	lwz r6, 0x2c(r3)
/* 80071710 0006E2F0  80 05 00 00 */	lwz r0, 0(r5)
/* 80071714 0006E2F4  38 65 00 03 */	addi r3, r5, 3
/* 80071718 0006E2F8  88 63 00 00 */	lbz r3, 0(r3)
/* 8007171C 0006E2FC  54 00 F2 3E */	rlwinm r0, r0, 0x1e, 8, 0x1f
/* 80071720 0006E300  1C A0 01 38 */	mulli r5, r0, 0x138
/* 80071724 0006E304  54 60 FF FE */	rlwinm r0, r3, 0x1f, 0x1f, 0x1f
/* 80071728 0006E308  38 A5 09 14 */	addi r5, r5, 0x914
/* 8007172C 0006E30C  2C 00 00 01 */	cmpwi r0, 1
/* 80071730 0006E310  7C A6 2A 14 */	add r5, r6, r5
/* 80071734 0006E314  41 82 00 24 */	beq lbl_80071758
/* 80071738 0006E318  40 80 00 2C */	bge lbl_80071764
/* 8007173C 0006E31C  2C 00 00 00 */	cmpwi r0, 0
/* 80071740 0006E320  40 80 00 08 */	bge lbl_80071748
/* 80071744 0006E324  48 00 00 20 */	b lbl_80071764
lbl_80071748:
/* 80071748 0006E328  88 05 00 42 */	lbz r0, 0x42(r5)
/* 8007174C 0006E32C  50 60 17 7A */	rlwimi r0, r3, 2, 0x1d, 0x1d
/* 80071750 0006E330  98 05 00 42 */	stb r0, 0x42(r5)
/* 80071754 0006E334  48 00 00 10 */	b lbl_80071764
lbl_80071758:
/* 80071758 0006E338  88 05 00 42 */	lbz r0, 0x42(r5)
/* 8007175C 0006E33C  50 60 07 FE */	rlwimi r0, r3, 0, 0x1f, 0x1f
/* 80071760 0006E340  98 05 00 42 */	stb r0, 0x42(r5)
lbl_80071764:
/* 80071764 0006E344  80 64 00 08 */	lwz r3, 8(r4)
/* 80071768 0006E348  38 03 00 04 */	addi r0, r3, 4
/* 8007176C 0006E34C  90 04 00 08 */	stw r0, 8(r4)
/* 80071770 0006E350  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftAction_80071708(Fighter_GObj* gobj, FtCmdState* cmd)
{
    char* cmd_x8 = cmd->x8;
    u8 temp_r3 = (u8) cmd_x8[3];
    int temp_r0 = (temp_r3 >> 1U) & 1;
    ftCo_Fighter* fp = gobj->user_data;
    HitCapsule* hit = &fp->x914[(((u32) *cmd_x8 >> 2U) & 0xFFFFFF)];
    switch (temp_r0) {
    case 0:
        hit->x42_b5 = false;
        // M2C_FIELD(hit, u8*, 0x42) =
        //     (u8) ((M2C_FIELD(hit, u8*, 0x42) & ~4) | ((temp_r3 << 2) & 4));
        break;
    case 1:
        hit->x42_b7 = false;
        // M2C_FIELD(hit, u8*, 0x42) =
        //     (u8) ((M2C_FIELD(hit, u8*, 0x42) & ~1) | (temp_r3 & 1));
        break;
    }
    cmd->x8 += 4;
}
#endif

void ftAction_80071774(Fighter_GObj* gobj, FtCmdState* cmd)
{
    cmd->x8 += 4;
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftAction_80071784(Fighter_GObj* gobj, FtCmdState* cmd)
{
    // clang-format off
    nofralloc
/* 80071784 0006E364  7C 08 02 A6 */	mflr r0
/* 80071788 0006E368  90 01 00 04 */	stw r0, 4(r1)
/* 8007178C 0006E36C  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80071790 0006E370  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80071794 0006E374  7C 9F 23 78 */	mr r31, r4
/* 80071798 0006E378  80 84 00 08 */	lwz r4, 8(r4)
/* 8007179C 0006E37C  80 84 00 00 */	lwz r4, 0(r4)
/* 800717A0 0006E380  54 84 01 BE */	clrlwi r4, r4, 6
/* 800717A4 0006E384  48 00 98 25 */	bl ftColl_8007AFC8
/* 800717A8 0006E388  80 7F 00 08 */	lwz r3, 8(r31)
/* 800717AC 0006E38C  38 03 00 04 */	addi r0, r3, 4
/* 800717B0 0006E390  90 1F 00 08 */	stw r0, 8(r31)
/* 800717B4 0006E394  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 800717B8 0006E398  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 800717BC 0006E39C  38 21 00 18 */	addi r1, r1, 0x18
/* 800717C0 0006E3A0  7C 08 03 A6 */	mtlr r0
/* 800717C4 0006E3A4  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftAction_80071784(Fighter_GObj* gobj, FtCmdState* cmd)
{
    ftColl_8007AFC8(gobj, *cmd->x8 & 0x03FFFFFF);
    cmd->x8 += 4;
}
#endif

void ftAction_800717C8(Fighter_GObj* gobj, FtCmdState* cmd)
{
    cmd->x8 += 4;
}

void ftAction_800717D8(Fighter_GObj* gobj, FtCmdState* cmd)
{
    ftColl_8007AFF8(gobj);
    cmd->x8 += 4;
}

void ftAction_80071810(Fighter_GObj* gobj, FtCmdState* cmd)
{
    cmd->x8 += 4;
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftAction_80071820(Fighter_GObj* gobj, FtCmdState* cmd)
{ // clang-format off
    nofralloc
/* 80071820 0006E400  80 A4 00 08 */	lwz r5, 8(r4)
/* 80071824 0006E404  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 80071828 0006E408  88 05 00 00 */	lbz r0, 0(r5)
/* 8007182C 0006E40C  54 00 07 BE */	clrlwi r0, r0, 0x1e
/* 80071830 0006E410  2C 00 00 02 */	cmpwi r0, 2
/* 80071834 0006E414  41 82 00 44 */	beq lbl_80071878
/* 80071838 0006E418  40 80 00 14 */	bge lbl_8007184C
/* 8007183C 0006E41C  2C 00 00 00 */	cmpwi r0, 0
/* 80071840 0006E420  41 82 00 18 */	beq lbl_80071858
/* 80071844 0006E424  40 80 00 24 */	bge lbl_80071868
/* 80071848 0006E428  48 00 00 4C */	b lbl_80071894
lbl_8007184C:
/* 8007184C 0006E42C  2C 00 00 04 */	cmpwi r0, 4
/* 80071850 0006E430  40 80 00 44 */	bge lbl_80071894
/* 80071854 0006E434  48 00 00 34 */	b lbl_80071888
lbl_80071858:
/* 80071858 0006E438  80 05 00 00 */	lwz r0, 0(r5)
/* 8007185C 0006E43C  54 00 02 3E */	clrlwi r0, r0, 8
/* 80071860 0006E440  90 03 22 00 */	stw r0, 0x2200(r3)
/* 80071864 0006E444  48 00 00 30 */	b lbl_80071894
lbl_80071868:
/* 80071868 0006E448  80 05 00 00 */	lwz r0, 0(r5)
/* 8007186C 0006E44C  54 00 02 3E */	clrlwi r0, r0, 8
/* 80071870 0006E450  90 03 22 04 */	stw r0, 0x2204(r3)
/* 80071874 0006E454  48 00 00 20 */	b lbl_80071894
lbl_80071878:
/* 80071878 0006E458  80 05 00 00 */	lwz r0, 0(r5)
/* 8007187C 0006E45C  54 00 02 3E */	clrlwi r0, r0, 8
/* 80071880 0006E460  90 03 22 08 */	stw r0, 0x2208(r3)
/* 80071884 0006E464  48 00 00 10 */	b lbl_80071894
lbl_80071888:
/* 80071888 0006E468  80 05 00 00 */	lwz r0, 0(r5)
/* 8007188C 0006E46C  54 00 02 3E */	clrlwi r0, r0, 8
/* 80071890 0006E470  90 03 22 0C */	stw r0, 0x220c(r3)
lbl_80071894:
/* 80071894 0006E474  80 64 00 08 */	lwz r3, 8(r4)
/* 80071898 0006E478  38 03 00 04 */	addi r0, r3, 4
/* 8007189C 0006E47C  90 04 00 08 */	stw r0, 8(r4)
/* 800718A0 0006E480  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftAction_80071820(Fighter_GObj* gobj, FtCmdState* cmd)
{
    char* cmd_x8 = cmd->x8;
    ftCo_Fighter* fp = gobj->user_data;
    int temp_r0 = (u8) *cmd_x8 & 3;
    /// @todo Suggests #Fighter::cmd_vars isn't an array.
    switch (temp_r0) {
    case 0:
        fp->cmd_vars[0] = (int) ((int) *cmd_x8 & 0xFFFFFF);
        break;
    case 1:
        fp->cmd_vars[1] = (int) ((int) *cmd_x8 & 0xFFFFFF);
        break;
    case 2:
        fp->cmd_vars[2] = (int) ((int) *cmd_x8 & 0xFFFFFF);
        break;
    case 3:
        fp->cmd_vars[3] = (int) ((int) *cmd_x8 & 0xFFFFFF);
        break;
    }
    cmd->x8 += 4;
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftAction_800718A4(Fighter_GObj* gobj, FtCmdState* cmd)
{ // clang-format off
    nofralloc
/* 800718A4 0006E484  80 A4 00 08 */	lwz r5, 8(r4)
/* 800718A8 0006E488  80 C3 00 2C */	lwz r6, 0x2c(r3)
/* 800718AC 0006E48C  80 05 00 00 */	lwz r0, 0(r5)
/* 800718B0 0006E490  54 00 01 BE */	clrlwi r0, r0, 6
/* 800718B4 0006E494  2C 00 00 01 */	cmpwi r0, 1
/* 800718B8 0006E498  41 82 00 30 */	beq lbl_800718E8
/* 800718BC 0006E49C  40 80 00 3C */	bge lbl_800718F8
/* 800718C0 0006E4A0  2C 00 00 00 */	cmpwi r0, 0
/* 800718C4 0006E4A4  40 80 00 08 */	bge lbl_800718CC
/* 800718C8 0006E4A8  48 00 00 30 */	b lbl_800718F8
lbl_800718CC:
/* 800718CC 0006E4AC  88 06 22 10 */	lbz r0, 0x2210(r6)
/* 800718D0 0006E4B0  38 60 00 01 */	li r3, 1
/* 800718D4 0006E4B4  50 60 26 F6 */	rlwimi r0, r3, 4, 0x1b, 0x1b
/* 800718D8 0006E4B8  98 06 22 10 */	stb r0, 0x2210(r6)
/* 800718DC 0006E4BC  C0 04 00 00 */	lfs f0, 0(r4)
/* 800718E0 0006E4C0  D0 06 22 14 */	stfs f0, 0x2214(r6)
/* 800718E4 0006E4C4  48 00 00 14 */	b lbl_800718F8
lbl_800718E8:
/* 800718E8 0006E4C8  88 06 22 10 */	lbz r0, 0x2210(r6)
/* 800718EC 0006E4CC  38 60 00 01 */	li r3, 1
/* 800718F0 0006E4D0  50 60 1F 38 */	rlwimi r0, r3, 3, 0x1c, 0x1c
/* 800718F4 0006E4D4  98 06 22 10 */	stb r0, 0x2210(r6)
lbl_800718F8:
/* 800718F8 0006E4D8  80 64 00 08 */	lwz r3, 8(r4)
/* 800718FC 0006E4DC  38 03 00 04 */	addi r0, r3, 4
/* 80071900 0006E4E0  90 04 00 08 */	stw r0, 8(r4)
/* 80071904 0006E4E4  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftAction_800718A4(Fighter_GObj* gobj, FtCmdState* cmd)
{
    ftCo_Fighter* fp = gobj->user_data;
    int cmd_x8 = *cmd->x8 & 0x03FFFFFF;
    switch (cmd_x8) {
    case 0:
        fp->throw_flags_b3 = true;
        fp->x2214 = cmd->x0;
        break;
    case 1:
        fp->throw_flags_b4 = true;
        break;
    }
    cmd->x8 += 4;
}
#endif

void ftAction_80071908(Fighter_GObj* gobj, FtCmdState* cmd)
{
    ftCo_Fighter* fp = gobj->user_data;
    fp->throw_flags_b1 = true;
    cmd->x8 += 4;
}

void ftAction_8007192C(Fighter_GObj* gobj, FtCmdState* cmd)
{
    ftCo_Fighter* fp = gobj->user_data;
    fp->throw_flags_b2 = true;
    cmd->x8 += 4;
}

void ftAction_80071950(Fighter_GObj* gobj, FtCmdState* cmd)
{
    ftCo_Fighter* fp = gobj->user_data;
    fp->allow_interrupt = true;
    cmd->x8 += 4;
}

void ftAction_80071974(Fighter_GObj* gobj, FtCmdState* cmd)
{
    ftCo_Fighter* fp = gobj->user_data;
    fp->throw_flags_b0 = true;
    cmd->x8 += 4;
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftAction_80071998(Fighter_GObj* gobj, FtCmdState* cmd)
{ // clang-format off
    nofralloc
/* 80071998 0006E578  7C 08 02 A6 */	mflr r0
/* 8007199C 0006E57C  90 01 00 04 */	stw r0, 4(r1)
/* 800719A0 0006E580  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800719A4 0006E584  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800719A8 0006E588  7C 9F 23 78 */	mr r31, r4
/* 800719AC 0006E58C  80 84 00 08 */	lwz r4, 8(r4)
/* 800719B0 0006E590  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 800719B4 0006E594  80 04 00 00 */	lwz r0, 0(r4)
/* 800719B8 0006E598  54 00 01 BE */	clrlwi r0, r0, 6
/* 800719BC 0006E59C  2C 00 00 01 */	cmpwi r0, 1
/* 800719C0 0006E5A0  41 82 00 28 */	beq lbl_800719E8
/* 800719C4 0006E5A4  40 80 00 10 */	bge lbl_800719D4
/* 800719C8 0006E5A8  2C 00 00 00 */	cmpwi r0, 0
/* 800719CC 0006E5AC  40 80 00 14 */	bge lbl_800719E0
/* 800719D0 0006E5B0  48 00 00 24 */	b lbl_800719F4
lbl_800719D4:
/* 800719D4 0006E5B4  2C 00 00 03 */	cmpwi r0, 3
/* 800719D8 0006E5B8  40 80 00 1C */	bge lbl_800719F4
/* 800719DC 0006E5BC  48 00 00 14 */	b lbl_800719F0
lbl_800719E0:
/* 800719E0 0006E5C0  48 00 BE 1D */	bl ftCommon_8007D7FC
/* 800719E4 0006E5C4  48 00 00 10 */	b lbl_800719F4
lbl_800719E8:
/* 800719E8 0006E5C8  48 00 BB ED */	bl ftCommon_8007D5D4
/* 800719EC 0006E5CC  48 00 00 08 */	b lbl_800719F4
lbl_800719F0:
/* 800719F0 0006E5D0  48 00 BC 1D */	bl ftCommon_8007D60C
lbl_800719F4:
/* 800719F4 0006E5D4  80 7F 00 08 */	lwz r3, 8(r31)
/* 800719F8 0006E5D8  38 03 00 04 */	addi r0, r3, 4
/* 800719FC 0006E5DC  90 1F 00 08 */	stw r0, 8(r31)
/* 80071A00 0006E5E0  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80071A04 0006E5E4  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80071A08 0006E5E8  38 21 00 20 */	addi r1, r1, 0x20
/* 80071A0C 0006E5EC  7C 08 03 A6 */	mtlr r0
/* 80071A10 0006E5F0  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftAction_80071998(Fighter_GObj* gobj, FtCmdState* cmd)
{
    ftCo_Fighter* fp = gobj->user_data;
    int temp_r0 = *cmd->x8 & 0x03FFFFFF;
    switch (temp_r0) { /* irregular */
    case 0:
        ftCommon_8007D7FC(fp);
        break;
    case 1:
        ftCommon_8007D5D4(fp);
        break;
    case 2:
        ftCommon_8007D60C(fp);
        break;
    }
    cmd->x8 += 4;
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftAction_80071A14(Fighter_GObj* gobj, FtCmdState* cmd)
{ // clang-format off
    nofralloc
/* 80071A14 0006E5F4  7C 08 02 A6 */	mflr r0
/* 80071A18 0006E5F8  90 01 00 04 */	stw r0, 4(r1)
/* 80071A1C 0006E5FC  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80071A20 0006E600  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80071A24 0006E604  7C 9F 23 78 */	mr r31, r4
/* 80071A28 0006E608  80 84 00 08 */	lwz r4, 8(r4)
/* 80071A2C 0006E60C  80 84 00 00 */	lwz r4, 0(r4)
/* 80071A30 0006E610  54 84 01 BE */	clrlwi r4, r4, 6
/* 80071A34 0006E614  48 00 9B F9 */	bl ftColl_8007B62C
/* 80071A38 0006E618  80 7F 00 08 */	lwz r3, 8(r31)
/* 80071A3C 0006E61C  38 03 00 04 */	addi r0, r3, 4
/* 80071A40 0006E620  90 1F 00 08 */	stw r0, 8(r31)
/* 80071A44 0006E624  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80071A48 0006E628  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80071A4C 0006E62C  38 21 00 18 */	addi r1, r1, 0x18
/* 80071A50 0006E630  7C 08 03 A6 */	mtlr r0
/* 80071A54 0006E634  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftAction_80071A14(Fighter_GObj* gobj, FtCmdState* cmd)
{
    ftColl_8007B62C(gobj, *cmd->x8 & 0x03FFFFFF);
    cmd->x8 += 4;
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftAction_80071A58(Fighter_GObj* gobj, FtCmdState* cmd)
{ // clang-format off
    nofralloc
/* 80071A58 0006E638  7C 08 02 A6 */	mflr r0
/* 80071A5C 0006E63C  90 01 00 04 */	stw r0, 4(r1)
/* 80071A60 0006E640  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80071A64 0006E644  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80071A68 0006E648  7C 9F 23 78 */	mr r31, r4
/* 80071A6C 0006E64C  80 84 00 08 */	lwz r4, 8(r4)
/* 80071A70 0006E650  80 84 00 00 */	lwz r4, 0(r4)
/* 80071A74 0006E654  54 84 01 BE */	clrlwi r4, r4, 6
/* 80071A78 0006E658  48 00 96 49 */	bl ftColl_8007B0C0
/* 80071A7C 0006E65C  80 7F 00 08 */	lwz r3, 8(r31)
/* 80071A80 0006E660  38 03 00 04 */	addi r0, r3, 4
/* 80071A84 0006E664  90 1F 00 08 */	stw r0, 8(r31)
/* 80071A88 0006E668  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80071A8C 0006E66C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80071A90 0006E670  38 21 00 18 */	addi r1, r1, 0x18
/* 80071A94 0006E674  7C 08 03 A6 */	mtlr r0
/* 80071A98 0006E678  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftAction_80071A58(Fighter_GObj* gobj, FtCmdState* cmd)
{
    ftColl_8007B0C0(gobj, *cmd->x8 & 0x03FFFFFF);
    cmd->x8 += 4;
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftAction_80071A9C(Fighter_GObj* gobj, FtCmdState* cmd)
{
    // clang-format off
    nofralloc
/* 80071A9C 0006E67C  7C 08 02 A6 */	mflr r0
/* 80071AA0 0006E680  90 01 00 04 */	stw r0, 4(r1)
/* 80071AA4 0006E684  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80071AA8 0006E688  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80071AAC 0006E68C  7C 9F 23 78 */	mr r31, r4
/* 80071AB0 0006E690  80 A4 00 08 */	lwz r5, 8(r4)
/* 80071AB4 0006E694  A0 85 00 00 */	lhz r4, 0(r5)
/* 80071AB8 0006E698  80 A5 00 00 */	lwz r5, 0(r5)
/* 80071ABC 0006E69C  54 84 F6 3E */	rlwinm r4, r4, 0x1e, 0x18, 0x1f
/* 80071AC0 0006E6A0  54 A5 03 BE */	clrlwi r5, r5, 0xe
/* 80071AC4 0006E6A4  48 00 96 65 */	bl ftColl_8007B128
/* 80071AC8 0006E6A8  80 7F 00 08 */	lwz r3, 8(r31)
/* 80071ACC 0006E6AC  38 03 00 04 */	addi r0, r3, 4
/* 80071AD0 0006E6B0  90 1F 00 08 */	stw r0, 8(r31)
/* 80071AD4 0006E6B4  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80071AD8 0006E6B8  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80071ADC 0006E6BC  38 21 00 18 */	addi r1, r1, 0x18
/* 80071AE0 0006E6C0  7C 08 03 A6 */	mtlr r0
/* 80071AE4 0006E6C4  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftAction_80071A9C(Fighter_GObj* gobj, FtCmdState* cmd)
{
    char* cmd_x8 = cmd->x8;
    ftColl_8007B128((s8) ((u16) *cmd_x8 >> 2U), (int) *cmd_x8 & 0x3FFFF);
    cmd->x8 += 4;
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftAction_80071AE8(Fighter_GObj* gobj, FtCmdState* cmd)
{ // clang-format off
    nofralloc
/* 80071AE8 0006E6C8  80 A4 00 08 */	lwz r5, 8(r4)
/* 80071AEC 0006E6CC  80 C3 00 2C */	lwz r6, 0x2c(r3)
/* 80071AF0 0006E6D0  80 05 00 00 */	lwz r0, 0(r5)
/* 80071AF4 0006E6D4  54 00 01 BF */	clrlwi. r0, r0, 6
/* 80071AF8 0006E6D8  41 82 00 10 */	beq lbl_80071B08
/* 80071AFC 0006E6DC  80 06 19 7C */	lwz r0, 0x197c(r6)
/* 80071B00 0006E6E0  28 00 00 00 */	cmplwi r0, 0
/* 80071B04 0006E6E4  41 82 00 14 */	beq lbl_80071B18
lbl_80071B08:
/* 80071B08 0006E6E8  88 06 22 18 */	lbz r0, 0x2218(r6)
/* 80071B0C 0006E6EC  38 60 00 01 */	li r3, 1
/* 80071B10 0006E6F0  50 60 36 72 */	rlwimi r0, r3, 6, 0x19, 0x19
/* 80071B14 0006E6F4  98 06 22 18 */	stb r0, 0x2218(r6)
lbl_80071B18:
/* 80071B18 0006E6F8  80 64 00 08 */	lwz r3, 8(r4)
/* 80071B1C 0006E6FC  38 03 00 04 */	addi r0, r3, 4
/* 80071B20 0006E700  90 04 00 08 */	stw r0, 8(r4)
/* 80071B24 0006E704  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftAction_80071AE8(Fighter_GObj* gobj, FtCmdState* cmd)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (!(*cmd->x8 & 0x03FFFFFF) || fp->x197C != NULL) {
        fp->x2218_b1 = true;
    }
    cmd->x8 += 4;
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftAction_80071B28(Fighter_GObj* gobj, FtCmdState* cmd)
{ // clang-format off
    nofralloc
/* 80071B28 0006E708  80 A4 00 08 */	lwz r5, 8(r4)
/* 80071B2C 0006E70C  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 80071B30 0006E710  80 A5 00 00 */	lwz r5, 0(r5)
/* 80071B34 0006E714  88 03 22 18 */	lbz r0, 0x2218(r3)
/* 80071B38 0006E718  50 A0 2E B4 */	rlwimi r0, r5, 5, 0x1a, 0x1a
/* 80071B3C 0006E71C  98 03 22 18 */	stb r0, 0x2218(r3)
/* 80071B40 0006E720  80 64 00 08 */	lwz r3, 8(r4)
/* 80071B44 0006E724  38 03 00 04 */	addi r0, r3, 4
/* 80071B48 0006E728  90 04 00 08 */	stw r0, 8(r4)
/* 80071B4C 0006E72C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftAction_80071B28(Fighter_GObj* gobj, FtCmdState* cmd)
{
    ftCo_Fighter* fp = gobj->user_data;
    fp->x2218_b2 = (*cmd->x8);
    // M2C_FIELD(fp, u8*, 0x2218) =
    //     (u8) ((M2C_FIELD(fp, u8*, 0x2218) & ~0x20) | ((*cmd->x8 << 5) &
    //     0x20));
    cmd->x8 += 4;
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
jtbl_t jtbl_803C08A4 = {
    lbl_80071BE0, lbl_80071BE8, lbl_80071BF0, lbl_80071BF8,
    lbl_80071C00, lbl_80071C08, lbl_80071C10,
};
#pragma push
asm void ftAction_80071B50(Fighter_GObj* gobj, FtCmdState* cmd)
{ // clang-format off
    nofralloc
/* 80071B50 0006E730  7C 08 02 A6 */	mflr r0
/* 80071B54 0006E734  90 01 00 04 */	stw r0, 4(r1)
/* 80071B58 0006E738  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80071B5C 0006E73C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80071B60 0006E740  7C 9F 23 78 */	mr r31, r4
/* 80071B64 0006E744  80 84 00 08 */	lwz r4, 8(r4)
/* 80071B68 0006E748  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 80071B6C 0006E74C  A1 04 00 00 */	lhz r8, 0(r4)
/* 80071B70 0006E750  38 04 00 04 */	addi r0, r4, 4
/* 80071B74 0006E754  55 08 F6 3E */	rlwinm r8, r8, 0x1e, 0x18, 0x1f
/* 80071B78 0006E758  90 1F 00 08 */	stw r0, 8(r31)
/* 80071B7C 0006E75C  2C 08 00 0A */	cmpwi r8, 0xa
/* 80071B80 0006E760  40 80 00 18 */	bge lbl_80071B98
/* 80071B84 0006E764  2C 08 00 07 */	cmpwi r8, 7
/* 80071B88 0006E768  40 80 00 FC */	bge lbl_80071C84
/* 80071B8C 0006E76C  2C 08 00 00 */	cmpwi r8, 0
/* 80071B90 0006E770  40 80 00 14 */	bge lbl_80071BA4
/* 80071B94 0006E774  48 00 00 F0 */	b lbl_80071C84
lbl_80071B98:
/* 80071B98 0006E778  2C 08 00 10 */	cmpwi r8, 0x10
/* 80071B9C 0006E77C  40 80 00 E8 */	bge lbl_80071C84
/* 80071BA0 0006E780  48 00 00 78 */	b lbl_80071C18
lbl_80071BA4:
/* 80071BA4 0006E784  80 BF 00 08 */	lwz r5, 8(r31)
/* 80071BA8 0006E788  28 08 00 06 */	cmplwi r8, 6
/* 80071BAC 0006E78C  80 85 00 00 */	lwz r4, 0(r5)
/* 80071BB0 0006E790  38 05 00 04 */	addi r0, r5, 4
/* 80071BB4 0006E794  90 1F 00 08 */	stw r0, 8(r31)
/* 80071BB8 0006E798  80 DF 00 08 */	lwz r6, 8(r31)
/* 80071BBC 0006E79C  88 A6 00 02 */	lbz r5, 2(r6)
/* 80071BC0 0006E7A0  88 C6 00 03 */	lbz r6, 3(r6)
/* 80071BC4 0006E7A4  41 81 00 C0 */	bgt lbl_80071C84
/* 80071BC8 0006E7A8  3C E0 80 3C */	lis r7, jtbl_803C08A4@ha
/* 80071BCC 0006E7AC  38 E7 08 A4 */	addi r7, r7, jtbl_803C08A4@l
/* 80071BD0 0006E7B0  55 00 10 3A */	slwi r0, r8, 2
/* 80071BD4 0006E7B4  7C 07 00 2E */	lwzx r0, r7, r0
/* 80071BD8 0006E7B8  7C 09 03 A6 */	mtctr r0
/* 80071BDC 0006E7BC  4E 80 04 20 */	bctr
entry lbl_80071BE0
/* 80071BE0 0006E7C0  48 01 65 69 */	bl ft_80088148
/* 80071BE4 0006E7C4  48 00 00 A0 */	b lbl_80071C84
entry lbl_80071BE8
/* 80071BE8 0006E7C8  48 01 68 91 */	bl ft_80088478
/* 80071BEC 0006E7CC  48 00 00 98 */	b lbl_80071C84
entry lbl_80071BF0
/* 80071BF0 0006E7D0  48 01 65 E9 */	bl ft_800881D8
/* 80071BF4 0006E7D4  48 00 00 90 */	b lbl_80071C84
entry lbl_80071BF8
/* 80071BF8 0006E7D8  48 01 69 19 */	bl ft_80088510
/* 80071BFC 0006E7DC  48 00 00 88 */	b lbl_80071C84
entry lbl_80071C00
/* 80071C00 0006E7E0  48 01 69 A9 */	bl ft_800885A8
/* 80071C04 0006E7E4  48 00 00 80 */	b lbl_80071C84
entry lbl_80071C08
/* 80071C08 0006E7E8  48 01 6A 39 */	bl ft_80088640
/* 80071C0C 0006E7EC  48 00 00 78 */	b lbl_80071C84
entry lbl_80071C10
/* 80071C10 0006E7F0  48 01 67 19 */	bl ft_80088328
/* 80071C14 0006E7F4  48 00 00 70 */	b lbl_80071C84
lbl_80071C18:
/* 80071C18 0006E7F8  80 9F 00 08 */	lwz r4, 8(r31)
/* 80071C1C 0006E7FC  2C 08 00 0D */	cmpwi r8, 0xd
/* 80071C20 0006E800  38 04 00 04 */	addi r0, r4, 4
/* 80071C24 0006E804  90 1F 00 08 */	stw r0, 8(r31)
/* 80071C28 0006E808  41 82 00 48 */	beq lbl_80071C70
/* 80071C2C 0006E80C  40 80 00 1C */	bge lbl_80071C48
/* 80071C30 0006E810  2C 08 00 0B */	cmpwi r8, 0xb
/* 80071C34 0006E814  41 82 00 2C */	beq lbl_80071C60
/* 80071C38 0006E818  40 80 00 30 */	bge lbl_80071C68
/* 80071C3C 0006E81C  2C 08 00 0A */	cmpwi r8, 0xa
/* 80071C40 0006E820  40 80 00 18 */	bge lbl_80071C58
/* 80071C44 0006E824  48 00 00 40 */	b lbl_80071C84
lbl_80071C48:
/* 80071C48 0006E828  2C 08 00 0F */	cmpwi r8, 0xf
/* 80071C4C 0006E82C  41 82 00 34 */	beq lbl_80071C80
/* 80071C50 0006E830  40 80 00 34 */	bge lbl_80071C84
/* 80071C54 0006E834  48 00 00 24 */	b lbl_80071C78
lbl_80071C58:
/* 80071C58 0006E838  48 01 6B D1 */	bl ft_80088828
/* 80071C5C 0006E83C  48 00 00 28 */	b lbl_80071C84
lbl_80071C60:
/* 80071C60 0006E840  48 01 6B 11 */	bl ft_80088770
/* 80071C64 0006E844  48 00 00 20 */	b lbl_80071C84
lbl_80071C68:
/* 80071C68 0006E848  48 01 6C 1D */	bl ft_80088884
/* 80071C6C 0006E84C  48 00 00 18 */	b lbl_80071C84
lbl_80071C70:
/* 80071C70 0006E850  48 01 6C 71 */	bl ft_800888E0
/* 80071C74 0006E854  48 00 00 10 */	b lbl_80071C84
lbl_80071C78:
/* 80071C78 0006E858  48 01 6C C5 */	bl ft_8008893C
/* 80071C7C 0006E85C  48 00 00 08 */	b lbl_80071C84
lbl_80071C80:
/* 80071C80 0006E860  48 01 6B 4D */	bl ft_800887CC
lbl_80071C84:
/* 80071C84 0006E864  80 7F 00 08 */	lwz r3, 8(r31)
/* 80071C88 0006E868  38 03 00 04 */	addi r0, r3, 4
/* 80071C8C 0006E86C  90 1F 00 08 */	stw r0, 8(r31)
/* 80071C90 0006E870  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80071C94 0006E874  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80071C98 0006E878  38 21 00 20 */	addi r1, r1, 0x20
/* 80071C9C 0006E87C  7C 08 03 A6 */	mtlr r0
/* 80071CA0 0006E880  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftAction_80071B50(Fighter_GObj* gobj, FtCmdState* cmd)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    int temp_r4_2;
    char* temp_r5;
    char* temp_r6;
    char temp_r8;
    u8 temp_r5_2;
    u8 temp_r6_2;

    char* cmd_x8 = cmd->x8;
    ftCo_Fighter* fp = gobj->user_data;
    temp_r8 = (s8) ((u16) *cmd_x8 >> 2U);
    cmd->x8 = cmd_x8 + 4;
    if (temp_r8 < 0xA) {
        if (temp_r8 < 7) {
            if (temp_r8 < 0) {
            } else {
                temp_r5 = cmd->x8;
                temp_r4_2 = M2C_FIELD(temp_r5, int*, 0);
                cmd->x8 = temp_r5 + 4;
                temp_r6 = cmd->x8;
                temp_r5_2 = M2C_FIELD(temp_r6, u8*, 2);
                temp_r6_2 = M2C_FIELD(temp_r6, u8*, 3);
                switch (temp_r8) {
                case 0:
                    ft_80088148(fp, temp_r4_2, (int) temp_r5_2,
                                (int) temp_r6_2);
                    break;
                case 1:
                    ft_80088478(fp, temp_r4_2, (int) temp_r5_2,
                                (int) temp_r6_2);
                    break;
                case 2:
                    ft_800881D8(fp, (u32) temp_r4_2, (u32) temp_r5_2,
                                (u32) temp_r6_2);
                    break;
                case 3:
                    ft_80088510(fp, temp_r4_2, temp_r5_2, temp_r6_2);
                    break;
                case 4:
                    ft_800885A8(fp, temp_r4_2, temp_r5_2, temp_r6_2);
                    break;
                case 5:
                    ft_80088640(fp, temp_r4_2, (int) temp_r5_2,
                                (int) temp_r6_2);
                    break;
                case 6:
                    ft_80088328(fp, temp_r4_2, (int) temp_r5_2,
                                (int) temp_r6_2);
                    break;
                }
            }
        }
    } else if (temp_r8 < 0x10) {
        cmd->x8 += 4;
        switch (temp_r8) { /* switch 1; irregular */
        case 10:           /* switch 1 */
            ft_80088828(fp);
            break;
        case 11: /* switch 1 */
            ft_80088770(fp);
            break;
        case 12: /* switch 1 */
            ft_80088884(fp);
            break;
        case 13: /* switch 1 */
            ft_800888E0(fp);
            break;
        case 14: /* switch 1 */
            ft_8008893C(fp);
            break;
        case 15: /* switch 1 */
            ft_800887CC(fp);
            break;
        }
    }
    cmd->x8 += 4;
}
#endif

void ftAction_80071CA4(Fighter_GObj* gobj, FtCmdState* cmd)
{
    cmd->x8 += 4;
    cmd->x8 += 4;
    cmd->x8 += 4;
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftAction_80071CCC(Fighter_GObj* gobj, FtCmdState* cmd)
{ // clang-format off
    nofralloc
/* 80071CCC 0006E8AC  7C 08 02 A6 */	mflr r0
/* 80071CD0 0006E8B0  90 01 00 04 */	stw r0, 4(r1)
/* 80071CD4 0006E8B4  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80071CD8 0006E8B8  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80071CDC 0006E8BC  7C 9F 23 78 */	mr r31, r4
/* 80071CE0 0006E8C0  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 80071CE4 0006E8C4  80 83 01 0C */	lwz r4, 0x10c(r3)
/* 80071CE8 0006E8C8  80 84 00 4C */	lwz r4, 0x4c(r4)
/* 80071CEC 0006E8CC  80 04 00 00 */	lwz r0, 0(r4)
/* 80071CF0 0006E8D0  28 00 00 00 */	cmplwi r0, 0
/* 80071CF4 0006E8D4  7C 04 03 78 */	mr r4, r0
/* 80071CF8 0006E8D8  40 82 00 14 */	bne lbl_80071D0C
/* 80071CFC 0006E8DC  80 7F 00 08 */	lwz r3, 8(r31)
/* 80071D00 0006E8E0  38 03 00 04 */	addi r0, r3, 4
/* 80071D04 0006E8E4  90 1F 00 08 */	stw r0, 8(r31)
/* 80071D08 0006E8E8  48 00 00 14 */	b lbl_80071D1C
lbl_80071D0C:
/* 80071D0C 0006E8EC  48 01 6C E9 */	bl ft_800889F4
/* 80071D10 0006E8F0  80 7F 00 08 */	lwz r3, 8(r31)
/* 80071D14 0006E8F4  38 03 00 04 */	addi r0, r3, 4
/* 80071D18 0006E8F8  90 1F 00 08 */	stw r0, 8(r31)
lbl_80071D1C:
/* 80071D1C 0006E8FC  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80071D20 0006E900  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80071D24 0006E904  38 21 00 20 */	addi r1, r1, 0x20
/* 80071D28 0006E908  7C 08 03 A6 */	mtlr r0
/* 80071D2C 0006E90C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftAction_80071CCC(Fighter_GObj* gobj, FtCmdState* cmd)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    ftCo_Fighter* fp = gobj->user_data;
    FtCollisionData* cd = fp->ft_data->x4C_collisionData;
    if (cd == NULL) {
        cmd->x8 += 4;
    } else {
        ft_800889F4(fp, cd);
        cmd->x8 += 4;
    }
}
#endif

void ftAction_80071D30(Fighter_GObj* gobj, FtCmdState* cmd)
{
    cmd->x8 += 4;
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftAction_80071D40(Fighter_GObj* gobj, FtCmdState* cmd)
{ // clang-format off
    nofralloc
/* 80071D40 0006E920  7C 08 02 A6 */	mflr r0
/* 80071D44 0006E924  90 01 00 04 */	stw r0, 4(r1)
/* 80071D48 0006E928  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80071D4C 0006E92C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80071D50 0006E930  7C 9F 23 78 */	mr r31, r4
/* 80071D54 0006E934  80 A4 00 08 */	lwz r5, 8(r4)
/* 80071D58 0006E938  A8 85 00 00 */	lha r4, 0(r5)
/* 80071D5C 0006E93C  80 A5 00 00 */	lwz r5, 0(r5)
/* 80071D60 0006E940  54 84 B0 0E */	rlwinm r4, r4, 0x16, 0, 7
/* 80071D64 0006E944  7C 84 CE 70 */	srawi r4, r4, 0x19
/* 80071D68 0006E948  54 A5 68 26 */	rlwinm r5, r5, 0xd, 0, 0x13
/* 80071D6C 0006E94C  7C A5 6E 70 */	srawi r5, r5, 0xd
/* 80071D70 0006E950  48 00 2D 9D */	bl ftParts_80074B0C
/* 80071D74 0006E954  80 7F 00 08 */	lwz r3, 8(r31)
/* 80071D78 0006E958  38 03 00 04 */	addi r0, r3, 4
/* 80071D7C 0006E95C  90 1F 00 08 */	stw r0, 8(r31)
/* 80071D80 0006E960  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80071D84 0006E964  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80071D88 0006E968  38 21 00 18 */	addi r1, r1, 0x18
/* 80071D8C 0006E96C  7C 08 03 A6 */	mtlr r0
/* 80071D90 0006E970  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftAction_80071D40(Fighter_GObj* gobj, FtCmdState* cmd)
{
    char* p_cmd_x8 = cmd->x8;
    u32 cmd_x8 = *p_cmd_x8;
    ftParts_80074B0C(gobj, (int) ((*p_cmd_x8 << 0x16) & 0xFF000000) >> 0x19,
                     (int) ((cmd_x8 << 0xD) | ((cmd_x8 >> 0x13U) & 0x1000)) >>
                         0xD);
    cmd->x8 += 4;
}
#endif

void ftAction_80071D94(Fighter_GObj* gobj, FtCmdState* cmd)
{
    ftParts_80074A8C(gobj);
    cmd->x8 += 4;
}

void ftAction_80071DCC(Fighter_GObj* gobj, FtCmdState* cmd)
{
    ftParts_80074ACC(gobj);
    cmd->x8 += 4;
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftAction_80071E04(Fighter_GObj* gobj, FtCmdState* cmd)
{
    // clang-format off
    nofralloc
/* 80071E04 0006E9E4  7C 08 02 A6 */	mflr r0
/* 80071E08 0006E9E8  90 01 00 04 */	stw r0, 4(r1)
/* 80071E0C 0006E9EC  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 80071E10 0006E9F0  93 E1 00 24 */	stw r31, 0x24(r1)
/* 80071E14 0006E9F4  93 C1 00 20 */	stw r30, 0x20(r1)
/* 80071E18 0006E9F8  7C 9E 23 78 */	mr r30, r4
/* 80071E1C 0006E9FC  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 80071E20 0006EA00  7C 7D 1B 78 */	mr r29, r3
/* 80071E24 0006EA04  7F A5 EB 78 */	mr r5, r29
/* 80071E28 0006EA08  80 84 00 08 */	lwz r4, 8(r4)
/* 80071E2C 0006EA0C  80 C3 00 2C */	lwz r6, 0x2c(r3)
/* 80071E30 0006EA10  A0 04 00 00 */	lhz r0, 0(r4)
/* 80071E34 0006EA14  80 84 00 00 */	lwz r4, 0(r4)
/* 80071E38 0006EA18  54 00 CF 7E */	rlwinm r0, r0, 0x19, 0x1d, 0x1f
/* 80071E3C 0006EA1C  1C 60 01 38 */	mulli r3, r0, 0x138
/* 80071E40 0006EA20  3B E3 0D F4 */	addi r31, r3, 0xdf4
/* 80071E44 0006EA24  7F E6 FA 14 */	add r31, r6, r31
/* 80071E48 0006EA28  38 7F 00 00 */	addi r3, r31, 0
/* 80071E4C 0006EA2C  54 84 02 7E */	clrlwi r4, r4, 9
/* 80071E50 0006EA30  48 00 8D 81 */	bl ftColl_8007ABD0
/* 80071E54 0006EA34  80 9E 00 08 */	lwz r4, 8(r30)
/* 80071E58 0006EA38  38 7F 00 00 */	addi r3, r31, 0
/* 80071E5C 0006EA3C  38 BD 00 00 */	addi r5, r29, 0
/* 80071E60 0006EA40  38 04 00 04 */	addi r0, r4, 4
/* 80071E64 0006EA44  90 1E 00 08 */	stw r0, 8(r30)
/* 80071E68 0006EA48  80 9E 00 08 */	lwz r4, 8(r30)
/* 80071E6C 0006EA4C  A0 84 00 00 */	lhz r4, 0(r4)
/* 80071E70 0006EA50  54 84 CD FE */	rlwinm r4, r4, 0x19, 0x17, 0x1f
/* 80071E74 0006EA54  48 00 8E 29 */	bl ftColl_8007AC9C
/* 80071E78 0006EA58  80 7E 00 08 */	lwz r3, 8(r30)
/* 80071E7C 0006EA5C  80 03 00 00 */	lwz r0, 0(r3)
/* 80071E80 0006EA60  54 00 95 FE */	rlwinm r0, r0, 0x12, 0x17, 0x1f
/* 80071E84 0006EA64  90 1F 00 24 */	stw r0, 0x24(r31)
/* 80071E88 0006EA68  80 7E 00 08 */	lwz r3, 8(r30)
/* 80071E8C 0006EA6C  A0 03 00 02 */	lhz r0, 2(r3)
/* 80071E90 0006EA70  54 00 DD FE */	rlwinm r0, r0, 0x1b, 0x17, 0x1f
/* 80071E94 0006EA74  90 1F 00 28 */	stw r0, 0x28(r31)
/* 80071E98 0006EA78  80 7E 00 08 */	lwz r3, 8(r30)
/* 80071E9C 0006EA7C  38 03 00 04 */	addi r0, r3, 4
/* 80071EA0 0006EA80  90 1E 00 08 */	stw r0, 8(r30)
/* 80071EA4 0006EA84  80 7E 00 08 */	lwz r3, 8(r30)
/* 80071EA8 0006EA88  A0 03 00 00 */	lhz r0, 0(r3)
/* 80071EAC 0006EA8C  54 00 CD FE */	rlwinm r0, r0, 0x19, 0x17, 0x1f
/* 80071EB0 0006EA90  90 1F 00 2C */	stw r0, 0x2c(r31)
/* 80071EB4 0006EA94  80 7E 00 08 */	lwz r3, 8(r30)
/* 80071EB8 0006EA98  88 03 00 01 */	lbz r0, 1(r3)
/* 80071EBC 0006EA9C  54 00 EF 3E */	rlwinm r0, r0, 0x1d, 0x1c, 0x1f
/* 80071EC0 0006EAA0  90 1F 00 30 */	stw r0, 0x30(r31)
/* 80071EC4 0006EAA4  80 7E 00 08 */	lwz r3, 8(r30)
/* 80071EC8 0006EAA8  88 03 00 01 */	lbz r0, 1(r3)
/* 80071ECC 0006EAAC  54 00 07 7E */	clrlwi r0, r0, 0x1d
/* 80071ED0 0006EAB0  90 1F 00 38 */	stw r0, 0x38(r31)
/* 80071ED4 0006EAB4  80 7E 00 08 */	lwz r3, 8(r30)
/* 80071ED8 0006EAB8  88 03 00 02 */	lbz r0, 2(r3)
/* 80071EDC 0006EABC  54 00 E7 3E */	rlwinm r0, r0, 0x1c, 0x1c, 0x1f
/* 80071EE0 0006EAC0  90 1F 00 3C */	stw r0, 0x3c(r31)
/* 80071EE4 0006EAC4  80 7E 00 08 */	lwz r3, 8(r30)
/* 80071EE8 0006EAC8  38 03 00 04 */	addi r0, r3, 4
/* 80071EEC 0006EACC  90 1E 00 08 */	stw r0, 8(r30)
/* 80071EF0 0006EAD0  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 80071EF4 0006EAD4  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 80071EF8 0006EAD8  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 80071EFC 0006EADC  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 80071F00 0006EAE0  38 21 00 28 */	addi r1, r1, 0x28
/* 80071F04 0006EAE4  7C 08 03 A6 */	mtlr r0
/* 80071F08 0006EAE8  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftAction_80071E04(Fighter_GObj* gobj, FtCmdState* cmd)
{
    HitCapsule* hit;
    char* cmd_x8 = cmd->x8;
    ftCo_Fighter* fp = gobj->user_data;
    hit = &fp->xDF4[(((u16) *cmd_x8 >> 7U) & 7)];
    ftColl_8007ABD0(hit, (int) *cmd_x8 & 0x7FFFFF, gobj);
    cmd->x8 += 4;
    ftColl_8007AC9C(hit, ((u16) M2C_FIELD(cmd->x8, u16*, 0) >> 7U) & 0x1FF,
                    gobj);
    hit->x24 = ((u32) M2C_FIELD(cmd->x8, u16*, 0) >> 0xEU) & 0x1FF;
    hit->x28 = (int) (((u16) M2C_FIELD(cmd->x8, u16*, 2) >> 5U) & 0x1FF);
    cmd->x8 += 4;
    hit->x2C = (int) (((u16) M2C_FIELD(cmd->x8, u16*, 0) >> 7U) & 0x1FF);
    hit->element = ((u8) M2C_FIELD(cmd->x8, u8*, 1) >> 3U) & 0xF;
    hit->sfx_severity = M2C_FIELD(cmd->x8, u8*, 1) & 7;
    hit->sfx_kind = ((u8) M2C_FIELD(cmd->x8, u16*, 2) >> 4U) & 0xF;
    cmd->x8 += 4;
}
#endif

void ftAction_80071F0C(Fighter_GObj* gobj, FtCmdState* cmd)
{
    cmd->x8 += 4;
    cmd->x8 += 4;
    cmd->x8 += 4;
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftAction_80071F34(Fighter_GObj* gobj, FtCmdState* cmd)
{ // clang-format off
    nofralloc
/* 80071F34 0006EB14  7C 08 02 A6 */	mflr r0
/* 80071F38 0006EB18  90 01 00 04 */	stw r0, 4(r1)
/* 80071F3C 0006EB1C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80071F40 0006EB20  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80071F44 0006EB24  7C 9F 23 78 */	mr r31, r4
/* 80071F48 0006EB28  80 84 00 08 */	lwz r4, 8(r4)
/* 80071F4C 0006EB2C  80 84 00 00 */	lwz r4, 0(r4)
/* 80071F50 0006EB30  54 84 01 BE */	clrlwi r4, r4, 6
/* 80071F54 0006EB34  48 00 D6 79 */	bl ftCommon_8007F5CC
/* 80071F58 0006EB38  80 7F 00 08 */	lwz r3, 8(r31)
/* 80071F5C 0006EB3C  38 03 00 04 */	addi r0, r3, 4
/* 80071F60 0006EB40  90 1F 00 08 */	stw r0, 8(r31)
/* 80071F64 0006EB44  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80071F68 0006EB48  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80071F6C 0006EB4C  38 21 00 20 */	addi r1, r1, 0x20
/* 80071F70 0006EB50  7C 08 03 A6 */	mtlr r0
/* 80071F74 0006EB54  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftAction_80071F34(Fighter_GObj* gobj, FtCmdState* cmd)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    ftCommon_8007F5CC(gobj, *cmd->x8 & 0x03FFFFFF);
    cmd->x8 += 4;
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftAction_80071F78(Fighter_GObj* gobj, FtCmdState* cmd)
{ // clang-format off
    nofralloc
/* 80071F78 0006EB58  80 A4 00 08 */	lwz r5, 8(r4)
/* 80071F7C 0006EB5C  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 80071F80 0006EB60  80 A5 00 00 */	lwz r5, 0(r5)
/* 80071F84 0006EB64  88 03 22 1E */	lbz r0, 0x221e(r3)
/* 80071F88 0006EB68  50 A0 1F 38 */	rlwimi r0, r5, 3, 0x1c, 0x1c
/* 80071F8C 0006EB6C  98 03 22 1E */	stb r0, 0x221e(r3)
/* 80071F90 0006EB70  80 64 00 08 */	lwz r3, 8(r4)
/* 80071F94 0006EB74  38 03 00 04 */	addi r0, r3, 4
/* 80071F98 0006EB78  90 04 00 08 */	stw r0, 8(r4)
/* 80071F9C 0006EB7C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftAction_80071F78(Fighter_GObj* gobj, FtCmdState* cmd)
{
    ftCo_Fighter* fp = gobj->user_data;
    fp->x221E_b4 = false;
    // M2C_FIELD(fp, u8*, 0x221E) =
    //     (u8) ((M2C_FIELD(fp, u8*, 0x221E) & ~8) | ((*cmd->x8 << 3) & 8));
    cmd->x8 += 4;
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftAction_80071FA0(Fighter_GObj* gobj, FtCmdState* cmd)
{ // clang-format off
    nofralloc
/* 80071FA0 0006EB80  80 A4 00 08 */	lwz r5, 8(r4)
/* 80071FA4 0006EB84  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 80071FA8 0006EB88  80 A5 00 00 */	lwz r5, 0(r5)
/* 80071FAC 0006EB8C  88 03 22 1E */	lbz r0, 0x221e(r3)
/* 80071FB0 0006EB90  50 A0 17 7A */	rlwimi r0, r5, 2, 0x1d, 0x1d
/* 80071FB4 0006EB94  98 03 22 1E */	stb r0, 0x221e(r3)
/* 80071FB8 0006EB98  80 64 00 08 */	lwz r3, 8(r4)
/* 80071FBC 0006EB9C  38 03 00 04 */	addi r0, r3, 4
/* 80071FC0 0006EBA0  90 04 00 08 */	stw r0, 8(r4)
/* 80071FC4 0006EBA4  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftAction_80071FA0(Fighter_GObj* gobj, FtCmdState* cmd)
{
    ftCo_Fighter* fp = gobj->user_data;
    fp->x221E_b5 = false;
    // M2C_FIELD(fp, u8*, 0x221E) =
    //     (u8) ((M2C_FIELD(fp, u8*, 0x221E) & ~4) | ((*cmd->x8 << 2) & 4));
    cmd->x8 += 4;
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
jtbl_t jtbl_803C08C0 = {
    lbl_80072210, lbl_80072228, lbl_80072240, lbl_80072258,
    lbl_80072270, lbl_80072288, lbl_800722A0,
};
#pragma push
asm void ftAction_80071FC8(Fighter_GObj* gobj, FtCmdState* cmd)
{ // clang-format off
    nofralloc
/* 80071FC8 0006EBA8  7C 08 02 A6 */	mflr r0
/* 80071FCC 0006EBAC  90 01 00 04 */	stw r0, 4(r1)
/* 80071FD0 0006EBB0  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 80071FD4 0006EBB4  BF 41 00 18 */	stmw r26, 0x18(r1)
/* 80071FD8 0006EBB8  7C 9A 23 78 */	mr r26, r4
/* 80071FDC 0006EBBC  80 C4 00 08 */	lwz r6, 8(r4)
/* 80071FE0 0006EBC0  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80071FE4 0006EBC4  A0 66 00 00 */	lhz r3, 0(r6)
/* 80071FE8 0006EBC8  38 06 00 04 */	addi r0, r6, 4
/* 80071FEC 0006EBCC  80 86 00 00 */	lwz r4, 0(r6)
/* 80071FF0 0006EBD0  54 65 F6 3E */	rlwinm r5, r3, 0x1e, 0x18, 0x1f
/* 80071FF4 0006EBD4  A3 86 00 02 */	lhz r28, 2(r6)
/* 80071FF8 0006EBD8  88 66 00 03 */	lbz r3, 3(r6)
/* 80071FFC 0006EBDC  54 84 B6 3E */	rlwinm r4, r4, 0x16, 0x18, 0x1f
/* 80072000 0006EBE0  3B C5 00 00 */	addi r30, r5, 0
/* 80072004 0006EBE4  90 1A 00 08 */	stw r0, 8(r26)
/* 80072008 0006EBE8  54 63 06 BE */	clrlwi r3, r3, 0x1a
/* 8007200C 0006EBEC  3B A4 00 00 */	addi r29, r4, 0
/* 80072010 0006EBF0  57 9C D7 3E */	rlwinm r28, r28, 0x1a, 0x1c, 0x1f
/* 80072014 0006EBF4  48 30 E5 6D */	bl HSD_Randi
/* 80072018 0006EBF8  2C 03 00 03 */	cmpwi r3, 3
/* 8007201C 0006EBFC  41 82 00 FC */	beq lbl_80072118
/* 80072020 0006EC00  40 80 00 1C */	bge lbl_8007203C
/* 80072024 0006EC04  2C 03 00 01 */	cmpwi r3, 1
/* 80072028 0006EC08  41 82 00 68 */	beq lbl_80072090
/* 8007202C 0006EC0C  40 80 00 A8 */	bge lbl_800720D4
/* 80072030 0006EC10  2C 03 00 00 */	cmpwi r3, 0
/* 80072034 0006EC14  40 80 00 18 */	bge lbl_8007204C
/* 80072038 0006EC18  48 00 01 AC */	b lbl_800721E4
lbl_8007203C:
/* 8007203C 0006EC1C  2C 03 00 05 */	cmpwi r3, 5
/* 80072040 0006EC20  41 82 01 60 */	beq lbl_800721A0
/* 80072044 0006EC24  40 80 01 A0 */	bge lbl_800721E4
/* 80072048 0006EC28  48 00 01 14 */	b lbl_8007215C
lbl_8007204C:
/* 8007204C 0006EC2C  80 7A 00 08 */	lwz r3, 8(r26)
/* 80072050 0006EC30  83 63 00 00 */	lwz r27, 0(r3)
/* 80072054 0006EC34  38 03 00 04 */	addi r0, r3, 4
/* 80072058 0006EC38  90 1A 00 08 */	stw r0, 8(r26)
/* 8007205C 0006EC3C  80 7A 00 08 */	lwz r3, 8(r26)
/* 80072060 0006EC40  38 03 00 04 */	addi r0, r3, 4
/* 80072064 0006EC44  90 1A 00 08 */	stw r0, 8(r26)
/* 80072068 0006EC48  80 7A 00 08 */	lwz r3, 8(r26)
/* 8007206C 0006EC4C  38 03 00 04 */	addi r0, r3, 4
/* 80072070 0006EC50  90 1A 00 08 */	stw r0, 8(r26)
/* 80072074 0006EC54  80 7A 00 08 */	lwz r3, 8(r26)
/* 80072078 0006EC58  38 03 00 04 */	addi r0, r3, 4
/* 8007207C 0006EC5C  90 1A 00 08 */	stw r0, 8(r26)
/* 80072080 0006EC60  80 7A 00 08 */	lwz r3, 8(r26)
/* 80072084 0006EC64  38 03 00 04 */	addi r0, r3, 4
/* 80072088 0006EC68  90 1A 00 08 */	stw r0, 8(r26)
/* 8007208C 0006EC6C  48 00 01 58 */	b lbl_800721E4
lbl_80072090:
/* 80072090 0006EC70  80 7A 00 08 */	lwz r3, 8(r26)
/* 80072094 0006EC74  38 03 00 04 */	addi r0, r3, 4
/* 80072098 0006EC78  90 1A 00 08 */	stw r0, 8(r26)
/* 8007209C 0006EC7C  80 7A 00 08 */	lwz r3, 8(r26)
/* 800720A0 0006EC80  83 63 00 00 */	lwz r27, 0(r3)
/* 800720A4 0006EC84  38 03 00 04 */	addi r0, r3, 4
/* 800720A8 0006EC88  90 1A 00 08 */	stw r0, 8(r26)
/* 800720AC 0006EC8C  80 7A 00 08 */	lwz r3, 8(r26)
/* 800720B0 0006EC90  38 03 00 04 */	addi r0, r3, 4
/* 800720B4 0006EC94  90 1A 00 08 */	stw r0, 8(r26)
/* 800720B8 0006EC98  80 7A 00 08 */	lwz r3, 8(r26)
/* 800720BC 0006EC9C  38 03 00 04 */	addi r0, r3, 4
/* 800720C0 0006ECA0  90 1A 00 08 */	stw r0, 8(r26)
/* 800720C4 0006ECA4  80 7A 00 08 */	lwz r3, 8(r26)
/* 800720C8 0006ECA8  38 03 00 04 */	addi r0, r3, 4
/* 800720CC 0006ECAC  90 1A 00 08 */	stw r0, 8(r26)
/* 800720D0 0006ECB0  48 00 01 14 */	b lbl_800721E4
lbl_800720D4:
/* 800720D4 0006ECB4  80 7A 00 08 */	lwz r3, 8(r26)
/* 800720D8 0006ECB8  38 03 00 04 */	addi r0, r3, 4
/* 800720DC 0006ECBC  90 1A 00 08 */	stw r0, 8(r26)
/* 800720E0 0006ECC0  80 7A 00 08 */	lwz r3, 8(r26)
/* 800720E4 0006ECC4  38 03 00 04 */	addi r0, r3, 4
/* 800720E8 0006ECC8  90 1A 00 08 */	stw r0, 8(r26)
/* 800720EC 0006ECCC  80 7A 00 08 */	lwz r3, 8(r26)
/* 800720F0 0006ECD0  83 63 00 00 */	lwz r27, 0(r3)
/* 800720F4 0006ECD4  38 03 00 04 */	addi r0, r3, 4
/* 800720F8 0006ECD8  90 1A 00 08 */	stw r0, 8(r26)
/* 800720FC 0006ECDC  80 7A 00 08 */	lwz r3, 8(r26)
/* 80072100 0006ECE0  38 03 00 04 */	addi r0, r3, 4
/* 80072104 0006ECE4  90 1A 00 08 */	stw r0, 8(r26)
/* 80072108 0006ECE8  80 7A 00 08 */	lwz r3, 8(r26)
/* 8007210C 0006ECEC  38 03 00 04 */	addi r0, r3, 4
/* 80072110 0006ECF0  90 1A 00 08 */	stw r0, 8(r26)
/* 80072114 0006ECF4  48 00 00 D0 */	b lbl_800721E4
lbl_80072118:
/* 80072118 0006ECF8  80 7A 00 08 */	lwz r3, 8(r26)
/* 8007211C 0006ECFC  38 03 00 04 */	addi r0, r3, 4
/* 80072120 0006ED00  90 1A 00 08 */	stw r0, 8(r26)
/* 80072124 0006ED04  80 7A 00 08 */	lwz r3, 8(r26)
/* 80072128 0006ED08  38 03 00 04 */	addi r0, r3, 4
/* 8007212C 0006ED0C  90 1A 00 08 */	stw r0, 8(r26)
/* 80072130 0006ED10  80 7A 00 08 */	lwz r3, 8(r26)
/* 80072134 0006ED14  38 03 00 04 */	addi r0, r3, 4
/* 80072138 0006ED18  90 1A 00 08 */	stw r0, 8(r26)
/* 8007213C 0006ED1C  80 7A 00 08 */	lwz r3, 8(r26)
/* 80072140 0006ED20  83 63 00 00 */	lwz r27, 0(r3)
/* 80072144 0006ED24  38 03 00 04 */	addi r0, r3, 4
/* 80072148 0006ED28  90 1A 00 08 */	stw r0, 8(r26)
/* 8007214C 0006ED2C  80 7A 00 08 */	lwz r3, 8(r26)
/* 80072150 0006ED30  38 03 00 04 */	addi r0, r3, 4
/* 80072154 0006ED34  90 1A 00 08 */	stw r0, 8(r26)
/* 80072158 0006ED38  48 00 00 8C */	b lbl_800721E4
lbl_8007215C:
/* 8007215C 0006ED3C  80 7A 00 08 */	lwz r3, 8(r26)
/* 80072160 0006ED40  38 03 00 04 */	addi r0, r3, 4
/* 80072164 0006ED44  90 1A 00 08 */	stw r0, 8(r26)
/* 80072168 0006ED48  80 7A 00 08 */	lwz r3, 8(r26)
/* 8007216C 0006ED4C  38 03 00 04 */	addi r0, r3, 4
/* 80072170 0006ED50  90 1A 00 08 */	stw r0, 8(r26)
/* 80072174 0006ED54  80 7A 00 08 */	lwz r3, 8(r26)
/* 80072178 0006ED58  38 03 00 04 */	addi r0, r3, 4
/* 8007217C 0006ED5C  90 1A 00 08 */	stw r0, 8(r26)
/* 80072180 0006ED60  80 7A 00 08 */	lwz r3, 8(r26)
/* 80072184 0006ED64  38 03 00 04 */	addi r0, r3, 4
/* 80072188 0006ED68  90 1A 00 08 */	stw r0, 8(r26)
/* 8007218C 0006ED6C  80 7A 00 08 */	lwz r3, 8(r26)
/* 80072190 0006ED70  83 63 00 00 */	lwz r27, 0(r3)
/* 80072194 0006ED74  38 03 00 04 */	addi r0, r3, 4
/* 80072198 0006ED78  90 1A 00 08 */	stw r0, 8(r26)
/* 8007219C 0006ED7C  48 00 00 48 */	b lbl_800721E4
lbl_800721A0:
/* 800721A0 0006ED80  80 7A 00 08 */	lwz r3, 8(r26)
/* 800721A4 0006ED84  38 03 00 04 */	addi r0, r3, 4
/* 800721A8 0006ED88  90 1A 00 08 */	stw r0, 8(r26)
/* 800721AC 0006ED8C  80 7A 00 08 */	lwz r3, 8(r26)
/* 800721B0 0006ED90  38 03 00 04 */	addi r0, r3, 4
/* 800721B4 0006ED94  90 1A 00 08 */	stw r0, 8(r26)
/* 800721B8 0006ED98  80 7A 00 08 */	lwz r3, 8(r26)
/* 800721BC 0006ED9C  38 03 00 04 */	addi r0, r3, 4
/* 800721C0 0006EDA0  90 1A 00 08 */	stw r0, 8(r26)
/* 800721C4 0006EDA4  80 7A 00 08 */	lwz r3, 8(r26)
/* 800721C8 0006EDA8  38 03 00 04 */	addi r0, r3, 4
/* 800721CC 0006EDAC  90 1A 00 08 */	stw r0, 8(r26)
/* 800721D0 0006EDB0  80 7A 00 08 */	lwz r3, 8(r26)
/* 800721D4 0006EDB4  38 03 00 04 */	addi r0, r3, 4
/* 800721D8 0006EDB8  90 1A 00 08 */	stw r0, 8(r26)
/* 800721DC 0006EDBC  80 7A 00 08 */	lwz r3, 8(r26)
/* 800721E0 0006EDC0  83 63 00 00 */	lwz r27, 0(r3)
lbl_800721E4:
/* 800721E4 0006EDC4  80 7A 00 08 */	lwz r3, 8(r26)
/* 800721E8 0006EDC8  28 1C 00 06 */	cmplwi r28, 6
/* 800721EC 0006EDCC  38 03 00 04 */	addi r0, r3, 4
/* 800721F0 0006EDD0  90 1A 00 08 */	stw r0, 8(r26)
/* 800721F4 0006EDD4  41 81 00 C0 */	bgt lbl_800722B4
/* 800721F8 0006EDD8  3C 60 80 3C */	lis r3, jtbl_803C08C0@ha
/* 800721FC 0006EDDC  38 63 08 C0 */	addi r3, r3, jtbl_803C08C0@l
/* 80072200 0006EDE0  57 80 10 3A */	slwi r0, r28, 2
/* 80072204 0006EDE4  7C 03 00 2E */	lwzx r0, r3, r0
/* 80072208 0006EDE8  7C 09 03 A6 */	mtctr r0
/* 8007220C 0006EDEC  4E 80 04 20 */	bctr
entry lbl_80072210
/* 80072210 0006EDF0  38 7F 00 00 */	addi r3, r31, 0
/* 80072214 0006EDF4  38 9B 00 00 */	addi r4, r27, 0
/* 80072218 0006EDF8  38 BE 00 00 */	addi r5, r30, 0
/* 8007221C 0006EDFC  38 DD 00 00 */	addi r6, r29, 0
/* 80072220 0006EE00  48 01 5F 29 */	bl ft_80088148
/* 80072224 0006EE04  48 00 00 90 */	b lbl_800722B4
entry lbl_80072228
/* 80072228 0006EE08  38 7F 00 00 */	addi r3, r31, 0
/* 8007222C 0006EE0C  38 9B 00 00 */	addi r4, r27, 0
/* 80072230 0006EE10  38 BE 00 00 */	addi r5, r30, 0
/* 80072234 0006EE14  38 DD 00 00 */	addi r6, r29, 0
/* 80072238 0006EE18  48 01 62 41 */	bl ft_80088478
/* 8007223C 0006EE1C  48 00 00 78 */	b lbl_800722B4
entry lbl_80072240
/* 80072240 0006EE20  38 7F 00 00 */	addi r3, r31, 0
/* 80072244 0006EE24  38 9B 00 00 */	addi r4, r27, 0
/* 80072248 0006EE28  38 BE 00 00 */	addi r5, r30, 0
/* 8007224C 0006EE2C  38 DD 00 00 */	addi r6, r29, 0
/* 80072250 0006EE30  48 01 5F 89 */	bl ft_800881D8
/* 80072254 0006EE34  48 00 00 60 */	b lbl_800722B4
entry lbl_80072258
/* 80072258 0006EE38  38 7F 00 00 */	addi r3, r31, 0
/* 8007225C 0006EE3C  38 9B 00 00 */	addi r4, r27, 0
/* 80072260 0006EE40  38 BE 00 00 */	addi r5, r30, 0
/* 80072264 0006EE44  38 DD 00 00 */	addi r6, r29, 0
/* 80072268 0006EE48  48 01 62 A9 */	bl ft_80088510
/* 8007226C 0006EE4C  48 00 00 48 */	b lbl_800722B4
entry lbl_80072270
/* 80072270 0006EE50  38 7F 00 00 */	addi r3, r31, 0
/* 80072274 0006EE54  38 9B 00 00 */	addi r4, r27, 0
/* 80072278 0006EE58  38 BE 00 00 */	addi r5, r30, 0
/* 8007227C 0006EE5C  38 DD 00 00 */	addi r6, r29, 0
/* 80072280 0006EE60  48 01 63 29 */	bl ft_800885A8
/* 80072284 0006EE64  48 00 00 30 */	b lbl_800722B4
entry lbl_80072288
/* 80072288 0006EE68  38 7F 00 00 */	addi r3, r31, 0
/* 8007228C 0006EE6C  38 9B 00 00 */	addi r4, r27, 0
/* 80072290 0006EE70  38 BE 00 00 */	addi r5, r30, 0
/* 80072294 0006EE74  38 DD 00 00 */	addi r6, r29, 0
/* 80072298 0006EE78  48 01 63 A9 */	bl ft_80088640
/* 8007229C 0006EE7C  48 00 00 18 */	b lbl_800722B4
entry lbl_800722A0
/* 800722A0 0006EE80  38 7F 00 00 */	addi r3, r31, 0
/* 800722A4 0006EE84  38 9B 00 00 */	addi r4, r27, 0
/* 800722A8 0006EE88  38 BE 00 00 */	addi r5, r30, 0
/* 800722AC 0006EE8C  38 DD 00 00 */	addi r6, r29, 0
/* 800722B0 0006EE90  48 01 60 79 */	bl ft_80088328
lbl_800722B4:
/* 800722B4 0006EE94  BB 41 00 18 */	lmw r26, 0x18(r1)
/* 800722B8 0006EE98  80 01 00 34 */	lwz r0, 0x34(r1)
/* 800722BC 0006EE9C  38 21 00 30 */	addi r1, r1, 0x30
/* 800722C0 0006EEA0  7C 08 03 A6 */	mtlr r0
/* 800722C4 0006EEA4  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftAction_80071FC8(Fighter_GObj* gobj, FtCmdState* cmd)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    int var_r27 = M2C_ERROR(saved_reg_r27);
    char* cmd_x8 = cmd->x8;
    void* fp = gobj->user_data;
    u8 temp_r30 = (u8) ((u16) M2C_FIELD(cmd_x8, u16*, 0) >> 2U);
    cmd->x8 = cmd_x8 + 4;
    {
        u8 temp_r29 = (u8) ((u32) M2C_FIELD(cmd_x8, u16*, 0) >> 0xAU);
        u32 temp_r28 = ((u16) M2C_FIELD(cmd_x8, u16*, 2) >> 6U) & 0xF;
        int temp_r3 = HSD_Randi(M2C_FIELD(cmd_x8, u8*, 3) & 0x3F);
        switch (temp_r3) { /* switch 1; irregular */
        case 0:            /* switch 1 */
        {
            char* cmd_x8 = cmd->x8;
            var_r27 = *cmd_x8;
            cmd->x8 = cmd_x8 + 4;
            cmd->x8 += 4;
            cmd->x8 += 4;
            cmd->x8 += 4;
            cmd->x8 += 4;
            break;
        }
        case 1: /* switch 1 */
            cmd->x8 += 4;
            {
                char* cmd_x8 = cmd->x8;
                var_r27 = *cmd_x8;
                cmd->x8 = cmd_x8 + 4;
            }
            cmd->x8 += 4;
            cmd->x8 += 4;
            cmd->x8 += 4;
            break;
        case 2: /* switch 1 */
            cmd->x8 += 4;
            cmd->x8 += 4;
            {
                char* cmd_x8 = cmd->x8;
                var_r27 = *cmd_x8;
                cmd->x8 = cmd_x8 + 4;
            }
            cmd->x8 += 4;
            cmd->x8 += 4;
            break;
        case 3: /* switch 1 */
            cmd->x8 += 4;
            cmd->x8 += 4;
            cmd->x8 += 4;
            {
                char* cmd_x8 = cmd->x8;
                var_r27 = *cmd_x8;
                cmd->x8 = cmd_x8 + 4;
            }
            cmd->x8 += 4;
            break;
        case 4: /* switch 1 */
            cmd->x8 += 4;
            cmd->x8 += 4;
            cmd->x8 += 4;
            cmd->x8 += 4;
            {
                char* cmd_x8 = cmd->x8;
                var_r27 = *cmd_x8;
                cmd->x8 = cmd_x8 + 4;
            }
            break;
        case 5: /* switch 1 */
            cmd->x8 += 4;
            cmd->x8 += 4;
            cmd->x8 += 4;
            cmd->x8 += 4;
            cmd->x8 += 4;
            var_r27 = *cmd->x8;
            break;
        }
        cmd->x8 += 4;
        switch (temp_r28) {
        case 0:
            ft_80088148(fp, var_r27, (int) temp_r30, (int) temp_r29);
            return;
        case 1:
            ft_80088478(fp, var_r27, (int) temp_r30, (int) temp_r29);
            return;
        case 2:
            ft_800881D8(fp, (u32) var_r27, (u32) temp_r30, (u32) temp_r29);
            return;
        case 3:
            ft_80088510(fp, var_r27, temp_r30, temp_r29);
            return;
        case 4:
            ft_800885A8(fp, var_r27, temp_r30, temp_r29);
            return;
        case 5:
            ft_80088640(fp, var_r27, (int) temp_r30, (int) temp_r29);
            return;
        case 6:
            ft_80088328(fp, var_r27, (int) temp_r30, (int) temp_r29);
        /* fallthrough */
        default:
            return;
        }
    }
}
#endif

void ftAction_800722C8(Fighter_GObj* gobj, FtCmdState* cmd)
{
    cmd->x8 += 4;
    cmd->x8 += 4;
    cmd->x8 += 4;
    cmd->x8 += 4;
    cmd->x8 += 4;
    cmd->x8 += 4;
    cmd->x8 += 4;
}

#if defined(MUST_MATCH) && !defined(WIP)
jtbl_t jtbl_803C08DC = {
    lbl_80072408, lbl_8007243C, lbl_80072480, lbl_80072530,
    lbl_80072574, lbl_800725B8, lbl_800725FC,
};
#pragma push
asm void ftAction_80072320(Fighter_GObj* gobj, FtCmdState* cmd)
{ // clang-format off
    nofralloc
/* 80072320 0006EF00  7C 08 02 A6 */	mflr r0
/* 80072324 0006EF04  90 01 00 04 */	stw r0, 4(r1)
/* 80072328 0006EF08  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 8007232C 0006EF0C  DB E1 00 38 */	stfd f31, 0x38(r1)
/* 80072330 0006EF10  BF 61 00 24 */	stmw r27, 0x24(r1)
/* 80072334 0006EF14  7C 9C 23 78 */	mr r28, r4
/* 80072338 0006EF18  7C 7B 1B 78 */	mr r27, r3
/* 8007233C 0006EF1C  80 84 00 08 */	lwz r4, 8(r4)
/* 80072340 0006EF20  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80072344 0006EF24  88 04 00 03 */	lbz r0, 3(r4)
/* 80072348 0006EF28  A3 C4 00 00 */	lhz r30, 0(r4)
/* 8007234C 0006EF2C  2C 00 00 02 */	cmpwi r0, 2
/* 80072350 0006EF30  8B A4 00 02 */	lbz r29, 2(r4)
/* 80072354 0006EF34  57 DE 05 BE */	clrlwi r30, r30, 0x16
/* 80072358 0006EF38  41 82 00 34 */	beq lbl_8007238C
/* 8007235C 0006EF3C  40 80 00 14 */	bge lbl_80072370
/* 80072360 0006EF40  2C 00 00 00 */	cmpwi r0, 0
/* 80072364 0006EF44  41 82 00 18 */	beq lbl_8007237C
/* 80072368 0006EF48  40 80 00 1C */	bge lbl_80072384
/* 8007236C 0006EF4C  48 00 00 2C */	b lbl_80072398
lbl_80072370:
/* 80072370 0006EF50  2C 00 00 04 */	cmpwi r0, 4
/* 80072374 0006EF54  40 80 00 24 */	bge lbl_80072398
/* 80072378 0006EF58  48 00 00 1C */	b lbl_80072394
lbl_8007237C:
/* 8007237C 0006EF5C  C3 E2 88 D8 */	lfs f31, ftAction_804D82B8
/* 80072380 0006EF60  48 00 00 18 */	b lbl_80072398
lbl_80072384:
/* 80072384 0006EF64  C3 E2 88 DC */	lfs f31, ftAction_804D82BC
/* 80072388 0006EF68  48 00 00 10 */	b lbl_80072398
lbl_8007238C:
/* 8007238C 0006EF6C  C3 E2 88 E0 */	lfs f31, ftAction_804D82C0
/* 80072390 0006EF70  48 00 00 08 */	b lbl_80072398
lbl_80072394:
/* 80072394 0006EF74  C3 FF 00 2C */	lfs f31, 0x2c(r31)
lbl_80072398:
/* 80072398 0006EF78  80 9C 00 08 */	lwz r4, 8(r28)
/* 8007239C 0006EF7C  38 7F 00 00 */	addi r3, r31, 0
/* 800723A0 0006EF80  38 04 00 04 */	addi r0, r4, 4
/* 800723A4 0006EF84  90 1C 00 08 */	stw r0, 8(r28)
/* 800723A8 0006EF88  80 9C 00 08 */	lwz r4, 8(r28)
/* 800723AC 0006EF8C  80 84 00 00 */	lwz r4, 0(r4)
/* 800723B0 0006EF90  48 01 59 5D */	bl ft_80087D0C
/* 800723B4 0006EF94  80 9C 00 08 */	lwz r4, 8(r28)
/* 800723B8 0006EF98  7C 65 1B 78 */	mr r5, r3
/* 800723BC 0006EF9C  28 1D 00 06 */	cmplwi r29, 6
/* 800723C0 0006EFA0  38 04 00 04 */	addi r0, r4, 4
/* 800723C4 0006EFA4  90 1C 00 08 */	stw r0, 8(r28)
/* 800723C8 0006EFA8  80 7C 00 08 */	lwz r3, 8(r28)
/* 800723CC 0006EFAC  A1 43 00 02 */	lhz r10, 2(r3)
/* 800723D0 0006EFB0  38 03 00 04 */	addi r0, r3, 4
/* 800723D4 0006EFB4  90 1C 00 08 */	stw r0, 8(r28)
/* 800723D8 0006EFB8  80 7C 00 08 */	lwz r3, 8(r28)
/* 800723DC 0006EFBC  89 03 00 02 */	lbz r8, 2(r3)
/* 800723E0 0006EFC0  38 03 00 04 */	addi r0, r3, 4
/* 800723E4 0006EFC4  89 23 00 03 */	lbz r9, 3(r3)
/* 800723E8 0006EFC8  90 1C 00 08 */	stw r0, 8(r28)
/* 800723EC 0006EFCC  41 81 02 BC */	bgt lbl_800726A8
/* 800723F0 0006EFD0  3C 60 80 3C */	lis r3, jtbl_803C08DC@ha
/* 800723F4 0006EFD4  38 63 08 DC */	addi r3, r3, jtbl_803C08DC@l
/* 800723F8 0006EFD8  57 A0 10 3A */	slwi r0, r29, 2
/* 800723FC 0006EFDC  7C 03 00 2E */	lwzx r0, r3, r0
/* 80072400 0006EFE0  7C 09 03 A6 */	mtctr r0
/* 80072404 0006EFE4  4E 80 04 20 */	bctr
entry lbl_80072408
/* 80072408 0006EFE8  38 00 00 00 */	li r0, 0
/* 8007240C 0006EFEC  FC 20 F8 90 */	fmr f1, f31
/* 80072410 0006EFF0  90 01 00 08 */	stw r0, 8(r1)
/* 80072414 0006EFF4  38 00 FF FF */	li r0, -1
/* 80072418 0006EFF8  38 7B 00 00 */	addi r3, r27, 0
/* 8007241C 0006EFFC  90 01 00 0C */	stw r0, 0xc(r1)
/* 80072420 0006F000  38 9E 00 00 */	addi r4, r30, 0
/* 80072424 0006F004  38 C0 00 7F */	li r6, 0x7f
/* 80072428 0006F008  38 E0 00 7F */	li r7, 0x7f
/* 8007242C 0006F00C  4B FB 3F BD */	bl lbAudioAx_800263E8
/* 80072430 0006F010  4B FB 40 B5 */	bl lbAudioAx_800264E4
/* 80072434 0006F014  90 7F 21 60 */	stw r3, 0x2160(r31)
/* 80072438 0006F018  48 00 02 70 */	b lbl_800726A8
entry lbl_8007243C
/* 8007243C 0006F01C  88 7F 22 1F */	lbz r3, 0x221f(r31)
/* 80072440 0006F020  FC 20 F8 90 */	fmr f1, f31
/* 80072444 0006F024  88 9F 00 0C */	lbz r4, 0xc(r31)
/* 80072448 0006F028  38 00 FF FF */	li r0, -1
/* 8007244C 0006F02C  54 63 EF FE */	rlwinm r3, r3, 0x1d, 0x1f, 0x1f
/* 80072450 0006F030  7C 64 1A 14 */	add r3, r4, r3
/* 80072454 0006F034  38 63 00 36 */	addi r3, r3, 0x36
/* 80072458 0006F038  90 61 00 08 */	stw r3, 8(r1)
/* 8007245C 0006F03C  38 7B 00 00 */	addi r3, r27, 0
/* 80072460 0006F040  38 9E 00 00 */	addi r4, r30, 0
/* 80072464 0006F044  90 01 00 0C */	stw r0, 0xc(r1)
/* 80072468 0006F048  38 C0 00 7F */	li r6, 0x7f
/* 8007246C 0006F04C  38 E0 00 7F */	li r7, 0x7f
/* 80072470 0006F050  4B FB 3F 79 */	bl lbAudioAx_800263E8
/* 80072474 0006F054  4B FB 40 71 */	bl lbAudioAx_800264E4
/* 80072478 0006F058  90 7F 21 4C */	stw r3, 0x214c(r31)
/* 8007247C 0006F05C  48 00 02 2C */	b lbl_800726A8
entry lbl_80072480
/* 80072480 0006F060  88 1F 22 25 */	lbz r0, 0x2225(r31)
/* 80072484 0006F064  54 00 FF FF */	rlwinm. r0, r0, 0x1f, 0x1f, 0x1f
/* 80072488 0006F068  40 82 00 48 */	bne lbl_800724D0
/* 8007248C 0006F06C  88 7F 22 1F */	lbz r3, 0x221f(r31)
/* 80072490 0006F070  FC 20 F8 90 */	fmr f1, f31
/* 80072494 0006F074  88 9F 00 0C */	lbz r4, 0xc(r31)
/* 80072498 0006F078  38 00 FF FF */	li r0, -1
/* 8007249C 0006F07C  54 63 EF FE */	rlwinm r3, r3, 0x1d, 0x1f, 0x1f
/* 800724A0 0006F080  7C 64 1A 14 */	add r3, r4, r3
/* 800724A4 0006F084  38 63 00 1E */	addi r3, r3, 0x1e
/* 800724A8 0006F088  90 61 00 08 */	stw r3, 8(r1)
/* 800724AC 0006F08C  38 7B 00 00 */	addi r3, r27, 0
/* 800724B0 0006F090  38 9E 00 00 */	addi r4, r30, 0
/* 800724B4 0006F094  90 01 00 0C */	stw r0, 0xc(r1)
/* 800724B8 0006F098  38 C0 00 7F */	li r6, 0x7f
/* 800724BC 0006F09C  38 E0 00 7F */	li r7, 0x7f
/* 800724C0 0006F0A0  4B FB 3F 29 */	bl lbAudioAx_800263E8
/* 800724C4 0006F0A4  4B FB 40 21 */	bl lbAudioAx_800264E4
/* 800724C8 0006F0A8  90 7F 21 44 */	stw r3, 0x2144(r31)
/* 800724CC 0006F0AC  48 00 01 DC */	b lbl_800726A8
lbl_800724D0:
/* 800724D0 0006F0B0  80 1F 00 04 */	lwz r0, 4(r31)
/* 800724D4 0006F0B4  2C 00 00 18 */	cmpwi r0, 0x18
/* 800724D8 0006F0B8  41 82 00 14 */	beq lbl_800724EC
/* 800724DC 0006F0BC  40 80 01 CC */	bge lbl_800726A8
/* 800724E0 0006F0C0  2C 00 00 0D */	cmpwi r0, 0xd
/* 800724E4 0006F0C4  41 82 00 08 */	beq lbl_800724EC
/* 800724E8 0006F0C8  48 00 01 C0 */	b lbl_800726A8
lbl_800724EC:
/* 800724EC 0006F0CC  88 7F 22 1F */	lbz r3, 0x221f(r31)
/* 800724F0 0006F0D0  FC 20 F8 90 */	fmr f1, f31
/* 800724F4 0006F0D4  88 9F 00 0C */	lbz r4, 0xc(r31)
/* 800724F8 0006F0D8  38 00 FF FF */	li r0, -1
/* 800724FC 0006F0DC  54 63 EF FE */	rlwinm r3, r3, 0x1d, 0x1f, 0x1f
/* 80072500 0006F0E0  7C 64 1A 14 */	add r3, r4, r3
/* 80072504 0006F0E4  38 63 00 1E */	addi r3, r3, 0x1e
/* 80072508 0006F0E8  90 61 00 08 */	stw r3, 8(r1)
/* 8007250C 0006F0EC  38 7B 00 00 */	addi r3, r27, 0
/* 80072510 0006F0F0  38 9E 00 00 */	addi r4, r30, 0
/* 80072514 0006F0F4  90 01 00 0C */	stw r0, 0xc(r1)
/* 80072518 0006F0F8  38 C0 00 7F */	li r6, 0x7f
/* 8007251C 0006F0FC  38 E0 00 7F */	li r7, 0x7f
/* 80072520 0006F100  4B FB 3E C9 */	bl lbAudioAx_800263E8
/* 80072524 0006F104  4B FB 3F C1 */	bl lbAudioAx_800264E4
/* 80072528 0006F108  90 7F 21 44 */	stw r3, 0x2144(r31)
/* 8007252C 0006F10C  48 00 01 7C */	b lbl_800726A8
entry lbl_80072530
/* 80072530 0006F110  88 7F 22 1F */	lbz r3, 0x221f(r31)
/* 80072534 0006F114  FC 20 F8 90 */	fmr f1, f31
/* 80072538 0006F118  88 9F 00 0C */	lbz r4, 0xc(r31)
/* 8007253C 0006F11C  38 00 FF FF */	li r0, -1
/* 80072540 0006F120  54 63 EF FE */	rlwinm r3, r3, 0x1d, 0x1f, 0x1f
/* 80072544 0006F124  7C 64 1A 14 */	add r3, r4, r3
/* 80072548 0006F128  38 63 00 42 */	addi r3, r3, 0x42
/* 8007254C 0006F12C  90 61 00 08 */	stw r3, 8(r1)
/* 80072550 0006F130  38 7B 00 00 */	addi r3, r27, 0
/* 80072554 0006F134  38 9E 00 00 */	addi r4, r30, 0
/* 80072558 0006F138  90 01 00 0C */	stw r0, 0xc(r1)
/* 8007255C 0006F13C  38 C0 00 7F */	li r6, 0x7f
/* 80072560 0006F140  38 E0 00 7F */	li r7, 0x7f
/* 80072564 0006F144  4B FB 3E 85 */	bl lbAudioAx_800263E8
/* 80072568 0006F148  4B FB 3F 7D */	bl lbAudioAx_800264E4
/* 8007256C 0006F14C  90 7F 21 50 */	stw r3, 0x2150(r31)
/* 80072570 0006F150  48 00 01 38 */	b lbl_800726A8
entry lbl_80072574
/* 80072574 0006F154  88 7F 22 1F */	lbz r3, 0x221f(r31)
/* 80072578 0006F158  FC 20 F8 90 */	fmr f1, f31
/* 8007257C 0006F15C  88 9F 00 0C */	lbz r4, 0xc(r31)
/* 80072580 0006F160  38 00 FF FF */	li r0, -1
/* 80072584 0006F164  54 63 EF FE */	rlwinm r3, r3, 0x1d, 0x1f, 0x1f
/* 80072588 0006F168  7C 64 1A 14 */	add r3, r4, r3
/* 8007258C 0006F16C  38 63 00 4E */	addi r3, r3, 0x4e
/* 80072590 0006F170  90 61 00 08 */	stw r3, 8(r1)
/* 80072594 0006F174  38 7B 00 00 */	addi r3, r27, 0
/* 80072598 0006F178  38 9E 00 00 */	addi r4, r30, 0
/* 8007259C 0006F17C  90 01 00 0C */	stw r0, 0xc(r1)
/* 800725A0 0006F180  38 C0 00 7F */	li r6, 0x7f
/* 800725A4 0006F184  38 E0 00 7F */	li r7, 0x7f
/* 800725A8 0006F188  4B FB 3E 41 */	bl lbAudioAx_800263E8
/* 800725AC 0006F18C  4B FB 3F 39 */	bl lbAudioAx_800264E4
/* 800725B0 0006F190  90 7F 21 54 */	stw r3, 0x2154(r31)
/* 800725B4 0006F194  48 00 00 F4 */	b lbl_800726A8
entry lbl_800725B8
/* 800725B8 0006F198  88 7F 22 1F */	lbz r3, 0x221f(r31)
/* 800725BC 0006F19C  FC 20 F8 90 */	fmr f1, f31
/* 800725C0 0006F1A0  88 9F 00 0C */	lbz r4, 0xc(r31)
/* 800725C4 0006F1A4  38 00 FF FF */	li r0, -1
/* 800725C8 0006F1A8  54 63 EF FE */	rlwinm r3, r3, 0x1d, 0x1f, 0x1f
/* 800725CC 0006F1AC  7C 64 1A 14 */	add r3, r4, r3
/* 800725D0 0006F1B0  38 63 00 5A */	addi r3, r3, 0x5a
/* 800725D4 0006F1B4  90 61 00 08 */	stw r3, 8(r1)
/* 800725D8 0006F1B8  38 7B 00 00 */	addi r3, r27, 0
/* 800725DC 0006F1BC  38 9E 00 00 */	addi r4, r30, 0
/* 800725E0 0006F1C0  90 01 00 0C */	stw r0, 0xc(r1)
/* 800725E4 0006F1C4  38 C0 00 7F */	li r6, 0x7f
/* 800725E8 0006F1C8  38 E0 00 7F */	li r7, 0x7f
/* 800725EC 0006F1CC  4B FB 3D FD */	bl lbAudioAx_800263E8
/* 800725F0 0006F1D0  4B FB 3E F5 */	bl lbAudioAx_800264E4
/* 800725F4 0006F1D4  90 7F 21 58 */	stw r3, 0x2158(r31)
/* 800725F8 0006F1D8  48 00 00 B0 */	b lbl_800726A8
entry lbl_800725FC
/* 800725FC 0006F1DC  88 1F 22 25 */	lbz r0, 0x2225(r31)
/* 80072600 0006F1E0  54 00 FF FF */	rlwinm. r0, r0, 0x1f, 0x1f, 0x1f
/* 80072604 0006F1E4  40 82 00 48 */	bne lbl_8007264C
/* 80072608 0006F1E8  88 7F 22 1F */	lbz r3, 0x221f(r31)
/* 8007260C 0006F1EC  FC 20 F8 90 */	fmr f1, f31
/* 80072610 0006F1F0  88 9F 00 0C */	lbz r4, 0xc(r31)
/* 80072614 0006F1F4  38 00 FF FF */	li r0, -1
/* 80072618 0006F1F8  54 63 EF FE */	rlwinm r3, r3, 0x1d, 0x1f, 0x1f
/* 8007261C 0006F1FC  7C 64 1A 14 */	add r3, r4, r3
/* 80072620 0006F200  38 63 00 2A */	addi r3, r3, 0x2a
/* 80072624 0006F204  90 61 00 08 */	stw r3, 8(r1)
/* 80072628 0006F208  38 7B 00 00 */	addi r3, r27, 0
/* 8007262C 0006F20C  38 9E 00 00 */	addi r4, r30, 0
/* 80072630 0006F210  90 01 00 0C */	stw r0, 0xc(r1)
/* 80072634 0006F214  38 C0 00 7F */	li r6, 0x7f
/* 80072638 0006F218  38 E0 00 7F */	li r7, 0x7f
/* 8007263C 0006F21C  4B FB 3D AD */	bl lbAudioAx_800263E8
/* 80072640 0006F220  4B FB 3E A5 */	bl lbAudioAx_800264E4
/* 80072644 0006F224  90 7F 21 48 */	stw r3, 0x2148(r31)
/* 80072648 0006F228  48 00 00 60 */	b lbl_800726A8
lbl_8007264C:
/* 8007264C 0006F22C  80 1F 00 04 */	lwz r0, 4(r31)
/* 80072650 0006F230  2C 00 00 18 */	cmpwi r0, 0x18
/* 80072654 0006F234  41 82 00 14 */	beq lbl_80072668
/* 80072658 0006F238  40 80 00 50 */	bge lbl_800726A8
/* 8007265C 0006F23C  2C 00 00 0D */	cmpwi r0, 0xd
/* 80072660 0006F240  41 82 00 08 */	beq lbl_80072668
/* 80072664 0006F244  48 00 00 44 */	b lbl_800726A8
lbl_80072668:
/* 80072668 0006F248  88 7F 22 1F */	lbz r3, 0x221f(r31)
/* 8007266C 0006F24C  FC 20 F8 90 */	fmr f1, f31
/* 80072670 0006F250  88 9F 00 0C */	lbz r4, 0xc(r31)
/* 80072674 0006F254  38 00 FF FF */	li r0, -1
/* 80072678 0006F258  54 63 EF FE */	rlwinm r3, r3, 0x1d, 0x1f, 0x1f
/* 8007267C 0006F25C  7C 64 1A 14 */	add r3, r4, r3
/* 80072680 0006F260  38 63 00 2A */	addi r3, r3, 0x2a
/* 80072684 0006F264  90 61 00 08 */	stw r3, 8(r1)
/* 80072688 0006F268  38 7B 00 00 */	addi r3, r27, 0
/* 8007268C 0006F26C  38 9E 00 00 */	addi r4, r30, 0
/* 80072690 0006F270  90 01 00 0C */	stw r0, 0xc(r1)
/* 80072694 0006F274  38 C0 00 7F */	li r6, 0x7f
/* 80072698 0006F278  38 E0 00 7F */	li r7, 0x7f
/* 8007269C 0006F27C  4B FB 3D 4D */	bl lbAudioAx_800263E8
/* 800726A0 0006F280  4B FB 3E 45 */	bl lbAudioAx_800264E4
/* 800726A4 0006F284  90 7F 21 48 */	stw r3, 0x2148(r31)
lbl_800726A8:
/* 800726A8 0006F288  BB 61 00 24 */	lmw r27, 0x24(r1)
/* 800726AC 0006F28C  80 01 00 44 */	lwz r0, 0x44(r1)
/* 800726B0 0006F290  CB E1 00 38 */	lfd f31, 0x38(r1)
/* 800726B4 0006F294  38 21 00 40 */	addi r1, r1, 0x40
/* 800726B8 0006F298  7C 08 03 A6 */	mtlr r0
/* 800726BC 0006F29C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-but-set-variable"
#endif

void ftAction_80072320(Fighter_GObj* gobj, FtCmdState* cmd)
{
    int spC;
    int sp8;
    float var_f31;
    int temp_r0_2;
    int temp_r0_3;
    int temp_r30;
    int temp_r5;
    char* temp_r4;
    u8 temp_r0;
    u8 temp_r29;
    void* temp_r31;

    var_f31 = M2C_ERROR(saved_reg_f31);
    temp_r4 = cmd->x8;
    temp_r31 = gobj->user_data;
    temp_r0 = M2C_FIELD(temp_r4, u8*, 3);
    temp_r29 = M2C_FIELD(temp_r4, u8*, 2);
    temp_r30 = M2C_FIELD(temp_r4, u16*, 0) & 0x3FF;
    switch ((int) temp_r0) { /* switch 1; irregular */
    case 0:                  /* switch 1 */
        var_f31 = 0.0f;
        break;
    case 1: /* switch 1 */
        var_f31 = 1.0f;
        break;
    case 2: /* switch 1 */
        var_f31 = -1.0f;
        break;
    case 3: /* switch 1 */
        var_f31 = M2C_FIELD(temp_r31, float*, 0x2C);
        break;
    }
    cmd->x8 += 4;
    temp_r5 = ft_80087D0C((Fighter*) temp_r31, M2C_FIELD(cmd->x8, int*, 0));
    cmd->x8 += 4;
    cmd->x8 += 4;
    cmd->x8 += 4;
    switch (temp_r29) {
    case 0:
        sp8 = 0;
        spC = -1;
        lbAudioAx_800263E8(gobj, temp_r30, temp_r5, 0x7F, var_f31);
        M2C_FIELD(temp_r31, int*, 0x2160) = lbAudioAx_800264E4();
        return;
    case 1:
        sp8 = M2C_FIELD(temp_r31, u8*, 0xC) +
              (((u8) M2C_FIELD(temp_r31, u8*, 0x221F) >> 3U) & 1) + 0x36;
        spC = -1;
        lbAudioAx_800263E8(gobj, temp_r30, temp_r5, 0x7F, var_f31);
        M2C_FIELD(temp_r31, int*, 0x214C) = lbAudioAx_800264E4();
        return;
    case 2:
        if (!(((u8) M2C_FIELD(temp_r31, u8*, 0x2225) >> 1U) & 1)) {
            sp8 = M2C_FIELD(temp_r31, u8*, 0xC) +
                  (((u8) M2C_FIELD(temp_r31, u8*, 0x221F) >> 3U) & 1) + 0x1E;
            spC = -1;
            lbAudioAx_800263E8(gobj, temp_r30, temp_r5, 0x7F, var_f31);
            M2C_FIELD(temp_r31, int*, 0x2144) = lbAudioAx_800264E4();
            return;
        }
        temp_r0_2 = M2C_FIELD(temp_r31, int*, 4);
        if (temp_r0_2 != 0x18) {
            if (temp_r0_2 < 0x18) {
                if (temp_r0_2 != 0xD) {
                    return;
                }
                goto block_21;
            }
        default:
            return;
        }
    block_21:
        sp8 = M2C_FIELD(temp_r31, u8*, 0xC) +
              (((u8) M2C_FIELD(temp_r31, u8*, 0x221F) >> 3U) & 1) + 0x1E;
        spC = -1;
        lbAudioAx_800263E8(gobj, temp_r30, temp_r5, 0x7F, var_f31);
        M2C_FIELD(temp_r31, int*, 0x2144) = lbAudioAx_800264E4();
        return;
    case 3:
        sp8 = M2C_FIELD(temp_r31, u8*, 0xC) +
              (((u8) M2C_FIELD(temp_r31, u8*, 0x221F) >> 3U) & 1) + 0x42;
        spC = -1;
        lbAudioAx_800263E8(gobj, temp_r30, temp_r5, 0x7F, var_f31);
        M2C_FIELD(temp_r31, int*, 0x2150) = lbAudioAx_800264E4();
        return;
    case 4:
        sp8 = M2C_FIELD(temp_r31, u8*, 0xC) +
              (((u8) M2C_FIELD(temp_r31, u8*, 0x221F) >> 3U) & 1) + 0x4E;
        spC = -1;
        lbAudioAx_800263E8(gobj, temp_r30, temp_r5, 0x7F, var_f31);
        M2C_FIELD(temp_r31, int*, 0x2154) = lbAudioAx_800264E4();
        return;
    case 5:
        sp8 = M2C_FIELD(temp_r31, u8*, 0xC) +
              (((u8) M2C_FIELD(temp_r31, u8*, 0x221F) >> 3U) & 1) + 0x5A;
        spC = -1;
        lbAudioAx_800263E8(gobj, temp_r30, temp_r5, 0x7F, var_f31);
        M2C_FIELD(temp_r31, int*, 0x2158) = lbAudioAx_800264E4();
        return;
    case 6:
        if (!(((u8) M2C_FIELD(temp_r31, u8*, 0x2225) >> 1U) & 1)) {
            sp8 = M2C_FIELD(temp_r31, u8*, 0xC) +
                  (((u8) M2C_FIELD(temp_r31, u8*, 0x221F) >> 3U) & 1) + 0x2A;
            spC = -1;
            lbAudioAx_800263E8(gobj, temp_r30, temp_r5, 0x7F, var_f31);
            M2C_FIELD(temp_r31, int*, 0x2148) = lbAudioAx_800264E4();
            return;
        }
        temp_r0_3 = M2C_FIELD(temp_r31, int*, 4);
        if (temp_r0_3 != 0x18) {
            if (temp_r0_3 < 0x18) {
                if (temp_r0_3 != 0xD) {
                    return;
                }
                goto block_31;
            }
        } else {
        block_31:
            sp8 = M2C_FIELD(temp_r31, u8*, 0xC) +
                  (((u8) M2C_FIELD(temp_r31, u8*, 0x221F) >> 3U) & 1) + 0x2A;
            spC = -1;
            lbAudioAx_800263E8(gobj, temp_r30, temp_r5, 0x7F, var_f31);
            M2C_FIELD(temp_r31, int*, 0x2148) = lbAudioAx_800264E4();
        }
        break;
    }
}
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
#endif

void ftAction_800726C0(Fighter_GObj* gobj, FtCmdState* cmd)
{
    cmd->x8 += 4;
    cmd->x8 += 4;
    cmd->x8 += 4;
    cmd->x8 += 4;
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftAction_800726F4(Fighter_GObj* gobj, FtCmdState* cmd)
{ // clang-format off
    nofralloc
/* 800726F4 0006F2D4  7C 08 02 A6 */	mflr r0
/* 800726F8 0006F2D8  90 01 00 04 */	stw r0, 4(r1)
/* 800726FC 0006F2DC  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 80072700 0006F2E0  93 E1 00 24 */	stw r31, 0x24(r1)
/* 80072704 0006F2E4  3F E0 43 30 */	lis r31, 0x4330
/* 80072708 0006F2E8  93 C1 00 20 */	stw r30, 0x20(r1)
/* 8007270C 0006F2EC  7C 9E 23 78 */	mr r30, r4
/* 80072710 0006F2F0  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 80072714 0006F2F4  3B A3 00 00 */	addi r29, r3, 0
/* 80072718 0006F2F8  80 A4 00 08 */	lwz r5, 8(r4)
/* 8007271C 0006F2FC  C8 22 88 D0 */	lfd f1, ftAction_804D82B0
/* 80072720 0006F300  A8 85 00 00 */	lha r4, 0(r5)
/* 80072724 0006F304  A8 05 00 02 */	lha r0, 2(r5)
/* 80072728 0006F308  54 84 B8 0E */	rlwinm r4, r4, 0x17, 0, 7
/* 8007272C 0006F30C  7C 84 CE 70 */	srawi r4, r4, 0x19
/* 80072730 0006F310  54 00 A8 16 */	rlwinm r0, r0, 0x15, 0, 0xb
/* 80072734 0006F314  7C 00 AE 70 */	srawi r0, r0, 0x15
/* 80072738 0006F318  7C 00 07 34 */	extsh r0, r0
/* 8007273C 0006F31C  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 80072740 0006F320  90 01 00 14 */	stw r0, 0x14(r1)
/* 80072744 0006F324  93 E1 00 10 */	stw r31, 0x10(r1)
/* 80072748 0006F328  C8 01 00 10 */	lfd f0, 0x10(r1)
/* 8007274C 0006F32C  EC 20 08 28 */	fsubs f1, f0, f1
/* 80072750 0006F330  4B FF DD A1 */	bl ftAnim_800704F0
/* 80072754 0006F334  80 BE 00 08 */	lwz r5, 8(r30)
/* 80072758 0006F338  88 05 00 00 */	lbz r0, 0(r5)
/* 8007275C 0006F33C  54 00 FF FF */	rlwinm. r0, r0, 0x1f, 0x1f, 0x1f
/* 80072760 0006F340  41 82 00 40 */	beq lbl_800727A0
/* 80072764 0006F344  80 85 00 00 */	lwz r4, 0(r5)
/* 80072768 0006F348  7F A3 EB 78 */	mr r3, r29
/* 8007276C 0006F34C  A8 05 00 02 */	lha r0, 2(r5)
/* 80072770 0006F350  54 84 70 0E */	rlwinm r4, r4, 0xe, 0, 7
/* 80072774 0006F354  C8 22 88 D0 */	lfd f1, ftAction_804D82B0
/* 80072778 0006F358  7C 84 CE 70 */	srawi r4, r4, 0x19
/* 8007277C 0006F35C  54 00 A8 16 */	rlwinm r0, r0, 0x15, 0, 0xb
/* 80072780 0006F360  7C 00 AE 70 */	srawi r0, r0, 0x15
/* 80072784 0006F364  7C 00 07 34 */	extsh r0, r0
/* 80072788 0006F368  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 8007278C 0006F36C  90 01 00 14 */	stw r0, 0x14(r1)
/* 80072790 0006F370  93 E1 00 10 */	stw r31, 0x10(r1)
/* 80072794 0006F374  C8 01 00 10 */	lfd f0, 0x10(r1)
/* 80072798 0006F378  EC 20 08 28 */	fsubs f1, f0, f1
/* 8007279C 0006F37C  4B FF DD 55 */	bl ftAnim_800704F0
lbl_800727A0:
/* 800727A0 0006F380  80 7E 00 08 */	lwz r3, 8(r30)
/* 800727A4 0006F384  38 03 00 04 */	addi r0, r3, 4
/* 800727A8 0006F388  90 1E 00 08 */	stw r0, 8(r30)
/* 800727AC 0006F38C  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 800727B0 0006F390  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 800727B4 0006F394  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 800727B8 0006F398  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 800727BC 0006F39C  38 21 00 28 */	addi r1, r1, 0x28
/* 800727C0 0006F3A0  7C 08 03 A6 */	mtlr r0
/* 800727C4 0006F3A4  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftAction_800726F4(Fighter_GObj* gobj, FtCmdState* cmd)
{
    char* cmd_x8 = cmd->x8;
    s16 temp_r0 = M2C_FIELD(cmd_x8, s16*, 2);
    ftAnim_800704F0(
        gobj,
        (int) ((M2C_FIELD(cmd_x8, s16*, 0) << 0x17) & 0xFF000000) >> 0x19,
        (float) (s16) ((int) ((temp_r0 << 0x15) |
                              (((u32) temp_r0 >> 0xBU) & 0x100000)) >>
                       0x15));
    {
        char* cmd_x8 = cmd->x8;
        if (((u8) M2C_FIELD(cmd_x8, s8*, 0) >> 1U) & 1) {
            s16 temp_r0_2 = M2C_FIELD(cmd_x8, s16*, 2);
            ftAnim_800704F0(gobj,
                            (int) (((int) M2C_FIELD(cmd_x8, s8*, 0) << 0xE) &
                                   0xFF000000) >>
                                0x19,
                            (float) (s16) ((int) ((temp_r0_2 << 0x15) |
                                                  (((u32) temp_r0_2 >> 0xBU) &
                                                   0x100000)) >>
                                           0x15));
        }
        cmd->x8 += 4;
    }
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftAction_800727C8(Fighter_GObj* gobj, FtCmdState* cmd)
{ // clang-format off
    nofralloc
/* 800727C8 0006F3A8  7C 08 02 A6 */	mflr r0
/* 800727CC 0006F3AC  90 01 00 04 */	stw r0, 4(r1)
/* 800727D0 0006F3B0  3C 00 43 30 */	lis r0, 0x4330
/* 800727D4 0006F3B4  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800727D8 0006F3B8  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800727DC 0006F3BC  7C 9F 23 78 */	mr r31, r4
/* 800727E0 0006F3C0  80 E4 00 08 */	lwz r7, 8(r4)
/* 800727E4 0006F3C4  C8 22 88 C8 */	lfd f1, ftAction_804D82A8
/* 800727E8 0006F3C8  A0 A7 00 02 */	lhz r5, 2(r7)
/* 800727EC 0006F3CC  A8 87 00 00 */	lha r4, 0(r7)
/* 800727F0 0006F3D0  54 A6 05 3E */	clrlwi r6, r5, 0x14
/* 800727F4 0006F3D4  80 A7 00 00 */	lwz r5, 0(r7)
/* 800727F8 0006F3D8  90 C1 00 14 */	stw r6, 0x14(r1)
/* 800727FC 0006F3DC  54 84 B0 0E */	rlwinm r4, r4, 0x16, 0, 7
/* 80072800 0006F3E0  7C 84 CE 70 */	srawi r4, r4, 0x19
/* 80072804 0006F3E4  90 01 00 10 */	stw r0, 0x10(r1)
/* 80072808 0006F3E8  54 A5 68 0E */	rlwinm r5, r5, 0xd, 0, 7
/* 8007280C 0006F3EC  7C A5 CE 70 */	srawi r5, r5, 0x19
/* 80072810 0006F3F0  C8 01 00 10 */	lfd f0, 0x10(r1)
/* 80072814 0006F3F4  EC 20 08 28 */	fsubs f1, f0, f1
/* 80072818 0006F3F8  4B FF E3 71 */	bl ftAnim_ApplyPartAnim
/* 8007281C 0006F3FC  80 7F 00 08 */	lwz r3, 8(r31)
/* 80072820 0006F400  38 03 00 04 */	addi r0, r3, 4
/* 80072824 0006F404  90 1F 00 08 */	stw r0, 8(r31)
/* 80072828 0006F408  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8007282C 0006F40C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80072830 0006F410  38 21 00 20 */	addi r1, r1, 0x20
/* 80072834 0006F414  7C 08 03 A6 */	mtlr r0
/* 80072838 0006F418  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftAction_800727C8(Fighter_GObj* gobj, FtCmdState* cmd)
{
    char* cmd_x8 = cmd->x8;
    ftAnim_ApplyPartAnim(
        gobj,
        (int) ((M2C_FIELD(cmd_x8, s16*, 0) << 0x16) & 0xFF000000) >> 0x19,
        (int) (((int) M2C_FIELD(cmd_x8, s16*, 0) << 0xD) & 0xFF000000) >> 0x19,
        (float) (M2C_FIELD(cmd_x8, u16*, 2) & 0xFFF));
    cmd->x8 += 4;
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftAction_8007283C(Fighter_GObj* gobj, FtCmdState* cmd)
{ // clang-format off
    nofralloc
/* 8007283C 0006F41C  7C 08 02 A6 */	mflr r0
/* 80072840 0006F420  90 01 00 04 */	stw r0, 4(r1)
/* 80072844 0006F424  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80072848 0006F428  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8007284C 0006F42C  7C 9F 23 78 */	mr r31, r4
/* 80072850 0006F430  80 A4 00 08 */	lwz r5, 8(r4)
/* 80072854 0006F434  C0 22 88 D8 */	lfs f1, ftAction_804D82B8
/* 80072858 0006F438  A8 85 00 00 */	lha r4, 0(r5)
/* 8007285C 0006F43C  80 A5 00 00 */	lwz r5, 0(r5)
/* 80072860 0006F440  54 84 B0 0E */	rlwinm r4, r4, 0x16, 0, 7
/* 80072864 0006F444  7C 84 CE 70 */	srawi r4, r4, 0x19
/* 80072868 0006F448  54 A5 68 0E */	rlwinm r5, r5, 0xd, 0, 7
/* 8007286C 0006F44C  7C A5 CE 70 */	srawi r5, r5, 0x19
/* 80072870 0006F450  4B FF E3 19 */	bl ftAnim_ApplyPartAnim
/* 80072874 0006F454  80 7F 00 08 */	lwz r3, 8(r31)
/* 80072878 0006F458  38 03 00 04 */	addi r0, r3, 4
/* 8007287C 0006F45C  90 1F 00 08 */	stw r0, 8(r31)
/* 80072880 0006F460  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80072884 0006F464  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80072888 0006F468  38 21 00 18 */	addi r1, r1, 0x18
/* 8007288C 0006F46C  7C 08 03 A6 */	mtlr r0
/* 80072890 0006F470  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftAction_8007283C(Fighter_GObj* gobj, FtCmdState* cmd)
{
    char* cmd_x8 = cmd->x8;
    ftAnim_ApplyPartAnim(gobj, (int) ((*cmd_x8 << 0x16) & 0xFF000000) >> 0x19,
                         (int) (((int) *cmd_x8 << 0xD) & 0xFF000000) >> 0x19,
                         0.0f);
    cmd->x8 += 4;
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftAction_80072894(Fighter_GObj* gobj, FtCmdState* cmd)
{ // clang-format off
    nofralloc
/* 80072894 0006F474  7C 08 02 A6 */	mflr r0
/* 80072898 0006F478  90 01 00 04 */	stw r0, 4(r1)
/* 8007289C 0006F47C  3C 00 43 30 */	lis r0, 0x4330
/* 800728A0 0006F480  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800728A4 0006F484  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800728A8 0006F488  7C 9F 23 78 */	mr r31, r4
/* 800728AC 0006F48C  80 84 00 08 */	lwz r4, 8(r4)
/* 800728B0 0006F490  C8 22 88 C8 */	lfd f1, ftAction_804D82A8
/* 800728B4 0006F494  A0 A4 00 02 */	lhz r5, 2(r4)
/* 800728B8 0006F498  80 84 00 00 */	lwz r4, 0(r4)
/* 800728BC 0006F49C  54 A5 04 FE */	clrlwi r5, r5, 0x13
/* 800728C0 0006F4A0  90 A1 00 14 */	stw r5, 0x14(r1)
/* 800728C4 0006F4A4  54 84 9C FE */	rlwinm r4, r4, 0x13, 0x13, 0x1f
/* 800728C8 0006F4A8  90 01 00 10 */	stw r0, 0x10(r1)
/* 800728CC 0006F4AC  C8 01 00 10 */	lfd f0, 0x10(r1)
/* 800728D0 0006F4B0  EC 20 08 28 */	fsubs f1, f0, f1
/* 800728D4 0006F4B4  48 00 BF 69 */	bl ftCommon_8007E83C
/* 800728D8 0006F4B8  80 7F 00 08 */	lwz r3, 8(r31)
/* 800728DC 0006F4BC  38 03 00 04 */	addi r0, r3, 4
/* 800728E0 0006F4C0  90 1F 00 08 */	stw r0, 8(r31)
/* 800728E4 0006F4C4  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800728E8 0006F4C8  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800728EC 0006F4CC  38 21 00 20 */	addi r1, r1, 0x20
/* 800728F0 0006F4D0  7C 08 03 A6 */	mtlr r0
/* 800728F4 0006F4D4  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftAction_80072894(Fighter_GObj* gobj, FtCmdState* cmd)
{
    char* cmd_x8 = cmd->x8;
    ftCommon_8007E83C(gobj,
                      ((u32) M2C_FIELD(cmd_x8, u32*, 0) >> 0xDU) & 0x1FFF,
                      (float) (M2C_FIELD(cmd_x8, u16*, 2) & 0x1FFF));
    cmd->x8 += 4;
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftAction_800728F8(Fighter_GObj* gobj, FtCmdState* cmd)
{ // clang-format off
    nofralloc
/* 800728F8 0006F4D8  7C 08 02 A6 */	mflr r0
/* 800728FC 0006F4DC  90 01 00 04 */	stw r0, 4(r1)
/* 80072900 0006F4E0  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80072904 0006F4E4  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80072908 0006F4E8  7C 9F 23 78 */	mr r31, r4
/* 8007290C 0006F4EC  80 A4 00 08 */	lwz r5, 8(r4)
/* 80072910 0006F4F0  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 80072914 0006F4F4  88 05 00 00 */	lbz r0, 0(r5)
/* 80072918 0006F4F8  54 00 FF FF */	rlwinm. r0, r0, 0x1f, 0x1f, 0x1f
/* 8007291C 0006F4FC  41 82 00 1C */	beq lbl_80072938
/* 80072920 0006F500  80 65 00 00 */	lwz r3, 0(r5)
/* 80072924 0006F504  A0 85 00 02 */	lhz r4, 2(r5)
/* 80072928 0006F508  54 63 9D 3E */	rlwinm r3, r3, 0x13, 0x14, 0x1f
/* 8007292C 0006F50C  54 84 04 FE */	clrlwi r4, r4, 0x13
/* 80072930 0006F510  48 00 C3 01 */	bl ftCommon_8007EC30
/* 80072934 0006F514  48 00 00 18 */	b lbl_8007294C
lbl_80072938:
/* 80072938 0006F518  80 85 00 00 */	lwz r4, 0(r5)
/* 8007293C 0006F51C  A0 A5 00 02 */	lhz r5, 2(r5)
/* 80072940 0006F520  54 84 9D 3E */	rlwinm r4, r4, 0x13, 0x14, 0x1f
/* 80072944 0006F524  54 A5 04 FE */	clrlwi r5, r5, 0x13
/* 80072948 0006F528  48 00 C2 65 */	bl ftCommon_8007EBAC
lbl_8007294C:
/* 8007294C 0006F52C  80 7F 00 08 */	lwz r3, 8(r31)
/* 80072950 0006F530  38 03 00 04 */	addi r0, r3, 4
/* 80072954 0006F534  90 1F 00 08 */	stw r0, 8(r31)
/* 80072958 0006F538  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8007295C 0006F53C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80072960 0006F540  38 21 00 20 */	addi r1, r1, 0x20
/* 80072964 0006F544  7C 08 03 A6 */	mtlr r0
/* 80072968 0006F548  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftAction_800728F8(Fighter_GObj* gobj, FtCmdState* cmd)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    char* temp_r5 = cmd->x8;
    if (((u8) M2C_FIELD(temp_r5, s8*, 0) >> 1U) & 1) {
        ftCommon_8007EC30(((u32) M2C_FIELD(temp_r5, s8*, 0) >> 0xDU) & 0xFFF,
                          M2C_FIELD(temp_r5, u16*, 2) & 0x1FFF);
    } else {
        ftCommon_8007EBAC((Fighter*) gobj->user_data,
                          ((u32) M2C_FIELD(temp_r5, s8*, 0) >> 0xDU) & 0xFFF,
                          M2C_FIELD(temp_r5, u16*, 2) & 0x1FFF);
    }
    cmd->x8 += 4;
}
#endif

void ftAction_8007296C(Fighter_GObj* gobj, FtCmdState* cmd)
{
    cmd->x8 += 4;
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftAction_8007297C(Fighter_GObj* gobj, FtCmdState* cmd)
{ // clang-format off
    nofralloc
/* 8007297C 0006F55C  7C 08 02 A6 */	mflr r0
/* 80072980 0006F560  90 01 00 04 */	stw r0, 4(r1)
/* 80072984 0006F564  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80072988 0006F568  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8007298C 0006F56C  7C 9F 23 78 */	mr r31, r4
/* 80072990 0006F570  80 84 00 08 */	lwz r4, 8(r4)
/* 80072994 0006F574  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 80072998 0006F578  80 84 00 00 */	lwz r4, 0(r4)
/* 8007299C 0006F57C  54 84 01 BE */	clrlwi r4, r4, 6
/* 800729A0 0006F580  48 00 C3 35 */	bl ftCommon_8007ECD4
/* 800729A4 0006F584  80 7F 00 08 */	lwz r3, 8(r31)
/* 800729A8 0006F588  38 03 00 04 */	addi r0, r3, 4
/* 800729AC 0006F58C  90 1F 00 08 */	stw r0, 8(r31)
/* 800729B0 0006F590  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800729B4 0006F594  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800729B8 0006F598  38 21 00 20 */	addi r1, r1, 0x20
/* 800729BC 0006F59C  7C 08 03 A6 */	mtlr r0
/* 800729C0 0006F5A0  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftAction_8007297C(Fighter_GObj* gobj, FtCmdState* cmd)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    ftCommon_8007ECD4(gobj->user_data, *cmd->x8 & 0x03FFFFFF);
    cmd->x8 += 4;
}
#endif

void ftAction_800729C4(Fighter_GObj* gobj, FtCmdState* cmd)
{
    cmd->x8 += 4;
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftAction_800729D4(Fighter_GObj* gobj, FtCmdState* cmd)
{ // clang-format off
    nofralloc
/* 800729D4 0006F5B4  7C 08 02 A6 */	mflr r0
/* 800729D8 0006F5B8  90 01 00 04 */	stw r0, 4(r1)
/* 800729DC 0006F5BC  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800729E0 0006F5C0  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800729E4 0006F5C4  7C 9F 23 78 */	mr r31, r4
/* 800729E8 0006F5C8  80 A4 00 08 */	lwz r5, 8(r4)
/* 800729EC 0006F5CC  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 800729F0 0006F5D0  88 05 00 00 */	lbz r0, 0(r5)
/* 800729F4 0006F5D4  80 85 00 00 */	lwz r4, 0(r5)
/* 800729F8 0006F5D8  54 00 07 BE */	clrlwi r0, r0, 0x1e
/* 800729FC 0006F5DC  A0 A5 00 02 */	lhz r5, 2(r5)
/* 80072A00 0006F5E0  2C 00 00 01 */	cmpwi r0, 1
/* 80072A04 0006F5E4  54 84 95 BE */	rlwinm r4, r4, 0x12, 0x16, 0x1f
/* 80072A08 0006F5E8  54 A5 04 BE */	clrlwi r5, r5, 0x12
/* 80072A0C 0006F5EC  41 82 00 1C */	beq lbl_80072A28
/* 80072A10 0006F5F0  40 80 00 1C */	bge lbl_80072A2C
/* 80072A14 0006F5F4  2C 00 00 00 */	cmpwi r0, 0
/* 80072A18 0006F5F8  40 80 00 08 */	bge lbl_80072A20
/* 80072A1C 0006F5FC  48 00 00 10 */	b lbl_80072A2C
lbl_80072A20:
/* 80072A20 0006F600  48 00 C4 A9 */	bl ftCommon_8007EEC8
/* 80072A24 0006F604  48 00 00 08 */	b lbl_80072A2C
lbl_80072A28:
/* 80072A28 0006F608  48 00 C5 35 */	bl ftCommon_8007EF5C
lbl_80072A2C:
/* 80072A2C 0006F60C  80 7F 00 08 */	lwz r3, 8(r31)
/* 80072A30 0006F610  38 03 00 04 */	addi r0, r3, 4
/* 80072A34 0006F614  90 1F 00 08 */	stw r0, 8(r31)
/* 80072A38 0006F618  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80072A3C 0006F61C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80072A40 0006F620  38 21 00 20 */	addi r1, r1, 0x20
/* 80072A44 0006F624  7C 08 03 A6 */	mtlr r0
/* 80072A48 0006F628  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftAction_800729D4(Fighter_GObj* gobj, FtCmdState* cmd)
{
    char* cmd_x8 = cmd->x8;
    ftCo_Fighter* fp = gobj->user_data;
    int temp_r0 = (u8) M2C_FIELD(cmd_x8, s8*, 0) & 3;
    int temp_r4 = ((u32) M2C_FIELD(cmd_x8, s8*, 0) >> 0xEU) & 0x3FF;
    switch (temp_r0) {
    case 0:
        ftCommon_8007EEC8(fp, temp_r4, M2C_FIELD(cmd_x8, u16*, 2) & 0x3FFF);
        break;
    case 1:
        ftCommon_8007EF5C(fp, temp_r4);
        break;
    }
    cmd->x8 += 4;
}
#endif

void ftAction_80072A4C(Fighter_GObj* gobj, FtCmdState* cmd)
{
    cmd->x8 += 4;
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftAction_80072A5C(Fighter_GObj* gobj, FtCmdState* cmd)
{ // clang-format off
    nofralloc
/* 80072A5C 0006F63C  7C 08 02 A6 */	mflr r0
/* 80072A60 0006F640  90 01 00 04 */	stw r0, 4(r1)
/* 80072A64 0006F644  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80072A68 0006F648  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80072A6C 0006F64C  7C 9F 23 78 */	mr r31, r4
/* 80072A70 0006F650  80 A4 00 08 */	lwz r5, 8(r4)
/* 80072A74 0006F654  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 80072A78 0006F658  A0 85 00 00 */	lhz r4, 0(r5)
/* 80072A7C 0006F65C  80 A5 00 00 */	lwz r5, 0(r5)
/* 80072A80 0006F660  54 84 F6 3E */	rlwinm r4, r4, 0x1e, 0x18, 0x1f
/* 80072A84 0006F664  54 A5 03 BE */	clrlwi r5, r5, 0xe
/* 80072A88 0006F668  48 04 D5 49 */	bl ftCo_800BFFD0
/* 80072A8C 0006F66C  80 7F 00 08 */	lwz r3, 8(r31)
/* 80072A90 0006F670  38 03 00 04 */	addi r0, r3, 4
/* 80072A94 0006F674  90 1F 00 08 */	stw r0, 8(r31)
/* 80072A98 0006F678  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80072A9C 0006F67C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80072AA0 0006F680  38 21 00 20 */	addi r1, r1, 0x20
/* 80072AA4 0006F684  7C 08 03 A6 */	mtlr r0
/* 80072AA8 0006F688  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftAction_80072A5C(Fighter_GObj* gobj, FtCmdState* cmd)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    char* cmd_x8 = cmd->x8;
    ftCo_800BFFD0(gobj->user_data, (int) (s8) ((u16) *cmd_x8 >> 2U),
                  (int) *cmd_x8 & 0x3FFFF);
    cmd->x8 += 4;
}
#endif

void ftAction_80072AAC(Fighter_GObj* gobj, FtCmdState* cmd)
{
    cmd->x8 += 4;
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftAction_80072ABC(Fighter_GObj* gobj, FtCmdState* cmd)
{ // clang-format off
    nofralloc
/* 80072ABC 0006F69C  7C 08 02 A6 */	mflr r0
/* 80072AC0 0006F6A0  90 01 00 04 */	stw r0, 4(r1)
/* 80072AC4 0006F6A4  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80072AC8 0006F6A8  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80072ACC 0006F6AC  7C 9F 23 78 */	mr r31, r4
/* 80072AD0 0006F6B0  80 84 00 08 */	lwz r4, 8(r4)
/* 80072AD4 0006F6B4  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 80072AD8 0006F6B8  A0 84 00 00 */	lhz r4, 0(r4)
/* 80072ADC 0006F6BC  54 84 F6 3E */	rlwinm r4, r4, 0x1e, 0x18, 0x1f
/* 80072AE0 0006F6C0  48 04 D7 21 */	bl ftCo_800C0200
/* 80072AE4 0006F6C4  80 7F 00 08 */	lwz r3, 8(r31)
/* 80072AE8 0006F6C8  38 03 00 04 */	addi r0, r3, 4
/* 80072AEC 0006F6CC  90 1F 00 08 */	stw r0, 8(r31)
/* 80072AF0 0006F6D0  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80072AF4 0006F6D4  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80072AF8 0006F6D8  38 21 00 18 */	addi r1, r1, 0x18
/* 80072AFC 0006F6DC  7C 08 03 A6 */	mtlr r0
/* 80072B00 0006F6E0  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftAction_80072ABC(Fighter_GObj* gobj, FtCmdState* cmd)
{
    ftCo_800C0200(gobj->user_data, (s8) ((u16) *cmd->x8 >> 2U));
    cmd->x8 += 4;
}
#endif

void ftAction_80072B04(Fighter_GObj* gobj, FtCmdState* cmd)
{
    cmd->x8 += 4;
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftAction_80072B14(Fighter_GObj* gobj, FtCmdState* cmd)
{ // clang-format off
    nofralloc
/* 80072B14 0006F6F4  80 A4 00 08 */	lwz r5, 8(r4)
/* 80072B18 0006F6F8  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 80072B1C 0006F6FC  80 A5 00 00 */	lwz r5, 0(r5)
/* 80072B20 0006F700  88 03 22 1E */	lbz r0, 0x221e(r3)
/* 80072B24 0006F704  50 A0 36 72 */	rlwimi r0, r5, 6, 0x19, 0x19
/* 80072B28 0006F708  98 03 22 1E */	stb r0, 0x221e(r3)
/* 80072B2C 0006F70C  80 64 00 08 */	lwz r3, 8(r4)
/* 80072B30 0006F710  38 03 00 04 */	addi r0, r3, 4
/* 80072B34 0006F714  90 04 00 08 */	stw r0, 8(r4)
/* 80072B38 0006F718  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftAction_80072B14(Fighter_GObj* gobj, FtCmdState* cmd)
{
    ftCo_Fighter* fp = gobj->user_data;
    fp->x221E_b1 = false;
    // M2C_FIELD(fp, u8*, 0x221E) =
    //     (u8) ((M2C_FIELD(fp, u8*, 0x221E) & ~0x40) |
    //           ((*cmd->x8 << 6) & 0x40));
    cmd->x8 += 4;
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftAction_80072B3C(Fighter_GObj* gobj, FtCmdState* cmd)
{ // clang-format off
    nofralloc
/* 80072B3C 0006F71C  80 A4 00 08 */	lwz r5, 8(r4)
/* 80072B40 0006F720  80 C3 00 2C */	lwz r6, 0x2c(r3)
/* 80072B44 0006F724  80 05 00 00 */	lwz r0, 0(r5)
/* 80072B48 0006F728  54 00 38 32 */	rlwinm r0, r0, 7, 0, 0x19
/* 80072B4C 0006F72C  7C 00 3E 70 */	srawi r0, r0, 7
/* 80072B50 0006F730  7C 00 07 74 */	extsb r0, r0
/* 80072B54 0006F734  98 06 21 00 */	stb r0, 0x2100(r6)
/* 80072B58 0006F738  80 64 00 08 */	lwz r3, 8(r4)
/* 80072B5C 0006F73C  88 06 21 01 */	lbz r0, 0x2101(r6)
/* 80072B60 0006F740  88 63 00 00 */	lbz r3, 0(r3)
/* 80072B64 0006F744  54 63 F0 02 */	slwi r3, r3, 0x1e
/* 80072B68 0006F748  7C 63 FE 70 */	srawi r3, r3, 0x1f
/* 80072B6C 0006F74C  50 60 07 FE */	rlwimi r0, r3, 0, 0x1f, 0x1f
/* 80072B70 0006F750  98 06 21 01 */	stb r0, 0x2101(r6)
/* 80072B74 0006F754  80 64 00 08 */	lwz r3, 8(r4)
/* 80072B78 0006F758  38 03 00 04 */	addi r0, r3, 4
/* 80072B7C 0006F75C  90 04 00 08 */	stw r0, 8(r4)
/* 80072B80 0006F760  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftAction_80072B3C(Fighter_GObj* gobj, FtCmdState* cmd)
{
    u32 cmd_x8;
    ftCo_Fighter* fp = gobj->user_data;
    cmd_x8 = *cmd->x8;
    fp->x2100 = (s8) ((int) ((cmd_x8 << 7) | ((cmd_x8 >> 0x19U) & 0x40)) >> 7);
    fp->x2101 = (u8) ((M2C_FIELD(fp, u8*, 0x2101) & ~1) |
                      (((int) ((u8) *cmd->x8 << 0x1E) >> 0x1F) & 1));
    cmd->x8 += 4;
}
#endif

void ftAction_80072B84(Fighter_GObj* gobj, FtCmdState* cmd)
{
    cmd->x8 += 4;
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftAction_80072B94(Fighter_GObj* gobj, FtCmdState* cmd)
{
    // clang-format off
    nofralloc
/* 80072B94 0006F774  7C 08 02 A6 */	mflr r0
/* 80072B98 0006F778  90 01 00 04 */	stw r0, 4(r1)
/* 80072B9C 0006F77C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80072BA0 0006F780  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80072BA4 0006F784  7C 9F 23 78 */	mr r31, r4
/* 80072BA8 0006F788  80 84 00 08 */	lwz r4, 8(r4)
/* 80072BAC 0006F78C  80 A3 00 2C */	lwz r5, 0x2c(r3)
/* 80072BB0 0006F790  80 84 00 00 */	lwz r4, 0(r4)
/* 80072BB4 0006F794  C0 25 08 94 */	lfs f1, 0x894(r5)
/* 80072BB8 0006F798  54 84 30 34 */	rlwinm r4, r4, 6, 0, 0x1a
/* 80072BBC 0006F79C  7C 84 36 70 */	srawi r4, r4, 6
/* 80072BC0 0006F7A0  48 02 B7 59 */	bl ftCo_8009E318
/* 80072BC4 0006F7A4  80 7F 00 08 */	lwz r3, 8(r31)
/* 80072BC8 0006F7A8  38 03 00 04 */	addi r0, r3, 4
/* 80072BCC 0006F7AC  90 1F 00 08 */	stw r0, 8(r31)
/* 80072BD0 0006F7B0  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80072BD4 0006F7B4  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80072BD8 0006F7B8  38 21 00 20 */	addi r1, r1, 0x20
/* 80072BDC 0006F7BC  7C 08 03 A6 */	mtlr r0
/* 80072BE0 0006F7C0  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftAction_80072B94(Fighter_GObj* gobj, FtCmdState* cmd)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    ftCo_Fighter* fp = gobj->user_data;
    u32 cmd_x8 = *cmd->x8;
    ftCo_8009E318((int) ((cmd_x8 << 6) | ((cmd_x8 >> 0x1AU) & 0x20)) >> 6, fp,
                  fp->cur_anim_frame);
    cmd->x8 += 4;
}
#endif

void ftAction_80072BE4(Fighter_GObj* gobj, FtCmdState* cmd)
{
    cmd->x8 += 4;
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftAction_80072BF4(Fighter_GObj* gobj, FtCmdState* cmd)
{ // clang-format off
    nofralloc
/* 80072BF4 0006F7D4  7C 08 02 A6 */	mflr r0
/* 80072BF8 0006F7D8  90 01 00 04 */	stw r0, 4(r1)
/* 80072BFC 0006F7DC  3C 00 43 30 */	lis r0, 0x4330
/* 80072C00 0006F7E0  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 80072C04 0006F7E4  93 E1 00 24 */	stw r31, 0x24(r1)
/* 80072C08 0006F7E8  7C 9F 23 78 */	mr r31, r4
/* 80072C0C 0006F7EC  80 84 00 08 */	lwz r4, 8(r4)
/* 80072C10 0006F7F0  C8 22 88 D0 */	lfd f1, ftAction_804D82B0
/* 80072C14 0006F7F4  80 84 00 00 */	lwz r4, 0(r4)
/* 80072C18 0006F7F8  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 80072C1C 0006F7FC  54 84 30 34 */	rlwinm r4, r4, 6, 0, 0x1a
/* 80072C20 0006F800  7C 84 36 70 */	srawi r4, r4, 6
/* 80072C24 0006F804  6C 84 80 00 */	xoris r4, r4, 0x8000
/* 80072C28 0006F808  90 81 00 1C */	stw r4, 0x1c(r1)
/* 80072C2C 0006F80C  90 01 00 18 */	stw r0, 0x18(r1)
/* 80072C30 0006F810  C8 01 00 18 */	lfd f0, 0x18(r1)
/* 80072C34 0006F814  EC 20 08 28 */	fsubs f1, f0, f1
/* 80072C38 0006F818  4B FF A0 45 */	bl Fighter_TakeDamage_8006CC7C
/* 80072C3C 0006F81C  80 7F 00 08 */	lwz r3, 8(r31)
/* 80072C40 0006F820  38 03 00 04 */	addi r0, r3, 4
/* 80072C44 0006F824  90 1F 00 08 */	stw r0, 8(r31)
/* 80072C48 0006F828  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 80072C4C 0006F82C  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 80072C50 0006F830  38 21 00 28 */	addi r1, r1, 0x28
/* 80072C54 0006F834  7C 08 03 A6 */	mtlr r0
/* 80072C58 0006F838  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftAction_80072BF4(Fighter_GObj* gobj, FtCmdState* cmd)
{
    u32 cmd_x8 = *cmd->x8;
    Fighter_TakeDamage_8006CC7C(
        gobj->user_data,
        (int) (cmd_x8 << 6 | ((cmd_x8 >> 0x1AU) & 0x20)) >> 6);
    cmd->x8 += 4;
}
#endif

void ftAction_80072C5C(Fighter_GObj* gobj, FtCmdState* cmd)
{
    cmd->x8 += 4;
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftAction_80072C6C(Fighter_GObj* gobj, FtCmdState* cmd)
{ // clang-format off
    nofralloc
/* 80072C6C 0006F84C  7C 08 02 A6 */	mflr r0
/* 80072C70 0006F850  90 01 00 04 */	stw r0, 4(r1)
/* 80072C74 0006F854  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80072C78 0006F858  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80072C7C 0006F85C  7C 9F 23 78 */	mr r31, r4
/* 80072C80 0006F860  80 84 00 08 */	lwz r4, 8(r4)
/* 80072C84 0006F864  80 84 00 00 */	lwz r4, 0(r4)
/* 80072C88 0006F868  54 84 01 BE */	clrlwi r4, r4, 6
/* 80072C8C 0006F86C  48 01 75 2D */	bl ft_8008A1B8
/* 80072C90 0006F870  80 7F 00 08 */	lwz r3, 8(r31)
/* 80072C94 0006F874  38 03 00 04 */	addi r0, r3, 4
/* 80072C98 0006F878  90 1F 00 08 */	stw r0, 8(r31)
/* 80072C9C 0006F87C  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80072CA0 0006F880  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80072CA4 0006F884  38 21 00 18 */	addi r1, r1, 0x18
/* 80072CA8 0006F888  7C 08 03 A6 */	mtlr r0
/* 80072CAC 0006F88C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftAction_80072C6C(Fighter_GObj* gobj, FtCmdState* cmd)
{
    ft_8008A1B8(gobj, *cmd->x8 & 0x03FFFFFF);
    cmd->x8 += 4;
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftAction_80072CB0(Fighter_GObj* gobj, FtCmdState* cmd)
{ // clang-format off
    nofralloc
/* 80072CB0 0006F890  80 A4 00 08 */	lwz r5, 8(r4)
/* 80072CB4 0006F894  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 80072CB8 0006F898  80 A5 00 00 */	lwz r5, 0(r5)
/* 80072CBC 0006F89C  88 03 22 25 */	lbz r0, 0x2225(r3)
/* 80072CC0 0006F8A0  50 A0 2E B4 */	rlwimi r0, r5, 5, 0x1a, 0x1a
/* 80072CC4 0006F8A4  98 03 22 25 */	stb r0, 0x2225(r3)
/* 80072CC8 0006F8A8  80 64 00 08 */	lwz r3, 8(r4)
/* 80072CCC 0006F8AC  38 03 00 04 */	addi r0, r3, 4
/* 80072CD0 0006F8B0  90 04 00 08 */	stw r0, 8(r4)
/* 80072CD4 0006F8B4  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftAction_80072CB0(Fighter_GObj* gobj, FtCmdState* cmd)
{
    ftCo_Fighter* fp = gobj->user_data;
    fp->x2225_b2 = false;
    // M2C_FIELD(fp, u8*, 0x2225) =
    //     (u8) ((M2C_FIELD(fp, u8*, 0x2225) & ~0x20) | ((*cmd->x8 << 5) &
    //     0x20));
    cmd->x8 += 4;
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftAction_80072CD8(Fighter_GObj* gobj, FtCmdState* cmd)
{ // clang-format off
    nofralloc
/* 80072CD8 0006F8B8  7C 08 02 A6 */	mflr r0
/* 80072CDC 0006F8BC  90 01 00 04 */	stw r0, 4(r1)
/* 80072CE0 0006F8C0  38 00 00 01 */	li r0, 1
/* 80072CE4 0006F8C4  94 21 FF 88 */	stwu r1, -0x78(r1)
/* 80072CE8 0006F8C8  93 E1 00 74 */	stw r31, 0x74(r1)
/* 80072CEC 0006F8CC  3B E4 00 00 */	addi r31, r4, 0
/* 80072CF0 0006F8D0  38 81 00 64 */	addi r4, r1, 0x64
/* 80072CF4 0006F8D4  93 C1 00 70 */	stw r30, 0x70(r1)
/* 80072CF8 0006F8D8  7C 7E 1B 78 */	mr r30, r3
/* 80072CFC 0006F8DC  38 A1 00 60 */	addi r5, r1, 0x60
/* 80072D00 0006F8E0  93 A1 00 6C */	stw r29, 0x6c(r1)
/* 80072D04 0006F8E4  38 C1 00 5C */	addi r6, r1, 0x5c
/* 80072D08 0006F8E8  83 A3 00 2C */	lwz r29, 0x2c(r3)
/* 80072D0C 0006F8EC  90 01 00 60 */	stw r0, 0x60(r1)
/* 80072D10 0006F8F0  48 01 1E ED */	bl ft_80084BFC
/* 80072D14 0006F8F4  2C 03 00 00 */	cmpwi r3, 0
/* 80072D18 0006F8F8  41 82 00 B0 */	beq lbl_80072DC8
/* 80072D1C 0006F8FC  80 C1 00 64 */	lwz r6, 0x64(r1)
/* 80072D20 0006F900  2C 06 FF FF */	cmpwi r6, -1
/* 80072D24 0006F904  41 82 00 34 */	beq lbl_80072D58
/* 80072D28 0006F908  38 01 00 2C */	addi r0, r1, 0x2c
/* 80072D2C 0006F90C  90 01 00 40 */	stw r0, 0x40(r1)
/* 80072D30 0006F910  38 7E 00 00 */	addi r3, r30, 0
/* 80072D34 0006F914  38 81 00 38 */	addi r4, r1, 0x38
/* 80072D38 0006F918  80 BF 00 08 */	lwz r5, 8(r31)
/* 80072D3C 0006F91C  80 05 00 00 */	lwz r0, 0(r5)
/* 80072D40 0006F920  90 01 00 2C */	stw r0, 0x2c(r1)
/* 80072D44 0006F924  90 C1 00 30 */	stw r6, 0x30(r1)
/* 80072D48 0006F928  80 BF 00 08 */	lwz r5, 8(r31)
/* 80072D4C 0006F92C  80 05 00 08 */	lwz r0, 8(r5)
/* 80072D50 0006F930  90 01 00 34 */	stw r0, 0x34(r1)
/* 80072D54 0006F934  4B FF ED FD */	bl ftAction_80071B50
lbl_80072D58:
/* 80072D58 0006F938  80 81 00 5C */	lwz r4, 0x5c(r1)
/* 80072D5C 0006F93C  2C 04 FF FF */	cmpwi r4, -1
/* 80072D60 0006F940  41 82 00 68 */	beq lbl_80072DC8
/* 80072D64 0006F944  C0 02 88 D8 */	lfs f0, ftAction_804D82B8
/* 80072D68 0006F948  D0 01 00 28 */	stfs f0, 0x28(r1)
/* 80072D6C 0006F94C  D0 01 00 1C */	stfs f0, 0x1c(r1)
/* 80072D70 0006F950  D0 01 00 24 */	stfs f0, 0x24(r1)
/* 80072D74 0006F954  D0 01 00 18 */	stfs f0, 0x18(r1)
/* 80072D78 0006F958  D0 01 00 20 */	stfs f0, 0x20(r1)
/* 80072D7C 0006F95C  D0 01 00 14 */	stfs f0, 0x14(r1)
/* 80072D80 0006F960  80 7F 00 08 */	lwz r3, 8(r31)
/* 80072D84 0006F964  88 03 00 01 */	lbz r0, 1(r3)
/* 80072D88 0006F968  54 00 FF FF */	rlwinm. r0, r0, 0x1f, 0x1f, 0x1f
/* 80072D8C 0006F96C  40 82 00 14 */	bne lbl_80072DA0
/* 80072D90 0006F970  80 7D 01 0C */	lwz r3, 0x10c(r29)
/* 80072D94 0006F974  80 63 00 08 */	lwz r3, 8(r3)
/* 80072D98 0006F978  88 A3 00 13 */	lbz r5, 0x13(r3)
/* 80072D9C 0006F97C  48 00 00 10 */	b lbl_80072DAC
lbl_80072DA0:
/* 80072DA0 0006F980  80 7D 01 0C */	lwz r3, 0x10c(r29)
/* 80072DA4 0006F984  80 63 00 08 */	lwz r3, 8(r3)
/* 80072DA8 0006F988  88 A3 00 14 */	lbz r5, 0x14(r3)
lbl_80072DAC:
/* 80072DAC 0006F98C  C0 22 88 D8 */	lfs f1, ftAction_804D82B8
/* 80072DB0 0006F990  38 7E 00 00 */	addi r3, r30, 0
/* 80072DB4 0006F994  39 01 00 20 */	addi r8, r1, 0x20
/* 80072DB8 0006F998  39 21 00 14 */	addi r9, r1, 0x14
/* 80072DBC 0006F99C  38 C0 00 00 */	li r6, 0
/* 80072DC0 0006F9A0  38 E0 00 00 */	li r7, 0
/* 80072DC4 0006F9A4  48 02 CA 71 */	bl ftCo_8009F834
lbl_80072DC8:
/* 80072DC8 0006F9A8  80 01 00 60 */	lwz r0, 0x60(r1)
/* 80072DCC 0006F9AC  2C 00 00 00 */	cmpwi r0, 0
/* 80072DD0 0006F9B0  41 82 00 14 */	beq lbl_80072DE4
/* 80072DD4 0006F9B4  38 7E 00 00 */	addi r3, r30, 0
/* 80072DD8 0006F9B8  38 9F 00 00 */	addi r4, r31, 0
/* 80072DDC 0006F9BC  4B FF ED 75 */	bl ftAction_80071B50
/* 80072DE0 0006F9C0  48 00 00 28 */	b lbl_80072E08
lbl_80072DE4:
/* 80072DE4 0006F9C4  80 7F 00 08 */	lwz r3, 8(r31)
/* 80072DE8 0006F9C8  38 03 00 04 */	addi r0, r3, 4
/* 80072DEC 0006F9CC  90 1F 00 08 */	stw r0, 8(r31)
/* 80072DF0 0006F9D0  80 7F 00 08 */	lwz r3, 8(r31)
/* 80072DF4 0006F9D4  38 03 00 04 */	addi r0, r3, 4
/* 80072DF8 0006F9D8  90 1F 00 08 */	stw r0, 8(r31)
/* 80072DFC 0006F9DC  80 7F 00 08 */	lwz r3, 8(r31)
/* 80072E00 0006F9E0  38 03 00 04 */	addi r0, r3, 4
/* 80072E04 0006F9E4  90 1F 00 08 */	stw r0, 8(r31)
lbl_80072E08:
/* 80072E08 0006F9E8  80 01 00 7C */	lwz r0, 0x7c(r1)
/* 80072E0C 0006F9EC  83 E1 00 74 */	lwz r31, 0x74(r1)
/* 80072E10 0006F9F0  83 C1 00 70 */	lwz r30, 0x70(r1)
/* 80072E14 0006F9F4  83 A1 00 6C */	lwz r29, 0x6c(r1)
/* 80072E18 0006F9F8  38 21 00 78 */	addi r1, r1, 0x78
/* 80072E1C 0006F9FC  7C 08 03 A6 */	mtlr r0
/* 80072E20 0006FA00  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-but-set-variable"
#endif
void ftAction_80072CD8(Fighter_GObj* gobj, FtCmdState* cmd)
{
    IntVec3 ivec1;
    int* sp40;
    M2C_UNK sp38;
    IntVec3 ivec0;
    Vec3 vec1;
    Vec3 vec0;
    u8 var_r5;
    ftCo_Fighter* fp = gobj->user_data;
    ivec1.y = 1;
    if (ft_80084BFC(gobj, &ivec1.z, &ivec1.y) != 0) {
        if (ivec1.z != -1) {
            sp40 = &ivec0.x;
            ivec0.x = M2C_FIELD(cmd->x8, int*, 0);
            ivec0.y = ivec1.z;
            ivec0.z = M2C_FIELD(cmd->x8, int*, 8);
            ftAction_80071B50(gobj, (FtCmdState*) &sp38);
        }
        if (ivec1.x != -1) {
            vec1.z = 0.0f;
            vec0.z = 0.0f;
            vec1.y = 0.0f;
            vec0.y = 0.0f;
            vec1.x = 0.0f;
            vec0.x = 0.0f;
            if (!(((u8) M2C_FIELD(cmd->x8, u8*, 1) >> 1U) & 1)) {
                var_r5 = fp->ft_data->x8->unk13;
            } else {
                var_r5 = fp->ft_data->x8->unk14;
            }
            ftCo_8009F834(gobj, (int) ivec1.x, var_r5, 0, 0, &vec1, &vec0,
                          0.0f);
        }
    }
    if (ivec1.y != 0) {
        ftAction_80071B50(gobj, cmd);
        return;
    }
    cmd->x8 += 4;
    cmd->x8 += 4;
    cmd->x8 += 4;
}
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
#endif

void ftAction_80072E24(Fighter_GObj* gobj, FtCmdState* cmd)
{
    cmd->x8 += 4;
    cmd->x8 += 4;
    cmd->x8 += 4;
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftAction_80072E4C(Fighter_GObj* gobj, FtCmdState* cmd)
{ // clang-format off
    nofralloc
/* 80072E4C 0006FA2C  7C 08 02 A6 */	mflr r0
/* 80072E50 0006FA30  90 01 00 04 */	stw r0, 4(r1)
/* 80072E54 0006FA34  38 00 FF FF */	li r0, -1
/* 80072E58 0006FA38  94 21 FF 88 */	stwu r1, -0x78(r1)
/* 80072E5C 0006FA3C  93 E1 00 74 */	stw r31, 0x74(r1)
/* 80072E60 0006FA40  38 A1 00 60 */	addi r5, r1, 0x60
/* 80072E64 0006FA44  38 C1 00 5C */	addi r6, r1, 0x5c
/* 80072E68 0006FA48  93 C1 00 70 */	stw r30, 0x70(r1)
/* 80072E6C 0006FA4C  3B C4 00 00 */	addi r30, r4, 0
/* 80072E70 0006FA50  38 81 00 64 */	addi r4, r1, 0x64
/* 80072E74 0006FA54  93 A1 00 6C */	stw r29, 0x6c(r1)
/* 80072E78 0006FA58  93 81 00 68 */	stw r28, 0x68(r1)
/* 80072E7C 0006FA5C  7C 7C 1B 78 */	mr r28, r3
/* 80072E80 0006FA60  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80072E84 0006FA64  38 60 00 01 */	li r3, 1
/* 80072E88 0006FA68  90 61 00 60 */	stw r3, 0x60(r1)
/* 80072E8C 0006FA6C  38 7C 00 00 */	addi r3, r28, 0
/* 80072E90 0006FA70  90 01 00 5C */	stw r0, 0x5c(r1)
/* 80072E94 0006FA74  80 FE 00 08 */	lwz r7, 8(r30)
/* 80072E98 0006FA78  8B A7 00 01 */	lbz r29, 1(r7)
/* 80072E9C 0006FA7C  57 BD 07 FE */	clrlwi r29, r29, 0x1f
/* 80072EA0 0006FA80  48 01 1D 99 */	bl ft_80084C38
/* 80072EA4 0006FA84  2C 03 00 00 */	cmpwi r3, 0
/* 80072EA8 0006FA88  41 82 00 48 */	beq lbl_80072EF0
/* 80072EAC 0006FA8C  2C 1D 00 00 */	cmpwi r29, 0
/* 80072EB0 0006FA90  40 82 00 40 */	bne lbl_80072EF0
/* 80072EB4 0006FA94  80 C1 00 64 */	lwz r6, 0x64(r1)
/* 80072EB8 0006FA98  2C 06 FF FF */	cmpwi r6, -1
/* 80072EBC 0006FA9C  41 82 00 34 */	beq lbl_80072EF0
/* 80072EC0 0006FAA0  38 01 00 2C */	addi r0, r1, 0x2c
/* 80072EC4 0006FAA4  90 01 00 40 */	stw r0, 0x40(r1)
/* 80072EC8 0006FAA8  38 7C 00 00 */	addi r3, r28, 0
/* 80072ECC 0006FAAC  38 81 00 38 */	addi r4, r1, 0x38
/* 80072ED0 0006FAB0  80 BE 00 08 */	lwz r5, 8(r30)
/* 80072ED4 0006FAB4  80 05 00 00 */	lwz r0, 0(r5)
/* 80072ED8 0006FAB8  90 01 00 2C */	stw r0, 0x2c(r1)
/* 80072EDC 0006FABC  90 C1 00 30 */	stw r6, 0x30(r1)
/* 80072EE0 0006FAC0  80 BE 00 08 */	lwz r5, 8(r30)
/* 80072EE4 0006FAC4  80 05 00 08 */	lwz r0, 8(r5)
/* 80072EE8 0006FAC8  90 01 00 34 */	stw r0, 0x34(r1)
/* 80072EEC 0006FACC  4B FF EC 65 */	bl ftAction_80071B50
lbl_80072EF0:
/* 80072EF0 0006FAD0  80 01 00 5C */	lwz r0, 0x5c(r1)
/* 80072EF4 0006FAD4  2C 00 FF FF */	cmpwi r0, -1
/* 80072EF8 0006FAD8  40 82 00 10 */	bne lbl_80072F08
/* 80072EFC 0006FADC  80 7E 00 08 */	lwz r3, 8(r30)
/* 80072F00 0006FAE0  A0 03 00 02 */	lhz r0, 2(r3)
/* 80072F04 0006FAE4  90 01 00 5C */	stw r0, 0x5c(r1)
lbl_80072F08:
/* 80072F08 0006FAE8  C0 22 88 D8 */	lfs f1, ftAction_804D82B8
/* 80072F0C 0006FAEC  7F 83 E3 78 */	mr r3, r28
/* 80072F10 0006FAF0  80 81 00 5C */	lwz r4, 0x5c(r1)
/* 80072F14 0006FAF4  39 01 00 20 */	addi r8, r1, 0x20
/* 80072F18 0006FAF8  D0 21 00 28 */	stfs f1, 0x28(r1)
/* 80072F1C 0006FAFC  39 21 00 14 */	addi r9, r1, 0x14
/* 80072F20 0006FB00  D0 21 00 1C */	stfs f1, 0x1c(r1)
/* 80072F24 0006FB04  38 A0 00 00 */	li r5, 0
/* 80072F28 0006FB08  38 C0 00 00 */	li r6, 0
/* 80072F2C 0006FB0C  D0 21 00 24 */	stfs f1, 0x24(r1)
/* 80072F30 0006FB10  38 E0 00 00 */	li r7, 0
/* 80072F34 0006FB14  D0 21 00 18 */	stfs f1, 0x18(r1)
/* 80072F38 0006FB18  D0 21 00 20 */	stfs f1, 0x20(r1)
/* 80072F3C 0006FB1C  D0 21 00 14 */	stfs f1, 0x14(r1)
/* 80072F40 0006FB20  48 02 C8 F5 */	bl ftCo_8009F834
/* 80072F44 0006FB24  80 01 00 60 */	lwz r0, 0x60(r1)
/* 80072F48 0006FB28  2C 00 00 00 */	cmpwi r0, 0
/* 80072F4C 0006FB2C  41 82 00 2C */	beq lbl_80072F78
/* 80072F50 0006FB30  38 7F 00 00 */	addi r3, r31, 0
/* 80072F54 0006FB34  38 80 00 46 */	li r4, 0x46
/* 80072F58 0006FB38  38 A0 00 7F */	li r5, 0x7f
/* 80072F5C 0006FB3C  38 C0 00 40 */	li r6, 0x40
/* 80072F60 0006FB40  48 01 51 E9 */	bl ft_80088148
/* 80072F64 0006FB44  2C 1D 00 00 */	cmpwi r29, 0
/* 80072F68 0006FB48  40 82 00 10 */	bne lbl_80072F78
/* 80072F6C 0006FB4C  38 7C 00 00 */	addi r3, r28, 0
/* 80072F70 0006FB50  38 9E 00 00 */	addi r4, r30, 0
/* 80072F74 0006FB54  4B FF EB DD */	bl ftAction_80071B50
lbl_80072F78:
/* 80072F78 0006FB58  80 01 00 60 */	lwz r0, 0x60(r1)
/* 80072F7C 0006FB5C  2C 00 00 00 */	cmpwi r0, 0
/* 80072F80 0006FB60  41 82 00 0C */	beq lbl_80072F8C
/* 80072F84 0006FB64  2C 1D 00 00 */	cmpwi r29, 0
/* 80072F88 0006FB68  41 82 00 28 */	beq lbl_80072FB0
lbl_80072F8C:
/* 80072F8C 0006FB6C  80 7E 00 08 */	lwz r3, 8(r30)
/* 80072F90 0006FB70  38 03 00 04 */	addi r0, r3, 4
/* 80072F94 0006FB74  90 1E 00 08 */	stw r0, 8(r30)
/* 80072F98 0006FB78  80 7E 00 08 */	lwz r3, 8(r30)
/* 80072F9C 0006FB7C  38 03 00 04 */	addi r0, r3, 4
/* 80072FA0 0006FB80  90 1E 00 08 */	stw r0, 8(r30)
/* 80072FA4 0006FB84  80 7E 00 08 */	lwz r3, 8(r30)
/* 80072FA8 0006FB88  38 03 00 04 */	addi r0, r3, 4
/* 80072FAC 0006FB8C  90 1E 00 08 */	stw r0, 8(r30)
lbl_80072FB0:
/* 80072FB0 0006FB90  38 7F 00 00 */	addi r3, r31, 0
/* 80072FB4 0006FB94  38 80 00 16 */	li r4, 0x16
/* 80072FB8 0006FB98  38 A0 00 00 */	li r5, 0
/* 80072FBC 0006FB9C  48 00 BB F1 */	bl ftCommon_8007EBAC
/* 80072FC0 0006FBA0  80 01 00 7C */	lwz r0, 0x7c(r1)
/* 80072FC4 0006FBA4  83 E1 00 74 */	lwz r31, 0x74(r1)
/* 80072FC8 0006FBA8  83 C1 00 70 */	lwz r30, 0x70(r1)
/* 80072FCC 0006FBAC  83 A1 00 6C */	lwz r29, 0x6c(r1)
/* 80072FD0 0006FBB0  83 81 00 68 */	lwz r28, 0x68(r1)
/* 80072FD4 0006FBB4  38 21 00 78 */	addi r1, r1, 0x78
/* 80072FD8 0006FBB8  7C 08 03 A6 */	mtlr r0
/* 80072FDC 0006FBBC  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-but-set-variable"
#endif
void ftAction_80072E4C(Fighter_GObj* gobj, FtCmdState* cmd)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[24] = { 0 };
#endif
    IntVec3 ivec1; /* compiler-managed */
    int* sp40;
    M2C_UNK sp38;
    IntVec3 ivec0;
    ftCo_Fighter* fp = gobj->user_data;
    Vec3 vec1;
    Vec3 vec0;
    ivec1.y = 1;
    ivec1.x = -1;
    {
        char* temp_r7 = cmd->x8;
        int temp_r29 = M2C_FIELD(temp_r7, u8*, 1) & 1;
        if ((ft_80084C38(gobj, &ivec1.z, &ivec1.y, &ivec1.x, temp_r7) != 0) &&
            (temp_r29 == 0) && (ivec1.z != -1))
        {
            sp40 = &ivec0.x;
            ivec0.x = M2C_FIELD(cmd->x8, int*, 0);
            ivec0.y = ivec1.z;
            ivec0.z = M2C_FIELD(cmd->x8, int*, 8);
            ftAction_80071B50(gobj, (FtCmdState*) &sp38);
        }
        if ((int) ivec1.x == -1) {
            ivec1.x = (int) M2C_FIELD(cmd->x8, u16*, 2);
        }
        vec1.z = 0.0f;
        vec0.z = 0.0f;
        vec1.y = 0.0f;
        vec0.y = 0.0f;
        vec1.x = 0.0f;
        vec0.x = 0.0f;
        ftCo_8009F834(gobj, ivec1.x, 0, 0, 0, &vec1, &vec0, 0.0f);
        if (ivec1.y != 0) {
            ft_80088148(fp, 0x46, 0x7F, 0x40);
            if (temp_r29 == 0) {
                ftAction_80071B50(gobj, cmd);
            }
        }
        if ((ivec1.y == 0) || (temp_r29 != 0)) {
            cmd->x8 += 4;
            cmd->x8 += 4;
            cmd->x8 += 4;
        }
        ftCommon_8007EBAC(fp, 0x16U, 0U);
    }
}
#endif
#if defined(__clang__)
#pragma clang diagnostic pop
#endif

void ftAction_80072FE0(Fighter_GObj* gobj, FtCmdState* cmd)
{
    cmd->x8 += 4;
    cmd->x8 += 4;
    cmd->x8 += 4;
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftAction_80073008(Fighter_GObj* gobj, FtCmdState* cmd)
{
    // clang-format off
    nofralloc
/* 80073008 0006FBE8  7C 08 02 A6 */	mflr r0
/* 8007300C 0006FBEC  3C E0 43 30 */	lis r7, 0x4330
/* 80073010 0006FBF0  90 01 00 04 */	stw r0, 4(r1)
/* 80073014 0006FBF4  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 80073018 0006FBF8  81 04 00 08 */	lwz r8, 8(r4)
/* 8007301C 0006FBFC  C8 62 88 C8 */	lfd f3, ftAction_804D82A8
/* 80073020 0006FC00  A0 A8 00 02 */	lhz r5, 2(r8)
/* 80073024 0006FC04  38 08 00 04 */	addi r0, r8, 4
/* 80073028 0006FC08  A0 C8 00 00 */	lhz r6, 0(r8)
/* 8007302C 0006FC0C  C0 42 88 C0 */	lfs f2, ftAction_804D82A0
/* 80073030 0006FC10  54 C8 05 BE */	clrlwi r8, r6, 0x16
/* 80073034 0006FC14  90 A1 00 2C */	stw r5, 0x2c(r1)
/* 80073038 0006FC18  90 04 00 08 */	stw r0, 8(r4)
/* 8007303C 0006FC1C  80 C4 00 08 */	lwz r6, 8(r4)
/* 80073040 0006FC20  90 E1 00 28 */	stw r7, 0x28(r1)
/* 80073044 0006FC24  88 A6 00 00 */	lbz r5, 0(r6)
/* 80073048 0006FC28  38 06 00 04 */	addi r0, r6, 4
/* 8007304C 0006FC2C  C8 01 00 28 */	lfd f0, 0x28(r1)
/* 80073050 0006FC30  90 A1 00 24 */	stw r5, 0x24(r1)
/* 80073054 0006FC34  EC 20 18 28 */	fsubs f1, f0, f3
/* 80073058 0006FC38  90 E1 00 20 */	stw r7, 0x20(r1)
/* 8007305C 0006FC3C  C8 01 00 20 */	lfd f0, 0x20(r1)
/* 80073060 0006FC40  EC 42 00 72 */	fmuls f2, f2, f1
/* 80073064 0006FC44  91 01 00 34 */	stw r8, 0x34(r1)
/* 80073068 0006FC48  EC 00 18 28 */	fsubs f0, f0, f3
/* 8007306C 0006FC4C  90 E1 00 30 */	stw r7, 0x30(r1)
/* 80073070 0006FC50  FC 00 00 1E */	fctiwz f0, f0
/* 80073074 0006FC54  C8 21 00 30 */	lfd f1, 0x30(r1)
/* 80073078 0006FC58  90 04 00 08 */	stw r0, 8(r4)
/* 8007307C 0006FC5C  EC 21 18 28 */	fsubs f1, f1, f3
/* 80073080 0006FC60  D8 01 00 18 */	stfd f0, 0x18(r1)
/* 80073084 0006FC64  80 81 00 1C */	lwz r4, 0x1c(r1)
/* 80073088 0006FC68  48 06 BD FD */	bl ftCo_800DEE84
/* 8007308C 0006FC6C  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 80073090 0006FC70  38 21 00 38 */	addi r1, r1, 0x38
/* 80073094 0006FC74  7C 08 03 A6 */	mtlr r0
/* 80073098 0006FC78  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftAction_80073008(Fighter_GObj* gobj, FtCmdState* cmd)
{
    char* temp_r8 = cmd->x8;
    u32 temp_r8_2 = M2C_FIELD(temp_r8, u16*, 0) & 0x3FF;
    cmd->x8 = temp_r8 + 4;
    {
        char* temp_r6 = cmd->x8;
        u8 temp_r5 = (u8) M2C_FIELD(temp_r6, s8*, 0);
        cmd->x8 = temp_r6 + 4;
        ftCo_800DEE84((int) (float) temp_r5, temp_r5, temp_r6, temp_r8_2,
                      (float) temp_r8_2,
                      0.003906f * (float) M2C_FIELD(temp_r8, u16*, 2));
    }
}
#endif

void ftAction_8007309C(Fighter_GObj* gobj, FtCmdState* cmd)
{
    cmd->x8 += 4;
    cmd->x8 += 4;
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftAction_800730B8(Fighter_GObj* gobj, FtCmdState* cmd)
{ // clang-format off
    nofralloc
/* 800730B8 0006FC98  7C 08 02 A6 */	mflr r0
/* 800730BC 0006FC9C  90 01 00 04 */	stw r0, 4(r1)
/* 800730C0 0006FCA0  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800730C4 0006FCA4  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800730C8 0006FCA8  7C 9F 23 78 */	mr r31, r4
/* 800730CC 0006FCAC  80 84 00 08 */	lwz r4, 8(r4)
/* 800730D0 0006FCB0  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 800730D4 0006FCB4  A0 04 00 00 */	lhz r0, 0(r4)
/* 800730D8 0006FCB8  88 84 00 00 */	lbz r4, 0(r4)
/* 800730DC 0006FCBC  54 05 FE 3E */	rlwinm r5, r0, 0x1f, 0x18, 0x1f
/* 800730E0 0006FCC0  54 84 FF FE */	rlwinm r4, r4, 0x1f, 0x1f, 0x1f
/* 800730E4 0006FCC4  48 05 5A 7D */	bl ftCo_800C8B60
/* 800730E8 0006FCC8  80 7F 00 08 */	lwz r3, 8(r31)
/* 800730EC 0006FCCC  38 03 00 04 */	addi r0, r3, 4
/* 800730F0 0006FCD0  90 1F 00 08 */	stw r0, 8(r31)
/* 800730F4 0006FCD4  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800730F8 0006FCD8  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800730FC 0006FCDC  38 21 00 20 */	addi r1, r1, 0x20
/* 80073100 0006FCE0  7C 08 03 A6 */	mtlr r0
/* 80073104 0006FCE4  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftAction_800730B8(Fighter_GObj* gobj, FtCmdState* cmd)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    char* cmd_x8 = cmd->x8;
    ftCo_800C8B60(gobj->user_data, ((u8) *cmd_x8 >> 1U) & 1,
                  (s8) ((u16) *cmd_x8 >> 1U));
    cmd->x8 += 4;
}
#endif

void ftAction_80073108(Fighter_GObj* gobj, FtCmdState* cmd)
{
    cmd->x8 += 4;
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftAction_80073118(Fighter_GObj* gobj, FtCmdState* cmd)
{
    // clang-format off
    nofralloc
/* 80073118 0006FCF8  7C 08 02 A6 */	mflr r0
/* 8007311C 0006FCFC  3D 00 43 30 */	lis r8, 0x4330
/* 80073120 0006FD00  90 01 00 04 */	stw r0, 4(r1)
/* 80073124 0006FD04  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 80073128 0006FD08  80 A4 00 08 */	lwz r5, 8(r4)
/* 8007312C 0006FD0C  89 45 00 03 */	lbz r10, 3(r5)
/* 80073130 0006FD10  38 05 00 04 */	addi r0, r5, 4
/* 80073134 0006FD14  90 04 00 08 */	stw r0, 8(r4)
/* 80073138 0006FD18  80 A4 00 08 */	lwz r5, 8(r4)
/* 8007313C 0006FD1C  C0 E2 88 C0 */	lfs f7, ftAction_804D82A0
/* 80073140 0006FD20  A8 C5 00 00 */	lha r6, 0(r5)
/* 80073144 0006FD24  38 05 00 04 */	addi r0, r5, 4
/* 80073148 0006FD28  A8 A5 00 02 */	lha r5, 2(r5)
/* 8007314C 0006FD2C  C8 C2 88 D0 */	lfd f6, ftAction_804D82B0
/* 80073150 0006FD30  6C C6 80 00 */	xoris r6, r6, 0x8000
/* 80073154 0006FD34  6C A5 80 00 */	xoris r5, r5, 0x8000
/* 80073158 0006FD38  90 C1 00 34 */	stw r6, 0x34(r1)
/* 8007315C 0006FD3C  90 04 00 08 */	stw r0, 8(r4)
/* 80073160 0006FD40  80 E4 00 08 */	lwz r7, 8(r4)
/* 80073164 0006FD44  90 A1 00 2C */	stw r5, 0x2c(r1)
/* 80073168 0006FD48  A8 C7 00 00 */	lha r6, 0(r7)
/* 8007316C 0006FD4C  38 07 00 04 */	addi r0, r7, 4
/* 80073170 0006FD50  A8 A7 00 02 */	lha r5, 2(r7)
/* 80073174 0006FD54  91 01 00 30 */	stw r8, 0x30(r1)
/* 80073178 0006FD58  6C C7 80 00 */	xoris r7, r6, 0x8000
/* 8007317C 0006FD5C  6C A6 80 00 */	xoris r6, r5, 0x8000
/* 80073180 0006FD60  90 04 00 08 */	stw r0, 8(r4)
/* 80073184 0006FD64  C8 01 00 30 */	lfd f0, 0x30(r1)
/* 80073188 0006FD68  81 24 00 08 */	lwz r9, 8(r4)
/* 8007318C 0006FD6C  90 E1 00 24 */	stw r7, 0x24(r1)
/* 80073190 0006FD70  EC 00 30 28 */	fsubs f0, f0, f6
/* 80073194 0006FD74  A8 A9 00 02 */	lha r5, 2(r9)
/* 80073198 0006FD78  38 09 00 04 */	addi r0, r9, 4
/* 8007319C 0006FD7C  90 C1 00 1C */	stw r6, 0x1c(r1)
/* 800731A0 0006FD80  6C A5 80 00 */	xoris r5, r5, 0x8000
/* 800731A4 0006FD84  90 A1 00 14 */	stw r5, 0x14(r1)
/* 800731A8 0006FD88  EC 27 00 32 */	fmuls f1, f7, f0
/* 800731AC 0006FD8C  A8 A9 00 00 */	lha r5, 0(r9)
/* 800731B0 0006FD90  91 01 00 28 */	stw r8, 0x28(r1)
/* 800731B4 0006FD94  91 01 00 20 */	stw r8, 0x20(r1)
/* 800731B8 0006FD98  C8 41 00 28 */	lfd f2, 0x28(r1)
/* 800731BC 0006FD9C  C8 01 00 20 */	lfd f0, 0x20(r1)
/* 800731C0 0006FDA0  90 04 00 08 */	stw r0, 8(r4)
/* 800731C4 0006FDA4  EC A2 30 28 */	fsubs f5, f2, f6
/* 800731C8 0006FDA8  EC 60 30 28 */	fsubs f3, f0, f6
/* 800731CC 0006FDAC  7D 44 53 78 */	mr r4, r10
/* 800731D0 0006FDB0  91 01 00 18 */	stw r8, 0x18(r1)
/* 800731D4 0006FDB4  91 01 00 10 */	stw r8, 0x10(r1)
/* 800731D8 0006FDB8  EC 67 00 F2 */	fmuls f3, f7, f3
/* 800731DC 0006FDBC  C8 41 00 18 */	lfd f2, 0x18(r1)
/* 800731E0 0006FDC0  C8 01 00 10 */	lfd f0, 0x10(r1)
/* 800731E4 0006FDC4  EC 82 30 28 */	fsubs f4, f2, f6
/* 800731E8 0006FDC8  EC 00 30 28 */	fsubs f0, f0, f6
/* 800731EC 0006FDCC  EC 47 01 72 */	fmuls f2, f7, f5
/* 800731F0 0006FDD0  EC 87 01 32 */	fmuls f4, f7, f4
/* 800731F4 0006FDD4  EC A7 00 32 */	fmuls f5, f7, f0
/* 800731F8 0006FDD8  48 02 B5 1D */	bl ftCo_8009E714
/* 800731FC 0006FDDC  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 80073200 0006FDE0  38 21 00 38 */	addi r1, r1, 0x38
/* 80073204 0006FDE4  7C 08 03 A6 */	mtlr r0
/* 80073208 0006FDE8  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftAction_80073118(Fighter_GObj* gobj, FtCmdState* cmd)
{
    char* temp_r5 = cmd->x8;
    u8 temp_r10 = M2C_FIELD(temp_r5, u8*, 3);
    cmd->x8 = temp_r5 + 4;
    {
        char* cmd_x8 = cmd->x8;
        cmd->x8 = cmd_x8 + 4;
        {
            char* cmd_x8 = cmd->x8;
            cmd->x8 = cmd_x8 + 4;
            {
                char* cmd_x8 = cmd->x8;
                cmd->x8 = cmd_x8 + 4;
                ftCo_8009E714(temp_r10, M2C_FIELD(cmd_x8, s16*, 0), cmd_x8,
                              temp_r10, 0.003906f * M2C_FIELD(cmd_x8, s16*, 0),
                              0.003906f * M2C_FIELD(cmd_x8, s16*, 2),
                              0.003906f * M2C_FIELD(cmd_x8, s16*, 0),
                              0.003906f * M2C_FIELD(cmd_x8, s16*, 2),
                              0.003906f * M2C_FIELD(cmd_x8, s16*, 2),
                              0.003906f);
            }
        }
    }
}
#endif

void ftAction_8007320C(Fighter_GObj* gobj, FtCmdState* cmd)
{
    cmd->x8 += 4;
    cmd->x8 += 4;
    cmd->x8 += 4;
    cmd->x8 += 4;
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftAction_80073240(Fighter_GObj*)
{ // clang-format off
    nofralloc
/* 80073240 0006FE20  7C 08 02 A6 */	mflr r0
/* 80073244 0006FE24  90 01 00 04 */	stw r0, 4(r1)
/* 80073248 0006FE28  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 8007324C 0006FE2C  DB E1 00 30 */	stfd f31, 0x30(r1)
/* 80073250 0006FE30  DB C1 00 28 */	stfd f30, 0x28(r1)
/* 80073254 0006FE34  BF 61 00 14 */	stmw r27, 0x14(r1)
/* 80073258 0006FE38  7C 7B 1B 78 */	mr r27, r3
/* 8007325C 0006FE3C  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 80073260 0006FE40  C0 3E 08 94 */	lfs f1, 0x894(r30)
/* 80073264 0006FE44  3B BE 03 E4 */	addi r29, r30, 0x3e4
/* 80073268 0006FE48  C0 1E 08 98 */	lfs f0, 0x898(r30)
/* 8007326C 0006FE4C  EC 01 00 2A */	fadds f0, f1, f0
/* 80073270 0006FE50  D0 1E 03 E8 */	stfs f0, 0x3e8(r30)
/* 80073274 0006FE54  80 1E 03 EC */	lwz r0, 0x3ec(r30)
/* 80073278 0006FE58  28 00 00 00 */	cmplwi r0, 0
/* 8007327C 0006FE5C  41 82 00 BC */	beq lbl_80073338
/* 80073280 0006FE60  C0 02 88 E4 */	lfs f0, ftAction_804D82C4
/* 80073284 0006FE64  C0 3D 00 00 */	lfs f1, 0(r29)
/* 80073288 0006FE68  FC 00 08 00 */	fcmpu cr0, f0, f1
/* 8007328C 0006FE6C  41 82 00 10 */	beq lbl_8007329C
/* 80073290 0006FE70  C0 1E 08 9C */	lfs f0, 0x89c(r30)
/* 80073294 0006FE74  EC 01 00 28 */	fsubs f0, f1, f0
/* 80073298 0006FE78  D0 1D 00 00 */	stfs f0, 0(r29)
lbl_8007329C:
/* 8007329C 0006FE7C  3C 60 80 3C */	lis r3, ftAction_803C06E8@ha
/* 800732A0 0006FE80  C3 C2 88 E4 */	lfs f30, ftAction_804D82C4
/* 800732A4 0006FE84  C3 E2 88 D8 */	lfs f31, ftAction_804D82B8
/* 800732A8 0006FE88  3B E3 06 E8 */	addi r31, r3, ftAction_803C06E8@l
lbl_800732AC:
/* 800732AC 0006FE8C  80 1D 00 08 */	lwz r0, 8(r29)
/* 800732B0 0006FE90  28 00 00 00 */	cmplwi r0, 0
/* 800732B4 0006FE94  41 82 00 84 */	beq lbl_80073338
/* 800732B8 0006FE98  C0 1D 00 00 */	lfs f0, 0(r29)
/* 800732BC 0006FE9C  FC 1E 00 00 */	fcmpu cr0, f30, f0
/* 800732C0 0006FEA0  40 82 00 24 */	bne lbl_800732E4
/* 800732C4 0006FEA4  C0 3D 00 04 */	lfs f1, 4(r29)
/* 800732C8 0006FEA8  C0 1E 08 9C */	lfs f0, 0x89c(r30)
/* 800732CC 0006FEAC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800732D0 0006FEB0  4C 41 13 82 */	cror 2, 1, 2
/* 800732D4 0006FEB4  41 82 00 64 */	beq lbl_80073338
/* 800732D8 0006FEB8  FC 00 08 50 */	fneg f0, f1
/* 800732DC 0006FEBC  D0 1D 00 00 */	stfs f0, 0(r29)
/* 800732E0 0006FEC0  48 00 00 0C */	b lbl_800732EC
lbl_800732E4:
/* 800732E4 0006FEC4  FC 00 F8 40 */	fcmpo cr0, f0, f31
/* 800732E8 0006FEC8  41 81 00 50 */	bgt lbl_80073338
lbl_800732EC:
/* 800732EC 0006FECC  80 9D 00 08 */	lwz r4, 8(r29)
/* 800732F0 0006FED0  7F A3 EB 78 */	mr r3, r29
/* 800732F4 0006FED4  8B 84 00 00 */	lbz r28, 0(r4)
/* 800732F8 0006FED8  57 9C F6 BE */	rlwinm r28, r28, 0x1e, 0x1a, 0x1f
/* 800732FC 0006FEDC  38 9C 00 00 */	addi r4, r28, 0
/* 80073300 0006FEE0  4B F9 28 65 */	bl Command_Execute
/* 80073304 0006FEE4  2C 03 00 00 */	cmpwi r3, 0
/* 80073308 0006FEE8  40 82 00 24 */	bne lbl_8007332C
/* 8007330C 0006FEEC  38 1C FF F6 */	addi r0, r28, -10
/* 80073310 0006FEF0  54 00 10 3A */	slwi r0, r0, 2
/* 80073314 0006FEF4  7C 7F 02 14 */	add r3, r31, r0
/* 80073318 0006FEF8  81 83 00 00 */	lwz r12, 0(r3)
/* 8007331C 0006FEFC  38 7B 00 00 */	addi r3, r27, 0
/* 80073320 0006FF00  38 9D 00 00 */	addi r4, r29, 0
/* 80073324 0006FF04  7D 88 03 A6 */	mtlr r12
/* 80073328 0006FF08  4E 80 00 21 */	blrl
lbl_8007332C:
/* 8007332C 0006FF0C  C0 1D 00 00 */	lfs f0, 0(r29)
/* 80073330 0006FF10  FC 1E 00 00 */	fcmpu cr0, f30, f0
/* 80073334 0006FF14  40 82 FF 78 */	bne lbl_800732AC
lbl_80073338:
/* 80073338 0006FF18  BB 61 00 14 */	lmw r27, 0x14(r1)
/* 8007333C 0006FF1C  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 80073340 0006FF20  CB E1 00 30 */	lfd f31, 0x30(r1)
/* 80073344 0006FF24  CB C1 00 28 */	lfd f30, 0x28(r1)
/* 80073348 0006FF28  38 21 00 38 */	addi r1, r1, 0x38
/* 8007334C 0006FF2C  7C 08 03 A6 */	mtlr r0
/* 80073350 0006FF30  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftAction_80073240(Fighter_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    ftCmdScript* ftCommand = &fp->x3E4_fighterCmdScript;
    u32 eventCode;
    fp->x3E4_fighterCmdScript.x3E8_scriptFrameTimer =
        fp->cur_anim_frame + fp->x898_unk;
    if (fp->x3E4_fighterCmdScript.x3EC_scriptCurrent != NULL) {
        if (ftCommand->x3E4_scriptEventTimer != F32_MAX) {
            ftCommand->x3E4_scriptEventTimer -= fp->frame_spd_mul;
        }
        do {
            if (ftCommand->x3EC_scriptCurrent == NULL) {
                break;
            }
            if (F32_MAX == ftCommand->x3E4_scriptEventTimer) {
                if (ftCommand->x3E8_scriptFrameTimer >= fp->frame_spd_mul) {
                    break;
                }
                ftCommand->x3E4_scriptEventTimer =
                    -ftCommand->x3E8_scriptFrameTimer;
            } else if (ftCommand->x3E4_scriptEventTimer > 0.0f) {
                break;
            }
            eventCode = gmScriptEventCast(ftCommand->x3EC_scriptCurrent,
                                          gmScriptEventDefault)
                            ->opcode;
            if (Command_Execute((CommandInfo*) ftCommand, eventCode) == false)
            {
                eventCode -= 0xA;
                ftAction_803C06E8[eventCode](fighter_gobj,
                                             (FtCmdState*) ftCommand);
            }
        } while (F32_MAX != ftCommand->x3E4_scriptEventTimer);
    }
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftAction_80073354(Fighter_GObj*)
{ // clang-format off
    nofralloc
/* 80073354 0006FF34  7C 08 02 A6 */	mflr r0
/* 80073358 0006FF38  90 01 00 04 */	stw r0, 4(r1)
/* 8007335C 0006FF3C  38 00 00 00 */	li r0, 0
/* 80073360 0006FF40  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 80073364 0006FF44  DB E1 00 38 */	stfd f31, 0x38(r1)
/* 80073368 0006FF48  DB C1 00 30 */	stfd f30, 0x30(r1)
/* 8007336C 0006FF4C  DB A1 00 28 */	stfd f29, 0x28(r1)
/* 80073370 0006FF50  BF 61 00 14 */	stmw r27, 0x14(r1)
/* 80073374 0006FF54  7C 7B 1B 78 */	mr r27, r3
/* 80073378 0006FF58  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 8007337C 0006FF5C  C0 3E 08 94 */	lfs f1, 0x894(r30)
/* 80073380 0006FF60  3B BE 03 E4 */	addi r29, r30, 0x3e4
/* 80073384 0006FF64  C0 1E 08 98 */	lfs f0, 0x898(r30)
/* 80073388 0006FF68  EC 01 00 2A */	fadds f0, f1, f0
/* 8007338C 0006FF6C  D0 1E 03 E8 */	stfs f0, 0x3e8(r30)
/* 80073390 0006FF70  90 1E 22 10 */	stw r0, 0x2210(r30)
/* 80073394 0006FF74  80 1E 03 EC */	lwz r0, 0x3ec(r30)
/* 80073398 0006FF78  28 00 00 00 */	cmplwi r0, 0
/* 8007339C 0006FF7C  41 82 00 E0 */	beq lbl_8007347C
/* 800733A0 0006FF80  C0 02 88 E4 */	lfs f0, ftAction_804D82C4
/* 800733A4 0006FF84  C0 3D 00 00 */	lfs f1, 0(r29)
/* 800733A8 0006FF88  FC 00 08 00 */	fcmpu cr0, f0, f1
/* 800733AC 0006FF8C  41 82 00 10 */	beq lbl_800733BC
/* 800733B0 0006FF90  C0 1E 08 9C */	lfs f0, 0x89c(r30)
/* 800733B4 0006FF94  EC 01 00 28 */	fsubs f0, f1, f0
/* 800733B8 0006FF98  D0 1D 00 00 */	stfs f0, 0(r29)
lbl_800733BC:
/* 800733BC 0006FF9C  3C 60 80 3C */	lis r3, ftAction_803C07AC@ha
/* 800733C0 0006FFA0  C3 C2 88 E4 */	lfs f30, ftAction_804D82C4
/* 800733C4 0006FFA4  C3 E2 88 D8 */	lfs f31, ftAction_804D82B8
/* 800733C8 0006FFA8  3B E3 07 AC */	addi r31, r3, ftAction_803C07AC@l
lbl_800733CC:
/* 800733CC 0006FFAC  80 1D 00 08 */	lwz r0, 8(r29)
/* 800733D0 0006FFB0  28 00 00 00 */	cmplwi r0, 0
/* 800733D4 0006FFB4  41 82 00 A8 */	beq lbl_8007347C
/* 800733D8 0006FFB8  C0 1D 00 00 */	lfs f0, 0(r29)
/* 800733DC 0006FFBC  FC 1E 00 00 */	fcmpu cr0, f30, f0
/* 800733E0 0006FFC0  40 82 00 24 */	bne lbl_80073404
/* 800733E4 0006FFC4  C0 3D 00 04 */	lfs f1, 4(r29)
/* 800733E8 0006FFC8  C0 1E 08 9C */	lfs f0, 0x89c(r30)
/* 800733EC 0006FFCC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800733F0 0006FFD0  4C 41 13 82 */	cror 2, 1, 2
/* 800733F4 0006FFD4  41 82 00 88 */	beq lbl_8007347C
/* 800733F8 0006FFD8  FC 00 08 50 */	fneg f0, f1
/* 800733FC 0006FFDC  D0 1D 00 00 */	stfs f0, 0(r29)
/* 80073400 0006FFE0  48 00 00 0C */	b lbl_8007340C
lbl_80073404:
/* 80073404 0006FFE4  FC 00 F8 40 */	fcmpo cr0, f0, f31
/* 80073408 0006FFE8  41 81 00 74 */	bgt lbl_8007347C
lbl_8007340C:
/* 8007340C 0006FFEC  80 9D 00 08 */	lwz r4, 8(r29)
/* 80073410 0006FFF0  7F A3 EB 78 */	mr r3, r29
/* 80073414 0006FFF4  C3 BD 00 00 */	lfs f29, 0(r29)
/* 80073418 0006FFF8  8B 84 00 00 */	lbz r28, 0(r4)
/* 8007341C 0006FFFC  57 9C F6 BE */	rlwinm r28, r28, 0x1e, 0x1a, 0x1f
/* 80073420 00070000  38 9C 00 00 */	addi r4, r28, 0
/* 80073424 00070004  4B F9 27 41 */	bl Command_Execute
/* 80073428 00070008  2C 03 00 00 */	cmpwi r3, 0
/* 8007342C 0007000C  40 82 00 24 */	bne lbl_80073450
/* 80073430 00070010  38 1C FF F6 */	addi r0, r28, -10
/* 80073434 00070014  54 00 10 3A */	slwi r0, r0, 2
/* 80073438 00070018  7C 7F 02 14 */	add r3, r31, r0
/* 8007343C 0007001C  81 83 00 00 */	lwz r12, 0(r3)
/* 80073440 00070020  38 7B 00 00 */	addi r3, r27, 0
/* 80073444 00070024  38 9D 00 00 */	addi r4, r29, 0
/* 80073448 00070028  7D 88 03 A6 */	mtlr r12
/* 8007344C 0007002C  4E 80 00 21 */	blrl
lbl_80073450:
/* 80073450 00070030  C0 1D 00 00 */	lfs f0, 0(r29)
/* 80073454 00070034  FC 00 E8 00 */	fcmpu cr0, f0, f29
/* 80073458 00070038  41 82 00 18 */	beq lbl_80073470
/* 8007345C 0007003C  FC 00 F8 40 */	fcmpo cr0, f0, f31
/* 80073460 00070040  4C 40 13 82 */	cror 2, 0, 2
/* 80073464 00070044  40 82 00 0C */	bne lbl_80073470
/* 80073468 00070048  38 00 00 00 */	li r0, 0
/* 8007346C 0007004C  90 1E 22 10 */	stw r0, 0x2210(r30)
lbl_80073470:
/* 80073470 00070050  C0 1D 00 00 */	lfs f0, 0(r29)
/* 80073474 00070054  FC 1E 00 00 */	fcmpu cr0, f30, f0
/* 80073478 00070058  40 82 FF 54 */	bne lbl_800733CC
lbl_8007347C:
/* 8007347C 0007005C  BB 61 00 14 */	lmw r27, 0x14(r1)
/* 80073480 00070060  80 01 00 44 */	lwz r0, 0x44(r1)
/* 80073484 00070064  CB E1 00 38 */	lfd f31, 0x38(r1)
/* 80073488 00070068  CB C1 00 30 */	lfd f30, 0x30(r1)
/* 8007348C 0007006C  CB A1 00 28 */	lfd f29, 0x28(r1)
/* 80073490 00070070  38 21 00 40 */	addi r1, r1, 0x40
/* 80073494 00070074  7C 08 03 A6 */	mtlr r0
/* 80073498 00070078  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftAction_80073354(Fighter_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    CommandInfo* cmd = (CommandInfo*) &fp->x3E4_fighterCmdScript;
    fp->x3E4_fighterCmdScript.x3E8_scriptFrameTimer =
        fp->cur_anim_frame + fp->x898_unk;
    fp->throw_flags = 0;
    if (fp->x3E4_fighterCmdScript.x3EC_scriptCurrent != NULL) {
        float timer = cmd->timer;
        if (timer != F32_MAX) {
            cmd->timer = timer - fp->frame_spd_mul;
        }
    loop_4:
        if ((u8*) cmd->u.data_position != NULL) {
            float timer = cmd->timer;
            if (timer == F32_MAX) {
                float frame_count = cmd->frame_count;
                if (!(frame_count >= fp->frame_spd_mul)) {
                    cmd->timer = -frame_count;
                    goto block_9;
                }
            } else if (!(timer > 0.0f)) {
            block_9: {
                float timer = cmd->timer;
                u32 temp_r28 = ((u8) *cmd->u.data_position >> 2U) & 0x3F;
                if (!Command_Execute(cmd, temp_r28)) {
                    ftAction_803C07AC[temp_r28 - 0xA](gobj, (FtCmdState*) cmd);
                }
                {
                    float timer1 = cmd->timer;
                    if (timer1 != timer) {
                        if (timer1 <= 0.0f) {
                            fp->throw_flags = 0;
                        }
                    }
                }
                if (cmd->timer != F32_MAX) {
                    goto loop_4;
                }
            }
            }
        }
    }
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftAction_8007349C(Fighter_GObj*)
{ // clang-format off
    nofralloc
/* 8007349C 0007007C  7C 08 02 A6 */	mflr r0
/* 800734A0 00070080  90 01 00 04 */	stw r0, 4(r1)
/* 800734A4 00070084  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 800734A8 00070088  DB E1 00 30 */	stfd f31, 0x30(r1)
/* 800734AC 0007008C  DB C1 00 28 */	stfd f30, 0x28(r1)
/* 800734B0 00070090  93 E1 00 24 */	stw r31, 0x24(r1)
/* 800734B4 00070094  93 C1 00 20 */	stw r30, 0x20(r1)
/* 800734B8 00070098  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 800734BC 0007009C  93 81 00 18 */	stw r28, 0x18(r1)
/* 800734C0 000700A0  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 800734C4 000700A4  C0 3E 08 94 */	lfs f1, 0x894(r30)
/* 800734C8 000700A8  3B BE 03 E4 */	addi r29, r30, 0x3e4
/* 800734CC 000700AC  C0 1E 08 98 */	lfs f0, 0x898(r30)
/* 800734D0 000700B0  EC 01 00 2A */	fadds f0, f1, f0
/* 800734D4 000700B4  D0 1E 03 E8 */	stfs f0, 0x3e8(r30)
/* 800734D8 000700B8  80 1E 03 EC */	lwz r0, 0x3ec(r30)
/* 800734DC 000700BC  28 00 00 00 */	cmplwi r0, 0
/* 800734E0 000700C0  41 82 00 B4 */	beq lbl_80073594
/* 800734E4 000700C4  C0 02 88 E4 */	lfs f0, ftAction_804D82C4
/* 800734E8 000700C8  C0 3D 00 00 */	lfs f1, 0(r29)
/* 800734EC 000700CC  FC 00 08 00 */	fcmpu cr0, f0, f1
/* 800734F0 000700D0  41 82 00 10 */	beq lbl_80073500
/* 800734F4 000700D4  C0 1E 08 9C */	lfs f0, 0x89c(r30)
/* 800734F8 000700D8  EC 01 00 28 */	fsubs f0, f1, f0
/* 800734FC 000700DC  D0 1D 00 00 */	stfs f0, 0(r29)
lbl_80073500:
/* 80073500 000700E0  3C 60 80 3C */	lis r3, ftAction_803C0870@ha
/* 80073504 000700E4  C3 C2 88 E4 */	lfs f30, ftAction_804D82C4
/* 80073508 000700E8  C3 E2 88 D8 */	lfs f31, ftAction_804D82B8
/* 8007350C 000700EC  3B E3 08 70 */	addi r31, r3, ftAction_803C0870@l
lbl_80073510:
/* 80073510 000700F0  80 1D 00 08 */	lwz r0, 8(r29)
/* 80073514 000700F4  28 00 00 00 */	cmplwi r0, 0
/* 80073518 000700F8  41 82 00 7C */	beq lbl_80073594
/* 8007351C 000700FC  C0 1D 00 00 */	lfs f0, 0(r29)
/* 80073520 00070100  FC 1E 00 00 */	fcmpu cr0, f30, f0
/* 80073524 00070104  40 82 00 24 */	bne lbl_80073548
/* 80073528 00070108  C0 3D 00 04 */	lfs f1, 4(r29)
/* 8007352C 0007010C  C0 1E 08 9C */	lfs f0, 0x89c(r30)
/* 80073530 00070110  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80073534 00070114  4C 41 13 82 */	cror 2, 1, 2
/* 80073538 00070118  41 82 00 5C */	beq lbl_80073594
/* 8007353C 0007011C  FC 00 08 50 */	fneg f0, f1
/* 80073540 00070120  D0 1D 00 00 */	stfs f0, 0(r29)
/* 80073544 00070124  48 00 00 0C */	b lbl_80073550
lbl_80073548:
/* 80073548 00070128  FC 00 F8 40 */	fcmpo cr0, f0, f31
/* 8007354C 0007012C  41 81 00 48 */	bgt lbl_80073594
lbl_80073550:
/* 80073550 00070130  80 9D 00 08 */	lwz r4, 8(r29)
/* 80073554 00070134  7F A3 EB 78 */	mr r3, r29
/* 80073558 00070138  8B 84 00 00 */	lbz r28, 0(r4)
/* 8007355C 0007013C  57 9C F6 BE */	rlwinm r28, r28, 0x1e, 0x1a, 0x1f
/* 80073560 00070140  38 9C 00 00 */	addi r4, r28, 0
/* 80073564 00070144  4B F9 26 01 */	bl Command_Execute
/* 80073568 00070148  2C 03 00 00 */	cmpwi r3, 0
/* 8007356C 0007014C  40 82 00 1C */	bne lbl_80073588
/* 80073570 00070150  7C 7F E2 14 */	add r3, r31, r28
/* 80073574 00070154  80 9D 00 08 */	lwz r4, 8(r29)
/* 80073578 00070158  88 03 FF F6 */	lbz r0, -0xa(r3)
/* 8007357C 0007015C  54 00 10 3A */	slwi r0, r0, 2
/* 80073580 00070160  7C 04 02 14 */	add r0, r4, r0
/* 80073584 00070164  90 1D 00 08 */	stw r0, 8(r29)
lbl_80073588:
/* 80073588 00070168  C0 1D 00 00 */	lfs f0, 0(r29)
/* 8007358C 0007016C  FC 1E 00 00 */	fcmpu cr0, f30, f0
/* 80073590 00070170  40 82 FF 80 */	bne lbl_80073510
lbl_80073594:
/* 80073594 00070174  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 80073598 00070178  CB E1 00 30 */	lfd f31, 0x30(r1)
/* 8007359C 0007017C  CB C1 00 28 */	lfd f30, 0x28(r1)
/* 800735A0 00070180  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 800735A4 00070184  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 800735A8 00070188  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 800735AC 0007018C  83 81 00 18 */	lwz r28, 0x18(r1)
/* 800735B0 00070190  38 21 00 38 */	addi r1, r1, 0x38
/* 800735B4 00070194  7C 08 03 A6 */	mtlr r0
/* 800735B8 00070198  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftAction_8007349C(Fighter_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    ftCo_Fighter* fp = gobj->user_data;
    CommandInfo* cmd = (CommandInfo*) &fp->x3E4_fighterCmdScript;
    fp->x3E4_fighterCmdScript.x3E8_scriptFrameTimer =
        fp->cur_anim_frame + fp->x898_unk;
    if (fp->x3E4_fighterCmdScript.x3EC_scriptCurrent != NULL) {
        float timer = cmd->timer;
        if (timer != F32_MAX) {
            cmd->timer = timer - fp->frame_spd_mul;
        }
    loop_4:
        if ((u32*) cmd->u.data_position != NULL) {
            float timer = cmd->timer;
            if (timer == F32_MAX) {
                float frame_count = cmd->frame_count;
                if (!(frame_count >= fp->frame_spd_mul)) {
                    cmd->timer = -frame_count;
                    goto block_9;
                }
            } else if (!(timer > 0.0f)) {
            block_9: {
                u32 temp_r28 = ((u8) *cmd->u.data_position >> 2U) & 0x3F;
                if (Command_Execute(cmd, temp_r28) == 0) {
                    cmd->u.data_position = &cmd->u.data_position[M2C_FIELD(
                        &ftAction_803C0870[temp_r28], u8*, -0xA)];
                }
                if (cmd->timer != F32_MAX) {
                    goto loop_4;
                }
            }
            }
        }
    }
}
#endif
