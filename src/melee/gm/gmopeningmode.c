#include "gm_unsplit.h"
#include "gmevent.h"

#include "ft/forward.h"

#include "gm/gmtitlemode.h"
#include "gm/types.h"
#include "melee/db/db.h"
#include "melee/gm/gm_1601.h"
#include "melee/gm/gm_16F1.h"
#include "melee/gm/gm_unsplit.h"
#include "melee/gm/gmmain_lib.h"
#include "melee/gm/types.h"
#include "melee/lb/lbaudio_ax.h"
#include "melee/lb/lbdvd.h"
#include "melee/lb/lbmthp.h"
#include "melee/lb/types.h"
#include "melee/mn/types.h"

#include "melee/pl/forward.h"

#include "melee/vi/vi0102.h"
#include "melee/vi/vi0401.h"
#include "melee/vi/vi0501.h"
#include "melee/vi/vi0502.h"
#include "melee/vi/vi1101.h"
#include "melee/vi/vi1201v1.h"
#include "melee/vi/vi1201v2.h"
#include "vi/vi0102.h"

#include <sysdolphin/baselib/random.h>

struct gm_random_history {
    u8 pad0[2];
    u8 character_usage[0x1A];
    u8 stage_usage[0x1D];
};

/* 1BF060 */ static void onExitTitle(GameModeState*);
/* 1BF4DC */ static void onEnterVs(GameModeState*);
/* 1BF634 */ static void gm_801BF634(s32, s32);
/* 1BF648 */ static int gm_801BF648(s32);
/* 1BF65C */ static void gm_801BF65C(s32, s8);
/* 1BF670 */ static u8 gm_801BF670(s32);
/* 1BF684 */ static void gm_801BF684(s32);
/* 1BF694 */ static u8 gm_801BF694(void);
/* 1BF6A8 */ static void gm_801BF6A8(int);
/* 1BF6B8 */ static u8 gm_801BF6B8(void);
/* 1BF6C8 */ static void gm_801BF6C8(int);
/* 1BF6E8 */ static void gm_801BF6E8(int);
/* 1BF728 */ static void onEnterCutsceneLuigi(GameModeState*);
/* 1BF834 */ static void onExitRegendCongrats(GameModeState*);
/* 1BF85C */ static void onEnterMovie(GameModeState*);
/* 1BF898 */ static void onExitMovie(GameModeState*);
/* 1BF8B8 */ static void onExitHowto(GameModeState*);
/* 1BF8D8 */ static void onExitOmake15(GameModeState*);
/* 49C188 */ static StartMeleeData vs_enter_data;
/* 49C2C0 */ static MatchExitInfo vs_exit_data;
/* 4D6928 */ static UNK_T regend_congrats_enter_data;
/* 4D692C */ static UNK_T regend_congrats_exit_data;
/* 4D6930 */ static UNK_T title_exit_data[2];
/* 49E548 */ static struct gm_8049E548_t gm_8049E548;

GameModeState gm_Mode_Opening_States[] = {
    {
        0,
        lbDvdPreload_3,
        0,
        onEnterMovie,
        onExitMovie,
        {
            GS_MOVIE_OPENING,
            NULL,
            NULL,
        },
    },
    {
        1,
        lbDvdPreload_3,
        0,
        onEnterVs,
        NULL,
        {
            GS_VS,
            &vs_enter_data,
            &vs_exit_data,
        },
    },
    {
        2,
        lbDvdPreload_3,
        0,
        gmTitleMode_OnEnter,
        onExitTitle,
        {
            GS_TITLE,
            NULL,
            &title_exit_data,
        },
    },
    {
        3,
        lbDvdPreload_3,
        0,
        onEnterVs,
        NULL,
        {
            GS_VS,
            &vs_enter_data,
            &vs_exit_data,
        },
    },
    {
        4,
        lbDvdPreload_3,
        0,
        NULL,
        onExitHowto,
        {
            GS_MOVIE_HOWTO,
            NULL,
            NULL,
        },
    },
    {
        5,
        lbDvdPreload_3,
        0,
        NULL,
        onExitOmake15,
        {
            GS_MOVIE_OMAKE15,
            NULL,
            NULL,
        },
    },
    { -1 },
};

GameModeState gm_Mode_DebugCutscene_States[] = {
    {
        0,
        lbDvdPreload_2,
        0,
        onEnterCutsceneLuigi,
        NULL,
        {
            GS_CUTSCENE_LUIGI,
            &un_804D6F3C,
            NULL,
        },
    },
    {
        1,
        lbDvdPreload_2,
        0,
        NULL,
        NULL,
        {
            GS_CUTSCENE_BRINSTAR,
            &un_804D6F60,
            NULL,
        },
    },
    {
        2,
        lbDvdPreload_2,
        0,
        NULL,
        NULL,
        {
            GS_CUTSCENE_EXPLOSION,
            NULL,
            NULL,
        },
    },
    {
        3,
        lbDvdPreload_2,
        0,
        NULL,
        NULL,
        {
            GS_CUTSCENE_3KIRBYS,
            &un_804D6F84,
            NULL,
        },
    },
    {
        4,
        lbDvdPreload_2,
        0,
        NULL,
        NULL,
        {
            GS_CUTSCENE_GIANTKIRBY,
            &un_804D6FA8,
            NULL,
        },
    },
    {
        5,
        lbDvdPreload_2,
        0,
        NULL,
        NULL,
        {
            GS_CUTSCENE_STARFOX,
            NULL,
            NULL,
        },
    },
    {
        6,
        lbDvdPreload_2,
        0,
        NULL,
        NULL,
        {
            GS_CUTSCENE_FZERO,
            NULL,
            NULL,
        },
    },
    {
        7,
        lbDvdPreload_2,
        0,
        NULL,
        NULL,
        {
            GS_CUTSCENE_METAL,
            &un_804D6FD8,
            NULL,
        },
    },
    {
        8,
        lbDvdPreload_2,
        0,
        NULL,
        NULL,
        {
            GS_CUTSCENE_BOWSERTOY,
            &un_804D7004,
            NULL,
        },
    },
    {
        9,
        lbDvdPreload_2,
        0,
        NULL,
        NULL,
        {
            GS_CUTSCENE_GIGATRANSFORM,
            &un_804D7038,
            NULL,
        },
    },
    {
        10,
        lbDvdPreload_2,
        0,
        NULL,
        NULL,
        {
            GS_CUTSCENE_GIGADEFEATED,
            NULL,
            NULL,
        },
    },
    {
        11,
        lbDvdPreload_2,
        0,
        NULL,
        onExitRegendCongrats,
        {
            GS_REGEND_CONGRATS,
            &regend_congrats_enter_data,
            &regend_congrats_exit_data,
        },
    },
    { -1 },
};

void onExitTitle(GameModeState* arg0)
{
    int* temp_r3 = gm_GetGameSceneLeaveData(arg0);
    if (DbLevel >= DbLKind_DebugRom) {
        if (*temp_r3 & 0x100) {
            gm_SetPendingGameMode(GM_DEBUG_VS);
            gm_SetNewGameModePending();
        } else if (*temp_r3 & 0x1000) {
            gm_SetPendingGameMode(GM_MENU);
            gm_SetNewGameModePending();
        } else if (*temp_r3 & 0x400) {
            gm_SetPendingGameMode(GM_DEBUG_SOUND_TEST);
            gm_SetNewGameModePending();
        } else if (*temp_r3 & 0x800) {
            gm_SetPendingGameMode(GM_DEBUG);
            gm_SetNewGameModePending();
        }
    } else if (*temp_r3 & 0x1000) {
        gm_80173EEC();
        gm_80172898(0x100);
        if (!gm_80173754(1, 0)) {
            gm_SetPendingGameMode(GM_MENU);
        }
        gm_SetNewGameModePending();
    }
}

static inline struct gm_random_history* gm_GetRandomHistory(void)
{
    return (struct gm_random_history*) gmMainLib_804D3EE0;
}

static inline s32 gm_GetCharacterUsage(s32 index)
{
    return gm_GetRandomHistory()->character_usage[index];
}

static inline s32 gm_GetCharacterUsageDirect(s32 index)
{
    return ((struct gm_random_history*) gmMainLib_804D3EE0)
        ->character_usage[index];
}

static inline s32 gm_GetStageUsage(s32 index)
{
    return gm_GetRandomHistory()->stage_usage[index];
}

void gm_SetupTitleDemo(void)
{
    s32 character_pool[29];
    s32 stage_pool[30];
    s32* pool;
    s32 c;
    s32 count;
    s32 i;
    s32 j;
    s32 a;
    s32 pick;
    s32 dup;
    s32 prev;
    u8 cur_id;

    count = 0;
    c = 0;
    do {
        if (gm_IsCKindUnlocked(c) != 0) {
            character_pool[count] = c;
            count += 1;
        }
        c += 1;
    } while (c < CKIND_PLAYABLE_COUNT);
    character_pool[count] = CKIND_PLAYABLE_COUNT;
    for (i = 0; i < count; i++) {
        for (j = i + 1; j < count; j++) {
            if (gm_GetCharacterUsageDirect(character_pool[i]) >
                gm_GetCharacterUsage(character_pool[j]))
            {
                a = character_pool[i];
                character_pool[i] = character_pool[j];
                character_pool[j] = a;
            }
        }
    }
    c = 0;
    pool = character_pool;
    do {
        do {
            j = pool[HSD_Randi(8)];
            dup = 0;
            for (pick = 0; pick < c; pick++) {
                if (j == gm_801BF648(pick) ||
                    (j == CKIND_ZELDA && gm_801BF648(pick) == CKIND_SEAK) ||
                    (j == CKIND_SEAK && gm_801BF648(pick) == CKIND_ZELDA))
                {
                    dup = 1;
                }
            }
        } while (dup != 0);
        gm_801BF634(c, j);
        gm_801BF65C(c, 0);
        c += 1;
        gm_GetRandomHistory()->character_usage[j] += 1;
    } while (c < 4);
    gm_801BF6C8(HSD_Randi(4));
    do {
        gm_801BF6E8(HSD_Randi(4));
        prev = gm_801BF6F8();
        c = gm_801BF6D8();
    } while (c == prev);

    c = (count = 0);
    do {
        if (gm_80164430(gm_801641CC(c)) != 0) {
            stage_pool[count] = c;
            count += 1;
        }
        c += 1;
    } while (c < 0x1D);
    stage_pool[count] = 0x1D;
    for (i = 0; i < count; i++) {
        for (j = i + 1; j < count; j++) {
            if (gm_GetStageUsage(stage_pool[i]) >
                gm_GetStageUsage(stage_pool[j]))
            {
                a = stage_pool[i];
                stage_pool[i] = stage_pool[j];
                stage_pool[j] = a;
            }
        }
    }
    do {
        count = stage_pool[HSD_Randi(8)];
        cur_id = gm_801BF694();
        prev =
#ifdef MUST_MATCH
            __rlwinm(cur_id, 0, 24, 31);
#else
            cur_id & 0xFF;
#endif

        c = gm_801641CC((u8) count);
    } while (c == prev);
    gm_801BF684(gm_801641CC((u8) count));
    gm_GetRandomHistory()->stage_usage[count] += 1;
    gm_801BF6A8(HSD_Randi(4));
}

void gm_PreloadTitleDemo(void)
{
    struct GameCache* var_r31;
    u64 temp_ret;
    int i;
    int j;
    int c_kind;

    var_r31 = &lbDvd_GetPreloadCacheScene()->game_cache;
    lbDvd_80018C6C();

    for (i = 0; i < 4; i++) {
        var_r31->entries[i].char_id = gm_801BF648(i);
        var_r31->entries[i].color = gm_801BF670(i);
    }
    var_r31->stkind = gm_801BF694();
    lbDvd_80018254();

    temp_ret = 4;
    for (j = 0; j < 4; j++) {
        c_kind = gm_801BF648(j);
        if (c_kind != CHKIND_NONE) {
            temp_ret |= lbAudioAx_80026E84(c_kind);
        }
    }
    temp_ret |= lbAudioAx_80026EBC(gm_801BF694());
    lbAudioAx_80026F2C(0x1E);
    lbAudioAx_8002702C(0xE, temp_ret);
    lbAudioAx_80027168();
}

extern const f32 gm_804DAC88;

void onEnterVs(GameModeState* arg0)
{
    StartMeleeData* md;
    VsModeData* temp_r30;
    int i;

    temp_r30 = &gmMainLib_804D3EE0->unk_1710;
    md = gm_GetGameSceneLoadData(arg0);
    gm_80167BC8(temp_r30);
    gm_8016F088(md);
    gm_80168FC4();
    gm_80167A64(&md->rules);

    md->rules.match_mode = gm_801BF6B8();
    md->rules.x0_6 = false;
    md->rules.time_limit = 0;
    md->rules.x1_0 = false;
    md->rules.x1_2 = true;
    md->rules.x1_3 = true;
    md->rules.disable_pausing = true;
    md->rules.x7 = 0;
    md->rules.x44 = gm_80183218;
    md->rules.x34 = gm_804DAC88;
    md->rules.stkind = (u16) gm_801BF694();
    gm_80167A14(md->players);

    for (i = 0; i < 4; i++) {
        CharacterKind kind = gm_801BF648(i);
        md->players[i].c_kind = kind;
        md->players[i].color = gm_801BF670(i);
        md->players[i].slot_type = Gm_PKind_Cpu;
        md->players[i].cpu_level = 9;
        md->players[i].xE = 4;
        md->players[i].xC_b1 = false;
        if (md->rules.match_mode == 1) {
            md->players[i].stocks = 99;
        }
    }
}

/// @todo .sdata2 order hack
const f32 gm_804DAC88 = 1.0F;

void gm_801BF634(s32 arg0, s32 character_kind)
{
    gm_8049E548.c_kind[arg0] = character_kind;
}

int gm_801BF648(s32 arg0)
{
    return gm_8049E548.c_kind[arg0];
}

void gm_801BF65C(s32 arg0, s8 arg1)
{
    gm_8049E548.x4[arg0] = arg1;
}

u8 gm_801BF670(s32 arg0)
{
    return gm_8049E548.x4[arg0];
}

void gm_801BF684(s32 arg0)
{
    gm_8049E548.unk_C = arg0;
}

u8 gm_801BF694(void)
{
    return gm_8049E548.unk_C;
}

void gm_801BF6A8(int arg0)
{
    gm_8049E548.unk_A = arg0;
}

u8 gm_801BF6B8(void)
{
    return gm_8049E548.unk_A;
}

void gm_801BF6C8(int arg0)
{
    gm_8049E548.unk_8 = arg0;
}

int gm_801BF6D8(void)
{
    return gm_8049E548.unk_8;
}

void gm_801BF6E8(int arg0)
{
    gm_8049E548.unk_9 = arg0;
}

int gm_801BF6F8(void)
{
    return gm_8049E548.unk_9;
}

void gm_801BF708(s8 arg0)
{
    gm_8049E548.unk_E = arg0;
}

u8 gm_801BF718(void)
{
    return gm_8049E548.unk_E;
}

static inline void gm_801BEFA4_inner3(int ckind)
{
    gm_801BEFA4(ckind);
}

static inline void gm_801BEFA4_inner2(int ckind)
{
    gm_801BEFA4_inner3(ckind);
}

static inline void gm_801BEFA4_inner(int ckind)
{
    gm_801BEFA4_inner2(ckind);
}

static inline void gm_801BEFA4_noinline(int ckind)
{
    gm_801BEFA4_inner(ckind);
}

static inline void gm_801BEFC0_inner3(int arg0)
{
    gm_801BEFC0(arg0);
}

static inline void gm_801BEFC0_inner2(int arg0)
{
    gm_801BEFC0_inner3(arg0);
}

static inline void gm_801BEFC0_inner(int arg0)
{
    gm_801BEFC0_inner2(arg0);
}

static inline void gm_801BEFC0_noinline(int arg0)
{
    gm_801BEFC0_inner(arg0);
}

void onEnterCutsceneLuigi(GameModeState* arg)
{
    s32 temp_r31;
    s32 temp_r31_2;
    PAD_STACK(4);

    un_804D6F3C[1] = 1;
    un_804D6F3C[3] = 1;
    vi0401_8031D020(0xE, HSD_Randi(4));
    temp_r31 = HSD_Randi(4);
    un_8031D9E4(0xE, HSD_Randi(4), temp_r31);
    un_804D6F84[4] = HSD_Randi(0x1B);
    un_804D6F84[5] = HSD_Randi(0x1B);
    un_804D6F84[6] = HSD_Randi(0x1B);
    temp_r31_2 = HSD_Randi(4);
    un_8031E110(0xE, HSD_Randi(4), temp_r31_2);
    un_804D6FD8[0] = 0xE;
    un_804D6FD8[1] = HSD_Randi(4);
    un_8031F980(0xE, HSD_Randi(4));
    un_803204B0(0xE, HSD_Randi(4));
    gm_801BEFA4_noinline(8);
    gm_801BEFC0_noinline(HSD_Randi(4));
}

void onExitRegendCongrats(GameModeState* arg)
{
    gm_SetPendingGameMode(GM_TITLE);
    gm_SetNewGameModePending();
}

void onEnterMovie(GameModeState* arg)
{
    PreloadedGameModeState* temp_r31 = lbDvd_GetPreloadCacheScene();
    PAD_STACK(4);
    lbDvd_800174BC();
    temp_r31->is_heap_persistent[1] = false;
    lbDvd_80018254();
}

void onExitMovie(GameModeState* arg)
{
    lbMthp_8001F800();
}

void onExitHowto(GameModeState* arg)
{
    lbMthp_8001F800();
}

void onExitOmake15(GameModeState* arg)
{
    lbMthp_8001F800();
}
