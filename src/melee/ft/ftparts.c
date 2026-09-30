/**
 * @file ftparts.c
 * @brief Fighter model parts and joint management
 * @details Handles the dynamic linking of models, joints, and DObjs for Melee fighters.
 * Module prefix: ft
 */
#include "ftparts.h"

#include <placeholder.h>

#include "fighter.h"
#include "forward.h"
#include "ftdata.h"
#include "ftmaterial.h"
#include "inlines.h"
#include "types.h"
#include <dolphin/mtx.h>
#include <melee/lb/lbrefract.h>
#include <sysdolphin/baselib/class.h>
#include <sysdolphin/baselib/debug.h>
#include <sysdolphin/baselib/displayfunc.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/mtx.h>
#include <sysdolphin/baselib/perf.h>
#include <sysdolphin/baselib/pobj.h>
#include <sysdolphin/baselib/util.h>

/// .bss
struct ft_jobj_scale_t {
    Mtx mtx;
    u8 has_z_scale : 1;
    char unk_31[7];
} ft_jobj_scale;

HSD_JObjInfo ftJObj = { ftParts_JObjInfoInit };
HSD_JObjInfo ftIntpJObj = { ftParts_IntpJObjInfoInit };
HSD_PObjInfo ftPObj = { ftParts_PObjInfoInit };

/**
 * @brief Creates a position matrix for a fighter\'s JObj, taking global Z-scale into account.
 * @param jobj The JObj to make the matrix for
 * @param mtx The input transform matrix
 * @param rmtx The resulting transform matrix
 */
void ftParts_JObjMakePositionMtx(HSD_JObj* jobj, Mtx mtx, Mtx rmtx)
{
    Fighter* fighter = (Fighter*) HSD_GObj_804D7814->user_data;

    hsdJObj.make_pmtx(jobj, mtx, rmtx);

    if (fighter->x34_scale.z != 1.0F) {
        Mtx temp_mtx;
        float scale_z = HSD_JObjGetScaleZ(jobj);
        float scale_y = HSD_JObjGetScaleY(jobj);
        float scale_x = HSD_JObjGetScaleX(jobj);
        MTXScale(temp_mtx, 1.0F / scale_x, 1.0F / scale_y, 1.0F / scale_z);
        MTXConcat(rmtx, temp_mtx, ft_jobj_scale.mtx);
        HSD_MtxInverse(rmtx, temp_mtx);
        MTXConcat(ft_jobj_scale.mtx, temp_mtx, ft_jobj_scale.mtx);
        ft_jobj_scale.has_z_scale = true;
    } else {
        ft_jobj_scale.has_z_scale = false;
    }
}

/**
 * @brief Initializes the custom JObj class used by fighters.
 */
void ftParts_JObjInfoInit(void)
{
    hsdInitClassInfo(HSD_CLASS_INFO(&ftJObj), HSD_CLASS_INFO(&hsdJObj),
                     "fighter_class_library", "ft_jobj", sizeof(HSD_JObjInfo),
                     sizeof(HSD_JObj));
    HSD_JOBJ_INFO(&ftJObj)->make_pmtx = ftParts_JObjMakePositionMtx;
}

/**
 * @brief Changes a given JObj to use the fighter\'s custom JObj class.
 * @param jobj The JObj to update
 */
void ftParts_80073758(HSD_JObj* jobj)
{
    hsdChangeClass(jobj, &ftJObj);
}

/**
 * @brief Loads a joint into an interpolated JObj.
 * @param jobj The JObj to load into
 * @param joint The joint data
 * @param parent The parent JObj
 * @return 0 on success
 */
s32 ftParts_IntpJObjLoad(HSD_JObj* jobj, HSD_Joint* joint, HSD_JObj* parent)
{
    HSD_DObjDesc* dobjdesc = joint->u.dobjdesc;
    s32 ret;
    joint->u.dobjdesc = NULL;
    ret = hsdJObj.load(jobj, joint, parent);
    joint->u.dobjdesc = dobjdesc;
    return ret;
}

/**
 * @brief Initializes the custom interpolated JObj class used by fighters.
 */
void ftParts_IntpJObjInfoInit(void)
{
    hsdInitClassInfo(HSD_CLASS_INFO(&ftIntpJObj), HSD_CLASS_INFO(&hsdJObj),
                     "fighter_class_library", "ft_intp_jobj",
                     sizeof(HSD_JObjInfo), sizeof(HSD_JObj));
    HSD_JOBJ_INFO(&ftIntpJObj)->load = ftParts_IntpJObjLoad;
}

static inline PObjSetupFlag ftPartsGetSetupFlags(HSD_JObj* jobj,
                                                 u32 rendermode)
{
    PObjSetupFlag flags = SETUP_NONE;
    if (!(rendermode & RENDER_SHADOW)) {
        if (jobj->flags & JOBJ_LIGHTING) {
            flags |= SETUP_NORMAL;
        }
        if (_HSD_TObjGetCurrentByType(NULL, TEX_COORD_REFLECTION) != NULL) {
            flags |= SETUP_NORMAL | SETUP_REFLECTION;
        }
        if (_HSD_TObjGetCurrentByType(NULL, TEX_COORD_HILIGHT) != NULL) {
            flags |= SETUP_NORMAL | SETUP_HIGHLIGHT;
        }
    }
    return flags;
}

static inline void ftPartsSetupZScaleMtx(Mtx src, Mtx dst)
{
    Mtx scale_mtx;
    if (ft_jobj_scale.has_z_scale) {
        PSMTXConcat(ft_jobj_scale.mtx, src, scale_mtx);
        HSD_MtxInverseTranspose(scale_mtx, dst);
    } else {
        HSD_MtxInverseTranspose(src, dst);
    }
}

static inline void ftPartsSetupNrmMtx(HSD_JObj* jobj, Mtx mtx, GXPosNrmMtx id)
{
    if (jobj->flags & JOBJ_LIGHTING) {
        GXLoadNrmMtxImm(mtx, id);
        HSD_PerfCountMtxLoad();
    }
}

static inline void ftPartsSetupTexMtx(Mtx mtx, GXTexMtx id)
{
    GXLoadTexMtxImm(mtx, id, GX_MTX3x4);
    HSD_PerfCountMtxLoad();
}

/**
 * @brief Sets up a rigid matrix for a PObj during rendering.
 * @param pobj The polygon object
 * @param vmtx The view matrix
 * @param pmtx The position matrix
 * @param rendermode Rendering mode flags
 */
void ftPartsSetupRigidMtx(HSD_PObj* pobj, Mtx vmtx, Mtx pmtx, u32 rendermode)
{
    HSD_JObj* jobj;
    MtxPtr tmp;          // r29
    PObjSetupFlag flags; // r28

    Mtx mtx;        // sp54
    void* mark_obj; // sp50
    u32 mark;       // sp4C

    tmp = pmtx;
    jobj = HSD_JObjGetCurrent();
    HSD_PObjGetMtxMark(0, &mark_obj, &mark);
    if (mark_obj != jobj || mark != HSD_MTX_RIGID) {
        HSD_PObjSetMtxMark(0, jobj, HSD_MTX_RIGID);
        GXSetCurrentMtx(GX_PNMTX0);

        GXLoadPosMtxImm(tmp, GX_PNMTX0);
        HSD_PerfCountMtxLoad();
        flags = ftPartsGetSetupFlags(jobj, rendermode);
        if (flags & SETUP_NORMAL) {
            ftPartsSetupZScaleMtx(tmp, mtx);
            ftPartsSetupNrmMtx(jobj, mtx, GX_PNMTX0);

            if (flags & SETUP_NORMAL_PROJECTION) {
                ftPartsSetupTexMtx(mtx, GX_TEXMTX0);
            }
        }
    }
}

/**
 * @brief Sets up a shared vertex matrix for a PObj during rendering.
 * @param pobj The polygon object
 * @param vmtx The view matrix
 * @param pmtx The position matrix
 * @param rendermode Rendering mode flags
 */
void ftPartsSetupSharedVtxMtx(HSD_PObj* pobj, MtxPtr vmtx, MtxPtr pmtx,
                              u32 rendermode)
{
    HSD_JObj* jobj;
    PObjSetupFlag flags = SETUP_NONE; // r28

    Mtx mtx0;       // spE4
    Mtx mtx1;       // spB4
    Mtx tmp;        // sp84
    void* mark_obj; // sp80
    u32 mark;       // sp7C

    jobj = HSD_JObjGetCurrent();

    HSD_PObjGetMtxMark(0, &mark_obj, &mark);
    if (mark_obj != jobj && mark != HSD_MTX_RIGID) {
        flags |= SETUP_JOINT0;
    }
    HSD_PObjSetMtxMark(0, jobj, HSD_MTX_RIGID);

    HSD_PObjGetMtxMark(1, &mark_obj, &mark);
    if (mark_obj != pobj->u.jobj && mark != HSD_MTX_RIGID) {
        flags |= SETUP_JOINT1;
    }
    HSD_PObjSetMtxMark(1, pobj->u.jobj, HSD_MTX_RIGID);

    if (flags == SETUP_NONE) {
        return;
    }

    flags |= ftPartsGetSetupFlags(jobj, rendermode);

#ifdef MUST_MATCH
    if (flags | SETUP_NORMAL)
#endif
    {
        GXSetCurrentMtx(GX_PNMTX0);

        GXLoadPosMtxImm(pmtx, GX_PNMTX0);
        HSD_PerfCountMtxLoad();
        if (flags & SETUP_NORMAL) {
            ftPartsSetupZScaleMtx(pmtx, mtx0);
            ftPartsSetupNrmMtx(jobj, mtx0, GX_PNMTX0);

            if (flags & SETUP_NORMAL_PROJECTION) {
                ftPartsSetupTexMtx(mtx0, GX_TEXMTX0);
            }
        }
    }

#ifdef MUST_MATCH
    if (flags | SETUP_REFLECTION)
#endif
    {
        HSD_JObjSetupMatrix(pobj->u.jobj);
        PSMTXConcat(vmtx, pobj->u.jobj->mtx, tmp);

        GXLoadPosMtxImm(tmp, GX_PNMTX1);
        HSD_PerfCountMtxLoad();
        if (flags & SETUP_NORMAL) {
            ftPartsSetupZScaleMtx(tmp, mtx1);
            ftPartsSetupNrmMtx(jobj, mtx1, GX_PNMTX1);

            if (flags & SETUP_NORMAL_PROJECTION) {
                ftPartsSetupTexMtx(mtx1, GX_TEXMTX1);
            }
        }
    }
}

/**
 * @brief Sets up an envelope matrix for a skinning PObj during rendering.
 * @param pobj The polygon object
 * @param vmtx The view matrix
 * @param pmtx The position matrix
 * @param rendermode Rendering mode flags
 */
void ftPartsSetupEnvelopeMtx(HSD_PObj* pobj, MtxPtr vmtx, MtxPtr pmtx,
                             u32 rendermode)
{
    HSD_JObj* jobj;           // r23
    HSD_SList* envelope_list; // r22
    int i;                    // r21
    MtxPtr node_mtxp;         // r20
    Mtx spAC;                 // spAC
    MtxPtr mtxp;              // r19
    PObjSetupFlag flags;      // r17

    jobj = HSD_JObjGetCurrent();
    HSD_PObjClearMtxMark(NULL, HSD_MTX_ENVELOPE);
    flags = ftPartsGetSetupFlags(jobj, rendermode);
    node_mtxp = _HSD_mkEnvelopeModelNodeMtx(jobj, spAC);
    envelope_list = pobj->u.envelope_list;
    for (i = 0; i < 10 && envelope_list != NULL; i++) {
        Mtx mtx;                // sp7C
        Mtx tmp;                // sp4C
        HSD_Envelope* envelope; // r19
        u32 mtx_id;             // r18
        int envelope_count;     // r17

        envelope = envelope_list->data;
        mtx_id = HSD_Index2PosNrmMtx(i);
        envelope_count = 0;
        HSD_ASSERT(328, envelope);
        if (envelope->weight >= 1.0F) {
            HSD_JObjSetupMatrix(envelope->jobj);
            if (node_mtxp != NULL) {
                PSMTXConcat(envelope->jobj->mtx, envelope->jobj->envelopemtx,
                            mtx);
                mtxp = mtx;
            } else {
                mtxp = envelope->jobj->mtx;
            }
        } else {
            mtx[0][0] = mtx[0][1] = mtx[0][2] = mtx[0][3] = mtx[1][0] =
                mtx[1][1] = mtx[1][2] = mtx[1][3] = mtx[2][0] = mtx[2][1] =
                    mtx[2][2] = mtx[2][3] = 0.0F;
            while (envelope != NULL) {
                HSD_JObj* jp;
                HSD_ASSERT(348, envelope->jobj);
                jp = envelope->jobj;
                HSD_JObjSetupMatrix(jp);
                HSD_ASSERT(351, jp->mtx);
                HSD_ASSERT(352, jp->envelopemtx);
                PSMTXConcat(jp->mtx, jp->envelopemtx, tmp);
                HSD_MtxScaledAdd(tmp, mtx, mtx, envelope->weight);
                envelope = envelope->next;
                envelope_count++;
            }
            mtxp = mtx;
        }
        HSD_PerfCountEnvelopeBlending(envelope_count);
        if (node_mtxp != NULL) {
            PSMTXConcat(mtxp, node_mtxp, mtx);
        }
        PSMTXConcat(vmtx, mtxp, tmp);

        GXLoadPosMtxImm(tmp, mtx_id);
        HSD_PerfCountMtxLoad();
        if (flags & SETUP_NORMAL) {
            ftPartsSetupZScaleMtx(tmp, mtx);
            ftPartsSetupNrmMtx(jobj, mtx, mtx_id);

            if (flags & SETUP_NORMAL_PROJECTION) {
                ftPartsSetupTexMtx(mtx, HSD_Index2TexMtx(i));
            }
        }

        envelope_list = envelope_list->next;
    }
}

/**
 * @brief Sets up matrices for a PObj based on its specific skinning/envelope type.
 * @param pobj The polygon object
 * @param vmtx The view matrix
 * @param pmtx The position matrix
 * @param rendermode Rendering mode flags
 */
void ftParts_PObjSetupMtx(HSD_PObj* pobj, Mtx vmtx, Mtx pmtx, u32 rendermode)
{
    if (!ft_jobj_scale.has_z_scale) {
        hsdPObj.setup_mtx(pobj, vmtx, pmtx, rendermode);
        return;
    }
    switch (pobj_type(pobj)) {
    case POBJ_SKIN:
        if (pobj->u.jobj == NULL) {
            ftPartsSetupRigidMtx(pobj, vmtx, pmtx, rendermode);
        } else {
            ftPartsSetupSharedVtxMtx(pobj, vmtx, pmtx, rendermode);
        }
        break;
    case POBJ_SHAPEANIM:
        ftPartsSetupRigidMtx(pobj, vmtx, pmtx, rendermode);
        break;
    case POBJ_ENVELOPE:
        ftPartsSetupEnvelopeMtx(pobj, vmtx, pmtx, rendermode);
        break;
    }
}

/**
 * @brief Initializes the custom PObj class used by fighters.
 */
void ftParts_PObjInfoInit(void)
{
    hsdInitClassInfo(HSD_CLASS_INFO(&ftPObj), HSD_CLASS_INFO(&hsdPObj),
                     "fighter_class_library", "ft_pobj", sizeof(HSD_PObjInfo),
                     sizeof(HSD_PObj));
    HSD_POBJ_INFO(&ftPObj)->load = lbRefract_PObjLoad;
    HSD_POBJ_INFO(&ftPObj)->setup_mtx = ftParts_PObjSetupMtx;
}

/**
 * @brief Sets the default PObj class to the fighter\'s custom PObj class.
 */
void ftPartsPObjSetDefaultClass(void)
{
    HSD_PObjSetDefaultClass(&ftPObj);
}

/**
 * @brief Clears the default PObj class.
 */
void ftPartsPObjClearDefaultClass(void)
{
    HSD_PObjSetDefaultClass(NULL);
}

/**
 * @brief Traverses a JObj and updates the bone and dobj arrays.
 * @param fighter The fighter
 * @param bone The bone struct to populate
 * @param jobj The current JObj being processed
 * @param dobj_index Pointer to the running index of dobjs
 * @param tree_depth The current depth in the skeletal tree
 */
void ftParts_80074194(Fighter* fighter, FighterBone* bone, HSD_JObj* jobj,
                      int* dobj_index, u32 tree_depth)
{
    HSD_DObj* dobj = HSD_JObjGetDObj(jobj);
    u32 jobj_flags = HSD_JObjGetFlags(jobj);
    int dobj_count = 0;
    HSD_MObj* mobj;

    PAD_STACK(8);

    bone->joint = jobj;

    bone->x8.x0.flags_b1 = true;
    bone->x8.x0.flags_b7 = jobj_flags & JOBJ_LIGHTING ? true : false;
    bone->x8.x0.flags2_b0 = jobj_flags & JOBJ_TEXGEN ? true : false;
    bone->x8.x0.flags2_b1 = jobj_flags & JOBJ_SPECULAR ? true : false;
    bone->x8.x0.flags2_b2 = jobj_flags & JOBJ_UNK_B18 ? true : false;
    bone->x8.x0.flags2_b3 = jobj_flags & JOBJ_UNK_B20 ? true : false;
    bone->x8.x0.flags2_b4 = jobj_flags & JOBJ_UNK_B19 ? true : false;
    bone->xC_u.x0.xC = tree_depth;

    while (true) {
        if (dobj == NULL) {
            break;
        }
        if (*dobj_index >= 124) {
            HSD_ASSERTREPORT(466, 0,
                             "fighter parts model dobj num over! player %d\n",
                             fighter->player_idx);
        }
        fighter->dobj_list.data[*dobj_index] = dobj;
        mobj = dobj != NULL ? dobj->mobj : NULL;
        if (mobj != NULL) {
            hsdChangeClass(mobj, &ftMObj);
        }
        dobj = dobj != NULL ? dobj->next : NULL;
        dobj_count++;
        (*dobj_index)++;
    }
    if (dobj_count >= 128) {
        HSD_ASSERTREPORT(480, 0, "fighter dobj num over! player %d\n",
                         fighter->player_idx);
    }
    if (*dobj_index != 0) {
        bone->xC_u.x0.xD = *dobj_index - 1;
    } else {
        bone->xC_u.x0.xD = 0;
    }
    bone->x8.x0.flags2_b6 = dobj_count != 0 ? true : false;
}

/**
 * @brief Sets up the parts structure for a fighter gobj, building out the bone list.
 * @param fighter_obj The fighter\'s GObj
 */
void ftParts_SetupParts(Fighter_GObj* fighter_obj)
{
    HSD_JObj* jobj = GET_JOBJ(fighter_obj);
    Fighter* fp = GET_FIGHTER(fighter_obj);
    u32 part = 0;
    u32 tree_depth = 0;
    int dobj_count = 0;

    if (ftPartsTable[fp->kind]->parts_num > MAX_FT_PARTS) {
        HSD_ASSERTREPORT(503, 0, "fighter parts num over! player %d\n",
                         fp->player_idx);
    }

    while (jobj != NULL) {
        if (ftParts_8007506C(fp->kind, part) != 0) {
            fp->parts[part].joint = NULL;
            part++;
            continue;
        }

        ftParts_80074194(fp, &fp->parts[part], jobj, &dobj_count, tree_depth);
        part++;

        if (!(HSD_JObjGetFlags(jobj) & JOBJ_INSTANCE) &&
            HSD_JObjGetChild(jobj) != NULL)
        {
            // Descend the left side of the tree
            jobj = HSD_JObjGetChild(jobj);
            tree_depth++;
            continue;
        }

        if (HSD_JObjGetNext(jobj) != NULL) {
            // Visit bottom nodes from left to right
            jobj = HSD_JObjGetNext(jobj);
            continue;
        }

        while (true) {
            if (HSD_JObjGetParent(jobj) == NULL) {
                // Finished
                jobj = NULL;
                break;
            }

            // Go back up the tree until we can continue to the right
            if (HSD_JObjGetNext(HSD_JObjGetParent(jobj)) != NULL) {
                jobj = HSD_JObjGetNext(HSD_JObjGetParent(jobj));
                tree_depth--;
                break;
            }

            jobj = HSD_JObjGetParent(jobj);
            tree_depth--;
        }
    }

    fp->dobj_list.count = dobj_count;

    if (part != ftPartsTable[fp->kind]->parts_num) {
        HSD_ASSERTREPORT(546, 0, "fighter parts num not match! player %d\n",
                         fp->player_idx);
    }
}

/**
 * @brief Sets up the animation skeleton secondary jobj references for a fighter.
 * @param gobj The fighter\'s GObj
 */
void ftParts_8007462C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int i = 0;
    HSD_JObj* jobj = fp->x8AC_animSkeleton;

    while (jobj != NULL) {
        if (ftParts_8007506C(fp->kind, i) != 0) {
            fp->parts[i].x4_jobj2 = NULL;
            i++;
            continue;
        }

        fp->parts[i].x4_jobj2 = jobj;
        i++;
        if (!(HSD_JObjGetFlags(jobj) & JOBJ_INSTANCE) &&
            HSD_JObjGetChild(jobj) != NULL)
        {
            jobj = HSD_JObjGetChild(jobj);
            continue;
        }
        if (HSD_JObjGetNext(jobj) != NULL) {
            jobj = HSD_JObjGetNext(jobj);
            continue;
        }
        while (true) {
            if (HSD_JObjGetParent(jobj) == NULL) {
                jobj = NULL;
                break;
            }
            if (HSD_JObjGetNext(HSD_JObjGetParent(jobj)) != NULL) {
                jobj = HSD_JObjGetNext(HSD_JObjGetParent(jobj));
                break;
            }
            jobj = HSD_JObjGetParent(jobj);
        }
    }
    if (i != ftPartsTable[fp->kind]->parts_num) {
        HSD_ASSERTREPORT(593, 0, "fighter parts num not match! player %d\n",
                         fp->player_idx);
    }
}

/**
 * @brief Loads a joint into the custom IntpJObj class.
 * @param joint The joint to load
 * @return The allocated JObj
 */
HSD_JObj* ftParts_8007482C(HSD_Joint* joint)
{
    HSD_JObj* jobj;
    HSD_JObjSetDefaultClass(HSD_CLASS_INFO(&ftIntpJObj));
    jobj = HSD_JObjLoadJoint(joint);
    HSD_JObjSetDefaultClass(NULL);
    return jobj;
}

/**
 * @brief Initializes the visibility table for a fighter costume.
 * @param desc The parts description struct
 * @param vis The visibility tracking struct
 * @param costume_id The selected costume ID
 * @param arg3 Primary DObj list
 * @param arg4 Secondary DObj list
 */
void ftParts_8007487C(FtPartsDesc* desc, FtPartsVis* vis, u32 costume_id,
                      DObjList* arg3, DObjList* arg4)
{
    void*(*vis_table)[4];
    PAD_STACK(0x8);

    vis_table = desc->vis_table;
    vis->model_num = desc->model_num;
    if (vis->model_num > 11) {
        HSD_ASSERTREPORT(627, 0, "fighter parts model num over!\n");
    }

    vis->xC[0] =
        vis_table[costume_id][0] ? vis_table[costume_id][0] : vis_table[0][0];
    vis->xC[1] =
        vis_table[costume_id][1] ? vis_table[costume_id][1] : vis_table[0][1];
    vis->xC[2] =
        vis_table[costume_id][2] ? vis_table[costume_id][2] : vis_table[0][2];
    vis->xC[3] =
        vis_table[costume_id][3] ? vis_table[costume_id][3] : vis_table[0][3];
    vis->xC[4] = 0;
    vis->cleared[0] = true;
    vis->cleared[1] = true;
    vis->cleared[2] = true;
    vis->cleared[3] = true;
    vis->cleared[4] = true;
    ftParts_80074D7C(vis, 0, arg3);
    ftParts_80074D7C(vis, 1, arg3);
    ftParts_80074D7C(vis, 2, arg4);
    ftParts_80074D7C(vis, 3, arg3);
    ftParts_80074D7C(vis, 4, arg3);
}

/**
 * @brief Fully sets up the part visibility for a fighter model based on their costume.
 * @param gobj The fighter\'s GObj
 */
void ftParts_800749CC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int i;

    ftParts_8007487C(&fp->ft_data->x8->x0, &fp->x5AC, fp->costume_id,
                     &fp->dobj_list, &fp->x203C);
    for (i = 0; i < fp->x5AC.model_num; i++) {
        fp->x5F4_arr[i].prev = -1;
    }
    ftParts_80074ACC(gobj);
}

/**
 * @brief Sets the pending part model index for a specific model group.
 * @param gobj The fighter GObj
 * @param model_idx The model group index
 * @param val The pending value to set
 */
void ftParts_80074A4C(Fighter_GObj* gobj, int model_idx, int val)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x5F4_arr[model_idx].prev = val;
    fp->x221D_b2 = true;
}

/**
 * @brief Gets the pending part model index for a specific model group.
 * @param gobj The fighter GObj
 * @param model_idx The model group index
 * @return The pending index
 */
int ftParts_80074A74(Fighter_GObj* gobj, int model_idx)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->x5F4_arr[model_idx].prev;
}

/**
 * @brief Commits the pending part model indices into the active indices.
 * @param gobj The fighter GObj
 */
void ftParts_80074A8C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int i;

    for (i = 0; i < fp->x5AC.model_num; i++) {
        fp->x5F4_arr[i].idx = fp->x5F4_arr[i].prev;
    }
    fp->x221D_b2 = false;
}

/**
 * @brief Clears the active model indices, effectively hiding model groups.
 * @param gobj The fighter GObj
 */
void ftParts_80074ACC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int i;

    for (i = 0; i < fp->x5AC.model_num; i++) {
        fp->x5F4_arr[i].idx = -1;
    }
    fp->x221D_b2 = false;
}

/**
 * @brief Sets a part model index and immediately updates DObj visibility flags.
 * @param gobj The fighter GObj
 * @param model_idx The model group index
 * @param val The model index to set
 */
void ftParts_80074B0C(Fighter_GObj* gobj, int model_idx, int val)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (val != fp->x5F4_arr[model_idx].idx) {
        fp->x5F4_arr[model_idx].idx = val;
        fp->x221D_b2 = true;
        ftParts_80074D7C(&fp->x5AC, 0, &fp->dobj_list);
    }
}

/**
 * @brief Updates DObj visibility for a given visibility index, hiding parts that don\'t match the active state.
 * @param fp The fighter
 * @param vis The visibility struct
 * @param idx The visibility lookup index
 * @param dobj_list The list of DObjs to apply visibility to
 */
void ftParts_80074B6C(Fighter* fp, FtPartsVis* vis, int idx,
                      DObjList* dobj_list)
{
    FtPartsVisLookup* lookup = vis->xC[idx]; // r4
    if (lookup != NULL && !vis->cleared[idx]) {
        int i; // r26
        for (i = 0; i < vis->model_num; i++) {
            int r25 = (int) fp->x5F4_arr[i].idx; // r25
            int j;                               // r24
            for (j = 0; j < lookup[i].x0; j++) {
                TempS* r27 = &lookup[i].x4[j]; // r27
                u8* r0 = r27->x4;              // r0
                if (j == r25) {
                    int k; // r20
                    for (k = 0; k < r27->x0; k++) {
                        HSD_DObjClearFlags(dobj_list->data[r0[k]], 1);
                    }
                } else {
                    int k; // r20
                    for (k = 0; k < r27->x0; k++) {
                        HSD_DObjSetFlags(dobj_list->data[r0[k]], 1);
                    }
                }
            }
            vis->cleared[idx] = 1;
        }
    }
}

/**
 * @brief Clears (hides) all DObjs associated with a given visibility lookup index.
 * @param vis The visibility struct
 * @param idx The visibility lookup index
 * @param dobj_list The list of DObjs
 */
void ftParts_80074CA0(FtPartsVis* vis, int idx, DObjList* dobj_list)
{
    FtPartsVisLookup* lookup = vis->xC[idx]; // r0
    if (lookup != NULL && !vis->cleared[idx]) {
        int i; // r24
        for (i = 0; i < vis->model_num; i++) {
            int j; // r23
            for (j = 0; j < lookup[i].x0; j++) {
                TempS* r26; // r26
                int k;      // r22
                u8* r29;    // r29
                r26 = &lookup[i].x4[j];
                r29 = r26->x4;
                for (k = 0; k < r26->x0; k++) {
                    HSD_DObjClearFlags(dobj_list->data[r29[k]], 1);
                }
            }
        }
        vis->cleared[idx] = true;
    }
}

/**
 * @brief Sets (shows) all DObjs associated with a given visibility lookup index.
 * @param vis The visibility struct
 * @param idx The visibility lookup index
 * @param dobj_list The list of DObjs
 */
void ftParts_80074D7C(FtPartsVis* vis, int idx, DObjList* dobj_list)
{
    FtPartsVisLookup* lookup = vis->xC[idx]; // r0
    if (lookup != NULL && vis->cleared[idx]) {
        int i; // r24
        for (i = 0; i < vis->model_num; i++) {
            int j; // r23
            for (j = 0; j < lookup[i].x0; j++) {
                TempS* r26; // r26
                int k;      // r22
                u8* r29;    // r29
                r26 = &lookup[i].x4[j];
                r29 = r26->x4;
                for (k = 0; k < r26->x0; k++) {
                    HSD_DObjSetFlags(dobj_list->data[r29[k]], 1);
                }
            }
        }
        vis->cleared[idx] = false;
    }
}

/**
 * @brief Allocates the parts and dobj_list arrays for a newly created fighter.
 * @param fp The fighter
 */
void ftParts_80074E58(Fighter* fp)
{
    int i;

    fp->parts = HSD_ObjAlloc(&fighter_parts_alloc_data);
    fp->dobj_list.data = HSD_ObjAlloc(&fighter_dobj_list_alloc_data);

    for (i = 0; i < ftPartsTable[fp->kind]->parts_num; i++) {
        fp->parts[i].x8.flags8 = 0;
        fp->parts[i].xC_u.flagsC = 0;
    }

    fp->parts[0].x8.x0.flags_b3 = true;
    fp->parts[ftParts_GetBoneIndex(fp, FtPart_TransN)].x8.x0.flags_b3 = true;
    fp->parts[ftParts_GetBoneIndex(fp, FtPart_XRotN)].x8.x0.flags_b3 = true;
    fp->parts[ftParts_GetBoneIndex(fp, FtPart_YRotN)].x8.x0.flags_b3 = true;
    fp->parts[ftParts_GetBoneIndex(fp, FtPart_HipN)].x8.x0.flags_b3 = true;
    fp->parts[ftParts_GetBoneIndex(fp, FtPart_TransN2)].x8.x0.flags_b3 = true;
    fp->parts[ftParts_GetBoneIndex(fp, FtPart_TransN)].x8.x0.flags_b4 = true;
    fp->parts[ftParts_GetBoneIndex(fp, 0x35)].x8.x0.flags_b4 = true;
}

/**
 * @brief Gets the actual internal bone index given a canonical Fighter_Part identifier.
 * @param fp The fighter
 * @param part The canonical part (e.g. FtPart_TransN)
 * @return The mapped bone index
 */
Fighter_Part ftParts_GetBoneIndex(Fighter* fp, Fighter_Part part)
{
    return ftPartsTable[fp->kind]->part_to_joint[part];
}

/**
 * @brief Remaps a joint index from one fighter\'s parts table to another.
 * @param to_table_idx Target table index
 * @param from_table_idx Source table index
 * @param joint_idx Joint index to remap
 * @return The mapped joint index, or FTPART_INVALID
 */
int ftPartsRemap(size_t to_table_idx, size_t from_table_idx, size_t joint_idx)
{
    FighterPartsTable* from_table = ftPartsTable[from_table_idx];
    if (joint_idx < from_table->parts_num) {
        size_t part_idx = from_table->joint_to_part[joint_idx];
        if (part_idx != FTPART_INVALID) {
            return ftPartsTable[to_table_idx]->part_to_joint[part_idx];
        }
    }
    return FTPART_INVALID;
}

/**
 * @brief Checks if a specific part is excluded or disabled for a fighter kind.
 * @param ftkind The fighter kind (e.g. Fox, Mario)
 * @param part The part index
 * @return A bitmask if the part is disabled, 0 otherwise
 */
u32 ftParts_8007506C(enum FighterKind ftkind, int part)
{
    Fighter_804D6540_x0_t* part_desc;
    int i;
    Fighter_804D6540_t* ft_data;

    ft_data = Fighter_804D6540[ftkind];
    if (ft_data != NULL && ft_data->x4 != 0) {
        part_desc = ft_data->x0;
        for (i = 0; i < ft_data->x4; i++, part_desc++) {
            if (part_desc->x0 == part) {
                return 1 << i;
            }
        }
    }
    return 0;
}

/**
 * @brief Applies model events and visibility updates for a fighter.
 * @param fp The fighter
 * @param arg1 Event type index
 * @param arg2 True to show, false to hide
 */
void ftParts_800750C8(Fighter* fp, enum_t arg1, bool arg2)
{
    if (arg1 == 2) {
        if (arg2) {
            ftParts_80074B6C(fp, &fp->x5AC, 2, &fp->x203C);
        } else {
            ftParts_80074D7C(&fp->x5AC, 2, &fp->x203C);
        }
        if (ftData_UnkIntBoolFunc0.model_events[fp->kind] != NULL) {
            ftData_UnkIntBoolFunc0.model_events[fp->kind](fp, 2, arg2);
        }
        if (arg2) {
            ftParts_80074B6C(fp, &fp->x5AC, 3, &fp->dobj_list);
        } else {
            ftParts_80074D7C(&fp->x5AC, 3, &fp->dobj_list);
        }
        if (ftData_UnkIntBoolFunc0.model_events[fp->kind] != NULL) {
            ftData_UnkIntBoolFunc0.model_events[fp->kind](fp, 3, arg2);
        }
    } else {
        if (arg2) {
            ftParts_80074B6C(fp, &fp->x5AC, arg1, &fp->dobj_list);
        } else {
            ftParts_80074D7C(&fp->x5AC, arg1, &fp->dobj_list);
        }
        if (ftData_UnkIntBoolFunc0.model_events[fp->kind] != NULL) {
            ftData_UnkIntBoolFunc0.model_events[fp->kind](fp, arg1, arg2);
        }
    }
}

/**
 * @brief Finds the n-th TObj within a DObjList.
 * @param arg0 The list of DObjs
 * @param n The zero-based index of the TObj to find
 * @return Pointer to the TObj
 */
HSD_TObj* ftParts_80075240(DObjList* arg0, int n)
{
    int tobj_i;
    int i;

    HSD_MObj* mobj;
    HSD_TObj* tobj;
    HSD_DObj* dobj;

    PAD_STACK(4);

    tobj_i = 0;

    for (i = 0; i < (int) arg0->count; i++) {
        dobj = arg0->data[i];
        if (dobj != NULL) {
            mobj = dobj != NULL ? dobj->mobj : NULL;
            if (mobj != NULL) {
                tobj = HSD_MObjGetTObj(mobj);
                while (true) {
                    if (tobj == NULL) {
                        break;
                    }
                    if (tobj_i == n) {
                        return tobj;
                    }
                    tobj_i++;
                    tobj = HSD_TObjGetNext(tobj);
                }
            }
        }
    }
    HSD_ASSERTREPORT(948, 0, "can't find tobj!\n");
}

/**
 * Inserts a new jobj relative to a root jobj, with the location specified by
 * the first argument.
 */
void ftParts_80075304(u8 type, HSD_JObj* root, HSD_JObj* new_jobj)
{
    switch (type) {
    case 0:
        /**
         * If type is 0, the new jobj is inserted as a child of the root,
         * and children of the root become children of the new jobj.
         */
        {
            HSD_JObj* child;
            if (root == NULL) {
                child = NULL;
            } else {
                child = root->child;
            }
            new_jobj->child = child;
            new_jobj->parent = root;
            root->child = new_jobj;
            if (child != NULL) {
                child->parent = new_jobj;
            }
            break;
        }
    case 1:
        /**
         * If type is 1, the new jobj is inserted as a child of the root,
         * alongside any existing children of the root.
         */
        {
            HSD_JObj* child;
            if (root == NULL) {
                child = NULL;
            } else {
                child = root->child;
            }
            new_jobj->next = child;
            new_jobj->parent = root;
            root->child = new_jobj;
            break;
        }
    case 2:
        /**
         * If type is 2, the new jobj is inserted as a sibling of the root.
         * Existing siblings of the root become children of the new jobj.
         */
        {
            HSD_JObj* next;
            if (root == NULL) {
                next = NULL;
            } else {
                next = root->next;
            }
            new_jobj->child = next;
            new_jobj->parent = root->parent;
            root->next = new_jobj;
            break;
        }
    case 3:
        /**
         * If type is 3, the new jobj is inserted as a sibling of the root,
         * alongside any existing siblings.
         */
        {
            HSD_JObj* next;
            if (root == NULL) {
                next = NULL;
            } else {
                next = root->next;
            }
            new_jobj->next = next;
            new_jobj->parent = root->parent;
            root->next = new_jobj;
            break;
        }
    }
}

/**
 * @brief Dynamically attaches a joint (like an item or weapon) to a fighter bone.
 * @param arg0 The fighter
 * @param arg1 Info detailing where and how to attach
 * @param arg2 The joint to attach
 */
void ftParts_800753D4(Fighter* fighter, struct Fighter_804D6540_x0_t* attach_info,
                      HSD_Joint* joint)
{
    HSD_Joint* curr_joint;
    HSD_Joint joint_copy;

    HSD_JObj* anim_jobj;
    HSD_JObj* main_jobj;
    int i;
    u32 tree_depth;
    int dobj_index;

    curr_joint = joint;
    if (attach_info->x3 != 0xFF) {
        s32 depth = 0;
        for (i = 0; i < attach_info->x3; i++) {
            ftAnim_GetNextJointInTree(&curr_joint, &depth);
        }
    }
    joint_copy = *curr_joint;
    joint_copy.next = 0;
    joint_copy.child = 0;

    main_jobj = ftParts_8007482C(&joint_copy);
    anim_jobj = ftParts_8007482C(&joint_copy);

    ftParts_80075304(attach_info->x2, fighter->parts[attach_info->x1].joint, main_jobj);
    ftParts_80075304(attach_info->x2, fighter->parts[attach_info->x1].x4_jobj2, anim_jobj);

    tree_depth = fighter->parts[attach_info->x1].xC_u.x0.xC;
    if (attach_info->x2 == 0 || attach_info->x2 == 1) {
        tree_depth++;
    }
    dobj_index = 0;
    ftParts_80074194(fighter, &fighter->parts[attach_info->x0], main_jobj, &dobj_index,
                     tree_depth);

    fighter->parts[attach_info->x0].x4_jobj2 = anim_jobj;
    fighter->parts[attach_info->x0].x8.x0.flags_b2 = true;
}

/**
 * @brief Removes a dynamically attached joint from a fighter bone.
 * @param fp The fighter
 * @param arg1 Info detailing what to remove
 */
void ftParts_800755E8(Fighter* fp, struct Fighter_804D6540_x0_t* attach_info)
{
    FighterBone* bone = &fp->parts[attach_info->x0];
    HSD_JObjRemove(bone->joint);
    HSD_JObjRemove(bone->x4_jobj2);
    bone->joint = NULL;
    bone->x4_jobj2 = NULL;
    bone->x8.x0.flags_b1 = false;
    bone->x8.x0.flags_b2 = false;
}

/**
 * @brief Gathers DObjs from a dynamically attached JObj hierarchy.
 * @param arg0 Unused fighter gobj
 * @param jobj The root JObj of the attachment
 * @param arg2 List to populate
 */
void ftParts_80075650(Fighter_GObj* fighter_gobj, HSD_JObj* jobj, DObjList* dobj_list)
{
    s32 dobj_index;
    HSD_DObj* dobj;

    HSD_DObj* next_dobj;
    HSD_MObj* mobj;

    PAD_STACK(8);

    dobj_index = 0;
    while (jobj != NULL) {
        dobj = HSD_JObjGetDObj(jobj);
        while (true) {
            if (dobj == NULL) {
                break;
            }
            if (dobj_index >= 0x20) {
                HSD_ASSERTREPORT(1063, 0,
                                 "fighter parts model dobj num over!\n");
            }
            dobj_list->data[dobj_index] = dobj;
            mobj = dobj->mobj;
            if (mobj != NULL) {
                hsdChangeClass(mobj, &ftMObj);
            }
            if (dobj != NULL) {
                next_dobj = dobj->next;
            } else {
                next_dobj = NULL;
            }
            dobj = next_dobj;
            dobj_index += 1;
        }
        if (!(HSD_JObjGetFlags(jobj) & JOBJ_INSTANCE) &&
            HSD_JObjGetChild(jobj) != NULL)
        {
            jobj = HSD_JObjGetChild(jobj);
        } else {
            if (HSD_JObjGetNext(jobj) != NULL) {
                jobj = HSD_JObjGetNext(jobj);
            } else {
                while (true) {
                    if (HSD_JObjGetParent(jobj) == NULL) {
                        jobj = NULL;
                        break;
                    }
                    if (HSD_JObjGetNext(HSD_JObjGetParent(jobj)) != NULL) {
                        jobj = HSD_JObjGetNext(HSD_JObjGetParent(jobj));
                        break;
                    }
                    jobj = HSD_JObjGetParent(jobj);
                }
            }
        }
    }
}

/**
 * @brief Sets the rotation of a JObj and clears its quaternion flag.
 * @param jobj The JObj
 * @param quat Quaternion rotation
 */
void ftParts_JObjSetRotation(HSD_JObj* jobj, Vec4* quat)
{
    HSD_JObjSetRotation(jobj, quat);
    HSD_JObjClearFlags(jobj, JOBJ_USE_QUATERNION);
}

/**
 * @brief Sets the X rotation for a specific fighter part.
 * @param fp The fighter
 * @param part_idx The bone/part index
 * @param rotate_x Rotation angle in radians
 */
void ftPartSetRotX(Fighter* fp, int part_idx, f32 rotate_x)
{
    HSD_JObj* jobj = fp->parts[part_idx].joint;
    if (HSD_JObjGetFlags(jobj) & JOBJ_USE_QUATERNION) {
        HSD_JObj* jobj2 = fp->parts[part_idx].x4_jobj2;
        if (HSD_JObjGetFlags(jobj2) & JOBJ_USE_QUATERNION) {
            HSD_ASSERTREPORT(1120, 0, "cant set fighter rot x!\n");
        }
        HSD_JObjSetRotationX(jobj2, rotate_x);
    } else {
        HSD_JObjSetRotationX(jobj, rotate_x);
    }
}

/**
 * @brief Sets the Y rotation for a specific fighter part.
 * @param fp The fighter
 * @param part_idx The bone/part index
 * @param rotate_y Rotation angle in radians
 */
void ftPartSetRotY(Fighter* fp, int part_idx, f32 rotate_y)
{
    HSD_JObj* jobj = fp->parts[part_idx].joint;
    if (HSD_JObjGetFlags(jobj) & JOBJ_USE_QUATERNION) {
        HSD_JObj* jobj2 = fp->parts[part_idx].x4_jobj2;
        if (HSD_JObjGetFlags(jobj2) & JOBJ_USE_QUATERNION) {
            HSD_ASSERTREPORT(1139, 0, "cant set fighter rot y!\n");
        }
        HSD_JObjSetRotationY(jobj2, rotate_y);
    } else {
        HSD_JObjSetRotationY(jobj, rotate_y);
    }
}

/**
 * @brief Sets the Z rotation for a specific fighter part.
 * @param arg0 The fighter
 * @param part_idx The bone/part index
 * @param rotate_z Rotation angle in radians
 */
void ftPartSetRotZ(Fighter* arg0, int part_idx, f32 rotate_z)
{
    HSD_JObj* jobj;
    HSD_JObj* jobj2;

    jobj = arg0->parts[part_idx].joint;
    if (HSD_JObjGetFlags(jobj) & JOBJ_USE_QUATERNION) {
        jobj2 = arg0->parts[part_idx].x4_jobj2;
        if (HSD_JObjGetFlags(jobj2) & JOBJ_USE_QUATERNION) {
            HSD_ASSERTREPORT(1158, 0, "cant set fighter rot z!\n");
        }
        HSD_JObjSetRotationZ(jobj2, rotate_z);
    } else {
        HSD_JObjSetRotationZ(jobj, rotate_z);
    }
}

/**
 * @brief Gets the X rotation of a specific fighter part.
 * @param fp The fighter
 * @param part_idx The bone/part index
 * @return Rotation angle in radians
 */
f32 ftPartGetRotX(Fighter* fp, int part_idx)
{
    HSD_JObj* jobj = fp->parts[part_idx].joint;
    if (HSD_JObjGetFlags(jobj) & JOBJ_USE_QUATERNION) {
        HSD_JObj* jobj = fp->parts[part_idx].x4_jobj2;
        if (HSD_JObjGetFlags(jobj) & JOBJ_USE_QUATERNION) {
            HSD_ASSERTREPORT(1177, 0, "cant get fighter rot x!\n");
        }
        return HSD_JObjGetRotationX(jobj);
    }
    return HSD_JObjGetRotationX(jobj);
}

/**
 * @brief Gets the Z rotation of a specific fighter part.
 * @note Actually returns RotationY from the internal structure.
 * @param fp The fighter
 * @param part_idx The bone/part index
 * @return Rotation angle in radians
 */
f32 ftPartGetRotZ(Fighter* fp, int part_idx)
{
    HSD_JObj* jobj = fp->parts[part_idx].joint;
    if (HSD_JObjGetFlags(jobj) & JOBJ_USE_QUATERNION) {
        HSD_JObj* jobj = fp->parts[part_idx].x4_jobj2;
        if (HSD_JObjGetFlags(jobj) & JOBJ_USE_QUATERNION) {
            HSD_ASSERTREPORT(1196, 0, "cant get fighter rot y!\n");
        }
        return HSD_JObjGetRotationY(jobj);
    }
    return HSD_JObjGetRotationY(jobj);
}

static char* ftParts_803C0BEC = "cant get fighter rot z!\n";
