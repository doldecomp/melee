#include "itanimlist.h"

#include "it_2725.h"
#include "it_3F14.h"
#include "iteffect.h"
#include "ithitbox.h"

#include "it/forward.h"

#include "it/inlines.h"
#include "it/itcoll.h"
#include "it/item.h"
#include "lb/inlines.h"
#include "lb/lbcommand.h"
#include "lb/lbspdisplay.h"

#include <baselib/gobjproc.h>

static void sdata2_order(void)
{
    (void) 0.00390599994f;
    (void) 4503599627370496.0;
    (void) 4503601774854144.0;
    (void) 1.0f;
    (void) 0.0f;
    (void) 3.40282347e+38f;
}

ItCmd it_803F22A8[16] = {
    it_80278F2C, it_802790C0, it_80279544, it_802795EC,
    it_80279680, it_802796C4, it_8027978C, it_802796FC,
    it_80279720, it_80279744, it_80279768, it_80279888,
    it_802798D4, it_8027990C, it_80279958, it_802799A8,
};

typedef struct itAnimlistCmdUnk {
    u16 x0_b0 : 6;
    u16 opcode : 8;
    u16 x0_b14 : 2;
    u16 x2;
} itAnimlistCmdUnk;

void it_80278F2C(Item_GObj* item_gobj, CommandInfo* cmd)
{
    Vec3 sp20;
    Vec3 sp14;
    s32 arg2;
    u16 ef_id;
    s32 arg6;
    PAD_STACK(4);

    arg2 = ((u16*) cmd->u)[0];
    arg2 = arg2 & 0x3FF;
    ++cmd->u;
    arg6 = (f32) ((u16*) cmd->u)[1];
    ef_id = ((u16*) cmd->u)[0];
    ++cmd->u;
    sp20.x = 0.003906f * ((s16*) cmd->u)[0];
    sp20.y = 0.003906f * ((s16*) cmd->u)[1];
    ++cmd->u;
    sp20.z = 0.003906f * ((s16*) cmd->u)[0];
    sp14.x = 0.003906f * ((s16*) cmd->u)[1];
    ++cmd->u;
    sp14.y = 0.003906f * ((s16*) cmd->u)[0];
    sp14.z = 0.003906f * ((s16*) cmd->u)[1];
    ++cmd->u;
    it_80278800(item_gobj, ef_id, arg2, &sp20, &sp14, 0, arg6);
}

#pragma push
#pragma dont_inline on

void it_802790C0(Item_GObj* item_gobj, CommandInfo* cmd)
{
    u8 _padA[16];
    Item* item = item_gobj->user_data;
    struct ItemHitbox* hb;
    HitCapsule* hit;
    union CmdUnion* u = cmd->u;
    u32 hitbox_idx = u->it_create_hitbox_0.id;
    u32 x4 = u->it_create_hitbox_0.hit_group;
    u32 bone_idx;
    hb = &item->x5D4_hitboxes[hitbox_idx];
    hit = &hb->hit;

    if (hit->state == HitCapsule_Disabled || hit->x4 != x4) {
        hit->x4 = x4;
        hit->state = HitCapsule_Enabled;
        item->xDC8_word.flags.x16 = 1;
        item->xDAA_flag.b2 = 0;
        it_8026FCF8(item, hit);
    }

    bone_idx = cmd->u->it_create_hitbox_0.bone;
    if (bone_idx != 0) {
        if (item->xBBC_dynamicBoneTable == NULL) {
            HSD_ASSERTREPORT(0x8B, 0, "item can\'t set attack!\n");
        }
        hit->jobj = item->xBBC_dynamicBoneTable->bones[bone_idx];
    } else {
        hit->jobj = item_gobj->hsd_obj;
    }
    it_80272460(hit,
                item->xC3C *
                    ((f32) cmd->u->it_create_hitbox_0.damage * item->xC40),
                item_gobj);
    ++cmd->u;

    hit->scale = 0.003906f * cmd->u->create_hitbox_1.size;
    item->x3C = hit->scale;
    it_80275594(item_gobj, hitbox_idx, 1.0f / item->scl);
    hit->b_offset.x = 0.003906f * cmd->u->create_hitbox_1.z_offset;
    ++cmd->u;
    hit->b_offset.y = 0.003906f * cmd->u->create_hitbox_2.y_offset;
    hit->b_offset.z = 0.003906f * cmd->u->create_hitbox_2.x_offset;
    ++cmd->u;

    hit->kb_angle = cmd->u->create_hitbox_3.angle;
    hit->x24 = cmd->u->create_hitbox_3.knockback_growth;
    hit->x28 = cmd->u->create_hitbox_3.weight_set_knockback;
    hit->x43_b1 = 0;
    ++cmd->u;

    hit->x2C = cmd->u->it_create_hitbox_4.base_knockback;
    hit->element = cmd->u->it_create_hitbox_4.element;
    hit->x40_b0 = cmd->u->it_create_hitbox_4.x40_b0;
    hit->x40_b1 = 0;
    hit->x34 = cmd->u->it_create_hitbox_4.shield_damage;
    hit->sfx_severity = cmd->u->it_create_hitbox_4.sfx_severity;
    hit->sfx_kind = cmd->u->it_create_hitbox_4.sfx_kind;
    hit->x40_b2 = cmd->u->it_create_hitbox_4.x40_b2;
    hit->x40_b3 = cmd->u->it_create_hitbox_4.x40_b3;
    ++cmd->u;

    hit->x40_b4 = ((u8*) cmd->u)[0];
    hit->x41_b4 = (((u8*) cmd->u)[1] >> 7) & 1;
    hit->x41_b5 = (((u8*) cmd->u)[1] >> 6) & 1;
    hit->x41_b6 = (((u8*) cmd->u)[1] >> 5) & 1;
    hit->x41_b7 = (((u8*) cmd->u)[1] >> 4) & 1;
    hit->x42_b0 = (((u8*) cmd->u)[1] >> 3) & 1;
    hit->x42_b1 = (((u8*) cmd->u)[1] >> 2) & 1;
    hit->x42_b2 = (((u8*) cmd->u)[1] >> 1) & 1;
    hit->x42_b3 = ((u8*) cmd->u)[1] & 1;
    hit->x42_b4 = (((u8*) cmd->u)[2] >> 7) & 1;
    hit->x42_b5 = (((u8*) cmd->u)[2] >> 6) & 1;
    hit->x42_b6 = (((u8*) cmd->u)[2] >> 5) & 1;
    hit->x42_b7 = (((u8*) cmd->u)[2] >> 4) & 1;
    hit->x43_b0 = (((u8*) cmd->u)[2] >> 3) & 1;
    hb->x138 = (((u8*) cmd->u)[2] >> 2) & 1;
    ++cmd->u;

    hit->x43_b2 = 0;
    if (HSD_GObj_804D7838 != NULL && HSD_GObj_804D7838->s_link > 11) {
        it_8027129C(item_gobj, hitbox_idx);
    }
}

#pragma pop

#pragma push
#pragma dont_inline on

void it_80279544(Item_GObj* item_gobj, CommandInfo* cmd)
{
    Item* item = item_gobj->user_data;
    HitCapsule* hit = &item->x5D4_hitboxes[cmd->u->set_hitbox_damage.idx].hit;
    u32 val = ((u16*) cmd->u)[1] & 0x1FFF;
    PAD_STACK(8);
    it_80272460(hit, (u32) (item->xC3C * ((f32) val * item->xC40)), item_gobj);
    ++cmd->u;
}

void it_802795EC(Item_GObj* item_gobj, CommandInfo* cmd)
{
    s32 idx = cmd->u->set_hitbox_scale.idx;
    Item* item = item_gobj->user_data;
    HitCapsule* hit = &item->x5D4_hitboxes[idx].hit;
    PAD_STACK(8);
    hit->scale = 0.003906f * cmd->u->set_hitbox_scale.value;
    item->x3C = hit->scale;
    it_80275594(item_gobj, idx, 1.0f / item->scl);
    ++cmd->u;
}

#pragma pop

#pragma push
#pragma dont_inline on

void it_80279680(Item_GObj* item_gobj, CommandInfo* cmd)
{
    it_80272560(item_gobj, cmd->u->set_throw_flags.hit_idx);
    ++cmd->u;
}

void it_802796C4(Item_GObj* item_gobj, CommandInfo* cmd)
{
    it_802725D4(item_gobj);
    ++cmd->u;
}

#pragma pop

void it_802796FC(Item_GObj* item_gobj, CommandInfo* cmd)
{
    Item* it = GET_ITEM(item_gobj);
    it->xDAC_itcmd_var0 = cmd->u->set_throw_flags.hit_idx;
    ++cmd->u;
}

void it_80279720(Item_GObj* item_gobj, CommandInfo* cmd)
{
    Item* it = GET_ITEM(item_gobj);
    it->xDB0_itcmd_var1 = cmd->u->set_throw_flags.hit_idx;
    ++cmd->u;
}

void it_80279744(Item_GObj* item_gobj, CommandInfo* cmd)
{
    Item* it = GET_ITEM(item_gobj);
    it->xDB4_itcmd_var2 = cmd->u->set_throw_flags.hit_idx;
    ++cmd->u;
}

void it_80279768(Item_GObj* gobj, CommandInfo* cmd)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDBC_itcmd_var4.flags.x0 = true;
    ++cmd->u;
}

#pragma push
#pragma dont_inline on
void it_8027978C(Item_GObj* item_gobj, CommandInfo* cmd)
{
    Item* item = item_gobj->user_data;
    itAnimlistCmdUnk* ptr = (itAnimlistCmdUnk*) cmd->u;
    s32 opcode = ptr->opcode;
    u32 arg1;
    u8 arg2;
    u8 arg3;
    PAD_STACK(8);
    cmd->u = (union CmdUnion*) (ptr + 1);
    if (opcode < 10) {
        if (opcode < 3) {
            if (opcode >= 0) {
                goto low_opcode;
            }
        }
        goto done;
    } else {
        if (opcode >= 12) {
            goto done;
        }
        goto high_opcode;
    }

low_opcode:
    arg1 = *(u32*) cmd->u;
    ++cmd->u;
    arg2 = ((u8*) cmd->u)[2];
    arg3 = ((u8*) cmd->u)[3];
    switch (opcode) {
    case 0:
        Item_8026AE84(item, arg1, arg2, arg3);
        break;
    case 1:
        Item_8026AF0C(item, arg1, arg2, arg3);
        break;
    case 2:
        Item_8026AFA0(item, arg1, arg2, arg3);
        break;
    }
    goto done;

high_opcode: {
    ++cmd->u;
    switch (opcode) {
    case 10:
        Item_8026B034(item);
        break;
    case 11:
        Item_8026B074(item);
        break;
    }
}
done:
    ++cmd->u;
}
#pragma pop

#pragma push
#pragma dont_inline on

void it_80279888(Item_GObj* item_gobj, CommandInfo* cmd)
{
    PAD_STACK(4);
    it_80273598(item_gobj, cmd->u->unk33.unk0, cmd->u->unk33.unk1);
    NEXT_CMD(cmd);
}

void it_802798D4(Item_GObj* item_gobj, CommandInfo* cmd)
{
    PAD_STACK(4);
    it_80273600(item_gobj);
    NEXT_CMD(cmd);
}

void it_8027990C(Item_GObj* item_gobj, CommandInfo* cmd)
{
    PAD_STACK(4);
    it_80273648(item_gobj, cmd->u->unk33.unk0, cmd->u->unk33.unk1);
    NEXT_CMD(cmd);
}

#pragma pop

void it_80279958(Item_GObj* item_gobj, CommandInfo* cmd)
{
    Item* it = GET_ITEM(item_gobj);
    it_80279B88(it, cmd->u->unk13.unk1, cmd->u->unk13.unk2);
    NEXT_CMD(cmd);
}

void it_802799A8(Item_GObj* item_gobj, CommandInfo* cmd)
{
    it_80279BBC(item_gobj->user_data);
    ++cmd->u;
}

void it_802799E4(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    CommandInfo* cmd = &item->x524_cmd;
    u32 opcode;

    cmd->frame_count = item->x5CC_currentAnimFrame;
    item->xDBC_itcmd_var4_word = 0;

    if (cmd->u == NULL) {
        return;
    }

    if (cmd->timer != F32_MAX) {
        cmd->timer -= item->x5D0_animFrameSpeed;
    }

loop:
    if (cmd->u == NULL) {
        return;
    }
    if (cmd->timer == F32_MAX) {
        if (cmd->frame_count >= item->x5D0_animFrameSpeed) {
            return;
        }
        cmd->timer = -cmd->frame_count;
    } else if (cmd->timer > 0.0f) {
        return;
    }

    opcode = cmd->u->unk0.opcode;
    if (Command_Execute(cmd, opcode) != 0) {
        goto loop;
    }
    opcode -= 10;
    it_803F22A8[opcode](item_gobj, cmd);
    goto loop;
}

#pragma push
#pragma dont_inline on

void it_80279AF0(Item_GObj* item_gobj, CommandInfo* cmd)
{
    it_80278F2C(item_gobj, (CommandInfo*) cmd);
}

#pragma pop

void it_80279B10(Item_GObj* item_gobj, CommandInfo* cmd)
{
    it_8027978C(item_gobj, cmd);
}

static ItCmd it_804D51C8[2] ATTRIBUTE_ALIGN(8) = {
    it_80279AF0,
    it_80279B10,
};

void fn_80279B30(Item_GObj* item_gobj, CommandInfo* cmd, int arg2)
{
    int idx = arg2 - 21;
    it_804D51C8[idx](item_gobj, cmd);
}

void it_80279B64(Item* item)
{
    lb_80014498(&item->x548_colorOverlay);
}

void it_80279B88(Item* item, s32 arg1, s32 arg2)
{
    lb_800144C8(&item->x548_colorOverlay, it_804D6D04, arg1, arg2);
}

void it_80279BBC(Item* item)
{
    lb_80014498(&item->x548_colorOverlay);
}

void it_80279BE0(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    while (lb_80014258(item_gobj, &item->x548_colorOverlay, fn_80279B30)) {
        lb_80014498(&item->x548_colorOverlay);
    }
}
