#ifndef _texp_h_
#define _texp_h_

#include <platform.h>

#include "baselib/forward.h"

#include <dolphin/gx/GXEnum.h>

#define HSD_TEXP_RAS ((HSD_TExp*) -2)
#define HSD_TEXP_TEX ((HSD_TExp*) -1)
#define HSD_TEXP_ZERO ((HSD_TExp*) 0)

#define TEVCONF_MODE 1

typedef enum _HSD_TEInput {
    HSD_TE_END = 0,
    HSD_TE_RGB = 1,
    HSD_TE_R = 2,
    HSD_TE_G = 3,
    HSD_TE_B = 4,
    HSD_TE_A = 5,
    HSD_TE_X = 6,
    HSD_TE_0 = 7,
    HSD_TE_1 = 8,
    HSD_TE_1_8 = 9,
    HSD_TE_2_8 = 10,
    HSD_TE_3_8 = 11,
    HSD_TE_4_8 = 12,
    HSD_TE_5_8 = 13,
    HSD_TE_6_8 = 14,
    HSD_TE_7_8 = 15,
    HSD_TE_INPUT_MAX = 16,
    HSD_TE_UNDEF = 0xFF
} HSD_TEInput;

typedef enum _HSD_TEType {
    HSD_TE_U8 = 0,
    HSD_TE_U16 = 1,
    HSD_TE_U32 = 2,
    HSD_TE_F32 = 3,
    HSD_TE_F64 = 4,
    HSD_TE_COMP_TYPE_MAX = 5
} HSD_TEType;

typedef enum _HSD_TExpType {
    HSD_TE_ZERO = 0,
    HSD_TE_TEV = 1,
    HSD_TE_TEX = 2,
    HSD_TE_RAS = 3,
    HSD_TE_CNST = 4,
    HSD_TE_IMM = 5,
    HSD_TE_KONST = 6,
    HSD_TE_ALL = 7,
    HSD_TE_TYPE_MAX = 8
} HSD_TExpType;

typedef struct _HSD_TevConf {
    GXTevOp clr_op;
    GXTevColorArg clr_a;
    GXTevColorArg clr_b;
    GXTevColorArg clr_c;
    GXTevColorArg clr_d;
    GXTevScale clr_scale;
    GXTevBias clr_bias;
    u8 clr_clamp;
    GXTevRegID clr_out_reg;
    GXTevOp alpha_op;
    GXTevAlphaArg alpha_a;
    GXTevAlphaArg alpha_b;
    GXTevAlphaArg alpha_c;
    GXTevAlphaArg alpha_d;
    GXTevScale alpha_scale;
    GXTevBias alpha_bias;
    u8 alpha_clamp;
    GXTevRegID alpha_out_reg;
    GXTevClampMode mode;
    GXTevSwapSel ras_swap;
    GXTevSwapSel tex_swap;
    GXTevKColorSel kcsel;
    GXTevKAlphaSel kasel;
} HSD_TevConf;

typedef struct HSD_TExpRes {
    int failed;
    int texmap;
    int cnst_remain;
    struct {
        u8 color;
        u8 alpha;
    } reg[8];
    u8 c_ref[4];
    u8 a_ref[4];
    u8 c_use[4];
    u8 a_use[4];
} HSD_TExpRes;

typedef struct _HSD_TevDesc {
    struct _HSD_TevDesc* next;
    u32 flags;
    u32 stage;
    u32 coord;
    u32 map;
    u32 color;
    union {
        HSD_TevConf tevconf;
        struct {
            u32 tevmode;
        } tevop;
    } u;
} HSD_TevDesc;

typedef struct _HSD_TExpTevDesc {
    struct _HSD_TevDesc desc;
    HSD_TObj* tobj;
} HSD_TExpTevDesc;

typedef struct _HSD_TECommon {
    HSD_TExpType type;
    HSD_TExp* next;
} HSD_TECommon;

typedef struct _HSD_TECnst {
    HSD_TExpType type; ///< must be HSD_TE_CNST for this union member
    HSD_TExp* next;
    void* val;
    HSD_TEInput comp; ///< if TE_RGB, val points to RGB array, else 1 value
    HSD_TEType ctype; ///< pointer type of val
    u8 reg;
    u8 idx;
    u8 ref;
    u8 range;
} HSD_TECnst;

typedef struct _HSD_TEArg {
    u8 type;
    u8 sel;
    u8 arg;
    HSD_TExp* exp;
} HSD_TEArg;

typedef struct _HSD_TETev {
    HSD_TExpType type;
    HSD_TExp* next;
    s32 c_ref;
    u8 c_dst;
    u8 c_op;
    u8 c_clamp;
    u8 c_bias;
    u8 c_scale;
    u8 c_range;
    s32 a_ref;
    u8 a_dst;
    u8 a_op;
    u8 a_clamp;
    u8 a_bias;
    u8 a_scale;
    u8 tex_swap;
    u8 ras_swap;
    u8 kcsel;
    u8 kasel;
    HSD_TEArg c_in[4];
    HSD_TEArg a_in[4];
    HSD_TObj* tex;
    u8 chan;
} HSD_TETev;

union HSD_TExp {
    HSD_TExpType type;
    struct _HSD_TECommon comm;
    struct _HSD_TETev tev;
    struct _HSD_TECnst cnst;
};

HSD_TExpType HSD_TExpGetType(HSD_TExp* texp);
HSD_TExp* HSD_TExpTev(HSD_TExp**);
HSD_TExp* HSD_TExpCnst(void*, HSD_TEInput, HSD_TEType, HSD_TExp**);
void HSD_TExpOrder(HSD_TExp*, HSD_TObj*, GXChannelID);

void HSD_TExpColorOp(HSD_TExp*, GXTevOp, GXTevBias, GXTevScale, u8);
void HSD_TExpColorIn(HSD_TExp*, HSD_TEInput, HSD_TExp*, HSD_TEInput, HSD_TExp*,
                     HSD_TEInput, HSD_TExp*, HSD_TEInput, HSD_TExp*);
void HSD_TExpAlphaOp(HSD_TExp*, GXTevOp, GXTevBias, GXTevScale, u8);
void HSD_TExpAlphaIn(HSD_TExp* texp, HSD_TEInput sel_a, HSD_TExp* exp_a,
                     HSD_TEInput sel_b, HSD_TExp* exp_b, HSD_TEInput sel_c,
                     HSD_TExp* exp_c, HSD_TEInput sel_d, HSD_TExp* exp_d);

void HSD_TExpFreeTevDesc(HSD_TExpTevDesc*);
HSD_TExp* HSD_TExpFreeList(HSD_TExp*, HSD_TExpType, s32);
int HSD_TExpCompile(HSD_TExp*, HSD_TExpTevDesc**, HSD_TExp**);
void HSD_TExpSetupTev(HSD_TExpTevDesc*, HSD_TExp*);

void HSD_TExpFree(HSD_TExp* texp);
void HSD_TExpRef(HSD_TExp* texp, u8 sel);
void HSD_TExpUnref(HSD_TExp* texp, u8 sel);
void HSD_TExpSetReg(HSD_TExp* texp);

#endif
