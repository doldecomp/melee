#include "ftcpuattack.h"

#include "ftcmdscript.h"

#include <melee/ft/types.h>
#include <melee/ft/chara/ftCommon/ftCo_0A01.h>

/// #ftCo_800B4AB0

/// #ftCo_800B52AC

/// #ftCo_800B5AB0

/// #ftCo_800B6208

/// #ftCo_800B630C

/// #ftCo_800B63D8

/// #ftCo_800B658C

/// #ftCo_800B683C

/// #ftCo_800B7180

/// #ftCo_800B732C

/// #ftCo_800B7638

/// #ftCo_800B77E8

/// #ftCo_800B885C

/// #ftCo_800B89CC

/// #ftCo_800B8A9C

/// #ftCo_800B9020

/// #ftCo_800B920C

void ftCo_800B92D4(Fighter* fp)
{
    PAD_STACK(4 * 4);
    if (fp->x1A88.x44 == NULL) {
        fp->x1A88.x44 = NULL;
        fp->x1A88.x18 = fp->x1A88.x1C;
        ftCo_800A0C8C(fp);
    } else {
        ftCo_800B46B8(fp, 0x94, 0x7F);
        ftCo_800B463C(fp, 0x7F);
    }
}

/// #ftCo_800B9340

/// #ftCo_800B9504

/// #ftCo_800B9704

/// #ftCo_800B9790

/// #ftCo_800B98C8

/// #ftCo_800B9A04

/// #ftCo_800B9CBC

bool ftCo_800B9F6C(Fighter* fp)
{
    if (fp->motion_id == ftCo_MS_GuardOn || fp->motion_id == ftCo_MS_Guard) {
        return true;
    }
    return false;
}

/// #ftCo_800B9F90

/// #ftCo_800BA080

/// #ftCo_800BA160

/// #ftCo_800BA224

/// #ftCo_800BA2E8

/// #ftCo_800BA674

/// #ftCo_800BA9A0

/// #ftCo_800BB104

/// #ftCo_800BB220

/// #ftCo_800BB768

/// #ftCo_800BB9B4
