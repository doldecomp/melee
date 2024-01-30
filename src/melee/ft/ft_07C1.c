#include <platform.h>
#include "it/forward.h"

#include "ft/ft_07C1.h"

#include "ft/types.h"
#include "ftCommon/ftCo_HammerWait.h"
#include "it/it_26B1.h"

#include <placeholder.h>
#include <baselib/gobj.h>

void ft_8007C224(HSD_GObj* gobj);

void ft_8007C114(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->item_gobj != NULL) {
        switch (itGetKind(fp->item_gobj)) {
        case It_Kind_Hammer:
            ftCo_800C555C(gobj);
            break;
        }
    }
    fp->x2219_b4 = 0;
}

void ft_8007C17C(HSD_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ft_8007C224(HSD_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ft_8007C2E0(void)
{
    NOT_IMPLEMENTED;
}

void ft_8007C4BC(HSD_GObj* gobj)
{
    NOT_IMPLEMENTED;
}
