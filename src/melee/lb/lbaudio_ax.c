#include "lbaudio_ax.static.h"

#include <melee/ft/forward.h>

#include <baselib/axdriver.h>
#include <baselib/synth.h>
#include <melee/gr/stage.h>
#include <melee/lb/lblanguage.h>

extern s8 flags_arr_803BB800[0x62];

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

/// #fn_80023254

/// #lbAudioAx_800233EC

/// #lbAudioAx_80023694

int lbAudioAx_800236B8(int arg0)
{
    AXDriverKeyOff(arg0);
    return -1;
}

/// #lbAudioAx_800236DC

bool lbAudioAx_80023710(int arg0)
{
    return AXDriver_8038D9D8(arg0);
}

/// #lbAudioAx_80023730

/// #fn_80023750

/// #lbAudioAx_800237A8

/// #lbAudioAx_80023870

/// #lbAudioAx_8002392C

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

/// #fn_80023ED4

/// #lbAudioAx_80023F28

/// #lbAudioAx_80024030

/// #lbAudioAx_800240B4

/// #lbAudioAx_8002411C

/// #lbAudioAx_80024184

/// #lbAudioAx_80024304

/// #lbAudioAx_8002438C

/// #lbAudioAx_800243F4

/// #fn_800244F4

/// #lbAudioAx_800245D4

/// #lbAudioAx_800245F4

/// #lbAudioAx_80024614

/// #lbAudioAx_80024634

/// #fn_80024654

/// #lbAudioAx_80024B1C

/// #lbAudioAx_80024B58

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

/// #lbAudioAx_80024BD0

/// #lbAudioAx_80024C08

/// #lbAudioAx_80024C84

/// #lbAudioAx_80024D50

/// #lbAudioAx_80024D78

/// #lbAudioAx_80024DC4

/// #lbAudioAx_80024E50

/// #lbAudioAx_80024E84

/// #lbAudioAx_80024F08

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

/// #lbAudioAx_8002500C

/// #lbAudioAx_80025038

/// #lbAudioAx_80025064

void lbAudioAx_80025098(s32 arg0)
{
    lbl_804D6408 = arg0;
}

/// #fn_800250A0

/// #fn_800251EC

/// #fn_800253D8

/// #fn_800256BC

/// #fn_800259A0

/// #fn_800259EC

/// #fn_80025A98

/// #fn_80025B44

/// #fn_80025CBC

/// #fn_80025E38

/// #fn_80025FAC

/// #fn_800262A0

/// #fn_800263B4

/// #lbAudioAx_800263E8

/// #lbAudioAx_800264E4

/// #lbAudioAx_80026510

/// #lbAudioAx_800265C4

/// #fn_80026650

/// #fn_800267B0

/// #fn_800268B4

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

/// #lbAudioAx_80026F2C

/// #lbAudioAx_8002702C

/// #lbAudioAx_80027168

/// #fn_80027488

/// #lbAudioAx_80027648

/// #lbAudioAx_8002785C

/// #lbAudioAx_80027AB0

extern int lbl_804D6418;

void lbAudioAx_80027DBC(void)
{
    HSD_AudioSFXKeyOffAll();
    AXDriverStop();
    lbl_804D6418 = 0;
    lbl_803BB300[0] = '\0';
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

/// #lbAudioAx_80028B2C

/// #lbAudioAx_80028B4C

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
