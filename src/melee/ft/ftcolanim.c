#include "ftcolanim.h"

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

void ftCo_Sleep_Anim(ftCo_GObj* gobj) {}

void ftCo_Sleep_IASA(ftCo_GObj* gobj) {}

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

UNK_RET ft_800BFF34(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

void ft_800BFF70(Fighter_GObj* gobj, FtCmdState* cmd, int arg0)
{
    ftCo_803C6ADC[arg0 - 0x15](gobj, cmd);
}

void ftCo_800BFFAC(Fighter* fp)
{
    lb_80014498(&fp->x488);
}

bool ftCo_800BFFD0(Fighter* fp, enum_t arg1, bool arg2)
{
    NOT_IMPLEMENTED;
}

void ftCo_800C0074(Fighter* fp)
{
    lb_80014498(&fp->x408);
}

UNK_RET ft_800C0098(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

void ftCo_800C0134(Fighter* fp)
{
    NOT_IMPLEMENTED;
}

void ftCo_800C0200(Fighter* fp, int arg1)
{
    NOT_IMPLEMENTED;
}

void ftCo_800C0358(Fighter* fp, Fighter* arg1, s32 arg2)
{
    NOT_IMPLEMENTED;
}

void ftCo_800C0408(Fighter_GObj* gobj)
{
    NOT_IMPLEMENTED;
}
