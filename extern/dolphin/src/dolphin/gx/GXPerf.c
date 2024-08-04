#include <dolphin/gx.h>
#include <dolphin/os.h>
#include <macros.h>

#include "__gx.h"

void GXSetGPMetric(GXPerf0 perf0, GXPerf1 perf1)
{
    u32 reg;

    CHECK_GXBEGIN(0x6A, "GXSetGPMetric");

    switch (gx->perf0) {
    case GX_PERF0_VERTICES:
    case GX_PERF0_CLIP_VTX:
    case GX_PERF0_CLIP_CLKS:
    case GX_PERF0_XF_WAIT_IN:
    case GX_PERF0_XF_WAIT_OUT:
    case GX_PERF0_XF_XFRM_CLKS:
    case GX_PERF0_XF_LIT_CLKS:
    case GX_PERF0_XF_BOT_CLKS:
    case GX_PERF0_XF_REGLD_CLKS:
    case GX_PERF0_XF_REGRD_CLKS:
    case GX_PERF0_CLIP_RATIO:
    case GX_PERF0_CLOCKS:
        reg = 0;
        GX_WRITE_XF_REG(6, reg);
        break;
    case GX_PERF0_TRIANGLES:
    case GX_PERF0_TRIANGLES_CULLED:
    case GX_PERF0_TRIANGLES_PASSED:
    case GX_PERF0_TRIANGLES_SCISSORED:
    case GX_PERF0_TRIANGLES_0TEX:
    case GX_PERF0_TRIANGLES_1TEX:
    case GX_PERF0_TRIANGLES_2TEX:
    case GX_PERF0_TRIANGLES_3TEX:
    case GX_PERF0_TRIANGLES_4TEX:
    case GX_PERF0_TRIANGLES_5TEX:
    case GX_PERF0_TRIANGLES_6TEX:
    case GX_PERF0_TRIANGLES_7TEX:
    case GX_PERF0_TRIANGLES_8TEX:
    case GX_PERF0_TRIANGLES_0CLR:
    case GX_PERF0_TRIANGLES_1CLR:
    case GX_PERF0_TRIANGLES_2CLR:
        reg = 0x23000000;
        GX_WRITE_RAS_REG(reg);
        break;
    case GX_PERF0_QUAD_0CVG:
    case GX_PERF0_QUAD_NON0CVG:
    case GX_PERF0_QUAD_1CVG:
    case GX_PERF0_QUAD_2CVG:
    case GX_PERF0_QUAD_3CVG:
    case GX_PERF0_QUAD_4CVG:
    case GX_PERF0_AVG_QUAD_CNT:
        reg = 0x24000000;
        GX_WRITE_RAS_REG(reg);
        break;
    case GX_PERF0_NONE:
        break;
    default:
        ASSERTMSGLINE(0xA6, 0, "GXSetGPMetric: Invalid GXPerf0 metric name");
        break;
    }

    switch (gx->perf1) {
    case GX_PERF1_TEXELS:
    case GX_PERF1_TX_IDLE:
    case GX_PERF1_TX_REGS:
    case GX_PERF1_TX_MEMSTALL:
    case GX_PERF1_TC_CHECK1_2:
    case GX_PERF1_TC_CHECK3_4:
    case GX_PERF1_TC_CHECK5_6:
    case GX_PERF1_TC_CHECK7_8:
    case GX_PERF1_TC_MISS:
    case GX_PERF1_CLOCKS:
        reg = 0x67000000;
        GX_WRITE_RAS_REG(reg);
        break;
    case GX_PERF1_VC_ELEMQ_FULL:
    case GX_PERF1_VC_MISSQ_FULL:
    case GX_PERF1_VC_MEMREQ_FULL:
    case GX_PERF1_VC_STATUS7:
    case GX_PERF1_VC_MISSREP_FULL:
    case GX_PERF1_VC_STREAMBUF_LOW:
    case GX_PERF1_VC_ALL_STALLS:
    case GX_PERF1_VERTICES:
        SET_REG_FIELD(0, gx->perfSel, 4, 4, 0);
        GX_WRITE_SOME_REG4(8, 0x20, gx->perfSel, -12);
        break;
    case GX_PERF1_FIFO_REQ:
    case GX_PERF1_CALL_REQ:
    case GX_PERF1_VC_MISS_REQ:
    case GX_PERF1_CP_ALL_REQ:
        reg = 0;
        __cpReg[3] = reg;
        break;
    case GX_PERF1_NONE:
        break;
    default:
        ASSERTMSGLINE(0xD8, 0, "GXSetGPMetric: Invalid GXPerf1 metric name");
        break;
    }

    gx->perf0 = perf0;
    switch (gx->perf0) {
    case GX_PERF0_VERTICES:            reg = 0x273;      GX_WRITE_XF_REG(6, reg); break;
    case GX_PERF0_CLIP_VTX:            reg = 0x14A;      GX_WRITE_XF_REG(6, reg); break;
    case GX_PERF0_CLIP_CLKS:           reg = 0x16B;      GX_WRITE_XF_REG(6, reg); break;
    case GX_PERF0_XF_WAIT_IN:          reg = 0x84;       GX_WRITE_XF_REG(6, reg); break;
    case GX_PERF0_XF_WAIT_OUT:         reg = 0xC6;       GX_WRITE_XF_REG(6, reg); break;
    case GX_PERF0_XF_XFRM_CLKS:        reg = 0x210;      GX_WRITE_XF_REG(6, reg); break;
    case GX_PERF0_XF_LIT_CLKS:         reg = 0x252;      GX_WRITE_XF_REG(6, reg); break;
    case GX_PERF0_XF_BOT_CLKS:         reg = 0x231;      GX_WRITE_XF_REG(6, reg); break;
    case GX_PERF0_XF_REGLD_CLKS:       reg = 0x1AD;      GX_WRITE_XF_REG(6, reg); break;
    case GX_PERF0_XF_REGRD_CLKS:       reg = 0x1CE;      GX_WRITE_XF_REG(6, reg); break;
    case GX_PERF0_TRIANGLES:           reg = 0x2303AE7F; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF0_CLIP_RATIO:          reg = 0x153;      GX_WRITE_XF_REG(6, reg); break;
    case GX_PERF0_TRIANGLES_CULLED:    reg = 0x23038E7F; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF0_TRIANGLES_PASSED:    reg = 0x23039E7F; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF0_TRIANGLES_SCISSORED: reg = 0x23031E7F; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF0_TRIANGLES_0TEX:      reg = 0x2303AC3F; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF0_TRIANGLES_1TEX:      reg = 0x2303AC7F; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF0_TRIANGLES_2TEX:      reg = 0x2303ACBF; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF0_TRIANGLES_3TEX:      reg = 0x2303ACFF; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF0_TRIANGLES_4TEX:      reg = 0x2303AD3F; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF0_TRIANGLES_5TEX:      reg = 0x2303AD7F; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF0_TRIANGLES_6TEX:      reg = 0x2303ADBF; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF0_TRIANGLES_7TEX:      reg = 0x2303ADFF; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF0_TRIANGLES_8TEX:      reg = 0x2303AE3F; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF0_TRIANGLES_0CLR:      reg = 0x2303A27F; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF0_TRIANGLES_1CLR:      reg = 0x2303A67F; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF0_TRIANGLES_2CLR:      reg = 0x2303AA7F; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF0_QUAD_0CVG:           reg = 0x2402C0C6; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF0_QUAD_NON0CVG:        reg = 0x2402C16B; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF0_QUAD_1CVG:           reg = 0x2402C0E7; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF0_QUAD_2CVG:           reg = 0x2402C108; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF0_QUAD_3CVG:           reg = 0x2402C129; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF0_QUAD_4CVG:           reg = 0x2402C14A; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF0_AVG_QUAD_CNT:        reg = 0x2402C1AD; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF0_CLOCKS:              reg = 0x21; GX_WRITE_XF_REG(6, reg); break;
    case GX_PERF0_NONE: break;
    default:
        ASSERTMSGLINE(0x1DA, 0, "GXSetGPMetric: Invalid GXPerf0 metric name");
        break;
    }

    gx->perf1 = perf1;
    switch (gx->perf1) {
    case GX_PERF1_TEXELS:      reg = 0x67000042; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF1_TX_IDLE:     reg = 0x67000084; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF1_TX_REGS:     reg = 0x67000063; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF1_TX_MEMSTALL: reg = 0x67000129; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF1_TC_CHECK1_2: reg = 0x6700014B; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF1_TC_CHECK3_4: reg = 0x6700018D; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF1_TC_CHECK5_6: reg = 0x670001CF; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF1_TC_CHECK7_8: reg = 0x67000211; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF1_TC_MISS:     reg = 0x67000252; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF1_VC_ELEMQ_FULL:    SET_REG_FIELD(0, gx->perfSel, 4, 4, 2); GX_WRITE_SOME_REG4(8, 0x20, gx->perfSel, -12); break;
    case GX_PERF1_VC_MISSQ_FULL:    SET_REG_FIELD(0, gx->perfSel, 4, 4, 3); GX_WRITE_SOME_REG4(8, 0x20, gx->perfSel, -12); break;
    case GX_PERF1_VC_MEMREQ_FULL:   SET_REG_FIELD(0, gx->perfSel, 4, 4, 4); GX_WRITE_SOME_REG4(8, 0x20, gx->perfSel, -12); break;
    case GX_PERF1_VC_STATUS7:       SET_REG_FIELD(0, gx->perfSel, 4, 4, 5); GX_WRITE_SOME_REG4(8, 0x20, gx->perfSel, -12); break;
    case GX_PERF1_VC_MISSREP_FULL:  SET_REG_FIELD(0, gx->perfSel, 4, 4, 6); GX_WRITE_SOME_REG4(8, 0x20, gx->perfSel, -12); break;
    case GX_PERF1_VC_STREAMBUF_LOW: SET_REG_FIELD(0, gx->perfSel, 4, 4, 7); GX_WRITE_SOME_REG4(8, 0x20, gx->perfSel, -12); break;
    case GX_PERF1_VC_ALL_STALLS:    SET_REG_FIELD(0, gx->perfSel, 4, 4, 9); GX_WRITE_SOME_REG4(8, 0x20, gx->perfSel, -12); break;
    case GX_PERF1_VERTICES:         SET_REG_FIELD(0, gx->perfSel, 4, 4, 8); GX_WRITE_SOME_REG4(8, 0x20, gx->perfSel, -12); break;
    case GX_PERF1_FIFO_REQ:    reg = 2; __cpReg[3] = reg; break;
    case GX_PERF1_CALL_REQ:    reg = 3; __cpReg[3] = reg; break;
    case GX_PERF1_VC_MISS_REQ: reg = 4; __cpReg[3] = reg; break;
    case GX_PERF1_CP_ALL_REQ:  reg = 5; __cpReg[3] = reg; break;
    case GX_PERF1_CLOCKS: reg = 0x67000021; GX_WRITE_RAS_REG(reg); break;
    case GX_PERF1_NONE: break;
    default:
        ASSERTMSGLINE(0x26B, 0, "GXSetGPMetric: Invalid GXPerf1 metric name");
        break;
    }

    gx->bpSent = 1;
}

void GXReadGPMetric(u32 *cnt0, u32 *cnt1)
{
    u32 ctrl, ctrh;
    u32 cpCtr0, cpCtr1, cpCtr2, cpCtr3;

    ASSERTMSGLINE(0x286, !gx->inDispList, "GXReadGPMetric: don't use in a display list");

    ctrl = __cpReg[32]; ctrh = __cpReg[33];
    cpCtr0 = (ctrh << 16) | ctrl;

    ctrl = __cpReg[34]; ctrh = __cpReg[35];
    cpCtr1 = (ctrh << 16) | ctrl;

    ctrl = __cpReg[36]; ctrh = __cpReg[37];
    cpCtr2 = (ctrh << 16) | ctrl;

    ctrl = __cpReg[38]; ctrh = __cpReg[39];
    cpCtr3 = (ctrh << 16) | ctrl;

    switch (gx->perf0) {
    case GX_PERF0_CLIP_RATIO:
        *cnt0 = cpCtr1 * 0x3E8 / cpCtr0;
        break;
    case GX_PERF0_VERTICES:
    case GX_PERF0_CLIP_VTX:
    case GX_PERF0_CLIP_CLKS:
    case GX_PERF0_XF_WAIT_IN:
    case GX_PERF0_XF_WAIT_OUT:
    case GX_PERF0_XF_XFRM_CLKS:
    case GX_PERF0_XF_LIT_CLKS:
    case GX_PERF0_XF_BOT_CLKS:
    case GX_PERF0_XF_REGLD_CLKS:
    case GX_PERF0_XF_REGRD_CLKS:

    case GX_PERF0_TRIANGLES:
    case GX_PERF0_TRIANGLES_CULLED:
    case GX_PERF0_TRIANGLES_PASSED:
    case GX_PERF0_TRIANGLES_SCISSORED:
    case GX_PERF0_TRIANGLES_0TEX:
    case GX_PERF0_TRIANGLES_1TEX:
    case GX_PERF0_TRIANGLES_2TEX:
    case GX_PERF0_TRIANGLES_3TEX:
    case GX_PERF0_TRIANGLES_4TEX:
    case GX_PERF0_TRIANGLES_5TEX:
    case GX_PERF0_TRIANGLES_6TEX:
    case GX_PERF0_TRIANGLES_7TEX:
    case GX_PERF0_TRIANGLES_8TEX:
    case GX_PERF0_TRIANGLES_0CLR:
    case GX_PERF0_TRIANGLES_1CLR:
    case GX_PERF0_TRIANGLES_2CLR:
    case GX_PERF0_QUAD_0CVG:
    case GX_PERF0_QUAD_NON0CVG:
    case GX_PERF0_QUAD_1CVG:
    case GX_PERF0_QUAD_2CVG:
    case GX_PERF0_QUAD_3CVG:
    case GX_PERF0_QUAD_4CVG:
    case GX_PERF0_AVG_QUAD_CNT:
    case GX_PERF0_CLOCKS:
        *cnt0 = cpCtr0;
        break;
    case GX_PERF0_NONE:
        *cnt0 = 0;
        break;
    default:
        ASSERTMSGLINE(0x2CF, 0, "GXReadGPMetric: Invalid GXPerf0 metric name");
        *cnt0 = 0;
        break;
    }

    switch (gx->perf1) {
    case GX_PERF1_TEXELS:
        *cnt1 = cpCtr3 * 4;
        break;
    case GX_PERF1_TC_CHECK1_2:
        *cnt1 = cpCtr2 + (cpCtr3 * 2);
        break;
    case GX_PERF1_TC_CHECK3_4:
        *cnt1 = (cpCtr2 * 3) + (cpCtr3 * 4);
        break;
    case GX_PERF1_TC_CHECK5_6:
        *cnt1 = (cpCtr2 * 5) + (cpCtr3 * 6);
        break;
    case GX_PERF1_TC_CHECK7_8:
        *cnt1 = (cpCtr2 * 7) + (cpCtr3 * 8);
        break;
    case GX_PERF1_TX_IDLE:
    case GX_PERF1_TX_REGS:
    case GX_PERF1_TX_MEMSTALL:
    case GX_PERF1_TC_MISS:
    case GX_PERF1_VC_ELEMQ_FULL:
    case GX_PERF1_VC_MISSQ_FULL:
    case GX_PERF1_VC_MEMREQ_FULL:
    case GX_PERF1_VC_STATUS7:
    case GX_PERF1_VC_MISSREP_FULL:
    case GX_PERF1_VC_STREAMBUF_LOW:
    case GX_PERF1_VC_ALL_STALLS:
    case GX_PERF1_VERTICES:
    case GX_PERF1_CLOCKS:
        *cnt1 = cpCtr3;
        break;
    case GX_PERF1_FIFO_REQ:
    case GX_PERF1_CALL_REQ:
    case GX_PERF1_VC_MISS_REQ:
    case GX_PERF1_CP_ALL_REQ:
        *cnt1 = cpCtr2;
        break;
    case GX_PERF1_NONE:
        *cnt1 = 0;
        break;
    default:
        ASSERTMSGLINE(0x30A, 0, "GXReadGPMetric: Invalid GXPerf1 metric name");
        *cnt1 = 0;
        break;
    }
}

void GXClearGPMetric(void)
{
    u32 reg;

    ASSERTMSGLINE(0x322, !gx->inDispList, "GXClearGPMetric: don't use in a display list");
    reg = 4;
    __cpReg[2] = reg;
}

u32 GXReadGP0Metric(void)
{
    u32 cnt0, cnt1;

    GXReadGPMetric(&cnt0, &cnt1);
    return cnt0;
}

u32 GXReadGP1Metric(void)
{
    u32 cnt0, cnt1;

    GXReadGPMetric(&cnt0, &cnt1);
    return cnt1;
}

void GXReadMemMetric(u32 *cp_req, u32 *tc_req, u32 *cpu_rd_req, u32 *cpu_wr_req, u32 *dsp_req, u32 *io_req, u32 *vi_req, u32 *pe_req, u32 *rf_req, u32 *fi_req)
{
    u32 ctrl, ctrh;

    ASSERTMSGLINE(0x380, !gx->inDispList, "GXReadMemMetric: don't use in a display list");

    ctrl = __memReg[26]; ctrh = __memReg[25];
    *cp_req = (ctrh << 16) | ctrl;

    ctrl = __memReg[28]; ctrh = __memReg[27];
    *tc_req = (ctrh << 16) | ctrl;

    ctrl = __memReg[30]; ctrh = __memReg[29];
    *cpu_rd_req = (ctrh << 16) | ctrl;

    ctrl = __memReg[32]; ctrh = __memReg[31];
    *cpu_wr_req = (ctrh << 16) | ctrl;

    ctrl = __memReg[34]; ctrh = __memReg[33];
    *dsp_req = (ctrh << 16) | ctrl;

    ctrl = __memReg[36]; ctrh = __memReg[35];
    *io_req = (ctrh << 16) | ctrl;

    ctrl = __memReg[38]; ctrh = __memReg[37];
    *vi_req = (ctrh << 16) | ctrl;

    ctrl = __memReg[40]; ctrh = __memReg[39];
    *pe_req = (ctrh << 16) | ctrl;

    ctrl = __memReg[42]; ctrh = __memReg[41];
    *rf_req = (ctrh << 16) | ctrl;

    ctrl = __memReg[44]; ctrh = __memReg[43];
    *fi_req = (ctrh << 16) | ctrl;
}

void GXClearMemMetric(void)
{
    ASSERTMSGLINE(0x3B9, !gx->inDispList, "GXClearMemMetric: don't use in a display list");

    __memReg[25] = 0;
    __memReg[26] = 0;
    __memReg[27] = 0;
    __memReg[28] = 0;
    __memReg[30] = 0;
    __memReg[29] = 0;
    __memReg[32] = 0;
    __memReg[31] = 0;
    __memReg[34] = 0;
    __memReg[33] = 0;
    __memReg[36] = 0;
    __memReg[35] = 0;
    __memReg[38] = 0;
    __memReg[37] = 0;
    __memReg[40] = 0;
    __memReg[39] = 0;
    __memReg[42] = 0;
    __memReg[41] = 0;
    __memReg[44] = 0;
    __memReg[43] = 0;
}

void GXReadPixMetric(u32 *top_pixels_in, u32 *top_pixels_out, u32 *bot_pixels_in, u32 *bot_pixels_out, u32 *clr_pixels_in, u32 *copy_clks)
{
    u32 ctrl, ctrh;

    ASSERTMSGLINE(0x3F1, !gx->inDispList, "GXReadPixMetric: don't use in a display list");

    ctrl = __peReg[12]; ctrh = __peReg[13];
    *top_pixels_in = ((ctrh << 16) | ctrl) * 4;

    ctrl = __peReg[14]; ctrh = __peReg[15];
    *top_pixels_out = ((ctrh << 16) | ctrl) * 4;

    ctrl = __peReg[16]; ctrh = __peReg[17];
    *bot_pixels_in = ((ctrh << 16) | ctrl) * 4;

    ctrl = __peReg[18]; ctrh = __peReg[19];
    *bot_pixels_out = ((ctrh << 16) | ctrl) * 4;

    ctrl = __peReg[20]; ctrh = __peReg[21];
    *clr_pixels_in = ((ctrh << 16) | ctrl) * 4;

    ctrl = __peReg[22]; ctrh = __peReg[23];
    *copy_clks = (ctrh << 16) | ctrl;
}

void GXClearPixMetric(void)
{
    u32 reg;

    CHECK_GXBEGIN(0x41D, "GXClearPixMetric");

    reg = 0x57000000;
    GX_WRITE_RAS_REG(reg);
    reg = 0x57000AAA;
    GX_WRITE_RAS_REG(reg);
    gx->bpSent = 1;
}

void GXSetVCacheMetric(GXVCachePerf attr)
{
    u32 reg;

    SET_REG_FIELD(0x43C, gx->perfSel, 4, 0, attr);
    GX_WRITE_SOME_REG4(8, 0x20, gx->perfSel, -12);
    reg = 1;
    GX_WRITE_SOME_REG4(8, 0x10, reg, -12);
}

void GXReadVCacheMetric(u32 *check, u32 *miss, u32 *stall)
{
    u32 hi, lo;

    hi = __cpReg[41]; lo = __cpReg[40];
    *check = (hi << 16) | lo;

    hi = __cpReg[43]; lo = __cpReg[42];
    *miss = (hi << 16) | lo;

    hi = __cpReg[45]; lo = __cpReg[44];
    *stall = (hi << 16) | lo;
}

void GXClearVCacheMetric(void)
{
    GX_WRITE_SOME_REG4(8, 0, 0, -12);
}

void GXInitXfRasMetric(void)
{
    u32 reg;

    CHECK_GXBEGIN(0x489, "GXInitXfRasMetric");

    reg = 0x2402C022;
    GX_WRITE_RAS_REG(reg);
    reg = 0x31000;
    GX_WRITE_XF_REG(6, reg);
    gx->bpSent = 0;
}

void GXReadXfRasMetric(u32 *xf_wait_in, u32 *xf_wait_out, u32 *ras_busy, u32 *clocks)
{
    u32 ctrl, ctrh;

    ctrl = __cpReg[32]; ctrh = __cpReg[33];
    *ras_busy = (ctrh << 16) | ctrl;

    ctrl = __cpReg[34]; ctrh = __cpReg[35];
    *clocks = (ctrh << 16) | ctrl;

    ctrl = __cpReg[36]; ctrh = __cpReg[37];
    *xf_wait_in = (ctrh << 16) | ctrl;

    ctrl = __cpReg[38]; ctrh = __cpReg[39];
    *xf_wait_out = (ctrh << 16) | ctrl;
}

u32 GXReadClksPerVtx(void)
{
    u32 perfCnt;
    u32 ctrh;

    GXDrawDone();
    __cpReg[49] = 0x1007;
    __cpReg[48] = 0x1007;

    ctrh = __cpReg[50];
    perfCnt = ctrh >> 8;
    return perfCnt;
}
