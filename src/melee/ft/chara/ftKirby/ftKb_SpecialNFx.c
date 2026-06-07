#include "ftKb_Init.h"

#include "ft/inlines.h"
#include "lb/lb_00B0.h"

extern f32 ftKb_Init_804D9450;
extern f32 ftKb_Init_804D9454;
extern f32 ftKb_Init_804D9458;

void ftKb_SpecialNFx_800FDC00(Fighter_GObj* gobj, Vec3* vec)
{
    if (gobj != NULL) {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp != NULL) {
            Vec3 offset;
            offset.x = ftKb_Init_804D9450;
            offset.y = ftKb_Init_804D9454;
            offset.z = ftKb_Init_804D9458;
            lb_8000B1CC(fp->parts[44].joint, &offset, vec);
            return;
        }
    }
    vec->x = vec->y = vec->z = ftKb_Init_804D9450;
}
