#ifndef SYSDOLPHIN_DEBCONSOLE_MAIN_H
#define SYSDOLPHIN_DEBCONSOLE_MAIN_H

#include <placeholder.h>

#include <sysdolphin/baselib/forward.h>

#include <dolphin/os/OSContext.h>

/* 394950 */ void hsd_80394950(OSContext*);
/* 394A48 */ void Exception_ReportStackTrace(OSContext*, int);
/* 394B18 */ void Exception_ReportCodeline(u16, int, int, OSContext*);
/* 394DF4 */ void fn_80394DF4(void*);
/* 394F48 */ void hsd_80394F48(void*);
/* 395550 */ s32 hsd_80395550(void*);
/* 395644 */ void hsd_80395644(void);
/* 3956D8 */ s32 hsd_803956D8(void*);
/* 3957C0 */ void hsd_803957C0(void* input);
/* 395970 */ s32 hsd_80395970(void);
/* 395A78 */ bool hsd_80395A78(void);
/* 395D88 */ bool hsd_80395D88(void*);
/* 396130 */ void hsd_80396130(void);
/* 396188 */ void hsd_80396188(void);
/* 3962A8 */ s32 hsd_803962A8(void*);
/* 3966A0 */ s32 hsd_803966A0(void*);
/* 396868 */ UNK_RET hsd_80396868(UNK_PARAMS);
/* 396884 */ void hsd_80396884(void);
/* 396A20 */ s32 hsd_80396A20(void*);
/* 396C78 */ s32 hsd_80396C78(void*);
/* 396E40 */ void hsd_80396E40(int);
/* 3970D8 */ void fn_803970D8(int);
/* 3970DC */ void fn_803970DC(int);
/* 3970E0 */ void fn_803970E0(int);
/* 3970E4 */ void fn_803970E4(int);
/* 3970E8 */ void fn_803970E8(int);
/* 3970EC */ void fn_803970EC(int);
/* 3970F0 */ void fn_803970F0(int);
/* 3970F4 */ void fn_803970F4(int);
/* 3970F8 */ void fn_803970F8(int);
/* 3970FC */ void fn_803970FC(int);
/* 397100 */ void fn_80397100(int);
/* 397104 */ void fn_80397104(int);
/* 397108 */ void fn_80397108(int);
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

#endif
