#include "mnmainrule.h"

#include "mnmain.h"

#include <sysdolphin/baselib/gobjplink.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/sislib.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/sc/types.h>

extern HSD_FogDesc* MenMain_fog;
extern UNK_T MenMain_lights;
extern HSD_CObjDesc* MenMain_cam;
extern StaticModelDesc MenMainBack_Top;
extern StaticModelDesc MenMainPanel_Top;
extern StaticModelDesc MenMainConTop_Top;
extern StaticModelDesc MenMainCursor_Top;
extern StaticModelDesc MenMainConRl_Top;
extern StaticModelDesc MenMainCursorRl_Top;
extern StaticModelDesc MenMainNmRl_Top;
extern StaticModelDesc MenMainCursorTr01_Top;
extern StaticModelDesc MenMainCursorTr02_Top;
extern StaticModelDesc MenMainCursorTr03_Top;
extern StaticModelDesc MenMainCursorTr04_Top;
extern StaticModelDesc MenMainCursorRl01_Top;
extern StaticModelDesc MenMainCursorRl02_Top;
extern StaticModelDesc MenMainCursorRl03_Top;
extern StaticModelDesc MenMainCursorRl04_Top;
extern StaticModelDesc MenMainCursorRl05_Top;
extern StaticModelDesc MenMainConIs_Top;
extern StaticModelDesc MenMainCursorIs_Top;
extern StaticModelDesc MenMainConSs_Top;
extern StaticModelDesc MenMainCursorSs_Top;

/// #fn_8022F538

/// #mn_8022FB88

/// #mn_8022FD18

/// #mn_8022FEC8

/// #mn_80230198

/// #mn_80230274

/// #mn_802307F8

/// #mn_802308F0

/// #fn_802309F0

/// #mn_80230D18

/// #mn_80230E38

int mn_80231634(struct mn_80231634_t* arg0)
{
    if (arg0 == NULL) {
        return 0;
    }
    return arg0->x10;
}

/// #mn_8023164C

/// #mn_80231714

void mn_802317E4(HSD_Archive* archive, int arg1)
{
    mn_80231804(archive, arg1);
}

extern int mn_804D6BD4;

void mn_80231804(HSD_Archive* archive, int arg1)
{
    HSD_GObjProc* temp_r3;
    mn_804D6BC8.cooldown = 0x14;
    mn_804D6BC8.x2 = 0;
    mn_804D6BC8.x4 = 0;
    mn_804A04F0.buttons = 0;
    mn_804A04F0.prev_menu = mn_804A04F0.cur_menu;
    mn_804A04F0.cur_menu = 0xD;
    mn_804A04F0.hovered_selection = 0;
    HSD_SisLib_803A5E70();

    lbArchive_LoadSections(
        archive, (void**) &MenMainBack_Top.joint, "MenMainBack_Top_joint",
        &MenMainBack_Top.animjoint, "MenMainBack_Top_animjoint",
        &MenMainBack_Top.matanim_joint, "MenMainBack_Top_matanim_joint",
        &MenMainBack_Top.shapeanim_joint, "MenMainBack_Top_shapeanim_joint",

        &MenMain_cam, "ScMenMain_cam_int1_camera", &MenMain_lights,
        "ScMenMain_scene_lights", &MenMain_fog, "ScMenMain_fog",

        &MenMainPanel_Top.joint, "MenMainPanel_Top_joint",
        &MenMainPanel_Top.animjoint, "MenMainPanel_Top_animjoint",
        &MenMainPanel_Top.matanim_joint, "MenMainPanel_Top_matanim_joint",
        &MenMainPanel_Top.shapeanim_joint, "MenMainPanel_Top_shapeanim_joint",

        &MenMainConRl_Top.joint, "MenMainConRl_Top_joint",
        &MenMainConRl_Top.animjoint, "MenMainConRl_Top_animjoint",
        &MenMainConRl_Top.matanim_joint, "MenMainConRl_Top_matanim_joint",
        &MenMainConRl_Top.shapeanim_joint, "MenMainConRl_Top_shapeanim_joint",

        &MenMainCursorRl_Top.joint, "MenMainCursorRl_Top_joint",
        &MenMainCursorRl_Top.animjoint, "MenMainCursorRl_Top_animjoint",
        &MenMainCursorRl_Top.matanim_joint,
        "MenMainCursorRl_Top_matanim_joint",
        &MenMainCursorRl_Top.shapeanim_joint,
        "MenMainCursorRl_Top_shapeanim_joint",

        &MenMainCursorRl_Top.joint, "MenMainCursorRl_Top_joint",
        &MenMainCursorRl_Top.animjoint, "MenMainCursorRl_Top_animjoint",
        &MenMainCursorRl_Top.matanim_joint,
        "MenMainCursorRl_Top_matanim_joint",
        &MenMainCursorRl_Top.shapeanim_joint,
        "MenMainCursorRl_Top_shapeanim_joint",

        &MenMainNmRl_Top.joint, "MenMainNmRl_Top_joint",
        &MenMainNmRl_Top.animjoint, "MenMainNmRl_Top_animjoint",
        &MenMainNmRl_Top.matanim_joint, "MenMainNmRl_Top_matanim_joint",
        &MenMainNmRl_Top.shapeanim_joint, "MenMainNmRl_Top_shapeanim_joint",

        &MenMainCursorTr01_Top.joint, "MenMainCursorTr01_Top_joint",
        &MenMainCursorTr01_Top.animjoint, "MenMainCursorTr01_Top_animjoint",
        &MenMainCursorTr01_Top.matanim_joint,
        "MenMainCursorTr01_Top_matanim_joint",
        &MenMainCursorTr01_Top.shapeanim_joint,
        "MenMainCursorTr01_Top_shapeanim_joint",

        &MenMainCursorTr02_Top.joint, "MenMainCursorTr02_Top_joint",
        &MenMainCursorTr02_Top.animjoint, "MenMainCursorTr02_Top_animjoint",
        &MenMainCursorTr02_Top.matanim_joint,
        "MenMainCursorTr02_Top_matanim_joint",
        &MenMainCursorTr02_Top.shapeanim_joint,
        "MenMainCursorTr02_Top_shapeanim_joint",

        &MenMainCursorTr03_Top.joint, "MenMainCursorTr03_Top_joint",
        &MenMainCursorTr03_Top.animjoint, "MenMainCursorTr03_Top_animjoint",
        &MenMainCursorTr03_Top.matanim_joint,
        "MenMainCursorTr03_Top_matanim_joint",
        &MenMainCursorTr03_Top.shapeanim_joint,
        "MenMainCursorTr03_Top_shapeanim_joint",

        &MenMainCursorTr04_Top.joint, "MenMainCursorTr04_Top_joint",
        &MenMainCursorTr04_Top.animjoint, "MenMainCursorTr04_Top_animjoint",
        &MenMainCursorTr04_Top.matanim_joint,
        "MenMainCursorTr04_Top_matanim_joint",
        &MenMainCursorTr04_Top.shapeanim_joint,
        "MenMainCursorTr04_Top_shapeanim_joint",

        &MenMainCursorRl01_Top.joint, "MenMainCursorRl01_Top_joint",
        &MenMainCursorRl01_Top.animjoint, "MenMainCursorRl01_Top_animjoint",
        &MenMainCursorRl01_Top.matanim_joint,
        "MenMainCursorRl01_Top_matanim_joint",
        &MenMainCursorRl01_Top.shapeanim_joint,
        "MenMainCursorRl01_Top_shapeanim_joint",

        &MenMainCursorRl02_Top.joint, "MenMainCursorRl02_Top_joint",
        &MenMainCursorRl02_Top.animjoint, "MenMainCursorRl02_Top_animjoint",
        &MenMainCursorRl02_Top.matanim_joint,
        "MenMainCursorRl02_Top_matanim_joint",
        &MenMainCursorRl02_Top.shapeanim_joint,
        "MenMainCursorRl02_Top_shapeanim_joint",

        &MenMainCursorRl03_Top.joint, "MenMainCursorRl03_Top_joint",
        &MenMainCursorRl03_Top.animjoint, "MenMainCursorRl03_Top_animjoint",
        &MenMainCursorRl03_Top.matanim_joint,
        "MenMainCursorRl03_Top_matanim_joint",
        &MenMainCursorRl03_Top.shapeanim_joint,
        "MenMainCursorRl03_Top_shapeanim_joint",

        &MenMainCursorRl04_Top.joint, "MenMainCursorRl04_Top_joint",
        &MenMainCursorRl04_Top.animjoint, "MenMainCursorRl04_Top_animjoint",
        &MenMainCursorRl04_Top.matanim_joint,
        "MenMainCursorRl04_Top_matanim_joint",
        &MenMainCursorRl04_Top.shapeanim_joint,
        "MenMainCursorRl04_Top_shapeanim_joint",

        &MenMainCursorRl05_Top.joint, "MenMainCursorRl05_Top_joint",
        &MenMainCursorRl05_Top.animjoint, "MenMainCursorRl05_Top_animjoint",
        &MenMainCursorRl05_Top.matanim_joint,
        "MenMainCursorRl05_Top_matanim_joint",
        &MenMainCursorRl05_Top.shapeanim_joint,
        "MenMainCursorRl05_Top_shapeanim_joint",

        &MenMainConIs_Top.joint, "MenMainConIs_Top_joint",
        &MenMainConIs_Top.animjoint, "MenMainConIs_Top_animjoint",
        &MenMainConIs_Top.matanim_joint, "MenMainConIs_Top_matanim_joint",
        &MenMainConIs_Top.shapeanim_joint, "MenMainConIs_Top_shapeanim_joint",

        &MenMainCursorIs_Top.joint, "MenMainCursorIs_Top_joint",
        &MenMainCursorIs_Top.animjoint, "MenMainCursorIs_Top_animjoint",
        &MenMainCursorIs_Top.matanim_joint,
        "MenMainCursorIs_Top_matanim_joint",
        &MenMainCursorIs_Top.shapeanim_joint,
        "MenMainCursorIs_Top_shapeanim_joint",

        &MenMainConSs_Top.joint, "MenMainConSs_Top_joint",
        &MenMainConSs_Top.animjoint, "MenMainConSs_Top_animjoint",
        &MenMainConSs_Top.matanim_joint, "MenMainConSs_Top_matanim_joint",
        &MenMainConSs_Top.shapeanim_joint, "MenMainConSs_Top_shapeanim_joint",

        &MenMainCursorSs_Top.joint, "MenMainCursorSs_Top_joint",
        &MenMainCursorSs_Top.animjoint, "MenMainCursorSs_Top_animjoint",
        &MenMainCursorSs_Top.matanim_joint,
        "MenMainCursorSs_Top_matanim_joint",
        &MenMainCursorSs_Top.shapeanim_joint,
        "MenMainCursorSs_Top_shapeanim_joint",

        0);

    mn_804D6BD4 = arg1;
    mn_8022C304();
    mn_8022BCF8();
    mn_8022BEDC(mn_8022BE34());
    mn_80229B2C();
    mn_80229DC0();
    temp_r3 = HSD_GObjProc_8038FD54(GObj_Create(0, 1, 0x80), fn_8022F538, 0);
    temp_r3->flags_3 = HSD_GObj_804D783C;
    HSD_GObj_80390CD4(mn_80230E38(1));
    lbAudioAx_80023F28(gmMainLib_8015ECB0());
}

/// #mn_80231F80
