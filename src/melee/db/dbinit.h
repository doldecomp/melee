#ifndef MELEE_DB_DBINIT_H
#define MELEE_DB_DBINIT_H

#include <melee/ft/kinds/ftCommon/forward.h>

#include <dat_macros.h>

struct db_Setup_commonData {
    /// Bonus names, bounded by #fn_80228E54.
    /* +0 */ char** bonus_names DAT_COUNT(0xD7);
    /// Common motion-state names (#fn_UpdateAnimationInfo).
    /* +4 */ char** motionstate_names DAT_COUNT(ftCo_MS_Count);
    /// Common submotion names (#fn_UpdateAnimationInfo).
    /* +8 */ char** submotion_names DAT_COUNT(ftCo_SM_Count);
};

#endif
