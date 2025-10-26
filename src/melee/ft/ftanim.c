#include "ftanim.h"

#include "placeholder.h"

#include <sysdolphin/baselib/aobj.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/mtx.h>
#include <sysdolphin/baselib/object.h>
#include <melee/ft/chara/ftCommon/ftCo_Attack100.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ft_0852.h>
#include <melee/ft/ftaction.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/ftdata.h>
#include <melee/ft/ftparts.h>
#include <melee/ft/inlines.h>
#include <melee/ft/types.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lbanim.h>
#include <melee/lb/lbvector.h>

static HSD_AnimJoint* ftAnim_804590D8[30];
static HSD_MatAnimJoint* ftAnim_804590D8_unk[30];
static HSD_Joint* ftAnim_804590D8_F0[30];

void ftAnim_8006DBF4(HSD_AnimJoint** panimjoint, int* arg1)
{
    HSD_AnimJoint* temp_r28 = *panimjoint;
    HSD_AnimJoint* var_r0;
    int i = *arg1;

    if (temp_r28->child != NULL) {
        ftAnim_804590D8[i++] = temp_r28;
        if (i >= 30) {
            OSReport("fighter joint depth num over!\n");
            __assert("ftanim.c", 0x2E, "0");
        }
        var_r0 = temp_r28->child;
    } else {
        if (temp_r28->next != NULL) {
            var_r0 = temp_r28->next;
        } else {
            while (1) {
                if (i == 0) {
                    var_r0 = NULL;
                    break;
                }
                if (ftAnim_804590D8[i - 1]->next != NULL) {
                    var_r0 = ftAnim_804590D8[--i]->next;
                    break;
                }
                i--;
            }
        }
    }
    *panimjoint = var_r0;
    *arg1 = i;
}

void ftAnim_8006DCF4(HSD_MatAnimJoint** pjoint, int* pdepth)
{
    HSD_MatAnimJoint* temp_r28;
    HSD_MatAnimJoint* var_r0;
    s32 i;

    temp_r28 = *pjoint;
    i = *pdepth;
    if (temp_r28->child != NULL) {
        ftAnim_804590D8_unk[i++] = temp_r28;
        if (i >= 30) {
            OSReport("fighter joint depth num over!\n");
            __assert("ftanim.c", 0x57, "0");
        }
        var_r0 = temp_r28->child;
    } else {
        if (temp_r28->next != NULL) {
            var_r0 = temp_r28->next;
        } else {
            while (1) {
                if (i == 0) {
                    var_r0 = NULL;
                    break;
                }
                if (ftAnim_804590D8_unk[i - 1]->next != 0U) {
                    var_r0 = ftAnim_804590D8_unk[--i]->next;
                    break;
                }
                i--;
            }
        }
    }
    *pjoint = var_r0;
    *pdepth = i;
}

void ftAnim_GetNextJointInTree(HSD_Joint** pjoint, s32* pdepth)
{
    HSD_Joint* temp_r28;
    HSD_Joint* var_r0;
    int i;

    temp_r28 = *pjoint;
    i = *pdepth;
    if (temp_r28->child != NULL) {
        ftAnim_804590D8_F0[i++] = temp_r28;
        if (i >= 30) {
            OSReport("fighter joint depth num over!\n");
            __assert("ftanim.c", 0x80, "0");
        }
        var_r0 = temp_r28->child;
    } else {
        if (temp_r28->next != NULL) {
            var_r0 = temp_r28->next;
        } else {
            while (1) {
                if (i == 0) {
                    var_r0 = NULL;
                    break;
                }
                if (ftAnim_804590D8_F0[i - 1]->next != 0U) {
                    var_r0 = ftAnim_804590D8_F0[--i]->next;
                    break;
                }
                i--;
            }
        }
    }
    *pjoint = var_r0;
    *pdepth = i;
}

void ftAnim_8006DF0C(Fighter* fp)
{
    HSD_JObj* temp_r31;
    HSD_JObj* temp_r30;
    Mtx mtx;
    Vec3 vec;

    if (fp->x2221_b2) {
        temp_r30 = fp->parts[0].joint;
        temp_r31 = fp->parts[fp->ft_data->x8->x10].joint;
        lb_8000B1CC(fp->parts[ftParts_GetBoneIndex(fp, FtPart_HipN)].joint,
                    &p_ftCommonData->x808, &vec);
        HSD_MtxInverse(HSD_JObjGetMtxPtr(temp_r30), mtx);
        PSMTXMultVec(mtx, &vec, &vec);
        HSD_JObjSetTranslate(temp_r31, &vec);
    }
}

/// #ftAnim_8006DF0C

static inline HSD_JObj* next(HSD_JObj* jobj)
{
    if (jobj == NULL) {
        return NULL;
    }
    return jobj->next;
}
static inline HSD_JObj* parent(HSD_JObj* jobj)
{
    if (jobj == NULL) {
        return NULL;
    }
    return jobj->parent;
}
static inline HSD_JObj* child(HSD_JObj* jobj)
{
    if (jobj == NULL) {
        return NULL;
    }
    return jobj->child;
}

void ftAnim_8006E054(Fighter* fp, HSD_JObj* jobj, HSD_JObj* arg2,
                     HSD_JObj* arg3)
{
    Vec3 sp5C;
    Vec3 sp50;
    Vec3 sp44;
    Vec3 sp38;
    Vec3 sp2C;
    u32 temp_r4;
    u32 temp_r4_2;
    u32 temp_r4_3;
    u32 temp_r4_4;
    u32 pad[1];

    HSD_AObjInitEndCallBack();

    while (jobj != NULL) {
        if (jobj == arg2) {
            if (jobj != NULL) {
                sp50.x = sp50.y = sp50.z = 0.0F;
                HSD_JObjAnim(jobj);
                fp->x698 = fp->x68C_transNPos;
                HSD_JObjGetTranslation(jobj, &fp->x68C_transNPos);
                if (!fp->x594_b6) {
                    float temp_f1 = ftCommon_GetModelScale(fp);
                    fp->x68C_transNPos.x *= temp_f1;
                    fp->x68C_transNPos.y *= temp_f1;
                    fp->x68C_transNPos.z *= temp_f1;
                } else {
                    float temp_f1_2 = fp->co_attrs.model_scaling;
                    fp->x68C_transNPos.x *= temp_f1_2;
                    fp->x68C_transNPos.y *= temp_f1_2;
                    fp->x68C_transNPos.z *= temp_f1_2;
                }
                fp->x6B0 = fp->x6A4_transNOffset;
                lbVector_Diff(&fp->x68C_transNPos, &fp->x698,
                              &fp->x6A4_transNOffset);
                HSD_JObjSetTranslate(jobj, &sp50);
            }
        } else if (fp->x594_b5 && jobj == arg3) {
            if (jobj != NULL) {
                sp44.x = sp44.y = sp44.z = 0.0F;
                HSD_JObjAnim(jobj);
                fp->x6CC = fp->x6C0;
                HSD_JObjGetTranslation(jobj, &fp->x6C0);
                if (!fp->x594_b6) {
                    float temp_f1_3 = ftCommon_GetModelScale(fp);
                    fp->x6C0.x *= temp_f1_3;
                    fp->x6C0.y *= temp_f1_3;
                    fp->x6C0.z *= temp_f1_3;
                } else {
                    float temp_f1_4 = fp->co_attrs.model_scaling;
                    fp->x6C0.x *= temp_f1_4;
                    fp->x6C0.y *= temp_f1_4;
                    fp->x6C0.z *= temp_f1_4;
                }
                fp->x6E4 = fp->x6D8;
                lbVector_Diff(&fp->x6C0, &fp->x6CC, &fp->x6D8);
                HSD_JObjSetTranslate(jobj, &sp44);
            }
        } else {
            HSD_JObjAnim(jobj);
        }

        if (!(HSD_JObjGetFlags(jobj) & 0x1000) && child(jobj) != NULL) {
            jobj = child(jobj);
        } else if (next(jobj) != NULL) {
            jobj = next(jobj);
        } else {
            while (1) {
                if (parent(jobj) == NULL) {
                    jobj = NULL;
                    break;
                }
                if (next(parent(jobj)) != NULL) {
                    jobj = next(parent(jobj));
                    break;
                }
                jobj = parent(jobj);
            }
        }
    }
    if (fp->x594_b5) {
        sp5C.x = fp->x68C_transNPos.x - fp->x6C0.x;
        sp5C.y = fp->x68C_transNPos.y - fp->x6C0.y;
        sp5C.z = fp->x68C_transNPos.z - fp->x6C0.z;
        HSD_JObjSetTranslate(arg2, &sp5C);
        fp->x68C_transNPos = fp->x6C0;
        fp->x698 = fp->x6CC;
        fp->x6A4_transNOffset = fp->x6D8;
        fp->x6B0 = fp->x6E4;
    }
    if (!fp->x2226_b2 && fp->x2221_b2) {
        jobj = fp->parts[fp->ft_data->x8->x10].joint;
        ftCommon_GetModelScale(fp);
        HSD_JObjGetTranslation(jobj, &sp2C);
        sp38 = fp->x68C_transNPos;
        if (!fp->x594_b6) {
            float temp_f1_5 = 1.0F / ftCommon_GetModelScale(fp);
            sp38.x *= temp_f1_5;
            sp38.y *= temp_f1_5;
            sp38.z *= temp_f1_5;
        } else {
            float temp_f1_6 = 1.0F / fp->co_attrs.model_scaling;
            sp38.x *= temp_f1_6;
            sp38.y *= temp_f1_6;
            sp38.z *= temp_f1_6;
        }
        lbVector_Sub(&sp2C, &sp38);
        HSD_JObjSetTranslate(jobj, &sp2C);
    }
    HSD_AObjInvokeCallBacks();
}

void ftAnim_8006E7B8(Fighter* fp, int arg1)
{
    HSD_JObj* jobj;
    int i;
    HSD_JObj* temp_r30;
    int temp_r27;

    HSD_AObjInitEndCallBack();
    i = arg1;
    temp_r30 = fp->parts[arg1].joint;
    temp_r27 = fp->parts[arg1].xC;
    jobj = temp_r30;
    while (jobj != NULL) {
        while (!fp->parts[i].flags_b1) {
            i++;
        }
        if (fp->parts[i].xC <= temp_r27 && i != arg1) {
            break;
        }
        if (!fp->parts[i].flags_b0 && !fp->parts[i].flags_b5) {
            HSD_JObjAnim(jobj);
        }
        i++;

        if (!(HSD_JObjGetFlags(jobj) & 0x1000) && child(jobj) != NULL) {
            jobj = child(jobj);
        } else if (next(jobj) != NULL) {
            jobj = next(jobj);
        } else {
            while (1) {
                if (parent(jobj) == NULL || parent(jobj) == temp_r30) {
                    jobj = NULL;
                    break;
                }
                if (next(parent(jobj)) != NULL) {
                    jobj = next(parent(jobj));
                    break;
                }
                jobj = parent(jobj);
            }
        }
    }
    HSD_AObjInvokeCallBacks();
}

void ftAnim_8006E9B4(Fighter_GObj* fighter_gobj)
{
    Fighter* fp;
    HSD_JObj* temp_r27;
    HSD_JObj* temp_r27_2;
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f2_2;
    f32 var_f31;
    f32 var_f30;

    fp = GET_FIGHTER(fighter_gobj);

    if (fp->anim_id != -1) {
        temp_r27 = fighter_gobj->hsd_obj;
        if (fp->x8A4_animBlendFrames == 0.0F) {
            HSD_JObjClearFlagsAll(temp_r27, 0x20000);
            if (fp->x594_b0) {
                ftAnim_8006E054(
                    fp, temp_r27,
                    fp->parts[ftParts_GetBoneIndex(fp, FtPart_TransN)].joint,
                    fp->parts[ftParts_GetBoneIndex(fp, 0x35)].joint);
            } else {
                ftAnim_8006E7B8(fp, 0);
            }
        } else {
            temp_r27_2 = fp->x8AC_animSkeleton;
            temp_f1 = lbGetJObjFramerate(temp_r27_2);
            fp->x8A8_unk += temp_f1;
            if (fp->x8A4_animBlendFrames <= fp->x8A8_unk) {
                fp->x8A8_unk = fp->x8A4_animBlendFrames;
                var_f30 = 1.0F;
                var_f31 = 0.0F;
            } else {
                temp_f1_2 =
                    temp_f1 /
                    (temp_f1 + (fp->x8A4_animBlendFrames - fp->x8A8_unk));
                var_f30 = temp_f1_2;
                var_f31 = 1.0F - temp_f1_2;
            }
            ftAnim_8006E7B8(fp, 0);
            if (fp->x594_b0) {
                ftAnim_8006E054(
                    fp, temp_r27_2,
                    fp->parts[ftParts_GetBoneIndex(fp, FtPart_TransN)]
                        .x4_jobj2,
                    fp->parts[ftParts_GetBoneIndex(fp, 0x35)].joint);
            } else {
                HSD_JObjAnimAll(temp_r27_2);
            }
            if (var_f31) {
                ftAnim_8006FE9C(fp, 1, var_f30, var_f31);
            } else {
                ftAnim_8006FF74(fp, 1);
            }
        }
        if (fp->x594_b2) {
            if (ftAnim_8006F3DC(fighter_gobj) < fp->cur_anim_frame) {
                fp->x898_unk += fp->cur_anim_frame + fp->frame_speed_mul;
            }
        }
        fp->cur_anim_frame = ftAnim_8006F3DC(fighter_gobj);
    }
}

// Process animation?
void ftAnim_8006EBA4(Fighter_GObj* gobj)
{
    ftAnim_8006E9B4(gobj);
    ftAction_80073240(gobj);
    ftAnim_800707B0(gobj);
    ftCo_800DB500(gobj);
}

void ftAnim_8006EBE8(HSD_GObj* gobj, float arg1, float anim_rate,
                     float anim_blend_frames)
{
    static u32 const mask = AOBJ_MASK | COBJ_MASK | DOBJ_MASK | FOBJ_MASK |
                            FOG_MASK | JOBJ_MASK | LOBJ_MASK | POBJ_MASK |
                            ROBJ_MASK | WOBJ_MASK | RENDER_MASK | CHAN_MASK |
                            TEVREG_MASK | CBOBJ_MASK;
    HSD_JObj* root_jobj = GET_JOBJ(gobj);
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_JObj* anim_jobj = fp->x8AC_animSkeleton;
    ftAnim_80070758(root_jobj);
    ftAnim_80070758(anim_jobj);
    if (anim_blend_frames == 0) {
        ftAnim_8006FA58(fp, true, fp->x108_costume_joint->child);
        ftAnim_8006FE08(fp, false);
        ftAnim_80070710(root_jobj, arg1);
        if (fp->x594_b1) {
            HSD_ForeachAnim(root_jobj, JOBJ_TYPE, mask, HSD_AObjSetFlags,
                            AOBJ_ARG_AU, AOBJ_LOOP);
        }
        HSD_ForeachAnim(root_jobj, JOBJ_TYPE, mask, HSD_AObjSetRate,
                        AOBJ_ARG_AF, anim_rate);
    } else {
        ftAnim_8006FB88(fp, true, fp->x108_costume_joint->child);
        ftAnim_8006FE08(fp, true);
        ftAnim_80070710(anim_jobj, arg1);
        ftAnim_80070710(root_jobj, arg1);
        if (fp->x594_b1) {
            HSD_ForeachAnim(anim_jobj, JOBJ_TYPE, mask, HSD_AObjSetFlags,
                            AOBJ_ARG_AU, AOBJ_LOOP);
            HSD_ForeachAnim(root_jobj, JOBJ_TYPE, mask, HSD_AObjSetFlags,
                            AOBJ_ARG_AU, AOBJ_LOOP);
        }
        HSD_ForeachAnim(anim_jobj, JOBJ_TYPE, mask, HSD_AObjSetRate,
                        AOBJ_ARG_AF, anim_rate);
        HSD_ForeachAnim(root_jobj, JOBJ_TYPE, mask, HSD_AObjSetRate,
                        AOBJ_ARG_AF, anim_rate);
    }
    fp->x8A4_animBlendFrames = anim_blend_frames;
    fp->x8A8_unk = 0;
}

void ftAnim_8006EDD0(Fighter* fp, int arg1, float arg8, float arg9)
{
    struct ftData_80085FD4_ret* temp_ret;
    HSD_JObj* jobj = fp->x8AC_animSkeleton;
    ftAnim_80070758(jobj);
    ftAnim_8006FB88(fp, 1, fp->x108_costume_joint->child);
    ftAnim_80070A10(fp, 0, ftData_80085E50(fp, arg1));
    ftAnim_80070710(jobj, arg8);
    temp_ret = ftData_80085FD4(fp, arg1);
    if (temp_ret->x10_b1) {
        HSD_ForeachAnim(jobj, JOBJ_TYPE, 0xFB7F, HSD_AObjSetFlags, AOBJ_ARG_AU,
                        0x20000000);
    }
    HSD_ForeachAnim(jobj, JOBJ_TYPE, 0xFB7F, HSD_AObjSetRate, AOBJ_ARG_AF,
                    arg9);
}

void ftAnim_8006EED4(Fighter* fp, Fighter_Part arg1, FigaTree* arg2,
                     float arg3, float arg4)
{
    HSD_JObj* temp_r26;
    HSD_JObj* temp_r31;
    struct ftData_80085FD4_ret* temp_ret;

    temp_r31 = fp->parts[arg1].joint;
    if (fp->x8A4_animBlendFrames == 0.0F) {
        ftAnim_8006FA58(fp, arg1,
                        ftAnim_8006F994(fp, temp_r31, fp->x108_costume_joint));
        ftAnim_8006F954(fp, arg1, 0, arg2);
        ftAnim_80070710(temp_r31, arg3);
        temp_ret = ftData_80085FD4(fp, fp->anim_id);
        if (temp_ret->x10_b1) {
            HSD_ForeachAnim(temp_r31, JOBJ_TYPE, 0xFB7F, HSD_AObjSetFlags,
                            AOBJ_ARG_AU, 0x20000000);
        }
        HSD_ForeachAnim(temp_r31, JOBJ_TYPE, 0xFB7F, HSD_AObjSetRate,
                        AOBJ_ARG_AF, arg4);
        ftAnim_8006E7B8(fp, arg1);
        return;
    }
    temp_r26 = fp->parts[arg1].x4_jobj2;
    ftAnim_8006FB88(fp, arg1,
                    ftAnim_8006F994(fp, temp_r31, fp->x108_costume_joint));
    ftAnim_8006F954(fp, arg1, 1, arg2);
    ftAnim_80070710(temp_r26, arg3);
    ftAnim_80070710(temp_r31, arg3);
    if (fp->x594_b1) {
        HSD_ForeachAnim(temp_r26, JOBJ_TYPE, 0xFB7F, HSD_AObjSetFlags,
                        AOBJ_ARG_AU, 0x20000000);
        HSD_ForeachAnim(temp_r31, JOBJ_TYPE, 0xFB7F, HSD_AObjSetFlags,
                        AOBJ_ARG_AU, 0x20000000);
    }
    HSD_ForeachAnim(temp_r26, JOBJ_TYPE, 0xFB7F, HSD_AObjSetRate, AOBJ_ARG_AF,
                    arg4);
    HSD_ForeachAnim(temp_r31, JOBJ_TYPE, 0xFB7F, HSD_AObjSetRate, AOBJ_ARG_AF,
                    arg4);
    HSD_JObjAnimAll(temp_r26);
    ftAnim_8006E7B8(fp, arg1);
}

static inline void ftAnim_8006F0FC_inline(HSD_JObj* jobj, float anim_rate)
{
    HSD_ForeachAnim(jobj, JOBJ_TYPE, 0xFB7F, HSD_AObjSetRate, AOBJ_ARG_AF,
                    anim_rate);
}

void ftAnim_8006F0FC(Fighter_GObj* gobj, float anim_rate)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    ftAnim_8006F0FC_inline(jobj, anim_rate);
    ftAnim_8006F0FC_inline(fp->x8AC_animSkeleton, anim_rate);
    fp->frame_speed_mul = anim_rate;
}

/// #ftAnim_SetAnimRate

void ftAnim_SetAnimRate(Fighter_GObj* gobj, float anim_rate)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->x2223_b0) {
        fp->x8A0_unk = anim_rate;
        return;
    }
    ftAnim_8006F0FC(gobj, anim_rate);
}

bool ftAnim_IsFramesRemaining(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int i;

    if (fp->x8A4_animBlendFrames == 0.0F) {
        for (i = 0; i < ftPartsTable[fp->kind]->parts_num; i++) {
            if (fp->parts[i].flags_b1 && !fp->parts[i].flags_b0 &&
                !fp->parts[i].flags_b5 && lb_8000B074(fp->parts[i].joint))
            {
                return true;
            }
        }
    } else {
        for (i = 0; i < ftPartsTable[fp->kind]->parts_num; i++) {
            if (fp->parts[i].flags_b1 && !fp->parts[i].flags_b0 &&
                !fp->parts[i].flags_b5 && lb_8000B074(fp->parts[i].x4_jobj2))
            {
                return true;
            }
        }
    }
    return false;
}

bool ftAnim_8006F368(Fighter* fp, Fighter_Part part)
{
    if (fp->x8A4_animBlendFrames == 0.0F) {
        if (lb_8000B074(fp->parts[part].joint)) {
            return true;
        }
    } else if (lb_8000B074(fp->parts[part].x4_jobj2)) {
        return true;
    }
    return false;
}

float ftAnim_8006F3DC(Fighter_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    if (fp->x8A4_animBlendFrames == 0.0F) {
        int i;
        for (i = 0; i < ftPartsTable[fp->kind]->parts_num; i++) {
            if (fp->parts[i].flags_b1 && !fp->parts[i].flags_b0 &&
                !fp->parts[i].flags_b5)
            {
                HSD_AObj* aobj = fp->parts[i].joint->aobj;
                if (aobj != 0) {
                    return aobj->curr_frame;
                }
            }
        }
#ifdef BUGFIX
        return 0.0F;
#endif
    } else {
        return lbGetJObjCurrFrame(fp->x8AC_animSkeleton);
    }
}

float ftAnim_8006F484(Fighter_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    HSD_JObj* jobj = GET_JOBJ(fighter_gobj);
    if (fp->x8A4_animBlendFrames == 0.0F) {
        return lbGetJObjEndFrame(jobj);
    }
    return lbGetJObjEndFrame(fp->x8AC_animSkeleton);
}

static HSD_JObj* get_part_joint(Fighter* fp, int i, int arg1)
{
    HSD_JObj* result;
    if (arg1 != 0) {
        result = fp->parts[i].x4_jobj2;
    } else {
        result = fp->parts[i].joint;
    }
    return result;
}

void ftAnim_8006F4C8(Fighter* fp, int arg1, FigaTree* arg2)
{
    s8* cur_node;
    FigaTrack* cur_track;
    u32 flags;
    u32 temp_r3;
    int i = 0;

    cur_node = arg2->nodes;
    cur_track = arg2->tracks;

    flags = fp->x594_bits;

    while (*cur_node != -1) {
        while (!fp->parts[i].flags_b1) {
            i++;
        }
        while (1) {
            if (!fp->parts[i].flags_b2) {
                break;
            }
            temp_r3 = ftParts_8007506C(fp->kind, i);
            if (temp_r3 == 0 || (temp_r3 & flags)) {
                break;
            }
            i++;
        }
        if (i >= 0x8C) {
            OSReport("atree data error! player %d\n", fp->player_id);
            __assert("ftanim.c", 0x2FF, "0");
        }
        if (!fp->parts[i].flags_b0 && !fp->parts[i].flags_b5) {
            HSD_JObj* jobj = get_part_joint(fp, i, arg1);
            lbAnim_8001E6D8(jobj, arg2, cur_track, *cur_node);
        }
        {
            s8 temp_r0 = *cur_node++;
            i++;
            cur_track += temp_r0;
        }
    }
}

void ftAnim_8006F628(Fighter* fp, Fighter_Part arg1, int arg2)
{
    FigaTree* temp_r31;
    s32 temp_r30;
    FighterKind temp_r29;
    s8* var_r28;
    FigaTrack* var_r27;
    int i;
    u32 temp_r3;
    u32 temp_r3_2;
    s8 temp_r0_2;
    int temp_r25;

    i = 0;
    temp_r31 = fp->x590;
    var_r28 = temp_r31->nodes;
    temp_r30 = fp->x594_bits;
    var_r27 = temp_r31->tracks;
    temp_r29 = fp->x597_bits;
    temp_r25 = fp->parts[arg1].xC;

    while (i < arg1) {
        temp_r3 = ftParts_8007506C(temp_r29, i);
        if ((temp_r3 == 0) || (temp_r3 & temp_r30)) {
            var_r27 = &var_r27[*var_r28++];
        }
        i++;
    }
    while (*var_r28 != -1) {
        while (1) {
            temp_r3_2 = ftParts_8007506C(temp_r29, i);
            if (temp_r3_2 == 0 || (temp_r3_2 & temp_r30)) {
                break;
            }
            i++;
        }
        if (fp->parts[i].xC <= temp_r25 && (i != arg1)) {
            break;
        }

        {
            int tmp = ftParts_80075028(fp->kind, temp_r29, i);
            if (tmp != 0xFFU) {
                if (fp->parts[tmp].flags_b1 && !fp->parts[tmp].flags_b0 &&
                    !fp->parts[tmp].flags_b5)
                {
                    HSD_JObj* var_r3 = get_part_joint(fp, tmp, arg2);
                    if (fp->parts[tmp].flags_b3) {
                        lbAnim_8001E6D8(var_r3, temp_r31, var_r27, *var_r28);
                    } else {
                        lbAnim_8001E7E8(var_r3, temp_r31, var_r27, *var_r28);
                    }
                }
            }
        }

        temp_r0_2 = *var_r28++;
        i++;
        var_r27 = &var_r27[temp_r0_2];
    }
}

void ftAnim_8006F7C8(Fighter* ft, Fighter_Part part, int arg2, FigaTree* tree)
{
    s8* nodes;
    FigaTrack* tracks;
    int r29;
    int i;
    int r27;
    int r22;
    PAD_STACK(8);

    nodes = tree->nodes;
    tracks = tree->tracks;
    r29 = ft->x594_bits;
    r27 = ft->parts[part].xC;

    for (i = 0; i < part; i++) {
        u32 r3 = ftParts_8007506C(ft->kind, i);
        if (r3 == 0 || r3 & r29) {
            tracks = &tracks[*nodes];
            nodes += 1;
        }
    }

    r22 = i;

    while (*nodes != -1) {
        FighterBone* r3 = &ft->parts[r22];
        int r21;

        while (!r3->flags_b1) {
            r3 += 1;
            i += 1;
            r22 += 1;
        }

        r21 = i;

        while (true) {
            u32 r3;
            if (!ft->parts[r21].flags_b2) {
                break;
            }

            r3 = ftParts_8007506C(ft->kind, i);
            if (r3 == 0 || r3 & r29) {
                break;
            }

            r21 += 1;
            i += 1;
            r22 += 1;
        }

        if (ft->parts[r22].xC <= r27 && i != part) {
            break;
        }

        if (!ft->parts[r22].flags_b0 && !ft->parts[r22].flags_b5) {
            HSD_JObj* r3;
            if (arg2) {
                r3 = ft->parts[r22].x4_jobj2;
            } else {
                r3 = ft->parts[r22].joint;
            }
            lbAnim_8001E6D8(r3, tree, tracks, *nodes);
        }

        tracks = &tracks[*nodes];
        i += 1;
        r22 += 1;
        nodes += 1;
    }
}

void ftAnim_8006F954(Fighter* fp, Fighter_Part arg1, int arg2,
                     FigaTree* unused)
{
    if (fp->kind != fp->x597_bits) {
        ftAnim_8006F628(fp, arg1, arg2);
    } else {
        ftAnim_8006F7C8(fp, arg1, arg2, fp->x590);
    }
}

HSD_Joint* ftAnim_8006F994(Fighter* fp, HSD_JObj* arg1, HSD_Joint* arg2)
{
    int i;
    s32 sp14;

    i = sp14 = 0;
    while (arg2 != NULL) {
        while (ftParts_8007506C(fp->kind, i) != 0) {
            i++;
        }
        if (arg1 == fp->parts[i].joint || arg1 == fp->parts[i].x4_jobj2) {
            return arg2;
        }
        i++;
        ftAnim_GetNextJointInTree(&arg2, &sp14);
    }
}

void ftAnim_8006FA58(Fighter* fp, int arg1, HSD_Joint* arg2)
{
    int i = arg1;
    s32 sp14 = 0;

    while (arg2 != NULL) {
        while (ftParts_8007506C(fp->kind, i) != 0) {
            i++;
        }
        if (i == fp->ft_data->x8->x10) {
            if (fp->parts[i].flags_b0) {
                lb_8000B760(fp->parts[i].joint, arg2);
            } else if (!fp->parts[i].flags_b5) {
                lb_8000B5DC(fp->parts[i].joint, arg2);
            }
            ftCommon_8007F6A4(fp, fp->parts[i].joint);
        } else {
            if (fp->parts[i].flags_b0) {
                lb_8000B6A4(fp->parts[i].joint, arg2);
            } else if (!fp->parts[i].flags_b5) {
                lb_8000B4FC(fp->parts[i].joint, arg2);
            }
        }
        i++;
        ftAnim_GetNextJointInTree(&arg2, &sp14);
    }
}

void ftAnim_8006FB88(Fighter* fp, int arg1, HSD_Joint* arg2)
{
    int i = arg1;
    s32 sp14 = 0;

    while (arg2 != NULL) {
        while (ftParts_8007506C(fp->kind, i) != 0) {
            i++;
        }
        if (i == fp->ft_data->x8->x10) {
            if (fp->parts[i].flags_b0) {
                lb_8000B760(fp->parts[i].x4_jobj2, arg2);
                HSD_JObjClearFlags(fp->parts[i].x4_jobj2, 0x20000);
            } else if (!fp->parts[i].flags_b5) {
                lb_8000B5DC(fp->parts[i].x4_jobj2, arg2);
            }
            ftCommon_8007F6A4(fp, fp->parts[i].x4_jobj2);
        } else {
            if (fp->parts[i].flags_b0) {
                lb_8000B6A4(fp->parts[i].x4_jobj2, arg2);
                HSD_JObjClearFlags(fp->parts[i].x4_jobj2, 0x20000);
            } else if (!fp->parts[i].flags_b5) {
                lb_8000B4FC(fp->parts[i].x4_jobj2, arg2);
            }
        }
        i++;
        ftAnim_GetNextJointInTree(&arg2, &sp14);
    }
}

/// #ftAnim_8006FCE4

void ftAnim_8006FE08(Fighter* fp, int arg1)
{
    if (fp->kind != fp->x597_bits) {
        ftAnim_8006FCE4(fp, arg1);
    } else {
        ftAnim_8006F4C8(fp, arg1, fp->x590);
    }
}

void ftAnim_8006FE48(Fighter_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    fp->x8AC_animSkeleton = ftParts_8007482C(fp->x108_costume_joint);
    fp->x8A4_animBlendFrames = 0.0F;
    fp->x8A8_unk = 0.0F;
    ftParts_8007462C(fighter_gobj);
}

void ftAnim_8006FE9C(Fighter* fp, int start_idx, float arg2, float arg3)
{
    int i;
    for (i = start_idx; i < ftPartsTable[fp->kind]->parts_num; i++) {
        if (fp->parts[i].flags_b1 && !fp->parts[i].flags_b0 &&
            !fp->parts[i].flags_b5)
        {
            if (fp->parts[i].flags_b4) {
                lbCopyJObjSRT(fp->parts[i].x4_jobj2, fp->parts[i].joint);
            } else {
                lb_8000C490(fp->parts[i].x4_jobj2, fp->parts[i].joint,
                            fp->parts[i].joint, arg2, arg3);
            }
        }
    }
}

void ftAnim_8006FF74(Fighter* fp, int start_idx)
{
    int i;
    for (i = start_idx; i < ftPartsTable[fp->kind]->parts_num; i++) {
        if (fp->parts[i].flags_b1 && !fp->parts[i].flags_b0 &&
            !fp->parts[i].flags_b5)
        {
            lbCopyJObjSRT(fp->parts[i].x4_jobj2, fp->parts[i].joint);
        }
    }
}

/// #ftAnim_8006FF74

/// #ftAnim_80070010

/// #ftAnim_80070108

/// #ftAnim_80070200

void ftAnim_80070308(Fighter_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    HSD_JObj* jobj = GET_JOBJ(fighter_gobj);

    HSD_JObjAddAnimAll(jobj, NULL,
                       CostumeListsForeachCharacter[fp->kind]
                           .costume_list[fp->x619_costume_id]
                           .x4,
                       NULL);
    HSD_JObjReqAnimAll(jobj, 0.0f);
    {
        struct ftData_x8_x8* temp_r27 = &fp->ft_data->x8->x8;
        u16* var_r0;
        fp->n_costume_tobjs = temp_r27->x8;
        if (fp->n_costume_tobjs > ARRAY_SIZE(fp->costume_tobjs)) {
            OSReport("fighter tobj num over!\n");
            __assert("ftanim.c", 0x4CC, "0");
        }
        if (temp_r27->xC[fp->x619_costume_id] != NULL) {
            var_r0 = temp_r27->xC[fp->x619_costume_id];
        } else {
            var_r0 = temp_r27->xC[0];
        }
        fp->x5D0 = var_r0;
    }
    {
        int i;
        for (i = 0; i < fp->n_costume_tobjs; i++) {
            fp->costume_tobjs[i] =
                ftParts_80075240(&fp->dobj_list, fp->x5D0[i]);
            if (fp->costume_tobjs[i]->aobj == NULL) {
                OSReport("can't find fighter texture anim!\n");
                __assert("ftanim.c", 0x4D4, "0");
            }
            HSD_AObjSetRate(fp->costume_tobjs[i]->aobj, 0.0F);
        }
    }
}

/// #ftAnim_80070458

extern struct {
    HSD_GObjEvent x0;
    void (*x4)(Fighter_GObj*, int, float frame);
} ftData_UnkCallbackPairs0[FTKIND_MAX];

static inline void tobjAnim(HSD_TObj** temp_r30, f32 frame)
{
    HSD_AObjReqAnim((*temp_r30)->aobj, frame);
    HSD_TObjAnim(*temp_r30);
}

void ftAnim_800704F0(Fighter_GObj* arg0, int arg1, f32 frame)
{
    Fighter* temp_r31;
    HSD_TObj** temp_r30;

    temp_r31 = arg0->user_data;
    if (arg1 >= temp_r31->n_costume_tobjs) {
        OSReport("texture no exist! %d %d\n", temp_r31->player_id, arg1);
        __assert("ftanim.c", 0x4F0U, "0");
    }
    tobjAnim(&temp_r31->costume_tobjs[arg1], frame);
    if (ftData_UnkCallbackPairs0[temp_r31->kind].x4 != NULL) {
        ftData_UnkCallbackPairs0[temp_r31->kind].x4(arg0, arg1, frame);
    }
    temp_r31->x221E_b7 = true;
}

/// #ftAnim_800705E0

static void ftAnim_80070654_inline(Fighter* fp)
{
    int i;
    for (i = 0; i < fp->n_costume_tobjs; i++) {
        HSD_AObjReqAnim(fp->costume_tobjs[i]->aobj, 0.0f);
        HSD_TObjAnim(fp->costume_tobjs[i]);
    }
}

void ftAnim_80070654(Fighter_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    ftAnim_80070654_inline(fp);

    if (ftData_UnkCallbackPairs0[fp->kind].x0 != NULL) {
        ftData_UnkCallbackPairs0[fp->kind].x0(fighter_gobj);
    }
    fp->x221E_b7 = false;
}

void ftAnim_80070710(HSD_JObj* jobj, float frame)
{
    HSD_JObjReqAnimAllByFlags(jobj, 1, frame);
}

void ftAnim_80070734(HSD_JObj* jobj, float frame)
{
    HSD_JObjReqAnimByFlags(jobj, 1, frame);
}

void ftAnim_80070758(HSD_JObj* jobj)
{
    HSD_JObjRemoveAnimAllByFlags(jobj, 1);
}

void ftAnim_8007077C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int i;

    for (i = 0; i < ARRAY_SIZE(fp->x8B0); i++) {
        fp->x8B0[i].x11 = -1;
        fp->x8B0[i].x10 = -1;
    }
}

void ftAnim_800707B0(Fighter_GObj* arg0)
{
    Fighter* fp = GET_FIGHTER(arg0);
    int i;
    int j;

    f32 var_f29;
    f32 var_f28;
    f32 temp_f0_2;

    FighterBone* temp_r3;
    struct Fighter_x8B0_t* temp_r4;

    for (i = 0; i < (signed) ARRAY_SIZE(fp->x8B0); i++) {
        temp_r4 = &fp->x8B0[i];
        if (temp_r4->x11 != -1) {
            struct ftData_x1C* temp_r26 = fp->ft_data->x1C[i];
            u8* var_r29 = temp_r26->x4;

            temp_r4->x8 += temp_r4->xC;
            if (temp_r4->x4 <= temp_r4->x8) {
                temp_r4->x8 = temp_r4->x4;
                var_f28 = 1.0F;
                var_f29 = 0.0F;
            } else {
                temp_f0_2 =
                    temp_r4->xC / (temp_r4->xC + (temp_r4->x4 - temp_r4->x8));
                var_f28 = temp_f0_2;
                var_f29 = 1.0F - temp_f0_2;
            }
            for (j = 0; j < temp_r26->x2; j++) {
                int temp_r0 = var_r29[j];
                if (fp->parts[temp_r0].flags_b5) {
                    if (var_f29) {
                        temp_r3 = &fp->parts[temp_r0];
                        lb_8000C490(temp_r3->x4_jobj2, temp_r3->joint,
                                    temp_r3->joint, var_f28, var_f29);
                    } else {
                        lbCopyJObjSRT(fp->parts[temp_r0].x4_jobj2,
                                      fp->parts[temp_r0].joint);
                    }
                }
            }
        }
    }
}

void ftAnim_80070904(Fighter* fp, int start_idx, HSD_AnimJoint* animjoint)
{
    int i = start_idx;
    int sp14 = 0;

    while (animjoint != NULL) {
        while (ftParts_8007506C(fp->kind, i) != 0) {
            i++;
        }
        if (!fp->parts[i].flags_b0 && animjoint->aobjdesc != NULL) {
            HSD_JObj* jobj = fp->parts[i].x4_jobj2;
            HSD_JObjAddAnim(jobj, animjoint, NULL, NULL);
            HSD_JObjClearFlags(jobj, 0x20000);
            HSD_JObjReqAnimByFlags(jobj, 1, 0.0F);
            HSD_JObjAnim(jobj);
            fp->parts[i].flags_b5 = true;
        }
        i++;
        ftAnim_8006DBF4(&animjoint, &sp14);
    }
}

/// #ftAnim_80070A10

void ftAnim_ApplyPartAnim(Fighter_GObj* gobj, s32 arg1, s32 arg2, f32 arg3)
{
    Fighter* fp = GET_FIGHTER(gobj);
    struct Fighter_x8B0_t* temp_r30;
    struct ftData_x1C* temp_r29;

    temp_r30 = &fp->x8B0[arg1];
    temp_r29 = fp->ft_data->x1C[arg1];
    temp_r30->x11 = arg2;
    temp_r30->x4 = arg3;
    temp_r30->x8 = 0.0F;
    if (arg3) {
        temp_r30->xC = lb_8000BFF0(temp_r29->x8[arg2]) / arg3;
    } else {
        temp_r30->xC = 0.0F;
    }
    ftAnim_80070904(fp, temp_r29->x0, temp_r29->x8[arg2]);
}

/// #ftAnim_80070C48

/// #ftAnim_80070CC4

/// #ftAnim_80070E74

void ftAnim_80070F28(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    int i;
    int j;

    for (i = 0; i < ARRAY_SIZE(fp->x8B0); i++) {
        struct Fighter_x8B0_t* slot = &fp->x8B0[i];
        if ((s8) slot->x11 != -1) {
            struct ftData_x1C* data = fp->ft_data->x1C[i];
            u8* parts_list = data->x4;

            for (j = 0; j < data->x2; j++) {
                u8 part_idx = parts_list[j];
                fp->parts[part_idx].flags_b5 = false;
            }
            slot->x11 = -1;
        }
    }
}
void ftAnim_80070FB4(Fighter_GObj* arg0, s32 arg1, s32 arg2)
{
    Fighter* fp = GET_FIGHTER(arg0);
    struct Fighter_x8B0_t* tmp = &fp->x8B0[arg1];
    tmp->x10 = arg2;
}

bool ftAnim_80070FD0(Fighter* fp)
{
    float rotation = ftParts_80075E78(fp, ftParts_GetBoneIndex(fp, 0x35));
    if (fp->x100 != rotation) {
        fp->x100 = rotation;
        return true;
    }
    return false;
}
