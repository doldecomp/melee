#include "gm_1B0FB.h"

#include "gm_1B03.h"

#include "gm_1B03.static.h"

#include "gm/gm_1A3F.h"
#include "if/soundtest.h"

#include <melee/pl/forward.h>

#include <sysdolphin/baselib/controller.h>
#include <sysdolphin/baselib/memory.h>
#include <sysdolphin/baselib/random.h>
#include <melee/db/db.h>
#include <melee/gm/gm_unsplit.h>
#include <melee/gm/gmcamera.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/gm/gmresult.h>
#include <melee/gm/gmresultplayer.h>
#include <melee/gm/gmtou.h>
#include <melee/gm/gmvsmelee.h>
#include <melee/gm/types.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lbbgflash.h>
#include <melee/lb/lbcardgame.h>
#include <melee/lb/lbcardnew.h>
#include <melee/lb/lbdvd.h>
#include <melee/lb/lbmthp.h>
#include <melee/lb/lbsnap.h>
#include <melee/lb/lbtime.h>
#include <melee/lb/types.h>
#include <melee/mn/mngallery.h>
#include <melee/mn/mnsnap.h>
#include <melee/mn/types.h>
#include <melee/vi/types.h>
#include <melee/vi/vi0102.h>
#include <melee/vi/vi0402.h>
#include <melee/vi/vi0501.h>
#include <melee/vi/vi1101.h>
#include <melee/vi/vi1201v1.h>

/* 4D68A4 */ UNK_T gm_804D68A4[0x8 / 4];
/* 4D689C */ UNK_T gm_804D689C[0x8 / 4];
/* 4D6898 */ UNK_T gm_804D6898[0x4 / 4];
/* 4D6890 */ UNK_T gm_804D6890[0x8 / 4];
/* 4D688C */ UNK_T gm_804D688C[0x4 / 4];
/* 4D6884 */ UNK_T gm_804D6884[0x8 / 4];
/* 4D6880 */ UNK_T gm_804D6880[0x4 / 4];
/* 4D6878 */ u32 gm_804D6878[2];

GameScene gm_803DD888_Scenes[] = {
    {
        0,
        2,
        0,
        gm_801B0FB8,
        NULL,
        {
            GS_DEBUG_MENU,
            gm_804D68B0,
            NULL,
        },
    },
    { -1 },
};

void gm_801B0FB8(GameScene* arg0)
{
    struct DebugSoundTestData* data;

    data = gm_801A427C(arg0);
    data->x0 = &un_803F9FA4;
    data->x4 = 0;
    un_802FF7DC();
    un_802FF884("/audio");
}
