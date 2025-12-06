#include "ftparts.h"

#include "fighter.h"
#include "ftdata.h"
#include "ftmaterial.h"

#include "ftparts.static.h"

#include "inlines.h"
#include "types.h"

#include "ft/forward.h"

#include <dolphin/mtx.h>
#include <dolphin/os/OSError.h>
#include <sysdolphin/baselib/class.h>
#include <sysdolphin/baselib/debug.h>
#include <sysdolphin/baselib/displayfunc.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/mtx.h>
#include <sysdolphin/baselib/perf.h>
#include <sysdolphin/baselib/pobj.h>
#include <sysdolphin/baselib/util.h>
#include <melee/lb/lbrefract.h>

#define MAX_FT_PARTS 140

#define JOBJ_NEXT(jobj) ((jobj) == NULL ? NULL : (jobj)->next)
#define JOBJ_PARENT(jobj) ((jobj) == NULL ? NULL : (jobj)->parent)
#define JOBJ_CHILD(jobj) ((jobj) == NULL ? NULL : (jobj)->child)

HSD_JObjInfo ftJObj = { ftParts_JObjInfoInit };
HSD_JObjInfo ftIntpJObj = { ftParts_IntpJObjInfoInit };
HSD_PObjInfo ftPObj = { ftParts_PObjInfoInit };

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

void ftParts_JObjInfoInit(void)
{
    hsdInitClassInfo(HSD_CLASS_INFO(&ftJObj), HSD_CLASS_INFO(&hsdJObj),
                     "fighter_class_library", "ft_jobj", sizeof(HSD_JObjInfo),
                     sizeof(HSD_JObj));
    HSD_JOBJ_INFO(&ftJObj)->make_pmtx = ftParts_JObjMakePositionMtx;
}

void ftParts_80073758(HSD_JObj* jobj)
{
    hsdChangeClass(jobj, &ftJObj);
}

s32 ftParts_IntpJObjLoad(HSD_JObj* jobj, HSD_Joint* joint, HSD_JObj* parent)
{
    HSD_DObjDesc* dobjdesc = joint->u.dobjdesc;
    s32 ret;
    joint->u.dobjdesc = NULL;
    ret = hsdJObj.load(jobj, joint, parent);
    joint->u.dobjdesc = dobjdesc;
    return ret;
}

void ftParts_IntpJObjInfoInit(void)
{
    hsdInitClassInfo(HSD_CLASS_INFO(&ftIntpJObj), HSD_CLASS_INFO(&hsdJObj),
                     "fighter_class_library", "ft_intp_jobj",
                     sizeof(HSD_JObjInfo), sizeof(HSD_JObj));
    HSD_JOBJ_INFO(&ftIntpJObj)->load = ftParts_IntpJObjLoad;
}

void ftParts_80073830(HSD_PObj* pobj, Mtx vmtx, Mtx pmtx, u32 rendermode)
{
    HSD_JObj* jobj;
    MtxPtr temp_r29;
    int var_r28;

    Mtx sp54;
    HSD_JObj* sp50;
    u32 sp4C;
    u8 _[4];
    Mtx sp18;

    temp_r29 = pmtx;
    jobj = HSD_JObjGetCurrent();
    HSD_PObjGetMtxMark(0, (void**) &sp50, &sp4C);
    if (sp50 != jobj || sp4C != 1) {
        HSD_PObjSetMtxMark(0, jobj, 1);
        GXSetCurrentMtx(GX_PNMTX0);
        GXLoadPosMtxImm(temp_r29, GX_PNMTX0);
        var_r28 = 0;
        HSD_PerfCurrentStat.nb_mtx_load++;
        if (!(rendermode & RENDER_SHADOW)) {
            if (jobj->flags & JOBJ_LIGHTING) {
                var_r28 |= 1;
            }
            if (_HSD_TObjGetCurrentByType(NULL, TEX_COORD_REFLECTION) != NULL)
            {
                var_r28 |= 1 | 2;
            }
            if (_HSD_TObjGetCurrentByType(NULL, TEX_COORD_HILIGHT) != NULL) {
                var_r28 |= 1 | 4;
            }
        }
        if (var_r28 & 1) {
            if (ft_jobj_scale.has_z_scale) {
                PSMTXConcat(ft_jobj_scale.mtx, temp_r29, sp18);
                HSD_MtxInverseTranspose(sp18, sp54);
            } else {
                HSD_MtxInverseTranspose(temp_r29, sp54);
            }
            if (jobj->flags & JOBJ_LIGHTING) {
                GXLoadNrmMtxImm(sp54, GX_PNMTX0);
                HSD_PerfCurrentStat.nb_mtx_load++;
            }
            if (var_r28 & (2 | 4)) {
                GXLoadTexMtxImm(sp54, GX_TEXMTX0, GX_MTX3x4);
                HSD_PerfCurrentStat.nb_mtx_load++;
            }
        }
    }
}

void ftParts_800739B8(HSD_PObj* pobj, MtxPtr vmtx, MtxPtr pmtx, u32 rendermode)
{
    HSD_JObj* jobj;
    int var_r28;

    Mtx spE4;
    Mtx spB4;
    Mtx sp84;
    HSD_JObj* sp80;
    u32 sp7C;
    u8 _[4];
    Mtx sp48;
    Mtx sp18;

    var_r28 = 0;
    jobj = HSD_JObjGetCurrent();
    HSD_PObjGetMtxMark(0, (void**) &sp80, &sp7C);
    if (sp80 != jobj && sp7C != 1) {
        var_r28 |= 1;
    }
    HSD_PObjSetMtxMark(0, jobj, 1);
    HSD_PObjGetMtxMark(1, (void**) &sp80, &sp7C);
    if (sp80 != pobj->u.jobj && sp7C != 1) {
        var_r28 |= 2;
    }
    HSD_PObjSetMtxMark(1, pobj->u.jobj, 1);
    if (var_r28 != 0) {
        {
            u32 flags = 0;
            if (!(rendermode & RENDER_SHADOW)) {
                if (jobj->flags & JOBJ_LIGHTING) {
                    flags |= 1;
                }
                if (_HSD_TObjGetCurrentByType(NULL, TEX_COORD_REFLECTION) !=
                    NULL)
                {
                    flags |= 1 | 2;
                }
                if (_HSD_TObjGetCurrentByType(NULL, TEX_COORD_HILIGHT) != NULL)
                {
                    flags |= 1 | 4;
                }
            }
            var_r28 |= flags;
        }

        if (var_r28 | 1) {
            GXSetCurrentMtx(GX_PNMTX0);
            GXLoadPosMtxImm(pmtx, GX_PNMTX0);
            HSD_PerfCurrentStat.nb_mtx_load =
                HSD_PerfCurrentStat.nb_mtx_load + 1;
            if (var_r28 & 1) {
                if (ft_jobj_scale.has_z_scale) {
                    PSMTXConcat(ft_jobj_scale.mtx, pmtx, sp48);
                    HSD_MtxInverseTranspose(sp48, spE4);
                } else {
                    HSD_MtxInverseTranspose(pmtx, spE4);
                }
                if (jobj->flags & JOBJ_LIGHTING) {
                    GXLoadNrmMtxImm(spE4, 0);
                    HSD_PerfCurrentStat.nb_mtx_load++;
                }
                if (var_r28 & (2 | 4)) {
                    GXLoadTexMtxImm(spE4, GX_TEXMTX0, GX_MTX3x4);
                    HSD_PerfCurrentStat.nb_mtx_load++;
                }
            }
        }
        if (var_r28 | 2) {
            HSD_JObjSetupMatrix(pobj->u.jobj);
            PSMTXConcat(vmtx, pobj->u.jobj->mtx, sp84);
            GXLoadPosMtxImm(sp84, 3);
            HSD_PerfCurrentStat.nb_mtx_load++;
            if (var_r28 & 1) {
                if (ft_jobj_scale.has_z_scale) {
                    PSMTXConcat(ft_jobj_scale.mtx, sp84, sp18);
                    HSD_MtxInverseTranspose(sp18, spB4);
                } else {
                    HSD_MtxInverseTranspose(sp84, spB4);
                }
                if (jobj->flags & JOBJ_LIGHTING) {
                    GXLoadNrmMtxImm(spB4, GX_PNMTX1);
                    HSD_PerfCurrentStat.nb_mtx_load++;
                }
                if (var_r28 & (2 | 4)) {
                    GXLoadTexMtxImm(spB4, GX_TEXMTX1, GX_MTX3x4);
                    HSD_PerfCurrentStat.nb_mtx_load++;
                }
            }
        }
    }
}

void ftParts_80073CA8(HSD_PObj* pobj, MtxPtr vmtx, MtxPtr pmtx, u32 rendermode)
{
    HSD_JObj* temp_r23;
    HSD_SList* var_r22;
    int var_r21;
    MtxPtr temp_r20;
    HSD_Envelope* envelope;
    MtxPtr var_r19_2;
    s32 temp_r18;
    s32 var_r17;
    int var_r17_2;

    HSD_JObj* jp;

    Mtx spAC;
    Mtx sp7C;
    Mtx sp4C;
    u8 _[4];
    Mtx sp18;

    temp_r23 = HSD_JObjGetCurrent();
    HSD_PObjClearMtxMark(NULL, HSD_MTX_ENVELOPE);
    var_r17 = 0;
    if (!(rendermode & 0x4000000)) {
        if (temp_r23->flags & 0x80) {
            var_r17 |= 1;
        }
        if (_HSD_TObjGetCurrentByType(NULL, TEX_COORD_REFLECTION) != NULL) {
            var_r17 |= 3;
        }
        if (_HSD_TObjGetCurrentByType(NULL, TEX_COORD_HILIGHT) != NULL) {
            var_r17 |= 5;
        }
    }
    temp_r20 = _HSD_mkEnvelopeModelNodeMtx(temp_r23, spAC);
    var_r22 = pobj->u.envelope_list;
    var_r21 = 0;
    while (var_r21 < 10 && var_r22 != NULL) {
        envelope = var_r22->data;
        temp_r18 = HSD_Index2PosNrmMtx(var_r21);
        var_r17_2 = 0;
        HSD_ASSERT(328, envelope);
        if (envelope->weight >= 1.0F) {
            HSD_JObjSetupMatrix(envelope->jobj);
            if (temp_r20 != NULL) {
                PSMTXConcat(envelope->jobj->mtx, envelope->jobj->envelopemtx,
                            sp7C);
                var_r19_2 = sp7C;
            } else {
                var_r19_2 = envelope->jobj->mtx;
            }
        } else {
            sp7C[2][3] = 0.0f;
            sp7C[2][2] = 0.0f;
            sp7C[2][1] = 0.0f;
            sp7C[2][0] = 0.0f;
            sp7C[1][3] = 0.0f;
            sp7C[1][2] = 0.0f;
            sp7C[1][1] = 0.0f;
            sp7C[1][0] = 0.0f;
            sp7C[0][3] = 0.0f;
            sp7C[0][2] = 0.0f;
            sp7C[0][1] = 0.0f;
            sp7C[0][0] = 0.0f;
            while (envelope != NULL) {
                HSD_ASSERT(348, envelope->jobj);
                jp = envelope->jobj;
                HSD_JObjSetupMatrix(jp);
                HSD_ASSERT(351, jp->mtx);
                HSD_ASSERT(352, jp->envelopemtx);
                PSMTXConcat(jp->mtx, jp->envelopemtx, sp4C);
                HSD_MtxScaledAdd(sp4C, sp7C, sp7C, envelope->weight);
                envelope = envelope->next;
                var_r17_2++;
            }
            var_r19_2 = sp7C;
        }
        HSD_PerfCountEnvelopeBlending(var_r17_2);
        if (temp_r20 != NULL) {
            PSMTXConcat(var_r19_2, temp_r20, sp7C);
        }
        PSMTXConcat(vmtx, var_r19_2, sp4C);
        GXLoadPosMtxImm(sp4C, temp_r18);
        HSD_PerfCurrentStat.nb_mtx_load += 1;
        if (var_r17 & 1) {
            if (ft_jobj_scale.has_z_scale) {
                PSMTXConcat(ft_jobj_scale.mtx, sp4C, sp18);
                HSD_MtxInverseTranspose(sp18, sp7C);
            } else {
                HSD_MtxInverseTranspose(sp4C, sp7C);
            }
            if (temp_r23->flags & 0x80) {
                GXLoadNrmMtxImm(sp7C, (u32) temp_r18);
                HSD_PerfCurrentStat.nb_mtx_load += 1;
            }
            if (var_r17 & 6) {
                GXLoadTexMtxImm(sp7C, HSD_Index2TexMtx((u32) var_r21),
                                GX_MTX3x4);
                HSD_PerfCurrentStat.nb_mtx_load += 1;
            }
        }
        var_r22 = var_r22->next;
        var_r21++;
    }
}

void ftParts_PObjSetupMtx(HSD_PObj* pobj, Mtx vmtx, Mtx pmtx, u32 rendermode)
{
    if (!ft_jobj_scale.has_z_scale) {
        hsdPObj.setup_mtx(pobj, vmtx, pmtx, rendermode);
        return;
    }
    switch (pobj->flags & 0x3000) {
    case 0x0:
        if (pobj->u.jobj == NULL) {
            ftParts_80073830(pobj, vmtx, pmtx, rendermode);
        } else {
            ftParts_800739B8(pobj, vmtx, pmtx, rendermode);
        }
        break;
    case 0x1000:
        ftParts_80073830(pobj, vmtx, pmtx, rendermode);
        break;
    case 0x2000:
        ftParts_80073CA8(pobj, vmtx, pmtx, rendermode);
        break;
    }
}

void ftParts_PObjInfoInit(void)
{
    hsdInitClassInfo(HSD_CLASS_INFO(&ftPObj), HSD_CLASS_INFO(&hsdPObj),
                     "fighter_class_library", "ft_pobj", sizeof(HSD_PObjInfo),
                     sizeof(HSD_PObj));
    HSD_POBJ_INFO(&ftPObj)->load = lbRefract_PObjLoad;
    HSD_POBJ_INFO(&ftPObj)->setup_mtx = ftParts_PObjSetupMtx;
}

void ftParts_80074148(void)
{
    HSD_PObjSetDefaultClass(&ftPObj);
}

void ftParts_80074170(void)
{
    HSD_PObjSetDefaultClass(NULL);
}

void ftParts_80074194(Fighter* fighter, FighterBone* bone, HSD_JObj* jobj,
                      int* dobj_index, u32 tree_depth)
{
    HSD_DObj* dobj = HSD_JObjGetDObj(jobj);
    u32 jobj_flags = HSD_JObjGetFlags(jobj);
    int dobj_count = 0;
    HSD_MObj* mobj;

    PAD_STACK(8);

    bone->joint = jobj;

    bone->flags_b1 = true;
    bone->flags_b7 = jobj_flags & JOBJ_LIGHTING ? true : false;
    bone->flags2_b0 = jobj_flags & JOBJ_TEXGEN ? true : false;
    bone->flags2_b1 = jobj_flags & JOBJ_SPECULAR ? true : false;
    bone->flags2_b2 = jobj_flags & JOBJ_UNK_B18 ? true : false;
    bone->flags2_b3 = jobj_flags & JOBJ_UNK_B20 ? true : false;
    bone->flags2_b4 = jobj_flags & JOBJ_UNK_B19 ? true : false;
    bone->xC = tree_depth;

    while (true) {
        if (dobj == NULL) {
            break;
        }
        if (*dobj_index >= 124) {
            HSD_ASSERTREPORT(466, 0,
                             "fighter parts model dobj num over! player %d\n",
                             fighter->player_id);
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
                         fighter->player_id);
    }
    if (*dobj_index != 0) {
        bone->xD = *dobj_index - 1;
    } else {
        bone->xD = 0;
    }
    bone->flags2_b6 = dobj_count != 0 ? true : false;
}

void ftParts_SetupParts(Fighter_GObj* fighter_obj)
{
    HSD_JObj* jobj = GET_JOBJ(fighter_obj);
    Fighter* fp = GET_FIGHTER(fighter_obj);
    u32 part = 0;
    u32 tree_depth = 0;
    int dobj_count = 0;

    if (ftPartsTable[fp->kind]->parts_num > MAX_FT_PARTS) {
        HSD_ASSERTREPORT(503, 0, "fighter parts num over! player %d\n",
                         fp->player_id);
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
                         fp->player_id);
    }
}

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
                         fp->player_id);
    }
}

HSD_JObj* ftParts_8007482C(HSD_Joint* joint)
{
    HSD_JObj* jobj;
    HSD_JObjSetDefaultClass(HSD_CLASS_INFO(&ftIntpJObj));
    jobj = HSD_JObjLoadJoint(joint);
    HSD_JObjSetDefaultClass(NULL);
    return jobj;
}

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

void ftParts_800749CC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int i;

    ftParts_8007487C(&fp->ft_data->x8->x0, &fp->x5AC, fp->x619_costume_id,
                     &fp->dobj_list, &fp->x203C);
    for (i = 0; i < fp->x5AC.model_num; i++) {
        fp->x5F4_arr[i].x0 = -1;
    }
    ftParts_80074ACC(gobj);
}

void ftParts_80074A4C(Fighter_GObj* gobj, int idx, int val)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x5F4_arr[idx].x0 = val;
    fp->x221D_b2 = true;
}

int ftParts_80074A74(Fighter_GObj* gobj, int idx)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->x5F4_arr[idx].x0;
}

void ftParts_80074A8C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int i;

    for (i = 0; i < fp->x5AC.model_num; i++) {
        fp->x5F4_arr[i].x1 = fp->x5F4_arr[i].x0;
    }
    fp->x221D_b2 = false;
}

void ftParts_80074ACC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int i;

    for (i = 0; i < fp->x5AC.model_num; i++) {
        fp->x5F4_arr[i].x1 = -1;
    }
    fp->x221D_b2 = false;
}

void ftParts_80074B0C(Fighter_GObj* gobj, int idx, int val)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (val != fp->x5F4_arr[idx].x1) {
        fp->x5F4_arr[idx].x1 = val;
        fp->x221D_b2 = true;
        ftParts_80074D7C(&fp->x5AC, 0, &fp->dobj_list);
    }
}

void ftParts_80074B6C(Fighter* fp, FtPartsVis* vis, int idx,
                      DObjList* dobj_list)
{
    FtPartsVisLookup* lookup = vis->xC[idx]; // r4
    if (lookup != NULL && !vis->cleared[idx]) {
        int i; // r26
        for (i = 0; i < vis->model_num; i++) {
            int r25 = (int) fp->x5F4_arr[i].x1; // r25
            int j;                              // r24
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

void ftParts_80074E58(Fighter* fp)
{
    int i;

    fp->parts = HSD_ObjAlloc(&fighter_parts_alloc_data);
    fp->dobj_list.data = HSD_ObjAlloc(&fighter_dobj_list_alloc_data);

    for (i = 0; i < ftPartsTable[fp->kind]->parts_num; i++) {
        fp->parts[i].flags8 = 0;
        fp->parts[i].flagsC = 0;
    }

    fp->parts[0].flags_b3 = true;
    fp->parts[ftParts_GetBoneIndex(fp, FtPart_TransN)].flags_b3 = true;
    fp->parts[ftParts_GetBoneIndex(fp, FtPart_XRotN)].flags_b3 = true;
    fp->parts[ftParts_GetBoneIndex(fp, FtPart_YRotN)].flags_b3 = true;
    fp->parts[ftParts_GetBoneIndex(fp, FtPart_HipN)].flags_b3 = true;
    fp->parts[ftParts_GetBoneIndex(fp, FtPart_TransN2)].flags_b3 = true;
    fp->parts[ftParts_GetBoneIndex(fp, FtPart_TransN)].flags_b4 = true;
    fp->parts[ftParts_GetBoneIndex(fp, 0x35)].flags_b4 = true;
}

Fighter_Part ftParts_GetBoneIndex(Fighter* fp, Fighter_Part part)
{
    return ftPartsTable[fp->kind]->part_to_joint[part];
}

int ftParts_80075028(size_t to_table_idx, size_t from_table_idx,
                     size_t joint_idx)
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

u32 ftParts_8007506C(enum FighterKind ftkind, int part)
{
    struct Fighter_804D6540_x0_t* var_r3;
    int i;
    struct Fighter_804D6540_t* temp_r3;

    temp_r3 = Fighter_804D6540[ftkind];
    if (temp_r3 != NULL && temp_r3->x4 != 0) {
        var_r3 = temp_r3->x0;
        for (i = 0; i < temp_r3->x4; i++, var_r3++) {
            if (var_r3->x0 == part) {
                return 1 << i;
            }
        }
    }
    return 0;
}

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

void ftParts_800753D4(Fighter* arg0, struct Fighter_804D6540_x0_t* arg1,
                      HSD_Joint* arg2)
{
    HSD_Joint* sp6C;
    HSD_Joint sp2C;

    HSD_JObj* temp_r31;
    HSD_JObj* temp_r30;
    int i;
    u32 tree_depth;
    int dobj_index;

    sp6C = arg2;
    if (arg1->x3 != 0xFF) {
        s32 depth = 0;
        for (i = 0; i < arg1->x3; i++) {
            ftAnim_GetNextJointInTree(&sp6C, &depth);
        }
    }
    sp2C = *sp6C;
    sp2C.next = 0;
    sp2C.child = 0;

    temp_r30 = ftParts_8007482C(&sp2C);
    temp_r31 = ftParts_8007482C(&sp2C);

    ftParts_80075304(arg1->x2, arg0->parts[arg1->x1].joint, temp_r30);
    ftParts_80075304(arg1->x2, arg0->parts[arg1->x1].x4_jobj2, temp_r31);

    tree_depth = arg0->parts[arg1->x1].xC;
    if (arg1->x2 == 0 || arg1->x2 == 1) {
        tree_depth++;
    }
    dobj_index = 0;
    ftParts_80074194(arg0, &arg0->parts[arg1->x0], temp_r30, &dobj_index,
                     tree_depth);

    arg0->parts[arg1->x0].x4_jobj2 = temp_r31;
    arg0->parts[arg1->x0].flags_b2 = true;
}

void ftParts_800755E8(Fighter* fp, u8* arg1)
{
    FighterBone* bone = &fp->parts[*arg1];
    HSD_JObjRemove(bone->joint);
    HSD_JObjRemove(bone->x4_jobj2);
    bone->joint = NULL;
    bone->x4_jobj2 = NULL;
    bone->flags_b1 = false;
    bone->flags_b2 = false;
}

void ftParts_80075650(Fighter_GObj* arg0, HSD_JObj* jobj, DObjList* arg2)
{
    s32 var_r30;
    HSD_DObj* dobj;

    HSD_DObj* var_r0;
    HSD_MObj* temp_r0;

    PAD_STACK(8);

    var_r30 = 0;
    while (jobj != NULL) {
        dobj = HSD_JObjGetDObj(jobj);
        while (true) {
            if (dobj == NULL) {
                break;
            }
            if (var_r30 >= 0x20) {
                HSD_ASSERTREPORT(1063, 0,
                                 "fighter parts model dobj num over!\n");
            }
            arg2->data[var_r30] = dobj;
            temp_r0 = dobj->mobj;
            if (temp_r0 != NULL) {
                hsdChangeClass(temp_r0, &ftMObj);
            }
            if (dobj != NULL) {
                var_r0 = dobj->next;
            } else {
                var_r0 = NULL;
            }
            dobj = var_r0;
            var_r30 += 1;
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

void ftParts_JObjSetRotation(HSD_JObj* jobj, Vec4* quat)
{
    HSD_JObjSetRotation(jobj, quat);
    HSD_JObjClearFlags(jobj, JOBJ_USE_QUATERNION);
}

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
