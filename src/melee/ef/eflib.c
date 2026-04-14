/*
 * TODO: I looked at the strings in the ASM, I think there was only
 *       ever eflib.c and efasync.c (?) The files in this folder
 *       and splits / symbols should be adjusted accordingly with time,
 *       but for the sake of matching files %, we can leave these
 *       separate for now. Also I dont know if anyone cares as long
 *       as it matches lol.
 */
#include "eflib.h"

#include "efasync.h"
#include "efdata.h"
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

#include "MSL/math.h"

#include <runtime.h>
#include <trigf.h>

// externs
extern u32* ptclref_804D0E5C[65];
extern EF_DAT_Entry efAsync_DatEntries[51];
extern u32 hsd_804D7900;

// forward declarations to avoid sdata2 pollution
void HSD_MtxGetScale(Mtx, Vec3*);
void grLib_801C99C0(s32, s32, HSD_JObj*, s32);

// forward declare for B4B8
void efLib_render_callback(HSD_GObj*, int);
void efLib_particles_proc_main(HSD_GObj*);
void efLib_particles_proc_aux(HSD_GObj*);

// Particle linkNo skip masks (bits 16+) for hsd_8039CEAC / hsd_8039EE24
// Set bit = skip processing for that linkNo
/* TODO: Get these from particles.h once that is fully fleshed out */
#define PTCL_SKIP_LINKNO_0 0x10000
#define PTCL_SKIP_LINKNO_1 0x20000
#define PTCL_SKIP_LINKNO_2 0x40000

// Particle linkNo render masks (bits 0+) for psDispParticles
// Set bit = include for rendering
/* TODO: Get these from particles.h once that is fully fleshed out */
#define PTCL_RENDER_LINKNO_0 0x1
#define PTCL_RENDER_LINKNO_1 0x2
#define PTCL_RENDER_LINKNO_2 0x4

/* ---------------------------------------------------- */
/*                       INLINES                        */
/* ---------------------------------------------------- */

void inline eflib_create_generator_add_appsrt(HSD_Generator** generator, s32 gfx_id,
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
            goto eflib_create_generator_add_appsrt_exit;
        }
        (*generator)->type &= 0xFFFFF9FF;
        (*generator)->type |= PSAPPSRT_UNK_B11;
    eflib_create_generator_add_appsrt_exit:;
    }
}

inline EF_Effect* eflib_create_effect_and_attach(int gfx_id, HSD_GObj* gobj, HSD_JObj* jobj)
{
    EF_Effect* effect = efLib_Create(gfx_id, gobj);
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
            effect->attach_jobj = jobj;
        }
    }
    return effect;
}

inline HSD_Generator*
eflib_generator_add_appsrt(HSD_Generator* generator, s32 status)
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
            else {                                                            \
                _parent = (_jobj)->parent;                                    \
            }                                                                 \
        } while (_parent != NULL);                                            \
    }

void efLib_Init(void)
{
    HSD_GObj* gobj;
    int i;
    HSD_ObjAllocInit(&efLib_AllocData, 0x2CU, 4U);

    efLib_EffectCount = 0;

    for (i = 0; i < 50; ++i) {
        efAsync_DatEntries[i].data = NULL;
    }

    hsd_8039D354(0);
    hsd_80398A08(0);
    hsd_804D7900 = (u32) efLib_Cb_PtclAppSRTHook;

    gobj = GObj_Create(8U, 0xBU, 1U);
    GObj_SetupGXLink(gobj, efLib_render_callback, 7U, 2U);
    HSD_GObj_SetupProc(gobj, efLib_particles_proc_main, 0xFU);

    gobj = GObj_Create(8U, 0xCU, 1U);
    GObj_SetupGXLink(gobj, efLib_render_callback, 8U, 2U);
    HSD_GObj_SetupProc(gobj, efLib_particles_proc_aux, 0xFU);

    HSD_JObjSetSPtclCallback(efLib_Cb_SPtcl);
    HSD_JObjSetDPtclCallback(efLib_Cb_DPtcl);
    psInitAppSRT(0, 0xA4);
    efAsync_QueueInit();

    for (i = 0; i < 8; i++) {
        efLib_ParamTable[i].gobj = NULL;
        efLib_ParamTable[i].alpha = 0xFF;
    }
}

void efLib_SetFlags(HSD_GObj* gobj, s32 expire_flags)
{
    HSD_GObj* gobj_1;
    HSD_GObj* gobj_2;
    EF_Effect* effect_1;
    EF_Effect* effect_2;

    gobj_1 = HSD_GObj_Entities->x2C;
    while (gobj_1 != NULL) {
        effect_1 = GET_EFFECT(gobj_1);
        if ((effect_1 != NULL) && (effect_1->parent_gobj == gobj)) {
            effect_1->expire_flags |= expire_flags;
        }
        gobj_1 = gobj_1->next;
    }
    gobj_2 = HSD_GObj_Entities->x30;
    while (gobj_2 != NULL) {
        effect_2 = GET_EFFECT(gobj_2);
        if ((effect_2 != NULL) && (effect_2->parent_gobj == gobj)) {
            effect_2->expire_flags |= expire_flags;
        }
        gobj_2 = gobj_2->next;
    }
}

void efLib_Destroy(HSD_GObj* gobj)
{
    EF_Effect* effect = gobj->user_data;
    HSD_JObj* jobj;
    int i;
    u8 obj_kind;

    if ((effect != NULL) && (effect->is_async == 0) && (gobj != NULL)) {
        for (i = 0; i < 8; i++) {
            HSD_GObj* efLib_gobj = efLib_ParamTable[i].gobj;
            if (efLib_gobj == gobj) {
                efLib_ParamTable[i].gobj = NULL;
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
    HSD_GObj* gobj_2;
    int i;
    PAD_STACK(48);

    for (i = 0; i < 8; i++) {
        if (efLib_ParamTable[i].gobj == gobj) {
            efLib_ParamTable[i].gobj = NULL;
        }
    }
    gobj_1 = HSD_GObj_Entities->x2C;
    while (gobj_1 != NULL) {
        HSD_GObj* gobj_2;
        EF_Effect* effect_1;

        gobj_2 = gobj_1->next;
        if (((effect_1 = GET_EFFECT(gobj_1)) != NULL) &&
            (effect_1->parent_gobj == gobj))
        {
            if (effect_1->gobj->obj_kind == HSD_GObj_804D7849) {
                HSD_JObjWalkTree(effect_1->gobj->hsd_obj, hsd_8039D688, NULL);
            }
            HSD_GObjPLink_80390228(effect_1->gobj);
        }
        gobj_1 = gobj_2;
    }
    gobj_2 = HSD_GObj_Entities->x30;
    while (gobj_2 != NULL) {
        HSD_GObj* gobj_3;
        EF_Effect* effect_2;

        effect_2 = GET_EFFECT(gobj_2);
        gobj_2 = gobj_2->next;
        if ((effect_2 != NULL) && (effect_2->parent_gobj == gobj)) {
            gobj_3 = effect_2->gobj;
            if (gobj_3->obj_kind == HSD_GObj_804D7849) {
                HSD_JObjWalkTree(gobj_3->hsd_obj, hsd_8039D688, NULL);
            }
            HSD_GObjPLink_80390228(effect_2->gobj);
        }
    }
    if (gobj->obj_kind == HSD_GObj_804D7849) {
        HSD_JObjWalkTree(gobj->hsd_obj, hsd_8039D688, NULL);
    }
}

void efLib_PauseAll(HSD_GObj* gobj)
{
    HSD_GObj* gobj_1;
    HSD_GObj* gobj_2;
    EF_Effect* effect_1;
    EF_Effect* effect_2;

    gobj_1 = HSD_GObj_Entities->x2C;
    while (gobj_1 != NULL) {
        effect_1 = GET_EFFECT(gobj_1);
        if ((effect_1 != NULL) && (effect_1->parent_gobj == gobj)) {
            effect_1->state_flags = (effect_1->state_flags & EF_STATE_ASYNC) | EF_STATE_ENTERING_PAUSE;
        }
        gobj_1 = gobj_1->next;
    }
    gobj_2 = HSD_GObj_Entities->x30;
    while (gobj_2 != NULL) {
        effect_2 = GET_EFFECT(gobj_2);
        if ((effect_2 != NULL) && (effect_2->parent_gobj == gobj)) {
            effect_2->state_flags = (effect_2->state_flags & EF_STATE_ASYNC) | EF_STATE_ENTERING_PAUSE;
        }
        gobj_2 = gobj_2->next;
    }
}

void efLib_ResumeAll(HSD_GObj* gobj)
{
    HSD_GObj* gobj_1;
    HSD_GObj* gobj_2;
    EF_Effect* effect_1;
    EF_Effect* effect_2;

    gobj_1 = HSD_GObj_Entities->x2C;
    while (gobj_1 != NULL) {
        effect_1 = GET_EFFECT(gobj_1);
        if ((effect_1 != NULL) && (effect_1->parent_gobj == gobj)) {
            effect_1->state_flags &= EF_STATE_ASYNC;
        }
        gobj_1 = gobj_1->next;
    }
    gobj_2 = HSD_GObj_Entities->x30;
    while (gobj_2 != NULL) {
        effect_2 = GET_EFFECT(gobj_2);
        if ((effect_2 != NULL) && (effect_2->parent_gobj == gobj)) {
            effect_2->state_flags &= EF_STATE_ASYNC;
        }
        gobj_2 = gobj_2->next;
    }
}

void efLib_remove_user_data(void* user_data)
{
    EF_Effect* effect;
    EF_Effect* effect_2;
    effect = effect_2 = user_data;
    if (effect_2->gobj != NULL) {
        if (effect->is_async == 0) {
            efLib_EffectCount--;
        }
        HSD_ObjFree(&efLib_AllocData, effect);
    } else {
        OSReport("Duplicate Free %08X\n", effect);
        HSD_ASSERT(53, 0);
    }
}

void efLib_RemoveLast(void)
{
    HSD_GObj* gobj;
    HSD_GObj* next;

    gobj = HSD_GObj_Entities->x2C;
    while (gobj != NULL) {
        next = gobj->next;
        efLib_Destroy(gobj);
        {
            u32 check = efLib_EffectCount, value = 0x40U;
            if (check < value) {
                return;
            }
        }
        gobj = next;
    }

    gobj = HSD_GObj_Entities->x30;
    while (gobj != NULL) {
        next = gobj->next;
        efLib_Destroy(gobj);
        {
            u32 check = efLib_EffectCount, value = 0x40U;
            if (check < value) {
                return;
            }
        }
        gobj = next;
    }

    HSD_ASSERTREPORT(77, 0, "can't remove no force effect!\n");
}

void efLib_Update(HSD_GObj* gobj)
{
    EF_Effect* effect;
    HSD_JObj* jobj = gobj->hsd_obj;
    switch ((effect = GET_EFFECT(gobj))->state_flags) {
    case EF_STATE_ENTERING_PAUSE:
        effect->state_flags++;
        break;
    case EF_STATE_PAUSED:
        return;
    }
    if (effect->lifetime != 0) {
        u16 param = effect->lifetime - 1;
        effect->lifetime = param;
        if (param == 0) {
            HSD_GObjPLink_80390228(gobj);
            return;
        }
    }
    if (effect->scale_flags != EF_SCALE_NO_INHERIT) {
        if ((effect->attach_jobj) != NULL) {
            Vec3 scale;
            if (HSD_JObjGetParent(effect->attach_jobj) != NULL) {
                HSD_JObj* attach_jobj = effect->attach_jobj;
                if (attach_jobj != NULL && HSD_JObjMtxIsDirty(attach_jobj)) {
                    HSD_JObjSetupMatrixSub(attach_jobj);
                }
                if (effect->scale_flags & EF_SCALE_INHERIT) {
                    HSD_MtxGetScale(HSD_JObjGetMtxPtr(effect->attach_jobj), &scale);
                }
            } else if (effect->scale_flags & EF_SCALE_INHERIT) {
                HSD_JObjGetScale(effect->attach_jobj, &scale);
            }
            if (effect->scale_flags & EF_SCALE_INHERIT) {
                scale.x = scale.z = scale.y;
                HSD_JObjSetScale(jobj, &scale);
            }
        }
    }
    HSD_JObjAnimAll(jobj);
    if (effect->update != NULL) {
        effect->update(effect);
    }
}

EF_Effect* efLib_Create(int gfx_id, HSD_GObj* parent_gobj)
{
    EF_Effect* effect;
    EF_EffectDesc* desc;
    u8 p_link;

    desc = &((EF_EffectDesc*) efAsync_DatEntries[gfx_id / 1000].data)[gfx_id % 1000];

    if (efLib_LoadKind == EF_LOADKIND_ASYNC) {
        if (efLib_EffectCount >= 64) {
            efLib_RemoveLast();
        }

        efLib_EffectCount += 1;
    }

    {
        EF_Effect* new_effect = HSD_ObjAlloc(&efLib_AllocData);
        if (new_effect == NULL) {
            effect = NULL;
        } else {
            new_effect->next = NULL;
            effect = new_effect;
            new_effect->gobj = NULL;
            new_effect->attach_jobj = NULL;
            new_effect->update = NULL;
            new_effect->state_flags = EF_STATE_ACTIVE;
            new_effect->expire_flags = EF_DOES_NOT_EXPIRE;
            new_effect->scale_flags = EF_SCALE_NO_INHERIT;
            new_effect->is_async = efLib_LoadKind;
        }
    }

    if (effect == NULL) {
        return NULL;
    }
    if (parent_gobj == NULL && effect->is_async) {
        HSD_ASSERTREPORT(177, 0, "error no parent gobj!\n");
    }

    if (gfx_id >= 27 || gfx_id < 25) {
        p_link = 11;
    } else {
        p_link = 12;
    }
    effect->parent_gobj = parent_gobj;
    {
        HSD_GObj* gobj = GObj_Create(HSD_GOBJ_CLASS_EFFECT, p_link, 0);
        effect->gobj = gobj;
        if (gobj == NULL) {
            if (effect->gobj != NULL) {
                if (effect->is_async == 0) {
                    efLib_EffectCount -= 1;
                }
                HSD_ObjFree(&efLib_AllocData, effect);
            } else {
                HSD_ASSERTREPORT(53, 0, "Duplicate Free %08X\n", effect);
            }
            return NULL;
        }
    }
    GObj_SetupGXLink(effect->gobj, HSD_GObj_JObjCallback, 7, 1);
    GObj_InitUserData(effect->gobj, 8, efLib_remove_user_data, effect);
    {
        HSD_JObj* jobj = HSD_JObjLoadJoint(desc->model_desc.joint);
        if (jobj == NULL) {
            HSD_GObjPLink_80390228(effect->gobj);
            return NULL;
        }
        {
            u8 kind = HSD_GObj_804D7849;
            HSD_GObjObject_80390A70(effect->gobj, kind, jobj);
        }
        if ((__cvt_fp2unsigned(10.0F * desc->lifetime) % 10) != 0) {
            lb_80011C18(jobj, 0x08000000);
        }
        effect->lifetime = __cvt_fp2unsigned(desc->lifetime);
        if (effect->lifetime != 0) {
            ++effect->lifetime;
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
                    s32 temp_r5_2 = efLib_AnimCount;
                    efLib_AnimCount++;
                    ((HSD_JObj**) efLib_AnimQueue)[temp_r5_2] = jobj;
                    if (efLib_AnimCount >= 32) {
                        HSD_ASSERTREPORT(224, 0, "Over Anime Call\n");
                    }
                }
            }
        }
    }
    HSD_GObj_SetupProc(effect->gobj, efLib_Update, 15);
    return effect;
}

EF_Effect* efLib_Create_Attach(u32 gfx_id, HSD_GObj* gobj, HSD_JObj* jobj)
{
    EF_Effect* effect = efLib_Create(gfx_id, gobj);
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
            effect->attach_jobj = jobj;
        }
    }
    return effect;
}

EF_Effect* efLib_Create_AttachChild(u32 gfx_id, HSD_GObj* gobj, HSD_JObj* jobj)
{
    EF_Effect* effect;
    if ((effect = eflib_create_effect_and_attach(gfx_id, gobj, jobj)) != NULL) {
        lb_8000C290(GET_JOBJ(effect->gobj), jobj);
    }
    return effect;
}

EF_Effect* efLib_Create_Attach_Scale(u32 gfx_id, HSD_GObj* gobj, HSD_JObj* jobj)
{
    EF_Effect* effect;
    if ((effect = eflib_create_effect_and_attach(gfx_id, gobj, jobj)) != NULL) {
        Vec3 scale;
        HSD_JObjGetScale(GET_JOBJ(gobj), &scale);
        scale.x = scale.z = scale.y;
        HSD_JObjSetScale(GET_JOBJ(effect->gobj), &scale);
    }
    return effect;
}

EF_Effect* efLib_Create_AttachChild_Scale(u32 gfx_id, HSD_GObj* gobj, HSD_JObj* jobj)
{
    // --- PLS DONT INLINE ------------------------------------------------
    extern EF_Effect* efLib_Create_Attach(u32 gfx_id, HSD_GObj* gobj, HSD_JObj* jobj);
    // --------------------------------------------------------------------

    EF_Effect* effect = efLib_Create_Attach(gfx_id, gobj, jobj);

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

EF_Effect* efLib_Create_Attach_Scale_FacingDir(u32 gfx_id, HSD_GObj* gobj, HSD_JObj* jobj)
{
    // --- PLS DONT INLINE ------------------------------------------------
    extern EF_Effect* efLib_Create_Attach(u32 gfx_id, HSD_GObj* gobj, HSD_JObj* jobj);
    // --------------------------------------------------------------------

    EF_Effect* effect = efLib_Create_Attach(gfx_id, gobj, jobj);
    PAD_STACK(4);

    if (effect != NULL) {
        Vec3 scale;
        HSD_JObjGetScale(GET_JOBJ(gobj), &scale);
        scale.x = scale.z = scale.y;
        HSD_JObjSetScale(GET_JOBJ(effect->gobj), &scale);
    }
    if (effect != NULL) {
        effect->update = efLib_Cb_SetRotY_FromFighterDir;
    }
    return effect;
}

EF_Effect* efLib_Create_Attach_Pos(u32 gfx_id, HSD_GObj* gobj, Vec3* position)
{
    HSD_JObj* jobj;
    EF_Effect* effect;

    effect = efLib_Create(gfx_id, gobj);
    if (effect != NULL) {
        jobj = GET_JOBJ(effect->gobj);
        (void) jobj;
        HSD_JObjSetTranslate(jobj, position);
    }
    return effect;
}

void efLib_render_callback(HSD_GObj* gobj, int code)
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
        psDispParticles(PTCL_RENDER_LINKNO_0 | PTCL_RENDER_LINKNO_2, particles_code);
        return;
    }
    psDispParticles(PTCL_RENDER_LINKNO_1, particles_code);
}

void efLib_particles_proc_main(HSD_GObj* gobj)
{
    hsd_8039CEAC(PTCL_SKIP_LINKNO_1 | PTCL_SKIP_LINKNO_2);
    hsd_8039EE24(PTCL_SKIP_LINKNO_1 | PTCL_SKIP_LINKNO_2);
}

void efLib_particles_proc_aux(HSD_GObj* gobj)
{
    hsd_8039CEAC(PTCL_SKIP_LINKNO_0);
    hsd_8039EE24(PTCL_SKIP_LINKNO_0);
}

HSD_Generator* efLib_CreateGenerator(s32 gfx_id, Vec3* pos)
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

HSD_Generator* efLib_CreateGenerator_AddAppSRT(s32 gfx_id)
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

HSD_Generator* efLib_CreateGenerator_Translate_FacingDir(s32 gfx_id, Vec3* translation, f32 direction)
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
            generator->appsrt->rot.y = -M_PI_2_F;
        } else {
            generator->appsrt->rot.y = M_PI_2_F;
        }
    }
    return generator;
}

HSD_Generator* efLib_CreateGenerator_Attach(s32 gfx_id, HSD_JObj* jobj)
{
    HSD_Generator* generator =
        hsd_8039EFAC(0, gfx_id / 1000, gfx_id, jobj);
    if (generator != NULL) {
        generator->type &= ~PSAPPSRT_UNK_B10;
    }
    return generator;
}

HSD_Generator* efLib_CreateGenerator_Attach_AddAppSRT(s32 gfx_id, HSD_JObj* jobj)
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

HSD_Generator* efLib_CreateGenerator_Attach_Scale(s32 gfx_id, va_list vlist, HSD_GObj* gobj)
{
    Vec3 scale;
    HSD_Generator* generator;
    s32 id;

    id = gfx_id;
    eflib_create_generator_add_appsrt(&generator, id, va_arg(vlist, HSD_JObj*));
    if (generator != NULL) {
        HSD_JObjGetScale(GET_JOBJ(gobj), &scale);
        generator->appsrt->scale.x = generator->appsrt->scale.y =
            generator->appsrt->scale.z = scale.y;
    }
    return generator;
}

HSD_Generator* efLib_CreateGenerator_AppSRT_SetScale(s32 gfx_id, va_list vlist)
{
    HSD_Generator* generator;

    eflib_create_generator_add_appsrt(&generator, gfx_id, va_arg(vlist, HSD_JObj*));
    if (generator != NULL) {
        generator->appsrt->scale.x = generator->appsrt->scale.y =
            generator->appsrt->scale.z = *va_arg(vlist, f32*);
    }
    return generator;
}

HSD_Generator* efLib_CreateGenerator_AppSRT_SetFacingDir(s32 gfx_id, va_list vlist)
{
    HSD_Generator* generator;
    f32 direction;

    eflib_create_generator_add_appsrt(&generator, gfx_id, va_arg(vlist, HSD_JObj*));
    if (generator != NULL) {
        direction = *va_arg(vlist, f32*);
        generator->appsrt->rot.y =
            direction < 0.0F ? -M_PI_2 : M_PI_2;
    }
    return generator;
}

HSD_Generator* efLib_CreateGenerator_AppSRT_SetFacingDirScale(s32 gfx_id, va_list vlist)
{
    HSD_Generator* generator;
    f32 direction;
    HSD_JObj* jobj;
    s32 id;

    id = gfx_id;
    jobj = va_arg(vlist, HSD_JObj*);
    eflib_create_generator_add_appsrt(&generator, id, jobj);
    if (generator != NULL) {
        direction = *va_arg(vlist, f32*);
        generator->appsrt->rot.y =
            direction < 0.0F ? -M_PI_2 : M_PI_2;
        generator->appsrt->scale.x = generator->appsrt->scale.y =
            generator->appsrt->scale.z = *va_arg(vlist, f32*);
    }
    return generator;
}

void efLib_SpawnParticleEffect(int bank, s32 gfx_id, HSD_JObj* jobj, bool flag)
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
        eflib_create_generator_add_appsrt(&generator, gfx_id, jobj);
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
        eflib_create_generator_add_appsrt(&generator, gfx_id, jobj);
        if (generator != NULL) {
            generator->type |= 0x1000;
        }
        return;
    }
    case 0x127: {
        // attach, inherit root rot.y + scale
        eflib_create_generator_add_appsrt(&generator, gfx_id, jobj);
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
        eflib_create_generator_add_appsrt(&generator, gfx_id, jobj);
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
        if ((generator = eflib_generator_add_appsrt(
                 hsd_8039F05C(0, (gfx_id / 1000), gfx_id), 1)) != NULL)
        {
            WALK_TO_ROOT(root, 53c);
            generator->appsrt->rot.y = HSD_JObjGetRotationY(root);
            HSD_JObjGetTranslation(root, &generator->appsrt->translate);
        }
        return;
    }
    case 0xD4: {
        // standalone(2, bank), rot.z + translate + scale
        if ((generator = hsd_8039F05C(2, bank, gfx_id)) != NULL) {
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
        // standalone(2, bank), rot.z + translate
        if ((generator = hsd_8039F05C(2, bank, gfx_id)) != NULL) {
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
        if ((generator = eflib_generator_add_appsrt(
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
        hsd_8039EFAC(chk, bank, gfx_id, root);
    } else {
        hsd_8039F6CC(chk, bank, gfx_id, root);
    }
}

// SPtcl callback. Registered via HSD_JObjSetSPtclCallback.
// Static particles are managed in a list and persist across frames.
void efLib_Cb_SPtcl(s32 linkNo, s32 bank, s32 gfx_id, HSD_JObj* jobj)
{
    if (bank == 0x1E) {
        grLib_801C99C0(bank, gfx_id, jobj, 0);
        return;
    }
    efLib_SpawnParticleEffect(bank, gfx_id, jobj, 0);
}

// DPtcl callback. Registered via HSD_JObjSetDPtclCallback.
// Dynamic particles are standalone generators, not in the managed list.
void efLib_Cb_DPtcl(int linkNo, int bank, int gfx_id, HSD_JObj* jobj)
{
    if (bank == 0x1E) {
        grLib_801C99C0(bank, gfx_id, jobj, 1);
        return;
    }
    efLib_SpawnParticleEffect(bank, gfx_id, jobj, 1);
}

void efLib_Cb_ParticleRender(HSD_Particle* particle)
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
void (*lbl_803BF810[0x03])(HSD_Particle* particle) = { efLib_Cb_ParticleRender, NULL,
                                                       NULL };

// Global particle callback. Checks if the particle cmdList matches
// bank 0 refs (0x96, 0x97, 0x98, 0x21B). If matched, attaches an
// AppSRT transform so the particle inherits transforms from its
// parent joint.
void efLib_Cb_PtclAppSRTHook(HSD_Particle* particle)
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

void efLib_Cb_SetOffsetY_FromParamY(EF_Effect* effect)
{
    Vec3 sp14;
    HSD_JObj* eff_jobj;

    eff_jobj = GET_JOBJ(effect->gobj);
    lb_8000B1CC(effect->attach_jobj, NULL, &sp14);
    sp14.y += effect->params.y;
    HSD_JObjSetTranslate(eff_jobj, &sp14);
}

void efLib_Cb_SetScale_FromParamX(EF_Effect* effect)
{
    f32 scale_x;
    f32 scale_y;
    f32 scale_z;
    HSD_JObj* eff_jobj;

    scale_x = effect->params.x *
              HSD_JObjGetScaleX(eff_jobj = GET_JOBJ(effect->gobj));
    HSD_JObjSetScaleX(eff_jobj, scale_x);

    scale_y = effect->params.x * HSD_JObjGetScaleY(eff_jobj);
    HSD_JObjSetScaleY(eff_jobj, scale_y);

    scale_z = effect->params.x * HSD_JObjGetScaleZ(eff_jobj);
    HSD_JObjSetScaleZ(eff_jobj, scale_z);
}

void efLib_Cb_SetRotYAndTransition(EF_Effect* effect)
{
    f64 temp_d;
    f32 rotate_y;
    HSD_JObj* eff_jobj;
    HSD_JObj* user_data;

    user_data = (HSD_JObj*) effect->user_data;
    eff_jobj = GET_JOBJ(effect->gobj);
    (void) user_data;
    if (user_data != NULL) {
        if (user_data->scale.x < 0.0F) {
            temp_d = -M_PI_2;
        } else {
            temp_d = M_PI_2;
        }
        rotate_y = temp_d;
        HSD_JObjSetRotationY(eff_jobj, rotate_y);
    }
    if ((u8) effect->expire_flags != EF_DOES_NOT_EXPIRE) {
        effect->lifetime = 0xBU;
        effect->update = NULL;
        HSD_JObjReqAnimAll(eff_jobj, 65.0F);
        return;
    }
    if (effect->lifetime == 1) {
        effect->lifetime = 6U;
        HSD_JObjReqAnimAll(eff_jobj, 60.0F);
    }
}

void efLib_Cb_SetJObjOffsetZ(EF_Effect* effect)
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

void efLib_Cb_SetRotY_FromFighterDir(EF_Effect* effect)
{
    HSD_JObj* eff_jobj;
    f64 half_pi;
    f32 rotate_y;

    eff_jobj = GET_JOBJ(effect->gobj);
    if (GET_FIGHTER(effect->parent_gobj)->facing_dir < 0.0F) {
        half_pi = -M_PI_2;
    } else {
        half_pi = M_PI_2;
    }
    rotate_y = half_pi;
    HSD_JObjSetRotationY(eff_jobj, rotate_y);
}

void efLib_Cb_SetRotYZ_FromFighter(EF_Effect* effect)
{
    HSD_JObj* jobj_1;
    f32 half_pi;
    Fighter* fighter;

    fighter = GET_FIGHTER(effect->parent_gobj);
    jobj_1 = GET_JOBJ(effect->gobj);
    half_pi = M_PI_2_F - fighter->mv.co.common.x4.x;
    if (fighter->facing_dir < 0.0F) {
        HSD_JObjSetRotationY(jobj_1, -M_PI_2_F);
        HSD_JObjSetRotationZ(jobj_1, half_pi);
    } else {
        HSD_JObjSetRotationY(jobj_1, M_PI_2_F);
        HSD_JObjSetRotationZ(jobj_1, -half_pi);
    }
}

void efLib_Cb_Fall_FromParamY(EF_Effect* effect)
{
    HSD_JObj* jobj_1;
    f32 rotate_y;
    f32 rotate_x;
    f32 translate_z;
    f32 translate_y;
    f32 translate_x;
    f32 translate_x_adjusted;

    jobj_1 = GET_JOBJ(effect->gobj);
    translate_x = HSD_JObjGetTranslationX(jobj_1);
    translate_y = HSD_JObjGetTranslationY(jobj_1);
    translate_z = HSD_JObjGetTranslationZ(jobj_1);
    rotate_x = HSD_JObjGetRotationX(jobj_1);
    rotate_y = HSD_JObjGetRotationY(jobj_1);
    effect->params.y -= 0.2f;
    translate_x_adjusted = translate_x + sinf(rotate_y);
    HSD_JObjSetTranslateX(jobj_1, translate_x_adjusted);
    HSD_JObjSetTranslateY(jobj_1, translate_y + effect->params.y);
    HSD_JObjSetTranslateZ(jobj_1, translate_z + cosf(rotate_y));
    HSD_JObjSetRotationX(jobj_1, 0.5F + rotate_x);
}

void efLib_Cb_SetOffset_FromParams(EF_Effect* effect)
{
    HSD_JObj* jobj_1;
    f32 translate_z;
    f32 translate_y;
    f32 translate_x;
    f32 translate_x_adjusted;

    jobj_1 = GET_JOBJ(effect->gobj);
    translate_x = HSD_JObjGetTranslationX(jobj_1);
    translate_y = HSD_JObjGetTranslationY(jobj_1);
    translate_z = HSD_JObjGetTranslationZ(jobj_1);
    effect->params.y -= 0.1f;
    translate_x_adjusted = translate_x + effect->params.x;
    HSD_JObjSetTranslateX(jobj_1, translate_x_adjusted);
    HSD_JObjSetTranslateY(jobj_1, translate_y + effect->params.y);
    HSD_JObjSetTranslateZ(jobj_1, translate_z + effect->params.z);
}

void efLib_Cb_LifetimeEndSpawn(EF_Effect* effect)
{
    if (effect->lifetime == 1) {
        hsd_8039EFAC(0, 0, 0x1AB, effect->attach_jobj);
        effect->update = NULL;
        effect->lifetime = 0x27U;
    }
}

void efLib_Cb_SetScaleRotY_FromFighter(EF_Effect* effect)
{
    f64 half_pi;
    Vec3 scale_1;
    Vec3 scale_2;
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
    HSD_JObjGetScale(jobj_1, &scale_1);
    HSD_JObjGetScale(jobj_2, &scale_2);
    scale_1.x *= scale_2.x;
    scale_1.y *= scale_2.y;
    scale_1.z *= scale_2.z;
    HSD_JObjSetScale(jobj_2, &scale_1);

    if (((Fighter*) user_data)->facing_dir < 0.0F) {
        half_pi = -M_PI_2;
    } else {
        half_pi = M_PI_2;
    }
    rotate_y = half_pi;
    HSD_JObjSetRotationY(jobj_2, rotate_y);
}

void efLib_Cb_SetRotYZ_FromParamZ_FighterDir(EF_Effect* effect)
{
    HSD_JObj* jobj_1;
    f32 rotate_z;

    jobj_1 = GET_JOBJ(effect->gobj);
    if ((GET_FIGHTER(effect->parent_gobj))->facing_dir < 0.0F) {
        HSD_JObjSetRotationY(jobj_1, -M_PI_2_F);
        rotate_z = effect->params.z;
        HSD_JObjSetRotationZ(jobj_1, rotate_z);
    } else {
        HSD_JObjSetRotationY(jobj_1, M_PI_2_F);
        rotate_z = -effect->params.z;
        HSD_JObjSetRotationZ(jobj_1, rotate_z);
    }
}

// Shows child jobj on motion 349, rotZ from floor slope.
void efLib_Cb_ftMr_SpecialLw(EF_Effect* effect)
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
    if ((fighter->cmd_vars[3] != 0U) &&
        (*(s32*) &fighter->mv.co.common.x4.z != 0))
    {
        f32 rotate_z = -atan2f(fighter->coll_data.floor.normal.x,
                               fighter->coll_data.floor.normal.y);
        HSD_JObjSetRotationZ(eff_jobj, rotate_z);
    } else {
        HSD_JObjSetRotationZ(eff_jobj, 0.0F);
    }
}

// Shows child jobj on motion 357, rotZ from floor slope.
void efLib_Cb_ftLg_SpecialLw(EF_Effect* effect)
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

    if ((fighter->cmd_vars[3] != 0U) &&
        (*(s32*) &fighter->mv.co.common.x4.z != 0))
    {
        f32 rotate_z = -atan2f(fighter->coll_data.floor.normal.x,
                               fighter->coll_data.floor.normal.y);
        HSD_JObjSetRotationZ(eff_jobj, rotate_z);
    } else {
        HSD_JObjSetRotationZ(eff_jobj, 0.0F);
    }
}

// Shows child jobj on motion 359, rotZ from floor slope.
void efLib_Cb_ftKp_SpecialHi(EF_Effect* effect)
{
    f32 rotate_z;
    Fighter* fighter;
    HSD_JObj* jobj_1;
    HSD_JObj* jobj_2;

    jobj_1 = GET_JOBJ(effect->gobj);
    jobj_2 = GET_JOBJ(effect->next->gobj);
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

// Bury effect, delegates to ftCo_800C0FCC.
void efLib_Cb_ftCo_Bury(EF_Effect* effect)
{
    ftCo_800C0FCC(effect->gobj, effect->parent_gobj);
}

// Sets TEV constant and register colors on a texture object.
// TEV is the GC GPU per-pixel color/alpha blending system.
// konst = constant color register, tev0 = computed color register.
// Color values packed as 0xRRGGBB.
void efLib_SetTevKonstColor(HSD_JObj* jobj, s32 count, u32 konst, u32 tev0)
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

// JObj animation queue!

// Effect JObjs are appended during efLib_Create, then HSD_JObjAnimAll is called
// on each at end-of-frame. Currently you have to cast to HSD_JObj** while keeping
// its type as EF_ParamEntry[0x10] for matching purposes... (compiler bases the
// efLib_ParamTable address off this array for some reason (???), so both must be
// the same type x_X ... if you can figure out a way around this pls fix ty).

/* 458EE0 */ EF_ParamEntry efLib_AnimQueue[0x10];

// Stores gobj effect params (gfx_id, alpha)
// Used by efLib_Cb_ApplyStoredAlpha to set TEV konst alpha.

/* 458F60 */ EF_ParamEntry efLib_ParamTable[0x8];

void efLib_SetParamAlpha(HSD_GObj* gobj, u8 alpha, f32 unused_1, f32 unused_2)
{
    s32 idx;

    // WHY
    EF_ParamEntry* base = efLib_AnimQueue + 0x10;

    for (idx = 0; idx < 8; idx++) {
        if (base[idx].gobj == gobj) {
            goto found;
        }
    }
    for (idx = 0; idx < 8; idx++) {
        if (base[idx].gobj == NULL) {
            goto found;
        }
    }
    return;

found:
    // WHY
    efLib_AnimQueue[idx + 0x10].gobj = gobj;
    efLib_AnimQueue[idx + 0x10].alpha = alpha;
}

void efLib_SetParamGfxId(HSD_GObj* gobj, s32 gfx_id)
{
    s32 idx;

    // WHY
    EF_ParamEntry* base = efLib_AnimQueue + 0x10;

    for (idx = 0; idx < 8; idx++) {
        if (base[idx].gobj == gobj) {
            goto found;
        }
    }
    for (idx = 0; idx < 8; idx++) {
        if (base[idx].gobj == NULL) {
            goto found;
        }
    }
    return;

found:
    // WHY
    efLib_AnimQueue[idx + 0x10].gobj = gobj;
    efLib_AnimQueue[idx + 0x10].gfx_id = gfx_id;
}

void efLib_Cb_ApplyStoredAlpha(EF_Effect* effect)
{
    HSD_DObj* dobj;
    HSD_JObj* jobj;
    HSD_MObj* mobj;
    HSD_TObj* tobj;
    HSD_JObj* hsd_obj;
    EF_ParamEntry* entry;
    PAD_STACK(8);

    hsd_obj = GET_JOBJ(effect->gobj);
    jobj = hsd_obj == NULL ? NULL : hsd_obj->child;
    dobj = HSD_JObjGetDObj(jobj);
    mobj = dobj != NULL ? dobj->mobj : NULL;
    tobj = HSD_MObjGetTObj(mobj);
    {
        s32 i;
        entry = &efLib_ParamTable[0];
        for (i = 0; i != 8; ++i) {
            if (entry->gobj == effect->parent_gobj) {
                if (efLib_ParamTable[i].gfx_id == 0x417) {
                    tobj = tobj->next;
                }
                tobj->tev->konst.a = (u8) efLib_ParamTable[i].alpha;
                if (efLib_ParamTable[i].gfx_id == 0x419) {
                    s32 j;
                    for (j = 0; j < 6; j++) {
                        jobj = jobj->next;
                        dobj = HSD_JObjGetDObj(jobj);
                        mobj = dobj != NULL ? dobj->mobj : NULL;
                        tobj = HSD_MObjGetTObj(mobj);
                        tobj->tev->konst.a = efLib_ParamTable[i].alpha;
                    }
                }
                break;
            }
            entry++;
        }
    }
}

void efLib_Cb_AccumOffset_FromParams(EF_Effect* effect)
{
    Vec3 translate;

    lb_8000B1CC(effect->attach_jobj, NULL, &translate);
    translate.x += effect->params.x;
    translate.y += effect->params.y;
    translate.z += effect->params.z;
    HSD_JObjSetTranslate(GET_JOBJ(effect->gobj), &translate);
}

EF_Effect* efLib_CreateGenerator_AppSRT_SetPos(int gfx_id, HSD_GObj* gobj, HSD_JObj* jobj, Vec3* vec)
{
    HSD_Generator* generator;
    EF_Effect* effect = efLib_Create(0, gobj);

    if (effect != NULL) {
        effect->update = efLib_Cb_AccumOffset_FromParams;
        effect->attach_jobj = jobj;
        effect->params = *vec;
        eflib_create_generator_add_appsrt(&generator, gfx_id, GET_JOBJ(effect->gobj));
    }
    return effect;
}
