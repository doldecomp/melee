#include "ftcolanim.h"

#include "ft/fighter.h"
#include "ft/ftaction.h"
#include "ft/ftdata.h"
#include "ft/types.h"
#include "lb/lb_00F9.h"

#include <melee/ft/chara/ftCommon/ftCo_HammerWait.h>

#pragma force_active on

/* 0BFE74 */ static void ftCo_800BFE74(Fighter_GObj* gobj, CommandInfo* cmd);
/* 0BFEB4 */ static void ftCo_800BFEB4(Fighter_GObj* gobj, CommandInfo* cmd);
/* 0BFEF4 */ static void ftCo_800BFEF4(Fighter_GObj* gobj, CommandInfo* cmd);
/* 0BFE94 */ static void ftCo_800BFE94(Fighter_GObj* gobj, CommandInfo* cmd);
/* 0BFED4 */ static void ftCo_800BFED4(Fighter_GObj* gobj, CommandInfo* cmd);
/* 0BFF14 */ static void ftCo_800BFF14(Fighter_GObj* gobj, CommandInfo* cmd);

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

void ftCo_Sleep_Anim(Fighter_GObj* gobj) {}

void ftCo_Sleep_IASA(Fighter_GObj* gobj) {}

static void ftCo_800BFE74(Fighter_GObj* gobj, CommandInfo* cmd)
{
    ftAction_80071028(gobj, cmd);
}

static void ftCo_800BFE94(Fighter_GObj* gobj, CommandInfo* cmd)
{
    ftAction_800711DC(gobj, cmd);
}

static void ftCo_800BFEB4(Fighter_GObj* gobj, CommandInfo* cmd)
{
    ftAction_80071B50(gobj, cmd);
}

static void ftCo_800BFED4(Fighter_GObj* gobj, CommandInfo* cmd)
{
    ftAction_80071CA4(gobj, cmd);
}

static void ftCo_800BFEF4(Fighter_GObj* gobj, CommandInfo* cmd)
{
    ftAction_800730B8(gobj, cmd);
}

static void ftCo_800BFF14(Fighter_GObj* gobj, CommandInfo* cmd)
{
    ftAction_80073108(gobj, cmd);
}

static void ft_800BFF34(Fighter_GObj* gobj, CommandInfo* cmd, int arg2)
{
    int i = arg2 - 0x15;
    ftCo_803C6AD0[i](gobj, cmd);
}

static void ft_800BFF70(Fighter_GObj* gobj, CommandInfo* cmd, int arg0)
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

#pragma push
#pragma dont_inline on
void ftCo_800C0200(Fighter* fp, int arg1)
{
    if (arg1 >= 0x7B) {
        OSReport("don't reset spycloak colanim!\n");
        __assert("ftcolanimlist.c", 0xC1, "0");
        return;
    }
    if (Fighter_804D653C[arg1].unk5 != 0) {
        lb_80014498(&fp->x488);
        if (ftData_UnkMotionStates4[fp->kind] != NULL) {
            ftData_UnkMotionStates4[fp->kind](fp->gobj);
        }
        if (ftCo_800C53E4(fp) != 0) {
            ftCo_800BFFD0(fp, 0x6A, 0);
        }
    } else {
        lb_80014498(&fp->x408);
        if (fp->x2224_b2) {
            ftCo_800BFFD0(fp, 0x7A, 0);
        }
        if (fp->dmg.x18F0 != 0) {
            ftCo_800BFFD0(fp, 8, 0);
        }
        if (fp->x221D_b6) {
            ftCo_800BFFD0(fp, 0x6B, 0);
        }
        if (fp->x1994 != 0 || fp->x1990 != 0 || fp->x2221_b0) {
            ftCo_800BFFD0(fp, 9, 0);
        }
    }
}

void ftCo_800C0358(Fighter* fp, Fighter* arg1, s32 arg2)
{
    if (arg2 >= 0x7B) {
        OSReport("don't reset spycloak colanim!\n");
        __assert("ftcolanimlist.c", 0xDE, "0");
        return;
    }
    if (Fighter_804D653C[arg2].unk5 != 0) {
        arg1->x488 = fp->x488;
    } else {
        arg1->x408 = fp->x408;
    }
}

void ftCo_800C0408(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    while (lb_80014258(gobj, &fp->x508, ft_800BFF34)) {
        lb_80014498(&fp->x508);
        if (fp->x2226_b4) {
            ftCo_800BFFD0(fp, 0x80, 0);
        }
    }
    while (lb_80014258(gobj, &fp->x408, ft_800BFF34)) {
        lb_80014498(&fp->x408);
        if (fp->x2224_b2) {
            ftCo_800BFFD0(fp, 0x7A, 0);
        }
        if (fp->dmg.x18F0 != 0) {
            ftCo_800BFFD0(fp, 8, 0);
        }
        if (fp->x221D_b6) {
            ftCo_800BFFD0(fp, 0x6B, 0);
        }
        if (fp->x1994 != 0 || fp->x1990 != 0 || fp->x2221_b0) {
            ftCo_800BFFD0(fp, 9, 0);
        }
    }
    if (fp->x408.x28_colanim.i == 0) {
        while (lb_80014258(gobj, &fp->x488, ft_800BFF34)) {
            lb_80014498(&fp->x488);
            if (ftData_UnkMotionStates4[fp->kind] != NULL) {
                ftData_UnkMotionStates4[fp->kind](fp->gobj);
            }
            if (ftCo_800C53E4(fp)) {
                ftCo_800BFFD0(fp, 0x6A, 0);
            }
        }
    } else {
        while (lb_80014258(gobj, &fp->x488, ft_800BFF70)) {
            lb_80014498(&fp->x488);
            if (ftData_UnkMotionStates4[fp->kind] != NULL) {
                ftData_UnkMotionStates4[fp->kind](fp->gobj);
            }
            if (ftCo_800C53E4(fp)) {
                ftCo_800BFFD0(fp, 0x6A, 0);
            }
        }
    }
    fp->x2221_b3 = true;
}
#pragma pop
