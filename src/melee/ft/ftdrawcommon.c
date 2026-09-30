/**
 * @file ftdrawcommon.c
 * @brief Common fighter rendering and GX display list routines.
 * @details Implements the primary GX drawing callbacks for fighters, including standard model
 * rendering, collision bubble overlay rendering, water reflection rendering (e.g. Fountain of Dreams),
 * camera shake matrix calculations, and shadow pass material switching.
 * Module prefix: ft (Fighter)
 */

#include "ftdrawcommon.h"

#include <Runtime/platform.h>

#include <placeholder.h>

#include "ft_0C88.h"
#include "ftafterimage.h"
#include "ftcommon.h"
#include "ftdata.h"
#include "ftlib.h"
#include "ftparts.h"
#include "inlines.h"
#include "kinds/ftCommon/ftCo_09F4.h"
#include "kinds/ftCommon/ftCo_0A01.h"
#include <dolphin/mtx.h>
#include <melee/cm/camera.h>
#include <melee/lb/lb_00F9.h>
#include <melee/lb/lb_0146.h>
#include <melee/lb/lbcollision.h>
#include <melee/lb/lbgx.h>
#include <sysdolphin/baselib/cobj.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/state.h>

/// RGBA debug wireframe color for ground light item pickup volume (white, 50% opacity)
static U8Vec4 ftDrawCommon_804D3A88 = { 0xFF, 0xFF, 0xFF, 0x80 };

/// RGBA debug wireframe color for aerial light item pickup volume (light blue, 50% opacity)
static U8Vec4 ftDrawCommon_804D3A8C = { 0x80, 0x80, 0xFF, 0x80 };

/// RGBA debug wireframe color for ground heavy item pickup volume (gray, 50% opacity)
static U8Vec4 ftDrawCommon_804D3A90 = { 0x80, 0x80, 0x80, 0x80 };

/**
 * @brief Sets the translation component of a 3x4 transform matrix from two 3D vectors.
 * @param[out] mtx Target 3x4 matrix whose translation column (column 3) is updated
 * @param[in] v First translation vector (shake offset)
 * @param[in] v2 Second translation vector (zero vector offset)
 */
static inline void mtx_thing_2(MtxPtr mtx, Vec3* v, Vec3* v2)
{
    mtx[0][3] = v->x + v2->x;
    mtx[1][3] = v->y + v2->y;
    mtx[2][3] = v->z + v2->z;
}

/**
 * @brief Inlined shake offset matrix calculation for fighter rendering.
 * @details Queries fighter shake offset via ftLib_GetShakeOffset and, if active,
 * creates a translation matrix concatenated with the active camera's view matrix.
 * @param gobj Pointer to fighter HSD_GObj
 * @param[out] shake_offset Temporary Vec3 buffer to receive shake offset from ftLib
 * @param[in] zero_vec Zero-initialized reference Vec3
 * @param[out] trans_mtx Temporary 3x4 matrix for translation
 * @param[out] out_mtx Output 3x4 matrix for concatenated view matrix
 * @return Pointer to out_mtx if shaking; NULL otherwise
 */
static inline MtxPtr ftDrawCommon_8008051C_inline(HSD_GObj* gobj, Vec3* shake_offset,
                                                  Vec3* zero_vec, Mtx trans_mtx, Mtx out_mtx)

{
    zero_vec->x = zero_vec->y = zero_vec->z = 0.0F;
    shake_offset->x = shake_offset->y = shake_offset->z = 0.0F;
    if (ftLib_GetShakeOffset(gobj, shake_offset)) {
        HSD_CObj* current = HSD_CObjGetCurrent();
        MtxPtr mtx = current->view_mtx;
        PSMTXIdentity(trans_mtx);
        mtx_thing_2(trans_mtx, shake_offset, zero_vec);
        PSMTXConcat(mtx, trans_mtx, out_mtx);
        return out_mtx;
    }
    return NULL;
}

/**
 * @brief Computes a camera view matrix offset by active screen/hit shake translation.
 * @details Queries active shake translation for the fighter via ftLib_GetShakeOffset
 * (e.g. hitlag rumble, smash charge vibration, grab mashing). If shaking, concatenates
 * the shake translation with the active camera's view matrix and returns the result.
 * @param gobj Pointer to fighter HSD_GObj
 * @param[out] out_mtx Output matrix buffer to store concatenated view matrix
 * @return Pointer to out_mtx if shaking; NULL if no shake offset
 */
MtxPtr ftDrawCommon_8008051C(HSD_GObj* gobj, MtxPtr out_mtx)
{
    u8 unused0[0x4];
    Vec3 shake_offset;
    Vec3 zero_vec;
    Mtx trans_mtx;
    u8 unused2[0x8];

    zero_vec.x = zero_vec.y = zero_vec.z = 0.0F;
    shake_offset.x = shake_offset.y = shake_offset.z = 0.0F;

    if (ftLib_GetShakeOffset(gobj, &shake_offset)) {
        HSD_CObj* current = HSD_CObjGetCurrent();
        MtxPtr mtx = current->view_mtx;
        PSMTXIdentity(trans_mtx);

        mtx_thing_2(trans_mtx, &shake_offset, &zero_vec);

        PSMTXConcat(mtx, trans_mtx, out_mtx);
        return out_mtx;
    }
    return NULL;
}

/// Debug primary wireframe color for dynamic bone rendering (white)
static const GXColor ftDrawCommon_804D836C = { 0xFF, 0xFF, 0xFF, 0xFE };

/// Debug secondary joint color for dynamic bone rendering (white)
static const GXColor ftDrawCommon_804D8370 = { 0xFF, 0xFF, 0xFF, 0xFF };

/**
 * @brief Main debug collision overlay and fighter model rendering routine.
 * @details Evaluates debug visualization flags and renders collision geometry:
 * - b6: Hitboxes (fighter->x914), hurtbox capsules (normal, intangible, or invincible),
 *   shield bubble (fighter->shield_hit), reflector bubble (fighter->reflect_hit),
 *   and absorber bubble (fighter->absorb_hit).
 * - b5: Item collision / hurt capsules (fighter->x1670) and dynamic bone sets (fighter->dynamic_bone_sets).
 * - b3: Environmental Collision Box (ECB) points via ftCo_800B395C.
 * - b4: Damage / special collision (fighter->dmg.x1930.x0).
 * - b2: Item pickup ranges (ground light, ground heavy, air light).
 * - b1: Thrown item / fighter hitbox (fighter->x1064_thrownHitbox).
 * - b0: Additional collision volumes (fighter->x1614).
 * If any debug shapes were drawn, invalidates GX pipeline state via HSD_StateInvalidate(-1).
 *
 * If model display flag b7 is enabled:
 * - Applies costume / metal shader part configurations via ftParts_800750C8:
 *   - Metal Mario / Cloaking Device / Super Star: disable part 0, enable part 2.
 *   - Normal costume textures: disable part 2, enable part 0.
 * - Applies camera shake offset matrix via ftDrawCommon_8008051C_inline.
 * - Invokes HSD_JObjDispAll to traverse joint hierarchy and render meshes.
 * - Calls character-specific matrix callback ftData_UnkMtxFunc0[fighter->kind] (e.g. Peach dress, Ice Climbers).
 * - Renders held items / accessories (fighter->x20A0_accessory).
 *
 * @param gobj Pointer to fighter HSD_GObj
 * @param render_flags GX display flags passed to HSD_GObj_80390EB8
 * @param draw_model Flag indicating whether to render the 3D model geometry
 */
void ftDrawCommon_800805C8(HSD_GObj* gobj, s32 render_flags, bool draw_model)
{
    GXColor primary_color;
    GXColor secondary_color;
    int i;

    s32 hit_status;
    Fighter* fighter;
    u32 vulnerability_level;
    u32 do_invalidate;
    Mtx shake_mtx;
    Mtx trans_mtx;
    MtxPtr mtx;
    u8 _pad[12];
    Vec3 shake_offset;
    Vec3 zero_vec;
    PAD_STACK(12);

    fighter = GET_FIGHTER(gobj);
    do_invalidate = false;

    /* Debug overlay visualization checks (Develop mode / Debug display) */
    if (fighter->x21FC_flag.x0.b6 != 0) {
        /* Render active offensive hitboxes */
        for (i = 0; i < ARRAY_SIZE(fighter->x914); i++) {
            if (lbColl_80009F54(&fighter->x914[i], render_flags, fighter->x34_scale.y))
            {
                do_invalidate = true;
            }
        }

        /* Render defensive hurtboxes based on intangibility / invincibility status */
        if (fighter->x221D_b6) {
            for (i = 0; i < (unsigned) fighter->hurt_capsules_len; i++) {
                if (lbColl_8000A584(&fighter->hurt_capsules[i].capsule, 1,
                                    render_flags, ftCommon_8007F804(fighter),
                                    fighter->cur_pos.z) != 0)
                {
                    do_invalidate = true;
                }
            }
        } else {
            hit_status = fighter->x1988;
            if (hit_status == 0 && fighter->x198C == 0) {
                /* Normal vulnerable hurtbox (yellow) */
                for (i = 0; i < (unsigned) fighter->hurt_capsules_len; i++) {
                    if (lbColl_8000A244(&fighter->hurt_capsules[i].capsule,
                                        render_flags, ftCommon_8007F804(fighter),
                                        fighter->cur_pos.z))
                    {
                        do_invalidate = true;
                    }
                }
            } else {
                /* Intangible (1, blue) vs. Invincible (2, green) */
                if (fighter->x198C == 2 || hit_status == 2) {
                    vulnerability_level = 2;
                } else {
                    vulnerability_level = 1;
                }
                for (i = 0; i < (unsigned) fighter->hurt_capsules_len; i++) {
                    if (lbColl_8000A584(
                            &fighter->hurt_capsules[i].capsule, vulnerability_level, render_flags,
                            ftCommon_8007F804(fighter), fighter->cur_pos.z))
                    {
                        do_invalidate = true;
                    }
                }
            }
        }

        /* Reflector collision bubble (e.g. Fox/Falco shine) */
        if (fighter->reflecting &&
            lbColl_8000A95C(&fighter->reflect_hit, render_flags,
                            ftCommon_8007F804(fighter), fighter->cur_pos.z))
        {
            do_invalidate = true;
        }

        /* Absorber collision bubble (e.g. Ness PSI Magnet, G&W Oil Panic bucket) */
        if (fighter->x2218_b6 &&
            lbColl_8000AB2C(&fighter->absorb_hit, render_flags,
                            ftCommon_8007F804(fighter), fighter->cur_pos.z))
        {
            do_invalidate = true;
        }

        /* Shield bubble */
        if (fighter->x221B.x221B_b0 &&
            lbColl_8000A78C(&fighter->shield_hit, render_flags,
                            ftCommon_8007F804(fighter), fighter->cur_pos.z))
        {
            do_invalidate = true;
        }
    }

    /* Dynamic bone sets and item collision */
    if (fighter->x21FC_flag.x0.b5 != 0) {
        for (i = 0; i < (unsigned) fighter->x166C; i++) {
            if (lbColl_8000A460(&fighter->x1670[i], render_flags)) {
                do_invalidate = true;
            }
        }
        for (i = 0; i < (unsigned) fighter->dynamics_num; i++) {
            primary_color = ftDrawCommon_804D836C;
            secondary_color = ftDrawCommon_804D8370;
            if (lb_800117F4(&fighter->dynamic_bone_sets[i].dyn_desc, &primary_color,
                            &secondary_color, fighter->dynamic_bone_sets[i].bone_id,
                            render_flags))
            {
                do_invalidate = true;
            }
        }
    }

    /* Environmental Collision Box (ECB) diamond visualization */
    if (fighter->x21FC_flag.x0.b3 && (ftCo_800B395C(gobj, render_flags) != 0)) {
        do_invalidate = true;
    }

    /* Damage collision / special collision volume */
    if (fighter->x21FC_flag.x0.b4 && fighter->x2223_b5 &&
        lb_80014770(&fighter->dmg.x1930.x0, render_flags))
    {
        do_invalidate = true;
    }

    /* Item pickup bounding volumes */
    if (fighter->x21FC_flag.x0.b2 != 0) {
        itPickup* it_pickup = &fighter->x294_itPickup;
        if (fighter->ground_or_air == 0) {
            /* Ground light item pickup range */
            if (lbGx_8001E2F8(&it_pickup->gr_light_offset, &fighter->cur_pos,
                              &ftDrawCommon_804D3A88, render_flags,
                              fighter->facing_dir))
            {
                do_invalidate = true;
            }
            /* Ground heavy item pickup range */
            if (lbGx_8001E2F8(&it_pickup->gr_heavy_offset, &fighter->cur_pos,
                              &ftDrawCommon_804D3A90, render_flags,
                              fighter->facing_dir))
            {
                do_invalidate = true;
            }
        } else if (lbGx_8001E2F8(&it_pickup->air_light_offset,
                                 &fighter->cur_pos, &ftDrawCommon_804D3A8C,
                                 render_flags, fighter->facing_dir))
        {
            /* Aerial item pickup range */
            do_invalidate = true;
        }
    }

    /* Thrown item / character hitbox */
    if (fighter->x21FC_flag.x0.b1 && !fighter->x2227_b2 &&
        lbColl_8000A044(&fighter->x1064_thrownHitbox, render_flags,
                        fighter->x34_scale.y))
    {
        do_invalidate = true;
    }

    /* Additional collision volumes */
    if (fighter->x21FC_flag.x0.b0 && !fighter->x2229_b4) {
        for (i = 0; i < ARRAY_SIZE(fighter->x1614); i++) {
            if (lbColl_8000A1A8(&fighter->x1614[i], render_flags,
                                fighter->x34_scale.y))
            {
                do_invalidate = true;
            }
        }
    }

    /* Invalidate cached GX state if debug geometry was rendered */
    if (do_invalidate) {
        HSD_StateInvalidate(-1);
    }

    /* Model display flag b7: skip model rendering if disabled */
    if (!fighter->x21FC_flag.x0.b7) {
        return;
    }

    if (!fighter->invisible && !fighter->x221E_b5 && draw_model) {
        /* Configure material parts: disable shadow (1) and magnifying glass (4) */
        ftParts_800750C8(fighter, 1, 0);
        ftParts_800750C8(fighter, 4, 0);
        if (fighter->is_metal || fighter->x2226_b5 || fighter->x2227_b3) {
            /* Metal shader: disable diffuse texture (part 0), enable metal reflection (part 2) */
            ftParts_800750C8(fighter, 0, 0);
            ftParts_800750C8(fighter, 2, 1);
        } else {
            /* Normal costume texture: disable metal (part 2), enable diffuse texture (part 0) */
            ftParts_800750C8(fighter, 2, 0);
            ftParts_800750C8(fighter, 0, 1);
        }
        ftCo_8009F5AC(fighter);
        fighter->x2223_b2 = false;
        fighter->x2227_b7 = true;
        fighter->x2228_b0 = false;

        /* Get camera view matrix with hit shake offset */
        mtx = ftDrawCommon_8008051C_inline(gobj, &shake_offset, &zero_vec, trans_mtx, shake_mtx);

        /* Render 3D joint hierarchy */
        HSD_JObjDispAll(GET_JOBJ(gobj), mtx, HSD_GObj_80390EB8(render_flags), 0);

        /* Character-specific post-render matrix callback (e.g. Peach dress, Ice Climbers) */
        if (ftData_UnkMtxFunc0[fighter->kind] != NULL) {
            ftData_UnkMtxFunc0[fighter->kind](gobj, render_flags, mtx);
        }
        ftCo_800C8AF0(fighter);
        ftCo_8009F7F8(fighter);
    }

    /* Render held items / accessories (e.g. Fox blaster, Peach turnip, Captain Falcon holster) */
    if (fighter->x20A0_accessory != NULL) {
        HSD_JObjDispAll(fighter->x20A0_accessory, NULL,
                        HSD_GObj_80390EB8(render_flags), 0);
    }
    ftCo_800C2600(gobj, render_flags);
}

/**
 * @brief Alternate rendering callback for silhouettes, shadows, and reflections.
 * @details Configures material parts pass 1 and renders the fighter hierarchy with
 * alternate material passes. Used for stage reflection rendering (e.g. Fountain of Dreams)
 * and silhouette / offscreen magnifying glass passes.
 * @param gobj Pointer to fighter HSD_GObj
 * @param flag_index GX display flags passed to HSD_GObj_80390EB8
 */
void ftDrawCommon_80080C28(HSD_GObj* gobj, intptr_t flag_index)
{
    Mtx shake_mtx;
    Mtx trans_mtx;
    f32* unused;
    f32 temp_f31;
    f32 temp_f0;
    Fighter* fighter;
    MtxPtr vmtx;
    HSD_JObj* jobj;
    Vec3 shake_offset;
    Vec3 zero_vec;
    PAD_STACK(4);

    fighter = GET_FIGHTER(gobj);
    if (fighter->x21FC_flag.x0.b7 != 0) {
        if (!fighter->invisible && !fighter->x221E_b5 && !fighter->x2226_b5) {
            ftCo_8009F5AC(fighter);
            /* Configure material parts for silhouette / reflection pass 1 */
            if (fighter->x5AC.xC[1] != NULL) {
                ftParts_800750C8(fighter, 0, 0);
                ftParts_800750C8(fighter, 2, 0);
                ftParts_800750C8(fighter, 4, 0);
                ftParts_800750C8(fighter, 1, 1);
            }

            fighter->x2223_b2 = 0;
            fighter->x2223_b3 = 0;
            fighter->x2227_b7 = 0;
            fighter->x2228_b0 = 1;
            vmtx = ftDrawCommon_8008051C_inline(gobj, &shake_offset, &zero_vec, trans_mtx, shake_mtx);

            jobj = GET_JOBJ(gobj);
            HSD_JObjDispAll(jobj, vmtx, HSD_GObj_80390EB8(flag_index), 0);
            if (ftData_UnkMtxFunc0[fighter->kind] != NULL) {
                ftData_UnkMtxFunc0[fighter->kind](gobj, flag_index, vmtx);
            }
            ftCo_800C8AF0(fighter);
            ftCo_8009F7F8(fighter);
        }

        /* Render held items / accessories */
        if (fighter->x20A0_accessory != NULL) {
            HSD_JObjDispAll(fighter->x20A0_accessory, NULL,
                            HSD_GObj_80390EB8(flag_index), 0);
        }
    }
}

/**
 * @brief Helper inline for magnifying glass pass 0 (background / base layer).
 * @details Enables material part 4 (magnifying glass highlight pass), sets
 * fp->x2223_b2 = 1, and renders the fighter hierarchy.
 * @param gobj Pointer to fighter HSD_GObj
 * @param flag_index GX display pass flags
 */
static inline void ftDrawCommon_80080E18_inline0(HSD_GObj* gobj,
                                                 int flag_index)
{
    Fighter* fp = GET_FIGHTER(gobj);
    MtxPtr matrix;
    u32 gx_flags;
    HSD_JObj* jobj;

    Mtx shake_mtx;

    if (fp->x21FC_flag.x0.b7 && !fp->invisible && !fp->x221E_b5 &&
        !fp->x2226_b5)
    {
        /* Enable material part 4 (magnifying glass pass) */
        ftParts_800750C8(fp, 0, 0);
        ftParts_800750C8(fp, 1, 0);
        ftParts_800750C8(fp, 2, 0);
        ftParts_800750C8(fp, 4, 1);
        fp->x2223_b2 = 1;
        fp->x2223_b3 = 0;

        jobj = GET_JOBJ(gobj);
        gx_flags = HSD_GObj_80390EB8(flag_index);
        matrix = ftDrawCommon_8008051C(gobj, shake_mtx);
        HSD_JObjDispAll(jobj, matrix, gx_flags, 0);
    }
}

/**
 * @brief Helper inline for magnifying glass pass 1 (foreground / overlay layer).
 * @details Enables material part 4 with secondary layer flag (fp->x2223_b3 = 1),
 * and renders the fighter hierarchy for magnifying glass overlay.
 * @param gobj Pointer to fighter HSD_GObj
 * @param flag_index GX display pass flags
 */
static inline void ftDrawCommon_80080E18_inline1(HSD_GObj* gobj,
                                                 int flag_index)
{
    Fighter* fp;
    MtxPtr matrix;
    u32 gx_flags;
    HSD_JObj* jobj;

    Mtx shake_mtx;

    fp = GET_FIGHTER(gobj);

    if (fp->x21FC_flag.x0.b7 && !fp->invisible && !fp->x221E_b5 &&
        !fp->x2226_b5)
    {
        /* Enable material part 4 secondary layer */
        ftParts_800750C8(fp, 0, 0);
        ftParts_800750C8(fp, 1, 0);
        ftParts_800750C8(fp, 2, 0);
        ftParts_800750C8(fp, 4, 1);
        fp->x2223_b2 = 1;
        fp->x2223_b3 = 1;

        jobj = gobj->hsd_obj;
        gx_flags = HSD_GObj_80390EB8(flag_index);
        matrix = ftDrawCommon_8008051C(gobj, shake_mtx);
        HSD_JObjDispAll(jobj, matrix, gx_flags, 0);
    }
}

/**
 * @brief Computes offscreen magnifying glass HUD position in camera space.
 * @details Transforms the fighter's position using the inverse camera viewing matrix
 * from Camera_800310B8(), updating fp->cur_pos and the root JObj translation.
 * @param gobj Pointer to fighter HSD_GObj
 * @param old Pointer to fighter instance data containing target frame coordinates
 */
static inline void ftDrawCommon_80080E18_inline2(HSD_GObj* gobj, Fighter* old)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_JObj* jobj = gobj->hsd_obj;
    Vec3* pos;

    MtxPtr matrix = HSD_CObjGetInvViewingMtxPtr(Camera_800310B8());
    /// @todo this seems to be using the wrong common attributes
    PSMTXMultVec(matrix, (Vec3*) &old->mv.co.walk.fast_anim_frame,
                 &fp->cur_pos);
    pos = &fp->cur_pos;

    HSD_JObjSetTranslate(jobj, pos);
}

/**
 * @brief Primary per-frame GX rendering callback for all fighters.
 * @details Registered on fighter GObjs during creation via GObj_SetupGXLink (priority 5).
 * Updates viewport visibility via ftLib_UpdateScreenVisibility and branches on camera mode:
 * - Camera mode 1: Multi-pass rendering for offscreen magnifying glass viewports.
 * - Camera mode 0: Standard rendering via ftDrawCommon_800805C8.
 * @param gobj Pointer to fighter HSD_GObj
 * @param arg1 GX display flags passed to HSD_GObj_80390EB8
 */
void ftDrawCommon_80080E18(HSD_GObj* gobj, intptr_t arg1)
{
    Fighter* fp = gobj->user_data;

    /* Skip rendering if fighter is sleeping or fully offscreen */
    if (!fp->is_sleeping && ftLib_UpdateScreenVisibility(gobj)) {
        switch (Camera_80031060()) {
        case 1:
            /* Offscreen magnifying glass HUD bubble camera mode */
            if (fp->x2220_b7) {
                ftDrawCommon_80080E18_inline2(gobj, fp);
            }
            if (fp->x5AC.xC[4] != NULL) {
                ftDrawCommon_80080E18_inline0(gobj, arg1);
                ftDrawCommon_800805C8(gobj, arg1, true);
                ftDrawCommon_80080E18_inline1(gobj, arg1);
            }
            break;
        case 0:
            /* Standard gameplay camera mode */
            fp->x2223_b3 = false;
            ftDrawCommon_800805C8(gobj, arg1,
                                  fp->x5AC.xC[4] != NULL ? false : true);
        }
    }
}

/**
 * @brief Restores the standard rendering callback (ftDrawCommon_80080E18) on all active fighters.
 * @details Iterates through the active fighter GObj list (HSD_GOBJ_PLINK_FIGHTER) and resets
 * render_cb to ftDrawCommon_80080E18. Called after stage reflection rendering passes.
 */
void ftDrawCommon_80081118(void)
{
    HSD_GObj* gobj = HSD_GObjPLinkHead[HSD_GOBJ_PLINK_FIGHTER];
    while (gobj != NULL) {
        gobj->render_cb = &ftDrawCommon_80080E18;
        gobj = gobj->next;
    }
}

/**
 * @brief Sets the reflection / silhouette rendering callback (ftDrawCommon_80080C28) on all active fighters.
 * @details Iterates through HSD_GOBJ_PLINK_FIGHTER and sets render_cb to ftDrawCommon_80080C28.
 * Used by stages with dynamic planar reflections such as Fountain of Dreams (grIzumi).
 */
void ftDrawCommon_80081140(void)
{
    HSD_GObj* gobj = HSD_GObjPLinkHead[HSD_GOBJ_PLINK_FIGHTER];
    while (gobj != NULL) {
        gobj->render_cb = ftDrawCommon_80080C28;
        gobj = gobj->next;
    }
}

/**
 * @brief Configures material parts for standard texture rendering across all active fighters.
 * @details Sets material shader parts to texture pass 0 for normal gameplay rendering.
 */
void ftDrawCommon_80081168(void)
{
    Fighter_GObj* cur;
    for (cur = HSD_GObjPLinkHead[HSD_GOBJ_PLINK_FIGHTER]; cur != NULL;
         cur = cur->next)
    {
        Fighter* fighter = GET_FIGHTER(cur);
        PAD_STACK(4 * 2);
        if (fighter->x5AC.xC[1] != NULL) {
            ftParts_800750C8(fighter, 1, 0);
            ftParts_800750C8(fighter, 2, 0);
            ftParts_800750C8(fighter, 4, 0);
            ftParts_800750C8(fighter, 0, 1);
        }
    }
}

/**
 * @brief Configures material parts for silhouette / alternate rendering across all active fighters.
 * @details Sets material shader parts to pass 1 for planar shadow or silhouette rendering.
 */
void ftDrawCommon_80081200(void)
{
    Fighter_GObj* cur;
    for (cur = HSD_GObjPLinkHead[HSD_GOBJ_PLINK_FIGHTER]; cur != NULL;
         cur = cur->next)
    {
        Fighter* fighter = GET_FIGHTER(cur);
        PAD_STACK(4 * 2);
        if (fighter->x5AC.xC[1] != NULL) {
            ftParts_800750C8(fighter, 0, 0);
            ftParts_800750C8(fighter, 2, 0);
            ftParts_800750C8(fighter, 4, 0);
            ftParts_800750C8(fighter, 1, 1);
        }
    }
}
