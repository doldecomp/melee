#include <platform.h>
#include <placeholder.h>

#include "ft/ftdrawcommon.h"

#include "cm/camera.h"
#include "ft/ft_0C88.h"
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
#include <dolphin/mtx/mtxvec.h>
#include <dolphin/mtx/types.h>
#include <baselib/cobj.h>
#include <baselib/gobj.h>
#include <baselib/state.h>

static char ftDrawCommon_803C0EB0[] = "translate";
static U8Vec4 ftDrawCommon_804D3A88 = { 0xFF, 0xFF, 0xFF, 0x80 };
static U8Vec4 ftDrawCommon_804D3A8C = { 0x80, 0x80, 0xFF, 0x80 };
static U8Vec4 ftDrawCommon_804D3A90 = { 0x80, 0x80, 0x80, 0x80 };
static char ftDrawCommon_804D3A94[] = "jobj.h";
static char ftDrawCommon_804D3A9C[] = "jobj";

extern s32 ftDrawCommon_804D836C[1];
extern s32 ftDrawCommon_804D8370[2];

static inline void mtx_thing(MtxPtr mtx, Vec3* ptr, float val, float val2)
{
    mtx[0][3] = ptr->x + val;
    mtx[1][3] = ptr->y + val;
    mtx[2][3] = ptr->z + val2;
}

MtxPtr ftDrawCommon_8008051C(HSD_GObj* arg1, MtxPtr arg2)
{
    u8 unused0[0x4];

    Vec3 sp54;

    u8 unused1[0xC];

    Mtx sp18;

    u8 unused2[0x8];

    float temp_f31;
    float temp_f0;

    MtxPtr temp_r31;

    temp_f31 = temp_f0 = 0.0F;
    sp54.z = temp_f31;
    sp54.y = temp_f31;
    sp54.x = temp_f31;

    if (ftLib_80087074(arg1, &sp54)) {
        temp_r31 = HSD_CObjGetCurrent()->view_mtx;
        PSMTXIdentity(sp18);

        mtx_thing(sp18, &sp54, temp_f31, temp_f0);

        PSMTXConcat(temp_r31, sp18, arg2);
        return arg2;
    }
    return NULL;
}

void ftDrawCommon_800805C8(HSD_GObj* gobj, s32 arg1, s32 arg2)
{
    u8 padding2[0x4];

    Mtx sp78;
    Mtx sp48;

    u8 padding1[0xC];

    Vec3 sp30;

    u8 padding0[0x14];

    float spA8;
    float spAC;
    float temp_f0;
    float temp_f31;
    Vec3* temp_r4;
    MtxPtr temp_r29;
    s32 fighter_2;
    u32 temp_r25;

    HSD_JObj* fighter0;

    itPickup* temp_r24;
    Fighter* fighter;
    Fighter* phi_r26;
    u32 phi_r25;

    u32 phi_r24;

    u32 phi_r30;
    MtxPtr phi_r29;

    fighter = gobj->user_data;
    phi_r30 = 0U;
    phi_r30 = 0U;
    if (fighter->x21FC_flag.b6 != 0) {
        phi_r26 = fighter + 0x138 * 0;
        phi_r25 = 0U;
        do {
            if (lbColl_80009F54(phi_r26->x914, arg1, fighter->x34_scale.y) !=
                0)
            {
                phi_r30 = 1U;
            }
            temp_r25 = phi_r25 + 1;
            phi_r26 = phi_r26 + 0x138;
            phi_r25 = temp_r25;
            // phi_r30 = phi_r30;
        } while (temp_r25 < 4U);
        if (fighter->x221D_b6) {
            phi_r26 = fighter + (0U * 0x4C);
            // phi_r30 = phi_r30;
            while (phi_r25 < (u8) fighter->hurt_capsules_len) {
                if (lbColl_8000A584(phi_r26->hurt_capsules, 1, arg1,
                                    ftCommon_8007F804(fighter),
                                    fighter->cur_pos.z) != 0)
                {
                    phi_r30 = 1U;
                }
                phi_r25 += 1;
                phi_r26 = phi_r26 + 0x4C;
            }
        } else {
            fighter_2 = fighter->x1988;
            if ((fighter_2 == 0) && ((s32) fighter->x198C == 0)) {
                phi_r26 = fighter;
                // phi_r30 = phi_r30;
                while (phi_r25 < (u8) fighter->hurt_capsules_len) {
                    if (lbColl_8000A244(phi_r26->hurt_capsules, arg1,
                                        ftCommon_8007F804(fighter),
                                        fighter->cur_pos.z) != 0)
                    {
                        phi_r30 = 1U;
                    }
                    phi_r25 += 1;
                    phi_r26 += 0x4C;
                }
            } else {
                if ((fighter->x198C == 2) || (fighter_2 == 2)) {
                    phi_r24 = 2;
                } else {
                    phi_r24 = 1;
                }
                phi_r26 = fighter;
                // phi_r30 = phi_r30;
                while (phi_r25 < fighter->hurt_capsules_len) {
                    if (lbColl_8000A584(phi_r26->hurt_capsules, phi_r24, arg1,
                                        ftCommon_8007F804(fighter),
                                        fighter->cur_pos.z) != 0)
                    {
                        phi_r30 = 1U;
                    }
                    phi_r25 += 1;
                    phi_r26 += 0x4C;
                }
            }
        }
        if ((fighter->x2218_b3 != 0) &&
            (lbColl_8000A95C(&fighter->reflect_hit, arg1,
                             ftCommon_8007F804(fighter),
                             fighter->cur_pos.z) != 0))
        {
            phi_r30 = 1U;
        }
        if ((fighter->x2218_b6 != 0) &&
            (lbColl_8000AB2C(&fighter->absorb_hit, arg2,
                             ftCommon_8007F804(fighter),
                             fighter->cur_pos.z) != 0))
        {
            phi_r30 = 1U;
        }
        if ((fighter->x221B_b0 != 0) &&
            (lbColl_8000A78C(&fighter->shield_hit, arg1,
                             ftCommon_8007F804(fighter),
                             fighter->cur_pos.z) != 0))
        {
            phi_r30 = 1U;
        }
    }
    // phi_r30 = phi_r30;
    if (fighter->x21FC_flag.b5 != 0) {
        phi_r25 = 0U;
        phi_r26 = fighter;
        phi_r25 = 0U;
        while (phi_r25 < (u8) fighter->x166C) {
            if (lbColl_8000A460(phi_r26->x1670, arg1) != 0) {
                phi_r30 = 1U;
            }
            phi_r25 += 1;
            phi_r26 += 0x28;
        }
        phi_r26 = fighter;
        while (phi_r25 < (unsigned) fighter->dynamics_num) {
            spAC = 0.0f;
            spA8 = 0.0f;
            if (lb_800117F4(&phi_r26->dynamic_bone_sets[0].dyn_desc, &spAC,
                            &spA8, phi_r26->dynamics_num, arg1) != 0)
            {
                phi_r30 = 1U;
            }
            phi_r25 += 1;
            phi_r26 += 0x18;
        }
    }
    if ((fighter->x21FC_flag.b3 != 0) && (ftCo_800B395C(gobj, arg1) != 0)) {
        phi_r30 = 1U;
    }
    if ((fighter->x21FC_flag.b4 != 0) && (fighter->x2223_b5 != 0) &&
        (lb_80014770(&fighter->dmg.x1930, arg1) != 0))
    {
        phi_r30 = 1U;
    }
    if (fighter->x21FC_flag.b3 != 0) {
        temp_r24 = &fighter->x294_itPickup;
        if (fighter->ground_or_air == 0) {
            if (lbGx_8001E2F8(&temp_r24->gr_light_offset, &fighter->cur_pos,
                              &ftDrawCommon_804D3A88, arg1,
                              fighter->facing_dir) != 0)
            {
                phi_r30 = 1U;
            }
            if (lbGx_8001E2F8(&temp_r24->gr_heavy_offset, &fighter->cur_pos,
                              &ftDrawCommon_804D3A90, arg1,
                              fighter->facing_dir) != 0)
            {
                phi_r30 = 1U;
            }
        } else if (lbGx_8001E2F8(&temp_r24->air_light_offset,
                                 &fighter->cur_pos, &ftDrawCommon_804D3A8C,
                                 arg1, fighter->facing_dir) != 0)
        {
            phi_r30 = 1U;
        }
    }
    if ((fighter->x21FC_flag.b2 != 0) && (fighter->x2227_b2 == 0) &&
        (lbColl_8000A044(&fighter->x1064_thrownHitbox, arg1,
                         fighter->x34_scale.y) != 0))
    {
        phi_r30 = 1U;
    }
    if ((fighter->x21FC_flag.b0 != 0) && (fighter->x2229_b4 == 0)) {
        phi_r26 = fighter + (0U * 0x2C);
        phi_r25 = 0U;
        do {
            if (lbColl_8000A1A8(&phi_r26->x1614, arg1, fighter->x34_scale.y) !=
                0)
            {
                phi_r30 = 1U;
            }
            temp_r25 = phi_r25 + 1;
            phi_r26 += 0x2C;
            phi_r25 = temp_r25;
        } while (temp_r25 < 2U);
    }
    if (phi_r30 != 0U) {
        HSD_StateInvalidate(-1);
    }
    if (fighter->x21FC_flag.b7 != 0) {
        if ((fighter->x221E_b0 == 0) && (fighter->x221E_b5 == 0) &&
            (arg2 != 0))
        {
            ftParts_800750C8(fighter, 1, 0);
            ftParts_800750C8(fighter, 4, 0);
            if ((fighter->x2223_b7 != 0) || (fighter->x2226_b5 != 0) ||
                (fighter->x2227_b3 != 0))
            {
                ftParts_800750C8(fighter, 0, 0);
                ftParts_800750C8(fighter, 2, 1);
            } else {
                ftParts_800750C8(fighter, 2, 0);
                ftParts_800750C8(fighter, 0, 1);
            }
            ftCo_800A5A5C(fighter);
            fighter->x2223_b2 = 0;
            temp_r4 = &sp30;
            fighter->x2227_b7 = 1;
            fighter->x2228_b0 = 0;
            temp_f31 = temp_f0 = 0.0f;
            sp30.z = temp_f31;
            sp30.y = temp_f31;
            sp30.x = temp_f31;
            phi_r29 = NULL;
            if (ftLib_80087074(gobj, temp_r4) != 0) {
                temp_r29 = HSD_CObjGetCurrent()->view_mtx;

                PSMTXIdentity(sp48);

                mtx_thing(sp48, &sp30, temp_f31, temp_f0);

                PSMTXConcat(temp_r29, sp48, sp78);
                phi_r29 = sp78;
            }
            fighter0 = gobj->hsd_obj;
            HSD_JObjDispAll(fighter0, phi_r29, HSD_GObj_80390EB8(arg1), 0);
            if (ftData_UnkMtxFunc0[fighter->kind] != NULL) {
                ftData_UnkMtxFunc0[fighter->kind](gobj, arg1,
                                                  (MtxPtr) phi_r29);
            }
            ftCo_800C8AF0(fighter);
            ftCo_8009F7F8(fighter);
        }
        if (fighter->x20A0_accessory != NULL) {
            HSD_JObjDispAll(fighter->x20A0_accessory, NULL,
                            HSD_GObj_80390EB8(arg1), 0);
        }
        ftCo_800C8D00(gobj);
    }
}

void ftDrawCommon_80080C28(HSD_GObj* gobj, int arg1)
{
    MtxPtr temp_r28;
    f32 temp_f31;
    f32 temp_f0;

    Mtx sp70;
    Mtx sp40;

    u8 pad0[0xC];

    Vec3 sp30;

    Fighter* fighter;

    MtxPtr phi_r28;
    void* temp_r27;

    u8 pad1[0x18];

    fighter = gobj->user_data;
    if (fighter->x21FC_flag.b7 != 0) {
        if ((fighter->x221E_b0 == 0) && (fighter->x221E_b5 == 0) &&
            (fighter->x2226_b5 == 0))
        {
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

            temp_f31 = temp_f0 = 0.0f;
            sp30.z = temp_f31;
            sp30.y = temp_f31;
            sp30.x = temp_f31;

            if (ftLib_80087074(gobj, &sp30) != 0) {
                temp_r28 = HSD_CObjGetCurrent()->view_mtx;
                PSMTXIdentity(sp40);

                mtx_thing(sp40, &sp30, temp_f31, temp_f0);

                PSMTXConcat(temp_r28, sp40, sp70);
                phi_r28 = sp70;
            }

            temp_r27 = gobj->hsd_obj;
            HSD_JObjDispAll(temp_r27, (MtxPtr) phi_r28,
                            HSD_GObj_80390EB8(arg1), 0);
            if (ftData_UnkMtxFunc0[fighter->kind] != NULL) {
                ftData_UnkMtxFunc0[fighter->kind](gobj, arg1,
                                                  (MtxPtr) phi_r28);
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

void ftDrawCommon_80080E18(HSD_GObj* gobj, int arg1)
{
    Unk2 sp54;
    s32 ret;
    s32 flags;
    Vec3* pos;
    HSD_JObj* jobj;
    MtxPtr arg2;
    MtxPtr matrix;

    Fighter* fighter2;
    Fighter* fighter;
    fighter = fighter2 = gobj->user_data;
    if (fighter->x221F_b3 == 0 && ftLib_80086A8C(gobj)) {
        ret = Camera_80031060();

        switch (ret) {
        case 1:
            if (fighter->x2220_flag.b7) {
                fighter2 = gobj->user_data;
                jobj = (HSD_JObj*) gobj->hsd_obj;

                matrix = HSD_CObjGetInvViewingMtxPtr(Camera_800310B8());
                PSMTXMUltiVec(matrix,
                              (Vec3*) &fighter->mv.co.walk.fast_anim_frame,
                              &fighter2->cur_pos);
                pos = &fighter2->cur_pos;

                HSD_JObjSetTranslate(jobj, pos);
            }
            if (fighter->x5C8 != NULL) {
                fighter = gobj->user_data;
                if ((fighter->x21FC_flag.b7) != 0) {
                    if ((fighter->x221E_b0 == 0) && (fighter->x221E_b5 == 0) &&
                        (fighter->x2226_b5 == 0))
                    {
                        ftParts_800750C8(fighter, 0, 0);
                        ftParts_800750C8(fighter, 1, 0);
                        ftParts_800750C8(fighter, 2, 0);
                        ftParts_800750C8(fighter, 4, 1);
                        fighter->x2223_b2 = 1;
                        fighter->x2223_b3 = 0;
                        {
                            HSD_JObj* fighter = gobj->hsd_obj;
                            u32 ret = HSD_GObj_80390EB8(arg1);
                            MtxPtr arg2 =
                                ftDrawCommon_8008051C(gobj, sp54.x38);
                            HSD_JObjDispAll(fighter, arg2, ret, 0);
                        }
                    }
                }
                ftDrawCommon_800805C8(gobj, arg1, 1);
                fighter = gobj->user_data;
                if (fighter->x21FC_flag.b7 != 0) {
                    if ((fighter->x221E_b0 == 0) && (fighter->x221E_b5 == 0) &&
                        (fighter->x2226_b5 == 0))
                    {
                        ftParts_800750C8(fighter, 0, 0);
                        ftParts_800750C8(fighter, 1, 0);
                        ftParts_800750C8(fighter, 2, 0);
                        ftParts_800750C8(fighter, 4, 1);
                        fighter->x2223_b2 = 1;
                        fighter->x2223_b3 = 1;
                        {
                            HSD_JObj* fighter = gobj->hsd_obj;
                            ret = HSD_GObj_80390EB8(arg1);
                            arg2 = ftDrawCommon_8008051C(gobj, sp54.xC);
                            HSD_JObjDispAll(fighter, arg2, ret, 0);
                        }
                    }
                }
            }
            break;
        case 0: {
            bool arg2;
            fighter->x2223_b3 = 0;
            if (fighter->x5C8 != 0U) {
                arg2 = 0;
            } else {
                arg2 = 1;
            }
            ftDrawCommon_800805C8(gobj, arg1, arg2);
        }
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
