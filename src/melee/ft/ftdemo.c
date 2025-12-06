#include "ftdemo.h"

#include "ftdynamics.h"

#include <platform.h>

#include "cm/camera.h"
#include "ef/efasync.h"
#include "ft/fighter.h"
#include "ft/ft_0BEC.h"
#include "ft/ft_0BEF.h"
#include "ft/ft_0BF0.h"
#include "ft/ft_0C31.h"
#include "ft/ft_0C88.h"
#include "ft/ftanim.h"
#include "ft/ftcoll.h"
#include "ft/ftdata.h"
#include "ft/ftdrawcommon.h"
#include "ft/ftlib.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "ftCommon/ftCo_09F4.h"
#include "ftCommon/ftCo_DemoCallback0.h"
#include "lb/lbshadow.h"

#include "pl/forward.h"

#include "pl/types.h"

#include <math.h>
#include <dolphin/os/OSError.h>
#include <baselib/archive.h>
#include <baselib/debug.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>
#include <baselib/gobjuserdata.h>
#include <baselib/objalloc.h>

static HSD_GObjEvent on_create_fighter[16] = {
    ftCo_800BECB0, ftCo_800BED88, ftCo_800BEF04, NULL,
    ftCo_800BEFD4, ftCo_800BF034, ftCo_800BF108, ftCo_800C6150,
    ftCo_800C7070, ftCo_800C70D0, ftCo_800C7178, ftCo_800C7220,
    ftCo_800C7294, ftCo_800C7308, ftCo_800C739C, ftCo_800C7434
};

static void initFighter(HSD_GObj* gobj, plAllocInfo2* alloc_info)
{
    struct plAllocInfo temp1;
    temp1.internal_id = alloc_info->internal_id;
    temp1.slot = alloc_info->slot;
    temp1.b0 = alloc_info->has_transformation;
    Fighter_UnkInitLoad_80068914(gobj, &temp1);
}

Fighter_GObj* ftDemo_CreateFighter(plAllocInfo2* alloc_info)
{
    Fighter_GObj* gobj = GObj_Create(HSD_GOBJ_CLASS_FIGHTER, 8, 0);
    GObj_SetupGXLink(gobj, ftDrawCommon_80080E18, 5, 0);
    {
        Fighter* fp = HSD_ObjAlloc(&fighter_alloc_data);
        fp->dat_attrs_backup = HSD_ObjAlloc(&fighter_dat_attrs_alloc_data);
        GObj_InitUserData(gobj, 4, Fighter_Unload_8006DABC, fp);
        ftData_8008572C(alloc_info->internal_id);
        initFighter(gobj, alloc_info);
        fp->x18 = 14;
        fp->x1C_actionStateList = ftData_803C52A0;
        fp->x20_actionStateList = ftData_UnkMotionStates0[fp->kind];
        fp->x24 = fp->ft_data->x14;
        fp->x28 = fp->ft_data->x18;
        efAsync_8006737C(ftData_UnkBytePerCharacter[fp->kind]);
        if (!alloc_info->b0) {
            ftData_80085820(fp->kind, fp->x619_costume_id);
        } else {
            ftData_800858E4(fp->kind, fp->x619_costume_id);
        }
        Fighter_UnkUpdateCostumeJoint_800686E4(gobj);
        {
            enum_t a, b;
            if (alloc_info->unk8 >= 9) {
                ftData_UnkDemoCallbacks0[fp->kind](alloc_info->unk8, &a, &b);
            } else if (alloc_info->unk8 >= 8) {
                b = 13;
                a = 13;
            } else if (alloc_info->unk8 >= 7) {
                b = 12;
                a = 12;
            } else if (alloc_info->unk8 >= 5) {
                a = 10;
                b = 11;
            } else {
                a = 0;
                b = 9;
            }
            ftData_80085B98(fp, a, b);
        }
        ftParts_80074E58(fp);
        ftParts_SetupParts(gobj);
        ftAnim_80070308(gobj);
        ftCo_800C884C(gobj);
        Fighter_80068E64(gobj);
        ftParts_800749CC(gobj);
        ftAnim_8007077C(gobj);
        ftCo_8009CF84(fp);
        ftAnim_8006FE48(gobj);
        Fighter_UnkUpdateVecFromBones_8006876C(fp);
        ftCo_8009F578(fp);
        if (ftData_OnLoad[fp->kind] != NULL) {
            ftData_OnLoad[fp->kind](gobj);
        }
        ftColl_8007B320(gobj);
        fp->x890_cameraBox = Camera_80029020();
        lbShadow_8000ED54(&fp->x20A4, gobj->hsd_obj);
    }
    HSD_GObjProc_8038FD54(gobj, Fighter_8006A360, 1);
    HSD_GObjProc_8038FD54(gobj, Fighter_procUpdate, 4);
    HSD_GObjProc_8038FD54(gobj, Fighter_procMap, 5);
    HSD_GObjProc_8038FD54(gobj, Fighter_8006C80C, 9);
    HSD_GObjProc_8038FD54(gobj, Fighter_8006D9AC, 16);
    Fighter_UnkProcessDeath_80068354(gobj);
    if (on_create_fighter[alloc_info->unk8] != NULL) {
        on_create_fighter[alloc_info->unk8](gobj);
    }
    ftLib_800867E8(gobj);
    return gobj;
}

void ftDemo_ObjAllocInit(void)
{
    Fighter_800679B0();
    HSD_ObjAllocInit(&fighter_x59C_alloc_data, 0xB000, 0x20);
}

void ftDemo_SetArchiveData(int pairs_idx, HSD_Archive* archive, int arr_idx)
{
    static int ints[5] = { 9, 10, 11, 14, 15 };
    ftData_UnkCountStruct* pair = &ftData_UnkIntPairs[pairs_idx];
    if (pair->data == NULL) {
        if (arr_idx >= 4) {
            pair->data = HSD_ArchiveGetPublicAddress(
                archive,
                ftDemo_GetMotionFileString(pairs_idx, ints[arr_idx - 4]));
        } else {
            pair->data = HSD_ArchiveGetPublicAddress(
                archive, ((char***) ftData_803C2468)[pairs_idx][arr_idx]);
        }
    }
}

char* ftDemo_GetMotionFileString(int cb_idx, int cb_arg)
{
    if (ftData_803C24EC[cb_idx] != NULL) {
        return ftData_803C24EC[cb_idx](cb_arg);
    } else {
        OSReport("no demo vi anim! %d\n", cb_arg);
        __assert("ftdemo.c", 296, "0");
    }
}

void ftDemo_SetFacingDirection(Fighter_GObj* gobj, float facing_dir)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->facing_dir = facing_dir;
    ftParts_80075AF0(fp, 0, M_PI_2 * fp->facing_dir);
}
