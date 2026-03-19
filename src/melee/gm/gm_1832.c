#include "gm_1832.h"

#include "gm_unsplit.h"

#include "pl/pl_040D.h"

#include <math_ppc.h>
#include <sysdolphin/baselib/fog.h>
#include <sysdolphin/baselib/cobj.h>
#include <sysdolphin/baselib/wobj.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/sislib.h>
#include <sysdolphin/baselib/sobjlib.h>
#include <sysdolphin/baselib/state.h>
#include <sysdolphin/baselib/tobj.h>
#include <sysdolphin/baselib/util.h>
#include <melee/cm/camera.h>
#include <melee/ef/efasync.h>
#include <melee/ef/eflib.h>
#include <melee/ft/ft_0877.h>
#include <melee/ft/ftbosslib.h>
#include <melee/ft/ftdemo.h>
#include <melee/ft/ftlib.h>
#include <melee/gm/gm_1A3F.h>
#include <melee/gm/gm_1A45.h>
#include <melee/gm/gm_1601.h>
#include <melee/gm/gm_1A36.h>
#include <melee/gm/types.h>
#include <melee/gr/ground.h>
#include <melee/gr/grpushon.h>
#include <melee/gr/stage.h>
#include <melee/if/ifstatus.h>
#include <melee/if/ifall.h>
#include <melee/it/item.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lb_00F9.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lbbgflash.h>
#include <melee/lb/lblanguage.h>
#include <melee/mn/types.h>
#include <melee/mp/mpcoll.h>
#include <melee/pl/player.h>
#include <melee/sc/types.h>

static struct {
    int x0;
    HSD_JObj* x4[13];
    u16 x38;
    u16 x3A;
    u16 x3C;
    u16 x3E;
} lbl_804735A8;
/// @brief related to 1p splash screen
static struct {
    HSD_ImageDesc x40[3];
    HSD_ImageDesc x88[3];
    u8 pad[0xE0 - 0x88 - 3 * 0x18];
    u8 xE0;
    u8 xE1;
    u8 xE2;
    u8 xE3;
    int xE4; ///< related to model scale
    int xE8; ///< game type
    u8 xEC;
    u8 xED;
    u8 xEE;    ///< roadmap (IrRdMap) progress
    u8 xEF;    ///< left char amt
    u8 xF0;    ///< right char amt
    u8 xF1[3]; ///< left char ids
    u8 xF4[3]; ///< right char ids
    u8 xF7[3]; ///< left costumes
    u8 xFA[3]; ///< right costumes
    u8 xFD[3]; ///< left metal flags
    u8 x100[3]; ///< right metal flags
    u8 pad_103;
    u8 pad_104[0x54];
} lbl_804735E8;

static HSD_Archive* lbl_804D65F4;

extern int lbl_804D6608;
extern s32 lbl_803B7C40[];
extern s32 lbl_803B7C28[];

extern DynamicModelDesc** lbl_804D662C;
extern HSD_Archive* lbl_804D6628;
extern u8 lbl_803D9828[];

typedef struct { s32 v[6]; } ClassicProcArray;

static struct {
    u8 pad[0x6A8];
    Vec3 x630[4];
    Vec3 x650[4];
    Vec3 x6A8[1];
}* lbl_804D6604;

/// Classic mode stage data table entry (size 0x10)
/// Table has 65 entries: 13 stages × 5 difficulty levels
typedef struct ClassicStageEntry {
    /* 0x00 */ u8 stage_kind;
    /* 0x01 */ u8 pad_1;
    /* 0x02 */ u16 scale0_pct; ///< Divided by 100 to get ratio
    /* 0x04 */ u16 scale1_pct; ///< Divided by 100 to get ratio
    /* 0x06 */ u8 pad_6[0xA];
} ClassicStageEntry;
STATIC_ASSERT(sizeof(ClassicStageEntry) == 0x10);

extern ClassicStageEntry lbl_803D9910[65];

/// #fn_8018325C

/// #fn_80184138

void fn_801849E0(HSD_GObj* gobj)
{
    fn_8018325C(gobj, 0);
}

void fn_80184A04(HSD_GObj* gobj)
{
    fn_8018325C(gobj, 1);
}

void fn_80184A28(HSD_GObj* gobj)
{
    fn_8018325C(gobj, 2);
}

void fn_80184A4C(HSD_GObj* gobj)
{
    fn_80184138(gobj, 0);
}

void fn_80184A70(HSD_GObj* gobj)
{
    fn_80184138(gobj, 1);
}

void fn_80184A94(HSD_GObj* gobj)
{
    fn_80184138(gobj, 2);
}

/// #fn_80184AB8

void fn_8018504C(void)
{
    PAD_STACK(16);
    if ((u16) lbl_804735A8.x3A < 0x31U) {
        lbl_804735A8.x3A = (u16) (lbl_804735A8.x3A + 1);
    } else {
        lbl_804735A8.x3A = 0;
    }
    if ((u16) lbl_804735A8.x3C < 0x31U) {
        lbl_804735A8.x3C = (u16) (lbl_804735A8.x3C + 1);
    }
    HSD_JObjReqAnimAll(lbl_804735A8.x4[5],
        (f32) (lbl_804735A8.x3C + ((lbl_804735E8.xEE * 0x32) - 0x32)));
    HSD_JObjAnimAll(lbl_804735A8.x4[5]);
    HSD_JObjReqAnimAll(lbl_804735A8.x4[4],
        (f32) (lbl_804735A8.x3A + ((lbl_804735E8.xEE * 0x32) - 0x32)));
    HSD_JObjAnimAll(lbl_804735A8.x4[4]);
    if (((u16) lbl_804735A8.x38 == 0x2D) &&
        ((s32) lbl_804735E8.xE4 == 3))
    {
        switch ((s32) lbl_804735E8.xE8) {
        case 1:
            lbAudioAx_800237A8(0x7C864, 0x7F, 0x40);
            return;
        case 2:
            lbAudioAx_800237A8(0x9C49, 0x7F, 0x40);
            return;
        case 3:
            lbAudioAx_800237A8(0x9C47, 0x7F, 0x40);
            break;
        }
    }
}

static f32 lbl_803D9248[] = {
    0.6f, 0.35f, 0.6f, 0.5f, 0.6f, 0.35f, 0.6f, 0.6f, 0.7f, 0.6f,
    0.5f, 0.6f, 0.6f, 0.6f, 0.5f, 0.5f, 0.6f, 0.5f, 0.6f, 0.6f,
    0.5f, 0.6f, 0.6f, 0.6f, 0.6f, 0.5f, 0.5f, 0.5f,
    0.0f, -6.0f, 0.0f,
    0.0f, -3.5f, 0.0f,
    -1.0f, -3.5f, 0.0f,
    0.0f, -3.5f, 0.0f,
    0.0f, -1.0f, 0.0f,
    0.0f, -3.0f, 0.0f,
    0.0f, -5.0f, 0.0f,
    0.0f, -3.5f, 0.0f,
    0.0f, -3.5f, 0.0f,
    0.0f, -3.5f, 0.0f,
    0.0f, -3.0f, 0.0f,
    -0.5f, -3.5f, 0.0f,
    -2.0f, -6.0f, 0.0f,
    0.0f, -2.5f, 0.0f,
    0.0f, -2.5f, 0.0f,
    -1.0f, -1.0f, 0.0f,
    0.0f, -5.0f, 0.0f,
    0.0f, -3.0f, 0.0f,
    -1.0f, -6.0f, 0.0f,
    -1.0f, -2.5f, 0.0f,
    -1.0f, -3.5f, 0.0f,
    0.0f, -3.5f, 0.0f,
    0.0f, -4.0f, 0.0f,
    -1.0f, -3.5f, 0.0f,
    0.0f, -1.5f, 0.0f,
    0.0f, -4.5f, 0.0f,
    0.0f, -3.5f, 0.0f,
    0.0f, -3.5f, 0.0f,
    3.0f, 4.0f, -5.0f,
};

typedef struct ClassicCharData {
    f32 scale[28];
    Vec3 offset[28];
    Vec3 samus_extra;
} ClassicCharData;

s32 fn_801851C0(void)
{
    volatile u8 pad_stack[8];
    Vec3 pos;
    s32 result;
    s32 i;
    (void) pad_stack;

    i = 0;
    while (i < (s32) lbl_804735E8.xE0) {
        ClassicCharData* data = (ClassicCharData*) lbl_803D9248;
        result = i + 1;
        Player_SetPlayerCharacter(result,
            (CharacterKind) lbl_804735E8.xF4[0]);
        Player_SetPlayerId(result, 0);
        Player_SetSlottype(result, Gm_PKind_Demo);
        Player_SetFacingDirection(result, 0.0f);
        Player_SetCostumeId(result, i);
        pos = data->offset[lbl_804735E8.xF4[0]];
        Player_80032768(result, &pos);
        if ((u8) lbl_804735E8.xF4[0] == 0xE) {
            pos.x += data->samus_extra.x;
            pos.y += data->samus_extra.y;
            pos.z += data->samus_extra.z;
            Player_80032828(result, 1, &pos);
        }
        Player_SetModelScale(result,
            data->scale[lbl_804735E8.xF4[0]]);
        Player_SetFlagsBit5(result, lbl_804735E8.x100[0]);
        Player_80037054(result, 6);
        i++;
    }
    return result;
}

void fn_801852FC(HSD_GObj* gobj)
{
    int i;
    int j;

    PAD_STACK(0x18);

    if (HSD_CObjSetCurrent(GET_COBJ(gobj))) {
        for (i = 0; i < lbl_804735E8.xE0; i++) {
            for (j = 0; j < lbl_804735E8.xE0 + 1; j++) {
                if (j == 0 || i + 1 != j) {
                    Player_800366DC(j, 0);
                } else {
                    Player_800366DC(j, 1);
                }
            }
            Camera_800313E0(gobj, 1);
            HSD_StateInvalidate(-1);
            HSD_ImageDescCopyFromEFB(&lbl_804735E8.x40[i], 0x82, 0, 0, 0);
            HSD_ImageDescCopyFromEFB(&lbl_804735E8.x88[i], 0x82, 0, 1, 1);
        }
        HSD_CObjEndCurrent();
    }
    lbl_804735E8.xE1 = 1;
}

void fn_80185408(int x, float arg8, float arg9, float argA, float argB)
{
    u8 _[0x30];
    Mtx sp1C;
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, 0, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_NONE,
                  GX_AF_NONE);
    GXSetNumTexGens(0);
    GXSetZMode(1, GX_LEQUAL, 1);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL,
                  GX_COLOR_NULL);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetCullMode(GX_CULL_NONE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);
    GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetColorUpdate(0);
    GXClearVtxDesc();
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_TEX_ST, GX_RGBA6, 0);
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXLoadPosMtxImm(HSD_identityMtx, 0);
    GXSetCurrentMtx(0);
    MTXOrtho(sp1C, 0.0F, 480.0F, 0.0F, 640.0F, 0.0F, 5000.0F);
    GXSetProjection(sp1C, GX_ORTHOGRAPHIC);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXWGFifo.f32 = argA;
    GXWGFifo.f32 = arg8;
    GXWGFifo.f32 = -4932.0F;
    GXWGFifo.f32 = argB;
    GXWGFifo.f32 = arg8;
    GXWGFifo.f32 = -4932.0F;
    GXWGFifo.f32 = argB;
    GXWGFifo.f32 = arg9;
    GXWGFifo.f32 = -4932.0F;
    GXWGFifo.f32 = argA;
    GXWGFifo.f32 = arg9;
    GXWGFifo.f32 = -4932.0F;
    GXSetColorUpdate(1);
    HSD_StateInvalidate(-1);
}

extern float MSL_TrigF_80400770[];
extern float MSL_TrigF_80400774[];
double fn_801855BC(double arg8)
{
    f64 temp_f2;
    f64 temp_f2_2;
    f64 temp_f2_3;
    f64 temp_f2_4;

    if (arg8 > 0.0) {
        temp_f2_2 = __frsqrte(arg8);
        temp_f2_3 =
            0.5 * temp_f2_2 * -(((f64) arg8 * (temp_f2_2 * temp_f2_2)) - 3.0);
        temp_f2_4 =
            0.5 * temp_f2_3 * -(((f64) arg8 * (temp_f2_3 * temp_f2_3)) - 3.0);
        temp_f2 =
            0.5 * temp_f2_4 * -(((f64) arg8 * (temp_f2_4 * temp_f2_4)) - 3.0);
        return arg8 *
               (0.5 * temp_f2 * -(((f64) arg8 * (temp_f2 * temp_f2)) - 3.0));
    }
    if (0.0 == arg8) {
        return 0.0;
    }
    if (arg8) {
        return MSL_TrigF_80400770[0];
    }
    return MSL_TrigF_80400774[0];
}

void fn_8018564C(HSD_GObj* gobj)
{
    fn_80185408(0xFC8000, 0.0F, 480.0F, 200.0F, 640.0F);
    HSD_SObjLib_803A54EC(gobj, 7);
}

void fn_8018569C(HSD_GObj* gobj)
{
    int i;
    PAD_STACK(8);
    if (HSD_CObjSetCurrent(GET_COBJ(gobj))) {
        for (i = 0; i < lbl_804735E8.xE0 + 1; i++) {
            if (i == 0) {
                Player_800366DC(i, 1);
            } else {
                Player_800366DC(i, 0);
            }
        }
        Camera_800313E0(gobj, 1);
        gobj->gxlink_prios = 0x1001;
        HSD_GObj_80390ED0(gobj, 7);
        HSD_CObjEndCurrent();
    }
}

void fn_8018575C(HSD_GObj* gobj)
{
    if (HSD_CObjSetCurrent(GET_COBJ(gobj))) {
        Camera_800313E0(gobj, 1);
        gobj->gxlink_prios = 0x1001;
        HSD_GObj_80390ED0(gobj, 7);
        HSD_CObjEndCurrent();
    }
}

/// #fn_801857C4

void fn_801859C8(HSD_GObj* gobj)
{
    HSD_SObj* sobj = gobj->hsd_obj;

    while (sobj != NULL) {
        if (sobj->x48 != 0) {
            sobj->x48--;
            if (sobj->x48 == 0) {
                sobj->x40 &= ~1;
            }
        }
        sobj = sobj->next;
    }
}

/// #fn_80185A0C

void fn_80185D64(void)
{
    int i;
    u8* ptr;

    ftDemo_ObjAllocInit();
    Player_InitAllPlayers();

    /// @todo fix pointer arithmetic
    /// is this indicative of an inner struct starting at xE4?
    ptr = (u8*) &lbl_804735E8.xE4;
    for (i = 0; i < lbl_804735E8.xEF; i++) {
        /// how do i access this sanely?
        // its clearly iterating through xF1
        u8 chr = ptr[0x0D];
        if (chr != CHKIND_MAX) {
            Player_80036E20(chr, lbl_804D65F4, 1);
        }
        ptr++;
    }

    ptr = (u8*) &lbl_804735E8.xE4;
    for (i = 0; i < lbl_804735E8.xF0; i++) {
        if (ptr[0x10] == CKIND_GKOOPS) {
            ptr[0x10] = CKIND_KOOPA;
        }
        if (ptr[0x10] != CHKIND_MAX) {
            Player_80036E20(ptr[0x10], lbl_804D65F4, 1);
        }
        ptr++;
    }
}

s32 fn_80185E34(void)
{
    ClassicProcArray local;
    u8* base;
    s32* sp;
    int i;
    int player_slot;

    i = 0;
    base = (u8*) &lbl_804735E8.xE4;
    player_slot = 0;
    sp = (s32*) &local;
    local = *(ClassicProcArray*) lbl_803B7C28;
    sp += i;

    while (i < (s32) lbl_804735E8.xEF) {
        if ((u8) base[0xD] != 0x21) {
            Player_80036CF0(player_slot);
            Player_SetPlayerCharacter(player_slot,
                                      (CharacterKind) base[0xD]);
            Player_SetCostumeId(player_slot, (s32) base[0x13]);
            Player_SetPlayerId(player_slot, 0);
            Player_SetSlottype(player_slot, Gm_PKind_Demo);
            Player_SetFacingDirection(player_slot, 0.0f);
            Player_SetModelScale(player_slot, 1.0f);
            Player_SetFlagsBit5(player_slot, base[0x19]);
            Player_80036F34(player_slot, 5);
            HSD_GObj_SetupProc(
                Player_GetEntity(player_slot),
                (HSD_GObjEvent) *sp, 0x16);
            player_slot++;
        }
        base++;
        sp++;
        i++;
    }
    return player_slot;
}

void fn_80185F5C(s32 arg0)
{
    ClassicProcArray local;
    u8* base;
    s32* sp;
    int i;
    int player_slot;

    i = 0;
    sp = (s32*) &local;
    player_slot = arg0;
    base = (u8*) &lbl_804735E8.xE4;
    sp += i;
    local = *(ClassicProcArray*) lbl_803B7C40;

    while (i < (s32) lbl_804735E8.xF0) {
        if ((u8) base[0xD] != 0x21) {
            Player_80036CF0(player_slot);
            Player_SetPlayerCharacter(player_slot,
                                      (CharacterKind) base[0x10]);
            Player_SetCostumeId(player_slot, (s32) base[0x16]);
            Player_SetPlayerId(player_slot, 0);
            Player_SetSlottype(player_slot, Gm_PKind_Demo);
            Player_SetFacingDirection(player_slot, 0.0f);
            Player_SetModelScale(player_slot, 1.0f);
            Player_SetFlagsBit5(player_slot, base[0x1C]);
            Player_80036F34(player_slot, 6);
            HSD_GObj_SetupProc(
                Player_GetEntity(player_slot),
                (HSD_GObjEvent) sp[3], 0x16);
            player_slot++;
        }
        base++;
        sp++;
        i++;
    }
}

void fn_80186080(void)
{
    s32 temp_r31;

    temp_r31 = HSD_SisLib_803A611C(0, NULL, 9, 0x14, 0, 0xE, 0, 0x12);
    HSD_SisLib_803A62A0(0, "SdIntro.dat", "SIS_IntroData");
    lbl_804735A8.x4[6] = (HSD_JObj*) HSD_SisLib_803A5ACC(
        0, temp_r31, 0.0f, 0.0f, 0.0f, 640.0f, 480.0f);
    if (lbl_804735E8.xE8 == 1) {
        if (lbLang_IsSavedLanguageUS()) {
            HSD_SisLib_803A6368((HSD_Text*) lbl_804735A8.x4[6], 5);
            return;
        }
        HSD_SisLib_803A6368((HSD_Text*) lbl_804735A8.x4[6], 2);
    } else if (lbl_804735E8.xE8 == 3) {
        if (lbLang_IsSavedLanguageUS()) {
            HSD_SisLib_803A6368((HSD_Text*) lbl_804735A8.x4[6], 6);
            return;
        }
        HSD_SisLib_803A6368((HSD_Text*) lbl_804735A8.x4[6], 3);
    } else if (lbl_804735E8.xE8 == 2) {
        if (lbLang_IsSavedLanguageUS()) {
            HSD_SisLib_803A6368((HSD_Text*) lbl_804735A8.x4[6], 7);
            return;
        }
        HSD_SisLib_803A6368((HSD_Text*) lbl_804735A8.x4[6], 4);
    }
}

/// #fn_801861B8

static SceneDesc* lbl_804D65FC;

void fn_80186400(void)
{
    HSD_GObj* gobj = GObj_Create(0xE, 0xF, 0);
    HSD_JObj* jobj = HSD_JObjLoadJoint(lbl_804D65FC->models[0]->joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0xB, 0);
    HSD_GObj_SetupProc(gobj, fn_80184AB8, 0);
    gm_8016895C(jobj, lbl_804D65FC->models[0], 0);
    HSD_JObjReqAnimAll(jobj, 0.0F);
    HSD_JObjAnimAll(jobj);
    if (lbl_804735E8.xE4 != 3) {
        lb_80011E24(jobj, &lbl_804735A8.x4[0], 4, -1);
        lb_80011E24(jobj, &lbl_804735A8.x4[1], 5, -1);
        lb_80011E24(jobj, &lbl_804735A8.x4[2], 0x3A, -1);
        lb_80011E24(jobj, &lbl_804735A8.x4[3], 0x3B, -1);
        HSD_JObjSetTranslateZ(lbl_804735A8.x4[2], 10000.0F);
        HSD_JObjSetTranslateZ(lbl_804735A8.x4[3], 10000.0F);
    }
}

/// #fn_80186634

void gm_80186DFC_OnFrame(void)
{
    if (lbl_804735A8.x0 != 0) {
        lbAudioAx_800236DC();
        gm_801A4B60();
    }
}

static struct enterdata {
    int x0, x4;
} lbl_804D6618;

static struct {
    int x0, x4;
    HSD_JObj* x8;
    HSD_JObj* xC;
} lbl_804736B0;

/// Classic Mode intro scene enter data (0x20 bytes)
typedef struct ClassicModeEnterData {
    /* 0x00 */ int x0;
    /* 0x04 */ int x4;
    /* 0x08 */ int x8;
    /* 0x0C */ int xC;
    /* 0x10 */ union {
        int x10_int;
        struct {
            u8 x10;
            u8 x11;
        };
    };
    /* 0x14 */ int x14;
    /* 0x18 */ int x18;
    /* 0x1C */ int x1C;
} ClassicModeEnterData;

void gm_80186E30_OnEnter(void* arg0_)
{
    ClassicModeEnterData* arg0 = arg0_;

    if (arg0->x10 == 0x1A || arg0->x11 == 0x1A) {
        lbl_804735A8.x0 = 1;
        return;
    }

    lbl_804735A8.x0 = 0;
    lbl_804735A8.x38 = 0;
    lbl_804735A8.x3A = 0;
    lbl_804735A8.x3C = 0;
    *(ClassicModeEnterData*) &lbl_804735E8.xE4 = *arg0;
    fn_80186634(arg0_);
    lbl_804D6608 = -1;
    gm_80167858((int)(s8) lbl_804735E8.xEC, lbl_804735E8.xED, 0xB, 0x2D);
    gm_80168F88();
}

void fn_80186EFC(HSD_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    PAD_STACK(8);
    HSD_JObjReqAnimAll(lbl_804736B0.xC, 0.0F);
    HSD_JObjAnimAll(jobj);
    if (lbl_804736B0.x4 < 0x8C) {
        lbl_804736B0.x4++;
    } else {
        lbl_804736B0.x0 = 1;
    }
}

/// #fn_80186F6C

extern HSD_Archive* lbl_804D6610;

#pragma push
#pragma dont_inline on
HSD_GObjProc* fn_801873F0(void)
{
    ftDemo_ObjAllocInit();
    Player_InitAllPlayers();
    Player_80036E20(lbl_804D6618.x0, lbl_804D6610, 1);
    Player_SetPlayerCharacter(0, lbl_804D6618.x0);
    Player_SetCostumeId(0, lbl_804D6618.x4);
    Player_SetPlayerId(0, 0);
    Player_SetSlottype(0, Gm_PKind_Demo);
    Player_SetFacingDirection(0, 0.0f);
    Player_SetModelScale(0, 1.0f);
    Player_80036F34(0, 6);
    return HSD_GObj_SetupProc(Player_GetEntity(0), fn_80186F6C, 0x16U);
}
#pragma pop

void fn_80187494(HSD_GObj* gobj, int arg1)
{
    int temp_ret = HSD_CObjSetCurrent(gobj->hsd_obj);
    PAD_STACK(4);
    if (temp_ret != 0) {
        Camera_800313E0(gobj, 1);
        gobj->gxlink_prios = 0x801;
        HSD_GObj_80390ED0(gobj, 7);
        HSD_CObjEndCurrent();
    }
}

static SceneDesc* lbl_804D6614;

void fn_801874FC(void)
{
    HSD_JObj* sp8;
    HSD_GObj* gobj;
    HSD_JObj* jobj;

    gobj = GObj_Create(0xE, 0xF, 0);
    jobj = HSD_JObjLoadJoint(lbl_804D6614->models[0]->joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0xB, 0);
    HSD_GObj_SetupProc(gobj, fn_80186EFC, 0);
    gm_8016895C(jobj, lbl_804D6614->models[0], 0);
    HSD_JObjReqAnimAll(jobj, 0.0f);
    HSD_JObjAnimAll(jobj);
    lb_80011E24(jobj, &sp8, 0x3A, -1);
    HSD_JObjSetTranslateZ(sp8, 10000.0F);
    lb_80011E24(jobj, &sp8, 0x3B, -1);
    HSD_JObjSetTranslateZ(sp8, 10000.0F);
    lb_80011E24(jobj, &lbl_804736B0.x8, 5, -1);
    lb_80011E24(jobj, &lbl_804736B0.xC, 6, -1);
}

/// #fn_801874FC

#pragma push
#pragma dont_inline on
void fn_80187714(void)
{
    Camera_80028B9C(6);
    lb_8000FCDC();
    mpColl_80041C78();
    Ground_801C0378(64);
    Stage_802251E8(0, NULL);
    Stage_8022524C();
    Item_80266FA8();
    Item_80266FCC();
    efLib_8005B4B8();
    efAsync_8006737C(0);
}
#pragma pop

extern HSD_Archive* lbl_804D6610;

void gm_8018776C_OnFrame(void)
{
    if (lbl_804736B0.x0 != 0) {
        lbArchive_80016EFC(lbl_804D6610);
        lbAudioAx_800236DC();
        gm_801A4B60();
    }
}

#pragma push
#pragma dont_inline on
void gm_801877A8_OnEnter(void* arg0_)
{
    struct enterdata* arg0 = arg0_;
    HSD_GObj* temp_r30;
    HSD_GObj* temp_r30_2;
    HSD_GObj* temp_r30_3;
    HSD_LObj* lobj;
    HSD_CObj* cobj;
    HSD_Fog* fog;
    PAD_STACK(8);

    lbl_804736B0.x0 = 0;
    lbl_804736B0.x4 = 0;

    lbl_804D6618 = *arg0;
    fn_80187714();
    lbl_804D6610 = lbArchive_80016DBC("IrAls", &lbl_804D6614,
                                      "ScItrAllstar_scene_data", 0);

    temp_r30 = GObj_Create(0x13, 0x14, 0);
    cobj = HSD_CObjLoadDesc(lbl_804D6614->cameras[0].desc);
    HSD_GObjObject_80390A70(temp_r30, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMax(temp_r30, fn_80187494, 8);
    temp_r30->gxlink_prios = 0x801;

    temp_r30_2 = GObj_Create(0xB, 3, 0);
    lobj = lb_80011AC4(lbl_804D6614->lights);
    HSD_GObjObject_80390A70(temp_r30_2, HSD_GObj_804D784A, lobj);
    GObj_SetupGXLink(temp_r30_2, HSD_GObj_LObjCallback, 0, 0);
    fn_801874FC();

    temp_r30_3 = GObj_Create(0xE, 0xF, 0);
    fog = HSD_FogLoadDesc(lbl_804D6614->fogs[0].desc);
    HSD_GObjObject_80390A70(temp_r30_3, HSD_GObj_804D7848, fog);
    GObj_SetupGXLink(temp_r30_3, HSD_GObj_FogCallback, 0xB, 0);
    fn_801873F0();
    lbAudioAx_80023F28(0x2D);
}
#pragma pop

static struct {
    void* x0;
    HSD_CameraAnim** x4;
    u8 pad_8[0x2E];
    u8 x36;
    u8 x37;
    u8 x38;
} lbl_804736C0;

void fn_80187910(HSD_GObj* arg0)
{
    Vec3 sp10;
    HSD_CObj* cobj;
    s32 frame;
    u8 val;
    f32 scale;

    PAD_STACK(8);
    cobj = arg0->hsd_obj;
    if (gm_801A36A0(lbl_804736C0.x38) & 0x100) {
        lbl_804736C0.x37 = (lbl_804736C0.x37 & 0x0F) |
            (((s32) cobj->eyepos->aobj->curr_frame / 300) << 4);
        val = (lbl_804736C0.x37 & 0x0F) |
            ((((lbl_804736C0.x37 >> 4) & 0xF) + 1) << 4);
        lbl_804736C0.x37 = val;
        if ((u32) ((val >> 4) & 0xF) >= 8U) {
            lbl_804736C0.x37 = (lbl_804736C0.x37 & 0x0F);
        }
        frame = ((lbl_804736C0.x37 >> 4) & 0xF) * 0x12C;
        HSD_CObjRemoveAnim(cobj);
        HSD_CObjAddAnim(cobj, *lbl_804736C0.x4);
        HSD_CObjReqAnim(cobj, (f32) frame);
    }
    HSD_CObjAnim(cobj);
    HSD_CObjGetInterest(cobj, &sp10);
    scale = Ground_801C0498();
    sp10.x *= scale;
    sp10.y *= scale;
    sp10.z *= scale;
    HSD_CObjSetInterest(cobj, &sp10);
    HSD_CObjGetEyePosition(cobj, &sp10);
    scale = Ground_801C0498();
    sp10.x *= scale;
    sp10.y *= scale;
    sp10.z *= scale;
    HSD_CObjSetEyePosition(cobj, &sp10);
}

/// #fn_80187AB4

void fn_80187C9C(HSD_GObj* gobj, int arg1)
{
    GXSetZMode(0, GX_NEVER, 0);
    HSD_GObj_JObjCallback(gobj, arg1);
    HSD_StateInvalidate(0x40);
}

/// #fn_80187CF4

/// #gm_80187F48_OnEnter

static HSD_Archive* lbl_804D6620;

void gm_80188364_OnLeave(void* arg0)
{
    HSD_Archive** var = &lbl_804D6620;
    lbArchive_80016EFC(*var);
}

void gm_8018838C_OnFrame(void)
{
    if (((u8) lbl_804736C0.x36 >> 2U) & 1) {
        gm_801A4B60();
    }
}

extern f32 lbl_804DA5E8;

f32 gm_801883C0(void)
{
    void* ptr;
    void* ptr2;
    void* ptr3;

    ptr = *(void**) ((u8*) &lbl_804736C0 + 0x8);
    if (ptr == NULL) {
        goto return_default;
    }

    ptr2 = *(void**) ((u8*) ptr + 0x28);
    goto check_ptr2;

return_default:
    return lbl_804DA5E8;

check_ptr2:
    ptr3 = *(void**) ((u8*) ptr2 + 0x24);
    ptr3 = *(void**) ((u8*) ptr3 + 0x18);
    if (ptr3 != NULL) {
        return *(f32*) ((u8*) ptr3 + 0x4);
    }

    ptr3 = *(void**) ((u8*) ptr2 + 0x28);
    ptr3 = *(void**) ((u8*) ptr3 + 0x18);
    if (ptr3 != NULL) {
        return *(f32*) ((u8*) ptr3 + 0x4);
    }

    return lbl_804DA5E8;
}

bool gm_8018841C(void)
{
    if (gm_801A4310() == MJ_TRAINING) {
        return true;
    }
    return false;
}

static int lbl_80473700[200];

int gm_80188454(int idx)
{
    return lbl_80473700[idx + 2];
}

int fn_8018846C(void)
{
    int result;
    int* ptr = lbl_80473700;
    int* p;

    result = pl_8004134C(0);
    p = ptr + Player_GetPlayerCharacter(0) + 2;
    if (*p < result) {
        *p = result;
    }
    if (result != 0) {
        ptr[67] = result;
        ptr[68] = 1;
    }
    if (ptr[68] != 0) {
        return ptr[67];
    }
    return result;
}

int fn_801884F8(void)
{
    int result;
    int* ptr = lbl_80473700;

    result = pl_80041300(0);
    if (result != 0) {
        ptr[65] = result;
        ptr[66] = 1;
    }
    if (ptr[66] != 0) {
        result = ptr[65];
    }
    return result;
}

void fn_80188550(int arg0)
{
    int current = lbl_80473700[0];

    if (arg0 != current) {
        if (arg0 > current) {
            int skip = current;
            u8* ptr = (u8*) lbl_80473700;
            int remaining = arg0 - current;
            int i = 0;

            do {
                if (i != 0) {
                    if (skip == 0) {
                        if (i != 0) {
                            ptr[0x75] = 1;
                        } else {
                            ptr[0x75] = 0;
                        }
                        gm_8016EDDC(i, (PlayerInitData*) (ptr + 0x74));
                        if (--remaining == 0) {
                            break;
                        }
                    } else {
                        skip--;
                    }
                }
                i++;
                ptr += 0x24;
            } while (i < 4);
        } else {
            int to_remove = current - arg0;
            int j = 3;

            do {
                if (j != 0 && to_remove != 0) {
                    if (current != 3) {
                        fn_8016EF98(to_remove + 1);
                    } else {
                        fn_8016EF98(j);
                    }
                    if (--to_remove == 0) {
                        break;
                    }
                }
                j--;
            } while (j >= 0);
        }
        lbl_80473700[0] = arg0;
    }
}

void fn_80188644(void)
{
    Vec3 sp10;
    u8* ptr;
    int saved_count;
    int i;

    PAD_STACK(8);

    saved_count = lbl_80473700[0];
    lbl_80473700[0] = 1;
    Player_SetFacingDirection(0, 1.0f);
    Player_SetHUDDamage(0, 0);
    Stage_80224E64(0, &sp10);
    Player_800328D4(0, &sp10);
    ifStatus_802F6508(0);

    ptr = (u8*) lbl_80473700;
    i = 0;
    do {
        if (i != 0 && i <= saved_count) {
            fn_8016EF98(i);
            if (i == 1) {
                if (i != 0) {
                    ptr[0x75] = 1;
                } else {
                    ptr[0x75] = 0;
                }
                gm_8016EDDC(i, (PlayerInitData*) (ptr + 0x74));
            }
        }
        i++;
        ptr += 0x24;
    } while (i < 4);

    lbl_80473700[189] = 0;
    lbl_80473700[190] = 0;
    lbl_80473700[191] = 0;
    lbl_80473700[192] = 0;
    lbl_80473700[193] = 0;
    lbl_80473700[194] = 0;
    lbl_80473700[195] = 0;
    lbl_80473700[189] = 2;
}

/// #fn_80188738

/// #fn_80188910

/// #fn_80188B3C

/// #fn_80188D3C

/// #fn_80188EE8

/// #fn_801891F4

s32 fn_80189B88(void)
{
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    u8* sub;
    u8* ptr;
    int i;
    PAD_STACK(8);

    sub = (u8*) lbl_80473700 + 0x114;
    sub[0] = 0;
    sub[1] = 0;
    HSD_GObj_SetupProc(GObj_Create(0xE, 2, 0),
                       (HSD_GObjEvent) fn_801891F4, 0x15);
    gobj = GObj_Create(0xE, 0xF, 0);
    jobj = HSD_JObjLoadJoint((*lbl_804D662C)->joint);
    *(HSD_GObj**) &sub[0xA4] = gobj;
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0xB, 0);
    HSD_GObj_SetupProc(gobj, (HSD_GObjEvent) fn_80188EE8, 0x11);
    gm_8016895C(jobj, *lbl_804D662C, 0);
    HSD_JObjReqAnimAll(jobj, 0.0f);
    HSD_JObjAnimAll(jobj);
    i = 0;
    ptr = sub;
    do {
        *(int*) &ptr[0x144] = 0;
        lb_80011E24(jobj, (HSD_JObj**) &ptr[0xA8], i, -1);
        i++;
        ptr += 4;
    } while (i < 0x27);
    *(int*) &sub[0x19C] = 0x1E;
    *(int*) &sub[0x148] = 0x1E;
    *(int*) &sub[0x1E0] = 0;
    *(int*) &sub[0x1E4] = 0;
    *(int*) &sub[0x1E8] = 0;
    *(int*) &sub[0x1EC] = 0;
    *(int*) &sub[0x1F0] = 0;
    *(int*) &sub[0x1F4] = 0;
    *(int*) &sub[0x1F8] = 0;
    *(int*) &sub[0x1E0] = 2;
    return 0;
}

/// #gm_80189CDC

s32 fn_8018A000(void)
{
    u8* base;
    u8* data;
    HSD_JObj* jobj;
    HSD_Text* text;

    PAD_STACK(24);
    base = (u8*) lbl_80473700;
    data = lbl_803D9828;
    memzero(&base[0x104], 0x10);
    lbl_804D6628 = lbArchive_80016DBC("GmTrain",
        &lbl_804D662C, &data[0xA0], 0);
    fn_80189B88();
    ifAll_802F3404();
    HSD_SisLib_803A611C(0, NULL, 9, 0x14, 0, 0xE, 0, 0x12);
    if (lbLang_IsSavedLanguageUS()) {
        HSD_SisLib_803A62A0(0, (char*) &data[0xBC],
                            (char*) &data[0xC8]);
    } else {
        HSD_SisLib_803A62A0(0, (char*) &data[0xDC],
                            (char*) &data[0xC8]);
    }
    jobj = *(HSD_JObj**) &base[0x1C0];
    if (jobj == NULL) {
        __assert("jobj.h", 0x3E1, "jobj");
    }
    *(HSD_Text**) &base[0x310] = HSD_SisLib_803A5ACC(
        0, 0, (12.0f * (jobj->translate.x + 9.798828f)) + 50.0f,
        150.0f, 0.1f, 167.0f, 16.0f);
    text = *(HSD_Text**) &base[0x310];
    lbLang_IsSettingUS();
    HSD_SisLib_803A6368(text, (s32) *(s16*) &data[2]);
    (*(HSD_Text**) &base[0x310])->default_fitting = 1;
    (*(HSD_Text**) &base[0x310])->x34.x = 0.7f;
    (*(HSD_Text**) &base[0x310])->x34.y = 0.6f;
    (*(HSD_Text**) &base[0x310])->default_alignment = 2;
    return (s32) *(HSD_Text**) &base[0x310];
}

u8 gm_8018A160(u8 difficulty, u8 stage_slot)
{
    return lbl_803D9910[stage_slot + (difficulty * 5)].stage_kind;
}

f32 gm_8018A188(u8 difficulty, u8 stage_slot)
{
    return (f32) lbl_803D9910[stage_slot + (difficulty * 5)].scale0_pct /
           100.0F;
}

f32 gm_8018A1D8(u8 difficulty, u8 stage_slot)
{
    return (f32) lbl_803D9910[stage_slot + (difficulty * 5)].scale1_pct /
           100.0F;
}

u8 gm_8018A228(u8 difficulty, u8 stage_slot, u8 idx)
{
    return lbl_803D9910[stage_slot + (difficulty * 5)].pad_6[idx * 3];
}

u8 gm_8018A25C(u8 difficulty, u8 stage_slot, u8 arg2)
{
    return lbl_803D9910[stage_slot + difficulty * 5].pad_6[arg2 * 3 + 1];
}

u8 gm_8018A290(u8 difficulty, u8 stage_slot, u8 idx)
{
    return lbl_803D9910[stage_slot + (difficulty * 5)].pad_6[2 + idx * 3];
}

f32 gm_8018A2C4(u8 difficulty, u8 stage_slot)
{
    return (f32) lbl_803D9910[stage_slot + (difficulty * 5)].scale0_pct /
           100.0F;
}

f32 gm_8018A314(u8 difficulty, u8 stage_slot)
{
    return (f32) lbl_803D9910[stage_slot + (difficulty * 5)].scale1_pct /
           100.0F;
}

/// #fn_8018A364
