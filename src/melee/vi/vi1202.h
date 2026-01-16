#ifndef GALE01_32110C
#define GALE01_32110C

#include <placeholder.h>

#include <baselib/forward.h>

typedef struct vi1202_UnkStruct vi1202_UnkStruct;

/// Configuration for crowd/announcer reactions during matches.
///
/// Evidence for "Crowd" naming:
/// - Symbol names from UnclePunch's Training Mode map (Feb 2019)
/// - Functions at 0x80321900+ named CrowdSFXManager_* in that map
/// - Audio function 0x8002411C named lbAudio_PlayCrowdSFX
/// - Code triggers match wiki descriptions of crowd gasps/cheers
typedef struct CrowdConfig {
    /// Knockback thresholds for crowd gasp intensity (cat 1/2/3)
    /* 0x00 */ f32 kb_threshold_low;
    /* 0x04 */ f32 kb_threshold_mid;
    /* 0x08 */ f32 kb_threshold_high;
    /// Angle range and multiplier for crowd reaction modifier
    /* 0x0C */ f32 angle_min;
    /* 0x10 */ f32 angle_max;
    /* 0x14 */ f32 angle_mult;
    /* 0x18 */ f32 x18;
    /* 0x1C */ s32 x1C;
    /// Cheer/gasp timing limits
    /* 0x20 */ s32 cheer_limit;
    /* 0x24 */ s32 x24;
    /* 0x28 */ s32 max_gasp_count;
    /// Horizontal margin from blast zone for out-of-bounds check
    /* 0x2C */ f32 horiz_margin;
    /// Y-position thresholds for recovery gasp intensity (cat 3/2/1)
    /* 0x30 */ f32 recovery_y_high;
    /* 0x34 */ f32 recovery_y_mid;
    /* 0x38 */ f32 recovery_y_low;
    /// Fighter count threshold to trigger blast zone proximity gasp
    /* 0x3C */ s32 fighters_near_blastzone;
    /// Y-offset added to blast zone bottom for proximity check
    /* 0x40 */ f32 blastzone_y_offset;
} CrowdConfig;

/* 4D6500 */ extern CrowdConfig* gCrowdConfig;

/* 32110C */ void un_8032110C(HSD_GObj*);
/* 321130 */ void un_80321130(HSD_GObj*);
/* 321154 */ void un_80321154(HSD_GObj*);
/* 321178 */ void un_80321178(void);
/* 321294 */ void vi1202_RunFrame(HSD_GObj*);
/* 321300 */ void vi1202_OnEnter(UNK_T);
/* 3218E0 */ void vi1202_OnFrame(void);
/* 321900 */ void un_80321900(void);
/* 321950 */ void un_80321950(vi1202_UnkStruct*);
/* 3219AC */ void fn_803219AC(HSD_GObj*);
/* 321A00 */ void un_80321A00(HSD_GObj*);
/* 321AF4 */ void un_80321AF4(HSD_GObj* gobj);
/* 321BF8 */ void un_80321BF8(int);
/* 321C28 */ void un_80321C28(void);
/* 321C70 */ void un_80321C70(void);
/* 321CA4 */ void un_80321CA4(s32);
/* 321CE8 */ void un_80321CE8(void);
/* 321D30 */ void un_80321D30(u32, f32);
/* 321EBC */ bool un_80321EBC(u32, f32);
/* 32201C */ bool un_8032201C(u32, s32);
/* 322178 */ void un_80322178(int);
/* 322258 */ bool un_80322258(float);
/* 322298 */ s32 un_80322298(float);
/* 3222EC */ float un_803222EC(float mag, float angle);
/* 322314 */ void un_80322314(void);
/* 32233C */ void un_8032233C(u32, u32);
/* 3224DC */ bool un_803224DC(s32 spawn_id, f32 pos_x, f32 kb_mag);
/* 322598 */ int un_80322598(int, float);

#endif
