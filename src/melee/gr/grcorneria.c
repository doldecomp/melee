#include "grcorneria.h"

#include "grcorneria.static.h"

#include "placeholder.h"

#include "baselib/forward.h"

#include "baselib/sislib.h"
#include "cm/camera.h"
#include "ft/ftlib.h"
#include "gm/gm_1832.h"
#include "gm/gm_1A45.h"
#include "gm/gmregclear.h"
#include "gr/granime.h"
#include "gr/grdatfiles.h"
#include "gr/grdisplay.h"
#include "gr/grlib.h"
#include "gr/grmaterial.h"
#include "gr/ground.h"
#include "gr/grvenom.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "gr/stage.h"
#include "gr/types.h"
#include "if/ifcoget.h"
#include "if/ifstatus.h"
#include "it/item.h"
#include "it/items/itarwinglaser.h"
#include "it/items/itgreatfoxlaser.h"
#include "lb/lb_00B0.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbspdisplay.h"
#include "mp/mplib.h"
#include "pl/player.h"

#include <baselib/controller.h>
#include <baselib/debug.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/jobj.h>
#include <baselib/random.h>

typedef struct grCn_StageData {
    /* 0x00 */ f32 x0;
    /* 0x04 */ f32 x4;
    /* 0x08 */ f32 x8;
    /* 0x0C */ f32 xC;
    /* 0x10 */ f32 x10;
    /* 0x14 */ f32 x14;
    /* 0x18 */ f32 x18;
    /* 0x1C */ f32 x1C;
    /* 0x20 */ f32 x20;
    /* 0x24 */ f32 x24;
    /* 0x28 */ f32 x28;
    /* 0x2C */ f32 x2C;
    /* 0x30 */ f32 x30;
    /* 0x34 */ f32 x34;
    /* 0x38 */ f32 x38;
    /* 0x3C */ f32 x3C;
    /* 0x40 */ f32 x40;
    /* 0x44 */ f32 x44;
    /* 0x48 */ f32 x48;
    /* 0x4C */ f32 x4C;
    /* 0x50 */ u8 pad50[0x18];
    /* 0x68 */ f32 x68;
    /* 0x6C */ u8 pad6C[0x4];
    /* 0x70 */ f32 x70;
    /* 0x74 */ s32 x74;
    /* 0x78 */ s32 x78;
    /* 0x7C */ s32 x7C;
    /* 0x80 */ s32 x80;
    /* 0x84 */ s32 x84;
    /* 0x88 */ f32 x88;
} grCn_StageData;

static grCn_StageData* grCn_804D69A0;
static u32 grCn_804D69A4;
static int grCn_804D69A8;
static bool grCn_804D69AC;
static int grCn_804D69B0;

static S16Vec3 grCn_803E1D38[] = {
    { 0x0003, 0x0003, 0x0000 }, { 0x0004, 0x0003, 0x0000 },
    { 0x0000, 0x000D, 0x0000 }, { 0x0001, 0x000E, 0x0000 },
    { 0x0002, 0x000F, 0x0000 }, { 0x0005, 0x0010, 0x0000 },
    { 0x0006, 0x0011, 0x0000 }, { 0x0007, 0x0012, 0x0000 },
};

static HSD_GObj* arwing_gobjs[3] = { 0 };
static int arwing_types[3] = { 0 };
static int arwing_groups[3] = { 0 };

StageCallbacks grCn_803E1D8C[] = {
    {
        grCorneria_801DD620,
        grCorneria_801DD64C,
        grCorneria_801DD654,
        grCorneria_801DD658,
        0x00000000,
    },
    {
        grCorneria_801DDAC4,
        grCorneria_801DDCE8,
        grCorneria_801DE024,
        grCorneria_801DE4BC,
        0x00000000,
    },
    {
        grCorneria_801DE8E4,
        grCorneria_801DEC00,
        grCorneria_801DED50,
        grCorneria_801DF8CC,
        0x00000000,
    },
    {
        grCorneria_801DD674,
        grCorneria_801DD9A0,
        grCorneria_801DD9A8,
        grCorneria_801DDAC0,
        0x80000000,
    },
    {
        grCorneria_801E0140,
        grCorneria_801E01A0,
        grCorneria_801E01A8,
        grCorneria_801E03C4,
        0x00000000,
    },
    {
        grCorneria_801E0DE4,
        grCorneria_801E0E0C,
        grCorneria_801E0E14,
        grCorneria_801E0E3C,
        0x20000000,
    },
    {
        grCorneria_801DFBF0,
        grCorneria_801DFC1C,
        grCorneria_801DFC24,
        grCorneria_801DFC28,
        0x00000000,
    },
    {
        grCorneria_801E0C3C,
        grCorneria_801E0D28,
        grCorneria_801E0D30,
        grCorneria_801E0DE0,
        0x40000000,
    },
    {
        grCorneria_801DFC2C,
        grCorneria_801DFC90,
        grCorneria_801DFC98,
        grCorneria_801DFEB4,
        0x00000000,
    },
    {
        grCorneria_801DFEB8,
        grCorneria_801DFF18,
        grCorneria_801DFF20,
        grCorneria_801E013C,
        0x00000000,
    },
    {
        grCorneria_801DF8D0,
        grCorneria_801DFBC4,
        grCorneria_801DFBCC,
        grCorneria_801DFBEC,
        0x00000000,
    },
    {
        grCorneria_801E1054,
        grCorneria_801E1058,
        grCorneria_801E1060,
        grCorneria_801E12CC,
        0x00000000,
    },
    {
        grCorneria_801E0F30,
        grCorneria_801E0F64,
        grCorneria_801E0F6C,
        grCorneria_801E1030,
        0x00000000,
    },
    {
        grCorneria_Arwing_801DE4C0,
        grCorneria_801DE560,
        grCorneria_801DE568,
        grCorneria_801DE8E0,
        0x00000000,
    },
    {
        grCorneria_Arwing_801DE4C0,
        grCorneria_801DE560,
        grCorneria_801DE568,
        grCorneria_801DE8E0,
        0x00000000,
    },
    {
        grCorneria_Arwing_801DE4C0,
        grCorneria_801DE560,
        grCorneria_801DE568,
        grCorneria_801DE8E0,
        0x00000000,
    },
    {
        grCorneria_Arwing_801DE4C0,
        grCorneria_801DE560,
        grCorneria_801DE568,
        grCorneria_801DE8E0,
        0x00000000,
    },
    {
        grCorneria_Arwing_801DE4C0,
        grCorneria_801DE560,
        grCorneria_801DE568,
        grCorneria_801DE8E0,
        0x00000000,
    },
    {
        grCorneria_Arwing_801DE4C0,
        grCorneria_801DE560,
        grCorneria_801DE568,
        grCorneria_801DE8E0,
        0x00000000,
    },
};

StageData grCn_803E1F08 = {
    CORNERIA,
    grCn_803E1D8C,
    "/GrCn",
    grCorneria_801DD350,
    grCorneria_801DD2C0,
    grCorneria_801DD478,
    grCorneria_801DD508,
    grCorneria_801DD52C,
    grCorneria_801E2EE4,
    grCorneria_801E2EEC,
    0x00000001,
    (void*) &grCn_803E1D38,
    8,
};

typedef struct {
    int data[3];
} grCn_Entry;

void grCorneria_801DCCFC(void)
{
    s32 stage;
    s32 imin, imax;
    PAD_STACK(16);

    arwing_gobjs[0] = NULL;
    arwing_types[0] = 0;
    arwing_groups[0] = 0;
    arwing_gobjs[1] = NULL;
    arwing_types[1] = 0;
    arwing_groups[1] = 0;
    arwing_gobjs[2] = NULL;
    arwing_types[2] = 0;
    arwing_groups[2] = 0;

    stage = Stage_80225194();
    switch (stage) {
    case 0xE9:
    case 0x47:
        grCn_804D69B0 = 1;
        break;
    default:
        grCn_804D69B0 = (imax = 0);
        break;
    }

    if (grCn_804D69B0 == 1) {
        grCn_804D69A8 = 0x78;
        return;
    }

    imin = grCn_804D69A0->x3C;
    imax = grCn_804D69A0->x40;
    if (imax > imin) {
        s32 range = imax - imin;
        imax = imin + (range != 0 ? HSD_Randi(range) : 0);
    } else if (imax < imin) {
        s32 range = imin - imax;
        imax += (range != 0 ? HSD_Randi(range) : 0);
    }
    grCn_804D69A8 = imax;
}

static inline s32 grCn_RandRange(s32 imax, s32 imin)
{
    if (imax > imin) {
        s32 range = imax - imin;
        imax = imin + (range != 0 ? HSD_Randi(range) : 0);
    } else if (imax < imin) {
        s32 range = imin - imax;
        imax += (range != 0 ? HSD_Randi(range) : 0);
    }
    return imax;
}

static inline int grCn_CheckFar(Vec3* pos)
{
    s32 kind = grCorneria_801E0A74(&pos->x);
    switch (kind) {
    case 4:
    case 9:
        pos->x -= 300.0f;
        kind = grCorneria_801E0A74(&pos->x);
        switch (kind) {
        case 4:
        case 9:
            return 0;
        }
    }
    return 1;
}

static inline void grCn_SpawnArwing(s32 slot, u32 type_id, int group)
{
    grCn_804D69A4 = slot;
    arwing_types[slot] = type_id;
    arwing_groups[slot] = group;
    arwing_gobjs[grCn_804D69A4] = grCorneria_801DD534(1);
}

static inline u32 grCn_PickUniqueType(s32 slot, int range, int base)
{
    int rand_id = arwing_types[slot];
    while (rand_id == arwing_types[0] || rand_id == arwing_types[1] ||
           rand_id == arwing_types[2])
    {
        rand_id = HSD_Randi(range) + base;
    }
    return rand_id;
}

void grCorneria_801DCE1C(void)
{
    Vec3 pos;
    UNUSED u8 pad[4];
    Vec3 pos2;

    if (Stage_80225194() != 0x46) {
        if (grCn_804D69B0 == 0) {
            if (arwing_gobjs[0] == NULL) {
                grCn_804D69A8--;
                if (grCn_804D69A8 <= 0) {
                    int far;
                    int type_id;
                    int group;
                    int* types;
                    int* groups;

                    grCorneria_801DDD4C(&pos);
                    far = grCn_CheckFar(&pos);

                    {
                        type_id = *(types = &arwing_types[0]);
                        while (type_id == *types) {
                            int var_r0 = far == 1 ? 9 : 13;
                            int var_r3_2;
                            if (var_r0 != 0) {
                                var_r3_2 = HSD_Randi(far == 1 ? 9 : 13);
                            } else {
                                var_r3_2 = 0;
                            }
                            type_id = var_r3_2 + 1;
                        }

                        if (*(groups = &arwing_groups[0]) == 4) {
                            group = 1;
                        } else {
                            group = HSD_Randf() > grCn_804D69A0->x4C ? 1 : 4;
                        }

                        grCn_804D69A4 = 0;
                        *types = type_id;
                        *groups = group;
                        arwing_gobjs[grCn_804D69A4] = grCorneria_801DD534(1);
                    }
                }
            } else {
                grCn_804D69A8 = grCn_RandRange((s32) grCn_804D69A0->x48,
                                               (s32) grCn_804D69A0->x44);
            }
        } else {
            {
                HSD_GObj** gobjs = &arwing_gobjs[0];
                int count = 0;
                for (count = 0; count < 3; count++) {
                    if (gobjs[count] == NULL) {
                        break;
                    }
                }

                if (count < 3) {
                    grCn_804D69A8--;
                    if (grCn_804D69A8 <= 0) {
                        bool has_near = false;
                        int i;

                        for (i = 0; i < 3; i++) {
                            if (i != count) {
                                switch (arwing_types[i]) {
                                case 1:
                                case 2:
                                case 3:
                                case 4:
                                case 5:
                                case 6:
                                case 7:
                                case 8:
                                case 9:
                                    if (gobjs[i] != NULL) {
                                        has_near = true;
                                    }
                                }
                            }
                        }

                        if (has_near == 0) {
                            int type_id = arwing_types[count];
                            while (type_id == arwing_types[0] ||
                                   type_id == arwing_types[1] ||
                                   type_id == arwing_types[2])
                            {
                                type_id = HSD_Randi(13) + 1;
                            }
                            grCn_804D69A4 = count;
                            arwing_types[count] = type_id;
                            arwing_groups[count] = count + 1;
                            arwing_gobjs[grCn_804D69A4] =
                                grCorneria_801DD534(1);
                        } else {
                            grCorneria_801DDD4C(&pos2);
                            if (grCn_CheckFar(&pos2) == 0) {
                                int type_id = arwing_types[count];
                                while (type_id == arwing_types[0] ||
                                       type_id == arwing_types[1] ||
                                       type_id == arwing_types[2])
                                {
                                    type_id = HSD_Randi(4) + 10;
                                }
                                grCn_804D69A4 = count;
                                arwing_types[count] = type_id;
                                arwing_groups[count] = count + 1;
                                arwing_gobjs[grCn_804D69A4] =
                                    grCorneria_801DD534(1);
                            }
                        }
                    }
                } else {
                    grCn_804D69A8 = 10;
                }
            }
        }
    } else {
        arwing_gobjs[0] = NULL;
        arwing_gobjs[1] = NULL;
        arwing_gobjs[2] = NULL;
    }
}

void grCorneria_801DD2C0(int unused)
{
    void* obj;
    int rand;
    PAD_STACK(32);

    obj = Ground_801C2BA4(3);
    if (obj != NULL) {
        obj = GET_JOBJ(obj);
        if (obj != NULL) {
            HSD_JObjSetFlagsAll(obj, JOBJ_HIDDEN);
        }
    }
    grCorneria_801E0678();
    obj = grCorneria_801DD534(12);
    if (gm_8017E7E0() != 0) {
        rand = HSD_Randi(4) + 4;
    } else {
        rand = HSD_Randi(4);
    }
    grCorneria_801E0F34(obj, rand);
    grCn_804D69AC = true;
}

extern Vec3 grCn_803B8090;

void grCorneria_801DD350(void)
{
    Ground* gp;
    u8 _pad[8];
    Vec3 light_pos;
    u8 _pad2[12];

    grCn_804D69A0 = (grCn_StageData*) Ground_801C49F8();
    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 1;
    grCorneria_801DD534(7);
    grCorneria_801DD534(3);
    grCorneria_801DCCFC();
    (gp = (grCorneria_801DD534(8)->user_data))->gv.corneria.xC4.value = 1;
    (gp = (grCorneria_801DD534(9)->user_data))->gv.corneria.xC4.value = 1;
    (gp = (grCorneria_801DD534(4)->user_data))->gv.corneria.xC4.value = 1;
    grCorneria_801DD534(0xB);
    Ground_801C39C0();
    Ground_801C3BB4();
    light_pos = grCn_803B8090;
    lb_80011A50(&light_pos, -1, 1.0f, 0.0f, 1.0471976f, -100000.0f, 100000.0f,
                100000.0f, -100000.0f);
    grCn_804D69AC = true;
    mpLib_80057BC0(0);
    mpLib_80057BC0(1);
    mpLib_80057BC0(2);
    mpLib_80057BC0(5);
    mpLib_80057BC0(6);
    mpLib_80057BC0(7);
}

void grCorneria_801DD478(void)
{
    HSD_GObj* gobj;
    Ground* gp;

    gobj = Ground_801C2BA4(11);
    if (gobj != NULL) {
        Ground_801C4A08(gobj);
    }
    gobj = Ground_801C2BA4(8);
    if (gobj != NULL) {
        Ground_801C4A08(gobj);
    }
    gobj = Ground_801C2BA4(9);
    if (gobj != NULL) {
        Ground_801C4A08(gobj);
    }
    gobj = Ground_801C2BA4(4);
    if (gobj != NULL) {
        Ground_801C4A08(gobj);
    }
    gobj = grCorneria_801DD534(8);
    gp = GET_GROUND(gobj);
    gp->gv.corneria.xC5 = 0;
    grCn_804D69AC = false;
    Ground_801C53EC(0x55737);
}

void grCorneria_801DD508(void)
{
    grZakoGenerator_801CAE04(NULL);
}

bool grCorneria_801DD52C(void)
{
    return false;
}

#pragma push
#pragma dont_inline on
HSD_GObj* grCorneria_801DD534(int arg0)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grCn_803E1D8C[arg0];

    gobj = Ground_GetStageGObj(arg0);

    if (gobj != NULL) {
        Ground* gp = gobj->user_data;
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
            HSD_GObj_SetupProc(gobj, callbacks->callback2, 4);
        }
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grcorneria.c", 0x26A,
                 arg0);
    }

    return gobj;
}
#pragma pop

void grCorneria_801DD620(Ground_GObj* gobj)
{
    grAnime_801C8138((HSD_GObj*) gobj, GET_GROUND(gobj)->map_id, 0);
}

bool grCorneria_801DD64C(Ground_GObj* arg)
{
    return false;
}

void grCorneria_801DD654(Ground_GObj* arg) {}

void grCorneria_801DD658(Ground_GObj* arg) {}

void grCorneria_801DD65C(Ground_GObj* gobj)
{
    GET_GROUND(gobj)->gv.corneria.xC4.flags.b0 = false;
}

static Vec3 grCn_803E1F70[5] = {
    { -274.14, 48.58, 0 }, { -200.81, -20.1, 0 }, { -59.31, -58.74, 0 },
    { -40.19, -73.77, 0 }, { 78.44, -73.48, 0 },
};

static Vec3 grCn_803E1FAC[5] = { 0 };

static grZakoGenerator_Spawn grCn_803E1FE8[1] = {
    { -59, -58, 18, -22, -73, 0 },
};
static grZakoGenerator_Spawn grCn_803E2000[2] = {
    { -81, -21, 28, 14, -59, 128 },
    { 14, -59, 128, 0, -75, 173 },
};

static int grCn_803E2030[] = {
    -1, 0, 1, 2, 3, 4, 5, 6, 6, 6, 7, 8, 9, 10,
};

static Vec3 lbl_803E2068[] = {
    { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 },    { 0, 0, 0 },  { 0, 0, 0 },
    { 0, 0, 0 }, { 0, 0, 0 }, { -40, 10, 0 }, { 15, 5, 0 }, { 190, -10, 0 },
    { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 },    { 0, 0, 0 },
};

static int grCn_803E2110[] = { 2, 2, 2, 2, 10 };

void grCorneria_801DD674(Ground_GObj* ground_gobj)
{
    Vec3 translate;
    HSD_JObj* jobj;
    u32 unused;

    Ground* gr = GET_GROUND(ground_gobj);
    Ground_801C2ED0(ground_gobj->hsd_obj, gr->map_id);
    gr->gv.corneria.xC4.flags.b0 = 1;
    gr->gv.corneria.xC4.flags.b1 = 0;
    gr->gv.corneria.base_x = 0.0f;
    gr->gv.corneria.base_y = 250.0f;
    gr->gv.corneria.xD0 = 0.0f;
    gr->gv.corneria.offset_x = 0.0f;
    gr->gv.corneria.offset_y.val = 0.0f;
    gr->gv.corneria.xE4.x = 0.0f;
    gr->gv.corneria.xE4.y = 0.0f;
    gr->gv.corneria.xE4.z = 0.0f;
    gr->gv.corneria.xF0 = 0.0f;
    gr->gv.corneria.xF4 = 0.0f;
    gr->gv.corneria.xF8 = 0.0f;
    gr->gv.corneria.x104 = 0;
    gr->x10_flags.b5 = 1;
    grAnime_801C8138(ground_gobj, gr->map_id, 0);
    grAnime_801C8780(ground_gobj, 3, 0, 0.0f, 1.0f);
    gr->gv.corneria.x128 = grCorneria_801DD534(0);
    jobj = ground_gobj->hsd_obj;
    translate.x = gr->gv.corneria.base_x + gr->gv.corneria.offset_x;
    translate.y = gr->gv.corneria.base_y + gr->gv.corneria.offset_y.val;
    translate.z = 0.0f;
    HSD_JObjSetTranslate(jobj, &translate);
    grCorneria_801E1878(ground_gobj);
    Ground_801C39C0();
    Ground_801C3BB4();
    gr->gv.corneria.x108 = 0;
    gr->gv.corneria.x10C = 0;
    gr->gv.corneria.x118 = 0;
    gr->gv.corneria.x11A = 0;
    gr->gv.corneria.x110 = 0;
    gr->gv.corneria.x114 = 0.0f;
    gr->gv.corneria.left_cannon =
        grMaterial_801C8CFC(0, 0, gr, Ground_801C3FA4(ground_gobj, 2),
                            fn_801E12D0, fn_801E12D4, 0);
    grMaterial_801C8DE0(gr->gv.corneria.left_cannon, 4.0f, 0.0f, 0.0f, 16.0f,
                        0.0f, 0.0f, 4.0f);
    grMaterial_801C8E08(gr->gv.corneria.left_cannon);
    gr->gv.corneria.right_cannon =
        grMaterial_801C8CFC(0, 2, gr, Ground_801C3FA4(ground_gobj, 3),
                            fn_801E12D0, fn_801E12D4, 0);
    grMaterial_801C8E08(gr->gv.corneria.right_cannon);
    grMaterial_801C8DE0(gr->gv.corneria.right_cannon, 4.0f, 0.0f, 0.0f, 16.0f,
                        0.0f, 0.0f, 4.0f);
    HSD_JObjClearFlags(Ground_801C3FA4(ground_gobj, 6), JOBJ_HIDDEN);
    HSD_JObjSetFlags(Ground_801C3FA4(ground_gobj, 5), JOBJ_HIDDEN);
    gr->gv.corneria.xC8 =
        grZakoGenerator_801CA394(grCn_803E1FE8, 1, grCorneria_801E2454, 0.3f);
    gr->gv.corneria.xCC =
        grZakoGenerator_801CA394(grCn_803E2000, 2, grCorneria_801E2480, 0.3f);
    Ground_801C10B8(ground_gobj, grCorneria_801DD65C);
    gr->x11_flags.b012 = 1;
    gr->gv.corneria.x12C = Ground_801C3FA4(ground_gobj, 8);
}

bool grCorneria_801DD9A0(Ground_GObj* arg)
{
    return false;
}

void grCorneria_801DD9A8(Ground_GObj* gobj)
{
    Ground* gp = HSD_GObjGetUserData(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    int i;

    if (!gp->gv.corneria.xC4.flags.b0) {
        f32 speed;

        grCorneria_801E1970(gobj);
        grCorneria_801E2228(gobj);

        speed = -35.0f * Ground_801C0498() - gp->gv.corneria.xD0;
        grZakoGenerator_801CA43C(gp->gv.corneria.xC8, Ground_801C3FA4(gobj, 0),
                                 speed);

        speed = -35.0f * Ground_801C0498() - gp->gv.corneria.xD0;
        grZakoGenerator_801CA43C(gp->gv.corneria.xCC, Ground_801C3FA4(gobj, 0),
                                 speed);

        grCorneria_801E1348(gobj);
        grCorneria_801E0E40();
        grCorneria_801DCE1C();
    }

    for (i = 0; i < 5; i++) {
        lb_8000B1CC(jobj, &grCn_803E1F70[i], &grCn_803E1FAC[i]);
    }

    Ground_801C2FE0(gobj);
    grCorneria_801E1878(gobj);
    grCorneria_801E2110();
    lb_800115F4();
}

void grCorneria_801DDAC0(Ground_GObj* arg) {}

void grCorneria_801DDAC4(Ground_GObj* gobj)
{
    HSD_GObj** data = arwing_gobjs;
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    f32 scale;

    arwing_gobjs[gp->gv.arwing.xC8 = grCn_804D69A4] = gobj;
    {
        s32 idx = arwing_groups[gp->gv.arwing.xC8];
        HSD_GObj* arwing = grCorneria_801DD534(grCn_803E2110[idx]);
        if (arwing != NULL) {
            GET_GROUND(arwing)->x10_flags.b2 = 0;
            {
                Ground* agp = GET_GROUND(arwing);
                if (agp != NULL) {
                    agp->gv.arwing.xC8 = gp->gv.arwing.xC8;
                }
            }
        }
    }
    scale = Ground_801C0498();
    HSD_JObjSetScaleX(jobj, scale * grCn_804D69A0->x70);
    HSD_JObjSetScaleY(jobj, scale);
    HSD_JObjSetScaleZ(jobj, scale);
    gp->gv.arwing.xD4 = 1;
    gp->gv.arwing.xD8 = 0.0f;
}

bool grCorneria_801DDCE8(Ground_GObj* arg)
{
    return false;
}

void grCorneria_801DDCF0(Vec3* vec)
{
    Ground* gp;
    HSD_GObj* gobj;
    PAD_STACK(4);

    gobj = Ground_801C2BA4(3);
    gp = GET_GROUND(gobj);
    vec->x = gp->gv.corneria.offset_x - gp->gv.corneria.xE4.x;
    vec->y = gp->gv.corneria.offset_y.val - gp->gv.corneria.xE4.y;
    vec->z = 0.0f;
}

void grCorneria_801DDD4C(Vec3* vec)
{
    Ground* gp;
    HSD_GObj* gobj;
    PAD_STACK(4);

    gobj = Ground_801C2BA4(3);
    gp = GET_GROUND(gobj);
    vec->x = gp->gv.corneria.base_x + gp->gv.corneria.offset_x;
    vec->y = gp->gv.corneria.base_y + gp->gv.corneria.offset_y.val;
    vec->z = 0.0f;
}

void grCorneria_801DDDA8(HSD_GObj* gobj, Vec3* vec)
{
    Ground* gp2;
    Ground* gp;
    HSD_JObj* jobj;
    u8 unused[12];
    Vec3 pos;
    int idx;
    PAD_STACK(4);

    if (gobj != NULL) {
        gp = gobj->user_data;
        gp2 = Ground_801C2BA4(3)->user_data;
        jobj = Ground_801C3FA4(gobj, 4);
        lb_8000B1CC(jobj, NULL, &pos);
        idx = arwing_types[gp->gv.arwing.xC8];
        vec->x = gp2->gv.arwing.xDC + (-pos.z + lbl_803E2068[idx].x);
        vec->y = pos.y + lbl_803E2068[idx].y;
        vec->z = pos.x + lbl_803E2068[idx].z;
    } else {
        vec->z = 0.0f;
        vec->y = 0.0f;
        vec->x = 0.0f;
    }

    if (vec->y <= 100.0f) {
        vec->y = 100.0f;
    }
}

extern Vec3 grCn_803B809C;

void grCorneria_801DDE88(HSD_GObj* gobj)
{
    Vec3 sp2C;
    Vec3 sp20;
    Ground* gp = GET_GROUND(gobj);

    sp2C = grCn_803B809C;
    if (gobj != NULL) {
        Ground* gp2 = HSD_GObjGetUserData(gobj);
        Ground* ship = GET_GROUND(Ground_801C2BA4(3));
        s32 idx;
        lb_8000B1CC(Ground_801C3FA4(gobj, 4), NULL, &sp20);
        idx = arwing_types[gp2->gv.arwing.xC8];
        sp2C.x = ship->gv.corneria.offset_x + (-sp20.z + lbl_803E2068[idx].x);
        sp2C.y = sp20.y + lbl_803E2068[idx].y;
        sp2C.z = sp20.x + lbl_803E2068[idx].z;
    } else {
        sp2C.z = 0.0f;
        sp2C.y = 0.0f;
        sp2C.x = 0.0f;
    }
    if (sp2C.y <= 100.0f) {
        sp2C.y = 100.0f;
    }
    switch (gp->gv.arwing.xD8) {
    case 0:
        if (grCorneria_801DEC08(&sp2C) == 0) {
            lbAudioAx_800237A8(0x55730, 0x7F, 0x40);
            gp->gv.arwing.xD8 = 1;
        }
        break;
    case 1:
        if (grCorneria_801DEC94(&sp2C) == 0) {
            gp->gv.arwing.xD8 = 2;
            return;
        }
        break;
    case 2:
        if (grCorneria_801DEC94(&sp2C) == 1) {
            lbAudioAx_800237A8(0x55732, 0x7F, 0x40);
            gp->gv.arwing.xD8 = 3;
        }
        break;
    }
}

extern Vec3 grCn_803B80A8;

/// Bounds shared by #grCorneria_801DE024 and #grCorneria_801DED50. Volatile
/// reads keep MWCC from duplicating them later in the literal pool.
static const f32 grCn_ArwingMinX = -10.0f;
static const f32 grCn_ArwingMaxX = 2000.0f;

static inline void grCorneria_801DE024_inline(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    Vec3 pos = grCn_803B80A8;
    grCorneria_801DDDA8(gobj, &pos);
    switch (gp->gv.arwing.xD8) {
    case 0:
        if (*(volatile const f32*) &grCn_ArwingMinX < pos.x &&
            pos.x < *(volatile const f32*) &grCn_ArwingMaxX)
        {
            lbAudioAx_800237A8(0x55731, 0x7F, 0x40);
            gp->gv.arwing.xD8 = 1;
        }
        break;
    case 1:
        if (pos.x < *(volatile const f32*) &grCn_ArwingMinX ||
            *(volatile const f32*) &grCn_ArwingMaxX < pos.x)
        {
            lbAudioAx_800237A8(0x55732, 0x7F, 0x40);
            gp->gv.arwing.xD8 = 2;
        }
        break;
    }
}

void grCorneria_801DE024(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Vec3 translate;
    HSD_GObj* ship_gobj = Ground_801C2BA4(3);
    HSD_JObj* ship_jobj = GET_JOBJ(ship_gobj);
    if (ship_jobj != NULL) {
        f32 y = HSD_JObjGetTranslationY(ship_jobj);
        HSD_JObjSetTranslateY(jobj, y);
        {
            HSD_JObj* j1 = Ground_801C3FA4(gobj, 1);
            f32 y1 = HSD_JObjGetTranslationY(j1) - 349.0f;
            HSD_JObjSetTranslateY(j1, y1);
        }
    }
    {
        if (arwing_gobjs[gp->gv.arwing.xC8] == gobj) {
            if (gp->gv.arwing.xD4 == 1) {
                gp->gv.arwing.xD4 = 0;
                {
                    s32 idx = arwing_types[gp->gv.arwing.xC8];
                    grAnime_801C8138(gobj, gp->map_id, grCn_803E2030[idx]);
                }
                return;
            }
            {
                s32 idx = arwing_types[gp->gv.arwing.xC8];
                if (idx < 10) {
                    if (idx >= 1) {
                        goto arwing_near_type;
                    }
                    goto arwing_type_done;
                } else {
                    if (idx >= 14) {
                        goto arwing_type_done;
                    }
                    goto arwing_far_type;
                }
            arwing_near_type:
                grCorneria_801DDE88(gobj);
                goto arwing_type_done;
            arwing_far_type: {
                HSD_JObjSetRotationY(jobj, -1.5707964f);
                grCorneria_801DE024_inline(gobj);
                {
                    f32 vf = grCorneria_801E2EA0();
                    HSD_JObj* j0;
                    if (vf > 0.0f) {
                        vf = 0.0f;
                    }
                    if (vf < -150.0f) {
                        vf = -150.0f;
                    }
                    j0 = Ground_801C3FA4(gobj, 0);
                    HSD_JObjGetTranslation(j0, &translate);
                    translate.y = ABS(vf);
                    HSD_JObjSetTranslate(j0, &translate);
                }
            }
            arwing_type_done:;
            }
            if (grAnime_801C83D0(gobj, 0, 7) != 0) {
                arwing_gobjs[gp->gv.arwing.xC8] = 0;
                Ground_801C4A08(gobj);
            }
        } else {
            Ground_801C4A08(gobj);
        }
    }
}

void grCorneria_801DE4BC(Ground_GObj* arg) {}

static int grCn_803E214C[6][2] = {
    { -1, -1 }, { 1, 0 }, { 2, 2 }, { 4, 4 }, { 5, 5 }, { -1, -1 },
};

static int grCn_803E217C[] = { 0x0D, 0x0D, 0x0E, 0x0F, 0x10 };

static int grCn_803E2190[5] = { 0, 0, 1, 2, 5 };

void grCorneria_Arwing_801DE4C0(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    int group;
    int joint_id;

    Ground_801C2ED0(jobj, gp->map_id);
    gp->gv.arwing.xC8 = grCn_804D69A4;
    gp->gv.arwing.xD0 = 0;
    gp->gv.arwing.xDC = 0.0f;
    gp->gv.arwing.xE0.z = 0.0f;
    gp->gv.arwing.xE0.y = 0.0f;
    gp->gv.arwing.xE0.x = 0.0f;
    group = arwing_groups[gp->gv.arwing.xC8];
    joint_id = grCn_803E2190[group];
    mpJointListAdd(joint_id);

    Ground_801C2ED0(jobj, gp->map_id);
}

bool grCorneria_801DE560(Ground_GObj* arg)
{
    return false;
}

void grCorneria_801DE568(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);

    if (arwing_gobjs[gp->gv.arwing.xC8] != NULL) {
        Ground_UpdateStarFoxArwingVisibility(gp, jobj, 10.0F);
        {
            f32 scale = Ground_801C0498();
            {
                f32 s = scale * grCn_804D69A0->x70;
                HSD_JObjSetScaleX(jobj, s);
            }
            {
                f32 s = scale * grCn_804D69A0->x70;
                HSD_JObjSetScaleY(jobj, s);
            }
            {
                f32 s = scale * grCn_804D69A0->x70;
                HSD_JObjSetScaleZ(jobj, s);
            }
        }
        Ground_801C2FE0(gobj);
    } else {
        mpLib_80057BC0(grCn_803E2190[arwing_groups[gp->gv.arwing.xC8]]);
        Ground_801C4A08(gobj);
    }
}

void grCorneria_801DE8E0(Ground_GObj* arg) {}

void grCorneria_801DE8E4(Ground_GObj* gobj)
{
    // grCn_Data* data = &grCn_803E1D38;
    Ground* gp = gobj->user_data;
    HSD_JObj* jobj = GET_JOBJ(gobj);
    f32 scale;

    scale = Ground_801C0498();
    gp->gv.corneria2.xC8 = grCn_804D69A4;
    Ground_ClearStarFoxArwingGObjs(gp);
    Ground_AnimateStarFoxArwingWithBackground(gobj);

    switch (arwing_types[gp->gv.corneria2.xC8]) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9: {
        HSD_GObj* arwing = grCorneria_801DD534(
            grCn_803E217C[arwing_groups[gp->gv.corneria2.xC8]]);
        Ground_LinkStarFoxArwing(gp, arwing);
        break;
    }
    case 10:
    case 11:
    case 12:
    case 13: {
        Ground_AttachStarFoxArwingModel(gobj, gp,
                                        arwing_gobjs[gp->gv.corneria2.xC8], 4);
        break;
    }
    default:
        Ground_DisableStarFoxArwingGObjs(gp);
        break;
    }
    HSD_JObjSetScaleX(jobj, scale * grCn_804D69A0->x70);
    HSD_JObjSetScaleY(jobj, scale * grCn_804D69A0->x70);
    HSD_JObjSetScaleZ(jobj, scale * grCn_804D69A0->x70);
    Ground_ResetStarFoxArwingState(gp);
    gp->gv.corneria2.xF8 = (s32) grCn_804D69A0->x68;
    gp->gv.corneria2.xFC = 0;
    gp->gv.corneria2.x100 = HSD_Randi(2);
}

bool grCorneria_801DEC00(Ground_GObj* arg)
{
    return false;
}

bool grCorneria_801DEC08(Vec3* pos)
{
    /// @todo #Stage_IsOutsideBlastZone here perturbs #grCorneria_801DED50.
    if (pos->x > Stage_GetBlastZoneRightOffset()) {
        return true;
    }
    if (pos->x < Stage_GetBlastZoneLeftOffset()) {
        return true;
    }
    if (pos->y > Stage_GetBlastZoneTopOffset()) {
        return true;
    }
    if (pos->y < Stage_GetBlastZoneBottomOffset()) {
        return true;
    }
    return false;
}
s32 grCorneria_801DEC94(Vec3* pos)
{
    if (pos->z > -30.0f) {
        /// @todo #Stage_IsOutsideBlastZoneWithMargin breaks the fallthrough.
        if (pos->x > Stage_GetBlastZoneRightOffset() - 30.0f) {
            return 1;
        }
        if (pos->x < Stage_GetBlastZoneLeftOffset() + 30.0f) {
            return 1;
        }
        if (pos->y > Stage_GetBlastZoneTopOffset() - 30.0f) {
            return 1;
        }
        if (pos->y < Stage_GetBlastZoneBottomOffset() + 30.0f) {
            return 1;
        }
    }
    return 0;
}

extern Vec3 grCn_803B80B4;

static int grCn_803E21B0[] = { 1, 1, 1, 1, 1 };

static inline int randi(int max)
{
    if (max != 0) {
        return HSD_Randi(max);
    }
    return 0;
}

static inline int get_grp_off(Ground_GObj* gobj)
{
    s32 grp_off = -1;
    {
        int* groups = arwing_groups;
        int g = groups[GET_GROUND(gobj)->gv.corneria2.xC8];
        switch (g) {
        case 0:
            break;
        case 1:
        case 2:
        case 3:
            grp_off = 0;
            break;
        case 4:
            grp_off = 1;
            break;
        }
    }
    return grp_off;
}

static inline Ground* get_arwing_ground(HSD_GObj* gobj)
{
    return GET_GROUND(gobj);
}

void grCorneria_801DED50(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = gobj->hsd_obj;
    HSD_JObj* arwing;
    HSD_GObj* far_arwing;
    Ground* ship_gp;
    Ground* arwing_gp;
    Vec3 pos = grCn_803B80B4;
    PAD_STACK(6);

    if (grCn_804D69AC) {
        return;
    }

    if (arwing_gobjs[gp->gv.corneria2.xC8] != NULL) {
        if (arwing_groups[gp->gv.corneria2.xC8] == 4) {
            arwing = Ground_801C3FA4(gobj, 1);
            HSD_JObjSetRotationZ(arwing, 0.0f);
        }
        switch (arwing_types[gp->gv.corneria2.xC8]) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9: {
            HSD_JObjSetRotationY(jobj, -1.5707964f);
            switch (gp->gv.corneria2.xF4) {
            case 0:
                if (gp->gv.corneria2.xF8 <= 0) {
                    s32 new_state = HSD_Randi(5) + 1;
                    int group_offset = -1;
                    gp->gv.corneria2.xF4 = new_state;
                    {
                        int group =
                            arwing_groups[GET_GROUND(gobj)->gv.corneria2.xC8];
                        switch (group) {
                        case 0:
                            break;
                        case 1:
                        case 2:
                        case 3:
                            group_offset = 0;
                            break;
                        case 4:
                            group_offset = 1;
                            break;
                        }
                    }
                    {
                        int anim_arg =
                            grCn_803E214C[gp->gv.corneria2.xF4][group_offset];
                        grAnime_801C8098(
                            gobj,
                            grCn_803E21B0[arwing_groups[gp->gv.corneria2.xC8]],
                            7, anim_arg, 0.0f, 1.0f);
                    }
                } else {
                    HSD_JObjSetRotationZ(
                        Ground_801C3FA4(
                            gobj, grCn_803E21B0
                                      [arwing_groups[gp->gv.corneria2.xC8]]),
                        0.0f);
                }
                gp->gv.corneria2.xF8 -= 1;
                break;
            case 1:
            case 2:
            case 3:
            case 4:
                if (grAnime_801C83D0(gobj, 0, 7) != 0) {
                    gp->gv.corneria2.xF4 = 0;
                    gp->gv.corneria2.xF8 = (s32) grCn_804D69A0->x68;
                }
                break;
            }
            {
                if ((arwing = (HSD_JObj*) arwing_gobjs[gp->gv.corneria2.xC8]))
                {
                    Vec3 arwing_pos;
                    arwing_gp = get_arwing_ground((HSD_GObj*) arwing);
                    ship_gp = GET_GROUND(Ground_801C2BA4(3));
                    lb_8000B1CC(Ground_801C3FA4((HSD_GObj*) arwing, 4), NULL,
                                &arwing_pos);
                    {
                        int* types = arwing_types;
                        int atype = types[arwing_gp->gv.corneria2.xC8];
                        pos.x = ship_gp->gv.corneria.offset_x +
                                (-arwing_pos.z + lbl_803E2068[atype].x);
                        pos.y = arwing_pos.y + lbl_803E2068[atype].y;
                        pos.z = arwing_pos.x + lbl_803E2068[atype].z;
                    }
                } else {
                    pos.z = 0.0f;
                    pos.y = 0.0f;
                    pos.x = 0.0f;
                }
            }
            if (pos.y <= 100.0f) {
                pos.y = 100.0f;
            }
            HSD_JObjSetTranslate(jobj, &pos);
            lb_8000B1CC(
                Ground_801C3FA4(
                    gobj, grCn_803E21B0[arwing_groups[gp->gv.corneria2.xC8]]),
                NULL, &pos);
            {
                f32 rot_z;
                f32 angle;
                {
                    HSD_GObj* item = gp->gv.corneria2.xDC;
                    if (item != NULL) {
                        Ground* gr = item->user_data;
                        if (gr != NULL) {
                            gr->gv.arwing.xE0 = pos;
                        }
                    }
                }
                rot_z = HSD_JObjGetRotationZ(Ground_801C3FA4(
                    gobj, grCn_803E21B0[arwing_groups[gp->gv.corneria2.xC8]]));
                angle = rot_z;
                {
                    HSD_GObj* item = gp->gv.corneria2.xDC;
                    if (item != NULL) {
                        Ground* gr = item->user_data;
                        if (gr != NULL) {
                            gr->gv.arwing.xDC = rot_z;
                        }
                    }
                }
                if (grCn_804D69B0 == 0) {
                    if (gp->gv.corneria2.xF0 % grCn_804D69A0->x74 == 0 &&
                        randi(grCn_804D69A0->x78) == 0)
                    {
                        gp->gv.corneria2.xFC = 1;
                    } else {
                        gp->gv.corneria2.xFC = 0;
                    }
                } else {
                    if (gp->gv.corneria2.xF0 % grCn_804D69A0->x7C == 0 &&
                        randi(grCn_804D69A0->x80) == 0)
                    {
                        gp->gv.corneria2.xFC = 1;
                    } else {
                        gp->gv.corneria2.xFC = 0;
                    }
                }
                if (gp->gv.corneria2.xFC != 0) {
                    gp->gv.corneria2.xFC = 0;
                    if (!grCorneria_801DEC08(&pos)) {
                        while (angle < -M_PI) {
                            angle += M_TAU;
                        }
                        while (angle > M_PI) {
                            angle -= M_TAU;
                        }
                        {
                            f32 abs_a = ABS(angle);
                            if (abs_a < 0.05235988f || ABS(angle) > 3.0892327f)
                            {
                                lbAudioAx_800237A8(0x55733, 0x7F, 0x40);
                                if (get_grp_off(gobj) == 1) {
                                    it_802E72E0(gobj, Ground_801C3FA4(gobj, 7),
                                                2, -1.0f, grCn_804D69A0->x70);
                                } else {
                                    it_802E72E0(gobj, Ground_801C3FA4(gobj, 5),
                                                0, -1.0f, grCn_804D69A0->x70);
                                }
                                grMaterial_801C9604(gobj, grCn_804D69A0->x84,
                                                    0);
                            }
                        }
                    }
                }
            }
        } break;
        case 10:
        case 11:
        case 12:
        case 13: {
            if (grCn_804D69B0 == 0) {
                if (gp->gv.corneria2.xF0 % grCn_804D69A0->x74 == 0 &&
                    randi(grCn_804D69A0->x78) == 0)
                {
                    gp->gv.corneria2.xFC = 1;
                } else {
                    gp->gv.corneria2.xFC = 0;
                }
            } else {
                if (gp->gv.corneria2.xF0 % grCn_804D69A0->x7C == 0 &&
                    randi(grCn_804D69A0->x80) == 0)
                {
                    gp->gv.corneria2.xFC = 1;
                } else {
                    gp->gv.corneria2.xFC = 0;
                }
            }
            {
                if ((far_arwing = arwing_gobjs[gp->gv.corneria2.xC8])) {
                    Vec3 arwing_pos;
                    arwing_gp = far_arwing->user_data;
                    ship_gp = GET_GROUND(Ground_801C2BA4(3));
                    lb_8000B1CC(Ground_801C3FA4(far_arwing, 4), NULL,
                                &arwing_pos);
                    {
                        s32 atype = arwing_types[arwing_gp->gv.corneria2.xC8];
                        pos.x = ship_gp->gv.corneria.offset_x +
                                (-arwing_pos.z + lbl_803E2068[atype].x);
                        pos.y = arwing_pos.y + lbl_803E2068[atype].y;
                        pos.z = arwing_pos.x + lbl_803E2068[atype].z;
                    }
                } else {
                    pos.z = 0.0f;
                    pos.y = 0.0f;
                    pos.x = 0.0f;
                }
            }
            if (pos.y <= 100.0f) {
                pos.y = 100.0f;
            }
            if (500.0F < pos.x &&
                pos.x < *(volatile const f32*) &grCn_ArwingMaxX &&
                gp->gv.corneria2.xFC != 0)
            {
                gp->gv.corneria2.xFC = 0;
                {
                    int player = HSD_Randi(4);
                    int tries;
                    for (tries = 0; tries < 4; tries++) {
                        player = (player + tries) & 3;
                        if (Player_GetPlayerSlotType(player) != Gm_PKind_NA) {
                            break;
                        }
                    }
                    Player_LoadPlayerCoords(player, &pos);
                }
                pos.y += 5.0f;
                lbAudioAx_800237A8(0x55734, 0x7F, 0x40);
                {
                    if (get_grp_off(gobj) == 1) {
                        it_802E7654(gobj, Ground_801C3FA4(gobj, 7), &pos, 3, 3,
                                    grCn_804D69A0->x70);
                    } else {
                        if (gp->gv.corneria2.x100 != 0) {
                            it_802E7654(gobj, Ground_801C3FA4(gobj, 5), &pos,
                                        1, 3, grCn_804D69A0->x70);
                        } else {
                            it_802E7654(gobj, Ground_801C3FA4(gobj, 6), &pos,
                                        1, 3, grCn_804D69A0->x70);
                        }
                        gp->gv.corneria2.x100 =
                            (gp->gv.corneria2.x100 + 1) & 1;
                    }
                }
                grMaterial_801C9604(gobj, grCn_804D69A0->x84, 0);
            }
        }
        }
        gp->gv.corneria2.xF0 += 1;
        return;
    }
    {
        HSD_GObj* item;
        item = gp->gv.corneria2.xE0;
        (void) item;
        if (item != NULL) {
            Ground_801C4A08(item);
        }
        item = gp->gv.corneria2.xE4;
        if (item != NULL) {
            Ground_801C4A08(item);
        }
        item = gp->gv.corneria2.xE8;
        if (item != NULL) {
            Ground_801C4A08(item);
        }
        item = gp->gv.corneria2.xEC;
        if (item != NULL) {
            Ground_801C4A08(item);
        }
        Ground_801C4A08(gobj);
    }
}

void grCorneria_801DF8CC(Ground_GObj* arg) {}

void grCorneria_801DF8D0(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    HSD_JObj* jobj = GET_JOBJ(gobj);
    f32 scale;

    scale = Ground_801C0498();
    gp->gv.corneria2.xC8 = grCn_804D69A4;
    Ground_ClearStarFoxArwingGObjs(gp);
    Ground_AnimateStarFoxArwing(gobj);

    switch (arwing_types[gp->gv.corneria2.xC8]) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9: {
        HSD_GObj* arwing = grCorneria_801DD534(
            grCn_803E217C[arwing_groups[gp->gv.corneria2.xC8]]);
        Ground_LinkStarFoxArwing(gp, arwing);
        break;
    }
    case 10:
    case 11:
    case 12:
    case 13: {
        Ground_AttachStarFoxArwingModel(gobj, gp,
                                        arwing_gobjs[gp->gv.corneria2.xC8], 4);
        break;
    }
    default:
        Ground_DisableStarFoxArwingGObjs(gp);
        break;
    }
    HSD_JObjSetScaleX(jobj, scale * grCn_804D69A0->x70);
    HSD_JObjSetScaleY(jobj, scale * grCn_804D69A0->x70);
    HSD_JObjSetScaleZ(jobj, scale * grCn_804D69A0->x70);
    Ground_ResetStarFoxArwingState(gp);
    gp->gv.corneria2.xF8 = (s32) grCn_804D69A0->x68;
    gp->gv.corneria2.xFC = 0;
}

bool grCorneria_801DFBC4(Ground_GObj* arg)
{
    return false;
}

void grCorneria_801DFBCC(Ground_GObj* arg)
{
    grCorneria_801DED50(arg);
}

void grCorneria_801DFBEC(Ground_GObj* arg) {}

void grCorneria_801DFBF0(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138((HSD_GObj*) gobj, gp->map_id, 0);
}

bool grCorneria_801DFC1C(Ground_GObj* arg)
{
    return false;
}

void grCorneria_801DFC24(Ground_GObj* arg) {}

void grCorneria_801DFC28(Ground_GObj* arg) {}

void grCorneria_801DFC2C(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);

    gp->gv.corneria.xC6.value = 0;
    gp->gv.corneria.offset_y.flags.b0 = 0;
    memzero(&gp->gv.corneria.xC8, 0x18);
    gp->gv.corneria.xC4.value = 0;
    gp->x11_flags.b012 = 1;
}

bool grCorneria_801DFC90(Ground_GObj* arg)
{
    return false;
}

void grCorneria_801DFC98(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);

    if (gp->gv.corneria.xC4.value == 0 &&
        gp->gv.corneria.offset_y.flags.b0 != 1)
    {
        HSD_JObjAddTranslationX(jobj, grCn_804D69A0->x88);
        HSD_JObjSetTranslateY(jobj, -grCorneria_801E2EA0());

        switch ((s8) gp->gv.corneria.xC5) {
        case 0:
            if (HSD_JObjGetTranslationX(jobj) >=
                3200.0f * Ground_801C0498() / 2 + -1400.0f)
            {
                grCorneria_801E03C8(gobj, 9);
                gp->gv.corneria.xC5 = 1;
                return;
            }
            break;
        case 1:
            if (HSD_JObjGetTranslationX(jobj) >=
                3200.0f * Ground_801C0498() / 2 + 1400.0f)
            {
                Ground_801C4A08(gobj);
            }
            break;
        }
    }
}

void grCorneria_801DFEB4(Ground_GObj* arg) {}

void grCorneria_801DFEB8(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;

    gp->gv.corneria.xC6.flags.b0 = 0;
    grAnime_801C8138((HSD_GObj*) gobj, gp->map_id, 0);
    gp->gv.corneria.xC4.value = 0;
    gp->x11_flags.b012 = 1;
}

bool grCorneria_801DFF18(Ground_GObj* arg)
{
    return false;
}

void grCorneria_801DFF20(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);

    if (gp->gv.corneria.xC4.value == 0 && gp->gv.corneria.xC6.flags.b0 != 1) {
        HSD_JObjAddTranslationX(jobj, grCn_804D69A0->x88);
        HSD_JObjSetTranslateY(jobj, -grCorneria_801E2EA0());

        switch ((s8) gp->gv.corneria.xC5) {
        case 0:
            if (HSD_JObjGetTranslationX(jobj) >=
                3200.0f * Ground_801C0498() / 2 + -1400.0f)
            {
                grCorneria_801E03C8(gobj, 4);
                gp->gv.corneria.xC5 = 1;
                return;
            }
            break;
        case 1:
            if (HSD_JObjGetTranslationX(jobj) >=
                3200.0f * Ground_801C0498() / 2 + 1400.0f)
            {
                Ground_801C4A08(gobj);
            }
            break;
        }
    }
}

void grCorneria_801E013C(Ground_GObj* arg) {}

void grCorneria_801E0140(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;

    gp->gv.corneria.xC6.flags.b0 = 0;
    grAnime_801C8138((HSD_GObj*) gobj, gp->map_id, 0);
    gp->gv.corneria.xC4.value = 0;
    gp->x11_flags.b012 = 1;
}

bool grCorneria_801E01A0(Ground_GObj* arg)
{
    return false;
}

void grCorneria_801E01A8(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);

    if (gp->gv.corneria.xC4.value == 0 && gp->gv.corneria.xC6.flags.b0 != 1) {
        HSD_JObjAddTranslationX(jobj, grCn_804D69A0->x88);
        HSD_JObjSetTranslateY(jobj, -grCorneria_801E2EA0());

        switch ((s8) gp->gv.corneria.xC5) {
        case 0:
            if (HSD_JObjGetTranslationX(jobj) >=
                4800.0f * Ground_801C0498() / 2 + -1400.0f)
            {
                grCorneria_801E03C8(gobj, 8);
                gp->gv.corneria.xC5 = 1;
                return;
            }
            break;
        case 1:
            if (HSD_JObjGetTranslationX(jobj) >=
                4800.0f * Ground_801C0498() / 2 + 1400.0f)
            {
                Ground_801C4A08(gobj);
            }
            break;
        }
    }
}

void grCorneria_801E03C4(Ground_GObj* arg) {}

u32 grCorneria_801E03C8(Ground_GObj* gobj, int id)
{
    Ground* gp;
    HSD_GObj* new_gobj;
    HSD_JObj* jobj = GET_JOBJ(gobj);
    f32 x = HSD_JObjGetTranslationX(jobj);
    PAD_STACK(8);

    new_gobj = grCorneria_801DD534(id);
    gp = GET_GROUND(new_gobj);

    if (id == 8) {
        f32 half = 3200.0f * Ground_801C0498() / 2;
        HSD_JObjSetTranslateX(HSD_GObjGetHSDObj(new_gobj),
                              x - (4800.0f * Ground_801C0498() / 2 + half));
        gp->gv.corneria.xC5 = 0;
    } else if (id == 9) {
        f32 half = 3200.0f * Ground_801C0498() / 2;
        HSD_JObjSetTranslateX(new_gobj->hsd_obj,
                              x - (3200.0f * Ground_801C0498() / 2 + half));
        gp->gv.corneria.xC5 = 0;
    } else if (id == 4) {
        f32 half = 4800.0f * Ground_801C0498() / 2;
        HSD_JObjSetTranslateX(new_gobj->hsd_obj,
                              x - (3200.0f * Ground_801C0498() / 2 + half));
        gp->gv.corneria.xC5 = 0;
    }
    if (new_gobj != NULL) {
        HSD_GObjGXLink_80390908(new_gobj, 3, 0);
    }
}

void grCorneria_801E0678(void)
{
    HSD_GObj* gobj;
    Ground* gp;

    gobj = Ground_801C2BA4(0xB);
    if (gobj != NULL) {
        Ground_801C4A08(gobj);
    }
    gobj = Ground_801C2BA4(8);
    HSD_JObjSetTranslateX(gobj->hsd_obj, 0.0f);
    gp = GET_GROUND(gobj);
    gp->gv.corneria.offset_y.flags.b0 = 1;

    gobj = Ground_801C2BA4(9);
    gp = GET_GROUND(gobj);
    gp->gv.corneria.xC6.flags.b0 = 1;
    {
        f32 half = 3200.0f * Ground_801C0498() / 2;
        HSD_JObjSetTranslateX(gobj->hsd_obj,
                              -(3200.0f * Ground_801C0498() / 2 + half));
    }

    gobj = Ground_801C2BA4(4);
    gp = GET_GROUND(gobj);
    gp->gv.corneria.xC6.flags.b0 = 1;
    {
        f32 half = 4800.0f * Ground_801C0498() / 2;
        HSD_JObjSetTranslateX(gobj->hsd_obj,
                              3200.0f * Ground_801C0498() / 2 + half);
    }
}

int grCorneria_801E08CC(void)
{
    f32 unused1;
    f32 unused2;
    Vec3 pos;
    HSD_GObj* gobj;
    f32 cam_x;

    Camera_GetTransformInterest(&pos);
    cam_x = pos.x;
    gobj = Ground_801C2BA4(8);
    if (gobj != NULL) {
        f32 x = HSD_JObjGetTranslationX(gobj->hsd_obj);
        if (cam_x > -(3200.0f * Ground_801C0498() / 2 - x) &&
            cam_x < 3200.0f * Ground_801C0498() / 2 + x)
        {
            return 8;
        }
    }
    gobj = Ground_801C2BA4(9);
    if (gobj != NULL) {
        f32 x = HSD_JObjGetTranslationX(gobj->hsd_obj);
        if (cam_x > -(3200.0f * Ground_801C0498() / 2 - x) &&
            cam_x < 3200.0f * Ground_801C0498() / 2 + x)
        {
            return 9;
        }
    }
    gobj = Ground_801C2BA4(4);
    if (gobj != NULL) {
        f32 x = HSD_JObjGetTranslationX(gobj->hsd_obj);
        if (cam_x > -(4800.0f * Ground_801C0498() / 2 - x) &&
            cam_x < 4800.0f * Ground_801C0498() / 2 + x)
        {
            return 4;
        }
    }
    HSD_ASSERT(0x9AC, 0);
    return -1;
}

int grCorneria_801E0A74(f32* arg0)
{
    HSD_GObj* gobj;

    gobj = Ground_801C2BA4(8);
    if (gobj != NULL) {
        f32 x = HSD_JObjGetTranslationX(gobj->hsd_obj);
        if (*arg0 > x - 3200.0f * Ground_801C0498() / 2 &&
            *arg0 < x + 3200.0f * Ground_801C0498() / 2)
        {
            return 8;
        }
    }
    gobj = Ground_801C2BA4(9);
    if (gobj != NULL) {
        f32 x = HSD_JObjGetTranslationX(gobj->hsd_obj);
        if (*arg0 > x - 3200.0f * Ground_801C0498() / 2 &&
            *arg0 < x + 3200.0f * Ground_801C0498() / 2)
        {
            return 9;
        }
    }
    gobj = Ground_801C2BA4(4);
    if (gobj != NULL) {
        f32 x = HSD_JObjGetTranslationX(gobj->hsd_obj);
        if (*arg0 > x - 4800.0f * Ground_801C0498() / 2 &&
            *arg0 < x + 4800.0f * Ground_801C0498() / 2)
        {
            return 4;
        }
    }
    HSD_ASSERTREPORT(0x9CB, 0, "grcorneria.c    grCorneriaGetPosMapKind2\n");
    return -1;
}

static inline void clearX10_b2(HSD_GObj* gobj)
{
    GET_GROUND(gobj)->x10_flags.b2 = false;
}

void grCorneria_801E0C3C(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
    clearX10_b2(gobj);
    Ground_801C4E70(Ground_801C3FA4(gobj, 5), Ground_801C3FA4(gobj, 2),
                    Ground_801C3FA4(gobj, 4), Ground_801C3FA4(gobj, 3),
                    Ground_801C3FA4(gobj, 7), Ground_801C3FA4(gobj, 6));
    grMaterial_801C8A04(jobj, JOBJ_UNK_B27);
    grMaterial_801C8858(jobj, JOBJ_ROOT_XLU);
    gp->x11_flags.b012 = 2;
}

bool grCorneria_801E0D28(Ground_GObj* arg)
{
    return false;
}

void grCorneria_801E0D30(Ground_GObj* gobj)
{
    HSD_JObj* jobj;

    if ((jobj = gobj->hsd_obj) != NULL) {
        HSD_JObjSetTranslateY(jobj, -grCorneria_801E2EA0());
    }
}

void grCorneria_801E0DE0(Ground_GObj* arg) {}

void grCorneria_801E0DE4(Ground_GObj* gobj)
{
    Ground* gr = GET_GROUND(gobj);
    smashTaunt_801E2550(gobj, &gr->gv.smashtaunt);
}

bool grCorneria_801E0E0C(Ground_GObj* arg)
{
    return false;
}

void grCorneria_801E0E14(Ground_GObj* gobj)
{
    Ground* gr = GET_GROUND(gobj);
    grCorneria_801E277C(gobj, &gr->gv.smashtaunt);
}

void grCorneria_801E0E3C(Ground_GObj* arg) {}

int grCn_804D466C = -1;

static s16 grCn_803E21F0[][2] = {
    { 0, 0 }, { 1, 6 }, { 2, 7 }, { 3, 8 }, { 4, 9 },
};

static grCn_Entry grCn_803E2204[20][5] = {
    0x00000001, 0x00000007, 0x0005573E, 0x00000004, 0x00000008, 0x0005573F,
    0x00000002, 0x00000009, 0x00055740, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000002, 0x0000000A, 0x00055741,
    0x00000001, 0x0000000B, 0x00055742, 0x00000004, 0x0000000C, 0x00055743,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000004, 0x0000000D, 0x00055744, 0x00000001, 0x0000000E, 0x00055745,
    0x00000002, 0x0000000F, 0x00055746, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000002, 0x00000010, 0x00055747,
    0x00000001, 0x00000011, 0x00055748, 0x00000004, 0x00000012, 0x00055749,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000001, 0x0000002F, 0x00018717, 0x00000004, 0x00000030, 0x00018718,
    0x00000003, 0x00000031, 0x00018719, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000003, 0x00000024, 0x0001870C,
    0x00000001, 0x0000000B, 0x00055742, 0x00000004, 0x0000000C, 0x00055743,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000004, 0x0000002C, 0x00018714, 0x00000001, 0x0000002D, 0x00018715,
    0x00000003, 0x0000002E, 0x00018716, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000004, 0x00000032, 0x0001871A,
    0x00000001, 0x00000033, 0x0001871B, 0x00000003, 0x00000034, 0x0001871C,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000004, 0x00000013, 0x0001AE20, 0x00000002, 0x00000014, 0x0001AE21,
    0x00000004, 0x00000015, 0x0001AE22, 0x00000001, 0x00000016, 0x0001AE23,
    0x00000000, 0x00000000, 0x00000000, 0x00000001, 0x00000017, 0x0001AE24,
    0x00000004, 0x00000018, 0x0001AE25, 0x00000002, 0x00000019, 0x0001AE26,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000004, 0x0000001A, 0x0001AE27, 0x00000001, 0x0000001B, 0x0001AE28,
    0x00000002, 0x0000001C, 0x0001AE29, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000001, 0x0000001D, 0x0001AE2A,
    0x00000001, 0x0000001E, 0x0001AE2B, 0x00000001, 0x0000001F, 0x0001AE2C,
    0x00000004, 0x00000020, 0x0001AE2D, 0x00000000, 0x00000000, 0x00000000,
    0x00000002, 0x00000021, 0x0001AE2E, 0x00000001, 0x00000022, 0x0001AE2F,
    0x00000004, 0x00000023, 0x0001AE30, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000003, 0x00000024, 0x0001870C,
    0x00000004, 0x00000025, 0x0001870D, 0x00000001, 0x00000026, 0x0001870E,
    0x00000001, 0x00000027, 0x0001870F, 0x00000000, 0x00000000, 0x00000000,
    0x00000001, 0x00000028, 0x00018710, 0x00000004, 0x00000029, 0x00018711,
    0x00000003, 0x0000002A, 0x00018712, 0x00000004, 0x0000002B, 0x00018713,
    0x00000000, 0x00000000, 0x00000000, 0x00000004, 0x0000002C, 0x00018714,
    0x00000001, 0x0000002D, 0x00018715, 0x00000003, 0x0000002E, 0x00018716,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000001, 0x0000002F, 0x00018717, 0x00000004, 0x00000030, 0x00018718,
    0x00000003, 0x00000031, 0x00018719, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000004, 0x00000032, 0x0001871A,
    0x00000001, 0x00000033, 0x0001871B, 0x00000003, 0x00000034, 0x0001871C,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000004, 0x00000005, 0x0005573C, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000004, 0x00000006, 0x0005573D,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

void grCorneria_801E0E40(void)
{
    u32 trigger;
    HSD_GObj* wgobj;
    PAD_STACK(8);

    if (!Camera_80030178()) {
        if (!Camera_80030154()) {
            return;
        }
    }

    trigger = HSD_PadMasterStatus[1].trigger;
    if ((trigger & (PAD_TRIGGER_L | PAD_TRIGGER_R)) == 0) {
        return;
    }

    if (Ground_801C2BA4(0xC) != NULL) {
        return;
    }

    if (trigger & PAD_TRIGGER_L) {
        grCn_804D466C -= 1;
    } else {
        grCn_804D466C += 1;
    }

    if (grCn_804D466C < 0) {
        grCn_804D466C = 0;
    }
    if (grCn_804D466C >= 0x14U) {
        grCn_804D466C = 0x13;
    }

    OSReport("talk no = %d\n", grCn_804D466C);
    wgobj = grCorneria_801DD534(0xC);
    HSD_ASSERT(0xAC3, wgobj);

    grCorneria_801E0F34(wgobj, grCn_804D466C);
}

void grCorneria_801E0F30(Ground_GObj* arg) {}

void grCorneria_801E0F34(Ground_GObj* gobj, int val)
{
    Ground* gp = GET_GROUND(gobj);
    gp->gv.arwing.xCC = 0;
    gp->gv.arwing.xC8 = 0;
    if (val < 0) {
        val = 0;
    }
    if (val >= 0x14u) {
        val = 0x13;
    }
    gp->gv.arwing.xC4 = val;
}

bool grCorneria_801E0F64(Ground_GObj* arg)
{
    return false;
}

void grCorneria_801E0F6C(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    Ground_UpdateStarFoxSequence(gobj, gp, 5, grCorneria_801DD534);
}

void grCorneria_801E1030(Ground_GObj* gobj)
{
    ifStatus_802F68F0();
    un_802FF620();
}

void grCorneria_801E1054(Ground_GObj* arg) {}

bool grCorneria_801E1058(Ground_GObj* arg)
{
    return false;
}

static inline void Fake_HSD_JObjSetTranslateX(HSD_JObj* jobj, f32 x)
{
    if (!jobj) {
        return;
    }
    if (!jobj) {
        __assert("jobj.h", 932, "jobj");
    }

    jobj->translate.x = x;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

void grCorneria_801E1060(Ground_GObj* gobj)
{
    HSD_GObj* bg;
    f32 pos;
    f32 total;

    pos = gm_801883C0();
    total = 3200.0f * Ground_801C0498();
    pos *= ((4800.0f * Ground_801C0498() / 2 +
             (total + 3200.0f * Ground_801C0498() / 2)) /
            2400.0f);

    bg = Ground_801C2BA4(8);
    if (bg != NULL) {
        Fake_HSD_JObjSetTranslateX(bg->hsd_obj, pos);
    }
    pos = pos -
          (3200.0f * Ground_801C0498() / 2 + 3200.0f * Ground_801C0498() / 2);

    bg = Ground_801C2BA4(9);
    if (bg != NULL) {
        Fake_HSD_JObjSetTranslateX(bg->hsd_obj, pos);
    }
    pos = pos -
          (3200.0f * Ground_801C0498() / 2 + 4800.0f * Ground_801C0498() / 2);

    bg = Ground_801C2BA4(4);
    if (bg != NULL) {
        Fake_HSD_JObjSetTranslateX(bg->hsd_obj, pos);
    }
}

void grCorneria_801E12CC(Ground_GObj* arg) {}

void fn_801E12D0(Item_GObj* gobj, Ground* gr) {}

void fn_801E12D4(Item_GObj* gobj, Ground* gr, Vec3* pos, HSD_GObj* arg3,
                 f32 damage)
{
    gr->gv.corneria.x114 += damage;
    OSReport("*** Beam Damage! %f\n", damage);
    if (gr->gv.corneria.x114 >= grCn_804D69A0->x38) {
        gr->gv.corneria.x108 = 4;
        grMaterial_801C8E28((HSD_GObj*) gr->gv.corneria.left_cannon);
        grMaterial_801C8E28((HSD_GObj*) gr->gv.corneria.right_cannon);
    }
}

static inline f32 grCn_GetX1C(void)
{
    return grCn_804D69A0->x1C;
}

static inline HSD_JObj* grCn_GetCannonJObj2(Ground_GObj* gobj)
{
    return Ground_801C3FA4(gobj, 2);
}

void grCorneria_801E1348(Ground_GObj* gobj)
{
    Vec3 sp40;
    u8 unused[8];
    Vec3 cannon_pos;
    Vec3 fighter_pos;
    Ground* gp = GET_GROUND(gobj);

    PAD_STACK(12);

    switch (gp->gv.corneria.x108) {
    case 0:
        if (gp->gv.corneria.x110 == 0) {
            if (HSD_Randf() <= grCn_804D69A0->x24) {
                gp->gv.corneria.x119 = 0;
                gp->gv.corneria.x118 = 1;
                gp->gv.corneria.x10C = grCn_804D69A0->x28;
                Ground_801C53EC(0x55739);
            } else {
                s32 imax;
                s32 imin = grCn_804D69A0->x30;
                imax = grCn_804D69A0->x34;
                if (imax > imin) {
                    s32 range = imax - imin;
                    imax = imin + (range != 0 ? HSD_Randi(range) : 0);
                } else if (imax < imin) {
                    s32 range = imin - imax;
                    imax += (range != 0 ? HSD_Randi(range) : 0);
                }
                gp->gv.corneria.x119 = 1;
                gp->gv.corneria.x118 = imax;
                gp->gv.corneria.x10C = grCn_804D69A0->x2C;
                Ground_801C53EC(0x5573A);
            }
            sp40.x = grCn_803E1FAC[1].x;
            sp40.y = grCn_803E1FAC[1].y;
            sp40.z = grCn_803E1FAC[1].z;
            grLib_801C9808(0xBC, 0, Ground_801C3FA4(gobj, 2));
            grLib_801C9808(0xBC, 0, Ground_801C3FA4(gobj, 3));
            Item_80268E5C((HSD_GObj*) gp->gv.corneria.left_cannon, 2,
                          ITEM_ANIM_UPDATE);
            Item_80268E5C((HSD_GObj*) gp->gv.corneria.right_cannon, 2,
                          ITEM_ANIM_UPDATE);
            grMaterial_801C8E28((HSD_GObj*) gp->gv.corneria.left_cannon);
            grMaterial_801C8E28((HSD_GObj*) gp->gv.corneria.right_cannon);
            gp->gv.corneria.x108 = 1;
            return;
        }
        gp->gv.corneria.x110 -= 1;
        return;
    case 1:
        if (gp->gv.corneria.x10C == 0) {
            hsd_8039D580(grCn_GetCannonJObj2(gobj));
            hsd_8039D580(Ground_801C3FA4(gobj, 3));
            Item_80268E5C((HSD_GObj*) gp->gv.corneria.left_cannon, 0,
                          ITEM_ANIM_UPDATE);
            Item_80268E5C((HSD_GObj*) gp->gv.corneria.right_cannon, 0,
                          ITEM_ANIM_UPDATE);
            gp->gv.corneria.x10C = grCn_804D69A0->x20;
            gp->gv.corneria.x108 = 2;
            return;
        }
        gp->gv.corneria.x10C -= 1;
        return;
    case 2: {
        int found = 0;
        lb_8000B1CC(Ground_801C3FA4(gobj, 2), NULL, &cannon_pos);
        {
            HSD_GObj* fighter = HSD_GObj_Entities->fighters;
            while (fighter != NULL) {
                ftLib_80086644(fighter, &fighter_pos);
                if (ABS(cannon_pos.y - fighter_pos.y) <= 10.0f) {
                    found = 1;
                    break;
                }
                fighter = fighter->next;
            }
        }
        if (found != 0) {
            gp->gv.corneria.x10C = 0;
        }
        if (gp->gv.corneria.x10C == 0) {
            gp->gv.corneria.x108 = 3;
            grMaterial_801C8E08((Item_GObj*) gp->gv.corneria.left_cannon);
            grMaterial_801C8E08((Item_GObj*) gp->gv.corneria.right_cannon);
            return;
        }
        gp->gv.corneria.x10C -= 1;
        return;
    }
    case 3:
        if (gp->gv.corneria.x118 != 0) {
            if (gp->gv.corneria.x110 == 0) {
                HSD_JObj* cannon;
                s32 side = gp->gv.corneria.x11A;
                sp40.x = 20.0f + grCn_803E1F70[1].x;
                sp40.y = 2.0f + grCn_803E1F70[1].y;
                if (side != 0) {
                    sp40.z = 9.0f;
                    cannon = Ground_801C3FA4(gobj, 2);
                } else {
                    cannon = Ground_801C3FA4(gobj, 3);
                    sp40.z = -9.0f;
                }
                grLib_801C9808(0xC0, 0, cannon);
                it_802EAF34(gobj, &sp40, (s8) gp->gv.corneria.x119);
                Ground_801C53EC(0x55735);
                gp->gv.corneria.x11A ^= 1;
                gp->gv.corneria.x110 = 0xA;
                gp->gv.corneria.x118 -= 1;
                return;
            }
            gp->gv.corneria.x110 -= 1;
            return;
        }
        {
            s32 rand_range = grCn_804D69A0->x18;
            s32 range = grCn_804D69A0->x18;
            gp->gv.corneria.x110 =
                (s32) (grCn_GetX1C() +
                       (range != 0 ? HSD_Randi(rand_range) : 0));
        }
        gp->gv.corneria.x10C = 0;
        gp->gv.corneria.x108 = 0;
        return;
    case 4:
        grLib_801C9808(0xE3, 0, Ground_801C3FA4(gobj, 2));
        grLib_801C9808(0xE3, 0, Ground_801C3FA4(gobj, 3));
        sp40.x = grCn_803E1FAC[1].x;
        sp40.y = grCn_803E1FAC[1].y;
        sp40.z = grCn_803E1FAC[1].z;
        Camera_80030E44(4, &sp40);
        Ground_801C53EC(0x76);
        HSD_JObjSetFlags(Ground_801C3FA4(gobj, 6), JOBJ_HIDDEN);
        HSD_JObjClearFlags(Ground_801C3FA4(gobj, 5), JOBJ_HIDDEN);
        mpLib_80057BC0(4);
        gp->gv.corneria.x108 = 5;
        return;
    case 5:
        return;
    }
}

void grCorneria_801E1878(Ground_GObj* gobj)
{
    Ground* gr = GET_GROUND(gobj);
    HSD_JObj* jobj = gobj->hsd_obj;
    HSD_JObj* tmp = gr->gv.corneria.x128->hsd_obj;
    HSD_JObj* target_jobj = tmp;

    /// @remarks Splitting the pad around a scoped @c pos places the vector
    /// at sp+0x18 as in the target; a function-scope @c pos with a single
    /// PAD_STACK(16) leaves it at sp+0x24 (six reg-save/load instructions
    /// arg-mismatch, 99.90%).
    PAD_STACK(8);
    {
        Vec3 pos;
        HSD_JObjGetTranslation(jobj, &pos);
        HSD_JObjSetTranslate(target_jobj, &pos);
    }
    PAD_STACK(8);

    Ground_801C39C0();
    Ground_801C3BB4();
}

void grCorneria_801E1970(Ground_GObj* gobj)
{
    Vec3 pos;
    Ground* gp = gobj->user_data;
    HSD_JObj* jobj = gobj->hsd_obj;

    if (gp->gv.corneria.x104 <= 0) {
        f32 randf = HSD_Randf();
        f32 a = grCn_804D69A0->x4 - grCn_804D69A0->x0;
        gp->gv.corneria.x104 = a * randf + grCn_804D69A0->x0;
        randf = HSD_Randf();
        gp->gv.corneria.xF4 = grCn_804D69A0->x8 * (2.0f * (randf - 0.5f));
        randf = HSD_Randf();
        gp->gv.corneria.xF8 = grCn_804D69A0->x8 * (2.0f * (randf - 0.5f));
    }
    gp->gv.corneria.x104 -= 1;
    gp->gv.corneria.xE4.z += gp->gv.corneria.xF4;
    gp->gv.corneria.xF0 += gp->gv.corneria.xF8;
    {
        f32 vel = gp->gv.corneria.xE4.z;
        f32 max = grCn_804D69A0->xC;
        if (vel > max) {
            gp->gv.corneria.xE4.z = max;
        } else if (vel < -max) {
            gp->gv.corneria.xE4.z = -max;
        }
    }
    {
        f32 vel = gp->gv.corneria.xF0;
        f32 max = grCn_804D69A0->xC;
        if (vel > max) {
            gp->gv.corneria.xF0 = max;
        } else if (vel < -max) {
            gp->gv.corneria.xF0 = -max;
        }
    }
    gp->gv.corneria.xE4.x = gp->gv.corneria.offset_x;
    gp->gv.corneria.xE4.y = gp->gv.corneria.offset_y.val;
    gp->gv.corneria.offset_x += gp->gv.corneria.xE4.z;
    gp->gv.corneria.offset_y.val += gp->gv.corneria.xF0;
    {
        f32 offset = gp->gv.corneria.offset_x;
        f32 limit = grCn_804D69A0->x10;
        if (offset > limit) {
            gp->gv.corneria.xF4 = -grCn_804D69A0->x8;
        } else if (offset < -limit) {
            gp->gv.corneria.xF4 = grCn_804D69A0->x8;
        }
    }
    {
        f32 offset = gp->gv.corneria.offset_y.val;
        f32 limit = grCn_804D69A0->x14;
        if (offset > limit) {
            gp->gv.corneria.xF8 = -grCn_804D69A0->x8;
        } else if (offset < -limit) {
            gp->gv.corneria.xF8 = grCn_804D69A0->x8;
        }
    }
    pos.x = gp->gv.corneria.base_x + gp->gv.corneria.offset_x;
    pos.y = gp->gv.corneria.base_y + gp->gv.corneria.offset_y.val;
    pos.z = 0.0f;
    HSD_JObjSetTranslate(jobj, &pos);
}

HSD_GObj* grCorneria_801E1BF0(void)
{
    HSD_GObj* gobj = grCorneria_801DD534(2);
    Ground* gp;
    HSD_JObj* jobj;

    HSD_ASSERT(0xC70, gobj);
    gp = GET_GROUND(gobj);
    HSD_ASSERT(0xC71, gp);
    jobj = HSD_GObjGetHSDObj(gobj);
    HSD_ASSERT(0xC72, jobj);
    HSD_JObjRemoveAnimAll(jobj);
    HSD_JObjSetTranslateX(jobj, 0.0f);
    HSD_JObjSetTranslateY(jobj, 0.0f);
    HSD_JObjSetTranslateZ(jobj, 0.0f);
    HSD_JObjSetRotationX(jobj, 0.0f);
    HSD_JObjSetRotationY(jobj, 0.0f);
    HSD_JObjSetRotationZ(jobj, 0.0f);
    HSD_JObjSetScaleX(jobj, 1.0f);
    HSD_JObjSetScaleY(jobj, 1.0f);
    HSD_JObjSetScaleZ(jobj, 1.0f);
    gp->gv.corneria.xC4.flags.b0 = 1;
    return gobj;
}

const GXColor grCn_804DB218 = { 0xAE, 0xBA, 0xD6, 0xFF };
const GXColor grCn_804DB21C = { 0xD7, 0xE4, 0xF6, 0xFF };
const GXColor grCn_804DB220 = { 0xE0, 0xEC, 0xFA, 0xFF };
const GXColor grCn_804DB224 = { 0x6A, 0x9E, 0xAD, 0xFF };
const GXColor grCn_804DB228 = { 0x4F, 0x94, 0xB5, 0xFF };
const GXColor grCn_804DB22C = { 0x49, 0x6E, 0x3F, 0xFF };
const GXColor grCn_804DB230 = { 0x6A, 0x9E, 0xAD, 0xFF };
const GXColor grCn_804DB234 = { 0x4F, 0x94, 0xB5, 0xFF };
const GXColor grCn_804DB238 = { 0x00, 0x50, 0x91, 0xFF };

void grCorneria_801E2110(void)
{
    GXColor c1, c2, c3, c4, c5, c6, c7, c8, c9;
    int id = grCorneria_801E08CC();

    if (id == 8) {
        c1 = grCn_804DB218;
        c2 = grCn_804DB21C;
        c3 = grCn_804DB220;
        Ground_801C058C(&c2);
        Ground_801C05EC(&c1);
        Ground_801C05A4(&c2);
        Ground_801C055C(&c3);
        Ground_801C05BC(&c3);
        Ground_801C0574(&c3);
    } else if (id == 9) {
        c4 = grCn_804DB224;
        c5 = grCn_804DB228;
        c6 = grCn_804DB22C;
        Ground_801C058C(&c5);
        Ground_801C05EC(&c4);
        Ground_801C05A4(&c5);
        Ground_801C055C(&c6);
        Ground_801C05BC(&c6);
        Ground_801C0574(&c6);
    } else if (id == 4) {
        c7 = grCn_804DB230;
        c8 = grCn_804DB234;
        c9 = grCn_804DB238;
        Ground_801C058C(&c8);
        Ground_801C05EC(&c7);
        Ground_801C05A4(&c8);
        Ground_801C055C(&c9);
        Ground_801C05BC(&c9);
        Ground_801C0574(&c9);
    }
}

void grCorneria_801E2228(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    PAD_STACK(32);

    if (!gp->gv.corneria.xC4.flags.b1) {
        if (!gp->gv.corneria.xC4.flags.b2 && grCorneria_801E08CC() == 4) {
            if (HSD_Randi(3) == 0) {
                gp->gv.corneria.xC4.flags.b1 = 1;
                gp->gv.corneria.x100 = 0;
                gp->gv.corneria.xFC = 0.0f;
            }
            gp->gv.corneria.xC4.flags.b2 = 1;
        }
        if (grCorneria_801E08CC() == 9) {
            gp->gv.corneria.xC4.flags.b2 = 0;
        }
    } else {
        s32 timer = gp->gv.corneria.x100;
        gp->gv.corneria.x100 = timer + 1;
        if (timer < 0x384) {
            f32 speed = gp->gv.corneria.xFC;
            f32 t = speed / 0.005f;
            if ((gp->gv.corneria.xD0 - (50.0f * Ground_801C0498() - 250.0f)) >
                (speed * t + -0.0025f * t * t))
            {
                gp->gv.corneria.xFC += 0.005f;
                if (gp->gv.corneria.xFC > 3.0f) {
                    gp->gv.corneria.xFC = 3.0f;
                }
            } else {
                gp->gv.corneria.xFC -= 0.005f;
                if (gp->gv.corneria.xFC < 0.005f) {
                    gp->gv.corneria.xFC = 0.005f;
                }
            }
            gp->gv.corneria.xD0 -= gp->gv.corneria.xFC;
            if (gp->gv.corneria.xD0 < 50.0f * Ground_801C0498() - 250.0f) {
                gp->gv.corneria.xD0 = 50.0f * Ground_801C0498() - 250.0f;
            }
        } else {
            f32 speed = gp->gv.corneria.xFC;
            f32 t = speed / 0.005f;
            if (-gp->gv.corneria.xD0 > (speed * t + -0.0025f * t * t)) {
                t = 0.005f;
                gp->gv.corneria.xFC = speed + t;
                if (gp->gv.corneria.xFC > 3.0f) {
                    gp->gv.corneria.xFC = 3.0f;
                }
            } else {
                gp->gv.corneria.xFC = speed - 0.005f;
                if (gp->gv.corneria.xFC < 0.005f) {
                    gp->gv.corneria.xFC = 0.005f;
                }
            }
            gp->gv.corneria.xD0 += gp->gv.corneria.xFC;
            if (gp->gv.corneria.xD0 > 0.0f) {
                gp->gv.corneria.xD0 = 0.0f;
                gp->gv.corneria.xC4.flags.b1 = 0;
            }
        }
    }
}

HSD_Generator* grCorneria_801E2454(Vec3* vec, s32 arg1)
{
    return grLib_801C96F8(0x7534, 0x1E, vec);
}

HSD_Generator* grCorneria_801E2480(Vec3* vec, s32 arg1)
{
    return grLib_801C96F8(0x7530, 0x1E, vec);
}

/// This triggers for both Corneria and Venom
void smashTaunt_801E24AC(Ground_GObj* gobj, int renderpass)
{
    Ground* gp = GET_GROUND(gobj);
    PAD_STACK(8);

    if (gm_801A45E8(1) || gm_801A45E8(2) || Camera_8003010C()) {
        if (gp->gv.smashtaunt.text == NULL) {
            return;
        }
        ((HSD_Text*) gp->gv.smashtaunt.text)->hidden = true;
        return;
    }
    if (gp->gv.smashtaunt.text != NULL) {
        ((HSD_Text*) gp->gv.smashtaunt.text)->hidden = false;
    }
    grDisplay_801C5DB0(gobj, renderpass);
}

void smashTaunt_801E2550(Ground_GObj* gobj, struct grSmashTaunt_GroundVars* gv)
{
    PAD_STACK(8);

    gv->text = NULL;
    Ground_801C11AC(gobj);
    ifStatus_802F6898();
    un_802FF570();
    gobj->render_cb = smashTaunt_801E24AC;
}

s32 grCorneria_801E2598(u32 arg0, u32 arg1)
{
    int val;

    val = grCn_803E2204[arg0][arg1].data[0];
    return val != 0;
}

static inline void grCn_HideJointPair(HSD_GObj* gobj, s16* joints)
{
    HSD_JObj* j0 = Ground_801C3FA4(gobj, joints[0]);
    if (j0 != NULL) {
        HSD_JObjSetFlagsAll(j0, JOBJ_HIDDEN);
    }
    {
        HSD_JObj* j1 = Ground_801C3FA4(gobj, joints[1]);
        if (j1 != NULL) {
            HSD_JObjSetFlagsAll(j1, JOBJ_HIDDEN);
        }
    }
}

/// @todo Only differs by a callee-saved register permutation.
void grCorneria_801E25C4(HSD_GObj* gobj, void* gv, int line, int arg3,
                         int arg4)
{
    struct grSmashTaunt_GroundVars* v = gv;
    s16 joint1;
    s16 joint0;
    int i;
    s16* joints;
    PAD_STACK(8);

    v->line = line;
    v->sis_data_idx = arg3;
    v->sound_id = arg4;
    joint0 = grCn_803E21F0[v->line][0];
    joint1 = grCn_803E21F0[v->line][1];
    joints = &grCn_803E21F0[i = 0][0];
    do {
        if (i != 0 && v->line != i) {
            grCn_HideJointPair(gobj, joints);
        }
        i++;
        joints += 2;
    } while (i < 5);
    v->jobj0 = Ground_801C3FA4(gobj, joint0);
    v->jobj1 = Ground_801C3FA4(gobj, joint1);
    v->jobj2 = Ground_801C3FA4(gobj, 5);
    v->joint_idx0 = joint0;
    v->joint_idx1 = joint1;
    v->joint_idx2 = 5;
    v->state = 0;
    v->timer = 0xA;
    grAnime_801C8098(gobj, joint0, 7, 0, 0.0f, 1.0f);
    grAnime_801C8098(gobj, joint1, 7, 0, 0.0f, 1.0f);
    grAnime_801C8098(gobj, 5, 7, 0, 0.0f, 1.0f);
    HSD_JObjAnimAll(gobj->hsd_obj);
}

void grCorneria_801E2738(HSD_GObj* gobj, void* ptr, u32 idx1, u32 idx2)
{
    grCorneria_801E25C4(gobj, ptr, grCn_803E2204[idx1][idx2].data[0],
                        grCn_803E2204[idx1][idx2].data[1],
                        grCn_803E2204[idx1][idx2].data[2]);
}

const GXColor grCn_804DB24C = { 0xFF, 0xFF, 0xFF, 0xFF };

void grCorneria_801E277C(Ground_GObj* gobj, struct grSmashTaunt_GroundVars* gv)
{
    Ground* gp = GET_GROUND(gobj);
    GXColor sp18;
    PAD_STACK(4);

    if (gv->jobj0 != NULL) {
        grMaterial_801C87D0(gv->jobj0, JOBJ_UNK_B27);
    }
    if (gv->jobj1 != NULL) {
        grMaterial_801C87D0(gv->jobj1, JOBJ_UNK_B27);
    }
    if (gv->jobj2 != NULL) {
        grMaterial_801C87D0(gv->jobj2, JOBJ_UNK_B27);
    }
    switch (gv->state) {
    case 0: {
        s16 timer = gv->timer;
        gv->timer = timer - 1;
        if (timer == 0) {
            Ground_801C53EC(0xB2);
        }
        if (grAnime_801C83D0(gobj, gv->joint_idx0, 2) != 0) {
            UnkArchiveStruct* archive;
            HSD_Text* text;
            gv->state = 1;
            gv->timer = 0x3C;
            grAnime_801C8098(gobj, gv->joint_idx0, 7, 1, 0.0f, 1.0f);
            grAnime_801C8098(gobj, gv->joint_idx1, 7, 1, 0.0f, 1.0f);
            grAnime_801C8098(gobj, gv->joint_idx2, 7, 1, 0.0f, 1.0f);
            grAnime_801C787C(gobj, gv->joint_idx0, 7);
            grAnime_801C787C(gobj, gv->joint_idx1, 7);
            grAnime_801C787C(gobj, gv->joint_idx2, 7);
            archive = grDatFiles_GetArchive();
            sp18 = grCn_804DB24C;
            HSD_SisLib_803A611C(1, NULL, 9, 0xD, 0, 1, 0, 7);
            HSD_SisLib_804D1124[1] = HSD_ArchiveGetPublicAddress(
                archive->unk0, "SIS_GrCorneriaData");
            text =
                HSD_SisLib_803A5ACC(1, 0, 140.0f, 380.0f, 0.0f, 288.0f, 96.0f);
            text->text_color = sp18;
            HSD_SisLib_803A6368(text, gv->sis_data_idx);
            gv->text = text;
            Ground_801C5440(gp, 0, gv->sound_id);
            return;
        }
        break;
    }
    case 1:
        gv->timer -= 1;
        if (gv->timer < 0 && Ground_801C54DC(gp, 0) == 0) {
            gv->state = 2;
            grAnime_801C8098(gobj, gv->joint_idx0, 7, 2, 0.0f, 1.0f);
            grAnime_801C8098(gobj, gv->joint_idx1, 7, 2, 0.0f, 1.0f);
            grAnime_801C8098(gobj, gv->joint_idx2, 7, 2, 0.0f, 1.0f);
            grAnime_801C7980(gobj, gv->joint_idx0, 7);
            grAnime_801C7980(gobj, gv->joint_idx1, 7);
            grAnime_801C7980(gobj, gv->joint_idx2, 7);
            HSD_SisLib_803A5F50(1);
            return;
        }
        break;
    case 2:
        if (grAnime_801C83D0(gobj, gv->joint_idx0, 2) != 0) {
            Ground_801C4A08(gobj);
        }
        break;
    }
}

void grCorneria_801E2A6C(void)
{
    HSD_GObj* gobj;
    PAD_STACK(20);

    if (stage_info.internal_stage_id == CORNERIA) {
        gobj = Ground_801C2BA4(12);
        if (gobj == NULL) {
            return;
        }
        gobj = Ground_801C2BA4(5);
        if (gobj != NULL) {
            Ground_801C5544(GET_GROUND(gobj), 0);
            Ground_801C4A08(gobj);
        }
        HSD_SisLib_803A5F50(1);
    } else if (stage_info.internal_stage_id == VENOM) {
        grVenom_80206CB0(0);
    }
}

void grCorneria_801E2AF4(void)
{
    HSD_GObj* gobj;
    PAD_STACK(20);

    if (stage_info.internal_stage_id == CORNERIA) {
        gobj = Ground_801C2BA4(12);
        if (gobj == NULL) {
            return;
        }
        Ground_801C4A08(gobj);
        gobj = Ground_801C2BA4(5);
        if (gobj != NULL) {
            Ground_801C5544(GET_GROUND(gobj), 0);
            Ground_801C4A08(gobj);
        }
        HSD_SisLib_803A5F50(1);
    } else if (stage_info.internal_stage_id == VENOM) {
        grVenom_80206CB0(1);
    }
}

#pragma push
#pragma dont_inline on
bool grCorneria_801E2B80(void)
{
    int rand;
    HSD_GObj* wgobj;
    PAD_STACK(44);

    if (stage_info.internal_stage_id == CORNERIA) {
        if (Ground_801C2BA4(12) != NULL) {
            return false;
        }
        rand = HSD_Randi(5) + 8;
        wgobj = grCorneria_801DD534(12);
        HSD_ASSERT(3598, wgobj);
        grCorneria_801E0F34(wgobj, rand);
        return true;
    } else if (stage_info.internal_stage_id == VENOM) {
        return grVenom_80206BF0(2);
    }
    return true;
}

bool grCorneria_801E2C34(void)
{
    int rand;
    HSD_GObj* wgobj;
    PAD_STACK(44);

    if (stage_info.internal_stage_id == CORNERIA) {
        if (Ground_801C2BA4(12) != NULL) {
            return false;
        }
        rand = HSD_Randi(5) + 13;
        wgobj = grCorneria_801DD534(12);
        HSD_ASSERT(3598, wgobj);
        grCorneria_801E0F34(wgobj, rand);
        return true;
    } else if (stage_info.internal_stage_id == VENOM) {
        return grVenom_80206BF0(20);
    }
    return true;
}
#pragma pop

bool grCorneria_801E2CE8(void)
{
    if (stage_info.internal_stage_id == CORNERIA ||
        stage_info.internal_stage_id == VENOM)
    {
        return true;
    }
    return false;
}

bool grCorneria_801E2D14(void)
{
    HSD_GObj* gobj;
    if (stage_info.internal_stage_id == CORNERIA) {
        gobj = Ground_801C2BA4(12);
        if (gobj != NULL) {
            return true;
        }
        return false;
    } else if (stage_info.internal_stage_id == VENOM) {
        gobj = Ground_801C2BA4(8);
        if (gobj != NULL) {
            return true;
        }
        return false;
    }
    return false;
}

bool grCorneria_801E2D90(enum_t line_id)
{
    if (stage_info.internal_stage_id == CORNERIA && line_id != -1) {
        s32 joint = mpJointFromLine(line_id);
        s32 result;

        result = joint == 0 || joint == 1 || joint == 2 || joint == 5 ||
                 joint == 6 || joint == 7;

        if (result) {
            return true;
        }
    }
    return false;
}

bool grCorneria_801E2E50(int line_id)
{
    if (stage_info.internal_stage_id == CORNERIA && line_id != -1) {
        if (mpJointFromLine(line_id) == 4) {
            return true;
        }
    }
    return false;
}

f32 grCorneria_801E2EA0(void)
{
    HSD_GObj* gobj;
    Ground* gp;

    gobj = Ground_801C2BA4(3);
    if (gobj != NULL) {
        gp = GET_GROUND(gobj);
        if (gp != NULL) {
            return gp->gv.corneria.xD0;
        }
    }
    return 0.0f;
}

DynamicsDesc* grCorneria_801E2EE4(enum_t arg)
{
    return NULL;
}

extern const f32 grCn_804DB260;
extern const f32 grCn_804DB264;
extern const f32 grCn_804DB268;

bool grCorneria_801E2EEC(Vec3* v, int arg1, HSD_JObj* jobj)
{
    Vec3 sp14;
    HSD_GObj* temp_r3;
    Ground* temp_r3_2;
    float temp_f31;
    float temp_f31_2;

    lb_8000B1CC(jobj, NULL, &sp14);
    temp_r3 = Ground_801C2BA4(3);
    if (temp_r3 != NULL) {
        temp_r3_2 = temp_r3->user_data;
        if (temp_r3_2 != NULL && temp_r3_2->gv.corneria.x12C == jobj) {
            temp_f31 = grCn_804DB264 * Ground_801C0498();
            temp_f31_2 = ((v->y - sp14.y) *
                          ((grCn_804DB260 * Ground_801C0498()) / temp_f31)) +
                         sp14.x;
            if (v->x > -((grCn_804DB260 * Ground_801C0498()) - temp_f31_2)) {
                return false;
            }
        }
    }
    if (v->y > sp14.y) {
        return true;
    }
    return false;
}

f32 grCorneria_801E2FCC(void)
{
    HSD_GObj* gobj;
    Ground* gp;

    gobj = Ground_801C2BA4(3);
    if (gobj != NULL) {
        gp = gobj->user_data;
        if (gp != NULL) {
            return (Ground_801C0498() * -35.0f - gp->gv.corneria.xD0) + 5.0f;
        }
    }
    return grCn_804DB268;
}

/// Defined after all readers so MWCC loads the named symbols instead of
/// folding the values back into the literal pool.
const f32 grCn_804DB260 = 107.0f;
const f32 grCn_804DB264 = 106.0f;
const f32 grCn_804DB268 = -3.4028235e38f;
