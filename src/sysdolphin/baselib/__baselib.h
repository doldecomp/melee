#ifndef SYSDOLPHIN_BASELIB___BASELIB_H
#define SYSDOLPHIN_BASELIB___BASELIB_H

#include <platform.h>
typedef struct {
    u8 x0[0x828];
} __baselib_UnkType001;

typedef struct {
    u8 x0[0x80 * 0x24];
} __baselib_UnkType002;

typedef struct {
    u8 x0[0x300];
} __baselib_UnkType003;

#pragma region baselib_shared_data_001

/* 004CDD18 */ extern u8 lbl_804D1138[0x10];
/* 004CDD28 */ extern u32 lbl_804D1148[0x80][0x9];
/* 004CEF28 */ extern __baselib_UnkType003 lbl_804D2348;
/* 004CF228 */ extern __baselib_UnkType001 lbl_804D2648;
/* 004CFA50 */ extern u8 lbl_804D2E70[2084];

#pragma endregion

#pragma region baselib_shared_data_002

/* 004D4588 */ extern unk_t lbl_804D79A8;
/* 004D4584 */ extern unk_t lbl_804D79A4;
/* 004D4580 */ extern unk_t lbl_804D79A0;

#pragma endregion

#pragma region baselib_unknown_002
extern u8 lbl_804D0B50[0x104];
extern u8 lbl_804D0C54[0x104];
#pragma endregion

#pragma region psdisptev
void psSetupTevCommon(void);
void psSetupTevInvalidState(void);
void psSetupTev(unk_t);
#pragma endregion

#endif
