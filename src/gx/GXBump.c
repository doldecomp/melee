#include <dolphin/gx.h>
#include <dolphin/os.h>
#include <macros.h>

#include "__gx.h"

#if DEBUG
#define GX_WRITE_SOME_REG5(a, b) \
do { \
    GX_WRITE_U8(a); \
    GX_WRITE_U32(b); \
    __gxVerif->rasRegs[(b >> 24) & 0xFF] = b; \
} while (0)
#else
#define GX_WRITE_SOME_REG5(a, b) \
do { \
    GX_WRITE_U8(a); \
    GX_WRITE_U32(b); \
} while (0)
#endif

void GXSetTevIndirect(GXTevStageID tev_stage, GXIndTexStageID ind_stage, GXIndTexFormat format, GXIndTexBiasSel bias_sel, GXIndTexMtxID matrix_sel, GXIndTexWrap wrap_s, GXIndTexWrap wrap_t, GXBool add_prev, GXBool utc_lod, GXIndTexAlphaSel alpha_sel)
{
    u32 reg;

    CHECK_GXBEGIN(0x7F, "GXInitIndTexture");
    reg = 0;
    SET_REG_FIELD(0x81, reg, 2, 0, ind_stage);
    SET_REG_FIELD(0x82, reg, 2, 2, format);
    SET_REG_FIELD(0x83, reg, 3, 4, bias_sel);
    SET_REG_FIELD(0x84, reg, 2, 7, alpha_sel);
    SET_REG_FIELD(0x85, reg, 4, 9, matrix_sel);
    SET_REG_FIELD(0x86, reg, 3, 13, wrap_s);
    SET_REG_FIELD(0x87, reg, 3, 16, wrap_t);
    SET_REG_FIELD(0x88, reg, 1, 19, utc_lod);
    SET_REG_FIELD(0x89, reg, 1, 20, add_prev);
    SET_REG_FIELD(0x8A, reg, 8, 24, tev_stage + 16);
    GX_WRITE_SOME_REG5(0x61, reg);
    gx->bpSent = 1;
}

void GXSetIndTexMtx(GXIndTexMtxID mtx_id, f32 offset[2][3], s8 scale_exp)
{
    s32 mtx[6];
    u32 reg;
    u32 id;

    CHECK_GXBEGIN(0xA7, "GXSetIndTexMtx");

    switch (mtx_id) {
    case GX_ITM_0:
    case GX_ITM_1:
    case GX_ITM_2:
        id = mtx_id - 1;
        break;
    case GX_ITM_S0:
    case GX_ITM_S1:
    case GX_ITM_S2:
        id = mtx_id - 5;
        break;
    case GX_ITM_T0:
    case GX_ITM_T1:
    case GX_ITM_T2:
        id = mtx_id - 9;
        break;
    default:
        id = 0;
        break;
    }

    mtx[0] = (int)(1024.0f * offset[0][0]) & 0x7FF;
    mtx[1] = (int)(1024.0f * offset[1][0]) & 0x7FF;
    scale_exp += 0x11;
    reg = 0;
    SET_REG_FIELD(0xBD, reg, 11, 0, mtx[0]);
    SET_REG_FIELD(0xBE, reg, 11, 11, mtx[1]);
    SET_REG_FIELD(0xBF, reg, 2, 22, scale_exp & 3);
    SET_REG_FIELD(0xC0, reg, 8, 24, id * 3 + 6);
    GX_WRITE_SOME_REG5(0x61, reg);

    mtx[2] = (int)(1024.0f * offset[0][1]) & 0x7FF;
    mtx[3] = (int)(1024.0f * offset[1][1]) & 0x7FF;
    reg = 0;
    SET_REG_FIELD(0xC6, reg, 11, 0, mtx[2]);
    SET_REG_FIELD(0xC7, reg, 11, 11, mtx[3]);
    SET_REG_FIELD(0xC8, reg, 2, 22, (scale_exp >> 2) & 3);
    SET_REG_FIELD(0xC9, reg, 8, 24, id * 3 + 7);
    GX_WRITE_SOME_REG5(0x61, reg);

    mtx[4] = (int)(1024.0f * offset[0][2]) & 0x7FF;
    mtx[5] = (int)(1024.0f * offset[1][2]) & 0x7FF;
    reg = 0;
    SET_REG_FIELD(0xCF, reg, 11, 0, mtx[4]);
    SET_REG_FIELD(0xD0, reg, 11, 11, mtx[5]);
    SET_REG_FIELD(0xD1, reg, 2, 22, (scale_exp >> 4) & 3);
    SET_REG_FIELD(0xD2, reg, 8, 24, id * 3 + 8);
    GX_WRITE_SOME_REG5(0x61, reg);

    gx->bpSent = 1;
}

void GXSetIndTexCoordScale(GXIndTexStageID ind_state, GXIndTexScale scale_s, GXIndTexScale scale_t)
{
    CHECK_GXBEGIN(0xE6, "GXSetIndTexScale");

    switch (ind_state) {
    case GX_INDTEXSTAGE0:
        SET_REG_FIELD(0xEA, gx->IndTexScale0, 4, 0, scale_s);
        SET_REG_FIELD(0xEB, gx->IndTexScale0, 4, 4, scale_t);
        SET_REG_FIELD(0xEC, gx->IndTexScale0, 8, 24, 0x25);
        GX_WRITE_SOME_REG5(0x61, gx->IndTexScale0);
        break;
    case GX_INDTEXSTAGE1:
        SET_REG_FIELD(0xF0, gx->IndTexScale0, 4, 8, scale_s);
        SET_REG_FIELD(0xF1, gx->IndTexScale0, 4, 12, scale_t);
        SET_REG_FIELD(0xF2, gx->IndTexScale0, 8, 24, 0x25);
        GX_WRITE_SOME_REG5(0x61, gx->IndTexScale0);
        break;
    case GX_INDTEXSTAGE2:
        SET_REG_FIELD(0xF6, gx->IndTexScale1, 4, 0, scale_s);
        SET_REG_FIELD(0xF7, gx->IndTexScale1, 4, 4, scale_t);
        SET_REG_FIELD(0xF8, gx->IndTexScale1, 8, 24, 0x26);
        GX_WRITE_SOME_REG5(0x61, gx->IndTexScale1);
        break;
    case GX_INDTEXSTAGE3:
        SET_REG_FIELD(0xFC, gx->IndTexScale1, 4, 8, scale_s);
        SET_REG_FIELD(0xFD, gx->IndTexScale1, 4, 12, scale_t);
        SET_REG_FIELD(0xFE, gx->IndTexScale1, 8, 24, 0x26);
        GX_WRITE_SOME_REG5(0x61, gx->IndTexScale1);
        break;
    default:
        ASSERTMSGLINE(0x102, 0, "GXSetIndTexCoordScale: Invalid Indirect Stage Id");
        break;
    }
    gx->bpSent = 1;
}

void GXSetIndTexOrder(GXIndTexStageID ind_stage, GXTexCoordID tex_coord, GXTexMapID tex_map)
{
    CHECK_GXBEGIN(0x11B, "GXSetIndTexOrder");

    ASSERTMSGLINE(0x11D, tex_map < 8, "GXSetIndTexOrder: Invalid direct texture Id");
    ASSERTMSGLINE(0x11E, tex_coord < 8, "GXSetIndTexOrder: Invalid texture coord");

    switch (ind_stage) {
    case GX_INDTEXSTAGE0:
        SET_REG_FIELD(0x122, gx->iref, 3, 0, tex_map);
        SET_REG_FIELD(0x123, gx->iref, 3, 3, tex_coord);
        break;
    case GX_INDTEXSTAGE1:
        SET_REG_FIELD(0x126, gx->iref, 3, 6, tex_map);
        SET_REG_FIELD(0x127, gx->iref, 3, 9, tex_coord);
        break;
    case GX_INDTEXSTAGE2:
        SET_REG_FIELD(0x12A, gx->iref, 3, 12, tex_map);
        SET_REG_FIELD(0x12B, gx->iref, 3, 15, tex_coord);
        break;
    case GX_INDTEXSTAGE3:
        SET_REG_FIELD(0x12E, gx->iref, 3, 18, tex_map);
        SET_REG_FIELD(0x12F, gx->iref, 3, 21, tex_coord);
        break;
    default:
        ASSERTMSGLINE(0x132, 0, "GXSetIndTexOrder: Invalid Indirect Stage Id");
        break;
    }
    GX_WRITE_SOME_REG5(0x61, gx->iref);
    gx->dirtyState |= 3;
    gx->bpSent = 1;
}

void GXSetNumIndStages(u8 nIndStages)
{
    CHECK_GXBEGIN(0x144, "GXSetNumIndStages");
    ASSERTMSGLINE(0x146, nIndStages <= 4, "GXSetNumIndStages: Exceeds max. number of indirect texture stages");
    SET_REG_FIELD(0x147, gx->genMode, 3, 16, nIndStages);
    gx->dirtyState |= 6;
}

void GXSetTevDirect(GXTevStageID tev_stage)
{
    CHECK_GXBEGIN(0x158, "GXSetTevDirect");
    GXSetTevIndirect(tev_stage, GX_INDTEXSTAGE0, GX_ITF_8, GX_ITB_NONE, GX_ITM_OFF, GX_ITW_OFF, GX_ITW_OFF, 0U, 0, 0);
}

void GXSetTevIndWarp(GXTevStageID tev_stage, GXIndTexStageID ind_stage, u8 signed_offset, u8 replace_mode, GXIndTexMtxID matrix_sel)
{
    GXIndTexWrap wrap = (replace_mode != 0) ? GX_ITW_0 : GX_ITW_OFF;

    CHECK_GXBEGIN(0x16E, "GXSetTevIndWarp");
    GXSetTevIndirect(tev_stage, ind_stage, GX_ITF_8, (signed_offset != 0) ? GX_ITB_STU : GX_ITB_NONE, matrix_sel, wrap, wrap, 0U, 0, 0);
}

void GXSetTevIndTile(GXTevStageID tev_stage, GXIndTexStageID ind_stage, u16 tilesize_s,
    u16 tilesize_t, u16 tilespacing_s, u16 tilespacing_t, GXIndTexFormat format,
    GXIndTexMtxID matrix_sel, GXIndTexBiasSel bias_sel, GXIndTexAlphaSel alpha_sel)
{
    GXIndTexWrap wrap_s;
    GXIndTexWrap wrap_t;
    f32 mtx[2][3];

    CHECK_GXBEGIN(0x190, "GXSetTevIndTile");
    ASSERTMSGLINE(0x191, tev_stage < 16, "GXSetTevIndTile: Invalid tev stage id");
    ASSERTMSGLINE(0x192, ind_stage < 4, "GXSetTevIndTile: Invalid indirect stage id");
    switch (tilesize_s) {
    case 256:
        wrap_s = GX_ITW_256;
        break;
    case 128:
        wrap_s = GX_ITW_128;
        break;
    case 64:
        wrap_s = GX_ITW_64;
        break;
    case 32:
        wrap_s = GX_ITW_32;
        break;
    case 16:
        wrap_s = GX_ITW_16;
        break;
    default:
        ASSERTMSGLINE(0x19B, 0, "GXSetTevIndTile: Invalid tilesize for S coordinate");
        wrap_s = GX_ITW_OFF;
        break;
    }
    switch (tilesize_t) {
    case 256:
        wrap_t = GX_ITW_256;
        break;
    case 128:
        wrap_t = GX_ITW_128;
        break;
    case 64:
        wrap_t = GX_ITW_64;
        break;
    case 32:
        wrap_t = GX_ITW_32;
        break;
    case 16:
        wrap_t = GX_ITW_16;
        break;
    default:
        ASSERTMSGLINE(0x1A7, 0, "GXSetTevIndTile: Invalid tilesize for T coordinate");
        wrap_t = GX_ITW_OFF;
        break;
    }
    mtx[0][0] = tilespacing_s / 1024.0f;
    mtx[0][1] = mtx[0][2] = 0.0f;
    mtx[1][1] = tilespacing_t / 1024.0f;
    mtx[1][0] = mtx[1][2] = 0.0f;
    GXSetIndTexMtx(matrix_sel, mtx, 0xA);
    GXSetTevIndirect(tev_stage, ind_stage, format, bias_sel, matrix_sel, wrap_s, wrap_t, 0U, 1, alpha_sel);
}

void GXSetTevIndBumpST(GXTevStageID tev_stage, GXIndTexStageID ind_stage, GXIndTexMtxID matrix_sel)
{
    GXIndTexMtxID sm;
    GXIndTexMtxID tm;

    CHECK_GXBEGIN(0x1CF, "GXSetTevIndBumpST");
    switch (matrix_sel) {
    case GX_ITM_0:
        sm = GX_ITM_S0;
        tm = GX_ITM_T0;
        break;
    case GX_ITM_1:
        sm = GX_ITM_S1;
        tm = GX_ITM_T1;
        break;
    case GX_ITM_2:
        sm = GX_ITM_S2;
        tm = GX_ITM_T2;
        break;
    default:
        ASSERTMSGLINE(0x1E0, 0, "GXSetTevIndBumpST: Invalid matrix selection");
        break;
    }
    GXSetTevIndirect(tev_stage, ind_stage, GX_ITF_8, GX_ITB_ST, sm, GX_ITW_0, GX_ITW_0, 0U, 0, 0);
    GXSetTevIndirect(tev_stage + 1, ind_stage, GX_ITF_8, GX_ITB_ST, tm, GX_ITW_0, GX_ITW_0, 1U, 0, 0);
    GXSetTevIndirect(tev_stage + 2, ind_stage, GX_ITF_8, GX_ITB_NONE, GX_ITM_OFF, GX_ITW_OFF, GX_ITW_OFF, 1U, 0, 0);
}

void GXSetTevIndBumpXYZ(GXTevStageID tev_stage, GXIndTexStageID ind_stage, GXIndTexMtxID matrix_sel)
{
    CHECK_GXBEGIN(0x214, "GXSetTevIndBumpXYZ");
    GXSetTevIndirect(tev_stage, ind_stage, GX_ITF_8, GX_ITB_STU, matrix_sel, GX_ITW_OFF, GX_ITW_OFF, 0U, 0, 0);
}

void GXSetTevIndRepeat(GXTevStageID tev_stage)
{
    CHECK_GXBEGIN(0x231, "GXSetTevIndRepeat");
    GXSetTevIndirect(tev_stage, GX_INDTEXSTAGE0, GX_ITF_8, GX_ITB_NONE, GX_ITM_OFF, GX_ITW_0, GX_ITW_0, 1U, 0, 0);
}

void __GXUpdateBPMask(void)
{
    u32 nIndStages;
    u32 i;
    u32 tmap;
    u32 new_imask;
    u32 nStages;
    u32 new_dmask;

    new_imask = 0;
    new_dmask = 0;
    nIndStages = GET_REG_FIELD(gx->genMode, 3, 16);
    for (i = 0; i < nIndStages; i++) {
        switch (i) {
        case 0: tmap = GET_REG_FIELD(gx->iref, 3, 0); break;
        case 1: tmap = GET_REG_FIELD(gx->iref, 3, 6); break;
        case 2: tmap = GET_REG_FIELD(gx->iref, 3, 12); break;
        case 3: tmap = GET_REG_FIELD(gx->iref, 3, 18); break;
        }
        new_imask |= 1 << tmap;
    }

#if DEBUG
    nStages = GET_REG_FIELD(gx->genMode, 4, 10) + 1;
    for (i = 0; i < nStages; i++) {
        tmap = gx->texmapId[i] & 0xFFFFFEFF;
        if (tmap != 0xFF) {
            new_dmask |= 1 << tmap;
        }
    }
    ASSERTMSGLINE(0x269, !(new_imask & new_dmask), "GXSetTevOrder/GXSetIndTexOrder: Same texture map cannot be specified in both");
#endif

    if ((u8)gx->bpMask != new_imask) {
        SET_REG_FIELD(0x26E, gx->bpMask, 8, 0, new_imask);
        GX_WRITE_SOME_REG5(0x61, gx->bpMask);
        gx->bpSent = 1;
    }
}

void __GXFlushTextureState(void)
{
    GX_WRITE_SOME_REG5(0x61, gx->bpMask);
    gx->bpSent = 1;
}
