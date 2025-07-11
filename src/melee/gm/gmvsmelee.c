#include "gmvsmelee.h"

#include <melee/gm/gm_1601.h>
#include <melee/gm/gm_1A3F.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/gm/types.h>
#include <melee/lb/lbdvd.h>

/* 4D6730 */ extern u8 gm_804D6730;

VsModeData* gm_801A5244(void)
{
    return &gmMainLib_804D3EE0->unk_590;
}

UNK_T gm_801A5250(void)
{
    return &gm_804D6730;
}

/// #gm_801A5258

/// #gm_801A52D0

/// #gm_801A5360

void gm_801A5598_OnInit(void)
{
    gm_80167B50(&gmMainLib_804D3EE0->unk_590);
    gmMainLib_8015CDEC();
}

/// #gm_801A55C4

/// #gm_801A55EC_OnLoad

void gm_801A5614_OnUnload(void) {}

void gm_801A5618(MinorScene* arg0, VsModeData* arg1, int arg2)
{
    CSSData* css_data = gm_801A427C(arg0);
    css_data->match_type = arg2;
    css_data->ko_star_counts = &gm_804D6730;
    css_data->data = *arg1;
    lbDvd_800174BC();
}

/// #gm_801A5680

/// #gm_801A5754

/// #gm_801A57A8

/// #gm_801A583C

/// #gm_801A5AF0

/// #gm_801A5C3C

/// #gm_801A5EC8

/// #gm_801A5F00

/// #gm_801A5F64
