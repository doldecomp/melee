#include "lbaudio_ax.static.h"

#include "baselib/forward.h"
#include <melee/ft/forward.h>

#include <m2c_macros.h>
#include <baselib/axdriver.h>
#include <baselib/gobjplink.h>
#include <baselib/gobjproc.h>
#include <baselib/gobjuserdata.h>
#include <baselib/synth.h>
#include <melee/cm/camera.h>
#include <melee/ft/ftlib.h>
#include <melee/gr/stage.h>
#include <melee/it/it_26B1.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lblanguage.h>

extern s8 flags_arr_803BB800[0x62];

typedef bool (*lbl_803BCA24_fn)(HSD_GObj*);

lbl_803BCA24_fn lbl_803BCA24[] = {
    fn_800251EC, fn_800253D8, fn_800256BC, fn_800259A0, fn_800259EC,
    fn_80025A98, fn_80025B44, fn_80025CBC, fn_80025E38, fn_80025E38,
};

int lbAudioAx_8002305C(int arg0, int arg1)
{
    static const int size = ARRAY_SIZE(unk_arr_803BC4A0);
    if (arg0 >= 0 && arg0 < size) {
        return unk_arr_803BC4A0[arg0][arg1];
    }
    return 0x62;
}

int lbAudioAx_80023090(int idx)
{
    if (idx < 0) {
        return 0;
    }
    if (idx >= 0x62) {
        return 0;
    }
    return flags_arr_803BB800[idx];
}

int lbAudioAx_800230C8(int i, int* lo, int* hi)
{
    if (i < 0) {
        return 1;
    }
    if (i >= 0x37) {
        return 1;
    }
    if (lo != NULL) {
        *lo = s32_arr_803BB8D4[i][0];
    }
    if (hi != NULL) {
        *hi = s32_arr_803BB8D4[i][1];
    }
    return 0;
}

int lbAudioAx_80023130(int arg0)
{
    int i;
    if (arg0 >= 0 && arg0 < 0x83D60) {
        for (i = 0; i < 0x37; i++) {
            if (s32_arr_803BB8D4[i][0] <= arg0 &&
                arg0 <= s32_arr_803BB8D4[i][1])
            {
                return i;
            }
        }
    }
    return 0x37;
}

int lbAudioAx_80023220(int idx)
{
    if (idx >= 0 && idx < 0x37) {
        return s32_arr_803BB5D0[idx][3];
    }
    return 0;
}

void fn_80023254(s32 arg0)
{
    int local_arr[0x38];
    int* arr_b44;
    int* local_ptr;
    s8(*arr_5d0)[4];
    int (*arr_4e4)[2];
    int count;
    int j;
    int n;
    int* shift_ptr;
    int i;

    arr_b44 = lbl_80433B44;
    local_ptr = local_arr;
    for (i = 0; i < 7; i++) {
        arr_b44[0] = 0x37;
        local_ptr[0] = 0;
        arr_b44[1] = 0x37;
        local_ptr[1] = 0;
        arr_b44[2] = 0x37;
        local_ptr[2] = 0;
        arr_b44[3] = 0x37;
        local_ptr[3] = 0;
        arr_b44[4] = 0x37;
        local_ptr[4] = 0;
        arr_b44[5] = 0x37;
        local_ptr[5] = 0;
        arr_b44[6] = 0x37;
        local_ptr[6] = 0;
        arr_b44[7] = 0x37;
        arr_b44 += 8;
        local_ptr[7] = 0;
        local_ptr += 8;
    }

    arr_b44 = lbl_80433B44;

    for (count = 0; count <= 0x37; count++) {
        local_ptr = local_arr;
        arr_5d0 = s32_arr_803BB5D0;
        arr_4e4 = offsets_arr_803BC4E4;
        j = 0;

        do {
            if (arg0 != (s8) (*arr_5d0)[2]) {
                goto next;
            }
            if (*local_ptr != 0) {
                goto next;
            }

            if ((u32) offsets_arr_803BC4E4[*arr_b44][0] >= (u32) (*arr_4e4)[0])
            {
                goto next;
            }

            if (count < 0x37) {
                shift_ptr = &lbl_80433B44[0x37];
                n = 0x37 - count;

                if ((n >> 3) != 0) {
                    i = n >> 3;
                    do {
                        shift_ptr[0] = shift_ptr[-1];
                        shift_ptr[-1] = shift_ptr[-2];
                        shift_ptr[-2] = shift_ptr[-3];
                        shift_ptr[-3] = shift_ptr[-4];
                        shift_ptr[-4] = shift_ptr[-5];
                        shift_ptr[-5] = shift_ptr[-6];
                        shift_ptr[-6] = shift_ptr[-7];
                        shift_ptr[-7] = shift_ptr[-8];
                        shift_ptr -= 8;
                        i--;
                    } while (i != 0);
                    n &= 7;
                    if (n == 0) {
                        goto insert;
                    }
                }

                i = n;
                do {
                    shift_ptr[0] = shift_ptr[-1];
                    shift_ptr--;
                    i--;
                } while (i != 0);
            }

        insert:
            *arr_b44 = j;
            *local_ptr = 1;

        next:
            j++;
            arr_5d0++;
            local_ptr++;
            arr_4e4++;
        } while (j <= 0x37);

        arr_b44++;
    }
}

/// #lbAudioAx_800233EC

int lbAudioAx_80023694(void)
{
    HSD_AudioSFXKeyOffAll();
    return -1;
}

int lbAudioAx_800236B8(int arg0)
{
    AXDriverKeyOff(arg0);
    return -1;
}

int lbAudioAx_800236DC(void)
{
    AXDriverStop();
    lbl_804D6418 = 0;
    lbl_803BB300[0] = '\0';
    return -1;
}

bool lbAudioAx_80023710(int arg0)
{
    return AXDriver_8038D9D8(arg0);
}

bool lbAudioAx_80023730(void)
{
    return AXDriver_8038EA18();
}

int fn_80023750(int arg0, int arg1, int arg2, int arg3, int arg4)
{
    arg1 *= 2;
    if (arg1 < 0) {
        arg1 = 0;
    }
    if (arg1 > 0xFF) {
        arg1 = 0xFF;
    }
    arg2 *= 2;
    if (arg2 < 0) {
        arg2 = 0;
    }
    if (arg2 > 0xFF) {
        arg2 = 0xFF;
    }
    return AXDriver_8038CFF4(arg0, arg1, arg2, arg3, arg4);
}

int lbAudioAx_800237A8(int sfx_id, int sfx_vol, int sfx_pan)
{
    if (sfx_id >= 0x83D61) {
        return fn_80023750(0x83D60, 0, 0x40, 0, 7);
    } else {
        return fn_80023750(sfx_id, sfx_vol, sfx_pan, 0, 7);
    }
}

int lbAudioAx_80023870(int arg0, int arg1, int arg2, int arg3)
{
    if (arg3 == 0) {
        return lbAudioAx_800237A8(arg0, arg1, arg2);
    }
    if (arg0 == 0x83D61) {
        HSD_AudioSFXKeyOffTrack(arg3);
        return -1;
    }
    return fn_80023750(arg0, arg1, arg2, arg3, 7);
}

void lbAudioAx_8002392C(void)
{
    lbArchive_LoadSymbols("LbAd.dat", &lbl_804D6454, "lbAudioLoadData", 0);
}

static inline int* lbAudioAx_80023968_inline(int arg0)
{
    if (lbLang_IsSettingUS()) {
        if (lbLang_IsSavedLanguageUS()) {
            return lbl_804D6454->x4[arg0];
        } else {
            return lbl_804D6454->xC[arg0];
        }
    } else {
        if (lbLang_IsSavedLanguageUS()) {
            return lbl_804D6454->x8[arg0];
        } else {
            return lbl_804D6454->x0[arg0];
        }
    }
}

int lbAudioAx_80023968(int arg0)
{
    int count = 0;
    int* var_r4;

    if (arg0 < 0 && arg0 >= 0x1E) {
        return -1;
    }

    var_r4 = lbAudioAx_80023968_inline(arg0);
    while (*var_r4 != 0x83D60) {
        var_r4++;
        count++;
    }
    return count;
}

int lbAudioAx_80023A44(int arg0, int arg1)
{
    int* var_r3;
    if (arg0 < 0 && arg0 >= 0x1E) {
        return 0x83D60;
    }
    if (arg1 < 0 && 0x83D60 <= arg1) {
        return 0x83D60;
    }

    var_r3 = lbAudioAx_80023968_inline(arg0);
    return var_r3[arg1];
}

/// #lbAudioAx_80023B24

bool fn_80023ED4(const char* arg0, int arg1, int arg2)
{
    int var_r0 = arg1 * 2;
    if (var_r0 < 0) {
        var_r0 = 0;
    }
    if (var_r0 > 0xFF) {
        var_r0 = 0xFF;
    }
    if (arg2 < 0) {
        arg2 = 0;
    }
    if (arg2 >= 9) {
        arg2 = 8;
    }
    return AXDriver_8038E8EC(arg0, var_r0, arg2);
}

u8 data_pad_0[0x1014 - 0xC80] = { 0 };
char* lbl_803BC314[] = {
    "1p_qk.hps",      "akaneia.hps",    "baloon.hps",     "bigblue.hps",
    "castle.hps",     "continue.hps",   "corneria.hps",   "docmari.hps",
    "ending.hps",     "famidemo.hps",   "ff_1p01.hps",    "ff_1p02.hps",
    "ff_bad.hps",     "ff_dk.hps",      "ff_emb.hps",     "ff_flat.hps",
    "ff_fox.hps",     "ff_fzero.hps",   "ff_good.hps",    "ff_ice.hps",
    "ff_kirby.hps",   "ff_link.hps",    "ff_mario.hps",   "ff_nes.hps",
    "ff_poke.hps",    "ff_samus.hps",   "ff_step1.hps",   "ff_step2.hps",
    "ff_step3.hps",   "ff_yoshi.hps",   "flatzone.hps",   "fourside.hps",
    "gameover.hps",   "garden.hps",     "greatbay.hps",   "greens.hps",
    "howto.hps",      "howto_s.hps",    "hyaku.hps",      "hyaku2.hps",
    "icemt.hps",      "inis1_01.hps",   "inis1_02.hps",   "inis2_01.hps",
    "inis2_02.hps",   "intro_es.hps",   "intro_nm.hps",   "item_h.hps",
    "item_s.hps",     "izumi.hps",      "kongo.hps",      "kraid.hps",
    "menu01.hps",     "menu02.hps",     "menu3.hps",      "mrider.hps",
    "mutecity.hps",   "old_dk.hps",     "old_kb.hps",     "old_ys.hps",
    "onetto.hps",     "onetto2.hps",    "opening.hps",    "pokesta.hps",
    "pstadium.hps",   "pura.hps",       "rcruise.hps",    "s_info1.hps",
    "s_info2.hps",    "s_info3.hps",    "s_new1.hps",     "s_new2.hps",
    "s_newcom.hps",   "s_select.hps",   "saria.hps",      "shrine.hps",
    "siren.hps",      "smari3.hps",     "sp_end.hps",     "sp_giga.hps",
    "sp_metal.hps",   "sp_zako.hps",    "swm_15min.hps",  "target.hps",
    "venom.hps",      "vl_battle.hps",  "vl_castle.hps",  "vl_corneria.hps",
    "vl_cosmos.hps",  "vl_figure1.hps", "vl_figure2.hps", "vl_fzero.hps",
    "vl_last_v2.hps", "vs_hyou1.hps",   "vs_hyou2.hps",   "yorster.hps",
    "ystory.hps",     "zebes.hps",      "testnz.hps",
};

static inline const char* lbAudioAx_80023F28_inline0(int arg0)
{
    if (arg0 < 0) {
        return NULL;
    } else if (arg0 >= 0x62) {
        return NULL;
    } else {
        strcpy(&lbl_803BB380[lbl_804D38D4], lbl_803BC314[arg0]);
        return lbl_803BB380;
    }
}

static inline bool lbAudioAx_80023F28_inline1(const char* var_r3)
{
    bool result;
    if (var_r3 == NULL || var_r3[0] == '\0') {
        result = true;
    } else if (strcmp(lbl_803BB300, var_r3) != 0) {
        lbAudioAx_800236DC();
        strcpy(lbl_803BB300, var_r3);
        fn_80023ED4(lbl_803BB300, 0x7F, 1);
        result = false;
    } else {
        result = true;
    }
    return result;
}

bool lbAudioAx_80023F28(s32 arg0)
{
    const char* var_r3;

    if (arg0 < 0 || arg0 >= 0x62) {
        return true;
    }
    if (!(var_r3 = lbAudioAx_80023F28_inline0(arg0))) {
        return true;
    }
    return lbAudioAx_80023F28_inline1(var_r3);
}

u8 data_pad[0x478] = { 0 };
static struct lbl_803BC918_t {
    int x0;
    int x4;
    int x8;
} lbl_803BC918[] = {
    { 0xAC, 0x13, 3 }, { 0xAD, 0x14, 3 }, { 0xAE, 0x00, 3 }, { 0xAF, 0x00, 3 },
    { 0xB0, 0x15, 3 }, { 0xB1, 0x00, 2 }, { 0xC1, 0x00, 2 }, { 0xBC, 0x00, 2 },
    { 0xDB, 0x00, 3 }, { 0xDC, 0x00, 3 }, { 0xDD, 0x00, 3 },
};

void lbAudioAx_80024030(s32 arg0)
{
    if (arg0 < 0xB) {
        fn_80023750(lbl_803BC918[arg0].x0, 0x7F, 0x40, lbl_803BC918[arg0].x4,
                    lbl_803BC918[arg0].x8);
    }
}

int lbAudioAx_800240B4(int arg0)
{
    return fn_80023750(arg0, 0x7F, 0x40, 0, 5);
}

int lbAudioAx_8002411C(int arg0)
{
    return fn_80023750(arg0, 0x7F, 0x40, 0, 6);
}

/// #lbAudioAx_8002411C

int lbAudioAx_80024184(int arg0, int arg1, int arg2, int arg3)
{
    switch (arg0) {
    case 0x56:
        arg3 = 9;
        break;
    case 0x57:
        arg3 = 8;
        break;
    case 0x58:
        arg3 = 7;
        break;
    case 0x59:
        arg3 = 0xC;
        break;
    case 0x5A:
        arg3 = 0xB;
        break;
    case 0x5B:
        arg3 = 0xA;
        break;
    case 0x6F:
        arg3 = 0xD;
        break;
    case 0x70:
        arg3 = 0xE;
        break;
    case 0x71:
        arg3 = 0xF;
        break;
    case 0x65:
        arg3 = 0x10;
        break;
    case 0x66:
        arg3 = 0x11;
        break;
    case 0x67:
        arg3 = 0x12;
        break;
    case 0x54:
        arg3 = 0x17;
        break;
    case 0x12E:
        arg3 = 0x18;
        break;
    case 0x20D:
        arg3 = arg3 != -1 ? arg3 : 0;
        break;
    default:
        arg3 = 0;
        break;
    }
    return fn_80023750(arg0, arg1, arg2, arg3, 7);
}

int lbAudioAx_80024304(int arg0)
{
    int var_r6;
    switch (arg0) {
    case 0x8A:
    case 0x8B:
    case 0x8C:
        var_r6 = 0x16;
        arg0 = 0x8B;
        break;
    default:
        var_r6 = 0;
        break;
    }

    return fn_80023750(arg0, 0x7F, 0x40, var_r6, 7);
}

int lbAudioAx_8002438C(int arg0)
{
    return fn_80023750(arg0, 0x7F, 0x40, 0, 8);
}

/// #lbAudioAx_800243F4

/// #fn_800244F4

void lbAudioAx_800245D4(int arg0)
{
    if (arg0 < 0) {
        arg0 = 0;
    }
    if (arg0 > 0x7F) {
        arg0 = 0x7F;
    }
    lbl_804D387C = arg0;
}

int lbAudioAx_800245F4(int arg0)
{
    if (arg0 < 0) {
        arg0 = 0;
    }
    if (arg0 > 0x7F) {
        arg0 = 0x7F;
    }
    return lbl_804D388C = arg0;
}

void lbAudioAx_80024614(int arg0)
{
    if (arg0 < 0) {
        arg0 = 0;
    }
    if (arg0 > 0x7F) {
        arg0 = 0x7F;
    }
    lbl_804D388C = arg0;
}

void lbAudioAx_80024634(int arg0)
{
    if (arg0 < 0) {
        arg0 = 0;
    }
    if (arg0 > 0xFF) {
        arg0 = 0xFF;
    }
    lbl_804D38D8 = arg0;
}

void fn_80024654(int arg0)
{
    f32 temp_f31;

    lbl_804D3880 = (lbl_804D387C / 127.0f) * lbl_804D38C0;
    if (arg0 == 1) {
        HSD_SynthStreamSetVolume(lbl_804D3880);
        lbl_804D63F0 = lbl_804D3880;
    } else if (lbl_804D63F0 != lbl_804D3880) {
        HSD_SynthStreamSetVolume(lbl_804D3880);
        lbl_804D63F0 = lbl_804D3880;
    }
    temp_f31 = lbl_804D38CC / 127.0f;
    lbl_804D38B0 = lbl_804D38C8;
    lbl_804D38B4 = lbl_804D38C8 * temp_f31;
    lbl_804D3898 = (u8) (lbl_804D38B4 * (0.88f * (lbl_804D388C * 2)));
    if (arg0 == 1) {
        HSD_SynthSFXUpdateAllVolume((u8) lbl_804D3898, 4, 2);
        HSD_SynthSFXUpdateAllVolume((u8) lbl_804D3898, 4, 3);
        lbl_804D63FC = lbl_804D3898;
    } else if (lbl_804D63FC != lbl_804D3898) {
        HSD_SynthSFXUpdateAllVolume((u8) lbl_804D3898, 4, 2);
        HSD_SynthSFXUpdateAllVolume((u8) lbl_804D3898, 4, 3);
        lbl_804D63FC = lbl_804D3898;
    }
    lbl_804D38B8 = temp_f31 * (lbl_804D38C8 * lbl_804D38E4);
    lbl_804D38A0 = (u8) (lbl_804D38B8 * (0.88f * (lbl_804D388C * 2)));
    if (arg0 == 1) {
        HSD_SynthSFXUpdateAllVolume((u8) lbl_804D38A0, 4, 4);
        HSD_SynthSFXUpdateAllVolume((u8) lbl_804D38A0, 4, 5);
        HSD_SynthSFXUpdateAllVolume((u8) lbl_804D38A0, 4, 6);
        HSD_SynthSFXUpdateAllVolume((u8) lbl_804D38A0, 4, 7);
        lbl_804D6400 = lbl_804D38A0;
    } else if (lbl_804D6400 != lbl_804D38A0) {
        HSD_SynthSFXUpdateAllVolume((u8) lbl_804D38A0, 4, 4);
        HSD_SynthSFXUpdateAllVolume((u8) lbl_804D38A0, 4, 5);
        HSD_SynthSFXUpdateAllVolume((u8) lbl_804D38A0, 4, 6);
        HSD_SynthSFXUpdateAllVolume((u8) lbl_804D38A0, 4, 7);
        lbl_804D6400 = lbl_804D38A0;
    }
    lbl_804D38BC = lbl_804D38C8 * lbl_804D38E4;
    lbl_804D38A8 = (u8) (lbl_804D38BC * (0.88f * (lbl_804D388C * 2)));
    if (arg0 == 1) {
        HSD_SynthSFXUpdateAllVolume((u8) lbl_804D38A8, 4, 8);
        lbl_804D6404 = lbl_804D38A8;
    } else if (lbl_804D6404 != lbl_804D38A8) {
        HSD_SynthSFXUpdateAllVolume((u8) lbl_804D38A8, 4, 8);
        lbl_804D6404 = lbl_804D38A8;
    }
    lbl_804D38AC = temp_f31 * (lbl_804D38EC * (lbl_804D38C4 * lbl_804D38E8));
    lbl_804D3888 = (u8) (lbl_804D38AC * (lbl_804D3884 * 2));
    if (arg0 == 1) {
        HSD_SynthSFXUpdateAllVolume((u8) lbl_804D3888, 4, 1);
        lbl_804D63F4 = lbl_804D3888;
    } else if (lbl_804D63F4 != lbl_804D3888) {
        HSD_SynthSFXUpdateAllVolume((u8) lbl_804D3888, 4, 1);
        lbl_804D63F4 = lbl_804D3888;
    }
    lbl_804D38E0 = lbl_804D38D8;
    if (arg0 == 1) {
        AXDriver_8038D914(5, 1, 0x20);
        AXDriver_8038D914(6, 1, 0x20);
        AXDriver_8038D914(8, 1, (u8) lbl_804D38D8);
        AXDriver_8038D914(7, 1, (u8) lbl_804D38D8);
        lbl_804D38DC = lbl_804D38E0;
        return;
    }
    if (lbl_804D38DC != lbl_804D38E0) {
        AXDriver_8038D914(5, 1, 0x20);
        AXDriver_8038D914(6, 1, 0x20);
        AXDriver_8038D914(8, 1, (u8) lbl_804D38D8);
        AXDriver_8038D914(7, 1, (u8) lbl_804D38D8);
        lbl_804D38DC = lbl_804D38E0;
    }
}

void lbAudioAx_80024B1C(int arg0, int arg1)
{
    if (arg1 < 0) {
        arg1 = 0;
    }
    if (arg1 > 0x7F) {
        arg1 = 0x7F;
    }
    AXDriver_8038D2B4(arg0, arg1 * 2);
}

void lbAudioAx_80024B58(int arg0, int arg1)
{
    if (arg1 < 0) {
        arg1 = 0;
    }
    if (arg1 > 0x7F) {
        arg1 = 0x7F;
    }
    AXDriver_8038D3B8(arg0, arg1 * 2);
}

int lbAudioAx_80024B94(int arg0, int arg1)
{
    int const limit = 0x4B0;
    if (arg1 < -limit) {
        arg1 = -limit;
    }
    if (arg1 > limit) {
        arg1 = limit;
    }
    return AXDriver_8038D4E4(arg0, arg1);
}

bool lbAudioAx_80024BD0(void)
{
    u32 temp_r3 = HSD_SynthGetSoundMode();
    lbl_804D3874 = temp_r3;
    return temp_r3 == 1 ? false : true;
}

static int lbl_804D3928[2] = { 1, 0 };

int lbAudioAx_80024C08(int arg0)
{
    switch (arg0) {
    case 0:
    case 1:
        if (lbl_804D3874 != lbl_804D3928[arg0]) {
            lbl_804D3874 = lbl_804D3928[arg0];
            if (lbl_804D3928[arg0] != 1U && lbl_804D3928[arg0] != 0U) {
                return false;
            }
            HSD_SynthSetSoundMode(lbl_804D3928[arg0]);
            return true;
        }
        return true;
    default:
        return false;
    }
}

void lbAudioAx_80024C84(void)
{
    lbl_804D640C = 0;
    lbl_804D6410 = false;
    lbl_804D38E4 = 1.0F;
    lbl_804D38E8 = 1.0F;
    lbl_804D38EC = 1.0F;
    lbl_804D6414 = 0;
    lbl_804D6418 = 0;
    lbl_804D6420 = 0;
    lbl_804D6424 = 0;
    lbl_804D6428 = 0;
    lbl_804D642C = 0;
    lbl_804D38F0 = -1;
    lbl_804D38F4 = -1;
    lbl_804D6430 = 0;
    lbl_804D6434 = 0;
    HSD_AudioSFXKeyOffTrack(5);
    HSD_AudioSFXKeyOffTrack(6);
    lbl_804D641C = 0;
    lbl_804D38C0 = 1.0F;
    lbl_804D38AC = 1.0F;
    lbl_804D38B0 = 1.0F;
    lbl_804D38B4 = 1.0F;
    lbl_804D38B8 = 1.0F;
    lbl_804D38BC = 1.0F;
    AXDriver_8038E844(5);
    AXDriver_8038E844(6);
    AXDriver_8038E844(8);
    AXDriver_8038E844(7);
    lbl_804D38D8 = 1;
    lbl_804D38CC = 0x7F;
}

void lbAudioAx_80024D50(void)
{
    lbAudioAx_80024C84();
    lbl_804D641C = 1;
}

void lbAudioAx_80024D78(int arg0)
{
    lbl_804D38D8 =
        (s32) s32_arr_803BB6B0[Stage_8022519C(Stage_80225194())][arg0];
}

/// #lbAudioAx_80024DC4

void lbAudioAx_80024E50(bool arg0)
{
    lbl_804D6410 = arg0;
    if (arg0) {
        AXDriverPause();
    } else {
        AXDriverResume();
    }
}

void lbAudioAx_80024E84(bool arg0)
{
    lbl_804D640C = arg0;
    if (arg0) {
        lbl_804D38E4 = 0.2F;
        lbl_804D38E8 = 0.2F;
        AXDriver_8038E6C0(5);
        AXDriver_8038E6C0(6);
        AXDriver_8038E6C0(8);
        AXDriver_8038E6C0(7);
    } else {
        lbl_804D38E4 = 1.0F;
        lbl_804D38E8 = 1.0F;
        AXDriver_8038E844(5);
        AXDriver_8038E844(6);
        AXDriver_8038E844(8);
        AXDriver_8038E844(7);
    }
}

void lbAudioAx_80024F08(void)
{
    HSD_SynthStreamSetVolume(0.0F);
    AXDriver_8038E6C0(2);
    AXDriver_8038E6C0(3);
    AXDriver_8038E6C0(4);
    AXDriver_8038E6C0(5);
    AXDriver_8038E6C0(6);
    AXDriver_8038E6C0(7);
    AXDriver_8038E6C0(8);
    AXDriver_8038E6C0(9);
}

void lbAudioAx_80024F6C(void)
{
    HSD_SynthStreamSetVolume(lbl_804D3880);
    AXDriver_8038E844(2);
    AXDriver_8038E844(3);
    AXDriver_8038E844(4);
    AXDriver_8038E844(9);
    if (lbl_804D640C == 0) {
        AXDriver_8038E844(5);
        AXDriver_8038E844(6);
        AXDriver_8038E844(8);
        AXDriver_8038E844(7);
    }
}

void lbAudioAx_80024FDC(void)
{
    lbl_804D6430 = 0x1FE;
    lbl_804D6420 += 1;
}

void lbAudioAx_80024FF4(void)
{
    lbl_804D6434 = 0x1E0;
    lbl_804D6424 += 1;
}

void lbAudioAx_8002500C(int arg0)
{
    if (arg0 > 0) {
        lbl_804D6420 -= arg0;
        if (lbl_804D6420 <= 0) {
            lbl_804D6420 = 0;
        }
    }
}

void lbAudioAx_80025038(int arg0)
{
    if (arg0 > 0) {
        lbl_804D6424 -= arg0;
        if (lbl_804D6424 < 0) {
            lbl_804D6424 = 0;
        }
    }
}

void lbAudioAx_80025064(bool arg0, bool arg1)
{
    f32 var_f0;
    if (arg0) {
        var_f0 = 1.0F;
    } else {
        var_f0 = 0.0F;
    }
    lbl_804D38C4 = var_f0;
    if (arg1) {
        var_f0 = 1.0F;
    } else {
        var_f0 = 0.0F;
    }
    lbl_804D38C8 = var_f0;
}

void lbAudioAx_80025098(s32 arg0)
{
    lbl_804D6408 = arg0;
}

int fn_800250A0(int arg0, int arg1, int arg2, int arg3)
{
    f32 result;

    PAD_STACK(8);

    if (arg0 > arg1) {
        arg0 = arg1;
    }
    if (arg2 != arg3) {
        if (arg2 <= arg3) {
            result = arg2 + arg0 * ((f32) arg3 - arg2) / arg1;
        } else {
            result = arg3 + arg0 * ((f32) arg2 - arg3) / arg1;
        }
        if (result < 0.0F) {
            result = 0.0F;
        }
        if (result > 127.0F) {
            result = 127.0F;
        }
        return result;
    }
    return 64;
}

bool fn_800251EC(HSD_GObj* gobj)
{
    lbAudioAx_UserData* ud;
    s32 pad1;
    s32 pad2;
    f32 cam_left;
    f32 cam_center;
    f32 cam_right;
    Vec3 pos;
    s32 result_flag;
    f32 pan;
    s32 val;
    f32 ratio;
    f32 temp;
    HSD_GObj* entity;
    s32 type;

    if (gobj == NULL) {
        goto ret_true;
    }

    ud = gobj->user_data;
    if (ud == NULL) {
        goto ret_true;
    }

    Camera_800307D0(&cam_left, &cam_center, &cam_right);

    if (gobj == NULL) {
        goto set_flag;
    }
    if (gobj->user_data == NULL) {
        goto set_flag;
    }
    entity = ((lbAudioAx_UserData*) gobj->user_data)->entity;
    if (entity == NULL) {
        goto set_flag;
    }

    type = *(u16*) entity;
    switch (type) {
    case 4:
        ftLib_80086644(entity, &pos);
        result_flag = 0;
        break;
    case 6:
        it_8026B294(entity, &pos);
        result_flag = 0;
        break;
    default:
        pos.x = 0.0f;
        pos.y = 0.0f;
        pos.z = 0.0f;
        goto set_flag;
    }
    goto check_flag;

set_flag:
    result_flag = 1;
check_flag:
    if (result_flag == 1) {
        return true;
    }

    pan = 64.0f;

    if (!(cam_left < cam_center)) {
        goto store_pan;
    }
    if (!(cam_center < cam_right)) {
        goto store_pan;
    }
    if (!(cam_left < pos.x)) {
        goto store_pan;
    }
    if (!(pos.x < cam_right)) {
        goto store_pan;
    }

    if (cam_center < pos.x) {
        val = ud->pan_right;
        if (!(val > 0x40)) {
            goto store_pan;
        }
        ratio = (pos.x - cam_center) / (cam_right - cam_center);
        temp = (f32) (val - 0x40) * ratio;
        if (temp < 0.0f) {
            temp = -temp;
        }
        pan = 64.0f + temp;
    } else {
        if (!(cam_center > pos.x)) {
            goto store_pan;
        }
        val = ud->pan_left;
        if (!(val < 0x40)) {
            goto store_pan;
        }
        ratio = (cam_center - pos.x) / (cam_center - cam_left);
        temp = (f32) (0x40 - val) * ratio;
        if (temp < 0.0f) {
            temp = -temp;
        }
        pan = 64.0f - temp;
    }

store_pan:
    ud->x2C.pan = (s32) pan;
    return false;

ret_true:
    return true;
}
/// #fn_800253D8

/// #fn_800256BC

/// #fn_800259A0

/// #fn_800259EC

/// #fn_80025A98

bool fn_80025B44(HSD_GObj* gobj)
{
    lbAudioAx_UserData* ud;
    s32 target;
    s32 current;
    s32 end_frame;
    s32 current_frame;
    s32 result;
    f32 f_result;

    if (gobj == NULL) {
        goto end;
    }

    ud = gobj->user_data;
    if (ud == NULL) {
        goto end;
    }

    end_frame = ud->end_frame;
    current_frame = ud->current_frame;
    target = ud->pan_right;
    current = ud->pan_left;

    if (current_frame > end_frame) {
        current_frame = end_frame;
    }

    if (current != target) {
        if (current < target) {
            f_result = (f32) current +
                       ((f32) current_frame * ((f32) target - (f32) current)) /
                           (f32) end_frame;
        } else {
            f_result = (f32) target +
                       ((f32) current_frame * ((f32) current - (f32) target)) /
                           (f32) end_frame;
        }
        if (f_result < 0.0f) {
            f_result = 0.0f;
        }
        if (f_result > 127.0f) {
            f_result = 127.0f;
        }
        result = (s32) f_result;
    } else {
        result = 0x40;
    }

    ud->x2C.pan = result;
end:
    return false;
}
bool fn_80025CBC(HSD_GObj* gobj)
{
    lbAudioAx_UserData* ud;
    s32 target;
    s32 current;
    s32 end_frame;
    s32 current_frame;
    s32 result;
    f32 f_result;

    if (gobj == NULL) {
        goto end;
    }

    ud = gobj->user_data;
    if (ud == NULL) {
        goto end;
    }

    end_frame = ud->end_frame;
    current_frame = ud->current_frame;
    target = ud->pan_right;
    current = ud->pan_left;

    if (current_frame > end_frame) {
        current_frame = end_frame;
    }

    if (current != target) {
        if (current < target) {
            f_result = (f32) current +
                       ((f32) current_frame * ((f32) target - (f32) current)) /
                           (f32) end_frame;
        } else {
            f_result = (f32) target +
                       ((f32) current_frame * ((f32) current - (f32) target)) /
                           (f32) end_frame;
        }
        if (f_result < 0.0f) {
            f_result = 0.0f;
        }
        if (f_result > 127.0f) {
            f_result = 127.0f;
        }
        result = (s32) f_result;
    } else {
        result = 0x40;
    }

    ud->x2C.pan = 0x7F - result;
end:
    return false;
}
bool fn_80025E38(HSD_GObj* gobj)
{
    lbAudioAx_UserData* ud;
    s32 end_frame;
    s32 current_frame;
    s32 end_val;
    s32 start_val;
    f32 diff;
    f32 ratio;

    if (gobj == NULL) {
        goto end;
    }

    ud = gobj->user_data;
    if (ud == NULL) {
        goto end;
    }

    current_frame = ud->current_frame;
    end_frame = ud->end_frame;

    if (current_frame > end_frame) {
        goto set_7f;
    }

    start_val = ud->start_val;
    end_val = ud->end_val;

    if (start_val < end_val) {
        diff = (f32) end_val - (f32) start_val;
        if (diff < 0.0f) {
            diff = -diff;
        }
        ratio = (f32) current_frame / (f32) end_frame;
        ud->x20 = start_val + (s32) (ratio * diff);
        goto end;
    }

    diff = (f32) end_val - (f32) start_val;
    if (diff < 0.0f) {
        diff = -diff;
    }
    ratio = (f32) current_frame / (f32) end_frame;
    ud->x20 = end_val - (s32) (ratio * diff);
    goto end;

set_7f:
    ud->x20 = 0x7F;

end:
    return false;
}
/// #fn_80025FAC

/// #fn_800262A0

/// @brief Free an object from the audio allocator pool.
void lbAudioAx_ObjFree(void* obj)
{
    if (obj != NULL) {
        void* p = obj;
        HSD_ObjFree(&lbl_80433710, p);
    }
}
typedef struct SoundParams {
    HSD_GObj* gobj;
    int x4;
    int sfx_id;
    int xC;
    int x10;
    int x14;
    int x18;
    int x1C;
    float x20;
    int x24;
    int x28;
} SoundParams;

HSD_GObj* lbAudioAx_800263E8(float f1, HSD_GObj* arg1, int sfx_id, int arg3,
                             int arg4, int arg5, int arg6, int arg7, int arg8,
                             int arg9, int arg10)
{
    void* userdata;
    HSD_GObj* gobj;
    SoundParams params;

    if (arg3 >= 0x83D60) {
        goto return_null;
    }

    params.gobj = arg1;
    params.x4 = sfx_id;
    params.sfx_id = arg3;
    params.xC = arg4;
    params.x10 = arg5;
    params.x14 = arg6;
    params.x18 = arg7;
    params.x1C = arg8;
    params.x20 = f1;
    params.x24 = arg9;
    params.x28 = arg10;

    gobj = GObj_Create(0x17, 0x3E, 0);
    if (gobj == NULL) {
        goto return_null;
    }

    userdata = HSD_ObjAlloc(&lbl_80433710);
    if (userdata == NULL) {
        HSD_GObjPLink_80390228(gobj);
        gobj = NULL;
        goto return_gobj;
    }

    GObj_InitUserData(gobj, 0x17, lbAudioAx_ObjFree, userdata);

    if (gobj != NULL) {
        HSD_GObjProc_8038FD54(gobj, fn_800262A0, 0x17);
    }

    fn_80025FAC(gobj, userdata, &params);

return_gobj:
    return gobj;

return_null:
    return NULL;
}

bool lbAudioAx_800264E4(void* data)
{
    lbAudioAx_UserData* inner;
    if (data != NULL) {
        inner = ((lbAudioAx_UserData*) data)->x2C.inner;
        if (inner == NULL) {
            return -1;
        }
        return inner->voice_id;
    }
    return -1;
}
bool lbAudioAx_80026510(HSD_GObj* arg0)
{
    HSD_GObj* next;
    HSD_GObj* gobj;
    int count;

    count = 0;

    if (arg0 == NULL) {
        goto end;
    }

    gobj = ((HSD_GObj**) HSD_GObj_Entities)[0x3E];

    while (gobj != NULL) {
        lbAudioAx_UserData* ud = gobj->user_data;
        next = gobj->next;

        if (ud != NULL) {
            if (ud->entity == arg0) {
                s32 voice_id;
                voice_id = ud->voice_id;
                if (voice_id != -1) {
                    AXDriverKeyOff(voice_id);
                }
                if (gobj != NULL) {
                    HSD_GObjPLink_80390228(gobj);
                }
                count++;
            }
        }
        gobj = next;
    }

end:
    if (count != 0) {
        return true;
    }
    return false;
}

bool lbAudioAx_800265C4(HSD_GObj* arg0, int arg1)
{
    HSD_GObj* gobj;

    PAD_STACK(16);

    gobj = ((HSD_GObj**) HSD_GObj_Entities)[0x3E];

    while (gobj != NULL) {
        lbAudioAx_UserData* ud = gobj->user_data;
        if (ud != NULL) {
            if (ud->entity == arg0) {
                if (ud->voice_id != -1 && ud->voice_id == arg1) {
                    AXDriverKeyOff(ud->voice_id);
                    if (gobj != NULL) {
                        HSD_GObjPLink_80390228(gobj);
                    }
                    return true;
                }
            }
        }
        gobj = gobj->next;
    }
    return false;
}
/// #fn_80026650

void fn_800267B0(void)
{
    char* base;
    int* arr_274;
    s8(*arr_5d0)[4];
    int* arr_194;
    int* arr_354;
    int (*arr_4e4)[2];
    int j;
    int i;

    base = (char*) &lbl_80433710;

    if ((u32) lbl_804D6450 == 0) {
        return;
    }

    for (i = 0; i < 5; i++) {
        arr_5d0 = s32_arr_803BB5D0;
        arr_4e4 = offsets_arr_803BC4E4;
        arr_274 = (int*) (base + 0x274);
        arr_194 = (int*) (base + 0x194);
        arr_354 = (int*) (base + 0x354);
        j = 0;

        goto loop_check;
    loop_body:
        if (*arr_274 != -1) {
            if (i == (s8) (*arr_5d0)[2]) {
                if (*arr_194 == -1) {
                    HSD_Synth_80388E08(*arr_354);
                    *arr_354 = -1;
                    *arr_274 = -1;
                    lbl_804D6448 -= (*arr_4e4)[0];
                }
            }
        }

        arr_274++;
        arr_5d0++;
        arr_194++;
        arr_354++;
        arr_4e4++;
        j++;

    loop_check:
        if ((u32) lbl_804D6438 >= (u32) (lbl_804D6448 + lbl_804D6450)) {
            continue;
        }
        if (j < 0x37) {
            goto loop_body;
        }
    }

    HSD_SynthSFXBankDeflag(2);
    HSD_SynthSFXBankDeflagSync();
}

void fn_800268B4(void)
{
    int* arr_38a4;
    int* arr_3984;
    int (*arr_4e4)[2];
    int i;

    lbl_804D6450 = 0;
    lbl_804D644C = 0;
    lbl_804D6448 = 0;

    arr_38a4 = lbl_804338A4;
    arr_3984 = lbl_80433984;
    arr_4e4 = offsets_arr_803BC4E4;

    for (i = 0x37; i > 0; i--) {
        int flag1, flag2;
        int flags;

        if (*arr_38a4 == -1) {
            flag1 = 0;
        } else {
            flag1 = 1;
        }

        if (*arr_3984 == -1) {
            flag2 = 0;
        } else {
            flag2 = 2;
        }

        flags = flag1 | flag2;

        switch (flags) {
        case 0:
            break;
        case 1:
            lbl_804D644C += (*arr_4e4)[0];
            lbl_804D6450 += (*arr_4e4)[0];
            break;
        case 2:
            lbl_804D6448 += (*arr_4e4)[0];
            break;
        case 3:
            lbl_804D644C += (*arr_4e4)[0];
            lbl_804D6448 += (*arr_4e4)[0];
            break;
        }

        arr_38a4++;
        arr_3984++;
        arr_4e4++;
    }
}

/// #fn_800269AC

/// #fn_80026C04

bool fn_80026E58(int arg0)
{
    if (lbl_80433984[arg0] == 2) {
        return true;
    }
    return false;
}

u64 lbAudioAx_80026E84(CharacterKind c_kind)
{
    if (c_kind < 0 || c_kind >= CHKIND_MAX) {
        return 0;
    }
    return lbl_803BB3C0[c_kind].x8;
}

u64 lbAudioAx_80026EBC(InternalStageId arg0)
{
    const int imax = ARRAY_SIZE(s32_arr_803BB6B0);
    int id = Stage_8022519C(arg0);
    int shift;

    if (id < 0 || id >= imax) {
        return 0;
    }
    if ((shift = s32_arr_803BB6B0[id][0]) == 0x37) {
        return 0;
    }
    return 1ULL << shift;
}

u64 lbAudioAx_80026F2C(s32 arg0)
{
    int* arr;
    int i;
    u64 mask = 0;

    if (arg0 & 1) {
        mask += 0x0048000000000003ULL;
    }

    if (arg0 & 2) {
        mask += 0x000000000000003CULL;
    }

    if (arg0 & 4) {
        mask += 0x00800003FFFFFFC0ULL;
    }

    if (arg0 & 8) {
        mask += 0x0023FFFC00000000ULL;
    }

    if (arg0 & 16) {
        mask += 0x0014000000000000ULL;
    }

    arr = lbl_804337C4;
    for (i = 0; i < 0x37; i++) {
        if ((mask & 1) != 0) {
            *arr = -1;
        }
        mask >>= 1;
        arr++;
    }

    return mask;
}

void lbAudioAx_8002702C(s32 flags, u64 base_val)
{
    u64 result = 0;
    s32 i;
    u64 mask;

    mask = base_val + 3 + ((u64) 0x480000 << 32);

    if (flags & 1) {
        result += 3 + ((u64) 0x480000 << 32);
    }
    if (flags & 2) {
        result += 0x3C;
    }
    if (flags & 4) {
        result += (u32) -64 + ((u64) 0x800003 << 32);
    }
    if (flags & 8) {
        result += ((u64) 0x23FFFC << 32);
    }
    if (flags & 16) {
        result += ((u64) 0x140000 << 32);
    }

    for (i = 0; i < 0x37; i++) {
        if ((result & 1) != 0) {
            if ((mask & 1) != 0) {
                lbl_804337C4[i] = 1;
            }
        }
        result >>= 1;
        mask >>= 1;
    }
}

/// #lbAudioAx_80027168

/// #fn_80027488

/// #lbAudioAx_80027648

/// #lbAudioAx_8002785C

/// #lbAudioAx_80027AB0

extern int lbl_804D6418;

void lbAudioAx_80027DBC(void)
{
    HSD_AudioSFXKeyOffAll();
    lbAudioAx_800236DC();
    lbAudioAx_80024C84();
    fn_800269AC();
}

/// #lbAudioAx_80027DF8

void lbAudioAx_8002835C(void)
{
    HSD_ObjAllocInit(&lbl_80433710, 0x48, 4);
}

/// #lbAudioAx_8002835C

/// #lbAudioAx_8002838C

/// #lbAudioAx_80028690

int lbAudioAx_80028B2C(void)
{
    return AXDriver_8038E5D4();
}

int lbAudioAx_80028B4C(void)
{
    return AXDriver_8038E5DC();
}

void lbAudioAx_80028B6C(void)
{
    lbl_804D38CC--;
    if (lbl_804D38CC < 0) {
        lbl_804D38CC = 0;
    }
}

void lbAudioAx_80028B90(void)
{
    lbl_804D38CC = 0x7F;
}
