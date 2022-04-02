#ifndef _texp_h_
#define _texp_h_

#include <dolphin/types.h>

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
    u32 clr_op;
    u32 clr_a;
    u32 clr_b;
    u32 clr_c;
    u32 clr_d;
    u32 clr_scale;
    u32 clr_bias;
    u32 clr_clamp;
    u32 clr_out_reg;
    u32 alpha_op;
    u32 alpha_a;
    u32 alpha_b;
    u32 alpha_c;
    u32 alpha_d;
    u32 alpha_scale;
    u32 alpha_bias;
    u32 alpha_clamp;
    u32 alpha_out_reg;
    u32 mode;
    u32 ras_swap;
    u32 tex_swap;
    u32 kcsel;
    u32 kasel;
} HSD_TevConf;

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
    struct _HSD_TObj* tobj;
} HSD_TExpTevDesc;

typedef struct _HSD_TECommon {
    HSD_TExpType type;
    union _HSD_TExp* next;
} HSD_TECommon;

typedef struct _HSD_TECnst {
    HSD_TExpType type;
    union _HSD_TExp* next;
    void* val;
    HSD_TEInput comp;
    HSD_TEType ctype;
    u8 reg;
    u8 idx;
    u8 ref;
    u8 range;
} HSD_TECnst;

typedef struct _HSD_TEArg {
    u8 type;
    u8 sel;
    u8 arg;
    union _HSD_TExp* exp;
} HSD_TEArg;

typedef struct _HSD_TETev {
    HSD_TExpType type;
    union _HSD_TExp* next;
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
    struct _HSD_TObj* tex;
    u8 chan;
} HSD_TETev;

typedef union _HSD_TExp {
    HSD_TExpType type;
    struct _HSD_TECommon comm;
    struct _HSD_TETev tev;
    struct _HSD_TECnst cnst;
} HSD_TExp;

HSD_TExpType HSD_TExpGetType(HSD_TExp* texp);

#endif
