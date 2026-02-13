#ifndef GALE01_391580
#define GALE01_391580

#include <placeholder.h>
#include <platform.h>

#include "baselib/forward.h"

#include "baselib/jobj.h"

struct hsd_804D0F60_t {
    HSD_ObjAllocData alloc_data;
    UNK_T pad;
};

/* 391580 */ void DrawRectangle(float x, float y, float w, float h,
                                GXColor* color);
/* 391664 */ f32 DrawASCII(int chr, float x, float y, GXColor* color);
/* 391A04 */ void hsd_80391A04(float scale_x, float scale_y, int line_width);
/* 391AC8 */ s32 hsd_80391AC8(char*, GXColor*, f32, f32);
/* 391E18 */ void hsd_80391E18(u8* list, f32 x1, f32 y1, f32 x2, f32 y2);
/* 391F28 */ void hsd_80391F28(GXColor*, f32, f32, f32, f32, f32);
/* 392194 */ void hsd_80392194(u8* dst, s32 flags, void* unused1,
                               void* unused2, u8* src);
/* 3921B8 */ void hsd_803921B8(void*, s32, s32, s32, s32, s32, s32, void*);
/* 3922FC */ void hsd_803922FC(void*, s32, s32, s32, s32, s32, s32, s32,
                               void*);
/* 392474 */ UNK_RET hsd_80392474(UNK_PARAMS);
/* 392480 */ HSD_SList* fn_80392480(Event event, int priority);
/* 392528 */ void hsd_80392528(Event);
/* 39254C */ void hsd_8039254C(void);
/* 392934 */ UNK_RET fn_80392934(UNK_PARAMS);
/* 392A08 */ UNK_RET fn_80392A08(int, int, int);
/* 392A3C */ void* fn_80392A3C(void);
/* 392CCC */ s32 fn_80392CCC(s32);
/* 392CD8 */ u8 fn_80392CD8(char*);
/* 392E2C */ void fn_80392E2C(s32);
/* 392E80 */ void hsd_80392E80(void);
/* 3931A4 */ bool hsd_803931A4(s32);
/* 3932D0 */ void fn_803932D0(s32, u32, s32);
/* 393328 */ s32 hsd_80393328(void);
/* 393440 */ void hsd_80393440(void*, void*);
/* 393840 */ void hsd_80393840(void);
/* 393844 */ void hsd_80393844(void);
/* 393A04 */ bool hsd_80393A04(void);
/* 393A54 */ void hsd_80393A54(int);
/* 393A5C */ int hsd_80393A5C(char*, int, int);
/* 393C14 */ void fn_80393C14(const u8* buf, size_t);
/* 393D2C */ s32 hsd_80393D2C(s32);
/* 393DA0 */ void hsd_80393DA0(u8*, size_t);
/* 393E34 */ void hsd_80393E34(s32* col_out, s32* row_out);
/* 393E68 */ void hsd_80393E68(u32, u32);
/* 393EF4 */ void hsd_80393EF4(int, int);
/* 394068 */ u8 hsd_80394068(void);
/* 394128 */ u8 hsd_80394128(s32, s32);
/* 3941E8 */ s32 hsd_803941E8(void*, void*);
/* 394314 */ void hsd_80394314(void);
/* 394434 */ void hsd_80394434(void*);
/* 394544 */ void hsd_80394544(s32, s32, u32, u32, s32, s32, s32, s32, s32,
                               s32, s32, void*);
/* 394668 */ void hsd_80394668(void);
/* 394950 */ void hsd_80394950(OSContext*);
/* 394A48 */ void Exception_ReportStackTrace(OSContext*, int);
/* 394B18 */ void Exception_ReportCodeline(u16, int, int, OSContext*);
/* 394DF4 */ void fn_80394DF4(void*);
/* 394E8C */ void hsd_80394E8C(void*);
/* 394F48 */ void hsd_80394F48(void*);
/* 395550 */ s32 hsd_80395550(void*);
/* 395644 */ void hsd_80395644(void);
/* 3956D8 */ s32 hsd_803956D8(void*);
/* 3957C0 */ void hsd_803957C0(u8 input);
/* 395970 */ s32 hsd_80395970(void);
/* 395A78 */ s32 hsd_80395A78(void);
/* 395D88 */ s32 hsd_80395D88(void*);
/* 396130 */ void hsd_80396130(void);
/* 396188 */ void hsd_80396188(void);
/* 3962A8 */ s32 hsd_803962A8(void*);
/* 3966A0 */ s32 hsd_803966A0(void*);
/* 396868 */ UNK_RET hsd_80396868(UNK_PARAMS);
/* 396884 */ void hsd_80396884(void);
/* 396A20 */ s32 hsd_80396A20(void*);
/* 396C78 */ s32 hsd_80396C78(void*);
/* 396E40 */ void hsd_80396E40(s32);
/* 3970D8 */ UNK_RET fn_803970D8(UNK_PARAMS);
/* 3970DC */ UNK_RET fn_803970DC(UNK_PARAMS);
/* 3970E0 */ UNK_RET fn_803970E0(UNK_PARAMS);
/* 3970E4 */ UNK_RET fn_803970E4(UNK_PARAMS);
/* 3970E8 */ UNK_RET fn_803970E8(UNK_PARAMS);
/* 3970EC */ UNK_RET fn_803970EC(UNK_PARAMS);
/* 3970F0 */ UNK_RET fn_803970F0(UNK_PARAMS);
/* 3970F4 */ UNK_RET fn_803970F4(UNK_PARAMS);
/* 3970F8 */ UNK_RET fn_803970F8(UNK_PARAMS);
/* 3970FC */ UNK_RET fn_803970FC(UNK_PARAMS);
/* 397100 */ UNK_RET fn_80397100(UNK_PARAMS);
/* 397104 */ UNK_RET fn_80397104(UNK_PARAMS);
/* 397108 */ UNK_RET fn_80397108(UNK_PARAMS);
/* 39710C */ UNK_RET fn_8039710C(UNK_PARAMS);
/* 397110 */ void hsd_80397110(void);
/* 397374 */ s32 fn_80397374(void*);
/* 397520 */ void hsd_80397520(void*);
/* 3975D4 */ void hsd_803975D4(void);
/* 397814 */ void* fn_80397814(void*);
/* 397DA4 */ void hsd_80397DA4(OSContext*);
/* 397DF4 */ void Exception_StoreDebugLevel(int);
/* 397DFC */ void hsd_80397DFC(u32 size);
/* 397E0C */ int baselib_mfspr(int);
/* 3982E4 */ void fn_803982E4(HSD_GObj*, int);
/* 398310 */ HSD_GObj* hsd_80398310(u16, u8, u8, u32);
/* 3983A4 */ void hsd_803983A4(HSD_Generator*);
/* 3984F4 */ void psInitDataBankLoad(int bank, int* cmdBank, int* texBank,
                                     u32* ref, int* formBank);
/* 398614 */ void psInitDataBankLocate(HSD_Archive* cmdBank,
                                       HSD_Archive* texBank, int* formBank);
/* 3989A0 */ void psInitDataBankRelocate(int* cmdBank, int* texBank,
                                         int* formBank, int* newCmdBank,
                                         int* newTexBank, int* newFormBank);
/* 398A08 */ void hsd_80398A08(u32);
/* 398C04 */ HSD_Particle* hsd_80398C04(HSD_Particle**, int, int, u32, u16,
                                        u8*, int, int, f32, f32, f32, f32, f32,
                                        f32, f32, f32, f32, HSD_Generator*,
                                        int);
/* 398F0C */ void hsd_80398F0C(s32, s32, s32, u16, s32, s32, s32, s32, f32,
                               f32, f32, f32, f32, f32, f32, f32, f32);
/* 398F8C */ void hsd_80398F8C(HSD_Particle*, f32);
/* 3991D8 */ s32 hsd_803991D8(HSD_Generator*, HSD_JObj*, f32, f32);
/* 39930C */ void* hsd_8039930C(void*, void*);
/* 39CEAC */ void hsd_8039CEAC(u32);
/* 39CF4C */ void hsd_8039CF4C(s32, HSD_JObj*);
/* 39D048 */ void hsd_8039D048(void* particle);
/* 39D0A0 */ void hsd_8039D0A0(HSD_Generator*);
/* 39D1E4 */ void hsd_8039D1E4(HSD_Generator*, void*);
/* 39D1EC */ u16 hsd_8039D1EC(void);
/* 39D214 */ void hsd_8039D214(HSD_Generator*);
/* 39D354 */ void hsd_8039D354(u32);
/* 39D3AC */ HSD_Generator* hsd_8039D3AC(HSD_Generator*, HSD_Generator*);
/* 39D4DC */ void hsd_8039D4DC(HSD_Generator*);
/* 39D580 */ void hsd_8039D580(HSD_JObj*);
/* 39D5DC */ void hsd_8039D5DC(HSD_JObj*);
/* 39D688 */ void hsd_8039D688(HSD_JObj*, f32**, s32);
/* 39D71C */ void hsd_8039D71C(HSD_Generator*);
/* 39D9C8 */ HSD_Generator* hsd_8039D9C8(void);
/* 39DAD4 */ f32 hsd_8039DAD4(HSD_Generator*);
/* 39EE24 */ void hsd_8039EE24(u32);
/* 39EFAC */ HSD_Generator* hsd_8039EFAC(s32, s32, s32, HSD_JObj*);
/* 39F05C */ HSD_Generator* hsd_8039F05C(s8, s32, s32);
/* 39F6CC */ HSD_Generator* hsd_8039F6CC(s32, s32, s32, HSD_JObj*);

/* 4D0F60 */ extern struct hsd_804D0F60_t hsd_804D0F60;
/* 4D0F90 */ extern struct hsd_804D0F60_t hsd_804D0F90;

#endif
