#include "gm_17BA.h"

#include "gm_unsplit.h"

#include <melee/gm/gmmain_lib.h>
#include <melee/gm/gmresult.h>
#include <melee/gm/types.h>
#include <melee/lb/lblanguage.h>

static const char* lbl_803D79D0[] = {
    "１Ｐ",
    "２Ｐ",
    "３Ｐ",
    "４Ｐ",
};

static const char* lbl_803D79E0[] = {
    "Ｐ１",
    "Ｐ２",
    "Ｐ３",
    "Ｐ４",
};

int fn_8017BACC(int arg0)
{
    MatchEnd* m = fn_80174274();
    int result;
    if ((result = m->player_standings[arg0].x9C) > 999999) {
        result = 999999;
    } else if (result < -999999) {
        result = -999999;
    }
    return result;
}

int fn_8017BB30(int arg0)
{
    MatchEnd* m = fn_80174274();
    int result;
    if ((result = m->player_standings[arg0].xA0) > 999999) {
        result = 999999;
    } else if (result < -999999) {
        result = -999999;
    }
    return result;
}

static inline const char* fn_8017BB94_inline(int arg0, int target)
{
    MatchEnd* temp_r3_2 = fn_80174274();
    int var_r3;

    if (arg0 == target) {
        var_r3 = -1;
    } else if (temp_r3_2->player_standings[target].slot_type != Gm_PKind_NA) {
        var_r3 = fn_8017AD04(temp_r3_2->player_standings[arg0].kills[target],
                             999999);
    } else {
        var_r3 = -1;
    }
    if (var_r3 != -1) {
        u32 temp_r3 = fn_80174274()->player_standings[target].x4;
        if (temp_r3 == 0x78) {
            if (lbLang_IsSavedLanguageUS()) {
                return lbl_803D79E0[target];
            } else {
                return lbl_803D79D0[target];
            }
        } else {
            struct NameTagData* tmp = GetPersistentNameData(temp_r3);
            return tmp->namedata;
        }
    }
    return NULL;
}

const char* fn_8017BB94(int arg0)
{
    PAD_STACK(8);
    return fn_8017BB94_inline(arg0, 0);
}

const char* fn_8017BC50(int arg0)
{
    PAD_STACK(8);
    return fn_8017BB94_inline(arg0, 1);
}

const char* fn_8017BD0C(int arg0)
{
    PAD_STACK(8);
    return fn_8017BB94_inline(arg0, 2);
}

const char* fn_8017BDC8(int arg0)
{
    PAD_STACK(8);
    return fn_8017BB94_inline(arg0, 3);
}
