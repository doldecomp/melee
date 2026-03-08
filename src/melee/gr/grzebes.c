#include "grzebes.h"

#include <platform.h>

#include "forward.h"

#include <dolphin/os.h>

#include "cm/camera.h"
#include "ft/ftdevice.h"
#include "ft/ftlib.h"
#include "gr/granime.h"
#include "gr/grdatfiles.h"
#include "gr/grdisplay.h"
#include "gr/grlib.h"
#include "gr/grmaterial.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "mp/mplib.h"

#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>
#include <baselib/lobj.h>
#include <baselib/random.h>

#include <MSL/math_ppc.h>

/* 1D84A0 */ static void grZebes_801D84A0(bool arg);
/* 1D8528 */ static void grZebes_801D8528(void);
/* 1D852C */ void grZebes_801D852C(void);
/* 1D8550 */ static bool grZebes_801D8550(void);
/* 1D8558 */ static Ground_GObj* grZebes_801D8558(int);
/* 1D8814 */ static bool grZebes_801D8814(Ground_GObj* arg);
/* 1D90FC */ static void grZebes_801D90FC(Ground_GObj* arg);
/* 1D9254 */ static bool grZebes_801D9254(Ground_GObj* arg);
/* 1D93D8 */ static void grZebes_801D93D8(Ground_GObj* arg);
/* 1D93DC */ void grZebes_801D93DC(Ground_GObj* gobj);
/* 1D9408 */ static bool grZebes_801D9408(Ground_GObj* arg);
/* 1D9410 */ static void grZebes_801D9410(Ground_GObj* arg);
/* 1D94EC */ static void grZebes_801D94EC(Ground_GObj* arg);
/* 1D94F0 */ static void fn_801D94F0(Ground_GObj* gobj);
/* 1D95B0 */ static bool grZebes_801D95B0(Ground_GObj* arg);
/* 1D95B8 */ static void grZebes_801D95B8(Ground_GObj* arg);
/* 1D9754 */ static void grZebes_801D9754(Ground_GObj* arg);
/* 1D99D8 */ static bool grZebes_801D99D8(Ground_GObj* arg);
/* 1DA0C4 */ static void grZebes_801DA0C4(f32 level);
/* 1DA254 */ static void grZebes_801DA254(Ground_GObj* gobj, f32 level);
/* 1D9F2C */ static void grZebes_801D9F2C(Ground_GObj* arg);
/* 1D9F7C */ static bool grZebes_801D9F7C(Ground_GObj* arg);
/* 1DA0C0 */ static void grZebes_801DA0C0(Ground_GObj* arg);
/* 1DA3E8 */ static void grZebes_801DA3E8(void);
/* 1DA528 */ static u8 grZebes_801DA528(HSD_GObj*, void*, s32, s32);
/* 1DA9D8 */ static void fn_801DA9D8(Item_GObj* arg0, Ground* gp, Vec3* pos,
                                     HSD_GObj* fobj, f32 slope);
/* 1DA9F0 */ static void fn_801DA9F0(Item_GObj* arg0, Ground* gp, Vec3* pos,
                                     HSD_GObj* fobj, f32 slope);
/* 1DAC90 */ static void fn_801DAC90(Item_GObj*, Ground*, Vec3*, HSD_GObj*,
                                     f32);
/* 1DAA08 */ static s32 grZebes_801DAA08(void);
/* 1DAE70 */ static void grZebes_801DAE70(s32, u8, f32, f32, f32);
/* 1DB3CC */ static s32 grZebes_801DB3CC(HSD_GObj* gobj);
/* 1DBB60 */ static s32 grZebes_801DBB60(s32 arg);
/* 1DC260 */ static void grZebes_801DC260(void);
/* 1DC408 */ static void grZebes_801DC408(Ground_GObj*);
/* 1DC744 */ static void grZebes_801DC744(s32, s32);
/* 1DC9DC */ static void grZebes_801DC9DC(s32 arg);
/* 1DCCB8 */ static DynamicsDesc* grZebes_801DCCB8(enum_t arg);
/* 1DCCC0 */ static bool grZebes_801DCCC0(Vec3* arg, int arg0, HSD_JObj* jobj);

static s16 grZe_803E1A10[] = {
    1, 6, 21, 4, 6, 14, 3, 6,
    1, 2, 7, 6, 5, 7, 1, 0,
};

static StageCallbacks grZe_callbacks[] = {
    { NULL, NULL, NULL, NULL, { 0 } },
    { NULL, NULL, NULL, NULL, { 0 } },
    { NULL, NULL, NULL, NULL, { 0 } },
    { NULL, NULL, NULL, NULL, { 0 } },
    { NULL, NULL, NULL, NULL, { 0 } },
    { NULL, NULL, NULL, NULL, { 0 } },
    { NULL, NULL, NULL, NULL, { 0 } },
    { NULL, NULL, NULL, NULL, { 0 } },
    { NULL, NULL, NULL, NULL, { 0 } },
    { NULL, NULL, NULL, NULL, { 0 } },
    { NULL, NULL, NULL, NULL, { 0 } },
    { NULL, NULL, NULL, NULL, { 0 } },
};

static u8 grZe_803E1B20[0x0A] = { 0 };
static u8 grZe_803E1B2C[0x58] = { 0 };
static u8 grZe_803E1B84[0x0A] = "grzebes.c";
static u8 grZe_803E1B90[0xF0] = { 0 };
static u8 grZe_803E1C80[0x6C] = { 0 };
static u8 grZe_803E1CEC[0x3C] = { 0 };

typedef struct grZe_AcidLevelEntry {
    /* +0 */ s16 base;
    /* +2 */ s16 delay_min;
    /* +4 */ s16 delay_max;
    /* +6 */ s16 level;
} grZe_AcidLevelEntry;

typedef struct grZe_YakumonoParam {
    /* 0x00 */ f32 x00;
    /* 0x04 */ f32 x04;
    /* 0x08 */ f32 x08;
    /* 0x0C */ f32 x0C;
    /* 0x10 */ s32 x10;
    /* 0x14 */ u8 pad_14[0x30 - 0x14];
    /* 0x30 */ f32 x30;
    /* 0x34 */ f32 x34;
    /* 0x38 */ f32 x38;
    /* 0x3C */ f32 x3C;
    /* 0x40 */ f32 x40;
    /* 0x44 */ f32 x44;
    /* 0x48 */ f32 x48;
    /* 0x4C */ f32 x4C;
    /* 0x50 */ f32 x50;
    /* 0x54 */ f32 x54;
    /* 0x58 */ f32 x58;
    /* 0x5C */ f32 x5C;
    /* 0x60 */ f32 x60;
    /* 0x64 */ f32 x64;
    /* 0x68 */ f32 x68;
    /* 0x6C */ f32 x6C;
    /* 0x70 */ f32 x70;
    /* 0x74 */ f32 x74;
    /* 0x78 */ f32 x78;
    /* 0x7C */ f32 x7C;
    /* 0x80 */ f32 x80;
    /* 0x84 */ f32 x84;
    /* 0x88 */ f32 x88;
    /* 0x8C */ f32 x8C;
    /* 0x90 */ f32 x90;
    /* 0x94 */ f32 x94;
    /* 0x98 */ f32 x98;
    /* 0x9C */ f32 x9C;
    /* 0xA0 */ grZe_AcidLevelEntry entries[30];
} grZe_YakumonoParam;

/* 4D6990 */ static grZe_YakumonoParam* grZe_804D6990;
/* 4D6994 */ static s32 grZe_804D6994;
/* 4D6998 */ static s16 grZe_804D6998;

extern f32 grZe_804DB0B0;

typedef struct grZe_BubbleEntry {
    /* 0x00 */ u8 active;
    /* 0x01 */ u8 pad_01;
    /* 0x02 */ s16 timer;
    /* 0x04 */ u32 unk04;
    /* 0x08 */ f32 x;
    /* 0x0C */ f32 y;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 size;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ HSD_GObj* gobj;
} grZe_BubbleEntry;;

/* 8049F140 */ static Vec3 grZe_8049F140[2];
/* 8049F158 */ static Vec3 grZe_8049F158[2];
/* 8049F170 */ static grZe_BubbleEntry grZe_8049F170[20];

typedef struct grZe_BubbleConfig {
    f32 scales[7];
    Vec3 positions[4];
} grZe_BubbleConfig;

typedef struct grZe_AcidState {
    /* +00 */ u8 state;
    /* +01 */ u8 next;
    /* +02 */ s16 timer;
    /* +04 */ f32 base_x;
    /* +08 */ f32 offset;
    /* +0C */ f32 velocity;
    /* +10 */ f32 damage;
    /* +14 */ HSD_JObj* jobj1;
    /* +18 */ HSD_JObj* jobj2;
    /* +1C */ Item_GObj* mat;
    /* +20 */ s32 anim_idx;
} grZe_AcidState;

extern const grZe_BubbleConfig grZe_803B8044;

void grZebes_801D84A0(bool arg) {}

void grZebes_801D84A4(void)
{
    grZe_804D6990 = Ground_801C49F8();
    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 1;
    grZebes_801D8558(0);
    grZebes_801D8558(1);
    grZebes_801D8558(6);
    grZebes_801D8558(4);
    grZebes_801D8558(8);
    Ground_801C39C0();
    Ground_801C3BB4();
    grZebes_801DA3E8();
}
void grZebes_801D8528(void) {}

void grZebes_801D852C(void)
{
    grZakoGenerator_801CAE04(0);
}

bool grZebes_801D8550(void)
{
    return false;
}

Ground_GObj* grZebes_801D8558(int id)
{
    Ground_GObj* gobj;
    StageCallbacks* cbs = &grZe_callbacks[id];
    gobj = Ground_801C14D0(id);
    if (gobj != NULL) {
        Ground* gp = GET_GROUND(gobj);
        gp->x8_callback = NULL;
        gp->xC_callback = NULL;
        GObj_SetupGXLink(gobj, grDisplay_801C5DB0, 3, 0);
        if (cbs->callback3 != NULL) {
            gp->x1C_callback = cbs->callback3;
        }
        if (cbs->callback0 != NULL) {
            cbs->callback0(gobj);
        }
        if (cbs->callback2 != NULL) {
            HSD_GObjProc_8038FD54(gobj, cbs->callback2, 4);
        }
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 256, id);
    }
    return gobj;
}

static const struct {
    Vec3 zero;
    Vec3 ref1;
    Vec3 ref2;
    Vec3 ref3;
    Vec3 ref4;
} grZe_803B7FF0 = {
    { 0.0f, 0.0f, 0.0f },
    { 8.2f, -4.55f, 0.0f },
    { 7.59f, 2.5f, 0.0f },
    { 8.589f, 1.215f, 0.0f },
    { 23.151f, 1.207f, 0.0f },
};

void grZebes_801D8644(HSD_GObj* gobj)
{
    Vec3 pos;
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    HSD_JObj* child_jobj;
    Item_GObj* mat_gobj;
    Item_GObj* mat_gobj2;
    PAD_STACK(8);

    gp->gv.zebes5.xF0 = (u32) grZebes_801D8558(7);
    Ground_801C2ED0(jobj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
    child_jobj = Ground_801C3FA4(gobj, 0x1E);
    mat_gobj = grMaterial_801C8CFC(7, 0, gp, child_jobj, NULL, fn_801DA9D8,
                                   NULL);
    grMaterial_801C8DE0(mat_gobj, 0.0f, -7.0f, 0.0f, 0.0f, 7.0f, 0.0f,
                        3.0f);
    grMaterial_801C8E08(mat_gobj);
    gp->gv.zebes5.xC4 = 0;
    gp->gv.zebes5.xC6 = 0x00FF;
    gp->gv.zebes5.xC8 = 0;
    gp->gv.zebes5.xCC = HSD_JObjGetTranslationX(child_jobj);
    gp->gv.zebes5.xD0 = 0.0f;
    gp->gv.zebes5.xD4 = 0.0f;
    gp->gv.zebes5.xD8 = 0.0f;
    gp->gv.zebes5.xDC = (u32) child_jobj;
    gp->gv.zebes5.xE0 = (u32) Ground_801C3FA4(gobj, 0x20);
    gp->gv.zebes5.xE4 = (u32) mat_gobj;
    gp->gv.zebes5.xE8 = 0x1C;
    gp->gv.zebes5.xEC = 0;
    gp->gv.zebes5.xF4 = 0;
    gp->gv.zebes5.xF6 = 0;
    pos = grZe_803B7FF0.zero;
    mat_gobj2 = grMaterial_801C8D44(0, 0, gp, &pos, 0, NULL, fn_801DAC90,
                                    NULL);
    grMaterial_801C8E08(mat_gobj2);
    gp->gv.zebes5.xFC = (u32) mat_gobj2;
    grZebes_801DC9DC((s32) gobj);
    gp->gv.zebes5.xF8 = (u32) grZakoGenerator_801CA394(
        (UNK_T) &grZe_803E1B90, 0xA, (UNK_T) grZebes_801DCB64, 1.0f);
    mpJointSetB10(0);
    Ground_801C2FE0((Ground_GObj*) gobj);
}

bool grZebes_801D8814(Ground_GObj* arg)
{
    return false;
}

void grZebes_801D881C(HSD_GObj* gobj)
{
    Vec3 sp80;
    Vec3 sp74;
    f32 col_heights[6];
    f32 col_x[6];
    Vec3 sp28;
    Vec3 sp1C;
    f32 sp18;
    f32 sp14;
    Ground* gp = GET_GROUND(gobj);
    HSD_GObj* secondary_gobj = (HSD_GObj*) gp->gv.zebes5.xF0;
    u8 result = grZebes_801DA528(gobj, &gp->gv.zebes5.xC8, 1, 2);

    if ((s32) gp->gv.zebes5.xEC != result) {
        gp->gv.zebes5.xEC = result;
        if (result == 1) {
            grAnime_801C7FF8(gobj, 0x15, 1, 1, 30.0f, 1.0f);
            grAnime_801C78FC(gobj, 0x15, 1U);
        } else if (result == 3) {
            grAnime_801C7FF8(gobj, 0x15, 1, 2, 0.0f, 1.0f);
            grAnime_801C78FC(gobj, 0x15, 1U);
        }
    }

    {
        s16 timer = *(s16*) &gp->gv.zebes5.xF8;
        *(s16*) &gp->gv.zebes5.xF8 = (s16) (timer - 1);
        if (timer < 0) {
            grZebes_801DAA08();
            {
                f32 base = grZe_804D6990->x08;
                *(s16*) &gp->gv.zebes5.xF8 =
                    (s16) ((grZe_804D6990->x0C - base) * HSD_Randf() + base);
            }
        }
    }

    {
        s32 popped = grZebes_801DB3CC(gobj);
        grZebes_801DC260();
        grZebes_801DBB60(gp->gv.zebes5.x100);
        grZebes_801DC408(gobj);

        switch (gp->gv.zebes5.xC4) {
        case 0:
            if (popped != 0) {
                gp->gv.zebes5.xC4 = 1;
                grAnime_801C8098(gobj, 0xE, 1, 3, 0.0f, 1.0f);
                grAnime_801C7980(gobj, 0xE, 1U);
                grAnime_801C8098(secondary_gobj, 1, 1, 3, 0.0f, 1.0f);
                grAnime_801C7980(secondary_gobj, 1, 1U);
            }
            break;
        case 1:
            if (grAnime_801C83D0(gobj, 0xE, 1) != 0) {
                f32 base;
                gp->gv.zebes5.xC4 = 2;
                base = grZe_804D6990->x00;
                gp->gv.zebes5.xC6 =
                    (s16) ((grZe_804D6990->x04 - base) * HSD_Randf() + base);
            }
            break;
        case 2:
            gp->gv.zebes5.xC6 =
                (s16) (gp->gv.zebes5.xC6 - 1);
            if (gp->gv.zebes5.xC6 < 0) {
                gp->gv.zebes5.xC4 = 3;
                grAnime_801C8098(gobj, 0xE, 1, 4, 0.0f, 1.0f);
                grAnime_801C7980(gobj, 0xE, 1U);
                grAnime_801C8098(secondary_gobj, 1, 1, 4, 0.0f, 1.0f);
                grAnime_801C7980(secondary_gobj, 1, 1U);
                gp->gv.zebes5.xF6 = 0;
                grZe_804D6994 = 0;
            }
            break;
        case 3:
        {
            s16 eq_counter;
            s32 divisor;
            s32 spawn_phase;
            gp->gv.zebes5.xF6 =
                (s16) (gp->gv.zebes5.xF6 + 1);
            divisor = grZe_804D6990->x10;
            eq_counter = gp->gv.zebes5.xF6;
            spawn_phase = eq_counter / divisor;
            if (eq_counter % divisor == 0) {
                s32 mirror = 6 - spawn_phase;
                if (spawn_phase < mirror) {
                    f32 scale_min = grZe_804D6990->x58;
                    u8* base = (u8*) grZe_8049F140 + spawn_phase * 0x24;
                    f32 rand = HSD_Randf();
                    grZebes_801DAE70(
                        spawn_phase, 4,
                        *(f32*) (base + 0x14),
                        *(f32*) (base + 0x18),
                        (grZe_804D6990->x5C - scale_min) * rand + scale_min);
                }
                if (spawn_phase <= mirror) {
                    u8* base2 = (u8*) grZe_8049F140 + mirror * 0x24;
                    f32 rand2 = HSD_Randf();
                    grZebes_801DAE70(
                        mirror, 4,
                        *(f32*) (base2 + 0x5C),
                        *(f32*) (base2 + 0x60),
                        (f32) (0.5 * rand2 + 1.0));
                }
            }
            if (grAnime_801C83D0(gobj, 0xE, 1) != 0) {
                int i;
                gp->gv.zebes5.xC4 = 0;
                for (i = 0; i < 20; i++) {
                    if (grZe_8049F170[i].active == 4) {
                        grZe_8049F170[i].active = 1;
                    }
                }
            }
            break;
        }
        }
    }

    sp80 = grZe_803B7FF0.ref1;
    sp74 = grZe_803B7FF0.ref2;
    {
        HSD_JObj* jobj = Ground_801C3FA4(gobj, 0xE);
        if (jobj != NULL) {
            lb_8000B1CC(jobj, &sp80, &grZe_8049F158[0]);
            lb_8000B1CC(jobj, &sp74, &grZe_8049F140[0]);
        }
    }

    if (gp->gv.zebes5.xC4 == 0) {
        int i;
        f32 colWidth;
        f32 left_x;

        mpJointListAdd(0);
        mpLib_80057424(0);

        colWidth = (grZe_8049F140[1].x - grZe_8049F140[0].x) / 5.0f;
        left_x = grZe_8049F140[0].x;

        col_heights[0] = -9999.0f;
        col_heights[1] = -9999.0f;
        col_heights[2] = -9999.0f;
        col_heights[3] = -9999.0f;
        col_heights[4] = -9999.0f;
        col_heights[5] = -9999.0f;

        {
            int j;
            grZe_BubbleEntry* entry = grZe_8049F170;
            for (j = 0; j < 20; j++, entry++) {
                if (entry->active == 1) {
                    f32 dx = entry->x - left_x;
                    f32 top = (f32) (1.8 * (f64) entry->size +
                                     (f64) entry->y);
                    {
                        f32 left_frac =
                            (f32) ((f64) dx - 0.9) / colWidth;
                        s32 col_left =
                            (s32) (0.5 + (f64) left_frac);
                        if (col_left > 5) {
                            col_left = 5;
                        } else if (col_left < 0) {
                            col_left = 0;
                        }
                        col_x[col_left] =
                            (f32) col_left * colWidth + left_x;
                        if (top > col_heights[col_left]) {
                            col_heights[col_left] = top;
                        }
                    }
                    {
                        f32 right_frac =
                            (f32) (0.9 + (f64) dx) / colWidth;
                        s32 col_right =
                            (s32) (0.5 + (f64) right_frac);
                        if (col_right > 5) {
                            col_right = 5;
                        } else if (col_right < 0) {
                            col_right = 0;
                        }
                        col_x[col_right] =
                            (f32) col_right * colWidth + left_x;
                        if (top > col_heights[col_right]) {
                            col_heights[col_right] = top;
                        }
                    }
                }
            }
        }

        sp28 = grZe_803B7FF0.ref3;
        sp1C = grZe_803B7FF0.ref4;

        {
            HSD_JObj* sima_jobj;
            sima_jobj = Ground_801C3FA4(gobj, 0xE);
            HSD_ASSERT(0x293, sima_jobj);
            lb_8000B1CC(sima_jobj, &sp28, &sp28);
        }
        col_x[0] = sp28.x;
        col_heights[0] = sp28.y;

        {
            HSD_JObj* sima_jobj;
            sima_jobj = Ground_801C3FA4(secondary_gobj, 1);
            HSD_ASSERT(0x299, sima_jobj);
            lb_8000B1CC(sima_jobj, &sp1C, &sp1C);
        }
        col_x[5] = sp1C.x;
        col_heights[5] = sp1C.y;

        for (i = 0; i < 5; i++) {
            if (i != 0) {
                f32 limit = col_heights[i + 1] - colWidth;
                if (col_heights[i] < limit) {
                    col_heights[i] = limit;
                }
            }
            if (i != 5) {
                f32 limit = col_heights[i] - colWidth;
                if (col_heights[i + 1] < limit) {
                    col_heights[i + 1] = limit;
                }
            }
        }

        {
            int k;
            for (k = 0; k <= 5; k++) {
                mpVtxSetPos(k, col_x[k], col_heights[k]);
            }
        }
        mpLib_80055E24(0);
    } else {
        mpLib_80057BC0(0);
    }

    Ground_801C4368(&sp18, &sp14);
    grZakoGenerator_801CA43C((void*) gp->gv.zebes5.xFC,
                             Ground_801C3FA4(gobj, 0xE), sp18);
    Ground_801C2FE0((Ground_GObj*) gobj);
    lb_800115F4();
}

void grZebes_801D90FC(Ground_GObj* arg) {}

void grZebes_801D9100(HSD_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    HSD_JObj* child_jobj;
    Item_GObj* mat_gobj;

    grAnime_801C8138(gobj, gp->map_id, 0);
    Ground_801C2ED0(jobj, gp->map_id);
    child_jobj = Ground_801C3FA4(gobj, 0xF);
    mat_gobj = grMaterial_801C8CFC(7, 0, gp, child_jobj, NULL, fn_801DA9F0,
                                   NULL);
    grMaterial_801C8DE0(mat_gobj, 0.0f, -5.0f, 0.0f, 0.0f, 5.0f, 0.0f,
                        2.0f);
    grMaterial_801C8E08(mat_gobj);
    gp->gv.zebes4.xC4 = 0xFF;
    gp->gv.zebes4.xC5 = 0;
    gp->gv.zebes4.xC6 = 0;
    gp->gv.zebes4.xC8 = HSD_JObjGetTranslationX(child_jobj);
    gp->gv.zebes4.xCC = 0.0f;
    gp->gv.zebes4.xD0 = 0.0f;
    gp->gv.zebes4.xD4 = 0.0f;
    gp->gv.zebes4.xD8 = (u32) child_jobj;
    gp->gv.zebes4.xDC = (u32) Ground_801C3FA4(gobj, 0x11);
    gp->gv.zebes4.xE0 = (u32) mat_gobj;
    gp->gv.zebes4.xE4 = 0xD;
    gp->gv.zebes4.xE8 = 0;
    gp->gv.zebes4.xEC =
        (u32) grZakoGenerator_801CA394((UNK_T) &grZe_803E1C80, 4,
                                       (UNK_T) grZebes_801DCBB0, 1.0f);
    Ground_801C2FE0((Ground_GObj*) gobj);
}

bool grZebes_801D9254(Ground_GObj* arg)
{
    return false;
}

static const Vec3 grZe_803B802C = { 24.1f, -4.6f, 0.0f };
static const Vec3 grZe_803B8038 = { 24.05f, 2.2f, 0.0f };

void grZebes_801D925C(HSD_GObj* gobj)
{
    Vec3 pos1;
    Vec3 pos2;
    f32 slope, intercept;
    HSD_JObj* jobj;
    Ground* gp = GET_GROUND(gobj);
    s32 result = grZebes_801DA528(gobj, &gp->gv.zebes4, 1, 2);

    if (gp->gv.zebes4.xE8 != result) {
        gp->gv.zebes4.xE8 = result;
        if (result == 1) {
            grAnime_801C7FF8(gobj, 6, 1, 1, 30.0f, 1.0f);
            grAnime_801C78FC(gobj, 6, 1U);
        } else if (result == 3) {
            grAnime_801C7FF8(gobj, 6, 1, 2, 0.0f, 1.0f);
            grAnime_801C78FC(gobj, 6, 1U);
        }
    }

    pos1 = grZe_803B802C;
    pos2 = grZe_803B8038;

    jobj = Ground_801C3FA4(gobj, 1);
    if (jobj != NULL) {
        lb_8000B1CC(jobj, &pos1, &grZe_8049F158[1]);
        lb_8000B1CC(jobj, &pos2, &grZe_8049F140[1]);
    }

    Ground_801C4368(&slope, &intercept);
    grZakoGenerator_801CA43C((void*) gp->gv.zebes4.xEC,
                             Ground_801C3FA4(gobj, 1), slope);
    Ground_801C2FE0((Ground_GObj*) gobj);
}

void grZebes_801D93D8(Ground_GObj* arg) {}

void grZebes_801D93DC(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grZebes_801D9408(Ground_GObj* arg)
{
    return false;
}

void grZebes_801D9410(Ground_GObj* gobj)
{
    f32 slope, intercept;
    HSD_JObj* jobj = GET_JOBJ(gobj);

    Ground_801C4368(&slope, &intercept);
    HSD_JObjSetTranslateY(jobj, slope);
    if (grAnime_801C83D0(gobj, 0, 7) != 0) {
        grZebes_801DA4FC(gobj);
    }
}

void grZebes_801D94EC(Ground_GObj* arg) {}

void fn_801D94F0(Ground_GObj* gobj)
{
    GET_GROUND(gobj)->gv.zebes.x0_b0 = false;
}

void grZebes_801D9508(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_GObj* map_a_gobj = Ground_801C2BA4(6);
    PAD_STACK(0x10);
    HSD_ASSERT(909, map_a_gobj);
    gp->gv.zebes.x4 = (u32) Ground_801C3FA4(map_a_gobj, 14);
    gp->gv.zebes.x8 = 1;
    gp->gv.zebes.xA = (s16) (HSD_Randi(600) + 3000);
    gp->gv.zebes.x0_b0 = true;
    Ground_801C10B8(gobj, fn_801D94F0);
}

bool grZebes_801D95B0(Ground_GObj* arg)
{
    return false;
}

void grZebes_801D95B8(Ground_GObj* gobj)
{
    Vec3 pos;
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    HSD_JObj* stored_jobj = (HSD_JObj*) gp->gv.zebes.x4;

    if (stored_jobj != NULL) {
        HSD_JObjGetTranslation2(stored_jobj, &pos);
        HSD_JObjSetTranslate(jobj, &pos);
    }
    if (!gp->gv.zebes.x0_b0) {
        if (gp->gv.zebes.xA > 0) {
            gp->gv.zebes.xA--;
            if (gp->gv.zebes.xA == 0) {
                if (gp->gv.zebes.x8 > 0) {
                    grAnime_801C8138(gobj, gp->map_id, 0);
                    gp->gv.zebes.x8 = -1;
                    return;
                }
                grAnime_801C8138(gobj, gp->map_id, 1);
                gp->gv.zebes.x8 = 1;
            }
        } else if (grAnime_801C83D0(gobj, 0, 7) != 0) {
            gp->gv.zebes.xA = (s16) (HSD_Randi(600) + 3000);
        }
    }
}

void grZebes_801D9754(Ground_GObj* arg) {}

void grZebes_801D9758(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    ftCo_800C07F8(gobj, 3, grZebes_801DCBFC);
    gp->gv.zebes.x4 = 1;
}

void grZebes_801D9798(HSD_GObj* gobj)
{
    Ground* gp = (Ground*) HSD_GObjGetUserData(gobj);
    grZe_YakumonoParam* yak = grZe_804D6990;
    grZe_AcidLevelEntry* entry;
    s16 delay_max, delay_min;
    s32 j;
    HSD_JObj* jobj;

    grAnime_801C8138(gobj, gp->map_id, 0);

    gp->gv.zebes5.xC4 = 0;

    entry = &yak->entries[gp->gv.zebes5.xC4];
    delay_max = entry->delay_max;
    delay_min = entry->delay_min;

    if (delay_max > delay_min) {
        s32 diff = delay_max - delay_min;
        delay_max = delay_min + ((diff != 0) ? HSD_Randi(diff) : 0);
    } else if (delay_max < delay_min) {
        s32 diff = delay_min - delay_max;
        delay_max += (diff != 0) ? HSD_Randi(diff) : 0;
    }

    gp->gv.zebes5.xC6 =
        (s16) (yak->entries[gp->gv.zebes5.xC4].base + delay_max);
    gp->gv.zebes5.xC8 = 0;
    gp->gv.zebes5.xCC = 0.0f;
    gp->gv.zebes5.xD0 = 0.0f;
    gp->gv.zebes5.xDC = 0;
    gp->x11_flags.b012 = 1;

    {
        grZe_AcidLevelEntry* ep = &grZe_804D6990->entries[1];
        j = 0;
        while (j < 0x1D &&
               (ep->base != 0 || ep->delay_min != 0 ||
                ep->delay_max != 0 || ep->level != 0))
        {
            ep++;
            j++;
        }
    }

    gp->gv.zebes5.xD8 =
        yak->x94 * HSD_Randf() + (f32) yak->entries[j].level;
    gp->gv.zebes5.xD4 = gp->gv.zebes5.xD8;

    jobj = Ground_801C3FA4(gobj, 0);
    if (jobj != NULL) {
        f32 level = gp->gv.zebes5.xD8;
        HSD_JObjSetTranslateY(jobj, level);
        Ground_801C438C(-55.0f + gp->gv.zebes5.xD8);
        Ground_801C438C(-55.0f + gp->gv.zebes5.xD8);
    }

    Ground_801C10B8(gobj, (void (*)(HSD_GObj*)) grZebes_801D9758);
}

bool grZebes_801D99D8(Ground_GObj* arg)
{
    return false;
}

void grZebes_801D99E0(HSD_GObj* gobj)
{
    Ground* gp = (Ground*) HSD_GObjGetUserData(gobj);
    grZe_YakumonoParam* yak = grZe_804D6990;
    s32 state = gp->gv.zebes5.xC8;

    switch (state) {
    case 0:
        break;
    case 1: {
        gp->gv.zebes5.xC6 =
            (s16) (gp->gv.zebes5.xC6 - 1);
        if (gp->gv.zebes5.xC6 < 0x78) {
            Camera_80030E44(1, NULL);
        }
        if (gp->gv.zebes5.xC6 < 0) {
            f32 target;
            f32 diff;
            f32 discriminant;

            gp->gv.zebes5.xD4 =
                yak->x94 * HSD_Randf() +
                (f32) yak->entries[gp->gv.zebes5.xC4].level;

            target = gp->gv.zebes5.xD4;
            if (target > yak->x8C) {
                gp->gv.zebes5.xD4 = yak->x8C;
            } else if (target < yak->x90) {
                gp->gv.zebes5.xD4 = yak->x90;
            }

            gp->gv.zebes5.xD0 = 0.0f;
            gp->gv.zebes5.xC8 = 2;
            gp->gv.zebes5.xC6 = 0;

            diff = gp->gv.zebes5.xD4 - gp->gv.zebes5.xD8;
            if (diff < 0.0f) {
                diff = -diff;
            }

            discriminant = (yak->x98 * yak->x98) -
                           (4.0f * diff) / yak->x9C;
            if (discriminant < 0.0f) {
                gp->gv.zebes5.xCC = 999.0f;
            } else {
                f32 root = sqrtf(discriminant);
                gp->gv.zebes5.xCC =
                    (f32) (0.5 * (f64) (yak->x9C * (yak->x98 - root)));
                if (gp->gv.zebes5.xCC < 0.0f) {
                    gp->gv.zebes5.xCC = 999.0f;
                }
            }

            if (gp->gv.zebes5.xD4 > gp->gv.zebes5.xD8) {
                Ground_801C53EC(0x61A80U);
            } else {
                Ground_801C53EC(0x61A81U);
            }
        }
        break;
    }
    case 2:
        gp->gv.zebes5.xC8 = 3;
        break;
    case 3: {
        f32 vel = gp->gv.zebes5.xD0;
        f32 accel = yak->x9C;
        f32 t = vel / accel;
        f32 delta = gp->gv.zebes5.xD4 - gp->gv.zebes5.xD8;
        f32 abs_delta;

        if (delta < 0.0f) {
            abs_delta = -delta;
        } else {
            abs_delta = delta;
        }

        if (abs_delta <
            (f32) -((0.5 * (f64) accel * (f64) (t * t)) -
                     (f64) (vel * t)))
        {
            gp->gv.zebes5.xC8 = 4;
        } else {
            f32 abs_delta2;
            if (delta < 0.0f) {
                abs_delta2 = -delta;
            } else {
                abs_delta2 = delta;
            }
            if (abs_delta2 < accel) {
                gp->gv.zebes5.xC8 = 4;
            } else {
                gp->gv.zebes5.xD0 = gp->gv.zebes5.xD0 + accel;
                if (gp->gv.zebes5.xD0 > gp->gv.zebes5.xCC) {
                    gp->gv.zebes5.xD0 = gp->gv.zebes5.xCC;
                }
            }
        }

        {
            f32 cur = gp->gv.zebes5.xD8;
            if (gp->gv.zebes5.xD4 > cur) {
                gp->gv.zebes5.xD8 = cur + gp->gv.zebes5.xD0;
            } else {
                gp->gv.zebes5.xD8 = cur - gp->gv.zebes5.xD0;
            }
        }
        break;
    }
    case 4: {
        f32 delta = gp->gv.zebes5.xD4 - gp->gv.zebes5.xD8;
        gp->gv.zebes5.xD0 = gp->gv.zebes5.xD0 - yak->x9C;

        if (gp->gv.zebes5.xD0 < 0.0f) {
            goto state4_done;
        } else {
            f32 abs_delta;
            if (delta < 0.0f) {
                abs_delta = -delta;
            } else {
                abs_delta = delta;
            }
            if (abs_delta < gp->gv.zebes5.xD0) {
                goto state4_done;
            }
        }

        goto state4_update_pos;

    state4_done:
        gp->gv.zebes5.xC8 = 1;
        gp->gv.zebes5.xD0 = 0.0f;

        gp->gv.zebes5.xC4 =
            (s16) (gp->gv.zebes5.xC4 + 1);
        {
            s16 idx = gp->gv.zebes5.xC4;
            if (idx == 0x1E) {
                gp->gv.zebes5.xC4 = 0;
            } else {
                grZe_AcidLevelEntry* e =
                    &yak->entries[idx];
                if (e->base == 0 && e->delay_min == 0 &&
                    e->delay_max == 0 && e->level == 0)
                {
                    gp->gv.zebes5.xC4 = 0;
                }
            }
        }

        {
            grZe_AcidLevelEntry* e2 =
                &yak->entries[gp->gv.zebes5.xC4];
            s16 delay_max = e2->delay_max;
            s16 delay_min = e2->delay_min;

            if (delay_max > delay_min) {
                s32 diff = delay_max - delay_min;
                delay_max = delay_min +
                            ((diff != 0) ? HSD_Randi(diff) : 0);
            } else if (delay_max < delay_min) {
                s32 diff = delay_min - delay_max;
                delay_max += (diff != 0) ? HSD_Randi(diff) : 0;
            }

            gp->gv.zebes5.xC6 =
                (s16) (yak->entries[gp->gv.zebes5.xC4].base +
                       delay_max);
        }

    state4_update_pos:
        {
            f32 cur = gp->gv.zebes5.xD8;
            if (gp->gv.zebes5.xD4 > cur) {
                gp->gv.zebes5.xD8 = cur + gp->gv.zebes5.xD0;
            } else {
                gp->gv.zebes5.xD8 = cur - gp->gv.zebes5.xD0;
            }
        }
        break;
    }
    }

    grZebes_801DA0C4(gp->gv.zebes5.xD8);
    grZebes_801DA254(gobj, gp->gv.zebes5.xD8);

    {
        HSD_JObj* jobj = Ground_801C3FA4(gobj, 0);
        if (jobj != NULL) {
            f32 level = gp->gv.zebes5.xD8;
            HSD_JObjSetTranslateY(jobj, level);
            Ground_801C438C(-55.0f + gp->gv.zebes5.xD8);
        }
    }
}

void grZebes_801D9F2C(Ground_GObj* arg) {}

void grZebes_801D9F30(Ground_GObj* gobj)
{
    Ground* gp;

    gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->gv.zebes2.xC4 = 0;
    gp->x11_flags.b012 = 1;
}

bool grZebes_801D9F7C(Ground_GObj* arg)
{
    return false;
}

void grZebes_801D9F84(Ground_GObj* gobj)
{
    f32 slope;
    f32 intercept;
    Ground* gp = GET_GROUND(gobj);

    switch (gp->gv.zebes2.xC4) {
    case 0:
        Ground_801C4368(&slope, &intercept);
        if (slope > 5.0f) {
            grAnime_801C7FF8(gobj, 3, 7, 2, 0.0f, 1.0f);
            grAnime_801C78FC(gobj, 3, 7);
            gp->gv.zebes2.xC4 = 1;
            Ground_801C53EC(0x61A85);
            return;
        }
        if (slope > -20.0f) {
            grAnime_801C7FF8(gobj, 3, 7, 1, 0.0f, 1.0f);
            grAnime_801C78FC(gobj, 3, 7);
            gp->gv.zebes2.xC4 = 1;
            Ground_801C53EC(0x61A85);
            return;
        }
        return;
    case 1:
        if (grAnime_801C83D0(gobj, 3, 7) != 0) {
            grAnime_801C7FF8(gobj, 3, 7, 0, 0.0f, 1.0f);
            gp->gv.zebes2.xC4 = 0;
        }
        break;
    }
}

void grZebes_801DA0C0(Ground_GObj* arg) {}

typedef struct grZe_ColorEntry {
    f32 threshold;
    f32 r;
    f32 g;
    f32 b;
} grZe_ColorEntry;

void grZebes_801DA0C4(f32 level)
{
    GXColor color;
    grZe_ColorEntry* table =
        (grZe_ColorEntry*) ((u8*) grZe_803E1A10 + 0x2D8);
    grZe_ColorEntry* ep = &table[1];
    u32 idx = 0;

    while (idx < 3U && level > ep->threshold) {
        ep++;
        idx++;
    }

    if ((s32) idx == 0) {
        color.r = (u8) table[1].r;
        color.g = (u8) table[1].g;
        color.b = (u8) table[1].b;
        color.a = 0xFF;
        return;
    }

    if (idx == 3) {
        color.r = (u8) table[3].r;
        color.g = (u8) table[3].g;
        color.b = (u8) table[3].b;
        color.a = 0xFF;
        return;
    }

    {
        f32 t0 = table[idx].threshold;
        f32 t = (level - t0) / (table[idx + 1].threshold - t0);

        if (Ground_801C2090(&color)) {
            f32 r0 = table[idx].r;
            color.r = (u8) (t * (table[idx + 1].r - r0) + r0);
            {
                f32 g0 = table[idx].g;
                color.g = (u8) (t * (table[idx + 1].g - g0) + g0);
            }
            {
                f32 b0 = table[idx].b;
                color.b = (u8) (t * (table[idx + 1].b - b0) + b0);
            }
            Ground_801C205C(&color);
        }
    }
}

void grZebes_801DA254(Ground_GObj* gobj, f32 level)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_LObj* lobj = (HSD_LObj*) gp->gv.zebes4.xDC;
    PAD_STACK(8);

    if (lobj == NULL) {
        HSD_GObj* lgobj = HSD_GObj_804D7824[4];
        if (lgobj != NULL) {
            lobj = (HSD_LObj*) lgobj->hsd_obj;
            while (lobj != NULL) {
                if (lobj->flags & 1) {
                    break;
                }
                lobj = HSD_LObjGetNext(lobj);
            }
        }
        gp->gv.zebes4.xDC = (u32) lobj;
    }

    if (lobj != NULL) {
        GXColor c1 = { 0xE6, 0xFF, 0x96, 0xFF };
        GXColor c2 = { 0x1E, 0x1E, 0x00, 0xFF };
        f32 t;
        GXColor result;

        t = (level - grZe_804D6990->x90) / (grZe_804D6990->x8C - grZe_804D6990->x90);
        result.r = (u8) (t * (f32) (c1.r - c2.r) + (f32) c2.r);
        result.g = (u8) (t * (f32) (c1.g - c2.g) + (f32) c2.g);
        result.b = (u8) (t * (f32) (c1.b - c2.b) + (f32) c2.b);
        result.a = 0xFF;
        HSD_LObjSetColor(lobj, result);
    }
}

void grZebes_801DA3E8(void)
{
    grZe_804D6998 = 0;
}

void grZebes_801DA3F4(Vec3* pos)
{
    Ground_GObj* gobj;
    HSD_JObj* jobj;

    if (grZe_804D6998 < 10 &&
        (gobj = grZebes_801D8558(5)) != NULL)
    {
        jobj = GET_JOBJ(gobj);
        if (jobj != NULL) {
            HSD_JObjSetTranslate(jobj, pos);
            grZe_804D6998 += 1;
            return;
        }
        Ground_801C4A08(gobj);
    }
}

void grZebes_801DA4FC(Ground_GObj* gobj)
{
    grZe_804D6998 -= 1;
    Ground_801C4A08(gobj);
}

u8 grZebes_801DA528(HSD_GObj* arg0, void* arg1, s32 arg2, s32 arg3)
{
    grZe_AcidState* st = (grZe_AcidState*) arg1;

    if (st->state != st->next) {
        st->state = st->next;
        switch (st->state) {
        case 0:
            grAnime_801C7FF8(arg0, st->anim_idx, 1, arg2, 0.0f, 1.0f);
            grMaterial_801C8E08(st->mat);
            st->timer = 0;
            st->offset = 0.0f;
            st->velocity = 0.0f;
            break;
        case 1:
            grAnime_801C78FC(arg0, st->anim_idx, 1);
            grMaterial_801C8E28((HSD_GObj*) st->mat);
            break;
        case 2: {
            f32 mn = grZe_804D6990->x50;
            st->timer = (s16) (((grZe_804D6990->x54 - mn) * HSD_Randf()) + mn);
            break;
        }
        case 3:
            grAnime_801C7FF8(arg0, st->anim_idx, 1, arg3, 0.0f, 1.0f);
            grAnime_801C78FC(arg0, st->anim_idx, 1);
            st->damage = 0.0f;
            break;
        }
    }

    switch (st->state) {
    case 0: {
        s16 t = st->timer;
        st->timer = t + 1;
        if ((f32) t > grZe_804D6990->x48) {
            st->timer = 0;
            st->damage -= 1.0f;
            if (st->damage < 0.0f) {
                st->damage = 0.0f;
            }
        }
        {
            f32 off = st->offset;
            f32 thresh = grZe_804D6990->x44;
            if (off > thresh) {
                st->velocity -= grZe_804D6990->x38;
            } else if (off < -thresh) {
                st->velocity += grZe_804D6990->x38;
            }
        }
        st->velocity *= (1.0f - grZe_804D6990->x3C);
        {
            f32 vel = st->velocity;
            f32 max_vel = grZe_804D6990->x34;
            if (vel > max_vel) {
                st->velocity = max_vel;
            } else if (vel < -max_vel) {
                st->velocity = -max_vel;
            }
        }
        st->offset += st->velocity;
        {
            f32 off = st->offset;
            f32 max_off = grZe_804D6990->x30;
            if (off > max_off) {
                st->offset = max_off;
            } else if (off < -max_off) {
                st->offset = -max_off;
            }
        }
        {
            f32 abs_off = st->offset;
            if (abs_off < 0.0f) {
                abs_off = -abs_off;
            }
            if (abs_off < grZe_804D6990->x44) {
                f32 abs_vel = st->velocity;
                if (abs_vel < 0.0f) {
                    abs_vel = -abs_vel;
                }
                if (abs_vel < grZe_804D6990->x40) {
                    st->offset = 0.0f;
                    st->velocity = 0.0f;
                }
            }
        }
        {
            f32 new_x = st->base_x + st->offset;
            HSD_JObjSetTranslateX(st->jobj1, new_x);
        }
        {
            f32 new_x = st->base_x + st->offset;
            HSD_JObjSetTranslateX(st->jobj2, new_x);
        }
        {
            f32 dmg = st->damage;
            f32 thr = grZe_804D6990->x4C;
            f32 frame;
            if (dmg > thr) {
                frame = 30.0f;
                st->next = 1;
                Ground_801C53EC(0x61A86);
                ftLib_80086C9C(1, 0x5A);
            } else {
                frame = (f32) ((f64) (dmg * thr) / 30.0);
            }
            grAnime_801C7B24(arg0, st->anim_idx, 1, frame);
        }
        break;
    }
    case 1:
        if (grAnime_801C83D0(arg0, st->anim_idx, 1) != 0) {
            st->next = 2;
        }
        break;
    case 2:
        st->timer -= 1;
        if (st->timer < 0) {
            st->next = 3;
        }
        break;
    case 3:
        if (grAnime_801C83D0(arg0, st->anim_idx, 1) != 0) {
            st->next = 0;
        }
        break;
    }

    return st->state;
}

void fn_801DA9D8(Item_GObj* arg0, Ground* gp, Vec3* pos, HSD_GObj* fobj,
                 f32 slope)
{
    gp->gv.zebes.xC.z += slope;
    gp->gv.zebes.xC.y = pos->x;
}

void fn_801DA9F0(Item_GObj* arg0, Ground* gp, Vec3* pos, HSD_GObj* fobj,
                 f32 slope)
{
    gp->gv.zebes.xC.y += slope;
    gp->gv.zebes.xC.x = pos->x;
}

s32 grZebes_801DAA08(void)
{
    s32 indices[20];
    s32 count = 0;
    s32 idx = 0;
    grZe_BubbleEntry* ptr = grZe_8049F170;
    s32* ip = indices;
    s32 ctr;

    for (ctr = 4; ctr != 0; ctr--) {
        if (ptr->active == 1 && idx != 0 && idx != 6 && ptr->unk04 == 0) {
            *ip = idx;
            ip++;
            count++;
        }
        ptr++;
        idx++;
        if (ptr->active == 1 && idx != 0 && idx != 6 && ptr->unk04 == 0) {
            *ip = idx;
            ip++;
            count++;
        }
        ptr++;
        idx++;
        if (ptr->active == 1 && idx != 0 && idx != 6 && ptr->unk04 == 0) {
            *ip = idx;
            ip++;
            count++;
        }
        ptr++;
        idx++;
        if (ptr->active == 1 && idx != 0 && idx != 6 && ptr->unk04 == 0) {
            *ip = idx;
            ip++;
            count++;
        }
        ptr++;
        idx++;
        if (ptr->active == 1 && idx != 0 && idx != 6 && ptr->unk04 == 0) {
            *ip = idx;
            ip++;
            count++;
        }
        ptr++;
        idx++;
    }

    if (count == 0) {
        return 0;
    }

    {
        s32 selected;
        HSD_JObj* new_jobj;

        if (count != 0) {
            selected = HSD_Randi(count);
        } else {
            selected = 0;
        }

        selected = indices[selected];
        new_jobj = Ground_801C13D0(2, 0);

        if (new_jobj != NULL) {
            grZe_BubbleEntry* sel = &grZe_8049F170[selected];
            HSD_JObj* parent_child;
            HSD_JObj* hsd_jobj;

            sel->unk04 = (u32) new_jobj;

            hsd_jobj = (HSD_JObj*) sel->gobj->hsd_obj;
            if (hsd_jobj == NULL) {
                parent_child = NULL;
            } else {
                parent_child = hsd_jobj->child;
            }

            HSD_JObjSetFlagsAll(parent_child, 0x10);
            HSD_JObjAddChild(parent_child, (HSD_JObj*) sel->unk04);

            {
                u8* dat = (u8*) grDatFiles_801C6330(2)->unk4->unk8;
                HSD_ShapeAnimJoint** sap =
                    *(HSD_ShapeAnimJoint***) (dat + 0x74);
                HSD_AnimJoint** ajp = *(HSD_AnimJoint***) (dat + 0x6C);
                HSD_MatAnimJoint** mjp =
                    *(HSD_MatAnimJoint***) (dat + 0x70);
                HSD_ShapeAnimJoint* sa;
                HSD_MatAnimJoint* ma;
                HSD_AnimJoint* aj;

                if (sap != NULL) {
                    sa = *sap;
                } else {
                    sa = NULL;
                }
                if (mjp != NULL) {
                    ma = *mjp;
                } else {
                    ma = NULL;
                }
                if (ajp != NULL) {
                    aj = *ajp;
                } else {
                    aj = NULL;
                }

                HSD_JObjAddAnimAll((HSD_JObj*) sel->unk04, aj, ma, sa);
            }

            HSD_JObjReqAnimAll((HSD_JObj*) sel->unk04, 0.0f);
            HSD_JObjAnimAll((HSD_JObj*) sel->unk04);
            grAnime_801C78FC(sel->gobj, 0, 7);
            return 1;
        }
    }
    return 0;
}

void fn_801DAC90(Item_GObj* arg0, Ground* arg1, Vec3* arg2, HSD_GObj* arg3,
                 f32 arg4)
{
    s32 found = -1;
    s32 i;

    for (i = 0; i < 20; i++) {
        if (grZe_8049F170[i].active == 1 && i != 0 && i != 6) {
            found = i;
            break;
        }
    }

    if (found != -1) {
        grZe_8049F170[found].active = 2;
        grZe_804D6994 = 0x78;
        grZe_8049F170[found].unk1C = 0.001f;
    }
}

void grZebes_801DAE70(s32 arg0, u8 arg1, f32 x, f32 y, f32 scale)
{
    grZe_BubbleEntry* entry = &grZe_8049F170[arg0];
    PAD_STACK(0x10);
    if (entry->active == 0) {
        if (entry->gobj == NULL) {
            Ground_GObj* gobj;

            entry->x = x;
            entry->y = y;
            entry->unk10 = 0.0f;
            entry->unk14 = 0.0f;
            entry->unk1C = scale;
            entry->size = scale;

            if (arg0 == 0 || arg0 == 6) {
                gobj = NULL;
            } else {
                gobj = grZebes_801D8558(3);
                if (gobj != NULL) {
                    HSD_JObj* jobj = GET_JOBJ(gobj);
                    Ground* gp = GET_GROUND(gobj);
                    Vec3 pos;

                    pos.x = x;
                    pos.y = y;
                    pos.z = 0.0f;
                    HSD_JObjSetTranslate(jobj, &pos);

                    pos.x = scale;
                    pos.y = scale;
                    pos.z = 0.001f;
                    HSD_JObjSetScale(jobj, &pos);

                    gp->gv.zebes3.xC4 = 0;
                    gp->gv.zebes3.xC8 = arg0;
                }
            }

            entry->active = arg1;
            entry->gobj = (HSD_GObj*) gobj;
            grZe_8049F170[arg0].unk04 = 0;
        }
    }
}

s32 grZebes_801DB088(Ground* gp, s32 arg1)
{
    grZe_BubbleEntry* entry = &grZe_8049F170[arg1];
    s32 result = 0;

    if (entry->active != 0) {
        HSD_GObj* bgobj = entry->gobj;

        if (bgobj != NULL) {
            Ground* bgp = (Ground*) HSD_GObjGetUserData(bgobj);

            if (bgp != NULL) {
                Item_GObj* mat = (Item_GObj*) bgp->gv.zebes3.xC4;

                if (mat != NULL) {
                    if (entry->active == 1) {
                        grMaterial_801C8E08(mat);
                    } else {
                        grMaterial_801C8E28((HSD_GObj*) mat);
                    }
                }

                {
                    f32 speed = grZe_804D6990->x68;
                    f32 target = entry->unk1C;
                    f32 current = entry->size;
                    f32 diff = target - current;

                    if (diff > speed) {
                        entry->size = current + speed;
                    } else if (diff < -speed) {
                        entry->size = current - speed;
                    } else {
                        entry->size = target;
                    }
                }

                if ((HSD_JObj*) entry->unk04 != NULL &&
                    grAnime_801C83D0(bgobj, 0, 7) != 0)
                {
                    HSD_JObjRemoveAll((HSD_JObj*) entry->unk04);
                    entry->unk04 = (u32) NULL;
                    {
                        HSD_JObj* jobj = (HSD_JObj*) bgobj->hsd_obj;
                        if (jobj != NULL) {
                            HSD_JObjClearFlagsAll(jobj, 0x10);
                        }
                    }
                }

                switch (entry->active) {
                case 3: {
                    s16 t = entry->timer;
                    entry->timer = (s16) (t - 1);
                    if (t < 0) {
                        Item_GObj* m = (Item_GObj*) bgp->gv.zebes3.xC4;
                        if (m != NULL) {
                            grMaterial_801C8CDC((HSD_GObj*) m);
                        }
                        Ground_801C4A08(bgobj);
                        {
                            Vec3 pos;
                            pos.x = entry->x;
                            pos.y = entry->y;
                            pos.z = 4.0f;
                            grLib_801C96F8(0x7530, 0x1E, &pos);
                        }
                        Ground_801C5440(gp, 0, 0x61A86);
                        entry->gobj = NULL;
                        entry->unk04 = (u32) NULL;
                        entry->active = 0;
                    }
                    break;
                }
                case 2: {
                    Item_GObj* m = (Item_GObj*) bgp->gv.zebes3.xC4;
                    if (m != NULL) {
                        grMaterial_801C8CDC((HSD_GObj*) m);
                    }
                    Ground_801C4A08(bgobj);
                    {
                        Vec3 pos;
                        pos.x = entry->x;
                        pos.y = entry->y;
                        pos.z = 4.0f;
                        grLib_801C96F8(0x7530, 0x1E, &pos);
                    }
                    entry->gobj = NULL;
                    entry->unk04 = (u32) NULL;
                    entry->active = 0;

                    if (arg1 < 7 && arg1 != 0 && arg1 != 6) {
                        f32 best_dist = 64.0f;
                        s32 best_idx = -1;
                        s32 j;

                        for (j = 7; j < 20; j++) {
                            if (grZe_8049F170[j].active == 1) {
                                f32 dx = grZe_8049F170[j].x - entry->x;
                                f32 dy = grZe_8049F170[j].y - entry->y;
                                f32 dist = dx * dx + dy * dy;
                                if (dist < best_dist) {
                                    best_idx = j;
                                    best_dist = dist;
                                }
                            }
                        }

                        if (best_idx != -1) {
                            grZe_BubbleEntry* src = &grZe_8049F170[best_idx];
                            entry->active = src->active;
                            entry->unk04 = src->unk04;
                            entry->size = src->size;
                            entry->unk1C = src->unk1C;
                            entry->gobj = src->gobj;
                            src->active = 0;
                            src->gobj = NULL;
                        } else {
                            for (j = 7; j < 20; j++) {
                                if (j != 0 && j != 6 &&
                                    grZe_8049F170[j].active == 1)
                                {
                                    grZe_8049F170[j].active = 3;
                                    grZe_8049F170[j].timer =
                                        (s16) (HSD_Randi(0x3C) + 0x0A);
                                }
                            }
                            result = 1;
                        }
                    }
                    break;
                }
                }
            }
        }
    }
    return result;
}

s32 grZebes_801DB3CC(HSD_GObj* gobj)
{
    grZe_BubbleEntry* base = grZe_8049F170;
    grZe_BubbleEntry* ptr;
    s32 popped = 0;
    int i;

    ptr = base;
    for (i = 0; i < 20; i++, ptr++) {
        if (ptr->active != 0) {
            if (grZebes_801DB088((Ground*) gobj, i) != 0) {
                popped = 1;
            }
        }
    }

    for (i = 0; i < 20; i++) {
        if (base[i].active != 0) {
            base[i].unk10 = 0.0f;
            base[i].unk14 = -grZe_804D6990->x84;
        }
    }

    {
        grZe_BubbleEntry* cur = base;
        int idx;
        for (idx = 0; idx < 7; idx++, cur++) {
            u8 active = cur->active;
            if (active == 1 || active == 4) {
                s32 neighbor_count = 0;
                if (idx != 0 && idx != 6) {
                    f32 fx = 0.0f;
                    f32 fy = 0.0f;
                    grZe_BubbleEntry* left = &base[idx - 1];
                    if (left->active != 0) {
                        f32 dy = left->y - cur->y;
                        f32 dx = left->x - cur->x;
                        f32 dist = dx * dx + dy * dy;
                        if (dist > 0.0f) {
                            dist = sqrtf(dist);
                        }
                        {
                            f32 col_r = grZe_804D6990->x74;
                            if (dist > col_r) {
                                f32 max_force = grZe_804D6990->x80;
                                f32 push = dist - col_r;
                                if (push > max_force) {
                                    push = max_force;
                                }
                                fx = (dx / dist) * push + 0.0f;
                                fy = (dy / dist) * push + 0.0f;
                            }
                        }
                        neighbor_count = 1;
                    }
                    {
                        grZe_BubbleEntry* right = &base[idx + 1];
                        if (right->active != 0) {
                            f32 dy2 = right->y - cur->y;
                            f32 dx2 = right->x - cur->x;
                            f32 dist2 = dx2 * dx2 + dy2 * dy2;
                            if (dist2 > 0.0f) {
                                dist2 = sqrtf(dist2);
                            }
                            {
                                f32 col_r2 = grZe_804D6990->x74;
                                if (dist2 > col_r2) {
                                    f32 max_force2 = grZe_804D6990->x80;
                                    f32 push2 = dist2 - col_r2;
                                    if (push2 > max_force2) {
                                        push2 = max_force2;
                                    }
                                    fx += (dx2 / dist2) * push2;
                                    fy += (dy2 / dist2) * push2;
                                }
                            }
                            neighbor_count += 1;
                        }
                    }
                    cur->x = cur->x + fx;
                    cur->y = cur->y + fy;
                    if (cur->active != 4 && neighbor_count != 2) {
                        cur->active = 3;
                        cur->timer = (s16) (HSD_Randi(0x3C) + 0xA);
                    }
                }
            }
        }
    }

    {
        int a;
        grZe_BubbleEntry* ea = base;
        for (a = 0; a < 19; a++, ea++) {
            if (ea->active != 0) {
                int b = a + 1;
                grZe_BubbleEntry* eb = &base[b];
                int rem = 20 - b;
                if (b < 20) {
                    for (; rem != 0; eb++, b++, rem--) {
                        if (eb->active != 0) {
                            f32 dy = eb->y - ea->y;
                            f32 dx = eb->x - ea->x;
                            f32 dist_sq = dx * dx + dy * dy;
                            f32 dist;
                            if (dist_sq > 0.0f) {
                                dist = sqrtf(dist_sq);
                            } else {
                                dist = dist_sq;
                            }
                            {
                                f32 raw_dist = dist;
                                f32 avg_size = ea->size + eb->size;
                                f32 col_rad =
                                    grZe_804D6990->x74 * 0.5f * avg_size;
                                if (dist < 0.001f) {
                                    dy = 0.001f;
                                    dx = 0.0f;
                                    raw_dist = 0.001f;
                                }
                                if (raw_dist < col_rad) {
                                    f32 strength =
                                        (f32) ((f64) (f32) (((f64) (col_rad /
                                                                     raw_dist) -
                                                              1.0) *
                                                             0.5) *
                                               0.9);
                                    if (a >= 7) {
                                        f32 vy = -dy * strength;
                                        f32 clamp_vy = vy;
                                        if (vy < 0.0f) {
                                            clamp_vy = 0.0f;
                                        }
                                        ea->unk10 += -dx * strength;
                                        ea->unk14 += clamp_vy;
                                    }
                                    if (b >= 7) {
                                        f32 vy2 = dy * strength;
                                        if (vy2 < 0.0f) {
                                            vy2 = 0.0f;
                                        }
                                        eb->unk10 += dx * strength;
                                        eb->unk14 += vy2;
                                    }
                                } else if (!(raw_dist <
                                             grZe_804D6990->x70 * 0.5f *
                                                 avg_size) &&
                                           raw_dist < grZe_804D6990->x6C *
                                                          0.5f * avg_size)
                                {
                                    f32 attract =
                                        grZe_804D6990->x78 / raw_dist;
                                    if (a >= 7) {
                                        ea->unk10 += dx * attract;
                                        ea->unk14 += dy * attract;
                                    }
                                    if (b >= 7) {
                                        eb->unk10 += -dx * attract;
                                        eb->unk14 += -dy * attract;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    {
        int k;
        grZe_BubbleEntry* p = base;
        for (k = 0; k < 20; k++, p++) {
            if (p->active != 0) {
                if (k == 0) {
                    p->unk10 = 0.0f;
                    p->unk14 = 0.0f;
                    p->x = grZe_8049F158[0].x;
                    p->y = grZe_8049F158[0].y;
                } else if (k == 6) {
                    p->unk10 = 0.0f;
                    p->unk14 = 0.0f;
                    p->x = grZe_8049F158[1].x;
                    p->y = grZe_8049F158[1].y;
                } else {
                    f32 old_y = p->y;
                    f32 old_x = p->x;
                    f32 new_y = old_y + p->unk14;
                    f32 new_x = old_x + p->unk10;
                    if (new_y < grZe_8049F140[0].y &&
                        new_x < grZe_8049F140[0].x)
                    {
                        if (old_y >= grZe_8049F140[0].y) {
                            new_y = grZe_8049F140[0].y;
                        } else if (old_x >= grZe_8049F140[0].x) {
                            new_x = grZe_8049F140[0].x;
                        }
                    }
                    if (new_y < grZe_8049F140[1].y &&
                        new_x > grZe_8049F140[1].x)
                    {
                        if (old_y >= grZe_8049F140[1].y) {
                            new_y = grZe_8049F140[1].y;
                        } else if (old_x <= grZe_8049F140[1].x) {
                            new_x = grZe_8049F140[1].x;
                        }
                    }
                    p->x = new_x;
                    p->y = new_y;
                    {
                        f32 vx = p->unk10;
                        f32 max_v = grZe_804D6990->x88;
                        if (vx > max_v) {
                            p->unk10 = max_v;
                        } else if (vx < -max_v) {
                            p->unk10 = -max_v;
                        }
                    }
                    {
                        f32 vy = p->unk14;
                        f32 max_v = grZe_804D6990->x88;
                        if (vy > max_v) {
                            p->unk14 = max_v;
                        } else if (vy < -max_v) {
                            p->unk14 = -max_v;
                        }
                    }
                }
            }
        }
    }

    return popped;
}

s32 grZebes_801DBB60(s32 arg)
{
    HSD_GObj* yaku = (HSD_GObj*) arg;
    grZe_BubbleEntry* bubbles = grZe_8049F170;
    s32 count = 0;
    s32 last_idx;
    f32 max_dist_sq = -1.0f;

    HSD_ASSERT(0x898, yaku);

    {
        int i;
        grZe_BubbleEntry* p = bubbles;
        for (i = 0; i < 20; i++, p++) {
            if (p->active == 1 && i != 0 && i != 6) {
                count++;
                last_idx = i;
                if (count > 2) break;
            }
        }
    }

    if (count == 0) {
        grMaterial_801C8E28(yaku);
        return 0;
    }

    if (count == 1) {
        grZe_BubbleEntry* entry = &bubbles[last_idx];
        grMaterial_801C8E08((Item_GObj*) yaku);
        grMaterial_801C8DE0((Item_GObj*) yaku, entry->x, entry->y, 0.0f,
                           entry->x, entry->y, 0.0f,
                           (f32)(2.0 * (f64) entry->size));
        return 1;
    }

    grMaterial_801C8E08((Item_GObj*) yaku);

    {
        s32 i;
        grZe_BubbleEntry* ei = bubbles;
        f32 x1, y1, x2, y2;

        for (i = 0; i < 20; i++, ei++) {
            if (ei->active == 1 && i != 0 && i != 6) {
                s32 j = i + 1;
                f32 ei_y = ei->y;
                f32 ei_x = ei->x;
                f32 ei_size = ei->size;
                s32 rem = 20 - j;
                grZe_BubbleEntry* ej = &bubbles[j];
                if (j < 20) {
                    for (; rem != 0; ej++, j++, rem--) {
                        if (ej->active == 1 && j != 0 && j != 6) {
                            f32 ej_x = ej->x;
                            f32 ej_y = ej->y;
                            f32 dx = ei_x - ej_x;
                            f32 dy = ei_y - ej_y;
                            f32 dist_sq = dx * dx + dy * dy;
                            if (max_dist_sq < dist_sq) {
                                f32 ej_size = ej->size;
                                max_dist_sq = dist_sq;
                                x1 = ei_x;
                                y1 = ei_y;
                                x2 = ej_x;
                                y2 = ej_y;
                                if (ei_size > ej_size) {
                                    last_idx = i;
                                } else {
                                    last_idx = j;
                                }
                            }
                        }
                    }
                }
            }
        }

        if (max_dist_sq < 0.0f) {
            HSD_ASSERT(0x8D2, 0);
        } else if (max_dist_sq < 0.0001f) {
            grZe_BubbleEntry* entry = &bubbles[last_idx];
            grMaterial_801C8DE0((Item_GObj*) yaku, entry->x, entry->y, 0.0f,
                               entry->x, entry->y, 0.0f,
                               (f32)(2.0 * (f64) entry->size));
            return 1;
        } else {
            f32 dy = y2 - y1;
            f32 dx = x2 - x1;
            f32 width = 1.0f;
            f32 inv_len_sq;
            int k = 0;
            grZe_BubbleEntry* bp = bubbles;

            inv_len_sq = 1.0f / (dx * dx + dy * dy);

            for (k = 0; k < 20; k++, bp++) {
                if (bp->active == 1 && k != 0 && k != 6) {
                    f32 by = bp->y;
                    f32 bx = bp->x;
                    f32 dpx = by - y1;
                    f32 dpy = bx - x1;
                    f32 t = inv_len_sq * (dx * dpy + dy * dpx);
                    f32 closest_dist;

                    if (t < 0.0f) {
                        closest_dist = dpy * dpy + dpx * dpx;
                    } else if (t > 1.0f) {
                        f32 ex = bx - x2;
                        f32 ey = by - y2;
                        closest_dist = ex * ex + ey * ey;
                    } else {
                        f32 cx = (dx * t + x1) - bx;
                        f32 cy = (dy * t + y1) - by;
                        closest_dist = cx * cx + cy * cy;
                    }

                    if (closest_dist > 0.0f) {
                        closest_dist = sqrtf(closest_dist);
                    }

                    {
                        f32 check = (f32)(2.0 * (f64) bp->size +
                                         (f64) closest_dist);
                        if (check > width) {
                            if (t < 0.5f) {
                                f32 dpx2 = bp->x - x1;
                                f32 dpy2 = bp->y - y1;
                                f32 dist2 = dpx2 * dpx2 + dpy2 * dpy2;
                                f32 new_width;
                                if (dist2 > 0.0f) {
                                    dist2 = sqrtf(dist2);
                                }
                                {
                                    f32 sum = dist2 + width;
                                    new_width = (f32)(0.5 *
                                        (2.0 * (f64) bp->size + (f64) sum));
                                }
                                if (dist2 > 0.001f) {
                                    f32 ratio = (new_width - width) / dist2;
                                    x1 += ratio * (bp->x - x1);
                                    y1 += ratio * (bp->y - y1);
                                }
                                {
                                    f32 ddy = y1 - y2;
                                    f32 ddx = x1 - x2;
                                    f32 dist3 = ddx * ddx + ddy * ddy;
                                    f32 expand;
                                    if (dist3 > 0.0f) {
                                        dist3 = sqrtf(dist3);
                                    }
                                    expand = new_width - width;
                                    width = new_width;
                                    {
                                        f32 ratio2 = expand / dist3;
                                        x2 += ddx * ratio2;
                                        y2 += ddy * ratio2;
                                    }
                                }
                            } else {
                                f32 dpx2 = bp->x - x2;
                                f32 dpy2 = bp->y - y2;
                                f32 dist2 = dpx2 * dpx2 + dpy2 * dpy2;
                                f32 new_width;
                                if (dist2 > 0.0f) {
                                    dist2 = sqrtf(dist2);
                                }
                                {
                                    f32 sum = dist2 + width;
                                    new_width = (f32)(0.5 *
                                        (2.0 * (f64) bp->size + (f64) sum));
                                }
                                if (dist2 > 0.001f) {
                                    f32 ratio = (new_width - width) / dist2;
                                    x2 += ratio * (bp->x - x2);
                                    y2 += ratio * (bp->y - y2);
                                }
                                {
                                    f32 ddy = y2 - y1;
                                    f32 ddx = x2 - x1;
                                    f32 dist3 = ddx * ddx + ddy * ddy;
                                    f32 expand;
                                    if (dist3 > 0.0f) {
                                        dist3 = sqrtf(dist3);
                                    }
                                    expand = new_width - width;
                                    width = new_width;
                                    {
                                        f32 ratio2 = expand / dist3;
                                        x1 += ddx * ratio2;
                                        y1 += ddy * ratio2;
                                    }
                                }
                            }
                            dy = y2 - y1;
                            dx = x2 - x1;
                            inv_len_sq = 1.0f / (dx * dx + dy * dy);
                        }
                    }
                }
            }

            grMaterial_801C8DE0((Item_GObj*) yaku, x1, y1, 0.0f, x2, y2,
                               0.0f, width);
            return 1;
        }
    }
    HSD_ASSERT(0x943, 0);
}

void grZebes_801DC260(void)
{
    grZe_BubbleEntry* entry = grZe_8049F170;
    int i;
    PAD_STACK(8);

    for (i = 0; i < 20; i++, entry++) {
        if (entry->active != 0) {
            HSD_GObj* gobj = entry->gobj;
            if (gobj != NULL) {
                Vec3 v;
                HSD_JObj* jobj = GET_JOBJ(gobj);

                v.x = entry->x;
                v.y = entry->y;
                v.z = 0.0f;
                HSD_JObjSetTranslate(jobj, &v);

                v.x = entry->size;
                v.y = entry->size;
                v.z = entry->size;
                HSD_JObjSetScale(jobj, &v);
            }
        }
    }
}

void grZebes_801DC408(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);

    if (gp->gv.zebes5.xC4 == 0) {
        if (grZe_804D6994 != 0) {
            grZe_804D6994 -= 1;
            return;
        }

        gp->gv.zebes5.xF6 = (s16) (gp->gv.zebes5.xF6 - 1);
        if (gp->gv.zebes5.xF6 < 0) {
            s32 count = 0;
            s32 first_free = -1;
            s32 i;

            for (i = 0; i < 20; i++) {
                if (grZe_8049F170[i].active != 0) {
                    count++;
                } else if (first_free == -1) {
                    first_free = i;
                }
            }

            if (count < 15) {
                Vec3* base = grZe_8049F140;
                f32 y_min = base[2].y;
                f32 bubble_r = grZe_804D6990->x74;
                f32 x_base = base[2].x + bubble_r;
                f32 x_range = -((2.0f * bubble_r) - (base[1].x - base[2].x));
                f32 y_range = base[1].y - y_min;
                f32 rscale = HSD_Randf();
                f32 ry = HSD_Randf();

                grZebes_801DAE70(first_free, 1,
                    x_range * HSD_Randf() + x_base,
                    y_range * ry + y_min,
                    (f32) (0.5 * (f64) rscale + 1.0));
                grZe_8049F170[first_free].size = 0.001f;
                Ground_801C53EC(0x61A83);
            }

            {
                f32 f_min = grZe_804D6990->x60;
                f32 f_max = grZe_804D6990->x64;
                s32 t_min = (s32) f_min;
                s16 timer = (s16) f_max;

                if ((s32) f_max > (s32) f_min) {
                    s32 range = timer - t_min;
                    timer = t_min + (range != 0 ? HSD_Randi(range) : 0);
                } else if (timer < t_min) {
                    s32 range = t_min - timer;
                    timer += (range != 0 ? HSD_Randi(range) : 0);
                }
                gp->gv.zebes5.xF6 = timer;
            }
        }
    }
}

void grZebes_801DC744(s32 arg0, s32 arg1)
{
    f32 scales[7];
    Vec3* base = grZe_8049F140;
    s32 i;

    scales[0] = grZe_803B8044.scales[0];
    scales[1] = grZe_803B8044.scales[1];
    scales[2] = grZe_803B8044.scales[2];
    scales[3] = grZe_803B8044.scales[3];
    scales[4] = grZe_803B8044.scales[4];
    scales[5] = grZe_803B8044.scales[5];
    scales[6] = grZe_803B8044.scales[6];

    if (arg0 & 1) {
        f32 x_start = base[2].x;
        f32 y_start = base[2].y;
        f32 x_step = (base[3].x - x_start) / 6.0f;
        f32 y_step = (base[3].y - y_start) / 6.0f;
        f32* sp = &scales[0];

        for (i = 0; i < 7; i++, sp++) {
            grZebes_801DAE70(i, arg1,
                x_step * (f32) i + x_start,
                y_step * (f32) i + y_start,
                *sp);
        }
    }

    if (arg0 & 2) {
        f32 p_x = base[2].x;
        f32 y_min = base[2].y;
        f32 bubble_r = grZe_804D6990->x74;
        f32 x_base = p_x + bubble_r;
        f32 x_range = (base[1].x - p_x) - 2.0f * bubble_r;
        f32 y_range = base[1].y - y_min;
        f64 mid_x = 0.5 * x_range + x_base;
        f64 lo_x = 0.2 * x_range + x_base;
        f64 hi_x, lo_y, hi_y, near_max_y, max_y;

        grZebes_801DAE70(7, arg1,
            (f32) mid_x,
            (f32) (0.5 * y_range + y_min),
            1.0f);

        hi_y = 0.8 * y_range + y_min;
        grZebes_801DAE70(8, arg1,
            (f32) lo_x, (f32) hi_y, 1.2f);

        hi_x = 0.8 * x_range + x_base;
        lo_y = 0.2 * y_range + y_min;
        grZebes_801DAE70(9, arg1,
            (f32) hi_x, (f32) lo_y, 1.1f);

        grZebes_801DAE70(10, arg1,
            (f32) hi_x, (f32) hi_y, 1.1f);

        grZebes_801DAE70(11, arg1,
            (f32) mid_x, (f32) lo_y, 1.2f);

        near_max_y = 0.9 * y_range + y_min;
        grZebes_801DAE70(12, arg1,
            (f32) mid_x, (f32) near_max_y, 1.3f);

        grZebes_801DAE70(13, arg1,
            (f32) mid_x, (f32) near_max_y, 1.3f);

        max_y = (f64) y_min + (f64) y_range;
        grZebes_801DAE70(14, arg1,
            (f32) (0.6 * x_range + x_base),
            (f32) max_y, 1.1f);

        grZebes_801DAE70(15, arg1,
            (f32) lo_x, (f32) max_y, 1.0f);
    }
}


const grZe_BubbleConfig grZe_803B8044 = {
    { 1.0f, 1.1f, 1.0f, 1.2f, 1.1f, 1.0f, 1.0f },
    {
        { 7.59f, 2.5f, 0.0f },
        { 24.05f, 2.2f, 0.0f },
        { 8.2f, -4.55f, 0.0f },
        { 24.1f, -4.6f, 0.0f },
    },
};

void grZebes_801DC9DC(s32 arg0)
{
    int i;
    PAD_STACK(0x30);

    grZe_804D6994 = 0;

    for (i = 0; i < 20; i++) {
        grZe_8049F170[i].active = 0;
        grZe_8049F170[i].gobj = NULL;
    }

    grZe_8049F158[0] = grZe_803B8044.positions[2];
    grZe_8049F158[1] = grZe_803B8044.positions[3];
    grZe_8049F140[0] = grZe_803B8044.positions[0];
    grZe_8049F140[1] = grZe_803B8044.positions[1];

    grZebes_801DC744(3, 1);

    for (i = 0; i < 100; i++) {
        grZebes_801DB3CC((HSD_GObj*) arg0);
    }
}

bool grZebes_801DCB64(Vec3* vec, int val)
{
    if (val < 9) {
        grLib_801C96F8(0xBA, 0, vec);
    } else {
        grLib_801C96F8(0xBB, 0, vec);
    }
    return false;
}

bool grZebes_801DCBB0(Vec3* vec, int val)
{
    if (val < 3) {
        grLib_801C96F8(0xBA, 0, vec);
    } else {
        grLib_801C96F8(0xBB, 0, vec);
    }
    return false;
}

bool grZebes_801DCBFC(Ground_GObj* gobj, HSD_GObj* fobj, void* arg)
{
    f32 unused;
    f32 unused2;
    Vec3 pos;
    Vec3 prev;
    f32 slope, intercept;

    Ground_801C4368(&slope, &intercept);
    ftLib_80086644(fobj, &pos);
    ftLib_80086684(fobj, &prev);
    prev.y += intercept;
    if (pos.y < slope) {
        *(void**) arg = ((HSD_GObj*) grZe_804D6990)->user_data;
        if (prev.y > slope) {
            Ground_801C43A4(&pos);
            Ground_801C53EC(0x61A82);
            Ground_801C53EC(0x66);
        }
        return true;
    }
    return false;
}

DynamicsDesc* grZebes_801DCCB8(enum_t arg)
{
    return false;
}

bool grZebes_801DCCC0(Vec3* arg, int arg0, HSD_JObj* jobj)
{
    return true;
}

f32 grZebes_801DCCC8(void)
{
    f32 slope, intercept;
    Ground_801C4368(&slope, &intercept);
    return grZe_804DB0B0 + slope;
}
