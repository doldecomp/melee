#include "gm_1601.h"

#include "gm_1601.static.h"

#include "gm_unsplit.h"
#include "gmmain_lib.h"
#include "runtime.h"
#include "stddef.h"

#include "baselib/gobjplink.h"
#include "baselib/particle.h"
#include "cm/camera.h"
#include "db/db.h"
#include "ef/efasync.h"
#include "ef/eflib.h"
#include "gr/ground.h"
#include "gr/stage.h"
#include "if/ifstatus.h"
#include "it/item.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "lb/lb_0192.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbtime.h"
#include "mp/mpcoll.h"
#include "pl/player.h"
#include "sc/types.h"
#include "ty/toy.h"

#include <m2c_macros.h>
#include <sysdolphin/baselib/controller.h>
#include <melee/gm/gm_1A45.h>
#include <melee/pl/player.h>

static struct VictoryTheme lbl_803D5480[0x1B] = {
    { 0x0, 0x11 },  { 0x1, 0xD },   { 0x2, 0x10 },  { 0x3, 0xF },
    { 0x4, 0x14 },  { 0x5, 0x16 },  { 0x6, 0x15 },  { 0x7, 0x16 },
    { 0x8, 0x16 },  { 0x9, 0xE },   { 0xA, 0x18 },  { 0xB, 0x17 },
    { 0xC, 0x16 },  { 0xD, 0x18 },  { 0xE, 0x13 },  { 0xF, 0x18 },
    { 0x10, 0x19 }, { 0x11, 0x1D }, { 0x12, 0x15 }, { 0x13, 0x15 },
    { 0x14, 0x10 }, { 0x15, 0x15 }, { 0x16, 0x16 }, { 0x17, 0xE },
    { 0x18, 0x18 }, { 0x19, 0x15 }, { 0x21, -1 },
};

static struct ResultAnimEntry lbl_803D53A8[0x1B] = {
    { 0, "GmRstMCa.dat" },    { 0x15, "GmRstMCl.dat" },
    { 1, "GmRstMDk.dat" },    { 0x16, "GmRstMDr.dat" },
    { 0x14, "GmRstMFc.dat" }, { 2, "GmRstMFx.dat" },
    { 3, "GmRstMGw.dat" },    { 0x19, "GmRstMGn.dat" },
    { 4, "GmRstMKb.dat" },    { 5, "GmRstMKp.dat" },
    { 6, "GmRstMLk.dat" },    { 7, "GmRstMLg.dat" },
    { 9, "GmRstMMs.dat" },    { 8, "GmRstMMr.dat" },
    { 0xA, "GmRstMMt.dat" },  { 0xB, "GmRstMNs.dat" },
    { 0xE, "GmRstMPn.dat" },  { 0xC, "GmRstMPe.dat" },
    { 0xD, "GmRstMPk.dat" },  { 0x18, "GmRstMPc.dat" },
    { 0xF, "GmRstMPr.dat" },  { 0x10, "GmRstMSs.dat" },
    { 0x13, "GmRstMSk.dat" }, { 0x11, "GmRstMYs.dat" },
    { 0x12, "GmRstMZd.dat" }, { 0x17, "GmRstMFe.dat" },
    { 0x21, NULL },
};

#pragma dont_inline on
u8 gm_801601C4(s8 arg0)
{
    f32 temp_f1;

    temp_f1 = ((arg0 + 0x64) / 200.0f);
    if (temp_f1 * 100.f == 50.0f) {
        return 0x7F;
    }
    if (temp_f1 > 50.0f) {
        return 127.0f * ((100.0f - temp_f1) / 50.0f);
    }
    return 0x7F;
}

u8 gm_80160244(s8 arg0)
{
    f32 temp_f2;

    temp_f2 = ((arg0 + 0x64) / 200.0f) * 100.0f;
    if (temp_f2 == 50.0f) {
        return 0x7F;
    }
    if (temp_f2 > 50.0f) {
        return 0x7F;
    }
    return (127.0f * (temp_f2 / 50.0f));
}
#pragma dont_inline reset

void gm_801602C0(s8 arg0)
{
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f3;
    s32 var_r0;
    s32 var_r0_2;
    PAD_STACK(8); // maybe an inlined function somewhere

    temp_f3 = (arg0 + 0x64) / 200.0f;
    temp_f1 = temp_f3 * 100.0f;

    if (temp_f1 == 50.0f) {
        var_r0 = 0x7F;
    } else if (temp_f1 > 50.0f) {
        var_r0 = 0x7F;
    } else {
        var_r0 = (127.0f * (temp_f1 / 50.0f));
    }

    temp_f1_2 = temp_f3 * 100.0f;
    if (temp_f1_2 == 50.0f) {
        var_r0_2 = 0x7F;
    } else if (temp_f1_2 > 50.0f) {
        var_r0_2 = (127.0f * ((100.0f - temp_f1_2) / 50.0f));
    } else {
        var_r0_2 = 0x7F;
    }

    lbAudioAx_80024614(var_r0_2);
    lbAudioAx_800245F4(var_r0);
}

void gm_801603B0(void)
{
    u8 temp_r31;
    s8 temp_r3;

    temp_r3 = gmMainLib_8015ED74();
    temp_r31 = gm_80160244(temp_r3);

    lbAudioAx_80024614(gm_801601C4(temp_r3));
    lbAudioAx_800245F4(temp_r31);
}

u32 fn_80160400(s32 cid)
{
    struct VictoryTheme* theme = lbl_803D5480;
    u8 id;

    while (true) {
        if (theme->character_id == cid) {
            return theme->theme_id;
        }

        id = theme[1].character_id;
        theme++;

        if ((s32) id == 0x21) {
            return -1;
        }
    }
}

char* gm_80160438(s32 cid)
{
    struct ResultAnimEntry* entry = lbl_803D53A8;
    s32 id;

    while (true) {
        id = entry->character_id;
        if (id == cid || id == 0x21) {
            return entry->path;
        }
        id = entry[1].character_id;
        entry++;
        if (id == 0x21) {
            return NULL;
        }
    }
}

bool gm_80160474(enum CharacterKind c_kind, enum MajorSceneKind scene)
{
    switch (scene) {
    case MJ_CLASSIC_GOVER:
    case MJ_CLASSIC:
        return lbl_803B75F8._380[c_kind];
    case MJ_ADVENTURE_GOVER:
    case MJ_ADVENTURE:
        return lbl_803B75F8._3C4[c_kind];
    default:
        return lbl_803B75F8._408[c_kind];
    }
}

char* gm_801604DC(enum CharacterKind c_kind, enum MajorSceneKind scene)
{
    s16 var_r3;

    switch (scene) {
    case MJ_CLASSIC_GOVER:
    case MJ_CLASSIC:
        var_r3 = lbl_803B75F8._380[c_kind];
        break;
    case MJ_ADVENTURE_GOVER:
    case MJ_ADVENTURE:
        var_r3 = lbl_803B75F8._3C4[c_kind];
        break;
    default:
        var_r3 = lbl_803B75F8._408[c_kind];
        break;
    }
    return un_8030813C(var_r3, scene) + 4;
}

char* gm_80160564(enum CharacterKind c_kind, enum MajorSceneKind scene)
{
    s16 var_r3;

    switch (scene) {
    case MJ_CLASSIC_GOVER:
    case MJ_CLASSIC:
        var_r3 = lbl_803B75F8._380[c_kind];
        break;
    case MJ_ADVENTURE_GOVER:
    case MJ_ADVENTURE:
        var_r3 = lbl_803B75F8._3C4[c_kind];
        break;
    default:
        var_r3 = lbl_803B75F8._408[c_kind];
        break;
    }
    return un_8030813C(var_r3, scene) + 0x24;
}

u8 fn_801605EC(s32 arg0)
{
    struct lbl_803B78C8_0x6* entry = lbl_803B78C8;
    s32 i;

    for (i = 0; i < NUM_UNLOCKABLE_CHARACTERS; entry++, i++) {
        if (arg0 == entry->x1) {
            return lbl_803B78C8[i].x0;
        }
    }
    return NUM_UNLOCKABLE_CHARACTERS;
}

s8 gm_80160638(s32 arg0)
{
    s32 temp_r4 = gm_80164024(arg0);
    struct lbl_803B78C8_0x6* entry = lbl_803B78C8;
    u32 i;

    for (i = 0; i < NUM_UNLOCKABLE_CHARACTERS; entry++, i++) {
        if (temp_r4 == entry->x1) {
            return lbl_803B78C8[i].x0;
        }
    }
    return NUM_UNLOCKABLE_CHARACTERS;
}

/// #fn_801606A8

/// #fn_80160710

/// #gm_8016075C

/// #fn_801607A8

/// #fn_801607F4

u8 fn_80160840(u8 arg0)
{
    if (arg0 >= 4) {
        return 4;
    }
    return arg0;
}

u32 gm_80160854(u8 slot, u8 team, u8 is_teams, u8 slot_type)
{
    u8 color_idx;

    if (is_teams != 0) {
        switch (team) { /* switch 1; irregular */
        case 0:         /* switch 1 */
            if (slot_type == Gm_PKind_Human) {
                color_idx = 0;
            } else {
                color_idx = 5;
            }
            return color_idx;
        case 1: /* switch 1 */
            if (slot_type == Gm_PKind_Human) {
                color_idx = 1;
            } else {
                color_idx = 6;
            }
            return color_idx;
        case 2: /* switch 1 */
            if (slot_type == Gm_PKind_Human) {
                color_idx = 3;
            } else {
                color_idx = 8;
            }
            return color_idx;
        case 3: /* switch 1 */
            if (slot_type == Gm_PKind_Human) {
                color_idx = 2;
            } else {
                color_idx = 7;
            }
            return color_idx;
        case 4: /* switch 1 */
            return 4U;
        }
    } else {
        if (slot_type != Gm_PKind_Human) {
            return 4U;
        }
        switch (slot) { /* irregular */
        case 0:
            return 0U;
        case 1:
            return 1U;
        case 2:
            return 2U;
        case 3:
            return 3U;
        }
    }
    return 0;
}

GXColor gm_80160968(u8 arg0)
{
    return lbl_803B7864[arg0];
}

/// #gm_80160980

/// #fn_801609E0

/// #gm_80160A60

/// #gm_80160B40

/// #gm_80160C90

/// #fn_80160DE8

/// #fn_80160F58

/// #fn_80161004

/// #fn_80161154

/// #fn_80161C90

/// #fn_80162068

/// #fn_80162170

/// #gm_801623A4

/// #gm_801623D8

/// #gm_801623FC

/// #gm_8016247C

/// #gm_80162574

/// #gm_8016260C

/// #gm_8016279C

/// #gm_80162800

/// #gm_801628C4

/// #gm_80162968

/// #gm_801629B4

/// #gm_80162A00

/// #gm_80162A4C

/// #gm_80162A98

/// #gm_80162B4C

/// #gm_80162B98

/// #gm_80162BD8

/// #fn_80162BFC

/// #gm_80162C48

/// #fn_80162CCC

/// #gm_80162D1C

/// #gm_80162D6C

/// #gm_80162DD4

/// #fn_80162DF8

/// #gm_80162E44

/// #gm_80162EC8

/// #gm_80162F18

/// #gm_80162F68

/// #gm_80162FD0

/// #fn_80162FF4

/// #gm_80163040

/// #fn_801630C4

/// #gm_80163114

/// #gm_80163164

/// #gm_801631CC

/// #gm_801631F0

/// #gm_80163274

/// #gm_80163298

/// #gm_8016332C

/// #gm_80163374

/// #gm_801634D4

/// #gm_8016365C

/// #gm_80163690

/// #gm_801636D8

/// #gm_80163838

/// #gm_801639C0

/// #gm_801639F4

/// #gm_80163A3C

/// #gm_80163B9C

bool fn_80163D24(void)
{
    int i;
    for (i = 0; i < 0x19; i++) {
        if (gmMainLib_8015D710(i)) {
            return true;
        }
    }
    return false;
}

bool fn_80163D74(void)
{
    int i;
    for (i = 0; i < 0x19; i++) {
        if (gmMainLib_8015D764(i)) {
            return true;
        }
    }
    return false;
}

u16 gm_80163DC4(u8 i)
{
    return *gmMainLib_8015D74C(i);
}

/// Get total number of KOs
int gm_80163DE8(void)
{
    int i;
    int total = 0;
    for (i = 0; i < 0x19; i++) {
        total += *gmMainLib_8015D74C(i);
    }
    return total;
}

u16 gm_80163E3C(u8 i)
{
    return *gmMainLib_8015D7A4(i);
}

int gm_80163E60(void)
{
    int i;
    int total = 0;
    for (i = 0; i < 0x19; i++) {
        total += *gmMainLib_8015D7A4(i);
    }
    return total;
}

int gm_80163EB4(u8 i)
{
    return *gmMainLib_8015D7BC(i);
}

int gm_80163ED8(void)
{
    int i;
    int total = 0;
    for (i = 0; i < 0x19; i++) {
        total += *gmMainLib_8015D7BC(i);
    }
    return total;
}

int gm_80163F2C(u8 i)
{
    return *gmMainLib_8015D7D4(i);
}

int gm_80163F50(void)
{
    int i;
    int total = 0;
    for (i = 0; i < 0x19; i++) {
        total += *gmMainLib_8015D7D4(i);
    }
    return total;
}

int fn_80163FA4(u8 arg0)
{
    int i;
    int count = 0;
    for (i = 0; i < arg0; i++) {
        if (gmMainLib_8015CEFC(i)) {
            count++;
        }
    }
    return count;
}

u8 gm_8016400C(u8 arg0)
{
    return lbl_803B7888[arg0];
}

u8 gm_80164024(u8 arg0)
{
    return lbl_803B78A4[arg0];
}

bool gm_8016403C(u8 item)
{
    u64 item_mask = gmMainLib_8015CC58()->item_mask;
    if ((1LL << item) & item_mask) {
        return true;
    }
    return false;
}

void fn_801640B0(u64* item_mask)
{
    int i;
    struct gmm_x1CB0* temp_r30 = gmMainLib_8015CC58();

    for (i = 0; i < 0x20; i++) {
        int shift;
        if ((shift = lbl_803B7844[(u8) i]) != 0x23) {
            if (temp_r30->item_mask & (1LL << i)) {
                *item_mask |= 1LL << shift;
            } else {
                *item_mask &= ~(1LL << shift);
            }
        }
    }
}

float fn_8016419C(u8 arg0)
{
    return lbl_803B7930[arg0 - 1].x;
}

float fn_801641B4(u8 arg0)
{
    return lbl_803B7930[arg0 - 1].y;
}

u16 gm_801641CC(u8 arg0)
{
    return lbl_803B7808[arg0];
}

void gm_801641E4(u8 stage, u8 enable)
{
    if (enable) {
        gmMainLib_8015CC58()->stage_mask |= 1 << stage;
    } else {
        gmMainLib_8015CC58()->stage_mask &= ~(1 << stage);
    }
}

/// #gm_80164250

/// #fn_801642A0

/// #gm_80164330

/// #gm_80164430

/// #gm_80164504

/// Are all stages unlocked?
bool gm_80164600(void)
{
    u16* stage_unlock_mask = (void*) gmMainLib_8015EDA4();
    int i;

    for (i = 0; i < NUM_UNLOCKABLE_STAGES; i++) {
        if (!(*stage_unlock_mask & (1LL << i))) {
            return false;
        }
    }
    return true;
}

/// #gm_8016468C

void gm_801647D0(void)
{
    u16* stage_unlock_mask = gmMainLib_8015EDA4();
    *stage_unlock_mask = 0;
}

/// #gm_801647F8

bool gm_80164840(u8 id)
{
    int i;
    u16* temp_r31;
    u8 var_r0 = 0;

    temp_r31 = gmMainLib_8015ED8C();
    for (i = 0; i < NUM_UNLOCKABLE_CHARACTERS; i++) {
        if (lbl_803B75F8.id[id] == lbl_803B75F8.thing[i].unk1) {
            var_r0 = lbl_803B75F8.thing[i].unk0;
            break;
        }
    }
    if ((var_r0 == 11) || (*temp_r31 & (1LL << var_r0))) {
        return true;
    }
    return false;
}

/// #gm_80164910

/// #gm_80164A0C

/// Are all unlockable characters unlocked?
bool gm_80164ABC(void)
{
    u16* unlockable_character_bitfield = gmMainLib_8015ED8C();
    int i;
    for (i = 0; i < NUM_UNLOCKABLE_CHARACTERS; i++) {
        if (!(*unlockable_character_bitfield & (1LL << i))) {
            /// @remarks Gekko codes which unlock all characters change this to
            ///          return @c true.
            return false;
        }
    }
    return true;
}

/// #fn_80164B48

/// #gm_80164F18

void gm_8016505C(void)
{
    u16* temp_r3 = gmMainLib_8015ED8C();
    *temp_r3 = 0;
}

bool gm_80165084(void)
{
    s32 i;
    bool result = true;

    for (i = 0; i <= 0x1B; i++) {
        if (i != 0x1A && gmMainLib_8015D94C(i) == 0) {
            result = false;
            break;
        }
    }

    return result;
}

void fn_801650E8(void)
{
    Ground_801C5800();
}

void fn_80165108(int slot, int arg1)
{
    if (slot == -1) {
        Camera_8002F73C(0xB, 5);
        return;
    }
    if (((Player_GetPlayerSlotType(slot) == Gm_PKind_Human) ||
         (Player_GetPlayerSlotType(slot) == Gm_PKind_Cpu)) &&
        (Player_GetEntity(slot) != NULL))
    {
        Camera_8002F73C(slot, arg1);
    }
}

void fn_80165190(s32 slot, s32 arg1)
{
    if (((Player_GetPlayerSlotType(slot) == Gm_PKind_Human) ||
         (Player_GetPlayerSlotType(slot) == Gm_PKind_Cpu)) &&
        (Player_GetEntity(slot) != NULL))
    {
        Camera_8002F760(slot, arg1);
    }
}

void fn_801651FC(s32 slot, s32 arg1)
{
    if (((Player_GetPlayerSlotType(slot) == Gm_PKind_Human) ||
         (Player_GetPlayerSlotType(slot) == Gm_PKind_Cpu)) &&
        (Player_GetEntity(slot) != NULL))
    {
        Camera_8002F784(slot, arg1);
    }
}

void gm_80165268(int unused)
{
    Camera_8002FC7C(4, 3);
}

void gm_80165290(int x)
{
    Camera_8002F8F4();
}

void fn_801652B0(s32 arg0, s32 arg1)
{
    Camera_8002F9E4(arg0, arg1);
}

/// #fn_801652D8

/// creates the develop mode stress test
HSD_GObj* gm_80165388(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    HSD_GObj* temp_r3;

    temp_r3 = hsd_80398310(arg0, arg1, arg2, arg3);
    if (temp_r3 != NULL) {
        hsd_80392528((Event) fn_801652D8);
    }
    return temp_r3;
}

/// frees the develop mode stress test
void gm_801653C8(HSD_GObj* gobj)
{
    HSD_GObjPLink_80390228(gobj);
}

f64 fn_801653E8(u8 arg0)
{
    return (0.1f * arg0);
}

u8 fn_80165418(MatchEnd* match_end)
{
    u8 winner = 0;
    s32 i;
    for (i = 0; i < 4; i++) {
        if (match_end->player_standings[i].slot_type != Gm_PKind_NA &&
            match_end->player_standings[i].is_small_loser == 0)
        {
            winner = i;
        }
    }
    return winner;
}

u8 fn_801654A0(MatchEnd* match_end)
{
    u8 winner = 0;
    s32 i;
    for (i = 0; i < 5; i++) {
        if (match_end->team_standings[i].active != 0 &&
            match_end->team_standings[i].is_small_loser == 0)
        {
            winner = i;
        }
    }
    return winner;
}

/// #fn_80165548

/// #fn_801656A8

/// #fn_8016588C

/// #fn_80165AC0

/// #fn_80165D60

/// #fn_80165E7C

/// #fn_80165FA4

/// #fn_801661E0

/// #gm_80166378

#ifdef MWERKS_GEKKO
float fn_80166A8C(register Vec3* src, register Vec3* dst)
{
    register float x = src->x;
    asm { psq_st x, Vec3.x(dst), 1, qr3 }
    return x;
}
#else
float fn_80166A8C(register Vec3* src, register Vec3* dst)
{
    NOT_IMPLEMENTED;
}
#endif

/// #gm_80166A98

u8 fn_80166CBC(struct fn_80166CBC_arg0_t* arg0, ssize_t index)
{
    return arg0[index].x5E;
}

/// #gm_80166CCC

bool gm_80167140(MatchEnd* me)
{
    s32 winners;

    if (me->result != 7) {
        if (me->is_teams == 1) {
            winners = me->n_team_winners;
        } else {
            winners = fn_80167194(me);
        }
        if (winners > 1) {
            return true;
        }
    }

    return false;
}

u8 fn_80167194(MatchEnd* me)
{
    return me->n_winners;
}

void fn_8016719C(s32 slot, s32 subchar)
{
    Vec3 respawn_pos;
    Vec3 offset;
    f32 var_f1;
    lbl_8046B6A0_t* match_info;
    s32 var_r30;
    s32 stage_id;
    u8* temp_r4;
    u8 temp_r3;

    match_info = gm_8016AE44();
    stage_id = gm_8016B004();
    if (Stage_80224DC8(stage_id) != 0) {
        var_r30 = Ground_801C5774();
        Stage_80224E38(&respawn_pos, var_r30);
        offset.z = 0.0f;
        offset.y = 0.0f;
        offset.x = 0.0f;
        if ((stage_id != 0x4C) && (subchar == 0)) {
            Ground_801C38BC(respawn_pos.x, respawn_pos.y);
            Camera_8002F3AC();
        }
    } else {
        var_r30 = fn_80167638(slot, &respawn_pos, &offset);
    }
    respawn_pos.x += offset.x;
    Player_SetSpawnPlatformPos(slot, &respawn_pos);

    if (!(((u8) stage_info.unk8C.b0 >> 2U) & 1)) {
        Player_80032FA4(slot, var_r30);
        Player_SetSomePos(slot, &offset);
    }

    respawn_pos.y = Stage_GetCamBoundsTopOffset();
    Player_80032768(slot, &respawn_pos);
    if (respawn_pos.x >= 0.0f) {
        var_f1 = -1.0f;
    } else {
        var_f1 = 1.0f;
    }
    Player_SetFacingDirection(slot, var_f1);
    Player_SetHPByIndex(slot, subchar, match_info->FighterMatchInfo[slot].x6);
    Player_80032070(slot, subchar);
    if (subchar != 1) {
        ifStatus_802F6508(slot);
        temp_r4 = (u8*) &match_info->FighterMatchInfo[slot].xC;
        temp_r3 = *temp_r4;
        if ((temp_r3 >> 7U) & 1) {
            *temp_r4 &= 0x80;
            Camera_800310E8();
        }
    }
}

/// #gm_80167320

/// #gm_80167470

/// #gm_801674C4

/// #fn_8016758C

/// #fn_80167638

/// #gm_801677C0

void gm_801677E8(s8 arg0)
{
    lbl_804D6598 = arg0;
}

u8 gm_801677F0(void)
{
    return lbl_804D6598;
}

/// #gm_801677F8

/// #gm_80167858

/// #gm_801678F8

void gm_8016795C(struct PlayerInitData* arg0)
{
    memzero(arg0, sizeof(*arg0));
    arg0->c_kind = CHKIND_NONE;
    arg0->slot_type = Gm_PKind_NA;
    arg0->stocks = 0;
    arg0->color = 0;
    arg0->slot = 0;
    arg0->x5 = -1;
    arg0->spawn_dir = 0;
    arg0->xB = 0;
    arg0->sub_color = 0;
    arg0->handicap = 9;
    arg0->team = 0;
    arg0->xC_b0 = false;
    arg0->xA = 0x78;
    arg0->xC_b1 = true;
    arg0->xE = 4;
    arg0->cpu_level = 0;
    arg0->x12 = 0;
    arg0->hp = 0;
    arg0->x18 = 1.0F;
    arg0->x1C = 1.0F;
    arg0->x20 = 1.0F;
}

void gm_80167A14(struct PlayerInitData* arg0)
{
    int i;
    for (i = 0; i < 6; i++) {
        gm_8016795C(&arg0[i]);
    }
}

void gm_80167A64(struct StartMeleeRules* arg0)
{
    memzero(arg0, sizeof(*arg0));
    arg0->x0_3 = 4;

    arg0->xC = 0;
    arg0->xB = 2;

    arg0->x20 = -1;
    arg0->x28 = 0;

    arg0->x3_1 = 1;

    arg0->x3_5 = 1;
    arg0->x3_4 = 1;
    arg0->x4_0 = 1;

    arg0->timer_shows_hours = 0;
    arg0->x2_5 = 1;
    arg0->x2_6 = 1;

    arg0->x2C = 1.0f;
    arg0->x30 = 1.0f;
    arg0->x34 = 1.0f;

    arg0->x4_6 = 1;
    arg0->x4_7 = 1;
    arg0->xD = 0x6E;
    arg0->xA = 0;
}

void gm_80167B50(VsModeData* arg0)
{
    gm_80167A64(&arg0->data.rules);
    gm_80167A14(arg0->data.players);
    arg0->loser = -1;
    arg0->ordered_stage_index = -1;
    arg0->winner = -1;
}

void gm_80167BC8(VsModeData* vs_data)
{
    GameRules* rules;
    struct gmm_x1CB0* prefs;
    s32 i;
    s8* handicap;

    rules = gmMainLib_8015CC34();
    prefs = gmMainLib_8015CC58();
    vs_data->data.rules.x0_6 = 0;

    switch (rules->mode) {
    case 0:
        vs_data->data.rules.x0_0 = 0;
        if (rules->time_limit != 0) {
            vs_data->data.rules.x0_6 = 1;
            vs_data->data.rules.x10 = rules->time_limit * 60;
        }
        break;
    case 1:
        vs_data->data.rules.x0_0 = 1;
        if (rules->stock_time_limit != 0) {
            vs_data->data.rules.x0_6 = 1;
            vs_data->data.rules.x10 = rules->stock_time_limit * 60;
            break;
        }
        break;
    case 2:
        vs_data->data.rules.x0_0 = 2;
        if (rules->time_limit != 0) {
            vs_data->data.rules.x0_6 = 1;
            vs_data->data.rules.x10 = rules->time_limit * 60;
        }
        break;
    case 3:
        vs_data->data.rules.x0_0 = 3;
        if (rules->time_limit != 0) {
            vs_data->data.rules.x0_6 = 1;
            vs_data->data.rules.x10 = rules->time_limit * 60;
        }
        break;
    }

    i = 0;
    for (i = 0; i < 6; i++) {
        vs_data->data.players[i].stocks = (s8) rules->stock_count;
        switch (rules->handicap) {
        case 0:
            vs_data->data.players[i].x18 = 1.0f;
            vs_data->data.players[i].x1C = 1.0f;
            break;
        case 1:
            handicap =
                gmMainLib_8015CE44(i, (s32) vs_data->data.players[i].xA);
            if (handicap != NULL) {
                vs_data->data.players[i].handicap = *handicap;
                // TODO :: fix these to actually get the offensive and
                // defensive ratios just not sure how to setup the structs
                vs_data->data.players[i].x18 = lbl_803B7930[(u8) *handicap].x;
                vs_data->data.players[i].x1C = lbl_803B7930[(u8) *handicap].y;
            } else {
                vs_data->data.players[i].handicap = 5;
                vs_data->data.players[i].x18 = 0.61f;
                vs_data->data.players[i].x1C = 1.6393442f;
            }
            break;
        case 2:
            vs_data->data.players[i].x18 =
                lbl_803B7930[(u8) vs_data->data.players[i].handicap].x;
            vs_data->data.players[i].x1C =
                lbl_803B7930[(u8) vs_data->data.players[i].handicap].y;
            break;
        }
    }

    vs_data->data.rules.x1_7 = (rules->friendly_fire & 1);
    vs_data->data.rules.x30 = 0.1f * rules->damage_ratio;
    vs_data->data.rules.xB = (s8) prefs->item_freq;
    prefs = gmMainLib_8015CC58();

    // TODO :: some weird item copy thing that needs to be fixed
    i = 0;
    do {
        if ((s32) lbl_803B75F8.pad_x24C[i] != 0x23) {
            // prefs->item_mask = vs_data->data.rules.x20;
            if ((prefs->item_mask & (1LL << i))) {
                vs_data->data.rules.x20 |= (1LL << prefs->item_mask);
            } else {
                vs_data->data.rules.x20 &= ~(1LL << prefs->item_mask);
            }
        }
    } while (i < 0x20);
    // this is what decomp.py spits out
    // temp_r31 = gmMainLib_8015CC58();
    // var_r28_2 = 0;
    // do {
    //     if ((s32) lbl_803B75F8.pad_x24C[var_r28_2] != 0x23) {
    //         __shl2i();
    //         if ((((temp_r31->unkC & M2C_ERROR(/* Read from unset register
    //         $r4 */)) ^ 0) | ((temp_r31->unk8 & M2C_ERROR(/* Read from unset
    //         register $r3 */)) ^ 0)) != 0) {
    //             __shl2i();
    //             arg0->unk2C = (s32) (arg0->unk2C | M2C_ERROR(/* Read from
    //             unset register $r4 */)); arg0->unk28 = (s32) (arg0->unk28 |
    //             M2C_ERROR(/* Read from unset register $r3 */));
    //         } else {
    //             __shl2i();
    //             arg0->unk2C = (s32) (arg0->unk2C & ~(M2C_ERROR(/* Read from
    //             unset register $r4 */) | M2C_ERROR(/* Read from unset
    //             register $r4 */))); arg0->unk28 = (s32) (arg0->unk28 &
    //             ~(M2C_ERROR(/* Read from unset register $r3 */) |
    //             M2C_ERROR(/* Read from unset register $r3 */)));
    //         }
    //     }
    //     var_r28_2 += 1;
    // } while (var_r28_2 < 0x20);

    switch (gmMainLib_8015ED30()) {
    case 1:
        vs_data->data.rules.xC = 0;
        break;
    case 0:
        vs_data->data.rules.xC = -1;
        break;
    case 2:
        vs_data->data.rules.xC = -2;
        break;
    }

    if (rules->pause != 0) {
        vs_data->data.rules.x2_4 = 0;
    } else {
        vs_data->data.rules.x2_4 = 1;
    }
    if ((rules->score_display != 0) && (rules->mode == 0)) {
        vs_data->data.rules.x3_0 = 1;
        return;
    }
    vs_data->data.rules.x3_0 = 0;
}

/// #gm_80167FC4

/// #gm_801685D4

/// #gm_80168638

/// #gm_80168710

/// #gm_801688AC

/// #gm_80168940

void gm_8016895C(HSD_JObj* arg0, DynamicModelDesc* arg1, int idx)
{
    HSD_AnimJoint* anim = arg1->anims != NULL ? arg1->anims[idx] : NULL;
    HSD_MatAnimJoint* matanim =
        arg1->matanims != NULL ? arg1->matanims[idx] : NULL;
    HSD_ShapeAnimJoint* shapeanim =
        arg1->shapeanims != NULL ? arg1->shapeanims[idx] : NULL;
    HSD_JObjAddAnimAll(arg0, anim, matanim, shapeanim);
}

/// #fn_801689E4

/// #fn_80168A6C

/// #gm_80168B34

/// #gm_80168BF8

/// #gm_80168C5C

/// #fn_80168E54

/// #fn_80168F2C

void fn_80168F7C(void)
{
    lbl_804D659A = 0;
}

void gm_80168F88(void)
{
    lbAudioAx_80026F2C(0x12);
    lbAudioAx_8002702C(2, 0x10);
    lbAudioAx_80027168();
    lbAudioAx_80027648();
}

// UnclePunch: Audio_LoadAnnouncer
void gm_80168FC4(void)
{
    lbAudioAx_80026F2C(0x12);
    lbAudioAx_8002702C(2, 0x20);
    lbAudioAx_80027168();
    lbAudioAx_80027648();
}

/// #fn_80169000

/// #gm_80169238

/// #gm_80169264

/// #gm_80169290

/// #gm_801692BC

void gm_801692E8(u32 secs, datetime* datetime)
{
    OSCalendarTime tm;

    lbTime_8000B028(&tm, secs);
    datetime->year = tm.year;
    datetime->month = tm.mon + 1;
    datetime->day = tm.mday;
    datetime->hour = tm.hour;
    datetime->minute = tm.min;
    if (tm.sec > 59) {
        datetime->second = 59;
    } else {
        datetime->second = tm.sec;
    }
}

struct lbl_8046B488_t* fn_80169364(void)
{
    return &lbl_8046B488;
}

u8 gm_80169370(s32 arg0)
{
    return lbl_8046B488.pad_0[arg0];
}

u8 gm_80169384(void)
{
    return lbl_8046B488.x7;
}

s32 gm_80169394(void)
{
    return lbl_8046B488.unk_10_b3;
}

s32 fn_801693A8(void)
{
    return lbl_8046B488.unk_10_b2;
}

static inline bool gm_801693BC_inline(u8 ckind)
{
    if (ckind - 0x1B <= 1) {
        return true;
    }
    return false;
}

/// Player is Fighting Wireframe
bool gm_801693BC(int arg0)
{
    u8 ckind;
    PAD_STACK(8);
    if (Player_GetFlagsBit1(arg0) && (int) lbl_8046B488.x8 > 1) {
        return true;
    }
    ckind = Player_GetPlayerCharacter(arg0);
    ckind -= CKIND_BOY;
    if (ckind <= CKIND_GIRL - CKIND_BOY) {
        return true;
    }
    return false;
}

void fn_80169434(s32 arg0)
{
    M2C_FIELD(&lbl_8046B488, s32*, 0x1B8) = arg0;
}

/// #fn_80169444

int gm_801694A0(HSD_GObj* arg0)
{
    int i;
    int count = lbl_8046B488.x7;
    PAD_STACK(8);
    for (i = 0; i < 6; i++) {
        if (Player_GetPlayerSlotType(i) != Gm_PKind_NA &&
            Player_GetFlagsBit1(i) && Player_GetPlayerState(i) == 2)
        {
            count++;
        }
    }
    return count;
}

UNK_T gm_80169520(void)
{
    return &M2C_FIELD(&lbl_8046B488, UNK_T*, 0x20);
}

UNK_T gm_80169530(void)
{
    return &M2C_FIELD(&lbl_8046B488, UNK_T*, 0xA2);
}

UNK_T gm_80169540(void)
{
    return &M2C_FIELD(&lbl_8046B488, UNK_T*, 0x124);
}

/// #fn_80169550

/// #fn_80169574

/// #fn_801695BC

/// #fn_801697FC

/// #fn_8016989C

/// #fn_80169900

/// #fn_80169A84

/// #fn_80169C54

/// #fn_80169F50

/// #fn_8016A09C

void gm_8016A164(void)
{
    int i;
    lbl_8046B6A0_t* match_info = gm_8016AE44();
    PAD_STACK(4);

    match_info->is_singleplayer = false;
    lbl_8046B488.x8 = 0;
    lbl_8046B488.x7 = 0;
    lbl_8046B488.unk_10_b1 = false;
    lbl_8046B488.unk_10_b0 = false;
    fn_8016B138();

    for (i = 1; i < 6; i++) {
        Player_SetSlottype(i, Gm_PKind_NA);
        Player_UnsetFlagsBit1(i);
    }
}

s32 fn_8016A1E4(void)
{
    return lbl_8046B488.unk_10_b0;
}

bool gm_8016A1F8(void)
{
    if (lbl_8046B488.unk_10_b1) {
        return true;
    }
    return false;
}

void gm_8016A21C(StartMeleeRules* arg0)
{
    arg0->x54 = (void*) &lbl_8046B488;
}

/// #gm_8016A22C

void gm_8016A404(s32 arg0)
{
    M2C_FIELD(&lbl_8046B488, s32*, 0x1BC) = arg0;
}

void gm_8016A414(f32 arg8)
{
    M2C_FIELD(&lbl_8046B488, f32*, 0x1C) = arg8;
}

void gm_8016A424(s8 arg0)
{
    lbl_8046B488.xF = arg0;
}

/// #gm_8016A434

/// #fn_8016A450

/// #fn_8016A46C

/// #fn_8016A488

/// #fn_8016A4C8

void gm_8016A92C(StartMeleeRules* arg0)
{
    lbl_8046B668.unk_1C = -2;
    arg0->x58 = (int) &lbl_8046B668;
}

/// #gm_8016A944

UNK_T gm_8016A97C(void)
{
    return &M2C_FIELD(&lbl_8046B668, UNK_T*, 0x1C);
}

UNK_T gm_8016A98C(void)
{
    return &lbl_8046B668;
}

/// #gm_8016A998

/// #gm_8016A9E8

/// #gm_8016AC44
