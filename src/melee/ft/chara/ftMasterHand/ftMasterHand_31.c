#include <melee/ft/chara/ftMasterHand/__ftMasterHand.h>

#include <melee/ft/ft_unknown_006.h>
#include <melee/ft/ftanim.h>

// TODO In ftcommon.h
extern void func_8007DBCC();

/**
 * TODO Real signature:
 * void ftMasterHand_OnGrabFighter_Victim(HSD_GObj* self_gobj, HSD_GObj* victim_gobj, f32);
 *
 * Is supposed to pass its third argument to func_8007DBCC.
 */
void ftMasterHand_OnGrabFighter_Victim(HSD_GObj* self_gobj, HSD_GObj* victim_gobj)
{
    // TODO
    f32 missing_arg;

    Fighter* self_fp = self_gobj->user_data;
    Fighter* victim_fp = victim_gobj->user_data;

    func_8007DB58(self_gobj);
    func_8009750C(self_gobj);
    func_800DD168(self_gobj);

    self_fp->x1A5C = victim_gobj;
    self_fp->x1A58_interactedFighter = victim_gobj;
    self_fp->x221B_flag.bits.b5 = FALSE;
    self_fp->x221B_flag.bits.b7 = FALSE;
    self_fp->facing_direction = victim_fp->facing_direction;

    func_800DA824(victim_fp);
    func_8007DBCC(self_fp, 0 /*, missing_arg */);
    func_800DB368(victim_fp, self_fp);
    self_fp->cb.x21B0_callback_Accessory1 = &func_800DB464;
    func_8007D5D4(self_fp);
    Fighter_ActionStateChange_800693AC(self_gobj, 327, 0, 0, 0.0F, 1.0F, 0.0F);

    self_fp->x221E_flag.bits.b0 = TRUE;
    self_fp->x2220_flag.bits.b3 = TRUE;

    func_8007E2F4(self_fp, 511);
    func_8006EBA4(self_gobj);
    func_8007E2FC(self_gobj);
}
