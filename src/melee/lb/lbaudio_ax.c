#include "lbaudio_ax.h"

#include "lbaudio_ax.static.h"

#include "cm/camera.h"
#include "ft/ftlib.h"
#include "gm/gm_1601.h"
#include "gm/gm_16A2.h"
#include "gm/gm_16AE.h"
#include "gr/stage.h"
#include "it/it_26B1.h"
#include "lb/lb_0195.h"
#include "lb/lbarchive.h"
#include "lb/lblanguage.h"
#include "pl/player.h"

#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <dolphin/ai.h>
#include <dolphin/ar.h>
#include <dolphin/ax.h>
#include <dolphin/axfx.h>
#include <sysdolphin/baselib/axdriver.h>
#include <sysdolphin/baselib/gobjplink.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/gobjuserdata.h>
#include <sysdolphin/baselib/random.h>
#include <sysdolphin/baselib/synth.h>

#define GET_SOUND(x) ((lbAudioAx_UserData*) HSD_GObjGetUserData(x))

#define GOBJ_TYPE_AUDIO_AX 0x3E

#define VOL_MAX 0x7F
#define PAN_MID 0x40

static bool fn_80026E58(int);

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
    if (i >= 55) {
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
        for (i = 0; i < 55; i++) {
            if (s32_arr_803BB8D4[i][0] <= arg0 &&
                arg0 <= s32_arr_803BB8D4[i][1])
            {
                return i;
            }
        }
    }
    return 55;
}

int lbAudioAx_80023220(int idx)
{
    if (idx >= 0 && idx < 55) {
        return s32_arr_803BB5D0[idx][3];
    }
    return 0;
}

/// Shift the priority list down one slot from @p count to make room.
static inline void fn_80023254_shift(int count)
{
    int i;
    for (i = 55; i > count; i--) {
        lbl_80433B44[i] = lbl_80433B44[i - 1];
    }
}

static void fn_80023254(int arg0)
{
    bool used[56];
    int count;
    int index;
    int i;
    int zero;

    PAD_STACK(8);

    for (i = 0; zero = count = 0, i < 56; i++) {
        lbl_80433B44[i] = 55;
        used[i] = zero;
    }

    for (; count <= 55; count++) {
        for (index = 0; index <= 55; index++) {
            if (arg0 == s32_arr_803BB5D0[index][0] && !used[index] &&
                offsets_arr_803BC4E4[lbl_80433B44[count]][0] <
                    offsets_arr_803BC4E4[index][0])
            {
                fn_80023254_shift(count);
                lbl_80433B44[count] = index;
                used[index] = true;
            }
        }
    }
}

int lbAudioAx_800233EC(int arg0)
{
    int slot;

    if (fn_80026E58(0x21) == 1) {
        slot = lbAudioAx_80023130(arg0);
        switch (slot) {
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 13:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
        case 22:
        case 23:
        case 24:
        case 25:
        case 26:
        case 27:
        case 28:
        case 29:
        case 30:
        case 31: {
            int i;
            for (i = 0; i < 0x4A; i++) {
                if (arg0 == offsets_arr_803BC6A4[i][0]) {
                    return offsets_arr_803BC6A4[i][1];
                }
            }
            break;
        }
        }
    } else {
        slot = lbAudioAx_80023130(arg0);
        switch (slot) {
        case 0x21: {
            int i;
            for (i = 0; i < 0x4A; i++) {
                if (arg0 == offsets_arr_803BC6A4[i][1]) {
                    return offsets_arr_803BC6A4[i][0];
                }
            }
            break;
        }
        }
    }

    return arg0;
}

int lbAudioAx_80023694(void)
{
    HSD_AudioSFXKeyOffAll();
    return -1;
}

int lbAudioAx_800236B8(int voice)
{
    AXDriverKeyOff(voice);
    return -1;
}

int lbAudioAx_800236DC(void)
{
    AXDriverStop();
    lbl_804D6418 = 0;
    cur_hps_stem[0] = '\0';
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

static int fn_80023750(int id, int vol, int pan, int track, int channel)
{
    vol *= 2;
    if (vol < 0) {
        vol = 0;
    }
    if (vol > 0xFF) {
        vol = 0xFF;
    }
    pan *= 2;
    if (pan < 0) {
        pan = 0;
    }
    if (pan > 0xFF) {
        pan = 0xFF;
    }
    return AXDriver_8038CFF4(id, vol, pan, track, channel);
}

int lbAudioAx_800237A8(int id, int vol, int pan)
{
    if (id >= 0x83D61) {
        return fn_80023750(0x83D60, 0, PAN_MID, 0, 7);
    } else {
        return fn_80023750(id, vol, pan, 0, 7);
    }
}

int lbAudioAx_80023870(int id, int vol, int pan, int track)
{
    if (track == 0) {
        return lbAudioAx_800237A8(id, vol, pan);
    }
    if (id == 0x83D61) {
        HSD_AudioSFXKeyOffTrack(track);
        return -1;
    }
    return fn_80023750(id, vol, pan, track, 7);
}

static struct {
    int** x0;
    int** x4;
    int** x8;
    int** xC;
}* lbl_804D6454;

void lbAudioAx_8002392C(void)
{
    lbArchive_LoadSymbols("LbAd.dat", &lbl_804D6454, "lbAudioLoadData", 0);
}

static inline int* getAudioLoadData(int arg0)
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
    int i = 0;
    int* var_r4;

#ifdef MUST_MATCH
    if (arg0 < 0 && arg0 >= 30) {
        return -1;
    }
#endif

    var_r4 = getAudioLoadData(arg0);
    while (*var_r4 != 0x83D60) {
        var_r4++;
        i++;
    }
    return i;
}

int lbAudioAx_80023A44(int arg0, int arg1)
{
    int* var_r3;

#ifdef MUST_MATCH
    if (arg0 < 0 && arg0 >= 0x1E) {
        return 0x83D60;
    }
    if (arg1 < 0 && 0x83D60 <= arg1) {
        return 0x83D60;
    }
#endif

    var_r3 = getAudioLoadData(arg0);
    return var_r3[arg1];
}

static inline void fn_800269AC_delay(void)
{
    int m, s, j, k, total;

    total = 0;
    for (j = total; j < 0x3E8; j++) {
        for (k = 0; k < 0x3E8; k++) {
            s = 0;
            for (m = s; m < 9; m++) {
                s += m;
            }
            total += s;
        }
    }
}

int lbAudioAx_80023B24(int id)
{
    int slot = lbAudioAx_80023130(id);
    PAD_STACK(4);

    if (s32_arr_803BB5D0[slot][1] != 5) {
        HSD_AudioSFXKeyOffAll();
        if (lbl_80433984[slot] != 2) {
            fn_800269AC_delay();
            HSD_SynthSFXUnloadBank(2);

            {
                int k;
                for (k = 0; k < 55; k++) {
                    if (s32_arr_803BB5D0[k][2] != 5) {
                        lbl_804337C4[k] = -1;
                        lbl_804338A4[k] = -1;
                        lbl_80433984[k] = -1;
                        lbl_80433A64[k] = -1;
                    }
                }
            }

            strcpy(&cur_ssm_file[ssm_stem_pos], ssm_files[slot]);
            lbl_80433A64[slot] = HSD_SynthSFXLoad(cur_ssm_file, 2, 0, 0);
            HSD_SynthSFXWaitForLoadCompletion(lb_800195D0);
            lbl_80433984[slot] = 2;
        }
    }

    return fn_80023750(id, VOL_MAX, PAN_MID, 0, 7);
}

static bool fn_80023ED4(const char* path, int vol, int arg2)
{
    vol *= 2;
    if (vol < 0) {
        vol = 0;
    }
    if (vol > 0xFF) {
        vol = 0xFF;
    }
    if (arg2 < 0) {
        arg2 = 0;
    }
    if (arg2 >= 9) {
        arg2 = 8;
    }
    return AXDriver_8038E8EC(path, vol, arg2);
}

static inline const char* getHPSFile(int arg0)
{
    if (arg0 < 0) {
        return NULL;
    } else if (arg0 >= 0x62) {
        return NULL;
    } else {
        strcpy(&cur_hps_file[hps_stem_pos], hps_files[arg0]);
        return cur_hps_file;
    }
}

static inline int lbAudioAx_80023F28_helper1(const char* filename)
{
    int result;
    if (filename == NULL || filename[0] == '\0') {
        result = 1;
    } else if (strcmp(cur_hps_stem, filename) != 0) {
        lbAudioAx_800236DC();
        strcpy(cur_hps_stem, filename);
        fn_80023ED4(cur_hps_stem, VOL_MAX, 1);
        result = 0;
    } else {
        result = 1;
    }
    return result;
}

int lbAudioAx_80023F28(int arg0)
{
    const char* filename;

    if (arg0 < 0 || arg0 >= 0x62) {
        return true;
    }
    if (!(filename = getHPSFile(arg0))) {
        return true;
    }
    return lbAudioAx_80023F28_helper1(filename);
}

void lbAudioAx_80024030(int arg0)
{
    static struct lbl_803BC918_t {
        int id;
        int track;
        int channel;
    } lbl_803BC918[] = {
        { 0xAC, 0x13, 3 }, { 0xAD, 0x14, 3 }, { 0xAE, 0x00, 3 },
        { 0xAF, 0x00, 3 }, { 0xB0, 0x15, 3 }, { 0xB1, 0x00, 2 },
        { 0xC1, 0x00, 2 }, { 0xBC, 0x00, 2 }, { 0xDB, 0x00, 3 },
        { 0xDC, 0x00, 3 }, { 0xDD, 0x00, 3 },
    };

    if (arg0 < 0xB) {
        fn_80023750(lbl_803BC918[arg0].id, VOL_MAX, PAN_MID,
                    lbl_803BC918[arg0].track, lbl_803BC918[arg0].channel);
    }
}

int lbAudioAx_800240B4(int id)
{
    return fn_80023750(id, VOL_MAX, PAN_MID, 0, 5);
}

int lbAudioAx_8002411C(int id)
{
    return fn_80023750(id, VOL_MAX, PAN_MID, 0, 6);
}

int lbAudioAx_80024184(int id, int vol, int pan, int track)
{
    switch (id) {
    case 0x56:
        track = 9;
        break;
    case 0x57:
        track = 8;
        break;
    case 0x58:
        track = 7;
        break;
    case 0x59:
        track = 0xC;
        break;
    case 0x5A:
        track = 0xB;
        break;
    case 0x5B:
        track = 0xA;
        break;
    case 0x6F:
        track = 0xD;
        break;
    case 0x70:
        track = 0xE;
        break;
    case 0x71:
        track = 0xF;
        break;
    case 0x65:
        track = 0x10;
        break;
    case 0x66:
        track = 0x11;
        break;
    case 0x67:
        track = 0x12;
        break;
    case 0x54:
        track = 0x17;
        break;
    case 0x12E:
        track = 0x18;
        break;
    case 0x20D:
        track = track != -1 ? track : 0;
        break;
    default:
        track = 0;
        break;
    }
    return fn_80023750(id, vol, pan, track, 7);
}

int lbAudioAx_80024304(int id)
{
    int track;
    switch (id) {
    case 0x8A:
    case 0x8B:
    case 0x8C:
        track = 0x16;
        id = 0x8B;
        break;
    default:
        track = 0;
        break;
    }

    return fn_80023750(id, VOL_MAX, PAN_MID, track, 7);
}

int lbAudioAx_8002438C(int id)
{
    return fn_80023750(id, VOL_MAX, PAN_MID, 0, 8);
}

int lbAudioAx_800243F4(int id)
{
    int track = 0xCA;
    switch (id) {
    case 0x7C830:
        track = 0xCB;
        /* fallthrough */
    case 0x7C831:
        track += 1;
        /* fallthrough */
    case 0x7C835:
        track += 1;
        /* fallthrough */
    case 0x7C83A:
        track += 1;
        /* fallthrough */
    case 0x7C83F:
        track += 1;
        /* fallthrough */
    case 0x7C840:
        track += 1;
        /* fallthrough */
    case 0x7C842:
        track += 1;
        /* fallthrough */
    case 0x7C844:
        track += 1;
        /* fallthrough */
    case 0x7C845:
        track += 1;
        /* fallthrough */
    case 0x7C846:
        track += 1;
        /* fallthrough */
    case 0x7C848:
        track += 1;
        /* fallthrough */
    case 0x7C84A:
        track += 1;
        /* fallthrough */
    case 0x7C84B:
        track += 1;
        /* fallthrough */
    case 0x7C84D:
        track += 1;
        /* fallthrough */
    case 0x7C83B:
        track += 1;
        /* fallthrough */
    case 0x7C83D:
        track += 1;
        /* fallthrough */
    case 0x7C84E:
        track += 1;
        /* fallthrough */
    case 0x7C84F:
        track += 1;
        /* fallthrough */
    case 0x7C850:
        track += 1;
        /* fallthrough */
    case 0x7C851:
        track += 1;
        /* fallthrough */
    case 0x7C834:
        track += 1;
        /* fallthrough */
    case 0x7C843:
        track += 1;
        /* fallthrough */
    case 0x7C832:
        track += 1;
        /* fallthrough */
    case 0x7C83C:
        track += 1;
        /* fallthrough */
    case 0x7C84C:
        track += 1;
        /* fallthrough */
    case 0x7C836:
        track += 1;
        /* fallthrough */
    case 0x7C849:
        track += 1;
        /* fallthrough */
    case 0x7C838:
        track += 1;
        break;
    }
    return fn_80023750(id, VOL_MAX, PAN_MID, track, 7);
}

static void fn_800244F4(void)
{
    lbl_804D387C = 0x7F;
    lbl_804D3884 = 0x7F;
    lbl_804D388C = 0x7F;
    lbl_804D3894 = 0x7F;
    lbl_804D389C = 0x7F;
    lbl_804D38A4 = 0x7F;
    lbl_804D38D8 = 1;
    lbl_804D38C0 = 1.0F;
    lbl_804D38AC = 1.0F;
    lbl_804D38B0 = 1.0F;
    lbl_804D38B4 = 1.0F;
    lbl_804D38B8 = 1.0F;
    lbl_804D38BC = 1.0F;
    lbl_804D640C = false;
    paused = false;
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
    lbl_804D641C = 0;
    lbl_804D63F4 = 0;
    lbl_804D63F8 = 0;
    lbl_804D63FC = 0;
    lbl_804D6400 = 0;
    lbl_804D6404 = 0;
    synth_volume = 1.0F;
    lbl_804D3888 = 0x7F;
    lbl_804D3890 = 0x7F;
    lbl_804D3898 = 0x7F;
    lbl_804D38A0 = 0x7F;
    lbl_804D38A8 = 0x7F;
    lbl_804D63F0 = 0.0F;
    lbl_804D38CC = 0x7F;
    gm_801603B0();
}

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
    lbl_804D3884 = arg0;
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

static void fn_80024654(int arg0)
{
    float temp_f31;

    synth_volume = (lbl_804D387C / 127.0F) * lbl_804D38C0;
    if (arg0 == 1) {
        HSD_SynthStreamSetVolume(synth_volume);
        lbl_804D63F0 = synth_volume;
    } else if (lbl_804D63F0 != synth_volume) {
        HSD_SynthStreamSetVolume(synth_volume);
        lbl_804D63F0 = synth_volume;
    }
    temp_f31 = lbl_804D38CC / 127.0F;
    lbl_804D38B0 = lbl_804D38C8;
    lbl_804D38B4 = lbl_804D38C8 * temp_f31;
    lbl_804D3898 = (u8) (lbl_804D38B4 * (0.88F * (lbl_804D388C * 2)));
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
    lbl_804D38A0 = (u8) (lbl_804D38B8 * (0.88F * (lbl_804D388C * 2)));
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
    lbl_804D38A8 = (u8) (lbl_804D38BC * (0.88F * (lbl_804D388C * 2)));
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

void lbAudioAx_80024B1C(int voice, int pan)
{
    if (pan < 0) {
        pan = 0;
    }
    if (pan > 0x7F) {
        pan = 0x7F;
    }
    AXDriver_8038D2B4(voice, pan * 2);
}

void lbAudioAx_80024B58(int voice, int vol)
{
    if (vol < 0) {
        vol = 0;
    }
    if (vol > VOL_MAX) {
        vol = VOL_MAX;
    }
    AXDriver_8038D3B8(voice, vol * 2);
}

int lbAudioAx_80024B94(int voice, int arg1)
{
    int const limit = 0x4B0;
    if (arg1 < -limit) {
        arg1 = -limit;
    }
    if (arg1 > limit) {
        arg1 = limit;
    }
    return AXDriver_8038D4E4(voice, arg1);
}

bool lbAudioAx_80024BD0(void)
{
    u32 mode = HSD_SynthGetSoundMode();
    sound_mode = mode;
    return mode == 1 ? false : true;
}

/// Set sound mode, returns true if successful
bool lbAudioAx_80024C08(enum_t mode)
{
    static enum_t to_synth_mode[2] = { 1, 0 };
    switch (mode) {
    case AUDIO_MODE_UNK0:
    case AUDIO_MODE_UNK1:
        if (sound_mode != to_synth_mode[mode]) {
            sound_mode = to_synth_mode[mode];
            if (to_synth_mode[mode] != 1U && to_synth_mode[mode] != 0U) {
                return false;
            }
            HSD_SynthSetSoundMode(to_synth_mode[mode]);
            return true;
        }
        return true;
    default:
        return false;
    }
}

void lbAudioAx_80024C84(void)
{
    lbl_804D640C = false;
    paused = false;
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
    lbl_804D38D8 = s32_arr_803BB6B0[Stage_8022519C(Stage_80225194())][arg0];
}

void lbAudioAx_80024DC4(int arg0)
{
    int* p = lbl_8043373C;
    int* q = lbl_8043373C;
    int i;
    for (i = 0; i < 0x10; i++) {
        if (p[i] == arg0) {
            lbl_80433780[i] = 0xa;
            return;
        }
    }
    for (i = 0; i < 0x10; i++) {
        if (q[i] == 0x83D60) {
            lbl_8043373C[i] = arg0;
            lbl_80433780[i] = 0xa;
            return;
        }
    }
}

void lbAudioAx_80024E50(bool pause)
{
    paused = pause;
    if (pause) {
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
    HSD_SynthStreamSetVolume(synth_volume);
    AXDriver_8038E844(2);
    AXDriver_8038E844(3);
    AXDriver_8038E844(4);
    AXDriver_8038E844(9);
    if (!lbl_804D640C) {
        AXDriver_8038E844(5);
        AXDriver_8038E844(6);
        AXDriver_8038E844(8);
        AXDriver_8038E844(7);
    }
}

void lbAudioAx_80024FDC(void)
{
    lbl_804D6430 = 0x1FE;
    lbl_804D6420++;
}

void lbAudioAx_80024FF4(void)
{
    lbl_804D6434 = 0x1E0;
    lbl_804D6424++;
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
    lbl_804D38C4 = arg0 ? 1.0F : 0.0F;
    lbl_804D38C8 = arg1 ? 1.0F : 0.0F;
}

void lbAudioAx_80025098(bool debug)
{
    debug_enabled = debug;
}

static int calcPan(int current, int end, int left, int right)
{
    float result;

    PAD_STACK(8);

    if (current > end) {
        current = end;
    }
    if (left != right) {
        if (left <= right) {
            result = left + current * ((float) right - left) / end;
        } else {
            result = right + current * ((float) left - right) / end;
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

static inline int soundGetPosition(HSD_GObj* gobj, Vec3* pos)
{
    if (gobj != NULL && gobj->user_data != NULL &&
        GET_SOUND(gobj)->owner != NULL)
    {
        switch (GET_SOUND(gobj)->owner->classifier) {
        case HSD_GOBJ_CLASS_FIGHTER:
            ftLib_80086644(GET_SOUND(gobj)->owner, pos);
            return 0;
        case HSD_GOBJ_CLASS_ITEM:
            it_8026B294(GET_SOUND(gobj)->owner, pos);
            return 0;
        }
        pos->x = pos->y = pos->z = 0.0F;
    }
    return 1;
}

static bool fn_800251EC(HSD_GObj* gobj)
{
    float cam_left;
    float cam_center;
    float cam_right;
    Vec3 pos;
    float temp;

    if (gobj != NULL) {
        lbAudioAx_UserData* ud = GET_SOUND(gobj);
        if (ud != NULL) {
            float pan;

            Camera_800307D0(&cam_left, &cam_center, &cam_right);

            if (soundGetPosition(gobj, &pos) == 1) {
                return true;
            }

            pan = 64.0F;

            if (cam_left < cam_center && cam_center < cam_right &&
                cam_left < pos.x && pos.x < cam_right)
            {
                if (cam_center < pos.x) {
                    if (ud->pan_right > PAN_MID) {
                        float ratio =
                            (pos.x - cam_center) / (cam_right - cam_center);
                        temp = ud->pan_right - PAN_MID;
                        temp = temp * ratio;
                        pan = 64.0F + ABS(temp);
                    }
                } else if (cam_center > pos.x) {
                    if (ud->pan_left < PAN_MID) {
                        float ratio =
                            (cam_center - pos.x) / (cam_center - cam_left);
                        temp = PAN_MID - ud->pan_left;
                        temp = temp * ratio;
                        pan = 64.0F - ABS(temp);
                    }
                }
            }

            ud->pan = pan;
            return false;
        }
    }

    return true;
}

static bool fn_800253D8(HSD_GObj* gobj)
{
    if (gobj != NULL) {
        lbAudioAx_UserData* ud = GET_SOUND(gobj);
        if (ud != NULL) {
            if (ud->x3C == 1.0F) {
                ud->pan = calcPan(ud->current_frame, ud->end_frame,
                                  ud->pan_left, ud->pan_right);
            } else {
                ud->pan = 0x7F - calcPan(ud->current_frame, ud->end_frame,
                                         ud->pan_left, ud->pan_right);
            }
        }
    }
    return false;
}

static bool fn_800256BC(HSD_GObj* gobj)
{
    if (gobj != NULL) {
        lbAudioAx_UserData* ud = GET_SOUND(gobj);
        if (ud != NULL) {
            if (ud->x3C == 1.0F) {
                ud->pan = calcPan(ud->current_frame, ud->end_frame,
                                  ud->pan_left, ud->pan_right);
            } else {
                ud->pan = 0x7F - calcPan(ud->current_frame, ud->end_frame,
                                         ud->pan_left, ud->pan_right);
            }
        }
    }
    return false;
}

static bool fn_800259A0(HSD_GObj* gobj)
{
    if (gobj != NULL) {
        lbAudioAx_UserData* ud = GET_SOUND(gobj);
        if (ud != NULL) {
            if (!ud->x44) {
                ud->x44 = true;
                fn_800251EC(gobj);
            }
        }
    }
    return false;
}

static bool fn_800259EC(HSD_GObj* gobj)
{
    if (gobj != NULL) {
        lbAudioAx_UserData* ud = GET_SOUND(gobj);
        if (ud != NULL) {
            if (!ud->x44) {
                ud->x44 = true;
                fn_800253D8(gobj);
            }
        }
    }
    return false;
}

static bool fn_80025A98(HSD_GObj* gobj)
{
    if (gobj != NULL) {
        lbAudioAx_UserData* ud = GET_SOUND(gobj);
        if (ud != NULL) {
            if (!ud->x44) {
                ud->x44 = true;
                fn_800253D8(gobj);
            }
        }
    }
    return false;
}

static bool fn_80025B44(HSD_GObj* gobj)
{
    lbAudioAx_UserData* ud;
    if (gobj != NULL) {
        ud = GET_SOUND(gobj);
        if (ud != NULL) {
            ud->pan = calcPan(ud->current_frame, ud->end_frame, ud->pan_left,
                              ud->pan_right);
        }
    }
    return false;
}

static bool fn_80025CBC(HSD_GObj* gobj)
{
    lbAudioAx_UserData* ud;
    if (gobj != NULL) {
        ud = GET_SOUND(gobj);
        if (ud != NULL) {
            ud->pan = 0x7F - calcPan(ud->current_frame, ud->end_frame,
                                     ud->pan_left, ud->pan_right);
        }
    }
    return false;
}

static bool fn_80025E38(HSD_GObj* gobj)
{
    if (gobj != NULL) {
        lbAudioAx_UserData* ud = gobj->user_data;
        if (ud != NULL) {
            if (ud->current_frame <= ud->end_frame) {
                if (ud->start_vol < ud->end_vol) {
                    ud->vol =
                        ud->start_vol +
                        (int) (((float) ud->current_frame / ud->end_frame) *
                               ABS((float) ud->end_vol - ud->start_vol));
                } else {
                    ud->vol =
                        ud->end_vol -
                        (int) (((float) ud->current_frame / ud->end_frame) *
                               ABS((float) ud->end_vol - ud->start_vol));
                }
            } else {
                ud->vol = VOL_MAX;
            }
        }
    }

    return false;
}

typedef struct {
    HSD_GObj* owner;
    int x4;
    int sfx_id;
    int start_vol;
    int end_vol;
    int pan_left;
    int pan_right;
    int end_frame;
    float x20;
    int x24;
    int voice;
} SoundParams;

static void fn_80025FAC(HSD_GObj* gobj, lbAudioAx_UserData* ud,
                        SoundParams* sp)
{
    typedef bool (*lbl_803BCA24_fn)(HSD_GObj*);
    static lbl_803BCA24_fn lbl_803BCA24[] = {
        fn_800251EC, fn_800253D8, fn_800256BC, fn_800259A0, fn_800259EC,
        fn_80025A98, fn_80025B44, fn_80025CBC, fn_80025E38, fn_80025E38,
    };

    PAD_STACK(8);

    if (gobj != NULL && ud != NULL && sp != NULL) {
        ud->gobj = gobj;
        ud->owner = sp->owner;
        ud->xC = sp->x4;
        ud->id = sp->sfx_id;
        ud->current_frame = 0;
        ud->end_frame = sp->end_frame;
        if (sp->x20 == 0.0F) {
            ud->x3C = (HSD_Randi(2) == 0) ? 1.0F : -1.0F;
        } else {
            ud->x3C = sp->x20;
        }
        ud->track = sp->x24;
        ud->start_vol = sp->start_vol;
        ud->end_vol = sp->end_vol;
        ud->pan_left = sp->pan_left;
        ud->pan_right = sp->pan_right;
        ud->x44 = false;
        ud->vol = VOL_MAX;
        ud->pan = PAN_MID;
        ud->x10 = lbl_803BCA24[ud->xC];
        ud->voice_id = -1;

        switch (ud->xC) {
        case 0:
        case 3:
            if (ud->start_vol == ud->end_vol) {
                ud->vol = ud->start_vol;
            }
            break;
        case 1:
        case 2:
        case 4:
        case 5:
            if (ud->start_vol == ud->end_vol) {
                ud->vol = ud->start_vol;
            }
            break;
        case 6:
        case 7:
            if (ud->start_vol == ud->end_vol) {
                ud->vol = ud->start_vol;
            }
            break;
        case 8:
        case 9:
            if (ud->start_vol == ud->end_vol) {
                ud->vol = ud->start_vol;
            }
            break;
        }

        switch (ud->xC) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            if (ud->current_frame < 0) {
                ud->current_frame = 0;
            }
            if (ud->end_frame < 0) {
                ud->end_frame = 0;
            }
            if (ud->track == 0) {
                ud->voice_id = lbAudioAx_800237A8(ud->id, ud->vol, ud->pan);
            } else {
                ud->voice_id =
                    lbAudioAx_80023870(ud->id, ud->vol, ud->pan, ud->track);
            }
            break;
        case 9:
            if (ud->current_frame < 0) {
                ud->current_frame = 0;
            }
            if (ud->end_frame < 0) {
                ud->end_frame = 0;
            }
            ud->voice_id = sp->voice;
            break;
        }
    }
}

static void fn_800262A0(HSD_GObj* gobj)
{
    lbAudioAx_UserData* ud;

    if (gobj == NULL) {
        return;
    }

    ud = gobj->user_data;
    if (ud == NULL) {
        return;
    }

    if (ud->x10 == NULL) {
        return;
    }

    if (ud->x10(gobj) == true) {
        if (gobj != NULL) {
            HSD_GObjPLink_80390228(gobj);
        }
        return;
    }

    if (ud->voice_id != -1) {
        lbAudioAx_80024B1C(ud->voice_id, ud->pan);
        lbAudioAx_80024B58(ud->voice_id, ud->vol);
    }

    if (ud->current_frame != -1 && ud->end_frame != -1 &&
        (ud->current_frame >= ud->end_frame ||
         ud->end_frame == (ud->voice_id * 0)))
    {
        if (gobj != NULL) {
            HSD_GObjPLink_80390228(gobj);
        }
    } else {
        ud->current_frame += 1;
    }
}

/// @brief Free an object from the audio allocator pool.
static void lbAudioAx_ObjFree(void* obj)
{
    if (obj != NULL) {
        void* p = obj;
        HSD_ObjFree(&lbl_80433710, p);
    }
}

HSD_GObj* lbAudioAx_800263E8(float f1, HSD_GObj* owner, int arg2, int sfx_id,
                             int start_vol, int end_vol, int pan_left,
                             int pan_right, int end_frame, int arg9, int voice)
{
    void* userdata;
    HSD_GObj* gobj;
    SoundParams params;

    if (sfx_id < 0x83D60) {
        params.owner = owner;
        params.x4 = arg2;
        params.sfx_id = sfx_id;
        params.start_vol = start_vol;
        params.end_vol = end_vol;
        params.pan_left = pan_left;
        params.pan_right = pan_right;
        params.end_frame = end_frame;
        params.x20 = f1;
        params.x24 = arg9;
        params.voice = voice;

        gobj = GObj_Create(HSD_GOBJ_CLASS_SOUND, GOBJ_TYPE_AUDIO_AX, 0);
        if (gobj != NULL) {
            userdata = HSD_ObjAlloc(&lbl_80433710);
            if (userdata == NULL) {
                HSD_GObjPLink_80390228(gobj);
                gobj = NULL;
            } else {
                GObj_InitUserData(gobj, HSD_GOBJ_CLASS_SOUND,
                                  lbAudioAx_ObjFree, userdata);

                if (gobj != NULL) {
                    HSD_GObj_SetupProc(gobj, fn_800262A0,
                                       HSD_GOBJ_CLASS_SOUND);
                }

                fn_80025FAC(gobj, userdata, &params);
            }
        }
        return gobj;
    }
    return NULL;
}

int lbAudioAx_800264E4(HSD_GObj* data)
{
    lbAudioAx_UserData* ud;
    if (data != NULL) {
        ud = GET_SOUND(data);
        if (ud == NULL) {
            return -1;
        }
        return ud->voice_id;
    }
    return -1;
}

bool lbAudioAx_80026510(HSD_GObj* target)
{
    HSD_GObj* next;
    HSD_GObj* cur;
    int count = 0;
    PAD_STACK(8);

    if (target != NULL) {
        cur = ((HSD_GObj**) HSD_GObj_Entities)[GOBJ_TYPE_AUDIO_AX];

        while (cur != NULL) {
            lbAudioAx_UserData* ud = GET_SOUND(cur);
            next = cur->next;

            if (ud != NULL && ud->owner == target) {
                if (ud->voice_id != -1) {
                    AXDriverKeyOff(ud->voice_id);
                }
                if (cur != NULL) {
                    HSD_GObjPLink_80390228(cur);
                }
                count++;
            }
            cur = next;
        }
    }

    return count == 0 ? false : true;
}

bool lbAudioAx_800265C4(HSD_GObj* target_obj, int voice)
{
    HSD_GObj* cur;

    PAD_STACK(8);

    cur = ((HSD_GObj**) HSD_GObj_Entities)[GOBJ_TYPE_AUDIO_AX];

    while (cur != NULL) {
        lbAudioAx_UserData* ud = GET_SOUND(cur);
        if (ud != NULL && ud->owner == target_obj && ud->voice_id != -1 &&
            ud->voice_id == voice)
        {
            AXDriverKeyOff(ud->voice_id);
            if (cur != NULL) {
                HSD_GObjPLink_80390228(cur);
            }
            return true;
        }
        cur = cur->next;
    }
    return false;
}

static int fn_80026650(void)
{
    int i;
    int priority;
    for (priority = 4; priority >= 0; priority--) {
        for (i = 0; i < 55; i++) {
            if (priority == s32_arr_803BB5D0[i][1] && lbl_804338A4[i] == 1 &&
                lbl_80433984[i] == -1)
            {
                return i;
            }
        }
    }
    return -1;
}

static void fn_800267B0(void)
{
    int j, i;

    if (lbl_804D6450 == 0) {
        return;
    }

    for (i = 0; i < 5; i++) {
        for (j = 0; lbl_804D6438 < lbl_804D6448 + lbl_804D6450 && j < 55; j++)
        {
            if (lbl_80433984[j] != -1 && i == s32_arr_803BB5D0[j][2] &&
                lbl_804338A4[j] == -1)
            {
                int x = lbl_80433A64[j];
                HSD_Synth_80388E08(x);
                lbl_80433A64[j] = -1;
                lbl_80433984[j] = -1;
                lbl_804D6448 -= offsets_arr_803BC4E4[j][0];
            }
        }
    }

    HSD_SynthSFXBankDeflag(2);
    HSD_SynthSFXBankDeflagSync();
}

static void fn_800268B4(void)
{
    int i;

    lbl_804D6450 = 0;
    lbl_804D644C = 0;
    lbl_804D6448 = 0;

    for (i = 0; i < 55; i++) {
        int flag1, flag2;
        int flags;

        if (lbl_804338A4[i] == -1) {
            flag1 = 0;
        } else {
            flag1 = 1;
        }

        if (lbl_80433984[i] == -1) {
            flag2 = 0;
        } else {
            flag2 = 2;
        }

        flags = flag1 | flag2;

        switch (flags) {
        case 0:
            break;
        case 1:
            lbl_804D644C += offsets_arr_803BC4E4[i][0];
            lbl_804D6450 += offsets_arr_803BC4E4[i][0];
            break;
        case 2:
            lbl_804D6448 += offsets_arr_803BC4E4[i][0];
            break;
        case 3:
            lbl_804D644C += offsets_arr_803BC4E4[i][0];
            lbl_804D6448 += offsets_arr_803BC4E4[i][0];
            break;
        }
    }
}

static void fn_800269AC(void)
{
    int i;

    PAD_STACK(8);

    if (HSD_SynthSFXGetPendingLoadCount() != 0) {
        for (i = 0; i < 55; i++) {
            if (s32_arr_803BB5D0[i][1] != 5 && lbl_80433A64[i] != -1 &&
                lbl_80433984[i] == -1)
            {
                int retry;
                for (retry = 0; retry < 0x40; retry++) {
                    if (HSD_SynthSFXCancelLoad(lbl_80433A64[i]) == 1) {
                        break;
                    }
                    fn_800269AC_delay();
                }
                lbl_80433A64[i] = -1;
                lbl_80433984[i] = -1;
            }
        }

        if (HSD_SynthSFXGetPendingLoadCount() != 0) {
            HSD_SynthSFXWaitForLoadCompletion(lb_800195D0);
            HSD_SynthSFXUnloadBank(2);
            for (i = 0; i < 55; i++) {
                if (s32_arr_803BB5D0[i][1] != 5) {
                    lbl_80433984[i] = -1;
                    lbl_80433A64[i] = -1;
                }
            }
        }
    }
}

static void fn_80026C04(int arg0, int unused)
{
    int i;
    int slot;

    if (arg0 != -1) {
        for (i = 0; i < 55; i++) {
            if (arg0 == lbl_80433A64[i]) {
                lbl_80433984[i] = 1;
                lbl_804D644C -= offsets_arr_803BC4E4[i][0];
                lbl_804D6450 -= offsets_arr_803BC4E4[i][0];
                lbl_804D6448 += offsets_arr_803BC4E4[i][0];
                break;
            }
        }
    }

    slot = fn_80026650();
    if (slot != -1) {
        strcpy(&cur_ssm_file[ssm_stem_pos], ssm_files[slot]);
        lbl_80433A64[slot] = HSD_SynthSFXLoad(cur_ssm_file, 2, fn_80026C04, 0);
    }
}

static bool fn_80026E58(int arg0)
{
    if (lbl_80433984[arg0] == 2) {
        return true;
    }
    return false;
}

u64 lbAudioAx_80026E84(CharacterKind ckind)
{
    if (ckind < 0 || ckind >= CHKIND_MAX) {
        return 0;
    }
    return lbl_803BB3C0[ckind].x8;
}

u64 lbAudioAx_80026EBC(StKind stkind)
{
    const int imax = ARRAY_SIZE(s32_arr_803BB6B0);
    GrKind grkind = Stage_8022519C(stkind);
    int shift;

    if (grkind < 0 || grkind >= imax) {
        return 0;
    }
    if ((shift = s32_arr_803BB6B0[grkind][0]) == 55) {
        return 0;
    }
    return 1ULL << shift;
}

void lbAudioAx_80026F2C(u32 flags)
{
    int i;
    u64 mask = 0;

    if (flags & 1) {
        mask += 0x0048000000000003ULL;
    }

    if (flags & 2) {
        mask += 0x000000000000003CULL;
    }

    if (flags & 4) {
        mask += 0x00800003FFFFFFC0ULL;
    }

    if (flags & 8) {
        mask += 0x0023FFFC00000000ULL;
    }

    if (flags & 16) {
        mask += 0x0014000000000000ULL;
    }

    for (i = 0; i < (int) ARRAY_SIZE(lbl_804337C4) - 1; i++) {
        if (mask & 1) {
            lbl_804337C4[i] = -1;
        }
        mask >>= 1;
    }
}

void lbAudioAx_8002702C(u32 flags, u64 mask)
{
    u64 result = 0;
    int i;

    mask += 0x48000000000003ULL;

    if (flags & 1) {
        result += 0x48000000000003ULL;
    }
    if (flags & 2) {
        result += 0x3C;
    }
    if (flags & 4) {
        result += 0x800003FFFFFFC0ULL;
    }
    if (flags & 8) {
        result += 0x23FFFC00000000ULL;
    }
    if (flags & 16) {
        result += 0x14000000000000ULL;
    }

    for (i = 0; i < (int) ARRAY_SIZE(lbl_804337C4) - 1; i++) {
        if ((result & 1) && (mask & 1)) {
            lbl_804337C4[i] = 1;
        }
        result >>= 1;
        mask >>= 1;
    }
}

static inline void lbAudioAx_80027168_inline(void)
{
    int i;
    for (i = 0; i < 55; i++) {
        if (s32_arr_803BB5D0[i][1] != 5 && lbl_80433984[i] == 2) {
            lbl_80433984[i] = 1;
        }
    }
}

static inline void lbAudioAx_80027168_inline_2(void)
{
    int slot = fn_80026650();
    if (slot != -1) {
        strcpy(&cur_ssm_file[ssm_stem_pos], ssm_files[slot]);
        lbl_80433A64[slot] = HSD_SynthSFXLoad(cur_ssm_file, 2, fn_80026C04, 0);
    }
}

void lbAudioAx_80027168(void)
{
    int slot;
    int count;
    int i;

    lbAudioAx_80027168_inline();

    for (i = count = 0; i < 55; i++) {
        if (s32_arr_803BB5D0[i][1] != 5 && lbl_804337C4[i] != -1) {
            count++;
        }
    }

    if (count == 0) {
        return;
    }

    fn_800269AC();

    for (i = 0; i < 55; i++) {
        lbl_804338A4[i] = lbl_804337C4[i];
    }

    fn_800268B4();
    fn_800267B0();

    if (lbl_804D6438 < lbl_804D6448 + lbl_804D6450) {
        OSReport("******** CAUTION ********\n"
                 "FGM load size is over\n");
        HSD_ASSERT(0xDB3, 0);
    }

    lbAudioAx_80027168_inline_2();
}

static int fn_80027488(void)
{
    int i;

    for (i = 0; i < 55; i++) {
        if (lbl_804338A4[i] == 1 && lbl_80433984[i] == -1) {
            return 1;
        }
    }

    for (i = 0; i < 55; i++) {
        if (lbl_804338A4[i] == 1 && lbl_80433984[i] == 1) {
            lbl_80433984[i] = 2;
        }
    }

    return 0;
}

void lbAudioAx_80027648(void)
{
    while (fn_80027488() == 1) {
        HSD_SynthSFXWaitForLoadCompletion(lb_800195D0);
    }
}

void lbAudioAx_8002785C(void)
{
    u64 result = 0;
    int i;
    StKind stkind;

    if (gm_8016B184()) {
        result = lbAudioAx_80026E84(Player_GetPlayerCharacter(0));
        for (i = 0; i < 3; i++) {
            if (gm_80169370(i) != CHKIND_MAX) {
                int opp = gm_80169370(i);
                result |= lbAudioAx_80026E84(opp);
                if (opp == 4) {
                    result |= 0x200004000;
                }
            }
        }
    } else {
        for (i = 0; i < 4; i++) {
            if (Player_GetPlayerSlotType(i) != Gm_PKind_NA) {
                result |= lbAudioAx_80026E84(Player_GetPlayerCharacter(i));
            }
        }
    }

    stkind = Stage_80225194();
    if (stkind == 0xD9 || stkind == 0xE5) {
        result |= 0x200004000;
    }
    if (stkind == 0x46 || stkind == 0x47) {
        result |= 0xC00;
    }

    lbl_804D38D8 = s32_arr_803BB6B0[Stage_8022519C(stkind)][1];
    result |= lbAudioAx_80026EBC(stkind);

    if (result) {
        lbAudioAx_80026F2C(0xC);
        lbAudioAx_8002702C(0xC, result);
        lbAudioAx_80027168();
        lbAudioAx_80027648();
    }
}

static char str_audio_us[0xC] = "/audio/us/";
static char str_audio[0xC] = "/audio/";

static inline enum_t setup_audio_lang(void)
{
    enum_t lang;
    if (lbLang_IsSavedLanguageUS()) {
        strcpy(cur_ssm_file, str_audio_us);
        ssm_stem_pos = 10;
        return LANG_US;
    } else {
        strcpy(cur_ssm_file, str_audio);
        ssm_stem_pos = 7;
        return LANG_JP;
    }
}

void lbAudioAx_80027AB0(int id)
{
    enum_t lang = setup_audio_lang();

    HSD_AudioSFXKeyOffAll();

    if (lbl_804D3878 != lang) {
        lbl_804D3878 = lang;
        AXDriver_8038DCFC();
        strcpy(&cur_ssm_file[ssm_stem_pos], "smash2.sem");
        AXDriver_8038DA70(cur_ssm_file, lb_800195D0);

        if (id != 0x83D61) {
            lbAudioAx_800237A8(id, VOL_MAX, PAN_MID);
        }

        {
            int i;
            for (i = 0; i < 55; i++) {
                if (i != 0) {
                    lbl_80433A64[i] = -1;
                    lbl_804337C4[i] = -1;
                    lbl_804338A4[i] = -1;
                    lbl_80433984[i] = -1;
                }
            }
        }

        HSD_SynthSFXUnloadBank(1);
        HSD_SynthSFXUnloadBank(2);

        if (lbl_80433984[0x33] < 1) {
            strcpy(&cur_ssm_file[ssm_stem_pos], ssm_files[0x33]);
            lbl_80433A64[0x33] = HSD_SynthSFXLoad(cur_ssm_file, 1, 0, 0);
            HSD_SynthSFXWaitForLoadCompletion(lb_800195D0);
            lbl_80433984[0x33] = 2;
        }

        if (lbl_80433984[1] < 1) {
            strcpy(&cur_ssm_file[ssm_stem_pos], ssm_files[1]);
            lbl_80433A64[1] = HSD_SynthSFXLoad(cur_ssm_file, 1, 0, 0);
            HSD_SynthSFXWaitForLoadCompletion(lb_800195D0);
            lbl_80433984[1] = 2;
        }

        if (lbl_80433984[0x36] < 1) {
            strcpy(&cur_ssm_file[ssm_stem_pos], ssm_files[0x36]);
            lbl_80433A64[0x36] = HSD_SynthSFXLoad(cur_ssm_file, 1, 0, 0);
            HSD_SynthSFXWaitForLoadCompletion(lb_800195D0);
            lbl_80433984[0x36] = 2;
        }
    }
}

void lbAudioAx_80027DBC(void)
{
    HSD_AudioSFXKeyOffAll();
    lbAudioAx_800236DC();
    lbAudioAx_80024C84();
    fn_800269AC();
}

static inline void lbAudioAx_80027DF8_inline(void)
{
    if (!lbl_804D640C) {
        int i;
        int* sl;
        int* t;
        t = lbl_80433780;
        sl = lbl_8043373C;
        for (i = 0; i < 16; t++, sl++, i++) {
            if (*t > 0) {
                (*t)--;
            }
            if (*t <= 0) {
                *sl = 0x83D60;
                *t = 0;
            }
        }
    }
}

void lbAudioAx_80027DF8(void)
{
    int carry;

    PAD_STACK(16);
    if (!lbl_804D640C) {
        lbl_804D6430--;
        if (lbl_804D6430 <= 0) {
            lbl_804D6420 = 0;
            lbl_804D6430 = 0;
        }
        lbl_804D6434--;
        if (lbl_804D6434 <= 0) {
            lbl_804D6424 = 0;
            lbl_804D6434 = 0;
        }
    }

    if (lbl_804D6420 != 0) {
        if (lbl_804D38F0 != -1) {
            if (AXDriver_8038D9D8(lbl_804D38F0) == 0) {
                lbl_804D38F0 = fn_80023750(0x84, lbl_804D6428, PAN_MID, 5, 4);
            } else {
                lbAudioAx_80024B58(lbl_804D38F0, lbl_804D6428);
            }
        } else {
            lbl_804D6428 = VOL_MAX;
            lbl_804D38F0 = fn_80023750(0x84, VOL_MAX, PAN_MID, 5, 4);
            lbl_804D642C = 0;
        }
    } else if (lbl_804D38F0 != -1) {
        fn_80023750(0x83D60, lbl_804D6428, PAN_MID, 5, 4);
        {
            carry = 0;
            lbl_804D6428 = carry;
            lbl_804D38F0 = -1;
            carry = lbl_804D38F4 == -1 ? carry : 0x7F;
            lbl_804D642C = carry;
        }
    }

    if (lbl_804D6424 != 0) {
        if (lbl_804D38F4 != -1) {
            if (AXDriver_8038D9D8(lbl_804D38F4) == 0) {
                lbl_804D38F4 = fn_80023750(0x85, lbl_804D642C, PAN_MID, 6, 4);
            } else {
                lbAudioAx_80024B58(lbl_804D38F4, lbl_804D642C);
            }
        } else {
            lbl_804D642C = 0x7F;
            lbl_804D38F4 = fn_80023750(0x85, VOL_MAX, PAN_MID, 6, 4);
            lbl_804D6428 = 0;
        }
    } else if (lbl_804D38F4 != -1) {
        fn_80023750(0x83D60, lbl_804D642C, PAN_MID, 6, 4);
        {
            carry = 0;
            lbl_804D642C = carry;
            lbl_804D38F4 = -1;
            carry = lbl_804D38F0 == -1 ? carry : 0x7F;
            lbl_804D6428 = carry;
        }
    }

    if (lbl_804D38F0 == -1 && lbl_804D38F4 == -1) {
        lbl_804D38EC = 1.0F;
    } else {
        lbl_804D38EC = 0.2F;
    }

    fn_80024654(0);

    if (lbl_804D641C == 1) {
        int i;
        PAD_STACK(8);
        for (i = 0; i < 0x10; i++) {
            if (lbl_8043373C[i] != 0x83D60) {
                lbAudioAx_800237A8(lbl_8043373C[i], VOL_MAX, PAN_MID);
                lbl_8043373C[i] = 0x83D60;
                lbl_80433780[i] = 0;
            }
        }
        lbl_804D641C = 0;
        return;
    }

    lbAudioAx_80027DF8_inline();
}

void lbAudioAx_8002835C(void)
{
    HSD_ObjAllocInit(&lbl_80433710, sizeof(lbAudioAx_UserData), 4);
}

void lbAudioAx_8002838C(void)
{
    static u32 ar_stack[0x10];

    struct AXFX_REVERBSTD rvbStd;
    struct AXFX_DELAY delay;
    int i;

    ARInit(ar_stack, ARRAY_SIZE(ar_stack));
    ARQInit();
    AIInit(NULL);

    lbl_804D643C = offsets_arr_803BC4E4[0][0];
    lbl_804D6440 = offsets_arr_803BC4E4[0x33][0];
    lbl_804D6440 += offsets_arr_803BC4E4[1][0];
    lbl_804D6440 += offsets_arr_803BC4E4[0x36][0];

    fn_80023254(3);
    lbl_804D6444 = offsets_arr_803BC4E4[lbl_80433B44[0]][0];

    fn_80023254(4);
    lbl_804D6444 += offsets_arr_803BC4E4[lbl_80433B44[0]][0];
    lbl_804D6444 += offsets_arr_803BC4E4[lbl_80433B44[1]][0];
    lbl_804D6444 += offsets_arr_803BC4E4[lbl_80433B44[2]][0];
    lbl_804D6444 += offsets_arr_803BC4E4[lbl_80433B44[3]][0];

    fn_80023254(5);
    lbl_804D6444 += offsets_arr_803BC4E4[lbl_80433B44[0]][0];

    lbl_804D6438 = lbl_804D643C + lbl_804D6440 + lbl_804D6444;
    lbl_804D3870 = lbl_804D6438;

    AXDriver_8038E498(AX_MAX_VOICES, 0, 0x40, lbl_804D3870);

    {
        static u8 lbl_80433C64[53 * 1024];
        AXDriver_8038E37C(AXDRIVER_AUX_REVERB_STD, &rvbStd);
        rvbStd.time = 1.88F;
        HSD_ASSERT(0xF6E, HSD_AudioGetAuxHeapSize(2, &rvbStd) < 53*1024);
        AXDriver_8038E30C(0, 2, &rvbStd, lbl_80433C64, sizeof(lbl_80433C64));
    }

    {
        static u8 lbl_80441064[71 * 1024];
        AXDriver_8038E37C(AXDRIVER_AUX_DELAY, &delay);
        HSD_ASSERT(0xF72, HSD_AudioGetAuxHeapSize(2, &delay) < 71*1024);
        AXDriver_8038E30C(1, 4, &delay, lbl_80441064, sizeof(lbl_80441064));
    }

    HSD_SynthSFXAllocateBank(lbl_804D643C);
    HSD_SynthSFXAllocateBank(lbl_804D6440);
    HSD_SynthSFXAllocateBank(lbl_804D6444);

    for (i = 0; i < 56; i++) {
        lbl_804337C4[i] = -1;
        lbl_804338A4[i] = -1;
        lbl_80433984[i] = -1;
        lbl_80433A64[i] = -1;
    }

    lbl_804D3878 = -1;
    lbl_804D6448 = 0;
    lbl_804D644C = 0;
    lbl_804D6450 = 0;
}

void lbAudioAx_80028690(void)
{
    enum_t lang;

    lbAudioAx_80024BD0();
    fn_800244F4();
    fn_80024654(1);

    lang = setup_audio_lang();

    strcpy(cur_hps_file, str_audio);
    hps_stem_pos = 7;

    if (lbl_804D3878 == -1) {
        HSD_AudioSFXKeyOffAll();
        HSD_SynthSFXUnloadBank(0);
        if (lbl_80433984[0] < 1) {
            strcpy(&cur_ssm_file[ssm_stem_pos], ssm_files[0]);
            lbl_80433A64[0] = HSD_SynthSFXLoad(cur_ssm_file, 0, 0, 0);
            HSD_SynthSFXWaitForLoadCompletion(lb_800195D0);
            lbl_80433984[0] = 2;
        }
    }

    if (lbl_804D3878 != lang) {
        int i;

        lbl_804D3878 = lang;
        AXDriver_8038DCFC();
        strcpy(&cur_ssm_file[ssm_stem_pos], "smash2.sem");
        AXDriver_8038DA70(cur_ssm_file, lb_800195D0);

        for (i = 0; i < 55; i++) {
            if (i != 0) {
                lbl_80433A64[i] = -1;
                lbl_804337C4[i] = -1;
                lbl_804338A4[i] = -1;
                lbl_80433984[i] = -1;
            }
        }

        HSD_SynthSFXUnloadBank(1);
        HSD_SynthSFXUnloadBank(2);

        if (lbl_80433984[0x33] < 1) {
            strcpy(&cur_ssm_file[ssm_stem_pos], ssm_files[0x33]);
            lbl_80433A64[0x33] = HSD_SynthSFXLoad(cur_ssm_file, 1, 0, 0);
            HSD_SynthSFXWaitForLoadCompletion(lb_800195D0);
            lbl_80433984[0x33] = 2;
        }

        if (lbl_80433984[1] < 1) {
            strcpy(&cur_ssm_file[ssm_stem_pos], ssm_files[1]);
            lbl_80433A64[1] = HSD_SynthSFXLoad(cur_ssm_file, 1, 0, 0);
            HSD_SynthSFXWaitForLoadCompletion(lb_800195D0);
            lbl_80433984[1] = 2;
        }

        if (lbl_80433984[0x36] < 1) {
            strcpy(&cur_ssm_file[ssm_stem_pos], ssm_files[0x36]);
            lbl_80433A64[0x36] = HSD_SynthSFXLoad(cur_ssm_file, 1, 0, 0);
            HSD_SynthSFXWaitForLoadCompletion(lb_800195D0);
            lbl_80433984[0x36] = 2;
        }

        if (lbl_80433984[2] < 1) {
            strcpy(&cur_ssm_file[ssm_stem_pos], ssm_files[2]);
            lbl_80433A64[2] = HSD_SynthSFXLoad(cur_ssm_file, 2, 0, 0);
            HSD_SynthSFXWaitForLoadCompletion(lb_800195D0);
            lbl_80433984[2] = 2;
        }
    }

    {
        int i;
        for (i = 0; i <= 16; i++) {
            lbl_8043373C[i] = 0x83D60;
            lbl_80433780[i] = 0;
        }
    }

    lbl_804D6414 = 0;
    lbl_804D38E4 = 1.0F;
    lbl_804D38E8 = 1.0F;
    lbl_804D38EC = 1.0F;
    lbl_804D6418 = 0;
    lbl_804D640C = false;
    lbl_804D6420 = 0;
    lbl_804D6424 = 0;
    lbl_804D6428 = 0;
    lbl_804D642C = 0;
    lbl_804D38F0 = -1;
    lbl_804D38F4 = -1;
    lbl_804D6430 = 0;
    lbl_804D6434 = 0;
    lbl_804D38C4 = 1.0F;
    lbl_804D38C8 = 1.0F;
}

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
