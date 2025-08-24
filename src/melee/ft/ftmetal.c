#include "ftmetal.h"

#include <melee/ft/fighter.h>
#include <melee/ft/ft_081B.h>
#include <melee/ft/ftanim.h>
#include <melee/ft/ftchangeparam.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/ftmaterial.h>
#include <melee/ft/ftparts.h>
#include <melee/ft/types.h>
#include <melee/lb/lb_00B0.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/id.h>

static s8 ftCo_804D3C90 = 0;

void ft_800C8170(Fighter* fp)
{
    int i;
    HSD_JObj* jobj;
    HSD_DObj* dobj;
    HSD_MObj* mobj;
    u32 flags;

    PAD_STACK(8);

    for (i = 0; i < ftPartsTable[fp->kind]->parts_num; i++) {
        if (fp->parts[i].flags_b1) {
            FighterBone* bone = &fp->parts[i];
            jobj = bone->joint;
            dobj = HSD_JObjGetDObj(jobj);
            flags = 0;
            if (bone->flags_b7) {
                flags |= JOBJ_LIGHTING;
            }
            if (bone->flags2_b0) {
                flags |= JOBJ_TEXGEN;
            }
            if (bone->flags2_b1) {
                flags |= JOBJ_SPECULAR;
            }
            if (bone->flags2_b2) {
                flags |= JOBJ_UNK_B18;
            }
            if (bone->flags2_b3) {
                flags |= JOBJ_UNK_B20;
            }
            if (bone->flags2_b4) {
                flags |= JOBJ_UNK_B19;
            }
            HSD_JObjClearFlags(jobj, 0x50180);
            HSD_JObjSetFlags(jobj, flags);
            while (dobj != NULL) {
                if (dobj != NULL) {
                    mobj = dobj->mobj;
                } else {
                    mobj = NULL;
                }
                switch (mobj->rendermode & RENDER_BLENDING) {
                case 0:
                    HSD_DObjModifyFlags(dobj, 2, 0xE);
                    break;
                case RENDER_XLU:
                    HSD_DObjModifyFlags(dobj, 8, 0xE);
                    break;
                case RENDER_XLU | RENDER_NO_ZUPDATE:
                    HSD_DObjModifyFlags(dobj, 4, 0xE);
                    break;
                default:
                    OSReport("mobj has unexpected blending flags (0x%x).",
                             dobj->mobj->rendermode);
                    HSD_Panic("ftmetal.c", 0x73, "");
                    break;
                }
                dobj = dobj != NULL ? dobj->next : NULL;
            }
        }
    }
}

static inline void enableMetal(Fighter* fp)
{
    HSD_DObj* dobj;
    int i;
    HSD_JObj* jobj;

    for (i = 0; i < ftPartsTable[fp->kind]->parts_num; i++) {
        if (fp->parts[i].flags_b1) {
            jobj = fp->parts[i].joint;
            dobj = HSD_JObjGetDObj(jobj);
            HSD_JObjSetFlags(jobj, 0x50180);
            HSD_JObjClearFlags(jobj, 0x180000);
            while (dobj != NULL) {
                HSD_DObjModifyFlags(dobj, 2, 0xE);
                dobj = dobj != NULL ? dobj->next : NULL;
            }
        }
    }
    ftCommon_80080460(fp);
}

void ftCo_800C8348(Fighter_GObj* arg0, int timer, int health)
{
    Fighter* fp = GET_FIGHTER(arg0);

    PAD_STACK(0x10);

    fp->metal_timer = timer;
    fp->metal_health = health;

    if (fp->is_metal) {
        return;
    }
    fp->is_metal = true;

    enableMetal(fp);
}

void ftCo_800C8438(Fighter_GObj* gobj)
{
    Fighter* fp;

    PAD_STACK(0x10);

    fp = GET_FIGHTER(gobj);
    fp->is_metal = fp->is_always_metal;
    fp->metal_timer = 0;
    fp->metal_health = 0;
    if (!fp->is_metal) {
        return;
    }

    enableMetal(fp);

    ftCo_800D105C(gobj);
    ft_80081C88(gobj, fp->x34_scale.y);
}

void ftCo_800C8540(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->metal_timer = 0;
    fp->metal_health = 0;
    if (!fp->is_always_metal) {
        fp->is_metal = false;
        ftCo_800D105C(gobj);
        ft_80081C88(gobj, fp->x34_scale.y);
        ft_800C8170(fp);
        ftCommon_80080474(fp);
    }
}

static inline HSD_DObj* dobj_next(HSD_DObj* dobj)
{
    if (dobj != NULL) {
        return dobj->next;
    }
    return NULL;
}

void ft_800C85B8(Fighter_GObj* gobj)
{
    u8 _[8];
    HSD_Joint* sp20;
    s32 sp1C;

    Fighter* temp_r28;
    u32 var_r27;
    int var_r26;
    HSD_JObj* temp_r25;
    int var_r24;
    HSD_DObj* var_r24_2;
    HSD_Joint* temp_r23;
    int i;
    HSD_DObj* var_r21;

    PAD_STACK(8);

    var_r26 = 0;
    temp_r28 = GET_FIGHTER(gobj);
    temp_r23 = temp_r28->ft_data->x5C;
    sp20 = temp_r23;
    sp1C = 0;
    i = 0;
    while (sp20 != 0) {
        if (ftParts_8007506C(temp_r28->kind, i) != 0) {
            i++;
        } else {
            HSD_IDInsertToTable(NULL, (u32) sp20, temp_r28->parts[i].joint);
            i++;
            ftAnim_GetNextJointInTree(&sp20, &sp1C);
        }
    }
    var_r27 = 0;
    sp20 = temp_r23;
    sp1C = 0;
    while (sp20 != 0) {
        if (ftParts_8007506C(temp_r28->kind, var_r27) != 0) {
            var_r27 += 1;
        } else {
            i = 0;
            temp_r25 = temp_r28->parts[i].joint;
            var_r24_2 = HSD_DObjLoadDesc(sp20->u.dobjdesc);
            if (var_r24_2 != NULL) {
                var_r21 = HSD_JObjGetDObj(temp_r25);
                temp_r28->parts[i].flags2_b5 = true;
                HSD_DObjResolveRefsAll(var_r24_2, sp20->u.dobjdesc);
                if (var_r21 == NULL) {
                    HSD_JObjAddDObj(temp_r25, var_r24_2);
                } else {
                    while (var_r21 != NULL) {
                        if (!(var_r21 != NULL ? var_r21->next : NULL)) {
                            break;
                        }
                        var_r21 = var_r21 != NULL ? var_r21->next : NULL;
                    }
                    lb_8000CE30(var_r21, var_r24_2);
                }
                while (true) {
                    if (var_r24_2 == NULL) {
                        break;
                    }
                    if (var_r26 >= 0x20) {
                        OSReport("fighter parts model dobj num over!\n");
                        __assert("ftmetal.c", 0xF8, "0");
                    }
                    temp_r28->x2040[var_r26] = var_r24_2;
                    {
                        HSD_MObj* mobj = var_r24_2->mobj;
                        if (mobj != NULL) {
                            hsdChangeClass(mobj, &ftMObj);
                        }
                    }
                    var_r24_2 = var_r24_2 != NULL ? var_r24_2->next : NULL;
                    var_r26++;
                    i++;
                }
                if (i >= 0x80) {
                    OSReport("fighter dobj num over!\n");
                    __assert("ftmetal.c", 0x106, "0");
                }
                temp_r28->parts[i].xD = var_r26 - 1;
                temp_r28->parts[i].flags2_b6 = true;
            }
            var_r27 += 1;
            ftAnim_GetNextJointInTree(&sp20, &sp1C);
        }
    }
    temp_r28->x203C = var_r26;
}
