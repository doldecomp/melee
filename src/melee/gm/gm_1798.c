#include "gm_1798.h"

#include <placeholder.h>

#include "forward.h"
#include "gm_1601.h"
#include "gm_unsplit.h"
#include "gmresult.h"
#include "gmresultplayer.h"
#include "gmresultplayer.static.h"
#include "types.h"
#include <melee/cm/camera.h>
#include <melee/ef/efasync.h>
#include <melee/ef/eflib.h>
#include <melee/ft/ftdemo.h>
#include <melee/gr/ground.h>
#include <melee/gr/stage.h>
#include <melee/it/item.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lb_00F9.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbbgflash.h>
#include <melee/lb/lbspdisplay.h>
#include <melee/mp/mpcoll.h>
#include <melee/pl/player.h>
#include <melee/sc/types.h>
#include <sysdolphin/baselib/aobj.h>
#include <sysdolphin/baselib/cobj.h>
#include <sysdolphin/baselib/controller.h>
#include <sysdolphin/baselib/displayfunc.h>
#include <sysdolphin/baselib/dobj.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/mobj.h>
#include <sysdolphin/baselib/random.h>
#include <sysdolphin/baselib/tobj.h>
#include <sysdolphin/baselib/wobj.h>

extern ResultsData lbl_8046DBE8;

ResultsDisplayData lbl_8046E1B0;
HSD_GObj* lbl_8046E38C[4];
HSD_JObj* lbl_8046E39C[4];
lbl_8046E3AC_t lbl_8046E3AC;

static U32Pair lbl_804D3FD0 ATTRIBUTE_ALIGN(8) = { 0x00500050, 0x00460034 };
static U32Pair lbl_804D3FD8 = { 0x006E0072, 0x0064004A };
static U32Pair lbl_804D3FE0 = { 0x00340034, 0x00340034 };
static U32Pair lbl_804D3FE8 = { 0x004A004A, 0x004A004A };
static U32Pair lbl_804D3FF0 = { 0x000C0008, 0x00060000 };
static U32Pair lbl_804D3FF8 = { 0x000E000E, 0x00060000 };

/// @todo .sdata2 order hack
#ifdef MUST_MATCH
static void sdata2_order(void)
{
    (void) 0.0f;
    (void) 1.0f;
    (void) 100.0f;
    (void) 10.0f;
    (void) S32_TO_F32;
    (void) -300.0f;
}
#endif

void fn_80179854(void)
{
    ResultsDisplayLayout* disp = (ResultsDisplayLayout*) &lbl_8046E1B0;
    GXColor color1 = { 0, 0, 0, 0 };
    GXColor color2 = { 0, 0, 0, 0x3C };
    MatchEnd* match_end = &disp->state.match_end;
    HSD_GObj** gobjs = disp->gobjs;
    int i;
    int lookup;
    PAD_STACK(4);

    lbBgFlash_800206D4(&color1, &color2, 0x1E);

    for (i = 0; i < 4; i++) {
        if (match_end->is_teams == 0) {
            lookup = match_end->player_standings[i].is_big_loser;
        } else {
            lookup =
                match_end->team_standings[match_end->player_standings[i].team]
                    .is_big_loser;
        }

        if (match_end->player_standings[i].slot_type != 3 && lookup != 0) {
            HSD_JObjSetTranslateX(GET_JOBJ(gobjs[i]), -300.0f);
            disp->state.x0_6 = 1;
        }
    }
}

extern s32 ftLib_800876B4(HSD_GObj*);

static inline int get_big_loser(int slot, MatchEnd* match_end)
{
    return match_end->player_standings[slot].is_big_loser;
}

static inline HSD_ImageDesc* fn_80179990_img_at(HSD_ImageDesc* imgs, int slot)
{
    return &imgs[slot];
}

static inline void fn_80179990_set_erase_color(MatchEnd* match_end, int slot)
{
    GXColor color;

    color = gm_80160968(
        gm_80160854((u8) slot, match_end->player_standings[slot].team,
                    (u8) (match_end->is_teams == 1),
                    match_end->player_standings[slot].slot_type));
    HSD_SetEraseColor(color.r, color.g, color.b, color.a);
}

static inline void fn_80179990_copy_efb(HSD_ImageDesc* imgs, int slot,
                                        const u16* w, const u16* h)
{
    HSD_ImageDescCopyFromEFB(&imgs[slot], 0x140 - ((s32) *w / 4) * 2,
                             0xF4 - ((s32) *h / 2) * 2, 0, 0);
}

static inline void fn_80179990_copy_efb_at(HSD_ImageDesc* imgs, int slot,
                                           const u16* w, const u16* h,
                                           const u16* x, const u16* y)
{
    HSD_ImageDescCopyFromEFB(&imgs[slot], *x + (0x140 - ((s32) *w / 4) * 2),
                             *y + (0xF4 - ((s32) *h / 2) * 2), 0, 0);
}

void fn_80179990(HSD_GObj* arg0, int arg1, int arg2)
{
    ResultsDisplayLayout* disp = (ResultsDisplayLayout*) &lbl_8046E1B0;
    MatchEnd* match_end = &disp->state.match_end;
    HSD_ImageDesc* image_desc1;
    HSD_CObj* cobj;
    HSD_JObj* child_jobj;
    int lookup;
    PAD_STACK(0x10);

    fn_801795D4();
    fn_801796F0(arg2);

    cobj = (HSD_CObj*) arg0->hsd_obj;

    if (match_end->is_teams == 0) {
        lookup = get_big_loser(arg2, match_end);
    } else {
        lookup =
            match_end->team_standings[match_end->player_standings[arg2].team]
                .is_big_loser;
    }

    if (lookup != 0) {
        HSD_JObj* root = (HSD_JObj*) disp->gobjs[arg2]->hsd_obj;
        child_jobj = root == NULL ? NULL : root->child;
    }

    if (HSD_CObjSetCurrent(cobj)) {
        if (lookup != 0) {
            fn_80179990_set_erase_color(match_end, arg2);
            HSD_CObjEraseScreen(cobj, 1, 0, 0);
            Camera_800313E0(arg0, 0);

            fn_80179990_copy_efb_at(
                disp->player_img2, arg2, disp->state.dim_w1 + lookup,
                disp->state.dim_h1 + lookup, disp->state.scissor_x + lookup,
                disp->state.scissor_y + lookup);

            if (!disp->state.x0_4) {
                fn_80179990_copy_efb(disp->player_img1, arg2,
                                     disp->state.dim_w1 + lookup,
                                     disp->state.dim_h1 + lookup);
            }

            HSD_CObjEraseScreen(cobj, 1, 1, 1);
            HSD_ImageDescCopyFromEFB(&lbl_8046E1B0.shared_img, 0x10E, 0x7C, 1,
                                     0);
            HSD_CObjEndCurrent();

            if (!disp->state.x0_4) {
                image_desc1 = disp->player_img1;
                child_jobj->u.dobj->mobj->tobj->imagedesc = &image_desc1[arg2];
            }

            if (disp->state.x0_4) {
                disp->jobjs[arg2]->u.dobj->next->mobj->tobj->imagedesc =
                    fn_80179990_img_at(disp->player_img2, arg2);
            }
        } else {
            if (ftLib_800876B4(Player_GetEntity(arg2)) == 0) {
                if (disp->state.player_flags[arg2] == 0 && disp->state.x0_6) {
                    fn_80179990_set_erase_color(match_end, arg2);
                    HSD_CObjEraseScreen(cobj, 1, 0, 0);
                    Camera_800313E0(arg0, 0);

                    fn_80179990_copy_efb_at(disp->player_img2, arg2,
                                            disp->state.dim_w1 + lookup,
                                            disp->state.dim_h1 + lookup,
                                            disp->state.scissor_x + lookup,
                                            disp->state.scissor_y + lookup);

                    HSD_CObjEraseScreen(cobj, 1, 1, 1);
                    HSD_ImageDescCopyFromEFB(&lbl_8046E1B0.shared_img, 0x10E,
                                             0x7C, 1, 0);
                    HSD_CObjEndCurrent();

                    disp->state.player_flags[arg2] = 1;
                    disp->jobjs[arg2]->u.dobj->next->mobj->tobj->imagedesc =
                        fn_80179990_img_at(disp->player_img2, arg2);
                }
            }
        }
    }
}

void fn_80179D3C(HSD_GObj* gobj, int arg1)
{
    fn_80179990(gobj, arg1, 0);
}

void fn_80179D60(HSD_GObj* gobj, int arg1)
{
    fn_80179990(gobj, arg1, 1);
}

void fn_80179D84(HSD_GObj* gobj, int arg1)
{
    fn_80179990(gobj, arg1, 2);
}

void fn_80179DA8(HSD_GObj* gobj, int arg1)
{
    fn_80179990(gobj, arg1, 3);
}

void fn_80179DCC(HSD_GObj* gobj, int arg1)
{
    HSD_CObj* cobj = GET_COBJ(gobj);
    if (HSD_CObjSetCurrent(cobj)) {
        Camera_800313E0(gobj, 0);
        gobj->gxlink_prios = 0x80;
        HSD_GObj_80390ED0(gobj, 7U);
        HSD_CObjEndCurrent();
    }
}

void fn_80179E34(HSD_GObj* gobj, int arg1)
{
    HSD_CObj* cobj = GET_COBJ(gobj);
    if (HSD_CObjSetCurrent(cobj)) {
        Camera_800313E0(gobj, 0);
        gobj->gxlink_prios = 0x80;
        HSD_GObj_80390ED0(gobj, 7U);
        HSD_CObjEndCurrent();
    }
}

void fn_80179E9C(HSD_GObj* gobj, int arg1)
{
    HSD_CObj* cobj = GET_COBJ(gobj);
    if (HSD_CObjSetCurrent(cobj)) {
        Camera_800313E0(gobj, 0);
        gobj->gxlink_prios = 0x80;
        HSD_GObj_80390ED0(gobj, 7U);
        HSD_CObjEndCurrent();
    }
}

void fn_80179F04(HSD_GObj* gobj, int arg1)
{
    HSD_CObj* cobj = GET_COBJ(gobj);
    if (HSD_CObjSetCurrent(cobj)) {
        Camera_800313E0(gobj, 0);
        gobj->gxlink_prios = 0x80;
        HSD_GObj_80390ED0(gobj, 7U);
        HSD_CObjEndCurrent();
    }
}

void fn_80179F6C(int idx, HSD_GObj* value)
{
    lbl_8046E38C[idx] = value;
}

void fn_80179F84(HSD_JObj* jobj)
{
    HSD_JObj* child;
    int i;
    HSD_JObj*(*p)[4];

    child = HSD_JObjGetChild(jobj);

    p = &lbl_8046E39C;

    for (i = 0; i < 4; i++) {
        (*p)[i] = child;
        child = HSD_JObjGetNext(child);
    }

    lbl_8046E3AC.x0_4 = 1;
}

void fn_8017A004(void)
{
    ResultsData* data = &lbl_8046DBE8;
    HSD_GObj* gobj = GObj_Create(0xB, 3, 0);
    HSD_LObj* lobj = lb_80011AC4(data->pnlsce->lights);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_LightKind, lobj);
    GObj_SetupGXLink(gobj, HSD_GObj_LObjCallback, 0, 0);
}

void fn_8017A078(s32 arg0)
{
    ResultsDisplayLayout* disp = (ResultsDisplayLayout*) &lbl_8046E1B0;
    ResultsPlayerConfig const* config = &lbl_803B7B68;
    Vec3 eye;
    Vec3 interest;
    ResultsRenderFuncs callbacks;
    HSD_GObj* gobj;
    HSD_CObj* cobj;
    int mode;
    int idx;
    s16 val;

    eye = config->x24;
    interest = config->x30;
    callbacks = config->x3C;

    gobj = GObj_Create(0x13, 0x14, 0);
    cobj = HSD_CObjLoadDesc((HSD_CObjDesc*) &gmResultCameraDesc);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_CameraKind, cobj);

    eye.y = (eye.y * (f32) (arg0 + 1)) + (0.7f * Player_800360D8(arg0));
    interest.y =
        (interest.y * (f32) (arg0 + 1)) + (0.7f * Player_800360D8(arg0));

    mode = fn_801795D4();
    idx = fn_801796F0(arg0);
    val = disp->state.score_tbl[mode].h[idx];
    interest.x -= (f32) val;
    eye.x -= (f32) val;
    interest.y -= 10.0f;
    eye.y -= 10.0f;
    eye.z += (20.0f * (f32) (mode - 2)) + 110.0f;

    if (mode == 0) {
        s32 kind = disp->state.char_kind[arg0];
        if (kind == CKIND_KOOPA && disp->state.variant[arg0] == 1) {
            eye.z += 6.0f;
        } else if (kind == CKIND_MARS && disp->state.variant[arg0] == 1) {
            eye.z += 7.5f;
        } else if (kind == CKIND_CAPTAIN && disp->state.variant[arg0] == 2) {
            eye.z += 6.0f;
        }
    }

    HSD_CObjSetEyePosition(cobj, &eye);
    HSD_CObjSetInterest(cobj, &interest);
    GObj_SetupGXLinkMax(gobj, callbacks.funcs[arg0], 5);
}

HSD_GObj* fn_8017A318(s32 arg0)
{
    static Scissor const scissor_init = { 270, 370, 124, 276 };
    u32* config = (u32*) &lbl_803B7B68;
    CameraKindData* data = (CameraKindData*) gmResultPlayerColors;
    ResultsDisplayLayout* disp = (ResultsDisplayLayout*) &lbl_8046E1B0;
    MatchEnd* match_end = &disp->state.match_end;
    s32 _pad[2];
    Scissor scissor;
    Vec3 eye;
    Vec3 interest;
    ResultsRenderFuncs callbacks;
    int slot;
    HSD_GObj* gobj;
    HSD_CObj* cobj;
    u8 variant;
    s32 kind_data;
    int vi;

    PAD_STACK(0xC);

    fn_801795D4();
    fn_801796F0(arg0);

    scissor = scissor_init;

    eye = ((ResultsPlayerConfig*) config)->x4C;
    interest = ((ResultsPlayerConfig*) config)->x58;
    callbacks = ((ResultsPlayerConfig*) config)->x64;
    if (match_end->is_teams == 0) {
        slot = match_end->player_standings[arg0].is_big_loser;
    } else {
        u8 team_idx = match_end->player_standings[arg0].team;
        slot = match_end->team_standings[team_idx].is_big_loser;
    }

    gobj = GObj_Create(0x13, 0x14, 0);
    cobj = HSD_CObjLoadDesc(&data->cobj_desc);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_CameraKind, cobj);

    {
        s32 n = arg0 + 1;
        eye.y *= (f32) n;
        interest.y *= (f32) n;
    }

    variant = disp->state.variant[arg0];

    vi = ((s32) variant <= 2) ? variant : 3;

    kind_data = disp->state.char_kind[arg0];
    (void) kind_data;
    eye.y += data->kind[kind_data].y_off[vi];

    vi = ((s32) variant <= 2) ? variant : 3;
    interest.y += data->kind[kind_data].y_off[vi];

    vi = ((s32) variant <= 2) ? variant : 3;
    eye.x += data->kind[kind_data].x_off[vi];

    {
        f32 interest_x;
        vi = ((s32) variant <= 2) ? variant : 3;
        interest_x = interest.x + data->kind[kind_data].x_off[vi];

        {
            f32 x_off, y_off;

            interest.x = interest_x;
            x_off = data->slot_off[kind_data][0][slot];
            eye.x += x_off;
            interest.x += x_off;

            eye.y = eye.y + (y_off = data->slot_off[kind_data][1][slot]);
            interest.y += y_off;
        }
    }

    if (slot == 0) {
        eye.z += 320.0f;
    }

    vi = ((s32) variant <= 2) ? variant : 3;
    if ((1.0f - data->kind[kind_data].z_scale[vi]) < 0.0f) {
        vi = ((s32) variant <= 2) ? variant : 3;
        eye.z += 100.0f * (1.0f - data->kind[kind_data].z_scale[vi]);
    } else {
        vi = ((s32) variant <= 2) ? variant : 3;
        eye.z += 300.0f * (1.0f - data->kind[kind_data].z_scale[vi]);
    }

    HSD_CObjSetEyePosition(cobj, &eye);
    HSD_CObjSetInterest(cobj, &interest);
    HSD_CObjSetScissor(cobj, &scissor);
    GObj_SetupGXLinkMax(gobj, callbacks.funcs[arg0], 0);

    if (slot == 0) {
        fn_8017A078(arg0);
    }
}

Fighter_GObj* fn_8017A67C(CharacterKind kind, int arg1, int arg2)
{
    ResultsPlayerConfig const* config = &lbl_803B7B68;
    ResultsDisplayLayout* disp = (ResultsDisplayLayout*) &lbl_8046E1B0;
    MatchEnd* match_end = &disp->state.match_end;
    HSD_GObj* gobj = NULL;
    int slot_type;

    if (match_end->is_teams == 0) {
        slot_type = match_end->player_standings[arg2].is_big_loser;
    } else {
        slot_type =
            match_end->team_standings[match_end->player_standings[arg2].team]
                .is_big_loser;
    }

    if (gm_80160438(kind) != NULL) {
        Vec3 pos;
        Vec3 pos2;
        f32 sp[4];
        PAD_STACK(0xC);
        pos = *(Vec3*) &config->x74;

        if ((u32) (kind - 0x12) <= 1U) {
            if ((int) match_end->player_standings[arg2].ftkind == 7) {
                kind = CKIND_SEAK;
            } else {
                kind = CKIND_ZELDA;
            }
        }

        Player_80036E20(kind, lbArchive_LoadArchive(gm_80160438(kind)), 0);
        Player_SetPlayerCharacter(arg2, kind);
        Player_SetCostumeId(arg2, arg1);
        Player_SetPlayerId(arg2, arg2);
        Player_SetSlottype(arg2, Gm_PKind_Demo);

        if (kind == CKIND_GAMEWATCH) {
            Player_SetFacingDirection(arg2, -1.0f);
        } else {
            Player_SetFacingDirection(arg2, 0.0f);
        }

        {
            int variant;

            if (slot_type == 0) {
                u32 buttons = HSD_PadCopyStatus[(u8) arg2].button;
                if (buttons & 0x200) {
                    variant = 0;
                } else if (buttons & 0x800) {
                    variant = 1;
                } else if (buttons & 0x400) {
                    variant = 2;
                } else {
                    variant = HSD_Randi(3);
                }
            } else {
                variant = 4;
            }

            if (variant != 4) {
                u8 override = disp->state.costume_override[arg2];
                if (override != 0) {
                    variant = override - 1;
                }
            }

            if (slot_type == 0) {
                pos2 = *(Vec3*) &config->x80;
                pos2.y = 100.0f * (f32) (arg2 + 1);
                Player_80032A04(arg2, &pos2);
                Player_SetScale(arg2,
                                1.8f * gmResultCharacterData.scale[kind]);
                Player_80036F34(arg2, variant);
            } else {
                int var_idx;
                f32 scale;
                *(Vec4*) sp = *(Vec4*) &config->x8C;
                if (variant <= 2) {
                    var_idx = variant;
                } else {
                    var_idx = 3;
                }
                scale = gmResultCharacterScaleData[kind].x20[var_idx];
                Player_80036F34(arg2, variant);
                Player_SetScale(
                    arg2,
                    scale * (sp[slot_type] * (20.0f / Player_800360D8(arg2))));
                pos.y = 100.0f * (f32) (arg2 + 1);
                Player_80032A04(arg2, &pos);
            }

            disp->state.variant[arg2] = (u8) variant;
            disp->state.char_kind[arg2] = (s32) kind;
            gobj = Player_GetEntity(arg2);
        }
    }

    return (Fighter_GObj*) gobj;
}

static inline void inline1(HSD_ImageDesc* imgs, int slot, const u16* w,
                           const u16* h)
{
    imgs[slot].image_ptr = NULL;
    lb_800121FC(&imgs[slot], *w, *h, 5, 0);
}

void fn_8017A9B4(int slot)
{
    ResultsDisplayLayout* disp = (ResultsDisplayLayout*) &lbl_8046E1B0;
    MatchEnd* match_end = &disp->state.match_end;
    int lookup;

    if (match_end->is_teams == 0) {
        lookup = match_end->player_standings[slot].is_big_loser;
    } else {
        int idx = match_end->player_standings[slot].team;
        lookup = match_end->team_standings[idx].is_big_loser;
    }

    inline1(disp->player_img1, slot, disp->state.dim_w1 + lookup,
            disp->state.dim_h1 + lookup);
    inline1(disp->player_img2, slot, disp->state.dim_w2 + lookup,
            disp->state.dim_h2 + lookup);
}

void fn_8017AA78(const u8* arg0)
{
    int i;

    memzero(lbl_8046E1B0.pad_000, sizeof(lbl_8046E1B0.pad_000));
    lbBgFlash_800208EC(6);
    Camera_80028B9C(8);
    lb_8000FCDC();
    mpColl_80041C78();
    Ground_801C0378(0x40);
    Stage_802251E8(St_Kind_Dummy, NULL);
    Stage_8022524C();
    Item_80266FA8();
    Item_80266FCC();
    efLib_Init();
    efAsync_LoadSync(0);
    ftDemo_ObjAllocInit();
    Player_InitAllPlayers();
    lbl_8046E1B0.shared_img.image_ptr = NULL;
    lb_800121FC(&lbl_8046E1B0.shared_img, 0x64, 0x98, GX_TF_RGB5A3, 0);
    lbl_8046E3AC.match_end = *fn_80174274();

    lbl_8046E3AC.x0_0 = 1;
    lbl_8046E3AC.x0_4 = 0;
    lbl_8046E3AC.x0_6 = 0;

    *(U32Pair*) lbl_8046E3AC.dim_w1 = lbl_804D3FD0;
    *(U32Pair*) lbl_8046E3AC.dim_h1 = lbl_804D3FD8;
    *(U32Pair*) lbl_8046E3AC.dim_w2 = lbl_804D3FE0;
    *(U32Pair*) lbl_8046E3AC.dim_h2 = lbl_804D3FE8;
    *(U32Pair*) lbl_8046E3AC.scissor_y = lbl_804D3FF0;
    *(U32Pair*) lbl_8046E3AC.scissor_x = lbl_804D3FF8;

    for (i = 0; i < 4; i++) {
        lbl_8046E3AC.player_flags[i] = 0;
        lbl_8046E3AC.costume_override[i] = arg0[i];
        if (lbl_8046E3AC.match_end.outcome == OUTCOME_NO_CONTEST) {
            lbl_8046E3AC.match_end.player_standings[i].is_big_loser = 1;
            lbl_8046E3AC.match_end
                .team_standings[lbl_8046E3AC.match_end.player_standings[i]
                                    .team]
                .is_big_loser = 1;
        }
        lbl_8046E3AC.x6[i] = 0;
        lbl_8046E3AC.score_tbl[i] = ((PackedS16x4*) gmResultScoreTableInit)[i];
        lbl_8046E3AC.x22F4[i] = ((PackedS16x4*) gmResultX22F4Init)[i];
    }
}
