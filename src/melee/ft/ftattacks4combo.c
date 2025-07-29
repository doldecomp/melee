
#include "ft/ftattacks4combo.h"

#include "ft/chara/ftCommon/ftCo_AttackS4.h"
#include "ft/chara/ftCommon/ftCo_Wait.h"
#include "ft/fighter.h"

bool ftCo_800CECE8(ftCo_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (((u32) fp->cmd_vars[0] != 0) && (fp->input.x668 & 0x100)) {
        ftCo_800CED30(gobj);
        return true;
    }
    return false;
}

// This atrocious-looking code is the only way I could get the compiler
// to spit out the redundant branch instructions found in the assembly.
// Otherwise a simple switch statement is functionally equivalent.
void ftCo_800CED30(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
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
    fp->allow_interrupt = 0;
    Fighter_ChangeMotionState(gobj, 0x155, 0U, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
}

void ftCo_AttackS42_Anim(ftCo_GObj* gobj)
{
    ftCo_AttackS4_Anim(gobj);
}

void ftCo_AttackS42_IASA(ftCo_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->allow_interrupt) {
        ftCo_Wait_IASA(gobj);
    }
}

void ftCo_AttackS42_Phys(ftCo_GObj* gobj)
{
    ftCo_AttackS4_Phys(gobj);
}

void ftCo_AttackS42_Coll(ftCo_GObj* gobj)
{
    ftCo_AttackS4_Coll(gobj);
}
