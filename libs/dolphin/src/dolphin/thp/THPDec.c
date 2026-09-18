#include <dolphin.h>

#include <dolphin/thp/thp.h>

#ifdef __MWERKS__
#define THP_SDATA __declspec(section ".sdata")
#else
#define THP_SDATA
#endif

static char __THP420Error[] = "ERROR: THP only supports 4:2:0!!!\n";

static const u8 __THPJpegNaturalOrder[80] = {
    0,  1,  8,  16, 9,  2,  3,  10, 17, 24, 32, 25, 18, 11, 4,  5,
    12, 19, 26, 33, 40, 48, 41, 34, 27, 20, 13, 6,  7,  14, 21, 28,
    35, 42, 49, 56, 57, 50, 43, 36, 29, 22, 15, 23, 30, 37, 44, 51,
    58, 59, 52, 45, 38, 31, 39, 46, 53, 60, 61, 54, 47, 55, 62, 63,
    63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63
};

static const f64 __THPAANScaleFactor[8] = {
    1.0f, 1.387039845f, 1.306562965f, 1.175875602f,
    1.0f, 0.785694958f, 0.541196100f, 0.275899379f,
};

struct THPAlignedHuffmanTabPtr {
    THPHuffmanTab* value;
    u8 padding[0x1C];
};

struct THPAlignedSamplePtr {
    THPSample* value;
    u8 padding[0x1C];
};

struct THPAlignedWidth {
    u32 value;
    u8 padding[0x1C];
};

struct THPQuantizationPtr {
    f32* value;
    u32 padding;
};

static THP_SDATA struct THPAlignedHuffmanTabPtr Ydchuff ATTRIBUTE_ALIGN(32);
static THP_SDATA struct THPAlignedHuffmanTabPtr Udchuff ATTRIBUTE_ALIGN(32);
static THP_SDATA struct THPAlignedHuffmanTabPtr Vdchuff ATTRIBUTE_ALIGN(32);
static THP_SDATA struct THPAlignedHuffmanTabPtr Yachuff ATTRIBUTE_ALIGN(32);
static THP_SDATA struct THPAlignedHuffmanTabPtr Uachuff ATTRIBUTE_ALIGN(32);
static THP_SDATA struct THPAlignedHuffmanTabPtr Vachuff ATTRIBUTE_ALIGN(32);
static f32 __THPIDCTWorkspace[64] ATTRIBUTE_ALIGN(32);
static THP_SDATA struct THPAlignedSamplePtr Gbase ATTRIBUTE_ALIGN(32);
static THP_SDATA struct THPAlignedWidth Gwid ATTRIBUTE_ALIGN(32);
static THP_SDATA struct THPQuantizationPtr Gq ATTRIBUTE_ALIGN(32);
struct THPLCWork {
    u8* offsets512[2][5];
    u8* offsets672[2][9];
    u8* work512[3];
};
static struct THPLCWork __THPLC;
extern u8* __THPLCWork672[3];

#define THPROUNDUP(a, b) ((((s32) (a)) + ((s32) (b) - 1L)) / ((s32) (b)))

void __THPPrepBitStream(THPFileInfo* info)
{
    u32* ptr;
    u32 offset, i, j, k;

    ptr = (u32*) ((uintptr_t) info->file & ~3);
    offset = (uintptr_t) info->file & 3;

    if (info->cnt != 33) {
        info->cnt -= (3 - offset) * 8;
    } else {
        info->cnt = (offset * 8) + 1;
    }

    info->file = (u8*) ptr;
    info->currByte = *ptr;

    for (i = 0; i < 4; i++) {
        if (info->validHuffmanTabs & (1 << i)) {
            for (j = 0; j < 32; j++) {
                info->huffmanTabs[i].quick[j] = 0xFF;

                for (k = 0; k < 5; k++) {
                    s32 code = j >> (5 - k - 1);

                    if (code <= info->huffmanTabs[i].maxCode[k + 1]) {
                        info->huffmanTabs[i]
                            .quick[j] = info->huffmanTabs[i].Vij[(
                            s32) (code + info->huffmanTabs[i].valPtr[k + 1])];
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

        Ydchuff.value = &info->huffmanTabs[YdcTab];
        Udchuff.value = &info->huffmanTabs[UdcTab];
        Vdchuff.value = &info->huffmanTabs[VdcTab];

        Yachuff.value = &info->huffmanTabs[YacTab];
        Uachuff.value = &info->huffmanTabs[UacTab];
        Vachuff.value = &info->huffmanTabs[VacTab];
    }
}

s32 THPDec_8032F8D4(u8* data, THPDec_8032FD40_Data* out)
{
    u8 hSample[4];
    u8 vSample[4];
    u8 componentId[4];
    u8 quantizationSelector[4];
    u8 marker;
    u8 componentCount;
    u8 tag[5] = "JFIF";
    u8 i;
    u8 valid;
    u32 j;
    u16 length;

    valid = 0;
    memset(out, 0, 0xC);

    {
        u8 soi0 = *data++;
        u8 soi1 = *data++;

        if (soi0 != 0xFF || soi1 != 0xD8) {
            return 0;
        }
    }

    for (;;) {
        if (*data++ != 0xFF) {
            return 0;
        }

        while ((s8) *data == 0xFF) {
            data++;
        }
        marker = *data++;

        if (marker == 0xC0) {
            out->_pad = data[4] | (data[3] << 8);
            out->val1 = data[6] | (data[5] << 8);
            componentCount = data[7];
            data += 8;

            if (componentCount != 3) {
                return 0;
            }

            for (i = 0; i < componentCount; i++) {
                u8 factors;

                componentId[i] = *data++;
                factors = *data++;
                hSample[i] = (u8) (factors >> 4);
                vSample[i] = (u8) (factors & 0xF);
                quantizationSelector[i] = *data++;
            }

            if (hSample[0] / hSample[1] == 2 && hSample[0] / hSample[2] == 2) {
                if (vSample[0] / vSample[1] == 2 &&
                    vSample[0] / vSample[2] == 2)
                {
                    out->val2 = 4;
                } else if (vSample[0] == vSample[1] &&
                           vSample[0] == vSample[2])
                {
                    out->val2 = 2;
                }
            } else if (hSample[0] == hSample[1] && hSample[0] == hSample[2]) {
                if (vSample[0] == vSample[1] && vSample[0] == vSample[2]) {
                    out->val2 = 1;
                }
            } else {
                return 0;
            }
        } else if (marker == 0xE0) {
            length = *data++;
            length = (u16) ((length << 8) | *data++);
            for (i = 0; i < 5; i++) {
                componentCount = *data++;
                if (componentCount != tag[i]) {
                    return 0;
                }
            }
            valid = 1;
            for (j = 0; j < (u32) (length - 7); j++) {
                data++;
            }
        } else if (marker == 0xDA) {
            break;
        } else if (0xC0 <= marker && marker <= 0xFE) {
            length = data[1] | (data[0] << 8);
            data += 2;

            for (j = 0; j < (u32) (length - 2); j++) {
                data++;
            }
        }

        if (out->val2 != 0 && valid != 0) {
            break;
        }
    }

    return 1;
}

s32 THPDec_8032FD40(THPDec_8032FD40_Data* data, u16 num)
{
    s32 base = data->val0 + 0x4028;
    s32 a;
    if (data->val2 != 4) {
        OSReport(__THP420Error);
        return 0;
    }
    a = (data->val1 / 2) * (num / 2) * 2 + (data->val1 * num);
    base = base + a;
    return base;
}

typedef struct THPVideoDecodeHeader {
    u16 xSize;
    u16 ySize;
} THPVideoDecodeHeader;

/**
 * Reads the headers of one compressed THP video frame into @p work.
 *
 * @param header Frame dimensions.
 * @param status_out Receives the status code: 0 on success, an error code
 *                   otherwise.
 * @param work   The decode work area, sized by ::THPDec_8032FD40.
 * @param data   The compressed frame data.
 * @param desc   The image descriptor built by ::THPDec_8032F8D4.
 * @return       @p work, ready for ::THPDec_80331340 / ::THPDec_803313D0, or
 *               NULL if the frame could not be read.
 */
THPFileInfo* THPVideoDecode(void* hdr, void* status_out, THPFileInfo* work,
                            void* data, THPDec_8032FD40_Data* desc)
{
    u8 done;
    THPFileInfo* info = work;
    THPVideoDecodeHeader* header = hdr;
    u8* statusOut = status_out;
    u8 status;
    s32 length;
    u32 i;

    DCZeroRange(info, 0x920);
    info->scratch = (u8*) info;
    info->scratch += 0x920;
    info->xSize = header->xSize;
    info->ySize = header->ySize;
    info->file = info->scanStart;
    info->cnt = 33;
    info->x8EC = 0;
    info->x8EE = 0;
    info->x8D2 = 0;
    info->x8E8 = 0;
    info->x8EA = 0;
    info->x7D = 0;
    info->dataStart = data;
    THPDec_803300E0(info);
    done = FALSE;
    info->file = info->dataStart;

    for (;;) {
        if ((*(info->file)++) != 0xFF) {
            goto _err_bad_syntax;
        }

        while (*info->file == 0xFF) {
            info->file++;
        }

        status = (*(info->file)++);

        if (status <= 0xD7) {
            if (status == 0xC4) {
                status = __THPReadHuffmanTableSpecification(info);
                if (status != 0) {
                    goto _err_bad_status;
                }
            } else if (status == 0xC0) {
                status = __THPReadFrameHeader(info);
                if (status != 0) {
                    goto _err_bad_status;
                }
            } else {
                *statusOut = 11;
                return NULL;
            }
        } else if (0xD8 <= status && status <= 0xDF) {
            if (status == 0xDD) {
                __THPRestartDefinition(info);
            } else if (status == 0xDB) {
                status = __THPReadQuantizationTable(info);
                if (status != 0) {
                    goto _err_bad_status;
                }
            } else if (status == 0xDA) {
                status = __THPReadScaneHeader(info);
                if (status != 0) {
                    goto _err_bad_status;
                }
                done = TRUE;
                info->scanStart = info->file;
            } else if (status != 0xD8) {
                *statusOut = 11;
                return NULL;
            }
        } else if (0xE0 <= status) {
            if (status == 0xE0) {
                status = THPDec_80330158(info);
                if (status != 0) {
                    goto _err_bad_status;
                }
            } else if (0xE1 <= status && status <= 0xEF) {
                THPDec_803302EC(&info->file);
            } else if (status == 0xFE) {
                length = (info->file[0] << 8) | info->file[1];
                info->file += 2;
                for (i = 0; i < length - 2; i++) {
                    info->file++;
                }
            } else {
                *statusOut = 11;
                return NULL;
            }
        }

        if (done) {
            *statusOut = 0;
            return work;
        }
    }

_err_bad_syntax:
    *statusOut = 3;
    goto _err_exit;

_err_bad_status:
    *statusOut = status;

_err_exit:
    return NULL;
}

/**
 * Carves the sixteen ::THPFileInfo::mcuBuffer blocks, 128 bytes each, out of
 * the work area's scratch space.
 *
 * @remarks The walk advances eight words at a time over @p info, so the
 *          buffers and the scratch pointer are written by word index
 *          (`[4]`..`[11]` is `mcuBuffer`, `[577]` is `scratch`).
 */
void THPDec_803300E0(THPFileInfo* info)
{
    s32 val;
    s32 offset;
    u8 count;
    u32* buffer;

    buffer = (u32*) info;
    count = 0;
    val = (buffer[577] + 31) & 0xFFFFFFE0;
    buffer[577] = (val + 2048);
    offset = val;
    while (count < 16) {
        buffer[4] = offset;
        buffer[5] = offset + 128;
        buffer[6] = offset + 256;
        buffer[7] = offset + 384;
        offset += 1024;
        buffer[8] = offset - 512;
        buffer[9] = offset - 384;
        buffer[10] = offset - 256;
        buffer[11] = offset - 128;
        buffer += 8;
        count += 8;
    }
}

u8 THPDec_80330158(THPFileInfo* info)
{
    u8 tag[5] = "JFIF";
    u16 length;
    u32 i;
    u8 xThumb;
    u8 yThumb;
    u16 version;
    u8 units;
    u32 segmentLength;

    length = (u16) ((info->file[0] << 8) | info->file[1]);
    info->file += 2;

    for (i = 0; i < 5; i++) {
        if (*(info->file)++ != tag[i]) {
            return 3;
        }
    }

    version = (u16) ((info->file[0] << 8) | info->file[1]);
    info->file += 2;
    units = *(info->file)++;
    info->file += 1;
    info->file += 1;
    info->file += 1;
    info->file += 1;

    xThumb = *(info->file)++;
    yThumb = *(info->file)++;

    if (xThumb != 0 || yThumb != 0) {
        return 7;
    }

    segmentLength = (u32) (info->file - info->dataStart);
    if (length + 4 != segmentLength) {
        return 8;
    }

    return 0;
}

s32 THPDec_803302EC(u8** data)
{
    u32 i;
    u8* ptr = *data;
    u16 high = ptr[0];
    u16 low = ptr[1];

    u16 count = (high << 8) | low;
    for (i = 0; i < count; i++) {
        (*data)++;
    }

    return 0;
}

u8 THPDec_803310CC(THPFileInfo* info);

static u8 __THPReadFrameHeader(THPFileInfo* info)
{
    u8 i;
    u8 j;
    u8 k;
    THPComponent* comp;
    u8 utmp8;
    u16 ySize;

    info->file += 2;

    utmp8 = (*(info->file)++);

    if (utmp8 != 8) {
        return 10;
    }

    info->yPixelSize = (u16) ((info->file)[0] << 8 | (info->file)[1]);
    info->file += 2;
    info->xPixelSize = (u16) ((info->file)[0] << 8 | (info->file)[1]);
    info->file += 2;

    info->nComponents = (*(info->file)++);
    if (info->nComponents != 3 && info->nComponents != 1) {
        return 12;
    }

    for (i = 0; i < info->nComponents; i++) {
        info->components[i].componentID = (*(info->file)++);
        utmp8 = (*(info->file)++);
        info->components[i].samplingH = (u8) (utmp8 >> 4);
        info->components[i].samplingV = (u8) (utmp8 & 0xF);
        info->components[i].quantizationTableSelector = (*(info->file)++);
    }

    info->samplingHMax = 1;
    info->samplingVMax = 1;
    for (j = 0; j < info->nComponents; j++) {
        comp = &info->components[j];
        info->samplingHMax = info->samplingHMax > comp->samplingH
                                 ? info->samplingHMax
                                 : comp->samplingH;
        info->samplingVMax = info->samplingVMax > comp->samplingV
                                 ? info->samplingVMax
                                 : comp->samplingV;
    }

    ySize = info->yPixelSize;
    info->x8D4 =
        (u16) THPROUNDUP(ySize, THPROUNDUP(ySize, info->samplingVMax * 8));
    for (k = 0; k < info->nComponents; k++) {
        info->components[k].x08 =
            THPROUNDUP(info->xPixelSize * info->components[k].samplingH,
                       info->samplingHMax);
        info->components[k].x0C =
            THPROUNDUP(info->yPixelSize * info->components[k].samplingV,
                       info->samplingVMax);
    }

    return 0;
}

static u8 __THPReadQuantizationTable(THPFileInfo* info)
{
    u16 length, id, i, row, col;
    f32 q_temp[64];

    length = (u16) ((info->file)[0] << 8 | (info->file)[1]);
    info->file += 2;
    length -= 2;

    for (;;) {
        id = (*(info->file)++);

        for (i = 0; i < 64; i++) {
            q_temp[__THPJpegNaturalOrder[i]] = (f32) (*(info->file)++);
        }

        info->validQuantTabs |= 1 << id;

        i = 0;
        for (row = 0; row < 8; row++) {
            for (col = 0; col < 8; col++) {
                info->quantTabs[id][i] = q_temp[i] * __THPAANScaleFactor[row] *
                                         __THPAANScaleFactor[col];
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
    u8 result;

    length = (u16) ((info->file)[0] << 8 | (info->file)[1]);
    info->file += 2;
    length -= 2;

    for (;;) {
        i = (*(info->file)++);
        id = (u8) (i & 15);
        t_class = (u8) (i >> 4);
        huffmanBits = info->file;
        tab_index = (u8) ((id << 1) + t_class);
        num_Vij = 0;

        for (i = 0; i < 16; i++) {
            num_Vij += (*(info->file)++);
        }

        info->huffmanTabs[tab_index].bits = huffmanBits;
        info->huffmanTabs[tab_index].Vij = info->file;
        info->huffmanTabs[tab_index].numVij = num_Vij;
        info->file += num_Vij;
        result =
            __THPHuffGenerateSizeTable(info, tab_index, (int) huffmanBits);
        if (result) {
            return result;
        }
        result = __THPHuffGenerateCodeTable(info, tab_index);
        if (result) {
            return result;
        }
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
    u8 numComponents;
    u8 i;
    u8* ptr;
    info->file += 2;
    ptr = info->file;
    info->file++;
    numComponents = *ptr;

    if (numComponents != info->nComponents) {
        return 12;
    }

    for (i = 0; i < numComponents; i++) {
        u8 selectors;
        u16 blocksPerRow;
        u16 rows;
        s32 shift;

        selectors = *info->file++;
        selectors = *info->file++;

        info->components[i].DCTableSelector = (u8) (selectors >> 4);
        info->components[i].ACTableSelector = (u8) (selectors & 0xF);

        if (!(info->validHuffmanTabs & (1 << (selectors >> 4)))) {
            return 15;
        }
        if (!(info->validHuffmanTabs & (1 << ((selectors & 0xF) + 1)))) {
            return 15;
        }

        info->x74 = info->xSize;
        info->decompressedY = info->ySize;

        blocksPerRow = info->components[i].x08;
        rows = THPROUNDUP(info->decompressedY, info->x8D4);
        rows += (info->decompressedY % info->x8D4 == 0) ? 0 : 1;
        rows *= info->x8D4;
        shift = info->samplingVMax - info->components[i].samplingV;
        rows >>= shift;
        info->components[i].x10 = (uintptr_t) info->scratch;
        info->scratch += blocksPerRow * rows;
    }

    info->file += 3;
    return THPDec_803310CC(info);
}

static u8 __THPHuffGenerateSizeTable(THPFileInfo* info, u8 tab_index,
                                     int huffmanBits)
{
    u8* bits;
    s32 p;
    s32 l;
    s32 i;

    bits = (u8*) huffmanBits;

    p = 0;
    for (l = 1; l <= 16; l++) {
        p += bits[l - 1];
    }

    info->huffmanTabs[tab_index].sizeTab = (s8*) info->scratch;
    info->scratch += p + 1;

    p = 0;
    for (l = 1; l <= 16; l++) {
        i = bits[l - 1];
        while (i--) {
            info->huffmanTabs[tab_index].sizeTab[p++] = (s8) l;
        }
    }

    info->huffmanTabs[tab_index].sizeTab[p] = 0;
    info->huffmanTabs[tab_index].numCodes = p;
    return 0;
}

static u8 __THPHuffGenerateCodeTable(THPFileInfo* info, u8 tab_index)
{
    s32 si;
    u32 code;
    s32 p;

    p = 0;
    si = info->huffmanTabs[tab_index].sizeTab[0];
    while (info->huffmanTabs[tab_index].sizeTab[p]) {
        while (info->huffmanTabs[tab_index].sizeTab[p] == si) {
            p++;
        }
        si++;
    }

    info->huffmanTabs[tab_index].codeTab = (u32*) info->scratch;
    info->scratch += p * sizeof(u32);

    p = 0;
    code = 0;
    si = info->huffmanTabs[tab_index].sizeTab[0];
    while (info->huffmanTabs[tab_index].sizeTab[p]) {
        while (info->huffmanTabs[tab_index].sizeTab[p] == si) {
            info->huffmanTabs[tab_index].codeTab[p++] = code;
            code++;
        }

        code <<= 1;
        si++;
    }

    return 0;
}

static int __THPHuffGenerateDecoderTables(THPFileInfo* info, u8 tabIndex)
{
    s32 p, l;
    THPHuffmanTab* h;

    p = 0;
    h = &info->huffmanTabs[tabIndex];
    for (l = 1; l <= 16; l++) {
        if (h->bits[l - 1]) {
            h->valPtr[l] = p - h->codeTab[p];
            p += h->bits[l - 1];
            h->maxCode[l] = h->codeTab[p - 1];
        } else {
            h->maxCode[l] = -1;
            h->valPtr[l] = -1;
        }
    }

    h->maxCode[17] = 0xfffffL;

    return 0;
}

u8 THPDec_803310CC(THPFileInfo* info)
{
    u32 i;
    s32 j;

    info->MCUsPerRow =
        (u16) THPROUNDUP(info->xPixelSize, info->samplingHMax * 8);
    info->x8D0 = (u16) THPROUNDUP(info->yPixelSize, info->samplingVMax * 8);
    info->x8CE = 0;

    for (i = 0; i < info->nComponents; i++) {
        THPComponent* c = &info->components[i];

        c->x28 = THPROUNDUP(info->xPixelSize * c->samplingH,
                            info->samplingHMax * 8);
        c->x24 = THPROUNDUP(info->yPixelSize * c->samplingV,
                            info->samplingVMax * 8);
        c->x14 = c->samplingH;
        c->x18 = c->samplingV;
        c->x1C = c->x14 * c->x18;
        c->x20 = c->x14 * 8;

        j = c->x1C;
        if (info->x8CE + c->x1C > 0x10) {
            return 0x11;
        }

        while (j-- > 0) {
            info->x8BC[info->x8CE++] = i;
        }

        if (info->x8CE > 6) {
            OSReport("THP does not support anything other than 4:2:0!\n");
            return 0;
        }

        c->predDC = 0;
    }

    return 0;
}

static u8 __THPRestartDefinition(THPFileInfo* info)
{
    info->RST = TRUE;
    info->file += 2;
    info->nMCU = (u16) ((info->file)[0] << 8 | (info->file)[1]);
    info->file += 2;
    info->currMCU = info->nMCU;
    return 0;
}

#ifdef __MWERKS__
#pragma function_align 16
#endif

void THPDec_80331340(THPFileInfo* info, void* tileY, void* tileU, void* tileV)
{
    info->tileY = tileY;
    info->tileU = tileU;
    info->tileV = tileV;

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

    __THPPrepBitStream(info);
    while (info->x8EE < info->x8EA + info->decompressedY) {
        __THPDecompressiMCURow640x480(info);
        info->x8EE += info->x8D4;
    }
}

void THPDec_803313D0(THPFileInfo* info, void* tileY, void* tileU, void* tileV,
                     u32 x)
{
    u32 width = x;
    info->tileY = tileY;
    info->tileU = tileU;
    info->tileV = tileV;

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

    __THPPrepBitStream(info);
    while (info->x8EE < info->x8EA + info->decompressedY) {
        __THPDecompressiMCURowNxN(info, width);
        info->x8EE += info->x8D4;
    }
}

inline void __THPInverseDCTNoYPos(register THPCoeff* in, register u32 xPos)
{
    register f32 *q, *ws;
    register f32 tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7, tmp8, tmp9;
    register f32 tmp10, tmp11, tmp12, tmp13;
    register f32 tmp20, tmp21, tmp22, tmp23;
    register f32 cc4 = 1.414213562F;
    register f32 cc2 = 1.847759065F;
    register f32 cc2c6s = 1.082392200F;
    register f32 cc2c6a = -2.613125930F;
    register f32 bias = 1024.0F;
    q = Gq.value;
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

        _loopHead1:
            or.         itmp0, itmp0, itmp3
            lhz         itmp2, 0x2(in)
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
        register THPSample* obase = Gbase.value;
        register u32 wid = Gwid.value;

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
    register f32 cc4 = 1.414213562F;
    register f32 cc2 = 1.847759065F;
    register f32 cc2c6s = 1.082392200F;
    register f32 cc2c6a = -2.613125930F;
    register f32 bias = 1024.0F;

    q = Gq.value;
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
        register THPSample* obase = Gbase.value;
        register u32 wid = Gwid.value;

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

inline s32 __THPHuffDecodeTab(register THPFileInfo* info,
                              register THPHuffmanTab* h)
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
    return (h->Vij[(s32) (tmp + h->valPtr[code])]);

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
    return (h->Vij[(s32) (code + h->valPtr[cnt])]);

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
    return (s32) cnt;

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

    code = (s32) (cb & (~mask));
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

    info->cnt = (u32) tmp;
    return (h->Vij[(s32) (code + h->valPtr[cnt])]);
}

static void __THPDecompressiMCURow640x480(THPFileInfo* info)
{
    u8 cl_num;
    u32 x_pos;
    THPComponent* comp;

    LCQueueWait(3);

    for (cl_num = 0; cl_num < info->MCUsPerRow; cl_num++) {
        __THPHuffDecodeDCTCompY(info, info->mcuBuffer[0]);
        __THPHuffDecodeDCTCompY(info, info->mcuBuffer[1]);
        __THPHuffDecodeDCTCompY(info, info->mcuBuffer[2]);
        __THPHuffDecodeDCTCompY(info, info->mcuBuffer[3]);
        __THPHuffDecodeDCTCompU(info, info->mcuBuffer[4]);
        __THPHuffDecodeDCTCompV(info, info->mcuBuffer[5]);

        Gbase.value = __THPLCWork672[0];
        Gwid.value = 640;
        Gq.value =
            info->quantTabs[info->components[0].quantizationTableSelector];
        x_pos = (u32) (cl_num * 16);
        __THPInverseDCTNoYPos(info->mcuBuffer[0], x_pos);
        __THPInverseDCTNoYPos(info->mcuBuffer[1], x_pos + 8);
        __THPInverseDCTY8(info->mcuBuffer[2], x_pos);
        __THPInverseDCTY8(info->mcuBuffer[3], x_pos + 8);

        comp = &info->components[1];
        Gbase.value = __THPLCWork672[1];
        Gwid.value = 320;
        Gq.value = info->quantTabs[comp->quantizationTableSelector];
        x_pos /= 2;
        __THPInverseDCTNoYPos(info->mcuBuffer[4], x_pos);

        comp = &info->components[2];
        Gbase.value = __THPLCWork672[2];
        Gq.value = info->quantTabs[comp->quantizationTableSelector];
        __THPInverseDCTNoYPos(info->mcuBuffer[5], x_pos);

        if (info->RST != 0) {
            info->currMCU--;
            if (info->currMCU == 0) {
                info->currMCU = info->nMCU;

                info->cnt = 1 + ((info->cnt + 6) & 0xFFFFFFF8);

                if (info->cnt > 32) {
                    info->cnt = 33;
                }

                info->components[0].predDC = 0;
                info->components[1].predDC = 0;
                info->components[2].predDC = 0;
            }
        }
    }

    LCStoreData(info->tileY, __THPLCWork672[0], 0x2800);
    LCStoreData(info->tileU, __THPLCWork672[1], 0xA00);
    LCStoreData(info->tileV, __THPLCWork672[2], 0xA00);

    info->tileY += 0x2800;
    info->tileU += 0xA00;
    info->tileV += 0xA00;
}

static void __THPDecompressiMCURowNxN(THPFileInfo* info, u32 x)
{
    u8 cl_num;
    u32 x_pos;
    THPComponent* comp;

    LCQueueWait(3);

    for (cl_num = 0; cl_num < info->MCUsPerRow; cl_num++) {
        __THPHuffDecodeDCTCompY(info, info->mcuBuffer[0]);
        __THPHuffDecodeDCTCompY(info, info->mcuBuffer[1]);
        __THPHuffDecodeDCTCompY(info, info->mcuBuffer[2]);
        __THPHuffDecodeDCTCompY(info, info->mcuBuffer[3]);
        __THPHuffDecodeDCTCompU(info, info->mcuBuffer[4]);
        __THPHuffDecodeDCTCompV(info, info->mcuBuffer[5]);

        comp = &info->components[0];
        Gbase.value = __THPLCWork672[0];
        Gwid.value = x;
        Gq.value = info->quantTabs[comp->quantizationTableSelector];
        x_pos = (u32) (cl_num * 16);
        __THPInverseDCTNoYPos(info->mcuBuffer[0], x_pos);
        __THPInverseDCTNoYPos(info->mcuBuffer[1], x_pos + 8);
        __THPInverseDCTY8(info->mcuBuffer[2], x_pos);
        __THPInverseDCTY8(info->mcuBuffer[3], x_pos + 8);

        comp = &info->components[1];
        Gbase.value = __THPLCWork672[1];
        Gwid.value = x / 2;
        Gq.value = info->quantTabs[comp->quantizationTableSelector];
        x_pos /= 2;
        __THPInverseDCTNoYPos(info->mcuBuffer[4], x_pos);

        comp = &info->components[2];
        Gbase.value = __THPLCWork672[2];
        Gq.value = info->quantTabs[comp->quantizationTableSelector];
        __THPInverseDCTNoYPos(info->mcuBuffer[5], x_pos);

        if (info->RST != 0) {
            info->currMCU--;
            if (info->currMCU == 0) {
                info->currMCU = info->nMCU;
                info->cnt = 1 + ((info->cnt + 6) & 0xFFFFFFF8);

                if (info->cnt > 32) {
                    info->cnt = 33;
                }

                info->components[0].predDC = 0;
                info->components[1].predDC = 0;
                info->components[2].predDC = 0;
            }
        }
    }

    LCStoreData(info->tileY, __THPLCWork672[0],
                ((4 * sizeof(u8) * 64) * (x / 16)));
    LCStoreData(info->tileU, __THPLCWork672[1],
                ((sizeof(u8) * 64) * (x / 16)));
    LCStoreData(info->tileV, __THPLCWork672[2],
                ((sizeof(u8) * 64) * (x / 16)));

    info->tileY += ((4 * sizeof(u8) * 64) * (x / 16));
    info->tileU += ((sizeof(u8) * 64) * (x / 16));
    info->tileV += ((sizeof(u8) * 64) * (x / 16));
}

static void __THPHuffDecodeDCTCompY(register THPFileInfo* info,
                                    THPCoeff* block)
{
    {
        register s32 t;
        THPCoeff dc;
        register THPCoeff diff;

        __dcbz((void*) block, 0);
        t = __THPHuffDecodeTab(info, Ydchuff.value);
        __dcbz((void*) block, 32);
        diff = 0;
        __dcbz((void*) block, 64);

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

            if (__cntlzw((u32) diff) > 32 - t) {
                diff += ((0xFFFFFFFF << t) + 1);
            }
        };

        __dcbz((void*) block, 96);
        dc = (s16) (info->components[0].predDC + diff);
        block[0] = info->components[0].predDC = dc;
    }

    {
        register s32 k;
        register s32 code;
        register u32 cnt;
        register u32 cb;
        register u32 increment;
        register s32 tmp;
        register THPHuffmanTab* h = Yachuff.value;

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
            ssss = (h->Vij[(s32) (tmp + h->valPtr[code])]);
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
            cnt = (u32) code;
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

            cnt = (u32) (ssss + 1);
            ssss = (h->Vij[(s32) (code + h->valPtr[ssss])]);

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
            ssss = (h->Vij[(s32) (code + h->valPtr[cnt])]);
            goto _DoneDecodeTab;

        _FailedCheckNoBits0:
        _FailedCheckNoBits1:
        _REALFAILEDCHECKNOBITS: {
            register u32 mask = 0xFFFFFFFF << (33 - cnt);
            register u32 tmp2;
            register u32 tmp3;
            code = (s32) (cb & (~mask));
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
            ssss = (h->Vij[(s32) (code + h->valPtr[tmp3])]);
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

                if (__cntlzw((u32) ssss) > 32 - rrrr) {
                    ssss += ((0xFFFFFFFF << rrrr) + 1);
                }

                block[__THPJpegNaturalOrder[k]] = (s16) ssss;
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
        info->cnt = cnt;
        info->currByte = cb;
    }
}

static void __THPHuffDecodeDCTCompU(register THPFileInfo* info,
                                    THPCoeff* block)
{
    THPCoeff dc;

    register s32 v; // r0

    register s16 cnt; // r7
    register s32 tmp; // r9
    register s32 nbits;
    register u32 cnt1;  // r10
    register u32 cnt33; // r8
    register u32 cb;    // r6
    register s32 t;     // r5

    register s32 k;
    register s32 ssss;

    __dcbz((void*) block, 0);
    t = __THPHuffDecodeTab(info, Udchuff.value);
    __dcbz((void*) block, 32);
    cnt = 0;
    __dcbz((void*) block, 64);

    if (t) {
        {
            register u32 cb2;
            register u32 code;
            register u32 cnt12;
#ifdef __MWERKS__ // clang-format off
            asm {
                lwz      cnt,info->cnt;
                subfic   code,cnt,33;
                lwz      cb2,info->currByte;
                subfc.   tmp, code, t;
                subi     cnt12,cnt,1;
                bgt      _notEnoughBitsDIFF;
                add      v,cnt,t;
                slw      cnt,cb2,cnt12;
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
                slw v, cb2, cnt12;
                lwzu cb2, 4(cnt);
                addi tmp, tmp, 1;
                stw cb2, info->currByte;
                srw cb2, cb2, code;
                stw cnt, info->file;
                add v, cb2, v;
                stw tmp, info->cnt;
                subfic tmp, t, 32;
                srw cnt, v, tmp;
            _DoneDIFF:
            }
#endif // clang-format on
        }

        if (__cntlzw((u32) cnt) > 32 - t) {
            cnt += ((0xFFFFFFFF << t) + 1);
        }
    }

    __dcbz((void*) block, 96);
    dc = (s16) (info->components[1].predDC + cnt);
    block[0] = info->components[1].predDC = dc;

    for (k = 1; k < 64; k++) {
        ssss = __THPHuffDecodeTab(info, Uachuff.value);
        nbits = ssss & 15;
        tmp = ssss >> 4;

        if (nbits) {
            k += tmp;
#ifdef __MWERKS__ // clang-format off
            asm {
                lwz      tmp,info->cnt;
                subfic   cnt33,tmp,33;
                lwz      cnt1,info->currByte;
                subf. cb, cnt33, nbits;
                subi     ssss,tmp,1;
                bgt      _notEnoughBits;
                add      v,tmp,nbits;
                slw      tmp,cnt1,ssss;
                stw      v,info->cnt;
                subfic   v,nbits,32;
                srw      tmp,tmp,v;
            }
#endif // clang-format on

#ifdef __MWERKS__ // clang-format off
            asm {
                b _Done;
            _notEnoughBits:
                lwz tmp, info->file;
                slw v, cnt1, ssss;
                lwzu cnt1, 4(tmp);
                addi cb, cb, 1;
                stw cnt1, info->currByte;
                srw cnt1, cnt1, cnt33;
                stw tmp, info->file;
                add v, cnt1, v;
                stw cb, info->cnt;
                subfic cb, nbits, 32;
                srw tmp, v, cb;
            _Done:
            }
#endif // clang-format on

            if (__cntlzw((u32) tmp) > 32 - nbits) {
                tmp += ((0xFFFFFFFF << nbits) + 1);
            }

            block[__THPJpegNaturalOrder[k]] = (s16) tmp;
        }

        else {
            if (tmp != 15) {
                break;
            }
            k += 15;
        }
    }
}

static void __THPHuffDecodeDCTCompV(register THPFileInfo* info,
                                    THPCoeff* block)
{
    THPCoeff dc;

    register s32 v; // r0

    register s16 cnt; // r7
    register s32 tmp; // r9
    register s32 nbits;
    register u32 cnt1;  // r10
    register u32 cnt33; // r8
    register u32 cb;    // r6
    register s32 t;     // r5

    register s32 k;
    register s32 ssss;

    __dcbz((void*) block, 0);
    t = __THPHuffDecodeTab(info, Vdchuff.value);
    __dcbz((void*) block, 32);
    cnt = 0;
    __dcbz((void*) block, 64);

    if (t) {
        {
            register u32 cb2;
            register u32 code;
            register u32 cnt12;
#ifdef __MWERKS__ // clang-format off
            asm {
                lwz      cnt,info->cnt;
                subfic   code,cnt,33;
                lwz      cb2,info->currByte;
                subf.    tmp, code, t;
                subi     cnt12,cnt,1;
                bgt      _notEnoughBitsDIFF;
                add      v,cnt,t;
                slw      cnt,cb2,cnt12;
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
                slw v, cb2, cnt12;
                lwzu cb2, 4(cnt);
                addi tmp, tmp, 1;
                stw cb2, info->currByte;
                srw cb2, cb2, code;
                stw cnt, info->file;
                add v, cb2, v;
                stw tmp, info->cnt;
                subfic tmp, t, 32;
                srw cnt, v, tmp;
            _DoneDIFF:
            }
#endif // clang-format on
        }

        if (__cntlzw((u32) cnt) > 32 - t) {
            cnt += ((0xFFFFFFFF << t) + 1);
        }
    }

    __dcbz((void*) block, 96);
    dc = (s16) (info->components[2].predDC + cnt);
    block[0] = info->components[2].predDC = dc;

    for (k = 1; k < 64; k++) {
        ssss = __THPHuffDecodeTab(info, Vachuff.value);
        nbits = ssss & 15;
        tmp = ssss >> 4;

        if (nbits) {
            k += tmp;
#ifdef __MWERKS__ // clang-format off
            asm {
                lwz      tmp,info->cnt;
                subfic   cnt33,tmp,33;
                lwz      cnt1,info->currByte;
                subf. cb, cnt33, nbits;
                subi     ssss,tmp,1;
                bgt      _notEnoughBits;
                add      v,tmp,nbits;
                slw      tmp,cnt1,ssss;
                stw      v,info->cnt;
                subfic   v,nbits,32;
                srw      tmp,tmp,v;
            }
#endif // clang-format on

#ifdef __MWERKS__ // clang-format off
            asm {
                b _Done;
            _notEnoughBits:
                lwz tmp, info->file;
                slw v, cnt1, ssss;
                lwzu cnt1, 4(tmp);
                addi cb, cb, 1;
                stw cnt1, info->currByte;
                srw cnt1, cnt1, cnt33;
                stw tmp, info->file;
                add v, cnt1, v;
                stw cb, info->cnt;
                subfic cb, nbits, 32;
                srw tmp, v, cb;
            _Done:
            }
#endif // clang-format on

            if (__cntlzw((u32) tmp) > 32 - nbits) {
                tmp += ((0xFFFFFFFF << nbits) + 1);
            }

            block[__THPJpegNaturalOrder[k]] = (s16) tmp;
        }

        else {
            if (tmp != 15) {
                break;
            }
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

struct THPLCSizeEntry {
    u32 id;
    u32 size;
};

/// THPInit initializes the adjacent LC work objects as one layout.
struct THPInitWork {
    struct THPLCWork cache;
    u8* work672[3];
};

static struct THPLCSizeEntry __THPLCSizeTableA[5] = {
    { 0, 0x1000 }, { 1, 0x400 }, { 2, 0x400 }, { 3, 0x400 }, { 4, 0x400 },
};

static struct THPLCSizeEntry __THPLCSizeTableB[9] = {
    { 0, 0x1000 }, { 1, 0x200 }, { 2, 0x200 }, { 3, 0x200 }, { 4, 0x200 },
    { 5, 0x200 },  { 6, 0x200 }, { 7, 0x200 }, { 8, 0x200 },
};

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
#endif
}
// clang-format on

#ifdef __MWERKS__
#pragma function_align 4
#endif

void THPInit(void)
{
    u8* base;
    int i;
    int j;
    struct THPInitWork* work = (struct THPInitWork*) &__THPLC;

    if ((PPCMfhid2() & 0x10000000) == 0) {
        DCInvalidateRange((void*) 0xE0000000, 0x4000);
        LCEnable();
    }

    base = (u8*) 0xE0000000;
    for (j = 0; j < 2; j++) {
        for (i = 0; i < 5; i++) {
            work->cache.offsets512[j][i] = base;
            base += __THPLCSizeTableA[i].size;
        }
    }

    base = (u8*) 0xE0000000;
    for (j = 0; j < 2; j++) {
        for (i = 0; i < 9; i++) {
            work->cache.offsets672[j][i] = base;
            base += __THPLCSizeTableB[i].size;
        }
    }

    base = (u8*) 0xE0000000;
    work->cache.work512[0] = base;
    base += 0x2000;
    work->cache.work512[1] = base;
    base += 0x800;
    work->cache.work512[2] = base;

    base = (u8*) 0xE0000000;
    work->work672[0] = base;
    base += 0x2800;
    work->work672[1] = base;
    base += 0xA00;
    work->work672[2] = base;

    OSInitFastCast();
}

u8* __THPLCWork672[3];
