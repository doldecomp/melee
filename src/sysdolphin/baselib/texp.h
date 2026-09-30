/**
 * @file texp.h
 * @brief Texture Expression (TExp) compilation system
 * @details Implements the TEV color combiner expression tree compiler for GameCube GX hardware.
 * Module prefix: HSD_TExp
 */
#ifndef _texp_h_
#define _texp_h_

#include <Runtime/platform.h>

#include <sysdolphin/baselib/forward.h>

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
    struct HSD_TExpRes_reg {
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
    union _HSD_TevDesc_u {
        HSD_TevConf tevconf;
        struct _HSD_TevDesc_u_tevop {
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

/**
 * @brief Returns the expression node type (TEV, TEX, RAS, CNST, etc.).
 * @param texp Texture expression node
 * @return Node type enum
 */
HSD_TExpType HSD_TExpGetType(HSD_TExp* texp);
/**
 * @brief Allocates and initializes a TEV stage expression node, prepending it to the given list.
 * @param list Pointer to the expression list head
 * @return The new TEV expression node
 */
HSD_TExp* HSD_TExpTev(HSD_TExp**);
/**
 * @brief Finds or allocates a constant color/alpha expression node.
 * @param val Pointer to the constant value
 * @param comp Component type (RGB, A, X)
 * @param type Data type of val
 * @param list Pointer to the expression list head
 * @return The constant expression node
 */
HSD_TExp* HSD_TExpCnst(void*, HSD_TEInput, HSD_TEType, HSD_TExp**);
/**
 * @brief Sets the texture object and color channel order for a TEV expression.
 * @param texp TEV expression node
 * @param tex Texture object (TObj)
 * @param chan Color channel ID
 */
void HSD_TExpOrder(HSD_TExp*, HSD_TObj*, GXChannelID);

/**
 * @brief Sets the color operation, bias, scale, and clamp for a TEV expression.
 * @param texp TEV expression node
 * @param op TEV color operation
 * @param bias TEV bias
 * @param scale TEV scale
 * @param clamp Clamp enable flag
 */
void HSD_TExpColorOp(HSD_TExp*, GXTevOp, GXTevBias, GXTevScale, u8);
/**
 * @brief Maps inputs (A, B, C, D) for the TEV color stage equation.
 * @param texp TEV expression node
 * @param sel_a Selector for input A
 * @param exp_a Expression for input A
 * @param sel_b Selector for input B
 * @param exp_b Expression for input B
 * @param sel_c Selector for input C
 * @param exp_c Expression for input C
 * @param sel_d Selector for input D
 * @param exp_d Expression for input D
 */
void HSD_TExpColorIn(HSD_TExp*, HSD_TEInput, HSD_TExp*, HSD_TEInput, HSD_TExp*,
                     HSD_TEInput, HSD_TExp*, HSD_TEInput, HSD_TExp*);
/**
 * @brief Sets the alpha operation, bias, scale, and clamp for a TEV expression.
 * @param texp TEV expression node
 * @param op TEV alpha operation
 * @param bias TEV bias
 * @param scale TEV scale
 * @param clamp Clamp enable flag
 */
void HSD_TExpAlphaOp(HSD_TExp*, GXTevOp, GXTevBias, GXTevScale, u8);
/**
 * @brief Maps inputs (A, B, C, D) for the TEV alpha stage equation.
 * @param texp TEV expression node
 * @param sel_a Selector for input A
 * @param exp_a Expression for input A
 * @param sel_b Selector for input B
 * @param exp_b Expression for input B
 * @param sel_c Selector for input C
 * @param exp_c Expression for input C
 * @param sel_d Selector for input D
 * @param exp_d Expression for input D
 */
void HSD_TExpAlphaIn(HSD_TExp* texp, HSD_TEInput sel_a, HSD_TExp* exp_a,
                     HSD_TEInput sel_b, HSD_TExp* exp_b, HSD_TEInput sel_c,
                     HSD_TExp* exp_c, HSD_TEInput sel_d, HSD_TExp* exp_d);

/**
 * @brief Frees a TEV descriptor list.
 * @param desc Pointer to TEV descriptor list
 */
void HSD_TExpFreeTevDesc(HSD_TExpTevDesc*);
/**
 * @brief Frees an expression list, selectively keeping referenced nodes if free_all is 0.
 * @param texp_list Expression list head
 * @param type Node type to free (or HSD_TE_ALL)
 * @param free_all If non-zero, unconditionally frees nodes matching the type
 * @return Updated expression list head
 */
HSD_TExp* HSD_TExpFreeList(HSD_TExp*, HSD_TExpType, s32);
/**
 * @brief Compiles the expression tree into GX TEV descriptors.
 * @param texp Root of the expression tree
 * @param desc Pointer to store the compiled TEV descriptors
 * @param list Pointer to expression list to manage lifecycle
 * @return Status flag (0 on success)
 */
int HSD_TExpCompile(HSD_TExp*, HSD_TExpTevDesc**, HSD_TExp**);
/**
 * @brief Loads compiled TEV descriptors into GX hardware registers.
 * @param desc TEV descriptor list
 * @param texp Associated expression tree
 */
void HSD_TExpSetupTev(HSD_TExpTevDesc*, HSD_TExp*);

/**
 * @brief Frees a single expression node.
 * @param texp Expression node
 */
void HSD_TExpFree(HSD_TExp* texp);
/**
 * @brief Increments the reference count of an expression node.
 * @param texp Expression node
 * @param sel Color/Alpha selector flag
 */
void HSD_TExpRef(HSD_TExp* texp, u8 sel);
/**
 * @brief Decrements the reference count of an expression node and frees descendants if zero.
 * @param texp Expression node
 * @param sel Color/Alpha selector flag
 */
void HSD_TExpUnref(HSD_TExp* texp, u8 sel);
/**
 * @brief Applies constant register values to the GX hardware.
 * @param texp Constant expression node
 */
void HSD_TExpSetReg(HSD_TExp* texp);

/**
 * @brief Checks if the color operation is a pass-through (A+B where A=0, B=0).
 * @param texp TEV expression node
 * @return true if pass-through
 */
static inline bool IsThroughColor(HSD_TExp* texp)
{
    return texp->tev.c_op == GX_TEV_ADD && texp->tev.c_in[0].sel == HSD_TE_0 &&
           texp->tev.c_in[1].sel == HSD_TE_0 && texp->tev.c_bias == 0 &&
           texp->tev.c_scale == 0;
}

/**
 * @brief Checks if the alpha operation is a pass-through.
 * @param texp TEV expression node
 * @return true if pass-through
 */
static inline bool IsThroughAlpha(HSD_TExp* texp)
{
    return texp->tev.a_op == GX_TEV_ADD && texp->tev.a_in[0].sel == HSD_TE_0 &&
           texp->tev.a_in[1].sel == HSD_TE_0 && texp->tev.a_bias == 0 &&
           texp->tev.a_scale == 0;
}

#endif
