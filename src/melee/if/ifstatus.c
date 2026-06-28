#include "ifstatus.h"

#include "ifall.h"
#include "m2c_macros.h"
#include "placeholder.h"

#include "gm/gm_unsplit.h"
#include "gm/types.h"
#include "if/if_2F72.h"
#include "if/ifcoget.h"
#include "if/ifstock.h"
#include "if/types.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "lb/lbarchive.h"
#include "lb/lbaudio_ax.h"
#include "mn/mnmain.h"
#include "pl/player.h"
#include "sc/types.h"

#include <baselib/aobj.h>
#include <baselib/dobj.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjplink.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>
#include <baselib/mobj.h>
#include <baselib/mtx.h>
#include <baselib/random.h>
#include <baselib/tobj.h>

typedef struct FlagsX {
    u32 b80 : 1;
    u32 b40 : 1;
    u32 b20 : 1;
    u32 b10 : 1;
    u32 b8 : 1;
    u32 b4 : 2;
    u32 b1 : 1;
    u8 x;
    u16 y;
} FlagsX;

typedef struct UnkX {
    u8 filler1[0x10];
    FlagsX x10_flags;
    u8 filler2[0x34 - 0x14];
    Vec4 x34_vec; // or float[4] instead of Vec4
    Vec4 x44_vec;
    HSD_JObj* x54_jobj[4];
} UnkX; // HudIndex

/* 2F491C */ static void ifStatus_PercentOnDeathAnimationThink(UnkX* value,
                                                               s32, s32);
/* 3F9628 */ Element_803F9628 ifStatus_803F9628[8] = {
    { NULL, 0, if_802F74D0, 0x7C860U, 8, 0, { 0 }, 0, NULL, NULL, 0, 0 },
    { NULL, 0, if_802F73C4, 0xC351U, 0, 0, { 0 }, 0, NULL, NULL, 0, 0 },
    { NULL, 0, if_802F74D0, 0x7C85EU, 0, 0, { 0 }, 0, NULL, NULL, 0, 0 },
    { NULL, 0, if_802F73C4, 0x7C85DU, 0, 0, { 0 }, 0, NULL, NULL, 0, 0 },
    { NULL, 0, if_802F73C4, 0x7C857U, 10, 0, { 0 }, 0, NULL, NULL, 0, 0 },
    { NULL, 0, if_802F74D0, 0x7C855U, 8, 0, { 0 }, 0, NULL, NULL, 0, 0 },
    { NULL, 0, if_802F74D0, 0x9C48U, 0, 0, { 0 }, 0, NULL, NULL, 0, 0 },
    { NULL, 0, if_802F74D0, 0x9C46U, 0, 0, { 0 }, 0, NULL, NULL, 0, 0 },
};
/* 4D6D60 */ static u8 ifStatus_804D6D60;
/* 4D6D61 */ static s8 ifStatus_804D6D61;

HudIndex* ifStatus_802F4910(void)
{
    return &ifStatus_HudInfo;
}

/// "jobj.h" @ lbl_804D57B0
/// "jobj" @ lbl_804D57B8
#define ASSERT_NOT_NULL(value, line)                                          \
    if (value == NULL) {                                                      \
        __assert("jobj.h", line, "jobj");                                     \
    }

static inline float foo(float a, float b)
{
    float result;
    if (ifStatus_804D6D61 != 0) {
        result = -a - b;
        ifStatus_804D6D61 = 0;
    } else {
        result = a + b;
        ifStatus_804D6D61 = 1;
    }
    return result;
}

static inline void
jobj_flagCheckSetMtxDirtySub(HSD_JObj* jobj) // jobj @ r30 when inlined
{
    //@12c
    if (!(jobj->flags & 0x02000000) && jobj) {
        //@140
        ASSERT_NOT_NULL(jobj, 0x234);
        //@154
        if ((!(jobj->flags & 0x800000) && (jobj->flags & 0x40)) == 0) {
            //@178
            HSD_JObjSetMtxDirtySub(jobj);
        }
    }
}

inline void jobj_translate_x(HSD_JObj* jobj, float dx);
inline void jobj_translate_y(HSD_JObj* jobj, float dy);

inline void jobj_unk_x(UnkX* value, s32 i)
{
    HSD_JObj* jobj_r30 = value->x54_jobj[i];
    //@c8
    ASSERT_NOT_NULL(jobj_r30, 993);
    //@e0
    if (fabsf_bitwise(jobj_r30->translate.x) <
        100.0f) { // 100.0f @ lbl_804DDA6C
        //@100
        jobj_r30 = value->x54_jobj[i];
        //@108
        jobj_translate_x(jobj_r30, (&value->x34_vec.x)[i]);
        //@12c
        jobj_flagCheckSetMtxDirtySub(jobj_r30);
    }
}

inline void jobj_unk_y(UnkX* value, s32 i)
{
    HSD_JObj* jobj_r30 = value->x54_jobj[i];
    //@184
    ASSERT_NOT_NULL(jobj_r30, 1006);
    //@19c
    if (jobj_r30->translate.y > -100.0f) { // -100.0f @ lbl_804DDA8C
        //@1a8
        jobj_r30 = value->x54_jobj[i];
        //@1b0
        jobj_translate_y(jobj_r30, (&value->x44_vec.x)[i]);

        //@1d4
        jobj_flagCheckSetMtxDirtySub(jobj_r30);
        //@228
        (&value->x44_vec.x)[i] -= 0.2028f; // gravity that makes percent tokens
                                           // fall down? @ lbl_804DDA90
    }
}

inline void jobj_translate_x(HSD_JObj* jobj, float dx)
{
    //@108
    ASSERT_NOT_NULL(jobj, 1102);
    //@120
    jobj->translate.x += dx;
}

inline void jobj_translate_y(HSD_JObj* jobj, float dy)
{
    //@1b0
    ASSERT_NOT_NULL(jobj, 1114);
    //@1c8
    jobj->translate.y += dy;
}

inline void jobj_unk(UnkX* value)
{
    //@b0
    s32 i;
    for (i = 0; i < 4; i++) // i@r31
    {
        jobj_unk_x(value, i);
        jobj_unk_y(value, i);
        //@234 loop increment
    }
}

inline void* jobj_get(HSD_JObj* jobj_r30, UnkX* value, s32 i)
{
    return value->x54_jobj[i];
}

void ifStatus_PercentOnDeathAnimationThink(UnkX* value, s32 arg1, s32 arg2)
{
    s32 i;

    if (value->x10_flags.b40) {
        for (i = 0; i < 4; i++) // i@r28
        {
            (&value->x34_vec.x)[i] =
                foo(0.6083f * HSD_Randf(), 0.3041f); // var_f0;
            (&value->x44_vec.x)[i] = 0.811f * HSD_Randf() + 1.2165f;
        }
        value->x10_flags.b40 = 0;
        return;
    }

    for (i = 0; i < 4; i++) // i@r31
    {
        HSD_JObj* jobj_r30 = value->x54_jobj[i];
        ASSERT_NOT_NULL(jobj_r30, 993);
        if (fabsf_bitwise(jobj_r30->translate.x) <
            100.0f) { // 100.0f @ lbl_804DDA6C
            float f = (&value->x34_vec.x)[i];
            jobj_r30 = (void*) jobj_get(jobj_r30, value, i);
            ASSERT_NOT_NULL(jobj_r30, 1102);
            jobj_r30->translate.x += f;
            jobj_flagCheckSetMtxDirtySub(jobj_r30);
        }
        jobj_r30 = (void*) jobj_get(jobj_r30, value, i);
        ASSERT_NOT_NULL(jobj_r30, 1006);

        if (jobj_r30->translate.y > -100.0f) {
            float f = (&value->x44_vec.x)[i];
            jobj_r30 = (void*) jobj_get(jobj_r30, value, i);
            jobj_r30 = (void*) jobj_get(jobj_r30, value, i);
            ASSERT_NOT_NULL(jobj_r30, 1114);
            jobj_r30->translate.y += f;
            jobj_flagCheckSetMtxDirtySub(jobj_r30);
            (&value->x44_vec.x)[i] -= 0.2028f; // @ lbl_804DDA90
        }
    }
}

inline f32 offset_rand(void)
{
    return HSD_Randf() - 0.5f;
}
void ifStatus_802F4B84(IfDamageState* state, s32 is_stamina)
{
    s32 i;
    u8 new_var;
    f32 mag;
    f32 ox;
    f32 oy;
    u8 frames;

    frames = state->frames_of_shake_remaining;
    if (frames != 0) {
        if (frames == 1) {
            for (i = 0; i < 4; i++) {
                HSD_JObjSetTranslateX(state->jobjs[i],
                                      state->translation_x[i]);
                HSD_JObjSetTranslateY(state->jobjs[i],
                                      state->translation_y[i]);
            }
            state->frames_of_shake_remaining = 0;
            return;
        }
        mag = 0.1014f * ((f32) (new_var = state->damage_from_last_attack));
        if (mag < 0.1014f) {
            mag = 0.1014f;
        } else if (mag > 1.5207f) {
            mag = 1.5207f;
        }
        for (i = 0; i < 4; i++) {
            ox = mag * (2.0f * offset_rand());
            oy = mag * (2.0f * offset_rand());
            if (ox < 0.0f) {
                ox -= 0.2028f;
            } else {
                ox += 0.2028f;
            }
            if (oy < 0.0f) {
                oy -= 0.2028f;
            } else {
                oy += 0.2028f;
            }
            HSD_JObjSetTranslateX(state->jobjs[i],
                                  state->translation_x[i] + ox);
            HSD_JObjSetTranslateY(state->jobjs[i],
                                  state->translation_y[i] + oy);
        }
        state->frames_of_shake_remaining -= 1;
    }
    PAD_STACK(8);
}

/* Color endpoints for damage percentage interpolation (extern from .sdata2) */
extern u8 ifStatus_804D57A8; /* Start color (low damage) */
extern u8 ifStatus_804D57AC; /* End color (high damage) */

void ifStatus_802F4EDC(HSD_GObj* gobj)
{
    HudIndex* hud;
    IfDamageState* state;
    HSD_JObj* jobj;
    HSD_JObj* digit_jobj;
    s32 is_stamina;
    HSD_TObj* tobj;
    HSD_MObj* mobj;
    HSD_MatAnimJoint** anim_base;
    s32 i;
    s32 var_ctr;
    u8 ones_digit;
    u8 tens_digit;
    u8 hundreds_digit;
    f32 digit_offset;
    f32 ones_offset;
    f32 tens_offset;
    f32 hundreds_offset;
    f32 pos;
    s16 clamped_damage;
    f32 factor;
    GXColor color;

    PAD_STACK(64);
    hud = &ifStatus_HudInfo;

    {
        IfDamageState* ptr;

        ptr = hud->players;
        jobj = gobj->hsd_obj;
        for (i = 0; i < 6; ptr++, i++) {
            if (ptr->HUD_parent_entity == gobj) {
                state = hud->players + i;
                goto found_player;
            }
        }
        state = NULL;
    found_player:
        (void) 0;
    }

    /* Check for death animation flag (bit 7 of flags byte at offset 0x10) */
    if (state->flags.explode_animation) {
        ifStatus_PercentOnDeathAnimationThink((UnkX*) state, 0, 0);
        return;
    }

    is_stamina = lb_8000B09C(jobj);

    /* Check if we need to start a new animation */
    if (state->flags.unk10 &&
        (state->flags.animation_status_id != 1 || is_stamina == 0))
    {
        state->flags.animation_status_id = 1;

        HSD_JObjRemoveAnim(jobj);

        anim_base = (HSD_MatAnimJoint**) &hud->janim_selection_joints;
        lb_8000C07C(jobj, 1, (HSD_AnimJoint**) hud->jobj_desc_parent,
                    (HSD_MatAnimJoint**) anim_base[0],
                    (HSD_ShapeAnimJoint**) anim_base[1]);
        HSD_JObjReqAnimAll(jobj, 0.0F);

        digit_jobj = state->jobjs[Percent];
        if (digit_jobj != NULL) {
            tobj = digit_jobj->u.dobj->mobj->tobj;
            HSD_TObjAddAnimAll(
                tobj,
                (HSD_TexAnim*) ((HSD_AnimJoint*) anim_base[0])
                    ->child->child->next->next->next->aobjdesc->fobjdesc);
            if (Player_GetMoreFlagsBit2((s8) state->player_slot)) {
                HSD_TObjReqAnimAll(tobj, 1.0F);
            } else {
                HSD_TObjReqAnimAll(tobj, 0.0F);
            }
            HSD_AObjSetRate(tobj->aobj, 0.0F);
            HSD_TObjAnim(tobj);
        }

        mn_8022F3D8(jobj, 1, 0x400);

        digit_jobj = state->jobjs[Ones];
        ones_digit = state->damage_percent % 10;
        HSD_TObjAddAnimAll(digit_jobj->u.dobj->mobj->tobj,
                           (HSD_TexAnim*) ((HSD_AnimJoint*) anim_base[0])
                               ->child->child->aobjdesc->fobjdesc);
        HSD_TObjReqAnimAll(digit_jobj->u.dobj->mobj->tobj, 2.0F * ones_digit);
        HSD_AObjSetRate(digit_jobj->u.dobj->mobj->tobj->aobj, 0.0F);

        digit_jobj = state->jobjs[Tens];
        tens_digit = (state->damage_percent % 100) / 10;
        HSD_TObjAddAnimAll(digit_jobj->u.dobj->mobj->tobj,
                           (HSD_TexAnim*) ((HSD_AnimJoint*) anim_base[0])
                               ->child->child->aobjdesc->fobjdesc);
        HSD_TObjReqAnimAll(digit_jobj->u.dobj->mobj->tobj, 2.0F * tens_digit);
        HSD_AObjSetRate(digit_jobj->u.dobj->mobj->tobj->aobj, 0.0F);

        digit_jobj = state->jobjs[Hundreds];
        hundreds_digit = (state->damage_percent % 1000) / 100;
        HSD_TObjAddAnimAll(digit_jobj->u.dobj->mobj->tobj,
                           (HSD_TexAnim*) ((HSD_AnimJoint*) anim_base[0])
                               ->child->child->aobjdesc->fobjdesc);
        HSD_TObjReqAnimAll(digit_jobj->u.dobj->mobj->tobj,
                           2.0F * hundreds_digit);
        HSD_AObjSetRate(digit_jobj->u.dobj->mobj->tobj->aobj, 0.0F);
    }

    HSD_JObjAnimAll(jobj);

    digit_jobj = state->jobjs[Ones];
    ones_digit = state->damage_percent % 10;
    HSD_TObjAddAnimAll(digit_jobj->u.dobj->mobj->tobj,
                       (HSD_TexAnim*) ifStatus_HudInfo.janim_selection_joints
                           ->child->child->aobjdesc->fobjdesc);
    HSD_TObjReqAnimAll(digit_jobj->u.dobj->mobj->tobj, 2.0F * ones_digit);
    HSD_AObjSetRate(digit_jobj->u.dobj->mobj->tobj->aobj, 0.0F);

    digit_jobj = state->jobjs[Tens];
    tens_digit = (state->damage_percent % 100) / 10;
    HSD_TObjAddAnimAll(digit_jobj->u.dobj->mobj->tobj,
                       (HSD_TexAnim*) ifStatus_HudInfo.janim_selection_joints
                           ->child->child->aobjdesc->fobjdesc);
    HSD_TObjReqAnimAll(digit_jobj->u.dobj->mobj->tobj, 2.0F * tens_digit);
    HSD_AObjSetRate(digit_jobj->u.dobj->mobj->tobj->aobj, 0.0F);

    if ((state->damage_percent % 1000) / 100 == 0 &&
        (state->damage_percent % 100) / 10 == 0)
    {
        HSD_JObjSetFlagsAll(state->jobjs[Tens], JOBJ_HIDDEN);
    } else {
        HSD_JObjClearFlagsAll(state->jobjs[Tens], JOBJ_HIDDEN);
    }

    digit_jobj = state->jobjs[Hundreds];
    hundreds_digit = (state->damage_percent % 1000) / 100;
    HSD_TObjAddAnimAll(digit_jobj->u.dobj->mobj->tobj,
                       (HSD_TexAnim*) ifStatus_HudInfo.janim_selection_joints
                           ->child->child->aobjdesc->fobjdesc);
    HSD_TObjReqAnimAll(digit_jobj->u.dobj->mobj->tobj, 2.0F * hundreds_digit);
    HSD_AObjSetRate(digit_jobj->u.dobj->mobj->tobj->aobj, 0.0F);

    if ((state->damage_percent % 1000) / 100 == 0) {
        HSD_JObjSetFlagsAll(state->jobjs[Hundreds], JOBJ_HIDDEN);
    } else {
        HSD_JObjClearFlagsAll(state->jobjs[Hundreds], JOBJ_HIDDEN);
    }

    /* Update colors when damage changes */
    if ((s16) state->old_damage != (s16) state->damage_percent) {
        if (Player_GetMoreFlagsBit2((s8) state->player_slot)) {
            /* Stamina mode: 0-100% range */
            clamped_damage = state->damage_percent;
            if (clamped_damage > 100) {
                clamped_damage = 100;
            } else if (clamped_damage < 0) {
                clamped_damage = 0;
            }
            factor = 1.0F - ((f32) clamped_damage / 100.0F);
            color.r = (s8) (factor * (f32) ((&ifStatus_804D57AC)[0] -
                                            (&ifStatus_804D57A8)[0]) +
                            (f32) (&ifStatus_804D57A8)[0]);
            color.g = (s8) (factor * (f32) ((&ifStatus_804D57AC)[1] -
                                            (&ifStatus_804D57A8)[1]) +
                            (f32) (&ifStatus_804D57A8)[1]);
            color.b = (s8) (factor * (f32) ((&ifStatus_804D57AC)[2] -
                                            (&ifStatus_804D57A8)[2]) +
                            (f32) (&ifStatus_804D57A8)[2]);
            color.a = 255;
        } else {
            /* Normal mode: 0-300% range */
            clamped_damage = state->damage_percent;
            if (clamped_damage > 300) {
                clamped_damage = 300;
            } else if (clamped_damage < 0) {
                clamped_damage = 0;
            }
            factor = (f32) clamped_damage / 300.0F;
            color.r = (s8) (factor * (f32) ((&ifStatus_804D57AC)[0] -
                                            (&ifStatus_804D57A8)[0]) +
                            (f32) (&ifStatus_804D57A8)[0]);
            color.g = (s8) (factor * (f32) ((&ifStatus_804D57AC)[1] -
                                            (&ifStatus_804D57A8)[1]) +
                            (f32) (&ifStatus_804D57A8)[1]);
            color.b = (s8) (factor * (f32) ((&ifStatus_804D57AC)[2] -
                                            (&ifStatus_804D57A8)[2]) +
                            (f32) (&ifStatus_804D57A8)[2]);
            color.a = 255;
        }

        /* Apply color to all digit materials */
        mobj = state->jobjs[Hundreds]->u.dobj->mobj;
        mobj->mat->diffuse.r = color.r;
        mobj->mat->diffuse.g = color.g;
        mobj->mat->diffuse.b = color.b;

        mobj = state->jobjs[Tens]->u.dobj->mobj;
        mobj->mat->diffuse.r = color.r;
        mobj->mat->diffuse.g = color.g;
        mobj->mat->diffuse.b = color.b;

        mobj = state->jobjs[Ones]->u.dobj->mobj;
        mobj->mat->diffuse.r = color.r;
        mobj->mat->diffuse.g = color.g;
        mobj->mat->diffuse.b = color.b;

        mobj = state->jobjs[Percent]->u.dobj->mobj;
        mobj->mat->diffuse.r = color.r;
        mobj->mat->diffuse.g = color.g;
        mobj->mat->diffuse.b = color.b;
    }

    /* Update JObj positions when animating */
    if (lb_8000B09C(jobj)) {
        for (i = 0; i < 4; i++) {
            digit_jobj = state->jobjs[i];
            if (digit_jobj == NULL) {
                __assert("jobj.h", 993, "jobj");
            }
            state->translation_x[i] = digit_jobj->translate.x;

            digit_jobj = state->jobjs[i];
            if (digit_jobj == NULL) {
                __assert("jobj.h", 1006, "jobj");
            }
            state->translation_y[i] = digit_jobj->translate.y;
        }
    }

    /* Calculate digit spacing offsets based on which digit is "1" */
    ones_offset = (state->damage_percent % 10 == 1) ? 0.5069F : 0.0F;
    tens_offset = ((state->damage_percent % 100) / 10 == 1) ? 0.5069F : 0.0F;

    /* Position percent sign */
    digit_jobj = state->jobjs[Percent];
    pos = state->translation_x[Percent] - ones_offset;
    if (digit_jobj == NULL) {
        __assert("jobj.h", 932, "jobj");
    }
    digit_jobj->translate.x = pos;
    jobj_flagCheckSetMtxDirtySub(digit_jobj);

    /* Position tens digit */
    digit_offset = ones_offset + tens_offset;
    digit_jobj = state->jobjs[Tens];
    pos = state->translation_x[Tens] + digit_offset;
    if (digit_jobj == NULL) {
        __assert("jobj.h", 932, "jobj");
    }
    digit_jobj->translate.x = pos;
    jobj_flagCheckSetMtxDirtySub(digit_jobj);

    /* Position hundreds digit */
    hundreds_offset =
        ((state->damage_percent % 1000) / 100 == 1) ? 0.5069F : 0.0F;
    digit_jobj = state->jobjs[Hundreds];
    pos = state->translation_x[Hundreds] +
          (tens_offset + digit_offset + hundreds_offset);
    if (digit_jobj == NULL) {
        __assert("jobj.h", 932, "jobj");
    }
    digit_jobj->translate.x = pos;
    jobj_flagCheckSetMtxDirtySub(digit_jobj);

    /* Handle shake animation */
    if (state->flags.force_digit_shake) {
        state->frames_of_shake_remaining = 10;
    }

    ifStatus_802F4B84(state, is_stamina);

    /* Apply final scale */
    if (ifStatus_804D6D60 >= 5) {
        jobj->scale.x = 0.65F;
    }
}

static inline IfDamageState* find_player_by_entity(HSD_GObj* gobj)
{
    s32 i;
    for (i = 0; i < 6; i++) {
        if (ifStatus_HudInfo.players[i].HUD_parent_entity == gobj) {
            return &ifStatus_HudInfo.players[i];
        }
    }
    return NULL;
}

void ifStatus_802F5B48(HSD_GObj* gobj)
{
    IfDamageState* p;
    s32 i;
    s32 diff;
    u8 t;

    p = find_player_by_entity(gobj);
    t = p->unk9;
    if (t != 0) {
        t = t + 1;
        p->unk9 = t;
        if (t > 0xC8U) {
            ifStatus_802F6788(p->player_slot);
            return;
        }
    }
    if (Player_GetEntity((s8) p->player_slot) == NULL) {
        return;
    }
    p->old_damage = p->damage_percent;
    if (Player_GetMoreFlagsBit2((s8) p->player_slot) != 0) {
        p->damage_percent = Player_GetRemainingHP((s8) p->player_slot);
        if (p->damage_percent > 0x3E7) {
            p->damage_percent = 0x3E7;
        } else if (p->damage_percent < 0) {
            p->damage_percent = 0;
        }
        if (p->old_damage != -1 && p->damage_percent < p->old_damage) {
            p->flags.force_digit_shake = 1;
            diff = p->old_damage - p->damage_percent;
            if (diff < 0) {
                diff = -diff;
            }
            p->damage_from_last_attack = diff;
        } else {
            p->flags.force_digit_shake = 0;
        }
        if (p->old_damage != -1 && p->damage_percent > p->old_damage) {
            p->flags.unk10 = 1;
        } else {
            p->flags.unk10 = 0;
        }
        if (p->old_damage == 0) {
            if (gm_8016AE44()->FighterMatchInfo[(s8) p->player_slot].x4_b5) {
                ifStatus_802F6948((s8) p->player_slot);
            }
        }
    } else {
        p->damage_percent = Player_GetDamage((s8) p->player_slot);
        if (p->damage_percent > 0x3E7) {
            p->damage_percent = 0x3E7;
        } else if (p->damage_percent < 0) {
            p->damage_percent = 0;
        }
        if (p->old_damage != -1 && p->damage_percent < p->old_damage) {
            p->flags.unk10 = 1;
        } else {
            p->flags.unk10 = 0;
        }
        if (p->old_damage != -1 && p->damage_percent > p->old_damage) {
            p->flags.force_digit_shake = 1;
            diff = p->old_damage - p->damage_percent;
            if (diff < 0) {
                diff = -diff;
            }
            p->damage_from_last_attack = diff;
            return;
        }
        p->flags.force_digit_shake = 0;
    }
}

inline IfDamageState* getPlayerByHUDParent(HSD_GObj* parent)
{
    s32 var_ctr;
    for (var_ctr = 0; var_ctr < 6; var_ctr++) {
        if (ifStatus_HudInfo.players[var_ctr].HUD_parent_entity == parent) {
            return &ifStatus_HudInfo.players[var_ctr];
        }
    }
    return NULL;
}

void ifStatus_802F5DE0(HSD_GObj* player, s32 arg1)
{
    if (!getPlayerByHUDParent(player)->flags.hide_all_digits) {
        HSD_GObj_JObjCallback(player, arg1);
    }
}

static inline IfDamageState* getPlayerByNext(HSD_GObj* gobj)
{
    s32 i;
    for (i = 0; i < 6; i++) {
        if (ifStatus_HudInfo.players[i].next == gobj) {
            return &ifStatus_HudInfo.players[i];
        }
    }
    return NULL;
}

void ifStatus_802F5E50(HSD_GObj* gobj, s32 arg1)
{
    IfDamageState* player = getPlayerByNext(gobj);
    if (!player->flags.hide_all_digits) {
        HSD_GObj_JObjCallback(gobj, arg1);
    }
}

void ifStatus_802F5EC0(IfDamageState* state, s32 player_idx)
{
    HSD_GObj* gobj;
    HSD_MatAnimJoint** anim_base;
    HSD_JObj* jobj;
    Vec3* vec;
    s32 i;
    HSD_TObj* tobj;
    HudIndex* hud = &ifStatus_HudInfo;

    if (state->HUD_parent_entity == NULL) {
        gobj = GObj_Create(0xE, 0xF, 0);
        jobj = HSD_JObjLoadJoint(hud->unk258);
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
        GObj_SetupGXLink(gobj, (void (*)(HSD_GObj*, int)) ifStatus_802F5DE0,
                         0xB, 0);
        HSD_GObj_SetupProc(gobj, ifStatus_802F5B48, 0x11);
        HSD_GObj_SetupProc(gobj, ifStatus_802F4EDC, 0x11);
        state->HUD_parent_entity = gobj;
    } else {
        jobj = state->HUD_parent_entity->hsd_obj;
    }
    state->flags.animation_status_id = 0;
    HSD_JObjRemoveAnim(jobj);
    anim_base = (HSD_MatAnimJoint**) &hud->janim_selection_joints;
    lb_8000C07C(jobj, 0, (HSD_AnimJoint**) hud->jobj_desc_parent,
                (HSD_MatAnimJoint**) anim_base[0],
                (HSD_ShapeAnimJoint**) anim_base[1]);
    HSD_JObjReqAnimAll(jobj, 0.0f);
    HSD_JObjAnimAll(jobj);
    vec = ifAll_802F3424((u8) player_idx);
    HSD_JObjSetTranslate(jobj, vec);
    for (i = 0; i < 4; i++) {
        state->jobjs[i] = (HSD_JObj*) ifStatus_802F6194((HSD_GObj*) jobj, i);
        state->translation_x[i] = HSD_JObjGetTranslationX(state->jobjs[i]);
        state->translation_y[i] = HSD_JObjGetTranslationY(state->jobjs[i]);
    }
    if (state->jobjs[3] != NULL) {
        tobj = state->jobjs[3]->u.dobj->mobj->tobj;
        HSD_TObjAddAnimAll(
            tobj, (HSD_TexAnim*) ((HSD_AnimJoint*) anim_base[0])
                      ->child->child->next->next->next->aobjdesc->fobjdesc);
        if (Player_GetMoreFlagsBit2((s8) state->player_slot) != 0) {
            HSD_TObjReqAnimAll(tobj, 1.0f);
        } else {
            HSD_TObjReqAnimAll(tobj, 0.0f);
        }
        HSD_AObjSetRate(tobj->aobj, 0.0f);
        HSD_TObjAnim(tobj);
    }
    ifStatus_802F5B48(state->HUD_parent_entity);
    state->old_damage = !state->damage_percent;
    ifStatus_802F4EDC(state->HUD_parent_entity);
    PAD_STACK(0x18);
}

HSD_GObj* ifStatus_802F6194(HSD_GObj* node, s32 n)
{
    HSD_GObj* gx_head;
    HSD_GObj* gx_next;
    HSD_GObj* gx_cur;
    s32 i;
    if ((node == NULL) || (n < 0)) {
        return NULL;
    }
    if (node == NULL) {
        gx_head = NULL;
    } else {
        gx_head = node->next_gx;
    }
    gx_cur = gx_head;
    i = 0;
    goto check_done;

advance_node:
    if (gx_cur == NULL) {
        gx_next = NULL;
    } else {
        gx_next = gx_cur->next;
    }
    gx_cur = gx_next;
    i += 1;

check_done:
    if (i >= n) {
        return gx_cur;
    }
    if (gx_cur != NULL) {
        goto advance_node;
    }
    return gx_cur;
}

static inline HSD_GObj* ifStatus_CreateMarkGObj(void)
{
    return GObj_Create(0xE, 0xF, 0);
}

void ifStatus_802F61FC(IfDamageState* state, s32 player_idx)
{
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    HSD_TObj* tobj;
    Vec3* vec;
    HSD_MObj* mobj;
    GXColor color;
    CharacterKind chara;
    s32 slot;
    u8 team;
    u8 hud_color;
    HudIndex* hud = &ifStatus_HudInfo;
    u8 idx = player_idx;
    PAD_STACK(0x10);

    chara = Player_GetPlayerCharacter(idx);
    if (state->next == NULL) {
        ifAll_802F3690();
        gobj = ifStatus_CreateMarkGObj();
        if (gobj == NULL) {
            HSD_ASSERTREPORT(0x30A, 0,
                             "Error : gobj dont't get (ifAddMark)\n");
        }
        jobj = HSD_JObjLoadJoint((HSD_Joint*) hud->unk268);
        if (jobj == NULL) {
            HSD_ASSERTREPORT(0x30E, 0,
                             "Error : jobj dont't get (ifAddMark)\n");
        }
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
        GObj_SetupGXLink(gobj, (void (*)(HSD_GObj*, int)) ifStatus_802F5E50,
                         0xB, 0);
        state->next = gobj;
    } else {
        jobj = state->next->hsd_obj;
    }
    tobj = jobj->child->u.dobj->mobj->tobj;
    lb_8000C07C(jobj, 0, (HSD_AnimJoint**) hud->unk26C,
                (HSD_MatAnimJoint**) hud->unk270,
                (HSD_ShapeAnimJoint**) hud->unk274);
    if (chara == CKIND_MASTERH || (u32) (chara - CKIND_GKOOPS) <= 1) {
        chara = CKIND_BOY;
    }
    HSD_TObjReqAnimAll(tobj, 0.5f + gm_80168B34(chara, 0, 0));
    HSD_AObjSetRate(tobj->aobj, 0.1f);
    HSD_TObjAnim(tobj);
    vec = ifAll_802F3424(idx);
    HSD_JObjSetTranslate(jobj, vec);
    HSD_JObjAddTranslationX(jobj, 0.25f);
    slot = Player_GetPlayerSlotType(idx);
    hud_color = gm_8016B168();
    team = Player_GetTeam(idx);
    color = gm_80160968(
        gm_80160854(Player_GetPlayerId(idx), team, hud_color, slot));
    mobj = HSD_JObjGetChild(jobj)->u.dobj->mobj;
    mobj->mat->diffuse.r = color.r;
    mobj->mat->diffuse.g = color.g;
    mobj->mat->diffuse.b = color.b;
}

void ifStatus_802F6508(s32 arg0)
{
    IfDamageState* hud_player;
    StartMeleeRules* rules;
    u32 mode;

    if (Player_GetPlayerSlotType(arg0) != Gm_PKind_NA &&
        (s32) ifStatus_804D6D60 > arg0 && (rules = gm_8016AE50(), rules->x2_6))
    {
        hud_player = &ifStatus_HudInfo.players[(u8) arg0];
        hud_player->damage_percent = -1;
        hud_player->old_damage = -1;
        hud_player->frames_of_shake_remaining = 0;
        hud_player->flags.explode_animation = 0;
        hud_player->flags.randomize_velocity = 0;
        hud_player->flags.force_digit_shake = 0;
        hud_player->flags.unk10 = 0;
        hud_player->player_slot = (u8) arg0;
        hud_player->unk9 = 0;
        ifStatus_802F61FC(hud_player, (u8) arg0);
        ifStatus_802F5EC0(hud_player, (u8) ((unsigned long long) arg0));
        if (rules->x3_0 && gm_8016B238() == 0) {
            un_802FF364(arg0);
        }
        mode = rules->x0_0;
        if (mode == 1 || rules->x4_2) {
            ifStock_802F98E8((u8) arg0, 0);
            return;
        }
        if (mode == 2) {
            ifStock_802F98E8((u8) arg0, 2);
            return;
        }
        ifStock_802F98E8((u8) arg0, 1);
    }
}

void ifStatus_802F665C(int arg0)
{
    int i;

    ifAll_802F343C(arg0);
    ifStatus_804D6D60 = arg0;
    for (i = 0; i < 6; i++) {
        ifStatus_802F6508(i);
    }
}

void ifStatus_802F66A4(void)
{
    HudIndex* hud = &ifStatus_HudInfo;
    s32 pad0;
    s32 pad1;
    DynamicModelDesc** mrk;
    DynamicModelDesc** num;
    HSD_Archive** arch;
    s32 reset;
    arch = ifAll_802F3690();
    lbArchive_LoadSections(*arch, (void**) &num, "DmgNum_scene_models",
                           (void**) &mrk, "DmgMrk_scene_models", 0);
    hud->unk258 = (*num)->joint;
    hud->jobj_desc_parent = (*num)->anims;
    hud->janim_selection_joints = (HSD_AnimJoint*) (*num)->matanims;
    hud->janim_selection_textures = (*num)->shapeanims;
    hud->unk268 = (*mrk)->joint;
    hud->unk26C = (*mrk)->anims;
    hud->unk270 = (*mrk)->matanims;
    hud->unk274 = (*mrk)->shapeanims;
    if (reset != 0) {
        ifStatus_804D6D60 = 0;
        memzero(hud, 0x258);
    }
}

void ifStatus_802F6788(u8 player_idx)
{
    IfDamageState* player_hud;
    s8 p_idx = (u8) player_idx;
    player_hud = &ifStatus_HudInfo.players[p_idx & 0xFF];
    if (player_hud->HUD_parent_entity != NULL) {
        HSD_GObjPLink_80390228(player_hud->HUD_parent_entity);
        player_hud->HUD_parent_entity = NULL;
    }
    if (player_hud->next != NULL) {
        HSD_GObjPLink_80390228(player_hud->next);
        player_hud->next = NULL;
    }
    ifStock_802FB650(player_idx & 0xFF);
}

void ifStatus_802F6804(void)
{
    s32 i;
    IfDamageState* v;

    i = 0;
    do {
        v = &ifStatus_HudInfo.players[i & 0xFF];
        if (v->HUD_parent_entity != NULL) {
            HSD_GObjPLink_80390228(v->HUD_parent_entity);
            v->HUD_parent_entity = NULL;
        }
        if (v->next != NULL) {
            HSD_GObjPLink_80390228(v->next);
            v->next = NULL;
        }
        ifStock_802FB650((s8) i & 0xFF);
        i++;
    } while (i < 6);
}

/// Hide Percentage Digits
void ifStatus_802F6898(void)
{
    s32 i;
    HudIndex* v = &ifStatus_HudInfo;
    for (i = 0; i < 6; i++) {
        v->players[i].flags.hide_all_digits = 1;
    }
}

/// Show All Percentage Digits
void ifStatus_802F68F0(void)
{
    s32 i;
    HudIndex* v = &ifStatus_HudInfo;
    for (i = 0; i < 6; i++) {
        v->players[i].flags.hide_all_digits = 0;
    }
}

void ifStatus_802F6948(s32 player_idx)
{
    IfDamageState* hud_player;
    struct StartMeleeRules* small_thing;
    IfDamageFlags* hud_player_flags;

    small_thing = gm_8016AE50();
    hud_player = &ifStatus_HudInfo.players[player_idx];
    hud_player_flags = &hud_player->flags;
    if (hud_player_flags->explode_animation != 1) {
        hud_player_flags->explode_animation = 1;
        hud_player_flags->randomize_velocity = 1;
        if (small_thing->x2_7 != 0) {
            hud_player->unk9 = 1;
        }
    }
}

void ifStatus_802F69C0(s32 player_idx, s32 arg1)
{
    IfDamageState* hud_player;
    IfDamageFlags* hud_player_flags;
    lbl_8046B6A0_t* big_thing;
    struct StartMeleeRules* small_thing;

    big_thing = gm_8016AE38();
    if (big_thing->x24C8.x0_0 != 1 && big_thing->x24C8.x2_5 != 0) {
        if_802F7C30(arg1);
    }

    big_thing = gm_8016AE38();
    big_thing->unk_D = player_idx;
    small_thing = gm_8016AE50();
    hud_player = &ifStatus_HudInfo.players[player_idx];
    hud_player_flags = &hud_player->flags;
    if (hud_player_flags->explode_animation != 1) {
        hud_player_flags->explode_animation = 1;
        hud_player_flags->randomize_velocity = 1;
        if (small_thing->x2_7 != 0) {
            hud_player->unk9 = 1;
        }
    }
    if ((big_thing->x24C8.x2_0 != 0) &&
        ((Player_GetPlayerSlotType(player_idx) == Gm_PKind_Human) ||
         (Player_GetPlayerSlotType(player_idx) == Gm_PKind_Cpu)) &&
        (Player_GetStocks(player_idx) == 0))
    {
        gm_8016B8D4(player_idx, Player_GetPlayerSlotType(player_idx));
    }

    /// @todo Inline with callback arg
    if (big_thing->x24C8.x0_0 != 1 && big_thing->x24C8.x2_5 != 0 &&
        &if_802F7BB4 != NULL)
    {
        if_802F7BB4(player_idx);
    }
}

void ifStatus_802F6AF8(s32 player_idx)
{
    IfDamageState* hud_player;
    lbl_8046B6A0_t* big_thing;
    struct StartMeleeRules* small_thing;
    IfDamageFlags* hud_player_flags;

    big_thing = gm_8016AE38();
    big_thing->unk_D = player_idx;
    small_thing = gm_8016AE50();
    hud_player = &ifStatus_HudInfo.players[player_idx];
    hud_player_flags = &hud_player->flags;
    if (hud_player_flags->explode_animation != 1) {
        hud_player_flags->explode_animation = 1;
        hud_player_flags->randomize_velocity = 1;
        if (small_thing->x2_7 != 0) {
            hud_player->unk9 = 1;
        }
    }
    if ((big_thing->x24C8.x2_0 != 0) &&
        ((Player_GetPlayerSlotType(player_idx) == Gm_PKind_Human) ||
         (Player_GetPlayerSlotType(player_idx) == Gm_PKind_Cpu)) &&
        (Player_GetStocks(player_idx) == 0))
    {
        gm_8016B8D4(player_idx, Player_GetPlayerSlotType(player_idx));
    }

    /// @todo Inline with callback arg
    if (big_thing->x24C8.x0_0 != 1 && big_thing->x24C8.x2_5 != 0 &&
        &if_802F7AF8 != NULL)
    {
        if_802F7AF8(player_idx);
    }
}

void ifStatus_802F6C04(s32 player_idx)
{
    IfDamageState* hud_player;
    IfDamageFlags* hud_player_flags;
    lbl_8046B6A0_t* big_thing;
    struct StartMeleeRules* small_thing;

    big_thing = gm_8016AE38();
    big_thing->unk_D = player_idx;
    small_thing = gm_8016AE50();
    hud_player = &ifStatus_HudInfo.players[player_idx];
    hud_player_flags = &hud_player->flags;
    if (hud_player_flags->explode_animation != 1) {
        hud_player_flags->explode_animation = 1;
        hud_player_flags->randomize_velocity = 1;
        if (small_thing->x2_7 != 0) {
            hud_player->unk9 = 1;
        }
    }
    if ((big_thing->x24C8.x2_0 != 0) &&
        ((Player_GetPlayerSlotType(player_idx) == Gm_PKind_Human) ||
         (Player_GetPlayerSlotType(player_idx) == Gm_PKind_Cpu)) &&
        (Player_GetStocks(player_idx) == 0))
    {
        gm_8016B8D4(player_idx, Player_GetPlayerSlotType(player_idx));
    }

    /// @todo Inline with callback arg
    if (big_thing->x24C8.x0_0 != 1 && big_thing->x24C8.x2_5 != 0 &&
        &if_802F7C30 != NULL)
    {
        if_802F7C30(player_idx);
    }
}

void ifStatus_802F6D10(s32 player_idx)
{
    IfDamageState* hud_player;
    lbl_8046B6A0_t* big_thing;
    struct StartMeleeRules* small_thing;
    IfDamageFlags* hud_player_flags;

    big_thing = gm_8016AE38();
    big_thing->unk_D = player_idx;
    small_thing = gm_8016AE50();
    hud_player = &ifStatus_HudInfo.players[player_idx];
    hud_player_flags = &hud_player->flags;
    if (hud_player_flags->explode_animation != 1) {
        hud_player_flags->explode_animation = 1;
        hud_player_flags->randomize_velocity = 1;
        if (small_thing->x2_7 != 0) {
            hud_player->unk9 = 1;
        }
    }
    if ((big_thing->x24C8.x2_0 != 0) &&
        ((Player_GetPlayerSlotType(player_idx) == Gm_PKind_Human) ||
         (Player_GetPlayerSlotType(player_idx) == Gm_PKind_Cpu)) &&
        (Player_GetStocks(player_idx) == 0))
    {
        gm_8016B8D4(player_idx, Player_GetPlayerSlotType(player_idx));
    }

    /// @todo Inline with callback arg
    if (big_thing->x24C8.x0_0 != 1 && big_thing->x24C8.x2_5 != 0 &&
        &if_802F7D08 != NULL)
    {
        if_802F7D08(player_idx);
    }
}

void ifStatus_802F6E1C(int slot)
{
    ifStatus_802F6508(slot);
}

void ifStatus_802F6E3C(s32 player_num)
{
    IfDamageState* player;

    player = &ifStatus_HudInfo.players[player_num];
    if (player->HUD_parent_entity != NULL) {
        HSD_GObj_80390CAC(player->HUD_parent_entity);
    }
    if (player->next != NULL) {
        HSD_GObj_80390CAC(player->next);
    }
    ifStock_802FB6AC(player_num);
}

void ifStatus_802F6EA4(int arg0, int arg1, int arg2, int arg3, Event arg4,
                       Event arg5)
{
    HSD_GObj* gobj;
    HSD_JObj* jobj;

    if (arg0 == 8) {
        if (arg4 != NULL) {
            ((IfStatusCb) arg4)(-1);
        }
        if (arg5 != NULL) {
            ((IfStatusCb) arg5)(-1);
        }
        if (arg1 >= 0) {
            lbAudioAx_800237A8(arg1, 0x7F, 0x40);
        }
        if (arg1 >= 0) {
            lbAudioAx_800237A8(arg2, 0x7F, 0x40);
        }
    } else {
        Element_803F9628* e;
        e = &ifStatus_803F9628[arg0];
        e->x20 = arg1;
        e->x24 = arg2;
        e->x11 = arg3;
        if (e->x0 != NULL) {
            HSD_GObjPLink_80390228(e->x0);
        }
        gobj = GObj_Create(0xE, 0xE, 0);
        jobj = HSD_JObjLoadJoint(e->x14->joint);
        lb_80011C18(jobj, 0x08000000);
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
        GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0xB, 0);
        if (e->x8 != NULL) {
            HSD_GObj_SetupProc(gobj, e->x8, 0);
        }
        lb_8000C0E8(jobj, 0, e->x14);
        HSD_JObjReqAnimAll(jobj, 0.0f);
        HSD_JObjAnimAll(jobj);
        e->x12.x0 = 0;
        e->x12.x1 = 0;
        e->x12.x2 = 0;
        e->x0 = gobj;
        e->x18 = (IfStatusCb) arg4;
        e->x1C = (IfStatusCb) arg5;
    }
}

void ifStatus_802F7034(UNK_T arg0)
{
    lbl_8046B6A0_t* big_thing;
    int a;
    int b;
    int c;
    u8 unkB;
    u8 mr;

    big_thing = gm_8016AE38();
    if (big_thing->unk_10 != 0) {
        a = big_thing->unk_10 - 1;
    } else {
        a = -1;
    }
    if (big_thing->unk_14 != 0) {
        b = big_thing->unk_14 - 1;
    } else {
        b = -1;
    }
    if (big_thing->unk_18 != 0) {
        c = big_thing->unk_18;
    } else {
        c = 0;
    }

    unkB = big_thing->unk_B;
    if (unkB != 0) {
        ifStatus_802F6EA4(unkB - 1, a, b, c, arg0, NULL);
        return;
    }
    mr = big_thing->match_result;
    if (mr == 1) {
        ifStatus_802F6EA4(0, a, b, c, arg0, NULL);
        return;
    }
    if (big_thing->x24C8.x5_1) {
        if (mr == 6) {
            ifStatus_802F6EA4(7, a, b, c, arg0, NULL);
            return;
        }
        ifStatus_802F6EA4(6, a, b, c, arg0, NULL);
        return;
    }
    ifStatus_802F6EA4(5, a, b, c, arg0, NULL);
}

void ifStatus_802F7134(void)
{
    u8 _[8];
    HSD_Archive** archive;
    DynamicModelDesc** volatile models;
    int i;

    for (i = 0; i < 8; i++) {
        ifStatus_803F9628[i].x0 = NULL;
        ifStatus_803F9628[i].x4 = 0;
    }

    archive = ifAll_802F3690();
    lbArchive_LoadSections(*archive, (void**) &models, "ScInfCnt_scene_models",
                           0);

    for (i = 0; i < 8; i++) {
        ifStatus_803F9628[i].x14 = models[i];
    }
}

/// free
void ifStatus_802F7220(void)
{
    s32 i;
    for (i = 0; i < 8; i++) {
        if (ifStatus_803F9628[i].x0 != NULL) {
            HSD_GObjPLink_80390228(ifStatus_803F9628[i].x0);
            ifStatus_803F9628[i].x0 = NULL;
        }
    }
}
