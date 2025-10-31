#include "ftaction.h"

#include <placeholder.h>
#include <platform.h>

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0881.h"
#include "ft/ft_0892.h"
#include "ft/ft_0C88.h"
#include "ft/ftanim.h"
#include "ft/ftcolanim.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftdynamics.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "ftCommon/ftCo_09F7.h"
#include "lb/inlines.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbcommand.h"
#include "lb/types.h"

#include <dolphin/mtx.h>
#include <baselib/gobj.h>
#include <baselib/gobjproc.h>
#include <baselib/random.h>

/* 07121C */ static void ftAction_8007121C(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 0715EC */ static void ftAction_800715EC(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 07162C */ static void ftAction_8007162C(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 07168C */ static void ftAction_8007168C(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 07169C */ static void ftAction_8007169C(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 0716F8 */ static void ftAction_800716F8(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 071708 */ static void ftAction_80071708(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 071774 */ static void ftAction_80071774(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 071784 */ static void ftAction_80071784(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 0717C8 */ static void ftAction_800717C8(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 0717D8 */ static void ftAction_800717D8(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 071810 */ static void ftAction_80071810(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 071820 */ static void ftAction_80071820(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 0718A4 */ static void ftAction_800718A4(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 071908 */ static void ftAction_80071908(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 07192C */ static void ftAction_8007192C(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 071950 */ static void ftAction_80071950(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 071974 */ static void ftAction_80071974(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 071998 */ static void ftAction_80071998(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 071A14 */ static void ftAction_80071A14(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 071A58 */ static void ftAction_80071A58(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 071A9C */ static void ftAction_80071A9C(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 071AE8 */ static void ftAction_80071AE8(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 071B28 */ static void ftAction_80071B28(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 071CCC */ static void ftAction_80071CCC(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 071D30 */ static void ftAction_80071D30(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 071D40 */ static void ftAction_80071D40(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 071D94 */ static void ftAction_80071D94(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 071DCC */ static void ftAction_80071DCC(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 071E04 */ static void ftAction_80071E04(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 071F0C */ static void ftAction_80071F0C(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 071F34 */ static void ftAction_80071F34(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 071F78 */ static void ftAction_80071F78(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 071FA0 */ static void ftAction_80071FA0(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 071FC8 */ static void ftAction_80071FC8(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 0722C8 */ static void ftAction_800722C8(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 072320 */ static void ftAction_80072320(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 0726C0 */ static void ftAction_800726C0(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 0726F4 */ static void ftAction_800726F4(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 0727C8 */ static void ftAction_800727C8(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 07283C */ static void ftAction_8007283C(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 072894 */ static void ftAction_80072894(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 0728F8 */ static void ftAction_800728F8(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 07296C */ static void ftAction_8007296C(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 07297C */ static void ftAction_8007297C(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 0729C4 */ static void ftAction_800729C4(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 0729D4 */ static void ftAction_800729D4(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 072A4C */ static void ftAction_80072A4C(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 072A5C */ static void ftAction_80072A5C(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 072AAC */ static void ftAction_80072AAC(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 072ABC */ static void ftAction_80072ABC(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 072B04 */ static void ftAction_80072B04(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 072B14 */ static void ftAction_80072B14(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 072B3C */ static void ftAction_80072B3C(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 072B84 */ static void ftAction_80072B84(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 072B94 */ static void ftAction_80072B94(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 072BE4 */ static void ftAction_80072BE4(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 072BF4 */ static void ftAction_80072BF4(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 072C5C */ static void ftAction_80072C5C(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 072C6C */ static void ftAction_80072C6C(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 072CB0 */ static void ftAction_80072CB0(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 072CD8 */ static void ftAction_80072CD8(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 072E24 */ static void ftAction_80072E24(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 072E4C */ static void ftAction_80072E4C(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 072FE0 */ static void ftAction_80072FE0(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 073008 */ static void ftAction_80073008(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 07309C */ static void ftAction_8007309C(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 073118 */ static void ftAction_80073118(Fighter_GObj* gobj,
                                           CommandInfo* cmd);
/* 07320C */ static void ftAction_8007320C(Fighter_GObj* gobj,
                                           CommandInfo* cmd);

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

static FtCmd ftAction_803C07AC[ARRAY_SIZE(ftAction_803C06E8)] = {
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

static u8 ftAction_803C0870[ARRAY_SIZE(ftAction_803C06E8)] = {
    05, 05, 01, 01, 01, 01, 01, 03, 01, 01, 01, 01, 01, 01, 01, 01, 01,
    01, 01, 01, 01, 01, 01, 01, 03, 01, 01, 01, 07, 04, 01, 01, 01, 01,
    01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 03, 03, 02, 01, 04
};

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

void ftAction_80071028(Fighter_GObj* gobj, CommandInfo* cmd)
{
    Fighter* fp = GET_FIGHTER(gobj);
    float unk;
    Vec3 offset;
    Vec3 range;
    // permuter jank?
    {
        CommandInfo* new_var;
        if (!fp->invisible) {
            int bone;
            if (cmd->u->test1.useUnkBone) {
                bone = fp->ft_data->x8->x12;
            } else {
                bone = cmd->u->test1.boneId;
            }
            {
                int use_common_bone_id = cmd->u->test1.useCommonBoneIDs;
                int destroy_on_state_change =
                    cmd->u->test1.destroyOnStateChange;
                gmScriptEventUpdatePtr((new_var = cmd)->u, struct test1);
                {
                    int gfx_id = new_var->u->test2.gfxID;
                    unk = new_var->u->test2.unkFloat;
                    gmScriptEventUpdatePtr(new_var->u, struct test2);
                    {
                        offset.z = (1 / 256.0f) * new_var->u->test3.offsetZ;
                        offset.y = (1 / 256.0f) * new_var->u->test3.offsetY;
                        gmScriptEventUpdatePtr(new_var->u, struct test3);
                        offset.x = (1 / 256.0f) * new_var->u->test4.offsetX;
                        range.z = (1 / 256.0f) * new_var->u->test4.rangeZ;
                        gmScriptEventUpdatePtr(new_var->u, struct test4);
                        range.y = (1 / 256.0f) * new_var->u->test5.rangeY;
                        range.x = (1 / 256.0f) * new_var->u->test5.rangeX;
                        gmScriptEventUpdatePtr(new_var->u, struct test5);
                        ftCo_8009F834(gobj, gfx_id, bone, use_common_bone_id,
                                      destroy_on_state_change, &offset, &range,
                                      unk);
                    }
                }
            }
        } else {
            ftAction_800711DC(gobj, cmd);
        }
    }
}

/// Skip GFX Spawn
void ftAction_800711DC(Fighter_GObj* gobj, CommandInfo* cmd)
{
    SKIP_CMD(cmd, 5);
}

void ftAction_8007121C(Fighter_GObj* gobj, CommandInfo* cmd)
{
    // char* temp_r3;
    // char part;
    // u32 temp_r4_2;
    // char* cmd_x8 = cmd->x8;
    // Fighter* fp = gobj->user_data;
    // HitCapsule* hit;
    // PAD_STACK(16);

    // if ((((u8) M2C_FIELD(cmd_x8, u8*, 0xF) >> 3U) & 1) &&
    //     fp->x1064_thrownHitbox.owner == NULL)
    // {
    //     ftAction_800715EC(gobj, cmd);
    // } else {
    //     hit = &fp->x914[(((u16) M2C_FIELD(cmd_x8, u16*, 0) >> 7U) & 7)];
    //     temp_r4_2 = ((u8) M2C_FIELD(cmd_x8, u8*, 1) >> 4U) & 7;
    //     if (hit->state == HitCapsule_Disabled || hit->x4 != temp_r4_2) {
    //         hit->x4 = temp_r4_2;
    //         hit->state = HitCapsule_Enabled;
    //         fp->x2219_b3 = 1;
    //         ftColl_800768A0(fp, hit);
    //     }
    //     temp_r3 = cmd->x8;
    //     part = (s8) ((u32) M2C_FIELD(temp_r3, u32*, 0) >> 0xB);
    //     if (((u8) M2C_FIELD(temp_r3, u8*, 2) >> 2U) & 1) {
    //         hit->jobj = fp->parts[ftParts_GetBoneIndex(fp, part)].joint;
    //     } else {
    //         hit->jobj = fp->parts[(int) part].joint;
    //     }
    //     ftColl_8007ABD0(hit, M2C_FIELD(cmd->x8, u16*, 2) & 0x3FF, gobj);
    //     ++cmd->u;
    //     hit->scale = 0.003906f * M2C_FIELD(cmd->x8, u16*, 0);
    //     hit->b_offset.x = 0.003906f * M2C_FIELD(cmd->x8, s16*, 2);
    //     ++cmd->u;
    //     // hit->b_offset.y = 0.003906f * cmd->x8_bits->x0;
    //     // hit->b_offset.z = 0.003906f * cmd->x8_bits->x2;
    //     ++cmd->u;
    //     ftColl_8007AC9C(hit, (M2C_FIELD(cmd->x8, u16*, 0) >> 7U) & 0x1FF,
    //                     gobj);
    //     hit->x24 = ((u32) M2C_FIELD(cmd->x8, u32*, 0) >> 0xEU) & 0x1FF;
    //     hit->x28 = (M2C_FIELD(cmd->x8, u16*, 2) >> 5U) & 0x1FF;
    //     // hit->x43_b0 = cmd->x8_bits->x3_b3;
    //     // hit->x43_b1 = cmd->x8_bits->x3_b5;
    //     // hit->x40_b0 = cmd->x8_bits->x3_b6;
    //     // hit->x40_b1 = cmd->x8_bits->x3_b7;
    //     ++cmd->u;
    //     hit->x2C = ((u16) M2C_FIELD(cmd->x8, u16*, 0) >> 7U) & 0x1FF;
    //     hit->element = ((u8) M2C_FIELD(cmd->x8, u8*, 1) >> 2U) & 0x1F;
    //     M2C_FIELD(hit, int*, 0x34) =
    //         (int) ((int) ((M2C_FIELD(cmd->x8, u32*, 0) << 0xE) & 0xFF800000)
    //         >>
    //                0x18);
    //     hit->sfx_severity = ((u16) M2C_FIELD(cmd->x8, u16*, 2) >> 7U) & 7;
    //     hit->sfx_kind = ((u8) M2C_FIELD(cmd->x8, u8*, 3) >> 2U) & 0x1F;
    //     // hit->x40_b2 = cmd->x8_bits->x3_b7;
    //     // hit->x40_b3 = cmd->x8_bits->x3_b6;
    //     ++cmd->u;
    //     hit->x42_b5 = 1;
    //     hit->x42_b7 = 1;
    //     hit->x41_b4 = 0;
    //     hit->x41_b6 = 0;
    //     hit->x41_b5 = 0;
    //     hit->x42_b0 = 0;
    //     hit->x42_b4 = 0;
    //     hit->x41_b7 = 0;
    //     hit->hit_grabbed_victim_only = cmd->u->unk1.unk2;
    //     hit->x42_b1 = 1;
    //     hit->x42_b2 = 0;
    //     hit->x43_b2 = 0;
    //     if ((HSD_GObj_804D7838 != NULL) && (HSD_GObj_804D7838->s_link > 9U))
    //     {
    //         ftColl_8007AD18(fp, hit);
    //     }
    // }
    // ftCommon_80080484(fp);
}

void ftAction_800715EC(Fighter_GObj* gobj, CommandInfo* cmd)
{
    SKIP_CMD(cmd, 5);
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
void ftAction_8007162C(Fighter_GObj* gobj, CommandInfo* cmd)
{
    HitCapsule* hit = &GET_FIGHTER(gobj)->x914[cmd->u->set_hitbox_damage.idx];
    ftColl_8007ABD0(hit, cmd->u->set_hitbox_damage.value, gobj);
    NEXT_CMD(cmd);
}

void ftAction_8007168C(Fighter_GObj* gobj, CommandInfo* cmd)
{
    NEXT_CMD(cmd);
}

void ftAction_8007169C(Fighter_GObj* gobj, CommandInfo* cmd)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HitCapsule* hit = &fp->x914[cmd->u->set_hitbox_scale.idx];
    hit->scale = 0.003906f * cmd->u->set_hitbox_scale.value;
    NEXT_CMD(cmd);
}

void ftAction_800716F8(Fighter_GObj* gobj, CommandInfo* cmd)
{
    NEXT_CMD(cmd);
}

void ftAction_80071708(Fighter_GObj* gobj, CommandInfo* cmd)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HitCapsule* hit = &fp->x914[cmd->u->unk22.idx];
    switch (cmd->u->unk22.type) {
    case 0:
        hit->x42_b5 = cmd->u->unk22.value;
        break;
    case 1:
        hit->x42_b7 = cmd->u->unk22.value;
        break;
    }
    NEXT_CMD(cmd);
}

void ftAction_80071774(Fighter_GObj* gobj, CommandInfo* cmd)
{
    NEXT_CMD(cmd);
}

void ftAction_80071784(Fighter_GObj* gobj, CommandInfo* cmd)
{
    ftColl_8007AFC8(gobj, cmd->u->unk2.hit_idx);
    NEXT_CMD(cmd);
}

void ftAction_800717C8(Fighter_GObj* gobj, CommandInfo* cmd)
{
    NEXT_CMD(cmd);
}

void ftAction_800717D8(Fighter_GObj* gobj, CommandInfo* cmd)
{
    ftColl_8007AFF8(gobj);
    NEXT_CMD(cmd);
}

void ftAction_80071810(Fighter_GObj* gobj, CommandInfo* cmd)
{
    NEXT_CMD(cmd);
}

/// Set one of #Fighter::cmd_vars
/// @todo Heavily suggests that #Fighter::cmd_vars is not an array.
void ftAction_80071820(Fighter_GObj* gobj, CommandInfo* cmd)
{
    Fighter* fp = GET_FIGHTER(gobj);

    switch (cmd->u->set_cmd_var.idx) {
    case 0:
        fp->cmd_vars[0] = cmd->u->set_cmd_var.value;
        break;
    case 1:
        fp->cmd_vars[1] = cmd->u->set_cmd_var.value;
        break;
    case 2:
        fp->cmd_vars[2] = cmd->u->set_cmd_var.value;
        break;
    case 3:
        fp->cmd_vars[3] = cmd->u->set_cmd_var.value;
        break;
    }
    NEXT_CMD(cmd);
}

void ftAction_800718A4(Fighter_GObj* gobj, CommandInfo* cmd)
{
    Fighter* fp = GET_FIGHTER(gobj);
    switch (cmd->u->unk2.hit_idx) {
    case 0:
        fp->throw_flags_b3 = true;
        fp->x2214 = cmd->timer;
        break;
    case 1:
        fp->throw_flags_b4 = true;
        break;
    }
    NEXT_CMD(cmd);
}

void ftAction_80071908(Fighter_GObj* gobj, CommandInfo* cmd)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->throw_flags_b1 = true;
    NEXT_CMD(cmd);
}

void ftAction_8007192C(Fighter_GObj* gobj, CommandInfo* cmd)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->throw_flags_b2 = true;
    NEXT_CMD(cmd);
}

/// Allow interrupt
void ftAction_80071950(Fighter_GObj* gobj, CommandInfo* cmd)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->allow_interrupt = true;
    NEXT_CMD(cmd);
}

void ftAction_80071974(Fighter_GObj* gobj, CommandInfo* cmd)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->throw_flags_b0 = true;
    NEXT_CMD(cmd);
}

void ftAction_80071998(Fighter_GObj* gobj, CommandInfo* cmd)
{
    Fighter* fp = GET_FIGHTER(gobj);
    switch (cmd->u->unk7.unk1) {
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
    NEXT_CMD(cmd);
}

void ftAction_80071A14(Fighter_GObj* gobj, CommandInfo* cmd)
{
    ftColl_8007B62C(gobj, cmd->u->unk7.unk1);
    NEXT_CMD(cmd);
}

void ftAction_80071A58(Fighter_GObj* gobj, CommandInfo* cmd)
{
    ftColl_8007B0C0(gobj, cmd->u->unk7.unk1);
    NEXT_CMD(cmd);
}

/// Set hurt capsule state
void ftAction_80071A9C(Fighter_GObj* gobj, CommandInfo* cmd)
{
    ftColl_8007B128(gobj, cmd->u->set_hurt_state.bone_idx,
                    cmd->u->set_hurt_state.state);
    NEXT_CMD(cmd);
}

void ftAction_80071AE8(Fighter_GObj* gobj, CommandInfo* cmd)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!cmd->u->unk23.disabled || fp->x197C != NULL) {
        fp->x2218_b1 = true;
    }
    NEXT_CMD(cmd);
}

void ftAction_80071B28(Fighter_GObj* gobj, CommandInfo* cmd)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x2218_b2 = cmd->u->unk24.unk0;
    NEXT_CMD(cmd);
}

void ftAction_80071B50(Fighter_GObj* gobj, CommandInfo* cmd)
{
    // int temp_r4_2;
    // char* temp_r5;
    // char* temp_r6;
    // char temp_r8;
    // u8 temp_r5_2;
    // u8 temp_r6_2;
    // char* cmd_x8 = cmd->x8;
    // Fighter* fp = gobj->user_data;

    // PAD_STACK(8);
    // temp_r8 = (s8) ((u16) *cmd_x8 >> 2U);
    // cmd->x8 = cmd_x8 + 4;
    // if (temp_r8 < 0xA) {
    //     if (temp_r8 < 7) {
    //         if (temp_r8 < 0) {
    //         } else {
    //             temp_r5 = cmd->x8;
    //             temp_r4_2 = M2C_FIELD(temp_r5, int*, 0);
    //             cmd->x8 = temp_r5 + 4;
    //             temp_r6 = cmd->x8;
    //             temp_r5_2 = M2C_FIELD(temp_r6, u8*, 2);
    //             temp_r6_2 = M2C_FIELD(temp_r6, u8*, 3);
    //             switch (temp_r8) {
    //             case 0:
    //                 ft_PlaySFX(fp, temp_r4_2, (int) temp_r5_2,
    //                            (int) temp_r6_2);
    //                 break;
    //             case 1:
    //                 ft_80088478(fp, temp_r4_2, (int) temp_r5_2,
    //                             (int) temp_r6_2);
    //                 break;
    //             case 2:
    //                 ft_800881D8(fp, (u32) temp_r4_2, (u32) temp_r5_2,
    //                             (u32) temp_r6_2);
    //                 break;
    //             case 3:
    //                 ft_80088510(fp, temp_r4_2, temp_r5_2, temp_r6_2);
    //                 break;
    //             case 4:
    //                 ft_800885A8(fp, temp_r4_2, temp_r5_2, temp_r6_2);
    //                 break;
    //             case 5:
    //                 ft_80088640(fp, temp_r4_2, (int) temp_r5_2,
    //                             (int) temp_r6_2);
    //                 break;
    //             case 6:
    //                 ft_80088328(fp, temp_r4_2, (int) temp_r5_2,
    //                             (int) temp_r6_2);
    //                 break;
    //             }
    //         }
    //     }
    // } else if (temp_r8 < 0x10) {
    //     ++cmd->u;
    //     switch (temp_r8) { /* switch 1; irregular */
    //     case 10:           /* switch 1 */
    //         ft_80088828(fp);
    //         break;
    //     case 11: /* switch 1 */
    //         ft_80088770(fp);
    //         break;
    //     case 12: /* switch 1 */
    //         ft_80088884(fp);
    //         break;
    //     case 13: /* switch 1 */
    //         ft_800888E0(fp);
    //         break;
    //     case 14: /* switch 1 */
    //         ft_8008893C(fp);
    //         break;
    //     case 15: /* switch 1 */
    //         ft_800887CC(fp);
    //         break;
    //     }
    // }
    // ++cmd->u;
}

void ftAction_80071CA4(Fighter_GObj* gobj, CommandInfo* cmd)
{
    SKIP_CMD(cmd, 3);
}

void ftAction_80071CCC(Fighter_GObj* gobj, CommandInfo* cmd)
{
    Fighter* fp = GET_FIGHTER(gobj);
    FtSFX* sfx = fp->ft_data->x4C_sfx;
    FtSFXArr* sfx_smash = sfx->smash;
    if (sfx_smash == NULL) {
        NEXT_CMD(cmd);
    } else {
        ft_800889F4(fp, sfx_smash);
        NEXT_CMD(cmd);
    }
}

void ftAction_80071D30(Fighter_GObj* gobj, CommandInfo* cmd)
{
    NEXT_CMD(cmd);
}

void ftAction_80071D40(Fighter_GObj* gobj, CommandInfo* cmd)
{
    ftParts_80074B0C(gobj, cmd->u->unk25.unk0, cmd->u->unk25.unk1);
    NEXT_CMD(cmd);
}

void ftAction_80071D94(Fighter_GObj* gobj, CommandInfo* cmd)
{
    ftParts_80074A8C(gobj);
    NEXT_CMD(cmd);
}

void ftAction_80071DCC(Fighter_GObj* gobj, CommandInfo* cmd)
{
    ftParts_80074ACC(gobj);
    NEXT_CMD(cmd);
}

void ftAction_80071E04(Fighter_GObj* gobj, CommandInfo* cmd)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HitCapsule* hit = &fp->xDF4[cmd->u->unk26_0.idx];
    ftColl_8007ABD0(hit, cmd->u->unk26_0.unk0, gobj);
    ++cmd->u;

    ftColl_8007AC9C(hit, cmd->u->unk26_1.unk0, gobj);
    hit->x24 = cmd->u->unk26_1.hit_x24;
    hit->x28 = cmd->u->unk26_1.hit_x28;
    NEXT_CMD(cmd);

    hit->x2C = cmd->u->unk26_2.hit_x2C;
    hit->element = cmd->u->unk26_2.element;
    hit->sfx_severity = cmd->u->unk26_2.sfx_severity;
    hit->sfx_kind = cmd->u->unk26_2.sfx_kind;
    NEXT_CMD(cmd);
}

void ftAction_80071F0C(Fighter_GObj* gobj, CommandInfo* cmd)
{
    SKIP_CMD(cmd, 3);
}

void ftAction_80071F34(Fighter_GObj* gobj, CommandInfo* cmd)
{
    PAD_STACK(8);
    ftCommon_8007F5CC(gobj, cmd->u->unk27.value);
    NEXT_CMD(cmd);
}

void ftAction_80071F78(Fighter_GObj* gobj, CommandInfo* cmd)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x221E_b4 = cmd->u->unk28.value;
    NEXT_CMD(cmd);
}

void ftAction_80071FA0(Fighter_GObj* gobj, CommandInfo* cmd)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x221E_b5 = cmd->u->unk29.value;
    NEXT_CMD(cmd);
}

void ftAction_80071FC8(Fighter_GObj* gobj, CommandInfo* cmd)
{
    // int var_r27 = M2C_ERROR(saved_reg_r27);
    // char* cmd_x8 = cmd->x8;
    // void* fp = gobj->user_data;
    // u8 temp_r30 = (u8) ((u16) M2C_FIELD(cmd_x8, u16*, 0) >> 2U);

    // PAD_STACK(8);
    // cmd->x8 = cmd_x8 + 4;
    // {
    //     u8 temp_r29 = (u8) ((u32) M2C_FIELD(cmd_x8, u16*, 0) >> 0xAU);
    //     u32 temp_r28 = ((u16) M2C_FIELD(cmd_x8, u16*, 2) >> 6U) & 0xF;
    //     int temp_r3 = HSD_Randi(M2C_FIELD(cmd_x8, u8*, 3) & 0x3F);
    //     switch (temp_r3) { /* switch 1; irregular */
    //     case 0:            /* switch 1 */
    //     {
    //         char* cmd_x8 = cmd->x8;
    //         var_r27 = *cmd_x8;
    //         cmd->x8 = cmd_x8 + 4;
    //         ++cmd->u;
    //         ++cmd->u;
    //         ++cmd->u;
    //         ++cmd->u;
    //         break;
    //     }
    //     case 1: /* switch 1 */
    //         ++cmd->u;
    //         {
    //             char* cmd_x8 = cmd->x8;
    //             var_r27 = *cmd_x8;
    //             cmd->x8 = cmd_x8 + 4;
    //         }
    //         ++cmd->u;
    //         ++cmd->u;
    //         ++cmd->u;
    //         break;
    //     case 2: /* switch 1 */
    //         ++cmd->u;
    //         ++cmd->u;
    //         {
    //             char* cmd_x8 = cmd->x8;
    //             var_r27 = *cmd_x8;
    //             cmd->x8 = cmd_x8 + 4;
    //         }
    //         ++cmd->u;
    //         ++cmd->u;
    //         break;
    //     case 3: /* switch 1 */
    //         ++cmd->u;
    //         ++cmd->u;
    //         ++cmd->u;
    //         {
    //             char* cmd_x8 = cmd->x8;
    //             var_r27 = *cmd_x8;
    //             cmd->x8 = cmd_x8 + 4;
    //         }
    //         ++cmd->u;
    //         break;
    //     case 4: /* switch 1 */
    //         ++cmd->u;
    //         ++cmd->u;
    //         ++cmd->u;
    //         ++cmd->u;
    //         {
    //             char* cmd_x8 = cmd->x8;
    //             var_r27 = *cmd_x8;
    //             cmd->x8 = cmd_x8 + 4;
    //         }
    //         break;
    //     case 5: /* switch 1 */
    //         ++cmd->u;
    //         ++cmd->u;
    //         ++cmd->u;
    //         ++cmd->u;
    //         ++cmd->u;
    //         var_r27 = *cmd->x8;
    //         break;
    //     }
    //     ++cmd->u;
    //     switch (temp_r28) {
    //     case 0:
    //         ft_PlaySFX(fp, var_r27, (int) temp_r30, (int) temp_r29);
    //         return;
    //     case 1:
    //         ft_80088478(fp, var_r27, (int) temp_r30, (int) temp_r29);
    //         return;
    //     case 2:
    //         ft_800881D8(fp, (u32) var_r27, (u32) temp_r30, (u32) temp_r29);
    //         return;
    //     case 3:
    //         ft_80088510(fp, var_r27, temp_r30, temp_r29);
    //         return;
    //     case 4:
    //         ft_800885A8(fp, var_r27, temp_r30, temp_r29);
    //         return;
    //     case 5:
    //         ft_80088640(fp, var_r27, (int) temp_r30, (int) temp_r29);
    //         return;
    //     case 6:
    //         ft_80088328(fp, var_r27, (int) temp_r30, (int) temp_r29);
    //     /* fallthrough */
    //     default:
    //         return;
    //     }
    // }
}

void ftAction_800722C8(Fighter_GObj* gobj, CommandInfo* cmd)
{
    SKIP_CMD(cmd, 7);
}

void ftAction_80072320(Fighter_GObj* gobj, CommandInfo* cmd)
{
    // int spC;
    // int sp8;
    // float var_f31;
    // int temp_r0_2;
    // int temp_r0_3;
    // int temp_r30;
    // int temp_r5;
    // char* temp_r4;
    // u8 temp_r0;
    // u8 temp_r29;
    // Fighter* temp_r31;

    // var_f31 = M2C_ERROR(saved_reg_f31);
    // temp_r4 = cmd->x8;
    // temp_r31 = gobj->user_data;
    // temp_r0 = M2C_FIELD(temp_r4, u8*, 3);
    // temp_r29 = M2C_FIELD(temp_r4, u8*, 2);
    // temp_r30 = M2C_FIELD(temp_r4, u16*, 0) & 0x3FF;
    // switch ((int) temp_r0) { /* switch 1; irregular */
    // case 0:                  /* switch 1 */
    //     var_f31 = 0.0f;
    //     break;
    // case 1: /* switch 1 */
    //     var_f31 = 1.0f;
    //     break;
    // case 2: /* switch 1 */
    //     var_f31 = -1.0f;
    //     break;
    // case 3: /* switch 1 */
    //     var_f31 = M2C_FIELD(temp_r31, float*, 0x2C);
    //     break;
    // }
    // ++cmd->u;
    // temp_r5 = ft_80087D0C((Fighter*) temp_r31, M2C_FIELD(cmd->x8, int*, 0));
    // ++cmd->u;
    // ++cmd->u;
    // ++cmd->u;
    // switch (temp_r29) {
    // case 0:
    //     sp8 = 0;
    //     spC = -1;
    //     M2C_FIELD(temp_r31, int*, 0x2160) = lbAudioAx_800264E4(
    //         lbAudioAx_800263E8(gobj, temp_r30, temp_r5, 0x7F, var_f31));
    //     return;
    // case 1:
    //     sp8 = M2C_FIELD(temp_r31, u8*, 0xC) +
    //           (((u8) M2C_FIELD(temp_r31, u8*, 0x221F) >> 3U) & 1) + 0x36;
    //     spC = -1;
    //     M2C_FIELD(temp_r31, int*, 0x214C) = lbAudioAx_800264E4(
    //         lbAudioAx_800263E8(gobj, temp_r30, temp_r5, 0x7F, var_f31));
    //     return;
    // case 2:
    //     if (!(((u8) M2C_FIELD(temp_r31, u8*, 0x2225) >> 1U) & 1)) {
    //         sp8 = M2C_FIELD(temp_r31, u8*, 0xC) +
    //               (((u8) M2C_FIELD(temp_r31, u8*, 0x221F) >> 3U) & 1) +
    //               0x1E;
    //         spC = -1;
    //         M2C_FIELD(temp_r31, int*, 0x2144) = lbAudioAx_800264E4(
    //             lbAudioAx_800263E8(gobj, temp_r30, temp_r5, 0x7F, var_f31));
    //         return;
    //     }
    //     temp_r0_2 = M2C_FIELD(temp_r31, int*, 4);
    //     if (temp_r0_2 != 0x18) {
    //         if (temp_r0_2 < 0x18) {
    //             if (temp_r0_2 != 0xD) {
    //                 return;
    //             }
    //             goto block_21;
    //         }
    //     default:
    //         return;
    //     }
    // block_21:
    //     sp8 = M2C_FIELD(temp_r31, u8*, 0xC) +
    //           (((u8) M2C_FIELD(temp_r31, u8*, 0x221F) >> 3U) & 1) + 0x1E;
    //     spC = -1;
    //     M2C_FIELD(temp_r31, int*, 0x2144) = lbAudioAx_800264E4(
    //         lbAudioAx_800263E8(gobj, temp_r30, temp_r5, 0x7F, var_f31));
    //     return;
    // case 3:
    //     sp8 = M2C_FIELD(temp_r31, u8*, 0xC) +
    //           (((u8) M2C_FIELD(temp_r31, u8*, 0x221F) >> 3U) & 1) + 0x42;
    //     spC = -1;
    //     M2C_FIELD(temp_r31, int*, 0x2150) = lbAudioAx_800264E4(
    //         lbAudioAx_800263E8(gobj, temp_r30, temp_r5, 0x7F, var_f31));
    //     return;
    // case 4:
    //     sp8 = M2C_FIELD(temp_r31, u8*, 0xC) +
    //           (((u8) M2C_FIELD(temp_r31, u8*, 0x221F) >> 3U) & 1) + 0x4E;
    //     spC = -1;
    //     M2C_FIELD(temp_r31, int*, 0x2154) = lbAudioAx_800264E4(
    //         lbAudioAx_800263E8(gobj, temp_r30, temp_r5, 0x7F, var_f31));
    //     return;
    // case 5:
    //     sp8 = M2C_FIELD(temp_r31, u8*, 0xC) +
    //           (((u8) M2C_FIELD(temp_r31, u8*, 0x221F) >> 3U) & 1) + 0x5A;
    //     spC = -1;
    //     M2C_FIELD(temp_r31, int*, 0x2158) = lbAudioAx_800264E4(
    //         lbAudioAx_800263E8(gobj, temp_r30, temp_r5, 0x7F, var_f31));
    //     return;
    // case 6:
    //     if (!(((u8) M2C_FIELD(temp_r31, u8*, 0x2225) >> 1U) & 1)) {
    //         sp8 = M2C_FIELD(temp_r31, u8*, 0xC) +
    //               (((u8) M2C_FIELD(temp_r31, u8*, 0x221F) >> 3U) & 1) +
    //               0x2A;
    //         spC = -1;
    //         M2C_FIELD(temp_r31, int*, 0x2148) = lbAudioAx_800264E4(
    //             lbAudioAx_800263E8(gobj, temp_r30, temp_r5, 0x7F, var_f31));
    //         return;
    //     }
    //     temp_r0_3 = M2C_FIELD(temp_r31, int*, 4);
    //     if (temp_r0_3 != 0x18) {
    //         if (temp_r0_3 < 0x18) {
    //             if (temp_r0_3 != 0xD) {
    //                 return;
    //             }
    //             goto block_31;
    //         }
    //     } else {
    //     block_31:
    //         sp8 = temp_r31->player_id + temp_r31->x221F_b4 + 0x2A;
    //         spC = -1;
    //         M2C_FIELD(temp_r31, int*, 0x2148) = lbAudioAx_800264E4(
    //             lbAudioAx_800263E8(gobj, temp_r30, temp_r5, 0x7F, var_f31));
    //     }
    //     break;
    // }
}

void ftAction_800726C0(Fighter_GObj* gobj, CommandInfo* cmd)
{
    SKIP_CMD(cmd, 4);
}

void ftAction_800726F4(Fighter_GObj* gobj, CommandInfo* cmd)
{
    ftAnim_800704F0(gobj, cmd->u->unk30.i0, cmd->u->unk30.f);
    if (cmd->u->unk30.b) {
        ftAnim_800704F0(gobj, cmd->u->unk30.i1, cmd->u->unk30.f);
    }
    NEXT_CMD(cmd);
}

void ftAction_800727C8(Fighter_GObj* gobj, CommandInfo* cmd)
{
    ftAnim_ApplyPartAnim(gobj, cmd->u->part_anim.unk1, cmd->u->part_anim.unk2,
                         cmd->u->part_anim.unk3);
    NEXT_CMD(cmd);
}

void ftAction_8007283C(Fighter_GObj* gobj, CommandInfo* cmd)
{
    ftAnim_ApplyPartAnim(gobj, cmd->u->part_anim.unk1, cmd->u->part_anim.unk2,
                         0.0f);
    NEXT_CMD(cmd);
}

void ftAction_80072894(Fighter_GObj* gobj, CommandInfo* cmd)
{
    ftCommon_8007E83C(gobj, cmd->u->unk9.unk1, cmd->u->unk9.unk2);
    NEXT_CMD(cmd);
}

void ftAction_800728F8(Fighter_GObj* gobj, CommandInfo* cmd)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (cmd->u->unk10.unk1) {
        ftCommon_8007EC30(cmd->u->unk10.unk2, cmd->u->unk10.unk3);
    } else {
        ftCommon_8007EBAC(fp, cmd->u->unk10.unk2, cmd->u->unk10.unk3);
    }
    NEXT_CMD(cmd);
}

void ftAction_8007296C(Fighter_GObj* gobj, CommandInfo* cmd)
{
    NEXT_CMD(cmd);
}

void ftAction_8007297C(Fighter_GObj* gobj, CommandInfo* cmd)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007ECD4(fp, cmd->u->unk11.unk1);
    NEXT_CMD(cmd);
}

void ftAction_800729C4(Fighter_GObj* gobj, CommandInfo* cmd)
{
    NEXT_CMD(cmd);
}

void ftAction_800729D4(Fighter_GObj* gobj, CommandInfo* cmd)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int unk2 = cmd->u->unk12.unk2;
    int unk3 = cmd->u->unk12.unk3;
    switch (cmd->u->unk12.unk1) {
    case 0:
        ftCommon_8007EEC8(fp, unk2, unk3);
        break;
    case 1:
        ftCommon_8007EF5C(fp, unk2);
        break;
    }
    NEXT_CMD(cmd);
}

void ftAction_80072A4C(Fighter_GObj* gobj, CommandInfo* cmd)
{
    NEXT_CMD(cmd);
}

void ftAction_80072A5C(Fighter_GObj* gobj, CommandInfo* cmd)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_800BFFD0(fp, cmd->u->unk13.unk1, cmd->u->unk13.unk2);
    NEXT_CMD(cmd);
}

void ftAction_80072AAC(Fighter_GObj* gobj, CommandInfo* cmd)
{
    NEXT_CMD(cmd);
}

void ftAction_80072ABC(Fighter_GObj* gobj, CommandInfo* cmd)
{
    ftCo_800C0200(GET_FIGHTER(gobj), cmd->u->unk14.unk1);
    NEXT_CMD(cmd);
}

void ftAction_80072B04(Fighter_GObj* gobj, CommandInfo* cmd)
{
    NEXT_CMD(cmd);
}

void ftAction_80072B14(Fighter_GObj* gobj, CommandInfo* cmd)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x221E_b1 = cmd->u->unk15.unk1;
    NEXT_CMD(cmd);
}

void ftAction_80072B3C(Fighter_GObj* gobj, CommandInfo* cmd)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x2100 = cmd->u->unk16.unk4;
    fp->x2101_bits_8 = cmd->u->unk16.unk3;
    NEXT_CMD(cmd);
}

void ftAction_80072B84(Fighter_GObj* gobj, CommandInfo* cmd)
{
    NEXT_CMD(cmd);
}

void ftAction_80072B94(Fighter_GObj* gobj, CommandInfo* cmd)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_8009E318(gobj, cmd->u->unk17.unk1, fp->cur_anim_frame);
    NEXT_CMD(cmd);
}

void ftAction_80072BE4(Fighter_GObj* gobj, CommandInfo* cmd)
{
    NEXT_CMD(cmd);
}

void ftAction_80072BF4(Fighter_GObj* gobj, CommandInfo* cmd)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_TakeDamage_8006CC7C(fp, cmd->u->unk18.damage_amount);
    NEXT_CMD(cmd);
}

void ftAction_80072C5C(Fighter_GObj* gobj, CommandInfo* cmd)
{
    NEXT_CMD(cmd);
}

void ftAction_80072C6C(Fighter_GObj* gobj, CommandInfo* cmd)
{
    ft_8008A1B8(gobj, cmd->u->unk19.unk1);
    NEXT_CMD(cmd);
}

void ftAction_80072CB0(Fighter_GObj* gobj, CommandInfo* cmd)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x2225_b2 = cmd->u->unk20.unk1;
    NEXT_CMD(cmd);
}

void ftAction_80072CD8(Fighter_GObj* gobj, CommandInfo* cmd)
{
    // IntVec3 ivec1;
    // int* sp40;
    // UNK_T sp38;
    // IntVec3 ivec0;
    // Vec3 vec1;
    // Vec3 vec0;
    // u8 var_r5;
    // Fighter* fp = gobj->user_data;
    // ivec1.y = 1;
    // if (ft_80084BFC(gobj, &ivec1.z, &ivec1.y) != 0) {
    //     if (ivec1.z != -1) {
    //         sp40 = &ivec0.x;
    //         ivec0.x = M2C_FIELD(cmd->x8, int*, 0);
    //         ivec0.y = ivec1.z;
    //         ivec0.z = M2C_FIELD(cmd->x8, int*, 8);
    //         ftAction_80071B50(gobj, (CommandInfo*) &sp38);
    //     }
    //     if (ivec1.x != -1) {
    //         vec1.z = 0.0f;
    //         vec0.z = 0.0f;
    //         vec1.y = 0.0f;
    //         vec0.y = 0.0f;
    //         vec1.x = 0.0f;
    //         vec0.x = 0.0f;
    //         if (!(((u8) M2C_FIELD(cmd->x8, u8*, 1) >> 1U) & 1)) {
    //             var_r5 = fp->ft_data->x8->x13;
    //         } else {
    //             var_r5 = fp->ft_data->x8->x14;
    //         }
    //         ftCo_8009F834(gobj, (int) ivec1.x, var_r5, 0, 0, &vec1, &vec0,
    //                       0.0f);
    //     }
    // }
    // if (ivec1.y != 0) {
    //     ftAction_80071B50(gobj, cmd);
    //     return;
    // }
    // SKIP_CMD(cmd, 3);
}

void ftAction_80072E24(Fighter_GObj* gobj, CommandInfo* cmd)
{
    SKIP_CMD(cmd, 3);
}

void ftAction_80072E4C(Fighter_GObj* gobj, CommandInfo* cmd)
{
    // IntVec3 ivec1; /* compiler-managed */
    // int* sp40;
    // UNK_T sp38;
    // IntVec3 ivec0;
    // Fighter* fp = gobj->user_data;
    // Vec3 vec1;
    // Vec3 vec0;

    // PAD_STACK(24);

    // ivec1.y = 1;
    // ivec1.x = -1;
    // {
    //     char* temp_r7 = cmd->x8;
    //     int temp_r29 = M2C_FIELD(temp_r7, u8*, 1) & 1;
    //     if ((ft_80084C38(gobj, &ivec1.z, &ivec1.y, &ivec1.x, temp_r7) != 0)
    //     &&
    //         (temp_r29 == 0) && (ivec1.z != -1))
    //     {
    //         sp40 = &ivec0.x;
    //         ivec0.x = M2C_FIELD(cmd->x8, int*, 0);
    //         ivec0.y = ivec1.z;
    //         ivec0.z = M2C_FIELD(cmd->x8, int*, 8);
    //         ftAction_80071B50(gobj, (CommandInfo*) &sp38);
    //     }
    //     if ((int) ivec1.x == -1) {
    //         ivec1.x = (int) M2C_FIELD(cmd->x8, u16*, 2);
    //     }
    //     vec1.z = 0.0f;
    //     vec0.z = 0.0f;
    //     vec1.y = 0.0f;
    //     vec0.y = 0.0f;
    //     vec1.x = 0.0f;
    //     vec0.x = 0.0f;
    //     ftCo_8009F834(gobj, ivec1.x, 0, 0, 0, &vec1, &vec0, 0.0f);
    //     if (ivec1.y != 0) {
    //         ft_PlaySFX(fp, 0x46, 0x7F, 0x40);
    //         if (temp_r29 == 0) {
    //             ftAction_80071B50(gobj, cmd);
    //         }
    //     }
    //     if ((ivec1.y == 0) || (temp_r29 != 0)) {
    //         SKIP_CMD(cmd, 3);
    //     }
    //     ftCommon_8007EBAC(fp, 0x16U, 0U);
    // }
}

void ftAction_80072FE0(Fighter_GObj* gobj, CommandInfo* cmd)
{
    SKIP_CMD(cmd, 3);
}

void ftAction_80073008(Fighter_GObj* gobj, CommandInfo* cmd)
{
    // s16 temp = cmd->u->unk31.unk1;
    // NEXT_CMD(cmd);
    // {
    //     char* temp_r6 = cmd->x8;
    //     u8 temp_r5 = (u8) M2C_FIELD(temp_r6, s8*, 0);
    //     cmd->x8 = temp_r6 + 4;
    //     // ftCo_800DEE84((int) (float) temp_r5, temp_r5, temp_r6, temp,
    //     //               (float) temp, 0.003906f * cmd->u->unk31.unk1);
    // }
}

void ftAction_8007309C(Fighter_GObj* gobj, CommandInfo* cmd)
{
    SKIP_CMD(cmd, 2);
}

void ftAction_800730B8(Fighter_GObj* gobj, CommandInfo* cmd)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_800C8B60(fp, cmd->u->unk21.unk1, cmd->u->unk21.unk2);
    NEXT_CMD(cmd);
}

void ftAction_80073108(Fighter_GObj* gobj, CommandInfo* cmd)
{
    NEXT_CMD(cmd);
}

void ftAction_80073118(Fighter_GObj* gobj, CommandInfo* cmd)
{
    // char* temp_r5 = cmd->x8;
    // u8 temp_r10 = M2C_FIELD(temp_r5, u8*, 3);
    // cmd->x8 = temp_r5 + 4;
    // {
    //     char* cmd_x8 = cmd->x8;
    //     cmd->x8 = cmd_x8 + 4;
    //     {
    //         char* cmd_x8 = cmd->x8;
    //         cmd->x8 = cmd_x8 + 4;
    //         {
    //             char* cmd_x8 = cmd->x8;
    //             cmd->x8 = cmd_x8 + 4;
    //             // ftCo_8009E714(temp_r10, M2C_FIELD(cmd_x8, s16*, 0),
    //             cmd_x8,
    //             //               temp_r10, 0.003906f * M2C_FIELD(cmd_x8,
    //             s16*,
    //             //               0), 0.003906f * M2C_FIELD(cmd_x8, s16*, 2),
    //             //               0.003906f * M2C_FIELD(cmd_x8, s16*, 0),
    //             //               0.003906f * M2C_FIELD(cmd_x8, s16*, 2),
    //             //               0.003906f * M2C_FIELD(cmd_x8, s16*, 2),
    //             //               0.003906f);
    //         }
    //     }
    // }
}

void ftAction_8007320C(Fighter_GObj* gobj, CommandInfo* cmd)
{
    SKIP_CMD(cmd, 4);
}

void ftAction_80073240(Fighter_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    CommandInfo* ftCommand = &fp->x3E4_fighterCmdScript;
    u32 eventCode;
    fp->x3E4_fighterCmdScript.frame_count = fp->cur_anim_frame + fp->x898_unk;
    if (fp->x3E4_fighterCmdScript.u != NULL) {
        if (ftCommand->timer != F32_MAX) {
            ftCommand->timer -= fp->frame_speed_mul;
        }
        do {
            if (ftCommand->u == NULL) {
                break;
            }
            if (F32_MAX == ftCommand->timer) {
                if (ftCommand->frame_count >= fp->frame_speed_mul) {
                    break;
                }
                ftCommand->timer = -ftCommand->frame_count;
            } else if (ftCommand->timer > 0.0f) {
                break;
            }
            eventCode =
                gmScriptEventCast(ftCommand->u, gmScriptEventDefault)->opcode;
            if (Command_Execute((CommandInfo*) ftCommand, eventCode) == false)
            {
                eventCode -= 0xA;
                ftAction_803C06E8[eventCode](fighter_gobj,
                                             (CommandInfo*) ftCommand);
            }
        } while (F32_MAX != ftCommand->timer);
    }
}

void ftAction_80073354(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    CommandInfo* cmd = (CommandInfo*) &fp->x3E4_fighterCmdScript;
    fp->x3E4_fighterCmdScript.timer = fp->cur_anim_frame + fp->x898_unk;
    fp->throw_flags = 0;
    if (fp->x3E4_fighterCmdScript.u != NULL) {
        float timer = cmd->timer;
        if (timer != F32_MAX) {
            cmd->timer = timer - fp->frame_speed_mul;
        }
    loop_4:
        if ((u8*) cmd->u != NULL) {
            float timer = cmd->timer;
            if (timer == F32_MAX) {
                float frame_count = cmd->frame_count;
                if (!(frame_count >= fp->frame_speed_mul)) {
                    cmd->timer = -frame_count;
                    goto block_9;
                }
            } else if (!(timer > 0.0f)) {
            block_9: {
                float timer = cmd->timer;
                u32 temp_r28 = 0;
                // u32 temp_r28 = ((u8) *cmd->u->data_position >> 2U) & 0x3F;
                if (!Command_Execute(cmd, temp_r28)) {
                    ftAction_803C07AC[temp_r28 - 0xA](gobj,
                                                      (CommandInfo*) cmd);
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

void ftAction_8007349C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    CommandInfo* cmd = (CommandInfo*) &fp->x3E4_fighterCmdScript;
    PAD_STACK(8);
    fp->x3E4_fighterCmdScript.frame_count = fp->cur_anim_frame + fp->x898_unk;
    if (fp->x3E4_fighterCmdScript.u == NULL) {
        return;
    }
    if (cmd->timer != F32_MAX) {
        cmd->timer -= fp->frame_speed_mul;
    }
    do {
        if (cmd->u == NULL) {
            break;
        }
        if (cmd->timer == F32_MAX) {
            if (cmd->frame_count >= fp->frame_speed_mul) {
                break;
            }
            cmd->timer = -cmd->frame_count;
        } else if (cmd->timer > 0.0f) {
            break;
        }
        {
            u32 id = cmd->u->Command_09.id;
            if (!Command_Execute(cmd, id)) {
                cmd->u += ftAction_803C0870[id - 10];
            }
        }
    } while (cmd->timer != F32_MAX);
}
