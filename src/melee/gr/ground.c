#include "ground.h"

#include "grcorneria.h"
#include "grdatfiles.h"
#include "grdisplay.h"
#include "grizumi.h"
#include "grkongo.h"
#include "grmaterial.h"
#include "groldkongo.h"
#include "grstadium.h"
#include "grzebes.h"
#include "platform.h"
#include "stage.h"

#include <placeholder.h>

#include "cm/camera.h"
#include "ft/ftdevice.h"
#include "ft/ftlib.h"
#include "gm/gm_unsplit.h"

#include "gr/forward.h"

#include "gr/inlines.h"
#include "if/textlib.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/items/itcoin.h"
#include "it/types.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbdvd.h"
#include "lb/lbshadow.h"
#include "lb/lbvector.h"
#include "mp/mpcoll.h"
#include "mp/mplib.h"
#include "mp/types.h"
#include "pl/player.h"
#include "sc/types.h"
#include "ty/toy.h"
#include "ty/tydisplay.h"
#include "ty/tylist.h"

#include <common_structs.h>
#include <math.h>
#include <math_ppc.h>
#include <trigf.h>
#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <dolphin/os/OSError.h>
#include <baselib/cobj.h>
#include <baselib/debug.h>
#include <baselib/fog.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjplink.h>
#include <baselib/gobjproc.h>
#include <baselib/gobjuserdata.h>
#include <baselib/jobj.h>
#include <baselib/lobj.h>
#include <baselib/memory.h>
#include <baselib/particle.h>
#include <baselib/psstructs.h>
#include <baselib/random.h>
#include <baselib/spline.h>
#include <baselib/wobj.h>

/* 1BFFA8 */ static void Ground_OnStart(void);
/* 1BFFAC */ static void Ground_801BFFAC(bool);
/* 1C0A70 */ static bool Ground_801C0A70(Vec3* pos);
/* 1C0C2C */ static void Ground_801C0C2C(HSD_GObj*);
/* 1C1CD0 */ static void Ground_801C1CD0(HSD_GObj*);
/* 1C1D38 */ static void Ground_801C1D38(HSD_GObj*);
/* 1C1E2C */ static void Ground_801C1E2C(HSD_GObj* gobj, int code);
/* 1C1E94 */ static void Ground_801C1E94(void);
/* 1C20E0 */ UNK_T Ground_801C20E0(UnkArchiveStruct*, UNK_T);
/* 1C24F8 */ static bool Ground_801C24F8(s32, u32, s32*);
/* 1C28CC */ void Ground_801C28CC(void*, s32);
/* 1C2BBC */ static void Ground_801C2BBC(HSD_GObj*, s32);
/* 1C2BD4 */ static void Ground_801C2BD4(void*);
/* 1C34AC */ void Ground_801C34AC(s32, HSD_JObj*, struct HSD_Joint*);
/* 1C466C */ void Ground_801C466C(void);
/* 1C55AC */ static void Ground_801C55AC(Ground*);
/* 1C5878 */ static void Ground_801C5878(void);

StageInfo stage_info;

static StageData Ground_803DFEA8 = {
    0,
    NULL,
    NULL,
    Ground_OnStart,
    Ground_801BFFAC,
    Ground_OnStart,
    Ground_OnStart,
    NULL,
    NULL,
    NULL,
    0,
    NULL,
    0,
};

extern StageData Ground_803DFEA8, grTe_803E5764, grCs_803E11A4, grRc_803E4ECC,
    grKg_803E1800, grGd_803E52E0, grGb_803E3F6C, grSh_803E5130, grZe_803E1B2C,
    grKr_803E4D0C, grSt_803E274C, grYt_803E51CC, grIz_803E0E5C, grGr_803E76D0,
    grCn_803E1F08, grVe_803E54CC, grPs_803E1334, grPu_803E6A3C, grMc_803E33DC,
    grBb_803E2D20, grOt_803E2858, grFs_803E3D94, grIm_803E4800, grI1_803E4950,
    grI2_803E4C00, grFz_803E7A00, grOp_803E6748, grOy_803E650C, grOk_803E65E8,
    grNKr_803E584C, grSh_Route_803E5988, grZe_Route_803E5E0C,
    grBb_Route_803E617C, grTe_803E5764, grNBa_803E7E38, grNLa_803E7F90,
    grFigureGet_803E7D34, grPushOn_803E7B10, grTMr_803E85A4, grTCa_803E8664,
    grTCLink_803E872C, grTDk_803E87EC, grTDr_803E88AC, grTFc_803E8974,
    grTFx_803E8A34, grTIc_803E8AF4, grTKb_803E8C0C, grTKp_803E8CCC,
    grTLk_803E8D8C, grTLg_803E8E4C, grTMs_803E8F0C, grTMewtwo_803E8FCC,
    grTNs_803E908C, grTPe_803E914C, grTPc_803E920C, grTPk_803E92CC,
    grTPr_803E9394, grTSs_803E9454, grTSk_803E9514, grTYs_803E95D4,
    grTZd_803E9694, grTGw_803E9754, grTFe_803E981C, grTGn_803E98DC,
    grHeal_803E84C4, grHr_803E821C, grEF1_803E62C0, grEF2_803E6370,
    grEF2_803E6420, grTe_803E5764;

static StageData* Ground_803DFEDC[] = {
    &Ground_803DFEA8,     &grTe_803E5764,       &grCs_803E11A4,
    &grRc_803E4ECC,       &grKg_803E1800,       &grGd_803E52E0,
    &grGb_803E3F6C,       &grSh_803E5130,       &grZe_803E1B2C,
    &grKr_803E4D0C,       &grSt_803E274C,       &grYt_803E51CC,
    &grIz_803E0E5C,       &grGr_803E76D0,       &grCn_803E1F08,
    &grVe_803E54CC,       &grPs_803E1334,       &grPu_803E6A3C,
    &grMc_803E33DC,       &grBb_803E2D20,       &grOt_803E2858,
    &grFs_803E3D94,       &grIm_803E4800,       NULL,
    &grI1_803E4950,       &grI2_803E4C00,       NULL,
    &grFz_803E7A00,       &grOp_803E6748,       &grOy_803E650C,
    &grOk_803E65E8,       &grNKr_803E584C,      &grSh_Route_803E5988,
    &grZe_Route_803E5E0C, &grBb_Route_803E617C, &grTe_803E5764,
    &grNBa_803E7E38,      &grNLa_803E7F90,      &grFigureGet_803E7D34,
    &grPushOn_803E7B10,   &grTMr_803E85A4,      &grTCa_803E8664,
    &grTCLink_803E872C,   &grTDk_803E87EC,      &grTDr_803E88AC,
    &grTFc_803E8974,      &grTFx_803E8A34,      &grTIc_803E8AF4,
    &grTKb_803E8C0C,      &grTKp_803E8CCC,      &grTLk_803E8D8C,
    &grTLg_803E8E4C,      &grTMs_803E8F0C,      &grTMewtwo_803E8FCC,
    &grTNs_803E908C,      &grTPe_803E914C,      &grTPc_803E920C,
    &grTPk_803E92CC,      &grTPr_803E9394,      &grTSs_803E9454,
    &grTSk_803E9514,      &grTYs_803E95D4,      &grTZd_803E9694,
    &grTGw_803E9754,      &grTFe_803E981C,      &grTGn_803E98DC,
    &grHeal_803E84C4,     &grHr_803E821C,       &grEF1_803E62C0,
    &grEF2_803E6370,      &grEF2_803E6420,      &grTe_803E5764,
    &grTe_803E5764,       &grTe_803E5764,       &grTe_803E5764,
    &grTe_803E5764,       &grTe_803E5764,       &grTe_803E5764,
    &grTe_803E5764,       &grTe_803E5764,       &grTe_803E5764,
    &grTe_803E5764,       &grTe_803E5764,       &grTe_803E5764,
    &grTe_803E5764,       &grTe_803E5764,       &grTe_803E5764,
    &grTe_803E5764,       &grTe_803E5764,       &grTe_803E5764,
    &grTe_803E5764,       &grTe_803E5764,       &grTe_803E5764,
    &grTe_803E5764,       &grTe_803E5764,       &grTe_803E5764,
    &grTe_803E5764,       &grTe_803E5764,       &grTe_803E5764,
    &grTe_803E5764,       &grTe_803E5764,       &grTe_803E5764,
    &grTe_803E5764,       &grTe_803E5764,       &grTe_803E5764,
    &grTe_803E5764,       &grTe_803E5764,       &grTe_803E5764,
    &grTe_803E5764,       &grTe_803E5764,       &grTe_803E5764,
};

#define _BUFFER_SZ (64)

static u8* Ground_804D6950;

/// @todo Move elsewhere.
static inline f32 fabsf(f32 x)
{
    if (x < 0) {
        return -x;
    } else {
        return x;
    }
}

static void Ground_OnStart(void) {}

static void Ground_801BFFAC(bool arg0) {}

static void zeroStageInfoArrays(void)
{
    int i;
    for (i = 0; i < 64; i++) {
        stage_info.x180[i] = NULL;
    }
    for (i = 0; i < 261; i++) {
        stage_info.x280[i] = NULL;
    }
}

void Ground_801BFFB0(void)
{
    u32 _[2];
    grDatFiles_801C6288();
    stage_info.flags = 0;
    stage_info.x6D0 = -1;
    stage_info.x6D2 = 0;
    stage_info.x6D4 = 0;
    stage_info.x6D8 = 0;
    stage_info.x6DC = 0;
    stage_info.x724 = -10000;
    stage_info.x12C = NULL;
    stage_info.unk8C.b3 = false;
    stage_info.unk8C.b2 = true;
    stage_info.x178 = NULL;
    stage_info.x17C = NULL;
    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = false;
    stage_info.unk8C.b6 = false;
    stage_info.x714 = -1;
    stage_info.x90 = NULL;
    stage_info.unk8C.b7 = false;
    stage_info.x720 = -1;
    stage_info.x94 = NULL;
    zeroStageInfoArrays();
    stage_info.x694[0] = NULL;
    stage_info.x694[1] = NULL;
    stage_info.x694[2] = NULL;
    stage_info.x694[3] = NULL;
    stage_info.x6A4 = NULL;
    stage_info.cam_info.cam_bounds.left = -170;
    stage_info.cam_info.cam_bounds.right = 170;
    stage_info.cam_info.cam_bounds.top = 120;
    stage_info.cam_info.cam_bounds.bottom = -60;
    stage_info.cam_info.cam_x_offset = 0;
    stage_info.cam_info.cam_y_offset = 0;
    stage_info.cam_info.cam_vertical_tilt = 30;
    stage_info.cam_info.cam_pan_degrees = -10;
    stage_info.cam_info.x20 = 0.2;
    stage_info.cam_info.x24 = 0.2;
    stage_info.cam_info.cam_zoom_rate = 82;
    stage_info.cam_info.cam_max_depth = 1000;
    stage_info.blast_zone.left = -99999;
    stage_info.blast_zone.right = 99999;
    stage_info.blast_zone.top = 99999;
    stage_info.blast_zone.bottom = -99999;
    stage_info.internal_stage_id = -1;
    stage_info.x6D2 = 0;
    stage_info.x6D4 = 0;
    stage_info.x98 = -1;
    stage_info.x9C = 0;
    stage_info.x72C = 0;
    stage_info.x6E0 = 0;
    stage_info.x708 = 0;
    stage_info.x740 = 0;
}

static void zeroBuffer(void)
{
    int i;
    for (i = 0; i < _BUFFER_SZ; i++) {
        Ground_804D6950[i] = 0;
    }
}

void Ground_801C0378(int arg0)
{
    ftCo_800C06C0();
    Ground_804D6950 = HSD_MemAlloc(_BUFFER_SZ);
    zeroBuffer();
}

void Ground_801C0478(void* ptr)
{
    HSD_Free(ptr);
}

f32 Ground_801C0498(void)
{
    UnkStage6B0* temp_r3 = stage_info.param;
    if (temp_r3 != NULL) {
        return temp_r3->x0;
    } else {
        return 1.0F;
    }
}

static void* alloc_user_data_ground(void)
{
    Ground* temp_r3 = HSD_MemAlloc(sizeof(Ground));
    if (temp_r3 == NULL) {
        OSReport("%s:%d: couldn t get user data(Ground)\n", __FILE__, 0x1DA);
    }
    return temp_r3;
}

void Ground_801C04BC(f32 arg8)
{
    UnkStage6B0* temp_r3 = stage_info.param;
    if (temp_r3 != NULL) {
        temp_r3->x0 = arg8;
    } else {
        HSD_ASSERT(521, 0);
    }
}

s32 Ground_801C0508(void)
{
    UnkStage6B0* temp_r3 = stage_info.param;
    return temp_r3 != NULL ? temp_r3->x4 : 128;
}

void Ground_801C052C(GXColor* arg0)
{
    UnkStage6B0* x = stage_info.param;
    x->xB8 = *arg0;
}

void Ground_801C0544(GXColor* arg0)
{
    UnkStage6B0* x = stage_info.param;
    x->xC0 = *arg0;
}

void Ground_801C055C(GXColor* arg0)
{
    UnkStage6B0* x = stage_info.param;
    x->xD0 = *arg0;
}

void Ground_801C0574(GXColor* arg0)
{
    UnkStage6B0* x = stage_info.param;
    x->xD8 = *arg0;
}

void Ground_801C058C(GXColor* arg0)
{
    UnkStage6B0* x = stage_info.param;
    x->xC4 = *arg0;
}

void Ground_801C05A4(GXColor* arg0)
{
    UnkStage6B0* x = stage_info.param;
    x->xCC = *arg0;
}

void Ground_801C05BC(GXColor* arg0)
{
    UnkStage6B0* x = stage_info.param;
    x->xD4 = *arg0;
}

void Ground_801C05D4(GXColor* arg0)
{
    UnkStage6B0* x = stage_info.param;
    x->xBC = *arg0;
}

void Ground_801C05EC(GXColor* arg0)
{
    UnkStage6B0* x = stage_info.param;
    x->xC8 = *arg0;
}

GXColor* Ground_801C0604(void)
{
    UnkStage6B0* x = stage_info.param;
    return &x->xB8;
}

GXColor* Ground_801C0618(void)
{
    UnkStage6B0* x = stage_info.param;
    return &x->xC0;
}

GXColor* Ground_801C062C(void)
{
    UnkStage6B0* x = stage_info.param;
    return &x->xD0;
}

GXColor* Ground_801C0640(void)
{
    UnkStage6B0* x = stage_info.param;
    return &x->xD8;
}

GXColor* Ground_801C0654(void)
{
    UnkStage6B0* x = stage_info.param;
    return &x->xC4;
}

GXColor* Ground_801C0668(void)
{
    UnkStage6B0* x = stage_info.param;
    return &x->xCC;
}

GXColor* Ground_801C067C(void)
{
    UnkStage6B0* x = stage_info.param;
    return &x->xD4;
}

GXColor* Ground_801C0690(void)
{
    UnkStage6B0* x = stage_info.param;
    return &x->xBC;
}

GXColor* Ground_801C06A4(void)
{
    UnkStage6B0* x = stage_info.param;
    return &x->xC8;
}

void Ground_801C06B8(InternalStageId arg0)
{
    if (Ground_803DFEDC[arg0] == NULL) {
        return;
    }
    if (Ground_803DFEDC[arg0]->data1 != NULL) {
        lbDvd_800178E8(4, Ground_803DFEDC[arg0]->data1, 4, 4, 0, 1, 7, 16, 0);
    }
    switch (arg0) {
    case IZUMI:
        grIzumi_801CD2D4();
        return;
    case PSTADIUM:
        grStadium_801D511C();
        return;
    }
}

void Ground_801C0754(StructPairWithStageID* pair)
{
    StageData* stage;
    s32 arg3;
    Ground_801BFFB0();
    stage_info.internal_stage_id = pair->stage_id;
    stage = Ground_803DFEDC[pair->stage_id];
    arg3 = (pair->list_idx == 0x55) ? 0 : 1;
    grDatFiles_801C6038(stage->data1, 0, arg3);
    Ground_801C28CC(stage_info.xA0, pair->list_idx);
    stage_info.x178 = stage->callback5;
    stage_info.x17C = stage->callback6;
    Ground_801C5878();
}

void Ground_801C0800(StructPairWithStageID* pair)
{
    StageData* stage_data = Ground_803DFEDC[pair->stage_id];
    Ground_801C38D0(stage_info.param->x8, stage_info.param->x14,
                    stage_info.param->x1C, stage_info.param->x18);
    Ground_801C38EC(stage_info.param->x10, stage_info.param->xC);
    Ground_801C3970(stage_info.param->x28);
    Ground_801C3900(stage_info.param->x2E, stage_info.param->x30,
                    stage_info.param->x34, stage_info.param->x38,
                    stage_info.param->x3C, stage_info.param->x40,
                    stage_info.param->x44, stage_info.param->x48);
    Ground_801C392C(stage_info.param->x50, stage_info.param->x54,
                    stage_info.param->x58, stage_info.param->x5C,
                    stage_info.param->x60, stage_info.param->x64);
    Ground_801C3960(stage_info.param->x20);
    Ground_801C3950(stage_info.param->x24);
    {
        int i;
        if (stage_info.itemdata != NULL) {
            for (i = 0; stage_info.itemdata[i] != NULL; i++) {
                it_8026B40C(stage_info.itemdata[i]->unk4,
                            stage_info.itemdata[i]->unk0);
            }
        }

        if (stage_info.ald_yaku_all != NULL) {
            for (i = 1; stage_info.ald_yaku_all[i] != NULL; i++) {
                Article* a = it_804D6D38[Pokemon_Random - It_Kind_Kuriboh];
                a->xC_itemStates->x0_itemStateDesc[i].xC_script =
                    stage_info.ald_yaku_all[i];
            }
        }
    }
    if (stage_info.map_ptcl != NULL && stage_info.map_texg != NULL) {
        psInitDataBankLoad(0x1E, stage_info.map_ptcl, stage_info.map_texg, 0,
                           0);
    }
    mpLibLoad(stage_info.coll_data);
    mpLib_80058820();
    Ground_801C1E94();
    Ground_801C466C();
    stage_data->callback0();
}

static bool Ground_801C0A70(Vec3* pos)
{
    if (HSD_Randi(2) != 0) {
        InternalStageId enabled_stages[] = {
            CASTLE,
            RCRUISE,
            KONGO,
            GARDEN,
            GREATBAY,
            SHRINE,
            ZEBES,
            KRAID,
            STORY,
            YORSTER,
            IZUMI,
            GREENS,
            CORNERIA,
            VENOM,
            PSTADIUM,
            PURA,
            MUTECITY,
            BIGBLUE,
            ONETT,
            FOURSIDE,
            // ICEMTN disabled
            // id 0x17 _/unknown?
            INISHIE1,
            INISHIE2,
            // id 0x1A _/unknown?
            // FLATZONE disabled
            OLDPUPUPU,
            OLDYOSHI,
            OLDKONGO,
            // TODO: what stages are these?
            36,
            37,
        };
        enum_t player_slot;
        size_t nstages = sizeof(enabled_stages) / sizeof(enabled_stages[0]);
        u32 _[5];
        size_t i;
        InternalStageId stage_id = stage_info.internal_stage_id;
        for (i = 0; i < nstages; i++) {
            if (stage_id == enabled_stages[i]) {
                break;
            }
        }
        if (i != nstages) {
            player_slot = HSD_Randi(4);
            if (Player_GetEntity(player_slot) != NULL) {
                s32 xoff;
                Player_LoadPlayerCoords(player_slot, pos);
                pos->y = -5.0f + Stage_GetBlastZoneTopOffset();
                xoff = HSD_Randi(0x64) - 0x32;
                pos->x += xoff;
                return true;
            }
        }
    }
    if (Stage_80224FDC(pos) != 0) {
        return true;
    } else {
        return false;
    }
}

BobOmbRain const Ground_803B7DEC = { 0, 0, 0, 0, 0, 6 };

HSD_Joint const Ground_803B7E0C = {
    NULL,        0,           NULL,        NULL, NULL,
    { 0, 0, 0 }, { 1, 1, 1 }, { 0, 0, 0 }, NULL, NULL,
};

void Ground_801C0C2C(HSD_GObj* arg0)
{
    Vec3 sp50;
    Vec3 sp44;
    Vec3 sp38;
    Vec3 sp2C;

    if (stage_info.unk8C.b6 || stage_info.unk8C.b7) {
        HSD_GObj* gobj = Ground_801C57A4();
        if (gobj != NULL && !ftLib_8008701C(gobj)) {
            ftLib_80086644(gobj, &sp50);
            if (stage_info.unk8C.b6) {
                bool result = false;
                f32 x_min = -stage_info.x70C;
                f32 y_min = -stage_info.x710;
                f32 x_max = +stage_info.x70C;
                f32 y_max = +stage_info.x710;
                int i;
                for (i = 0x99; i < 0xB3; i++) {
                    if (Ground_801C2D24(i, &sp44)) {
                        bool var_r0_2 = 0;
                        bool var_r3_2 = 0;
                        bool var_r4_2 = 0;
                        f32 xpos = sp50.x - sp44.x;
                        f32 ypos = sp50.y - sp44.y;
                        if (xpos > x_min && xpos < x_max) {
                            var_r4_2 = 1;
                        }
                        if (var_r4_2 && ypos > y_min) {
                            var_r3_2 = 1;
                        }
                        if (var_r3_2 && ypos < y_max) {
                            var_r0_2 = 1;
                        }
                        if (var_r0_2 && (stage_info.x90 == NULL ||
                                         stage_info.x90(&sp50, i)))
                        {
                            result = true;
                            break;
                        }
                    }
                }
                if (result) {
                    stage_info.x714 = i;
                } else {
                    stage_info.x714 = -1;
                }
                stage_info.unk8C.b6 = false;
            }
            if (stage_info.unk8C.b7) {
                bool result = false;
                f32 x_min = -stage_info.x718;
                f32 y_min = -stage_info.x71C;
                f32 x_max = +stage_info.x718;
                f32 y_max = +stage_info.x71C;
                int i;
                for (i = 0xBD; i < 0xC7; i++) {
                    if (Ground_801C2D24(i, &sp38)) {
                        bool var_r0_2 = 0;
                        bool var_r3_2 = 0;
                        bool var_r4_2 = 0;
                        f32 xpos = sp50.x - sp38.x;
                        f32 ypos = sp50.y - sp38.y;
                        if (xpos > x_min && xpos < x_max) {
                            var_r4_2 = 1;
                        }
                        if (var_r4_2 && ypos > y_min) {
                            var_r3_2 = 1;
                        }
                        if (var_r3_2 && ypos < y_max) {
                            var_r0_2 = 1;
                        }
                        if (var_r0_2 && (stage_info.x94 == NULL ||
                                         stage_info.x94(&sp50, i)))
                        {
                            result = true;
                            break;
                        }
                    }
                }
                if (result) {
                    stage_info.x720 = i;
                } else {
                    stage_info.x720 = -1;
                }
                stage_info.unk8C.b7 = false;
            }
        }
    }
    if (gm_8016B238()) {
        int temp_r3_2 = gm_8016AEDC();
        if (temp_r3_2 > 0x4B0 && temp_r3_2 - stage_info.x9C > 0x1E) {
            stage_info.x9C = temp_r3_2;
            if (Ground_801C0A70(&sp2C)) {
                BobOmbRain spC = Ground_803B7DEC;
                spC.x8_vec = sp2C;
                it_8026BE84(&spC);
            }
        }
    }
}

void Ground_801C0F78(StructPairWithStageID* pair)
{
    Ground_803DFEDC[pair->stage_id]->OnLoad();
}

void Ground_801C0FB8(StructPairWithStageID* pair)
{
    struct {
        void* unk0;
        s32 unk4;
        void (*unk8)(s32);
    }* cur;
    void* next;
    Ground_803DFEDC[pair->stage_id]->OnStart();
    for (cur = stage_info.x6A4; cur != NULL; cur = next) {
        next = cur->unk0;
        cur->unk8(cur->unk4);
        HSD_Free(cur);
    }
    stage_info.x6A4 = NULL;
    HSD_GObjProc_8038FD54(GObj_Create(HSD_GOBJ_CLASS_STAGE, 5, 0),
                          Ground_801C0C2C, 10);
}

void Ground_801C1074(StructPairWithStageID* pair, s32 arg1)
{
    Ground_803DFEDC[pair->stage_id]->callback1(arg1);
}

void Ground_801C10B8(HSD_GObj* arg0, HSD_GObjEvent arg1)
{
    struct {
        void* unk0;
        HSD_GObj* unk4;
        HSD_GObjEvent unk8;
    }* temp_r3;
    temp_r3 = HSD_MemAlloc(0xC);
    if (temp_r3 != NULL) {
        temp_r3->unk0 = stage_info.x6A4;
        temp_r3->unk4 = arg0;
        temp_r3->unk8 = arg1;
        stage_info.x6A4 = temp_r3;
    } else {
        OSReport("%s:%d: assert\n", __FILE__, 1119);
        OSPanic(__FILE__, 1120, "");
    }
}

void Ground_801C1154(void) {}

void Ground_801C1158(void)
{
    switch (stage_info.internal_stage_id) {
    case PSTADIUM:
        grStadium_801D39A0(Ground_801C2BA4(1));
        break;
    case CORNERIA:
    case VENOM:
        grCorneria_801E2A6C();
        break;
    }
}

void Ground_801C11AC(HSD_GObj* gobj)
{
    HSD_JObj* jobj;
    Vec3 scale;
    f32 tmp = 1.0f;
    jobj = gobj->hsd_obj;
    scale.z = tmp;
    scale.y = tmp;
    scale.x = tmp;
    HSD_JObjSetScale(jobj, &scale);
}

static HSD_Joint* Ground_801C126C(HSD_Joint* node, s32* depth)
{
    HSD_Joint* result;
    *depth -= 1;
    if (*depth < 0) {
        return node;
    }
    if (node->child != NULL) {
        if ((result = Ground_801C126C(node->child, depth)) != NULL) {
            return result;
        }
    }
    if (node->next != NULL) {
        if ((result = Ground_801C126C(node->next, depth)) != NULL) {
            return result;
        }
    }
    return NULL;
}

HSD_JObj* Ground_801C13D0(s32 arg0, s32 depth)
{
    HSD_JObj* result = NULL;
    UnkArchiveStruct* archive = grDatFiles_801C6330(arg0);
    if (archive != NULL && arg0 < archive->unk4->unkC) {
        HSD_Joint* joint;
        if (depth == 0) {
            joint = archive->unk4->unk8[arg0].unk0;
        } else {
            s32 tmp_depth = depth;
            joint =
                Ground_801C126C(archive->unk4->unk8[arg0].unk0, &tmp_depth);
        }
        result = HSD_JObjLoadJoint(joint);
    }
    return result;
}

static char Ground_804D44F8[8] = "archive";

#define assert_line(line, cond)                                               \
    ((cond) ? (void) 0 : __assert(__FILE__, line, #cond))

static HSD_JObj* get_jobj_inline(float phi_f0)
{
    HSD_JObj* jobj;
    HSD_Joint sp14 = Ground_803B7E0C;
    sp14.scale.x = sp14.scale.y = sp14.scale.z = phi_f0;
    jobj = HSD_JObjLoadJoint(&sp14);
    if (jobj == NULL) {
        OSReport("%s:%d: couldn t get jobj\n", __FILE__, 0x4C4);
        while (1) {
        }
    }
    return jobj;
}

Ground_GObj* Ground_801C14D0(int map_id)
{
    StageInfo* stageinfo = &stage_info;
    float phi_f0;
    HSD_JObj* new_var;
    HSD_GObj* new_var2;
    HSD_CObj* temp_r27;
    HSD_JObj* temp_r3_11;
    HSD_Joint* temp_r24;
    HSD_JObj* temp_r23;
    HSD_GObj* gobj;
    UnkArchiveStruct* archive;
    HSD_JObj* temp_r3_8;
    Ground* temp_r3;
    s16* phi_r23;
    int phi_r24;
    int i;

    gobj = GObj_Create(HSD_GOBJ_CLASS_STAGE, 5, 0);
    if (gobj == NULL) {
        OSReport("%s:%d: couldn t get gobj!\n", __FILE__, 0x522);
        return NULL;
    }
    temp_r3 = alloc_user_data_ground();
    if (temp_r3 == NULL) {
        HSD_GObjPLink_80390228(gobj);
        return NULL;
    }
    GObj_InitUserData(gobj, 3, Ground_801C0478, temp_r3);
    temp_r3->map_id = map_id;
    temp_r3->gobj = gobj;
    temp_r3->x10_flags.b0 = 0;
    temp_r3->x10_flags.b1 = 0;
    temp_r3->x10_flags.b2 = 1;
    temp_r3->x8_callback = 0;
    temp_r3->xC_callback = 0;
    temp_r3->x1C_callback = 0;
    temp_r3->x10_flags.b5 = 0;
    temp_r3->x10_flags.b6 = 0;
    temp_r3->x11_flags.b012 = 0;
    temp_r3->x10_flags.b7 = 0;
    temp_r3->x18 = 0;
    temp_r3->x10_flags.b3 = 0;
    {
        size_t i;
        for (i = 0; i < ARRAY_SIZE(temp_r3->x20); i++) {
            temp_r3->x20[i] = -1;
        }
    }

    grMaterial_801C95C4(gobj);
    archive = grDatFiles_801C6324();
    assert_line(0x54E, archive);

    if (map_id < archive->unk4->unkC) {
        archive = grDatFiles_801C6330(map_id);
        temp_r24 = archive->unk4->unk8[map_id].unk0;
        temp_r23 = HSD_JObjLoadJoint(temp_r24);
        Ground_801C34AC(map_id, temp_r23, temp_r24);
        if (stageinfo->param != NULL) {
            phi_f0 = stageinfo->param->x0;
        } else {
            phi_f0 = 1.0f;
        }
        new_var = get_jobj_inline(phi_f0);
        HSD_JObjAddNext(temp_r23, new_var);
        if (new_var == NULL) {
            HSD_GObjPLink_80390228(gobj);
            OSReport("%s:%d: couldn t get jobj\n", __FILE__, 0x55D);
            return NULL;
        }
        if (Ground_803DFEDC[stageinfo->internal_stage_id]
                    ->callbacks[map_id]
                    .flags_b2 == 1 &&
            archive->unk4->unk8[map_id].x10 != NULL)
        {
            HSD_GObj* temp_r23_2 = GObj_Create(17, 19, 0);
            temp_r27 = lb_80013B14(archive->unk4->unk8[map_id].x10);
            new_var2 = temp_r23_2;
            HSD_GObjObject_80390A70(temp_r23_2, HSD_GObj_804D784B, temp_r27);
            GObj_SetupGXLinkMax(new_var2, &grDisplay_801C5F60, 5);
            temp_r23_2->gxlink_prios = 8;
            temp_r3->x18 = temp_r23_2;
            Ground_801C2BD4(temp_r27);
        }
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, new_var);
        phi_r24 = archive->unk4->unk8[map_id].x30;
        phi_r23 = archive->unk4->unk8[map_id].x2C;
        for (; phi_r24 != 0; phi_r24--, phi_r23++) {
            if ((temp_r3_8 = Ground_801C3FA4(gobj, *phi_r23)) != NULL) {
                lb_8000F9F8(temp_r3_8);
            }
        }
    } else {
        new_var = HSD_JObjAlloc();
        if (new_var != NULL) {
            PSMTXIdentity(new_var->mtx);
            new_var->scl = NULL;
        }
        if (stageinfo->param != NULL) {
            phi_f0 = stageinfo->param->x0;
        } else {
            phi_f0 = 1.0f;
        }
        temp_r3_11 = get_jobj_inline(phi_f0);
        HSD_JObjAddNext(new_var, temp_r3_11);
        if (temp_r3_11 == NULL) {
            HSD_GObjPLink_80390228(gobj);
            OSReport("%s:%d: couldn t get jobj\n", __FILE__, 0x598);
            return NULL;
        }
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, temp_r3_11);
    }
    HSD_GObjProc_8038FD54(gobj, &Ground_801C1CD0, 1);
    HSD_GObjProc_8038FD54(gobj, &Ground_801C1D38, 4);
    Ground_801C2BBC(gobj, map_id);
    return gobj;
}

HSD_GObj* Ground_801C1A20(HSD_Joint* arg0, s32 arg1)
{
    HSD_GObj* temp_r30;
    HSD_JObj* temp_r29;
    HSD_JObj* temp_r3_4;
    f32 phi_f0;
    Ground* gp;
    int i;

    temp_r30 = GObj_Create(HSD_GOBJ_CLASS_STAGE, 5, 0);
    if (temp_r30 == NULL) {
        OSReport("%s:%d: couldn t get gobj!\n", __FILE__, 0x5B8);
        return NULL;
    }
    gp = alloc_user_data_ground();
    if (gp == NULL) {
        HSD_GObjPLink_80390228(temp_r30);
        return NULL;
    }
    GObj_InitUserData(temp_r30, 3, Ground_801C0478, gp);
    gp->map_id = arg1;
    gp->gobj = temp_r30;
    gp->x10_flags.b0 = 0;
    gp->x10_flags.b1 = 0;
    gp->x10_flags.b2 = 1;
    gp->x8_callback = NULL;
    gp->xC_callback = NULL;
    gp->x1C_callback = NULL;
    gp->x10_flags.b5 = 0;
    gp->x18 = NULL;
    gp->x10_flags.b3 = 0;
    for (i = 0; i < 8; i++) {
        gp->x20[i] = -1;
    }
    grMaterial_801C95C4(temp_r30);
    temp_r29 = HSD_JObjLoadJoint(arg0);
    Ground_801C34AC(arg1, temp_r29, arg0);
    temp_r3_4 = get_jobj_inline(Ground_801C0498());
    HSD_JObjAddNext(temp_r29, temp_r3_4);
    if (temp_r3_4 == NULL) {
        HSD_GObjPLink_80390228(temp_r30);
        OSReport("%s:%d: couldn t get jobj\n", __FILE__, 0x5E8);
        return NULL;
    }
    HSD_GObjObject_80390A70(temp_r30, HSD_GObj_804D7849, temp_r3_4);
    HSD_GObjProc_8038FD54(temp_r30, Ground_801C1CD0, 1);
    HSD_GObjProc_8038FD54(temp_r30, Ground_801C1D38, 4);
    return temp_r30;
}

static void Ground_801C1CD0(HSD_GObj* gobj)
{
    u32 _[2];
    HSD_JObj* jobj = gobj->hsd_obj;
    Ground* gp = gobj->user_data;
    HSD_JObjAnimAll(jobj);
    grMaterial_801C9698(gobj);
    mpColl_804D64AC += 1;
    if (gp->x8_callback != NULL) {
        gp->x8_callback(gobj);
    }
}

static void Ground_801C1D38(HSD_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    if (gp->xC_callback != NULL) {
        gp->xC_callback(gobj);
    }
}

void Ground_801C1D6C(u32 arg0)
{
    stage_info.flags |= arg0;
}

u32 Ground_801C1D84(void)
{
    return stage_info.flags & 0x330;
}

u32 Ground_801C1D98(void)
{
    return stage_info.flags & 0x20;
}

u32 Ground_801C1DAC(void)
{
    return stage_info.flags & 0x100;
}

u32 Ground_801C1DC0(void)
{
    return stage_info.flags & 0x80;
}

s16 Ground_801C1DD4(void)
{
    return stage_info.x6D0;
}

void Ground_801C1DE4(s32* arg0, s32* arg1)
{
    *arg0 = stage_info.x6D4;
    *arg1 = stage_info.x6D2;
}

void Ground_801C1E00(s32 arg0)
{
    stage_info.unk8C.b2 = arg0;
}

s32 Ground_801C1E18(void)
{
    return stage_info.unk8C.b2;
}

void Ground_801C1E2C(HSD_GObj* gobj, int code)
{
    bool stage_is_something;
    HSD_JObj* jobj;
    if (Camera_80030A78()) {
        return;
    }
    stage_is_something = stage_info.unk8C.b2;
    if (!stage_is_something) {
        return;
    }
    jobj = gobj->hsd_obj;
    if (jobj != NULL) {
        HSD_FogSet(gobj->hsd_obj);
    }
}

void* Ground_801C1E84(void)
{
    return stage_info.x12C;
}

// void Camera_SetBackgroundColor(u8, u8, u8);     /* extern */
// UnkStruct3* grDatFiles_801C6330(int); /* extern */
// void Ground_801C1E2C(HSD_GObj*, int); /* extern */
// extern s8 HSD_GObj_804D7848;
// extern float @330;

inline HSD_FogDesc* foo(void)
{
    StageCallbacks* phi_r29;
    StageCallbacks* temp_r29;
    int temp_r30;
    int i;

    grDatFiles_801C6324();
    temp_r30 = grDatFiles_801C6324()->unk4->unkC;
    temp_r29 = Ground_803DFEDC[stage_info.internal_stage_id]->callbacks;
    grDatFiles_801C6324();
    for (i = 0; i < temp_r30; i++) {
        phi_r29 = &temp_r29[i];
        if (phi_r29->flags_b1 == 1) {
            return grDatFiles_801C6330(i)->unk4->unk8[i].x1C;
        }
    }
    return NULL;
}

void Ground_801C1E94(void)
{
    HSD_Fog* temp_r29_2;
    HSD_GObj* temp_r30_2;

    UnkStage6B0* temp_r3;
    HSD_FogDesc* phi_r0;
    float phi_f1;
    StageInfo* stageinfo = &stage_info;

    phi_r0 = foo();
    if (phi_r0 != NULL) {
        temp_r30_2 = GObj_Create(0xA, 0xB, 0);
        temp_r29_2 = HSD_FogLoadDesc(phi_r0);
        HSD_GObjObject_80390A70(temp_r30_2, HSD_GObj_804D7848, temp_r29_2);
        GObj_SetupGXLink(temp_r30_2, Ground_801C1E2C, 0, 0);
        temp_r3 = stageinfo->param;
        if (temp_r3 != NULL) {
            phi_f1 = temp_r3->x0;
        } else {
            phi_f1 = 1;
        }
        temp_r29_2->start *= phi_f1;
        temp_r29_2->end *= phi_f1;
        Camera_SetBackgroundColor(temp_r29_2->color.r, temp_r29_2->color.g,
                                  temp_r29_2->color.b);
        stageinfo->x12C = temp_r30_2;
    } else {
        Camera_SetBackgroundColor(0, 0, 0);
    }
}

void Ground_ApplyStageBackgroundColor(void)
{
    HSD_Fog* fog;
    if (stage_info.x12C != NULL && (fog = GET_FOG(stage_info.x12C)) != NULL) {
        Camera_SetBackgroundColor(fog->color.r, fog->color.g, fog->color.b);
    } else {
        Camera_SetBackgroundColor(0, 0, 0);
    }
}

void Ground_801C205C(GXColor* color)
{
    if (stage_info.x12C != NULL && color != NULL) {
        HSD_Fog* fog = GET_FOG(stage_info.x12C);
        if (fog != NULL) {
            fog->color = *color;
        }
    }
}

bool Ground_801C2090(GXColor* color)
{
    if (stage_info.x12C != NULL && color != NULL) {
        HSD_Fog* fog = GET_FOG(stage_info.x12C);
        if (fog != NULL) {
            *color = fog->color;
            return true;
        }
    }
    return false;
}

f32 Ground_801C20D0(void)
{
    return stage_info.cam_info.cam_vertical_tilt;
}

/// @todo attempt decomp once param types are known
char lightset[9] = "lightset";
char plightset[10] = "*lightset";

/// #Ground_801C20E0

void Ground_801C2374(HSD_LObj* lobj)
{
    Vec3 vec;
    f32 vec_mul;
    HSD_LObj* cur = lobj;
    vec_mul = Ground_801C0498();
    while (cur != NULL) {
        Vec3* vec_ptr;
        if (HSD_LObjGetPosition(cur, &vec)) {
            vec_ptr = &vec;
            vec.x *= vec_mul;
            vec.y *= vec_mul;
            vec.z *= vec_mul;
            HSD_LObjSetPosition(cur, vec_ptr);
        }
        if (HSD_LObjGetInterest(cur, &vec)) {
            vec_ptr = &vec;
            vec.x *= vec_mul;
            vec.y *= vec_mul;
            vec.z *= vec_mul;
            HSD_LObjSetInterest(cur, vec_ptr);
        }
        cur = cur == NULL ? NULL : cur->next;
    }
}

HSD_Spline* Ground_801C247C(s32 arg0, s32 arg1)
{
    UnkArchiveStruct* archive = grDatFiles_801C6330(arg0);
    if (archive == NULL) {
        __assert(__FILE__, 0x7E1, Ground_804D44F8);
    }
    if (archive->unk4 != NULL && arg1 < archive->unk4->unk14) {
        return archive->unk4->unk10[arg1];
    } else {
        return NULL;
    }
}

static const int BGM_Undefined = -1;

#define RANDI_MAX (100)

static bool Ground_801C24F8(s32 arg0, u32 arg1, s32* arg2)
{
    bool temp_r25;
    /// @todo @c phi_r30 probably belongs to an @c inline.
    UnkBgmStruct* phi_r30;
    UnkBgmStruct* phi_r30_0 = stage_info.param->xB0;
    enum_t bgm = BGM_Undefined;
    bool result = false;
    int i;
    for (i = 0; i < stage_info.param->xB4; i++) {
        phi_r30 = &phi_r30_0[i];
        if (phi_r30->x0 == arg0) {
            if (arg1 & 4) {
                temp_r25 = arg1 & 0x40;
                switch (phi_r30->x14) {
                case 0:
                    if (temp_r25) {
                        arg1 |= 2;
                    } else {
                        arg1 |= 1;
                    }
                    break;
                case 1:
                    if (HSD_Randi(0xC) == 0 || temp_r25) {
                        arg1 |= 2;
                    } else {
                        arg1 |= 1;
                    }
                    break;
                case 8:
                    arg1 |= 1;
                    break;
                case 2:
                    if (phi_r30->x16 > HSD_Randi(RANDI_MAX) || temp_r25) {
                        arg1 |= 2;
                    } else {
                        arg1 |= 1;
                    }
                    break;
                case 3:
                    if (gm_80164840(CKIND_MARS) &&
                        (phi_r30->x16 > HSD_Randi(RANDI_MAX) || temp_r25))
                    {
                        arg1 |= 2;
                    } else {
                        arg1 |= 1;
                    }
                    break;
                case 4:
                    if (gm_80164840(CKIND_CLINK) &&
                        (phi_r30->x16 > HSD_Randi(RANDI_MAX) || temp_r25))
                    {
                        arg1 |= 2;
                    } else {
                        arg1 |= 1;
                    }
                    break;
                case 5:
                    if (un_803048C0(0x11A) &&
                        (phi_r30->x16 > HSD_Randi(RANDI_MAX) || temp_r25))
                    {
                        arg1 |= 2;
                    } else {
                        arg1 |= 1;
                    }
                    break;
                case 6:
                    if (gm_80164ABC() &&
                        (phi_r30->x16 > HSD_Randi(RANDI_MAX) || temp_r25))
                    {
                        arg1 |= 2;
                    } else {
                        arg1 |= 1;
                    }
                    break;
                case 7:
                    if (gm_80164600() &&
                        (phi_r30->x16 > HSD_Randi(RANDI_MAX) || temp_r25))
                    {
                        arg1 |= 2;
                    } else {
                        arg1 |= 1;
                    }
                    break;
                }
            }
            if (arg1 & 0x10) {
                stage_info.unk8C.b0 = 0;
                if (arg1 & 1) {
                    bgm = phi_r30->xC;
                } else if (arg1 & 2) {
                    /// @todo Weird comparison, but typing #UnkBgmStruct::x10
                    /// as @c signed doesn't match and neither does typing
                    /// #BGM_Undefined as @c unsigned.
                    if (phi_r30->x10 != (unsigned) BGM_Undefined) {
                        bgm = phi_r30->x10;
                        result = true;
                    } else {
                        bgm = phi_r30->xC;
                    }
                }
            } else if (arg1 & 0x20) {
                if (arg1 & 1) {
                    bgm = phi_r30->xC;
                    stage_info.unk8C.b0 = false;
                } else if (arg1 & 2) {
                    if (phi_r30->x10 != (unsigned) BGM_Undefined) {
                        bgm = phi_r30->x10;
                        stage_info.unk8C.b0 = true;
                        result = true;
                    } else {
                        bgm = phi_r30->xC;
                        stage_info.unk8C.b0 = false;
                    }
                }
            } else if (arg1 & 1) {
                bgm = phi_r30->x4;
                stage_info.unk8C.b0 = false;
            } else if (arg1 & 2) {
                /// @todo Even weirder.
                if ((unsigned) phi_r30->x8 != (unsigned) BGM_Undefined) {
                    bgm = phi_r30->x8;
                    stage_info.unk8C.b0 = true;
                    result = true;
                } else {
                    bgm = phi_r30->x4;
                    stage_info.unk8C.b0 = false;
                }
            }
            break;
        }
    }
    HSD_ASSERT(2242, bgm!=BGM_Undefined);
    if (bgm == -2) {
        *arg2 = lbAudioAx_8002305C(Player_GetPlayerCharacter(0), HSD_Randi(2));
    } else {
        *arg2 = bgm;
    }
    return result;
}

bool Ground_801C28AC(s32 arg0, u32 arg1, s32* arg2)
{
    return Ground_801C24F8(arg0, arg1, arg2);
}

static char msg0[] =
    "%s:%d: not found stage param in DAT(grkind=%d stkind=%d,num=%d)\n";
static char msg1[] =
    "             check StageParam.csv or StageItem.csv, stdata.c\n";
static char msg2[] = " stageid=%d\n";

/// #Ground_801C28CC

u8* Ground_801C2AD8(void)
{
    return stage_info.xA0;
}

f32 Ground_801C2AE8(s32 arg0)
{
    UnkBgmStruct* phi_r5 = stage_info.param->xB0;
    int i;
    for (i = 0; i < stage_info.param->xB4; i++) {
        if (phi_r5->x0 == arg0) {
            return (0.01f * stage_info.param->x68) * (0.01f * phi_r5->x18);
        }
        phi_r5 += 1;
    }
    OSReport("%s:%d: not found stage param in DAT\n", __FILE__, 0x927);
    while (1) {
    }
}

HSD_GObj* Ground_801C2BA4(s32 i)
{
    return stage_info.x180[i];
}

static void Ground_801C2BBC(HSD_GObj* arg0, s32 i)
{
    stage_info.x180[i] = arg0;
}

static const int Gr_CObj_Max = 4;

static void Ground_801C2BD4(void* arg0)
{
    int i;
    for (i = 0; i < 4; i++) {
        if (stage_info.x694[i] == arg0) {
            return;
        }
    }

    for (i = 0; i < 4; i++) {
        if (stage_info.x694[i] == NULL) {
            stage_info.x694[i] = arg0;
            break;
        }
    }
    HSD_ASSERT(0x94D, i!=Gr_CObj_Max);
}

bool Ground_801C2C8C(void* arg0)
{
    int i;
    for (i = 0; i < 4; i++) {
        if (stage_info.x694[i] == arg0) {
            return true;
        }
    }
    return false;
}

HSD_JObj* Ground_801C2CF4(s32 i)
{
    return stage_info.x280[i];
}

void Ground_801C2D0C(s32 i, HSD_JObj* jobj)
{
    stage_info.x280[i] = jobj;
}

bool Ground_801C2D24(enum_t arg0, Vec3* arg1)
{
    Vec3 sp20;
    Vec3 sp14;
    u32 _;
    if (arg0 == 8) {
        Ground_801C2D24(4, arg1);
        Ground_801C2D24(5, &sp20);
        lbVector_Add(arg1, &sp20);
        arg1->x *= 0.5f;
        arg1->y *= 0.5f;
        arg1->z *= 0.5f;
        return true;
    }
    if (arg0 == 9) {
        Ground_801C2D24(6, arg1);
        Ground_801C2D24(7, &sp14);
        lbVector_Add(arg1, &sp14);
        arg1->x *= 0.5f;
        arg1->y *= 0.5f;
        arg1->z *= 0.5f;
        return true;
    }
    if (stage_info.x280[arg0] != NULL) {
        lb_8000B1CC(stage_info.x280[arg0], NULL, arg1);
        return true;
    }
    if ((unsigned) arg0 - 1 <= 2) {
        return Ground_801C2D24(0, arg1);
    }
    if ((unsigned) arg0 - 5 <= 2) {
        return Ground_801C2D24(4, arg1);
    }
    if (arg0 == 0x7F) {
        if (Ground_801C2D24(0x94, arg1)) {
            arg1->y += 50;
            return true;
        }
        return Ground_801C2D24(0, arg1);
    }
    if (arg0 == 4) {
        Stage_UnkSetVec3TCam_Offset(arg1);
        return true;
    }
    return false;
}

bool Ground_801C2ED0(HSD_JObj* jobj, s32 arg1)
{
    u8 _[4];
    bool result = false;
    UnkArchiveStruct* temp_r3 = grDatFiles_801C6330(arg1);
    S16Vec3* cur;
    int i;
    int max;
    if (temp_r3 != NULL) {
        cur = temp_r3->unk4->unk8[arg1].unk20;
        max = temp_r3->unk4->unk8[arg1].unk24;
        for (i = 0; i < max; i++, cur++) {
            mpLib_800552B0(cur->x, jobj, cur->z);
            mpLib_80055E9C(cur->x);
            mpLib_80057424(cur->x);
            result = true;
        }
    }
    max = Ground_803DFEDC[stage_info.internal_stage_id]->x30;
    cur = Ground_803DFEDC[stage_info.internal_stage_id]->x2C;
    for (i = 0; i < max; i++, cur++) {
        if (cur->y == arg1) {
            mpLib_800552B0(cur->x, jobj, cur->z);
            mpLib_80055E9C(cur->x);
            mpLib_80057424(cur->x);
            result = true;
        }
    }
    Ground_801C3214(arg1);
    return result;
}

static s16 Ground_804D6954;

bool Ground_801C2FE0(Ground_GObj* arg0)
{
    StageData* stagedata;
    UnkArchiveStruct* archive;

    // XXX must be int to match - using enum causes mr instead of addi
    int map_id;

    struct UnkStageDat_x8_t* dat;
    CollJoint* temp_r3;
    bool result;
    S16Vec3* vec;
    int i;
    int count;
    Ground* gr = GET_GROUND(arg0);

    map_id = gr->map_id;

    if (Ground_804D6950[map_id] == 0) {
        result = false;

        temp_r3 = mpGetGroundCollJoint();
        Ground_804D6954++;
        stagedata = Ground_803DFEDC[stage_info.internal_stage_id];
        count = stagedata->x30;
        vec = stagedata->x2C;

        for (i = 0; i < count; i++, vec++) {
            if (vec->y == map_id) {
                mpLib_80055E9C(vec->x);
                temp_r3[vec->x].xC = Ground_804D6954;
                result = true;
            }
        }

        archive = grDatFiles_801C6330(map_id);
        if (archive != NULL) {
            int temp_r30;

            dat = &archive->unk4->unk8[map_id];
            vec = dat->unk20;
            count = dat->unk24;

            for (i = 0; i < count; i++, vec++) {
                if (Ground_804D6954 != temp_r3[vec->x].xC) {
                    mpLib_80055E9C(vec->x);
                    temp_r3[vec->x].xC = Ground_804D6954;
                    result = true;
                }
            }
        }

        return result;
    }

    return false;
}

bool Ground_801C3128(s32 arg0, void (*arg1)(int))
{
    /// @todo Unused variable; is this an argument?
    StageData* stage_data;
    bool result;
    mpGetGroundCollJoint();
    result = false;
    {
        /// @todo @c cur cannot be swapped below @c max, hinting at a missing
        /// @c inline function.
        S16Vec3* cur;
        int max = Ground_803DFEDC[stage_info.internal_stage_id]->x30;
        cur = Ground_803DFEDC[stage_info.internal_stage_id]->x2C;
        {
            int i;
            for (i = 0; i < max; i++, cur++) {
                if (cur->y == arg0) {
                    arg1(cur->x);
                    result = true;
                }
            }
            {
                UnkArchiveStruct* tmp = grDatFiles_801C6330(arg0);
                if (tmp != NULL) {
                    cur = tmp->unk4->unk8[arg0].unk20;
                    max = tmp->unk4->unk8[arg0].unk24;
                    for (i = 0; i < max; i++, cur++) {
                        arg1(cur->x);
                        result = true;
                    }
                }
            }
        }
    }
    return result;
}

bool Ground_801C3214(int arg0)
{
    if (Ground_804D6950[arg0] == 1) {
        Ground_804D6950[arg0] = 0;
        return Ground_801C3128(arg0, mpJointListAdd);
    }

    return false;
}

bool Ground_801C3260(s32 arg0)
{
    if (Ground_804D6950[arg0] == 0) {
        Ground_804D6950[arg0] = 1;
        return Ground_801C3128(arg0, mpLib_80057BC0);
    }
    return false;
}

void Ground_801C32AC(s32 arg0)
{
    Ground_801C3128(arg0, mpLib_80057424);
}

s32 Ground_801C32D4(s32 arg0, s32 arg1)
{
    /// @todo Shared @c inline with #Ground_801C33C0.
    u8 _[4];
    s32 result;
    int max;
    S16Vec3* cur;
    int i;
    mpGetGroundCollJoint();
    /// @todo Might be an @c inline starting here.
    max = Ground_803DFEDC[stage_info.internal_stage_id]->x30;
    cur = Ground_803DFEDC[stage_info.internal_stage_id]->x2C;
    result = -1;
    for (i = 0; i < max; cur++, i++) {
        if (cur->y == arg0 && cur->z == arg1) {
            result = cur->x;
        }
    }
    {
        UnkArchiveStruct* tmp;
        tmp = grDatFiles_801C6330(arg0);
        if (tmp != NULL) {
            max = tmp->unk4->unk8[arg0].unk24;
            cur = tmp->unk4->unk8[arg0].unk20;
            for (i = 0; i < max; cur++, i++) {
                if (cur->z == arg1) {
                    result = cur->x;
                }
            }
        }
    }
    return result;
}

s32 Ground_801C33C0(s32 arg0, s32 arg1)
{
    /// @attention @c x and @c z being swapped compared to #Ground_801C32D4
    ///            is the only difference.
    u8 _[4];
    s32 result;
    int max;
    S16Vec3* cur;
    int i;
    mpGetGroundCollJoint();
    /// @todo Might be an @c inline starting here.
    max = Ground_803DFEDC[stage_info.internal_stage_id]->x30;
    cur = Ground_803DFEDC[stage_info.internal_stage_id]->x2C;
    result = -1;
    for (i = 0; i < max; cur++, i++) {
        if (cur->y == arg0 && cur->x == arg1) {
            result = cur->z;
        }
    }
    {
        UnkArchiveStruct* tmp;
        tmp = grDatFiles_801C6330(arg0);
        if (tmp != NULL) {
            max = tmp->unk4->unk8[arg0].unk24;
            cur = tmp->unk4->unk8[arg0].unk20;
            for (i = 0; i < max; cur++, i++) {
                if (cur->x == arg1) {
                    result = cur->z;
                }
            }
        }
    }
    return result;
}

u32 unknown[] = {
    0x00000002, 0,          0x42C80000, 0x43270000, 0,          0x00000002,
    0x00000001, 0x42C80000, 0x43270000, 0,          0x00000002, 0x00000002,
    0x42C80000, 0x43270000, 0,          0x00000002, 0x00000003, 0x42C80000,
    0x43270000, 0,          0x00000002, 0x00000004, 0x42C80000, 0x43480000,
    0,          0x00000002, 0x00000094, 0,          0x433B0000, 0,
    0x0000000E, 0,          0xC28E0000, 0x436E0000, 0,          0x0000000E,
    0x00000001, 0xC28E0000, 0x436E0000, 0,          0x0000000E, 0x00000002,
    0xC28E0000, 0x436E0000, 0,          0x0000000E, 0x00000003, 0xC28E0000,
    0x436E0000, 0,          0x0000000E, 0x00000094, 0,          0x43750000,
    0,          0x00000015, 0x00000004, 0x41100000, 0x426C0000, 0,
    0x00000015, 0,          0xC1100000, 0x42860000, 0,          0x00000015,
    0x00000001, 0x42580000, 0x40000000, 0,          0x00000015, 0x00000002,
    0xC2960000, 0x40800000, 0,          0x00000015, 0x00000003, 0x42AE0000,
    0xC1500000, 0,          0x0000001F, 0,          0xC4750000, 0x42540000,
    0,          0x0000001F, 0x00000004, 0xC4750000, 0x42F00000, 0,
    0x0000001F, 0x00000099, 0x44C96000, 0x43480000, 0,          0x00000020,
    0,          0x43700000, 0xC3928000, 0,          0x00000020, 0x00000099,
    0x41200000, 0x40000000, 0,          0x00000020, 0x00000004, 0x43700000,
    0,          0,          0x00000021, 0x00000099, 0,          0x446EC000,
    0,          0x00000022, 0,          0xC47A0000, 0x42B00000, 0,
    0x00000022, 0x00000004, 0xC47A0000, 0x42C80000, 0,          0x00000027,
    0,          0x43C30000, 0x44610000, 0,          0x00000027, 0x00000094,
    0x43C30000, 0x44610000, 0,          0x00000027, 0x00000004, 0x43C30000,
    0x44610000, 0,          0x00000013, 0,          0xC2480000, 0x42700000,
    0,          0x00000013, 0x00000004, 0x41F00000, 0x42C80000, 0,
    0x00000006, 0,          0x41F00000, 0x42700000, 0,          0x00000006,
    0x00000004, 0xC2200000, 0x42700000, 0,          0xFFFFFFFF, 0,
    0,          0x40A00000, 0,          0xFFFFFFFF, 0x00000001, 0,
    0x40A00000, 0,          0xFFFFFFFF, 0x00000002, 0,          0x40A00000,
    0,          0xFFFFFFFF, 0x00000003, 0,          0x40A00000, 0,
    0xFFFFFFFF, 0x00000094, 0,          0,          0,          0xFFFFFFFF,
    0xFFFFFFFF, 0,          0,          0,
};

/// #void Ground_801C34AC

void Ground_801C36F4(int map_id, HSD_JObj* root, UNK_T joint)
{
    HSD_JObj* phi_r6;
    UnkStageDat* temp_r3_2;
    UnkArchiveStruct* archive;
    int temp_r4_2;
    struct {
        void* x0;
        u8 x4_pad[0x8];
    }* phi_r3;
    int i;
    u32 unused[4];

    archive = grDatFiles_801C6330(map_id);
    if (archive == NULL) {
        __assert(__FILE__, 2936, "archive");
    }
    if (root == NULL || joint == NULL) {
        OSReport("%s:%d:Error (root=%08x joint=%08x)\n", __FILE__, __FILE__,
                 root, joint);
        return;
    }
    temp_r3_2 = archive->unk4;
    temp_r4_2 = temp_r3_2->unk4;
    if (temp_r4_2 == 0) {
        return;
    }
    phi_r3 = temp_r3_2->unk0;
    for (i = 0; true; i++) {
        if (i >= temp_r4_2) {
            return;
        }
        if (phi_r3[i].x0 == joint) {
            break;
        }
    }

    for (i = 0; i < 0x57 * 3; i++) {
        phi_r6 = stage_info.x280[i];
        if (phi_r6 != NULL) {
            while (phi_r6->parent != NULL) {
                phi_r6 = phi_r6->parent;
            }
            if (phi_r6 == root) {
                stage_info.x280[i] = NULL;
            }
        }
    }
}

void Ground_801C3880(f32 val)
{
    stage_info.cam_info.cam_bounds.top = val;
}

void Ground_801C3890(f32 val)
{
    stage_info.cam_info.cam_bounds.bottom = val;
}

void Ground_801C38A0(f32 val)
{
    stage_info.cam_info.cam_bounds.left = val;
}

void Ground_801C38AC(f32 val)
{
    stage_info.cam_info.cam_bounds.right = val;
}

void Ground_801C38BC(f32 x, f32 y)
{
    stage_info.cam_info.cam_x_offset = x;
    stage_info.cam_info.cam_y_offset = y;
}

void Ground_801C38D0(f32 tilt, f32 pan, f32 a, f32 b)
{
    stage_info.cam_info.cam_vertical_tilt = tilt;
    stage_info.cam_info.cam_pan_degrees = pan;
    stage_info.cam_info.x20 = a;
    stage_info.cam_info.x24 = b;
}

void Ground_801C38EC(f32 depth, f32 zoom)
{
    stage_info.cam_info.cam_max_depth = depth;
    stage_info.cam_info.cam_zoom_rate = zoom;
}

void Ground_801C3900(f32 arg8, f32 arg9, f32 argA, f32 argB, f32 up, f32 down,
                     f32 left, f32 right)
{
    stage_info.cam_info.x3C = arg8;
    stage_info.cam_info.pausecam_zpos_min = arg9;
    stage_info.cam_info.pausecam_zpos_init = argA;
    stage_info.cam_info.pausecam_zpos_max = argB;
    stage_info.cam_info.cam_angle_up = up;
    stage_info.cam_info.cam_angle_down = down;
    stage_info.cam_info.cam_angle_left = left;
    stage_info.cam_info.cam_angle_right = right;
}

void Ground_801C392C(f32 x, f32 y, f32 z, f32 fov, f32 vert, f32 horz)
{
    stage_info.cam_info.fixed_cam_pos.x = x;
    stage_info.cam_info.fixed_cam_pos.y = y;
    stage_info.cam_info.fixed_cam_pos.z = z;
    stage_info.cam_info.fixed_cam_fov = fov;
    stage_info.cam_info.fixed_cam_vert_angle = vert;
    stage_info.cam_info.fixed_cam_horz_angle = horz;
}

void Ground_801C3950(f32 zoom)
{
    stage_info.cam_info.cam_fixed_zoom = zoom;
}

void Ground_801C3960(f32 ratio)
{
    stage_info.cam_info.cam_track_ratio = ratio;
}

void Ground_801C3970(f32 smooth)
{
    stage_info.cam_info.cam_track_smooth = smooth;
}

void Ground_801C3980(f32 top)
{
    stage_info.blast_zone.top = top;
}

void Ground_801C3990(f32 bottom)
{
    stage_info.blast_zone.bottom = bottom;
}

void Ground_801C39A0(f32 left)
{
    stage_info.blast_zone.left = left;
}

void Ground_801C39B0(f32 right)
{
    stage_info.blast_zone.right = right;
}

void Ground_801C39C0(void)
{
    Vec3 sp20;
    Vec3 sp14;
    Vec3 sp8;
    f32 phi_f3;
    f32 phi_f4;
    f32 phi_f5;
    f32 phi_f0;
    f32 phi_f1;
    f32 phi_f2;
    if (Ground_801C2D24(0x95, &sp20) && Ground_801C2D24(0x96, &sp14) &&
        Ground_801C2D24(0x94, &sp8))
    {
        if (sp20.x < sp14.x) {
            phi_f3 = sp20.x - sp8.x;
            phi_f4 = sp14.x - sp8.x;
        } else {
            phi_f3 = sp14.x - sp8.x;
            phi_f4 = sp20.x - sp8.x;
        }
        if (sp20.y < sp14.y) {
            phi_f5 = sp20.y - sp8.y;
            phi_f0 = sp14.y - sp8.y;
        } else {
            phi_f5 = sp14.y - sp8.y;
            phi_f0 = sp20.y - sp8.y;
        }
        phi_f1 = sp8.x;
        phi_f2 = sp8.y;
    } else {
        OSReport("use dummy CamRange ...!\n");
        switch (stage_info.internal_stage_id) {
        default:
            phi_f1 = 0;
            phi_f3 = -170;
            phi_f2 = 0;
            phi_f4 = 170;
            phi_f0 = 120;
            phi_f5 = -60;
            break;
        case 2:
            phi_f3 = -170;
            phi_f4 = 170;
            phi_f0 = 120;
            phi_f5 = -100;
            phi_f1 = 0;
            phi_f2 = 180;
            break;
        case 14:
            phi_f3 = -470;
            phi_f4 = 470;
            phi_f0 = 120;
            phi_f5 = -60;
            phi_f1 = 0;
            phi_f2 = 300;
            break;
        case 26:
            phi_f3 = -470;
            phi_f4 = 470;
            phi_f0 = 180;
            phi_f5 = -60;
            phi_f1 = 0;
            phi_f2 = 130;
            break;
        case 25:
            phi_f3 = -200;
            phi_f4 = 200;
            phi_f0 = 200;
            phi_f5 = -60;
            phi_f1 = 0;
            phi_f2 = 130;
            break;
        case 3:
            phi_f1 = 0;
            phi_f3 = -200;
            phi_f2 = 0;
            phi_f4 = 200;
            phi_f0 = 150;
            phi_f5 = -160;
            break;
        case 11:
            phi_f1 = 0;
            phi_f3 = -170;
            phi_f2 = 0;
            phi_f4 = 170;
            phi_f0 = 180;
            phi_f5 = -60;
            break;
        case 18:
            phi_f1 = 0;
            phi_f3 = -170;
            phi_f2 = 0;
            phi_f4 = 170;
            phi_f0 = 180;
            phi_f5 = 10;
            break;
        }
    }
    stage_info.cam_info.cam_bounds.top = phi_f0;
    stage_info.cam_info.cam_bounds.bottom = phi_f5;
    stage_info.cam_info.cam_bounds.left = phi_f3;
    stage_info.cam_info.cam_bounds.right = phi_f4;
    stage_info.cam_info.cam_x_offset = phi_f1;
    stage_info.cam_info.cam_y_offset = phi_f2;
}

void Ground_801C3BB4(void)
{
    Vec3 sp1C;
    Vec3 sp10;
    u8 _[8];
    f32 lft;
    f32 rgt;
    f32 top;
    f32 bot;
    if (Ground_801C2D24(0x97, &sp1C) && Ground_801C2D24(0x98, &sp10)) {
        if (sp1C.x < sp10.x) {
            lft = sp1C.x - stage_info.cam_info.cam_x_offset;
            rgt = sp10.x - stage_info.cam_info.cam_x_offset;
        } else {
            lft = sp10.x - stage_info.cam_info.cam_x_offset;
            rgt = sp1C.x - stage_info.cam_info.cam_x_offset;
        }
        if (sp1C.y < sp10.y) {
            bot = sp1C.y - stage_info.cam_info.cam_y_offset;
            top = sp10.y - stage_info.cam_info.cam_y_offset;
        } else {
            bot = sp10.y - stage_info.cam_info.cam_y_offset;
            top = sp1C.y - stage_info.cam_info.cam_y_offset;
        }
    } else {
        OSReport("use dummy DeadRange ...\n");
        switch (stage_info.internal_stage_id) {
        default:
            lft = -250;
            rgt = 250;
            top = 200;
            bot = -100;
            break;
        case CASTLE:
            lft = -250;
            rgt = 250;
            top = 180;
            bot = -150;
            break;
        case CORNERIA:
            lft = -550;
            rgt = 550;
            top = 200;
            bot = -100;
            break;
        case InternalStageID_Unk26:
            lft = -600;
            rgt = 600;
            top = 200;
            bot = -100;
            break;
        case SHRINE:
            lft = -550;
            rgt = 550;
            top = 200;
            bot = -150;
            break;
        case INISHIE2:
            lft = -300;
            rgt = 300;
            top = 300;
            bot = -160;
            break;
        case RCRUISE:
            lft = -300;
            rgt = 300;
            top = 270;
            bot = -240;
            break;
        case YORSTER:
            lft = -300;
            rgt = 300;
            top = 210;
            bot = -240;
            break;
        }
    }
    stage_info.blast_zone.top = top;
    stage_info.blast_zone.bottom = bot;
    stage_info.blast_zone.left = lft;
    stage_info.blast_zone.right = rgt;
}

s32 Ground_801C3D44(void* arg0, f32 arg8, f32 arg9)
{
    stage_info.unk8C.b6 = 1;
    stage_info.x70C = 0.5f * arg8;
    stage_info.x710 = 0.5f * arg9;
    stage_info.x90 = arg0;
    if (stage_info.x714 != -1) {
        stage_info.flags |= 0x10;
        stage_info.x6D0 = stage_info.x714;
    } else {
        stage_info.flags &= 0xFFFFFFEF;
    }
    return stage_info.x714;
}

s32 Ground_801C3DB4(void* arg0, f32 arg8, f32 arg9)
{
    stage_info.unk8C.b7 = 1;
    stage_info.x718 = 0.5f * arg8;
    stage_info.x71C = 0.5f * arg9;
    stage_info.x94 = arg0;
    if (stage_info.x720 != -1) {
        stage_info.flags |= 0x40;
    } else {
        stage_info.flags &= 0xFFFFFFBF;
    }
    return stage_info.x720;
}

static HSD_AObj* Ground_801C3E18(HSD_JObj* jobj)
{
    HSD_AObj* result;
    if (jobj == NULL) {
        return NULL;
    }
    if (jobj->aobj != NULL) {
        return jobj->aobj;
    }
    result = Ground_801C3E18(jobj->child);
    if (result != NULL) {
        return result;
    }
    result = Ground_801C3E18(jobj->next);
    if (result != NULL) {
        return result;
    }
    return NULL;
}

f32 Ground_801C3F20(HSD_JObj* arg0)
{
    HSD_AObj* aobj = Ground_801C3E18(arg0);
    if (aobj != NULL) {
        return aobj->curr_frame;
    }
    return 0.0F;
}

HSD_JObj* Ground_801C3FA4(HSD_GObj* gobj, int depth)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    if (gobj->hsd_obj == NULL) {
        return NULL;
    }
    jobj = HSD_JObjGetChild(jobj);
    if (jobj == NULL) {
        return NULL;
    }
    while (jobj != NULL && depth != 0) {
        --depth;
        if (!(jobj->flags & 0x1000) && HSD_JObjGetChild(jobj) != NULL) {
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
    return jobj;
}

/// @todo Why isn't this emitted to @c jobj.c?
HSD_JObj* Ground_801C4100(HSD_JObj* jobj)
{
    if (!(jobj->flags & JOBJ_INSTANCE) && HSD_JObjGetChild(jobj) != NULL) {
        return HSD_JObjGetChild(jobj);
    }
    if (HSD_JObjGetNext(jobj) != NULL) {
        return HSD_JObjGetNext(jobj);
    }
    while (true) {
        if (HSD_JObjGetParent(jobj) == NULL) {
            return NULL;
        }
        if (HSD_JObjGetNext(HSD_JObjGetParent(jobj)) != NULL) {
            return HSD_JObjGetNext(HSD_JObjGetParent(jobj));
        }
        jobj = HSD_JObjGetParent(jobj);
    }
}

s32 Ground_801C4210(void)
{
    u8 _[8];
    /// @todo With a hard-coded range for @c i, very unlikely it's not
    /// returning
    ///       an @c enum. Probably preset joints (accesses a list of
    ///       #HSD_JObj).
    enum_t count = 0;
    enum_t i;
    for (i = 199; i < 220; i++) {
        if (stage_info.x280[i] != NULL &&
            it_8027B5B0(It_Kind_Mato, 0, stage_info.x280[i], NULL, 0) != NULL)
        {
            count++;
        }
    }
    stage_info.x6D4 = count;
    stage_info.x6D2 = count;
    return count;
}

void Ground_801C42AC(void)
{
    BobOmbRain sp8;
    HSD_JObj* jobj;
    int i;
    for (i = 0xFC; i < 0x104; i++) {
        jobj = stage_info.x280[i];
        if (jobj != NULL) {
            sp8.x14 = 0x14;
            sp8.x4 = jobj;
            sp8.x1C.b0 = true;
            it_8026BE84(&sp8);
        }
    }
}

void Ground_801C4338(void)
{
    stage_info.x6D4--;
    if (stage_info.x6D4 == 0) {
        stage_info.flags |= 0x20;
    }
}

void Ground_801C4368(f32* slope, f32* intercept)
{
    *slope = stage_info.x724;
    *intercept = stage_info.x724 - stage_info.x728;
}

void Ground_801C438C(f32 val)
{
    stage_info.x728 = stage_info.x724;
    stage_info.x724 = val;
}

void Ground_801C43A4(UNK_T arg0)
{
    grZebes_801DA3F4(arg0);
}

bool Ground_801C43C4(void* arg0)
{
    UnkStageDat* tmp;
    int max;
    struct {
        void* unk0;
        u8 flag : 1;
    }* phi_r4;
    int i;
    tmp = grDatFiles_801C6324()->unk4;
    phi_r4 = tmp->unk20;
    max = tmp->unk24;
    if (arg0 != NULL && max != 0) {
        for (i = 0; i != max; i++, phi_r4++) {
            if (phi_r4->unk0 == arg0) {
                if (phi_r4->flag) {
                    return true;
                } else {
                    return false;
                }
            }
        }
        HSD_ASSERT(3652, 0);
    }
    return false;
}

void Ground_801C445C(HSD_LObj* lobj)
{
    Vec3 pos0;
    Vec3 pos1;
    Vec3 pos2;
    Vec3 pos3;
    u8 _[4];
    HSD_WObj* wobj;
    HSD_LObj* cur;
    f32 pos_mul;
    if (lobj == NULL) {
        return;
    }
    for (cur = lobj; cur != NULL; cur = cur->next) {
        wobj = HSD_LObjGetPositionWObj(lobj);
        if (wobj != NULL) {
            HSD_WObjGetPosition(wobj, &pos0);
        }
        wobj = HSD_LObjGetInterestWObj(lobj);
        if (wobj != NULL) {
            HSD_WObjGetPosition(wobj, &pos2);
        }
        HSD_LObjAnim(cur);
        wobj = HSD_LObjGetPositionWObj(lobj);
        if (wobj != NULL) {
            HSD_WObjGetPosition(wobj, &pos1);
            if (pos0.x != pos1.x || pos0.y != pos1.y || pos0.z != pos1.z) {
                pos_mul = stage_info.param != NULL ? stage_info.param->x0 : 1;
                pos1.x *= pos_mul;
                pos1.y *= pos_mul;
                pos1.z *= pos_mul;
                HSD_WObjSetPosition(wobj, &pos1);
            }
        }
        wobj = HSD_LObjGetInterestWObj(lobj);
        if (wobj != NULL) {
            HSD_WObjGetPosition(wobj, &pos3);
            if (pos2.x != pos3.x || pos2.y != pos3.y || pos2.z != pos3.z) {
                pos_mul =
                    stage_info.param != NULL ? stage_info.param->x0 : 1.0F;
                pos3.x *= pos_mul;
                pos3.y *= pos_mul;
                pos3.z *= pos_mul;
                HSD_WObjSetPosition(wobj, &pos3);
            }
        }
    }
}

static void Ground_801C461C(HSD_GObj* gobj)
{
    Ground_801C445C(gobj->hsd_obj);
}

static void Ground_801C4640(HSD_GObj* gobj, int unused)
{
    HSD_LObj_803668EC(gobj->hsd_obj);
    HSD_LObjSetupInit(HSD_CObjGetCurrent());
}

static LightList** Ground_801C466C_inline(void)
{
    StageCallbacks* var_r26;
    int i;
    int temp_r28;

    temp_r28 = grDatFiles_801C6324()->unk4->unkC;
    var_r26 = Ground_803DFEDC[stage_info.internal_stage_id]->callbacks;
    grDatFiles_801C6324();

    for (i = 0; i < temp_r28; i++) {
        if (var_r26->flags_b0 == 1) {
            UnkArchiveStruct* archive = grDatFiles_801C6330(i);
            return Ground_801C20E0(archive, archive->unk4->unk8[i].x18);
        }
        var_r26++;
    }
    return NULL;
}

float Ground_803E065C[] = { 0, 0, 0, 0 };
float Ground_803E066C[] = { 0, 0.57, 0.57, 0.57, 0 };

struct a {
    UNK_T x0;
    UNK_T x4;
    int x8;
    int xC;
    UNK_T x10;
    UNK_T x14;
    UNK_T x18;
};

float Ground_804D4508 = 16;

struct a Ground_803E0680 = {
    NULL, NULL, 0xD0000, -1, &Ground_803E066C, NULL, &Ground_804D4508,
};

UNK_T Ground_803E069C[] = { NULL, NULL, NULL, NULL };

struct a Ground_803E06AC = { NULL, NULL, 0x40000, -1, NULL, NULL, NULL };

static LightList* Ground_803E06C8[3] = { 0 };

void Ground_801C466C(void)
{
    Vec3 sp10; /* compiler-managed */
    HSD_GObj* temp_r3;
    HSD_LObj* temp_r3_2;
    HSD_LObj* var_r27;
    LightList** var_r27_2;
    HSD_LObj* var_r26_2;
    LightList** var_r28_2;
    LightList** var_r3;
    float var_f31;
    int temp_r28;

    var_r28_2 = Ground_801C466C_inline();
    if (var_r28_2 == NULL) {
        var_r28_2 = Ground_803E06C8;
    }
    temp_r3 = GObj_Create(0xD, 3, 0);
    if (temp_r3 == NULL) {
        OSReport("%s:%d: couldn t get gobj\n", __FILE__, 0xEAF);
        while (true) {
        }
    }
    temp_r3_2 = lb_80011AC4(var_r28_2);
    if (temp_r3_2 == NULL) {
        OSReport("%s:%d: couldn t get lobj\n", __FILE__, 0xEB1);
        while (true) {
        }
    }
    HSD_GObjObject_80390A70(temp_r3, HSD_GObj_804D784A, temp_r3_2);
    GObj_SetupGXLink(temp_r3, Ground_801C4640, 0, 0);
    var_r27 = temp_r3_2;
    if (stage_info.param != NULL) {
        var_f31 = stage_info.param->x0;
    } else {
        var_f31 = 1.0F;
    }
    while (var_r27 != NULL) {
        if (HSD_LObjGetPosition(var_r27, &sp10) != 0) {
            sp10.x *= var_f31;
            sp10.y *= var_f31;
            sp10.z *= var_f31;
            HSD_LObjSetPosition(var_r27, &sp10);
        }
        if (HSD_LObjGetInterest(var_r27, &sp10) != 0) {
            sp10.x *= var_f31;
            sp10.y *= var_f31;
            sp10.z *= var_f31;
            HSD_LObjSetInterest(var_r27, &sp10);
        }
        if (var_r27 == NULL) {
            var_r27 = NULL;
        } else {
            var_r27 = var_r27->next;
        }
    }
    HSD_LObjReqAnimAll(temp_r3_2, 0.0F);
    HSD_ForeachAnim(temp_r3_2, LOBJ_TYPE, ALL_TYPE_MASK, HSD_AObjSetRate,
                    AOBJ_ARG_AF, 1.0);
    var_r27_2 = var_r28_2;
    var_r26_2 = temp_r3_2;
    if ((*var_r28_2)->anims != NULL) {
        while (var_r26_2 != NULL) {
            if (Ground_801C43C4((*var_r27_2)->anims[0]) != 0) {
                if (var_r26_2->aobj != NULL) {
                    HSD_AObjSetFlags(var_r26_2->aobj, AOBJ_LOOP);
                }
                if (var_r26_2->position != NULL) {
                    HSD_ForeachAnim(var_r26_2->position, WOBJ_TYPE,
                                    ALL_TYPE_MASK, HSD_AObjSetFlags,
                                    AOBJ_ARG_AU, AOBJ_LOOP);
                }
                if (var_r26_2->interest != NULL) {
                    HSD_ForeachAnim(var_r26_2->interest, WOBJ_TYPE,
                                    ALL_TYPE_MASK, HSD_AObjSetFlags,
                                    AOBJ_ARG_AU, AOBJ_LOOP);
                }
            }
            if (var_r26_2 == NULL) {
                var_r26_2 = NULL;
            } else {
                var_r26_2 = var_r26_2->next;
            }
            var_r27_2 += 1;
        }
    }
    HSD_LObjAnimAll(temp_r3_2);
    HSD_GObjProc_8038FD54(temp_r3, Ground_801C461C, 0);
}

HSD_GObj* Ground_801C498C(void)
{
    HSD_GObj* gobj;
    for (gobj = HSD_GObj_Entities->xC; gobj != NULL; gobj = gobj->next) {
        if (gobj->classifier == 13) {
            break;
        }
    }
    return gobj;
}

LightList** Ground_801C49B4(void)
{
    UnkArchiveStruct* archive = grDatFiles_801C6324();
    if (stage_info.map_plit != NULL) {
        return Ground_801C20E0(archive, stage_info.map_plit);
    }
    return Ground_803E06C8;
}

void* Ground_801C49F8(void)
{
    return stage_info.yakumono_param;
}

static inline void removeStageGObj(HSD_GObj* gobj)
{
    void* obj = gobj->hsd_obj;
    int i;
    for (i = 0; i < 4; i++) {
        if (stage_info.x694[i] == obj) {
            stage_info.x694[i] = NULL;
            break;
        }
    }
}

// Stage destroy ground gobj
void Ground_801C4A08(HSD_GObj* gobj)
{
    UnkArchiveStruct* archive;
    Ground* gp;
    HSD_JObj* jobj;
    s32 map_id;
    u8 _[24];
    if (gobj == NULL) {
        return;
    }
    gp = gobj->user_data;
    jobj = gobj->hsd_obj;
    if (gp != NULL) {
        map_id = gp->map_id;
        if (gp->x1C_callback != NULL) {
            gp->x1C_callback(gobj);
        }
        if (stage_info.x180[map_id] == gobj) {
            stage_info.x180[map_id] = NULL;
        }
        Ground_801C55AC(gp);
        if (gp->x18 != NULL) {
            removeStageGObj(gp->x18);
            HSD_GObjPLink_80390228(gp->x18);
        }
        if (gobj->hsd_obj != NULL && Ground_804D6950[map_id] == 0) {
            Ground_804D6950[map_id] = 1;
            Ground_801C3128(map_id, mpLib_80057BC0);
        }
        archive = grDatFiles_801C6330(gp->map_id);
        if (archive != NULL) {
            Ground_801C36F4(gp->map_id, jobj,
                            archive->unk4->unk8[map_id].unk0);
        }
    }
    HSD_GObjPLink_80390228(gobj);
}

void Ground_801C4B50(HSD_Spline* spline, Vec3* arg1, Vec3* result, f32 arg8)
{
    Vec3 vec0;
    Vec3 vec1;
    Vec3 vec2;
    f32 result_x;
    f32 phi_f31;
    f32 result_y;
    f32 result_z;
    f32 z1;
    f32 y0;
    splGetSplinePoint(arg1, spline, arg8);
    lbShadow_8000E9F0(&vec0, spline, arg8);
    lbVector_Normalize(&vec0);
    y0 = vec0.y;
    if (vec0.y < 0.0F) {
        y0 = -vec0.y;
    }
    if (y0 > 0.9L) {
        vec2.x = vec2.y = 0.0F;
        vec2.z = 1.0F;
    } else {
        vec2.x = vec2.z = 0.0F;
        vec2.y = 1.0F;
    }
    lbVector_CrossprodNormalized(&vec0, &vec2, &vec1);
    lbVector_CrossprodNormalized(&vec1, &vec0, &vec2);
    result_y = asinf(vec1.z);
    z1 = vec1.z;
    if (vec1.z < 0.0F) {
        z1 = -vec1.z;
    }
    if (z1 >= 0.99999F) {
        phi_f31 = asinf(-vec0.y);
        if (vec0.x * cosf(phi_f31) * sinf(result_y) < 0.0F) {
            phi_f31 = M_PI - phi_f31;
        }
        result_x = phi_f31;
        result_z = 0.0F;
    } else {
        result_x = asinf(vec2.z / cosf(result_y));
        if (vec0.z * cosf(result_x) * cosf(result_y) < 0) {
            result_x = M_PI - result_x;
        }
        result_z = asinf(-vec1.y / cosf(result_y));
        if (-vec1.x * cosf(result_y) * cosf(result_z) < 0) {
            result_z = M_PI - result_z;
        }
    }
    result->x = result_x;
    result->y = result_y;
    result->z = result_z;
}

bool Ground_801C4D70(HSD_GObj* arg0, Vec3* arg1, f32 arg8)
{
    stage_info.x72C = arg0;
    stage_info.x730 = *arg1;
    stage_info.x73C = arg8;
    return true;
}

bool Ground_801C4DA0(Vec3* arg0, f32* arg1)
{
    *arg0 = stage_info.x730;
    *arg1 = stage_info.x73C;
    return true;
}

bool Ground_801C4DD0(void)
{
    InternalStageId stage_id = stage_info.internal_stage_id;
    if (stage_id == KONGO) {
        grKongo_801D8270(stage_info.x72C);
    } else if (stage_id == OLDKONGO) {
        grOldKongo_802105AC(stage_info.x72C);
    }
    return true;
}

bool Ground_801C4E20(void)
{
    InternalStageId stage_id = stage_info.internal_stage_id;
    if (stage_id == KONGO) {
        grKongo_801D828C(stage_info.x72C);
    } else if (stage_id == OLDKONGO) {
        grOldKongo_802105C8(stage_info.x72C);
    }
    return true;
}

void Ground_801C4E70(HSD_JObj* arg0, HSD_JObj* arg1, HSD_JObj* arg2,
                     HSD_JObj* arg3, HSD_JObj* arg4, HSD_JObj* arg5)
{
    Vec3 vec;
    stage_info.unk8C.b3 = true;
    lb_8000B1CC(arg0, NULL, &vec);
    stage_info.x130 = vec;
    lb_8000B1CC(arg1, NULL, &vec);
    stage_info.x13C = vec;
    lb_8000B1CC(arg2, NULL, &vec);
    stage_info.x148 = vec;
    lb_8000B1CC(arg3, NULL, &vec);
    stage_info.x154 = vec;
    lb_8000B1CC(arg4, NULL, &vec);
    stage_info.x160 = vec;
    lb_8000B1CC(arg5, NULL, &vec);
    stage_info.x16C = vec;
}

struct Node {
    float* x0;
    UNK_T x4;
};

struct Node Ground_804D4500 = { Ground_803E065C, NULL };

SDATA UNK_T Ground_804D450C[] = { &Ground_803E0680, &Ground_804D4500 };
SDATA UNK_T Ground_804D4514[] = { &Ground_803E069C, NULL };
SDATA UNK_T Ground_804D451C[] = { &Ground_803E06AC, &Ground_804D4514 };

SDATA char Ground_804D4524[] = "fog.h";
SDATA char Ground_804D452C[] = "fog";

static inline float vec_len(Vec3* v)
{
    float x2 = v->x * v->x;
    float y2 = v->y * v->y;
    float z2 = v->z * v->z;
    return sqrtf(x2 + y2 + z2);
}

void Ground_801C4FAC(HSD_CObj* cobj)
{
    Vec3 d;
    float dx2;
    float dy2;
    float dz2;
    HSD_Fog* fog;

    float phi_f1;
    float phi_f2;
    float temp_f3_2;
    float phi_f31;
    float phi_f30;

    Vec3 sp74;
    Vec3 sp68;
    Vec3 sp5C;
    Vec3 sp50;
    Vec3 sp44;
    Vec3 sp38;
    Vec3 sp2C;
    Vec3 sp20;

    if (stage_info.unk8C.b3) {
        HSD_CObjGetEyeVector(cobj, &sp74);
        sp68 = stage_info.x130;
        sp5C = stage_info.x13C;
        if (sp74.x < 0) {
            sp50 = stage_info.x148;
            sp44 = stage_info.x154;
        } else {
            sp50 = stage_info.x160;
            sp44 = stage_info.x16C;
        }
        if (sp74.z < 0) {
            temp_f3_2 = 1.0f / sqrtf((sp74.x * sp74.x) + (sp74.z * sp74.z));
            phi_f1 = temp_f3_2 * fabsf(sp74.x);
            phi_f2 = temp_f3_2 * fabsf(sp74.z);
            sp50.x *= phi_f1;
            sp50.y *= phi_f1;
            sp50.z *= phi_f1;

            sp44.x *= phi_f1;
            sp44.y *= phi_f1;
            sp44.z *= phi_f1;

            sp68.x *= phi_f2;
            sp68.y *= phi_f2;
            sp68.z *= phi_f2;

            sp5C.x *= phi_f2;
            sp5C.y *= phi_f2;
            sp5C.z *= phi_f2;
            PSVECAdd(&sp68, &sp50, &sp38);
            PSVECAdd(&sp5C, &sp44, &sp2C);
        } else {
            sp38 = sp50;
            sp2C = sp44;
        }
        HSD_CObjGetEyePosition(cobj, &sp20);
        if (stage_info.x12C != NULL) {
            fog = GET_FOG(stage_info.x12C);
            if (fog != NULL) {
                d.x = sp38.x - sp20.x;
                d.y = sp38.y - sp20.y;
                d.z = sp38.z - sp20.z;
                dx2 = d.x * d.x;
                dy2 = d.y * d.y;
                dz2 = d.z * d.z;
                phi_f31 = sqrtf(dx2 + dy2 + dz2);
                d.x = sp2C.x - sp20.x;
                d.y = sp2C.y - sp20.y;
                d.z = sp2C.z - sp20.z;
                dx2 = d.x * d.x;
                dy2 = d.y * d.y;
                dz2 = d.z * d.z;
                phi_f30 = sqrtf(dx2 + dy2 + dz2);
                if (phi_f30 < 10) {
                    phi_f30 = 10;
                }
                if (phi_f31 < 5) {
                    phi_f31 = 5;
                }
                if (phi_f31 > phi_f30) {
                    phi_f30 = 1.0f + phi_f31;
                }
                if (fog == NULL) {
                    __assert("fog.h", 0xB4, "fog");
                }
                fog->start = phi_f31;

                if (fog == NULL) {
                    __assert("fog.h", 0xBF, "fog");
                }
                fog->end = phi_f30;
            }
        }
    }
}

void Ground_801C53EC(u32 arg0)
{
    lbAudioAx_800237A8(arg0, 0x7F, 0x40);
}

void Ground_801C5414(int arg0, int arg1)
{
    lbAudioAx_80023870(arg0, 0x7F, 0x40, arg1);
}

/// @file
/// @todo Don't hardcode 8
void Ground_801C5440(Ground* gp, s32 i, u32 arg2)
{
    if (i < 0 || i >= 8) {
        return;
    }
    if (gp == NULL) {
        return;
    }
    if (arg2 == 540000) {
        return;
    }
    if (arg2 != 540001) {
        if (gp->x20[i] != -1) {
            Ground* tmp_gp = gp;
            lbAudioAx_800236B8(tmp_gp->x20[i]);
        }
        gp->x20[i] = lbAudioAx_800237A8(arg2, 0x7F, 0x40);
    } else {
        Ground_801C5544(gp, i);
    }
}

bool Ground_801C54DC(Ground* gp, s32 i)
{
    if (i < 0 || i >= 8) {
        return false;
    }
    if (gp != NULL && gp->x20[i] != -1 && lbAudioAx_80023710(gp->x20[i])) {
        return true;
    }
    return false;
}

void Ground_801C5544(Ground* gp, s32 i)
{
    if (i < 0 || i >= 8) {
        return;
    }
    if (gp == NULL) {
        return;
    }
    if (gp->x20[i] != -1) {
        Ground* tmp_gp = gp;
        lbAudioAx_800236B8(tmp_gp->x20[i]);
    }
    gp->x20[i] = -1;
}

static void Ground_801C55AC(Ground* gp)
{
    if (gp != NULL) {
        int i;
        for (i = 0; i < 8; i++) {
            Ground_801C5544(gp, i);
        }
    }
}

void Ground_801C5630(Ground* gp, s32 i, f32 val)
{
    if (i < 0 || i >= 8) {
        return;
    }
    if (gp != NULL && gp->x20[i] != -1) {
        lbAudioAx_80024B58(gp->x20[i], 127 * val);
    }
}

void Ground_801C5694(Ground* gp, s32 i, f32 val)
{
    if (i < 0 || i >= 8) {
        return;
    }
    if (gp != NULL && gp->x20[i] != -1) {
        lbAudioAx_80024B1C(gp->x20[i], 63.5f * (val + 1));
    }
}

DynamicsDesc* Ground_801C5700(int i)
{
    if (stage_info.x178 != NULL) {
        return stage_info.x178(i);
    }
    return NULL;
}

void Ground_801C5740(s32 arg0)
{
    stage_info.x6D8 = arg0;
}

void Ground_801C5750(void)
{
    stage_info.x6D8 = 0;
}

s32 Ground_801C5764(void)
{
    return stage_info.x6D8;
}

s16 Ground_801C5774(void)
{
    return stage_info.x6DC;
}

void Ground_801C5784(s32 arg0)
{
    stage_info.x740 = arg0;
}

s32 Ground_801C5794(void)
{
    return stage_info.x740;
}

HSD_GObj* Ground_801C57A4(void)
{
    return Player_GetEntity(0);
}

HSD_GObj* Ground_801C57C8(void)
{
    return Player_GetEntityAtIndex(0, 1);
}

f32 Ground_801C57F0(void)
{
    return stage_info.x6E0;
}

void Ground_801C5800(void)
{
    if (stage_info.param->x4C_fixed_cam) {
        Camera_8002F8F4();
    } else {
        Camera_8002F474();
    }
}

s32 Ground_801C5840(void)
{
    s32 i = HSD_Randi(1);
    return stage_info.x6E4[i];
}

void Ground_801C5878(void)
{
    PAD_STACK(8);
    tyDisplay_8031C2CC();
    if (gm_8016B498() != 0) {
        int temp_r30 = tyDisplay_8031C2EC();
        un_8031C454();
        stage_info.x6E4[0] = temp_r30;
    } else {
        stage_info.x6E4[0] = -1;
    }
}

Item_GObj* Ground_801C58E0(s32 arg0, s32 arg1)
{
    s32 tmp = arg0;
    Item_GObj* result;
    Vec3 sp10;
    Ground_801C2D24(arg1, &sp10);
    result = it_802F2094(0, &sp10, tmp, 0);
    un_80304A58(tmp);
    return result;
}

static inline s32 randi(s32 max)
{
    if (max != 0) {
        return HSD_Randi(max);
    }
    return 0;
}

int Ground_801C5940(void)
{
    struct {
        u8 x0_pad[0x4];
        struct {
            s16 a, b;
        }* unk4;
        s32 unk8;
    }* phi_r8;
    int i, j, out_idx;
    UnkArchiveStruct* archive;
    const size_t vals_count = 32;
    u8 _[4];
    int vals[vals_count];
    archive = grDatFiles_801C6324();
    out_idx = 0;
    if (archive->unk4->unk4 == 0) {
        return -1;
    }
    phi_r8 = archive->unk4->unk0;
    for (i = 0; i < archive->unk4->unk4; i++, phi_r8++) {
        int max = phi_r8->unk8;
        for (j = 0; j < max; j++) {
            int val = phi_r8->unk4[j].b;
            if (val >= 220 && val < 252 && (unsigned) out_idx < vals_count) {
                vals[out_idx] = val;
                out_idx++;
            }
        }
    }
    if (out_idx == 0) {
        return -1;
    }
    return vals[randi(out_idx)];
}

void Ground_801C5A28(void)
{
    un_803124BC();
    un_8031234C(0);
    un_80305918(0, 0, 1);
}

void Ground_801C5A60(void)
{
    un_8031234C(1);
}

void Ground_801C5A84(s32 arg0)
{
    stage_info.x98 = arg0;
}

s32 Ground_801C5A94(void)
{
    return stage_info.x98;
}

void Ground_801C5AA4(bool arg0)
{
    stage_info.unk8C.b1 = arg0;
}

bool Ground_801C5ABC(void)
{
    return stage_info.unk8C.b1;
}

u32 Ground_801C5AD0(s32 i)
{
    return Ground_803DFEDC[i]->flags2;
}

void Ground_801C5AEC(Vec3* v, Vec3* arg1, Vec3* arg2, Vec3* arg3)
{
    lbVector_EulerAnglesFromONB(v, arg1, arg2, arg3);
    if (!(fabsf(v->x) < 30000)) {
        v->x = 0;
    }
    if (!(fabsf(v->y) < 30000)) {
        v->y = 0;
    }
    if (!(fabsf(v->z) < 30000)) {
        v->z = 0;
    }
}
