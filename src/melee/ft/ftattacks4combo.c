
#include "ft/ftattacks4combo.h"

#include "ft/chara/ftCommon/ftCo_AttackS4.h"
#include "ft/chara/ftCommon/ftCo_Wait.h"
#include "ft/fighter.h"

bool ftCo_800CECE8(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->cmd_vars[0] != 0 && (fp->input.x668 & HSD_PAD_A)) {
        ftCo_800CED30(gobj);
        return true;
    }
    return false;
}

/// This atrocious-looking code is the only way I could get the compiler
/// to spit out the redundant branch instructions found in the assembly.
/// Otherwise a simple switch statement is functionally equivalent.
void ftCo_800CED30(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    FighterKind kind = fp->kind;

    if (kind == FTKIND_CLINK) {
        goto first;
    } else {
        if (kind < FTKIND_CLINK) {
            if (kind != FTKIND_LINK) {
                goto second;
            first:
                if (kind != FTKIND_LINK) {
                    goto third;
                }
            }
        } else {
        second:
            OSReport("don't have smash42 motion!!!\n");
            __assert("ftattacks4combo.c", 0x36, "0");
        }
    }
third:
    fp->allow_interrupt = false;
    Fighter_ChangeMotionState(gobj, ftLk_MS_AttackS42, 0, 0.0F, 1.0F, 0.0F,
                              NULL);
    ftAnim_8006EBA4(gobj);
}

void ftCo_AttackS42_Anim(Fighter_GObj* gobj)
{
    ftCo_AttackS4_Anim(gobj);
}

void ftCo_AttackS42_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->allow_interrupt) {
        ftCo_Wait_IASA(gobj);
    }
}

void ftCo_AttackS42_Phys(Fighter_GObj* gobj)
{
    ftCo_AttackS4_Phys(gobj);
}

void ftCo_AttackS42_Coll(Fighter_GObj* gobj)
{
    ftCo_AttackS4_Coll(gobj);
}
