#include "lbfile.h"
#include "lbmthp.h"

#include <sysdolphin/baselib/memory.h>
#include <sysdolphin/baselib/sobjlib.h>
#include <sysdolphin/baselib/tobj.h>

struct lbl_804335B8_t {
    /* 0x00 */ GXTexObj tex0; /* 0x00-0x20 (size 0x20) */
    /* 0x20 */ void* x20;     /* image ptr for tex0 */
    /* 0x24 */ GXTexObj tex1; /* 0x24-0x44 (size 0x20) */
    /* 0x44 */ void* x44;     /* image ptr for tex1 */
    /* 0x48 */ GXTexObj tex2; /* 0x48-0x68 (size 0x20) */
    /* 0x68 */ void* x68;     /* image ptr for tex2 */
    /* 0x6C */ u16 x6C;       /* width */
    /* 0x6E */ u16 x6E;       /* height */
    /* 0x70 */ struct HSD_ImageDesc x70;
    /* 0x88 */ struct HSD_SObjDesc x88;
    /* 0x90 */ struct HSD_SObj* x90;
    /* 0x94 */ u32 unk94;
    /* 0x98 */ u32 unk98;
    /* 0x9C */ char pad_9C[0xA0 - 0x9C];
}; /* size = 0xA0 */
STATIC_ASSERT(sizeof(struct lbl_804335B8_t) == 0xA0);

extern struct lbl_804333E0_t Movieplayer;

static struct lbl_804335B8_t lbl_804335B8;

void* lbMthp8001F890(HSD_GObj* gobj)
{
    lbl_804335B8.x70.image_ptr = NULL;
    lbl_804335B8.x70.width = lbl_804335B8.x6C;
    lbl_804335B8.x70.height = lbl_804335B8.x6E;
    lbl_804335B8.x70.format = GX_TF_RGBA8;
    lbl_804335B8.x70.mipmap = 0;
    lbl_804335B8.x70.minLOD = lbl_804335B8.x70.maxLOD = 0.0F;
    lbl_804335B8.x88.image = &lbl_804335B8.x70;
    lbl_804335B8.x88.tlut = NULL;
    lbl_804335B8.x90 =
        HSD_SObjLib_803A477C(gobj, &lbl_804335B8.x88, 0, 0, 0x80, 0);
    lbl_804335B8.x90->x40 |= 0x10;
    return lbl_804335B8.x90;
}

void lbMthp8001F928(HSD_GObj* gobj, int arg1)
{
    u16* pWidth = &lbl_804335B8.x6C;
    u16* pHeight = &lbl_804335B8.x6E;

    /* First texture - full size */
    GXInitTexObj(&lbl_804335B8.tex0, lbl_804335B8.x20, lbl_804335B8.x6C,
                 lbl_804335B8.x6E, 1, 0, 0, 0);
    GXInitTexObjLOD(&lbl_804335B8.tex0, 0, 0, 0.0F, 0.0F, 0.0F, 0, 0, 0);
    GXLoadTexObj(&lbl_804335B8.tex0, 0);

    /* Second texture - half size */
    GXInitTexObj(&lbl_804335B8.tex1, lbl_804335B8.x44, (u16) (*pWidth >> 1),
                 (u16) (*pHeight >> 1), 1, 0, 0, 0);
    GXInitTexObjLOD(&lbl_804335B8.tex1, 0, 0, 0.0F, 0.0F, 0.0F, 0, 0, 0);
    GXLoadTexObj(&lbl_804335B8.tex1, 1);

    /* Third texture - half size */
    GXInitTexObj(&lbl_804335B8.tex2, lbl_804335B8.x68, (u16) (*pWidth >> 1),
                 (u16) (*pHeight >> 1), 1, 0, 0, 0);
    GXInitTexObjLOD(&lbl_804335B8.tex2, 0, 0, 0.0F, 0.0F, 0.0F, 0, 0, 0);
    GXLoadTexObj(&lbl_804335B8.tex2, 2);

    HSD_SObjLib_803A49E0(gobj, arg1);
}

void lbMthp8001FAA0(const char* filename, int width, int height)
{
    struct {
        u16 w;
        u16 h;
        u8 pad[0x18];
    } header;
    s32 output;
    s32 yuv_size;
    s32 uv_size;
    void* context;
    void* decode_buf;
    s32 decoded;

    lbl_804335B8.x6C = (u16) width;
    lbl_804335B8.x6E = (u16) height;
    THPInit();
    lbFile_80016760(filename, &lbl_804335B8.unk94, &lbl_804335B8.unk98);
    yuv_size = lbl_804335B8.x6C * lbl_804335B8.x6E;
    lbl_804335B8.x20 = HSD_MemAlloc(yuv_size);
    DCInvalidateRange(lbl_804335B8.x20, (u32) yuv_size);
    uv_size = (s32) (lbl_804335B8.x6C * lbl_804335B8.x6E) >> 2;
    lbl_804335B8.x44 = HSD_MemAlloc(uv_size);
    DCInvalidateRange(lbl_804335B8.x44, (u32) uv_size);
    lbl_804335B8.x68 = HSD_MemAlloc(uv_size);
    DCInvalidateRange(lbl_804335B8.x68, (u32) uv_size);
    context = HSD_MemAlloc(0xC);
    memset(&header, 0, 0x1CU);
    header.w = width;
    header.h = height;
    THPDec_8032F8D4(lbl_804335B8.unk94, context);
    decode_buf = HSD_MemAlloc(THPDec_8032FD40(context, header.h));
    decoded = THPVideoDecode(&header, &output, decode_buf,
                             (void*) lbl_804335B8.unk94, context);
    if ((u16) lbl_804335B8.x6C == 0x280) {
        THPDec_80331340(decoded, lbl_804335B8.x20, lbl_804335B8.x44,
                        lbl_804335B8.x68);
    } else {
        THPDec_803313D0(decoded, lbl_804335B8.x20, lbl_804335B8.x44,
                        lbl_804335B8.x68, lbl_804335B8.x6C);
    }
    HSD_Free(context);
    HSD_Free(decode_buf);
}
