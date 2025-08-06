#include "gmfixedcamera.h"

#include "gm_1B03.static.h"

#include "gm_unsplit.h"
#include "gmvsdata.h"

#include <sysdolphin/baselib/controller.h>
#include <sysdolphin/baselib/memory.h>
#include <sysdolphin/baselib/random.h>
#include <melee/db/db.h>
#include <melee/gm/gm_unsplit.h>
#include <melee/gm/gmcamera.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/gm/gmresult.h>
#include <melee/gm/gmresultplayer.h>
#include <melee/gm/gmtou.h>
#include <melee/gm/gmvsmelee.h>
#include <melee/gm/types.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lbbgflash.h>
#include <melee/lb/lbcardgame.h>
#include <melee/lb/lbcardnew.h>
#include <melee/lb/lbdvd.h>
#include <melee/lb/lbmthp.h>
#include <melee/lb/lbsnap.h>
#include <melee/lb/lbtime.h>
#include <melee/lb/types.h>
#include <melee/mn/mngallery.h>
#include <melee/mn/types.h>
#include <melee/un/un_2FC9.h>
#include <melee/vi/types.h>
#include <melee/vi/vi0102.h>
#include <melee/vi/vi0402.h>
#include <melee/vi/vi0501.h>
#include <melee/vi/vi1101.h>
#include <melee/vi/vi1201v1.h>

/* extern functions referenced in MinorScenes */
extern void gm_801BFA6C(MinorScene*);
extern void gm_801BFABC(MinorScene*);
extern void gm_801BFCFC(MinorScene*);
extern void gm_801A6254(MinorScene*);
extern void gm_801A6308(MinorScene*);

MinorScene gm_803DF1E0_MinorScenes[] = {
    {
        0,
        3,
        0,
        gm_801B9F10,
        gm_801B9F3C,
        {
            MN_CSS,
            &gm_804807B0,
            &gm_804807B0,
        },
    },
    {
        1,
        3,
        0,
        gm_801B9F64,
        gm_801B9F8C,
        {
            MN_SSS,
            &gm_80480668,
            &gm_80480668,
        },
    },
    {
        2,
        3,
        0,
        gm_801B9FC8,
        gm_801B9FFC,
        {
            MN_VS,
            &gm_80480530,
            &gm_80479D98,
        },
    },
    {
        3,
        3,
        0,
        gm_801BA024,
        gm_801BA058,
        {
            MN_SUDDEN_DEATH,
            &gm_80480530,
            &gm_8047E2A4,
        },
    },
    {
        4,
        3,
        0,
        gm_801BA078,
        gm_801BA098,
        {
            MN_RESULTS,
            &gm_8047C020,
            NULL,
        },
    },
    {
        0x80,
        2,
        0,
        gm_801BFA6C,
        NULL,
        {
            MN_APPROACH,
            &gm_804D6860,
            &gm_804D6860,
        },
    },
    {
        0x81,
        2,
        0,
        gm_801BFABC,
        gm_801A6254,
        {
            MN_VS,
            &gm_80480530,
            &gm_80479D98,
        },
    },
    {
        0xC0,
        2,
        0,
        gm_801BFCFC,
        gm_801A6308,
        {
            MN_PRIZE_INTERFACE,
            &un_804A1F48,
            NULL,
        },
    },
    { -1 },
};

void gm_801B9F10(MinorScene* scene)
{
    gm_801A5618(scene, &gmMainLib_804D3EE0->unk_A90, 7);
}

void gm_801B9F3C(MinorScene* scene)
{
    gm_801A5680(scene, &gmMainLib_804D3EE0->unk_A90);
}

void gm_801B9F64(MinorScene* scene)
{
    gm_801A5754(scene, &gmMainLib_804D3EE0->unk_A90);
}

void gm_801B9F8C(MinorScene* scene)
{
    gm_801A57A8(scene, &gmMainLib_804D3EE0->unk_A90, 0);
}

void fn_801B9FB8(StartMeleeData* arg0, StartMeleeData* arg1)
{
    arg0->rules.x38 = gm_80165290;
}

void gm_801B9FC8(MinorScene* scene)
{
    VsModeData* data = &gmMainLib_804D3EE0->unk_A90;
    gm_801A583C(scene, data, fn_801B9FB8, NULL);
}

void gm_801B9FFC(MinorScene* scene)
{
    gm_801A5AF0(scene, 4, 3);
}

void gm_801BA024(MinorScene* scene)
{
    VsModeData* data = &gmMainLib_804D3EE0->unk_A90;
    gm_801A5C3C(scene, data, fn_801B9FB8, NULL);
}

void gm_801BA058(MinorScene* scene)
{
    gm_801A5EC8(scene);
}

void gm_801BA078(MinorScene* scene)
{
    gm_801A5F00(scene);
}

void gm_801BA098(MinorScene* scene)
{
    VsModeData* data = &gmMainLib_804D3EE0->unk_A90;
    gm_801A5F64(scene, data, 0);
}

void gm_801BA0C4_OnInit(void)
{
    gm_80167B50(&gmMainLib_804D3EE0->unk_A90);
}

void gm_801BA0EC_OnLoad(void)
{
    gm_801A55C4();
}
