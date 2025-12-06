#include "gr/grflatzone.h"

#include "gr/grdisplay.h"
#include "gr/grdynamicattr.h"
#include "gr/grlib.h"
#include "gr/grmaterial.h"
#include "gr/ground.h"
#include "gr/inlines.h"
#include "gr/stage.h"
#include "gr/types.h"
#include "it/inlines.h"
#include "lb/lb_00F9.h"
#include "mp/mplib.h"

#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>
#include <baselib/random.h>

static StageCallbacks grFz_803E7940[9] = {
    { grFlatzone_80217030, grFlatzone_8021705C, grFlatzone_80217064,
      grFlatzone_80217068, 0 },
    { grFlatzone_802173D4, grFlatzone_80217430, grFlatzone_80217438,
      grFlatzone_8021743C, 0 },
    { grFlatzone_8021707C, grFlatzone_802171CC, grFlatzone_802171D4,
      grFlatzone_802173D0, 0xC0000000 },
    { grFlatzone_80217648, grFlatzone_802176B4, grFlatzone_802176BC,
      grFlatzone_80217CD0, 0 },
    { grFlatzone_80217CD4, grFlatzone_80217D28, grFlatzone_80217D30,
      grFlatzone_80217DA4, 0 },
    { grFlatzone_80217450, grFlatzone_802174E4, grFlatzone_802174EC,
      grFlatzone_80217644, 0 },
    { grFlatzone_80217DA8, grFlatzone_80217DFC, grFlatzone_80217E04,
      grFlatzone_80217E78, 0 },
    { grFlatzone_80217E7C, grFlatzone_80217E80, grFlatzone_80217E88,
      grFlatzone_80217E8C, 0 },
    { grFlatzone_80217E90, grFlatzone_80217EE8, grFlatzone_80217EF0,
      grFlatzone_8021805C, 0 }
};

StageData grFz_803E7A00 = {
    27,
    grFz_803E7940,
    "/GrFz.dat",
    grFlatzone_80216E78,
    grFlatzone_80216E74,
    grFlatzone_UnkStage0_OnLoad,
    grFlatzone_UnkStage0_OnStart,
    grFlatzone_80216F40,
    grFlatzone_802182B4,
    grFlatzone_802182BC,
    (1 << 0),
    NULL,
    0,
};

extern void fn_8021706C(HSD_GObj*);
extern void fn_80217440(HSD_GObj*);
extern void Camera_800311CC(f32);          /* extern */
extern void Camera_800311DC(f32);          /* extern */
extern void* it_802EEFA8(Vec3*, s32, f32); /* extern */

static struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    f32 unk28;
    s32 unk2C;
    s32 unk30;
    s32 unk34;
    f32 unk38;
    s32 unk3C;
}* grFz_804D6AB0;
// static s8 grFz_804D4920[8] = { 0x6A, 0x6F, 0x62, 0x6A, 0x2E, 0x68, 0, 0 };
// static s8 grFz_804D4928[8] = { 0x6A, 0x6F, 0x62, 0x6A, 0, 0, 0, 0 };
static Vec3 grFz_803B8430;

void grFlatzone_80216E74(bool arg0)
{
    return;
}

void grFlatzone_80216E78(void)
{
    u8* temp_r5;

    grFz_804D6AB0 = Ground_801C49F8();
    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 1;
    grFlatzone_80216F48(0);
    grFlatzone_80216F48(1);
    grFlatzone_80216F48(2);
    grFlatzone_80216F48(3);
    grFlatzone_80216F48(4);
    grFlatzone_80216F48(5);
    grFlatzone_80216F48(6);
    grFlatzone_80216F48(8);
    grFlatzone_80218060(1);
    Ground_801C39C0();
    Ground_801C3BB4();
    Camera_800311DC(1.0f);
    Camera_800311CC(1000.0f);
    Ground_801C3990(Stage_GetBlastZoneBottomOffset() - 50.0f);
}

void grFlatzone_UnkStage0_OnLoad(void)
{
    return;
}

void grFlatzone_UnkStage0_OnStart(void)
{
    return;
}

bool grFlatzone_80216F40(void)
{
    return 0;
}

HSD_GObj* grFlatzone_80216F48(s32 gobj_id)
{
    StageCallbacks* callbacks = &grFz_803E7940[gobj_id];
    HSD_GObj* gobj = Ground_801C14D0(gobj_id);
    if (gobj != NULL) {
        Ground* gp = GET_GROUND(gobj);
        gp->x8_callback = NULL;
        gp->xC_callback = NULL;
        GObj_SetupGXLink(gobj, grDisplay_801C5DB0, 3, 0);
        if (callbacks->callback3 != NULL) {
            gp->x1C_callback = callbacks->callback3;
        }
        if (callbacks->callback0 != NULL) {
            callbacks->callback0(gobj);
        }
        if (callbacks->callback2 != NULL) {
            HSD_GObjProc_8038FD54(gobj, callbacks->callback2, 4);
        }
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grflatzone.c", 0xE8,
                 gobj_id);
    }
    return gobj;
}

void grFlatzone_80217030(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grFlatzone_8021705C(Ground_GObj* gobj)
{
    return 0;
}

void grFlatzone_80217064(Ground_GObj* gobj)
{
    return;
}

void grFlatzone_80217068(Ground_GObj* gobj)
{
    return;
}

void fn_8021706C(HSD_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    gp->gv.flatzone.xC4 = 0;
}

static inline int rand_int_inner(s32 a)
{
    return (a != 0) ? HSD_Randi(a) : 0;
}

static inline int rand_int(s32 a, s32 b)
{
    if (a > b) {
        s32 c = a - b;
        a = b + ((c != 0) ? HSD_Randi(c) : 0);
    } else if (a < b) {
        s32 c = b - a;
        a += ((c != 0) ? HSD_Randi(c) : 0);
    }
    return a;
}

void grFlatzone_8021707C(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Ground_801C2ED0(jobj, gp->map_id);
    HSD_JObjSetTranslateZ(jobj, 1.0f);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->gv.flatzone.xC4 = 1;
    gp->gv.flatzone.xC7 = 1;
    gp->gv.flatzone.xC6 = 0;
    gp->gv.flatzone.xC8 = rand_int(grFz_804D6AB0->unk4, grFz_804D6AB0->unk0);
    Ground_801C10B8(gobj, fn_8021706C);
}

bool grFlatzone_802171CC(Ground_GObj* gobj)
{
    return 0;
}

static inline void grFlatzone_802171D4_inline(Ground_GObj* gobj)
{
    if (gobj != NULL) {
        Ground* gp = GET_GROUND(gobj);
        if (gp != NULL) {
            gp->gv.flatzone.xC4 = 1;
        }
    }
}

void grFlatzone_802171D4(Ground_GObj* gobj)
{
    s32 sp24;
    s16 temp_r3;

    Ground* gp = GET_GROUND(gobj);
    if (!gp->gv.flatzone.xC4 && gp->gv.flatzone.xC7) {
        if (gp->gv.flatzone.xC8 != 0) {
            gp->gv.flatzone.xC8 -= 1;
            if (gp->gv.flatzone.xC8 == 0) {
                gp->gv.flatzone.xC7 = 0;
                gp->gv.flatzone.xC6 = gp->gv.flatzone.xC5;
                do {
                    s16 vals[2] = { 3, 4 };
                    gp->gv.flatzone.xC5 = vals[HSD_Randi(2)];
                } while (gp->gv.flatzone.xC6 == gp->gv.flatzone.xC5);
                switch (gp->gv.flatzone.xC5) {
                case 1:
                    grFlatzone_802171D4_inline(Ground_801C2BA4(4));
                    grFlatzone_80218260();
                    break;
                case 2:
                    grFlatzone_802171D4_inline(Ground_801C2BA4(6));
                    grFlatzone_80218260();
                    break;
                case 3:
                    grFlatzone_802171D4_inline(Ground_801C2BA4(8));
                    grFlatzone_802181B4();
                    break;
                case 4:
                    grFlatzone_802171D4_inline(Ground_801C2BA4(3));
                    grFlatzone_802181B4();
                    break;
                }
            }
        } else {
            grFlatzone_80218060(0);
            gp->gv.flatzone.xC8 =
                rand_int(grFz_804D6AB0->unk4, grFz_804D6AB0->unk0);
        }
    }
    Ground_801C2FE0((HSD_GObj*) gobj);
    lb_800115F4();
}

void grFlatzone_802173D0(Ground_GObj* gobj) {}

void grFlatzone_802173D4(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
    grMaterial_801C8858(jobj, 0x28000000U);
    gp->x11_flags.b012 = 2;
}

bool grFlatzone_80217430(Ground_GObj* gobj)
{
    return 0;
}

void grFlatzone_80217438(Ground_GObj* gobj)
{
    return;
}

void grFlatzone_8021743C(Ground_GObj* gobj)
{
    return;
}

void fn_80217440(HSD_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    gp->gv.flatzone.xC4 = 0;
}

void grFlatzone_80217450(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Ground_801C2ED0(jobj, gp->map_id);
    HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
    gp->gv.flatzone.xC7 = 8;
    gp->gv.pad_0[4] = 8;
    gp->gv.pad_0[5] = 0;
    gp->gv.pad_0[6] = 0;
    gp->gv.flatzone.xCC = 0;
    gp->gv.flatzone.xC6 = 0xFF;
    gp->gv.flatzone.xC4 = 1;
    Ground_801C10B8((HSD_GObj*) gobj, fn_80217440);
}

bool grFlatzone_802174E4(Ground_GObj* gobj)
{
    return 0;
}

#define SIGN_RANDOM() ((HSD_Randi(2) != 0) ? 1.0f : -1.0f)

void grFlatzone_802176BC(Ground_GObj* gobj)
{
    s32 var_r29 = 0;
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Vec3 pos = grFz_803B8430;
    if (gp->gv.flatzone.xC4 != 0) {
        if (gp->gv.flatzone.xD0 == 3) {
            HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
            if (gp->gv.flatzone2.xCC == NULL) {
                grDynamicAttr_801CA1C0(gp->gv.flatzone2.xCC);
                gp->gv.flatzone2.xCC = NULL;
            }
        }
        gp->gv.flatzone.xC4 = 0;
        gp->gv.flatzone.xC8 = SIGN_RANDOM();
        gp->gv.flatzone.xD0 = 0;
        gp->gv.flatzone.xD4 = grFz_804D6AB0->unk20;
        if (gp->gv.flatzone.xC8 == 1.0f) {
            pos.x = grFz_804D6AB0->unk24;
            gp->gv.flatzone.xD4 = (s32) ((f32) gp->gv.flatzone.xD4 * 0.5f);
        } else {
            pos.x = grFz_804D6AB0->unk28;
            {
                HSD_GObj* gobj = Ground_801C2BA4(2);
                if (gobj != NULL) {
                    Ground* gp = GET_GROUND(gobj);
                    if (gp != NULL) {
                        grAnime_801C8138(gobj, gp->map_id, 1);
                    }
                }
            }
        }
        HSD_JObjSetTranslate(jobj, &pos);
    }
    switch (gp->gv.flatzone2.xD0) {
    case 0:
        if ((s32) gp->gv.flatzone2.xD4 ==
            (s32) ((s32) grFz_804D6AB0->unk20 / 2))
        {
            if (gp->gv.flatzone2.xC8 == 1.0f) {
                grAnime_801C8138((HSD_GObj*) gobj, gp->map_id, 0);
            } else {
                grAnime_801C8138((HSD_GObj*) gobj, gp->map_id, 2);
            }
            HSD_JObjRemoveAnimAll(jobj);
        }
        gp->gv.unk.xD4 -= 1;
        if (gp->gv.unk.xD4 <= 0) {
            gp->gv.unk.xD0 = 1;
            gp->gv.unk.xD4 =
                grFz_804D6AB0->unk2C *
                (grFz_804D6AB0->unk30 +
                 rand_int_inner(grFz_804D6AB0->unk34 - grFz_804D6AB0->unk30));
            if (gp->gv.unk.xC8 == 1.0f) {
                grAnime_801C8138(gobj, gp->map_id, 0);
            } else {
                grAnime_801C8138(gobj, gp->map_id, 2);
            }
        }
        break;
    case 1:
        if ((gp->gv.unk.xD4 % grFz_804D6AB0->unk2C) == 1) {
            HSD_JObjGetTranslation(jobj, &pos);
            pos.x += grFz_804D6AB0->unk38 * gp->gv.flatzone2.xC8;
            HSD_JObjSetTranslate(jobj, &pos);
        }
        gp->gv.flatzone2.xD4 -= 1;
        if (gp->gv.flatzone2.xD4 <= 0) {
            gp->gv.flatzone2.xD0 = 2;
            gp->gv.flatzone2.xD4 = 0;
            if (gp->gv.flatzone2.xC8 == 1.0f) {
                grAnime_801C8138(gobj, gp->map_id, 1);
            } else {
                grAnime_801C8138(gobj, gp->map_id, 3);
            }
        }
        break;
    case 2:
        if (grAnime_801C83D0(gobj, 0, 1) != 0) {
            Vec3 pos_2;
            int ret;
            f32 other_x;
            f32 other_z;
            s32 var_r0;
            gp->gv.unk.xD0 = 3;
            gp->gv.unk.xD4 = grFz_804D6AB0->unk3C;
            HSD_JObjGetTranslation(jobj, &pos);
            other_x = (36.0f * gp->gv.unk.xC8) + pos.x;
            pos.x = other_x;
            pos.y -= 27.0f;
            other_z = 5.0f + pos.z;
            pos.z -= 5.0f;
            if (mpCheckMultiple(other_x, other_z, pos.x, pos.z, &pos_2, &ret,
                                0, 0, 1, -1, 0x32) != 0)
            {
                var_r0 = ret;
            } else {
                var_r0 = -1;
            }
            if (var_r0 != -1) {
                gp->gv.flatzone2.xCC = grDynamicAttr_801CA0F8(
                    0x11, &pos_2, var_r0, 22.0f, grFz_804D6AB0->unk3C);
            }
            var_r29 = 1;
        }
        break;
    case 3:
        gp->gv.flatzone2.xD4 -= 1;
        if ((s32) gp->gv.flatzone2.xD4 <= 1) {
            gp->gv.flatzone2.xD0 = 4;
            gp->gv.flatzone2.xD4 = 0;
        }
        break;
    case 4:
        HSD_JObjRemoveAnimAll(jobj);
        HSD_JObjSetFlagsAll(jobj, 0x10U);
        gp->gv.flatzone2.xCC = 0;
        gp->gv.flatzone2.xD0 = -1;
        break;
    }
    if (var_r29 != 0) {
        {
            HSD_GObj* gobj = Ground_801C2BA4(2);
            if (gobj != NULL) {
                Ground* gp = GET_GROUND(gobj);
                if (gp != NULL) {
                    gp->gv.flatzone.xC4 = 1;
                }
            }
        }
        if (gp->gv.flatzone2.xC8 != 1.0f) {
            HSD_GObj* gobj = Ground_801C2BA4(2);
            if (gobj != NULL) {
                Ground* gp = GET_GROUND(gobj);
                if (gp != NULL) {
                    grAnime_801C8138(gobj, gp->map_id, 0);
                }
            }
        }
    }
    Ground_801C2FE0(gobj);
}

void grFlatzone_80217644(Ground_GObj* gobj)
{
    return;
}

void grFlatzone_80217648(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Ground_801C2ED0(jobj, gp->map_id);
    HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
    gp->gv.flatzone.xC4 = 0;
    gp->gv.flatzone2.xC8 = 1.0f;
    gp->gv.flatzone2.xCC = NULL;
    gp->gv.flatzone2.xD0 = -1;
    gp->gv.flatzone2.xD4 = 0;
}

bool grFlatzone_802176B4(Ground_GObj* gobj)
{
    return 0;
}

void grFlatzone_80217CD0(Ground_GObj* gobj) {}

void grFlatzone_80217CD4(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Ground_801C2ED0(jobj, gp->map_id);
    HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
    gp->gv.flatzone.xC4 = 0;
}

bool grFlatzone_80217D28(Ground_GObj* gobj)
{
    return 0;
}

void grFlatzone_80217D30(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    if (gp->gv.flatzone.xC4 != 0) {
        {
            HSD_GObj* gobj = Ground_801C2BA4(2);
            if (gobj != NULL) {
                Ground* gp = gobj->user_data;
                if (gp != NULL) {
                    gp->gv.flatzone.xC7 = 1;
                }
            }
        }
        gp->gv.flatzone.xC4 = 0;
    }
    Ground_801C2FE0((HSD_GObj*) gobj);
}

void grFlatzone_80217DA4(Ground_GObj* gobj)
{
    return;
}

void grFlatzone_80217DA8(Ground_GObj* gobj)
{
    grFlatzone_80217CD4(gobj);
}

bool grFlatzone_80217DFC(Ground_GObj* gobj)
{
    return 0;
}

static s16 grFz_803E7A68[] = { 0x0000, 0x0001, 0x0002, 0xFFFF, 0xFFFF, 0x0003,
                               0x0004, 0x0005, 0x0006, 0x0007, 0x0008, 0x0009,
                               0x000A, 0x000B, 0x000C, 0x000D, 0x000E, 0x000F,
                               0x0010, 0x0011, 0x0012, 0xFFFF, 0xFFFF, 0xFFFF,
                               0xFFFF, 0x0013, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
                               0x0014, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0015,
                               0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000,
                               0x0000, 0x0000, 0x0000, 0x0000, 0x0000 };

void grFlatzone_802174EC(Ground_GObj* gobj)
{
    s16 temp_r0;
    s16 temp_r4;

    Ground* gp = GET_GROUND(gobj);
    if (((u8) gp->gv.pad_0[0] == 0) && ((u8) gp->gv.pad_0[3] != 8) &&
        ((u8) gp->gv.pad_0[5] != 0))
    {
        temp_r4 = gp->gv.flatzone.xC8;
        gp->gv.flatzone.xC8 = temp_r4 - 1;
        if (temp_r4 < 0) {
            gp->gv.pad_0[6] = gp->gv.pad_0[5];
            do {
                gp->gv.pad_0[5] = HSD_Randi(4) + 1;
                if (gp->gv.pad_0[6] == gp->gv.pad_0[5]) {
                    continue;
                }
                temp_r0 = *((u16*) grFz_803E7A68 +
                            (gp->gv.pad_0[3] * 10 + (gp->gv.pad_0[5])));
            } while (temp_r0 == -1);
            gp->gv.pad_0[1] = (u8) temp_r0;
            grAnime_801C8138(gobj, gp->map_id, gp->gv.pad_0[1]);
            gp->gv.flatzone.xC8 =
                rand_int(grFz_804D6AB0->unkC, grFz_804D6AB0->unk8);
        }
    }
    Ground_801C2FE0(gobj);
    if (gp->gv.pad_0[2] != gp->gv.pad_0[1]) {
        gp->gv.pad_0[2] = gp->gv.pad_0[1];
        mpLib_80058560();
    }
}

void grFlatzone_80217E04(Ground_GObj* gobj)
{
    grFlatzone_80217D30(gobj);
}

void grFlatzone_80217E78(Ground_GObj* gobj)
{
    return;
}

void grFlatzone_80217E7C(Ground_GObj* gobj)
{
    return;
}

bool grFlatzone_80217E80(Ground_GObj* gobj)
{
    return 0;
}

void grFlatzone_80217E88(Ground_GObj* gobj)
{
    return;
}

void grFlatzone_80217E8C(Ground_GObj* gobj)
{
    return;
}

void grFlatzone_80217E90(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Ground_801C2ED0(jobj, gp->map_id);
    HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
    gp->gv.flatzone.xC4 = 0;
    *(s32*) &gp->gv.flatzone.xC8 = 0;
}

bool grFlatzone_80217EE8(Ground_GObj* gobj)
{
    return 0;
}

void grFlatzone_80217EF0(Ground_GObj* gobj)
{
    Vec3 pos;
    f32 var_f1;
    s32 temp_r30;
    s32 temp_r5;
    void* temp_r3;
    void* temp_r3_2;
    void* temp_r3_4;

    Ground* gp = GET_GROUND(gobj);
    if ((u8) gp->gv.pad_0[0] != 0) {
        gp->gv.unk.xC8 = grFz_804D6AB0->unk10;
        gp->gv.pad_0[0] = 0;
    }
    if ((s32) gp->gv.unk.xC8 > 0) {
        if ((gp->gv.unk.xC8 % grFz_804D6AB0->unk14) == 0) {
            pos.x = (HSD_Randf() *
                     (f32) (grFz_804D6AB0->unk18 - grFz_804D6AB0->unk1C)) -
                    (f32) -grFz_804D6AB0->unk1C;
            pos.y = Stage_GetBlastZoneTopOffset() - 5.0f;
            pos.z = 0.0f;
            {
                f32 sign = SIGN_RANDOM();
                HSD_GObj* gobj = it_802EEFA8(&pos, HSD_Randi(5), sign);
                if (gobj != NULL) {
                    Item* ip = GET_ITEM(gobj);
                    if (ip != NULL) {
                        ip->x378_itemColl.joint_id_only = 0x32;
                    }
                }
            }
        }
        gp->gv.unk.xC8 -= 1;
        if ((s32) gp->gv.unk.xC8 <= 0) {
            HSD_GObj* gobj = Ground_801C2BA4(2);
            if (gobj != NULL) {
                Ground* gp = GET_GROUND(gobj);
                if (gp != NULL) {
                    gp->gv.flatzone.xC7 = 1;
                }
            }
        }
    }
}

void grFlatzone_8021805C(Ground_GObj* gobj)
{
    return;
}

#if 0
void grFlatzone_80218060(s32 arg0) {
    HSD_GObj *temp_r3;
    s32 temp_r28;
    s32 temp_r3_3;
    s32 temp_r3_4;
    s32 var_r27;
    s32 var_r3;
    s32 var_r3_2;
    u8 temp_r0;
    u8 temp_r3_2;
    void *temp_r29;

    temp_r3 = Ground_801C2BA4(5);
    if (temp_r3 != NULL) {
        temp_r29 = temp_r3->user_data;
        if (temp_r29 != NULL) {
            if (arg0 != 0) {
                temp_r29->unkC7 = 2U;
                temp_r29->unkC9 = 1U;
            } else {
                do {
loop_4:
                    temp_r29->unkC7 = HSD_Randi(8);
                    temp_r3_2 = temp_r29->unkC7;
                    if (temp_r3_2 == (u8) temp_r29->unkC8) {
                        goto loop_4;
                    }
                } while ((s16) (grFz_803E7940 + (temp_r3_2 * 0xA))->unk12A == -1);
                do {
                    temp_r0 = HSD_Randi(4) + 1;
                    temp_r29->unkC9 = temp_r0;
                } while ((s16) (grFz_803E7940 + (temp_r29->unkC7 * 0xA) + ((temp_r0 * 2) & 0x1FE))->unk128 == -1);
            }
            temp_r29->unkCA = 0;
            var_r27 = grFz_804D6AB0->unkC;
            temp_r28 = grFz_804D6AB0->unk8;
            if (var_r27 > temp_r28) {
                temp_r3_3 = var_r27 - temp_r28;
                if (temp_r3_3 != 0) {
                    var_r3 = HSD_Randi(temp_r3_3);
                } else {
                    var_r3 = 0;
                }
                var_r27 = temp_r28 + var_r3;
            } else if (var_r27 < temp_r28) {
                temp_r3_4 = temp_r28 - var_r27;
                if (temp_r3_4 != 0) {
                    var_r3_2 = HSD_Randi(temp_r3_4);
                } else {
                    var_r3_2 = 0;
                }
                var_r27 += var_r3_2;
            }
            temp_r29->unkCC = (s16) var_r27;
            temp_r29->unkC5 = (u8) (grFz_803E7940 + (temp_r29->unkC7 * 0xA) + (temp_r29->unkC9 * 2))->unk128;
            grAnime_801C8138(temp_r3, temp_r29->unk14, (s32) temp_r29->unkC5);
        }
    }
}
#endif

void grFlatzone_802181B4(void)
{
    HSD_GObj* gobj = Ground_801C2BA4(5);
    if (gobj != NULL) {
        Ground* gp = GET_GROUND(gobj);
        if (gp != NULL) {
            do {
                gp->gv.flatzone.xC7 = HSD_Randi(8);
            } while (gp->gv.flatzone.xC7 == gp->gv.pad_0[4]);
            gp->gv.pad_0[5] = 0;
            gp->gv.pad_0[6] = 0;
            gp->gv.flatzone.xCC = 0;
            gp->gv.flatzone.xC5 =
                *(grFz_803E7A68 + (gp->gv.pad_0[3] * 10 + gp->gv.pad_0[5]));
            grAnime_801C8138(gobj, gp->map_id, gp->gv.flatzone.xC5);
        }
    }
}

void grFlatzone_80218260(void)
{
    HSD_GObj* gobj = Ground_801C2BA4(5);
    if (gobj != NULL) {
        Ground* gp = GET_GROUND(gobj);
        if (gp != NULL) {
            gp->gv.flatzone.xC7 = 8;
            {
                HSD_JObj* jobj = GET_JOBJ(gobj);
                if (jobj != NULL) {
                    HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
                }
            }
        }
    }
}
DynamicsDesc* grFlatzone_802182B4(enum_t arg0)
{
    return NULL;
}

bool grFlatzone_802182BC(Vec3* arg0, int arg1, HSD_JObj* arg2)
{
    return 1;
}
