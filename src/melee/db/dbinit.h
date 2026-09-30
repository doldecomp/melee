#ifndef MELEE_DB_DBINIT_H
#define MELEE_DB_DBINIT_H

#include <dat_macros.h>

struct db_Setup_commonData {
    char** bonus_names DAT_EXTENT;
    char** motionstate_names DAT_EXTENT;
    char** submotion_names DAT_EXTENT;
};

#endif
