#include "ft/ftdrawcommon.h"

#include <placeholder.h>
#include <platform.h>

#include "cm/camera.h"
#include "ft/ft_0C88.h"
#include "ft/ft_0C8C.h"
#include "ft/ftafterimage.h"
#include "ft/ftcommon.h"
#include "ft/ftdata.h"
#include "ft/ftlib.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ftCommon/ftCo_09F4.h"
#include "ftCommon/ftCo_0A01.h"
#include "lb/lb_00F9.h"
#include "lb/lbcollision.h"
#include "lb/lbgx.h"

#include <dolphin/mtx.h>
#include <baselib/cobj.h>
#include <baselib/gobj.h>
#include <baselib/state.h>

static U8Vec4 ftDrawCommon_804D3A88 = { 0xFF, 0xFF, 0xFF, 0x80 };
static U8Vec4 ftDrawCommon_804D3A8C = { 0x80, 0x80, 0xFF, 0x80 };
static U8Vec4 ftDrawCommon_804D3A90 = { 0x80, 0x80, 0x80, 0x80 };

static inline void mtx_thing_2(MtxPtr mtx, Vec3* v, Vec3* v2)
{
    mtx[0][3] = v->x + v2->x;
    mtx[1][3] = v->y + v2->y;
    mtx[2][3] = v->z + v2->z;
}

MtxPtr ftDrawCommon_8008051C(HSD_GObj* arg1, MtxPtr arg2)
{
    u8 unused0[0x4];
    Vec3 sp54;
    Vec3 v;
    Mtx sp18;
    u8 unused2[0x8];

    v.x = v.y = v.z = 0.0F;
    sp54.x = sp54.y = sp54.z = 0.0F;

    if (ftLib_80087074(arg1, &sp54)) {
        HSD_CObj* current = HSD_CObjGetCurrent();
        MtxPtr mtx = current->view_mtx;
        PSMTXIdentity(sp18);

        mtx_thing_2(sp18, &sp54, &v);

        PSMTXConcat(mtx, sp18, arg2);
        return arg2;
    }
    return NULL;
}

static const GXColor ftDrawCommon_804D836C = { 0xFF, 0xFF, 0xFF, 0xFE };
static const GXColor ftDrawCommon_804D8370 = { 0xFF, 0xFF, 0xFF, 0xFF };

void ftDrawCommon_800805C8(HSD_GObj* gobj, s32 arg1, bool arg2)
{
    GXColor spAC;
    GXColor spA8;

    s32 fighter_2;
    Fighter* fighter;
    u32 phi_r24;
    u32 do_invalidate;
    MtxPtr mtx;
    int i;

    PAD_STACK(0x18);

    fighter = GET_FIGHTER(gobj);
    do_invalidate = false;
    if (fighter->x21FC_flag.b6 != 0) {
        for (i = 0; i < ARRAY_SIZE(fighter->x914); i++) {
            if (lbColl_80009F54(&fighter->x914[i], arg1, fighter->x34_scale.y))
            {
                do_invalidate = true;
            }
        }
        if (fighter->x221D_b6) {
            for (i = 0; i < (unsigned) fighter->hurt_capsules_len; i++) {
                if (lbColl_8000A584(&fighter->hurt_capsules[i].capsule, 1,
                                    arg1, ftCommon_8007F804(fighter),
                                    fighter->cur_pos.z) != 0)
                {
                    do_invalidate = true;
                }
            }
        } else {
            fighter_2 = fighter->x1988;
            if (fighter_2 == NULL && fighter->x198C == 0) {
                for (i = 0; i < (unsigned) fighter->hurt_capsules_len; i++) {
                    if (lbColl_8000A244(&fighter->hurt_capsules[i].capsule,
                                        arg1, ftCommon_8007F804(fighter),
                                        fighter->cur_pos.z))
                    {
                        do_invalidate = true;
                    }
                }
            } else {
                if (fighter->x198C == 2 || fighter_2 == 2) {
                    phi_r24 = 2;
                } else {
                    phi_r24 = 1;
                }
                for (i = 0; i < (unsigned) fighter->hurt_capsules_len; i++) {
                    if (lbColl_8000A584(
                            &fighter->hurt_capsules[i].capsule, phi_r24, arg1,
                            ftCommon_8007F804(fighter), fighter->cur_pos.z))
                    {
                        do_invalidate = true;
                    }
                }
            }
        }
        if (fighter->reflecting &&
            lbColl_8000A95C(&fighter->reflect_hit, arg1,
                            ftCommon_8007F804(fighter), fighter->cur_pos.z))
        {
            do_invalidate = true;
        }
        if (fighter->x2218_b6 &&
            lbColl_8000AB2C(&fighter->absorb_hit, arg1,
                            ftCommon_8007F804(fighter), fighter->cur_pos.z))
        {
            do_invalidate = true;
        }
        if (fighter->x221B_b0 &&
            lbColl_8000A78C(&fighter->shield_hit, arg1,
                            ftCommon_8007F804(fighter), fighter->cur_pos.z))
        {
            do_invalidate = true;
        }
    }
    if (fighter->x21FC_flag.b5 != 0) {
        for (i = 0; i < (unsigned) fighter->x166C; i++) {
            if (lbColl_8000A460(&fighter->x1670[i], arg1)) {
                do_invalidate = true;
            }
        }
        for (i = 0; i < (unsigned) fighter->dynamics_num; i++) {
            spAC = ftDrawCommon_804D836C;
            spA8 = ftDrawCommon_804D8370;
            if (lb_800117F4(&fighter->dynamic_bone_sets[i].dyn_desc, &spAC,
                            &spA8, fighter->dynamic_bone_sets[i].bone_id,
                            arg1))
            {
                do_invalidate = true;
            }
        }
    }
    if (fighter->x21FC_flag.b3 && (ftCo_800B395C(gobj, arg1) != 0)) {
        do_invalidate = true;
    }
    if (fighter->x21FC_flag.b4 && fighter->x2223_b5 &&
        lb_80014770(&fighter->dmg.x1930.x0, arg1))
    {
        do_invalidate = true;
    }
    if (fighter->x21FC_flag.b2 != 0) {
        itPickup* temp_r24 = &fighter->x294_itPickup;
        if (fighter->ground_or_air == 0) {
            if (lbGx_8001E2F8(&temp_r24->gr_light_offset, &fighter->cur_pos,
                              &ftDrawCommon_804D3A88, arg1,
                              fighter->facing_dir))
            {
                do_invalidate = true;
            }
            if (lbGx_8001E2F8(&temp_r24->gr_heavy_offset, &fighter->cur_pos,
                              &ftDrawCommon_804D3A90, arg1,
                              fighter->facing_dir))
            {
                do_invalidate = true;
            }
        } else if (lbGx_8001E2F8(&temp_r24->air_light_offset,
                                 &fighter->cur_pos, &ftDrawCommon_804D3A8C,
                                 arg1, fighter->facing_dir))
        {
            do_invalidate = true;
        }
    }
    if (fighter->x21FC_flag.b1 && !fighter->x2227_b2 &&
        lbColl_8000A044(&fighter->x1064_thrownHitbox, arg1,
                        fighter->x34_scale.y))
    {
        do_invalidate = true;
    }
    if (fighter->x21FC_flag.b0 && !fighter->x2229_b4) {
        for (i = 0; i < ARRAY_SIZE(fighter->x1614); i++) {
            if (lbColl_8000A1A8(&fighter->x1614[i], arg1,
                                fighter->x34_scale.y))
            {
                do_invalidate = true;
            }
        }
    }
    if (do_invalidate) {
        HSD_StateInvalidate(-1);
    }

    if (!fighter->x21FC_flag.b7) {
        return;
    }

    if (!fighter->invisible && !fighter->x221E_b5 && arg2) {
        Mtx sp78;

        ftParts_800750C8(fighter, 1, 0);
        ftParts_800750C8(fighter, 4, 0);
        if (fighter->is_metal || fighter->x2226_b5 || fighter->x2227_b3) {
            ftParts_800750C8(fighter, 0, 0);
            ftParts_800750C8(fighter, 2, 1);
        } else {
            ftParts_800750C8(fighter, 2, 0);
            ftParts_800750C8(fighter, 0, 1);
        }
        ftCo_8009F5AC(fighter);
        fighter->x2223_b2 = false;
        fighter->x2227_b7 = true;
        fighter->x2228_b0 = false;

        mtx = ftDrawCommon_8008051C(gobj, sp78);
        HSD_JObjDispAll(GET_JOBJ(gobj), mtx, HSD_GObj_80390EB8(arg1), 0);
        if (ftData_UnkMtxFunc0[fighter->kind] != NULL) {
            ftData_UnkMtxFunc0[fighter->kind](gobj, arg1, mtx);
        }
        ftCo_800C8AF0(fighter);
        ftCo_8009F7F8(fighter);
    }
    if (fighter->x20A0_accessory != NULL) {
        HSD_JObjDispAll(fighter->x20A0_accessory, NULL,
                        HSD_GObj_80390EB8(arg1), 0);
    }
    ftCo_800C2600(gobj, arg1);
}

void ftDrawCommon_80080C28(HSD_GObj* gobj, int arg1)
{
    Mtx sp70;

    MtxPtr temp_r28;
    f32 temp_f31;
    f32 temp_f0;

    Fighter* fighter;

    MtxPtr phi_r28;
    HSD_JObj* temp_r27;

    PAD_STACK(4);

    fighter = GET_FIGHTER(gobj);
    if (fighter->x21FC_flag.b7 != 0) {
        if (!fighter->invisible && !fighter->x221E_b5 && !fighter->x2226_b5) {
            ftCo_8009F5AC(fighter);
            if (fighter->x5BC != 0U) {
                ftParts_800750C8(fighter, 0, 0);
                ftParts_800750C8(fighter, 2, 0);
                ftParts_800750C8(fighter, 4, 0);
                ftParts_800750C8(fighter, 1, 1);
            }

            phi_r28 = NULL;

            fighter->x2223_b2 = 0;
            fighter->x2223_b3 = 0;
            fighter->x2227_b7 = 0;
            fighter->x2228_b0 = 1;

            phi_r28 = ftDrawCommon_8008051C(gobj, sp70);

            temp_r27 = GET_JOBJ(gobj);
            HSD_JObjDispAll(temp_r27, phi_r28, HSD_GObj_80390EB8(arg1), 0);
            if (ftData_UnkMtxFunc0[fighter->kind] != NULL) {
                ftData_UnkMtxFunc0[fighter->kind](gobj, arg1, phi_r28);
            }
            ftCo_800C8AF0(fighter);
            ftCo_8009F7F8(fighter);
        }
        if (fighter->x20A0_accessory != NULL) {
            HSD_JObjDispAll(fighter->x20A0_accessory, NULL,
                            HSD_GObj_80390EB8(arg1), 0);
        }
    }
}

typedef struct _Unk2 {
    u8 x0_filler[0xC];
    Mtx xC;
    u8 x18_filler[0x38 - 0xC];
    Mtx x38;
    u8 x48_filler[0x68 - 0x3C];
} Unk2;

static inline void ftDrawCommon_80080E18_inline0(HSD_GObj* gobj, int arg1)
{
    Fighter* fp = GET_FIGHTER(gobj);
    MtxPtr matrix;
    u32 ret;
    HSD_JObj* jobj;

    Mtx sp54;

    if (fp->x21FC_flag.b7 && !fp->invisible && !fp->x221E_b5 && !fp->x2226_b5)
    {
        ftParts_800750C8(fp, 0, 0);
        ftParts_800750C8(fp, 1, 0);
        ftParts_800750C8(fp, 2, 0);
        ftParts_800750C8(fp, 4, 1);
        fp->x2223_b2 = 1;
        fp->x2223_b3 = 0;

        jobj = GET_JOBJ(gobj);
        ret = HSD_GObj_80390EB8(arg1);
        matrix = ftDrawCommon_8008051C(gobj, sp54);
        HSD_JObjDispAll(jobj, matrix, ret, 0);
    }
}

static inline void ftDrawCommon_80080E18_inline1(HSD_GObj* gobj, int arg1)
{
    Fighter* fp;
    MtxPtr matrix;
    u32 ret;
    HSD_JObj* jobj;

    Mtx sp24;

    fp = GET_FIGHTER(gobj);

    if (fp->x21FC_flag.b7 && !fp->invisible && !fp->x221E_b5 && !fp->x2226_b5)
    {
        ftParts_800750C8(fp, 0, 0);
        ftParts_800750C8(fp, 1, 0);
        ftParts_800750C8(fp, 2, 0);
        ftParts_800750C8(fp, 4, 1);
        fp->x2223_b2 = 1;
        fp->x2223_b3 = 1;

        jobj = gobj->hsd_obj;
        ret = HSD_GObj_80390EB8(arg1);
        matrix = ftDrawCommon_8008051C(gobj, sp24);
        HSD_JObjDispAll(jobj, matrix, ret, 0);
    }
}

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

void ftDrawCommon_80080E18(HSD_GObj* gobj, int arg1)
{
    Fighter* fp = gobj->user_data;

    if (!fp->x221F_b3 && ftLib_80086A8C(gobj)) {
        switch (Camera_80031060()) {
        case 1:
            if (fp->x2220_b7) {
                ftDrawCommon_80080E18_inline2(gobj, fp);
            }
            if (fp->x5C8 != NULL) {
                ftDrawCommon_80080E18_inline0(gobj, arg1);
                ftDrawCommon_800805C8(gobj, arg1, true);
                ftDrawCommon_80080E18_inline1(gobj, arg1);
            }
            break;
        case 0:
            fp->x2223_b3 = false;
            ftDrawCommon_800805C8(gobj, arg1, fp->x5C8 != NULL ? false : true);
        }
    }
}

void ftDrawCommon_80081118(void)
{
    HSD_GObj* gobj = HSD_GObj_Entities->fighters;
    while (gobj != NULL) {
        gobj->render_cb = &ftDrawCommon_80080E18;
        gobj = gobj->next;
    }
}

void ftDrawCommon_80081140(void)
{
    HSD_GObj* gobj = HSD_GObj_Entities->fighters;
    while (gobj != NULL) {
        gobj->render_cb = ftDrawCommon_80080C28;
        gobj = gobj->next;
    }
}

void ftDrawCommon_80081168(void)
{
    Fighter_GObj* cur;
    for (cur = HSD_GObj_Entities->fighters; cur != NULL; cur = cur->next) {
        Fighter* fighter = GET_FIGHTER(cur);
        PAD_STACK(4 * 2);
        if (fighter->x5BC != NULL) {
            ftParts_800750C8(fighter, 1, 0);
            ftParts_800750C8(fighter, 2, 0);
            ftParts_800750C8(fighter, 4, 0);
            ftParts_800750C8(fighter, 0, 1);
        }
    }
}

void ftDrawCommon_80081200(void)
{
    Fighter_GObj* cur;
    for (cur = HSD_GObj_Entities->fighters; cur != NULL; cur = cur->next) {
        Fighter* fighter = GET_FIGHTER(cur);
        PAD_STACK(4 * 2);
        if (fighter->x5BC != NULL) {
            ftParts_800750C8(fighter, 0, 0);
            ftParts_800750C8(fighter, 2, 0);
            ftParts_800750C8(fighter, 4, 0);
            ftParts_800750C8(fighter, 1, 1);
        }
    }
}
