#include "ftcolanim.h"

#include "ft/fighter.h"
#include "ft/ftaction.h"
#include "ft/types.h"
#include "lb/lb_00F9.h"

#pragma force_active on

/* 0BFE74 */ static void ftCo_800BFE74(Fighter_GObj* gobj, FtCmdState* cmd);
/* 0BFEB4 */ static void ftCo_800BFEB4(Fighter_GObj* gobj, FtCmdState* cmd);
/* 0BFEF4 */ static void ftCo_800BFEF4(Fighter_GObj* gobj, FtCmdState* cmd);
/* 0BFE94 */ static void ftCo_800BFE94(Fighter_GObj* gobj, FtCmdState* cmd);
/* 0BFED4 */ static void ftCo_800BFED4(Fighter_GObj* gobj, FtCmdState* cmd);
/* 0BFF14 */ static void ftCo_800BFF14(Fighter_GObj* gobj, FtCmdState* cmd);
/* 0BFF34 */ static UNK_RET ft_800BFF34(UNK_PARAMS);
/* 0BFF70 */ static void ft_800BFF70(Fighter_GObj* gobj, FtCmdState* cmd,
                                     int arg0);

FtCmd ftCo_803C6AD0[3] = {
    ftCo_800BFE74,
    ftCo_800BFEB4,
    ftCo_800BFEF4,
};

FtCmd ftCo_803C6ADC[3] = {
    ftCo_800BFE94,
    ftCo_800BFED4,
    ftCo_800BFF14,
};

/* literal */ char ftCo_803C6AE8[] = "don't reset spycloak colanim!\n";
/* literal */ char ftCo_803C6B08[] = "ftcolanimlist.c";
/* literal */ SDATA char ftCo_804D3C10[] = "0";

void ftCo_Sleep_Anim(Fighter_GObj* gobj) {}

void ftCo_Sleep_IASA(Fighter_GObj* gobj) {}

static void ftCo_800BFE74(Fighter_GObj* gobj, FtCmdState* cmd)
{
    ftAction_80071028(gobj, cmd);
}

static void ftCo_800BFE94(Fighter_GObj* gobj, FtCmdState* cmd)
{
    ftAction_800711DC(gobj, cmd);
}

static void ftCo_800BFEB4(Fighter_GObj* gobj, FtCmdState* cmd)
{
    ftAction_80071B50(gobj, cmd);
}

static void ftCo_800BFED4(Fighter_GObj* gobj, FtCmdState* cmd)
{
    ftAction_80071CA4(gobj, cmd);
}

static void ftCo_800BFEF4(Fighter_GObj* gobj, FtCmdState* cmd)
{
    ftAction_800730B8(gobj, cmd);
}

static void ftCo_800BFF14(Fighter_GObj* gobj, FtCmdState* cmd)
{
    ftAction_80073108(gobj, cmd);
}

/// #ft_800BFF34

void ft_800BFF70(Fighter_GObj* gobj, FtCmdState* cmd, int arg0)
{
    int i = arg0 - 21;
    ftCo_803C6ADC[i](gobj, cmd);
}

void ftCo_800BFFAC(Fighter* fp)
{
    lb_80014498(&fp->x488);
}

bool ftCo_800BFFD0(Fighter* fp, int arg1, int arg2)
{
    if (arg1 >= 0x7B) {
        s32 temp_r7 = arg1 - 0x7B;
        if (lb_800144C8(&fp->x508, Fighter_804D6538, temp_r7, arg2)) {
            return true;
        }
    } else if (Fighter_804D653C[arg1].unk5 != 0) {
        if (lb_800144C8(&fp->x488, Fighter_804D653C, arg1, arg2)) {
            return true;
        }
    } else if (lb_800144C8(&fp->x408, Fighter_804D653C, arg1, arg2)) {
        return true;
    }
    return false;
}

void ftCo_800C0074(Fighter* fp)
{
    lb_80014498(&fp->x408);
}

/// #ft_800C0098

/// #ftCo_800C0134

/// #ftCo_800C0200

/// #ftCo_800C0358

/// #ftCo_800C0408
