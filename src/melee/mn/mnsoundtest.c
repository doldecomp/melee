#include <platform.h>

#include <baselib/forward.h>

#include "lb/lbarchive.h"
#include "sc/types.h"

#include <dolphin/os.h>
#include <baselib/controller.h>
#include <baselib/debug.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjplink.h>
#include <baselib/gobjproc.h>
#include <baselib/gobjuserdata.h>
#include <baselib/jobj.h>
#include <baselib/memory.h>
#include <baselib/sislib.h>

extern HSD_PadStatus HSD_PadCopyStatus[4];

f32 mnSoundTest_803EF0A8[] = { 0,    19,   -0.1, 20,   39,   -0.1, 0,
                               20,   -0.1, 0,    0,    -0.1, 0,    200,
                               0,    0,    10,   -0.1, -2,   -6.6, 0,
                               -1.7, -4.7, 0,    -1.7, 2 };

void gmMainLib_8015ED74(void); /* extern */
s32 gm_801601C4(void);         /* extern */
s32 gm_80160244(void);         /* extern */
void lbAudioAx_800245F4(s32);  /* extern */
void lbAudioAx_80024614(s32);  /* extern */
extern s32 mnSoundTest_804D6C48;
extern s32 mnSoundTest_804D6C4C;

typedef struct {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    UNK_T unk10;
    HSD_Text* unk14;
    HSD_Text* unk18;
} soundtest_user_data;

void mnSoundTest_8024A790(HSD_GObj* arg0)
{
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f30;
    f32 temp_f31;
    s32 temp_r30;
    s32 temp_r30_2;
    s32 temp_r3;
    s32 temp_r3_2;

    soundtest_user_data* temp_r31 = (soundtest_user_data*) arg0->user_data;
    // control the volume by holding down L trigger
    temp_f31 = 1.0f * (1.0f - HSD_PadCopyStatus->nml_analogL) *
               (1.0f - HSD_PadCopyStatus[1].nml_analogL) *
               (1.0f - HSD_PadCopyStatus[2].nml_analogL) *
               (1.0f - HSD_PadCopyStatus[3].nml_analogL);
    // R trigger doesn't seem to do anything
    temp_f30 = 1.0f * (1.0f - HSD_PadCopyStatus->nml_analogR) *
               (1.0f - HSD_PadCopyStatus[1].nml_analogR) *
               (1.0f - HSD_PadCopyStatus[2].nml_analogR) *
               (1.0f - HSD_PadCopyStatus[3].nml_analogR);
    if ((temp_f31 < 0.9f) || (temp_r31->unk8 < 1.0f)) {
        gmMainLib_8015ED74();
        temp_f1 = temp_f31 * (f32) gm_801601C4();
        temp_r30 = (s32) (temp_r31->unk8 * temp_f1);
        lbAudioAx_80024614(temp_r30);
        mnSoundTest_804D6C48 = temp_r30;
    } else {
        gmMainLib_8015ED74();
        temp_r3 = gm_801601C4();
        if (temp_r3 != (s32) mnSoundTest_804D6C48) {
            lbAudioAx_80024614(temp_r3);
            mnSoundTest_804D6C48 = temp_r3;
        }
    }
    if ((temp_f30 < 0.9f) || (temp_r31->unkC < 1.0f)) {
        gmMainLib_8015ED74();
        temp_f1_2 = temp_f30 * (f32) gm_80160244();
        temp_r30_2 = (s32) (temp_r31->unkC * temp_f1_2);
        lbAudioAx_800245F4(temp_r30_2);
        mnSoundTest_804D6C4C = temp_r30_2;
        return;
    }
    gmMainLib_8015ED74();
    temp_r3_2 = gm_80160244();
    if (temp_r3_2 != (s32) mnSoundTest_804D6C4C) {
        lbAudioAx_800245F4(temp_r3_2);
        mnSoundTest_804D6C4C = temp_r3_2;
    }
}
