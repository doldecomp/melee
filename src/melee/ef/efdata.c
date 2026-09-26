#include "efdata.h"

/* 458EB0 */ HSD_ObjAllocData efLib_AllocData;

// .sbss (mwcc allocates .sbss in reverse definition order ? sometimes...)
/* 4D64F0 */ s32 efLib_AnimCount;
/* 4D64EC */ u32 efLib_EffectCount;
/* 4D64E8 */ u32 efLib_LoadKind;
