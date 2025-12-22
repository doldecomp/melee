#include <dolphin/thp/thp.h>

#include <dolphin.h>

static const u8 __THPJpegNaturalOrder[80]
    = { 0,  1,  8,  16, 9,  2,  3,  10, 17, 24, 32, 25, 18, 11, 4,  5,  12, 19, 26, 33, 40, 48, 41, 34, 27, 20, 13,
        6,  7,  14, 21, 28, 35, 42, 49, 56, 57, 50, 43, 36, 29, 22, 15, 23, 30, 37, 44, 51, 58, 59, 52, 45, 38, 31,
        39, 46, 53, 60, 61, 54, 47, 55, 62, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63 };

static const f64 __THPAANScaleFactor[8] = {
    1.0f, 1.387039845f, 1.306562965f, 1.175875602f, 1.0f, 0.785694958f, 0.541196100f, 0.275899379f,
};

static THPHuffmanTab* Ydchuff ATTRIBUTE_ALIGN(32);
static THPHuffmanTab* Udchuff ATTRIBUTE_ALIGN(32);
static THPHuffmanTab* Vdchuff ATTRIBUTE_ALIGN(32);
static THPHuffmanTab* Yachuff ATTRIBUTE_ALIGN(32);
static THPHuffmanTab* Uachuff ATTRIBUTE_ALIGN(32);
static THPHuffmanTab* Vachuff ATTRIBUTE_ALIGN(32);
static f32 __THPIDCTWorkspace[64] ATTRIBUTE_ALIGN(32);
static u8* __THPHuffmanBits;
static u8* __THPHuffmanSizeTab;
static u16* __THPHuffmanCodeTab;
static THPSample* Gbase ATTRIBUTE_ALIGN(32);
static u32 Gwid ATTRIBUTE_ALIGN(32);
static f32* Gq ATTRIBUTE_ALIGN(32);
static u8* __THPLCWork512[3];
extern u8* __THPLCWork672[3];
static u32 __THPOldGQR5;
static u32 __THPOldGQR6;
static u8* __THPWorkArea;
static THPCoeff* __THPMCUBuffer[6];
static THPFileInfo* __THPInfo;
static BOOL __THPInitFlag = FALSE;

#define THPROUNDUP(a, b) ((((s32)(a)) + ((s32)(b) - 1L)) / ((s32)(b)))

void __THPPrepBitStream(THPFileInfo* info)
{
    u32* ptr;
    u32 offset, i, j, k;

    ptr    = (u32*)((u32)info->file & 0xFFFFFFFC);
    offset = (u32)info->file & 3;

    if (info->cnt != 33) {
        info->cnt -= (3 - offset) * 8;
    } else {
        info->cnt = (offset * 8) + 1;
    }

    info->file     = (u8*)ptr;
    info->currByte = *ptr;

    for (i = 0; i < 4; i++) {
        if (info->validHuffmanTabs & (1 << i)) {
            for (j = 0; j < 32; j++) {
                info->huffmanTabs[i].quick[j] = 0xFF;

                for (k = 0; k < 5; k++) {
                    s32 code = j >> (5 - k - 1);

                    if (code <= info->huffmanTabs[i].maxCode[k + 1]) {
                        info->huffmanTabs[i].quick[j]
                            = info->huffmanTabs[i].Vij[(s32)(code + info->huffmanTabs[i].valPtr[k + 1])];
                        info->huffmanTabs[i].increment[j] = k + 1;
                        k = 99;
                    }
                }
            }
        }
    }

    {
        s32 YdcTab, UdcTab, VdcTab, YacTab, UacTab, VacTab;

        YdcTab = (info->components[0].DCTableSelector << 1);
        UdcTab = (info->components[1].DCTableSelector << 1);
        VdcTab = (info->components[2].DCTableSelector << 1);

        YacTab = (info->components[0].ACTableSelector << 1) + 1;
        UacTab = (info->components[1].ACTableSelector << 1) + 1;
        VacTab = (info->components[2].ACTableSelector << 1) + 1;

        Ydchuff = &info->huffmanTabs[YdcTab];
        Udchuff = &info->huffmanTabs[UdcTab];
        Vdchuff = &info->huffmanTabs[VdcTab];

        Yachuff = &info->huffmanTabs[YacTab];
        Uachuff = &info->huffmanTabs[UacTab];
        Vachuff = &info->huffmanTabs[VacTab];
    }
}

static inline void __THPGQRSetup(void)
{
    register u32 tmp1, tmp2;

#ifdef __MWERKS__ // clang-format off
    asm {
        mfspr   tmp1, GQR5;
        mfspr   tmp2, GQR6;
    }
#endif // clang-format on

    __THPOldGQR5 = tmp1;
    __THPOldGQR6 = tmp2;

#ifdef __MWERKS__ // clang-format off
    asm {
        li      r3, 0x0007
        oris    r3, r3, 0x0007
        mtspr   GQR5, r3
        li      r3, 0x3D04
        oris    r3, r3, 0x3D04
        mtspr   GQR6, r3
    }
#endif // clang-format on
}

static inline void __THPGQRRestore(void)
{
    register u32 tmp1, tmp2;
    tmp1 = __THPOldGQR5;
    tmp2 = __THPOldGQR6;

#ifdef __MWERKS__ // clang-format off
    asm {
        mtspr   GQR5, tmp1;
        mtspr   GQR6, tmp2;
    }
#endif // clang-format on
}

static void __THPDecompressYUV(void* tileY, void* tileU, void* tileV)
{
    u16 currentY, targetY;
    __THPInfo->dLC[0] = tileY;
    __THPInfo->dLC[1] = tileU;
    __THPInfo->dLC[2] = tileV;

    currentY = __THPInfo->decompressedY;
    targetY  = __THPInfo->yPixelSize;

    __THPGQRSetup();
    __THPPrepBitStream(__THPInfo);

    if (__THPInfo->xPixelSize == 512 && targetY == 448) {
        while (currentY < targetY) {
            __THPDecompressiMCURow512x448();
            currentY += 16;
        }
    } else if (__THPInfo->xPixelSize == 640 && targetY == 480) {
        while (currentY < targetY) {
            __THPDecompressiMCURow640x480();
            currentY += 16;
        }
    } else {
        while (currentY < targetY) {
            __THPDecompressiMCURowNxN();
            currentY += 16;
        }
    }

    __THPGQRRestore();
}

static u8 __THPSetupBuffers(THPFileInfo* info)
{
    u8 i;
    THPCoeff* buffer;

    if (info->cnt != 4) {
        OSReport("ERROR: THP only supports 4:2:0!!!\n");
        return 0;
    }

    buffer = (THPCoeff*)OSRoundUp32B(__THPWorkArea);

    for (i = 0; i < 6; i++) {
        __THPMCUBuffer[i] = &buffer[i * 64];
    }
}

/**
 * Decodes a THP video file.
 *
 * @param file   Pointer to the THP video file.
 * @param tileY  Pointer to the output tile for Y component.
 * @param tileU  Pointer to the output tile for U component.
 * @param tileV  Pointer to the output tile for V component.
 * @param work   Pointer to the work area.
 * @return       Error code indicating the success or failure of the decoding process.
 */
s32 THPVideoDecode(void* file, void* tileY, void* tileU, void* tileV, void* workArea)
{
    u8 all_done, status;
    s32 errorCode;

    THPFileInfo* info = __THPInfo;

    DCZeroRange(file, sizeof(THPFileInfo));
    info->cnt           = 33;
    info->decompressedY = 0;
    info->file          = (u8*)file;

    all_done = FALSE;

    for (;;) {
        if ((*(info->file)++) != 0xFF) {
            goto _err_bad_syntax;
        }

        while (*info->file == 0xFF) {
            ((info->file)++);
        }

        status = (*(info->file)++);

        if (status <= 0xD7) {
            if (status == 0xC4) {
                status = __THPReadHuffmanTableSpecification(info);

                if (status != 0) {
                    goto _err_bad_status;
                }
            }

            else if (status == 192) {
                status = __THPReadFrameHeader();
                if (status != 0) {
                    goto _err_bad_status;
                }
            }

            else {
                goto _err_unsupported_marker;
            }
        }

        else if (0xD8 <= status && status <= 0xDF) {
            if (status == 221) {
                __THPRestartDefinition(info);
            }

            else if (status == 219) {
                status = __THPReadQuantizationTable(info);
                if (status != 0) {
                    goto _err_bad_status;
                }
            }

            else if (status == 218) {
                status = __THPReadScaneHeader(info);
                if (status != 0) {
                    goto _err_bad_status;
                }

                all_done = TRUE;
            } else if (status == 216) {
                // empty but required for match
            } else {
                goto _err_unsupported_marker;
            }
        }

        else if (0xE0 <= status) {
            if ((224 <= status && status <= 239) || status == 254) {
                info->file += (info->file)[0] << 8 | (info->file)[1];
            } else {
                goto _err_unsupported_marker;
            }
        }

        if (all_done) {
            break;
        }
    }

    __THPSetupBuffers(info);
    __THPDecompressYUV(tileY, tileU, tileV);
    return 0;

_err_no_input:
    errorCode = 25;
    goto _err_exit;

_err_no_output:
    errorCode = 27;
    goto _err_exit;

_err_no_work:
    errorCode = 26;
    goto _err_exit;

_err_unsupported_marker:
    errorCode = 11;
    goto _err_exit;

_err_bad_resource:
    errorCode = 1;
    goto _err_exit;

_err_no_mem:
    errorCode = 6;
    goto _err_exit;

_err_bad_syntax:
    errorCode = 3;
    goto _err_exit;

_err_bad_status:
    errorCode = status;
    goto _err_exit;

_err_lc_not_enabled:
    errorCode = 28;
    goto _err_exit;

_err_not_initialized:
    errorCode = 29;
    goto _err_exit;

_err_exit:
    return errorCode;
}

s32 THPDec_803302EC(u8** arg0){
    u32 i;
    u8* ptr = *arg0;
    u16 high = ptr[0];
    u16 low = ptr[1];
    
    u16 count = (high << 8) | low;
    for(i = 0; i <count; i++){
        (*arg0)++;
    }

    return 0;
}

static u8 __THPReadFrameHeader(void)
{
    u8 i, utmp8;

    __THPInfo->file += 2;

    utmp8 = (*(__THPInfo->file)++);

    if (utmp8 != 8) {
        return 10;
    }

    __THPInfo->yPixelSize = (u16)((__THPInfo->file)[0] << 8 | (__THPInfo->file)[1]);
    __THPInfo->file += 2;
    __THPInfo->xPixelSize = (u16)((__THPInfo->file)[0] << 8 | (__THPInfo->file)[1]);
    __THPInfo->file += 2;

    utmp8 = (*(__THPInfo->file)++);
    if (utmp8 != 3) {
        return 12;
    }

    for (i = 0; i < 3; i++) {
        utmp8 = (*(__THPInfo->file)++);
        utmp8 = (*(__THPInfo->file)++);
        if ((i == 0 && utmp8 != 0x22) || (i > 0 && utmp8 != 0x11)) {
            return 19;
        }

        __THPInfo->components[i].quantizationTableSelector = (*(__THPInfo->file)++);
    }

    return 0;
}

static u8 __THPReadQuantizationTable(THPFileInfo* info)
{
    u16 length, id, i, row, col;
    f32 q_temp[64];

    length = (u16)((info->file)[0] << 8 | (info->file)[1]);
    info->file += 2;
    length -= 2;

    for (;;) {
        id = (*(info->file)++);

        for (i = 0; i < 64; i++) {
            q_temp[__THPJpegNaturalOrder[i]] = (f32)(*(info->file)++);
        }

        info->x78 |= 1 << id;

        i = 0;
        for (row = 0; row < 8; row++) {
            for (col = 0; col < 8; col++) {
                info->quantTabs[id][i] = q_temp[i] * __THPAANScaleFactor[row] * __THPAANScaleFactor[col];
                i++;
            }
        }

        length -= 65;
        if (!length) {
            break;
        }
    }

    return 0;
}

static u8 __THPReadHuffmanTableSpecification(THPFileInfo* info)
{
    u8 t_class, id, i;
    u8 tab_index;
    u16 length, num_Vij;
    u8* huffmanBits;
    int result;

    //__THPHuffmanSizeTab = __THPWorkArea;
    //__THPHuffmanCodeTab = (u16*)((u32)__THPWorkArea + 256 + 1);
    length              = (u16)((info->file)[0] << 8 | (info->file)[1]);
    info->file += 2;
    length -= 2;

    for (;;) {
        i                = (*(info->file)++);
        id               = (u8)(i & 15);
        t_class          = (u8)(i >> 4);
        huffmanBits      = info->file;
        tab_index        = (u8)((id << 1) + t_class);
        num_Vij          = 0;

        for (i = 0; i < 16; i++) {
            num_Vij += (*(info->file)++);
        }


        info->huffmanTabs[tab_index].bits = huffmanBits;
        info->huffmanTabs[tab_index].Vij = info->file;
        info->huffmanTabs[tab_index].pad2[1] = num_Vij;
        info->file += num_Vij;
        result = __THPHuffGenerateSizeTable(info, tab_index, (int) huffmanBits);
        if (result) return result;
        result = __THPHuffGenerateCodeTable(info, tab_index);
        if (result) return result;
        __THPHuffGenerateDecoderTables(info, tab_index);

        info->validHuffmanTabs |= 1 << tab_index;
        length -= 17 + num_Vij;

        if (length == 0) {
            break;
        }
    }

    return 0;
}

static u8 __THPReadScaneHeader(THPFileInfo* info)
{
    u8 i, utmp8;
    info->file += 2;

    utmp8 = (*(info->file)++);

    if (utmp8 != 3) {
        return 12;
    }

    for (i = 0; i < 3; i++) {
        utmp8 = (*(info->file)++);

        utmp8                                    = (*(info->file)++);
        info->components[i].DCTableSelector = (u8)(utmp8 >> 4);
        info->components[i].ACTableSelector = (u8)(utmp8 & 15);

        if ((info->validHuffmanTabs & (1 << ((utmp8 >> 4)))) == 0) {
            return 15;
        }

        if ((info->validHuffmanTabs & (1 << ((utmp8 & 15) + 1))) == 0) {
            return 15;
        }
    }

    info->file += 3;
    info->MCUsPerRow           = (u16)THPROUNDUP(info->xPixelSize, 16);
    info->components[0].predDC = 0;
    info->components[1].predDC = 0;
    info->components[2].predDC = 0;
    return 0;
}

static u8 __THPHuffGenerateSizeTable(THPFileInfo* info, u8 a, int b)
{
    s32 p, l, i;
    p = 0;

    for (l = 1; l <= 16; l++) {
        i = (s32)__THPHuffmanBits[l - 1];
        while (i--) {
            __THPHuffmanSizeTab[p++] = (u8)l;
        }
    }

    __THPHuffmanSizeTab[p] = 0;
}

static u8 __THPHuffGenerateCodeTable(THPFileInfo* info, u8 tab_index)
{
    u8 si;
    u16 p, code;

    p    = 0;
    code = 0;
    si   = __THPHuffmanSizeTab[0];

    while (__THPHuffmanSizeTab[p]) {
        while (__THPHuffmanSizeTab[p] == si) {
            __THPHuffmanCodeTab[p++] = code;
            code++;
        }

        code <<= 1;
        si++;
    }
}

static int __THPHuffGenerateDecoderTables(THPFileInfo* info, u8 tabIndex)
{
    s32 p, l;
    THPHuffmanTab* h;

    p = 0;
    h = &info->huffmanTabs[tabIndex];
    for (l = 1; l <= 16; l++) {
        if (h->bits[l - 1]) {
            h->valPtr[l] = p - h->codetab[p];
            p += h->bits[l - 1];
            h->maxCode[l] = h->codetab[p - 1];
        } else {
            h->maxCode[l] = -1;
            h->valPtr[l]  = -1;
        }
    }

    h->maxCode[17] = 0xfffffL;

    return 0;
}

static u8 __THPRestartDefinition(THPFileInfo* info)
{
    info->RST = TRUE;
    info->file += 2;
    info->nMCU = (u16)((info->file)[0] << 8 | (info->file)[1]);
    info->file += 2;
    info->currMCU = info->nMCU;
    return 0;
}

inline void __THPInverseDCTNoYPos(register THPCoeff* in, register u32 xPos)
{
    register f32 *q, *ws;
    register f32 tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7, tmp8, tmp9;
    register f32 tmp10, tmp11, tmp12, tmp13;
    register f32 tmp20, tmp21, tmp22, tmp23;
    register f32 cc4    = 1.414213562F;
    register f32 cc2    = 1.847759065F;
    register f32 cc2c6s = 1.082392200F;
    register f32 cc2c6a = -2.613125930F;
    register f32 bias   = 1024.0F;
    q                   = Gq;
    ws                  = &__THPIDCTWorkspace[0] - 2;

    {
        register u32 itmp0, itmp1, itmp2, itmp3;
#ifdef __MWERKS__ // clang-format off
        asm {
            li          itmp2, 8
            mtctr       itmp2

        _loopHead0:
            psq_l       tmp10, 0(in), 0, 5
            psq_l       tmp11, 0(q), 0, 0
            lwz         itmp0, 12(in)
            lwz         itmp3, 8(in)
            ps_mul      tmp10, tmp10, tmp11
            lwz         itmp1, 4(in)
            or.         itmp0, itmp0, itmp3

        _loopHead1:
            lhz         r0, 0x2(in)
            bne         _regularIDCT
            ps_merge00  tmp0, tmp10, tmp10
            cmpwi       itmp1, 0
            psq_st      tmp0, 8(ws), 0, 0
            bne         _halfIDCT
            psq_st      tmp0, 16(ws), 0, 0
            cmpwi       itmp2, 0
            psq_st      tmp0, 24(ws), 0, 0
            bne         _quarterIDCT
            addi        q, q, 8*sizeof(f32)
            psq_stu     tmp0, 32(ws), 0, 0
            addi        in, in, 8*sizeof(THPCoeff)
            bdnz        _loopHead0
            b           _loopEnd

        _quarterIDCT:
            addi        in, in, 8*sizeof(THPCoeff)
            ps_msub     tmp2, tmp10, cc2, tmp10
            addi        q, q, 8*sizeof(f32)
            ps_merge00  tmp9, tmp10, tmp10
            lwz         itmp1, 4(in)
            ps_sub      tmp1, cc2, cc2c6s
            ps_msub     tmp3, tmp10, cc4, tmp2
            ps_merge11  tmp5, tmp10, tmp2
            psq_l       tmp11, 0(q), 0, 0
            ps_nmsub    tmp4, tmp10, tmp1, tmp3
            ps_add      tmp7, tmp9, tmp5
            psq_l       tmp10, 0(in), 0, 5
            ps_merge11  tmp6, tmp3, tmp4
            ps_sub      tmp5, tmp9, tmp5
            lwz         itmp0, 12(in)
            ps_add      tmp8, tmp9, tmp6
            lwz         itmp3, 8(in)
            ps_sub      tmp6, tmp9, tmp6
            psq_stu     tmp7, 8(ws), 0, 0
            ps_merge10  tmp6, tmp6, tmp6
            psq_stu     tmp8, 8(ws), 0, 0
            ps_merge10  tmp5, tmp5, tmp5
            psq_stu     tmp6, 8(ws), 0, 0
            ps_mul      tmp10, tmp10, tmp11
            psq_stu     tmp5, 8(ws), 0, 0
            bdnz        _loopHead1
            b           _loopEnd

        _halfIDCT:
            psq_l       tmp1, 4(in), 0, 5
            psq_l       tmp9, 8(q), 0, 0
            addi        in, in, 8*sizeof(THPCoeff)
            ps_mul      tmp1, tmp1, tmp9
            addi        q, q, 8*sizeof(f32)
            ps_sub      tmp3, tmp10, tmp1
            ps_add      tmp2, tmp10, tmp1
            lwz         itmp0, 12(in)
            ps_madd     tmp4, tmp1, cc4, tmp3
            ps_nmsub    tmp5, tmp1, cc4, tmp2
            ps_mul      tmp8, tmp3, cc2
            ps_merge00  tmp4, tmp2, tmp4
            lwz         itmp3, 8(in)
            ps_nmsub    tmp6, tmp1, cc2c6a, tmp8
            ps_merge00  tmp5, tmp5, tmp3
            lwz         itmp1, 4(in)
            ps_sub      tmp6, tmp6, tmp2
            ps_nmsub    tmp7, tmp10, cc2c6s, tmp8
            ps_merge11  tmp2, tmp2, tmp6
            ps_msub     tmp8, tmp3, cc4, tmp6
            psq_l       tmp10, 0(in), 0, 5
            ps_add      tmp9, tmp4, tmp2
            ps_sub      tmp7, tmp7, tmp8
            psq_l       tmp11, 0(q), 0, 0
            ps_merge11  tmp3, tmp8, tmp7
            ps_sub      tmp4, tmp4, tmp2
            psq_stu     tmp9, 8(ws), 0, 0
            ps_add      tmp0, tmp5, tmp3
            ps_sub      tmp1, tmp5, tmp3
            psq_stu     tmp0, 8(ws), 0, 0
            ps_merge10  tmp1, tmp1, tmp1
            ps_merge10  tmp4, tmp4, tmp4
            psq_stu     tmp1, 8(ws), 0, 0
            ps_mul      tmp10, tmp10, tmp11
            psq_stu     tmp4, 8(ws), 0, 0
            bdnz        _loopHead1
            b           _loopEnd

        _regularIDCT:
            psq_l       tmp9, 4(in), 0, 5
            psq_l       tmp5, 8(q), 0, 0
            ps_mul      tmp9, tmp9, tmp5
            psq_l       tmp2, 8(in), 0, 5
            psq_l       tmp6, 16(q), 0, 0
            ps_merge01  tmp0, tmp10, tmp9
            psq_l       tmp3, 12(in), 0, 5
            ps_merge01  tmp1, tmp9, tmp10
            psq_l       tmp7, 24(q), 0, 0
            addi        in, in, 8*sizeof(THPCoeff)
            ps_madd     tmp4, tmp2, tmp6, tmp0
            ps_nmsub    tmp5, tmp2, tmp6, tmp0
            ps_madd     tmp6, tmp3, tmp7, tmp1
            ps_nmsub    tmp7, tmp3, tmp7, tmp1
            addi        q, q, 8*sizeof(f32)
            ps_add      tmp0, tmp4, tmp6
            ps_sub      tmp3, tmp4, tmp6
            ps_msub     tmp2, tmp7, cc4, tmp6
            lwz         itmp0, 12(in)
            ps_sub      tmp8, tmp7, tmp5
            ps_add      tmp1, tmp5, tmp2
            ps_sub      tmp2, tmp5, tmp2
            ps_mul      tmp8, tmp8, cc2
            lwz         itmp3, 8(in)
            ps_merge00  tmp1, tmp0, tmp1
            ps_nmsub    tmp6, tmp5, cc2c6a, tmp8
            ps_msub     tmp4, tmp7, cc2c6s, tmp8
            lwz         itmp1, 4(in)
            ps_sub      tmp6, tmp6, tmp0
            ps_merge00  tmp2, tmp2, tmp3
            ps_madd     tmp5, tmp3, cc4, tmp6
            ps_merge11  tmp7, tmp0, tmp6
            psq_l       tmp10, 0(in), 0, 5
            ps_sub      tmp4, tmp4, tmp5
            ps_add      tmp3, tmp1, tmp7
            psq_l       tmp11, 0(q), 0, 0
            ps_merge11  tmp4, tmp5, tmp4
            ps_sub      tmp0, tmp1, tmp7
            ps_mul      tmp10, tmp10, tmp11
            ps_add      tmp5, tmp2, tmp4
            ps_sub      tmp6, tmp2, tmp4
            ps_merge10  tmp5, tmp5, tmp5
            psq_stu     tmp3, 8(ws), 0, 0
            ps_merge10  tmp0, tmp0, tmp0
            psq_stu     tmp6, 8(ws), 0, 0
            psq_stu     tmp5, 8(ws), 0, 0
            psq_stu     tmp0, 8(ws), 0, 0
            bdnz        _loopHead1

        _loopEnd:

        }
#endif // clang-format on
    }

    ws = &__THPIDCTWorkspace[0];

    {
        register THPSample* obase = Gbase;
        register u32 wid          = Gwid;

        register u32 itmp0, off0, off1;
        register THPSample *out0, *out1;

#ifdef __MWERKS__ // clang-format off
        asm {
            psq_l       tmp10, 8*0*sizeof(f32)(ws), 0, 0
            slwi        xPos, xPos, 2
            psq_l       tmp11, 8*4*sizeof(f32)(ws), 0, 0
            slwi        off1, wid, 2
            psq_l       tmp12, 8*2*sizeof(f32)(ws), 0, 0
            mr         off0, xPos
            ps_add      tmp6, tmp10, tmp11
            psq_l       tmp13, 8*6*sizeof(f32)(ws), 0, 0
            ps_sub      tmp8, tmp10, tmp11
            add         off1, off0, off1
            ps_add      tmp6, tmp6, bias
            li      itmp0, 3
            ps_add      tmp7, tmp12, tmp13
            add         out0, obase, off0
            ps_sub      tmp9, tmp12, tmp13
            ps_add      tmp0, tmp6, tmp7
            add         out1, obase, off1
            ps_add      tmp8, tmp8, bias
            mtctr   itmp0

        _loopHead10:
            psq_l       tmp4, 8*1*sizeof(f32)(ws), 0, 0
            ps_msub     tmp9, tmp9, cc4, tmp7
            psq_l       tmp5, 8*3*sizeof(f32)(ws), 0, 0
            ps_sub      tmp3, tmp6, tmp7
            ps_add      tmp1, tmp8, tmp9
            psq_l       tmp6, 8*5*sizeof(f32)(ws), 0, 0
            ps_sub      tmp2, tmp8, tmp9
            psq_l       tmp7, 8*7*sizeof(f32)(ws), 0, 0
            ps_add      tmp8, tmp6, tmp5
            ps_sub      tmp6, tmp6, tmp5
            addi        ws, ws, 2*sizeof(f32)
            ps_add      tmp9, tmp4, tmp7
            ps_sub      tmp4, tmp4, tmp7
            psq_l       tmp10, 8*0*sizeof(f32)(ws), 0, 0
            ps_add      tmp7, tmp9, tmp8
            ps_sub      tmp5, tmp9, tmp8
            ps_add      tmp8, tmp6, tmp4
            psq_l       tmp11, 8*4*sizeof(f32)(ws), 0, 0
            ps_add      tmp9, tmp0, tmp7
            ps_mul      tmp8, tmp8, cc2
            psq_l       tmp12, 8*2*sizeof(f32)(ws), 0, 0
            ps_sub      tmp23, tmp0, tmp7
            ps_madd     tmp6, tmp6, cc2c6a, tmp8
            psq_l       tmp13, 8*6*sizeof(f32)(ws), 0, 0
            ps_sub      tmp6, tmp6, tmp7
            addi        off0, off0, 2*sizeof(THPSample)
            psq_st      tmp9, 0(out0), 0, 6
            ps_msub     tmp4, tmp4, cc2c6s, tmp8
            ps_add      tmp9, tmp1, tmp6
            ps_msub     tmp5, tmp5, cc4, tmp6
            ps_sub      tmp22, tmp1, tmp6
            psq_st      tmp9, 8(out0), 0, 6
            ps_add      tmp8, tmp2, tmp5
            ps_add      tmp4, tmp4, tmp5
            psq_st      tmp8, 16(out0), 0, 6
            addi        off1, off1, 2*sizeof(THPSample)
            ps_sub      tmp9, tmp3, tmp4
            ps_add      tmp20, tmp3, tmp4
            psq_st      tmp9, 24(out0), 0, 6
            ps_sub      tmp21, tmp2, tmp5
            ps_add      tmp6, tmp10, tmp11
            psq_st      tmp20, 0(out1), 0, 6
            ps_sub      tmp8, tmp10, tmp11
            ps_add      tmp6, tmp6, bias
            psq_st      tmp21, 8(out1), 0, 6
            ps_add      tmp7, tmp12, tmp13
            ps_sub      tmp9, tmp12, tmp13
            psq_st      tmp22, 16(out1), 0, 6
            add         out0, obase, off0
            ps_add      tmp0, tmp6, tmp7
            psq_st      tmp23, 24(out1), 0, 6
            ps_add      tmp8, tmp8, bias
            add         out1, obase, off1
            bdnz        _loopHead10
            psq_l       tmp4, 8*1*sizeof(f32)(ws), 0, 0
            ps_msub     tmp9, tmp9, cc4, tmp7
            psq_l       tmp5, 8*3*sizeof(f32)(ws), 0, 0
            ps_sub      tmp3, tmp6, tmp7
            ps_add      tmp1, tmp8, tmp9
            psq_l       tmp6, 8*5*sizeof(f32)(ws), 0, 0
            ps_sub      tmp2, tmp8, tmp9
            psq_l       tmp7, 8*7*sizeof(f32)(ws), 0, 0
            ps_add      tmp8, tmp6, tmp5
            ps_sub      tmp6, tmp6, tmp5
            ps_add      tmp9, tmp4, tmp7
            ps_sub      tmp4, tmp4, tmp7
            ps_add      tmp7, tmp9, tmp8
            ps_sub      tmp5, tmp9, tmp8
            ps_add      tmp8, tmp6, tmp4
            ps_add      tmp9, tmp0, tmp7
            ps_mul      tmp8, tmp8, cc2
            ps_sub      tmp23, tmp0, tmp7
            ps_madd     tmp6, tmp6, cc2c6a, tmp8
            psq_st      tmp9, 0(out0), 0, 6
            ps_sub      tmp6, tmp6, tmp7
            ps_msub     tmp4, tmp4, cc2c6s, tmp8
            psq_st      tmp23, 24(out1), 0, 6
            ps_add      tmp9, tmp1, tmp6
            ps_msub     tmp5, tmp5, cc4, tmp6
            ps_sub      tmp22, tmp1, tmp6
            psq_st      tmp9, 8(out0), 0, 6
            ps_add      tmp8, tmp2, tmp5
            ps_add      tmp4, tmp4, tmp5
            psq_st      tmp22, 16(out1), 0, 6
            psq_st      tmp8, 16(out0), 0, 6
            ps_sub      tmp9, tmp3, tmp4
            ps_add      tmp20, tmp3, tmp4
            psq_st      tmp9, 24(out0), 0, 6
            ps_sub      tmp21, tmp2, tmp5
            psq_st      tmp20, 0(out1), 0, 6
            psq_st      tmp21, 8(out1), 0, 6
        }
#endif // clang-format on
    }
}

inline void __THPInverseDCTY8(register THPCoeff* in, register u32 xPos)
{
    register f32 *q, *ws;
    register f32 tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7, tmp8, tmp9;
    register f32 tmp10, tmp11, tmp12, tmp13;
    register f32 tmp20, tmp21, tmp22, tmp23;
    register f32 cc4    = 1.414213562F;
    register f32 cc2    = 1.847759065F;
    register f32 cc2c6s = 1.082392200F;
    register f32 cc2c6a = -2.613125930F;
    register f32 bias   = 1024.0F;

    q  = Gq;
    ws = &__THPIDCTWorkspace[0] - 2;

    {
        register u32 itmp0, itmp1, itmp2, itmp3;

#ifdef __MWERKS__ // clang-format off
        asm {
            li          itmp2, 8
            mtctr       itmp2

        _loopHead0:
            psq_l       tmp10, 0(in), 0, 5
            psq_l       tmp11, 0(q), 0, 0
            lwz         itmp0, 12(in)
            lwz         itmp3, 8(in)
            ps_mul      tmp10, tmp10, tmp11
            lwz         itmp1, 4(in)
            lhz         itmp2, 2(in)
            or          itmp0, itmp0, itmp3

        _loopHead1:
            cmpwi       itmp0, 0
            bne         _regularIDCT
            ps_merge00  tmp0, tmp10, tmp10
            cmpwi       itmp1, 0
            psq_st      tmp0, 8(ws), 0, 0
            bne         _halfIDCT
            psq_st      tmp0, 16(ws), 0, 0
            cmpwi       itmp2, 0
            psq_st      tmp0, 24(ws), 0, 0
            bne         _quarterIDCT
            addi        q, q, 8*sizeof(f32)
            psq_stu     tmp0, 32(ws), 0, 0
            addi        in, in, 8*sizeof(THPCoeff)
            bdnz        _loopHead0
            b           _loopEnd

        _quarterIDCT:
            ps_msub     tmp2, tmp10, cc2, tmp10
            addi        in, in, 8*sizeof(THPCoeff)
            ps_merge00  tmp9, tmp10, tmp10
            addi        q, q, 8*sizeof(f32)
            ps_sub      tmp1, cc2, cc2c6s
            lwz         itmp1, 4(in)
            ps_msub     tmp3, tmp10, cc4, tmp2
            lhz         itmp2, 2(in)
            ps_merge11  tmp5, tmp10, tmp2
            psq_l       tmp11, 0(q), 0, 0
            ps_nmsub    tmp4, tmp10, tmp1, tmp3
            ps_add      tmp7, tmp9, tmp5
            psq_l       tmp10, 0(in), 0, 5
            ps_merge11  tmp6, tmp3, tmp4
            ps_sub      tmp5, tmp9, tmp5
            lwz         itmp0, 12(in)
            ps_add      tmp8, tmp9, tmp6
            lwz         itmp3, 8(in)
            ps_sub      tmp6, tmp9, tmp6
            psq_stu     tmp7, 8(ws), 0, 0
            ps_merge10  tmp6, tmp6, tmp6
            psq_stu     tmp8, 8(ws), 0, 0
            ps_merge10  tmp5, tmp5, tmp5
            or          itmp0, itmp0, itmp3
            psq_stu     tmp6, 8(ws), 0, 0
            ps_mul      tmp10, tmp10, tmp11
            psq_stu     tmp5, 8(ws), 0, 0
            bdnz        _loopHead1
            b           _loopEnd

        _halfIDCT:
            psq_l       tmp1, 4(in), 0, 5
            psq_l       tmp9, 8(q), 0, 0
            addi        in, in, 8*sizeof(THPCoeff)
            ps_mul      tmp1, tmp1, tmp9
            addi        q, q, 8*sizeof(f32)
            ps_sub      tmp3, tmp10, tmp1
            ps_add      tmp2, tmp10, tmp1
            lwz         itmp0, 12(in)
            ps_madd     tmp4, tmp1, cc4, tmp3
            ps_nmsub    tmp5, tmp1, cc4, tmp2
            ps_mul      tmp8, tmp3, cc2
            ps_merge00  tmp4, tmp2, tmp4
            lwz         itmp3, 8(in)
            ps_nmsub    tmp6, tmp1, cc2c6a, tmp8
            ps_merge00  tmp5, tmp5, tmp3
            lwz         itmp1, 4(in)
            ps_sub      tmp6, tmp6, tmp2
            ps_nmsub    tmp7, tmp10, cc2c6s, tmp8
            lhz         itmp2, 2(in)
            ps_merge11  tmp2, tmp2, tmp6
            ps_msub     tmp8, tmp3, cc4, tmp6
            psq_l       tmp10, 0(in), 0, 5
            ps_add      tmp9, tmp4, tmp2
            ps_sub      tmp7, tmp7, tmp8
            psq_l       tmp11, 0(q), 0, 0
            ps_merge11  tmp3, tmp8, tmp7
            ps_sub      tmp4, tmp4, tmp2
            psq_stu     tmp9, 8(ws), 0, 0
            ps_add      tmp0, tmp5, tmp3
            ps_sub      tmp1, tmp5, tmp3
            or          itmp0, itmp0, itmp3
            psq_stu     tmp0, 8(ws), 0, 0
            ps_merge10  tmp1, tmp1, tmp1
            ps_merge10  tmp4, tmp4, tmp4
            psq_stu     tmp1, 8(ws), 0, 0
            ps_mul      tmp10, tmp10, tmp11
            psq_stu     tmp4, 8(ws), 0, 0
            bdnz        _loopHead1
            b           _loopEnd

        _regularIDCT:
            psq_l       tmp9, 4(in), 0, 5
            psq_l       tmp5, 8(q), 0, 0
            ps_mul      tmp9, tmp9, tmp5
            psq_l       tmp2, 8(in), 0, 5
            psq_l       tmp6, 16(q), 0, 0
            ps_merge01  tmp0, tmp10, tmp9
            psq_l       tmp3, 12(in), 0, 5
            ps_merge01  tmp1, tmp9, tmp10
            psq_l       tmp7, 24(q), 0, 0
            addi        in, in, 8*sizeof(THPCoeff)
            ps_madd     tmp4, tmp2, tmp6, tmp0
            ps_nmsub    tmp5, tmp2, tmp6, tmp0
            ps_madd     tmp6, tmp3, tmp7, tmp1
            ps_nmsub    tmp7, tmp3, tmp7, tmp1
            addi        q, q, 8*sizeof(f32)
            ps_add      tmp0, tmp4, tmp6
            ps_sub      tmp3, tmp4, tmp6
            ps_msub     tmp2, tmp7, cc4, tmp6
            lwz         itmp0, 12(in)
            ps_sub      tmp8, tmp7, tmp5
            ps_add      tmp1, tmp5, tmp2
            ps_sub      tmp2, tmp5, tmp2
            ps_mul      tmp8, tmp8, cc2
            lwz         itmp3, 8(in)
            ps_merge00  tmp1, tmp0, tmp1
            ps_nmsub    tmp6, tmp5, cc2c6a, tmp8
            ps_msub     tmp4, tmp7, cc2c6s, tmp8
            lwz         itmp1, 4(in)
            ps_sub      tmp6, tmp6, tmp0
            ps_merge00  tmp2, tmp2, tmp3
            lhz         itmp2, 2(in)
            ps_madd     tmp5, tmp3, cc4, tmp6
            ps_merge11  tmp7, tmp0, tmp6
            psq_l       tmp10, 0(in), 0, 5
            ps_sub      tmp4, tmp4, tmp5
            ps_add      tmp3, tmp1, tmp7
            psq_l       tmp11, 0(q), 0, 0
            ps_merge11  tmp4, tmp5, tmp4
            ps_sub      tmp0, tmp1, tmp7
            ps_mul      tmp10, tmp10, tmp11
            ps_add      tmp5, tmp2, tmp4
            ps_sub      tmp6, tmp2, tmp4
            ps_merge10  tmp5, tmp5, tmp5
            psq_stu     tmp3, 8(ws), 0, 0
            ps_merge10  tmp0, tmp0, tmp0
            psq_stu     tmp6, 8(ws), 0, 0
            psq_stu     tmp5, 8(ws), 0, 0
            or          itmp0, itmp0, itmp3
            psq_stu     tmp0, 8(ws), 0, 0
            bdnz        _loopHead1

        _loopEnd:

        }
#endif // clang-format on
    }

    ws = &__THPIDCTWorkspace[0];

    {
        register THPSample* obase = Gbase;
        register u32 wid          = Gwid;

        register u32 itmp0, off0, off1;
        register THPSample *out0, *out1;

#ifdef __MWERKS__ // clang-format off
        asm {
            psq_l       tmp10, 8*0*sizeof(f32)(ws), 0, 0
            slwi off0, wid, 3;
            psq_l       tmp11, 8*4*sizeof(f32)(ws), 0, 0
            slwi        xPos, xPos, 2
            psq_l       tmp12, 8*2*sizeof(f32)(ws), 0, 0
            slwi        off1, wid, 2
            ps_add      tmp6, tmp10, tmp11
            add         off0, off0, xPos
            psq_l       tmp13, 8*6*sizeof(f32)(ws), 0, 0
            ps_sub      tmp8, tmp10, tmp11
            add         off1, off0, off1
            ps_add      tmp6, tmp6, bias
            li          itmp0, 3
            ps_add      tmp7, tmp12, tmp13
            add         out0, obase, off0
            ps_sub      tmp9, tmp12, tmp13
            ps_add      tmp0, tmp6, tmp7
            add         out1, obase, off1
            ps_add      tmp8, tmp8, bias
            mtctr       itmp0

        _loopHead10:
            psq_l       tmp4, 8*1*sizeof(f32)(ws), 0, 0
            ps_msub     tmp9, tmp9, cc4, tmp7
            psq_l       tmp5, 8*3*sizeof(f32)(ws), 0, 0
            ps_sub      tmp3, tmp6, tmp7
            ps_add      tmp1, tmp8, tmp9
            psq_l       tmp6, 8*5*sizeof(f32)(ws), 0, 0
            ps_sub      tmp2, tmp8, tmp9
            psq_l       tmp7, 8*7*sizeof(f32)(ws), 0, 0
            ps_add      tmp8, tmp6, tmp5
            ps_sub      tmp6, tmp6, tmp5
            addi        ws, ws, 2*sizeof(f32)
            ps_add      tmp9, tmp4, tmp7
            ps_sub      tmp4, tmp4, tmp7
            psq_l       tmp10, 8*0*sizeof(f32)(ws), 0, 0
            ps_add      tmp7, tmp9, tmp8
            ps_sub      tmp5, tmp9, tmp8
            ps_add      tmp8, tmp6, tmp4
            psq_l       tmp11, 8*4*sizeof(f32)(ws), 0, 0
            ps_add      tmp9, tmp0, tmp7
            ps_mul      tmp8, tmp8, cc2
            psq_l       tmp12, 8*2*sizeof(f32)(ws), 0, 0
            ps_sub      tmp23, tmp0, tmp7
            ps_madd     tmp6, tmp6, cc2c6a, tmp8
            psq_l       tmp13, 8*6*sizeof(f32)(ws), 0, 0
            ps_sub      tmp6, tmp6, tmp7
            addi        off0, off0, 2*sizeof(THPSample)
            psq_st      tmp9, 0(out0), 0, 6
            ps_msub     tmp4, tmp4, cc2c6s, tmp8
            ps_add      tmp9, tmp1, tmp6
            ps_msub     tmp5, tmp5, cc4, tmp6
            ps_sub      tmp22, tmp1, tmp6
            psq_st      tmp9, 8(out0), 0, 6
            ps_add      tmp8, tmp2, tmp5
            ps_add      tmp4, tmp4, tmp5
            psq_st      tmp8, 16(out0), 0, 6
            addi        off1, off1, 2*sizeof(THPSample)
            ps_sub      tmp9, tmp3, tmp4
            ps_add      tmp20, tmp3, tmp4
            psq_st      tmp9, 24(out0), 0, 6
            ps_sub      tmp21, tmp2, tmp5
            ps_add      tmp6, tmp10, tmp11
            psq_st      tmp20, 0(out1), 0, 6
            ps_sub      tmp8, tmp10, tmp11
            ps_add      tmp6, tmp6, bias
            psq_st      tmp21, 8(out1), 0, 6
            ps_add      tmp7, tmp12, tmp13
            ps_sub      tmp9, tmp12, tmp13
            psq_st      tmp22, 16(out1), 0, 6
            add         out0, obase, off0
            ps_add      tmp0, tmp6, tmp7
            psq_st      tmp23, 24(out1), 0, 6
            ps_add      tmp8, tmp8, bias
            add         out1, obase, off1

            bdnz        _loopHead10
            psq_l       tmp4, 8*1*sizeof(f32)(ws), 0, 0
            ps_msub     tmp9, tmp9, cc4, tmp7
            psq_l       tmp5, 8*3*sizeof(f32)(ws), 0, 0
            ps_sub      tmp3, tmp6, tmp7
            ps_add      tmp1, tmp8, tmp9
            psq_l       tmp6, 8*5*sizeof(f32)(ws), 0, 0
            ps_sub      tmp2, tmp8, tmp9
            psq_l       tmp7, 8*7*sizeof(f32)(ws), 0, 0
            ps_add      tmp8, tmp6, tmp5
            ps_sub      tmp6, tmp6, tmp5
            ps_add      tmp9, tmp4, tmp7
            ps_sub      tmp4, tmp4, tmp7
            ps_add      tmp7, tmp9, tmp8
            ps_sub      tmp5, tmp9, tmp8
            ps_add      tmp8, tmp6, tmp4
            ps_add      tmp9, tmp0, tmp7
            ps_mul      tmp8, tmp8, cc2
            ps_sub      tmp23, tmp0, tmp7
            ps_madd     tmp6, tmp6, cc2c6a, tmp8
            psq_st      tmp9, 0(out0), 0, 6
            ps_sub      tmp6, tmp6, tmp7
            ps_msub     tmp4, tmp4, cc2c6s, tmp8
            psq_st      tmp23, 24(out1), 0, 6
            ps_add      tmp9, tmp1, tmp6
            ps_msub     tmp5, tmp5, cc4, tmp6
            ps_sub      tmp22, tmp1, tmp6
            psq_st      tmp9, 8(out0), 0, 6
            ps_add      tmp8, tmp2, tmp5
            ps_add      tmp4, tmp4, tmp5
            psq_st      tmp8, 16(out0), 0, 6
            ps_sub      tmp9, tmp3, tmp4
            psq_st      tmp22, 16(out1), 0, 6
            ps_add      tmp20, tmp3, tmp4
            psq_st      tmp9, 24(out0), 0, 6
            ps_sub      tmp21, tmp2, tmp5
            psq_st      tmp20, 0(out1), 0, 6
            psq_st      tmp21, 8(out1), 0, 6
        }
#endif // clang-format on
    }
}

static void __THPDecompressiMCURow512x448(void)
{
    u8 cl_num;
    u32 x_pos;
    THPComponent* comp;

    LCQueueWait(3);

    for (cl_num = 0; cl_num < __THPInfo->MCUsPerRow; cl_num++) {
        __THPHuffDecodeDCTCompY(__THPInfo, __THPMCUBuffer[0]);
        __THPHuffDecodeDCTCompY(__THPInfo, __THPMCUBuffer[1]);
        __THPHuffDecodeDCTCompY(__THPInfo, __THPMCUBuffer[2]);
        __THPHuffDecodeDCTCompY(__THPInfo, __THPMCUBuffer[3]);
        __THPHuffDecodeDCTCompU(__THPInfo, __THPMCUBuffer[4]);
        __THPHuffDecodeDCTCompV(__THPInfo, __THPMCUBuffer[5]);

        comp  = &__THPInfo->components[0];
        Gbase = __THPLCWork512[0];
        Gwid  = 512;
        Gq    = __THPInfo->quantTabs[comp->quantizationTableSelector];
        x_pos = (u32)(cl_num * 16);
        __THPInverseDCTNoYPos(__THPMCUBuffer[0], x_pos);
        __THPInverseDCTNoYPos(__THPMCUBuffer[1], x_pos + 8);
        __THPInverseDCTY8(__THPMCUBuffer[2], x_pos);
        __THPInverseDCTY8(__THPMCUBuffer[3], x_pos + 8);

        comp  = &__THPInfo->components[1];
        Gbase = __THPLCWork512[1];
        Gwid  = 256;
        Gq    = __THPInfo->quantTabs[comp->quantizationTableSelector];
        x_pos /= 2;
        __THPInverseDCTNoYPos(__THPMCUBuffer[4], x_pos);
        comp  = &__THPInfo->components[2];
        Gbase = __THPLCWork512[2];
        Gq    = __THPInfo->quantTabs[comp->quantizationTableSelector];
        __THPInverseDCTNoYPos(__THPMCUBuffer[5], x_pos);

        if (__THPInfo->RST != 0) {
            if ((--__THPInfo->currMCU) == 0) {
                __THPInfo->currMCU = __THPInfo->nMCU;
                __THPInfo->cnt     = 1 + ((__THPInfo->cnt + 6) & 0xFFFFFFF8);

                if (__THPInfo->cnt > 33) {
                    __THPInfo->cnt = 33;
                }

                __THPInfo->components[0].predDC = 0;
                __THPInfo->components[1].predDC = 0;
                __THPInfo->components[2].predDC = 0;
            }
        }
    }

    LCStoreData(__THPInfo->dLC[0], __THPLCWork512[0], 0x2000);
    LCStoreData(__THPInfo->dLC[1], __THPLCWork512[1], 0x800);
    LCStoreData(__THPInfo->dLC[2], __THPLCWork512[2], 0x800);

    __THPInfo->dLC[0] += 0x2000;
    __THPInfo->dLC[1] += 0x800;
    __THPInfo->dLC[2] += 0x800;
}

inline s32 __THPHuffDecodeTab(register THPFileInfo* info, register THPHuffmanTab* h)
{
    register s32 code;
    register u32 cnt;
    register s32 cb;
    register u32 increment;
    register s32 tmp;

#ifdef __MWERKS__ // clang-format off
    asm {
        lwz     cnt, info->cnt;
        addi    increment, h, 32;
        lwz     cb, info->currByte;
        addi    code, cnt, 4;
        cmpwi   cnt, 28;
        rlwnm   tmp, cb, code, 27, 31;
        bgt     _notEnoughBits;
        lbzx    code, h, tmp;
        lbzx    increment, increment, tmp;
        cmpwi   code, 0xFF;
        beq     _FailedCheckEnoughBits;
        add     cnt, cnt, increment;
        stw     cnt, info->cnt;
    }
#endif // clang-format on
    _done: return code;

    {
        register u32 maxcodebase;
        register u32 tmp2;

    _FailedCheckEnoughBits:
        maxcodebase = (u32) & (h->maxCode);
        cnt += 5;

#ifdef __MWERKS__ // clang-format off
        asm {
            li          tmp2, sizeof(s32)*(5);
            li          code, 5;
            add         maxcodebase, maxcodebase, tmp2;
          __WHILE_START:
            cmpwi       cnt, 33;
            slwi        tmp, tmp, 1

            beq         _FCEB_faster;
            rlwnm       increment, cb, cnt, 31, 31;
            lwzu        tmp2, 4(maxcodebase);
            or          tmp, tmp, increment
            addi        cnt, cnt, 1;
            b __WHILE_CHECK;

          _FCEB_faster:
            lwz     increment, info->file;
            li      cnt, 1;
            lwzu    cb, 4(increment);
            lwzu    tmp2, 4(maxcodebase);

            stw     increment, info->file;
            rlwimi  tmp, cb, 1,31,31;
            stw     cb, info->currByte;
            b __FL_WHILE_CHECK;

          __FL_WHILE_START:
            slwi    tmp, tmp, 1;
            rlwnm   increment, cb, cnt, 31, 31;
            lwzu    tmp2, 4(maxcodebase);
            or      tmp, tmp, increment;

          __FL_WHILE_CHECK:
            cmpw    tmp,tmp2
            addi    cnt, cnt, 1;
            addi        code, code, 1
            bgt     __FL_WHILE_START;
            b _FCEB_Done;

          __WHILE_CHECK:
            cmpw    tmp,tmp2
            addi        code, code, 1
            bgt     __WHILE_START;
        }
#endif // clang-format on
    }
_FCEB_Done:
    info->cnt = cnt;
    return (h->Vij[(s32)(tmp + h->valPtr[code])]);

#ifdef __MWERKS__ // clang-format off
    asm {
      _notEnoughBits:
        cmpwi   cnt, 33;
        lwz     tmp, info->file;
        beq     _getfullword;

        cmpwi   cnt, 32;
        rlwnm   code, cb, code, 27, 31
        beq     _1bitleft;

        lbzx    tmp, h, code;
        lbzx    increment, increment, code;
        cmpwi   tmp, 0xFF;
        add     code, cnt, increment;
        beq _FailedCheckNoBits0;

        cmpwi   code, 33;
        stw     code, info->cnt;
        bgt     _FailedCheckNoBits1;
    }
#endif // clang-format on
    return tmp;

#ifdef __MWERKS__ // clang-format off
    asm {
      _1bitleft:
        lwzu    cb, 4(tmp);

        stw     tmp, info->file;
        rlwimi  code, cb, 4, 28, 31;
        lbzx    tmp, h, code;
        lbzx    increment, increment, code
        stw     cb, info->currByte;
        cmpwi   tmp, 0xFF
        stw     increment, info->cnt;
        beq     _Read4;

    }
#endif // clang-format on
    return tmp;

_Read4: {
    register u32 maxcodebase = (u32) & (h->maxCode);
    register u32 tmp2;

#ifdef __MWERKS__ // clang-format off
    asm {
            li      cnt, sizeof(s32)*5;
            add     maxcodebase, maxcodebase, cnt;

            slwi    tmp, code, 32-5;
            li      cnt,5;
            rlwimi  tmp, cb, 32-1, 1,31;

          __DR4_WHILE_START:

            subfic  cb, cnt, 31;
            lwzu    tmp2, 4(maxcodebase);
            srw     code, tmp, cb;
          __DR4_WHILE_CHECK:
            cmpw    code, tmp2
            addi    cnt, cnt, 1
            bgt     __DR4_WHILE_START;
    }
#endif // clang-format on
}

    info->cnt = cnt;
__CODE_PLUS_VP_CNT:
    return (h->Vij[(s32)(code + h->valPtr[cnt])]);

_getfullword:
#ifdef __MWERKS__ // clang-format off
    asm {
        lwzu    cb, 4(tmp);

        rlwinm  code, cb, 5, 27, 31
        stw     tmp, info->file;
        lbzx    cnt, h, code;
        lbzx    increment, increment, code;
        cmpwi   cnt, 0xFF
        stw     cb, info->currByte;
        addi    increment, increment, 1
        beq     _FailedCheckEnoughbits_Updated;

        stw     increment, info->cnt;
    }
#endif // clang-format on
    return (s32)cnt;

_FailedCheckEnoughbits_Updated:

    cnt = 5;
    do {
#ifdef __MWERKS__ // clang-format off
        asm {
            subfic  tmp, cnt, 31;
            addi    cnt, cnt, 1;
            srw     code, cb, tmp;
        }
#endif // clang-format on
    } while (code > h->maxCode[cnt]);

    info->cnt = cnt + 1;
    goto __CODE_PLUS_VP_CNT;

_FailedCheckNoBits0:
_FailedCheckNoBits1:

{
    register u32 mask = 0xFFFFFFFF << (33 - cnt);
    register u32 tmp2;

    code = (s32)(cb & (~mask));
    mask = (u32) & (h->maxCode);

#ifdef __MWERKS__ // clang-format off
    asm {
            lwz     tmp, info->file;
            subfic  tmp2, cnt, 33;
            addi    cnt, tmp2, 1;
            slwi    tmp2, tmp2, 2;
            lwzu    cb, 4(tmp);
            add     mask,mask, tmp2;
            stw     tmp, info->file;
            slwi    code, code, 1;
            stw     cb, info->currByte;
            rlwimi  code, cb, 1, 31, 31;
            lwzu    tmp2, 4(mask);
            li      tmp, 2;
            b       __FCNB1_WHILE_CHECK;

          __FCNB1_WHILE_START:
            slwi    code, code, 1;

            addi    cnt, cnt, 1;
            lwzu    tmp2, 4(mask);
            add     code, code, increment;
            addi    tmp, tmp, 1;

          __FCNB1_WHILE_CHECK:
            cmpw    code, tmp2;
            rlwnm   increment, cb, tmp, 31, 31;
            bgt     __FCNB1_WHILE_START;
    }
#endif // clang-format on
}

    info->cnt = (u32)tmp;
    return (h->Vij[(s32)(code + h->valPtr[cnt])]);
}

static void __THPDecompressiMCURow640x480(void)
{
    u8 cl_num;
    u32 x_pos;
    THPComponent* comp;

    THPFileInfo* info = __THPInfo;
    THPCoeff** r28 = __THPMCUBuffer;

    LCQueueWait(3);

    {
        for (cl_num = 0; cl_num < __THPInfo->MCUsPerRow; cl_num++) {
            THPFileInfo* um = __THPInfo;
            __THPHuffDecodeDCTCompY(um, r28[10]);
            __THPHuffDecodeDCTCompY(info, r28[5]);
            __THPHuffDecodeDCTCompY(info, r28[6]);
            __THPHuffDecodeDCTCompY(info, r28[7]);
            __THPHuffDecodeDCTCompU(info, r28[8]);
            __THPHuffDecodeDCTCompV(info, r28[9]);

            comp  = &__THPInfo->components[0];
            Gbase = __THPLCWork672[0];
            Gwid  = 640;
            Gq    = __THPInfo->quantTabs[comp->quantizationTableSelector];
            x_pos = (u32)(cl_num * 16);
            __THPInverseDCTNoYPos(__THPMCUBuffer[0], x_pos);
            __THPInverseDCTNoYPos(r28[5], x_pos + 8);
            __THPInverseDCTY8(r28[6], x_pos);
            __THPInverseDCTY8(r28[3], x_pos + 8);

            comp  = &__THPInfo->components[1];
            Gbase = __THPLCWork672[1];
            Gwid  = 320;
            Gq    = __THPInfo->quantTabs[comp->quantizationTableSelector];
            x_pos /= 2;
            __THPInverseDCTNoYPos(__THPMCUBuffer[4], x_pos);

            comp  = &__THPInfo->components[2];
            Gbase = __THPLCWork672[2];
            Gq    = __THPInfo->quantTabs[comp->quantizationTableSelector];
            __THPInverseDCTNoYPos(__THPMCUBuffer[5], x_pos);

            if (__THPInfo->RST != 0) {
                __THPInfo->currMCU--;
                if (__THPInfo->currMCU == 0) {
                    __THPInfo->currMCU = __THPInfo->nMCU;

                    __THPInfo->cnt = 1 + ((__THPInfo->cnt + 6) & 0xFFFFFFF8);

                    if (__THPInfo->cnt > 32) {
                        __THPInfo->cnt = 33;
                    }

                    __THPInfo->components[0].predDC = 0;
                    __THPInfo->components[1].predDC = 0;
                    __THPInfo->components[2].predDC = 0;
                }
            }
        }
    }

    LCStoreData(info->dLC[0], __THPLCWork672[0], 0x2800);
    LCStoreData(info->dLC[1], __THPLCWork672[1], 0xA00);
    LCStoreData(info->dLC[2], __THPLCWork672[2], 0xA00);

    info->dLC[0] += 0x2800;
    info->dLC[1] += 0xA00;
    info->dLC[2] += 0xA00;
}

static void __THPDecompressiMCURowNxN(void)
{
    u8 cl_num;
    u32 x_pos, x;
    THPComponent* comp;
    THPFileInfo* info = __THPInfo;

    x = __THPInfo->xPixelSize;

    LCQueueWait(3);

    for (cl_num = 0; cl_num < __THPInfo->MCUsPerRow; cl_num++) {
        __THPHuffDecodeDCTCompY(info, __THPMCUBuffer[0]);
        __THPHuffDecodeDCTCompY(info, __THPMCUBuffer[1]);
        __THPHuffDecodeDCTCompY(info, __THPMCUBuffer[2]);
        __THPHuffDecodeDCTCompY(info, __THPMCUBuffer[3]);
        __THPHuffDecodeDCTCompU(info, __THPMCUBuffer[4]);
        __THPHuffDecodeDCTCompV(info, __THPMCUBuffer[5]);

        comp  = &__THPInfo->components[0];
        Gbase = __THPLCWork672[0];
        Gwid  = x;
        Gq    = __THPInfo->quantTabs[comp->quantizationTableSelector];
        x_pos = (u32)(cl_num * 16);
        __THPInverseDCTNoYPos(__THPMCUBuffer[0], x_pos);
        __THPInverseDCTNoYPos(__THPMCUBuffer[1], x_pos + 8);
        __THPInverseDCTY8(__THPMCUBuffer[2], x_pos);
        __THPInverseDCTY8(__THPMCUBuffer[3], x_pos + 8);

        comp  = &__THPInfo->components[1];
        Gbase = __THPLCWork672[1];
        Gwid  = x / 2;
        Gq    = __THPInfo->quantTabs[comp->quantizationTableSelector];
        x_pos /= 2;
        __THPInverseDCTNoYPos(__THPMCUBuffer[4], x_pos);

        comp  = &__THPInfo->components[2];
        Gbase = __THPLCWork672[2];
        Gq    = __THPInfo->quantTabs[comp->quantizationTableSelector];
        __THPInverseDCTNoYPos(__THPMCUBuffer[5], x_pos);

        if (__THPInfo->RST != 0) {
            __THPInfo->currMCU--;
            if (__THPInfo->currMCU == 0) {
                __THPInfo->currMCU = __THPInfo->nMCU;
                __THPInfo->cnt     = 1 + ((__THPInfo->cnt + 6) & 0xFFFFFFF8);

                if (__THPInfo->cnt > 32) {
                    __THPInfo->cnt = 33;
                }

                __THPInfo->components[0].predDC = 0;
                __THPInfo->components[1].predDC = 0;
                __THPInfo->components[2].predDC = 0;
            }
        }
    }

    {
        u8** work = __THPLCWork672;
        LCStoreData(info->dLC[0], work[0], ((4 * sizeof(u8) * 64) * (x / 16)));
        LCStoreData(info->dLC[1], work[1], ((sizeof(u8) * 64) * (x / 16)));
        LCStoreData(info->dLC[2], work[2], ((sizeof(u8) * 64) * (x / 16)));
    }
    info->dLC[0] += ((4 * sizeof(u8) * 64) * (x / 16));
    info->dLC[1] += ((sizeof(u8) * 64) * (x / 16));
    info->dLC[2] += ((sizeof(u8) * 64) * (x / 16));
}

static void __THPHuffDecodeDCTCompY(register THPFileInfo* info, THPCoeff* block)
{
    {
        register s32 t;
        THPCoeff dc;
        register THPCoeff diff;

        __dcbz((void*)block, 0);
        t = __THPHuffDecodeTab(info, Ydchuff);
        __dcbz((void*)block, 32);
        diff = 0;
        __dcbz((void*)block, 64);

        if (t) {
            {
                register s32 v;
                register u32 cb;
                register u32 cnt;
                register u32 code;
                register u32 tmp;
                register u32 cnt1;
                register u32 tmp1;
#ifdef __MWERKS__ // clang-format off
                asm {
                    lwz      cnt,info->cnt;
                    subfic   code,cnt,33;
                    lwz      cb,info->currByte;

                    subfc. tmp, code, t;
                    subi     cnt1,cnt,1;

                    bgt      _notEnoughBitsDIFF;
                    add      v,cnt,t;

                    slw      cnt,cb,cnt1;
                    stw      v,info->cnt;
                    subfic   v,t,32;
                    srw      diff,cnt,v;
                }
#endif // clang-format on

#ifdef __MWERKS__ // clang-format off
                asm {
                    b _DoneDIFF;
                _notEnoughBitsDIFF:
                    lwz tmp1, info->file;
                    slw v, cb, cnt1;
                    lwzu cb, 4(tmp1);
                    addi tmp, tmp, 1;
                    stw cb, info->currByte;
                    srw cb, cb, code;
                    stw tmp1, info->file;
                    add v, cb, v;
                    stw tmp, info->cnt;
                    subfic tmp, t, 32;
                    srw diff, v, tmp;
                _DoneDIFF:
                }
#endif // clang-format on
            }

            if (__cntlzw((u32)diff) > 32 - t) {
                diff += ((0xFFFFFFFF << t) + 1);
            }
        };

        __dcbz((void*)block, 96);
        dc       = (s16)(info->components[0].predDC + diff);
        block[0] = info->components[0].predDC = dc;
    }

    {
        register s32 k;
        register s32 code;
        register u32 cnt;
        register u32 cb;
        register u32 increment;
        register s32 tmp;
        register THPHuffmanTab* h = Yachuff;

#ifdef __MWERKS__ // clang-format off
        asm {
            lwz     cnt, info->cnt;
            addi    increment, h, 32;
            lwz     cb, info->currByte;
        }
#endif // clang-format on

        for (k = 1; k < 64; k++)
        {
            register s32 ssss;
            register s32 rrrr;

#ifdef __MWERKS__ // clang-format off
            asm {
                addi    code, cnt, 4;
                cmpwi   cnt, 28;
                rlwnm   tmp, cb, code, 27, 31;
                bgt     _notEnoughBits;

                lbzx    ssss, h, tmp;
                lbzx    code, increment, tmp;
                cmpwi   ssss, 0xFF;

                beq     _FailedCheckEnoughBits;
                add     cnt, cnt, code;
                b       _DoneDecodeTab;
            }
#endif // clang-format on

            {
                register u32 maxcodebase;
                register u32 tmp2;

            _FailedCheckEnoughBits:
                cnt += 5;
                maxcodebase = (u32) & (h->maxCode);
#ifdef __MWERKS__ // clang-format off
                asm {
                    li          tmp2, sizeof(s32)*(5);
                    li          code, 5;
                    add         maxcodebase, maxcodebase, tmp2;
                __WHILE_START:
                    cmpwi       cnt, 33;
                    slwi        tmp, tmp, 1

                    beq         _FCEB_faster;
                    rlwnm       ssss, cb, cnt, 31, 31;
                    lwzu        tmp2, 4(maxcodebase);
                    or          tmp, tmp, ssss
                    addi        cnt, cnt, 1;
                    b __WHILE_CHECK;

                _FCEB_faster:
                    lwz     ssss, info->file;
                    li      cnt, 1;
                    lwzu    cb, 4(ssss);

                    lwzu    tmp2, 4(maxcodebase);

                    stw     ssss, info->file;
                    rlwimi  tmp, cb, 1,31,31;
                    b __FL_WHILE_CHECK;

                __FL_WHILE_START:
                    slwi    tmp, tmp, 1;

                    rlwnm   ssss, cb, cnt, 31, 31;
                    lwzu    tmp2, 4(maxcodebase);
                    or      tmp, tmp, ssss;

                __FL_WHILE_CHECK:
                    cmpw    tmp,tmp2
                    addi    cnt, cnt, 1;
                    addi    code, code, 1
                    bgt     __FL_WHILE_START;
                    b _FCEB_Done;

                __WHILE_CHECK:
                    cmpw    tmp,tmp2
                    addi    code, code, 1
                    bgt     __WHILE_START;
                }
#endif // clang-format on
            }
        _FCEB_Done:
            ssss = (h->Vij[(s32)(tmp + h->valPtr[code])]);
            goto _DoneDecodeTab;

        _notEnoughBits:
#ifdef __MWERKS__ // clang-format off
            asm {
                cmpwi   cnt, 33;
                lwz     tmp, info->file;
                beq     _getfullword;

                cmpwi   cnt, 32;
                rlwnm   code, cb, code, 27, 31
                beq     _1bitleft;

                lbzx    ssss, h, code;
                lbzx    rrrr, increment, code;
                cmpwi   ssss, 0xFF;
                add     code, cnt, rrrr;
                beq _FailedCheckNoBits0;

                cmpwi   code, 33;
                bgt     _FailedCheckNoBits1;
            }
#endif // clang-format on
            cnt = (u32)code;
            goto _DoneDecodeTab;

        _getfullword: {
#ifdef __MWERKS__ // clang-format off
            asm {
                lwzu    cb, 4(tmp);
                rlwinm  code, cb, 5, 27, 31
                stw     tmp, info->file;
                lbzx    ssss, h, code;
                lbzx    tmp, increment, code;
                cmpwi   ssss, 0xFF
                addi    cnt, tmp, 1
                beq     _FailedCheckEnoughbits_Updated;
            }
#endif // clang-format on
        }
            goto _DoneDecodeTab;

        _FailedCheckEnoughbits_Updated:
            ssss = 5;
            do {
#ifdef __MWERKS__ // clang-format off
                asm {
                    subfic  tmp, ssss, 31;
                    addi    ssss, ssss, 1;
                    srw     code, cb, tmp;
                }
#endif // clang-format on
            } while (code > h->maxCode[ssss]);

            cnt  = (u32)(ssss + 1);
            ssss = (h->Vij[(s32)(code + h->valPtr[ssss])]);

            goto _DoneDecodeTab;

        _1bitleft:
#ifdef __MWERKS__ // clang-format off
            asm {
                lwzu    cb, 4(tmp);

                stw     tmp, info->file;
                rlwimi  code, cb, 4, 28, 31;
                lbzx    ssss, h, code;
                lbzx    cnt, increment, code
                cmpwi   ssss, 0xFF
                beq     _Read4;
            }
#endif // clang-format on

            goto _DoneDecodeTab;

        _Read4: {
            register u32 maxcodebase = (u32) & (h->maxCode);
            register u32 tmp2;

#ifdef __MWERKS__ // clang-format off
            asm {
                li  cnt, sizeof(s32)*5;
                add     maxcodebase, maxcodebase, cnt;

                slwi    tmp, code, 32-5;
                li      cnt,5;
                rlwimi  tmp, cb, 32-1, 1,31;

            __DR4_WHILE_START:

                subfic  ssss, cnt, 31;
                lwzu    tmp2, 4(maxcodebase);
                srw     code, tmp, ssss;
            __DR4_WHILE_CHECK:
                cmpw    code, tmp2
                addi    cnt, cnt, 1
                bgt     __DR4_WHILE_START;
            }
#endif // clang-format on
        }
            ssss = (h->Vij[(s32)(code + h->valPtr[cnt])]);
            goto _DoneDecodeTab;

        _FailedCheckNoBits0:
        _FailedCheckNoBits1:
        _REALFAILEDCHECKNOBITS: {
            register u32 mask = 0xFFFFFFFF << (33 - cnt);
            register u32 tmp2;
            register u32 tmp3;
            code = (s32)(cb & (~mask));
            mask = (u32) & (h->maxCode);

#ifdef __MWERKS__ // clang-format off
            asm {
                lwz     tmp, info->file;
                subfic  tmp2, cnt, 33;
                addi    tmp3, tmp2, 1;
                slwi    tmp2, tmp2, 2;
                lwzu    cb, 4(tmp);
                add     mask,mask, tmp2;
                stw     tmp, info->file;
                slwi    code, code, 1;
                rlwimi  code, cb, 1, 31, 31;
                lwzu    tmp2, 4(mask);
                li      cnt, 2;
                b       __FCNB1_WHILE_CHECK;

            __FCNB1_WHILE_START:
                slwi    code, code, 1;

                addi    tmp3, tmp3, 1;
                lwzu    tmp2, 4(mask);
                add     code, code, rrrr;
                addi    cnt, cnt, 1;

            __FCNB1_WHILE_CHECK:
                cmpw    code, tmp2;
                rlwnm   rrrr, cb, cnt, 31, 31;
                bgt     __FCNB1_WHILE_START;
            }
#endif // clang-format on
            ssss = (h->Vij[(s32)(code + h->valPtr[tmp3])]);
        }

            goto _DoneDecodeTab;

        _DoneDecodeTab:
#ifdef __MWERKS__ // clang-format off
            asm {
                andi.   rrrr, ssss, 15;
                srawi   ssss, ssss, 4;
                beq     _RECV_SSSS_ZERO;
            }
#endif // clang-format on

            {
                k += ssss;
                {
                    register s32 v;
                    register u32 cnt1;
                    register u32 tmp1;
#ifdef __MWERKS__ // clang-format off
                    asm {
                        subfic   code,cnt,33;
                        subfc. tmp, code, rrrr;
                        subi     cnt1,cnt,1;
                        bgt      _RECVnotEnoughBits;
                        add      cnt,cnt,rrrr;
                        slw      tmp1,cb,cnt1;
                        subfic   v,rrrr,32;
                        srw      ssss,tmp1,v;
                        b _RECVDone;
                    _RECVnotEnoughBits:
                        lwz tmp1, info->file;
                        slw v, cb, cnt1;
                        lwzu cb, 4(tmp1);
                        addi cnt, tmp, 1;
                        stw tmp1, info->file;
                        srw tmp1, cb, code;

                        add v, tmp1, v;
                        subfic tmp, rrrr, 32;
                        srw ssss, v, tmp;
                    _RECVDone:
                    }
#endif // clang-format on
                }

                if (__cntlzw((u32)ssss) > 32 - rrrr) {
                    ssss += ((0xFFFFFFFF << rrrr) + 1);
                }

                block[__THPJpegNaturalOrder[k]] = (s16)ssss;
                goto _RECV_END;
            }

            {
            _RECV_SSSS_ZERO:
                if (ssss != 15) {
                    break;
                }

                k += 15;
            };

#ifdef __MWERKS__ // clang-format off
            asm { _RECV_END: }
#else // clang-format on
        _RECV_END: // Exists just to shut up VSCode
#endif
        }
        info->cnt      = cnt;
        info->currByte = cb;
    }
}

static void __THPHuffDecodeDCTCompU(register THPFileInfo* info, THPCoeff* block)
{
    THPCoeff dc;

    register s32 v; // r0

    register s16 cnt; // r7
    register u32 tmp; // r9
    register u32 cnt33; // r8
    register u32 cnt1; // r10
    register u32 cb; // r6
    register s32 t; // r5

    register u32 tmp1;
    register s32 k;
    register s32 ssss;
    register s32 rrrr;

    __dcbz((void*)block, 0);
    t = __THPHuffDecodeTab(info, Udchuff);
    __dcbz((void*)block, 32);
    cnt = 0;
    __dcbz((void*)block, 64);

    if (t) {
#ifdef __MWERKS__ // clang-format off
        asm {
            lwz      cnt,info->cnt;
            subfic   cnt33,cnt,33;
            lwz      cb,info->currByte;
            subfc.   tmp, cnt33, t;
            subi     cnt1,cnt,1;
            bgt      _notEnoughBitsDIFF;
            add      v,cnt,t;
            slw      cnt,cb,cnt1;
            stw      v,info->cnt;
            subfic   v,t,32;
            srw      cnt,cnt,v;
        }
#endif // clang-format on

#ifdef __MWERKS__ // clang-format off
        asm {
            b _DoneDIFF;
        _notEnoughBitsDIFF:
            lwz cnt, info->file;
            slw v, cb, cnt1;
            lwzu cb, 4(cnt);
            addi tmp, tmp, 1;
            stw cb, info->currByte;
            srw cb, cb, cnt33;
            stw cnt, info->file;
            add v, cb, v;
            stw tmp, info->cnt;
            subfic tmp, t, 32;
            srw cnt, v, tmp;
        _DoneDIFF:
        }
#endif // clang-format on

        if (__cntlzw((u32)cnt) > 32 - t) {
            cnt += ((0xFFFFFFFF << t) + 1);
        }
    }

    __dcbz((void*)block, 96);
    dc       = (s16)(info->components[1].predDC + cnt);
    block[0] = info->components[1].predDC = dc;

    for (k = 1; k < 64; k++) {
        ssss = __THPHuffDecodeTab(info, Uachuff);
        rrrr = ssss >> 4;
        ssss &= 15;

        if (ssss) {
            k += rrrr;
#ifdef __MWERKS__ // clang-format off
            asm {
                lwz      cnt,info->cnt;
                subfic   cnt33,cnt,33;
                lwz      cb,info->currByte;
                subf. tmp, cnt33, ssss;
                subi     cnt1,cnt,1;
                bgt      _notEnoughBits;
                add      v,cnt,ssss;
                slw      cnt,cb,cnt1;
                stw      v,info->cnt;
                subfic   v,ssss,32;
                srw      rrrr,cnt,v;
            }
#endif // clang-format on

#ifdef __MWERKS__ // clang-format off
            asm {
                b _Done;
            _notEnoughBits:
                lwz tmp1, info->file;
                slw v, cb, cnt1;
                lwzu cb, 4(tmp1);
                addi tmp, tmp, 1;
                stw cb, info->currByte;
                srw cb, cb, cnt33;
                stw tmp1, info->file;
                add v, cb, v;
                stw tmp, info->cnt;
                subfic tmp, ssss, 32;
                srw rrrr, v, tmp;
            _Done:
            }
#endif // clang-format on

            if (__cntlzw((u32)rrrr) > 32 - ssss) {
                rrrr += ((0xFFFFFFFF << ssss) + 1);
            }

            block[__THPJpegNaturalOrder[k]] = (s16)rrrr;
        }

        else {
            if (rrrr != 15)
                break;
            k += 15;
        }
    }
}

static void __THPHuffDecodeDCTCompV(register THPFileInfo* info, THPCoeff* block)
{
    register s32 t;
    register THPCoeff diff;
    THPCoeff dc;
    register s32 v;
    register u32 cb;
    register u32 cnt;
    register u32 cnt33;
    register u32 tmp;
    register u32 cnt1;
    register u32 tmp1;
    register s32 k;
    register s32 ssss;
    register s32 rrrr;

    __dcbz((void*)block, 0);
    t = __THPHuffDecodeTab(info, Vdchuff);
    __dcbz((void*)block, 32);
    diff = 0;
    __dcbz((void*)block, 64);

    if (t) {
#ifdef __MWERKS__ // clang-format off
        asm {
            lwz      cnt,info->cnt;
            subfic   cnt33,cnt,33;
            lwz      cb,info->currByte;
            subf. tmp, cnt33, t;
            subi     cnt1,cnt,1;
            bgt      _notEnoughBitsDIFF;
            add      v,cnt,t;
            slw      cnt,cb,cnt1;
            stw      v,info->cnt;
            subfic   v,t,32;
            srw      diff,cnt,v;
        }
#endif // clang-format on

#ifdef __MWERKS__ // clang-format off
        asm {
            b _DoneDIFF;
        _notEnoughBitsDIFF:
            lwz tmp1, info->file;
            slw v, cb, cnt1;
            lwzu cb, 4(tmp1);
            addi tmp, tmp, 1;
            stw cb, info->currByte;
            srw cb, cb, cnt33;
            stw tmp1, info->file;
            add v, cb, v;
            stw tmp, info->cnt;
            subfic tmp, t, 32;
            srw diff, v, tmp;
        _DoneDIFF:
        }
#endif // clang-format on

        if (__cntlzw((u32)diff) > 32 - t) {
            diff += ((0xFFFFFFFF << t) + 1);
        }
    }

    __dcbz((void*)block, 96);

    dc       = (s16)(info->components[2].predDC + diff);
    block[0] = info->components[2].predDC = dc;

    for (k = 1; k < 64; k++) {
        ssss = __THPHuffDecodeTab(info, Vachuff);
        rrrr = ssss >> 4;
        ssss &= 15;

        if (ssss) {
            k += rrrr;

#ifdef __MWERKS__ // clang-format off
            asm {
                lwz      cnt,info->cnt;
                subfic   cnt33,cnt,33;
                lwz      cb,info->currByte;

                subf. tmp, cnt33, ssss;
                subi     cnt1,cnt,1;

                bgt      _notEnoughBits;
                add      v,cnt,ssss;

                slw      cnt,cb,cnt1;
                stw      v,info->cnt;
                subfic   v,ssss,32;
                srw      rrrr,cnt,v;
            }
#endif // clang-format on

#ifdef __MWERKS__ // clang-format off
            asm {
                b _Done;
            _notEnoughBits:
                lwz tmp1, info->file;
                slw v, cb, cnt1;
                lwzu cb, 4(tmp1);
                addi tmp, tmp, 1;
                stw cb, info->currByte;
                srw cb, cb, cnt33;
                stw tmp1, info->file;
                add v, cb, v;
                stw tmp, info->cnt;
                subfic tmp, ssss, 32;
                srw rrrr, v, tmp;
            _Done:
            }
#endif // clang-format on

            if (__cntlzw((u32)rrrr) > 32 - ssss) {
                rrrr += ((0xFFFFFFFF << ssss) + 1);
            }

            block[__THPJpegNaturalOrder[k]] = (s16)rrrr;
        } else {
            if (rrrr != 15)
                break;
            k += 15;
        }
    }
}

#define OS_GQR_F32 0x0000
#define OS_GQR_U8 0x0004
#define OS_GQR_U16 0x0005
#define OS_GQR_S8 0x0006
#define OS_GQR_S16 0x0007

#define OS_FASTCAST_U8 2
#define OS_FASTCAST_U16 3
#define OS_FASTCAST_S8 4
#define OS_FASTCAST_S16 5

// clang-format off
static inline void OSInitFastCast(void) {
#ifdef __MWERKS__
  asm
  {
        li      r3, OS_GQR_U8
        oris    r3, r3, OS_GQR_U8
        mtspr   GQR2, r3

        li      r3, OS_GQR_U16
        oris    r3, r3, OS_GQR_U16
        mtspr   GQR3, r3

        li      r3, OS_GQR_S8
        oris    r3, r3, OS_GQR_S8
        mtspr   GQR4, r3

        li      r3, OS_GQR_S16
        oris    r3, r3, OS_GQR_S16
        mtspr   GQR5, r3
  }
#else

#endif
}
// clang-format off


BOOL THPInit(void)
{
    u8* base;
    //OSRegisterVersion(__THPVersion);
    base = (u8*)(0xE000 << 16);

    __THPLCWork512[0] = base;
    base += 0x2000;
    __THPLCWork512[1] = base;
    base += 0x800;
    __THPLCWork512[2] = base;
    base += 0x200;

    base              = (u8*)(0xE000 << 16);
    __THPLCWork672[0] = base;
    base += 0x2A00;
    __THPLCWork672[1] = base;
    base += 0xA80;
    __THPLCWork672[2] = base;
    base += 0xA80;

    //OSInitFastCast();

    __THPInitFlag = TRUE;
    return TRUE;
}
