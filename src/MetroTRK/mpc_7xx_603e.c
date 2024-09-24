#include "mpc_7xx_603e.h"

static int const target_cpu_minor_type = 84;

/// #TRKSaveExtended1Block

/// #TRKRestoreExtended1Block

int TRKTargetCPUMinorType(void)
{
    return target_cpu_minor_type;
}
