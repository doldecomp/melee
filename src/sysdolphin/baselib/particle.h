#ifndef GALE01_391580
#define GALE01_391580

#include <platform.h>
#include <placeholder.h>

#include "baselib/forward.h"

#include "baselib/jobj.h"

/* 391580 */ void DrawRectangle(float x, float y, float w, float h,
                                GXColor* color);
/* 391664 */ void DrawASCII(int chr, float x, float y, GXColor* color);
/* 391A04 */ void hsd_80391A04(float scale_x, float scale_y, int line_width);
/* 391AC8 */ UNK_RET hsd_80391AC8(UNK_PARAMS);
/* 391E18 */ UNK_RET hsd_80391E18(UNK_PARAMS);
/* 391F28 */ UNK_RET hsd_80391F28(UNK_PARAMS);
/* 392194 */ UNK_RET hsd_80392194(UNK_PARAMS);
/* 3921B8 */ UNK_RET hsd_803921B8(UNK_PARAMS);
/* 3922FC */ UNK_RET hsd_803922FC(UNK_PARAMS);
/* 392474 */ UNK_RET hsd_80392474(UNK_PARAMS);
/* 392480 */ UNK_RET fn_80392480(UNK_PARAMS);
/* 392528 */ void hsd_80392528(Event);
/* 39254C */ UNK_RET hsd_8039254C(UNK_PARAMS);
/* 392934 */ UNK_RET fn_80392934(UNK_PARAMS);
/* 392A08 */ UNK_RET fn_80392A08(UNK_PARAMS);
/* 392A3C */ UNK_RET fn_80392A3C(UNK_PARAMS);
/* 392CCC */ s32 fn_80392CCC(s32);
/* 392CD8 */ UNK_RET fn_80392CD8(UNK_PARAMS);
/* 392E2C */ UNK_RET fn_80392E2C(UNK_PARAMS);
/* 392E80 */ void hsd_80392E80(void);
/* 3931A4 */ bool hsd_803931A4(s32);
/* 3932D0 */ UNK_RET fn_803932D0(UNK_PARAMS);
/* 393328 */ UNK_RET hsd_80393328(UNK_PARAMS);
/* 393440 */ UNK_RET hsd_80393440(UNK_PARAMS);
/* 393840 */ UNK_RET hsd_80393840(UNK_PARAMS);
/* 393844 */ UNK_RET hsd_80393844(UNK_PARAMS);
/* 393A04 */ bool hsd_80393A04(void);
/* 393A54 */ void hsd_80393A54(int);
/* 393A5C */ int hsd_80393A5C(char*, int, int);
/* 393C14 */ UNK_RET fn_80393C14(UNK_PARAMS);
/* 393D2C */ UNK_RET hsd_80393D2C(UNK_PARAMS);
/* 393DA0 */ void hsd_80393DA0(void*, int);
/* 393E34 */ UNK_RET hsd_80393E34(UNK_PARAMS);
/* 393E68 */ UNK_RET hsd_80393E68(UNK_PARAMS);
/* 393EF4 */ UNK_RET hsd_80393EF4(UNK_PARAMS);
/* 394068 */ UNK_RET hsd_80394068(UNK_PARAMS);
/* 394128 */ UNK_RET hsd_80394128(UNK_PARAMS);
/* 3941E8 */ UNK_RET hsd_803941E8(UNK_PARAMS);
/* 394314 */ UNK_RET hsd_80394314(UNK_PARAMS);
/* 394434 */ UNK_RET hsd_80394434(UNK_PARAMS);
/* 394544 */ UNK_RET hsd_80394544(UNK_PARAMS);
/* 394668 */ UNK_RET hsd_80394668(UNK_PARAMS);
/* 394950 */ UNK_RET hsd_80394950(UNK_PARAMS);
/* 394A48 */ void Exception_ReportStackTrace(OSContext*, int);
/* 394B18 */ void Exception_ReportCodeline(u16, int, int, OSContext*);
/* 394DF4 */ UNK_RET fn_80394DF4(UNK_PARAMS);
/* 394E8C */ UNK_RET hsd_80394E8C(UNK_PARAMS);
/* 394F48 */ UNK_RET hsd_80394F48(UNK_PARAMS);
/* 395550 */ UNK_RET hsd_80395550(UNK_PARAMS);
/* 395644 */ UNK_RET hsd_80395644(UNK_PARAMS);
/* 3956D8 */ UNK_RET hsd_803956D8(UNK_PARAMS);
/* 3957C0 */ UNK_RET hsd_803957C0(UNK_PARAMS);
/* 395970 */ UNK_RET hsd_80395970(UNK_PARAMS);
/* 395A78 */ UNK_RET hsd_80395A78(UNK_PARAMS);
/* 395D88 */ UNK_RET hsd_80395D88(UNK_PARAMS);
/* 396130 */ UNK_RET hsd_80396130(UNK_PARAMS);
/* 396188 */ UNK_RET hsd_80396188(UNK_PARAMS);
/* 3962A8 */ UNK_RET hsd_803962A8(UNK_PARAMS);
/* 3966A0 */ UNK_RET hsd_803966A0(UNK_PARAMS);
/* 396868 */ UNK_RET hsd_80396868(UNK_PARAMS);
/* 396884 */ UNK_RET hsd_80396884(UNK_PARAMS);
/* 396A20 */ UNK_RET hsd_80396A20(UNK_PARAMS);
/* 396C78 */ UNK_RET hsd_80396C78(UNK_PARAMS);
/* 396E40 */ UNK_RET hsd_80396E40(UNK_PARAMS);
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
/* 397110 */ UNK_RET hsd_80397110(UNK_PARAMS);
/* 397374 */ UNK_RET fn_80397374(UNK_PARAMS);
/* 397520 */ UNK_RET hsd_80397520(UNK_PARAMS);
/* 3975D4 */ UNK_RET hsd_803975D4(UNK_PARAMS);
/* 397814 */ UNK_RET fn_80397814(UNK_PARAMS);
/* 397DA4 */ void hsd_80397DA4(OSContext*);
/* 397DF4 */ void Exception_StoreDebugLevel(int);
/* 397DFC */ void hsd_80397DFC(u32 arg0);
/* 397E0C */ UNK_RET baselib_mfspr(UNK_PARAMS);
/* 3982E4 */ UNK_RET fn_803982E4(UNK_PARAMS);
/* 398310 */ HSD_GObj* hsd_80398310(s32, s32, s32, s32);
/* 3983A4 */ UNK_RET hsd_803983A4(UNK_PARAMS);
/* 3984F4 */ void psInitDataBankLoad(int bank, int* cmdBank, int* texBank,
                                     u32* ref, int* formBank);
/* 398614 */ void psInitDataBankLocate(HSD_Archive* cmdBank,
                                       HSD_Archive* texBank, int* formBank);
/* 3989A0 */ void psInitDataBankRelocate(int* cmdBank, int* texBank,
                                         int* formBank, int* newCmdBank,
                                         int* newTexBank, int* newFormBank);
/* 398A08 */ void hsd_80398A08(u32);
/* 398C04 */ UNK_RET hsd_80398C04(UNK_PARAMS);
/* 398F0C */ UNK_RET hsd_80398F0C(UNK_PARAMS);
/* 398F8C */ UNK_RET hsd_80398F8C(UNK_PARAMS);
/* 3991D8 */ UNK_RET hsd_803991D8(UNK_PARAMS);
/* 39930C */ UNK_RET hsd_8039930C(UNK_PARAMS);
/* 39CEAC */ void hsd_8039CEAC(u32);
/* 39CF4C */ UNK_RET hsd_8039CF4C(UNK_PARAMS);
/* 39D048 */ UNK_RET hsd_8039D048(UNK_PARAMS);
/* 39D0A0 */ UNK_RET hsd_8039D0A0(UNK_PARAMS);
/* 39D1E4 */ void hsd_8039D1E4(UNK_T arg0, int arg1);
/* 39D1EC */ UNK_RET hsd_8039D1EC(UNK_PARAMS);
/* 39D214 */ UNK_RET hsd_8039D214(UNK_PARAMS);
/* 39D354 */ void hsd_8039D354(u32);
/* 39D3AC */ UNK_RET hsd_8039D3AC(UNK_PARAMS);
/* 39D4DC */ void hsd_8039D4DC(HSD_Generator*);
/* 39D580 */ UNK_RET hsd_8039D580(UNK_PARAMS);
/* 39D5DC */ void hsd_8039D5DC(HSD_JObj*);
/* 39D688 */ void hsd_8039D688(HSD_JObj*, f32**, s32);
/* 39D71C */ UNK_RET hsd_8039D71C(UNK_PARAMS);
/* 39D9C8 */ UNK_RET hsd_8039D9C8(UNK_PARAMS);
/* 39DAD4 */ UNK_RET hsd_8039DAD4(UNK_PARAMS);
/* 39EE24 */ void hsd_8039EE24(u32);
/* 39EFAC */ HSD_Generator* hsd_8039EFAC(s32, s32, s32, HSD_JObj*);
/* 39F05C */ HSD_Generator* hsd_8039F05C(s8, s8, s32);
/* 39F6CC */ void hsd_8039F6CC(s32, s32, s32, HSD_JObj*);
/* 4D0F60 */ extern HSD_ObjAllocData hsd_804D0F60;
/* 4D0F90 */ extern HSD_ObjAllocData hsd_804D0F90;
/* 4D78D0 */ extern u32 hsd_804D78D0;
/* 4D78D4 */ extern u32 hsd_804D78D4;
/* 4D78D8 */ extern u16 hsd_804D78D8;
/* 4D78DE */ extern u16 hsd_804D78DE;
/* 4D78E0 */ extern u16 hsd_804D78E0;
/* 4D78E8 */ extern u32 hsd_804D78E8;
/* 4D78F0 */ extern u32 hsd_804D78F0;

#endif
