#include "vi1101.static.h"

#include "vi.h"

/// #un_8031F294

/// #fn_8031F548

/// #fn_8031F56C

/// #fn_8031F600

/// #un_8031F714_OnEnter

void un_8031F960_OnFrame(void)
{
    vi_8031CAAC();
}

void un_8031F980(int arg0, int arg1)
{
    M2C_FIELD(&un_804D7004, u8*, 0) = arg0;
    M2C_FIELD(&un_804D7004, u8*, 1) = arg1;
}
