#include <platform.h>

/* 4D7950 */ static s32 prevTev[2];

/// #psSetupTevCommon

void psSetupTevInvalidState(void)
{
    prevTev[0] = -1;
}

/// #psSetupTev
