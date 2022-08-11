#ifndef SYSDOLPHIN_BASELIB___BASELIB_H
#define SYSDOLPHIN_BASELIB___BASELIB_H

#include <dolphin/types.h>

#pragma region baselib_unknown_002
extern u16 lbl_804D78D8;
extern u16 lbl_804D78DE;
extern u8 lbl_804D0B50[0x104];
extern u8 lbl_804D0C54[0x104];
#pragma endregion

#pragma region psdisptev
void psSetupTevCommon(void);
void psSetupTevInvalidState();
void psSetupTev(unk_t);
#pragma endregion


#endif