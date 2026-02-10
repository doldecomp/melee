#include "mnruleplus.h"

#include "platform.h"

#include "baselib/gobj.h"
#include "baselib/gobjgxlink.h"
#include "baselib/gobjobject.h"
#include "baselib/gobjproc.h"
#include "baselib/gobjuserdata.h"
#include "baselib/jobj.h"
#include "baselib/memory.h"
#include "gm/gmmain_lib.h"
#include "gm/types.h"

#include "mn/forward.h"

#include "mn/mnmain.h"
#include "sc/types.h"

extern StaticModelDesc MenMainConRl_Top;
extern StaticModelDesc MenMainCursorRl_Top;
extern StaticModelDesc MenMainCursorTr01_Top;
extern StaticModelDesc MenMainCursorTr02_Top;
extern StaticModelDesc MenMainCursorTr03_Top;
extern StaticModelDesc MenMainCursorTr04_Top;
extern StaticModelDesc MenMainNmRl_Top;
extern MenuKindData* mn_803EB6B0;
extern HSD_GObj* mn_804D6BE0;

static mn_803ED1D0_t mn_803ED1D0 = { { 3, 4, 5, 6, 7, 8, 9 },
                                     { 7, 2, 2, 2, 2, 0 },
                                     { 20.0f, 21.0f, 22.0f, 23.0f, 24.0f,
                                       25.0f, 26.0f, 27.0f, 28.0f, 29.0f,
                                       30.0f, 31.0f },
                                     { 0.0f, 99.0f, 0.0f },
                                     { 200.0f, 399.0f, 200.0f },
                                     { 100.0f, 124.0f, -0.1f },
                                     {
                                         125.0f,
                                         149.0f,
                                         -0.1f,
                                     },
                                     {
                                         150.0f,
                                         174.0f,
                                         -0.1f,
                                     },
                                     {
                                         175.0f,
                                         199.0f,
                                         -0.1f,
                                     },
                                     {
                                         0.0f,
                                         99.0f,
                                         60.0f,
                                     } };

static s32 mn_804DBE48 = 0x02030506;

/// #fn_8023201C

/// #mn_80232458

/// #mn_802324E4

/// #mn_80232660

/// #mn_802327A4

/// #mn_80232D4C

/// #fn_80232F44

/// HSD_GObj* mn_80233218(enum MenuState state)
/// {
///     ?* sp9C;
///     u32* sp98;
///     HSD_GObj* sp94;
///     u8 sp90;
///     HSD_JObj* sp44;
///     s16 sp3E;
///     s16 sp3C;
///     s16 sp3A;
///     s16 sp38;
///     s16 sp36;
///     s16 sp34;
///     s16 sp32;
///     s16 sp30;
///     s16 sp2E;
///     s16 sp2C;
///     s16 sp2A;
///     s16 sp28;
///     s16 sp26;
///     s16 sp24;
///     s16 sp22;
///     u16 sp20;
///     s32 sp14;
///     ?* var_r28_3;
///     GameRules* temp_ret_2;
///     HSD_GObj* temp_r3;
///     HSD_JObj* temp_r19;
///     HSD_JObj* temp_r21;
///     HSD_JObj* temp_r3_2;
///     HSD_JObj* temp_r3_4;
///     HSD_JObj* temp_r3_5;
///     HSD_JObj* temp_r3_6;
///     HSD_Text* temp_r3_7;
///     HSD_Text* temp_r3_8;
///     MenuRulesPlusData* temp_r3_3;
///     MenuRulesPlusData* temp_ret;
///     MenuRulesPlusData* var_r26;
///     f32 var_f1;
///     f32* var_r29;
///     f32* var_r29_2;
///     s32 var_ctr;
///     s32 var_r0;
///     s32 var_r24;
///     s32 var_r27;
///     s32 var_r28;
///     s32 var_r28_2;
///     s32 var_r29_4;
///     s32 var_r31;
///     s32 var_r31_3;
///     s32* var_r31_4;
///     u16 var_r3;
///     u16* var_r20;
///     u16* var_r24_2;
///     u16* var_r4;
///     u8 temp_r0;
///     u8 temp_r14;
///     u8 temp_r22;
///     u8 temp_r4;
///     u8 var_r19_2;
///     u8 var_r31_2;
///     void* var_r19;
///     void* var_r29_3;
///     void* var_r4_2;

///     var_r29 = saved_reg_r29;
///     var_r3 = 0x10;
///     temp_r22 = (u8) mn_804A04F0.hovered_selection;
///     sp20 = 0;
///     sp22 = 1;
///     sp24 = 2;
///     sp26 = 3;
///     sp28 = 4;
///     sp2A = 5;
///     sp90 = mn_803EB6B0.unk138;
///     sp2C = 6;
///     sp2E = 7;
///     sp30 = 8;
///     sp32 = 9;
///     sp34 = 0xA;
///     sp36 = 0xB;
///     sp38 = 0xC;
///     sp3A = 0xD;
///     sp3C = 0xE;
///     sp3E = 0xF;
///     var_r4 = &sp20 + 0x20;
///     var_ctr = 0x11 - 0x10;
///     if (0x10 < 0x11) {
///         do {
///             *var_r4 = var_r3;
///             var_r4 += 2;
///             var_r3 += 1;
///             var_ctr -= 1;
///         } while (var_ctr != 0);
///     }
///     temp_r3 = GObj_Create(6U, 7U, 0x80U);
///     sp94 = temp_r3;
///     mn_804D6BE0 = sp94;
///     temp_r3_2 = HSD_JObjLoadJoint(MenMainConRl_Top.unk0);
///     HSD_GObjObject_80390A70(temp_r3, HSD_GObj_804D7849, temp_r3_2);
///     GObj_SetupGXLink(temp_r3, HSD_GObj_JObjCallback, 4U, 0x80U);
///     HSD_GObjProc_8038FD54(temp_r3, fn_80232F44, 0U);
///     HSD_JObjAddAnimAll(temp_r3_2, MenMainConRl_Top.unk4,
///     MenMainConRl_Top.unk8, MenMainConRl_Top.unkC);
///     HSD_JObjReqAnimAll(temp_r3_2, 0.0f);
///     HSD_JObjAnimAll(temp_r3_2);
///     temp_ret = HSD_MemAlloc(0xE0);
///     temp_r3_3 = temp_ret;
///     if (temp_r3_3 == NULL) {
///         OSReport(&(mn_803ED1D0 + 0x138)->unk0, (u32) (u64) temp_ret,
///         (bitwise f32) temp_ret);
///         __assert(&(mn_803ED1D0 + 0x150)->unk0, 0x3DFU, mn_803ED1D0 +
///         0x160);
///     }
///     GObj_InitUserData(sp94, 0U, HSD_Free, temp_r3_3);
///     temp_r3_3->menu_kind = mn_804A04F0.cur_menu;
///     temp_r3_3->hovered_selection = (u8) mn_804A04F0.hovered_selection;
///     temp_r3_3->rule_values.time_limit =
///     gmMainLib_8015CC34()->stock_time_limit;
///     temp_r3_3->rule_values.friendly_fire =
///     gmMainLib_8015CC34()->friendly_fire; temp_r3_3->rule_values.pause =
///     gmMainLib_8015CC34()->pause; temp_r3_3->rule_values.score =
///     gmMainLib_8015CC34()->score_display; temp_ret_2 = gmMainLib_8015CC34();
///     var_f1 = (bitwise f32) temp_ret_2;
///     var_r24 = 0;
///     temp_r3_3->rule_values.sd_penalty = temp_ret_2->unk_xc;
///     var_r26 = temp_r3_3;
///     temp_r3_3->state = (u8) state;
///     temp_r3_3->description = NULL;
///     do {
///         var_f1 = (bitwise f32) lb_80011E24(temp_r3_2, var_r26 + 0xC,
///         var_r24, -1, var_f1); var_r24 += 1; var_r26 += 4;
///     } while (var_r24 < 0xA);
///     sp98 = &mn_804A04F0.confirmed_option;
///     *sp98 = (u8) (temp_r3_3 + temp_r3_3->hovered_selection)->unk2;
///     if ((u8) state != 0) {
///         temp_r0 = temp_r3_3->state;
///         temp_r19 = temp_r3_3->option_tree[2];
///         switch ((s32) temp_r0) {                    /* irregular */
///         case 2:
///             break;
///         case 1:
///             var_r29 = mn_803ED1D0 + 0xE8;
///             break;
///         case 3:
///             var_r29 = mn_803ED1D0 + 0xF4;
///             break;
///         }
///         HSD_JObjReqAnim(temp_r19, *var_r29);
///         HSD_JObjAnim(temp_r19);
///     }
///     var_r27 = 0;
///     var_r19 = temp_r3_3 + (0 * 0x1C);
///     sp9C = &MenMainCursorTr04_Top;
///     var_r24_2 = &mn_803ED1D0[5].unk1;
///     var_r20 = &mn_803ED1D0[9].unk1;
/// loop_85:
///     if (var_r27 < (s32) sp90) {
///         var_r28 = 0;
///         var_r31 = 0;
/// loop_22:
///         if (var_r31 < (s32) (u8) var_r27) {
///             if (mn_80231F80((u8) var_r31) != 0) {
///                 var_r28 += 1;
///             }
///             var_r31 += 1;
///             goto loop_22;
///         }
///         var_r28_2 = 0;
///         var_r31_2 = 0;
///         temp_r21 = *(temp_r3_3 + ((*(mn_803ED1D0 + ((var_r28 * 2) & 0x1FE))
///         * 4) + 0xC)); do {
///             if (mn_80231F80(var_r31_2) != 0) {
///                 var_r28_2 += 1;
///             }
///             var_r31_2 += 1;
///         } while ((s32) var_r31_2 < 6);
///         HSD_JObjReqAnim(temp_r21, (f32) var_r28_2);
///         HSD_JObjAnim(temp_r21);
///         if ((gm_801A4310() == 0x1B) && ((u8) var_r27 == 1)) {
///             var_r0 = 0;
///         } else if ((u8) var_r27 == 3) {
///             if (gmMainLib_8015EE0C() != 0) {
///                 var_r0 = 1;
///             } else {
///                 var_r0 = 0;
///             }
///         } else if ((u8) var_r27 == 5) {
///             if (gmMainLib_8015EE44() != 0) {
///                 var_r0 = 1;
///             } else {
///                 var_r0 = 0;
///             }
///         } else {
///             var_r0 = 1;
///         }
///         if (var_r0 != 0) {
///             var_r28_3 = &MenMainCursorRl_Top;
///             temp_r3_4 = HSD_JObjLoadJoint(MenMainCursorRl_Top.unk0);
///             HSD_JObjAddAnimAll(temp_r3_4, MenMainCursorRl_Top.unk4,
///             MenMainCursorRl_Top.unk8, MenMainCursorRl_Top.unkC);
///             HSD_JObjReqAnimAll(temp_r3_4, 0.0f);
///             HSD_JObjAnimAll(temp_r3_4);
///             lb_8001204C(temp_r3_4, &sp44, &sp20, 0x11);
///             HSD_JObjReqAnim(sp60, *(var_r20 + (((u32) CLZ(var_r27 -
///             temp_r22) >> 3U) & 0x1FFFFFFC))); HSD_JObjAnim(sp60); if ((s32)
///             temp_r22 != var_r27) {
///                 HSD_JObjSetFlagsAll(sp84, 0x10U);
///             }
///             if (((s32) temp_r22 != var_r27) || (var_r27 == 5)) {
///                 HSD_JObjSetFlagsAll(sp78, 0x10U);
///             } else {
///                 HSD_JObjReqAnimAll(sp78, mn_803ED1D0->unk58);
///             }
///             if (((s32) temp_r22 != var_r27) || (var_r27 != 5)) {
///                 HSD_JObjSetFlagsAll(sp64, 0x10U);
///             }
///             if (var_r27 == 5) {
///                 var_r29_2 = mn_803ED1D0 + ((temp_r22 == var_r27) * 0xC) +
///                 0x7C;
///             } else {
///                 var_r29_2 = mn_803ED1D0 + ((temp_r22 == var_r27) * 0xC) +
///                 0x64;
///             }
///             HSD_JObjReqAnimAll(sp4C, *var_r29_2);
///             HSD_JObjAnimAll(sp4C);
///             HSD_JObjAddChild(temp_r21, temp_r3_4);
///             if (var_r27 != 5) {
///                 switch (var_r27) {                  /* switch 1; irregular
///                 */ case 0:                             /* switch 1 */
///                     var_r28_3 = &MenMainCursorTr01_Top;
///                     break;
///                 case 1:                             /* switch 1 */
///                     var_r28_3 = &MenMainCursorTr02_Top;
///                     break;
///                 default:                            /* switch 1 */
///                     var_r28_3 = &MenMainCursorTr03_Top;
///                     break;
///                 case 4:                             /* switch 1 */
///                     var_r28_3 = sp9C;
///                     break;
///                 }
///                 temp_r3_5 = HSD_JObjLoadJoint(var_r28_3->unk0);
///                 HSD_JObjAddAnimAll(temp_r3_5, var_r28_3->unk4,
///                 var_r28_3->unk8, var_r28_3->unkC);
///                 HSD_JObjReqAnimAll(temp_r3_5, 0.0f);
///                 HSD_JObjAnimAll(temp_r3_5);
///                 var_r31_3 = 0;
///                 var_r29_3 = var_r19;
/// loop_66:
///                 if (var_r31_3 < (s32) *var_r24_2) {
///                     lb_80011E24(temp_r3_5, var_r29_3 + 0x34, var_r31_3,
///                     -1); var_r29_3 += 4; var_r31_3 += 1; goto loop_66;
///                 }
///                 if (var_r27 != 0) {
///                     if ((var_r27 >= 0) && (var_r27 < 5)) {
///                         temp_r4 = *(temp_r3_3 + (var_r27 + 2));
///                         if (((u8) var_r27 != 1) && ((u8) var_r27 != 2) &&
///                         ((u8) var_r27 != 3) && ((u8) var_r27 != 4)) {
///                             var_r4_2 = NULL;
///                         } else if (temp_r4 == 0) {
///                             var_r4_2 = mn_803ED1D0 + ((mn_803ED1D0 +
///                             ((var_r27 * 2) & 0x1FE))->unk119 * 0xC) + 0xA0;
///                         } else {
///                             var_r4_2 = mn_803ED1D0 + ((temp_r4 - 1) * 0xC)
///                             + 0xA0;
///                         }
///                         HSD_JObjReqAnimAll(temp_r3_5, var_r4_2->unk4);
///                         HSD_JObjAnimAll(temp_r3_5);
///                     }
///                 } else {
///                     var_r31_4 = &sp14;
///                     var_r29_4 = 0;
///                     sp14 = mn_804DBE48;
///                     do {
///                         temp_r3_6 =
///                         HSD_JObjLoadJoint(MenMainNmRl_Top.unk0);
///                         HSD_JObjAddAnimAll(temp_r3_6, MenMainNmRl_Top.unk4,
///                         MenMainNmRl_Top.unk8, MenMainNmRl_Top.unkC);
///                         HSD_JObjAddChild(*(temp_r3_3 + ((*var_r31_4 * 4) +
///                         0x34)), temp_r3_6); var_r29_4 += 1; var_r31_4 += 1;
///                     } while (var_r29_4 < 4);
///                     mn_802324E4(temp_r3_3->rule_values.time_limit,
///                     temp_r3_3);
///                 }
///                 HSD_JObjAddChild(temp_r21, temp_r3_5);
///             }
///         }
///         var_r20 += 8;
///         var_r19 += 0x1C;
///         var_r24_2 += 2;
///         var_r27 += 1;
///         goto loop_85;
///     }
///     temp_r3_7 = temp_r3_3->description;
///     temp_r14 = *sp98;
///     if (temp_r3_7 != NULL) {
///         HSD_SisLib_803A5CC4(temp_r3_7);
///         temp_r3_3->description = NULL;
///     }
///     if (((s32) temp_r22 == 0) || ((s32) temp_r22 == 5)) {
///         var_r19_2 = mn_803ED1D0[temp_r22].unk124;
///     } else {
///         var_r19_2 = (&mn_803ED1D0[temp_r22] + temp_r14)->unk124;
///     }
///     temp_r3_8 = HSD_SisLib_803A5ACC(0, 1, -9.5f, 8.0f, 17.0f,
///     364.68332f, 76.77544f); temp_r3_3->description = temp_r3_8;
///     temp_r3_8->font_size.x = 0.0521f;
///     temp_r3_8->font_size.y = 0.0521f;
///     HSD_SisLib_803A6368(temp_r3_8, (s32) var_r19_2);
///     return sp94;
/// }

void mn_802339FC(void)
{
    MenuState state;
    HSD_GObjProc* think;

    mn_804A04F0.prev_menu = mn_804A04F0.cur_menu;

    switch (mn_804A04F0.prev_menu) {
    case MENU_KIND_RULES_STAGE:
        mn_804A04F0.cur_menu = MENU_KIND_RULES_EXTRA;
        state = MENU_STATE_EXIT_TO;
        mn_804A04F0.hovered_selection = 5;
        break;
    default:
        mn_804A04F0.cur_menu = MENU_KIND_RULES_EXTRA;
        state = MENU_STATE_ENTER_TO;
        mn_804A04F0.hovered_selection = 0;
        break;
    }

    mn_80233218(state);
    think = HSD_GObjProc_8038FD54(GObj_Create(0U, 1U, 0x80U),
                                  (void (*)(HSD_GObj*)) fn_8023201C, 0U);
    think->flags_3 = HSD_GObj_804D783C;
}
