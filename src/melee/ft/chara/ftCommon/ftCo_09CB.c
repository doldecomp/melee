#include <platform.h>

#include "ft/types.h"
#include "lb/lb_00F9.h"

#include <placeholder.h>
#include <baselib/debug.h>
#include <baselib/jobj.h>

#pragma force_active on

/* 09CB40 */ static UNK_RET ftCo_8009CB40(UNK_PARAMS);
/* 09D18C */ static UNK_RET ftCo_8009D18C(UNK_PARAMS);
/* 09D2A4 */ static UNK_RET ftCo_8009D2A4(UNK_PARAMS);
/* 09D3BC */ static UNK_RET ftCo_8009D3BC(UNK_PARAMS);
/* 09D4D4 */ static UNK_RET ftCo_8009D4D4(UNK_PARAMS);
/* 09D5EC */ static UNK_RET ftCo_8009D5EC(UNK_PARAMS);
/* 09D704 */ static UNK_RET ftCo_8009D704(UNK_PARAMS);
/* 09D81C */ static UNK_RET ftCo_8009D81C(UNK_PARAMS);
/* 09D920 */ static UNK_RET ftCo_8009D920(UNK_PARAMS);
/* 09DA38 */ static UNK_RET ftCo_8009DA38(UNK_PARAMS);
/* 09DB50 */ static UNK_RET ftCo_8009DB50(UNK_PARAMS);
/* 09DD94 */ static UNK_RET ftCo_8009DD94(UNK_PARAMS);
/* 09E1D4 */ static UNK_RET ftCo_8009E1D4(UNK_PARAMS);
/* 09E4A8 */ static UNK_RET ftCo_8009E4A8(UNK_PARAMS);
/* 09E614 */ static UNK_RET ftCo_8009E614(UNK_PARAMS);

/* literal */ float const ftCo_804D8768 = 0;
/* literal */ float const ftCo_804D876C = 1;
/* literal */ SDATA char ftCo_804D3B28[] = "jobj.h";
/* literal */ SDATA char ftCo_804D3B30[] = "jobj";
/* literal */ SDATA char ftCo_804D3B38[] = "scale";
/* literal */ SDATA char ftCo_804D3B40[] = "0";
/* literal */ char ftDynamics_803C5720[] = "translate";
/* literal */ char ftDynamics_803C572C[] = "fighter dynamics num over!\n";
/* literal */ char ftDynamics_803C5748[] = "ftdynamics.c";

/// #ftCo_8009CB40

/// #ftCo_8009CF84

/// @todo #ft_80459B88
extern KirbyHat_r13 ft_80459B88;

void ftCo_8009D074(Fighter* fp)
{
    int* new_var2;
    int i2;
    ArticleDynamicBones* new_var;
    int i;
    KirbyHatStruct* kirbyHatNodes;
    kirbyHatNodes = ft_80459B88.x18_kirbyHatStruct;
    fp->dynamics_num = kirbyHatNodes->x14_hatDynamics->dynamicsNum;
    if ((*(new_var2 = &fp->dynamics_num)) >=
        (signed) ARRAY_SIZE(fp->dynamic_bone_sets))
    {
        OSReport("         fighter dynamics num over!\n");
        __assert("ftdynamics.c", 135,
                 "fp->dynamiscs_num < Ft_Dynamics_NumMax");
    }
    for (i = 0; i < fp->dynamics_num; i++) {
        HSD_JObj* kirbyHatJObj;
        FtDynamicBones* article;
        article = &kirbyHatNodes->x14_hatDynamics->ftDynamicBones->array[i];
        kirbyHatJObj = fp->fv.kb.hat.jobj;

        for (i2 = 0; i2 < article->x0_apply_phys_num; i2++) {
            if (kirbyHatJObj->child != NULL) {
                kirbyHatJObj = kirbyHatJObj->child;
                continue;
            } else {
                while (kirbyHatJObj->next == NULL) {
                    kirbyHatJObj = kirbyHatJObj->parent;
                }
            }
            kirbyHatJObj = kirbyHatJObj->next;
        }

        lb_8000FD48(kirbyHatJObj, &fp->dynamic_bone_sets[i].x4_dynamicBones,
                    article->x4_dynamicBones.x4_jobj_num);
        fp->dynamic_bone_sets[i].x0_apply_phys_num = 0;
        new_var = kirbyHatNodes->x14_hatDynamics->ftDynamicBones;
        lb_80011710(&new_var->array[i].x4_dynamicBones,
                    &fp->dynamic_bone_sets[i].x4_dynamicBones);
    }
}

/// #ftCo_8009D18C

/// #ftCo_8009D2A4

/// #ftCo_8009D3BC

/// #ftCo_8009D4D4

/// #ftCo_8009D5EC

/// #ftCo_8009D704

/// #ftCo_8009D81C

/// #ftCo_8009D920

/// #ftCo_8009DA38

/// #ftCo_8009DB50

/// #ftCo_8009DC54

/// #ftCo_8009DD94

/// #ftCo_8009E0A8

/// #ftCo_8009E0D4

/// #ftCo_8009E140

/// #ftCo_8009E1D4

/// #ftCo_8009E318

/// #ftCo_8009E4A8

/// #ftCo_8009E614

/// #ftCo_8009E714

/// #ftCo_8009E7B4

/// #ftCo_8009EAF8
