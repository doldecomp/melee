#include <Runtime/platform.h>

#include <melee/gm/forward.h>
#include <melee/gm/gm_18A1.h>
#include <melee/gm/gm_unsplit.h>
#include <melee/gm/gmregclear.h>
#include <melee/gm/types.h>
#include <melee/ty/toy.h>

typedef struct lbl_804706D8_t {
    s16 x0;
    u8 x2;
    u8 x3;
} lbl_804706D8_t;

static lbl_804706D8_t lbl_804706D8[12];

typedef struct RegClearCharEntry {
    /* 0x00 */ u8 x0;
    /* 0x01 */ u8 x1;
    /* 0x02 */ u8 x2;
    /* 0x03 */ u8 x3;
    /* 0x04 */ f32 x4;
    /* 0x08 */ f32 x8;
} RegClearCharEntry;

StartMeleeData gmClassic_80472AF8;
MatchExitInfo gmClassic_8047086C;
DebugGameOverData gmClassic_80470850;
CSSData gmClassic_80470708;

void gm_8017DB58(struct Unk1PData_x24* arg0)
{
    int i;
    for (i = 0; i < 3; i++) {
        arg0[i].ckind = ChKind_None;
    }
}

u8 gm_8017DB6C(gm_8017DB6C_arg0_t* arg0, int index)
{
    return arg0[index].x0;
}

u8 gm_8017DB78(gm_8017DB6C_arg0_t* arg0, int index)
{
    return arg0[index].x1;
}

s32 gm_8017DB88(void* arg0, u8 arg1, s32 arg2, s32 arg3, u8* arg4, u8 arg5,
                u8 (*arg6)(s32, s32, u8), u8 (*arg7)(s32, s32, u8),
                u8 (*arg8)(s32, s32, u8), f32 (*arg9)(s32, s32),
                f32 (*arg10)(s32, s32))
{
    u8 chars[4];
    s32 val;
    f32 fval;

    {
        u8* p;
        RegClearCharEntry* out;
        s32 i;
        s32 count;

        count = fn_8017DE54(arg1, arg4);
        chars[1] = 0x21;
        out = arg0;
        chars[2] = 0x21;
        p = chars;
        i = 0;
        chars[3] = 0x21;
        chars[0] = arg5;
        for (; i < count; i++) {
            p[1] = fn_8017D9C0(chars, arg4);
            out->x0 = p[1];
            if (arg8 != NULL) {
                val = arg8(arg3, arg2, (u8) i);
            } else {
                val = 0;
            }
            out->x1 = val;
            if (arg6 != NULL) {
                val = arg6(arg3, arg2, (u8) i);
            } else {
                val = 0;
            }
            out->x2 = val;
            if (arg7 != NULL) {
                val = arg7(arg3, arg2, (u8) i);
            } else {
                val = 0;
            }
            out->x3 = val;
            if (arg9 != NULL) {
                fval = arg9(arg3, arg2);
            } else {
                fval = 0.0f;
            }
            out->x4 = fval;
            if (arg10 != NULL) {
                fval = arg10(arg3, arg2);
            } else {
                fval = 0.0f;
            }
            out->x8 = fval;
            p++;
            out++;
        }
        for (; i < 3; i++) {
            ((RegClearCharEntry*) arg0)[i].x0 = 0x21;
        }
        return count;
    }
}
s32 fn_8017DD7C(PlayerInitData* arg0, Unk1PData_x24* arg1, u8 arg2)
{
    s32 index = 1;
    int i;
    for (i = 0; i < 3; i++) {
        if (arg1[i].ckind != ChKind_None) {
            gm_SetupPlayerDefaults(&arg0[index]);
            arg0[index].ckind = arg1[i].ckind;
            arg0[index].slot_type = 1;
            arg0[index].stocks = 1;
            arg0[index].team = arg0->team;
            arg0[index].color = arg1[i].color;
            arg0[index].cpu_kind = arg1[i].cpu_kind;
            arg0[index].cpu_level = arg1[i].cpu_level;
            arg0[index].attack_ratio = arg1[i].attack_ratio;
            arg0[index].defense_ratio = arg1[i].defense_ratio;
            arg0[index].xD_b1 = 1;
            if (arg0[index].ckind == CKind_GKoops) {
                arg0[index].xC_b1 = 0;
            }
            index++;
        }
    }
    return index - 1;
}

s32 fn_8017DE54(u8 arg0, u8* arg1)
{
    u8* p;
    s32 count;

    if (arg0 & 0x20) {
        return 0;
    }
    if (arg0 & 0x10) {
        count = 0;
        if ((s32) arg1[0] != 0x21) {
            count = 1;
        }
        p = &arg1[1];
        if ((s32) *p != 0x21) {
            count += 1;
        }
        if ((s32) p[1] != 0x21) {
            count += 1;
        }
        return 3 - count;
    }
    if (arg0 & 2) {
        return 2;
    }
    return 0;
}

Unk1PData* fn_8017DEC8(int arg0)
{
    switch (arg0) {
    case 0:
        return &gm_GetAdventureData()->x0;
    case 1:
        return &gm_GetAllStarData()->x0;
    case 2:
        return &gm_80473A18.x0;
    default:
        return NULL;
    }
}

Unk1PData* fn_8017DF28(void)
{
    switch (gm_GetCurrentGameMode()) {
    case GM_CLASSIC:
        return &gm_GetAllStarData()->x0;
    case GM_ADVENTURE:
        return &gm_GetAdventureData()->x0;
    case GM_ALLSTAR:
        return &gm_80473A18.x0;
    default:
        return NULL;
    }
}

u8 fn_8017DF90(void)
{
    switch (gm_GetCurrentGameMode()) {
    case GM_CLASSIC:
        return 1;
    case GM_ADVENTURE:
        return 0;
    case GM_ALLSTAR:
        return 2;
    default:
        return 3;
    }
}

int gm_8017DFF4(int arg0)
{
    Unk1PData* var_r3 = fn_8017DEC8(arg0);
    if (var_r3 != NULL) {
        return var_r3->x0.cpu_level;
    }
    return -1;
}

int gm_8017E068(void)
{
    Unk1PData* var_r3 = fn_8017DF28();
    if (var_r3 != NULL) {
        return var_r3->x0.cpu_level;
    }
    return -1;
}

int fn_8017E0E4(void)
{
    Unk1PData* var_r3 = fn_8017DF28();
    if (var_r3 != NULL) {
        return var_r3->xC.xC;
    }
    return -1;
}

bool fn_8017E160(void)
{
    Unk1PData* var_r3 = fn_8017DF28();
    struct Unk1PData_xC* temp_r3_2;

    if (var_r3 != NULL) {
        int i;
        for (i = 0; i < 3; i++) {
            if (var_r3->xC.x24[i].ckind != ChKind_None) {
                return true;
            }
        }
        return false;
    }
    return false;
}

void fn_8017E21C(void)
{
    int i;
    for (i = 0; i < 12; i++) {
        lbl_804706D8[i].x0 = -1;
    }
}

s8 gm_8017E280(u16 arg0, u32 arg1)
{
    lbl_804706D8_t* var_r7 = lbl_804706D8;
    s32 index;
    index = 0;
    for (index = 0; index < 12; index++) {
        if (arg0 == var_r7[index].x0) {
            var_r7[index].x2 += arg1;
            return var_r7[index].x2;
        }
    }
    index = 0;
    for (index = 0; index < 12; index++) {
        if (var_r7[index].x0 == -1) {
            var_r7[index].x0 = arg0;
            var_r7[index].x2 = arg1;
            return (u8) arg1;
        }
    }
    return -1;
}

int fn_8017E318(void)
{
    int i;
    int sum = 0;
    for (i = 0; i < 12; i++) {
        if (lbl_804706D8[i].x0 != -1) {
            sum += lbl_804706D8[i].x2;
        }
    }
    return sum;
}

void fn_8017E3C8(void)
{
    int i = 0;
    PAD_STACK(8);
    for (i = 0; i < 12; i++) {
        if (lbl_804706D8[i].x0 != -1) {
            Toy_SetUnlockState(lbl_804706D8[i].x0, lbl_804706D8[i].x2);
        }
    }
}
