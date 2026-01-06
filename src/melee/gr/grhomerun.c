#include "grhomerun.h"

#include <platform.h>

#include "cm/camera.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"

void grHomeRun_8021C750(bool arg) {}

/// #grHomeRun_8021C754

void grHomeRun_8021C7FC(void) {}

void grHomeRun_8021C800(void)
{
    grZakoGenerator_801CAE04(0);
}

bool grHomeRun_8021C824(void)
{
    return false;
}

/// #grHomeRun_8021C82C

/// #grHomeRun_8021C914

bool grHomeRun_8021CB10(Ground_GObj* arg)
{
    return false;
}

void grHomeRun_8021CB18(Ground_GObj* arg) {}

void grHomeRun_8021CB1C(Ground_GObj* arg) {}

/// #grHomeRun_8021CB20

bool grHomeRun_8021D678(Ground_GObj* arg)
{
    return false;
}

/// #grHomeRun_8021D680

void grHomeRun_8021DEB0(Ground_GObj* arg) {}

void grHomeRun_8021DEB4(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138((HSD_GObj*) gobj, gp->map_id, 0);
}

bool grHomeRun_8021DEE0(Ground_GObj* arg)
{
    return false;
}

void grHomeRun_8021DEE8(Ground_GObj* arg) {}

void grHomeRun_8021DEEC(Ground_GObj* arg) {}

/// #grHomeRun_8021DEF0

bool grHomeRun_8021DF48(Ground_GObj* arg)
{
    return false;
}

/// #grHomeRun_8021DF50

/// #grHomeRun_8021E008

void grHomeRun_8021E038(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, false);
}

bool grHomeRun_8021E064(Ground_GObj* arg)
{
    return false;
}

void grHomeRun_8021E06C(Ground_GObj* arg) {}

void grHomeRun_8021E070(Ground_GObj* arg) {}

/// #grHomeRun_8021E074

bool grHomeRun_8021E0CC(Ground_GObj* arg)
{
    return false;
}

/// #grHomeRun_8021E0D4

/// #grHomeRun_8021E18C

void grHomeRun_8021E1BC(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, false);
}

bool grHomeRun_8021E1E8(Ground_GObj* arg)
{
    return false;
}

void grHomeRun_8021E1F0(Ground_GObj* arg) {}

void grHomeRun_8021E1F4(Ground_GObj* arg) {}

/// #grHomeRun_8021E1F8

bool grHomeRun_8021E250(Ground_GObj* arg)
{
    return false;
}

/// #grHomeRun_8021E258

/// #grHomeRun_8021E310

void grHomeRun_8021E340(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, false);
}

bool grHomeRun_8021E36C(Ground_GObj* arg)
{
    return false;
}

void grHomeRun_8021E374(Ground_GObj* arg) {}

void grHomeRun_8021E378(Ground_GObj* arg) {}

/// #grHomeRun_8021E37C

bool grHomeRun_8021E3D4(Ground_GObj* arg)
{
    return false;
}

/// #grHomeRun_8021E3DC

/// #grHomeRun_8021E494

void grHomeRun_8021E4C4(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, false);
}

bool grHomeRun_8021E4F0(Ground_GObj* arg)
{
    return false;
}

void grHomeRun_8021E4F8(Ground_GObj* arg) {}

void grHomeRun_8021E4FC(Ground_GObj* arg) {}

/// #grHomeRun_8021E500

/// #fn_8021E994

/// #grHomeRun_8021EA30

void grHomeRun_8021EAF8(void)
{
    stage_info.flags |= (1 << 7);
}

// Copies the main camera into a target camera
void fn_8021EB10(HSD_GObj* target_cam_gobj)
{
    HSD_GObj* main_cam_gobj;
    HSD_CObj* main_cam_cobj;
    HSD_CObj* target_cam_cobj;

    f32 fov;
    f32 aspect;
    HSD_RectF32 viewport;
    Scissor scissor;
    Vec3 position;

    target_cam_cobj = GET_COBJ(target_cam_gobj);
    main_cam_gobj = Camera_80030A50();
    if (main_cam_gobj) {
        if ((main_cam_cobj = GET_COBJ(main_cam_gobj))) {
            HSD_CObjSetFlags(target_cam_cobj, HSD_CObjGetFlags(main_cam_cobj));
            HSD_CObjGetViewportf(main_cam_cobj, &viewport);
            HSD_CObjSetViewportf(target_cam_cobj, &viewport);
            HSD_CObjGetScissor(main_cam_cobj, &scissor);
            HSD_CObjSetScissor(target_cam_cobj, &scissor);
            target_cam_cobj->u = main_cam_cobj->u;
            HSD_CObjSetNear(target_cam_cobj, HSD_CObjGetNear(main_cam_cobj));
            HSD_CObjSetFar(target_cam_cobj, HSD_CObjGetFar(main_cam_cobj));

            HSD_CObjGetPerspective(main_cam_cobj, &fov, &aspect);
            HSD_CObjSetPerspective(target_cam_cobj, fov, aspect);
            HSD_CObjGetEyePosition(main_cam_cobj, &position);
            HSD_CObjSetEyePosition(target_cam_cobj, &position);
            HSD_CObjGetInterest(main_cam_cobj, &position);
            HSD_CObjSetInterest(target_cam_cobj, &position);
        }
    }
    if (HSD_CObjSetCurrent(target_cam_cobj) != 0) {
        HSD_FogSet(NULL);
        HSD_GObj_80390ED0(target_cam_gobj, 7U);
        HSD_CObjEndCurrent();
    }
}

/// #grHomeRun_8021EC58

/// #grHomeRun_8021ED74

/// #grHomeRun_8021EDD4

DynamicsDesc* grHomeRun_8021EEB4(enum_t arg)
{
    return false;
}

/// #grHomeRun_8021EEBC

extern f32 grHr_804DBC94;

f32 grHomeRun_8021EF10(void)
{
    return grHr_804DBC94 * Ground_801C0498();
}
