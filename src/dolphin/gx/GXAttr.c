#include <dolphin/gx/GXAttr.h>

extern void __GXXfVtxSpecs();
extern void GXSetVtxDesc(u32, s32);

#pragma region __GXSetVCD
extern u8 lbl_804D5BB0[4];
extern u8 lbl_804D5BB4[4];
extern u8 lbl_804D5BB8[4];

extern void __GXSetVCD();
#pragma endregion

extern void GXClearVtxDesc();
extern void GXSetVtxAttrFmt(s8 vertex_format, s32, s32, s32, s8);
extern void __GXSetVAT();
extern void GXSetArray(s32, s32, s8);
extern void GXInvalidateVtxCache();
void GXSetTexCoordGen2(u32, s32, u32, s32, s32, s32);