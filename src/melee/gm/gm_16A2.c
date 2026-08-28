#include "gm_16A2.h"

#include "gm_unsplit.h"

#include "gr/ground.h"
#include "gr/stage.h"
#include "if/ifnametag.h"
#include "if/ifstatus.h"
#include "lb/lb_00B0.h"

#include <stddef.h>
#include <sysdolphin/baselib/random.h>
#include <melee/pl/player.h>

/* 46B488 */ static struct lbl_8046B488_t lbl_8046B488;
/* 46B668 */ static struct lbl_8046B668_t lbl_8046B668;

struct gm_8016A22C_header {
    u8 bytes[0x20];
    /* 0x020 */ s8 x20[0xA2 - 0x20];
    /* 0x0A2 */ u8 xA2[0x124 - 0xA2];
};

typedef void (*GmEventPlayerInitCallback)(s32 slot, u8 remaining_count);

struct lbl_8046B488_event_player_init_cb_t {
    char pad_0[0x1BC];
    GmEventPlayerInitCallback event_player_init_cb;
};
ASSERT_SIZE(struct lbl_8046B488_event_player_init_cb_t, 0x1C0);

struct lbl_8046B488_t* gm_1601_GetUnkData(void)
{
    return &lbl_8046B488;
}

s8 gm_80169370(s32 arg0)
{
    return ((s8*) gm_1601_GetUnkData())[arg0];
}

int gm_80169384(void)
{
    return gm_1601_GetUnkData()->x7;
}

s32 gm_80169394(void)
{
    return gm_1601_GetUnkData()->unk_10_b3;
}

s32 fn_801693A8(void)
{
    return gm_1601_GetUnkData()->unk_10_b2;
}

/// Player is Fighting Wireframe
bool gm_801693BC(int arg0)
{
    u8 ckind;
    PAD_STACK(8);
    if (Player_GetFlagsBit1(arg0) && (int) gm_1601_GetUnkData()->x8 > 1) {
        return true;
    }
    ckind = Player_GetPlayerCharacter(arg0);
    ckind -= CKIND_BOY;
    if (ckind <= CKIND_GIRL - CKIND_BOY) {
        return true;
    }
    return false;
}

void fn_80169434(GmRouteCallback fn)
{
    gm_1601_GetUnkData()->x1B8 = fn;
}

bool fn_80169444(bool arg0)
{
    struct lbl_8046B488_t* gp = gm_1601_GetUnkData();

    if (gp->x1B8 != NULL) {
        if (gp->x1B8(arg0) == 1) {
            gp->x1B8 = NULL;
            return true;
        }
    }
    return false;
}
int gm_801694A0(HSD_GObj* arg0)
{
    int i;
    int count = gm_1601_GetUnkData()->x7;
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
    return gm_1601_GetUnkData()->x20;
}

UNK_T gm_80169530(void)
{
    return gm_1601_GetUnkData()->xA2;
}

UNK_T gm_80169540(void)
{
    return gm_1601_GetUnkData()->x124;
}

void fn_80169550(int slot)
{
    struct lbl_8046B488_t* gp = gm_1601_GetUnkData();
    s8 idx = gp->x1A6[slot];
    gp->x20[idx] = -1;
}

void fn_80169574(ssize_t size, s8* buf)
{
    memzero(buf, size);
    buf[size] = -2;
}

static inline s8* fn_801695BC_rand_color(s32 ncolors, s8* colors)
{
    return &colors[HSD_Randi(ncolors)];
}

void fn_801695BC(u8 arg0, u8 arg1, u8 arg2, const u8* arg3, s8* arg4)
{
    s32 tmp2;
    s8 tmp;
    s32 i;
    s32 ncolors_s32;
    s32 color_i;
    u8 ncolors;
    s8 colors[6];

    ncolors = gm_80169238(arg0);
    if ((s8) arg0 != 0x21) {
        ncolors_s32 = ncolors;
        for (i = 0; i < ncolors; i++) {
            colors[i] = (s8) i;
        }
        if ((s8) arg1 == (s8) arg0) {
            colors[(s8) arg2] = -1;
        }
        for (i = 0; i < ncolors_s32; i++) {
            s8* other = fn_801695BC_rand_color(ncolors_s32, colors);
            tmp = *other;
            *other = colors[i];
            colors[i] = tmp;
        }
        color_i = 0;
        for (i = 0; arg4[i] != -2; i++) {
            if ((s8) arg0 == (s8) arg3[i]) {
                if (colors[color_i % ncolors_s32] == -1) {
                    color_i += 1;
                }
                arg4[i] = colors[color_i % ncolors_s32];
                color_i += 1;
            }
        }
        for (i = 1; arg4[i] != -2; i++) {
            if ((s8) arg0 == (s8) arg3[i] && (s8) arg0 == (s8) arg3[i - 1]) {
                if (HSD_Randi(2) != 0) {
                    tmp2 = arg4[i];
                    arg4[i] = arg4[i - 1];
                    arg4[i - 1] = tmp2;
                }
            }
        }
    }
}

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
void fn_801697FC(s8 character, s8 costume, s8 new_character, s8 new_costume,
                 s8* buf)
{
    u8 ncolors = gm_80169238(character);
    int i;

    if (character == 0x21) {
        return;
    }
    if (new_character == character && costume == new_costume) {
        costume = (costume + 1) % ncolors;
    }
    for (i = 0; buf[i] != -2; i++) {
        buf[i] = costume;
    }
}
#ifdef MUST_MATCH
#pragma pop
#endif

void fn_8016989C(u8* arg0, u8 arg1, u8 arg2, u8* arg3, s8* arg4)
{
    int i;
    for (i = 0; i < 3; i++) {
        fn_801695BC(arg0[i], arg1, arg2, arg3, arg4);
    };
}

void fn_80169900(u8 arg0, struct lbl_8046B488_t* arg1, s8* arg2, s8* arg3)
{
    s32 var_r28 = 0;

    switch (arg0) {
    case 0: {
        s8* src;
        s8* dst;
        dst = arg2;
        src = arg3;
        while (*src != -2) {
            *dst = arg1->x0;
            src += 1;
            dst += 1;
        }
        break;
    }
    case 1: {
        s8* dst = arg2;
        arg2 = arg3;
        while (*arg2 != -2) {
            if (HSD_Randi(2) != 0) {
                *dst = arg1->x0;
            } else {
                *dst = arg1->x1;
            }
            arg2 += 1;
            dst += 1;
        }
        break;
    }
    case 2: {
        s32 var_r27 = HSD_Randi(5);
        while (arg3[var_r28] != -2) {
            if (var_r27 != 0) {
                var_r27 -= 1;
                arg2[var_r28] = arg1->x0;
            } else {
                var_r27 = 5;
                if (HSD_Randi(2) != 0) {
                    if (arg1->x1 != CHKIND_NONE &&
                        gm_IsCKindUnlocked(arg1->x1))
                    {
                        arg2[var_r28] = arg1->x1;
                    } else {
                        arg2[var_r28] = arg1->x0;
                    }
                } else {
                    if (arg1->x2 != CHKIND_NONE &&
                        gm_IsCKindUnlocked(arg1->x2))
                    {
                        arg2[var_r28] = arg1->x2;
                    } else {
                        arg2[var_r28] = arg1->x0;
                    }
                }
            }
            var_r28 += 1;
        }
        break;
    }
    }
}

s32 fn_80169A84(u8 arg0, s8* arg1, s8* arg2)
{
    s8* p;
    s32 count;
    s8* list;
    int i;
    s8* src;
    s8* dst;
    u8 tmp;
    s8 result;
    switch (arg0) {
    case 1:
        i = 0;
        {
            s8* list_start = lbl_8046B488.x1C0;
            list = list_start;
        }
        p = list;
        do {
            if (i != 4 && gm_IsCKindUnlocked((u8) i) != 0) {
                *p = i;
            } else {
                *p = -1;
            }
            i += 1;
            p += 1;
        } while (i < CKIND_PLAYABLE_COUNT);

        i = 0;
        p = list;
        do {
            s8* q;
            q = &lbl_8046B488.x0 + HSD_Randi(0x1B);
            tmp = q[0x1C0];
            i += 1;
            q[0x1C0] = (u8) *p;
            *p = tmp;
            p += 1;
        } while (i < CKIND_PLAYABLE_COUNT);

        {
            s32 j;
            count = 0;
            for (j = 0; j < 0x1A; j++) {
                if (*list != -1) {
                    count += 1;
                    if (count > 0x10) {
                        *list = -1;
                    }
                }
                list++;
            }
        }

        {
            s32 idx = 0;
            s8* dst2 = arg1;
            s8* src2 = arg2;
            while (*src2 != -2) {
                while ((result = (p = &lbl_8046B488.x0 + idx)[0x1C0]) == -1) {
                    idx = (idx + 1) % 27;
                }
                result = Player_800325C8(result, 0);
                *dst2 = result;
                idx += 1;
                src2 += 1;
                dst2 += 1;
            }
        }
        break;
    case 0:
        dst = arg1;
        src = arg2;
        while (*src != -2) {
            *dst = -1;
            src += 1;
            dst += 1;
        }
        break;
    }
}

static inline struct lbl_8046B488_t* fn_80169C54_inline(void)
{
    return fn_8016AE60();
}

static inline void fn_80169C54_apply(s32 p, s32 count, s32* buf)
{
    s32 i;

    for (i = 0; i < count; i++) {
        Player_80031DA8(p, buf[i]);
    }
}

void fn_80169C54(s8 arg0, s8 arg1)
{
    struct lbl_8046B488_t* st;
    s32 buf[7];
    s8* pc;
    s32 n;
    s32 i;
    s32 count;
    s32 k;
    s32 j;
    s32 p1;
    s32 p0;
    s8* cp;
    s32 p;
    s32 ch;

    n = 0;
    st = fn_80169C54_inline();
    pc = &st->x0;
    for (i = 0; i < 7; i++) {
        buf[i] = -1;
    }
    for (i = 0; i < 3; i++) {
        if ((s32) *pc == 4) {
            if (st->xB == 0) {
                count = gm_80169238(4U);
                for (k = 0; k < count; k++) {
                    buf[k] = k;
                    n++;
                }
            } else {
                n = 1;
                buf[0] = st->xC;
            }
            break;
        }
        pc++;
    }

    if (arg0 == 4) {
        buf[n] = arg1;
        n++;
    }
    if (n > 0) {
        j = 0;
        cp = &st->x0;
        do {
            ch = *cp;
            if (0x21 != ch && ch != 4) {
                p = Player_800325C8((CharacterKind) ch, 0);
                if ((p != -1) && (p != 4)) {
                    fn_80169C54_apply(p, n, buf);
                }
                p = Player_800325C8((CharacterKind) ch, 1);
                if ((p != -1) && (p != 4)) {
                    fn_80169C54_apply(p, n, buf);
                }
            }
            j++;
            cp++;
        } while (j < 3);
        if (arg0 != 4) {
            p0 = Player_800325C8((CharacterKind) arg0, 0);
            if ((p0 != -1) && (p0 != 4)) {
                for (k = 0; k < n; k++) {
                    Player_80031DA8(p0, buf[k]);
                }
            }
            p1 = Player_800325C8((CharacterKind) arg0, 1);
            if ((p1 != -1) && (p1 != 4)) {
                for (k = 0; k < n; k++) {
                    Player_80031DA8(p1, buf[k]);
                }
            }
        }
    }
}

static inline void fn_80169F50_inline(s8 costume, struct lbl_8046B488_t* gp,
                                      int character)
{
    s32 i;
    s32 costume_id;
    if (character == 4 && gp->xE != 0) {
        i = 0;
        costume_id = costume;
        for (; gp->x20[i] != -2; i++) {
            if (gp->x20[i] == -1) {
                continue;
            }
            if (gp->x124[i] == -1) {
                continue;
            }
            Player_80031DA8(gp->x124[i], costume_id);
        }
    }
}

void fn_80169F50(s8 arg0, s8 arg1)
{
    struct lbl_8046B488_t* gp = &lbl_8046B488;
    s32 i;
    s8* p;
    s8 v;
    s32 flag;
    s8 temp_arg0;

    temp_arg0 = arg0;
    flag = 0;
    p = &gp->x0;
    for (i = 0; i < 3; i++) {
        if (p[i] == 4) {
            flag = 1;
            break;
        }
    }

    if (flag == 1 && gp->xE != 0) {
        for (i = 0; gp->x20[i] != -2; i++) {
            v = gp->x20[i];
            if (v == -1) {
                continue;
            }
            if (gp->xA2[i] != 4) {
                continue;
            }
            if (gp->x124[i] == -1) {
                continue;
            }
            Player_80031DA8(gp->x124[i], v);
        }
    }

    fn_80169F50_inline(arg1, gp, temp_arg0);
}

void fn_8016A09C(void)
{
    s32 i;
    s32 var_r29;
    s32 j;
    PAD_STACK(4);
    var_r29 = 0;

    gm_16AE_GetUnkData_1();
    lbl_8046B488.unk_10_b1 = 1;
    lbl_8046B488.unk_10_b0 = 0;

    for (i = 0; i < 6; i++) {
        if (Player_GetPlayerSlotType(i) == Gm_PKind_NA) {
            if (var_r29 >= (j = (s32) lbl_8046B488.x9)) {
                break;
            }
            Player_SetFlagsBit1(i);
            var_r29++;
        }
    }

    for (j = 0; j < 6; j++) {
        if (Player_GetFlagsBit1(j) != 0) {
            Player_SetTeam(j, 4);
        }
    }
}

/// @todo Offset mismatch indicates a TU split between #lbl_8046B378 and
///       #lbl_8046B488
void gm_8016A164(void)
{
    int i;
    struct lbl_8046B488_t* gp = gm_1601_GetUnkData();
    lbl_8046B6A0_t* match_info = gm_16AE_GetUnkData_1();
    PAD_STACK(4);
    if (gp == 0) {
        if (match_info == 0) {
        }
    }

    match_info->is_singleplayer = false;
    gp->x8 = 0;
    gp->x7 = 0;
    gp->unk_10_b1 = false;
    gp->unk_10_b0 = false;
    fn_8016B138();

    for (i = 1; i < 6; i++) {
        Player_SetSlottype(i, Gm_PKind_NA);
        Player_UnsetFlagsBit1(i);
    }
}

s32 fn_8016A1E4(void)
{
    return gm_1601_GetUnkData()->unk_10_b0;
}

bool gm_8016A1F8(void)
{
    if (gm_1601_GetUnkData()->unk_10_b1) {
        return true;
    }
    return false;
}

void gm_8016A21C(StartMeleeRules* arg0)
{
    arg0->x54 = (void*) gm_1601_GetUnkData();
}

static inline GmEventPlayerInitCallback*
gm_8016A404_event_player_init_cb(struct lbl_8046B488_t* gp)
{
    struct lbl_8046B488_event_player_init_cb_t* state =
        (struct lbl_8046B488_event_player_init_cb_t*) gp;
    return &state->event_player_init_cb;
}

static inline struct gm_8016A22C_header*
gm_8016A22C_header(struct lbl_8046B488_t* gp)
{
    return (struct gm_8016A22C_header*) gp;
}

s32 gm_8016A22C(s8 k0, s8 k1, s8 k2, u8 a3, u8 a4, int a5, int mode, int a7,
                u8 color, u8 p87, u8 p8b, int x6, int x7, int x9, int xA,
                int flag2, int flag1, f32 f1, f32 f2)
{
    int i;
    struct lbl_8046B488_t* gp = &lbl_8046B488;
    struct gm_8016A22C_header* header;
    u8 x7_tmp;

    memzero(gp, 0x1C0);

    lbl_8046B488.x0 = k0;
    lbl_8046B488.x1 = k1;
    lbl_8046B488.x2 = k2;

    lbl_8046B488.x3 = a3;
    lbl_8046B488.x4 = a4;
    lbl_8046B488.x5 = (u8) a5;

    lbl_8046B488.x1AC = p87;
    lbl_8046B488.x1AD = 0x21;
    lbl_8046B488.x1B2 = p8b;

    lbl_8046B488.x6 = x6;
    lbl_8046B488.x7 = x7;
    lbl_8046B488.x8 = x7;

    if (x9 > 5) {
        x9 = 5;
    }
    lbl_8046B488.x9 = (u8) x9;

    lbl_8046B488.xA = (u8) xA;

    lbl_8046B488.x14 = f1;
    lbl_8046B488.x18 = f2;

    lbl_8046B488.unk_10_b2 = flag2;
    lbl_8046B488.unk_10_b1 = flag1;

    lbl_8046B488.x1C = 1.0f;

    lbl_8046B488.xB = (u8) mode;
    lbl_8046B488.xD = (u8) a7;
    lbl_8046B488.xE = color;

    lbl_8046B488.xC = a3;

    header = gm_8016A22C_header(gp);
    x7_tmp = header->bytes[7];
    memzero(header->x20, x7_tmp);
    header->x20[x7_tmp] = -2;

    fn_80169900(gp->xD, gp, (s8*) header->xA2, header->x20);

    switch (header->bytes[0xB]) {
    case 0:
        for (i = 0; i < 3; i++) {
            fn_801695BC(header->bytes[i], p87, p8b, header->xA2, header->x20);
        }
        break;

    case 1: {
        u8 c = gp->xC;
        for (i = 0; i < 3; i++) {
            fn_801697FC(header->bytes[i], c, p87, p8b, header->x20);
        }
        break;
    }
    }

    return fn_80169A84(gp->xE, gp->x124, gp->x20);
}

void gm_8016A404(s32 arg0)
{
    *gm_8016A404_event_player_init_cb(&lbl_8046B488) =
        (GmEventPlayerInitCallback) arg0;
}

void gm_8016A414(f32 arg8)
{
    lbl_8046B488.x1C = arg8;
}

void gm_8016A424(s8 arg0)
{
    lbl_8046B488.xF = arg0;
}

void gm_8016A434(void)
{
    lbl_8046B488.unk_10_b3 = 1;
}

void fn_8016A450(void)
{
    lbl_8046B488.unk_10_b4 = 1;
}

void fn_8016A46C(void)
{
    lbl_8046B488.unk_10_b6 = 1;
}

void fn_8016A488(int arg0)
{
    if (gm_16AE_GetUnkData_1()->hud_enabled == true) {
        Player_80031848(arg0);
    }
}

static inline int getSpawnPointIndex(int spawn_slot)
{
    return spawn_slot + lbl_8046B488.xA - 1;
}

static inline f32 fn_8016A4C8_attack_ratio(void)
{
    return lbl_8046B488.x14;
}

static inline int roll_cpu_type(void)
{
    int cpu_type = 0x17;
    if ((s32) lbl_8046B488.x7 != 1) {
        switch (HSD_Randi(4)) {
        case 0:
        case 1:
        case 2:
            return 0x17;
        case 3:
            cpu_type = 0x18;
            break;
        default:
            cpu_type = 0x17;
            break;
        }
    }
    return cpu_type;
}

static inline s8 findMatchingController(int spawn_slot, int costume_id)
{
    s8 chr = Player_GetPlayerCharacter(spawn_slot);
    s32 matching_slot;

    for (matching_slot = 0; matching_slot < 6; matching_slot++) {
        if (Player_GetPlayerSlotType(matching_slot) != Gm_PKind_NA &&
            Player_GetFlagsBit1(matching_slot) == 0 &&
            chr == Player_GetPlayerCharacter(matching_slot) &&
            costume_id == (s32) Player_GetCostumeId(matching_slot))
        {
            return 1;
        }
    }
    return 0;
}

void fn_8016A4C8(void)
{
    struct lbl_8046B488_t* gp;
    s32 has_active_spawn;
    s32 spawn_enabled;
    f32 facing_dir;
    Vec3 spawn_pos;
    s32 spawn_slot;

    PAD_STACK(0xC4);

    gp = &lbl_8046B488;
    has_active_spawn = 0;
    if (lbl_8046B488.unk_10_b1) {
        spawn_enabled = 1;
    } else {
        spawn_enabled = 0;
    }
    if (spawn_enabled == 0) {
        return;
    }

    for (spawn_slot = 0; spawn_slot < 6; spawn_slot++) {
        if (Player_GetFlagsBit1(spawn_slot) != 0 &&
            Player_GetPlayerState(spawn_slot) == 0)
        {
            if (gm_80169384() > 0) {
                if (lbl_8046B488.x7 != 0) {
                    gp->x7 -= 1;
                }
                fn_8016B738(1);
                Player_80036D24(spawn_slot);
                lbl_8046B488.x1A6[spawn_slot] = gm_80169384();
                Player_SetFlagsBit1(spawn_slot);
                Player_SetTeam(spawn_slot, 4);
                Ground_801C2D24(getSpawnPointIndex(spawn_slot), &spawn_pos);
                spawn_pos.y = Stage_GetCamBoundsTopOffset();
                Player_80032768(spawn_slot, &spawn_pos);
                Player_SetSlottype(spawn_slot, Gm_PKind_Cpu);
                Player_SetPlayerCharacter(spawn_slot, gp->xA2[gm_80169384()]);
                Player_SetStocks(spawn_slot, 1);
                {
                    int costume_id = gp->x20[gm_80169384()];
                    Player_SetCostumeId(spawn_slot, costume_id);
                    Player_SetControllerIndex(
                        spawn_slot,
                        findMatchingController(spawn_slot, costume_id));
                }
                {
                    u8 more_flags = gp->xF;
                    Player_SetMoreFlagsBit6(spawn_slot, more_flags);
                }
                Player_SetMoreFlagsBit1(spawn_slot, 0U);
                if (spawn_pos.x >= 0.0f) {
                    facing_dir = -1.0f;
                } else {
                    facing_dir = 1.0f;
                }
                Player_SetFacingDirection(spawn_slot, facing_dir);
                Player_SetHUDDamage(spawn_slot, 0);
                Player_SetPlayerId(spawn_slot, spawn_slot);
                Player_SetFlagsBit0(spawn_slot, 0);
                Player_SetNametagSlotID(spawn_slot, 0x78);
                {
                    u8 cpu_level = gp->x6;
                    Player_SetPlayerAndEntityCpuLevel(spawn_slot,
                                                      (s32) cpu_level);
                }
                Player_SetPlayerAndEntityCpuType(spawn_slot, roll_cpu_type());
                if (lbl_8046B488.unk_10_b4) {
                    Player_SetFlagsBit5(spawn_slot, 1U);
                    Player_SetPlayerAndEntityCpuType(spawn_slot, 0x1B);
                }
                if (lbl_8046B488.unk_10_b6) {
                    Player_SetFlagsAEBit0(spawn_slot, 1U);
                } else {
                    Player_SetFlagsAEBit0(spawn_slot, 0U);
                }
                Player_SetFlagsBit6(spawn_slot, lbl_8046B488.unk_10_b5);
                {
                    f32 model_scale = gp->x1C;
                    Player_SetModelScale(spawn_slot, model_scale);
                }
                Player_SetAttackRatio(spawn_slot, fn_8016A4C8_attack_ratio());
                {
                    f32 defense_ratio = lbl_8046B488.x18;
                    Player_SetDefenseRatio(spawn_slot, defense_ratio);
                }
                if ((s32) gp->x8 > 1) {
                    Player_SetMoreFlagsBit5(spawn_slot, 1);
                } else {
                    Player_SetMoreFlagsBit5(spawn_slot, 0);
                }
                if (Player_GetPlayerCharacter(spawn_slot) == CKIND_KIRBY &&
                    gp->xE != 0)
                {
                    int tmp = gp->x124[gm_80169384()];
                    Player_SetUnk4D(spawn_slot, tmp);
                    Player_SetFlagsAEBit1(spawn_slot, 1);
                }
                if (((struct lbl_8046B488_event_player_init_cb_t*) gp)
                        ->event_player_init_cb != NULL)
                {
                    ((struct lbl_8046B488_event_player_init_cb_t*) gp)
                        ->event_player_init_cb(spawn_slot, lbl_8046B488.x7);
                }
                Player_SetStructFunc(spawn_slot, fn_8016A488);
                Player_80031AD0(spawn_slot);
                ifStatus_802F6508(spawn_slot);
                un_802FD28C(spawn_slot);
            }
        }
    }
    if ((s32) gp->x7 == 0) {
        s32 active_slot;
        active_slot = 0;
    scan_active_spawn:
        if (Player_GetPlayerSlotType(active_slot) != Gm_PKind_NA &&
            Player_GetFlagsBit1(active_slot) != 0 &&
            Player_GetStocks(active_slot) != 0)
        {
            has_active_spawn = 1;
        } else {
            active_slot += 1;
            if (active_slot < 6) {
                goto scan_active_spawn;
            }
        }
        if (has_active_spawn == 0) {
            lbl_8046B488.unk_10_b0 = 1;
            lbl_8046B488.unk_10_b1 = 0;
            if (gp->x1B8 != NULL && gp->x1B8(1) == 1) {
                gp->x1B8 = NULL;
            }
        }
    }
}

void gm_8016A92C(StartMeleeRules* arg0)
{
    lbl_8046B668.arr2[0] = -2;
    arg0->x58 = &lbl_8046B668;
}

bool gm_8016A944(void)
{
    if (gm_GetRules()->x58 != NULL) {
        return true;
    }
    return false;
}

UNK_T gm_8016A97C(void)
{
    return &M2C_FIELD(&lbl_8046B668, UNK_T*, 0x1C);
}

struct lbl_8046B668_t* gm_8016A98C(void)
{
    return &lbl_8046B668;
}

int gm_8016A998(s8 arg0, s8 arg1)
{
    int i;
    struct lbl_8046B668_t* ptr = gm_8016A98C();
    for (i = 0; i < 27; i++) {
        if (ptr->arr2[i] == -2) {
            ptr->arr2[i + 1] = -2;
            ptr->arr2[i] = arg1;
            ptr->arr1[i] = (u8) arg0;
            return i;
        }
    }
    return -1;
}

int gm_8016A9E8(u8 arg0, s8 arg1)
{
    int i;
    int found;
    struct lbl_8046B668_t* ptr = gm_8016A98C();

    found = -1;
    for (i = 0; i < 27; i++) {
        if (ptr->arr2[i] == -2) {
            found = i;
            break;
        }
    }
    if (found != -1) {
        for (i = found; i >= 0; i--) {
            ptr->arr2[i + 1] = ptr->arr2[i];
            ptr->arr1[i + 1] = ptr->arr1[i];
        }
        ptr->arr2[0] = arg1;
        ptr->arr1[0] = arg0;
        found++;
    }
    return found;
}

bool gm_8016AC44(s8 ckind, s8 costume_id)
{
    s32 idx;
    s32 i;

    if ((gm_GetRules()->x58 != NULL ? 1 : 0) == 1) {
        struct lbl_8046B668_t* ptr = &lbl_8046B668;
        idx = -1;
        for (i = 0; i < 27; i++) {
            if (ptr->arr2[i] == -2) {
                idx = i;
                break;
            }
        }
        if (idx != -1) {
            for (i = idx; i >= 0; i--) {
                if (ptr->arr2[i] == costume_id && ckind == ptr->arr1[i]) {
                    ptr->arr2[i] = -1;
                    return true;
                }
            }
        }
    }
    return false;
}
