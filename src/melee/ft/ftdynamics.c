#include <platform.h>
#include <placeholder.h>

#include "ft/forward.h"

#include "ftdynamics.h"

#include "ft/ft_0877.h"
#include "ft/ftcoll.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "gr/ground.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"

#include <stddef.h>
#include <baselib/debug.h>
#include <baselib/jobj.h>

#pragma force_active on

char const* _assert_msg = "translate";

/// #ftCo_8009CB40

void ftCo_8009CF84(Fighter* fp)
{
    ftData* data = fp->ft_data;
    fp->dynamics_num = data->x2C->dynamicsNum;
    if (fp->dynamics_num >= Ft_Dynamics_NumMax) {
        OSReport("fighter dynamics num over!\n");
        __assert(__FILE__, 109, "0");
    }
    {
        ssize_t i;
        for (i = 0; i < data->x2C->dynamicsNum; i++) {
            BoneDynamicsDesc* bones = &data->x2C->ftDynamicBones->array[i];
            lb_8000FD48(fp->parts[bones->bone_id].joint,
                        &fp->dynamic_bone_sets[i].dyn_desc,
                        bones->dyn_desc.count);
            fp->dynamic_bone_sets[i].bone_id = 0;
            ftCo_8009CB40(fp, i, 1, 0);
            lb_80011710(&data->x2C->ftDynamicBones->array[i].dyn_desc,
                        &fp->dynamic_bone_sets[i].dyn_desc);
        }
    }
}

void ftCo_8009D074(Fighter* fp)
{
    KirbyHatStruct* hat = ft_80459B88.hats[FTKIND_KOOPA];
    fp->dynamics_num = hat->hat_dynamics[2]->dynamicsNum;
    if (fp->dynamics_num >= Ft_Dynamics_NumMax) {
        OSReport("fighter dynamics num over!\n");
        __assert(__FILE__, 135, "fp->dynamics_num < Ft_Dynamics_NumMax");
    }
    {
        ssize_t i;
        for (i = 0; i < fp->dynamics_num; i++) {
            BoneDynamicsDesc* article =
                &hat->hat_dynamics[2]->ftDynamicBones->array[i];
            HSD_JObj* cur = fp->fv.kb.hat.jobj;
            ssize_t j;
            for (j = 0; j < (signed) article->bone_id; j++) {
                if (cur->child != NULL) {
                    cur = cur->child;
                    continue;
                }
                while (cur->next == NULL) {
                    cur = cur->parent;
                }
                cur = cur->next;
            }
            lb_8000FD48(cur, &fp->dynamic_bone_sets[i].dyn_desc,
                        article->dyn_desc.count);
            fp->dynamic_bone_sets[i].bone_id = 0;
            lb_80011710(
                &hat->hat_dynamics[2]->ftDynamicBones->array[i].dyn_desc,
                &fp->dynamic_bone_sets[i].dyn_desc);
        }
    }
}

void ftCo_8009D18C(Fighter* fp)
{
    KirbyHatStruct* hat = ft_80459B88.hats[FTKIND_ZELDA];
    fp->dynamics_num = hat->hat_dynamics[2]->dynamicsNum;
    if (fp->dynamics_num >= Ft_Dynamics_NumMax) {
        OSReport("fighter dynamics num over!\n");
        __assert(__FILE__, 167, "fp->dynamics_num < Ft_Dynamics_NumMax");
    }
    {
        ssize_t i;
        for (i = 0; i < fp->dynamics_num; i++) {
            BoneDynamicsDesc* article =
                &hat->hat_dynamics[2]->ftDynamicBones->array[i];
            HSD_JObj* cur = fp->fv.kb.hat.jobj;
            ssize_t j;
            for (j = 0; j < (signed) article->bone_id; j++) {
                if (cur->child != NULL) {
                    cur = cur->child;
                    continue;
                }
                while (cur->next == NULL) {
                    cur = cur->parent;
                }
                cur = cur->next;
            }
            lb_8000FD48(cur, &fp->dynamic_bone_sets[i].dyn_desc,
                        article->dyn_desc.count);
            fp->dynamic_bone_sets[i].bone_id = 0;
            lb_80011710(
                &hat->hat_dynamics[2]->ftDynamicBones->array[i].dyn_desc,
                &fp->dynamic_bone_sets[i].dyn_desc);
        }
    }
}

void ftCo_8009D2A4(Fighter* fp)
{
    KirbyHatStruct* hat = ft_80459B88.hats[FTKIND_NANA];
    fp->dynamics_num = hat->hat_dynamics[2]->dynamicsNum;
    if (fp->dynamics_num >= Ft_Dynamics_NumMax) {
        OSReport("fighter dynamics num over!\n");
        __assert(__FILE__, 199, "fp->dynamics_num < Ft_Dynamics_NumMax");
    }
    {
        ssize_t i;
        for (i = 0; i < fp->dynamics_num; i++) {
            BoneDynamicsDesc* article =
                &hat->hat_dynamics[2]->ftDynamicBones->array[i];
            HSD_JObj* cur = fp->fv.kb.hat.jobj;
            ssize_t j;
            for (j = 0; j < (signed) article->bone_id; j++) {
                if (cur->child != NULL) {
                    cur = cur->child;
                    continue;
                }
                while (cur->next == NULL) {
                    cur = cur->parent;
                }
                cur = cur->next;
            }
            lb_8000FD48(cur, &fp->dynamic_bone_sets[i].dyn_desc,
                        article->dyn_desc.count);
            fp->dynamic_bone_sets[i].bone_id = 0;
            lb_80011710(
                &hat->hat_dynamics[2]->ftDynamicBones->array[i].dyn_desc,
                &fp->dynamic_bone_sets[i].dyn_desc);
        }
    }
}

void ftCo_8009D3BC(Fighter* fp)
{
    KirbyHatStruct* hat = ft_80459B88.hats[FTKIND_FALCO];
    fp->dynamics_num = hat->hat_dynamics[2]->dynamicsNum;
    if (fp->dynamics_num >= Ft_Dynamics_NumMax) {
        OSReport("fighter dynamics num over!\n");
        __assert(__FILE__, 232, "fp->dynamics_num < Ft_Dynamics_NumMax");
    }
    {
        ssize_t i;
        for (i = 0; i < fp->dynamics_num; i++) {
            BoneDynamicsDesc* article =
                &hat->hat_dynamics[2]->ftDynamicBones->array[i];
            HSD_JObj* cur = fp->fv.kb.hat.jobj;
            ssize_t j;
            for (j = 0; j < (signed) article->bone_id; j++) {
                if (cur->child != NULL) {
                    cur = cur->child;
                    continue;
                }
                while (cur->next == NULL) {
                    cur = cur->parent;
                }
                cur = cur->next;
            }
            lb_8000FD48(cur, &fp->dynamic_bone_sets[i].dyn_desc,
                        article->dyn_desc.count);
            fp->dynamic_bone_sets[i].bone_id = 0;
            lb_80011710(
                &hat->hat_dynamics[2]->ftDynamicBones->array[i].dyn_desc,
                &fp->dynamic_bone_sets[i].dyn_desc);
        }
    }
}

void ftCo_8009D4D4(Fighter* fp)
{
    KirbyHatStruct* hat = ft_80459B88.hats[FTKIND_KIRBY];
    fp->dynamics_num = hat->hat_dynamics[1]->dynamicsNum;
    if (fp->dynamics_num >= Ft_Dynamics_NumMax) {
        OSReport("fighter dynamics num over!\n");
        __assert(__FILE__, 265, "fp->dynamics_num < Ft_Dynamics_NumMax");
    }
    {
        ssize_t i;
        for (i = 0; i < fp->dynamics_num; i++) {
            BoneDynamicsDesc* article =
                &hat->hat_dynamics[1]->ftDynamicBones->array[i];
            HSD_JObj* cur = fp->fv.kb.hat.jobj;
            ssize_t j;
            for (j = 0; j < (signed) article->bone_id; j++) {
                if (cur->child != NULL) {
                    cur = cur->child;
                    continue;
                }
                while (cur->next == NULL) {
                    cur = cur->parent;
                }
                cur = cur->next;
            }
            lb_8000FD48(cur, &fp->dynamic_bone_sets[i].dyn_desc,
                        article->dyn_desc.count);
            fp->dynamic_bone_sets[i].bone_id = 0;
            lb_80011710(
                &hat->hat_dynamics[1]->ftDynamicBones->array[i].dyn_desc,
                &fp->dynamic_bone_sets[i].dyn_desc);
        }
    }
}

void ftCo_8009D5EC(Fighter* fp)
{
    KirbyHatStruct* hat = ft_80459B88.hats[FTKIND_MARS];
    fp->dynamics_num = hat->hat_dynamics[0]->dynamicsNum;
    if (fp->dynamics_num >= Ft_Dynamics_NumMax) {
        OSReport("fighter dynamics num over!\n");
        __assert(__FILE__, 298, "fp->dynamics_num < Ft_Dynamics_NumMax");
    }
    {
        ssize_t i;
        for (i = 0; i < fp->dynamics_num; i++) {
            BoneDynamicsDesc* article =
                &hat->hat_dynamics[0]->ftDynamicBones->array[i];
            HSD_JObj* cur = fp->fv.kb.hat.jobj;
            ssize_t j;
            for (j = 0; j < (signed) article->bone_id; j++) {
                if (cur->child != NULL) {
                    cur = cur->child;
                    continue;
                }
                while (cur->next == NULL) {
                    cur = cur->parent;
                }
                cur = cur->next;
            }
            lb_8000FD48(cur, &fp->dynamic_bone_sets[i].dyn_desc,
                        article->dyn_desc.count);
            fp->dynamic_bone_sets[i].bone_id = FtPart_TopN;
            lb_80011710(
                &hat->hat_dynamics[0]->ftDynamicBones->array[i].dyn_desc,
                &fp->dynamic_bone_sets[i].dyn_desc);
        }
    }
}

/// #ftCo_8009D704

void ftCo_8009D704(Fighter* fp)
{
    KirbyHatStruct* hat = ft_80459B88.hats[FTKIND_LINK];
    fp->dynamics_num = hat->hat_dynamics[2]->dynamicsNum;
    if (fp->dynamics_num >= Ft_Dynamics_NumMax) {
        OSReport("fighter dynamics num over!\n");
        __assert(__FILE__, 331, "fp->dynamics_num < Ft_Dynamics_NumMax");
    }
    {
        ssize_t i;
        for (i = 0; i < fp->dynamics_num; i++) {
            BoneDynamicsDesc* article =
                &hat->hat_dynamics[2]->ftDynamicBones->array[i];
            HSD_JObj* cur = fp->fv.kb.hat.jobj;
            ssize_t j;
            for (j = 0; j < (signed) article->bone_id; j++) {
                if (cur->child != NULL) {
                    cur = cur->child;
                    continue;
                }
                while (cur->next == NULL) {
                    cur = cur->parent;
                }
                cur = cur->next;
            }
            lb_8000FD48(cur, &fp->dynamic_bone_sets[i].dyn_desc,
                        article->dyn_desc.count);
            fp->dynamic_bone_sets[i].bone_id = FtPart_TopN;
            lb_80011710(
                &hat->hat_dynamics[2]->ftDynamicBones->array[i].dyn_desc,
                &fp->dynamic_bone_sets[i].dyn_desc);
        }
    }
}

void ftCo_8009D81C(Fighter* fp)
{
    KirbyHatStruct* data = ft_80459B88.hats[FTKIND_YOSHI];
    fp->dynamics_num = data->hat_dynamics[3]->dynamicsNum;
    if (fp->dynamics_num >= Ft_Dynamics_NumMax) {
        OSReport("fighter dynamics num over!\n");
        __assert(__FILE__, 364, "fp->dynamics_num < Ft_Dynamics_NumMax");
    }
    {
        ssize_t i;
        for (i = 0; i < fp->dynamics_num; i++) {
            BoneDynamicsDesc* desc =
                &data->hat_dynamics[3]->ftDynamicBones->array[i];
            fp->parts[desc->bone_id].flags_b0 = true;
            lb_8000FD48(fp->parts[desc->bone_id].joint,
                        &fp->dynamic_bone_sets[i].dyn_desc,
                        desc->dyn_desc.count);
            desc->bone_id = FtPart_TopN;
            lb_80011710(
                &data->hat_dynamics[3]->ftDynamicBones->array[i].dyn_desc,
                &fp->dynamic_bone_sets[i].dyn_desc);
        }
    }
}

void ftCo_8009D920(Fighter* fp)
{
    KirbyHatStruct* hat = ft_80459B88.hats[FTKIND_LUIGI];
    fp->dynamics_num = hat->hat_dynamics[1]->dynamicsNum;
    if (fp->dynamics_num >= Ft_Dynamics_NumMax) {
        OSReport("fighter dynamics num over!\n");
        __assert(__FILE__, 388, "fp->dynamics_num < Ft_Dynamics_NumMax");
    }
    {
        ssize_t i;
        for (i = 0; i < fp->dynamics_num; i++) {
            BoneDynamicsDesc* article =
                &hat->hat_dynamics[1]->ftDynamicBones->array[i];
            HSD_JObj* cur = fp->fv.kb.hat.jobj;
            {
                ssize_t j;
                for (j = article->bone_id; j > 0; j--) {
                    if (cur->child != NULL) {
                        cur = cur->child;
                        continue;
                    }
                    while (cur->next == NULL) {
                        cur = cur->parent;
                    }
                    cur = cur->next;
                }
            }
            lb_8000FD48(cur, &fp->dynamic_bone_sets[i].dyn_desc,
                        article->dyn_desc.count);
            fp->dynamic_bone_sets[i].bone_id = FtPart_TopN;
            lb_80011710(
                &hat->hat_dynamics[1]->ftDynamicBones->array[i].dyn_desc,
                &fp->dynamic_bone_sets[i].dyn_desc);
        }
    }
}

void ftCo_8009DA38(Fighter* fp)
{
    KirbyHatStruct* hat = ft_80459B88.hats[FTKIND_GANON];
    fp->dynamics_num = hat->hat_dynamics[1]->dynamicsNum;
    if (fp->dynamics_num >= Ft_Dynamics_NumMax) {
        OSReport("fighter dynamics num over!\n");
        __assert(__FILE__, 421, "fp->dynamics_num < Ft_Dynamics_NumMax");
    }
    {
        ssize_t i;
        for (i = 0; i < fp->dynamics_num; i++) {
            BoneDynamicsDesc* article =
                &hat->hat_dynamics[1]->ftDynamicBones->array[i];
            HSD_JObj* cur = fp->fv.kb.hat.jobj;
            ssize_t j;
            for (j = article->bone_id; j > 0; j--) {
                if (cur->child != NULL) {
                    cur = cur->child;
                    continue;
                }
                while (cur->next == NULL) {
                    cur = cur->parent;
                }
                cur = cur->next;
            }
            lb_8000FD48(cur, &fp->dynamic_bone_sets[i].dyn_desc,
                        article->dyn_desc.count);
            fp->dynamic_bone_sets[i].bone_id = FtPart_TopN;
            lb_80011710(
                &hat->hat_dynamics[1]->ftDynamicBones->array[i].dyn_desc,
                &fp->dynamic_bone_sets[i].dyn_desc);
        }
    }
}

/// #ftCo_8009DB50

static inline bool inlineA0(Fighter* fp)
{
    u32 temp_r0 = fp->x619_costume_id;
    if (temp_r0 == 2) {
        return 0;
    }
    if (temp_r0 == 3) {
        return 1;
    }
    return 3;
}

void ftCo_8009DC54(Fighter* fp)
{
    ftData* data = fp->ft_data;
    ssize_t idx;
    if (fp->x619_costume_id == 2) {
        idx = 0;
    } else if (fp->x619_costume_id == 3) {
        idx = 1;
    } else {
        return;
    }
    fp->dynamics_num = 3;
    if (fp->dynamics_num >= Ft_Dynamics_NumMax) {
        OSReport("fighter dynamics num over!\n");
        __assert(__FILE__, 490, "fp->dynamics_num < Ft_Dynamics_NumMax");
    }
    {
        ssize_t i;
        for (i = 0; i < 2; i++) {
            HSD_JObj* cur = fp->fv.kb.hat.jobj;
            BoneDynamicsDesc* bones =
                &data->x2C->ftDynamicBones->array[idx * 2 + i];
            ssize_t j;
            for (j = 0; j < (signed) bones->bone_id; j++) {
                if (cur->child != NULL) {
                    cur = cur->child;
                    continue;
                }
                while (cur->next == NULL) {
                    cur = cur->parent;
                }
                cur = cur->next;
            }
            {
                DynamicsDesc* desc = &fp->dynamic_bone_sets[i + 1].dyn_desc;
                lb_8000FD48(cur, desc, bones->bone_id);
                fp->dynamic_bone_sets[i + 1].bone_id = FtPart_TopN;
                lb_80011710(&data->x2C->ftDynamicBones->array[i + 4].dyn_desc,
                            desc);
            }
        }
    }
}

void ftCo_8009DB50(Fighter* fp)
{
    KirbyHatStruct* hat = ft_80459B88.hats[FTKIND_PURIN];
    PAD_STACK(2 * 4);
    fp->dynamics_num = hat->hat_dynamics[4]->dynamicsNum;
    if (fp->dynamics_num >= Ft_Dynamics_NumMax) {
        OSReport("fighter dynamics num over!\n");
        __assert("ftdynamics.c", 455, "fp->dynamics_num < Ft_Dynamics_NumMax");
    }
    {
        ssize_t i;
        for (i = 0; i < fp->dynamics_num; i++) {
            BoneDynamicsDesc* desc =
                &hat->hat_dynamics[4]->ftDynamicBones->array[i];
            fp->parts[desc->bone_id].flags_b0 = true;
            lb_8000FD48(fp->parts[desc->bone_id].joint,
                        &fp->dynamic_bone_sets[i].dyn_desc,
                        desc->dyn_desc.count);
            fp->dynamic_bone_sets[i].bone_id = FtPart_TopN;
            lb_80011710(
                &hat->hat_dynamics[4]->ftDynamicBones->array[i].dyn_desc,
                &fp->dynamic_bone_sets[i].dyn_desc);
        }
    }
}

static inline bool inlineB0(Fighter* fp)
{
    if (!(fp->x34_scale.y < 1.0f)) {
        return 0;
    }
    if (fp->x34_scale.y > 1.0f) {
        if (fp->kind == FTKIND_MEWTWO) {
            if (fp->motion_id < 0xDF || fp->motion_id > 0xE8) {
                return 1;
            }
        }
        if (fp->ground_or_air == GA_Air || fp->kind == FTKIND_KOOPA) {
            return 0;
        }
        if (fp->kind != FTKIND_GKOOPS) {
            return 1;
        }
    }
    return 1;
}

void ftCo_8009DD94(Fighter_GObj* gobj, bool arg1)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ssize_t dynamics_num = fp->dynamics_num;
    if (dynamics_num != 0 && stage_info.internal_stage_id == FLATZONE) {
        HSD_JObjSetupMatrix(GET_JOBJ(gobj));
    }
    {
        bool ret_B0 = inlineB0(fp);
        ftColl_8007AF60(gobj);
        ftCo_8009E614(fp);
        if (fp->kind == FTKIND_PEACH) {
            ssize_t i;
            for (i = 0; i < (dynamics_num - 1); i++) {
                lb_8001044C(&fp->dynamic_bone_sets[i].dyn_desc, &fp->x1670,
                            fp->x166C, fp->cur_pos.y, arg1,
                            fp->dynamic_bone_sets[i].bone_id, 3, ret_B0);
            }
            lb_8001044C(&fp->dynamic_bone_sets[i].dyn_desc, &fp->x1670,
                        fp->x166C, fp->cur_pos.y, arg1,
                        fp->dynamic_bone_sets[i].bone_id, 0, ret_B0);
        } else if (fp->kind == FTKIND_MEWTWO) {
            ssize_t i;
            for (i = 0; i < dynamics_num; i++) {
                lb_8001044C(&fp->dynamic_bone_sets[i].dyn_desc, &fp->x1670,
                            fp->x166C, fp->cur_pos.y, arg1,
                            fp->dynamic_bone_sets[i].bone_id, 8, ret_B0);
            }
        } else {
            ssize_t i = 0;
            for (i = 0; i < dynamics_num; i++) {
                lb_8001044C(&fp->dynamic_bone_sets[i].dyn_desc, &fp->x1670,
                            fp->x166C, fp->cur_pos.y, arg1,
                            fp->dynamic_bone_sets[i].bone_id, 0, ret_B0);
            }
        }
    }
    if (dynamics_num != 0 && stage_info.internal_stage_id != FLATZONE) {
        ssize_t i;
        HSD_JObjSetupMatrix(GET_JOBJ(gobj));
        for (i = 0; i < dynamics_num; i++) {
            HSD_JObj* cur;
            for (cur = fp->dynamic_bone_sets[i].dyn_desc.data->jobj;
                 cur != NULL; cur = cur->child)
            {
                HSD_JObjSetupMatrix(cur);
            }
        }
    }
}

void ftCo_8009E0A8(Fighter_GObj* gobj)
{
    ftCo_8009DD94(gobj, GET_FIGHTER(gobj)->x2228_b1);
}

void ftCo_UnloadDynamicBones(Fighter* fp)
{
    ssize_t i;
    for (i = 0; i < fp->dynamics_num; i++) {
        lb_8000FD18(&fp->dynamic_bone_sets[i].dyn_desc);
    }
    fp->dynamics_num = 0;
}

void ftCo_8009E140(Fighter* fp, bool arg1)
{
    ssize_t i;
    PAD_STACK(2 * 4);
    if (fp->kind == FTKIND_KIRBY) {
        return;
    }
    if (fp->kind == FTKIND_PURIN) {
        ftCo_8009CB40(fp, 0, arg1, 0);
        return;
    }
    for (i = 0; i < fp->dynamics_num; i++) {
        ftCo_8009CB40(fp, i, arg1, 0);
    }
}

HSD_JObj* ftCo_8009E1D4(HSD_JObj* arg0, HSD_JObj* arg1, HSD_JObj* arg2)
{
    HSD_JObj* temp;
    if (arg0 == arg2) {
        return arg1;
    }
    if (arg0->child != NULL) {
        temp = ftCo_8009E1D4(arg0->child, arg1->child, arg2);
        if (temp != NULL) {
            return temp;
        }
    }
    if (arg0->next != NULL) {
        temp = ftCo_8009E1D4(arg0->next, arg1->next, arg2);
        if (temp != NULL) {
            return temp;
        }
    }
    return NULL;
}

enum_t ftCo_8009E318(Fighter_GObj* gobj, enum Fighter_Part arg1, f32 arg2)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_JObj* part_jobj = fp->parts[arg1].joint;
    ssize_t i;
    for (i = 0; i < fp->dynamics_num; i++) {
        ssize_t j;
        struct DynamicsData* cur;
        for (cur = fp->dynamic_bone_sets[i].dyn_desc.data, j = 0; cur != NULL;
             cur = cur->next, j++)
        {
            if (cur->jobj == part_jobj) {
                if (fp->parts[arg1].flags_b0) {
                    fp->parts[arg1].flags_b0 = false;
                    fp->dynamic_bone_sets[i].bone_id = j + 1;
                    goto exit_true;
                } else {
                    fp->parts[arg1].flags_b0 = true;
                    fp->dynamic_bone_sets[i].bone_id = j;
                    goto exit_false;
                }
            }
        }
    }
    return -1;
exit_true: {
    if (fp->x590 != 0) {
        ftAnim_8006EED4(fp, arg1, fp->x590, arg2, fp->frame_speed_mul);
    }
    return 0;
}
exit_false: {
    HSD_JObj* walk_jobj =
        ftCo_8009E1D4(GET_JOBJ(gobj), fp->x8AC_animSkeleton, part_jobj);
    ftAnim_80070758(part_jobj);
    ftAnim_80070758(walk_jobj);
    return 0;
}
}

void ftCo_8009E4A8(Fighter* fp)
{
    float cur_anim_frame = fp->cur_anim_frame;
    float frame_speed_mul = fp->frame_speed_mul;
    if (fp->x594_b4) {
        Fighter_Part part = fp->ft_data->x2C->x10[fp->x28[fp->anim_id * 2]];
        if (part != (unsigned) FtPart_TopN) {
            ssize_t i;
            for (i = 0; i < fp->dynamics_num; i++) {
                ftCo_8009CB40(fp, i, 1, part);
                if (fp->x590 != 0) {
                    ftAnim_8006EED4(
                        fp, fp->ft_data->x2C->ftDynamicBones->array[i].bone_id,
                        part, cur_anim_frame, frame_speed_mul);
                }
            }
        }
    } else {
        if (fp->x594_b3) {
            ssize_t i;
            for (i = 0; i < fp->dynamics_num; i++) {
                ftCo_8009CB40(fp, i, 0, 0);
                if (fp->x590 != 0) {
                    ftAnim_8006EED4(
                        fp, fp->ft_data->x2C->ftDynamicBones->array[i].bone_id,
                        fp->x590, cur_anim_frame, frame_speed_mul);
                }
            }
        }
    }
}

void ftCo_8009E614(Fighter* fp)
{
    if ((fp->kind == FTKIND_MARS || fp->kind == FTKIND_EMBLEM) &&
        !fp->x2227_b6)
    {
        int x = lb_80011ABC();
        if (x == -1) {
            ftCo_8009E4A8(fp);
            return;
        }
        if (x == +1) {
            ssize_t i;
            ftData* data = fp->ft_data;
            float frame_speed_mul, cur_anim_frame;
            cur_anim_frame = fp->cur_anim_frame;
            frame_speed_mul = fp->frame_speed_mul;
            if (fp->x594_b4 || fp->x594_b3) {
                for (i = 0; i < data->x2C->dynamicsNum; i++) {
                    ftCo_8009CB40(fp, i, 1, 0);
                }
                if (fp->x590 != 0) {
                    ftAnim_8006EBE8(fp->gobj, cur_anim_frame, frame_speed_mul,
                                    0.0f);
                    ftAnim_8006E9B4(fp->gobj);
                }
            }
        }
    }
}

bool ftCo_8009E714(Fighter_GObj* gobj, Fighter_Part bone_id, int arg2, float x,
                   float y, float arg5, float arg6, float arg7)
{
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    HSD_JObj* jobj = fp->parts[bone_id].joint;
    int var_r31 = arg2;
    Vec3 out_vec;
    Vec3 in_vec;
    in_vec.x = x;
    in_vec.y = y;
    in_vec.z = 0.0f;
    lb_8000B1CC(jobj, &in_vec, &out_vec);
    if (var_r31 < 0) {
        var_r31 = 120;
    }
    lb_800119DC(&out_vec, var_r31, arg5, arg6, arg7);
    return 0;
}

/// #ftCo_8009E7B4

void ftCo_8009EAF8(ftCo_GObj* gobj)
{
    Ground_801C4E20();
}
