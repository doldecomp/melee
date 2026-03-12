#include "eflib.h"

#include "efasync.h"
#include "inlines.h"
#include "types.h"

#include "baselib/displayfunc.h"
#include "baselib/gobjobject.h"
#include "baselib/gobjplink.h"
#include "baselib/gobjproc.h"
#include "baselib/particle.h"
#include "baselib/psappsrt.h"
#include "baselib/psdisp.h"
#include "baselib/psstructs.h"
#include "baselib/state.h"

#include "dolphin/mtx.h"

#include "ft/inlines.h"
#include "ftCommon/ftCo_Bury.h"

#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"

#include <runtime.h>
#include <trigf.h>

// externs
extern u32* ptclref_804D0E5C[65];
extern ef_Symbols efAsync_803C025C[51];
extern HSD_ObjAllocData efLib_AllocData;
extern u32 hsd_804D7900;

// forward declarations to avoid sdata2 pollution
void HSD_MtxGetScale(Mtx arg0, Vec3* arg1);
void grLib_801C99C0(s32, s32, HSD_JObj*, s32);

// forward declare for B4B8
void efLib_RenderCallback(HSD_GObj* gobj, int code);

// .sbss
s32 efLib_804D64F0[2];
u32 efLib_804D64EC;
u32 efLib_804D64E8;

/* ---------------------------------------------------- */
/*                       INLINES                        */
/* ---------------------------------------------------- */

void inline eflib_attach_gfx(HSD_Generator** generator, s32 gfx_id,
                             HSD_JObj* jobj)
{
    *generator = hsd_8039EFAC(0, gfx_id / 1000, gfx_id, jobj);
    if (*generator != NULL) {
        HSD_psAppSRT* appsrt;
        if ((appsrt = (*generator)->appsrt) == NULL) {
            appsrt = psAddGeneratorAppSRT_begin(*generator, 0);
        }
        if (appsrt != NULL) {
            appsrt->gp = *generator;
        } else {
            hsd_8039D4DC(*generator);
            *generator = NULL;
            goto eflib_attach_gfx_exit;
        }
        (*generator)->type &= 0xFFFFF9FF;
        (*generator)->type |= PSAPPSRT_UNK_B11;
    eflib_attach_gfx_exit:;
    }
}

static inline HSD_JObj* efLib_GetJObj(HSD_GObj* gobj)
{
    return gobj->hsd_obj;
}

inline Effect* eflib_attach_effect(int idx, HSD_GObj* gobj, HSD_JObj* jobj)
{
    Effect* effect = efLib_8005BE88(idx, gobj);
    if ((effect) != NULL) {
        HSD_JObj* effect_jobj;
        if ((effect_jobj = GET_JOBJ(effect->gobj)) == NULL) {
            HSD_GObjPLink_80390228(effect->gobj);
            return NULL;
        } else {
            Vec3 translate;
            lb_8000C1C0(effect_jobj, jobj);
            lb_8000B1CC(jobj, NULL, &translate);
            HSD_JObjSetTranslate(effect_jobj, &translate);
            effect->xC = jobj;
        }
    }
    return effect;
}

inline HSD_Generator*
efLib_EnsureGeneratorAppSRT_inline(HSD_Generator* generator, s32 status)
{
    HSD_psAppSRT* psAppSRT;

    if (generator != NULL) {
        if ((psAppSRT = generator->appsrt) == NULL) {
            psAppSRT = psAddGeneratorAppSRT_begin(generator, status);
        }
        if (psAppSRT == NULL) {
            hsd_8039D4DC(generator);
            generator = NULL;
        }
    }
    return generator;
}

/* ---------------------------------------------------- */
/*                       MACROS                         */
/* ---------------------------------------------------- */

/*
 * --------------------------------------------------------------------
 * TODO: Figure out how to make this an inline that keeps match at 100%
 * --------------------------------------------------------------------
 */
#define WALK_TO_ROOT(_jobj, _label)                                           \
    {                                                                         \
        HSD_JObj* _parent;                                                    \
        goto _wr_##_label;                                                    \
        do {                                                                  \
            if ((_jobj) == NULL) {                                            \
                _parent = NULL;                                               \
            } else {                                                          \
                _parent = (_jobj)->parent;                                    \
            }                                                                 \
            (_jobj) = _parent;                                                \
            _wr_##_label : if ((_jobj) == NULL)                               \
            {                                                                 \
                _parent = NULL;                                               \
            }                                                                 \
            else                                                              \
            {                                                                 \
                _parent = (_jobj)->parent;                                    \
            }                                                                 \
        } while (_parent != NULL);                                            \
    }

void efLib_8005B4B8(void)
{
    HSD_GObj* gobj;
    int i;
    HSD_ObjAllocInit(&efLib_AllocData, 0x2CU, 4U);

    efLib_804D64EC = 0;

    for (i = 0; i < 50; ++i) {
        efAsync_803C025C[i].unk8 = NULL;
    }

    hsd_8039D354(0);
    hsd_80398A08(0);
    hsd_804D7900 = (u32) fn_8005DCD0;

    gobj = GObj_Create(8U, 0xBU, 1U);
    GObj_SetupGXLink(gobj, efLib_RenderCallback, 7U, 2U);
    HSD_GObjProc_8038FD54(gobj, efLib_8005C9A4, 0xFU);

    gobj = GObj_Create(8U, 0xCU, 1U);
    GObj_SetupGXLink(gobj, efLib_RenderCallback, 8U, 2U);
    HSD_GObjProc_8038FD54(gobj, fn_8005C9D0, 0xFU);

    HSD_JObjSetSPtclCallback(fn_8005DB20);
    HSD_JObjSetDPtclCallback(fn_8005DB70);
    psInitAppSRT(0, 0xA4);
    efAsync_80067980();

    for (i = 0; i < 8; i++) {
        efLib_80458F60[i].x0_gobj = NULL;
        efLib_80458F60[i].x6_unk = 0xFF;
    }
}

void efLib_8005B704(HSD_GObj* arg_gobj, s32 arg1)
{
    HSD_GObj* gobj_1;
    HSD_GObj* gobj_2;
    Effect* eff_1;
    Effect* eff_2;

    gobj_1 = HSD_GObj_Entities->x2C;
    while (gobj_1 != NULL) {
        eff_1 = GET_EFFECT(gobj_1);
        if ((eff_1 != NULL) && (eff_1->parent_gobj == arg_gobj)) {
            eff_1->x26 |= arg1;
        }
        gobj_1 = gobj_1->next;
    }
    gobj_2 = HSD_GObj_Entities->x30;
    while (gobj_2 != NULL) {
        eff_2 = GET_EFFECT(gobj_2);
        if ((eff_2 != NULL) && (eff_2->parent_gobj == arg_gobj)) {
            eff_2->x26 |= arg1;
        }
        gobj_2 = gobj_2->next;
    }
}

void efLib_8005B780(HSD_GObj* gobj)
{
    Effect* effect = gobj->user_data;
    HSD_JObj* jobj;
    int i;
    u8 obj_kind;

    if ((effect != NULL) && (effect->x29 == 0) && (gobj != NULL)) {
        for (i = 0; i < 8; i++) {
            HSD_GObj* efLib_gobj = efLib_80458F60[i].x0_gobj;
            if (efLib_gobj == gobj) {
                efLib_80458F60[i].x0_gobj = NULL;
            }
        }
        obj_kind = gobj->obj_kind;
        if (obj_kind == HSD_GObj_804D7849) {
            jobj = gobj->hsd_obj;
            HSD_JObjWalkTree(jobj, hsd_8039D688, NULL);
        }
        HSD_GObjPLink_80390228(gobj);
    }
}

void efLib_DestroyAll(HSD_GObj* gobj)
{
    HSD_GObj* gobj_1;
    HSD_GObj* gobj_4;
    int i;
    PAD_STACK(48);

    for (i = 0; i < 8; i++) {
        if (efLib_80458F60[i].x0_gobj == gobj) {
            efLib_80458F60[i].x0_gobj = NULL;
        }
    }
    gobj_1 = HSD_GObj_Entities->x2C;
    while (gobj_1 != NULL) {
        HSD_GObj* gobj_2;
        Effect* eff_1;

        gobj_2 = gobj_1->next;
        if (((eff_1 = GET_EFFECT(gobj_1)) != NULL) &&
            (eff_1->parent_gobj == gobj))
        {
            if (eff_1->gobj->obj_kind == HSD_GObj_804D7849) {
                HSD_JObjWalkTree(eff_1->gobj->hsd_obj, hsd_8039D688, NULL);
            }
            HSD_GObjPLink_80390228(eff_1->gobj);
        }
        gobj_1 = gobj_2;
    }
    gobj_4 = HSD_GObj_Entities->x30;
    while (gobj_4 != NULL) {
        HSD_GObj* gobj_5;
        Effect* eff_2;

        eff_2 = GET_EFFECT(gobj_4);
        gobj_4 = gobj_4->next;
        if ((eff_2 != NULL) && (eff_2->parent_gobj == gobj)) {
            gobj_5 = eff_2->gobj;
            if (gobj_5->obj_kind == HSD_GObj_804D7849) {
                HSD_JObjWalkTree(gobj_5->hsd_obj, hsd_8039D688, NULL);
            }
            HSD_GObjPLink_80390228(eff_2->gobj);
        }
    }
    if (gobj->obj_kind == HSD_GObj_804D7849) {
        HSD_JObjWalkTree(gobj->hsd_obj, hsd_8039D688, NULL);
    }
}

void efLib_PauseAll(HSD_GObj* arg_gobj)
{
    HSD_GObj* gobj_1;
    HSD_GObj* gobj_2;
    Effect* eff_1;
    Effect* eff_2;

    gobj_1 = HSD_GObj_Entities->x2C;
    while (gobj_1 != NULL) {
        eff_1 = GET_EFFECT(gobj_1);
        if ((eff_1 != NULL) && (eff_1->parent_gobj == arg_gobj)) {
            eff_1->x28 = (eff_1->x28 & 0x80) | 1;
        }
        gobj_1 = gobj_1->next;
    }
    gobj_2 = HSD_GObj_Entities->x30;
    while (gobj_2 != NULL) {
        eff_2 = GET_EFFECT(gobj_2);
        if ((eff_2 != NULL) && (eff_2->parent_gobj == arg_gobj)) {
            eff_2->x28 = (eff_2->x28 & 0x80) | 1;
        }
        gobj_2 = gobj_2->next;
    }
}

void efLib_ResumeAll(HSD_GObj* arg_gobj)
{
    HSD_GObj* gobj_1;
    HSD_GObj* gobj_2;
    Effect* eff_1;
    Effect* eff_2;

    gobj_1 = HSD_GObj_Entities->x2C;
    while (gobj_1 != NULL) {
        eff_1 = GET_EFFECT(gobj_1);
        if ((eff_1 != NULL) && (eff_1->parent_gobj == arg_gobj)) {
            eff_1->x28 &= 0x80;
        }
        gobj_1 = gobj_1->next;
    }
    gobj_2 = HSD_GObj_Entities->x30;
    while (gobj_2 != NULL) {
        eff_2 = GET_EFFECT(gobj_2);
        if ((eff_2 != NULL) && (eff_2->parent_gobj == arg_gobj)) {
            eff_2->x28 &= 0x80;
        }
        gobj_2 = gobj_2->next;
    }
}

void efLib_RemoveUserData(void* effect)
{
    Effect* ep;
    Effect* new_var2;
    ep = new_var2 = effect;
    if (new_var2->gobj != NULL) {
        if (ep->x29 == 0) {
            efLib_804D64EC--;
        }
        HSD_ObjFree(&efLib_AllocData, ep);
    } else {
        OSReport("Duplicate Free %08X\n", ep);
        HSD_ASSERT(53, 0);
    }
}

void efLib_8005BBB4(void)
{
    HSD_GObj* gobj;
    HSD_GObj* next;

    gobj = HSD_GObj_Entities->x2C;
    while (gobj != NULL) {
        next = gobj->next;
        efLib_8005B780(gobj);
        {
            u32 check = efLib_804D64EC, value = 0x40U;
            if (check < value) {
                return;
            }
        }
        gobj = next;
    }

    gobj = HSD_GObj_Entities->x30;
    while (gobj != NULL) {
        next = gobj->next;
        efLib_8005B780(gobj);
        {
            u32 check = efLib_804D64EC, value = 0x40U;
            if (check < value) {
                return;
            }
        }
        gobj = next;
    }

    HSD_ASSERTREPORT(77, 0, "can't remove no force effect!\n");
}

void fn_8005BC50(HSD_GObj* gobj)
{
    Effect* effect;
    HSD_JObj* jobj = gobj->hsd_obj;
    switch ((effect = GET_EFFECT(gobj))->x28) {
    case 1:
        effect->x28++;
        break;
    case 2:
        return;
    }
    if (effect->x24 != 0) {
        u16 param = effect->x24 - 1;
        effect->x24 = param;
        if (param == 0) {
            HSD_GObjPLink_80390228(gobj);
            return;
        }
    }
    if (effect->x27 != 0b00000000) {
        if ((effect->xC) != NULL) {
            Vec3 scale;
            if (HSD_JObjGetParent(effect->xC) != NULL) {
                HSD_JObj* jobj_eff = effect->xC;
                if (jobj_eff != NULL && HSD_JObjMtxIsDirty(jobj_eff)) {
                    HSD_JObjSetupMatrixSub(jobj_eff);
                }
                if (effect->x27 & 0b00000001) {
                    HSD_MtxGetScale(HSD_JObjGetMtxPtr(effect->xC), &scale);
                }
            } else if (effect->x27 & 0b00000001) {
                HSD_JObjGetScale(effect->xC, &scale);
            }
            if (effect->x27 & 0b00000001) {
                scale.x = scale.z = scale.y;
                HSD_JObjSetScale(jobj, &scale);
            }
        }
    }
    HSD_JObjAnimAll(jobj);
    if (effect->x10 != NULL) {
        effect->x10(effect);
    }
}

Effect* efLib_8005BE88(int idx, HSD_GObj* parent_gobj)
{
    Effect* ep;
    EffectDesc* desc;
    u8 p_link;

    desc = &((EffectDesc*) efAsync_803C025C[idx / 1000].unk8)[idx % 1000];

    if (efLib_804D64E8 == 0) {
        if (efLib_804D64EC >= 64) {
            efLib_8005BBB4();
        }

        efLib_804D64EC += 1;
    }

    {
        Effect* new_ep = HSD_ObjAlloc(&efLib_AllocData);
        if (new_ep == NULL) {
            ep = NULL;
        } else {
            new_ep->x0 = NULL;
            ep = new_ep;
            new_ep->gobj = NULL;
            new_ep->xC = 0;
            new_ep->x10 = 0;
            new_ep->x28 = 0;
            new_ep->x26 = 0;
            new_ep->x27 = 0;
            new_ep->x29 = efLib_804D64E8;
        }
    }

    if (ep == NULL) {
        return NULL;
    }
    if (parent_gobj == NULL && ep->x29) {
        HSD_ASSERTREPORT(177, 0, "error no parent gobj!\n");
    }

    if (idx >= 27 || idx < 25) {
        p_link = 11;
    } else {
        p_link = 12;
    }
    ep->parent_gobj = parent_gobj;
    {
        HSD_GObj* gobj = GObj_Create(HSD_GOBJ_CLASS_EFFECT, p_link, 0);
        ep->gobj = gobj;
        if (gobj == NULL) {
            if (ep->gobj != NULL) {
                if (ep->x29 == 0) {
                    efLib_804D64EC -= 1;
                }
                HSD_ObjFree(&efLib_AllocData, ep);
            } else {
                HSD_ASSERTREPORT(53, 0, "Duplicate Free %08X\n", ep);
            }
            return NULL;
        }
    }
    GObj_SetupGXLink(ep->gobj, HSD_GObj_JObjCallback, 7, 1);
    GObj_InitUserData(ep->gobj, 8, efLib_RemoveUserData, ep);
    {
        HSD_JObj* jobj = HSD_JObjLoadJoint(desc->model_desc.joint);
        if (jobj == NULL) {
            HSD_GObjPLink_80390228(ep->gobj);
            return NULL;
        }
        {
            u8 kind = HSD_GObj_804D7849;
            HSD_GObjObject_80390A70(ep->gobj, kind, jobj);
        }
        if ((__cvt_fp2unsigned(10.0F * desc->x0) % 10) != 0) {
            lb_80011C18(jobj, 0x08000000);
        }
        ep->x24 = __cvt_fp2unsigned(desc->x0);
        if (ep->x24 != 0) {
            ++ep->x24;
        }
        {
            if ((desc->model_desc.animjoint != NULL) |
                (desc->model_desc.matanim_joint != NULL) |
                (desc->model_desc.shapeanim_joint != NULL))
            {
                HSD_JObjAddAnimAll(jobj, desc->model_desc.animjoint,
                                   desc->model_desc.matanim_joint,
                                   desc->model_desc.shapeanim_joint);
                HSD_JObjReqAnimAll(jobj, 0.0F);
                {
                    s32 temp_r5_2 = efLib_804D64F0[0];
                    efLib_804D64F0[0]++;
                    ((HSD_JObj**) efLib_80458EE0)[temp_r5_2] = jobj;
                    if (efLib_804D64F0[0] >= 32) {
                        HSD_ASSERTREPORT(224, 0, "Over Anime Call\n");
                    }
                }
            }
        }
    }
    HSD_GObjProc_8038FD54(ep->gobj, fn_8005BC50, 15);
    return ep;
}

// --- Effect Attachments ----------------------------------------------

Effect* efLib_8005C1B4(u32 idx, HSD_GObj* gobj, HSD_JObj* jobj)
{
    Effect* effect = efLib_8005BE88(idx, gobj);
    if ((effect) != NULL) {
        HSD_JObj* effect_jobj;
        if ((effect_jobj = GET_JOBJ(effect->gobj)) == NULL) {
            HSD_GObjPLink_80390228(effect->gobj);
            return NULL;
        } else {
            Vec3 translate;
            lb_8000C1C0(effect_jobj, jobj);
            lb_8000B1CC(jobj, NULL, &translate);
            HSD_JObjSetTranslate(effect_jobj, &translate);
            effect->xC = jobj;
        }
    }
    return effect;
}

Effect* efLib_8005C2BC(u32 idx, HSD_GObj* gobj, HSD_JObj* jobj)
{
    Effect* effect;
    if ((effect = eflib_attach_effect(idx, gobj, jobj)) != NULL) {
        lb_8000C290(GET_JOBJ(effect->gobj), jobj);
    }
    return effect;
}

Effect* efLib_8005C3DC(u32 idx, HSD_GObj* gobj, HSD_JObj* jobj)
{
    Effect* effect;
    if ((effect = eflib_attach_effect(idx, gobj, jobj)) != NULL) {
        Vec3 scale;
        HSD_JObjGetScale(GET_JOBJ(gobj), &scale);
        scale.x = scale.z = scale.y;
        HSD_JObjSetScale(GET_JOBJ(effect->gobj), &scale);
    }
    return effect;
}

Effect* efLib_8005C5C4(u32 idx, HSD_GObj* gobj, HSD_JObj* jobj)
{
    // --- PLS DONT INLINE ------------------------------------------------
    extern Effect* efLib_8005C1B4(u32 idx, HSD_GObj* gobj, HSD_JObj* jobj);
    // --------------------------------------------------------------------

    Effect* effect = efLib_8005C1B4(idx, gobj, jobj);

    if (effect != NULL) {
        lb_8000C290(GET_JOBJ(effect->gobj), jobj);
    }

    if (effect != NULL) {
        Vec3 scale;
        PAD_STACK(4);
        HSD_JObjGetScale(GET_JOBJ(gobj), &scale);
        scale.x = scale.z = scale.y;
        HSD_JObjSetScale(GET_JOBJ(effect->gobj), &scale);
    }
    return effect;
}

Effect* efLib_8005C6F4(u32 idx, HSD_GObj* gobj, HSD_JObj* jobj)
{
    // --- PLS DONT INLINE ------------------------------------------------
    extern Effect* efLib_8005C1B4(u32 idx, HSD_GObj* gobj, HSD_JObj* jobj);
    // --------------------------------------------------------------------

    Effect* effect = efLib_8005C1B4(idx, gobj, jobj);
    PAD_STACK(4);

    if (effect != NULL) {
        Vec3 scale;
        HSD_JObjGetScale(GET_JOBJ(gobj), &scale);
        scale.x = scale.z = scale.y;
        HSD_JObjSetScale(GET_JOBJ(effect->gobj), &scale);
    }
    if (effect != NULL) {
        effect->x10 = efLib_8005E2B4;
    }
    return effect;
}

Effect* efLib_8005C814(u32 idx, HSD_GObj* gobj, Vec3* translation)
{
    HSD_JObj* jobj_1;
    Effect* eff_1;

    eff_1 = efLib_8005BE88(idx, gobj);
    if (eff_1 != NULL) {
        jobj_1 = GET_JOBJ(eff_1->gobj);
        (void) jobj_1;
        HSD_JObjSetTranslate(jobj_1, translation);
    }
    return eff_1;
}

// --- End Effect Attachments ---------------------------------------------

void efLib_RenderCallback(HSD_GObj* gobj, int code)
{
    u32 particles_code;

    switch (code) {
    case 0:
        particles_code = 0;
        break;
    case 1:
        particles_code = 1;
        break;
    case 2:
        particles_code = 2;
        break;
    default:
        return;
    }
    HSD_StateSetColorUpdate(1);
    if (gobj->gx_link == 7) {
        psDispParticles(5, particles_code);
        return;
    }
    psDispParticles(2, particles_code);
}

void efLib_8005C9A4(HSD_GObj* gobj)
{
    hsd_8039CEAC(0x60000);
    hsd_8039EE24(0x60000);
}

void fn_8005C9D0(HSD_GObj* gobj)
{
    hsd_8039CEAC(0x10000);
    hsd_8039EE24(0x10000);
}

HSD_Generator* efLib_8005C9FC(s32 gfx_id, Vec3* pos)
{
    HSD_Generator* generator;
    u8 linkNo;

    linkNo = 0;
    switch (gfx_id) {
    case 0x121:
        linkNo = 2;
        break;
    case 0xFF:
    case 0x7918:
    case 0xFC:
    case 0xF7:
        linkNo = 1;
        break;
    }

    {
        u32 bank = (gfx_id / 1000);
        generator = hsd_8039F05C(linkNo, bank, gfx_id);
        if (generator != NULL) {
            generator->pos.x = pos->x;
            generator->pos.y = pos->y;
            generator->pos.z = pos->z;
        }
    }
    return generator;
}

HSD_Generator* efLib_8005CAB0(s32 gfx_id)
{
    HSD_Generator* generator;
    HSD_psAppSRT* appsrt;

    generator = hsd_8039F05C(0, (gfx_id / 1000), gfx_id);
    if (generator != NULL) {
        if ((appsrt = generator->appsrt) == NULL) {
            appsrt = psAddGeneratorAppSRT_begin(generator, 1);
        }
        if (appsrt == NULL) {
            hsd_8039D4DC(generator);
            return NULL;
        }
    }
    return generator;
}

HSD_Generator* efLib_8005CB34(s32 gfx_id, Vec3* translation, f32 direction)
{
    HSD_Generator* generator;
    HSD_psAppSRT* appsrt;

    generator = hsd_8039F05C(0, (gfx_id / 1000), gfx_id);
    if (generator != NULL) {
        if ((appsrt = generator->appsrt) == NULL) {
            appsrt = psAddGeneratorAppSRT_begin(generator, 1);
        }
        if (appsrt == NULL) {
            hsd_8039D4DC(generator);
            generator = NULL;
        }
    }
    if (generator != NULL) {
        generator->appsrt->translate.x = translation->x;
        generator->appsrt->translate.y = translation->y;
        generator->appsrt->translate.z = translation->z;
        if (direction < 0.0F) {
            generator->kind |= 0x40000;
            generator->appsrt->rot.y = -1.5707964F;
        } else {
            generator->appsrt->rot.y = 1.5707964F;
        }
    }
    return generator;
}

HSD_Generator* efLib_8005CC2C(s32 gfx_id, HSD_JObj* jobj)
{
    HSD_Generator* generator =
        hsd_8039EFAC(0, (gfx_id / 1000) /* bank */, gfx_id, jobj);
    if (generator != NULL) {
        generator->type &= ~PSAPPSRT_UNK_B10;
    }
    return generator;
}

HSD_Generator* efLib_8005CC84(s32 gfx_id, HSD_JObj* jobj)
{
    HSD_Generator* generator = hsd_8039EFAC(0, gfx_id / 1000, gfx_id, jobj);
    if (generator != NULL) {
        HSD_psAppSRT* appsrt;
        if ((appsrt = (generator)->appsrt) == NULL) {
            appsrt = psAddGeneratorAppSRT_begin(generator, 0);
        }
        if (appsrt != NULL) {
            appsrt->gp = generator;
        } else {
            hsd_8039D4DC(generator);
            return NULL;
        }
        (generator)->type &= 0xFFFFF9FF;
        (generator)->type |= PSAPPSRT_UNK_B11;
    }
    return generator;
}

HSD_Generator* efLib_8005CD2C(s32 gfx_id, va_list vlist, HSD_GObj* gobj)
{
    Vec3 scale;
    HSD_Generator* generator;
    s32 id;

    id = gfx_id;
    eflib_attach_gfx(&generator, id, va_arg(vlist, HSD_JObj*));
    if (generator != NULL) {
        HSD_JObjGetScale(GET_JOBJ(gobj), &scale);
        generator->appsrt->scale.x = generator->appsrt->scale.y =
            generator->appsrt->scale.z = scale.y;
    }
    return generator;
}

HSD_Generator* efLib_8005CE48(s32 gfx_id, va_list vlist)
{
    HSD_Generator* generator;

    eflib_attach_gfx(&generator, gfx_id, va_arg(vlist, HSD_JObj*));
    if (generator != NULL) {
        generator->appsrt->scale.x = generator->appsrt->scale.y =
            generator->appsrt->scale.z = *va_arg(vlist, f32*);
    }
    return generator;
}

HSD_Generator* efLib_8005CF40(s32 gfx_id, va_list vlist)
{
    HSD_Generator* generator;
    f32 direction;

    eflib_attach_gfx(&generator, gfx_id, va_arg(vlist, HSD_JObj*));
    if (generator != NULL) {
        direction = *va_arg(vlist, f32*);
        generator->appsrt->rot.y =
            direction < 0.0F ? -1.5707963267948966L : 1.5707963267948966L;
    }
    return generator;
}

HSD_Generator* efLib_8005D044(s32 gfx_id, va_list vlist)
{
    HSD_Generator* generator;
    f32 direction;
    HSD_JObj* jobj;
    s32 id;

    id = gfx_id;
    jobj = va_arg(vlist, HSD_JObj*);
    eflib_attach_gfx(&generator, id, jobj);
    if (generator != NULL) {
        direction = *va_arg(vlist, f32*);
        generator->appsrt->rot.y =
            direction < 0.0F ? -1.5707963267948966L : 1.5707963267948966L;
        generator->appsrt->scale.x = generator->appsrt->scale.y =
            generator->appsrt->scale.z = *va_arg(vlist, f32*);
    }
    return generator;
}

void efLib_8005D174(int arg0, s32 gfx_id, HSD_JObj* jobj, bool flag)
{
    HSD_Generator* generator;
    HSD_JObj* root = jobj;
    s32 chk = 0;

    PAD_STACK(28); // once walk macro is inlined i am sure this will auto-fix

    switch (gfx_id) {
    case 0x4A38:
    case 0x4A39:
    case 0x4A3A:
    case 0xB798:
    case 0xB799:
    case 0xB79A: {
        // attach, inherit root rot.y
        eflib_attach_gfx(&generator, gfx_id, jobj);
        if (generator != NULL) {
            WALK_TO_ROOT(root, 170);
            generator->appsrt->rot.y = HSD_JObjGetRotationY(root);
        }
        return;
    }
    case 0x2D:
    case 0x2E:
    case 0x31: {
        // attach, set flag 0x1000
        eflib_attach_gfx(&generator, gfx_id, jobj);
        if (generator != NULL) {
            generator->type |= 0x1000;
        }
        return;
    }
    case 0x127: {
        // attach, inherit root rot.y + scale
        eflib_attach_gfx(&generator, gfx_id, jobj);
        if (generator != NULL) {
            WALK_TO_ROOT(root, 2f0);
            generator->appsrt->rot.y = HSD_JObjGetRotationY(root);
            HSD_JObjGetScale(root, &generator->appsrt->scale);
        }
        return;
    }
    case 0x2:
    case 0x6:
    case 0xA3:
    case 0xA7:
    case 0xAA:
    case 0xF2:
    case 0x12A:
    case 0x132:
    case 0x133: {
        // attach, inherit root scale
        eflib_attach_gfx(&generator, gfx_id, jobj);
        if (generator != NULL) {
            WALK_TO_ROOT(root, 428);
            HSD_JObjGetScale(root, &generator->appsrt->scale);
        }
        return;
    }
    case 0x16D:
    case 0x16E:
    case 0x16F:
    case 0x170:
    case 0x7E2: {
        // standalone, inherit root rot.y + translation
        if ((generator = efLib_EnsureGeneratorAppSRT_inline(
                 hsd_8039F05C(0, (gfx_id / 1000), gfx_id), 1)) != NULL)
        {
            WALK_TO_ROOT(root, 53c);
            generator->appsrt->rot.y = HSD_JObjGetRotationY(root);
            HSD_JObjGetTranslation(root, &generator->appsrt->translate);
        }
        return;
    }
    case 0xD4: {
        // standalone(2, arg0), rot.z + translate + scale
        if ((generator = hsd_8039F05C(2, arg0, gfx_id)) != NULL) {
            HSD_psAppSRT* psAppSRT;
            if ((psAppSRT = generator->appsrt) == NULL) {
                psAppSRT = psAddGeneratorAppSRT_begin(generator, 1);
            }
            if (psAppSRT != NULL) {
                WALK_TO_ROOT(root, 64c);
                psAppSRT->rot.z = HSD_JObjGetRotationZ(root);
                HSD_JObjGetTranslation(root, &psAppSRT->translate);
                HSD_JObjGetScale(root, &psAppSRT->scale);
                return;
            }
            hsd_8039D4DC(generator);
        }
        return;
    }
    case 0x243: {
        // standalone(2, arg0), rot.z + translate
        if ((generator = hsd_8039F05C(2, arg0, gfx_id)) != NULL) {
            HSD_psAppSRT* psAppSRT;

            if ((psAppSRT = generator->appsrt) == NULL) {
                psAppSRT = psAddGeneratorAppSRT_begin(generator, 1);
            }
            if (psAppSRT != NULL) {
                WALK_TO_ROOT(root, 77c);
                psAppSRT->rot.z = HSD_JObjGetRotationZ(root);
                HSD_JObjGetTranslation(root, &psAppSRT->translate);
                return;
            }
            hsd_8039D4DC(generator);
        }
        return;
    }
    case 0xE3: {
        // standalone, root translate + root scale
        if ((generator = efLib_EnsureGeneratorAppSRT_inline(
                 hsd_8039F05C(0, (gfx_id / 1000), gfx_id), 1)) != NULL)
        {
            lb_8000B1CC(jobj, NULL, &generator->appsrt->translate);
            WALK_TO_ROOT(root, 864);
            HSD_JObjGetScale(root, &generator->appsrt->scale);
        }
        return;
    }

    case 0xFC:
    case 0xFF:
    case 0xF7:
    case 0x7918:
        chk = 1;
    }

    if (flag) {
        hsd_8039EFAC(chk, arg0, gfx_id, root);
    } else {
        hsd_8039F6CC(chk, arg0, gfx_id, root);
    }
}

void fn_8005DB20(s32 arg0, s32 arg1, s32 arg2, HSD_JObj* arg3)
{
    if (arg1 == 0x1E) {
        grLib_801C99C0(arg1, arg2, arg3, 0);
        return;
    }
    efLib_8005D174(arg1, arg2, arg3, 0);
}

void fn_8005DB70(int arg0, int lo, int hi, HSD_JObj* jobj)
{
    if (lo == 0x1E) {
        grLib_801C99C0(lo, hi, jobj, 1);
        return;
    }
    efLib_8005D174(lo, hi, jobj, 1);
}

void efLib_8005DBC0(HSD_Particle* particle)
{
    Vec3 translate;
    Vec3 scale;
    Quaternion rot;
    HSD_psAppSRT* appsrt;

    if (particle && particle->appsrt) {
        translate = particle->appsrt->translate;
        scale = particle->appsrt->scale;
        rot = particle->appsrt->rot;

        psRemoveParticleAppSRT(particle);

        if ((appsrt = psAddParticleAppSRT_begin(particle, 1))) {
            appsrt->translate = translate;
            appsrt->rot = rot;
            appsrt->scale = scale;
        } else {
            particle->cmdWait = 0;
            particle->size = 0.0F;
            particle->life = 1;
        }
    }
}

// must be placed here for data ordering reasons...
void (*lbl_803BF810[0x03])(HSD_Particle* particle) = { efLib_8005DBC0, NULL,
                                                       NULL };

void fn_8005DCD0(HSD_Particle* particle)
{
    if (particle->cmdList ==
        ((HSD_PSCmdList*) ptclref_804D0E5C[0][0x96])->cmdList)
    {
        hsd_8039D1E4((HSD_Generator*) particle, lbl_803BF810);
    }
    if (particle->cmdList ==
        ((HSD_PSCmdList*) ptclref_804D0E5C[0][0x97])->cmdList)
    {
        hsd_8039D1E4((HSD_Generator*) particle, lbl_803BF810);
    }
    if (particle->cmdList ==
        ((HSD_PSCmdList*) ptclref_804D0E5C[0][0x98])->cmdList)
    {
        hsd_8039D1E4((HSD_Generator*) particle, lbl_803BF810);
    }
    if (particle->cmdList ==
        ((HSD_PSCmdList*) ptclref_804D0E5C[0][0x21B])->cmdList)
    {
        hsd_8039D1E4((HSD_Generator*) particle, lbl_803BF810);
    }
}

void efLib_8005DDB8(Effect* effect)
{
    Vec3 sp14;
    HSD_JObj* eff_jobj;

    eff_jobj = GET_JOBJ(effect->gobj);
    lb_8000B1CC(effect->xC, NULL, &sp14);
    sp14.y += effect->translate.y;
    HSD_JObjSetTranslate(eff_jobj, &sp14);
}

void efLib_8005DE94(Effect* effect)
{
    f32 scale_x;
    f32 scale_y;
    f32 scale_z;
    HSD_JObj* eff_jobj;

    scale_x = effect->translate.x *
              HSD_JObjGetScaleX(eff_jobj = GET_JOBJ(effect->gobj));
    HSD_JObjSetScaleX(eff_jobj, scale_x);

    scale_y = effect->translate.x * HSD_JObjGetScaleY(eff_jobj);
    HSD_JObjSetScaleY(eff_jobj, scale_y);

    scale_z = effect->translate.x * HSD_JObjGetScaleZ(eff_jobj);
    HSD_JObjSetScaleZ(eff_jobj, scale_z);
}

void efLib_8005E090(Effect* effect)
{
    f64 temp_d;
    f32 rotate_y;
    HSD_JObj* eff_jobj;
    HSD_JObj* temp_r4;

    temp_r4 = (HSD_JObj*) effect->x14;
    eff_jobj = GET_JOBJ(effect->gobj);
    (void) temp_r4;
    if (temp_r4 != NULL) {
        if (temp_r4->scale.x < 0.0F) {
            temp_d = -1.5707963267948966L;
        } else {
            temp_d = 1.5707963267948966L;
        }
        rotate_y = temp_d;
        HSD_JObjSetRotationY(eff_jobj, rotate_y);
    }
    if ((u8) effect->x26 != 0) {
        effect->x24 = 0xBU;
        effect->x10 = NULL;
        HSD_JObjReqAnimAll(eff_jobj, 65.0F);
        return;
    }
    if (effect->x24 == 1) {
        effect->x24 = 6U;
        HSD_JObjReqAnimAll(eff_jobj, 60.0F);
    }
}

void efLib_8005E1D8(Effect* effect)
{
    HSD_JObj* eff_jobj_child;
    f32 translate_z;
    HSD_JObj* eff_jobj;

    eff_jobj = GET_JOBJ(effect->gobj);
    if (eff_jobj == NULL) {
        eff_jobj_child = NULL;
    } else {
        eff_jobj_child = eff_jobj->child;
    }
    translate_z = 2.0F + HSD_JObjGetTranslationZ(eff_jobj_child);
    HSD_JObjSetTranslateZ(eff_jobj_child, translate_z);
}

void efLib_8005E2B4(Effect* effect)
{
    HSD_JObj* eff_jobj;
    f64 temp_d;
    f32 rotate_y;

    eff_jobj = GET_JOBJ(effect->gobj);
    if (GET_FIGHTER(effect->parent_gobj)->facing_dir < 0.0F) {
        temp_d = -1.5707963267948966L;
    } else {
        temp_d = 1.5707963267948966L;
    }
    rotate_y = temp_d;
    HSD_JObjSetRotationY(eff_jobj, rotate_y);
}

void efLib_8005E3A0(Effect* effect)
{
    HSD_JObj* jobj_1;
    f32 f32_1;
    Fighter* fighter;

    fighter = GET_FIGHTER(effect->parent_gobj);
    jobj_1 = GET_JOBJ(effect->gobj);
    f32_1 = 1.5707964f - fighter->mv.co.common.x4;
    if (fighter->facing_dir < 0.0F) {
        HSD_JObjSetRotationY(jobj_1, -1.5707964f);
        HSD_JObjSetRotationZ(jobj_1, f32_1);
    } else {
        HSD_JObjSetRotationY(jobj_1, 1.5707964f);
        HSD_JObjSetRotationZ(jobj_1, -f32_1);
    }
}

void efLib_8005E648(Effect* effect)
{
    HSD_JObj* jobj_1;
    f32 rotate_y;
    f32 rotate_x;
    f32 translate_z;
    f32 translate_y;
    f32 translate_x;
    f32 temp_f;

    jobj_1 = GET_JOBJ(effect->gobj);
    translate_x = HSD_JObjGetTranslationX(jobj_1);
    translate_y = HSD_JObjGetTranslationY(jobj_1);
    translate_z = HSD_JObjGetTranslationZ(jobj_1);
    rotate_x = HSD_JObjGetRotationX(jobj_1);
    rotate_y = HSD_JObjGetRotationY(jobj_1);
    effect->translate.y -= 0.2f;
    temp_f = translate_x + sinf(rotate_y);
    HSD_JObjSetTranslateX(jobj_1, temp_f);
    HSD_JObjSetTranslateY(jobj_1, translate_y + effect->translate.y);
    HSD_JObjSetTranslateZ(jobj_1, translate_z + cosf(rotate_y));
    HSD_JObjSetRotationX(jobj_1, 0.5F + rotate_x);
}

void efLib_8005E950(Effect* effect)
{
    HSD_JObj* jobj_1;
    f32 translate_z;
    f32 translate_y;
    f32 translate_x;
    f32 temp_f;

    jobj_1 = GET_JOBJ(effect->gobj);
    translate_x = HSD_JObjGetTranslationX(jobj_1);
    translate_y = HSD_JObjGetTranslationY(jobj_1);
    translate_z = HSD_JObjGetTranslationZ(jobj_1);
    effect->translate.y -= 0.1f;
    temp_f = translate_x + effect->translate.x;
    HSD_JObjSetTranslateX(jobj_1, temp_f);
    HSD_JObjSetTranslateY(jobj_1, translate_y + effect->translate.y);
    HSD_JObjSetTranslateZ(jobj_1, translate_z + effect->translate.z);
}

void efLib_8005EB70(Effect* effect)
{
    if (effect->x24 == 1) {
        hsd_8039EFAC(0, 0, 0x1AB, effect->xC);
        effect->x10 = NULL;
        effect->x24 = 0x27U;
    }
}

void efLib_8005EBC8(Effect* effect)
{
    f64 temp_d;
    Vec3 sp38;
    Vec3 sp2C;
    HSD_JObj* jobj_2;
    f32 rotate_y;
    HSD_JObj* jobj_1;
    void* user_data;
    HSD_GObj* gobj_1;
    PAD_STACK(0xC);

    gobj_1 = effect->parent_gobj;
    jobj_1 = GET_JOBJ(gobj_1);
    jobj_2 = GET_JOBJ(effect->gobj);
    user_data = gobj_1->user_data;
    user_data = (void*) GET_FIGHTER(gobj_1);
    HSD_JObjGetScale(jobj_1, &sp38);
    HSD_JObjGetScale(jobj_2, &sp2C);
    sp38.x *= sp2C.x;
    sp38.y *= sp2C.y;
    sp38.z *= sp2C.z;
    HSD_JObjSetScale(jobj_2, &sp38);

    if (((Fighter*) user_data)->facing_dir < 0.0F) {
        temp_d = -1.5707963267948966L;
    } else {
        temp_d = 1.5707963267948966L;
    }
    rotate_y = temp_d;
    HSD_JObjSetRotationY(jobj_2, rotate_y);
}

void efLib_8005EDDC(Effect* effect)
{
    HSD_JObj* jobj_1;
    f32 rotate_z;

    jobj_1 = GET_JOBJ(effect->gobj);
    if ((GET_FIGHTER(effect->parent_gobj))->facing_dir < 0.0F) {
        HSD_JObjSetRotationY(jobj_1, -1.5707964f);
        rotate_z = effect->translate.z;
        HSD_JObjSetRotationZ(jobj_1, rotate_z);
    } else {
        HSD_JObjSetRotationY(jobj_1, 1.5707964f);
        rotate_z = -effect->translate.z;
        HSD_JObjSetRotationZ(jobj_1, rotate_z);
    }
}

void efLib_8005F08C(Effect* effect)
{
    HSD_JObj* eff_jobj;
    HSD_JObj* eff_child_jobj;
    HSD_JObj* eff_child_nxt_jobj;
    Fighter* fighter;

    eff_jobj = GET_JOBJ(effect->gobj);
    eff_child_jobj = eff_jobj == NULL ? NULL : eff_jobj->child;
    eff_child_nxt_jobj = eff_child_jobj == NULL ? NULL : eff_child_jobj->next;

    fighter = GET_FIGHTER(effect->parent_gobj);

    if (fighter->motion_id == 349) {
        HSD_JObjClearFlagsAll(eff_child_nxt_jobj, 0x10U);
    } else {
        HSD_JObjSetFlagsAll(eff_child_nxt_jobj, 0x10U);
    }
    if ((fighter->cmd_vars[3] != 0U) && ((s32) fighter->mv.co.common.xC != 0))
    {
        f32 rotate_z = -atan2f(fighter->coll_data.floor.normal.x,
                               fighter->coll_data.floor.normal.y);
        HSD_JObjSetRotationZ(eff_jobj, rotate_z);
    } else {
        HSD_JObjSetRotationZ(eff_jobj, 0.0F);
    }
}

void efLib_8005F270(Effect* effect)
{
    HSD_JObj* eff_jobj;
    HSD_JObj* eff_child_jobj;
    HSD_JObj* eff_child_nxt_jobj;
    Fighter* fighter;

    eff_jobj = GET_JOBJ(effect->gobj);
    eff_child_jobj = eff_jobj == NULL ? NULL : eff_jobj->child;
    eff_child_nxt_jobj = eff_child_jobj == NULL ? NULL : eff_child_jobj->next;

    fighter = GET_FIGHTER(effect->parent_gobj);

    if (fighter->motion_id == 357) {
        HSD_JObjClearFlagsAll(eff_child_nxt_jobj, 0x10U);
    } else {
        HSD_JObjSetFlagsAll(eff_child_nxt_jobj, 0x10U);
    }

    if ((fighter->cmd_vars[3] != 0U) && ((s32) fighter->mv.co.common.xC != 0))
    {
        f32 rotate_z = -atan2f(fighter->coll_data.floor.normal.x,
                               fighter->coll_data.floor.normal.y);
        HSD_JObjSetRotationZ(eff_jobj, rotate_z);
    } else {
        HSD_JObjSetRotationZ(eff_jobj, 0.0F);
    }
}

void efLib_8005F454(Effect* effect)
{
    f32 rotate_z;
    Fighter* fighter;
    HSD_JObj* jobj_1;
    HSD_JObj* jobj_2;

    jobj_1 = GET_JOBJ(effect->gobj);
    jobj_2 = GET_JOBJ(effect->x0->x4);
    if ((fighter = GET_FIGHTER(effect->parent_gobj))->motion_id == 359) {
        HSD_JObjClearFlagsAll(jobj_2, 0x10U);
    } else {
        HSD_JObjSetFlagsAll(jobj_2, 0x10U);
    }
    if ((fighter->cmd_vars[2] & 1) && ((s32) fighter->mv.co.common.x10 != 0)) {
        rotate_z = -atan2f(fighter->coll_data.floor.normal.x,
                           fighter->coll_data.floor.normal.y);
        HSD_JObjSetRotationZ(jobj_1, rotate_z);
        HSD_JObjSetRotationZ(jobj_2, rotate_z);
    } else {
        HSD_JObjSetRotationZ(jobj_1, 0.0F);
        HSD_JObjSetRotationZ(jobj_2, 0.0F);
    }
}

void efLib_8005F748(Effect* effect)
{
    ftCo_800C0FCC(effect->gobj, effect->parent_gobj);
}

void efLib_8005F774(HSD_JObj* jobj, s32 count, u32 konst, u32 tev0)
{
    HSD_DObj* dobj = HSD_JObjGetDObj(jobj);
    HSD_MObj* mobj = dobj != NULL ? dobj->mobj : NULL;
    HSD_TObj* tobj = HSD_MObjGetTObj(mobj);

    while (count != 0) {
        HSD_TObj* next = tobj->next;
        tobj = next;
        count--;
    }

    tobj->tev->konst.r = (konst >> 16) & 0xFF;
    tobj->tev->konst.g = (konst >> 8) & 0xFF;
    tobj->tev->konst.b = konst & 0xFF;
    tobj->tev->tev0.r = (tev0 >> 16) & 0xFF;
    tobj->tev->tev0.g = (tev0 >> 8) & 0xFF;
    tobj->tev->tev0.b = tev0 & 0xFF;
}

// Must be declared here for the below functions to base their references to
// efLib_80458F60 off of efLib_80458EE0 whereas the above functions seemingly
// are unaware that these two structs live right next to each other. I assumed
// that there was a split or something but I am not sure because the jobj
// text is supposedly shared between these functions and eflib. Weird.

/* 458EE0 */ _struct_efLib_80458EE0 efLib_80458EE0[0x10];
/* 458F60 */ _struct_efLib_80458EE0 efLib_80458F60[0x8];

void efLib_8005F864(HSD_GObj* gobj, u8 arg1, f32 arg2, f32 arg3)
{
    s32 idx;

    // WHY
    _struct_efLib_80458EE0* base = efLib_80458EE0 + 0x10;

    for (idx = 0; idx < 8; idx++) {
        if (base[idx].x0_gobj == gobj) {
            goto found;
        }
    }
    for (idx = 0; idx < 8; idx++) {
        if (base[idx].x0_gobj == NULL) {
            goto found;
        }
    }
    return;

found:
    // WHY
    efLib_80458EE0[idx + 0x10].x0_gobj = gobj;
    efLib_80458EE0[idx + 0x10].x6_unk = arg1;
}

void efLib_8005F990(HSD_GObj* gobj, u16 arg1)
{
    s32 idx;

    // WHY
    _struct_efLib_80458EE0* base = efLib_80458EE0 + 0x10;

    for (idx = 0; idx < 8; idx++) {
        if (base[idx].x0_gobj == gobj) {
            goto found;
        }
    }
    for (idx = 0; idx < 8; idx++) {
        if (base[idx].x0_gobj == NULL) {
            goto found;
        }
    }
    return;

found:
    // WHY
    efLib_80458EE0[idx + 0x10].x0_gobj = gobj;
    efLib_80458EE0[idx + 0x10].x4_unk = arg1;
}

void efLib_8005FAB8(Effect* effect)
{
    HSD_DObj* dobj;
    HSD_JObj* jobj;
    HSD_MObj* mobj;
    HSD_TObj* tobj;
    HSD_JObj* hsd_obj;
    _struct_efLib_80458EE0* entry;
    PAD_STACK(8);

    hsd_obj = GET_JOBJ(effect->gobj);
    jobj = hsd_obj == NULL ? NULL : hsd_obj->child;
    dobj = HSD_JObjGetDObj(jobj);
    mobj = dobj != NULL ? dobj->mobj : NULL;
    tobj = HSD_MObjGetTObj(mobj);
    {
        s32 i;
        entry = &efLib_80458F60[0];
        for (i = 0; i != 8; ++i) {
            if (entry->x0_gobj == effect->parent_gobj) {
                if (efLib_80458F60[i].x4_unk == 0x417) {
                    tobj = tobj->next;
                }
                tobj->tev->konst.a = (u8) efLib_80458F60[i].x6_unk;
                if (efLib_80458F60[i].x4_unk == 0x419) {
                    s32 j;
                    for (j = 0; j < 6; j++) {
                        jobj = jobj->next;
                        dobj = HSD_JObjGetDObj(jobj);
                        mobj = dobj != NULL ? dobj->mobj : NULL;
                        tobj = HSD_MObjGetTObj(mobj);
                        tobj->tev->konst.a = efLib_80458F60[i].x6_unk;
                    }
                }
                break;
            }
            entry++;
        }
    }
}

void fn_8005FBE4(Effect* effect)
{
    Vec3 translate;

    lb_8000B1CC(effect->xC, NULL, &translate);
    translate.x += effect->translate.x;
    translate.y += effect->translate.y;
    translate.z += effect->translate.z;
    HSD_JObjSetTranslate(GET_JOBJ(effect->gobj), &translate);
}

Effect* efLib_8005FCD8(int arg0, HSD_GObj* gobj, HSD_JObj* jobj, Vec3* vec)
{
    HSD_Generator* generator;
    Effect* ep = efLib_8005BE88(0, gobj);

    if (ep != NULL) {
        ep->x10 = fn_8005FBE4;
        ep->xC = jobj;
        ep->translate = *vec;
        eflib_attach_gfx(&generator, arg0, GET_JOBJ(ep->gobj));
    }
    return ep;
}
