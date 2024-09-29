#ifndef GALE01_09CB40
#define GALE01_09CB40

#include <platform.h>

#include "ft/forward.h"
#include "ftCommon/forward.h"
#include "ftKirby/forward.h"

/* 09CF84 */ void ftCo_8009CF84(Fighter* fp);
/* 09D074 */ void ftCo_8009D074(Fighter* fp);
/* 09DC54 */ void ftCo_8009DC54(Fighter* fp);
/* 09E0A8 */ void ftCo_8009E0A8(HSD_GObj* gobj);
/* 09E0D4 */ void ftCo_UnloadDynamicBones(Fighter* fp);
/* 09E140 */ void ftCo_8009E140(Fighter* fp, bool);
/* 09E318 */ enum_t ftCo_8009E318(Fighter_GObj*, Fighter_Part, float);
/* 09E714 */ bool ftCo_8009E714(Fighter_GObj* gobj, Fighter_Part part,
                                int arg2, float x, float y, float arg5,
                                float arg6, float arg7);
/* 09E7B4 */ void ftCo_8009E7B4(Fighter* fp, u8*);
/* 09EAF8 */ void ftCo_8009EAF8(HSD_GObj* gobj);

/// @todo
/* 09CB40 */ static void ftCo_8009CB40(Fighter* fp, ssize_t bone_idx, bool,
                                       Fighter_Part);
/* 09D18C */ static void ftCo_8009D18C(Fighter* fp);
/* 09D2A4 */ static void ftCo_8009D2A4(Fighter* fp);
/* 09D3BC */ static void ftCo_8009D3BC(Fighter* fp);
/* 09D4D4 */ static void ftCo_8009D4D4(Fighter* fp);
/* 09D5EC */ static void ftCo_8009D5EC(Fighter* fp);
/* 09D704 */ static void ftCo_8009D704(Fighter* fp);
/* 09D81C */ static void ftCo_8009D81C(Fighter* fp);
/* 09D920 */ static void ftCo_8009D920(Fighter* fp);
/* 09DA38 */ static void ftCo_8009DA38(ftKb_Fighter* fp);
/* 09DB50 */ static void ftCo_8009DB50(Fighter* fp);
/* 09DD94 */ static void ftCo_8009DD94(Fighter_GObj*, bool);
/* 09E1D4 */ static HSD_JObj* ftCo_8009E1D4(HSD_JObj*, HSD_JObj*, HSD_JObj*);
/* 09E4A8 */ static void ftCo_8009E4A8(Fighter* fp);
/* 09E614 */ static void ftCo_8009E614(Fighter* fp);

#endif
