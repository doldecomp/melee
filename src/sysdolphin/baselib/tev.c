#include <dolphin/gx/forward.h>

#include "tev.h"

#include "debug.h"

#include <__mem.h>
#include <placeholder.h>
#include <dolphin/gx/GXAttr.h>
#include <dolphin/gx/GXEnum.h>
#include <dolphin/gx/GXLight.h>
#include <dolphin/gx/GXTev.h>
#include <dolphin/gx/types.h>

static struct {
    GXColorS10 a;
    int c;
} TevReg[4] = { 0 };

static HSD_Chan prev_ch[4] = {
    { NULL, 0, 0, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 0, 0, 0, 0, 2, 0, NULL },
    { NULL, 1, 0, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 0, 0, 0, 0, 2, 2, NULL },
    { NULL, 2, 0, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 0, 0, 0, 0, 2, 0, NULL },
    { NULL, 3, 0, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 0, 0, 0, 0, 2, 2, NULL },
};

HSD_ObjAllocData render_alloc_data;
HSD_ObjAllocData tevreg_alloc_data;
HSD_ObjAllocData chan_alloc_data;

static int current_tev;
static int num_tex_gens;
static int prev_num_chans;

int prev_mat_invalid[2];
int prev_amb_invalid[2];

void HSD_RenderInitAllocData(void)
{
    HSD_ObjAllocInit(&render_alloc_data, 28, 4);
    HSD_ObjAllocInit(&tevreg_alloc_data, 20, 4);
    HSD_ObjAllocInit(&chan_alloc_data, 48, 4);
}

HSD_ObjAllocData* HSD_RenderGetAllocData(void)
{
    return &render_alloc_data;
}

HSD_ObjAllocData* HSD_TevRegGetAllocData(void)
{
    return &tevreg_alloc_data;
}

HSD_ObjAllocData* HSD_ChanGetAllocData(void)
{
    return &chan_alloc_data;
}

void HSD_SetupChannel(HSD_Chan* ch)
{
    int idx;
    GXChannelID chan;
    int no;

    NOT_IMPLEMENTED;
}

void HSD_StateSetNumChans(int num)
{
    if (prev_num_chans != num) {
        GXSetNumChans(num);
    }
}

void HSD_SetupChannelAll(HSD_Chan* channel)
{
    int num = 0;
    while (channel != NULL) {
        int temp = HSD_Channel2Num(channel->chan);
        if (temp > num) {
            num = temp;
        }
        HSD_SetupChannel(channel);
        channel = channel->next;
    }
    HSD_StateSetNumChans((u8) num);
}

int HSD_TexCoordID2Num(int);

void HSD_StateRegisterTexGen(int coord)
{
    int temp_r3 = HSD_TexCoordID2Num(coord);
    if (temp_r3 > num_tex_gens) {
        num_tex_gens = temp_r3;
    }
}

void HSD_StateSetNumTexGens(void)
{
    GXSetNumTexGens(num_tex_gens);
    num_tex_gens = 0;
}

void HSD_StateInitTev(void)
{
    current_tev = 0;
}

int HSD_StateGetNumTevStages(void)
{
    return current_tev;
}

int HSD_StateAssignTev(void)
{
    return HSD_Index2TevStage(current_tev++);
}

void HSD_StateSetNumTevStages(void)
{
    GXSetNumTevStages(current_tev);
    current_tev = 0;
}

void HSD_SetupTevStage(HSD_TevDesc* desc)
{
    u8 _[8] = { 0 };
    GXSetTevOrder(desc->stage, desc->coord, desc->map, desc->color);
    if (desc->flags == 0) {
        /// @todo Incorrect cast.
        GXSetTevOp(desc->stage, (GXTevMode) desc->u.tevconf.clr_op);
        GXSetTevSwapMode(desc->stage, GX_TEV_SWAP0, GX_TEV_SWAP0);
        return;
    }
    GXSetTevColorOp(desc->stage, desc->u.tevconf.clr_op,
                    desc->u.tevconf.clr_bias, desc->u.tevconf.clr_scale,
                    desc->u.tevconf.clr_clamp, desc->u.tevconf.clr_out_reg);
    GXSetTevColorIn(desc->stage, desc->u.tevconf.clr_a, desc->u.tevconf.clr_b,
                    desc->u.tevconf.clr_c, desc->u.tevconf.clr_d);
    GXSetTevAlphaOp(desc->stage, desc->u.tevconf.alpha_op,
                    desc->u.tevconf.alpha_bias, desc->u.tevconf.alpha_scale,
                    desc->u.tevconf.alpha_clamp,
                    desc->u.tevconf.alpha_out_reg);
    GXSetTevAlphaIn(desc->stage, desc->u.tevconf.alpha_a,
                    desc->u.tevconf.alpha_b, desc->u.tevconf.alpha_c,
                    desc->u.tevconf.alpha_d);
    GXSetTevSwapMode(desc->stage, desc->u.tevconf.ras_swap,
                     desc->u.tevconf.tex_swap);
    GXSetTevKColorSel(desc->stage, desc->u.tevconf.kcsel);
    GXSetTevKAlphaSel(desc->stage, desc->u.tevconf.kasel);
}

#pragma push
#pragma dont_inline on
void HSD_SetupTevStageAll(HSD_TevDesc* desc)
{
    int var_r31 = 0;
    while (desc != NULL) {
        int temp_r3 = HSD_TevStage2Num(desc->stage);
        if (temp_r3 > var_r31) {
            var_r31 = temp_r3;
        }
        HSD_SetupTevStage(desc);
        desc = desc->next;
    }
    current_tev = var_r31;
    GXSetNumTevStages(current_tev);
    current_tev = 0;
}
#pragma pop

int HSD_Channel2Num(int chan)
{
    switch (chan) {
    case 0:
        return 1;
    case 1:
        return 2;
    case 2:
        return 1;
    case 3:
        return 2;
    case 4:
        return 1;
    case 5:
        return 2;
    case 0xFF:
        return 0;
    default:
        HSD_ASSERT(656, 0);
        return 0;
    }
}

int HSD_Index2TevStage(int idx)
{
    switch (idx) {
    case 0:
        return 0;
    case 1:
        return 1;
    case 2:
        return 2;
    case 3:
        return 3;
    case 4:
        return 4;
    case 5:
        return 5;
    case 6:
        return 6;
    case 7:
        return 7;
    case 8:
        return 8;
    case 9:
        return 9;
    case 10:
        return 10;
    case 11:
        return 11;
    case 12:
        return 12;
    case 13:
        return 13;
    case 14:
        return 14;
    case 15:
        return 15;
    default:
        HSD_ASSERT(709, 0);
        return 15;
    }
}

#pragma push
#pragma force_active on
int HSD_TevStage2Index(int stage)
{
    switch (stage) {
    case 0:
        return 0;
    case 1:
        return 1;
    case 2:
        return 2;
    case 3:
        return 3;
    case 4:
        return 4;
    case 5:
        return 5;
    case 6:
        return 6;
    case 7:
        return 7;
    case 8:
        return 8;
    case 9:
        return 9;
    case 10:
        return 10;
    case 11:
        return 11;
    case 12:
        return 12;
    case 13:
        return 13;
    case 14:
        return 14;
    case 15:
        return 15;
    default:
        HSD_ASSERT(762, 0);
        return 0;
    }
}
#pragma pop

int HSD_TevStage2Num(int stage)
{
    switch (stage) {
    case 0:
        return 1;
    case 1:
        return 2;
    case 2:
        return 3;
    case 3:
        return 4;
    case 4:
        return 5;
    case 5:
        return 6;
    case 6:
        return 7;
    case 7:
        return 8;
    case 8:
        return 9;
    case 9:
        return 10;
    case 10:
        return 11;
    case 11:
        return 12;
    case 12:
        return 13;
    case 13:
        return 14;
    case 14:
        return 15;
    case 15:
        return 16;
    default:
        HSD_ASSERT(793, 0);
        return 0;
    }
}

void HSD_SetTevRegAll(void)
{
    u32 i;
    for (i = 0; i < 4; i++) {
        if (TevReg[i].c != 0) {
            int reg;
            switch (i) {
            case 0:
                reg = 1;
                break;
            case 1:
                reg = 2;
                break;
            case 2:
                reg = 3;
                break;
            case 3:
                reg = 0;
                break;
            default:
                reg = 1;
                break;
            }
            GXSetTevColorS10(reg, TevReg[i].a);
            TevReg[i].c = 0;
        }
    }
}

int HSD_TexCoordID2Num(int id)
{
    switch (id) {
    case 0:
        return 1;
    case 1:
        return 2;
    case 2:
        return 3;
    case 3:
        return 4;
    case 4:
        return 5;
    case 5:
        return 6;
    case 6:
        return 7;
    case 7:
        return 8;
    case 0xFF:
        return 0;
    default:
        HSD_ASSERT(1010, 0);
        return 0;
    }
}

#pragma push
#pragma force_active on
void ChanUpdateFunc(HSD_Chan* chan, int arg1, f32* arg2)
{
    if (chan != NULL) {
        switch (arg1) {
        case 5:
            chan->mat_color.r = 255.0 * *arg2;
            return;
        case 6:
            chan->mat_color.g = 255.0 * *arg2;
            return;
        case 7:
            chan->mat_color.b = 255.0 * *arg2;
            return;
        case 8:
            chan->mat_color.a = 255.0 * *arg2;
            return;
        case 9:
            chan->amb_color.r = 255.0 * *arg2;
            return;
        case 10:
            chan->amb_color.g = 255.0 * *arg2;
            return;
        case 11:
            chan->amb_color.b = 255.0 * *arg2;
            return;
        case 12:
            chan->amb_color.a = 255.0 * *arg2;
            break;
        }
    }
}
#pragma pop

static HSD_Chan invalid_prev_ch[4] = {
    { NULL, 0, 0, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 0, 0, 0, 0, 2, 0, NULL },
    { NULL, 1, 0, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 0, 0, 0, 0, 2, 2, NULL },
    { NULL, 2, 0, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 0, 0, 0, 0, 2, 0, NULL },
    { NULL, 3, 0, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 0, 0, 0, 0, 2, 2, NULL },
};

void _HSD_StateInvalidateColorChannel(void)
{
    memcpy(&prev_ch, &invalid_prev_ch, sizeof(prev_ch));
    prev_amb_invalid[0] = 1;
    prev_amb_invalid[1] = 1;
    prev_mat_invalid[0] = 1;
    prev_mat_invalid[1] = 1;
    prev_num_chans = -1;
}

void _HSD_StateInvalidateTevStage(void)
{
    current_tev = 0;
}

void _HSD_StateInvalidateTevRegister(void)
{
    int i;
    for (i = 0; i < 4; i++) {
        TevReg[i].c = 0;
    }
}

void _HSD_StateInvalidateTexCoordGen(void)
{
    num_tex_gens = 0;
}
