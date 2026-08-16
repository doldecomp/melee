#include "ftKb_Init.static.h"

#include "ftkirby.h"
#include "ftkirbyspecialdonkey.h"
#include "ftkirbyspecialiceclimber.h"
#include "ftkirbyspecialpeach.h"

#include "ef/efasync.h"
#include "ft/chara/ftKirby/ftkirbyspecialmewtwo.h"
#include "ft/fighter.h"
#include "ft/ft_0877.h"
#include "ft/ftanim.h"
#include "ft/ftdynamics.h"
#include "ft/ftmaterial.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftKirby/ftkirbyspecialgamewatch.h"
#include "it/it_26B1.h"
#include "lb/lb_00B0.h"
#include "lb/lbarchive.h"
#include "lb/lbdvd.h"
#include "pl/player.h"

#include <stddef.h>
#include <baselib/gobj.h>
#include <baselib/id.h>
#include <baselib/jobj.h>

void ftAnim_80070458(Fighter* fp, CostumeTObjList*, u32 tobj_idx, float frame);
void fn_800F9260(HSD_GObj*);
void ftCommon_8007D9A0(Fighter* fp);
void fn_8010B1F4(Fighter_GObj*);
static void fn_801095DC(HSD_GObj*);
static void fn_80109680(HSD_GObj*);
static void fn_80109714(HSD_GObj*);
static void fn_801097B8(HSD_GObj*);
void fn_800F64C8(Fighter_GObj*, float);

#pragma force_active on
char ftKb_Init_assert_msg_0[] = "fighter parts model dobj num over!\n";
char ftKb_Init_assert_msg_1[] = "ftkirby.c";
char ftKb_Init_assert_msg_2[] = "fighter dobj num over!\n";
#pragma force_active reset

void ftKb_SpecialN_800EEC34(int arg0, int arg1, int arg2)
{
    int i;
    int lo;

    if (ftKb_Init_803CA9D0[arg0].filename != NULL) {
        lbDvd_800178E8(2, ftKb_Init_803CA9D0[arg0].filename, 4, 4, 0, 1, 3, 1,
                       0);
    }
    if (ftKb_Init_803CB3E8[arg0] != NULL) {
        if (arg1 == 0xFF) {
            lo = 0;
        } else {
            lo = arg1;
            arg2 = arg1 + 1;
        }
        for (i = lo; i < arg2; i++) {
            if (ftKb_Init_803CB3E8[arg0][i].dat_filename != NULL) {
                lbDvd_800178E8(2, ftKb_Init_803CB3E8[arg0][i].dat_filename, 4,
                               4, 0, 1, 3, 1, 0);
            }
        }
    }
    if (ftKb_Init_803CB46C[arg0] != -1) {
        efAsync_LoadAsync(ftKb_Init_803CB46C[arg0]);
    }
}

void ftKb_SpecialN_800EED50(s32 arg0, s32 arg1)
{
    ftKirby_CostumeArchive* item;
    Fighter_CostumeStrings* costumes;
    Fighter_CostumeStrings* cs;

    if (arg0 != -1 && arg0 != 4) {
        if (ftKb_Init_803CA9D0[arg0].filename != NULL) {
            if (((HSD_Archive**) &ft_80459B88)[arg0] == NULL) {
                lbArchive_80017040(NULL, ftKb_Init_803CA9D0[arg0].filename,
                                   &((HSD_Archive**) &ft_80459B88)[arg0],
                                   ftKb_Init_803CA9D0[arg0].name, 0);
            }
        }
        if (ftKb_Init_803CB3E8[arg0] != NULL) {
            item = &ftKb_Init_803C9FC8[arg0][arg1];
            if (item->joint == NULL) {
                costumes = ftKb_Init_803CB3E8[arg0];
                cs = &costumes[arg1];
                if (cs->matanim_joint_name != NULL) {
                    lbArchive_80017040(NULL, costumes[arg1].dat_filename, item,
                                       cs->joint_name, &item->matanim,
                                       cs->matanim_joint_name, 0);
                } else {
                    lbArchive_80017040(NULL, costumes[arg1].dat_filename, item,
                                       cs->joint_name, 0);
                    item->matanim = NULL;
                }
            }
        }
        efAsync_LoadSync((u8) ftKb_Init_803CB46C[arg0]);
    }
}

void ftKb_Init_UnkMotionStates5(void)
{
    Player_80031DC8(ftKb_SpecialN_800EED50);
}

void ftKb_SpecialN_800EEEC4(HSD_GObj* gobj, FighterKind kind)
{
    HSD_GObjEvent cb;

    if ((cb = ftKb_Init_803C9CC8[kind * 2 + 1]) != NULL) {
        cb(gobj);
    }
}

/// #ftKb_SpecialN_800EEEC4

void ftKb_UnkMtxFunc0(Fighter_GObj* gobj, int arg1, Mtx mtx)
{
    Fighter* fp = gobj->user_data;

    if (fp->u.kb.hat.jobj == NULL) {
        return;
    }
    if (!fp->x2225_b2) {
        return;
    }

    {
        MtxPtr bone_mtx = HSD_JObjGetMtxPtr(fp->parts[6].joint);
        HSD_JObj* jobj = fp->u.kb.hat.jobj;
        HSD_JObjCopyMtx(fp->u.kb.hat.jobj, bone_mtx);
        jobj->flags |=
            JOBJ_USER_DEF_MTX | JOBJ_MTX_INDEP_PARENT | JOBJ_MTX_INDEP_SRT;
        HSD_JObjSetMtxDirty(jobj);
        HSD_JObjDispAll(fp->u.kb.hat.jobj, mtx, HSD_GObj_80390EB8(arg1), 0);
    }
    PAD_STACK(8);
}

HSD_JObj* ftKb_Init_UnkMotionStates6(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->u.kb.hat.jobj) {
        return fp->u.kb.hat.jobj;
    }

    /// @todo What???
    return (HSD_JObj*) gobj;
}

void ftKb_SpecialN_800EF040(Fighter_GObj* gobj, int arg1, KirbyHatStruct* hat)
{
    u32 mask = (u32) hat->hat_dynamics[1];
    if (mask != 0) {
        Fighter* fp = GET_FIGHTER(gobj);
        struct Fighter_804D6540_t* ft_data = Fighter_804D6540[fp->kind];
        int count = ft_data->x4;
        HSD_Joint* joint = ftKb_Init_803C9FC8[arg1][fp->x619_costume_id].joint;
        struct Fighter_804D6540_x0_t* parts = ft_data->x0;
        int i;
        for (i = 0; i < count; i++, parts++) {
            if ((1 << i) & mask) {
                ftParts_800753D4(fp, parts, joint);
            }
        }
    }
}

char ftKb_Init_804D3DAC[2] = "0";

typedef struct ftKirbyCopyData {
    u8 pad_0[0x1C60];
    ftKirby_CostumeArchive* costume_archives[FTKIND_MAX];
    u8 pad_1CE4[0xB8];
    char parts_dobj_over[0x24];
    char source_name[0xC];
    char fighter_dobj_over[0x18];
} ftKirbyCopyData;

/// @todo `byte_base` is always zero; it reproduces retail's shift-derived
/// offset initialization, suggesting the original code indexed bones by
/// element index rather than byte offset.
static inline void ftKb_SpecialN_800EF0E4_insert_joint_refs(
    s32* total_dobjs, HSD_Joint* root, Fighter* fp, s32* part_off,
    HSD_Joint** joint, s32* joint_idx, s32* byte_base)
{
    *part_off = (*byte_base = (*total_dobjs = 0)) << 4;
    *joint = root;
    *joint_idx = 0;
    while (*joint != NULL) {
        FighterBone* parts = fp->parts;
        FighterBone* bone = (FighterBone*) ((u8*) parts + *part_off);
        while (!bone->flags_b1) {
            bone = (FighterBone*) ((u8*) bone + 0x10);
            *part_off += 0x10;
        }
        HSD_IDInsertToTable(NULL, (u32) *joint,
                            ((FighterBone*) ((u8*) parts + *part_off))->joint);
        *part_off += 0x10;
        ftAnim_GetNextJointInTree(joint, joint_idx);
    }
    *joint = root;
}

static inline void ftKb_SpecialN_800EF0E4_finish(Fighter* fp, s32 total_dobjs)
{
    fp->u.gw.x2240_chefVar1 = total_dobjs;
    ftPartsPObjClearDefaultClass();
    PAD_STACK(4);
}

void ftKb_SpecialN_800EF0E4(Fighter_GObj* gobj, int arg1, u8* arg2)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKirbyCopyData* data = (ftKirbyCopyData*) ftKb_Init_MotionStateTable;
    s32 dst_off;
    s32 total_dobjs;
    HSD_DObj** dst;
    HSD_JObj* jobj;
    HSD_DObj* dobj;
    HSD_Joint* current_joint;
    s32 byte_off;
    HSD_Joint* root;
    s32 joint_idx;
    s32 byte_base;
    HSD_MObj* mobj;
    HSD_DObj* tail;

    ftPartsPObjSetDefaultClass();
    root = data->costume_archives[arg1][fp->x619_costume_id].joint;
    ftKb_SpecialN_800EF0E4_insert_joint_refs(&total_dobjs, root, fp, &byte_off,
                                             &current_joint, &joint_idx,
                                             &byte_base);
    {
        s32 group_count;
        u8* arg2_cur;
        s32 part_off;

        joint_idx = 0;
        arg2_cur = arg2;
        byte_off = byte_base << 2;
        part_off = 0;
        while (current_joint != NULL) {
            FighterBone* parts_base = fp->parts;
            FighterBone* parts = parts_base;
            FighterBone* bone;
            group_count = 0;
            bone = (FighterBone*) ((u8*) parts + part_off);
            while (!bone->flags_b1) {
                bone = (FighterBone*) ((u8*) bone + 0x10);
                arg2_cur++;
                part_off += 0x10;
            }
            jobj = ((FighterBone*) ((u8*) parts + part_off))->joint;
            dobj = HSD_DObjLoadDesc(current_joint->u.dobjdesc);
            *arg2_cur = total_dobjs;
            if (dobj != NULL) {
                tail = HSD_JObjGetDObj(jobj);
                HSD_DObjResolveRefsAll(dobj, current_joint->u.dobjdesc);
                if (tail == NULL) {
                    HSD_JObjAddDObj(jobj, dobj);
                } else {
                    while (tail != NULL) {
                        HSD_DObj* nxt = (tail != NULL) ? tail->next : NULL;
                        if (nxt == NULL) {
                            break;
                        }
                        tail = (tail != NULL) ? tail->next : NULL;
                    }
                    lb_8000CE30(tail, dobj);
                }
                dst_off = byte_off;
                for (;;) {
                    if (dobj == NULL) {
                        break;
                    }
                    if (total_dobjs >= 0x20) {
                        OSReport(data->parts_dobj_over);
                        __assert(data->source_name, 0x43E, ftKb_Init_804D3DAC);
                    }
                    dst = (HSD_DObj**) fp->u.gw.x2244_chefVar2;
                    *(HSD_DObj**) ((u8*) dst + dst_off) = dobj;
                    mobj = dobj->mobj;
                    if (mobj != NULL) {
                        hsdChangeClass(mobj, &ftMObj);
                    }
                    dobj = (dobj != NULL) ? dobj->next : NULL;
                    dst_off += 4;
                    byte_off += 4;
                    total_dobjs += 1;
                    group_count += 1;
                }
                if (group_count >= 0x80) {
                    OSReport(data->fighter_dobj_over);
                    __assert(data->source_name, 0x44C, ftKb_Init_804D3DAC);
                }
                ((FighterBone*) ((u8*) fp->parts + part_off))->flags_b6 = true;
            }
            arg2_cur++;
            part_off += 0x10;
            ftAnim_GetNextJointInTree(&current_joint, &joint_idx);
        }
    }
    ftKb_SpecialN_800EF0E4_finish(fp, total_dobjs);
}

void ftKb_SpecialN_800EF35C(Fighter_GObj* gobj, int arg1, u8* arg2)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKirby_CostumeArchive* costume_data = ftKb_Init_803C9FC8[arg1];
    HSD_MatAnimJoint* matanimjoint = costume_data[fp->x619_costume_id].matanim;
    int idx = 0;
    arg1 = 0;
    PAD_STACK(4);
    while (matanimjoint != NULL) {
        if (ftParts_8007506C(fp->kind, arg1) != 0) {
            arg1++;
            arg2++;
        } else {
            if (matanimjoint->matanim != NULL) {
                HSD_DObjAddAnimAll(fp->u.kb.hat.x14.data[*arg2],
                                   matanimjoint->matanim, NULL);
            }
            arg1++;
            arg2++;
            ftAnim_GetNextMatAnimJointInTree(&matanimjoint, &idx);
        }
    }
}

void ftKb_SpecialN_800EF438(Fighter_GObj* gobj, KirbyHatStruct* hat)
{
    HSD_Joint* current_joint;
    s32 joint_idx;
    HSD_Joint* root = (HSD_Joint*) hat->hat_dynamics[2];
    ftKirbyCopyData* data = (ftKirbyCopyData*) ftKb_Init_MotionStateTable;
    s32 byte_off;
    Fighter* fp = GET_FIGHTER(gobj);
    s32 total_dobjs;
    s32 insert_part_off;
    s32 dst_off;
    HSD_DObj* dobj;
    HSD_MObj* mobj;
    HSD_JObj* jobj;
    HSD_DObj* tail;
    s32 group_count;

    PAD_STACK(4);
    if (root != NULL) {
        s32 byte_base;
        s32 part_off;
        ftPartsPObjSetDefaultClass();
        ftKb_SpecialN_800EF0E4_insert_joint_refs(
            &total_dobjs, root, fp, &insert_part_off, &current_joint,
            &joint_idx, &byte_base);
        joint_idx = 0;
        byte_off = byte_base << 2;
        part_off = 0;
        while (current_joint != NULL) {
            group_count = 0;
            while (!((FighterBone*) ((u8*) fp->parts + part_off))->flags_b1) {
                part_off += 0x10;
            }
            jobj = ((FighterBone*) ((u8*) fp->parts + part_off))->joint;
            dobj = HSD_DObjLoadDesc(current_joint->u.dobjdesc);
            if (dobj != NULL) {
                tail = HSD_JObjGetDObj(jobj);
                ((FighterBone*) ((u8*) fp->parts + part_off))->flags2_b7 =
                    true;
                HSD_DObjResolveRefsAll(dobj, current_joint->u.dobjdesc);
                if (tail == NULL) {
                    HSD_JObjAddDObj(jobj, dobj);
                } else {
                    while (tail != NULL) {
                        HSD_DObj* nxt = (tail != NULL) ? tail->next : NULL;
                        if (nxt == NULL) {
                            break;
                        }
                        tail = (tail != NULL) ? tail->next : NULL;
                    }
                    lb_8000CE30(tail, dobj);
                }
                dst_off = byte_off;
                for (;;) {
                    HSD_DObj** dst;
                    if (dobj == NULL) {
                        break;
                    }
                    if (total_dobjs >= 0x20) {
                        OSReport(data->parts_dobj_over);
                        __assert(data->source_name, 0x4B9, ftKb_Init_804D3DAC);
                    }
                    dst = (HSD_DObj**) fp->u.gw.x224C_greenhouseGObj;
                    *(HSD_DObj**) ((u8*) dst + dst_off) = dobj;
                    mobj = dobj->mobj;
                    if (mobj != NULL) {
                        hsdChangeClass(mobj, &ftMObj);
                    }
                    dobj = (dobj != NULL) ? dobj->next : NULL;
                    dst_off += 4;
                    byte_off += 4;
                    total_dobjs += 1;
                    group_count += 1;
                }
                if (group_count >= 0x80) {
                    OSReport(data->fighter_dobj_over);
                    __assert(data->source_name, 0x4C7, ftKb_Init_804D3DAC);
                }
            }
            part_off += 0x10;
            ftAnim_GetNextJointInTree(&current_joint, &joint_idx);
        }
        fp->u.gw.x2248_manholeGObj = (HSD_GObj*) total_dobjs;
        ftPartsPObjClearDefaultClass();
    } else {
        *(s32*) fp->u.gw.x224C_greenhouseGObj = 0;
    }
}

/// @note The inline helper and the shared `fp->parts[i]` indexing are
/// required for register allocation: both bone accesses must share one
/// strength-reduced offset, and the helper materializes its Fighter* directly
/// into a saved register.
static inline void ftKb_RemoveHatParts(Fighter_GObj* gobj, u32 mask)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int i = Fighter_804D6540[fp->kind]->x4 - 1;
    for (; i >= 0; i--) {
        if ((1 << i) & mask) {
            ftParts_800755E8(fp, &Fighter_804D6540[fp->kind]->x0[i]);
        }
    }
}

void ftKb_SpecialN_800EF69C(Fighter_GObj* gobj, int arg1, KirbyHatStruct* hat)
{
    Fighter* fp;
    u32 mask;
    if ((u32) (fp = GET_FIGHTER(gobj))->u.gw.x2244_chefVar2 != 0U) {
        u32 i = 0;
        while (i < ftPartsTable[fp->kind]->parts_num) {
            FighterBone* bone = &fp->parts[i];
            HSD_JObj* jobj;
            HSD_DObj* dobj;
            jobj = bone->joint;
            dobj = (HSD_DObj*) jobj;
            if (jobj != NULL && (bone->flags_b6 || bone->flags2_b7)) {
                u8* b9p = &((u8*) bone)[9];
                if ((*b9p >> 1) & 1) {
                    if ((*b9p >> 2) & 1) {
                        dobj =
                            *(HSD_DObj**) ((u8*) fp->x203C.data +
                                           ((((u8*) bone)[0xD] * 2) & 0x1FC));
                    } else {
                        dobj =
                            *(HSD_DObj**) ((u8*) fp->dobj_list.data +
                                           ((((u8*) bone)[0xD] * 2) & 0x1FC));
                    }
                    HSD_DObjRemoveAll(dobj != NULL ? dobj->next : NULL);
                    lb_8000CE30(dobj, NULL);
                } else {
                    HSD_DObjRemoveAll(HSD_JObjGetDObj(jobj));
                    lb_8000CE40(jobj, NULL);
                }
                fp->parts[i].flags_b6 = fp->parts[i].flags2_b7 = false;
            }
            i += 1;
        }
        HSD_ObjFree(&fighter_x2040_alloc_data,
                    (void*) fp->u.gw.x2244_chefVar2);
        HSD_ObjFree(&fighter_x2040_alloc_data, fp->u.gw.x224C_greenhouseGObj);
        fp->u.gw.x2244_chefVar2 = 0;
    }
    mask = (u32) hat->hat_dynamics[1];
    if (mask != 0) {
        ftKb_RemoveHatParts(gobj, mask);
    }
}

void ftKb_UnkIntBoolFunc0(Fighter* fp, int arg1, bool arg2)
{
    if (fp->u.kb.hat.x14.data != NULL) {
        if (arg2) {
            if (fp->u.kb.hat.jobj != NULL) {
                ftParts_80074CA0(&fp->u.kb.hat.x24, arg1, &fp->u.kb.hat.x14);
                return;
            }
            {
                s32 var_r0;
                s8 idx = fp->x5F4_arr[0].idx;
                if (idx >= 2 && idx <= 6) {
                    var_r0 = 1;
                } else {
                    var_r0 = 0;
                }
                if (var_r0 != 0) {
                    ftParts_80074D7C(&fp->u.kb.hat.x24, arg1,
                                     &fp->u.kb.hat.x14);
                    return;
                }
            }
            if (arg1 == 2) {
                if (*fp->u.kb.hat.x1C.data != NULL) {
                    ftParts_80074D7C(&fp->x5AC, arg1, &fp->x203C);
                    ftParts_80074CA0(&fp->u.kb.hat.x24, arg1,
                                     &fp->u.kb.hat.x1C);
                }
            } else {
                ftParts_80074D7C(&fp->x5AC, arg1, &fp->dobj_list);
                ftParts_80074CA0(&fp->u.kb.hat.x24, arg1, &fp->u.kb.hat.x14);
            }
        } else {
            if (fp->u.kb.hat.jobj == NULL && arg1 == 2) {
                ftParts_80074D7C(&fp->u.kb.hat.x24, arg1, &fp->u.kb.hat.x1C);
                return;
            }
            ftParts_80074D7C(&fp->u.kb.hat.x24, arg1, &fp->u.kb.hat.x14);
        }
    }
}

void ftKb_Init_UnkCallbackPairs0_0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->u.kb.hat.x14.data != NULL && fp->u.kb.hat.jobj == NULL) {
        ftAnim_800705E0(&fp->u.kb.x44);
    }
}

void ftKb_Init_UnkCallbackPairs0_1(Fighter_GObj* gobj, int arg1, float arg2)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->u.kb.hat.x14.data != NULL && fp->u.kb.hat.jobj == NULL) {
        ftAnim_80070458(fp, &fp->u.kb.x44, arg1, arg2);
    }
}

void ftKb_SpecialN_800EFA40(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(4);
    if (fp->u.kb.hat.jobj == NULL) {
        Kirby_Unk* unk = ft_80459B88.x0;
        fp->u.kb.hat.x14.data = HSD_ObjAlloc(&fighter_x2040_alloc_data);
        ftPartsPObjSetDefaultClass();
        fp->u.kb.hat.jobj = HSD_JObjLoadJoint(unk->x0);
        fp->x2225_b2 = true;
        ftPartsPObjClearDefaultClass();
        ftParts_80075650(gobj, fp->u.kb.hat.jobj, &fp->u.kb.hat.x14);
        ftParts_8007487C(&unk->x4, &fp->u.kb.hat.x24, 0, &fp->u.kb.hat.x14,
                         &fp->u.kb.hat.x14);
    }
}

static inline void ftKb_SpecialN_800EFAF0_inline(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->u.kb.hat.jobj != NULL) {
        HSD_JObjRemoveAll(fp->u.kb.hat.jobj);
        fp->u.kb.hat.jobj = NULL;
        HSD_ObjFree(&fighter_x2040_alloc_data, fp->u.kb.hat.x14.data);
        fp->u.kb.hat.x14.data = NULL;
    }
}

void ftKb_SpecialN_800EFAF0(Fighter_GObj* gobj)
{
    ftKb_SpecialN_800EFAF0_inline(gobj);
}

static inline void ftKb_LoadHat(Fighter_GObj* gobj, Fighter* fp,
                                KirbyHatStruct* hat)
{
    fp->u.kb.hat.x14.data = HSD_ObjAlloc(&fighter_x2040_alloc_data);
    ftPartsPObjSetDefaultClass();
    fp->u.kb.hat.jobj = HSD_JObjLoadJoint(hat->hat_joint);
    fp->x2225_b2 = true;
    ftPartsPObjClearDefaultClass();
    ftParts_80075650(gobj, fp->u.kb.hat.jobj, &fp->u.kb.hat.x14);
    ftParts_8007487C(&hat->desc, &fp->u.kb.hat.x24, 0, &fp->u.kb.hat.x14,
                     &fp->u.kb.hat.x14);
}

void ftKb_SpecialN_800EFB4C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->u.kb.hat.jobj == NULL) {
        KirbyHatStruct** hats = ft_80459B88.hats;
        KirbyHatStruct* hat = hats[FTKIND_MARIO];
        ftKb_LoadHat(gobj, fp, hat);
    }
}

void ftKb_SpecialN_800EFBFC(Fighter_GObj* gobj)
{
    ftKb_SpecialN_800EFAF0_inline(gobj);
}

void ftKb_SpecialN_800EFC58(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->u.kb.hat.jobj == NULL) {
        KirbyHatStruct** hats = ft_80459B88.hats;
        KirbyHatStruct* hat = hats[FTKIND_FOX];
        ftKb_LoadHat(gobj, fp, hat);
    }
}

void ftKb_SpecialN_800EFD08(Fighter_GObj* gobj)
{
    ftKb_SpecialN_800EFAF0_inline(gobj);
}

void ftKb_SpecialN_800EFD64(Fighter_GObj* gobj)
{
    if (GET_FIGHTER(gobj)->u.kb.hat.jobj == NULL) {
        Fighter* fp = HSD_GObjGetUserData(gobj);
        KirbyHatStruct** hats = ft_80459B88.hats;
        KirbyHatStruct* hat = hats[FTKIND_KIRBY];
        ftKb_LoadHat(gobj, fp, hat);
        ftCo_8009D4D4(fp);
    }
}

void ftKb_SpecialN_800EFE1C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_SpecialN_800EFAF0_inline(gobj);
    ftCo_UnloadDynamicBones(fp);
}

void ftKb_SpecialN_800EFE80(Fighter_GObj* gobj)
{
    if (GET_FIGHTER(gobj)->u.kb.hat.jobj == NULL) {
        Fighter* fp = HSD_GObjGetUserData(gobj);
        KirbyHatStruct** hats = ft_80459B88.hats;
        KirbyHatStruct* hat = hats[FTKIND_KOOPA];
        ftKb_LoadHat(gobj, fp, hat);
        ftCo_8009D074(fp);
    }
}

void ftKb_SpecialN_800EFF38(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_SpecialN_800EFAF0_inline(gobj);
    ftCo_UnloadDynamicBones(fp);
}

void ftKb_SpecialN_800EFF9C(Fighter_GObj* gobj)
{
    if (GET_FIGHTER(gobj)->u.kb.hat.jobj == NULL) {
        Fighter* fp = HSD_GObjGetUserData(gobj);
        KirbyHatStruct** hats = ft_80459B88.hats;
        KirbyHatStruct* hat = hats[FTKIND_LINK];
        ftKb_LoadHat(gobj, fp, hat);
        ftCo_8009D704(fp);
    }
}

void ftKb_SpecialN_800F0054(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_SpecialN_800EFAF0_inline(gobj);
    ftCo_UnloadDynamicBones(fp);
}

void ftKb_SpecialN_800F00B8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->u.kb.hat.jobj == NULL) {
        KirbyHatStruct** hats = ft_80459B88.hats;
        KirbyHatStruct* hat = hats[FTKIND_SEAK];
        ftKb_LoadHat(gobj, fp, hat);
    }
}

void ftKb_SpecialN_800F0168(Fighter_GObj* gobj)
{
    ftKb_SpecialN_800EFAF0_inline(gobj);
}

void ftKb_SpecialN_800F01C4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->u.kb.hat.jobj == NULL) {
        KirbyHatStruct** hats = ft_80459B88.hats;
        KirbyHatStruct* hat = hats[FTKIND_NESS];
        ftKb_LoadHat(gobj, fp, hat);
    }
}

void ftKb_SpecialN_800F0274(Fighter_GObj* gobj)
{
    ftKb_SpecialN_800EFAF0_inline(gobj);
}

void ftKb_SpecialN_800F02D0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->u.kb.hat.jobj == NULL) {
        KirbyHatStruct** hats = ft_80459B88.hats;
        KirbyHatStruct* hat = hats[FTKIND_PEACH];
        ftKb_LoadHat(gobj, fp, hat);
    }
}

void ftKb_SpecialN_800F0380(Fighter_GObj* gobj)
{
    ftKb_SpecialN_800EFAF0_inline(gobj);
}

void ftKb_SpecialN_800F03DC(Fighter_GObj* gobj)
{
    if (GET_FIGHTER(gobj)->u.kb.hat.jobj == NULL) {
        Fighter* fp = HSD_GObjGetUserData(gobj);
        KirbyHatStruct** hats = ft_80459B88.hats;
        KirbyHatStruct* hat = hats[FTKIND_NANA];
        ftKb_LoadHat(gobj, fp, hat);
        ftCo_8009D2A4(fp);
    }
}

void ftKb_SpecialN_800F0494(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_SpecialN_800EFAF0_inline(gobj);
    ftCo_UnloadDynamicBones(fp);
}

void ftKb_SpecialN_800F04F8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->u.kb.hat.jobj == NULL) {
        KirbyHatStruct** hats = ft_80459B88.hats;
        KirbyHatStruct* hat = hats[FTKIND_PIKACHU];
        ftKb_LoadHat(gobj, fp, hat);
    }
}

void ftKb_SpecialN_800F05A8(Fighter_GObj* gobj)
{
    ftKb_SpecialN_800EFAF0_inline(gobj);
}

void ftKb_SpecialN_800F0604(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->u.kb.hat.jobj == NULL) {
        KirbyHatStruct** hats = ft_80459B88.hats;
        KirbyHatStruct* hat = hats[FTKIND_SAMUS];
        ftKb_LoadHat(gobj, fp, hat);
    }
}

void ftKb_SpecialN_800F06B4(Fighter_GObj* gobj)
{
    ftKb_SpecialN_800EFAF0_inline(gobj);
}

void ftKb_SpecialN_800F0710(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->u.kb.hat.jobj == NULL) {
        KirbyHatStruct** hats = ft_80459B88.hats;
        KirbyHatStruct* hat = hats[FTKIND_MEWTWO];
        ftKb_LoadHat(gobj, fp, hat);
    }
}

void ftKb_SpecialN_800F07C0(Fighter_GObj* gobj)
{
    ftKb_SpecialN_800EFAF0_inline(gobj);
}

void ftKb_SpecialN_800F081C(Fighter_GObj* gobj)
{
    if (((Fighter*) HSD_GObjGetUserData(gobj))->u.kb.hat.jobj == NULL) {
        Fighter* fp = HSD_GObjGetUserData(gobj);
        KirbyHatStruct** hats = ft_80459B88.hats;
        KirbyHatStruct* hat = hats[FTKIND_LUIGI];
        ftKb_LoadHat(gobj, fp, hat);
        ftCo_8009D920(fp);
    }
}

void ftKb_SpecialN_800F08D4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_SpecialN_800EFAF0_inline(gobj);
    ftCo_UnloadDynamicBones(fp);
}

void ftKb_SpecialN_800F0938(Fighter_GObj* gobj)
{
    if (GET_FIGHTER(gobj)->u.kb.hat.jobj == NULL) {
        Fighter* fp = HSD_GObjGetUserData(gobj);
        KirbyHatStruct** hats = ft_80459B88.hats;
        KirbyHatStruct* hat = hats[FTKIND_MARS];
        ftKb_LoadHat(gobj, fp, hat);
        ftCo_8009D5EC(fp);
    }
}

void ftKb_SpecialN_800F09F0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_SpecialN_800EFAF0_inline(gobj);
    ftCo_UnloadDynamicBones(fp);
}

void ftKb_SpecialN_800F0A54(Fighter_GObj* gobj)
{
    if (GET_FIGHTER(gobj)->u.kb.hat.jobj == NULL) {
        Fighter* fp = HSD_GObjGetUserData(gobj);
        KirbyHatStruct** hats = ft_80459B88.hats;
        KirbyHatStruct* hat = hats[FTKIND_ZELDA];
        ftKb_LoadHat(gobj, fp, hat);
        ftCo_8009D18C(fp);
    }
}

void ftKb_SpecialN_800F0B0C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_SpecialN_800EFAF0_inline(gobj);
    ftCo_UnloadDynamicBones(fp);
}

void ftKb_SpecialN_800F0B70(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->u.kb.hat.jobj == NULL) {
        KirbyHatStruct** hats = ft_80459B88.hats;
        KirbyHatStruct* hat = hats[FTKIND_CLINK];
        ftKb_LoadHat(gobj, fp, hat);
    }
}

void ftKb_SpecialN_800F0C20(Fighter_GObj* gobj)
{
    ftKb_SpecialN_800EFAF0_inline(gobj);
}

void ftKb_SpecialN_800F0C7C(Fighter_GObj* gobj)
{
    if (GET_FIGHTER(gobj)->u.kb.hat.jobj == NULL) {
        Fighter* fp = HSD_GObjGetUserData(gobj);
        KirbyHatStruct** hats = ft_80459B88.hats;
        KirbyHatStruct* hat = hats[FTKIND_FALCO];
        ftKb_LoadHat(gobj, fp, hat);
        ftCo_8009D3BC(fp);
    }
}

void ftKb_SpecialN_800F0D34(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_SpecialN_800EFAF0_inline(gobj);
    ftCo_UnloadDynamicBones(fp);
}

void ftKb_SpecialN_800F0D98(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->u.kb.hat.jobj == NULL) {
        KirbyHatStruct** hats = ft_80459B88.hats;
        KirbyHatStruct* hat = hats[FTKIND_GAMEWATCH];
        ftKb_LoadHat(gobj, fp, hat);
    }
}

void ftKb_SpecialN_800F0E48(Fighter_GObj* gobj)
{
    ftKb_SpecialN_800EFAF0_inline(gobj);
}

void ftKb_SpecialN_800F0EA4(Fighter_GObj* gobj)
{
    if (GET_FIGHTER(gobj)->u.kb.hat.jobj == NULL) {
        Fighter* fp = HSD_GObjGetUserData(gobj);
        KirbyHatStruct** hats = ft_80459B88.hats;
        KirbyHatStruct* hat = hats[FTKIND_GANON];
        ftKb_LoadHat(gobj, fp, hat);
        ftCo_8009DA38(fp);
    }
}

void ftKb_SpecialN_800F0F5C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_SpecialN_800EFAF0_inline(gobj);
    ftCo_UnloadDynamicBones(fp);
}
/// Shared body of the Kirby hat loaders: load the hat model/parts for
/// @p kind and start its animation.
/// @todo Should be an inline function (which would also allow removing the
/// callers' @c dont_inline pragmas), but that shifts register allocation.
#define LOAD_HAT(gobj, fp, fp2, kind, hat, part_dobj_indices)                 \
    do {                                                                      \
        (hat) = ft_80459B88.hats[kind];                                       \
        ftKb_SpecialN_800EF040(gobj, (kind) + 1, hat);                        \
        (fp2)->u.kb.hat.x14.data = HSD_ObjAlloc(&fighter_x2040_alloc_data);   \
        (fp2)->u.kb.hat.x1C.data = HSD_ObjAlloc(&fighter_x2040_alloc_data);   \
        ftKb_SpecialN_800EF0E4(gobj, (kind) + 1, part_dobj_indices);          \
        ftKb_SpecialN_800EF35C(gobj, (kind) + 1, part_dobj_indices);          \
        ftKb_SpecialN_800EF438(gobj, hat);                                    \
        ftParts_8007487C((FtPartsDesc*) (hat), &(fp)->u.kb.hat.x24,           \
                         (fp)->x619_costume_id, &(fp)->u.kb.hat.x14,          \
                         &(fp)->u.kb.hat.x1C);                                \
        ftAnim_80070200(fp, (ftData_x8_x8*) &(hat)->desc.vis_table,           \
                        &(fp)->u.kb.x44, &(fp)->u.kb.hat.x14);                \
    } while (0)

#pragma push
#pragma dont_inline on
void ftKb_SpecialN_800F0FC0(Fighter_GObj* gobj)
{
    u8 part_dobj_indices[0x90];
    Fighter* fp = fp = gobj->user_data;
    KirbyHatStruct* hat;
    PAD_STACK(8);
    if (fp->u.kb.hat.x14.data != NULL) {
        return;
    }
    LOAD_HAT(gobj, fp, fp, FTKIND_CAPTAIN, hat, part_dobj_indices);
}
#pragma pop

void ftKb_SpecialN_800F10A4(Fighter_GObj* gobj)
{
    ftKb_SpecialN_800EF69C(gobj, 3, ft_80459B88.hats[FTKIND_CAPTAIN]);
}

/// Load Yoshi's hat for Kirby copy ability.
/// @note The split Fighter* locals are required for register allocation.
#pragma push
#pragma dont_inline on
void ftKb_SpecialN_800F10D4(Fighter_GObj* gobj)
{
    u8 part_dobj_indices[0x88];
    Fighter* fp = gobj->user_data;
    Fighter* fp2 = gobj->user_data;
    KirbyHatStruct* hat;
    PAD_STACK(8);
    if (fp2->u.kb.hat.x14.data != NULL) {
        return;
    }
    LOAD_HAT(gobj, fp, fp2, FTKIND_YOSHI, hat, part_dobj_indices);
    ftCo_8009D81C(fp2);
}
#pragma pop

void ftKb_SpecialN_800F11AC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_SpecialN_800EF69C(gobj, 0xF, ft_80459B88.hats[14]);
    ftCo_UnloadDynamicBones(fp);
}

/// Load Jigglypuff's hat for Kirby copy ability.
/// @note The split Fighter* locals are required for register allocation.
#pragma push
#pragma dont_inline on
void ftKb_SpecialN_800F11F0(Fighter_GObj* gobj)
{
    u8 part_dobj_indices[0x88];
    Fighter* fp = gobj->user_data;
    Fighter* fp2 = gobj->user_data;
    KirbyHatStruct* hat;
    PAD_STACK(8);
    if (fp2->u.kb.hat.x14.data != NULL) {
        return;
    }
    LOAD_HAT(gobj, fp, fp2, FTKIND_PURIN, hat, part_dobj_indices);
    ftCo_8009DB50(fp2);
}
#pragma pop

void ftKb_SpecialN_800F12C8(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_SpecialN_800EF69C(gobj, 0x10, ft_80459B88.hats[FTKIND_PURIN]);
    ftCo_UnloadDynamicBones(fp);
}

/// Load Dr. Mario's hat for Kirby copy ability.
/// @note The self-assignment `fp = fp` is required for register allocation.
#pragma push
#pragma dont_inline on
void ftKb_SpecialN_800F130C(Fighter_GObj* gobj)
{
    u8 part_dobj_indices[0x90];
    Fighter* fp = fp = gobj->user_data;
    KirbyHatStruct* hat;
    PAD_STACK(8);
    if (fp->u.kb.hat.x14.data != NULL) {
        return;
    }
    LOAD_HAT(gobj, fp, fp, FTKIND_DRMARIO, hat, part_dobj_indices);
}
#pragma pop

void ftKb_SpecialN_800F13F0(Fighter_GObj* gobj)
{
    ftKb_SpecialN_800EF69C(gobj, 0x16, ft_80459B88.hats[FTKIND_DRMARIO]);
}

u8* ftKb_SpecialN_800F1420(Fighter_GObj* gobj, u32* arg1)
{
    Fighter* fp = GET_FIGHTER(gobj);
    FtPartsVisLookup* lookup = fp->x5AC.xC[4];
    int i;
    u8* p;
    for (i = 0; i < lookup->x0; i++) {
        int j;
        TempS* entry = &lookup->x4[i];
        p = entry->x4;

        for (j = 0; j < entry->x0; j++, p++) {
            HSD_DObj* dobj = fp->u.kb.hat.x14.data[*p];
            HSD_MObj* mobj;

            if (dobj != NULL) {
                mobj = dobj->mobj;
            } else {
                mobj = NULL;
            }

            if (mobj != NULL) {
                HSD_Material* mat = mobj->mat;
                if (mat != NULL) {
                    *(u32*) &mat->diffuse = *arg1;
                }
            }
        }
    }
    return p;
}

#pragma push
#pragma dont_inline on
void ftKb_SpecialN_800F14B4(Fighter_GObj* gobj)
{
    u8 part_dobj_indices[0x88];
    Fighter* fp = fp = gobj->user_data;
    KirbyHatStruct* hat;
    FtPartsVisLookup* lookup;
    PAD_STACK(8);
    if (fp->u.kb.hat.x14.data != NULL) {
        return;
    }
    LOAD_HAT(gobj, fp, fp, FTKIND_PICHU, hat, part_dobj_indices);
    lookup = (FtPartsVisLookup*) hat->hat_dynamics[3];
    fp->u.kb.hat.x24.xC[4] = lookup;
    fp->x5AC.xC[4] = lookup;
    ftParts_80074D7C(&fp->u.kb.hat.x24, 4, &fp->u.kb.hat.x14);
    ftKb_SpecialN_800F1420(gobj, (u32*) ((u8*) hat->hat_dynamics[4] + 4));
    *(u32*) &fp->x610_color_rgba[1] = *(u32*) ((u8*) hat->hat_dynamics[4] + 8);
    Fighter_UpdateModelScale(gobj);
}
#pragma pop

void ftKb_SpecialN_800F15D8(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    KirbyHatStruct* new_var;
    new_var = ft_80459B88.hats[FTKIND_PICHU];
    ftKb_SpecialN_800EF69C(gobj, 0x18, new_var);
    fp->x5AC.xC[4] = NULL;
    Fighter_UpdateModelScale(gobj);
}

/// #ftKb_SpecialN_Enter
void ftKb_SpecialN_Enter(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ftKb_Init_803C9DD0[fp->u.kb.hat.kind] != NULL) {
        ftKb_Init_803C9DD0[fp->u.kb.hat.kind](gobj);
    } else {
        ftKb_SpecialN_800F5F68(gobj);
    }
}

/// #ftKb_SpecialAirN_Enter
void ftKb_SpecialAirN_Enter(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ftKb_Init_803C9E54[fp->u.kb.hat.kind] != NULL) {
        ftKb_Init_803C9E54[fp->u.kb.hat.kind](gobj);
    } else {
        ftKb_SpecialN_800F6070(gobj);
    }
}

void ftKb_SpecialN_800F16D0(Fighter_GObj* gobj, FighterKind kind)
{
    struct ft_80459B88_t* g = &ft_80459B88;
    KirbyHatStruct* hat;
    PAD_STACK(8);

    switch (kind) {
    case FTKIND_MARIO:
        it_8026B3F8((Article*) g->x0->xC, It_Kind_Kirby_MarioFire);
        break;
    case FTKIND_LUIGI:
        it_8026B3F8((Article*) g->hats[16]->hat_dynamics[0],
                    It_Kind_Kirby_LuigiFire);
        break;
    case FTKIND_POPO:
        it_8026B3F8((Article*) g->hats[9]->hat_dynamics[0],
                    It_Kind_Kirby_IceClimberIce);
        break;
    case FTKIND_PEACH:
        hat = g->hats[8];
        it_8026B3F8((Article*) hat->hat_dynamics[0], It_Kind_Kirby_PeachToad);
        it_8026B3F8((Article*) hat->hat_dynamics[1],
                    It_Kind_Kirby_PeachToadSpore);
        break;
    case FTKIND_FOX:
        hat = g->hats[0];
        it_8026B3F8((Article*) hat->hat_dynamics[0], It_Kind_Kirby_FoxLaser);
        it_8026B3F8((Article*) hat->hat_dynamics[1], It_Kind_Kirby_FoxBlaster);
        break;
    case FTKIND_FALCO:
        hat = g->hats[21];
        it_8026B3F8((Article*) hat->hat_dynamics[3], It_Kind_Kirby_FalcoLaser);
        it_8026B3F8((Article*) hat->hat_dynamics[4],
                    It_Kind_Kirby_FalcoBlaster);
        break;
    case FTKIND_LINK:
        hat = g->hats[5];
        it_8026B3F8((Article*) hat->hat_dynamics[0], It_Kind_Kirby_LinkArrow);
        it_8026B3F8((Article*) hat->hat_dynamics[1], It_Kind_Kirby_LinkBow);
        break;
    case FTKIND_CLINK:
        hat = g->hats[19];
        it_8026B3F8((Article*) hat->hat_dynamics[0], It_Kind_Kirby_CLinkArrow);
        it_8026B3F8((Article*) hat->hat_dynamics[1], It_Kind_Kirby_CLinkBow);
        break;
    case FTKIND_MEWTWO:
        it_8026B3F8((Article*) g->hats[15]->hat_dynamics[3],
                    It_Kind_Kirby_MewtwoShadowBall);
        break;
    case FTKIND_NESS:
        hat = g->hats[7];
        it_8026B3F8((Article*) hat->hat_dynamics[0],
                    It_Kind_Kirby_NessPKFlush);
        it_8026B3F8((Article*) hat->hat_dynamics[1],
                    It_Kind_Kirby_NessPKFlush_Explode);
        break;
    case FTKIND_PIKACHU:
        hat = g->hats[11];
        it_8026B3F8((Article*) hat->hat_dynamics[0],
                    It_Kind_Kirby_PikachuTJolt_Ground);
        it_8026B3F8((Article*) hat->hat_dynamics[1],
                    It_Kind_Kirby_PikachuTJolt_Air);
        break;
    case FTKIND_PICHU:
        hat = g->hats[22];
        it_8026B3F8((Article*) hat->hat_dynamics[0],
                    It_Kind_Kirby_PichuTJolt_Ground);
        it_8026B3F8((Article*) hat->hat_dynamics[1],
                    It_Kind_Kirby_PichuTJolt_Air);
        break;
    case FTKIND_SAMUS:
        it_8026B3F8((Article*) g->hats[12]->hat_dynamics[0],
                    It_Kind_Kirby_SamusCharge);
        break;
    case FTKIND_KOOPA:
        it_8026B3F8((Article*) g->hats[4]->hat_dynamics[0],
                    It_Kind_Kirby_KoopaFlame);
        break;
    case FTKIND_GKOOPS:
        it_8026B3F8((Article*) g->hats[30]->hat_dynamics[0],
                    It_Kind_Kirby_KoopaFlame);
        break;
    case FTKIND_SEAK:
        hat = g->hats[6];
        it_8026B3F8((Article*) hat->hat_dynamics[0],
                    It_Kind_Kirby_SeakNeedleThrow);
        it_8026B3F8((Article*) hat->hat_dynamics[1],
                    It_Kind_Kirby_SeakNeedleHeld);
        break;
    case FTKIND_DRMARIO:
        it_8026B3F8((Article*) g->hats[20]->hat_dynamics[0],
                    It_Kind_Kirby_DrMarioVitamin);
        break;
    case FTKIND_GAMEWATCH:
        hat = g->hats[23];
        it_8026B3F8((Article*) hat->hat_dynamics[5],
                    It_Kind_Kirby_GameWatchChef);
        it_8026B3F8((Article*) hat->hat_dynamics[6],
                    It_Kind_Kirby_GameWatchChefPan);
        break;
    case FTKIND_YOSHI:
        it_8026B3F8((Article*) g->hats[13]->hat_dynamics[5],
                    It_Kind_Kirby_YoshiEggLay);
        break;
    }
}

void ftKb_SpecialN_800F190C(Fighter_GObj* gobj, FighterKind kind)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    fp->u.kb.x68 = 9;
    fp->u.kb.x6C = 9;
    fp->u.kb.xC0 = NULL;
    fp->u.kb.xC4 = false;
    fp->u.kb.xC8 = ftKb_Init_804D935C;
    fp->u.kb.xCC = false;
    fp->u.kb.xD0 = NULL;
    fp->u.kb.x74 = 0;
    fp->u.kb.x78 = 0;
    fp->u.kb.ns_flash_gobj = NULL;
    fp->u.kb.x80 = 0;
    fp->u.kb.x84 = da->specialn_kp_max_fuel;
    fp->u.kb.x88 = da->specialn_kp_flame_scale;
    fp->u.kb.x8C.x = 1.0F;
    fp->u.kb.x8C.y = 1.0F;
    fp->u.kb.x8C.z = 1.0F;
    fp->u.kb.x98 = NULL;
    fp->u.kb.x9C = 0;
    fp->u.kb.xA0 = NULL;
    fp->u.kb.xA4 = 0;
    fp->u.kb.xA8 = 0;
    fp->u.kb.xAC = 0;
    fp->u.kb.xB0 = 0;
    fp->u.kb.xB4 = 0;
    fp->u.kb.xB8 = NULL;
    fp->u.kb.xBC = 0;
    fp->u.kb.xD4 = 1;
    fp->u.kb.xD8 = 3;
    fp->u.kb.xDC = NULL;
}

void ftKb_SpecialN_800F19AC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    FighterKind kind = fp->u.kb.hat.kind;

    switch (kind) {
    case FTKIND_POPO:
        ftKb_SpecialNIc_80108D04(gobj);
        break;
    case FTKIND_PEACH:
        ftKb_SpecialNPe_8010C3F4(gobj);
        break;
    case FTKIND_FOX:
    case FTKIND_FALCO:
        ftKb_SpecialNFx_800FDEE0(gobj);
        break;
    case FTKIND_LINK:
    case FTKIND_CLINK:
        ftKb_SpecialNLk800FB800(gobj);
        ftKb_SpecialNLk800FB840(gobj);
        break;
    case FTKIND_MEWTWO:
        ftKb_SpecialNMt_8010709C(gobj);
        break;
    case FTKIND_NESS:
        ftKb_SpecialNNs_800FECE8(gobj);
        break;
    case FTKIND_SAMUS:
        ftKb_SpecialNSs_800FCD60(gobj);
        break;
    case FTKIND_SEAK:
        ftKb_SpecialNSk_8010603C(gobj);
        break;
    case FTKIND_YOSHI:
        ftKb_SpecialNYs_801093B4(gobj);
        ftKb_SpecialNYs_8010A8BC(gobj);
        break;
    case FTKIND_DONKEY:
        ftKb_SpecialNPr_80100DE0(gobj);
        break;
    case FTKIND_GAMEWATCH:
        ftKb_SpecialNGw_8010D0A8(gobj);
        break;
    }
}

void ftKb_SpecialN_800F1A8C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    FighterKind kind = fp->u.kb.hat.kind;

    switch (kind) {
    case FTKIND_POPO:
        ftKb_SpecialNIc_80108D04(gobj);
        break;
    case FTKIND_PEACH:
        ftKb_SpecialNPe_8010C3F4(gobj);
        break;
    case FTKIND_FOX:
    case FTKIND_FALCO:
        ftKb_SpecialNFx_800FDEE0(gobj);
        break;
    case FTKIND_LINK:
    case FTKIND_CLINK:
        ftKb_SpecialNLk800FB800(gobj);
        ftKb_SpecialNLk800FB840(gobj);
        break;
    case FTKIND_MEWTWO:
        ftKb_SpecialNMt_80107130(gobj);
        break;
    case FTKIND_NESS:
        ftKb_SpecialNNs_800FECE8(gobj);
        break;
    case FTKIND_SAMUS:
        ftKb_SpecialNSs_800FCD60(gobj);
        break;
    case FTKIND_SEAK:
        ftKb_SpecialNSk_8010603C(gobj);
        break;
    case FTKIND_YOSHI:
        ftKb_SpecialNYs_801093B4(gobj);
        ftKb_SpecialNYs_8010A8BC(gobj);
        break;
    case FTKIND_DONKEY:
        ftKb_SpecialNPr_80100DE0(gobj);
        break;
    case FTKIND_GAMEWATCH:
        ftKb_SpecialNGw_8010D0A8(gobj);
        break;
    }
}

void ftKb_Init_UnkMotionStates3(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    FighterKind kind = fp->u.kb.hat.kind;

    switch (kind) {
    case FTKIND_KOOPA:
    case FTKIND_GKOOPS:
        ftKb_SpecialNKp_800FA7D4(gobj);
        break;
    }
}

void ftKb_SpecialN_800F1BAC(Fighter_GObj* gobj, s32 kind, bool arg2)
{
    Fighter* fp = gobj->user_data;
    HSD_GObjEvent cb;

    if (fp->u.kb.hat.kind != kind) {
        fp->u.kb.hat.kind = kind;
        ftKb_SpecialN_800F190C(gobj, fp->u.kb.hat.kind);
        if ((cb = ftKb_Init_803C9CC8[fp->u.kb.hat.kind * 2]) != NULL) {
            cb(gobj);
        }
        ftKb_SpecialN_800F16D0(gobj, fp->u.kb.hat.kind);
        if (arg2 == 1) {
            ft_PlaySFX(fp, 0x222F3, 0x7F, 0x40);
        }
    } else if (arg2 == 1) {
        ft_PlaySFX(fp, 0x222F6, 0x7F, 0x40);
    }
    fp->death3_cb = ftKb_Init_800EE74C;
    fp->death1_cb = ftKb_Init_800EE7B8;
}

#pragma force_active on
bool fn_800F1CA0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    u32 val = fp->u.kb.hat.kind;
    switch (val) {
    case 2:
    case 7:
    case 10:
    case 11:
    case 13:
        return true;
    default:
        return false;
    }
}
#pragma force_active reset

s32 ftKb_SpecialN_800F1CD8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    FighterKind kind = fp->u.kb.hat.kind;
    bool result;

    switch (kind) {
    case FTKIND_CAPTAIN:
    case FTKIND_SEAK:
    case FTKIND_POPO:
    case FTKIND_NANA:
    case FTKIND_SAMUS:
        result = true;
        break;
    default:
        result = false;
        break;
    }

    if (result) {
        return true;
    }
    return false;
}

void ftKb_SpecialN_800F1D24(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 x60;
    CollData* coll = &fp->coll_data;
    if (fp->kind == FTKIND_KIRBY) {
        x60 = fp->u.kb.x60;
        if (x60 != 0) {
            fp->u.kb.x60 = x60 - 1;
        } else {
            ftKb_SpecialN_800F1DAC(gobj);
        }
        if ((coll->env_flags & 0x800) || (coll->env_flags & 0x20) ||
            (coll->env_flags & 0x4000) || (coll->env_flags & 0x10000))
        {
            fp->u.kb.x60 = 5;
        }
    }
}

void ftKb_SpecialN_800F1DAC(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    CollData* coll = &fp->coll_data;
    Vec3 vec;
    PAD_STACK(16);

    if ((coll->env_flags & 0x800) && !(coll->prev_env_flags & 0xFC0)) {
        vec.x = coll->ecb.left.x;
        vec.y = coll->ecb.left.y;
        vec.z = ftKb_Init_804D935C;
        efAsync_Spawn(gobj, &GET_FIGHTER(gobj)->x60C, 2, 0x49E,
                      fp->parts[0].joint, &vec);
        return;
    }
    if ((coll->env_flags & 0x20) && !(coll->prev_env_flags & 0x3F)) {
        vec.x = coll->ecb.right.x;
        vec.y = coll->ecb.right.y;
        vec.z = ftKb_Init_804D935C;
        efAsync_Spawn(gobj, &GET_FIGHTER(gobj)->x60C, 2, 0x49E,
                      fp->parts[0].joint, &vec);
        return;
    }
    if ((coll->env_flags & 0x4000) && !(coll->prev_env_flags & 0x6000)) {
        vec.x = ftKb_Init_804D935C;
        vec.y = coll->ecb.top.y;
        vec.z = ftKb_Init_804D935C;
        efAsync_Spawn(gobj, &GET_FIGHTER(gobj)->x60C, 2, 0x49E,
                      fp->parts[0].joint, &vec);
        return;
    }
    if ((coll->env_flags & 0x10000) && !(coll->prev_env_flags & 0x18000)) {
        vec.x = ftKb_Init_804D935C;
        vec.y = coll->ecb.bottom.y;
        vec.z = ftKb_Init_804D935C;
        efAsync_Spawn(gobj, &GET_FIGHTER(gobj)->x60C, 2, 0x49E,
                      fp->parts[0].joint, &vec);
    }
}

void ftKb_SpecialN_800F1F1C(Fighter_GObj* gobj, Vec3* pos)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->kind == FTKIND_KIRBY) {
        efAsync_Spawn(gobj, &fp->x60C, 2, 0x49E, fp->parts[0].joint, pos);
    }
}
