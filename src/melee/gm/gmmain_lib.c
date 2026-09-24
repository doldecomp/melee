#include <melee/gm/gmmain_lib.h>

#include <Runtime/platform.h>

#include <placeholder.h>

#include <melee/gm/forward.h>
#include <melee/gm/gm_unsplit.h>
#include <melee/gm/gmhomerun.h>
#include <melee/gm/types.h>
#include <dolphin/os/OSReset.h>
#include <dolphin/pad.h>
#include <melee/db/db.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lbcardnew.h>
#include <melee/lb/lblanguage.h>
#include <melee/lb/lbtime.h>
#include <melee/mn/mnname.h>
#include <melee/ty/toy.h>
#include <sysdolphin/baselib/random.h>
#include <sysdolphin/baselib/video.h>

/* 15D888 */ static void gmMainLib_8015D888(u32);
/* 46B0F0 */ struct gmMainLib_8046B0F0_t gmMainLib_8046B0F0;
/* 45A6C0 */ struct gmm_x0 gmMainLib_8045A6C0;
/* 4D3EE0 */ struct gmm_x0* gmMainLib_804D3EE0 = &gmMainLib_8045A6C0;

GameRules gmMainLib_DefaultGameRules = {
    0,
    0x34,
    0,  // mode
    2,  // time limit
    3,  // stock count
    0,  // handicap
    10, // damage ratio
    0,
    0,     // stock time limit
    false, // friendly fire
    true,  // pause
    0,     // score display
    0,     // unk_xc
    0,     // xD
    8,     // xE
    8,     // xF
    0,     // unk_x10
    0,     // x11
    8,     // x12
    0,     // x13
    /* unk_14 */ -1,
};

struct GamePrefs gmMainLib_DefaultGamePrefs = {
    2, U64_MAX, { true, true, true, true }, 0, true, LANG_JP, U32_MAX,
};

GXRenderModeObj gmMainLib_803D4A80 = {
    VI_TVMODE_NTSC_PROG,
    0x280,
    0x1E0,
    0x1E0,
    0x28,
    0,
    0x280,
    0x1E0,
    VI_XFBMODE_SF,
    0,
    0,
    {
        { 6, 6 },
        { 6, 6 },
        { 6, 6 },
        { 6, 6 },
        { 6, 6 },
        { 6, 6 },
        { 6, 6 },
        { 6, 6 },
        { 6, 6 },
        { 6, 6 },
        { 6, 6 },
        { 6, 6 },
    },
    { 8, 8, 0xA, 0xC, 0xA, 8, 8 },
};

#ifdef MUST_MATCH
static void order_bss(void)
{
    (void) gmMainLib_8045A6C0;
    (void) gmMainLib_8046B0F0;
}
#endif

static inline u32 bitset_mask(u32 bit)
{
    return 1 << (bit % 32);
}

static inline void bitset_set(u32* words, u32 bit)
{
    words[bit / 32] |= bitset_mask(bit);
}

static inline void bitset_clear(u32* words, u32 bit)
{
    words[bit / 32] &= ~bitset_mask(bit);
}

static inline u32 bitset_test(const u32* words, u32 bit)
{
    u32 mask = bitset_mask(bit);
    return words[bit / 32] & mask;
}

/// Same as #bitset_test, but loads the word before forming the mask.
static inline u32 bitset_test_word(const u32* words, u32 bit)
{
    u32 word = words[bit / 32];
    return word & bitset_mask(bit);
}

static inline s64 bitset64_mask(u32 bit)
{
    return 1LL << bit;
}

static inline s32 selkind_mask(u8 kind)
{
    return 1 << kind;
}

static inline s32 selkind_bit(s32 word, u8 kind)
{
    return word & selkind_mask(kind);
}

static inline struct NameTagData* GetNameTagSlot(struct NameTagDataBank* banks,
                                                 s32 idx)
{
    return &banks[idx / GM_NAMETAG_BANK_SIZE]
                .inner[idx % GM_NAMETAG_BANK_SIZE];
}

GameRules* gmMainLib_GetGameRules(void)
{
    return &gmMainLib_804D3EE0->x1850;
}

struct GmCardData* gmMainLib_GetCardData(void)
{
    return &gmMainLib_804D3EE0->thing;
}

struct NameTagDataBank* gmMainLib_GetNameTagDataBanks(void)
{
    return gmMainLib_GetCardData()->nametag_banks;
}

struct GamePrefs* gmMainLib_GetGamePrefs(void)
{
    return &gmMainLib_GetCardData()->save_data.x1CB0;
}

static inline struct FighterData*
GetPersistentFighterDataBase(struct GmCardData* data)
{
    return data->save_data.x1F2C;
}

struct FighterData* GetPersistentFighterData(SelectableCharacterKind selkind)
{
    struct FighterData* base = gmMainLib_GetCardData()->save_data.x1F2C;
    return &base[selkind];
}

void* gmMainLib_GetTrophyFlags(void)
{
    return gmMainLib_GetCardData()->save_data.trophy_flags;
}

void* gmMainLib_GetTrophyCategoryFlags(void)
{
    return &gmMainLib_GetCardData()->save_data.trophy_category_flags;
}

s16* gmMainLib_GetTrophyCount(void)
{
    return &gmMainLib_GetCardData()->save_data.trophy_count;
}

struct NameTagData* GetPersistentNameData(s32 arg0)
{
    return GetNameTagSlot(gmMainLib_GetCardData()->nametag_banks, arg0);
}

struct gmm_x0_44_t* gmMainLib_8015CCE4(void)
{
    return &gmMainLib_804D3EE0->unk_44;
}

u32* gmMainLib_8015CCF0(void)
{
    return &gmMainLib_GetCardData()->save_data.x1A48;
}

void* gmMainLib_8015CCFC(void)
{
    return &gmMainLib_GetCardData()->save_data.x1A4C;
}

void* gmMainLib_GetVsPlayContestants(void)
{
    return &gmMainLib_GetCardData()->save_data.x1A30;
}

void* gmMainLib_GetVsPlayTime(void)
{
    return &gmMainLib_GetCardData()->save_data.x1A34;
}

void* gmMainLib_GetCombinedVSPlayTime(void)
{
    return &gmMainLib_GetCardData()->save_data.x1A38;
}

u32* gmMainLib_GetTimeMatchTotal(void)
{
    return &gmMainLib_GetCardData()->save_data.time_matches;
}

u32* gmMainLib_GetStockMatchTotal(void)
{
    return &gmMainLib_GetCardData()->save_data.stock_matches;
}

u32* gmMainLib_GetCoinMatchTotal(void)
{
    return &gmMainLib_GetCardData()->save_data.coin_matches;
}

u32* gmMainLib_GetBonusMatchTotal(void)
{
    return &gmMainLib_GetCardData()->save_data.bonus_matches;
}

u32* gmMainLib_GetStaminaMatchTotal(void)
{
    return &gmMainLib_GetCardData()->save_data.stamina_matches;
}

u32* gmMainLib_GetMatchResetCounter(void)
{
    return &gmMainLib_GetCardData()->save_data.match_resets;
}

void* gmMainLib_GetSingleplayerTime(void)
{
    return &gmMainLib_GetCardData()->save_data.x1A3C;
}

void* gmMainLib_8015CD80(void)
{
    return &gmMainLib_GetCardData()->save_data.x1A44;
}

void* gmMainLib_GetPowerCount(void)
{
    return &gmMainLib_GetCardData()->save_data.x1A50;
}

int* gm_GetPowerTime(void)
{
    return &gmMainLib_GetCardData()->save_data.x1A54;
}

void* gmMainLib_GetTotalDamage(void)
{
    return &gmMainLib_GetCardData()->save_data.x1A58;
}

s32* gmMainLib_GetKOTotal(void)
{
    return &gmMainLib_GetCardData()->save_data.x1A5C;
}

void* gmMainLib_GetSelfDestructTotal(void)
{
    return &gmMainLib_GetCardData()->save_data.x1A60;
}

struct gmm_x0_528_t* gmMainLib_8015CDC8(void)
{
    return &gmMainLib_804D3EE0->vs.unk_51C;
}

struct gmm_x0_528_t* gmMainLib_8015CDD4(void)
{
    return &gmMainLib_804D3EE0->vs.unk_522;
}

struct gmm_x0_528_t* gmMainLib_8015CDE0(void)
{
    return &gmMainLib_804D3EE0->vs.unk_528;
}

void gmMainLib_8015CDEC(void)
{
    ssize_t i;
    for (i = 0; i < Gm_Player_NumMax; i++) {
        s8* ptr = gmMainLib_8015CE44(i, GM_NAMETAG_COUNT);
        if (ptr != 0) {
            *ptr = 5;
        }
    }
}

s8* gmMainLib_8015CE44(s32 arg0, s32 arg1)
{
    if (arg1 == GM_NAMETAG_COUNT) {
        if (arg0 < PAD_MAX_CONTROLLERS) {
            return &gmMainLib_804D3EE0->modes.nametags[arg0];
        }
        return 0;
    } else {
        return &GetNameTagSlot(gmMainLib_GetCardData()->nametag_banks, arg1)
                    ->x1A2;
    }
}

void gmMainLib_8015CEB4(s32 arg0)
{
    gmMainLib_GetCardData()->save_data.x1A68 |= bitset64_mask(arg0);
}

bool gmMainLib_8015CEFC(int arg0)
{
    if (gmMainLib_804D3EE0->thing.save_data.x1A68 & bitset64_mask(arg0)) {
        return true;
    } else {
        return false;
    }
}

s32 gmMainLib_8015CF5C(s32 arg0)
{
    return gmMainLib_GetCardData()->save_data.x1A70[arg0];
}

void gmMainLib_8015CF70(s32 arg0, s32 arg1)
{
    gmMainLib_GetCardData()->save_data.x1A70[arg0] = arg1;
}

void gmMainLib_8015CF84(void)
{
    gmMainLib_GetCardData()->save_data.x1B3C = 1;
}

bool gmMainLib_8015CF94(void)
{
    if (gmMainLib_GetCardData()->save_data.x1B3C) {
        return true;
    }
    return false;
}

s8* gmMainLib_8015CFB4(u8 arg0)
{
    return &GetPersistentFighterData(arg0)->x78;
}

s32 gmMainLib_8015CFCC(u8 arg0)
{
    return selkind_mask(arg0) & gmMainLib_8015ED98()->xC;
}

void gmMainLib_8015D00C(u8 arg0)
{
    GetPersistentFighterDataBase(gmMainLib_GetCardData())[arg0].x7A.b0 = true;
    gmMainLib_8015ED98()->xC |= selkind_mask(arg0);
}

s32* gmMainLib_8015D06C(u8 arg0)
{
    return &GetPersistentFighterData(arg0)->x7C.x84;
}

s32* gmMainLib_8015D084(u8 selkind)
{
    return &gmMainLib_8015EDBC()->xB0[selkind];
}

s32* gmMainLib_8015D0C0(u8 arg0)
{
    return &GetPersistentFighterData(arg0)->x7C.x88;
}

bool gmMainLib_8015D0D8(u8 arg0)
{
    return GetPersistentFighterData(arg0)->x7C.b4;
}

s32 gmMainLib_8015D0F4(u8 arg0)
{
    return selkind_bit(gmMainLib_8015ED98()->x10, arg0);
}

void gmMainLib_8015D134(u8 arg0)
{
    GetPersistentFighterDataBase(gmMainLib_GetCardData())[arg0].x7C.b4 = true;
    gmMainLib_8015ED98()->x10 |= selkind_mask(arg0);
}

u8* gmMainLib_8015D194(u8 arg0)
{
    return &GetPersistentFighterData(arg0)->x7C.x80;
}

s32 gmMainLib_8015D1AC(u8 arg0)
{
    return GetPersistentFighterData(arg0)->x7C.b789;
}

void gmMainLib_8015D1C8(u8 arg0, int stocks)
{
    GetPersistentFighterData(arg0)->x7C.b789 = stocks;
}

s32* gmMainLib_8015D1E8(u8 arg0)
{
    return &GetPersistentFighterData(arg0)->x7C.x8C;
}

bool gmMainLib_8015D200(u8 arg0)
{
    return GetPersistentFighterData(arg0)->x7C.b5;
}

s32 gmMainLib_8015D21C(u8 arg0)
{
    return selkind_bit(gmMainLib_8015ED98()->x14, arg0);
}

void gmMainLib_8015D25C(u8 arg0)
{
    GetPersistentFighterDataBase(gmMainLib_GetCardData())[arg0].x7C.b5 = true;
    gmMainLib_8015ED98()->x14 |= selkind_mask(arg0);
}

u8* gmMainLib_8015D2BC(u8 arg0)
{
    return &GetPersistentFighterData(arg0)->x7C.x81;
}

s32 gmMainLib_8015D2D4(u8 arg0)
{
    return GetPersistentFighterData(arg0)->x7C.b10_to_12;
}

void gmMainLib_8015D2F0(u8 arg0, int stocks)
{
    GetPersistentFighterData(arg0)->x7C.b10_to_12 = stocks;
}

s32* gmMainLib_8015D310(u8 arg0)
{
    return &GetPersistentFighterData(arg0)->x7C.x90;
}

bool gmMainLib_8015D328(u8 arg0)
{
    return GetPersistentFighterData(arg0)->x7C.b6;
}

s32 gmMainLib_8015D344(u8 arg0)
{
    return selkind_bit(gmMainLib_8015ED98()->x18, arg0);
}

void gmMainLib_8015D384(u8 arg0)
{
    GetPersistentFighterDataBase(gmMainLib_GetCardData())[arg0].x7C.b6 = true;
    gmMainLib_8015ED98()->x18 |= selkind_mask(arg0);
}

u8* gmMainLib_8015D3E4(u8 arg0)
{
    return &GetPersistentFighterData(arg0)->x7C.x82;
}

s32 gmMainLib_8015D3FC(u8 arg0)
{
    return GetPersistentFighterData(arg0)->x7C.b13_to_15;
}

void gmMainLib_8015D418(u8 arg0, int stocks)
{
    GetPersistentFighterData(arg0)->x7C.b13_to_15 = stocks;
}

u32* gmMainLib_8015D438(u8 arg0)
{
    return &GetPersistentFighterData(arg0)->x7C.x94;
}

s32* gmMainLib_8015D450(u8 arg0)
{
    return &gmMainLib_8015EDBC()->x4C[arg0];
}

bool gmMainLib_8015D48C(u8 arg0)
{
    return GetPersistentFighterData(arg0)->x7C.b0;
}

s32 gmMainLib_8015D4A8(u8 arg0)
{
    return selkind_bit(gmMainLib_8015ED98()->x1C, arg0);
}

void gmMainLib_8015D4E8(u8 arg0, s32 arg1)
{
    GetPersistentFighterData(arg0)->x7C.b0 = arg1;
}

bool gmMainLib_8015D508(void)
{
    struct GmCardData* card = gmMainLib_GetCardData();
    s32 i;
    for (i = 0; i < SELKIND_COUNT; ++i) {
        struct FighterData* base = GetPersistentFighterDataBase(card);
        if (!base[(u8) i].x7C.b0) {
            return false;
        }
    }
    return true;
}

bool gmMainLib_8015D5DC(void)
{
    s32 i;
    for (i = 0; i < 0x19; i++) {
        if (selkind_bit(gmMainLib_8015EDB0()->x4, i) == 0) {
            return false;
        }
    }
    return true;
}

bool gmMainLib_8015D640(void)
{
    s32 i;
    for (i = 0; i < 0x19; i++) {
        if (selkind_bit(gmMainLib_8015EDBC()->x8, i) == 0) {
            return false;
        }
    }
    return true;
}

s32* gmMainLib_8015D6A4(u8 arg0)
{
    return &GetPersistentFighterData(arg0)->x7C.x98;
}

bool gmMainLib_8015D6BC(u8 arg0)
{
    return GetPersistentFighterData(arg0)->x7C.b1;
}

void gmMainLib_8015D6D8(u8 arg0, s32 arg1)
{
    GetPersistentFighterData(arg0)->x7C.b1 = arg1;
}

s32* gmMainLib_8015D6F8(u8 arg0)
{
    return &GetPersistentFighterData(arg0)->x7C.x9C;
}

bool gmMainLib_8015D710(u8 arg0)
{
    return GetPersistentFighterData(arg0)->x7C.b2;
}

void gmMainLib_8015D72C(u8 arg0, s32 arg1)
{
    GetPersistentFighterData(arg0)->x7C.b2 = arg1;
}

u16* gmMainLib_8015D74C(u8 arg0)
{
    return &GetPersistentFighterData(arg0)->x7C.xA0;
}

bool gmMainLib_8015D764(u8 arg0)
{
    return GetPersistentFighterData(arg0)->x7C.b3;
}

void gmMainLib_8015D780(u8 arg0)
{
    GetPersistentFighterData(arg0)->x7C.b3 = 1;
}

u16* gmMainLib_8015D7A4(u8 arg0)
{
    return &GetPersistentFighterData(arg0)->x7C.xA2;
}

s32* gmMainLib_8015D7BC(u8 arg0)
{
    return &GetPersistentFighterData(arg0)->x7C.xA4;
}

s32* gmMainLib_8015D7D4(u8 arg0)
{
    return &GetPersistentFighterData(arg0)->x7C.xA8;
}

u16* gmMainLib_8015D7EC(u8 arg0)
{
    return &GetPersistentFighterData(arg0)->x7C.x7E;
}

u32* gmMainLib_8015D804(s32 arg0)
{
    struct GmCardData* thing = gmMainLib_GetCardData();
    return &thing->save_data.x1B80[arg0];
}

s32 gmMainLib_8015D818(u32 arg0)
{
    u8 _[32];

    if (gmMainLib_8015D94C(arg0) == 0) {
        *gmMainLib_8015D804(arg0) = lbTime_GetTimeInSeconds();
        gmMainLib_8015D888(arg0);
        gmMainLib_8015D8FC(arg0);
        return 1;
    }
    return 0;
}

void gmMainLib_8015D888(u32 arg0)
{
    bitset_set(gmMainLib_GetCardData()->save_data.x1B40, arg0);
}

void gmMainLib_8015D8B0(u32 arg0)
{
    bitset_clear(gmMainLib_GetCardData()->save_data.x1B40, arg0);
}

s32 gmMainLib_8015D8D8(u32 arg0)
{
    return bitset_test(gmMainLib_GetCardData()->save_data.x1B40, arg0);
}

void gmMainLib_8015D8FC(u32 arg0)
{
    bitset_set(gmMainLib_GetCardData()->save_data.x1B4C, arg0);
}

void gmMainLib_8015D924(u32 arg0)
{
    bitset_clear(gmMainLib_GetCardData()->save_data.x1B4C, arg0);
}

int gmMainLib_8015D94C(u32 arg0)
{
    return bitset_test_word(gmMainLib_GetCardData()->save_data.x1B4C, arg0);
}

u32* gmMainLib_8015D970(ssize_t idx)
{
    struct gmm_x0_44_t* trophies = gmMainLib_8015CCE4();
    return &trophies->times[idx];
}

bool gmMainLib_8015D984(u32 arg0)
{
    PAD_STACK(8);

    if (gmMainLib_8015DA90(arg0) == 0) {
        *gmMainLib_8015D970(arg0) = lbTime_GetTimeInSeconds();

        gmMainLib_8015D9F4(arg0);
        gmMainLib_8015DA40(arg0);
        return true;
    }

    return false;
}

void gmMainLib_8015D9F4(u32 arg0)
{
    bitset_set(gmMainLib_8015CCE4()->flags, arg0);
}

s32 gmMainLib_8015DA1C(u32 arg0)
{
    return bitset_test(gmMainLib_8015CCE4()->flags, arg0);
}

void gmMainLib_8015DA40(u32 arg0)
{
    bitset_set(gmMainLib_GetCardData()->save_data.x1B58, arg0);
}

void gmMainLib_8015DA68(u32 arg0)
{
    bitset_clear(gmMainLib_GetCardData()->save_data.x1B58, arg0);
}

int gmMainLib_8015DA90(u32 arg0)
{
    return bitset_test_word(gmMainLib_GetCardData()->save_data.x1B58, arg0);
}

void gmMainLib_8015DAB4(u32 arg0)
{
    bitset_set(gmMainLib_GetCardData()->save_data.x1C88, arg0);
}

bool gmMainLib_8015DADC(u32 arg0)
{
    return bitset_test(gmMainLib_GetCardData()->save_data.x1C88, arg0);
}

u8 gmMainLib_8015DB00(void)
{
    return gmMainLib_804D3EE0->unk_1;
}

void gmMainLib_8015DB0C(u8 arg0)
{
    gmMainLib_804D3EE0->unk_1 = arg0;
}

void gmMainLib_8015DB18(void)
{
    gmMainLib_804D3EE0->unk_1 += 1;
}

void gmMainLib_8015DB2C(u8 arg0)
{
    struct gmm_x0* gmmthing = gmMainLib_804D3EE0;
    gmmthing->x39[arg0] = lbTime_8000AF74(gmMainLib_804D3EE0->x39[arg0], 1);
}

u8 gmMainLib_8015DB6C(u8 arg0)
{
    return gmMainLib_804D3EE0->x39[arg0];
}

void gmMainLib_8015DB80(void)
{
    int i;
    for (i = 0; i < 11; i++) {
        gmMainLib_804D3EE0->x39[(u8) i] = 0;
    }
}

static inline void gmMainLib_AdjustNameTags(VsModeData* vmd, u8 tag)
{
    u8* ptr;
    s32 i;

    for (i = 0; i < 6; i++) {
        ptr = &vmd->start.players[i].nametag;
        if (vmd->start.players[i].nametag == tag) {
            *ptr = GM_NAMETAG_COUNT;
        } else if (*ptr > tag && *ptr != GM_NAMETAG_COUNT) {
            *ptr -= 1;
        }
    }
}

static inline void gmMainLib_AdjustNameTag(u8* tag_ptr, u8 tag)
{
    if (*tag_ptr == tag) {
        *tag_ptr = GM_NAMETAG_COUNT;
    } else if (*tag_ptr > tag && *tag_ptr != GM_NAMETAG_COUNT) {
        *tag_ptr = *tag_ptr - 1;
    }
}

/// As #gmMainLib_AdjustNameTag, but clears the slot instead of marking it
/// unassigned.
static inline void gmMainLib_ClearNameTag(u8* tag_ptr, u8 tag)
{
    if (*tag_ptr == tag) {
        *tag_ptr = 0;
    } else if (*tag_ptr > tag && *tag_ptr != GM_NAMETAG_COUNT) {
        *tag_ptr = *tag_ptr - 1;
    }
}

void gmMainLib_8015DBF4(s32 arg0)
{
    struct gmm_x0_vsdata* vs;
    struct gmm_x0_vsmodes* base;
    GameRules* gr;

    vs = &gmMainLib_804D3EE0->vs;
    base = &gmMainLib_804D3EE0->modes;
    gmMainLib_AdjustNameTag(&gmMainLib_8015CDC8()->nametag, (u8) arg0);
    gmMainLib_AdjustNameTag(&gmMainLib_804D3EE0->vs.unk_522.nametag,
                            (u8) arg0);
    gmMainLib_AdjustNameTag(&gmMainLib_804D3EE0->vs.unk_528.nametag,
                            (u8) arg0);
    gmMainLib_AdjustNameTag(&vs->unk_530.nametag, (u8) arg0);
    gmMainLib_AdjustNameTag(&gmMainLib_804D3EE0->vs.unk_530.unk_584.unk_586,
                            (u8) arg0);

    gmMainLib_AdjustNameTags(&gmHomeRun_VsModeData, (u8) arg0);
    gmMainLib_AdjustNameTags(&base->table[GmVsMode_Multiman], (u8) arg0);
    gmMainLib_AdjustNameTags(&base->table[GmVsMode_Training], (u8) arg0);
    gmMainLib_AdjustNameTags(&base->table[GmVsMode_Melee], (u8) arg0);
    gmMainLib_AdjustNameTags(&base->table[GmVsMode_SuperSuddenDeath],
                             (u8) arg0);
    gmMainLib_AdjustNameTags(&base->table[GmVsMode_Invisible], (u8) arg0);
    gmMainLib_AdjustNameTags(&base->table[GmVsMode_Camera], (u8) arg0);
    gmMainLib_AdjustNameTags(&base->table[GmVsMode_FixedCamera], (u8) arg0);
    gmMainLib_AdjustNameTags(&base->table[GmVsMode_SingleButton], (u8) arg0);
    gmMainLib_AdjustNameTags(&base->table[GmVsMode_Tiny], (u8) arg0);
    gmMainLib_AdjustNameTags(&base->table[GmVsMode_Giant], (u8) arg0);
    gmMainLib_AdjustNameTags(&base->table[GmVsMode_Stamina], (u8) arg0);
    gmMainLib_AdjustNameTags(&base->table[GmVsMode_Slomo], (u8) arg0);
    gmMainLib_AdjustNameTags(&base->table[GmVsMode_Lightning], (u8) arg0);
    gmMainLib_AdjustNameTags(&base->table[GmVsMode_Multiman], (u8) arg0);

    gr = &gmMainLib_804D3EE0->x1850;
    gmMainLib_ClearNameTag(&gr->unk_x10, (u8) arg0);
    gmMainLib_ClearNameTag(&gr->x11, (u8) arg0);
    gmMainLib_ClearNameTag(&gr->x13, (u8) arg0);
}

static inline void SetDefaultHandicaps(VsModeData* mode)
{
    struct PlayerInitData* p = mode->start.players;
    s32 i;
    for (i = 0; i < GM_MAX_PLAYERS; i++) {
        p[i].handicap = 9;
    }
}

void gmMainLib_8015EA80(void)
{
    struct gmm_x0_vsmodes* modes = &gmMainLib_804D3EE0->modes;

    PAD_STACK(16);

    gmMainLib_8015CDEC();
    SetDefaultHandicaps(&modes->table[GmVsMode_Melee]);
    SetDefaultHandicaps(&modes->table[GmVsMode_SuperSuddenDeath]);
    SetDefaultHandicaps(&modes->table[GmVsMode_Invisible]);
    SetDefaultHandicaps(&modes->table[GmVsMode_Camera]);
    SetDefaultHandicaps(&modes->table[GmVsMode_FixedCamera]);
    SetDefaultHandicaps(&modes->table[GmVsMode_SingleButton]);
    SetDefaultHandicaps(&modes->table[GmVsMode_Tiny]);
    SetDefaultHandicaps(&modes->table[GmVsMode_Giant]);
    SetDefaultHandicaps(&modes->table[GmVsMode_Stamina]);
    SetDefaultHandicaps(&modes->table[GmVsMode_Slomo]);
    SetDefaultHandicaps(&modes->table[GmVsMode_Lightning]);
    SetDefaultHandicaps(&modes->table[GmVsMode_Multiman]);
}

int gmMainLib_8015ECB0(void)
{
    return gmMainLib_804D3EE0->x1850.bgm;
}

void gmMainLib_8015ECBC(void)
{
    u8 _[4];

    GameRules* rules = &gmMainLib_804D3EE0->x1850;
    if (gm_80164600() && gm_80164ABC()) {
        if (HSD_Randi(4) != 0) {
            rules->bgm = 0x34;
        } else {
            rules->bgm = 0x36;
        }
    } else {
        rules->bgm = 0x34;
    }
}

int gmMainLib_8015ED30(void)
{
    return gmMainLib_804D3EE0->x1850.unk_xc;
}

int GetRumbleSettingOfPort(ssize_t port)
{
    return gmMainLib_GetCardData()->save_data.x1CB0.rumble_enabled[port];
}

void gmMainLib_SetRumbleEnabled(ssize_t port, bool enabled)
{
    gmMainLib_GetGamePrefs()->rumble_enabled[port] = enabled;
}

s32 gmMainLib_8015ED5C(void)
{
    return gmMainLib_804D3EE0->x1850.unk_14;
}

void gmMainLib_8015ED68(ssize_t port)
{
    gmMainLib_804D3EE0->x1850.unk_14 = port;
}

u8 gmMainLib_8015ED74(void)
{
    return gmMainLib_GetGamePrefs()->sound_balance;
}

void gmMainLib_8015ED80(s8 arg0)
{
    gmMainLib_GetGamePrefs()->sound_balance = arg0;
}

u16* gmMainLib_GetUnlockedCharactersBitmaskPtr(void)
{
    return &gmMainLib_GetCardData()->save_data.unlocked_characters;
}

struct gmm_retval_ED98* gmMainLib_8015ED98(void)
{
    return &gmMainLib_GetCardData()->save_data.unk_8;
}

u16* gmMainLib_8015EDA4(void)
{
    return &gmMainLib_GetCardData()->save_data.x186A;
}

struct gmm_retval_EDB0* gmMainLib_8015EDB0(void)
{
    return &gmMainLib_GetCardData()->save_data.unk_28;
}

struct gmm_retval_EDBC* gmMainLib_8015EDBC(void)
{
    return &gmMainLib_GetCardData()->save_data.unk_30;
}

struct gmm_x1868_1A8_t* gmMainLib_8015EDC8(void)
{
    return &gmMainLib_GetCardData()->save_data.unk_1A8;
}

s32 gmMainLib_8015EDD4(void)
{
    return gmMainLib_GetCardData()->save_data.x186C & 4;
}

void gmMainLib_8015EDE4(void)
{
    gmMainLib_GetCardData()->save_data.x186C |= 4;
}

void gmMainLib_8015EDF8(void)
{
    gmMainLib_GetCardData()->save_data.x186C &= ~4;
}

s32 gmMainLib_8015EE0C(void)
{
    return gmMainLib_GetCardData()->save_data.x186C & 1;
}

void gmMainLib_8015EE1C(void)
{
    gmMainLib_GetCardData()->save_data.x186C |= 1;
}

void gmMainLib_8015EE30(void)
{
    gmMainLib_GetCardData()->save_data.x186C &= ~1;
}

s32 gmMainLib_8015EE44(void)
{
    return gmMainLib_GetCardData()->save_data.x186C & 2;
}

void gmMainLib_8015EE54(void)
{
    gmMainLib_GetCardData()->save_data.x186C |= 2;
}

void gmMainLib_8015EE68(void)
{
    gmMainLib_GetCardData()->save_data.x186C &= ~2;
    gmMainLib_GetGamePrefs()->stage_mask =
        gmMainLib_DefaultGamePrefs.stage_mask;
}

s32 gmMainLib_8015EE90(void)
{
    return gmMainLib_GetCardData()->save_data.x186C & 8;
}

void gmMainLib_8015EEA0(void)
{
    gmMainLib_GetCardData()->save_data.x186C |= 8;
}

void gmMainLib_8015EEB4(void)
{
    gmMainLib_GetCardData()->save_data.x186C &= ~8;
}

void gmMainLib_8015EEC8(void)
{
    int i;
    PAD_STACK(0x10);

    for (i = 0; i < SELKIND_COUNT; i++) {
        struct FighterData* data = GetPersistentFighterData(i);
        memzero(&data->x7C, sizeof(data->x7C));
    }
    memzero(&gmMainLib_GetCardData()->save_data.x1A68,
            offsetof(GmSaveData, x1B40) - offsetof(GmSaveData, x1A68));
}

void gmMainLib_8015EF30(struct GmStats* stats)
{
    stats->sd_count = 0;
    stats->attacks_hit = 0;
    stats->attacks_total = 0;
    stats->damage_dealt = 0;
    stats->damage_taken = 0;
    stats->peak_damage = 0;
    stats->match_count = 0;
    stats->victories = 0;
    stats->losses = 0;
    stats->play_time = 0;
    stats->total_player_count = 0;
    stats->damage_recovered = 0;
    stats->walk_distance = 0;
    stats->run_distance = 0;
    stats->fall_distance = 0;
    stats->peak_height = 0;
    stats->coins_swiped = 0;
    stats->coins_lost = 0;
    stats->coins_collected = 0;
}

void InitializePersistentNameData(s32 arg0)
{
    struct NameTagData* data;
    struct NameTagDataBank* bank;
    int i;

    PAD_STACK(16);

    bank = gmMainLib_804D3EE0->thing.nametag_banks;
    data = &bank[(u8) arg0 / GM_NAMETAG_BANK_SIZE]
                .inner[(u8) arg0 % GM_NAMETAG_BANK_SIZE];
    for (i = 0; i < GM_NAMETAG_COUNT; i++) {
        data->vs_kos[i] = 0;
    }
    gmMainLib_8015EF30(&data->stats);
    for (i = 0; i < SELKIND_COUNT; i++) {
        data->play_time_by_fighter[i] = 0;
    }
    data->x1A2 = 5;
}

static inline void ResetAllPersistentFighterData(void)
{
    s32 i;

    for (i = 0; i < SELKIND_COUNT; i++) {
        int j = 0;
        u8 k = i;
        struct FighterData* base =
            GetPersistentFighterDataBase(gmMainLib_GetCardData());
        for (; SELKIND_COUNT > j; j++) {
            base[k].fighter_kos[j] = 0;
        }
        gmMainLib_8015EF30(&base[k].stats);
    }
}

static inline void ResetPersistentFighterData(s32 i)
{
    int j = 0;
    struct FighterData* base =
        GetPersistentFighterDataBase(gmMainLib_GetCardData());
    for (; SELKIND_COUNT > j; j++) {
        base[(u8) i].fighter_kos[j] = 0;
    }
    gmMainLib_8015EF30(&base[(u8) i].stats);
}

void gmMainLib_8015F150(void)
{
    s32 i;

    for (i = 0; i < SELKIND_COUNT; i++) {
        ResetPersistentFighterData(i);
    }
}

void gmMainLib_8015F260(void)
{
    s32 i;

    PAD_STACK(16);

    for (i = 0; i < GM_NAMETAG_COUNT; i++) {
        InitializePersistentNameData(i);
    }
}

void gmMainLib_8015F464(void)
{
    memzero(gmMainLib_8015ED98(), sizeof(*gmMainLib_8015ED98()));
}

void gmMainLib_8015F490(void)
{
    memzero(gmMainLib_8015EDB0(), sizeof(*gmMainLib_8015EDB0()));
}

void gmMainLib_8015F4BC(void)
{
    memzero(gmMainLib_8015EDBC(), sizeof(*gmMainLib_8015EDBC()));
}

u32 gmMainLib_8015F4E8(void)
{
    return gmMainLib_GetGamePrefs()->deflicker;
}

void gmMainLib_8015F4F4(u8 arg0)
{
    gmMainLib_GetCardData()->save_data.x1CB0.deflicker = arg0;
}

void gmMainLib_8015F500(void)
{
    GXRenderModeObj* mode;

    if (gmMainLib_8046B0F0.progressive) {
        mode = gmMainLib_8015F4E8() ? &gmMainLib_803D4A80 : &GXNtsc480Prog;
    } else {
        mode = gmMainLib_8015F4E8() ? &GXNtsc480IntDf : &GXNtsc480Int;
    }
    HSD_VISetConfigure(mode);
}

void gmMainLib_8015F588(bool deflicker)
{
    GXRenderModeObj* mode;

    if (gmMainLib_8046B0F0.progressive) {
        mode = deflicker ? &gmMainLib_803D4A80 : &GXNtsc480Prog;
    } else {
        mode = deflicker ? &GXNtsc480IntDf : &GXNtsc480Int;
    }
    HSD_VISetConfigure(mode);
}

static s8 gmMainLib_804D3EE4[] = { 0 };

void gmMainLib_8015F600(int arg0, int arg1)
{
    s32 lang;
    PAD_STACK(80);

    if (arg0 == 1) {
        ResetAllPersistentFighterData();

        memzero(&gmMainLib_804D3EE0->thing.save_data.trophy_count,
                offsetof(GmSaveData, x1F2C) -
                    offsetof(GmSaveData, trophy_count));
        Toy_80311960();

        if (arg1 == 0) {
            Toy_803124BC();
            Toy_SetUnlockState((s32) (s16) Toy_80305058(2, 0x63, 0, 100.0f),
                               1);
        }

        gmMainLib_804D3EE0->thing.save_data.x1CB0 = gmMainLib_DefaultGamePrefs;

        {
            switch (lbLang_GetLanguageSetting()) {
            case 0:
                lang = 0;
                break;
            case 1:
                lang = 1;
                break;
            }
            lbLang_SetSavedLanguage(lang);
        }

        memzero(&gmMainLib_804D3EE0->thing, offsetof(GmSaveData, x1CB0));
        gm_801623FC(0x32);
        gm_IncrementPowerCount();

        if (arg1 == 0 && Toy_803048C0(0xA5) > 0 && gm_80164430(0x14U) == 0) {
            gm_80164504(0x14U);
        }
    } else {
        s32 bank_offset = (arg0 - 2) * GM_NAMETAG_BANK_SIZE;
        s32 j;
        for (j = 0; j < GM_NAMETAG_BANK_SIZE; j++) {
            struct NameTagData* data;
            struct NameTagDataBank* bank;
            s32 idx;
            idx = j + bank_offset;

            InitializePersistentNameData(idx);

            bank = gmMainLib_804D3EE0->thing.nametag_banks;
            {
                struct NameTagData* tmp =
                    &bank[(u8) idx / GM_NAMETAG_BANK_SIZE]
                         .inner[(u8) idx % GM_NAMETAG_BANK_SIZE];
                data = tmp;
            }
            {
                char* src = mnName_8023749C((s32) (u8) idx);
                if (src != NULL) {
                    s32 k = 0;
                    char c;
                    while (gmMainLib_804D3EE4[0] != (s8) (c = *src)) {
                        data->namedata[k] = c;
                        k++;
                        src++;
                    }
                    data->namedata[k] = gmMainLib_804D3EE4[0];
                } else {
                    data->namedata[0] = gmMainLib_804D3EE4[0];
                }
            }
            data->rumble_enabled = true;
        }
    }
}

static inline void setupAudioVideo(void)
{
    lbAudioAx_80028690();
    gmMainLib_8015F500();
}

static inline void resetSaveData(void)
{
    int i;

    for (i = 1; i < 9; i++) {
        gmMainLib_8015F600(i, 1);
    }
    setupAudioVideo();
}

void gmMainLib_8015FA34(s32 arg0)
{
    s32 i;

    PAD_STACK(56);

    for (i = 1; i < 9; i++) {
        if ((arg0 != 0 && arg0 != 2) || lb_8001B6E0(i) != 0) {
            gmMainLib_8015F600(i, 0);
        } else if (i == 1 && !gmMainLib_8046B0F0.skip_intro) {
            gm_IncrementPowerCount();
        }
    }
    if (DbLevel > DbLKind_DebugDevelop && db_804D6B20 != 0) {
        gmMainLib_804D3EE0->thing.save_data.x186C = 0xFF;
        gm_80164F18();
        gm_8016468C();
        gm_8017297C();
        gm_801741FC();
    }
    setupAudioVideo();
}

void gmMainLib_8015FB68(void)
{
    gmMainLib_804D3EE0->thing.save_data.x186C = 0;
    gm_8016505C();
    gm_801647D0();
    gm_801729EC();
    gm_80174238();
    Toy_80311960();
}

void gmMainLib_8015FBA4(void)
{
    memzero(gmMainLib_804D3EE0, sizeof(*gmMainLib_804D3EE0));
    if (DVDConvertPathToEntrynum("/usa.ini") != -1) {
        lbLang_SetLanguageSetting(1);
        lbLang_SetSavedLanguage(1);
    } else {
        lbLang_SetLanguageSetting(0);
        lbLang_SetSavedLanguage(0);
    }

    gmMainLib_8045A6C0.x1850 = gmMainLib_DefaultGameRules;
    resetSaveData();
}

int gmMainLib_8015FC74(void)
{
    int prev;

    prev = gmMainLib_8046B0F0.x10;
    gmMainLib_8046B0F0.x10 = lbTime_GetTimeInSeconds();
    return gmMainLib_8046B0F0.x10 - prev;
}

void gmMainLib_8015FCC0(void)
{
    struct gmMainLib_8046B0F0_t* tmp = &gmMainLib_8046B0F0;
    tmp->skip_intro = OSGetResetCode() == 0x80000000 ? true : false;
    tmp->resetting = false;
    tmp->progressive = false;
    tmp->xC = 0;
    tmp->x10 = lbTime_GetTimeInSeconds();
}
