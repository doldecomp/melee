#include <melee/ft/chara/ftKoopa/ftkoopa.h>

#include <melee/it/itkind.h>

extern void func_800BC7E0(HSD_GObj*, HSD_GObj*);
extern void func_800BC8D4(HSD_GObj*, HSD_GObj*);
extern void func_800DE7C0(HSD_GObj*, s32, s32);
extern void func_800DE2A8(HSD_GObj*, HSD_GObj*);

extern const f32 lbl_804D9ADC; //1.0
extern const f32 lbl_804D9AD8; //0.0

void ftKoopa_OnDeath(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    ftKoopaAttributes* koopaAttr = fp->x2D4_specialAttributes;
    ftKoopaVars* ftVars;
    f32 unk = 0.0;
    f32 unk1 = 0.0;
    
    func_80074A4C(gobj, 0, 0);

    ftVars = (ftKoopaVars*)&fp->sa.koopa.x222C;
    
    fp->dmg.x18B0 = koopaAttr->x0;
    ftVars->x0 = koopaAttr->x10;
    ftVars->x4 = koopaAttr->x18;
}

void func_80132A64(HSD_GObj* gobj) {
    func_80134D78(gobj);
    return;
}

void ftKoopa_OnLoadForGKoopa(Fighter* fp) {
    PUSH_ATTRS(fp, ftKoopaAttributes);
}

void ftKoopa_OnLoad(HSD_GObj* gobj) {
    ftData* ftDataInfo; 
    void** items;
    Fighter* fp;
    
    fp = (Fighter*)gobj->user_data;
    ftDataInfo = fp->x10C_ftData;
    items = ftDataInfo->x48_items;
   
    PUSH_ATTRS(fp, ftKoopaAttributes);  

    func_8026B3F8(items[0], It_Kind_Koopa_Flame);

    fp->x2226_flag.bits.b1 = 1;
}

void func_80132B38(void) {
    return;
}

void ftKoopa_OnItemPickup(HSD_GObj* fighter_gobj, BOOL bool) {
    Fighter_OnItemPickup(fighter_gobj, bool, 1, 1);
}

void ftKoopa_OnItemInvisible(HSD_GObj* gobj) {
    Fighter_OnItemInvisible(gobj, 1);
}

void ftKoopa_OnItemVisible(HSD_GObj* gobj) {
    Fighter_OnItemVisible(gobj, 1);
}

void ftKoopa_OnItemDrop(HSD_GObj* gobj, BOOL bool1)
{
    Fighter_OnItemDrop(gobj, bool1, 1, 1);
}

void ftKoopa_LoadSpecialAttrs(HSD_GObj* gobj) {
    COPY_ATTRS(gobj, ftKoopaAttributes);
}

void ftKoopa_OnKnockbackEnter(HSD_GObj *gobj) {
    Fighter_OnKnockbackEnter(gobj, 1);
}

void ftKoopa_OnKnockbackExit(HSD_GObj *gobj) {
    Fighter_OnKnockbackExit(gobj, 1);
}

f32 func_80132DC0(HSD_GObj *gobj) {
    Fighter *fp = gobj->user_data;
    return ((ftKoopaAttributes*)fp->x2D4_specialAttributes)->x4C;
}

f32 func_80132DD0(HSD_GObj *gobj) {
    Fighter *fp = gobj->user_data;
    return ((ftKoopaAttributes*)fp->x2D4_specialAttributes)->x48;
}

f32 func_80132DE0(HSD_GObj *gobj) {
    Fighter *fp = gobj->user_data;
    return ((ftKoopaAttributes*)fp->x2D4_specialAttributes)->x44;
}

f32 func_80132DF0(HSD_GObj *gobj) {
    Fighter *fp = gobj->user_data;
    return ((ftKoopaAttributes*)fp->x2D4_specialAttributes)->x40;
}

f32 func_80132E00(HSD_GObj *gobj) {
    Fighter *fp = gobj->user_data;
    return ((ftKoopaAttributes*)fp->x2D4_specialAttributes)->x3C;
}

f32 func_80132E10(HSD_GObj *gobj) {
    Fighter *fp = gobj->user_data;
    return ((ftKoopaAttributes*)fp->x2D4_specialAttributes)->x34;
}

f32 func_80132E20(HSD_GObj *gobj) {
    Fighter *fp = gobj->user_data;
    return ((ftKoopaAttributes*)fp->x2D4_specialAttributes)->x38;
}

void func_80132E30(HSD_GObj *gobj) {
    Fighter *fp;
    HSD_GObj* temp;
    BOOL flag_set;

    fp = gobj->user_data;
    if (fp->x2210_ThrowFlags.b4 != 0) {
        fp->x2210_ThrowFlags.b4 = 0;
        flag_set = TRUE;
    } else {
        flag_set = FALSE;
    }
    if (flag_set != FALSE) {
        fp->x2C_facing_direction = -fp->x2C_facing_direction;
        fp->x234C_stateVar4 = 1;
    }
    if ((u32) fp->x2200_ftcmd_var0 != 0) {
        if (fp->x1A58_interactedFighter != 0) {
            temp = fp->x1A58_interactedFighter;
            func_8007E2F4(fp, 0);
            func_800DE2A8(gobj, temp);
            func_800DE7C0(temp, 0, 0);
            fp->x2200_ftcmd_var0 = 0;
        }
    }
}

void ftKoopa_SpecialS_StartAction(HSD_GObj *gobj)
{
    Fighter *fp = gobj->user_data;

    f64 unk = 0.0;

    fp->x2210_ThrowFlags.flags = 0;
    fp->x2200_ftcmd_var0 = 0;
    fp->x2344_stateVar2 = 0;
    fp->x234C_stateVar4 = 0;

    Fighter_ActionStateChange_800693AC(gobj, 0x15B, 0, 0, lbl_804D9AD8, lbl_804D9ADC, lbl_804D9AD8);

    func_8006EBA4(gobj);

    fp = gobj->user_data;

    func_8007E2D0(fp, 8, func_8013302C, NULL, func_800BC7E0);

    fp->x2340_stateVar1 = 0;
    fp->x2348_stateVar3 = 0;

    return;
}

void ftKoopa_SpecialAirS_StartAction(HSD_GObj *gobj)
{
    Fighter *fp = gobj->user_data;

    f64 unk = 0.0;

    fp->x2210_ThrowFlags.flags = 0;
    fp->x2200_ftcmd_var0 = 0;
    fp->x2344_stateVar2 = 0;
    fp->x234C_stateVar4 = 0;

    Fighter_ActionStateChange_800693AC(gobj, 0x161, 0, 0, lbl_804D9AD8, lbl_804D9ADC, lbl_804D9AD8);

    func_8006EBA4(gobj);

    fp = gobj->user_data;

    func_8007E2D0(fp, 8, func_801330E4, NULL, func_800BC8D4);

    fp->x2340_stateVar1 = 0;
    fp->x2348_stateVar3 = 0;

    return;
}

void func_8013302C(HSD_GObj *gobj)
{
    Fighter *fp = gobj->user_data;

    if((s32)fp->x2344_stateVar2 != 0) {
        Fighter_ActionStateChange_800693AC(gobj, 349, 0x80, 0, lbl_804D9AD8, lbl_804D9ADC, lbl_804D9AD8);
    } else {
        Fighter_ActionStateChange_800693AC(gobj, 348, 0x0, 0, lbl_804D9AD8, lbl_804D9ADC, lbl_804D9AD8);
    }
    fp->x2222_flag.bits.b2 = 1;
    func_8007E2F4(fp, 0x1FF);
    func_8007E2FC(gobj);
    fp->x2340_stateVar1 = 0;
    fp->x2200_ftcmd_var0 = 0;
    return;
}

void func_801330E4(HSD_GObj* gobj) {
    Fighter* fp;

    fp = gobj->user_data;
    if ((s32) fp->x2344_stateVar2 != 0) {
        Fighter_ActionStateChange_800693AC(gobj, 0x163, 0x80, 0, lbl_804D9AD8, lbl_804D9ADC, lbl_804D9AD8);
    } else {
        Fighter_ActionStateChange_800693AC(gobj, 0x162, 0, 0, lbl_804D9AD8, lbl_804D9ADC, lbl_804D9AD8);
    }
    fp->x2222_flag.bits.b2 = 1;
    func_8007E2F4(fp, 0x1FF);
    func_8007E2FC(gobj);
    fp->x2340_stateVar1 = 0;
    fp->x2200_ftcmd_var0 = 0;
}

void func_8013319C(HSD_GObj* gobj) {
    Fighter* fp;

    double unk = 0.0;

    fp = gobj->user_data;
    func_8007D5D4(fp);
    Fighter_ActionStateChange_800693AC(gobj, 0x161, 0x0C4C5088, 0, fp->x894_currentAnimFrame, lbl_804D9ADC, lbl_804D9AD8);
    fp = gobj->user_data;
    func_8007E2D0(fp, 8, func_801330E4, NULL, func_800BC8D4);
    fp->x2340_stateVar1 = 0;
    fp->x2348_stateVar3 = 0;
}

void func_8013322C(HSD_GObj* gobj) {
    Fighter* ft1;
    Fighter* ft2;

    double unk = 0.0;

    ft2 = gobj->user_data;
    func_8007D7FC(ft2);
    Fighter_ActionStateChange_800693AC(gobj, 0x15B, 0x0C4C5088, 0, ft2->x894_currentAnimFrame, lbl_804D9ADC, lbl_804D9AD8);
    ft1 = gobj->user_data;
    func_8007E2D0(ft1, 8, func_8013302C, NULL, func_800BC7E0);
    ft1->x2340_stateVar1 = 0;
    ft1->x2348_stateVar3 = 0;
    ft2->x2340_stateVar1 = 0;
    ft2->x2200_ftcmd_var0 = 0;
}

void func_801332C4(HSD_GObj* gobj) {
    HSD_GObj* temp_r31;
    Fighter* fp;

    fp = gobj->user_data;
    temp_r31 = fp->x1A58_interactedFighter;
    func_8007D5D4(fp);
    if (temp_r31 != 0) {
        func_800DC920(gobj, temp_r31);
        func_800CC730(temp_r31);
    }
    func_800CC730(gobj);
}

void func_80133324(HSD_GObj* gobj) {
    Fighter* fp;

    fp = gobj->user_data;
    func_8007D7FC(fp);
    Fighter_ActionStateChange_800693AC(gobj, 0x15C, 0x0C4C5088, 0, fp->x894_currentAnimFrame, lbl_804D9ADC, lbl_804D9AD8);
    func_8007E2F4(fp, 0x1FF);
    func_8007E2FC(gobj);
}

void func_80133398(HSD_GObj* gobj) {
    HSD_GObj* unk_gobj;
    Fighter* fp;

    fp = gobj->user_data;
    unk_gobj = fp->x1A58_interactedFighter;
    func_8007D5D4(fp);
    if (unk_gobj != 0) {
        func_800DC920(gobj, unk_gobj);
        func_800CC730(unk_gobj);
    }
    func_800CC730(gobj);
}

void func_801333F8(HSD_GObj* gobj) {
    Fighter* fp;

    fp = gobj->user_data;
    func_8007D7FC(fp);
    Fighter_ActionStateChange_800693AC(gobj, 0x15E, 0x044C1080, 0, fp->x894_currentAnimFrame, lbl_804D9ADC, lbl_804D9AD8);
    func_8007E2F4(fp, 0x1FF);
    func_8007E2FC(gobj);
    func_8006F0FC(gobj, lbl_804D9AD8);
    fp->x2340_stateVar1 = 0;
    fp->x2200_ftcmd_var0 = 0;
}

void func_80133484(HSD_GObj* gobj) {
    HSD_GObj* unk_gobj;
    Fighter* fp;

    fp = gobj->user_data;
    unk_gobj = fp->x1A58_interactedFighter;
    func_8007D5D4(fp);
    if (unk_gobj != 0) {
        func_800DC920(gobj, unk_gobj);
        func_800CC730(unk_gobj);
    }
    func_800CC730(gobj);
}

void func_801334E4(HSD_GObj* gobj) {
    Fighter* fp;

    u32 x = 0;
    
    fp = gobj->user_data;
    
    
    func_8007D7FC(fp);
    
    if ((s32) fp->x234C_stateVar4 != 0) {
        fp->x2C_facing_direction = -fp->x2C_facing_direction;
    }
    Fighter_ActionStateChange_800693AC(gobj, 0x15F, 0x0C4C5088, 0, fp->x894_currentAnimFrame, lbl_804D9ADC, lbl_804D9AD8);
    
    if ((s32) fp->x234C_stateVar4 != 0) {
        fp->x2C_facing_direction = -fp->x2C_facing_direction;
    }
    if (fp->x1A58_interactedFighter != 0) {
        func_800BCE64(fp->x1A58_interactedFighter, 0x119);
    }
    func_8007E2F4(fp, 0x1FF);
    func_8007E2FC(gobj);
}

void func_8013359C(HSD_GObj* gobj) {
    Fighter* fp;

    fp = gobj->user_data;
    func_8007D7FC(fp);
    if ((s32) fp->x234C_stateVar4 != 0) {
        fp->x2C_facing_direction = -fp->x2C_facing_direction;
    }
    Fighter_ActionStateChange_800693AC(gobj, 0x160, 0x0C4C5088, 0, fp->x894_currentAnimFrame, lbl_804D9ADC, lbl_804D9AD8);
    if ((s32) fp->x234C_stateVar4 != 0) {
        fp->x2C_facing_direction = -fp->x2C_facing_direction;
    }
    if (fp->x1A58_interactedFighter != 0U) {
        func_800BCE64(fp->x1A58_interactedFighter, 0x11A);
    }
    func_8007E2F4(fp, 0x1FF);
    func_8007E2FC(gobj);
}

void func_80133654(HSD_GObj* gobj) {
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        func_8008A2BC(gobj);
    }
}

void func_80133690(HSD_GObj* gobj) {
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        func_800CC730(gobj);
    }
}

void func_801336CC(HSD_GObj* gobj) {
    Fighter* ft_temp;
    Fighter* fp;

    ftKoopaAttributes* koopaAttr;

    double unk = 0.0;
    double unk1 = 0.0;

    fp = ft_temp = gobj->user_data;
    koopaAttr = (ftKoopaAttributes *) fp->x2D4_specialAttributes;
    if (((u32) fp->x2200_ftcmd_var0 != 0) && ((s32) fp->x2344_stateVar2 != 0)) {
        func_8007ABD0(&fp->x914[0], koopaAttr->x2C, gobj);
        fp->x2200_ftcmd_var0 = 0;
    }
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        if ((s32) fp->x2340_stateVar1 != 0) {
            fp->x2344_stateVar2 = 1;
            ft_temp = gobj->user_data;
            if ((s32) ft_temp->x2344_stateVar2 != 0) {
                Fighter_ActionStateChange_800693AC(gobj, 0x15D, 0x80, 0, lbl_804D9AD8, lbl_804D9ADC, lbl_804D9AD8);
            } else {
                Fighter_ActionStateChange_800693AC(gobj, 0x15C, 0, 0, lbl_804D9AD8, lbl_804D9ADC, lbl_804D9AD8);
            }
            ft_temp->x2222_flag.bits.b2 = 1;
            func_8007E2F4(ft_temp, 0x1FF);
            func_8007E2FC(gobj);
            ft_temp->x2340_stateVar1 = 0;
            ft_temp->x2200_ftcmd_var0 = 0;
            func_800BC9C8(fp->x1A58_interactedFighter);
            return;
        }
        fp = gobj->user_data;
        Fighter_ActionStateChange_800693AC(gobj, 0x15E, 0x80080, 0, fp->x894_currentAnimFrame, lbl_804D9ADC, lbl_804D9AD8);
        func_8006F0FC(gobj, lbl_804D9AD8);
        fp->x2340_stateVar1 = 0;
        fp->x2200_ftcmd_var0 = 0;
        func_8007E2F4(fp, 0x1FF);
    }
}
