#include "it_2725.h"

#include "inlines.h"
#include "it_266F.h"

#include <platform.h>

#include "cm/camera.h"
#include "db/db.h"
#include "ef/efasync.h"
#include "ef/efsync.h"
#include "ft/fighter.h"
#include "ft/ft_0892.h"
#include "ft/ft_0C31.h"
#include "ft/ftdevice.h"
#include "ft/ftlib.h"
#include "gm/gm_unsplit.h"
#include "gr/grlib.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"

#include "it/forward.h"

#include "it/it_26B1.h"
#include "it/itcoll.h"
#include "it/items/it_27CF.h"
#include "it/items/it_2ADA.h"
#include "it/items/it_2E5A.h"
#include "it/items/it_2E6A.h"
#include "it/items/it_2F28.h"
#include "it/items/itarwinglaser.h"
#include "it/items/itbat.h"
#include "it/items/itbombhei.h"
#include "it/items/itbox.h"
#include "it/items/itcapsule.h"
#include "it/items/itcerebi.h"
#include "it/items/itchicorita.h"
#include "it/items/itchicoritaleaf.h"
#include "it/items/itclimbersblizzard.h"
#include "it/items/itclimbersice.h"
#include "it/items/itclimbersstring.h"
#include "it/items/itclinkmilk.h"
#include "it/items/itcoin.h"
#include "it/items/itcrazyhandbomb.h"
#include "it/items/itdkinoko.h"
#include "it/items/itdosei.h"
#include "it/items/itdrmariopill.h"
#include "it/items/itegg.h"
#include "it/items/itentei.h"
#include "it/items/itevyoshiegg.h"
#include "it/items/itfflower.h"
#include "it/items/itfflowerflame.h"
#include "it/items/itfire.h"
#include "it/items/itflipper.h"
#include "it/items/itfoods.h"
#include "it/items/itfoxblaster.h"
#include "it/items/itfoxillusion.h"
#include "it/items/itfoxlaser.h"
#include "it/items/itfreeze.h"
#include "it/items/itfreezer.h"
#include "it/items/itfushigibana.h"
#include "it/items/itgamewatchbreath.h"
#include "it/items/itgamewatchchef.h"
#include "it/items/itgamewatchfire.h"
#include "it/items/itgamewatchgreenhouse.h"
#include "it/items/itgamewatchjudge.h"
#include "it/items/itgamewatchmanhole.h"
#include "it/items/itgamewatchpanic.h"
#include "it/items/itgamewatchparachute.h"
#include "it/items/itgamewatchrescue.h"
#include "it/items/itgamewatchturtle.h"
#include "it/items/itgreatfoxlaser.h"
#include "it/items/itgshell.h"
#include "it/items/ithammer.h"
#include "it/items/ithammerhead.h"
#include "it/items/itharisen.h"
#include "it/items/ithassam.h"
#include "it/items/itheart.h"
#include "it/items/itheiho.h"
#include "it/items/ithinoarashi.h"
#include "it/items/ithitodeman.h"
#include "it/items/ithouou.h"
#include "it/items/itkabigon.h"
#include "it/items/itkamex.h"
#include "it/items/itkinoko.h"
#include "it/items/itkirbycutterbeam.h"
#include "it/items/itkirbygamewatchchefpan.h"
#include "it/items/itkirbyhammer.h"
#include "it/items/itkireihana.h"
#include "it/items/itklap.h"
#include "it/items/itkoopaflame.h"
#include "it/items/itkusudama.h"
#include "it/items/itkyasarin.h"
#include "it/items/itkyasarinegg.h"
#include "it/items/itleadead.h"
#include "it/items/itlgun.h"
#include "it/items/itlgunbeam.h"
#include "it/items/itlgunray.h"
#include "it/items/itlikelike.h"
#include "it/items/itlinkarrow.h"
#include "it/items/itlinkbomb.h"
#include "it/items/itlinkboomerang.h"
#include "it/items/itlinkbow.h"
#include "it/items/itlinkhookshot.h"
#include "it/items/itlipstick.h"
#include "it/items/itlipstickspore.h"
#include "it/items/itlizardon.h"
#include "it/items/itlucky.h"
#include "it/items/itlugia.h"
#include "it/items/itluigifireball.h"
#include "it/items/itmaril.h"
#include "it/items/itmariocape.h"
#include "it/items/itmariofireball.h"
#include "it/items/itmarumine.h"
#include "it/items/itmasterhandbullet.h"
#include "it/items/itmasterhandlaser.h"
#include "it/items/itmatadogas.h"
#include "it/items/itmato.h"
#include "it/items/itmetalb.h"
#include "it/items/itmetamon.h"
#include "it/items/itmew.h"
#include "it/items/itmewtwodisable.h"
#include "it/items/itmewtwoshadowball.h"
#include "it/items/itmsbomb.h"
#include "it/items/itnessbat.h"
#include "it/items/itnesspkfire.h"
#include "it/items/itnesspkfirepillar.h"
#include "it/items/itnesspkflush.h"
#include "it/items/itnesspkflushexplode.h"
#include "it/items/itnesspkthunderball.h"
#include "it/items/itnesspkthundertrail.h"
#include "it/items/itnessyoyo.h"
#include "it/items/itnokonoko.h"
#include "it/items/itoctarock.h"
#include "it/items/itoctarockstone.h"
#include "it/items/itoldkuri.h"
#include "it/items/itoldottosea.h"
#include "it/items/itparasol.h"
#include "it/items/itpatapata.h"
#include "it/items/itpeachexplode.h"
#include "it/items/itpeachparasol.h"
#include "it/items/itpeachtoad.h"
#include "it/items/itpeachtoadspore.h"
#include "it/items/itpeachturnip.h"
#include "it/items/itpikachuthunder.h"
#include "it/items/itpikachutjoltair.h"
#include "it/items/itpikachutjoltground.h"
#include "it/items/itpippi.h"
#include "it/items/itporygon2.h"
#include "it/items/itrabbitc.h"
#include "it/items/itraikou.h"
#include "it/items/itrshell.h"
#include "it/items/itsamusbomb.h"
#include "it/items/itsamuschargeshot.h"
#include "it/items/itsamusgrapple.h"
#include "it/items/itsamusmissile.h"
#include "it/items/itscball.h"
#include "it/items/itseakchain.h"
#include "it/items/itseakneedleheld.h"
#include "it/items/itseakneedlethrown.h"
#include "it/items/itseakvanish.h"
#include "it/items/itsonans.h"
#include "it/items/itspycloak.h"
#include "it/items/itsscope.h"
#include "it/items/itsscopebeam.h"
#include "it/items/itstar.h"
#include "it/items/itstarrod.h"
#include "it/items/itstarrodstar.h"
#include "it/items/itsuikun.h"
#include "it/items/itsword.h"
#include "it/items/ittaru.h"
#include "it/items/ittarucann.h"
#include "it/items/itthunder.h"
#include "it/items/ittincle.h"
#include "it/items/ittogepy.h"
#include "it/items/ittomato.h"
#include "it/items/ittools.h"
#include "it/items/ittosakinto.h"
#include "it/items/itunknown.h"
#include "it/items/itwhispyapple.h"
#include "it/items/itwhitebea.h"
#include "it/items/itwstar.h"
#include "it/items/ityoshieggthrow.h"
#include "it/items/ityoshistar.h"
#include "it/items/itzeldadinfire.h"
#include "it/items/itzeldadinfireexplode.h"
#include "it/items/itzgshell.h"
#include "it/items/itzrshell.h"
#include "it/types.h"
#include "items/it_27CF.h"
#include "items/itbat.h"
#include "items/itbombhei.h"
#include "items/itbox.h"
#include "items/itcapsule.h"
#include "items/itcoin.h"
#include "items/itdkinoko.h"
#include "items/itdosei.h"
#include "items/itegg.h"
#include "items/itevyoshiegg.h"
#include "items/itfflower.h"
#include "items/itfflowerflame.h"
#include "items/itflipper.h"
#include "items/itfoods.h"
#include "items/itfoxillusion.h"
#include "items/itfreeze.h"
#include "items/itgshell.h"
#include "items/ithammer.h"
#include "items/ithammerhead.h"
#include "items/itharisen.h"
#include "items/itheart.h"
#include "items/itkinoko.h"
#include "items/itkusudama.h"
#include "items/itlgun.h"
#include "items/itlgunbeam.h"
#include "items/itlgunray.h"
#include "items/itlinkarrow.h"
#include "items/itlinkboomerang.h"
#include "items/itlipstick.h"
#include "items/itlipstickspore.h"
#include "items/itmball.h"
#include "items/itmetalb.h"
#include "items/itmsbomb.h"
#include "items/itparasol.h"
#include "items/itrabbitc.h"
#include "items/itrshell.h"
#include "items/itscball.h"
#include "items/itspycloak.h"
#include "items/itsscope.h"
#include "items/itsscopebeam.h"
#include "items/itstar.h"
#include "items/itstarrod.h"
#include "items/itstarrodstar.h"
#include "items/itsword.h"
#include "items/ittaru.h"
#include "items/ittarucann.h"
#include "items/ittomato.h"
#include "items/itwstar.h"
#include "lb/inlines.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbcollision.h"
#include "lb/lbvector.h"
#include "mp/mpcoll.h"
#include "mp/mplib.h"
#include "pl/plattack.h"
#include "pl/plbonuslib.h"
#include "pl/plstale.h"
#include "pl/pltrick.h"
#include "ty/tydisplay.h"

#include <math.h>
#include <math_ppc.h>
#include <dolphin/mtx.h>
#include <baselib/dobj.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjproc.h>
#include <baselib/mobj.h>
#include <baselib/random.h>
#include <baselib/tev.h>

extern Vec3 it_803B8570;       // { 0.0f, 0.0f, 0.0f }
extern Vec3 it_803B857C;       // { 0.0f, 0.0f, 0.0f }
extern Quaternion it_803B8588; //{ 0.0f, 0.0f, 0.0f, 0.0f }
extern Quaternion it_803B8598; //{ 0.0f, 0.0f, 0.0f, 0.0f }
extern const Vec3 it_803B85A8[6];
extern s64 it_803B85F0;
extern s64 it_803B85F8;

// Common items
struct sdata_ItemGXLink it_803F1418[43] = {
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_80284E10, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC,
};

struct ItemLogicTable it_803F14C4[ARRAY_SIZE(it_803F1418)] = {
    {
        // Capsule
        it_803F5468,
        it_3F14_Logic0_Spawned,
        NULL,
        it_3F14_Logic0_PickedUp,
        it_3F14_Logic0_Dropped,
        it_3F14_Logic0_Thrown,
        it_3F14_Logic0_DmgDealt,
        it_3F14_Logic0_DmgReceived,
        it_3F14_Logic0_EnteredAir,
        it_3F14_Logic0_Reflected,
        it_3F14_Logic0_Clanked,
        NULL,
        it_3F14_Logic0_ShieldBounced,
        it_3F14_Logic0_HitShield,
        it_3F14_Logic0_EvtUnk,
    },
    {
        // Box
        it_803F5850,
        it_3F14_Logic1_Spawned,
        it_3F14_Logic1_Destroyed,
        it_3F14_Logic1_PickedUp,
        it_3F14_Logic1_Dropped,
        it_3F14_Logic1_Thrown,
        it_3F14_Logic1_DmgDealt,
        it_3F14_Logic1_DmgReceived,
        it_3F14_Logic1_EnteredAir,
        it_3F14_Logic1_Reflected,
        it_3F14_Logic1_Clanked,
        NULL,
        NULL,
        it_3F14_Logic1_HitShield,
        it_3F14_Logic1_EvtUnk,
    },
    {
        // Taru
        it_803F58E0,
        it_3F14_Logic2_Spawned,
        NULL,
        it_3F14_Logic2_PickedUp,
        it_3F14_Logic2_Dropped,
        it_3F14_Logic2_Thrown,
        it_3F14_Logic2_DmgDealt,
        it_3F14_Logic2_DmgReceived,
        NULL,
        it_3F14_Logic2_Reflected,
        it_3F14_Logic2_Clanked,
        NULL,
        NULL,
        it_3F14_Logic2_HitShield,
        it_3F14_Logic2_EvtUnk,
    },
    {
        // Egg
        it_803F5988,
        it_3F14_Logic3_Spawned,
        NULL,
        it_3F14_Logic3_PickedUp,
        it_3F14_Logic3_Dropped,
        it_3F14_Logic3_Thrown,
        it_3F14_Logic3_DmgDealt,
        it_3F14_Logic3_DmgReceived,
        it_3F14_Logic3_EnteredAir,
        it_3F14_Logic3_Reflected,
        it_3F14_Logic3_Clanked,
        NULL,
        NULL,
        it_3F14_Logic3_HitShield,
        it_3F14_Logic3_EvtUnk,
    },
    {
        // Kusudama
        it_803F59F8,
        it_3F14_Logic4_Spawned,
        NULL,
        it_3F14_Logic4_PickedUp,
        it_3F14_Logic4_Dropped,
        it_3F14_Logic4_Thrown,
        it_3F14_Logic4_DmgDealt,
        it_3F14_Logic4_DmgReceived,
        NULL,
        it_3F14_Logic4_Reflected,
        it_3F14_Logic4_Clanked,
        NULL,
        NULL,
        it_3F14_Logic4_HitShield,
        it_3F14_Logic4_EvtUnk,
    },
    {
        // TaruCann
        it_803F63C0,
        it_3F14_Logic5_Spawned,
        it_3F14_Logic5_Destroyed,
        it_3F14_Logic5_PickedUp,
        it_3F14_Logic5_Dropped,
        it_3F14_Logic5_Thrown,
        it_3F14_Logic5_DmgDealt,
        NULL,
        NULL,
        it_3F14_Logic5_Reflected,
        it_3F14_Logic5_Clanked,
        NULL,
        NULL,
        it_3F14_Logic5_HitShield,
        it_3F14_Logic5_EvtUnk,
    },
    {
        // BombHei
        it_803F54D8,
        it_3F14_Logic6_Spawned,
        NULL,
        it_3F14_Logic6_PickedUp,
        it_3F14_Logic6_Dropped,
        it_3F14_Logic6_Thrown,
        it_3F14_Logic6_DmgDealt,
        it_3F14_Logic6_DmgReceived,
        it_3F14_Logic6_EnteredAir,
        it_3F14_Logic6_Reflected,
        it_3F14_Logic6_Clanked,
        NULL,
        it_3F14_Logic6_ShieldBounced,
        it_3F14_Logic6_HitShield,
        it_3F14_Logic6_EvtUnk,
    },
    {
        // Dosei
        it_803F55D0,
        it_3F14_Logic7_Spawned,
        NULL,
        it_3F14_Logic7_PickedUp,
        it_3F14_Logic7_Dropped,
        it_3F14_Logic7_Thrown,
        it_3F14_Logic7_DmgDealt,
        it_3F14_Logic7_DmgReceived,
        it_3F14_Logic7_EnteredAir,
        it_3F14_Logic7_Reflected,
        it_3F14_Logic7_Clanked,
        NULL,
        it_3F14_Logic7_ShieldBounced,
        it_3F14_Logic7_HitShield,
        it_3F14_Logic7_EvtUnk,
    },
    {
        // Heart
        it_803F56C8,
        it_3F14_Logic8_Spawned,
        it_3F14_Logic8_Destroyed,
        it_3F14_Logic8_PickedUp,
        it_3F14_Logic8_Dropped,
        NULL,
        NULL,
        NULL,
        it_3F14_Logic8_EnteredAir,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_3F14_Logic8_EvtUnk,
    },
    {
        // Tomato
        it_803F5740,
        it_3F14_Logic9_Spawned,
        it_3F14_Logic9_Destroyed,
        it_3F14_Logic9_PickedUp,
        it_3F14_Logic9_Dropped,
        NULL,
        NULL,
        NULL,
        it_3F14_Logic9_EnteredAir,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_3F14_Logic9_EvtUnk,
    },
    {
        // Star
        it_803F57A0,
        it_3F14_Logic10_Spawned,
        NULL,
        NULL,
        NULL,
        NULL,
        it_3F14_Logic10_DmgDealt,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_3F14_Logic10_EvtUnk,
    },
    {
        // Bat
        it_803F57B0,
        it_3F14_Logic11_Spawned,
        NULL,
        it_3F14_Logic11_PickedUp,
        it_3F14_Logic11_Dropped,
        it_3F14_Logic11_Thrown,
        it_3F14_Logic11_DmgDealt,
        NULL,
        it_3F14_Logic11_EnteredAir,
        it_3F14_Logic11_Reflected,
        it_3F14_Logic11_Clanked,
        NULL,
        it_3F14_Logic11_ShieldBounced,
        it_3F14_Logic11_HitShield,
        it_3F14_Logic11_EvtUnk,
    },
    {
        // Sword
        it_803F5800,
        it_3F14_Logic12_Spawned,
        NULL,
        it_3F14_Logic12_PickedUp,
        it_3F14_Logic12_Dropped,
        it_3F14_Logic12_Thrown,
        it_3F14_Logic12_DmgDealt,
        NULL,
        it_3F14_Logic12_EnteredAir,
        it_3F14_Logic12_Reflected,
        it_3F14_Logic12_Clanked,
        NULL,
        it_3F14_Logic12_ShieldBounced,
        it_3F14_Logic12_HitShield,
        it_3F14_Logic12_EvtUnk,
    },
    {
        // Parasol
        it_803F5AB0,
        it_3F14_Logic13_Spawned,
        NULL,
        it_3F14_Logic13_PickedUp,
        it_3F14_Logic13_Dropped,
        it_3F14_Logic13_Thrown,
        it_3F14_Logic13_DmgDealt,
        NULL,
        it_3F14_Logic13_EnteredAir,
        it_3F14_Logic13_Reflected,
        it_3F14_Logic13_Clanked,
        NULL,
        it_3F14_Logic13_ShieldBounced,
        it_3F14_Logic13_HitShield,
        it_3F14_Logic13_EvtUnk,
    },
    {
        // G Shell
        it_803F5BA8,
        it_3F14_Logic14_Spawned,
        NULL,
        it_3F14_Logic14_PickedUp,
        it_3F14_Logic14_Dropped,
        it_3F14_Logic14_Thrown,
        it_3F14_Logic14_DmgDealt,
        it_3F14_Logic14_DmgReceived,
        it_3F14_Logic14_EnteredAir,
        it_3F14_Logic14_Reflected,
        it_3F14_Logic14_Clanked,
        NULL,
        it_3F14_Logic14_ShieldBounced,
        it_3F14_Logic14_HitShield,
        it_3F14_Logic14_EvtUnk,
    },
    {
        // R Shell
        it_803F5C48,
        it_3F14_Logic15_Spawned,
        NULL,
        it_3F14_Logic15_PickedUp,
        it_3F14_Logic15_Dropped,
        it_3F14_Logic15_Thrown,
        it_3F14_Logic15_DmgDealt,
        it_3F14_Logic15_DmgReceived,
        it_3F14_Logic15_EnteredAir,
        it_3F14_Logic15_Reflected,
        it_3F14_Logic15_Clanked,
        NULL,
        it_3F14_Logic15_ShieldBounced,
        it_3F14_Logic15_HitShield,
        it_3F14_Logic15_EvtUnk,
    },
    {
        // L Gun
        it_803F5CC8,
        it_3F14_Logic16_Spawned,
        NULL,
        it_3F14_Logic16_PickedUp,
        it_3F14_Logic16_Dropped,
        it_3F14_Logic16_Thrown,
        it_3F14_Logic16_DmgDealt,
        NULL,
        it_3F14_Logic16_EnteredAir,
        it_3F14_Logic16_Reflected,
        it_3F14_Logic16_Clanked,
        NULL,
        it_3F14_Logic16_ShieldBounced,
        it_3F14_Logic16_HitShield,
        it_3F14_Logic16_EvtUnk,
    },
    {
        // Freeze
        it_803F5D28,
        it_3F14_Logic17_Spawned,
        it_3F14_Logic17_Destroyed,
        it_3F14_Logic17_PickedUp,
        it_3F14_Logic17_Dropped,
        it_3F14_Logic17_Thrown,
        it_3F14_Logic17_DmgDealt,
        it_3F14_Logic17_DmgReceived,
        NULL,
        it_3F14_Logic17_Reflected,
        it_3F14_Logic17_Clanked,
        it_3F14_Logic17_Absorbed,
        it_3F14_Logic17_ShieldBounced,
        it_3F14_Logic17_HitShield,
        it_3F14_Logic17_EvtUnk,
    },
    {
        // Foods
        it_803F5DB0,
        it_3F14_Logic18_Spawned,
        NULL,
        it_3F14_Logic18_PickedUp,
        it_3F14_Logic18_Dropped,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_3F14_Logic18_EvtUnk,
    },
    {
        // MSBomb
        ItemStateTable_MsBomb,
        it_3F14_Logic19_Spawned,
        NULL,
        it_3F14_Logic19_PickedUp,
        it_3F14_Logic19_Dropped,
        it_3F14_Logic19_Thrown,
        it_3F14_Logic19_DmgDealt,
        it_3F14_Logic19_DmgReceived,
        it_3F14_Logic19_EnteredAir,
        it_3F14_Logic19_Reflected,
        it_3F14_Logic19_Clanked,
        NULL,
        it_3F14_Logic19_ShieldBounced,
        it_3F14_Logic19_HitShield,
        it_3F14_Logic19_EvtUnk,
    },
    {
        // Flipper
        it_803F5EA8,
        it_3F14_Logic20_Spawned,
        NULL,
        it_3F14_Logic20_PickedUp,
        it_3F14_Logic20_Dropped,
        it_3F14_Logic20_Thrown,
        it_3F14_Logic20_DmgDealt,
        it_3F14_Logic20_DmgReceived,
        it_3F14_Logic20_EnteredAir,
        it_3F14_Logic20_Reflected,
        it_3F14_Logic20_Clanked,
        NULL,
        it_3F14_Logic20_ShieldBounced,
        it_3F14_Logic20_HitShield,
        it_3F14_Logic20_EvtUnk,
    },
    {
        // S_Scope
        it_803F5F40,
        it_3F14_Logic21_Spawned,
        NULL,
        it_3F14_Logic21_PickedUp,
        it_3F14_Logic21_Dropped,
        it_3F14_Logic21_Thrown,
        it_3F14_Logic21_DmgDealt,
        NULL,
        it_3F14_Logic21_EnteredAir,
        it_3F14_Logic21_Reflected,
        it_3F14_Logic21_Clanked,
        NULL,
        it_3F14_Logic21_ShieldBounced,
        it_3F14_Logic21_HitShield,
        it_3F14_Logic21_EvtUnk,
    },
    {
        // StarRod
        it_803F5F90,
        it_3F14_Logic22_Spawned,
        NULL,
        it_3F14_Logic22_PickedUp,
        it_3F14_Logic22_Dropped,
        it_3F14_Logic22_Thrown,
        it_3F14_Logic22_DmgDealt,
        NULL,
        it_3F14_Logic22_EnteredAir,
        it_3F14_Logic22_Reflected,
        it_3F14_Logic22_Clanked,
        NULL,
        it_3F14_Logic22_ShieldBounced,
        it_3F14_Logic22_HitShield,
        it_3F14_Logic22_EvtUnk,
    },
    {
        // LipStick
        it_803F6310,
        it_3F14_Logic23_Spawned,
        NULL,
        it_3F14_Logic23_PickedUp,
        it_3F14_Logic23_Dropped,
        it_3F14_Logic23_Thrown,
        it_3F14_Logic23_DmgDealt,
        NULL,
        it_3F14_Logic23_EnteredAir,
        it_3F14_Logic23_Reflected,
        it_3F14_Logic23_Clanked,
        NULL,
        it_3F14_Logic23_ShieldBounced,
        it_3F14_Logic23_HitShield,
        it_3F14_Logic23_EvtUnk,
    },
    {
        // Harisen
        it_803F5FF0,
        it_3F14_Logic24_Spawned,
        NULL,
        it_3F14_Logic24_PickedUp,
        it_3F14_Logic24_Dropped,
        it_3F14_Logic24_Thrown,
        it_3F14_Logic24_DmgDealt,
        NULL,
        it_3F14_Logic24_EnteredAir,
        it_3F14_Logic24_Reflected,
        it_3F14_Logic24_Clanked,
        NULL,
        it_3F14_Logic24_ShieldBounced,
        it_3F14_Logic24_HitShield,
        it_3F14_Logic24_EvtUnk,
    },
    {
        // F Flower
        it_803F6090,
        it_3F14_Logic25_Spawned,
        NULL,
        it_3F14_Logic25_PickedUp,
        it_3F14_Logic25_Dropped,
        it_3F14_Logic25_Thrown,
        it_3F14_Logic25_DmgDealt,
        NULL,
        it_3F14_Logic25_EnteredAir,
        it_3F14_Logic25_Reflected,
        it_3F14_Logic25_Clanked,
        NULL,
        it_3F14_Logic25_ShieldBounced,
        it_3F14_Logic25_HitShield,
        it_3F14_Logic25_EvtUnk,
    },
    {
        // Kinoko
        it_803F6110,
        it_3F14_Logic26_Spawned,
        NULL,
        NULL,
        NULL,
        NULL,
        it_3F14_Logic26_DmgDealt,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_3F14_Logic26_EvtUnk,
    },
    {
        // DKinoko
        it_803F6130,
        it_3F14_Logic27_Spawned,
        NULL,
        NULL,
        NULL,
        NULL,
        it_3F14_Logic27_DmgDealt,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_3F14_Logic27_EvtUnk,
    },
    {
        // Hammer
        it_803F6150,
        it_3F14_Logic28_Spawned,
        NULL,
        it_3F14_Logic28_PickedUp,
        it_3F14_Logic28_Dropped,
        NULL,
        NULL,
        NULL,
        it_3F14_Logic28_EnteredAir,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_3F14_Logic28_EvtUnk,
    },
    {
        // WStar
        it_803F61B0,
        it_3F14_Logic29_Spawned,
        NULL,
        it_3F14_Logic29_PickedUp,
        it_3F14_Logic29_Dropped,
        NULL,
        NULL,
        NULL,
        it_3F14_Logic29_EnteredAir,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_3F14_Logic30_EvtUnk,
    },
    {
        // ScBall
        it_803F6220,
        it_3F14_Logic30_Spawned,
        NULL,
        it_3F14_Logic30_PickedUp,
        it_3F14_Logic30_Dropped,
        it_3F14_Logic30_Thrown,
        it_3F14_Logic30_DmgDealt,
        NULL,
        it_3F14_Logic30_EnteredAir,
        it_3F14_Logic30_Reflected,
        it_3F14_Logic30_Clanked,
        NULL,
        it_3F14_Logic30_ShieldBounced,
        it_3F14_Logic30_HitShield,
        it_3F14_Logic30_EvtUnk,
    },
    {
        // RabbitC
        it_803F6270,
        it_3F14_Logic31_Spawned,
        NULL,
        it_3F14_Logic31_PickedUp,
        it_3F14_Logic31_Dropped,
        NULL,
        NULL,
        NULL,
        it_3F14_Logic31_EnteredAir,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_3F14_Logic31_EvtUnk,
    },
    {
        // MetalB
        it_803F62C0,
        it_3F14_Logic32_Spawned,
        NULL,
        it_3F14_Logic32_PickedUp,
        it_3F14_Logic32_Dropped,
        NULL,
        NULL,
        it_3F14_Logic32_DmgReceived,
        it_3F14_Logic32_EnteredAir,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_3F14_Logic32_EvtUnk,
    },
    {
        // Spycloak
        it_803F6370,
        it_3F14_Logic33_Spawned,
        NULL,
        it_3F14_Logic33_PickedUp,
        it_3F14_Logic33_Dropped,
        NULL,
        NULL,
        NULL,
        it_3F14_Logic33_EnteredAir,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_3F14_Logic33_EvtUnk,
    },
    {
        // M Ball
        it_803F6488,
        it_3F14_Logic34_Spawned,
        it_3F14_Logic34_Destroyed,
        it_3F14_Logic34_PickedUp,
        it_3F14_Logic34_Dropped,
        it_3F14_Logic34_Thrown,
        it_3F14_Logic34_DmgDealt,
        NULL,
        it_3F14_Logic34_EnteredAir,
        it_3F14_Logic34_Reflected,
        it_3F14_Logic34_Clanked,
        NULL,
        it_3F14_Logic34_ShieldBounced,
        it_3F14_Logic34_HitShield,
        it_3F14_Logic34_EvtUnk,
    },
    {
        // L Gun Ray
        it_803F64F8,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_3F14_Logic35_DmgDealt,
        NULL,
        NULL,
        it_3F14_Logic35_Reflected,
        it_3F14_Logic35_Clanked,
        it_3F14_Logic35_Absorbed,
        it_3F14_Logic35_ShieldBounced,
        it_3F14_Logic35_HitShield,
        it_3F14_Logic35_EvtUnk,
    },
    {
        // Star Rod Star
        it_803F6530,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_3F14_Logic36_DmgDealt,
        NULL,
        NULL,
        it_3F14_Logic36_Reflected,
        it_3F14_Logic36_Clanked,
        it_3F14_Logic36_Absorbed,
        it_3F14_Logic36_ShieldBounced,
        it_3F14_Logic36_HitShield,
        it_3F14_Logic36_EvtUnk,
    },
    {
        // LipStick Spore
        it_803F6680,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_3F14_Logic37_DmgDealt,
        NULL,
        NULL,
        it_3F14_Logic37_Reflected,
        it_3F14_Logic37_Clanked,
        it_3F14_Logic37_Absorbed,
        it_3F14_Logic37_ShieldBounced,
        it_3F14_Logic37_HitShield,
        it_3F14_Logic37_EvtUnk,
    },
    {
        // S Scope Beam
        it_803F6568,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_3F14_Logic38_DmgDealt,
        NULL,
        NULL,
        it_3F14_Logic38_Reflected,
        it_3F14_Logic38_Clanked,
        it_3F14_Logic38_Absorbed,
        it_3F14_Logic38_ShieldBounced,
        it_3F14_Logic38_HitShield,
        it_3F14_Logic38_EvtUnk,
    },
    {
        // L Gun Beam
        it_803F6630,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_3F14_Logic39_DmgDealt,
        NULL,
        NULL,
        it_3F14_Logic39_Reflected,
        it_3F14_Logic39_Clanked,
        it_3F14_Logic39_Absorbed,
        it_3F14_Logic39_ShieldBounced,
        it_3F14_Logic39_HitShield,
        it_3F14_Logic39_EvtUnk,
    },
    {
        // Hammer Head
        it_803F6640,
        it_3F14_Logic40_Spawned,
        NULL,
        it_3F14_Logic40_PickedUp,
        it_3F14_Logic40_Dropped,
        it_3F14_Logic40_Thrown,
        it_3F14_Logic40_DmgDealt,
        it_3F14_Logic40_DmgReceived,
        NULL,
        it_3F14_Logic40_Reflected,
        it_3F14_Logic40_Clanked,
        NULL,
        NULL,
        it_3F14_Logic40_HitShield,
        it_3F14_Logic40_EvtUnk,
    },
    {
        // F Flower Flame
        it_803F66C8,
        it_3F14_Logic41_Spawned,
        NULL,
        it_3F14_Logic41_PickedUp,
        it_3F14_Logic41_Dropped,
        NULL,
        NULL,
        NULL,
        it_3F14_Logic41_EnteredAir,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_3F14_Logic41_EvtUnk,
    },
    {
        // EvYoshiEgg
        it_803F6728,
        it_3F14_Logic42_Spawned,
        it_3F14_Logic42_Destroyed,
        it_3F14_Logic42_PickedUp,
        it_3F14_Logic42_Dropped,
        it_3F14_Logic42_Thrown,
        it_3F14_Logic42_DmgDealt,
        it_3F14_Logic42_DmgReceived,
        it_3F14_Logic42_EnteredAir,
        it_3F14_Logic42_Reflected,
        it_3F14_Logic42_Clanked,
        NULL,
        NULL,
        it_3F14_Logic42_HitShield,
        it_3F14_Logic42_EvtUnk,
    },
};

// static char it_803F1ED8[]; // unsure of type
// static char it_803F1EE4[]; // unsure of type
// static char it_803F1EF0[]; // unsure of type
// static char it_803F1F00[] = "!(jobj->flags & JOBJ_USE_QUATERNION)"; // ?
// "translate" static char it_803F1F0C[] = "!(jobj->flags &
// JOBJ_USE_QUATERNION)"; // ?

// char it_803F1F38[];
char* it_803F1F38;
// char it_803F1F58[];
char* it_803F1F58;

HSD_ClassInfo it_803F1F90;
//  = {
//     (struct _HSD_ClassInfoHead) {
//         it_80277D08, // void (*info_init)(void);
//         0x00000000, // u32 flags;
//         0x00000000, // char* library_name;
//         0x00000000, // char* class_name;
//         0x00000000, // s16 obj_size;
//         0x00000000, // s16 info_size;
//         0x00000000, // struct _HSD_ClassInfo* parent;
//         0x00000000, // struct _HSD_ClassInfo* next;
//         0x00000000, // struct _HSD_ClassInfo* child;
//         0x00000000, // u32 nb_exist;
//         0x00000000, // u32 nb_peak;
//     },
//     0x00000000, // HSD_Class* (*alloc)(struct _HSD_ClassInfo* c);
//     0x00000000, // int (*init)(struct _HSD_Class* c);
//     0x00000000, // void (*release)(struct _HSD_Class* c);
//     0x00000000, // void (*destroy)(struct _HSD_Class* c);
//     0x00000000, // void (*amnesia)(struct _HSD_ClassInfo* c);
//     // ... lots more data, but no other struct elements to put them in
// };

void* jumptable_803F20E0[114];

static ItCmd it_803F22A8[16] = {
    // static void* it_803F22A8[16] = {
    it_80278F2C, it_802790C0, it_80279544, it_802795EC,
    it_80279680, it_802796C4, it_8027978C, it_802796FC,
    it_80279720, it_80279744, it_80279768, it_80279888,
    it_802798D4, it_8027990C, it_80279958, it_802799A8,
};

char it_803F22E8;
char it_803F2300;

// Pokemon items
struct sdata_ItemGXLink it_803F2310[47] = {
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC,
};

ItemLogicTable it_803F23CC[ARRAY_SIZE(it_803F2310)] = {
    {
        // Tosakinto (Goldeen)
        it_803F7A48,
        it_802C8F4C,
        it_2725_Logic0_Destroyed,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802C8FC4,
    },
    {
        // Chicorita
        it_803F7A98,
        it_802C9588,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic1_EvtUnk,
    },
    {
        // Kabigon (Snorlax)
        it_803F7AD8,
        it_802C9D40,
        it_2725_Logic2_Destroyed,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802C9E24,
    },
    {
        // Kamex (Blastoise)
        it_803F7B08,
        it_802CA49C,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802CA538,
    },
    {
        // Matadogas (Weezing)
        it_803F7B58,
        it_802CAFD4,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802CB0F8,
    },
    {
        // Lizardon (Charizard)
        it_803F7BC0,
        it_802CB8AC,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802CB940,
    },
    {
        // Fire (Moltres)
        it_803F7C10,
        it_2725_Logic6_Spawned,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic6_EvtUnk,
    },
    {
        // Thunder (Zapdos)
        it_803F7C40,
        it_2725_Logic7_Spawned,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802CCB14,
    },
    {
        // Freezer (Articuno)
        it_803F7C70,
        it_802CCF9C,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802CD000,
    },
    {
        // Sonans (Wobbuffet)
        it_803F7CA0,
        it_802CD44C,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic9_DmgDealt,
        it_802CD7D4,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802CD4DC,
    },
    {
        // Hassam (Scizor)
        it_803F7CF8,
        it_802CDBE0,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802CDC60,
    },
    {
        // Unknown (Unown)
        it_803F7D60,
        it_802CE710,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802CE7D0,
    },
    {
        // Entei
        it_803F7DC8,
        it_802CF3E0,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802CF450,
    },
    {
        // Raikou
        it_803F7DE8,
        it_802CF814,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802CF884,
    },
    {
        // Suikun (Suicune)
        it_803F7E08,
        it_2725_Logic14_Spawned,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802CFCB8,
    },
    {
        // Kireihana (Bellossom)
        it_803F7E28,
        it_2725_Logic15_Spawned,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic15_EvtUnk,
    },
    {
        // Marumine (Electrode)
        it_803F7E78,
        it_2725_Logic16_Spawned,
        NULL,
        it_802D0D18,
        it_802D0E30,
        it_802D0E90,
        it_802D0AD0,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802D0AB0,
    },
    {
        // Lugia
        it_803F7EE8,
        it_2725_Logic17_Spawned,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic17_EvtUnk,
    },
    {
        // Houou (Ho-oh)
        it_803F7F58,
        it_2725_Logic18_Spawned,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802D25BC,
    },
    {
        // Metamon (Ditto)
        it_803F7FC8,
        it_802D3008,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic19_EvtUnk,
    },
    {
        // Pippi (Clefairy)
        it_803F7FF8,
        it_2725_Logic20_Spawned,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802D32DC,
    },
    {
        // Togepy
        it_803F8058,
        it_2725_Logic21_Spawned,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic21_EvtUnk,
    },
    {
        // Mew
        it_803F80C8,
        it_2725_Logic22_Spawned,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802D3B6C,
    },
    {
        // Cerebi
        it_803F80F8,
        it_2725_Logic23_Spawned,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802D3F4C,
    },
    {
        // Hitodeman (Staryu)
        it_803F8128,
        it_2725_Logic24_Spawned,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802D43B0,
    },
    {
        // Lucky (Chansey)
        it_803F8190,
        it_802D5050,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802D5648,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802D56F0,
    },
    {
        // Porygon2
        it_803F8250,
        it_2725_Logic26_Spawned,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802D5CD8,
    },
    {
        // Hinoarashi (Cyndaquil)
        it_803F8270,
        it_802D5CF8,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic27_DmgReceived,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802D61A8,
    },
    {
        // Maril
        it_803F82B0,
        it_2725_Logic28_Spawned,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802D6F00,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802D6FB0,
    },
    {
        // Fushigibana (Venusaur)
        it_803F82F0,
        it_2725_Logic29_Spawned,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic29_EvtUnk,
    },
    {
        // Chicorita leaf
        it_803F7AC8,
        it_2725_Logic30_Spawned,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic30_HitShield,
        NULL,
        NULL,
        it_2725_Logic30_Reflected,
        it_2725_Logic30_HitShield,
        it_2725_Logic30_HitShield,
        NULL,
        it_2725_Logic30_HitShield,
        it_2725_Logic30_EvtUnk,
    },
    {
        // Kamex hydro pump
        it_803F7B48,
        it_2725_Logic31_Spawned,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic31_DmgDealt,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic31_HitShield,
        it_2725_Logic31_EvtUnk,
    },
    {
        // Matadogas gas 1
        it_803F7BB0,
        it_2725_Logic32_Spawned,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic33_EvtUnk,
    },
    {
        // Matadogas gas 2
        it_803F7BB0,
        it_2725_Logic33_Spawned,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic33_EvtUnk,
    },
    {
        // Lizardon flame 1
        it_803F7C00,
        it_2725_Logic34_Spawned,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic37_Reflected,
        NULL,
        it_2725_Logic37_Absorbed,
        NULL,
        it_2725_Logic37_HitShield,
        it_2725_Logic37_EvtUnk,
    },
    {
        // Lizardon flame 2
        it_803F7C00,
        it_2725_Logic35_Spawned,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic37_Reflected,
        NULL,
        it_2725_Logic37_Absorbed,
        NULL,
        it_2725_Logic37_HitShield,
        it_2725_Logic37_EvtUnk,
    },
    {
        // Lizardon flame 3
        it_803F7C00,
        it_2725_Logic36_Spawned,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic37_Reflected,
        NULL,
        it_2725_Logic37_Absorbed,
        NULL,
        it_2725_Logic37_HitShield,
        it_2725_Logic37_EvtUnk,
    },
    {
        // Lizardon flame 4
        it_803F7C00,
        it_2725_Logic37_Spawned,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic37_Reflected,
        NULL,
        it_2725_Logic37_Absorbed,
        NULL,
        it_2725_Logic37_HitShield,
        it_2725_Logic37_EvtUnk,
    },
    {
        // Unknown swarm (mini-unowns)
        it_803F7D90,
        it_2725_Logic38_Spawned,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic38_EvtUnk,
    },
    {
        // Lugia aeroblast 1
        it_803F7F48,
        it_2725_Logic39_Spawned,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802D23D4,
    },
    {
        // Lugia aeroblast 2
        it_803F7F48,
        it_2725_Logic40_Spawned,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802D23D4,
    },
    {
        // Lugia aeroblast 3
        it_803F7F48,
        it_2725_Logic41_Spawned,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802D23D4,
    },
    {
        // Houou sacred fire
        it_803F7FB8,
        it_2725_Logic42_Spawned,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802D2ED0,
    },
    {
        // Hitodeman star
        it_803F8180,
        it_2725_Logic43_Spawned,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802D4EF4,
        NULL,
        NULL,
        it_802D4F28,
        NULL,
        it_2725_Logic43_Absorbed,
        it_802D4F08,
        it_802D4F50,
        it_802D4F58,
    },
    {
        // Lucky egg
        it_803F8200,
        it_2725_Logic44_Spawned,
        NULL,
        it_2725_Logic44_PickedUp,
        it_2725_Logic44_Dropped,
        NULL,
        NULL,
        NULL,
        it_2725_Logic44_EnteredAir,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic44_EvtUnk,
    },
    {
        // Hinoarashi flame
        it_803F82A0,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802D6808,
        NULL,
        NULL,
        it_802D6810,
        it_802D6830,
        it_802D6838,
        it_802D6840,
        it_802D6848,
        it_802D6850,
    },
    {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
};

static ItemKind it_803F2ED0[22] = {
    // Common Pokemon
    Pokemon_Tosakinto,
    Pokemon_Chicorita,
    Pokemon_Kabigon,
    Pokemon_Kamex,
    Pokemon_Matadogas,
    Pokemon_Lizardon,
    Pokemon_Sonans,
    Pokemon_Hassam,
    Pokemon_Unknown,
    Pokemon_Kireihana,
    Pokemon_Marumine,
    Pokemon_Metamon,
    Pokemon_Pippi,
    Pokemon_Togepy,
    Pokemon_Hitodeman,
    Pokemon_Lucky,
    Pokemon_Porygon2,
    Pokemon_Hinoarashi,
    Pokemon_Maril,
    Pokemon_Fushigibana,
    0xBC, // Pokemon_Chicorita_Leaf
    0x00,
};

// Character-specific items
struct sdata_ItemGXLink it_803F2F28[118] = {
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,

    it_8026EECC, it_8026EECC, it_8026EECC, it_8029CD18, it_8029CD18,

    it_8026EECC, it_8026EECC, it_8029FDDC, it_8029FDDC, it_8026EECC,
    it_8026EECC, it_802A7D8C, it_802A7D8C, it_8026EECC, it_8026EECC,

    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,

    it_8026EECC, it_8026EECC, it_802A7D8C, it_802A7D8C, it_8026EECC,

    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,

    it_8026EECC, it_802F13B4, it_8026EECC,
};

struct ItemLogicTable it_803F3100[ARRAY_SIZE(it_803F2F28)] = {
    {
        // Kuriboh
        it_803F8320,
        it_802D73F0,
        it_2725_Logic9_Destroyed,
        it_2725_Logic0_PickedUp,
        it_2725_Logic0_Dropped,
        it_2725_Logic0_Thrown,
        NULL,
        it_2725_Logic0_DmgReceived,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        // Leadead
        it_803F8EB0,
        it_802E8BCC,
        it_2725_Logic1_Destroyed,
        it_2725_Logic1_PickedUp,
        it_2725_Logic1_Dropped,
        it_2725_Logic1_Thrown,
        NULL,
        it_802E8CD8,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        // Octarock
        it_803F8B48,
        it_802E4A44,
        it_2725_Logic9_Destroyed,
        it_2725_Logic2_PickedUp,
        it_2725_Logic2_Dropped,
        it_2725_Logic2_Thrown,
        NULL,
        it_802E4B00,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802E5AA4,
    },
    {
        // Ottosea
        it_803F89C8,
        it_802E2470,
        it_2725_Logic3_Destroyed,
        it_802E31F8,
        it_802E32B4,
        it_802E3314,
        NULL,
        it_2725_Logic8_DmgReceived,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802E3784,
    },
    {
        // Octarock stone
        it_803F8E90,
        it_802E878C,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic4_DmgDealt,
        NULL,
        NULL,
        it_2725_Logic4_Reflected,
        it_2725_Logic4_Clanked,
        it_2725_Logic4_Absorbed,
        it_2725_Logic4_ShieldBounced,
        it_2725_Logic4_HitShield,
        it_802E89B0,
    },
    {
        // Mario fireball
        it_803F6788,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic87_DmgDealt,
        NULL,
        NULL,
        it_2725_Logic87_Reflected,
        it_2725_Logic87_Clanked,
        it_2725_Logic87_Absorbed,
        it_2725_Logic87_ShieldBounced,
        it_2725_Logic87_HitShield,
        it_2725_Logic87_EvtUnk,
    },
    {
        // Dr Mario pill
        it_803F75D0,
        NULL,
        NULL,
        it_2725_Logic6_PickedUp,
        NULL,
        NULL,
        it_2725_Logic88_DmgDealt,
        NULL,
        NULL,
        it_2725_Logic88_Reflected,
        it_2725_Logic88_Clanked,
        it_2725_Logic88_Absorbed,
        it_2725_Logic88_ShieldBounced,
        it_2725_Logic88_HitShield,
        it_2725_Logic88_EvtUnk,
    },
    {
        // Kirby cutter beam
        it_803F6798,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic7_DmgDealt,
        NULL,
        NULL,
        it_2725_Logic7_Reflected,
        it_2725_Logic7_Clanked,
        it_2725_Logic7_Absorbed,
        it_2725_Logic7_ShieldBounced,
        it_2725_Logic7_HitShield,
        it_8029C4B4,
    },
    {
        // Kirby hammer
        it_803F6C98,
        NULL,
        it_2725_Logic8_Destroyed,
        it_2725_Logic8_PickedUp,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802ADDB0,
    },
    {
        it_803F6C88,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802ADBE4,
    },
    {
        it_803F9470,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802F2BDC,
    },
    {
        // Fox laser
        it_803F67D0,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic94_Clanked,
        NULL,
        NULL,
        it_2725_Logic94_Reflected,
        it_2725_Logic94_Clanked,
        it_2725_Logic94_Absorbed,
        it_2725_Logic94_ShieldBounced,
        it_2725_Logic94_HitShield,
        it_2725_Logic94_EvtUnk,
    },
    {
        // Falco laser
        it_803F67D0,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic94_Clanked,
        NULL,
        NULL,
        it_2725_Logic94_Reflected,
        it_2725_Logic94_Clanked,
        it_2725_Logic94_Absorbed,
        it_2725_Logic94_ShieldBounced,
        it_2725_Logic94_HitShield,
        it_2725_Logic94_EvtUnk,
    },
    {
        // Fox illusion
        it_803F6818,
        NULL,
        it_2725_Logic14_Destroyed,
        NULL,
        NULL,
        NULL,
        it_2725_Logic14_DmgDealt,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_8029D948,
    },
    {
        // Falco phantasm
        it_803F6818,
        NULL,
        it_2725_Logic14_Destroyed,
        NULL,
        NULL,
        NULL,
        it_2725_Logic14_DmgDealt,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_8029D948,
    },
    {
        // Link bomb
        it_803F6888,
        NULL,
        NULL,
        it_8029DEB0,
        it_8029EC34,
        it_8029E5D0,
        it_8029F960,
        it_2725_Logic16_DmgReceived,
        it_2725_Logic16_EnteredAir,
        it_2725_Logic16_Reflected,
        NULL,
        NULL,
        it_2725_Logic16_ShieldBounced,
        it_2725_Logic16_HitShield,
        it_8029FD84,
    },
    {
        // Young Link bomb
        it_803F6888,
        NULL,
        NULL,
        it_8029DEB0,
        it_8029EC34,
        it_8029E5D0,
        it_8029F960,
        it_2725_Logic16_DmgReceived,
        it_2725_Logic16_EnteredAir,
        it_2725_Logic16_Reflected,
        NULL,
        NULL,
        it_2725_Logic16_ShieldBounced,
        it_2725_Logic16_HitShield,
        it_8029FD84,
    },
    {
        // Link boomerang
        it_803F6920,
        NULL,
        it_2725_Logic18_Destroyed,
        it_802A0E70,
        it_802A0F84,
        it_802A0F88,
        it_802A1F08,
        NULL,
        NULL,
        it_802A20E8,
        it_802A1FA8,
        it_2725_Logic18_Absorbed,
        it_802A2320,
        it_802A2288,
        it_802A23CC,
    },
    {
        // Young Link boomerang
        it_803F6920,
        NULL,
        it_2725_Logic18_Destroyed,
        it_802A0E70,
        it_802A0F84,
        it_802A0F88,
        it_802A1F08,
        NULL,
        NULL,
        it_802A20E8,
        it_802A1FA8,
        it_2725_Logic18_Absorbed,
        it_802A2320,
        it_802A2288,
        it_802A23CC,
    },
    {
        // Link hookshot
        it_803F6998,
        it_802A2418,
        NULL,
        it_2725_Logic20_PickedUp,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802A7D40,
    },
    {
        // Young Link hookshot
        it_803F6998,
        NULL,
        NULL,
        it_2725_Logic20_PickedUp,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802A7D40,
    },
    {
        // Link arrow
        it_803F6A28,
        NULL,
        it_2725_Logic98_Destroyed,
        it_2725_Logic98_PickedUp,
        NULL,
        NULL,
        it_2725_Logic98_DmgDealt,
        NULL,
        NULL,
        it_2725_Logic98_Reflected,
        it_2725_Logic98_Clanked,
        NULL,
        NULL,
        it_2725_Logic98_HitShield,
        it_2725_Logic98_EvtUnk,
    },
    {
        // Young Link arrow
        it_803F6A28,
        NULL,
        it_2725_Logic98_Destroyed,
        it_2725_Logic98_PickedUp,
        NULL,
        NULL,
        it_2725_Logic98_DmgDealt,
        NULL,
        NULL,
        it_2725_Logic98_Reflected,
        it_2725_Logic98_Clanked,
        NULL,
        NULL,
        it_2725_Logic98_HitShield,
        it_2725_Logic98_EvtUnk,
    },
    {
        // Ness PK fire
        it_803F6B28,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic23_DmgDealt,
        NULL,
        NULL,
        it_2725_Logic23_Reflected,
        it_2725_Logic23_Clanked,
        it_2725_Logic23_Absorbed,
        it_2725_Logic23_ShieldBounced,
        it_2725_Logic23_HitShield,
        it_802AA474,
    },
    {
        // Ness PK fire pillar
        it_803F6B60,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        itNesspkfirepillar_Logic24_DmgReceived,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        itNesspkfirepillar_Logic24_EvtUnk,
    },
    {
        // Ness PK flash
        it_803F6B70,
        NULL,
        it_2725_Logic102_Destroyed,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic102_Reflected,
        it_2725_Logic102_Clanked,
        it_2725_Logic102_Absorbed,
        NULL,
        NULL,
        it_2725_Logic102_EvtUnk,
    },
    {
        // Ness PK thunder ball
        it_803F6BC8,
        NULL,
        it_802AB90C,
        NULL,
        NULL,
        NULL,
        it_2725_Logic26_DmgDealt,
        NULL,
        NULL,
        it_802AC098,
        it_802AC074,
        it_802AC338,
        it_802AC35C,
        it_802AC3F8,
        it_802AC41C,
    },
    {
        // Ness PK thunder trail 1
        it_803F6C08,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        // Ness PK thunder trail 2
        it_803F6C08,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        // Ness PK thunder trail 3
        it_803F6C08,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        // Ness PK thunder trail 4
        it_803F6C08,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        // Fox blaster
        it_803F6CA8,
        NULL,
        NULL,
        it_2725_Logic96_PickedUp,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic96_EvtUnk,
    },
    {
        // Falco blaster
        it_803F6CA8,
        NULL,
        NULL,
        it_2725_Logic96_PickedUp,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic96_EvtUnk,
    },
    {
        // Link bow
        it_803F6E98,
        NULL,
        it_2725_Logic100_Destroyed,
        it_2725_Logic100_PickedUp,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic100_EvtUnk,
    },
    {
        // Young Link bow
        it_803F6E98,
        NULL,
        it_2725_Logic100_Destroyed,
        it_2725_Logic100_PickedUp,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic100_EvtUnk,
    },
    {
        // Ness PK flush explode
        it_803F6F40,
        NULL,
        it_2725_Logic103_Destroyed,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic103_Clanked,
        it_2725_Logic103_Absorbed,
        it_2725_Logic103_ShieldBounced,
        it_2725_Logic103_HitShield,
        it_2725_Logic103_EvtUnk,
    },
    {
        // Sheik needle thrown
        it_803F6F50,
        NULL,
        it_2725_Logic109_Destroyed,
        NULL,
        NULL,
        NULL,
        it_2725_Logic109_DmgDealt,
        it_2725_Logic109_DmgReceived,
        NULL,
        it_2725_Logic109_Reflected,
        it_2725_Logic109_Clanked,
        NULL,
        it_2725_Logic109_ShieldBounced,
        it_2725_Logic109_HitShield,
        it_2725_Logic109_EvtUnk,
    },
    {
        // Sheik needle held
        it_803F70A8,
        NULL,
        NULL,
        it_2725_Logic110_PickedUp,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic110_EvtUnk,
    },
    {
        // Pikachu thunder
        it_803F70C8,
        NULL,
        it_2725_Logic39_Destroyed,
        NULL,
        NULL,
        NULL,
        it_2725_Logic39_DmgDealt,
        NULL,
        NULL,
        NULL,
        it_2725_Logic39_Clanked,
        it_2725_Logic39_Absorbed,
        NULL,
        it_2725_Logic39_HitShield,
        it_2725_Logic39_EvtUnk,
    },
    {
        // Pichu thunder
        it_803F70C8,
        NULL,
        it_2725_Logic39_Destroyed,
        NULL,
        NULL,
        NULL,
        it_2725_Logic39_DmgDealt,
        NULL,
        NULL,
        NULL,
        it_2725_Logic39_Clanked,
        it_2725_Logic39_Absorbed,
        NULL,
        it_2725_Logic39_HitShield,
        it_2725_Logic39_EvtUnk,
    },
    {
        // Mario cape
        it_803F70F8,
        NULL,
        it_2725_Logic41_Destroyed,
        it_2725_Logic41_PickedUp,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802B2870,
    },
    {
        // Dr Mario cape
        it_803F70F8,
        NULL,
        it_2725_Logic41_Destroyed,
        it_2725_Logic41_PickedUp,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802B2870,
    },
    {
        // Sheik vanish
        it_803F70B8,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic42_DmgDealt,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802B1DCC,
    },
    {
        // Yoshi egg throw
        it_803F7118,
        NULL,
        NULL,
        it_2725_Logic43_PickedUp,
        NULL,
        NULL,
        it_802B2C04,
        NULL,
        NULL,
        it_802B2E5C,
        it_2725_Logic43_Clanked,
        NULL,
        it_802B2F88,
        it_802B2E7C,
        it_802B2FA8,
    },
    {
        // Yoshi egg lay
        it_803F94A0,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic114_DmgReceived,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic114_EvtUnk,
    },
    {
        // Yoshi star
        it_803F7158,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802B309C,
        NULL,
        NULL,
        it_802B314C,
        it_802B30C0,
        it_802B3108,
        it_802B312C,
        it_802B30E4,
        it_802B3348,
    },
    {
        // Pikachu tjolt ground
        it_803F7190,
        NULL,
        it_2725_Logic106_Destroyed,
        NULL,
        NULL,
        NULL,
        it_2725_Logic106_DmgDealt,
        NULL,
        NULL,
        it_2725_Logic106_Reflected,
        it_2725_Logic106_Clanked,
        it_2725_Logic106_Absorbed,
        it_2725_Logic106_ShieldBounced,
        it_2725_Logic106_HitShield,
        it_2725_Logic106_EvtUnk,
    },
    {
        // Pikachu tjolt air
        it_803F71D8,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic107_DmgDealt,
        NULL,
        NULL,
        it_2725_Logic107_Reflected,
        it_2725_Logic107_Clanked,
        it_2725_Logic107_Absorbed,
        it_2725_Logic107_ShieldBounced,
        it_2725_Logic107_HitShield,
        it_2725_Logic107_EvtUnk,
    },
    {
        // Pichu tjolt ground
        it_803F7190,
        NULL,
        it_2725_Logic106_Destroyed,
        NULL,
        NULL,
        NULL,
        it_2725_Logic106_DmgDealt,
        NULL,
        NULL,
        it_2725_Logic106_Reflected,
        it_2725_Logic106_Clanked,
        it_2725_Logic106_Absorbed,
        it_2725_Logic106_ShieldBounced,
        it_2725_Logic106_HitShield,
        it_2725_Logic106_EvtUnk,
    },
    {
        // Pichu tjolt air
        it_803F71D8,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic107_DmgDealt,
        NULL,
        NULL,
        it_2725_Logic107_Reflected,
        it_2725_Logic107_Clanked,
        it_2725_Logic107_Absorbed,
        it_2725_Logic107_ShieldBounced,
        it_2725_Logic107_HitShield,
        it_2725_Logic107_EvtUnk,
    },
    {
        // Samus bomb
        it_803F7220,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic50_DmgDealt,
        NULL,
        it_2725_Logic50_EnteredAir,
        it_2725_Logic50_Reflected,
        it_2725_Logic50_Clanked,
        NULL,
        it_2725_Logic50_ShieldBounced,
        it_2725_Logic50_HitShield,
        it_2725_Logic50_EvtUnk,
    },
    {
        // Samus charge shot
        it_803F7288,
        NULL,
        it_2725_Logic108_Destroyed,
        it_2725_Logic108_PickedUp,
        NULL,
        NULL,
        it_2725_Logic108_DmgDealt,
        NULL,
        NULL,
        it_2725_Logic108_Reflected,
        it_2725_Logic108_Clanked,
        it_2725_Logic108_Absorbed,
        it_2725_Logic108_ShieldBounced,
        it_2725_Logic108_HitShield,
        it_2725_Logic108_EvtUnk,
    },
    {
        // Samus missile
        it_803F7340,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic52_DmgDealt,
        NULL,
        NULL,
        it_2725_Logic52_Reflected,
        it_2725_Logic52_Clanked,
        NULL,
        it_2725_Logic52_ShieldBounced,
        it_2725_Logic52_HitShield,
        it_2725_Logic52_EvtUnk,
    },
    {
        // Samus grapple beam
        it_803F73A8,
        it_2725_Logic53_Spawned,
        NULL,
        it_2725_Logic53_PickedUp,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic53_EvtUnk,
    },
    {
        // Sheik chain
        it_803F7438,
        NULL,
        NULL,
        it_2725_Logic54_PickedUp,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic54_EvtUnk,
    },
    {
        // Peach explode
        it_803F7488,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic55_DmgDealt,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic55_EvtUnk,
    },
    {
        // Peach turnip
        it_803F74A8,
        NULL,
        it_2725_Logic56_Destroyed,
        it_2725_Logic56_PickedUp,
        it_2725_Logic56_Dropped,
        it_2725_Logic56_Thrown,
        it_2725_Logic56_DmgDealt,
        NULL,
        NULL,
        it_2725_Logic56_Reflected,
        it_2725_Logic56_Clanked,
        NULL,
        it_2725_Logic56_ShieldBounced,
        it_2725_Logic56_HitShield,
        it_2725_Logic56_EvtUnk,
    },
    {
        // Bowser flame
        ItemStateTable_KoopaFlame,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic111_DmgDealt,
        NULL,
        NULL,
        it_2725_Logic111_Reflected,
        it_2725_Logic111_Clanked,
        it_2725_Logic111_Absorbed,
        it_2725_Logic111_ShieldBounced,
        it_2725_Logic111_HitShield,
        it_2725_Logic111_EvtUnk,
    },
    {
        // Ness bat
        it_803F6C68,
        NULL,
        NULL,
        it_2725_Logic58_PickedUp,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic58_EvtUnk,
    },
    {
        // Ness yo-yo
        it_803F7558,
        NULL,
        NULL,
        it_2725_Logic59_PickedUp,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic59_EvtUnk,
    },
    {
        // Peach parasol
        it_803F74F8,
        NULL,
        it_2725_Logic60_Destroyed,
        it_2725_Logic60_PickedUp,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic60_EvtUnk,
    },
    {
        // Peach toad
        it_803F7528,
        NULL,
        it_2725_Logic91_Destroyed,
        it_2725_Logic91_PickedUp,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic91_EvtUnk,
    },
    {
        // Luigi fireball
        it_803F75C0,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic89_DmgDealt,
        NULL,
        NULL,
        it_2725_Logic89_Reflected,
        it_2725_Logic89_Clanked,
        it_2725_Logic89_Absorbed,
        it_2725_Logic89_ShieldBounced,
        it_2725_Logic89_HitShield,
        it_2725_Logic89_EvtUnk,
    },
    {
        // Ice Climbers ice
        it_803F7668,
        NULL,
        it_2725_Logic90_Destroyed,
        NULL,
        NULL,
        NULL,
        it_2725_Logic90_DmgDealt,
        NULL,
        NULL,
        it_2725_Logic90_Reflected,
        it_2725_Logic90_Clanked,
        it_2725_Logic90_Absorbed,
        it_2725_Logic90_ShieldBounced,
        it_2725_Logic90_HitShield,
        it_2725_Logic90_EvtUnk,
    },
    {
        // Ice Climbers blizzard
        it_803F76A8,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic64_DmgDealt,
        NULL,
        NULL,
        it_2725_Logic64_Reflected,
        it_2725_Logic64_Clanked,
        it_2725_Logic64_Absorbed,
        it_2725_Logic64_ShieldBounced,
        it_2725_Logic64_HitShield,
        it_2725_Logic64_EvtUnk,
    },
    {
        // Zelda din fire
        ItemStateTable_ZeldaDinFire,
        NULL,
        it_2725_Logic65_Destroyed,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic65_Reflected,
        it_2725_Logic65_Clanked,
        it_2725_Logic65_Absorbed,
        NULL,
        NULL,
        it_2725_Logic65_EvtUnk,
    },
    {
        // Zelda din fire explode
        it_803F7740,
        NULL,
        it_2725_Logic66_Destroyed,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic66_Clanked,
        it_2725_Logic66_Absorbed,
        it_2725_Logic66_ShieldBounced,
        it_2725_Logic66_HitShield,
        it_2725_Logic66_EvtUnk,
    },
    {
        // Mewtwo disable
        it_803F7750,
        NULL,
        it_2725_Logic67_Destroyed,
        NULL,
        NULL,
        NULL,
        it_2725_Logic67_DmgDealt,
        NULL,
        NULL,
        it_2725_Logic67_Reflected,
        it_2725_Logic67_Clanked,
        it_2725_Logic67_Absorbed,
        it_2725_Logic67_ShieldBounced,
        it_2725_Logic67_HitShield,
        it_2725_Logic67_EvtUnk,
    },
    {
        // Peach toad spore
        it_803F7548,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic92_DmgDealt,
        NULL,
        NULL,
        it_2725_Logic68_Reflected,
        it_2725_Logic68_Clanked,
        it_2725_Logic68_Absorbed,
        it_2725_Logic68_ShieldBounced,
        it_2725_Logic68_HitShield,
        it_2725_Logic92_EvtUnk,
    },
    {
        // Mewtwo shadow ball
        it_803F7760,
        NULL,
        it_2725_Logic101_Destroyed,
        it_2725_Logic101_PickedUp,
        NULL,
        NULL,
        it_2725_Logic101_DmgDealt,
        NULL,
        NULL,
        it_2725_Logic101_Reflected,
        it_2725_Logic101_Clanked,
        it_2725_Logic101_Absorbed,
        it_2725_Logic101_ShieldBounced,
        it_2725_Logic101_HitShield,
        it_2725_Logic101_EvtUnk,
    },
    {
        // Ice Climbers string (belay)
        it_803F76B8,
        NULL,
        NULL,
        it_2725_Logic70_PickedUp,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic70_EvtUnk,
    },
    {
        // Game & Watch greenhouse (insecticide spray)
        it_803F7898,
        NULL,
        it_2725_Logic71_Destroyed,
        it_2725_Logic71_PickedUp,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic71_EvtUnk,
    },
    {
        // Game & Watch manhole
        it_803F78D8,
        NULL,
        it_2725_Logic72_Destroyed,
        it_2725_Logic72_PickedUp,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic72_EvtUnk,
    },
    {
        // Game & Watch fire
        it_803F78E8,
        NULL,
        it_2725_Logic73_Destroyed,
        it_2725_Logic73_PickedUp,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic73_EvtUnk,
    },
    {
        // Game & Watch parachute
        it_803F78F8,
        NULL,
        it_2725_Logic74_Destroyed,
        it_2725_Logic74_PickedUp,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic74_EvtUnk,
    },
    {
        // Game & Watch turtle
        it_803F7918,
        NULL,
        it_2725_Logic75_Destroyed,
        it_2725_Logic75_PickedUp,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic75_EvtUnk,
    },
    {
        // Game & Watch breath
        it_803F7938,
        NULL,
        it_2725_Logic76_Destroyed,
        it_2725_Logic76_PickedUp,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic76_EvtUnk,
    },
    {
        // Game & Watch judge
        it_803F7968,
        NULL,
        it_2725_Logic77_Destroyed,
        it_2725_Logic77_PickedUp,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic77_EvtUnk,
    },
    {
        // Game & Watch panic
        it_803F79A0,
        NULL,
        it_2725_Logic78_Destroyed,
        it_2725_Logic78_PickedUp,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic78_EvtUnk,
    },
    {
        // Game & Watch chef
        it_803F79E0,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic112_DmgDealt,
        NULL,
        NULL,
        it_2725_Logic112_Reflected,
        it_2725_Logic112_Clanked,
        it_2725_Logic112_Absorbed,
        it_2725_Logic112_ShieldBounced,
        it_2725_Logic112_HitShield,
        it_2725_Logic112_EvtUnk,
    },
    {
        // Young Link milk
        it_803F7A28,
        NULL,
        NULL,
        it_2725_Logic80_PickedUp,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic80_EvtUnk,
    },
    {
        // Game & Watch rescue
        it_803F79C0,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic81_EvtUnk,
    },
    {
        // Master Hand laser
        it_803F9378,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic84_EvtUnk,
    },
    {
        // Master Hand bullet
        it_803F9388,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic83_DmgDealt,
        NULL,
        NULL,
        it_2725_Logic83_Reflected,
        it_2725_Logic83_Clanked,
        it_2725_Logic83_Absorbed,
        it_2725_Logic83_ShieldBounced,
        it_2725_Logic83_HitShield,
        it_2725_Logic85_EvtUnk,
    },
    {
        // Crazy Hand laser
        it_803F9378,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic84_EvtUnk,
    },
    {
        // Crazy Hand bullet
        it_803F9388,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic85_EvtUnk,
    },
    {
        // Crazy Hand bomb
        it_803F93A8,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic86_DmgDealt,
        NULL,
        NULL,
        it_2725_Logic86_Reflected,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic86_EvtUnk,
    },
    {
        it_803F6788,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic87_DmgDealt,
        NULL,
        NULL,
        it_2725_Logic87_Reflected,
        it_2725_Logic87_Clanked,
        it_2725_Logic87_Absorbed,
        it_2725_Logic87_ShieldBounced,
        it_2725_Logic87_HitShield,
        it_2725_Logic87_EvtUnk,
    },
    {
        it_803F75D0,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic88_DmgDealt,
        NULL,
        NULL,
        it_2725_Logic88_Reflected,
        it_2725_Logic88_Clanked,
        it_2725_Logic88_Absorbed,
        it_2725_Logic88_ShieldBounced,
        it_2725_Logic88_HitShield,
        it_2725_Logic88_EvtUnk,
    },
    {
        it_803F75C0,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic89_DmgDealt,
        NULL,
        NULL,
        it_2725_Logic89_Reflected,
        it_2725_Logic89_Clanked,
        it_2725_Logic89_Absorbed,
        it_2725_Logic89_ShieldBounced,
        it_2725_Logic89_HitShield,
        it_2725_Logic89_EvtUnk,
    },
    {
        it_803F7668,
        NULL,
        it_2725_Logic90_Destroyed,
        NULL,
        NULL,
        NULL,
        it_2725_Logic90_DmgDealt,
        NULL,
        NULL,
        it_2725_Logic90_Reflected,
        it_2725_Logic90_Clanked,
        it_2725_Logic90_Absorbed,
        it_2725_Logic90_ShieldBounced,
        it_2725_Logic90_HitShield,
        it_2725_Logic90_EvtUnk,
    },
    {
        it_803F7528,
        NULL,
        it_2725_Logic91_Destroyed,
        it_2725_Logic91_PickedUp,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic91_EvtUnk,
    },
    {
        it_803F7548,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic92_DmgDealt,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic92_EvtUnk,
    },
    {
        it_803F67D0,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic94_Clanked,
        NULL,
        NULL,
        it_2725_Logic94_Reflected,
        it_2725_Logic94_Clanked,
        it_2725_Logic94_Absorbed,
        it_2725_Logic94_ShieldBounced,
        it_2725_Logic94_HitShield,
        it_2725_Logic94_EvtUnk,
    },
    {
        it_803F67D0,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic94_Clanked,
        NULL,
        NULL,
        it_2725_Logic94_Reflected,
        it_2725_Logic94_Clanked,
        it_2725_Logic94_Absorbed,
        it_2725_Logic94_ShieldBounced,
        it_2725_Logic94_HitShield,
        it_2725_Logic94_EvtUnk,
    },
    {
        it_803F6CA8,
        NULL,
        NULL,
        it_2725_Logic96_PickedUp,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic96_EvtUnk,
    },
    {
        it_803F6CA8,
        NULL,
        NULL,
        it_2725_Logic96_PickedUp,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic96_EvtUnk,
    },
    {
        it_803F6A28,
        NULL,
        it_2725_Logic98_Destroyed,
        it_2725_Logic98_PickedUp,
        NULL,
        NULL,
        it_2725_Logic98_DmgDealt,
        NULL,
        NULL,
        it_2725_Logic98_Reflected,
        it_2725_Logic98_Clanked,
        NULL,
        NULL,
        it_2725_Logic98_HitShield,
        it_2725_Logic98_EvtUnk,
    },
    {
        it_803F6A28,
        NULL,
        it_2725_Logic98_Destroyed,
        it_2725_Logic98_PickedUp,
        NULL,
        NULL,
        it_2725_Logic98_DmgDealt,
        NULL,
        NULL,
        it_2725_Logic98_Reflected,
        it_2725_Logic98_Clanked,
        NULL,
        NULL,
        it_2725_Logic98_HitShield,
        it_2725_Logic98_EvtUnk,
    },
    {
        it_803F6E98,
        NULL,
        it_2725_Logic100_Destroyed,
        it_2725_Logic100_PickedUp,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic100_EvtUnk,
    },
    {
        it_803F6E98,
        NULL,
        it_2725_Logic100_Destroyed,
        it_2725_Logic100_PickedUp,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic100_EvtUnk,
    },
    {
        it_803F7760,
        NULL,
        it_2725_Logic101_Destroyed,
        it_2725_Logic101_PickedUp,
        NULL,
        NULL,
        it_2725_Logic101_DmgDealt,
        NULL,
        NULL,
        it_2725_Logic101_Reflected,
        it_2725_Logic101_Clanked,
        it_2725_Logic101_Absorbed,
        it_2725_Logic101_ShieldBounced,
        it_2725_Logic101_HitShield,
        it_2725_Logic101_EvtUnk,
    },
    {
        it_803F6B70,
        NULL,
        it_2725_Logic102_Destroyed,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic102_Reflected,
        it_2725_Logic102_Clanked,
        it_2725_Logic102_Absorbed,
        NULL,
        NULL,
        it_2725_Logic102_EvtUnk,
    },
    {
        it_803F6F40,
        NULL,
        it_2725_Logic103_Destroyed,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic103_Clanked,
        it_2725_Logic103_Absorbed,
        it_2725_Logic103_ShieldBounced,
        it_2725_Logic103_HitShield,
        it_2725_Logic103_EvtUnk,
    },
    {
        it_803F7190,
        NULL,
        it_2725_Logic106_Destroyed,
        NULL,
        NULL,
        NULL,
        it_2725_Logic106_DmgDealt,
        NULL,
        NULL,
        it_2725_Logic106_Reflected,
        it_2725_Logic106_Clanked,
        it_2725_Logic106_Absorbed,
        it_2725_Logic106_ShieldBounced,
        it_2725_Logic106_HitShield,
        it_2725_Logic106_EvtUnk,
    },
    {
        it_803F71D8,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic107_DmgDealt,
        NULL,
        NULL,
        it_2725_Logic107_Reflected,
        it_2725_Logic107_Clanked,
        it_2725_Logic107_Absorbed,
        it_2725_Logic107_ShieldBounced,
        it_2725_Logic107_HitShield,
        it_2725_Logic107_EvtUnk,
    },
    {
        it_803F7190,
        NULL,
        it_2725_Logic106_Destroyed,
        NULL,
        NULL,
        NULL,
        it_2725_Logic106_DmgDealt,
        NULL,
        NULL,
        it_2725_Logic106_Reflected,
        it_2725_Logic106_Clanked,
        it_2725_Logic106_Absorbed,
        it_2725_Logic106_ShieldBounced,
        it_2725_Logic106_HitShield,
        it_2725_Logic106_EvtUnk,
    },
    {
        it_803F71D8,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic107_DmgDealt,
        NULL,
        NULL,
        it_2725_Logic107_Reflected,
        it_2725_Logic107_Clanked,
        it_2725_Logic107_Absorbed,
        it_2725_Logic107_ShieldBounced,
        it_2725_Logic107_HitShield,
        it_2725_Logic107_EvtUnk,
    },
    {
        it_803F7288,
        NULL,
        it_2725_Logic108_Destroyed,
        it_2725_Logic108_PickedUp,
        NULL,
        NULL,
        it_2725_Logic108_DmgDealt,
        NULL,
        NULL,
        it_2725_Logic108_Reflected,
        it_2725_Logic108_Clanked,
        it_2725_Logic108_Absorbed,
        it_2725_Logic108_ShieldBounced,
        it_2725_Logic108_HitShield,
        it_2725_Logic108_EvtUnk,
    },
    {
        it_803F6F50,
        NULL,
        it_2725_Logic109_Destroyed,
        NULL,
        NULL,
        NULL,
        it_2725_Logic109_DmgDealt,
        it_2725_Logic109_DmgReceived,
        NULL,
        it_2725_Logic109_Reflected,
        it_2725_Logic109_Clanked,
        NULL,
        it_2725_Logic109_ShieldBounced,
        it_2725_Logic109_HitShield,
        it_2725_Logic109_EvtUnk,
    },
    {
        it_803F70A8,
        NULL,
        NULL,
        it_2725_Logic110_PickedUp,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic110_EvtUnk,
    },
    {
        ItemStateTable_KoopaFlame,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic111_DmgDealt,
        NULL,
        NULL,
        it_2725_Logic111_Reflected,
        it_2725_Logic111_Clanked,
        it_2725_Logic111_Absorbed,
        it_2725_Logic111_ShieldBounced,
        it_2725_Logic111_HitShield,
        it_2725_Logic111_EvtUnk,
    },
    {
        it_803F79E0,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic112_DmgDealt,
        NULL,
        NULL,
        it_2725_Logic112_Reflected,
        it_2725_Logic112_Clanked,
        it_2725_Logic112_Absorbed,
        it_2725_Logic112_ShieldBounced,
        it_2725_Logic112_HitShield,
        it_2725_Logic112_EvtUnk,
    },
    {
        it_803F7958,
        NULL,
        it_2725_Logic113_Destroyed,
        it_2725_Logic113_PickedUp,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic113_EvtUnk,
    },
    {
        it_803F94A0,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic114_DmgReceived,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic114_EvtUnk,
    },
    {
        // Unk4
        it_803F8BD8,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic115_DmgDealt,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic115_EvtUnk,
    },
    {
        // Coin
        it_803F93C8,
        it_2725_Logic116_Spawned,
        it_2725_Logic116_Destroyed,
        it_2725_Logic116_PickedUp,
        it_2725_Logic116_Thrown,
        it_2725_Logic116_Thrown,
        NULL,
        it_2725_Logic116_DmgReceived,
        it_2725_Logic116_EnteredAir,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic116_EvtUnk,
    },
    {
        // Pokemon random
        it_803F8C8C,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic117_DmgDealt,
        it_2725_Logic117_DmgReceived,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic117_EvtUnk,
    },
};

// Monster and Stage-specific Items
struct sdata_ItemGXLink it_803F4CA8[30] = {
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, NULL,
};

struct ItemLogicTable it_803F4D20[ARRAY_SIZE(it_803F4CA8)] = {
    {
        // Old Goomba (old-Kuri)
        it_803F8320,
        it_802D73F0,
        it_2725_Logic9_Destroyed,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic0_DmgReceived,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802D84D8,
    },
    {
        // Target (Mato)
        it_803F83E0,
        it_802D84F8,
        it_2725_Logic9_Destroyed,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802D85F4,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        // Yoshi's Story Shy Guy (Heiho)
        it_803F83F0,
        it_802D8688,
        it_2725_Logic9_Destroyed,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802D8EC8,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802D9A0C,
    },
    {
        // Koopa Troopa (Green) (Nokonoko)
        it_803F85F0,
        it_802DC69C,
        it_2725_Logic9_Destroyed,
        it_802DD4F4,
        it_802DD59C,
        it_802DD67C,
        NULL,
        it_2725_Logic3_DmgReceived,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802DD7D0,
    },
    {
        // Koopa Troopa (Red) (Patapata)
        it_803F88C0,
        it_802E05A0,
        it_2725_Logic9_Destroyed,
        it_2725_Logic4_PickedUp,
        it_2725_Logic4_Dropped,
        it_2725_Logic4_Thrown,
        NULL,
        it_2725_Logic4_DmgReceived,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802E16D8,
    },
    {
        // Like-Like (likelike)
        it_803F8468,
        it_802D9BA8,
        it_2725_Logic5_Destroyed,
        it_2725_Logic5_PickedUp,
        it_2725_Logic5_Dropped,
        it_2725_Logic5_Thrown,
        NULL,
        it_2725_Logic5_DmgReceived,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802E16D8,
    },
    {
        // Old Redead (old-lead) [invalid]
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        // Old Octorok (old-octa) [invalid]
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        // Old Ottosea (old-otto)
        it_803F89C8,
        it_802E2470,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic8_DmgReceived,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        // Polar Bear (whitebea)
        it_803F8A88,
        it_802E37BC,
        it_2725_Logic9_Destroyed,
        it_2725_Logic9_PickedUp,
        it_2725_Logic9_Dropped,
        it_2725_Logic9_Thrown,
        NULL,
        it_802E3884,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802E4A24,
    },
    {
        // Klaptrap (klap)
        it_803F8940,
        it_802E1820,
        it_2725_Logic10_Destroyed,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic10_DmgReceived,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802E2450,
    },
    {
        // Green Shell (zgshell)
        it_803F86C8,
        it_802DE040,
        it_2725_Logic11_Destroyed,
        it_2725_Logic11_PickedUp,
        it_2725_Logic11_Dropped,
        it_2725_Logic11_Thrown,
        it_2725_Logic11_DmgDealt,
        it_2725_Logic11_DmgReceived,
        it_2725_Logic11_EnteredAir,
        it_2725_Logic11_Reflected,
        it_2725_Logic11_Clanked,
        NULL,
        it_2725_Logic11_ShieldBounced,
        it_2725_Logic11_HitShield,
        it_802DFED4,
    },
    {
        // Red Shell (green act) (zrshell)
        it_803F87F0,
        it_802E02E8,
        it_2725_Logic12_Destroyed,
        it_2725_Logic12_PickedUp,
        it_2725_Logic12_Dropped,
        it_2725_Logic12_Thrown,
        it_2725_Logic12_DmgDealt,
        it_2725_Logic12_DmgReceived,
        it_2725_Logic12_EnteredAir,
        it_2725_Logic12_Reflected,
        it_2725_Logic12_Clanked,
        NULL,
        it_2725_Logic12_ShieldBounced,
        it_2725_Logic12_HitShield,
        it_802E0468,
    },
    {
        // Tingle (Tincle) (on balloon)
        it_803F9000,
        it_802EB5C8,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic13_DmgDealt,
        it_2725_Logic13_DmgReceived,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802EC850,
    },
    {
        // [Invalid]
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        // [Invalid]
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        // [Invalid]
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        // Whispy Apple
        it_803F91D0,
        NULL,
        NULL,
        it_802EEA08,
        it_802EEA70,
        it_802EEB28,
        it_802EEED0,
        NULL,
        it_2725_Logic18_EnteredAir,
        it_802EEF10,
        it_802EEED8,
        NULL,
        it_802EEF68,
        it_802EEF30,
        it_802EEF88,
    },
    {
        // Whispy's Healing Apple
        it_803F91D0,
        NULL,
        NULL,
        it_802EEA08,
        it_802EEA70,
        it_802EEB28,
        it_802EEED0,
        NULL,
        it_2725_Logic18_EnteredAir,
        it_802EEF10,
        it_802EEED8,
        NULL,
        it_802EEF68,
        it_802EEF30,
        it_802EEF88,
    },
    {
        // [Invalid]
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        // [Invalid]
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        // [Invalid]
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        // Tool (Flatzone)
        it_803F9260,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic22_DmgDealt,
        it_2725_Logic22_DmgReceived,
        NULL,
        it_2725_Logic22_Reflected,
        it_2725_Logic22_Clanked,
        it_2725_Logic22_Absorbed,
        it_2725_Logic22_ShieldBounced,
        it_2725_Logic22_HitShield,
        it_802EFA24,
    },
    {
        // [Invalid]
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        // [Invalid]
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        // Birdo (Kyasarin)
        it_803F90D0,
        it_802ECE90,
        it_2725_Logic25_Destroyed,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802EDDC0,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802EE1E0,
    },
    {
        // Arwing Laser
        it_803F8DE8,
        NULL,
        it_802E79C8,
        NULL,
        NULL,
        NULL,
        it_802E838C,
        NULL,
        NULL,
        it_802E8420,
        it_802E838C,
        it_802E8418,
        it_802E85F4,
        it_802E8784,
        NULL,
    },
    {
        // Great Fox's Laser
        it_803F8FD0,
        it_802EB1EC,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic27_DmgDealt,
        NULL,
        NULL,
        it_2725_Logic27_Reflected,
        it_2725_Logic27_Clanked,
        it_2725_Logic27_Absorbed,
        NULL,
        NULL,
        it_802EB5A8,
    },
    {
        // Birdo's Egg
        it_803F9328,
        NULL,
        NULL,
        it_2725_Logic28_PickedUp,
        it_2725_Logic28_Dropped,
        it_2725_Logic28_Thrown,
        it_2725_Logic28_DmgDealt,
        it_802F022C,
        NULL,
        it_2725_Logic28_Reflected,
        it_2725_Logic28_Clanked,
        NULL,
        it_2725_Logic28_ShieldBounced,
        it_2725_Logic28_HitShield,
        it_802F0320,
    },
    {
        // NULL
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
};

static char it_803F5428;
HSD_ObjAllocUnk4 it_804A0E30;
HSD_ObjAllocUnk6 it_804A0E50;
HSD_ObjAllocUnk6 it_804A0E60;
// u8 it_804A0E70[0xF0];
// Article* it_804A0F60[30];
// static char it_804D5188[] = "src/sysdolphin/baselib/jobj.h"; // ?
// static char it_804D5190[] = "jobj";
static char it_804D5198;
// static char it_804D519C[]; // Not sure of type
// static char it_804D51A4[]; // Not sure of type
static char it_804D51B8;
static char it_804D51C0;
static ItCmd it_804D51C8[2] = {
    it_80279AF0,
    it_80279B10,
};
// static char it_804D51D0[]; // Not sure of type
// static char it_804D51D8[]; // Not sure of type
// static char it_804D51E0[];
// static char it_804D51E8[];

// s8 it_804D6D00; // Not sure of type
struct Fighter_804D653C_t* it_804D6D04;
// s32 it_804D6D08; // Not sure of type
// s32 it_804D6D0C; // Not sure of type
// u32 it_804D6D10; // Not sure of type
// u32it_804D6D14; // Not sure of type
// u32 it_804D6D18; // Not sure of type
// u8 it_804D6D1C; // Not sure of type
// Article* it_804D6D20[]; // Not sure of type
// Article** it_804D6D24;
// ItemCommonData* it_804D6D28; // 8 bytes instead of 4 for some reason
// Article** it_804D6D30; // 8 bytes instead of 4 for some reason
// Article** it_804D6D38; // 8 bytes instead of 4 for some reason
f32* it_804D6D40;

// static f32 it_804DC708 = 0.0f;
// static f32 it_804DC70C = 0.00001f;
// static f32 it_804DC710 = 1.0f;
// static f32 it_804DC714 = -1.0f;
// static f64 it_804DC718 = M_PI_2;
// static f64 const it_804DC720 = U32_TO_F32;
// static f32 it_804DC728 = 0.01f;
// static f32 it_804DC72C = deg_to_rad;
// static f32 it_804DC730 = 1.0f;
// static f32 it_804DC734 = 0.0f;
// static f32 it_804DC738 = 1.0f;
extern f32 it_804DC73C; // = 0.0f;
// static f32 it_804DC740 = -1.0f;
static f32 it_804DC744 = 1.0f;
// static f64 const it_804DC748 = S32_TO_F32;
// static f32 it_804DC750 = 1.5f;
// static f32 it_804DC754 = 0.00001f;
// static f64 it_804DC758 = 0.5f;
// static f64 it_804DC760 = 3.0f;
// static f32 it_804DC768 = 0.85f;
static const f32 it_804DC76C = 0.01f;
static f32 it_804DC770 = 0.0f;
// static f32 it_804DC774 = 1.0f;
// static f32 it_804DC778 = 2.0f;
// static f32 it_804DC77C = 0.5f;
// static f64 it_804DC780 = M_PI;
// static f64 it_804DC788 = 0.0f;
// static f32 it_804DC790 = 0.003906f;
// static f64 it_804DC798 = U32_TO_F32;
// static f64 it_804DC7A0 = S32_TO_F32;
// static f32 it_804DC7A8 = 1.0f;
// static f32 it_804DC7AC = 0.0f;
// static f32 it_804DC7B0 = F32_MAX;
// static f32 it_804DC7B8 = 0.0f;
// static f32 it_804DC7BC = -1.0f;
// static f32 it_804DC7C0 = 1.0f;
// static f32 it_804DC7C4 = 0.001f;
// static f64 it_804DC7C8 = M_PI_2;
// static f32 it_804DC7D0 = 0.0f;
// static f32 it_804DC7D4 = 1.0f;
// static f32 it_804DC7D8 = deg_to_rad;
// static f64 it_804DC7E0 = S32_TO_F32;
// static f32 it_804DC7E8 = M_PI_2;
// static f32 it_804DC7EC = 0.1f;
// static f64 it_804DC7F0 = 10.0f;
static const f64 it_804DC7F8 = 0.5f;
// static f32 it_804DC800 = 30.0f;
// static f32 it_804DC804= 10.0f;
// static f64 it_804DC808 = M_PI_2;
// static f32 it_804DC810 = deg_to_rad;
// static f64 it_804DC818 = 3.0f;
// static f32 it_804DC820 = -1.0f;
// static f32 0.00000000680742f = 0.00000000680742f;
// static f32 it_804DC828 = 2.0f;
// static f32 it_804DC82C = 0.5f;

typedef enum PokemonKind {
    Pokemon_ID_Tosakinto,   // Goldeen (Tosakinto)
    Pokemon_ID_Chicorita,   // Chikorita (Chicorita)
    Pokemon_ID_Kabigon,     // Snorlax (Kabigon)
    Pokemon_ID_Kamex,       // Blastoise (Kamex)
    Pokemon_ID_Matadogas,   // Weezing (Matadogas)
    Pokemon_ID_Lizardon,    // Charizard (Lizardon)
    Pokemon_ID_Fire,        // Moltres (Fire)
    Pokemon_ID_Thunder,     // Zapdos (Thunder)
    Pokemon_ID_Freezer,     // Articuno (Freezer)
    Pokemon_ID_Sonans,      // Wobbuffet (Sonans)
    Pokemon_ID_Hassam,      // Scizor (Hassam)
    Pokemon_ID_Unknown,     // Unown (Unknown)
    Pokemon_ID_Entei,       // Entei
    Pokemon_ID_Raikou,      // Raikou
    Pokemon_ID_Suikun,      // Suicune (Suikun)
    Pokemon_ID_Kireihana,   // Bellossom (Kireihana)
    Pokemon_ID_Marumine,    // Electrode (Marumine)
    Pokemon_ID_Lugia,       // Lugia
    Pokemon_ID_Houou,       // Ho-oh (Houou)
    Pokemon_ID_Metamon,     // Ditto (Metamon)
    Pokemon_ID_Pippi,       // Clefairy (Pippi)
    Pokemon_ID_Togepy,      // Togepi (Togepy)
    Pokemon_ID_Mew,         // Mew
    Pokemon_ID_Cerebi,      // Celebi (Cerebi)
    Pokemon_ID_Hitodeman,   // Staryu (Hitodeman)
    Pokemon_ID_Lucky,       // Chansey (Lucky)
    Pokemon_ID_Porygon2,    // Porygon2
    Pokemon_ID_Hinoarashi,  // Cyndaquil (Hinoarashi)
    Pokemon_ID_Maril,       // Marill (Maril)
    Pokemon_ID_Fushigibana, // Venusaur (Fushigibana)
} PokemonKind;

static inline void it_8027129C_by_4(Item_GObj* item_gobj)
{
    u32 cnt;

    for (cnt = 0; cnt < 4; cnt++) {
        it_8027129C(item_gobj, cnt);
    }
}

void it_80272560(Item_GObj* item_gobj, s32 idx)
{
    Item* item;
    s32 stack[2];

    item = item_gobj->user_data;
    lbColl_80008428(&item->x5D4_hitboxes[idx].hit);
    item->xDAA_flag.b2 = false;

    it_8027129C_by_4(item_gobj);
}

void it_802725D4(Item_GObj* item_gobj)
{
    u32 i;
    Item* item = item_gobj->user_data;

#if 1
    u8* var_r31 = ((u8*) item);

    for (i = 0; i < 4; ++i) {
        lbColl_80008428((HitCapsule*) (var_r31 + (i * 0x13c) + 0x5d4));
    }
#else
    for (i = 0; i < 4; ++i) {
        lbColl_80008428(&item->x5D4_hitboxes[i].hit);
    }
#endif

    for (i = 0; i < 4; ++i) {
        it_8027129C(item_gobj, i);
    }
    // lol. 0xDC8 should probably be split into 4 bitfields
    item->xDC8_word.flags.x16 = 0;
    item->xDAA_flag.b2 = 0;
}

void it_80272674(Item_GObj* item_gobj, s32 idx)
{
    HitCapsuleState state;
    Item* item = item_gobj->user_data;
    HitCapsule* hitbox;

    lbColl_80008434(&item->x5D4_hitboxes[idx].hit);
    item->xDC8_word.flags.x16 = 1;

    item = GET_ITEM((HSD_GObj*) item_gobj);
    hitbox = &item->x5D4_hitboxes[idx].hit;
    state = hitbox->state;

    switch (state) {
    case HitCapsule_Enabled:
        lb_8000B1CC(hitbox->jobj, &hitbox->b_offset, &hitbox->x4C);
        hitbox->x58 = hitbox->x4C;
        hitbox->state = 2;
        item->xDAA_flag.b2 = 1;
        return;
    case HitCapsule_Unk2:
        hitbox->state = 3;
        /* fallthrough */
    case HitCapsule_Unk3:
        hitbox->x58 = hitbox->x4C;
        lb_8000B1CC(hitbox->jobj, &hitbox->b_offset, &hitbox->x4C);
        /* fallthrough */
    case 4: // HitCapsule_Max
    case HitCapsule_Disabled:
        return;
    }
}

static inline void it_80272784_inline(Item_GObj* item_gobj)
{
    u32 i;

    for (i = 0; i < 4; ++i) {
        it_8027129C(item_gobj, i);
    }
}

void it_80272784(Item_GObj* item_gobj)
{
    u32 i;
    Item* item = GET_ITEM((HSD_GObj*) item_gobj);

#if 1
    u8* var_r31 = ((u8*) item);

    for (i = 0; i < 4; ++i) {
        lbColl_80008434((HitCapsule*) (var_r31 + (i * 0x13c) + 0x5d4));
    }
#else
    for (i = 0; i < 4; ++i) {
        lbColl_80008434(&item->x5D4_hitboxes[i].hit);
    }
#endif

    item->xDC8_word.flags.x16 = 1;
    it_80272784_inline(item_gobj);
}

Fighter* it_80272818(Item* item)
{
    return ((it_2728_DatAttrs*) item->xC4_article_data->x4_specialAttributes)
        ->fighter;
}

// Returns Item_GObj of the specified kind if part of HSD_GObj_Entities->items
Item_GObj* it_80272828(ItemKind kind)
{
    Item_GObj* item_gobj_return;
    Item_GObj* item_gobj_check;

    item_gobj_return = NULL;
    item_gobj_check = (Item_GObj*) HSD_GObj_Entities->items;
    while (item_gobj_check != NULL) {
        if (((Item*) item_gobj_check->user_data)->kind == kind) {
            item_gobj_return = item_gobj_check;
        }

        item_gobj_check = item_gobj_check->next;
    }
    return item_gobj_return;
}

void it_80272860(Item_GObj* item_gobj, f32 arg1, f32 arg2)
{
    Item* item;
    f32 var_f3;
    s32 var_r0;
    s32 var_r3;

    item = item_gobj->user_data;
    // if these aren't ternaries it allocates registers differently .-.
    var_r0 = arg1 < 0.0f ? -1 : 1;

    var_f3 = item->x40_vel.y;

    var_r3 = var_f3 < 0.0f ? -1 : 1;

    if (var_r3 != var_r0) {
        if (var_f3 < 0.0f) {
            var_f3 = -var_f3;
        }
        if (var_f3 < arg2) {
        label_1:
            item->x40_vel.y -= arg1;
            return;
        }
        return;
    }
    // big dumb
    goto label_1;
}

void it_802728C8(Item_GObj* item_gobj)
{
    u32 rem;
    HSD_JObj* item_jobj2;
    HSD_JObj* item_jobj1;
    PAD_STACK(12);

    item_jobj1 = GET_JOBJ((HSD_GObj*) item_gobj);
    item_jobj2 = item_jobj1 == NULL ? NULL : item_jobj1->child;
    rem = (u32) (s32) ((Item*) item_gobj->user_data)->xD44_lifeTimer %
          it_804D6D28->x44_float;
    if (rem != 0) {
        HSD_JObjClearFlagsAll(item_jobj2, 0x10U);
        return;
    }
    HSD_JObjSetFlagsAll(item_jobj2, 0x10U);
}

void it_80272940(Item_GObj* item_gobj)
{
    HSD_JObj* item_jobj2;
    HSD_JObj* item_jobj1;

    item_jobj1 = GET_JOBJ((HSD_GObj*) item_gobj);
    item_jobj2 = item_jobj1 == NULL ? NULL : item_jobj1->child;
    HSD_JObjClearFlagsAll(item_jobj2, 0x10U);
}

// void it_80272980(Item_GObj* item_gobj, f32 arg1) {
void it_80272980(Item_GObj* item_gobj)
{
    f32 dir;
    f32 vel_x;
    s32 int_dir;
    Item* item;

    item = item_gobj->user_data;
    vel_x = item->x40_vel.x;
    if (vel_x < 0.0f) {
        vel_x = -vel_x;
    }
    if (!(vel_x < 0.00001f) || !item->facing_dir) {
        if (item->x40_vel.x >= 0.0f) {
            dir = 1.0f;
        } else {
            dir = -1.0f;
        }
        item->facing_dir = dir;
    }

    if (-1.0f == item->facing_dir) {
        int_dir = -1;
    } else {
        int_dir = 1;
    }
    mpCollSetFacingDir(&item->x378_itemColl, int_dir);
}

void it_80272A18(HSD_JObj* item_jobj)
{
    HSD_JObjClearFlagsAll(item_jobj, 0x10U);
}

void it_80272A3C(HSD_JObj* item_jobj)
{
    HSD_JObjSetFlagsAll(item_jobj, 0x10U);
}

void it_80272A60(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    efSync_Spawn(0x40E, item_gobj, &item->pos);
    Item_8026AE84(item, 0x74, 0x7F, 0x40);
    it_80274C60(item_gobj);
}

void it_80272AC4(Item_GObj* item_gobj, Vec3* arg1)
{
    Item* item;
    Vec3* temp;

    item = item_gobj->user_data;
    // mut add + return i guess?
    temp = lbVector_Add(arg1, &item->pos);
    efSync_Spawn(0x40C, item_gobj, arg1);
    Item_8026AE84(item, 0x74, 0x7F, 0x40);
    it_80274C60(item_gobj);
}

void it_80272B40(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    efSync_Spawn(0x40C, item_gobj, &item->pos);
    Item_8026AE84(item, 0x74, 0x7F, 0x40);
    it_80274C60(item_gobj);
}

void it_80272BA4(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    efSync_Spawn(0x411, item_gobj, &item->pos);
    Item_8026AE84(item, 0x73, 0x7F, 0x40);
    it_80274C60(item_gobj);
}

void it_80272C08(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    efSync_Spawn(0x410, item_gobj, &item->pos);
    Item_8026AE84(item, 0x74, 0x7F, 0x40);
    it_80274C60(item_gobj);
}

bool it_80272C6C(Item_GObj* item_gobj)
{
    return lb_8000B09C(item_gobj->hsd_obj);
}

HSD_JObj* it_80272C90(Item_GObj* item_gobj)
{
    return it_80272CC0(
        item_gobj, ((Item*) item_gobj->user_data)
                       ->xC4_article_data->x10_modelDesc->x8_bone_attach_id);
}

static inline HSD_JObj* jobj_child(HSD_JObj* jobj)
{
    if (jobj == NULL) {
        return NULL;
    } else {
        return jobj->child;
    }
}

HSD_JObj* it_80272CC0(Item_GObj* item_gobj, enum_t idx)
{
    Item* item = GET_ITEM(item_gobj);
    HSD_JObj* jobj = GET_JOBJ(item_gobj);
    if (item->xC4_article_data->x10_modelDesc->x4_bone_count != 0) {
        return item->xBBC_dynamicBoneTable->bones[idx];
    }
    if (idx != 0) {
        for (; idx > 0; --idx) {
            jobj = jobj_child(jobj);
        }
    }

    return jobj;
}

/// Check if the HSD_GObj* class is an item
bool it_80272D1C(Item_GObj* item_gobj)
{
    if ((item_gobj != NULL) && (item_gobj->classifier == HSD_GOBJ_CLASS_ITEM))
    { // ITEM_UNK_ENEMY?
        return true;
    }
    return false;
}

s32 it_80272D40(Item_GObj* item_gobj)
{
    bool chk;

    if (ftLib_80086960((HSD_GObj*) item_gobj)) {
        return 0;
    }
    if ((item_gobj != NULL) && (item_gobj->classifier == HSD_GOBJ_CLASS_ITEM))
    { // ITEM_UNK_ENEMY?
        chk = true;
    } else {
        chk = false;
    }
    if (chk) {
        return 1;
    }
    return 2;
}

bool itColl_BounceOffVictim(Item_GObj* item_gobj)
{
    Item* item;
    ItemCommonData* val;

    item = item_gobj->user_data;
    // needs x58-x60 to be f32 type, otherwise requires pointer casting
    item->x40_vel.x *= it_804D6D28->x58_float;
    val = it_804D6D28;
    item->x40_vel.y = (item->x40_vel.y * val->x5C_float) + val->x60_float;
    return (bool) val; // i have no idea what this means
}

void it_80272DE4(HSD_JObj* jobj, f32 scale)
{
    HSD_JObjAddScaleX(jobj, scale);
    HSD_JObjAddScaleY(jobj, scale);
    HSD_JObjAddScaleZ(jobj, scale);
}

void it_80272F7C(HSD_JObj* jobj, f32 scale)
{
    Vec3 temp;

    temp.x = temp.y = temp.z = scale;
    HSD_JObjSetScale(jobj, &temp);
}

bool it_80273030(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->x40_vel.x = -item->x40_vel.x * item->xC70;
    item->x40_vel.y = -item->x40_vel.y * item->xC70;
    item->facing_dir = -item->facing_dir;
    item->xD44_lifeTimer = item->xD48_halfLifeTimer;
    return false;
}

bool itColl_BounceOffShield(Item_GObj* item_gobj)
{
    Item* item;
    f32 dir;
    f32 vel_x;
    s32 int_dir;
    PAD_STACK(4);

    item = GET_ITEM((HSD_GObj*) item_gobj);
    lbVector_Mirror(&item->x40_vel, &item->xC58);
    item = item_gobj->user_data;
    vel_x = item->x40_vel.x;
    if (vel_x < 0.0f) {
        vel_x = -vel_x;
    }
    if (!(vel_x < 0.00001f) || !item->facing_dir) {
        if (item->x40_vel.x >= 0.0f) {
            dir = 1.0f;
        } else {
            dir = -1.0f;
        }
        item->facing_dir = dir;
    }
    if (-1.0f == item->facing_dir) {
        int_dir = -1;
    } else {
        int_dir = 1;
    }
    mpCollSetFacingDir(&item->x378_itemColl, int_dir);
    return false;
}

bool it_80273130(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xD44_lifeTimer--;
    if (item->xD44_lifeTimer <= 0.0f) {
        return true;
    }
    return false;
}

void it_80273168(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    if (!(item->xDCD_flag.b2)) {
        Item_8026AE84(item, item->xD70, 0x7F, 0x40);
    }
}

void it_802731A4(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    if (!(item->xDCD_flag.b2)) {
        Item_8026AE84(item, item->xD78, 0x7F, 0x40);
    }
}

void it_802731E0(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    if (!(item->xDCD_flag.b2)) {
        Item_8026AE84(item, item->xD74, 0x7F, 0x40);
    }
}

void it_8027321C(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    if (!item->xDCD_flag.b2) {
        if (item->kind == It_Kind_Unk4) {
            lbAudioAx_80023870(item->xD84, 0x7F, 0x40, 0x9A);
            return;
        }
        Item_8026AE84(item, item->xD84, 0x7F, 0x40);
    }
}

void it_8027327C(Item_GObj* item_gobj, enum_t ID1, enum_t ID2)
{
    Item* item;

    item = item_gobj->user_data;
    if (ID1 != -1) {
        it_802787B4(item_gobj, ID1);
    }
    if (!item->xDCD_flag.b2) {
        it_802732E4(item, ID2);
        if (ID2 == 0x12F) {
            lbAudioAx_80024DC4(ID2);
        }
    }
}

void it_802732E4(Item* item, s32 arg1)
{
    if (!item->xDCD_flag.b2) {
        Item_8026AE84(item, arg1, 0x7F, 0x40);
    }
}

void it_80273318(Item_GObj* item_gobj, HSD_Joint* joint, s32 arg2)
{
    Item* item = GET_ITEM(item_gobj);
    item->xC8_joint = joint;
    HSD_GObjObject_80390B0C((HSD_GObj*) item_gobj);
    Item_802680CC((HSD_GObj*) item_gobj);
    Item_8026849C((HSD_GObj*) item_gobj);
    HSD_JObjSetTranslate(item_gobj->hsd_obj, &item->pos);
}

void it_80273408(Item_GObj* item_gobj)
{
    it_80273454(item_gobj);
    it_8027346C(item_gobj);
    it_80273484(item_gobj);
    it_8027349C(item_gobj);
    it_802734B4(item_gobj);
}

void it_80273454(Item_GObj* item_gobj)
{
    Item* item = item_gobj->user_data;

    item->x40_vel.x = item->x40_vel.y = item->x40_vel.z = 0.0f;
}

void it_8027346C(Item_GObj* item_gobj)
{
    Item* item = item_gobj->user_data;

    item->x64_vec_unk2.x = item->x64_vec_unk2.y = item->x64_vec_unk2.z = 0.0f;
}

void it_80273484(Item_GObj* item_gobj)
{
    Item* item = item_gobj->user_data;

    item->x58_vec_unk.x = item->x58_vec_unk.y = item->x58_vec_unk.z = 0.0f;
}

void it_8027349C(Item_GObj* item_gobj)
{
    Item* item = item_gobj->user_data;

    item->x70_nudge.x = item->x70_nudge.y = item->x70_nudge.z = 0.0f;
}

void it_802734B4(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    item->x7C.x = item->x7C.y = item->x7C.z = 0.0f;
    item->x88.x = item->x88.y = item->x88.z = 0.0f;
    item->x94.x = item->x94.y = item->x94.z = 0.0f;
    item->xA0.x = item->xA0.y = item->xA0.z = 0.0f;
    item->xAC_unk.x = item->xAC_unk.z = 0.0f;
    item->xAC_unk.y = 1.0f;
}

void it_80273500(Item_GObj* item_gobj, Vec3* arg1)
{
    Item* item = GET_ITEM(item_gobj);
    item->x40_vel.x = arg1->x;
    item->x40_vel.y = arg1->y;
    item->x40_vel.z = arg1->z;
    it_8027346C(item_gobj);
    it_80273484(item_gobj);
    it_8027349C(item_gobj);
    it_802734B4(item_gobj);
}

void it_80273598(Item_GObj* item_gobj, s32 arg1, s32 arg2)
{
    Item* item = GET_ITEM(item_gobj);
    if (item->owner != NULL && ftLib_80086960(item->owner)) {
        ftLib_80086D40(item->owner, arg1, arg2);
    }
}

void it_80273600(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    if (item->owner != NULL && ftLib_80086960(item->owner)) {
        ftLib_80086E68(item->owner);
    }
}

void it_80273648(Item_GObj* item_gobj, s32 arg1, s32 arg2)
{
    ftLib_80086DC4(arg1, arg2);
}

void it_80273670(Item_GObj* item_gobj, int arg1, f32 arg8)
{
    HSD_JObj* item_jobj1;
    HSD_JObj* item_jobj2;
    Item* item;
    HSD_Joint* joint;
    ItemStateDesc* desc;

    item = GET_ITEM((HSD_GObj*) item_gobj);
    item_jobj1 = GET_JOBJ((HSD_GObj*) item_gobj);
    item->xD0_itemStateDesc =
        &(item->xC4_article_data->xC_itemStates->x0_itemStateDesc[arg1]);
    if (item->xD0_itemStateDesc != NULL) {
        HSD_JObjRemoveAnimAll(item_jobj1);
        joint = item->xC8_joint;
        if (joint != NULL) {
            if (item_jobj1 == NULL) {
                item_jobj2 = NULL;
            } else {
                item_jobj2 = item_jobj1->child;
            }
            lb_8000B804(item_jobj2, joint->child);
        }
        desc = item->xD0_itemStateDesc;
        HSD_JObjAddAnimAll(item_jobj1, desc->x0_anim_joint,
                           desc->x4_matanim_joint,
                           (HSD_ShapeAnimJoint*) desc->x8_parameters);
        lb_8000BA0C(item_jobj1, item->x5D0_animFrameSpeed);
        HSD_JObjReqAnimAll(item_jobj1, arg8);
    }
    HSD_JObjAnimAll(item_jobj1);
    HSD_JObjRemoveAnimAll(item_jobj1);
    item->x524_cmd.u = NULL;
}

void it_80273748(Item_GObj* item_gobj, Vec3* pos, Vec3* vel)
{
    Item* item;
    HSD_JObj* jobj2;
    f32 rotation;
    f32 dir_radians;
    f32 dir;
    f32 vel_x;
    s32 hold_kind;
    s32 int_dir;
    Vec3 sp54;
    Vec3 sp48;
    Vec3 sp3C;
    HSD_JObj* jobj_2;
    Item* item_2;
    HSD_GObj* owner;
    HSD_JObj* jobj;
    PAD_STACK(32);

    item = GET_ITEM(item_gobj);
    jobj = GET_JOBJ(item_gobj);
    owner = item->owner;
    it_80275070(item_gobj,
                item->xC4_article_data->x10_modelDesc->x8_bone_attach_id);
    if (!it_8026B6C8(item_gobj)) {
        it_8026B390(item_gobj);
    }
    it_802756E0(item_gobj);
    item_2 = item_gobj->user_data;
    jobj_2 = item_gobj->hsd_obj;
    rotation = it_80274990(item_gobj);
    lb_8000B804(jobj_2, item_2->xC8_joint);
    Item_8026849C((HSD_GObj*) item_gobj);
    it_80274658(item_gobj, rotation);
    if (item->xDC8_word.flags.x0) {
        owner = (HSD_GObj*) item->x51C;
    }
    item->x40_vel = *vel;
    item->x40_vel.x *= item->xCC_item_attr->x4_throw_speed_mul;
    item->x40_vel.y *= item->xCC_item_attr->x4_throw_speed_mul;
    item->x40_vel.z *= item->xCC_item_attr->x4_throw_speed_mul;
    {
        Item* item = item_gobj->user_data;
        vel_x = item->x40_vel.x;
        if (vel_x < 0.0f) {
            vel_x = -vel_x;
        }
        if (!(vel_x < 0.00001f) || (!item->facing_dir)) {
            if (item->x40_vel.x >= 0.0f) {
                dir = 1.0f;
            } else {
                dir = -1.0f;
            }
            item->facing_dir = dir;
        }
        if (-1.0f == item->facing_dir) {
            int_dir = -1;
        } else {
            int_dir = 1;
        }
        mpCollSetFacingDir(&item->x378_itemColl, int_dir);
    }
    if (item->xDC8_word.flags.x19 == 1) {
        dir_radians = M_PI_2 * item->facing_dir;
        HSD_JObjSetRotationY(jobj, dir_radians);
    }
    if (((it_8026B2B4(item_gobj) == 1) &&
         (hold_kind = item->hold_kind, (hold_kind != 4)) &&
         (hold_kind != 6)) ||
        (item->hold_kind == 8))
    {
        jobj2 = it_80272C90(item_gobj);
        HSD_JObjGetTranslation(jobj2, &sp3C);
        sp3C.x = -sp3C.x;
        sp3C.y = -sp3C.y;
        sp3C.z = -sp3C.z;
        lb_8000B1CC(ftLib_80086630((Fighter_GObj*) owner, item->xDC4), &sp3C,
                    &sp54);
        lb_8000B1CC(ftLib_80086630((Fighter_GObj*) owner, item->xDC4), NULL,
                    &sp48);
        sp3C.x = sp54.x - sp48.x;
        sp3C.y = sp54.y - sp48.y;
        sp3C.z = 0.0f;
    } else {
        sp3C.x = sp3C.y = sp3C.z = 0.0f;
    }
    item->pos.x = pos->x + sp3C.x;
    item->pos.y = pos->y + sp3C.y;
    item->pos.z = 0.0f;
    HSD_JObjSetTranslate(jobj, &item->pos);
}

void it_80273B50(Item_GObj* item_gobj, Vec3* vel)
{
    s32 stack_top[9];
    Item* item;
    HSD_GObj* owner_gobj;
    HSD_JObj* jobj;
    f32 rotation;
    f32 dir_radians;
    f32 dir;
    f32 vel_x;
    s32 hold_kind;
    Vec3 sp40;
    Vec3 sp34;
    s32 int_dir;
    Vec3* pos;
    HSD_JObj* item_jobj3;
    HSD_JObj* item_jobj1;
    Item* item3;

    item = GET_ITEM(item_gobj);
    item_jobj1 = GET_JOBJ(item_gobj);
    owner_gobj = item->owner;
    it_80275070(item_gobj,
                item->xC4_article_data->x10_modelDesc->x8_bone_attach_id);
    if (!it_8026B6C8(item_gobj)) {
        it_8026B390(item_gobj);
    }
    it_802756E0(item_gobj);
    {
        HSD_JObj* item_jobj2;
        Item* item = GET_ITEM(item_gobj);
        item_jobj2 = GET_JOBJ(item_gobj);
        rotation = it_80274990(item_gobj);
        lb_8000B804(item_jobj2, item->xC8_joint);
        Item_8026849C(item_gobj);
    }
    it_80274658(item_gobj, rotation);
    if (item->xDC8_word.flags.x0) {
        owner_gobj = item->x51C;
    }
    item->x40_vel = *vel;
    item->x40_vel.x *= item->xCC_item_attr->x4_throw_speed_mul;
    item->x40_vel.y *= item->xCC_item_attr->x4_throw_speed_mul;
    item->x40_vel.z *= item->xCC_item_attr->x4_throw_speed_mul;
    {
        Item* item2 = GET_ITEM(item_gobj);
        vel_x = item2->x40_vel.x;
        if (vel_x < 0.0f) {
            vel_x = -vel_x;
        }
        if (!(vel_x < 0.00001f) || !item2->facing_dir) {
            if (item2->x40_vel.x >= 0.0f) {
                dir = 1.0f;
            } else {
                dir = -1.0f;
            }
            item2->facing_dir = dir;
        }
        if (-1.0f == item2->facing_dir) {
            int_dir = -1;
        } else {
            int_dir = 1;
        }
        mpCollSetFacingDir(&item2->x378_itemColl, int_dir);
    }
    if (item->xDC8_word.flags.x19 == 1) {
        dir_radians = M_PI_2 * item->facing_dir;
        HSD_JObjSetRotationY(item_jobj1, dir_radians);
    }
    if (((it_8026B2B4(item_gobj) == 1) &&
         (hold_kind = item->hold_kind, (hold_kind != 4)) &&
         (hold_kind != 6)) ||
        (item->hold_kind == 8))
    {
        jobj = it_80272C90(item_gobj);
        HSD_JObjGetTranslation(jobj, &sp40);
        sp40.x = -sp40.x;
        sp40.y = -sp40.y;
        sp40.z = -sp40.z;
    } else {
        sp40.x = sp40.y = sp40.z = 0.0f;
    }
    {
        Item* item3 = GET_ITEM(item_gobj);
        HSD_JObj* item_jobj3 = GET_JOBJ(item_gobj);
        if (&sp40 != NULL) {
            lb_8000B1CC(
                ftLib_80086630((Fighter_GObj*) owner_gobj, item3->xDC4), &sp40,
                &sp34);
        } else {
            lb_8000B1CC(
                ftLib_80086630((Fighter_GObj*) owner_gobj, item3->xDC4), NULL,
                &sp34);
        }
        pos = &item3->pos;
        item3->pos.x = sp34.x;
        item3->pos.y = sp34.y;
        item3->pos.z = 0.0f;
        HSD_JObjSetTranslate(item_jobj3, pos);
    }
}

void it_80273F34(Item_GObj* item_gobj, HSD_GObj* arg_gobj2)
{
    Item* item = GET_ITEM(item_gobj);
    HSD_JObj* item_jobj = GET_JOBJ(item_gobj);
    f32 rotate;
    s32 int_dir;

    item->xDC8_word.flags.x13 = 0;
    item->xDC8_word.flags.x14 = 1;
    item->xDC4 = 0;
    item->xD54_throwNum++;
    item->xD50_landNum = 0;

    it_80275BC8(item_gobj, arg_gobj2);
    it_80274DAC(item_gobj);

    if (item->xDC8_word.flags.x19 == 1) {
        rotate = M_PI_2 * item->facing_dir;
        HSD_JObjSetRotationY(item_jobj, rotate);
    }

    if (ftLib_80086960(arg_gobj2)) {
        Item_8026A848(item_gobj, arg_gobj2);
        it_8027B070(item_gobj, arg_gobj2);
    }

    if (-1.0f == item->facing_dir) {
        int_dir = -1;
    } else {
        int_dir = 1;
    }

    mpCollSetFacingDir(&item->x378_itemColl, int_dir);
    Item_8026B074(item);
    it_802762BC(item);
    HSD_JObjSetTranslate(item_jobj, &item->pos);

    it_8027B4A4(arg_gobj2, item_gobj);
    it_8027B378(arg_gobj2, item_gobj, it_802758D4(item_gobj));
}

void it_80274198(Item_GObj* item_gobj, bool chk)
{
    Item* item;
    HSD_GObj* owner_gobj;
    HSD_GObj* x51C_gobj;

    item = item_gobj->user_data;
    owner_gobj = item->owner;
    if (item->xDC8_word.flags.x0 != 0) {
        if (chk == true) {
            x51C_gobj = item->x51C;
            item->owner = x51C_gobj;
            owner_gobj = x51C_gobj;
            item->x51C = NULL;
        } else {
            owner_gobj = item->x51C;
        }
    }
    it_80273F34(item_gobj, owner_gobj);
}

void it_802741F4(Item_GObj* item_gobj, bool chk)
{
    Item* item = GET_ITEM(item_gobj);
    HSD_GObj* owner_gobj = item->owner;
    if (item->xDC8_word.flags.x0) {
        if (chk == true) {
            HSD_GObj* x51C_gobj = item->x51C;
            item->owner = x51C_gobj;
            owner_gobj = x51C_gobj;
            item->x51C = NULL;
        } else {
            owner_gobj = item->x51C;
        }
    }
    it_80273F34(item_gobj, owner_gobj);
}

void it_80274250(Item_GObj* item_gobj, Vec3* arg1)
{
    HSD_GObj* owner_gobj;
    Item* item;
    PAD_STACK(16);

    it_80273B50(item_gobj, arg1);
    item = GET_ITEM((HSD_GObj*) item_gobj);
    owner_gobj = item->owner;
    if (item->xDC8_word.flags.x0) {
        owner_gobj = item->x51C;
    }
    it_80273F34(item_gobj, owner_gobj);
}

void it_8027429C(Item_GObj* item_gobj, Vec3* arg1)
{
    HSD_GObj* owner_gobj;
    Item* item;
    PAD_STACK(16);

    it_80273B50(item_gobj, arg1);
    item = GET_ITEM(item_gobj);
    owner_gobj = item->owner;
    if (item->xDC8_word.flags.x0) {
        HSD_GObj* x51C_gobj = item->x51C;
        owner_gobj = x51C_gobj;
        item->owner = x51C_gobj;
        item->x51C = NULL;
    }
    it_80273F34(item_gobj, owner_gobj);
}

void it_802742F4(Item_GObj* item_gobj, HSD_GObj* gobj, Fighter_Part ftpart)
{
    Item* item;
    flag32 word;
    u8 flag;

    item = item_gobj->user_data;
    lb_8000B804(item_gobj->hsd_obj, item->xC8_joint);
    Item_8026849C(item_gobj);
    if (ftLib_80086960(gobj)) {
        // word = item->xDC8_word;
        // item->xDC8_word.word = (word & ~0x1E000) | (((((word >> 0xDU) & 0xF)
        // | (1 << ftLib_80086BE0(gobj))) << 0xD) & 0x1E000);
        // item->xDC8_word.word = item->xDC8_word.word & ~0x1E000;
        // item->xDC8_word.word = (item->xDC8_word.word >> 0xDU) & 0xF;
        // item->xDC8_word.word = (((1 << ftLib_80086BE0(gobj))) << 0xD) &
        // 0x1E000; item->xDC8_word.word |= (item->xDC8_word.word >> 0xDU) &
        // 0xF; item->xDC8_word.word = item->xDC8_word.word & ~0x1E000 |
        // (item->xDC8_word.word >> 0xDU) & 0xF | (((1 <<
        // ftLib_80086BE0(gobj))) << 0xD) & 0x1E000;
        item->xDC8_word.flags.xF |= 1 << ftLib_80086BE0(gobj);
        // item->xDC8_word.word |= (item->xDC8_word.word >> 0xDU) & 0xF | (((1
        // << ftLib_80086BE0(gobj))) << 0xD) & 0x1E000; item->xDC8_word.word =
        // ((item->xDC8_word.word | ((1 << ftLib_80086BE0(gobj)))) >> 0xDU) &
        // 0xF | 0x1E000; item->xDC8_word.flags.x3 = 1;
        // item->xDC8_word.flags.xF = 0;

        // if (!(((u8) item->xDC8_word.word >> 7U) & 1)) {
        if (!item->xDC8_word.flags.x0) {
            item->owner = gobj;
        } else {
            item->x51C = gobj;
        }
        item->xDC4 = ftpart;
        item->x20_team_id = ftLib_80086EB4(gobj);
        item->xD50_landNum = 0;
        item->xDC8_word.flags.x13 = 1;
        HSD_JObjClearFlagsAll(HSD_JObjGetChild(item_gobj->hsd_obj), 16U);
        it_802756D0(item_gobj);
        it_8026B3A8(item_gobj);
        db_80225DD8(item_gobj, (Fighter_GObj*) gobj);
    }
    if (item->xDD0_flag.b6) {
        item->xDD0_flag.b6 = 0;
        item->xD40 = 0.0f;
        it_80279BBC(item);
    }
    if (item->kind < It_Kind_L_Gun_Ray) { // If a common item
        it_80275158(item_gobj, it_804D6D28->x30);
    }
    it_80274F48(item_gobj,
                item->xC4_article_data->x10_modelDesc->x8_bone_attach_id, gobj,
                ftpart);
    it_80274C88(item_gobj);
}

void it_80274484(Item_GObj* item_gobj, HSD_JObj* jobj, f32 scale)
{
    Vec3 sp1C;
    Item* item;
    f32 unused;

    item = GET_ITEM((HSD_GObj*) item_gobj);
    item->scl = scale;
    sp1C.z = item->scl;
    sp1C.y = item->scl;
    sp1C.x = item->scl;
    HSD_JObjSetScale(jobj, &sp1C);
    it_80275534(item_gobj, item->x3C);
    it_80274DFC(item_gobj);
    it_80274E44(item_gobj);
}

void it_80274574(Item_GObj* item_gobj)
{
    it_80274594(item_gobj);
}

inline void HSD_JObjSetScale_2(HSD_JObj* jobj, Vec3* scale)
{
    ((jobj) ? ((void) 0) : __assert("jobj.h", 760, "jobj"));
    jobj->scale = *scale;
    if (!(jobj->flags & (1 << 25))) {
        ftCo_800C6AFC(jobj);
    }
}

void it_80274594(Item_GObj* item_gobj)
{
    Vec3 sp18;
    Item* item = GET_ITEM((HSD_GObj*) item_gobj);
    HSD_JObj* item_jobj = GET_JOBJ(item_gobj);
    PAD_STACK(4);

    item->scl *= ftLib_80086A0C(item->owner);
    sp18.z = item->scl;
    sp18.y = item->scl;
    sp18.x = item->scl;
    HSD_JObjSetScale_2(item_jobj, &sp18);
    it_80275534(item_gobj, item->x3C);
    it_80274DFC(item_gobj);
    it_80274E44(item_gobj);
}

int it_80274658(Item_GObj* item_gobj, f32 arg1)
{
    Item* item;
    f32 spin_speed1;
    f32 spin_speed2;
    s32 dir1;
    s32 dir2;

    item = GET_ITEM(item_gobj);
    spin_speed2 = 0.0f;
    spin_speed1 = item->spin_spd;
    if (spin_speed1 != spin_speed2) {
        spin_speed2 = 0.01f * spin_speed1 * (0.017453292f * arg1);
    }
    item->xD3C_spinSpeed = spin_speed2;
    if (item->facing_dir < 0.0f) {
        dir1 = -1;
    } else {
        dir1 = 1;
    }
    if (item->x40_vel.x < 0.0f) {
        dir2 = -1;
    } else {
        dir2 = 1;
    }
    if (dir2 != dir1) {
        item->xD3C_spinSpeed = -item->xD3C_spinSpeed;
    }
    if (item->xDC8_word.flags.x19 != 1) {
        item->xD3C_spinSpeed *= -item->facing_dir;
    }
    return dir2;
}

HSD_JObj* it_802746F8(Item_GObj* item_gobj)
{
    u32 bit_chk;
    s32 var_ctr;
    HSD_JObj* item_jobj2;
    HSD_JObj* item_jobj1;

    item_jobj1 = item_gobj->hsd_obj;
    bit_chk = (((Item*) item_gobj->user_data)
                   ->xC4_article_data->x10_modelDesc->xC_bit_field >>
               6U) &
              3;
    if (bit_chk != 0) {
        for (var_ctr = bit_chk; var_ctr > 0; var_ctr--) {
            if (item_jobj1 == NULL) {
                item_jobj2 = NULL;
            } else {
                item_jobj2 = item_jobj1->child;
            }
            item_jobj1 = item_jobj2;
        }
    }
    return item_jobj1;
}

void it_80274740(Item_GObj* item_gobj)
{
    HSD_JObj* item_jobj;
    Item* item;
    u32 bit_chk;
    s32 var_ctr;
    PAD_STACK(24);

    item = item_gobj->user_data;
    item_jobj = item_gobj->hsd_obj;
    bit_chk = (item->xC4_article_data->x10_modelDesc->xC_bit_field >> 6U) & 3;
    if (bit_chk != 0) {
        for (var_ctr = bit_chk; var_ctr > 0; var_ctr--) {
            if (item_jobj == NULL) {
                item_jobj = NULL;
            } else {
                item_jobj = item_jobj->child;
            }
        }
    }
    item->xD3C_spinSpeed = 0.0f;
    if (item->xDC8_word.flags.x17 == 0) {
        HSD_JObjSetRotationZ(item_jobj, item->xD3C_spinSpeed);
    } else if (item->xDC8_word.flags.x17 == 1) {
        HSD_JObjSetRotationX(item_jobj, item->xD3C_spinSpeed);
    } else {
        HSD_JObjSetRotationY(item_jobj, item->xD3C_spinSpeed);
    }
}

f32 it_80274990(Item_GObj* item_gobj)
{
    u32 bit_chk;
    s32 var_ctr;
    Item* item;
    HSD_JObj* item_jobj;
    PAD_STACK(48);

    item = item_gobj->user_data;
    item_jobj = item_gobj->hsd_obj;
    bit_chk = (item->xC4_article_data->x10_modelDesc->xC_bit_field >> 6U) & 3;
    if (bit_chk != 0) {
        for (var_ctr = bit_chk; var_ctr > 0; var_ctr--) {
            if (item_jobj == NULL) {
                item_jobj = NULL;
            } else {
                item_jobj = item_jobj->child;
            }
        }
    }
    if (item->xDC8_word.flags.x17 == 0) {
        return HSD_JObjGetRotationZ(item_jobj);
    }
    if (item->xDC8_word.flags.x17 == 1) {
        return HSD_JObjGetRotationX(item_jobj);
    }
    return HSD_JObjGetRotationY(item_jobj);
}

void it_80274A64(Item_GObj* item_gobj)
{
    HSD_JObj* item_jobj;
    Item* item;
    u32 bit_chk;
    s32 var_ctr;
    PAD_STACK(24);

    item = item_gobj->user_data;
    item_jobj = item_gobj->hsd_obj;
    bit_chk = (item->xC4_article_data->x10_modelDesc->xC_bit_field >> 6U) & 3;
    if (bit_chk != 0) {
        for (var_ctr = bit_chk; var_ctr > 0; var_ctr--) {
            if (item_jobj == NULL) {
                item_jobj = NULL;
            } else {
                item_jobj = item_jobj->child;
            }
        }
    }
    if (item->xDC8_word.flags.x17 == 0) {
        HSD_JObjAddRotationZ(item_jobj, item->xD3C_spinSpeed);
    } else if (item->xDC8_word.flags.x17 == 1) {
        HSD_JObjAddRotationX(item_jobj, item->xD3C_spinSpeed);
    } else {
        HSD_JObjAddRotationY(item_jobj, item->xD3C_spinSpeed);
    }
}

void it_80274C60(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xDC8_word.flags.xC = 0;
}

bool it_80274C78(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    return item->xDC8_word.flags.xC;
}

void it_80274C88(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xDD0_flag.b0 = 0;
    item->xDAA_flag.b3 = 0;
}

void it_80274CAC(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xDD0_flag.b0 = 1;
    if (db_ShowEnemyStompRange() != 0) {
        item->xDAA_flag.b3 = 1;
    }
}

void it_80274D04(Item_GObj* item_gobj, struct lb_80014638_arg1_t* arg1)
{
    Vec3 sp20;
    Vec3 sp14;
    PAD_STACK(4);

    it_8026BB88(item_gobj, &sp20);
    it_8026BBCC(item_gobj, &sp14);
    arg1->unk_x = sp20.x - sp14.x;
    arg1->unk_y = sp20.y - sp14.y;
}

void it_80274D6C(Item_GObj* arg0)
{
    Item* item = GET_ITEM(arg0);

    float right_x = item->x378_itemColl.ecb.right.x;
    float right_y = item->x378_itemColl.ecb.right.y;
    float left_x = item->x378_itemColl.ecb.left.x;
    float top_y = item->x378_itemColl.ecb.top.y;

    item->xB54.x8.y = right_x + item->pos.x;
    item->xB54.x8.x = left_x + item->pos.x;
    item->xB54.x8.z = right_y + item->pos.y + top_y;
}

void it_80274DAC(Item_GObj* arg0)
{
    Item* temp_r4 = GET_ITEM(arg0);
    temp_r4->xB54.unk_x = 0.0F;
    temp_r4->xB54.unk_y = 0.0F;
    {
        Item* item = GET_ITEM(arg0);
        float right_x = item->x378_itemColl.ecb.right.x;
        float right_y = item->x378_itemColl.ecb.right.y;
        float left_x = item->x378_itemColl.ecb.left.x;
        float top_y = item->x378_itemColl.ecb.top.y;

        item->xB54.x8.y = right_x + item->pos.x;
        item->xB54.x8.x = left_x + item->pos.x;
        item->xB54.x8.z = right_y + item->pos.y + top_y;
    }
}

void it_80274DFC(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xBCC_unk.x *= item->scl;
    item->xBCC_unk.y *= item->scl;
    item->xBD4_grabRange.x *= item->scl;
    item->xBD4_grabRange.y *= item->scl;
}

void it_80274E44(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xBEC.top *= item->scl;
    item->xBEC.bottom *= item->scl;
    item->xBEC.right *= item->scl;
    item->xBEC.left *= item->scl;
    item->xBDC.top *= item->scl;
    item->xBDC.bottom *= item->scl;
    item->xBDC.right *= item->scl;
    item->xBDC.left *= item->scl;
}

void it_80274ECC(Item_GObj* item_gobj, bool arg1)
{
    ((Item*) item_gobj->user_data)->xD09 = arg1;
}

void it_80274ED8(void)
{
    it_804D6D0C++;
}

void it_80274EE8(u32 arg0)
{
    it_804D6D08++;
}

void it_80274EF8(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xDC8_word.flags.x2 = 0;
}

void it_80274F10(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xDC8_word.flags.x2 = 1;
}

void it_80274F28(Item* item, s8 arg1, HSD_GObjEvent arg2,
                 HSD_GObjInteraction arg3)
{
    item->xDD0_flag.b5 = 1;
    item->xD08 = arg1;
    item->grab_dealt = arg2;
    item->grabbed_for_victim = arg3;
}

inline HSD_JObj* get_bone_by_id(Item_GObj* item_gobj, int bone_id)
{
    Item* item = GET_ITEM(item_gobj);
    HSD_JObj* jobj = GET_JOBJ(item_gobj);
    if (item->xC4_article_data->x10_modelDesc->x4_bone_count) {
        jobj = item->xBBC_dynamicBoneTable->bones[bone_id];
    } else if (bone_id != 0) {
        while (bone_id-- > 0) {
            if (jobj == NULL) {
                jobj = NULL;
            } else {
                jobj = jobj->child;
            }
        }
    }
    return jobj;
}

void it_80274F48(Item_GObj* item_gobj, s32 bone_id, HSD_GObj* arg2_gobj,
                 Fighter_Part part_idx)
{
    u8 _[8];
    HSD_JObj* jobj = get_bone_by_id(item_gobj, bone_id);
    lb_8000C2F8(jobj, ftLib_80086630(arg2_gobj, part_idx));
}

void it_80274FDC(Item_GObj* item_gobj, s32 bone_id, Fighter_GObj* arg2_gobj,
                 Fighter_Part part_idx)
{
    u8 _[8];
    HSD_JObj* jobj = get_bone_by_id(item_gobj, bone_id);
    lb_8000C1C0(jobj, ftLib_80086630(arg2_gobj, part_idx));
}

void it_80275070(Item_GObj* item_gobj, s32 bone_id)
{
    u8 _[8];
    HSD_JObj* jobj = get_bone_by_id(item_gobj, bone_id);
    lb_8000C390(jobj);
}

bool it_802750E8(Item_GObj* item_gobj, s32 mask)
{
    Item* item = GET_ITEM(item_gobj);
    return item->xDC0 & mask;
}

void it_802750F8(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xDCC_flag.b3 = 0;
    Item_802697D4((HSD_GObj*) item_gobj);
    Item_80269978((HSD_GObj*) item_gobj);
    item->xDCC_flag.b3 = 1;
}

/// Set both life timers on the item
void it_80275158(Item_GObj* item_gobj, f32 lifetime)
{
    Item* item;

    item = GET_ITEM((HSD_GObj*) item_gobj);
    item->xD44_lifeTimer = lifetime;
    item->xD48_halfLifeTimer = lifetime * it_804D6D28->x4C_float;
}

void it_80275174(Item_GObj* item_gobj, f32 lifetime)
{
    ((Item*) item_gobj->user_data)->xD48_halfLifeTimer =
        lifetime * it_804D6D28->x4C_float;
}

void it_8027518C(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xD44_lifeTimer = it_804D6D28->xF8;
    item->xDCF_flag.b2 = 1;
    item->xDD1_flag.b0 = 1;
    it_8026BDB4(item_gobj);
}

bool it_802751D8(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xD44_lifeTimer--;
    if (item->xD44_lifeTimer <= 0.0f) {
        return true;
    }
    return false;
}

void it_80275210(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xDC8_word.flags.x1C = 1;
}

void it_80275228(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xDC8_word.flags.x1C = 0;
}

void it_80275240(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xDC8_word.flags.x1E = 0;
}

void it_80275258(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xDD0_flag.b4 = 0;
}

void it_80275270(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xDD0_flag.b4 = 1;
}

void it_80275288(Item_GObj* item_gobj, s32 arg1, s32 arg2)
{
    Item* item = GET_ITEM(item_gobj);
    int val = arg2 + HSD_Randi(arg1);
    Item_8026AE84(item, val, 127, 64);
}

void it_802752D8(Item_GObj* item_gobj, s32 arg1, s32 arg2)
{
    Item* item = GET_ITEM(item_gobj);
    int val = arg2 + HSD_Randi(arg1);
    Item_8026AFA0(item, val, 127, 64);
}

void it_80275328(HSD_GObj* gobj, ItemLink* arg1)
{
    arg1->prev = NULL;
    arg1->next = NULL;
    arg1->x8_vel.z = 0.0f;
    arg1->x8_vel.y = 0.0f;
    arg1->x8_vel.x = 0.0f;
    arg1->pos.z = 0.0f;
    arg1->pos.y = 0.0f;
    arg1->pos.x = 0.0f;
    arg1->x20_vec.z = 0.0f;
    arg1->x20_vec.y = 0.0f;
    arg1->x20_vec.x = 0.0f;
    arg1->flag0 = 0;
    arg1->flag1 = 0;
    arg1->flag2 = 0;
    arg1->unk = 0;
    arg1->x1D0_GObj = gobj;
    arg1->x1D4_JObj = NULL;
}

void it_80275390(Item_GObj* item_gobj)
{
    ((Item*) item_gobj->user_data)->owner = NULL;
    it_8026B3A8(item_gobj);
}

void it_802753BC(Item_GObj* item_gobj, s16 arg1)
{
    Item* item;

    item = item_gobj->user_data;
    item->xC94 = 0;
    item->xC9C = arg1;
    item->xCA0 = 0;
    item->xCA4 = 0;
}

void it_802753DC(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xC34_damageDealt = 0;
    item->xC40 = 1.0f;
    item->xC44 = 1.0f;
    item->xC3C = 1.0f;
    item->xC48 = 0;
    item->xC4C = 0;
    item->xC50 = 0;
    item->xDCE_flag.b6 = 0;
}

void it_80275414(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xDCD_flag.b7 = 1;
}

void it_8027542C(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xDCD_flag.b7 = 0;
}

void it_80275444(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xDCD_flag.b5 = 1;
    item->xDCD_flag.b7 = 1;
    item->xDCD_flag.b6 = 1;
}

void it_80275474(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xDCD_flag.b5 = 0;
    item->xDCD_flag.b7 = 0;
    item->xDCD_flag.b6 = 0;
}

void it_802754A4(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xDCE_flag.b2 = 1;
}

void it_802754BC(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xDCE_flag.b2 = 0;
}

void it_802754D4(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xDCE_flag.b0 = 1;
    item->xDCE_flag.b2 = 1;
    item->xDCE_flag.b1 = 1;
}

void it_80275504(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xDCE_flag.b0 = 0;
    item->xDCE_flag.b2 = 0;
    item->xDCE_flag.b1 = 0;
}

void it_80275534(Item_GObj* item_gobj, f32 scale)
{
    Item* item;
    HitCapsule* hitcapsule;
    u32 var_ctr;

    item = item_gobj->user_data;
    for (var_ctr = 0U; var_ctr < 4U; var_ctr++) {
        hitcapsule = &item->x5D4_hitboxes[var_ctr].hit;
        if (hitcapsule->state != HitCapsule_Disabled) {
            hitcapsule->scale = scale;
        }
    }
}

void it_80275594(Item_GObj* item_gobj, s32 idx, f32 mult)
{
    Item* item;
    HitCapsule* hitcapsule;

    item = item_gobj->user_data;
    hitcapsule = &item->x5D4_hitboxes[idx].hit;
    if (hitcapsule->state != HitCapsule_Disabled) {
        hitcapsule->scale *= mult;
    }
}

void it_802755C0(Item_GObj* item_gobj, f32 scale)
{
    Item* item;
    HitCapsule* hitcapsule;
    u32 var_ctr;

    item = item_gobj->user_data;
    for (var_ctr = 0U; var_ctr < 4U; var_ctr++) {
        hitcapsule = &item->x5D4_hitboxes[var_ctr].hit;
        if (hitcapsule->state != HitCapsule_Disabled) {
            hitcapsule->scale *= scale;
        }
    }
}

void it_80275640(Item_GObj* item_gobj, f32 arg1)
{
    Item* item = GET_ITEM(item_gobj);
    u32 i;

    for (i = 0; i < 4; i++) {
        HitCapsule* hitcapsule = &item->x5D4_hitboxes[i].hit;
        if (hitcapsule->state != HitCapsule_Disabled) {
            it_80272460(hitcapsule, hitcapsule->damage * arg1, item_gobj);
        }
    }
}

void it_802756D0(Item_GObj* item_gobj)
{
    ((Item*) item_gobj->user_data)->xD0C = 2;
}

void it_802756E0(Item_GObj* item_gobj)
{
    ((Item*) item_gobj->user_data)->xD0C = 0;
    it_802714C0(item_gobj);
}

void it_8027570C(Item_GObj* item_gobj, s32 idx)
{
    Item* item;

    item = item_gobj->user_data;
    item->x5D4_hitboxes[idx].hit.x40_b0 = 0;
}

void it_8027572C(Item_GObj* item_gobj, s32 idx)
{
    Item* item;

    item = item_gobj->user_data;
    item->x5D4_hitboxes[idx].hit.x40_b0 = 1;
}

#pragma push
#pragma dont_inline on

void it_8027574C(Item_GObj* item_gobj)
{
    Item* item = item_gobj->user_data;
    it_80274D04(item_gobj, &item->xB54);
    it_80274D6C(item_gobj);
}

#pragma pop

void it_80275788(Item_GObj* item_gobj)
{
#if 0
    Item* item;
    HitCapsule* hitcapsule;
    u32 var_ctr;

    item = item_gobj->user_data;
    for (var_ctr = 0U; var_ctr < 4U; var_ctr++) {
        hitcapsule = &item->x5D4_hitboxes[var_ctr].hit;
        if (hitcapsule->state != HitCapsule_Disabled) {
            hitcapsule->state = HitCapsule_Max;
            item->xDAA_flag.b2 = 1;
        }
    }
#elif 1
    Item* item;
    HitCapsule* hitcapsule;
    u32 state;
    u32 var_ctr;

    item = item_gobj->user_data;
    state = 4;
    for (var_ctr = 0U; var_ctr < 4U; var_ctr++) {
        hitcapsule = &item->x5D4_hitboxes[var_ctr].hit;
        if (hitcapsule->state != HitCapsule_Disabled) {
            hitcapsule->state = state;
            item->xDAA_flag.b2 = 1;
        }
    }
#else
    Item* item;
    HitCapsule* hitcapsule;
    u32 state;

    item = item_gobj->user_data;
    state = 4;
    hitcapsule = &item->x5D4_hitboxes[0].hit;
    if (hitcapsule->state != HitCapsule_Disabled) {
        hitcapsule->state = state;
        item->xDAA_flag.b2 = 1;
    }
    hitcapsule = &item->x5D4_hitboxes[1].hit;
    if (hitcapsule->state != HitCapsule_Disabled) {
        hitcapsule->state = state;
        item->xDAA_flag.b2 = 1;
    }
    hitcapsule = &item->x5D4_hitboxes[2].hit;
    if (hitcapsule->state != HitCapsule_Disabled) {
        hitcapsule->state = state;
        item->xDAA_flag.b2 = 1;
    }
    hitcapsule = &item->x5D4_hitboxes[3].hit;
    if (hitcapsule->state != HitCapsule_Disabled) {
        hitcapsule->state = state;
        item->xDAA_flag.b2 = 1;
    }
#endif
}

void it_80275820(Item_GObj* item_gobj, Vec3* arg1, Vec3* arg2, s32 idx)
{
    Item* item;
    HitCapsule* hitcapsule;

    item = item_gobj->user_data;
    hitcapsule = &item->x5D4_hitboxes[idx].hit;
    if (hitcapsule->state != HitCapsule_Disabled) {
        hitcapsule->x58 = *arg2;
        hitcapsule->x4C = *arg1;
    }
}

bool it_80275870(Item_GObj* item_gobj)
{
    Item* item;
    HitCapsule* hitcapsule;
    u32 var_ctr;

    item = item_gobj->user_data;
    for (var_ctr = 0U; var_ctr < 4U; var_ctr++) {
        hitcapsule = &item->x5D4_hitboxes[var_ctr].hit;
        if (hitcapsule->state != HitCapsule_Disabled) {
            return true;
        }
    }
    return false;
}

f32 it_802758D4(Item_GObj* item_gobj)
{
    Item* item;
    HitCapsule* hitcapsule;
    u32 var_ctr;
    f32 damage;
    bool disable_chk;

    item = item_gobj->user_data;
    damage = 0.0f;
    for (var_ctr = 0U; var_ctr < 4U; var_ctr++) {
        hitcapsule = &item->x5D4_hitboxes[var_ctr].hit;
        if (hitcapsule->state != HitCapsule_Disabled) {
            disable_chk = true;
            break;
        } else {
            disable_chk = false;
        }
    }

    if (disable_chk) {
        for (var_ctr = 0U; var_ctr < 4U; var_ctr++) {
            hitcapsule = &item->x5D4_hitboxes[var_ctr].hit;
            if (hitcapsule->state != HitCapsule_Disabled) {
                if (damage <= hitcapsule->damage) {
                    damage = hitcapsule->damage;
                }
            }
        }
    }
    return damage;
}

void it_802759DC(Item_GObj* item_gobj1, Item_GObj* item_gobj2)
{
    Vec3 sp44;
    f32 sp40;
    Vec3 sp34;
    CollData* coll1;
    CollData* coll2;
    Item* item1;
    f32 temp_f31;
    bool chk;
    s32 temp_r3_2;
    u8 _1[12];
    Vec3 sp1C;
    u8 _2[8];

    chk = false;
    item1 = GET_ITEM((HSD_GObj*) item_gobj1);
    sp44 = item1->pos;
    coll2 = it_8026C100(item_gobj2);
    coll1 = &item1->x378_itemColl;
    if (coll2 != NULL) {
        if (mpLib_80054ED8(coll2->floor.index)) {
            int floor_index;
            temp_r3_2 = mpLib_8005199C_Floor(&sp44, -1, -1);
            if (temp_r3_2 != -1 && (floor_index = coll2->floor.index,
                                    mpLinesConnected(temp_r3_2, floor_index)))
            {
                coll1->floor.index = temp_r3_2;
                mpLib_8004DD90_Floor(temp_r3_2, &sp44, &sp40, 0, NULL);
                // if (sp40 >= (f32) ((u8) it_804D6D28 + 0xF0)) {
                // if (sp40 >= (f32) it_804D6D28->filler[12]) {
                if (sp40 >= it_804D6D28->xF0) {
                    item1->pos.x = sp44.x;
                    item1->pos.y = sp44.y + sp40;
                    item1->pos.z = sp44.z;
                    mpColl_80043680(coll1, &item1->pos);
                    chk = true;
                    it_802762B0(item1);
                }
            }
        }
        if (!chk) {
            temp_f31 = 0.5f * (coll2->ecb.top.y + coll2->ecb.bottom.y);
            it_8026BC90(item_gobj2, &sp1C);
            sp34.x = sp1C.x + it_804DC73C;
            // sp34.x = sp1C.x + 0.0f;
            sp34.y = sp1C.y + temp_f31;
            sp34.z = sp1C.z + it_804DC73C;
            // sp34.z = sp1C.z + 0.0f;
            coll1->last_pos = sp34;
            mpColl_80043670(coll1);
            coll1->cur_pos = sp44;
            if (mpColl_800471F8(coll1)) {
                it_802762B0(item1);
                item1->pos = coll1->cur_pos;
                return;
            }
            it_802762BC(item1);
            item1->pos = sp44;
        }
    }
}

void it_80275BC8(Item_GObj* item_gobj, HSD_GObj* arg_gobj)
{
    itECB sp24;
    Item* item;
    Vec3 sp14;
    u8* it_comm_data_xE8;
    PAD_STACK(4);

    item = GET_ITEM((HSD_GObj*) item_gobj);
    sp24 = item->xBFC;
    it_802762BC(item);
    item->x378_itemColl.cur_pos = item->pos;
    if (arg_gobj != NULL) {
        switch (it_80272D40((Item_GObj*) arg_gobj)) { /* irregular */
        case 0:
            it_8026BB68((Item_GObj*) arg_gobj, &sp14);
            break;
        case 1:
            it_8026BB88((Item_GObj*) arg_gobj, &sp14);
            break;
        default:
            OSReport(it_803F1F38);
            __assert(it_803F1F58, 0x7FU, &it_804D5198);
            break;
        }
    } else {
        sp14 = item->pos;
    }

    // it_comm_data_xE8 = &it_804D6D28->filler_1a[4];
    it_comm_data_xE8 = &it_804D6D28->xE8;
    sp24.top *= *(f32*) it_comm_data_xE8;
    sp24.bottom *= *(f32*) it_comm_data_xE8;
    sp24.right *= *(f32*) it_comm_data_xE8;
    sp24.left *= *(f32*) it_comm_data_xE8;
    // temp_struct = it_804D6D28->xE8;
    // scl = ((Vec2*) temp_struct)->x;
    // sp24.top *= scl;
    // sp24.bottom *= scl;
    // sp24.right *=  scl;
    // sp24.left *= scl;

    item->xC0C = item->xC1C;

    if (item->xDCE_flag.b7 == 1) {
        it_80275D5C(item_gobj, &sp24);
    }
    it_80276100(item_gobj, &sp14);
}

void it_80275D5C(Item_GObj* item_gobj, itECB* arg_ecb)
{
    f32 scale;
    s32 int_dir;
    Item* item;
    PAD_STACK(8);

    item = GET_ITEM((HSD_GObj*) item_gobj);
    scale = item->scl;
    item->xC1C = *arg_ecb;
    mpColl_SetECBSource_Fixed(
        &item->x378_itemColl, (HSD_GObj*) item_gobj, item->xC1C.top * scale,
        item->xC1C.bottom * scale, item->xC1C.right * scale,
        item->xC1C.left * scale);
    if (-1.0f == item->facing_dir) {
        int_dir = -1;
    } else {
        int_dir = 1;
    }
    mpCollSetFacingDir(&item->x378_itemColl, int_dir);
}

void it_80275DFC(Item_GObj* item_gobj)
{
    Item* item;
    f32 scale;
    s32 int_dir;
    PAD_STACK(14);

    // item = GET_ITEM((HSD_GObj*) item_gobj);
    item = item_gobj->user_data;
    scale = item->scl;
    item->xC1C = item->xC0C;
    mpColl_SetECBSource_Fixed(
        &item->x378_itemColl, (HSD_GObj*) item_gobj, item->xC1C.top * scale,
        item->xC1C.bottom * scale, item->xC1C.right * scale,
        item->xC1C.left * scale);
    if (-1.0f == item->facing_dir) {
        int_dir = -1;
    } else {
        int_dir = 1;
    }
    mpCollSetFacingDir(&item->x378_itemColl, int_dir);
}

void it_80275E98(Item_GObj* item_gobj, SpawnItem* spawn)
{
    Item* item1;
    Item* item2;
    CollData* coll;
    ItemAttr* attr;
    ItemKind kind;
    f32 scale;
    s32 int_dir;
    PAD_STACK(18);

    item1 = item_gobj->user_data;
    attr = item1->xCC_item_attr;
    coll = &item1->x378_itemColl;
    item1->x378_itemColl.cur_pos = item1->pos;
    mpColl_80041EE4(coll);
    kind = item1->kind;
    if (kind < It_Kind_L_Gun_Ray) {
        coll->x34_flags.b1234 = 2;
    } else if (kind < It_Kind_Kuriboh) {
        coll->x34_flags.b1234 = 4;
    } else if (kind < It_Kind_Octarock_Stone) {
        coll->x34_flags.b1234 = 3;
    } else if (kind < It_Kind_Mario_Fire) {
        coll->x34_flags.b1234 = 4;
    } else if (kind < It_Kind_Unk4) {
        coll->x34_flags.b1234 = 5;
    } else if (kind < Pokemon_Random) {
        coll->x34_flags.b1234 = 5;
    } else if (kind < Pokemon_Tosakinto) {
        coll->x34_flags.b1234 = 5;
    } else if (kind < Pokemon_Chicorita_Leaf) {
        coll->x34_flags.b1234 = 5;
    } else if (kind < It_Kind_Old_Kuri) {
        coll->x34_flags.b1234 = 4;
    } else if (kind < It_Kind_Arwing_Laser) {
        coll->x34_flags.b1234 = 3;
    } else if (kind < 238) {
        coll->x34_flags.b1234 = 4;
    }

    item2 = item_gobj->user_data;
    scale = item2->scl;
    item2->xC1C = item1->xC1C;
    mpColl_SetECBSource_Fixed(
        &item2->x378_itemColl, (HSD_GObj*) item_gobj, item2->xC1C.top * scale,
        item2->xC1C.bottom * scale, item2->xC1C.right * scale,
        item2->xC1C.left * scale);
    if (-1.0f == item2->facing_dir) {
        int_dir = -1;
    } else {
        int_dir = 1;
    }
    mpCollSetFacingDir(&item2->x378_itemColl, int_dir);
    coll->x50 = attr->x1C_damage_mul;
    if (spawn->x44_flag.b0 == 1) {
        if (spawn->x48_ground_or_air == GA_Air) {
            it_80276100(item_gobj, &spawn->pos);
            return;
        }
        it_80276174(item_gobj, &spawn->pos);
        return;
    }
    coll->last_pos = spawn->pos;
    mpColl_80043670(coll);
}

void it_80276100(Item_GObj* item_gobj, Vec3* pos)
{
    Item* item = GET_ITEM(item_gobj);
    CollData* coll = &item->x378_itemColl;
    coll->last_pos = *pos;
    mpColl_80043670(coll);
    mpColl_800471F8(coll);
    item->pos = coll->cur_pos;
}

void it_80276174(Item_GObj* item_gobj, Vec3* pos)
{
    f32 unused1;
    f32 unused2;
    Vec3 temp_pos;
    Item* item;

    item = GET_ITEM((HSD_GObj*) item_gobj);
    item->x378_itemColl.last_pos = *pos;
    mpColl_80043670(&item->x378_itemColl);
    if (mpCheckMultiple(item->pos.x, item->pos.y, item->pos.x,
                        item->pos.y - it_804D6D28->xF4, &temp_pos, NULL, NULL,
                        NULL, 1, -1, -1))
    {
        item->pos = temp_pos;
    }
}

// bool it_80276214(Item_GObj* item_gobj) {}
void it_80276214(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->x378_itemColl.last_pos = item->x378_itemColl.cur_pos;
    item->x378_itemColl.cur_pos = item->pos;
    if (item->xDCE_flag.b7 == 1) {
        it_80276278(item_gobj);
    }
}

void it_80276278(Item_GObj* item_gobj)
{
    Item* item;
    CollData* coll_data;

    item = GET_ITEM((HSD_GObj*) item_gobj);
    coll_data = &item->x378_itemColl;

    mpColl_800436E4(coll_data, it_80274990(item_gobj));
}

void it_802762B0(Item* item)
{
    item->ground_or_air = GA_Ground;
}

void it_802762BC(Item* item)
{
    item->ground_or_air = GA_Air;
    item->xDC8_word.flags.x1F = 0;
}

bool it_802762D8(Item_GObj* item_gobj)
{
    CollData* coll;
    bool chk;

    chk = false;
    coll = &((Item*) item_gobj->user_data)->x378_itemColl;
    if (coll->env_flags & Collide_LeftEdge) {
        chk = true;
    }
    if (coll->env_flags & Collide_RightEdge) {
        return true;
    }
    return chk;
}

s32 it_80276308(Item_GObj* item_gobj)
{
    Item* item;
    CollData* coll;
    s32 ret_val;

    item = item_gobj->user_data;
    ret_val = 0;
    coll = &item->x378_itemColl;
    if (item->x378_itemColl.env_flags & Collide_LeftWallMask) {
        ret_val = 8;
        item->xC30 = coll->left_facing_wall.index;
    }
    if (coll->env_flags & Collide_RightWallMask) {
        item->xC30 = coll->right_facing_wall.index;
        ret_val = 4;
    }
    return ret_val;
}

s32 it_80276348(Item_GObj* item_gobj, Vec3* vec)
{
    s32 ret_val;
    Item* item;
    CollData* coll;

    item = item_gobj->user_data;
    ret_val = 0;
    coll = &item->x378_itemColl;
    if (coll->env_flags & Collide_LeftWallMask) {
        ret_val = 8;
        item->xC30 = coll->left_facing_wall.index;
        *vec = coll->left_facing_wall.normal;
    }
    if (coll->env_flags & Collide_RightWallMask) {
        item->xC30 = coll->right_facing_wall.index;
        *vec = coll->right_facing_wall.normal;
        ret_val = 4;
    }
    return ret_val;
}

bool it_802763B8(Item_GObj* item_gobj)
{
    Item* item;
    CollData* coll;
    bool chk = false;

    item = item_gobj->user_data;
    coll = &item->x378_itemColl;
    if (coll->env_flags & Collide_FloorMask) {
        item->xC30 = coll->floor.index;
        chk = true;
    }
    return chk;
}

s32 it_802763E0(Item_GObj* item_gobj)
{
    int result = 0;
    Item* item = GET_ITEM(item_gobj);
    CollData* colldata = &item->x378_itemColl;
    if ((item->x378_itemColl.env_flags & Collide_CeilingMask)) {
        item->xC30 = colldata->ceiling.index;
        result = 2;
    }
    return result;
}

#pragma push
#pragma dont_inline on
void it_80276408(Item_GObj* item_gobj, CollData* coll, Vec3* vec)
{
    if (coll->env_flags & Collide_LeftWallMask) {
        *vec = coll->left_facing_wall.normal;
    }
    if (coll->env_flags & Collide_RightWallMask) {
        *vec = coll->right_facing_wall.normal;
    }
    if (coll->env_flags & Collide_CeilingMask) {
        *vec = coll->ceiling.normal;
    }
    if (coll->env_flags & Collide_FloorMask) {
        *vec = coll->floor.normal;
    }
}
#pragma pop

f32 it_8027649C(Item_GObj* item_gobj)
{
    Vec3 sp20;
    Vec3 sp14;
    f32 angle;
    s32 int_dir;
    Item* item;
    CollData* coll;
    PAD_STACK(4);

    item = GET_ITEM((HSD_GObj*) item_gobj);
    coll = &item->x378_itemColl;
    sp14.z = 0.0f;
    sp14.x = 0.0f;
    sp14.y = 1.0f;
    if (coll->env_flags & Collide_LeftWallMask) {
        sp20 = coll->left_facing_wall.normal;
    }
    if (coll->env_flags & Collide_RightWallMask) {
        sp20 = coll->right_facing_wall.normal;
    }
    if (coll->env_flags & Collide_CeilingMask) {
        sp20 = coll->ceiling.normal;
    }
    if (coll->env_flags & Collide_FloorMask) {
        sp20 = coll->floor.normal;
    }
    angle = lbVector_Angle(&sp20, &sp14);
    if (sp20.x < 0.0f) {
        int_dir = -1;
    } else {
        int_dir = 1;
    }
    return item->facing_dir * (angle * int_dir);
}

void it_802765BC(Item_GObj* item_gobj, enum_t arg1)
{
    Vec3 sp74;
    Vec3* sp68 = NULL;
    Vec3 sp5C;
    Vec3* sp50 = NULL;
    Vec3 sp44;
    Vec3* sp38 = NULL;
    HSD_JObj* jobj;
    Item* item1;
    Item* item2;
    Item* item3;
    Item* item4;
    f32 angle1;
    f32 angle2;
    f32 angle3;
    f32 rotate_angle1;
    f32 rotate_angle2;
    f32 rotate_angle3;
    s32 dir1;
    s32 dir2;
    s32 dir3;
    u32 bit_chk;
    PAD_STACK(80);

    item1 = item_gobj->user_data;
    jobj = it_80272CC0(item_gobj, arg1);
    bit_chk = item1->xDC8_word.flags.x17;
    if (bit_chk == 0) {
        item2 = item_gobj->user_data;
        sp74.z = 0.0f;
        sp74.x = 0.0f;
        sp74.y = 1.0f;
        it_80276408(item_gobj, &item2->x378_itemColl, sp68);
        angle1 = lbVector_Angle(sp68, &sp74);
        if (sp68->x < 0.0f) {
            dir1 = -1;
        } else {
            dir1 = 1;
        }
        rotate_angle1 =
            -item1->facing_dir * (item2->facing_dir * (angle1 * dir1));
        HSD_JObjSetRotationZ(jobj, rotate_angle1);
    } else if (bit_chk == 1) {
        item3 = item_gobj->user_data;
        sp5C.z = 0.0f;
        sp5C.x = 0.0f;
        sp5C.y = 1.0f;
        it_80276408(item_gobj, &item3->x378_itemColl, sp50);
        angle2 = lbVector_Angle(sp50, &sp5C);
        if (sp50->x < 0.0f) {
            dir2 = -1;
        } else {
            dir2 = 1;
        }
        rotate_angle2 = item3->facing_dir * (angle2 * dir2);
        HSD_JObjSetRotationX(jobj, rotate_angle2);
    } else {
        item4 = item_gobj->user_data;
        sp44.z = 0.0f;
        sp44.x = 0.0f;
        sp44.y = 1.0f;
        it_80276408(item_gobj, &item4->x378_itemColl, sp38);
        angle3 = lbVector_Angle(sp38, &sp44);
        if (sp38->x < 0.0f) {
            dir3 = -1;
        } else {
            dir3 = 1;
        }
        rotate_angle3 = item4->facing_dir * (angle3 * dir3);
        HSD_JObjSetRotationY(jobj, rotate_angle3);
    }
}

void it_80276934(Item_GObj* item_gobj, enum_t arg1)
{
    Vec3 sp80;
    Vec3 sp74;
    Vec3 sp64;
    Vec3 sp58;
    Vec3 sp48;
    Vec3 sp3C;
    HSD_JObj* jobj;
    Item* item1;
    Item* item2;
    Item* item3;
    Item* item4;
    f32 angle1;
    f32 angle2;
    f32 angle3;
    f32 rotate_angle1;
    f32 rotate_angle2;
    f32 rotate_angle3;
    s32 dir1;
    s32 dir2;
    s32 dir3;
    u32 bit_chk;
    PAD_STACK(48);

    item1 = item_gobj->user_data;
    jobj = it_80272CC0(item_gobj, arg1);
    bit_chk = item1->xDC8_word.flags.x17;
    if (bit_chk == 0) {
        item2 = item_gobj->user_data;
        sp80.z = 0.0f;
        sp80.x = 0.0f;
        sp80.y = 1.0f;
        mpLineGetNormal(item2->xC30, &sp74);
        angle1 = lbVector_Angle(&sp74, &sp80);
        if (sp74.x < 0.0f) {
            dir1 = -1;
        } else {
            dir1 = 1;
        }
        rotate_angle1 =
            -item1->facing_dir * (item2->facing_dir * (angle1 * dir1));
        HSD_JObjSetRotationZ(jobj, rotate_angle1);
    } else if (bit_chk == 1) {
        item3 = item_gobj->user_data;
        sp64.z = 0.0f;
        sp64.x = 0.0f;
        sp64.y = 1.0f;
        mpLineGetNormal(item3->xC30, &sp58);
        angle2 = lbVector_Angle(&sp58, &sp64);
        if (sp58.x < 0.0f) {
            dir2 = -1;
        } else {
            dir2 = 1;
        }
        rotate_angle2 = item3->facing_dir * (angle2 * dir2);
        HSD_JObjSetRotationX(jobj, rotate_angle2);
    } else {
        item4 = item_gobj->user_data;
        sp48.z = 0.0f;
        sp48.x = 0.0f;
        sp48.y = 1.0f;
        mpLineGetNormal(item4->xC30, &sp3C);
        angle3 = lbVector_Angle(&sp3C, &sp48);
        if (sp3C.x < 0.0f) {
            dir3 = -1;
        } else {
            dir3 = 1;
        }
        rotate_angle3 = item4->facing_dir * (angle3 * dir3);
        HSD_JObjSetRotationY(jobj, rotate_angle3);
    }
}

void it_80276CB8(Item_GObj* item_gobj)
{
    if (GET_ITEM(item_gobj)->x378_itemColl.env_flags & Collide_FloorMask) {
        it_802765BC(item_gobj, 0);
    }
}

void it_80276CEC(Item_GObj* item_gobj)
{
    CollData* coll;
    Item* item;
    u32 coll_index;

    item = item_gobj->user_data;
    coll = &item->x378_itemColl;
    if (coll->env_flags & Collide_LeftWallMask) {
        item->xAC_unk = coll->left_facing_wall.normal;
        coll_index = coll->left_facing_wall.index;
    }
    if (coll->env_flags & Collide_RightWallMask) {
        item->xAC_unk = coll->right_facing_wall.normal;
        coll_index = coll->right_facing_wall.index;
    }
    if (coll->env_flags & Collide_CeilingMask) {
        item->xAC_unk = coll->ceiling.normal;
        coll_index = coll->ceiling.index;
    }
    if (coll->env_flags & Collide_FloorMask) {
        item->xAC_unk = coll->floor.normal;
        coll_index = coll->floor.index;
    }
    item->xC2C = coll_index;
}

bool it_80276D9C(Item_GObj* item_gobj, enum_t arg1)
{
    itECB sp34;
    CollData* coll;
    Item* item;
    f32 pos_x1;
    f32 pos_x2;
    f32 pos_x3;
    f32 pos_x4;
    s32 dir1;
    s32 dir2;
    bool ret_val;
    PAD_STACK(34);

    ret_val = true;
    item = item_gobj->user_data;
    coll = &item->x378_itemColl;
    if ((coll->env_flags & Collide_LeftWallMask) &&
        (coll->env_flags & Collide_RightWallMask))
    {
        // if (coll->env_flags & Collide_WallMask) {
        dir1 = 1;
    } else {
        dir1 = 0;
    }
    if (dir1 != 0) {
        sp34 = item->xC1C;
        if (coll->facing_dir == 1) {
            pos_x1 = coll->ecb.right.x - 1.0f;
            if (pos_x1 < 0.0f) {
                pos_x1 = -pos_x1;
            }
            sp34.right = pos_x1;
            pos_x2 = 1.0f + coll->ecb.left.x;
            if (pos_x2 < 0.0f) {
                pos_x2 = -pos_x2;
            }
            sp34.left = pos_x2;
        } else {
            pos_x3 = 1.0f + coll->ecb.left.x;
            if (pos_x3 < 0.0f) {
                pos_x3 = -pos_x3;
            }
            sp34.right = pos_x3;
            pos_x4 = coll->ecb.right.x - 1.0f;
            if (pos_x4 < 0.0f) {
                pos_x4 = -pos_x4;
            }
            sp34.left = pos_x4;
        }
        item->xC1C = sp34;
        mpColl_SetECBSource_Fixed(
            &item->x378_itemColl, (HSD_GObj*) item_gobj,
            item->xC1C.top * it_804DC744, item->xC1C.bottom * it_804DC744,
            item->xC1C.right * it_804DC744, item->xC1C.left * it_804DC744);
        // mpColl_SetECBSource_Fixed(&item->x378_itemColl, (HSD_GObj*)
        // item_gobj, item->xC1C.top * 1.0f, item->xC1C.bottom * 1.0f,
        // item->xC1C.right
        // * 1.0f, item->xC1C.left * 1.0f);
        if (-1.0f == item->facing_dir) {
            dir2 = -1;
        } else {
            dir2 = 1;
        }
        mpCollSetFacingDir(&item->x378_itemColl, dir2);
        return false;
    }
    if ((arg1 & 4) && (coll->prev_env_flags & Collide_RightWallMask)) {
        ret_val = false;
        item->pos.x += 1.5f;
    }
    if ((arg1 & 8) && (coll->prev_env_flags & Collide_LeftWallMask)) {
        ret_val = false;
        item->pos.x -= 1.5f;
    }
    if ((arg1 & 2) && (coll->prev_env_flags & Collide_CeilingMask)) {
        ret_val = false;
        item->pos.y -= 1.5f;
    }
    if ((arg1 & 1) && (coll->prev_env_flags & Collide_FloorMask)) {
        ret_val = false;
        item->pos.y += 1.5f;
    }
    return ret_val;
}

#pragma push
#pragma dont_inline on

void it_80276FC4(Item_GObj* item_gobj, s32 arg1)
{
    Item* it = item_gobj->user_data;
    ItemAttr* attr = it->xCC_item_attr;
    it_8027781C(item_gobj);
    if (it_80276D9C(item_gobj, arg1)) {
        it_8027321C(item_gobj);
        it_80277C40(item_gobj, arg1);
        it_80275640(item_gobj, attr->x58);
    }
}

#pragma pop

bool it_80277040(Item_GObj* item_gobj)
{
    Vec3 sp5C;
    Vec3 sp50;
    Vec3 sp44;
    Vec3 sp38;
    Vec3 sp20;
    Vec3 sp14;
    CollData* coll;
    Item* item2;
    Item* item1;
    f32 temp_f31;
    f32 temp_f30;
    f32 temp_f3;
    f32 var_f1;
    f32 angle1;
    f32 angle2;
    bool chk;
    s32 int_dir1;
    s32 int_dir3;
    bool ret_val;
    s32 int_dir2;
    s32 int_dir4;
    PAD_STACK(20);

    ret_val = true;
    item1 = GET_ITEM((HSD_GObj*) item_gobj);
    coll = &item1->x378_itemColl;
    var_f1 = item1->xCC_item_attr->x50;
    if (var_f1 < 0.0f) {
        var_f1 = -var_f1;
    }
    if (var_f1 < 0.00001f) {
        item1->x88.y = 0.0f;
        item1->x88.x = 0.0f;
        return false;
    }
    sp20.z = 0.0f;
    sp20.x = 0.0f;
    sp20.y = 1.0f;
    if (coll->env_flags & Collide_LeftWallMask) {
        sp5C = coll->left_facing_wall.normal;
    }
    if (coll->env_flags & Collide_RightWallMask) {
        sp5C = coll->right_facing_wall.normal;
    }
    if (coll->env_flags & Collide_CeilingMask) {
        sp5C = coll->ceiling.normal;
    }
    if (coll->env_flags & Collide_FloorMask) {
        sp5C = coll->floor.normal;
    }
    item1->x94 = item1->x88;
    // item1->x98 = item1->x8C;
    // item1->x9C = item1->x90;
    angle1 = lbVector_AngleXY(&sp5C, &sp20);
    if (angle1 < 0.0f) {
        angle1 = -angle1;
    }
    if (angle1 >= it_804D6D28->xC0) {
        sp50.z = 0.0f;
        sp50.x = 0.0f;
        sp50.y = -1.0f;
        lbVector_CrossprodNormalized(&sp5C, &sp50, &sp44);
        lbVector_CrossprodNormalized(&sp44, &sp5C, &sp38);
        temp_f3 = item1->xCC_item_attr->x50;
        temp_f31 = item1->x94.x / temp_f3;
        temp_f30 = item1->x94.y / temp_f3;
        item1->x88.x = sp38.x * temp_f3;
        item1->x88.y = sp38.y * temp_f3;
        item2 = item_gobj->user_data;
        it_80276408(item_gobj, &item2->x378_itemColl, &sp14);
        angle2 = lbVector_Angle(&sp14, &item2->xAC_unk);
        if (angle2 < 0.0f) {
            angle2 = -angle2;
        }
        if ((angle2 >= it_804D6D28->xC4) && (item2->xC30 == item2->xC2C)) {
            chk = true;
        } else {
            chk = false;
        }
        if (!chk) {
            if (item1->x94.x || item1->x94.y) {
                if (sp38.x < 0.0f) {
                    int_dir1 = -1;
                } else {
                    int_dir1 = 1;
                }
                if (temp_f31 < 0.0f) {
                    int_dir2 = -1;
                } else {
                    int_dir2 = 1;
                }
                if (int_dir2 == int_dir1) {
                    if (sp38.y < 0.0f) {
                        int_dir3 = -1;
                    } else {
                        int_dir3 = 1;
                    }
                    if (temp_f30 < 0.0f) {
                        int_dir4 = -1;
                    } else {
                        int_dir4 = 1;
                    }
                    if (int_dir4 != int_dir3) {
                        goto block_38;
                    }
                } else {
                block_38:
                    item1->xD58++;
                    if (item1->xD58 >= it_804D6D28->x38_float) {
                        item1->xD58 = 0;
                        ret_val = false;
                        item1->x88.y = 0.0f;
                        item1->x88.x = 0.0f;
                    }
                }
            }
        } else {
            item1->xD5C = 2;
        }
    } else {
        ret_val = false;
        item1->x88.y = 0.0f;
        item1->x88.x = 0.0f;
    }
    return ret_val;
}

void it_8027737C(Item_GObj* item_gobj, Vec3* pos)
{
    Vec3 sp1C;
    Item* item;
    f32 temp_f1;
    u8 _[4];

    item = GET_ITEM((HSD_GObj*) item_gobj);
    if (item->xDC8_word.flags.x1F && item->xD5C != 0U) {
        PSVECAdd(&item->x88, &item->x7C, &item->x7C);
        item->x7C.x *= item->xCC_item_attr->x54;
        item->x7C.y *= item->xCC_item_attr->x54;
        if (sqrtf_accurate(SQ(item->x7C.x) + SQ(item->x7C.y)) >
            it_804D6D28->xC8)
        {
            lbVector_NormalizeXY(&item->x7C);
            temp_f1 = it_804D6D28->xC8;
            item->x7C.x *= temp_f1;
            item->x7C.y *= temp_f1;
        }
        if (SQ(item->x7C.x) + SQ(item->x7C.y) < it_804D6D28->xCC) {
            item->xDC8_word.flags.x1F = 0;
            item->x7C.y = 0.0f;
            item->x7C.x = 0.0f;
            return;
        }

        it_802775F0(item_gobj, &item->x7C);
        it_80274A64(item_gobj);
        PSVECAdd(&item->x7C, pos, &sp1C);
        *pos = sp1C;
    }
}

bool it_80277544(Item_GObj* item_gobj)
{
    Vec3 sp10;
    Item* item;
    bool ret_val;

    ret_val = false;
    item = GET_ITEM((HSD_GObj*) item_gobj);
    if (item->xD5C != 0U && it_80277040(item_gobj) != 0 &&
        ((PSVECAdd(&item->x40_vel, &item->x70_nudge, &sp10),
          ((SQ(sp10.x) + SQ(sp10.y))) >= it_804D6D28->xCC) ||
         (item->xD5C == 2U)))
    {
        item->xDC8_word.flags.x1F = 1;
        ret_val = true;
        item->xD5C = 1;
    }
    return ret_val;
}

void it_802775F0(Item_GObj* item_gobj, Vec3* arg1)
{
    Item* item = GET_ITEM((HSD_GObj*) item_gobj);
    u8 _[4];

    if (item->spin_spd) {
        f32 temp_sqrt = sqrtf_accurate(SQ(arg1->x) + SQ(arg1->y));
        item->xD3C_spinSpeed = 0.85f * (temp_sqrt / item->xC1C.bottom);
        if ((arg1->x < 0 ? -1 : 1) != (item->facing_dir < 0 ? -1 : 1)) {
            item->xD3C_spinSpeed = -item->xD3C_spinSpeed;
        }
        if (item->xDC8_word.flags.x19 != 1) {
            item->xD3C_spinSpeed *= -item->facing_dir;
        }
    }
}

bool it_8027770C(Item_GObj* item_gobj)
{
    Vec3 sp38;
    f32 mult;
    bool ret_val;
    enum_t var_r5;
    Item* item;
    ItemAttr* attr;
    CollData* coll;
    PAD_STACK(44);

    var_r5 = 0;
    item = item_gobj->user_data;
    ret_val = false;
    coll = &item->x378_itemColl;
    attr = item->xCC_item_attr;
    if (coll->env_flags & Collide_LeftWallMask) {
        var_r5 = 8;
        item->xC30 = coll->left_facing_wall.index;
        sp38 = coll->left_facing_wall.normal;
    }
    if (coll->env_flags & Collide_RightWallMask) {
        var_r5 = 4;
        item->xC30 = coll->right_facing_wall.index;
        sp38 = coll->right_facing_wall.normal;
    }
    if (var_r5 != 0) {
        if (((item->x40_vel.z * sp38.z) +
             ((item->x40_vel.x * sp38.x) + (item->x40_vel.y * sp38.y))) < 0.0f)
        {
            lbVector_Mirror(&item->x40_vel, &sp38);
        }
        mult = attr->x58;
        ret_val = true;
        item->x40_vel.x *= mult;
        item->x40_vel.y *= mult;
        item->x40_vel.z *= mult;
    }
    return ret_val;
}

static inline float product_xy(Vec3* a, Vec3* b)
{
    return (a->x * b->x + a->y * b->y);
}

static inline float return_sqrt_value(Vec3* v)
{
    return sqrtf_accurate(product_xy(v, v));
}

bool it_8027781C(Item_GObj* item_gobj)
{
    Item* item;
    CollData* coll;
    ItemAttr* attr;
    // PAD_STACK(8);
    s32 stack[2];

    f32 speed;
    bool chk;
    Vec3 sp48;
    Vec3 sp3C;
    Vec3 sp30;

    item = GET_ITEM((HSD_GObj*) item_gobj);
    attr = item->xCC_item_attr;
    coll = &item->x378_itemColl;
    sp3C = it_803B8570;
    // sp3C.x = sp3C.y = sp3C.z = 0.0f;
    chk = false;
    sp30 = it_803B857C;

    speed = return_sqrt_value(&item->x40_vel);
    if ((coll->env_flags & Collide_LeftWallMask) &&
        product_xy(&item->x40_vel, &coll->left_facing_wall.normal) < 0.0f)
    {
        sp48 = item->x40_vel;
        lbVector_Mirror(&sp48, &coll->left_facing_wall.normal);
        lbVector_Add_xy(&sp30, &sp48);
        if (mpCollGetSpeedLeftWall(coll, &sp48)) {
            lbVector_Add_xy(&sp3C, &sp48);
        }
        chk = true;
    }
    if ((coll->env_flags & Collide_RightWallMask) &&
        product_xy(&item->x40_vel, &coll->right_facing_wall.normal) < 0.0f)
    {
        sp48 = item->x40_vel;
        lbVector_Mirror(&sp48, &coll->right_facing_wall.normal);
        lbVector_Add_xy(&sp30, &sp48);
        if (mpCollGetSpeedRightWall(coll, &sp48)) {
            lbVector_Add_xy(&sp3C, &sp48);
        }
        chk = true;
    }
    if ((coll->env_flags & Collide_CeilingMask) &&
        product_xy(&item->x40_vel, &coll->ceiling.normal) < 0.0f)
    {
        sp48 = item->x40_vel;
        lbVector_Mirror(&sp48, &coll->ceiling.normal);
        lbVector_Add_xy(&sp30, &sp48);
        if (mpCollGetSpeedCeiling(coll, &sp48)) {
            lbVector_Add_xy(&sp3C, &sp48);
        }
        chk = true;
    }
    if ((coll->env_flags & Collide_FloorMask) &&
        product_xy(&item->x40_vel, &coll->floor.normal) < 0.0f)
    {
        sp48 = item->x40_vel;
        lbVector_Mirror(&sp48, &coll->floor.normal);
        lbVector_Add_xy(&sp30, &sp48);
        if (mpCollGetSpeedFloor(coll, &sp48)) {
            lbVector_Add_xy(&sp3C, &sp48);
        }
        chk = true;
    }
    if (chk) {
        if (return_sqrt_value(&sp30) < it_804DC76C) {
            sp30.x = item->x40_vel.x;
            sp30.y = -1.0f * item->x40_vel.y;
        }
        lbVector_NormalizeXY(&sp30);
        speed *= attr->x58;
        sp30.x *= speed;
        sp30.y *= speed;
        item->x64_vec_unk2 = sp3C;
        item->x40_vel = sp30;

        return true;
    }
    return false;
}

void it_80277C40(Item_GObj* item_gobj, s32 arg1)
{
    Vec3 sp20;
    Vec3 sp14;
    CollData* coll;
    Item* item;

    item = GET_ITEM((HSD_GObj*) item_gobj);
    coll = &item->x378_itemColl;
    sp14.z = 0.0f;
    sp14.y = 0.0f;
    sp14.x = 0.0f;
    sp20.z = 0.0f;
    sp20.y = 0.0f;
    sp20.x = 0.0f;
    if (arg1 & 8) {
        sp20.x = coll->ecb.right.x;
        sp20.y = coll->ecb.right.y;
    }
    if (arg1 & 4) {
        sp20.x = coll->ecb.left.x;
        sp20.y = coll->ecb.left.y;
    }
    if (arg1 & 2) {
        sp20.x = coll->ecb.top.x;
        sp20.y = coll->ecb.top.y;
    }
    if (arg1 & 1) {
        sp20.x = coll->ecb.bottom.x;
        sp20.y = coll->ecb.bottom.y;
    }
    if (!item->xDCF_flag.b0) {
        it_80278800(item_gobj, 0x405, 0, &sp20, &sp14, 0U, 0.0f);
    }
}

void it_80277D08(void)
{
#if 1
    HSD_MObjInfo* mobj = (HSD_MObjInfo*) &it_803F1F90;
    hsdInitClassInfo(&it_803F1F90, &hsdMObj.parent,
                     (char*) ((s32) &it_803F1F90 + 0xDC), "it_mobj", 0x50,
                     0x20);
    mobj->parent.release = hsdMObj.parent.release;
    mobj->parent.amnesia = hsdMObj.parent.amnesia;
    mobj->setup = fn_80277D8C;
    mobj->load = hsdMObj.load;
    mobj->make_texp = hsdMObj.make_texp;
#else
    hsdInitClassInfo(&it_803F1F90, &hsdMObj.parent,
                     (char*) ((s32) &it_803F1F90 + 0xDC), "it_mobj", 0x50,
                     0x20);
    it_803F1F90.release = hsdMObj.parent.release;
    it_803F1F90.amnesia = hsdMObj.parent.amnesia;
    // it_803F1F90.unk3C = fn_80277D8C;
    it_803F1F90.destroy = (void (*)(struct _HSD_Class* c)) fn_80277D8C;
    // it_803F1F90.alloc = (s32 (*)(HSD_MObj*, HSD_MObjDesc*)) hsdMObj.load;
    // it_803F1F90.init = (HSD_TExp* (*)(HSD_MObj*, HSD_TObj*, HSD_TExp**))
    // hsdMObj.make_texp;
#endif
}

void fn_80277D8C(HSD_MObj* mobj, u32 rendermode_arg)
{
    HSD_TObj* tobj2;
    HSD_TExp sp38;
    HSD_PEDesc pe_desc;
    Item* item;
    HSD_PEDesc* setup_render_arg;
    HSD_TObj** tobj1_ptr;
    u32 rendermode;
    u32 unused[1];

    item = GET_ITEM(HSD_GObj_804D7814);
    HSD_StateInitTev();
    rendermode = mobj->rendermode;
    HSD_SetMaterialColor(mobj->mat->ambient, mobj->mat->diffuse,
                         mobj->mat->specular, mobj->mat->alpha);
    if (rendermode & 8) {
        HSD_SetMaterialShininess(mobj->mat->shininess);
    }
    tobj1_ptr = NULL;
    tobj2 = mobj->tobj;
    if ((rendermode & 0x04000000) && tobj_shadows) {
        tobj1_ptr = &tobj2;
        while (*tobj1_ptr != NULL) {
            tobj1_ptr = &(*tobj1_ptr)->next;
        }
        *tobj1_ptr = tobj_shadows;
    }
    if ((rendermode & 0x1000) && ((HSD_TObj*) tobj_toon != NULL) &&
        ((HSD_ImageDesc*) tobj_toon->imagedesc != NULL))
    {
        tobj_toon->next = tobj2;
        tobj2 = tobj_toon;
    }
    HSD_TObjSetup(tobj2);
    HSD_TObjSetupTextureCoordGen(tobj2);
    HSD_MOBJ_METHOD(mobj)->setup_tev(mobj, tobj2, rendermode);
    it_80278108(item, mobj, it_80277F90(item, mobj, &sp38));
    if (item->x5C9 != 0xFF) {
        rendermode |= 0x60000000;
    }
    if (item->xDCF_flag.b4 && !item->xDCF_flag.b5) {
        rendermode |= 0x20000000;
    }
    if (item->xDCF_flag.b5 && (item->x5C9 == 0xFF)) {
        pe_desc.flags = 0x38;
        pe_desc.dst_alpha = 0;
        pe_desc.type = 0;
        pe_desc.src_factor = 4;
        setup_render_arg = &pe_desc;
        pe_desc.dst_factor = 5;
        pe_desc.logic_op = 0xF;
        pe_desc.z_comp = 3;
        pe_desc.alpha_comp0 = 7;
        pe_desc.ref0 = 0;
        pe_desc.alpha_op = 0;
        pe_desc.alpha_comp1 = 7;
        pe_desc.ref1 = 0;
    } else {
        setup_render_arg = mobj->pe;
    }
    HSD_SetupRenderModeWithCustomPE(rendermode, setup_render_arg);
    if (tobj1_ptr != NULL) {
        *tobj1_ptr = NULL;
    }
}

HSD_TExp* it_80277F90(Item* item, HSD_MObj* mobj, HSD_TExp* arg2)
{
    s32 sp80;
    s32 sp3C;
    s32 sp38;
    s32 sp34;
    s32 sp30;
    u32 sp28;
    s32 sp1C;
    HSD_TevDesc sp14;
    Vec3 spC;
    Vec3* var_r5;
    // s32 temp_r3_2;
    // s32 temp_r3_3;
    s32 temp_ret;
    s32 var_ctr;
    bool chk;
    // u8 temp_r3;
    Vec3* var_r4;

    if (!item->xDCF_flag.b4) {
        // temp_r3 = ;
        if (item->x548_colorOverlay.x7C_flag2 &&
            item->x548_colorOverlay.x7C_light_enable)
        {
#if 1
            arg2->cnst.type = (HSD_TExpType) ((s32) &it_803F1F90 + 0xC4);
            arg2->cnst.next = (HSD_TExp*) ((s32) &it_803F1F90 + 0xC8);
            arg2->cnst.val = (void*) ((s32) &it_803F1F90 + 0xCC);
            arg2->cnst.comp = (HSD_TEInput) ((s32) &it_803F1F90 + 0xD0);
            arg2->cnst.ctype = (HSD_TEType) ((s32) &it_803F1F90 + 0xD4);
            arg2->cnst.reg = (u8) ((s32) &it_803F1F90 + 0xD8);
#else
            // arg2->tev.type = (HSD_TExpType) ((s32) &it_803F1F90 + 0xC4);
            // arg2->tev.next = (HSD_TExp*) ((s32) &it_803F1F90 + 0xC8);
            // arg2->tev.c_ref = (s32) ((s32) &it_803F1F90 + 0xCC);
            // arg2->tev.c_dst = (u8) ((s32) &it_803F1F90 + 0xD0);
            // arg2->tev.c_scale = (u8) ((s32) &it_803F1F90 + 0xD4);
            // arg2->tev.a_ref = (s32) ((s32) &it_803F1F90 + 0xD8);
#endif
            temp_ret = lbGetFreeColorRegister(0, mobj, NULL);
            // temp_r3_2 = temp_ret;
            if (temp_ret == -1) {
                // OSReport(&it_803F1F90 + 0xF4, (u32) (u64) temp_ret, (f32)
                // temp_ret);
                // __assert(&it_803F1F90 + 0x118, 0xDDU, &it_804D51B8);
                HSD_ObjAllocGetFreed((HSD_ObjAllocData*) arg2);
            }
            arg2->cnst.reg = (s8) temp_ret;
            arg2->cnst.val = &item->x548_colorOverlay.x50_light_color;
            HSD_TExpSetReg(arg2);
            var_ctr = 14;
            var_r5 = &spC;
            var_r4 = (Vec3*) ((s32) &it_803F1F90 + 0x48);
            while (var_ctr != 0) {
                // var_r4->x += 8;
                // var_r5->x += 8;
                var_r5 = var_r4;
                // var_r5->z = var_r4->z;
                // var_r5->y = var_r4->y;
                var_ctr--;
            }
            var_r5->z = var_r4->z;
            sp14.stage = HSD_StateAssignTev(); // type GXTevStageID?
            sp14.color = 2; // (GXTevKColorSel) GX_TEV_KCSEL_3_4 ?
            sp14.u.tevconf.clr_a = GX_CC_ZERO;
            sp14.u.tevconf.clr_b = lb_8000CC8C(temp_ret);
            sp14.u.tevconf.clr_c = GX_CC_RASA;
            chk = false;
            sp14.u.tevconf.clr_d = GX_CC_CPREV;
            if (temp_ret < 4) {
                chk = true;
            }
            if (chk) {
                sp80 = lb_8000CCA4(temp_ret);
            }
            HSD_SetupTevStage((HSD_TevDesc*) &sp14);
            return arg2;
        }
    }
    return NULL;
}

void it_80278108(Item* item, HSD_MObj* mobj, HSD_TExp* arg2)
{
    GXColor sp168; /* compiler-managed */
    s32 sp110;     /* compiler-managed */
    s32 sp10C;
    s32 sp108;
    GXColor* sp104;  /* compiler-managed */
    HSD_TExp* sp100; /* compiler-managed */
    HSD_TExp* spFC = NULL;
    // s32 spA4;                                       /* compiler-managed */
    // s32 spA0;
    // s32 sp9C;
    // s32* sp98;
    // HSD_TExp* sp94;
    HSD_TExp* sp90 = NULL;
    s32 sp8C;
    s32 sp88;
    s32 sp68;
    s32 sp40;
    s32 sp3C;
    s32 sp24;
    HSD_TevDesc sp1C;
    // u8 sp1A;
    // u8 sp19;
    GXColor sp18;
    Vec3 sp14;
    Vec3* var_r5;
    // Fighter_GObj* temp_r3_2;
    ColorOverlay* var_r4;
    // ColorOverlay* var_r4;
    s32 temp_r3_4;
    s32 temp_r3_5;
    s32 temp_r3_6;
    s32 temp_r3_7;
    s32 temp_r4;
    s32 temp_r7;
    s32 temp_r8_2;
    s32 temp_ret;
    s32 temp_ret_2;
    s32 var_ctr;
    s32 var_r0;
    s32 var_r0_2;
    s32 var_r0_3;
    s32 var_r0_4;
    bool chk1;
    s32 var_r3;
    u32 temp_r3_3;
    // u8 temp_r3;
    u8 temp_r5_2;
    u8 temp_r8;
    u8 temp_r8_3;
    // void* temp_r5;
    GXColor* color_hex;
    Vec3* var_r4_2;

    // temp_r3 = item->unkDCF;
    if (!item->xDCF_flag.b5) {
        var_r4 = &item->x548_colorOverlay;
        chk1 = false;
        if (item->xDCF_flag.b3) {
            // temp_r3_2 = item->owner;
            if ((item->owner != NULL) && item->xDC8_word.flags.x13) {
                var_r4 =
                    (ColorOverlay*) ftCo_800C0674((Fighter_GObj*) item->owner);
            }
        }
        if (item->xDCF_flag.b4) {
            chk1 = true;
            sp168.r = item->xBC8;
        } else if (item->x5C8) {
            if (var_r4->x7C_color_enable) {
                temp_r3_3 = ((0xFF - item->xBC7) *
                             (0xFF - (s32) ((s32) &it_803F1F90 + 0x2F))) /
                            255;
                // temp_r5 = item->xBC4;
                color_hex = &var_r4->x2C_hex;
                if ((s32) temp_r3_3 == 0xFF) {
                    sp168 = var_r4->x2C_hex;
                } else {
                    // temp_r8 = temp_r5->unk0;
                    temp_r8 = item->xBC4;
                    temp_r3_4 = 0xFF - temp_r3_3;
                    temp_r8_2 =
                        temp_r8 +
                        ((color_hex->a * (color_hex->r - temp_r8)) / 255);
                    temp_r7 = temp_r8_2 * 0xFF;
                    temp_r4 = temp_r7 / temp_r3_4;
                    sp168.r = (u8) temp_r4;
                    if ((u32) temp_r4 != 0U) {
                        sp168.r = (s8) (temp_r7 / temp_r4);
                    } else {
                        sp168.r = ((temp_r3_4 - temp_r8_2) * 0xFF) / 255;
                    }
                    // temp_r8_3 = temp_r5->unk1;
                    temp_r8_3 = item->xBC5;
                    sp168.g = (s8) ((s32) ((temp_r8_3 +
                                            ((color_hex->a *
                                              (color_hex->g - temp_r8_3)) /
                                             255)) *
                                           0xFF) /
                                    temp_r3_4);
                    // temp_r5_2 = temp_r5->unk2;
                    temp_r5_2 = item->xBC6;
                    sp168.b = (s8) ((s32) ((temp_r5_2 +
                                            ((color_hex->a *
                                              (color_hex->b - temp_r5_2)) /
                                             255)) *
                                           0xFF) /
                                    temp_r3_4);
                }
                chk1 = true;
            } else {
                chk1 = true;
                sp168.r = item->xBC4;
            }
        } else if (var_r4->x7C_flag2) {
            chk1 = true;
            sp168 = var_r4->x2C_hex;
        }
        if (chk1) {
            spFC->cnst.type = (HSD_TExpType) ((s32) &it_803F1F90 + 0xC4);
            spFC->cnst.next = (HSD_TExp*) ((s32) &it_803F1F90 + 0xC8);
            spFC->cnst.val = (void*) ((s32) &it_803F1F90 + 0xCC);
            spFC->cnst.comp = (HSD_TEInput) ((s32) &it_803F1F90 + 0xD0);
            spFC->cnst.ctype = (HSD_TEType) ((s32) &it_803F1F90 + 0xD4);
            spFC->cnst.reg = (u8) ((s32) &it_803F1F90 + 0xD4);
            spFC->tev.a_dst = (u8) ((s32) &it_803F1F90 + 0xD8);
            temp_ret = lbGetFreeColorRegister(0, mobj, arg2);
            temp_r3_5 = temp_ret;
            if (temp_r3_5 == -1) {
                OSReport((char*) (&it_803F1F90 + 0xF4), (u32) (u64) temp_ret,
                         (f32) temp_ret);
                __assert((char*) (&it_803F1F90 + 0x118), 0x144U,
                         (char*) &it_804D51B8);
            }
            sp110 = (s8) temp_r3_5;
            sp104 = &sp168;
            HSD_TExpSetReg((HSD_TExp*) &spFC);
            sp100 = arg2;
            if (temp_r3_5 < 4) {
                var_r0 = 1;
            } else {
                var_r0 = 0;
            }
            if (var_r0 != 0) {
                var_r3 = 4;
            } else {
                var_r3 = 0;
            }
            temp_ret_2 =
                lbGetFreeColorRegister(var_r3, mobj, (HSD_TExp*) &spFC);
            temp_r3_6 = temp_ret_2;
            if (temp_r3_6 == -1) {
                OSReport((char*) (&it_803F1F90 + 0x128),
                         (u32) (u64) temp_ret_2, (f32) temp_ret_2);
                __assert((char*) (&it_803F1F90 + 0x118), 0x152U,
                         (char*) &it_804D51B8);
            }
            if ((u8) item->x5C9 != 0xFF) {
                sp90->cnst.type = (HSD_TExpType) ((s32) &it_803F1F90 + 0xC4);
                sp90->cnst.next = (HSD_TExp*) ((s32) &it_803F1F90 + 0xC8);
                sp90->cnst.val = (void*) ((s32) &it_803F1F90 + 0xCC);
                sp90->cnst.comp = (HSD_TEInput) ((s32) &it_803F1F90 + 0xD0);
                sp90->cnst.ctype = (HSD_TEType) ((s32) &it_803F1F90 + 0xD4);
                sp90->cnst.reg = (u8) ((s32) &it_803F1F90 + 0xD4);
                sp90->tev.a_dst = (u8) ((s32) &it_803F1F90 + 0xD8);
                sp90->tev.a_dst = (s8) temp_r3_6;
                sp90->cnst.comp = 5;
                sp90->cnst.idx = 3;
                sp90->tev.c_ref = item->x5C9;
                sp100 = sp90;
            } else {
                sp100 = NULL;
            }
            sp110 = (s8) temp_r3_6;
            sp18.r = sp168.a;
            sp18.g = sp168.a;
            sp18.b = sp168.a;
            sp104 = &sp18;
            HSD_TExpSetReg((HSD_TExp*) &spFC);
            var_ctr = 0xE;
            var_r5 = &sp14;
            var_r4_2 = (Vec3*) ((s32) &it_803F1F90 + 0x48);
            do {
                // temp_r3_7 = var_r4_2->z;
                // var_r4_2->x += 8;
                // var_r5->x += 8;
                var_r5 = var_r4_2;
                // var_r5->z = temp_r3_7;
                // var_r5->y = (s32) var_r4_2->y;
                var_ctr -= 1;
            } while (var_ctr != 0);
            // var_r5->z = (s32) var_r4_2->z;
            sp1C.stage = HSD_StateAssignTev();
            sp1C.color = lb_8000CC8C(temp_r3_5);
            sp1C.u.tevconf.clr_op = lb_8000CC8C(temp_r3_6);
            if (temp_r3_5 < 4) {
                var_r0_2 = 1;
            } else {
                var_r0_2 = 0;
            }
            if (var_r0_2 != 0) {
                sp88 = lb_8000CCA4(temp_r3_5);
            } else {
                if (temp_r3_6 < 4) {
                    var_r0_3 = 1;
                } else {
                    var_r0_3 = 0;
                }
                if (var_r0_3 != 0) {
                    sp88 = lb_8000CCA4(temp_r3_6);
                }
            }
            if ((u8) item->x5C9 != 0xFF) {
                sp68 = lb_8000CD90(temp_r3_6);
                if (temp_r3_6 < 4) {
                    var_r0_4 = 1;
                } else {
                    var_r0_4 = 0;
                }
                if (var_r0_4 != 0) {
                    sp8C = lb_8000CDA8(temp_r3_6);
                }
            }
            HSD_SetupTevStage((HSD_TevDesc*) &sp1C);
        }
    }
}

void it_80278574(HSD_GObj* gobj, GXColor* arg1)
{
    HSD_DObj* var_r3;
    HSD_JObj* var_r0;
    HSD_JObj* var_r0_2;
    HSD_JObj* var_r0_3;
    HSD_JObj* var_r0_4;
    HSD_JObj* var_r0_5;
    HSD_JObj* var_r0_6;
    HSD_JObj* var_r0_7;
    HSD_JObj* var_r0_8;
    HSD_JObj* var_r31;
    HSD_JObj* var_r3_2;
    HSD_JObj* var_r3_3;
    HSD_MObj* temp_r4;
    HSD_Material* temp_r4_2;
    PAD_STACK(4);

    // var_r31 = GET_JOBJ(gobj->hsd_obj);
    var_r31 = gobj->hsd_obj;
    while (var_r31 != NULL) {
        var_r3 = HSD_JObjGetDObj(var_r31);
        while (var_r3 != NULL) {
            temp_r4 = var_r3->mobj;
            if (temp_r4 != NULL) {
                temp_r4_2 = temp_r4->mat;
                if (temp_r4_2 != NULL) {
                    temp_r4_2->diffuse = *arg1;
                }
            }
            if (var_r3 != NULL) {
                var_r3 = var_r3->next;
            } else {
                var_r3 = NULL;
            }
        }
        if (var_r31 == NULL) {
            var_r0 = NULL;
        } else {
            var_r0 = var_r31->child;
        }
        if (var_r0 != NULL) {
            if (var_r31 == NULL) {
                var_r0_2 = NULL;
            } else {
                var_r0_2 = var_r31->child;
            }
            var_r31 = var_r0_2;
        } else {
            if (var_r31 == NULL) {
                var_r0_3 = NULL;
            } else {
                var_r0_3 = var_r31->next;
            }
            if (var_r0_3 != NULL) {
                if (var_r31 == NULL) {
                    var_r0_4 = NULL;
                } else {
                    var_r0_4 = var_r31->next;
                }
                var_r31 = var_r0_4;
            } else {
            loop_25:
                if (var_r31 == NULL) {
                    var_r0_5 = NULL;
                } else {
                    var_r0_5 = var_r31->parent;
                }
                if (var_r0_5 == NULL) {
                    var_r31 = NULL;
                } else {
                    if (var_r31 == NULL) {
                        var_r3_2 = NULL;
                    } else {
                        var_r3_2 = var_r31->parent;
                    }
                    if (var_r3_2 == NULL) {
                        var_r0_6 = NULL;
                    } else {
                        var_r0_6 = var_r3_2->next;
                    }
                    if (var_r0_6 != NULL) {
                        if (var_r31 == NULL) {
                            var_r3_3 = NULL;
                        } else {
                            var_r3_3 = var_r31->parent;
                        }
                        if (var_r3_3 == NULL) {
                            var_r0_7 = NULL;
                        } else {
                            var_r0_7 = var_r3_3->next;
                        }
                        var_r31 = var_r0_7;
                    } else {
                        if (var_r31 == NULL) {
                            var_r0_8 = NULL;
                        } else {
                            var_r0_8 = var_r31->parent;
                        }
                        var_r31 = var_r0_8;
                        goto loop_25;
                    }
                }
            }
        }
    }
}

#if 0
// load ItCo.dat/usd ?
void it_8027870C(s32 arg0) {
    if (lbLang_IsSettingUS() != 0) {
        lbArchive_80017040(0, &it_803F1EE4, &it_804D6D20, &it_803F1EF0, 0);
    } else {
        lbArchive_80017040(0, &it_803F1ED8, &it_804D6D20, &it_803F1EF0, 0);
    }
    it_804D6D28 = it_804D6D20->unk0;
    it_804D6D24 = it_804D6D20->unk4;
    it_804D6D38 = it_804D6D20->unk8;
    it_804D6D30 = it_804D6D20->unkC;
    it_804D6D40 = it_804D6D20->unk10;
    it_804D6D04 = it_804D6D20->unk14;
}
#endif

void it_802787B4(Item_GObj* item_gobj, s32 arg1)
{
    Vec3 sp1C;
    Vec3 sp10;
    sp1C.x = sp1C.y = sp1C.z = 0.0F;
    sp10.x = sp10.y = sp10.z = 0.0F;
    it_80278800(item_gobj, arg1, 0, &sp1C, &sp10, 1, 0.0F);
}

void it_80278800(Item_GObj* item_gobj, s32 ef_id, s32 arg2, Vec3* arg3,
                 Vec3* arg4, s32 arg5, f32 arg6)
{
    f32 sp88;
    f32 sp84;
    f32 sp80;
    Vec3 sp74;
    Vec3 sp68;
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    HSD_JObj* jobj;
    Item* item;
    f32 temp_f1;
    f64 var_f0;
    PAD_STACK(52);

    item = item_gobj->user_data;

    // Not sure what to make of mixing this case statement with the if's below.
    // Commenting out those cases did not affect the % match *shrug*
    switch (ef_id) {
    case 0x402:
    // case 0x403:
    // case 0x409:
    // case 0x412:
    // case 0x413:
    // case 0x414:
    // case 0x41B:
    // case 0x422:
    // case 0x433:
    case 0x449:
    case 0x473:
        // block_50:
        if (arg5 == 1) {
            jobj = it_80272CC0(item_gobj, arg2);
            efSync_Spawn(ef_id, item_gobj, jobj);
            return;
        }
        jobj = it_80272CC0(item_gobj, arg2);
        efAsync_Spawn((HSD_GObj*) item_gobj,
                      &((Item*) item_gobj->user_data)->xBC0, 0U, ef_id, jobj);
        return;
    case 0x446:
    case 0x448:
        if (arg5 == 1) {
            jobj = it_80272CC0(item_gobj, arg2);
            efSync_Spawn(ef_id, item_gobj, jobj, arg3);
            return;
        }
        jobj = it_80272CC0(item_gobj, arg2);
        efAsync_Spawn((HSD_GObj*) item_gobj,
                      &((Item*) item_gobj->user_data)->xBC0, 7U, ef_id, jobj,
                      arg3);
        return;
    // case 0x417:
    // case 0x418:
    // case 0x419:
    case 0x41A:
        jobj = it_80272CC0(item_gobj, arg2);
        efSync_Spawn(ef_id, item_gobj, jobj, 0xF25959);
        return;
    case 0x415:
    // case 0x41E:
    // case 0x428:
    // case 0x429:
    case 0x42A:
    // case 0x438:
    case 0x439:
    case 0x43E:
    case 0x44D:
    // case 0x45B:
    case 0x45C:
    // case 0x45F:
    // case 0x460:
    case 0x461:
        // case 0x462:
        // case 0x463:
        // case 0x464:
        // case 0x465:
        // case 0x466:
        // case 0x467:
        // case 0x468:
        // case 0x469:
        // case 0x46A:
        // case 0x46B:
        // case 0x46C:
        // case 0x46D:
        // case 0x46E:
        // case 0x46F:
        // case 0x470:
        // case 0x471:
        // case 0x472:
        sp88 = 1.0f;
        if (arg5 == 1) {
            jobj = it_80272CC0(item_gobj, arg2);
            efSync_Spawn(ef_id, item_gobj, jobj, &sp88);
            return;
        }
        jobj = it_80272CC0(item_gobj, arg2);
        efAsync_Spawn((HSD_GObj*) item_gobj,
                      &((Item*) item_gobj->user_data)->xBC0, 3U, ef_id, jobj,
                      &sp88);
        return;
    case 0x44E:
    // case 0x44F:
    // case 0x450:
    // case 0x451:
    // case 0x452:
    // case 0x457:
    // case 0x458:
    // case 0x459:
    case 0x45A:
        sp84 = 1.0f;
        jobj = it_80272CC0(item_gobj, arg2);
        efSync_Spawn(ef_id, item_gobj, jobj, &item->facing_dir, &sp84);
        return;
    // case 0x423:
    case 0x424:
        sp80 = 0.0f;
        jobj = it_80272CC0(item_gobj, arg2);
        efAsync_Spawn((HSD_GObj*) item_gobj,
                      &((Item*) item_gobj->user_data)->xBC0, 3U, ef_id, jobj,
                      &sp80);
        return;
    }
    // default:
    sp74 = *arg3;
    sp74.x += 2.0f * arg4->x * (HSD_Randf() - 1.0f);
    sp74.y += 2.0f * arg4->y * (HSD_Randf() - 1.0f);
    sp74.z += 2.0f * arg4->z * (HSD_Randf() - 1.0f);
    lb_8000B1CC(it_80272CC0(item_gobj, arg2), &sp74, &sp68);
    if (ef_id < 0x250) {
        if (arg5 == 1) {
            efSync_Spawn(ef_id, item_gobj, &sp68);
            return;
        }
        jobj = it_80272CC0(item_gobj, arg2);
        efAsync_Spawn((HSD_GObj*) item_gobj,
                      &((Item*) item_gobj->user_data)->xBC0, 2U, ef_id, jobj,
                      &sp74);
        return;
    } else if (ef_id == 0x41E) {
        return;
    } else if (ef_id < 0x41E) {
        if (ef_id == 0x3FF) {
            goto block_558;
        } else if (ef_id < 0x3FF) {
            if (ef_id == 0x3F5) {
                goto block_4FC;
            } else if (ef_id < 0x3F5) {
                if (ef_id == 0x3EE) {
                    goto block_4A8;
                } else if (ef_id < 0x3EE) {
                    if (ef_id >= 0x3ED) {
                        goto block_4FC;
                    } else if (ef_id >= 0x3E9) {
                        goto block_4A8;
                    } else {
                        return;
                    }
                }
                if (ef_id >= 0x3F3) {
                    goto block_4A8;
                } else {
                    goto block_4FC;
                }
            } else {
                if (ef_id == 0x3FD) {
                    goto block_558;
                } else if (ef_id >= 0x3FD) {
                    goto block_4FC;
                }
                if (ef_id >= 0x3FA) {
                    goto block_4A8;
                } else if (ef_id >= 0x3F7) {
                    goto block_558;
                } else {
                    goto block_4A8;
                }
            }
        }
        if (ef_id == 0x408) {
            goto block_61C;
        } else if (ef_id < 0x408) {
            if (ef_id == 0x405) {
                goto block_4A8;
            } else if (ef_id < 0x405) {
                if (ef_id >= 0x404) {
                    goto block_61C;
                } else if (ef_id < 0x402) {
                    return;
                } else {
                    goto block_4FC;
                }
            }
            if (ef_id >= 0x407) {
                goto block_4A8;
            } else {
                goto block_61C;
            }
        }
        if (ef_id == 0x416) {
            goto block_4A8;
        } else if (ef_id < 0x416) {
            if (ef_id >= 0x412) {
                return;
            }
            if (ef_id >= 0x40C) {
                goto block_4A8;
            } else {
                return;
            }
        } else if (ef_id >= 0x41C) {
            goto block_4A8;
        } else {
            // goto block_50;
            return;
        }
    } else if (ef_id == 0x440) {
        goto block_59C;
    } else if (ef_id < 0x440) {
        if (ef_id < 0x432) {
            if (ef_id < 0x428) {
                if (ef_id >= 0x425) {
                    goto block_4A8;
                } else if (ef_id < 0x422) {
                    return;
                } else {
                    goto block_4A8;
                }
            }
            if (ef_id == 0x42D) {
                goto block_4A8;
            } else if (ef_id >= 0x42D) {
                goto block_4FC;
            } else {
                return;
            }
        }
        if (ef_id < 0x438) {
            if (ef_id == 0x434) {
                goto block_4A8;
            } else if (ef_id >= 0x434) {
                goto block_59C;
            } else {
                return;
            }
        }
        if (ef_id >= 0x43D) {
            return;
        } else if (ef_id >= 0x43A) {
            goto block_4FC;
        } else {
            return;
        }
    } else if (ef_id == 0x4D0) {
        goto block_4A8;
    } else if (ef_id < 0x4D0) {
        if (ef_id < 0x446) {
            if (ef_id == 0x443) {
                goto block_4FC;
            } else {
                goto block_4A8;
            }
        } else if (ef_id >= 0x44D) {
            return;
        } else if (ef_id >= 0x44A) {
            goto block_4A8;
        } else {
            // goto block_50;
            return;
        }
    } else if (ef_id == 0x514) {
        goto block_6B4;
    } else if (ef_id < 0x514) {
        if (ef_id >= 0x513) {
            goto block_680;

        } else {
            return;
        }
    } else if (ef_id >= 0x516) {
        return;
    } else {
        goto block_6E8;
    }

block_4A8:
    if (arg5 == 1) {
        efSync_Spawn(ef_id, item_gobj, &sp68);
        return;
    }
    jobj = it_80272CC0(item_gobj, arg2);
    efAsync_Spawn((HSD_GObj*) item_gobj, &((Item*) item_gobj->user_data)->xBC0,
                  2U, ef_id, jobj, &sp74);
    return;
block_4FC:
    if (arg5 == 1) {
        efSync_Spawn(ef_id, item_gobj, &sp68, &item->facing_dir);
        return;
    }
    jobj = it_80272CC0(item_gobj, arg2);
    efAsync_Spawn((HSD_GObj*) item_gobj, &((Item*) item_gobj->user_data)->xBC0,
                  5U, ef_id, jobj, &sp74, &item->facing_dir);
    return;
block_558:
    sp64 = 0.0f;
    jobj = it_80272CC0(item_gobj, arg2);
    efAsync_Spawn((HSD_GObj*) item_gobj, &((Item*) item_gobj->user_data)->xBC0,
                  6U, ef_id, jobj, &sp74, &item->facing_dir, &sp64);
    return;
block_59C:
    temp_f1 = item->facing_dir;
    if (item->facing_dir < 0.0f) {
        var_f0 = M_PI;
    } else {
        var_f0 = 0.0f;
    }
    sp60 = var_f0;
    if (arg5 == 1) {
        efSync_Spawn(ef_id, item_gobj, &sp68, &sp60);
        return;
    }
    jobj = it_80272CC0(item_gobj, arg2);
    efAsync_Spawn((HSD_GObj*) item_gobj, &((Item*) item_gobj->user_data)->xBC0,
                  5U, ef_id, jobj, &sp74, &sp60);
    return;
block_61C:
    sp5C = 0.0f;
    if (arg5 == 1) {
        efSync_Spawn(ef_id, item_gobj, &sp68, &sp5C);
        return;
    }
    jobj = it_80272CC0(item_gobj, arg2);
    efAsync_Spawn((HSD_GObj*) item_gobj, &((Item*) item_gobj->user_data)->xBC0,
                  5U, ef_id, jobj, &sp74, &sp5C);
    return;
block_680:
    jobj = it_80272CC0(item_gobj, arg2);
    efAsync_Spawn((HSD_GObj*) item_gobj, &((Item*) item_gobj->user_data)->xBC0,
                  8U, 2U, jobj, &sp74);
    return;
block_6B4:
    jobj = it_80272CC0(item_gobj, arg2);
    efAsync_Spawn((HSD_GObj*) item_gobj, &((Item*) item_gobj->user_data)->xBC0,
                  8U, 3U, jobj, &sp74);
    return;
block_6E8:
    jobj = it_80272CC0(item_gobj, arg2);
    efAsync_Spawn((HSD_GObj*) item_gobj, &((Item*) item_gobj->user_data)->xBC0,
                  8U, 4U, jobj, &sp74);
    return;
}

void it_80278F2C(Item_GObj* item_gobj, CommandInfo* cmd)
{
    Vec3 sp20;
    Vec3 sp14;
    u16 temp_r9;
    // s32 temp_r5;
    PAD_STACK(28);

    ++cmd->u;
    // temp_r5 = cmd->x8_bits->x0 & 0x3FF;
    // temp_r9 = cmd->x8_bits->x0;
    // cmd->x8 = (char*) (&cmd->x8 + 4);
    ++cmd->u;
    // sp20.x = 0.003906f * (f32) cmd->x8_bits->x0;
    // sp20.x = 0.003906f * (((f32) cmd->x8_bits->x0 - it_804DC798) -
    // it_804DC7A0);
    // sp20.y = 0.003906f * (f32) cmd->x8_bits->x2;
    ++cmd->u;
    // cmd->x8 = (char*) (&cmd->x8 + 4);
    // sp20.z = 0.003906f * (f32) cmd->x8_bits->x0;
    // sp14.x = 0.003906f * (f32) cmd->x8_bits->x2;
    ++cmd->u;
    // cmd->x8 = (char*) (&cmd->x8 + 4);
    // sp14.y = 0.003906f * (f32) cmd->x8_bits->x0;
    // sp14.z = 0.003906f * (f32) cmd->x8_bits->x2;
    // cmd->x8 = (char*) (&cmd->x8 + 4);
    ++cmd->u;

    // void it_80278800(Item_GObj* item_gobj, s32 ef_id, s32 arg2, Vec3* arg3,
    // Vec3* arg4, s32 arg5, f32 arg6)
    //  it_80278800((Item_GObj*) temp_r9, temp_r6->x0 & 0x3FF, &sp20, &sp14, 0,
    //  temp_r9, temp_r10_2, (f32) (s32) (f32) temp_r10->x2, 0.003906f);
    // it_80278800(item_gobj, temp_r9, temp_r5, &sp20, &sp14, 0, 0.003906f);
}

void it_802790C0(Item_GObj* item_gobj, CommandInfo* cmd)
{
#if 0
    HitCapsule* hitcapsule;
    s32 temp_r31;
    u32 temp_r28;
    u32 temp_r5_2;
    u32 var_r4;
    Item* item;
    PAD_STACK(12);

    item = GET_ITEM((HSD_GObj*) item_gobj);
    // var_r4 = ((u16) cmd->x8_bits->x0 >> 7U) & 7;
    hitcapsule = &item->x5D4_hitboxes[var_r4].hit;
    temp_r28 = var_r4;
    // temp_r5_2 = ((u8) cmd->x8_bits->x0 >> 4U) & 7;
    if ((hitcapsule->state == HitCapsule_Disabled) ||
        (hitcapsule->x4 != temp_r5_2))
    {
        hitcapsule->x4 = temp_r5_2;
        hitcapsule->state = HitCapsule_Enabled;
        item->xDC8_word.flags.x16 = 1;
        item->xDAA_flag.b2 = 0;
        it_8026FCF8(item, hitcapsule);
    }
    // temp_r31 = ((u32) cmd->x8_bits->x0 >> 0xDU) & S8_MAX;
    if (temp_r31 != 0U) {
        if (!item->xBBC_dynamicBoneTable) {
            OSReport((char*) &it_803F22E8);
            __assert((char*) &it_803F2300, 0x8BU, (char*) &it_804D51C0);
        }
        hitcapsule->jobj = item->xBBC_dynamicBoneTable->bones[temp_r31];
    } else {
        hitcapsule->jobj = item_gobj->hsd_obj;
    }
    // it_80272460(hitcapsule,
    //             item->xC3C * ((cmd->x8_bits->x2 & 0x1FFF) * item->xC40),
    //             item_gobj);
    cmd->x8 = cmd->x8 + 4;
    hitcapsule->scale = 0.003906f * (f32) (u16) cmd->x8_bits->x0;
    item->x3C = hitcapsule->scale;
    // it_80275594(item_gobj, temp_r28, temp_r5, it_804DC7A8 / item->scl,
    // 0.003906f); it_80275594(item_gobj, temp_r28, cmd->x8_bits, 1.0f /
    // item->scl, 0.003906f);
    it_80275594(item_gobj, temp_r28, 1.0f / item->scl);
    // hitcapsule->b_offset.x = 0.003906f * (f32) (s16) cmd->x8_bits->x2;
    cmd->x8 = cmd->x8 + 4;
    hitcapsule->b_offset.y = 0.003906f * (f32) (s16) cmd->x8_bits->x0;
    // hitcapsule->b_offset.z = 0.003906f * (f32) (s16) cmd->x8_bits->x2;
    cmd->x8 = cmd->x8 + 4;
    hitcapsule->kb_angle = ((u16) cmd->x8_bits->x0 >> 7U) & 0x1FF;
    // hitcapsule->x24 = ((u32) cmd->x8_bits->x0 >> 14U) & 0x1FF;
    hitcapsule->x24 = ((u32) cmd->x8_bits->x0 >> 14U) & 0x1FF;
    // hitcapsule->x28 = ((u16) cmd->x8_bits->x2 >> 5U) & 0x1FF;
    hitcapsule->x43_b1 = 1;
    cmd->x8 = cmd->x8 + 4;
    hitcapsule->x2C = ((u16) cmd->x8_bits->x0 >> 7U) & 0x1FF;
    hitcapsule->element = ((u8) cmd->x8_bits->x0 >> 2U) & 0x1F;
    // hitcapsule->unk40 = (u8) ((hitcapsule->unk40 & ~0x80) |
    // ((cmd->x8_bits->unk1 << 6) & 0x80));
    hitcapsule->x40_b0 = cmd->x8_bits->unk6.unk1;
    hitcapsule->x40_b1 = 0;
    hitcapsule->x34 = (s32) ((cmd->x8_bits->x0 << 0xF) & 0xFF800000) >> 0x18;
    // hitcapsule->sfx_severity = ((u16) cmd->x8_bits->x2 >> 6U) & 7;
    // hitcapsule->sfx_kind = ((u8) cmd->x8[0]->unk3 >> 2U) & 0xF;
    // hitcapsule->sfx_kind = ((u8) cmd->x8_bits->x2 >> 2U) & 0xF;
    // hitcapsule->sfx_kind = cmd->x8_bits->x3_b5;
    // hitcapsule->x40_b2 = (u8) ((hitcapsule->x40_b2 & ~0x20) |
    // ((cmd->x8_bits->unk3 << 5) & 0x20));
    // hitcapsule->x40_b2 = cmd->x8_bits->x3_b7;
    // hitcapsule->x40_b3 = (u8) ((hitcapsule->x40_b3 & ~0x10) |
    // ((cmd->x8_bits->unk3 << 3) & 0x10));
    // hitcapsule->x40_b3 = cmd->x8_bits->x3_b6;
    cmd->x8 = cmd->x8 + 4;
    hitcapsule->x40_b4 = ((u8) cmd->x8_bits->x0 << 4) & 0xFF0;
    // hitcapsule->x41_b4 = cmd->x8_bits->x0_b7;
    // hitcapsule->x41_b4 = (u8) ((hitcapsule->x41_b4 & ~8) | (((u8)
    // cmd->x8_bits->unk1 >> 4U) & 8)); hitcapsule->x41_b4 = ((u8)
    // cmd->x8_bits->x0 >> 4U) & 8;
    // hitcapsule->x41_b4 = cmd->x8_bits->x1_b0;
    // hitcapsule->x41_b5 = (u8) ((hitcapsule->x41_b5 & ~4) | (((u8)
    // cmd->x8[0]->unk1 >> 4U) & 4)); hitcapsule->x41_b5 = ((u8)
    // cmd->x8_bits->x0 >> 4U) & 4;
    // hitcapsule->x41_b5 = cmd->x8_bits->x1_b1;
    // hitcapsule->x41_b6 = (u8) ((hitcapsule->x41_b6 & ~2) | (((u8)
    // cmd->x8[0]->unk1 >> 4U) & 2));
    // hitcapsule->x41_b6 = cmd->x8_bits->x1_b2;
    // hitcapsule->x41_b6 = cmd->x8_bits->x1_b6;
    // hitcapsule->x41_b7 = (u8) ((hitcapsule->x41_b7 & ~1) | (((u8)
    // cmd->x8[0]->unk1 >> 4U) & 1));
    // hitcapsule->x41_b7 = cmd->x8_bits->x1_b3;
    // hitcapsule->x41_b7 = cmd->x8_bits->x1_b7;
    // hitcapsule->x42_b0 = (u8) ((hitcapsule->x42_b0 & ~0x80) |
    // ((cmd->x8[0]->unk1 << 4) & 0x80));
    // hitcapsule->x42_b0 = cmd->x8_bits->x1_b4;
    // hitcapsule->x42_b0 = cmd->x8_bits->x1_b0;
    // hitcapsule->x42_b1 = (u8) ((hitcapsule->x42_b1 & ~0x40) |
    // ((cmd->x8[0]->unk1 << 4) & 0x40));
    // hitcapsule->x42_b1 = cmd->x8_bits->x1_b5;
    // hitcapsule->x42_b1 = cmd->x8_bits->x1_b1;
    // hitcapsule->x42_b2 = (u8) ((hitcapsule->x42_b2 & ~0x20) |
    // ((cmd->x8[0]->unk1 << 4) & 0x20));
    // hitcapsule->x42_b2 = cmd->x8_bits->x1_b6;
    // hitcapsule->x42_b2 = cmd->x8_bits->x1_b2;
    // hitcapsule->x42_b3 = (u8) ((hitcapsule->x42_b3 & ~0x10) |
    // ((cmd->x8[0]->unk1 << 4) & 0x10));
    // hitcapsule->x42_b3 = cmd->x8_bits->x1_b7;
    // hitcapsule->x42_b4 = cmd->x8_bits->x2_b0;
    // hitcapsule->x42_b5 = cmd->x8_bits->x2_b1;
    // hitcapsule->x42_b6 = cmd->x8_bits->x2_b2;
    // hitcapsule->x42_b7 = cmd->x8_bits->x2_b3;
    // hitcapsule->x43 = cmd->x8_bits->x2;
    // hitcapsule->x43_b0 = cmd->x8_bits->x2_b4;
    // hitcapsule->hit_grabbed_victim_only = (u8)
    // ((hitcapsule->hit_grabbed_victim_only & ~0x80) | (((u8) cmd->x8_bits->x0
    // << 5) & 0x80)); hitcapsule->hit_grabbed_victim_only = ((u8)
    // cmd->x8_bits->x0 << 5) & 0x80; hitcapsule->hit_grabbed_victim_only =
    // cmd->x8_bits->x2_b5;
    // (&item->x5D4_hitboxes[var_r4])->x138 = cmd->x8_bits->x2_b5;
    // item->x5D4_hitboxes[var_r4].x138 = (u8) cmd->x8_bits->x2;
    // cmd->unk8 = (void* ) (cmd->unk8 + 4);
    // cmd->x8[0] = cmd->x8[1];
    cmd->x8 = cmd->x8 + 4;
    hitcapsule->x43_b2 = 1;
    if (HSD_GObj_804D7838 && ((u8) HSD_GObj_804D7838->s_link > 11U)) {
        it_8027129C(item_gobj, temp_r28);
    }
#endif
}

void it_80279544(Item_GObj* item_gobj, CommandInfo* cmd)
{
    // struct it_278F_struct_1B* temp_r4;
    Item* item;
    // PAD_STACK(4);

    // temp_r4 = &((struct it_278F_struct_1A*) cmd)->x8[0];
    item = GET_ITEM((HSD_GObj*) item_gobj);
    // item = item_gobj->user_data;
    // it_80272460(
    // &item->x5D4_hitboxes[(cmd->x8_bits->x0 >> 7U) & 7].hit,
    // (s32) (u32) (item->xC3C *
    // ((f32) ((u16) cmd->x8_bits->x2 & 0x1FFF) * item->xC40)),
    // item_gobj);
    // cmd->unk8 = (void* ) (cmd->unk8 + 4);
    // ((struct it_278F_struct_1A*) cmd)->x8[0] = ((struct it_278F_struct_1A*)
    // cmd)->x8[1];
    // cmd->x8 = cmd->x8 + 4;
}

void it_802795EC(Item_GObj* item_gobj, CommandInfo* cmd)
{
    // s32 temp_r4_2;
    HitCapsule* hitcapsule;
    Item* item;

    // temp_r4_2 = ((u16) cmd->x8_bits->x0 >> 7U) & 7;
    item = GET_ITEM((HSD_GObj*) item_gobj);
    // hitcapsule = &item->x5D4_hitboxes[temp_r4_2].hit;
    // hitcapsule->scale = 0.003906f * (cmd->x8_bits->x0 & 0x7FFFFF);
    // item->x3C = hitcapsule->scale;
    // it_80275594(item_gobj, temp_r4_2, 1.0f / item->scl);
    // cmd->x8 = cmd->x8 + 4;
}

#pragma push
#pragma dont_inline on

void it_80279680(Item_GObj* item_gobj, CommandInfo* cmd)
{
    it_80272560(item_gobj, cmd->u->set_throw_flags.hit_idx);
    ++cmd->u;
}

void it_802796C4(Item_GObj* item_gobj, CommandInfo* cmd)
{
    it_802725D4(item_gobj);
    ++cmd->u;
}

#pragma pop

void it_802796FC(Item_GObj* item_gobj, CommandInfo* cmd)
{
    Item* it = GET_ITEM(item_gobj);
    it->xDAC_itcmd_var0 = cmd->u->set_throw_flags.hit_idx;
    ++cmd->u;
}

void it_80279720(Item_GObj* item_gobj, CommandInfo* cmd)
{
    Item* it = GET_ITEM(item_gobj);
    it->xDB0_itcmd_var1 = cmd->u->set_throw_flags.hit_idx;
    ++cmd->u;
}

void it_80279744(Item_GObj* item_gobj, CommandInfo* cmd)
{
    Item* it = GET_ITEM(item_gobj);
    it->xDB4_itcmd_var2 = cmd->u->set_throw_flags.hit_idx;
    ++cmd->u;
}

void it_80279768(Item_GObj* item_gobj, CommandInfo* cmd)
{
    Item* item = item_gobj->user_data;
    item->xDBC_itcmd_var4 |= (item->xDBC_itcmd_var4 >> 24U & 0x80);
    // item->xDBC_itcmd_var4 |= (item->xDBC_itcmd_var4 >> 25U & 0x80);
    ++cmd->u;
}

#pragma push
#pragma dont_inline on
void it_8027978C(Item_GObj* item_gobj, CommandInfo* cmd)
{
    // #if 1
    //     Item* item;
    //     s32 temp_r4_2;
    //     u8 temp_r7;
    //     u8 temp_r5_2;
    //     // u8 temp_r6_2;

    //     item = GET_ITEM((HSD_GObj*) item_gobj);
    //     // temp_r7 = ((u16) cmd->x8_bits->x0 >> 2U) & U8_MAX;
    //     cmd->x8 = cmd->x8 + 4;
    //     if (temp_r7 < 10U) {
    //         if (temp_r7 < 3U) {
    //             if (temp_r7 < 0U) {
    //             } else {
    //                 // temp_r4_2 = (s32) cmd->x8_bits->x0;
    //                 cmd->x8 = cmd->x8 + 4;
    //                 // temp_r5_2 = cmd->x8_bits->x2;
    //                 // temp_r6_2 = (u8) ((u16) cmd->x8_bits->x2 >> 8U);
    //                 // temp_r6_2 = cmd->x8_bits->x2;
    //                 // switch (temp_r7) {
    //                 // case 0:
    //                 //     Item_8026AE84(item, temp_r4_2, (s32) temp_r5_2,
    //                 //                   (s32) temp_r6_2);
    //                 //     break;
    //                 // case 1:
    //                 //     Item_8026AF0C(item, temp_r4_2, (s32) temp_r5_2,
    //                 //                   (s32) temp_r6_2);
    //                 //     break;
    //                 // case 2:
    //                 //     Item_8026AFA0(item, temp_r4_2, (s32) temp_r5_2,
    //                 //                   (s32) temp_r6_2);
    //                 //     break;
    //                 // }
    //             }
    //         }
    //     } else if (temp_r7 >= 12U) {
    //     } else {
    //         cmd->x8 = cmd->x8 + 4;
    //         switch (temp_r7) {
    //         case 10:
    //             Item_8026B034(item);
    //             break;
    //         case 11:
    //             Item_8026B074(item);
    //             break;
    //         }
    //     }
    // #else
    //     temp_r4_2 = (s32) cmd->x8_bits->x0;
    //     cmd->x8 = cmd->x8 + 4;
    //     temp_r5_2 = cmd->x8_bits->x2;
    //     // temp_r6_2 = (u8) ((u16) cmd->x8_bits->x2 >> 8U);
    //     temp_r6_2 = cmd->x8_bits->x2;
    //     switch (temp_r7) {
    //     case 0:
    //         Item_8026AE84(item, temp_r4_2, (s32) temp_r5_2, (s32)
    //         temp_r6_2); break;
    //     case 1:
    //         Item_8026AF0C(item, temp_r4_2, (s32) temp_r5_2, (s32)
    //         temp_r6_2); break;
    //     case 2:
    //         Item_8026AFA0(item, temp_r4_2, (s32) temp_r5_2, (s32)
    //         temp_r6_2); break;
    //     case 10:
    //         Item_8026B034(item);
    //         break;
    //     case 11:
    //         Item_8026B074(item);
    //         break;
    //     }
    // #endif
    //     cmd->x8 = cmd->x8 + 4;
}
#pragma pop

#pragma push
#pragma dont_inline on

void it_80279888(Item_GObj* item_gobj, CommandInfo* cmd)
{
    PAD_STACK(4);
    it_80273598(item_gobj, cmd->u->unk33.unk0, cmd->u->unk33.unk1);
    NEXT_CMD(cmd);
}

void it_802798D4(Item_GObj* item_gobj, CommandInfo* cmd)
{
    PAD_STACK(4);
    it_80273600(item_gobj);
    NEXT_CMD(cmd);
}

void it_8027990C(Item_GObj* item_gobj, CommandInfo* cmd)
{
    PAD_STACK(4);
    it_80273648(item_gobj, cmd->u->unk33.unk0, cmd->u->unk33.unk1);
    NEXT_CMD(cmd);
}

#pragma pop

void it_80279958(Item_GObj* item_gobj, CommandInfo* cmd)
{
    Item* it = GET_ITEM(item_gobj);
    it_80279B88(it, cmd->u->unk13.unk1, cmd->u->unk13.unk2);
    NEXT_CMD(cmd);
}

void it_802799A8(Item_GObj* item_gobj, CommandInfo* cmd)
{
    it_80279BBC(item_gobj->user_data);
    ++cmd->u;
}

void it_802799E4(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    CommandInfo* cmd = &item->x524_cmd;
    u32 opcode;

    cmd->frame_count = item->x5CC_currentAnimFrame;
    item->xDBC_itcmd_var4 = 0;

    if (cmd->u == NULL) {
        return;
    }

    if (cmd->timer != F32_MAX) {
        cmd->timer -= item->x5D0_animFrameSpeed;
    }

loop:
    if (cmd->u == NULL) {
        return;
    }
    if (cmd->timer == F32_MAX) {
        if (cmd->frame_count >= item->x5D0_animFrameSpeed) {
            return;
        }
        cmd->timer = -cmd->frame_count;
    } else if (cmd->timer > 0.0f) {
        return;
    }

    opcode = (*(u8*) cmd->u >> 2) & 0x3F;
    if (Command_Execute(cmd, opcode) != 0) {
        goto loop;
    }
    opcode -= 10;
    it_803F22A8[opcode](item_gobj, cmd);
    goto loop;
}

#pragma push
#pragma dont_inline on

void it_80279AF0(Item_GObj* item_gobj, CommandInfo* cmd)
{
    it_80278F2C(item_gobj, (CommandInfo*) cmd);
}

#pragma pop

void it_80279B10(Item_GObj* item_gobj, CommandInfo* cmd)
{
    it_8027978C(item_gobj, cmd);
}

void fn_80279B30(Item_GObj* item_gobj, CommandInfo* cmd, int arg2)
{
    int idx = arg2 - 21;
    it_804D51C8[idx](item_gobj, cmd);
}

void it_80279B64(Item* item)
{
    lb_80014498(&item->x548_colorOverlay);
}

void it_80279B88(Item* item, s32 arg1, s32 arg2)
{
    lb_800144C8(&item->x548_colorOverlay, it_804D6D04, arg1, arg2);
}

void it_80279BBC(Item* item)
{
    lb_80014498(&item->x548_colorOverlay);
}

void it_80279BE0(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    while (lb_80014258(item_gobj, &item->x548_colorOverlay, fn_80279B30)) {
        lb_80014498(&item->x548_colorOverlay);
    }
}

void it_80279C48(Item_GObj* item_gobj, Article* arg1)
{
    Vec3 sp10;
    HSD_GObj* gobj;
    Item* item;
    f32 dir;

    item = item_gobj->user_data;
    gobj = ftLib_8008627C(&item->pos, item->owner);
    if (gobj != NULL) {
        ftLib_80086644(gobj, &sp10);
        if ((item->pos.x - sp10.x) > 0.0f) {
            item->facing_dir = -1.0f;
            return;
        }
        item->facing_dir = 1.0f;
        return;
    }
    if (HSD_Randi(2) != 0) {
        dir = 1.0f;
    } else {
        dir = -1.0f;
    }
    item->facing_dir = dir;
}

#pragma push
#pragma dont_inline on

void it_80279CDC(Item_GObj* item_gobj, f32 scale)
{
    it_8027A13C(item_gobj);
    it_80279D5C(item_gobj, scale);
    it_8026B3A8(item_gobj);
    it_802756D0(item_gobj);
    it_8026BDB4(item_gobj);
}

#pragma pop

void it_80279D38(Item_GObj* item_gobj)
{
    it_8027B964(item_gobj, false);
}

void it_80279D5C(Item_GObj* item_gobj, f32 scale)
{
    Vec3 sp18;
    HSD_JObj* item_jobj;
    u32 temp_r4;
    Item* item;

    // item_jobj = GET_JOBJ((HSD_GObj*) item_gobj);
    item_jobj = item_gobj->hsd_obj;
    item = GET_ITEM((HSD_GObj*) item_gobj);
    sp18.z = scale;
    sp18.y = scale;
    sp18.x = scale;
    item->xDD4_itemVar.it_279D.x4C = scale;
    item->xDD4_itemVar.it_279D.x5C = 0;
    HSD_JObjSetScale(item_jobj, &sp18);
}

void it_80279E24(Item_GObj* item_gobj)
{
    HSD_JObj* item_jobj;
    f32 scale;
    Item* item;
    PAD_STACK(4);

    // item_jobj = GET_JOBJ((HSD_GObj*) item_gobj);
    item_jobj = item_gobj->hsd_obj;
    item = GET_ITEM((HSD_GObj*) item_gobj);
    // item = item_gobj->user_data;
    scale = HSD_JObjGetScaleX(item_jobj);
    if (item->xDD4_itemVar.it_279D.x50 <= 0.0f) {
        item->xDD4_itemVar.it_279D.x50 = item->xDD4_itemVar.it_279D.x44;
        if (item->xDD4_itemVar.it_279D.x58 & 1) {
            if (item->xDD4_itemVar.it_279D
                    .x2C[item->xDD4_itemVar.it_279D.x58] <= scale)
            {
                item_jobj = item_gobj->hsd_obj;
                item = item_gobj->user_data;
                scale = HSD_JObjGetScaleX(item_jobj);
                it_80272F7C(item_jobj,
                            item->xDD4_itemVar.it_279D
                                .x2C[item->xDD4_itemVar.it_279D.x58]);
                item->xDD4_itemVar.it_279D.x58++;
                item->xDD4_itemVar.it_279D.x4C =
                    (item->xDD4_itemVar.it_279D
                         .x2C[item->xDD4_itemVar.it_279D.x58] -
                     scale) /
                    item->xDD4_itemVar.it_279D.x44;
            }
        } else {
            if (item->xDD4_itemVar.it_279D
                    .x2C[item->xDD4_itemVar.it_279D.x58] >= scale)
            {
                item_jobj = item_gobj->hsd_obj;
                item = item_gobj->user_data;
                scale = HSD_JObjGetScaleX(item_jobj);
                it_80272F7C(item_jobj,
                            item->xDD4_itemVar.it_279D
                                .x2C[item->xDD4_itemVar.it_279D.x58]);
                item->xDD4_itemVar.it_279D.x58++;
                item->xDD4_itemVar.it_279D.x4C =
                    (item->xDD4_itemVar.it_279D
                         .x2C[item->xDD4_itemVar.it_279D.x58] -
                     scale) /
                    item->xDD4_itemVar.it_279D.x44;
            }
        }
        if ((s32) item->xDD4_itemVar.it_279D.x54 <=
            (s32) item->xDD4_itemVar.it_279D.x58)
        {
            item->xDD4_itemVar.it_279D.x5C = 2;
            return;
        }
    }
    item->xDD4_itemVar.it_279D.x50 =
        (f32) (item->xDD4_itemVar.it_279D.x50 - 1.0f);
    it_80272DE4(item_jobj, item->xDD4_itemVar.it_279D.x4C);
}

void it_80279FF8(Item_GObj* item_gobj)
{
    HSD_JObj* item_jobj;
    Item* item;
    PAD_STACK(8);

    item = GET_ITEM((HSD_GObj*) item_gobj);
    if (item->xDD4_itemVar.it_279D.x5C == 0) {
        item_jobj = GET_JOBJ((HSD_GObj*) item_gobj);
        if (item->xCC_item_attr->x60_scale >
            (item->xDD4_itemVar.it_279D.x48 + HSD_JObjGetScaleX(item_jobj)))
        {
            it_80272DE4(item_jobj, item->xCC_item_attr->x60_scale);
            return;
        }
        it_80272F7C(item_jobj, item->xCC_item_attr->x60_scale);
        item->xDD4_itemVar.it_279D.x5C = 1;
        return;
    }
    if (item->xDD4_itemVar.it_279D.x5C != 2) {
        it_80279E24(item_gobj);
    }
}

#pragma push
#pragma dont_inline on

bool it_8027A09C(Item_GObj* item_gobj)
{
    Item* item;
    PAD_STACK(8);

    item = item_gobj->user_data;
    it_80272860(item_gobj, item->xDD4_itemVar.it_279D.x1C,
                item->xDD4_itemVar.it_279D.x20);
    if (item->xDD4_itemVar.it_279D.x24 <= 0.0f) {
        it_80272F7C(item_gobj->hsd_obj, item->xCC_item_attr->x60_scale);
        return true;
    }
    item->xDD4_itemVar.it_279D.x24 -= 1.0f;
    return false;
}

#pragma pop

bool it_8027A118(Item_GObj* item_gobj, HSD_GObjEvent arg1)
{
    it_8026E4D0(item_gobj, arg1);
    return false;
}

void it_8027A13C(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xDD4_itemVar.it_279D.x10.z = 0.0f;
    item->xDD4_itemVar.it_279D.x10.y = 0.0f;
    item->xDD4_itemVar.it_279D.x10.x = 0.0f;
    item->xDD4_itemVar.it_279D.x4.z = 0.0f;
    item->xDD4_itemVar.it_279D.x4.y = 0.0f;
    item->xDD4_itemVar.it_279D.x4.x = 0.0f;
}

void it_8027A160(HSD_JObj* bone, Item* item)
{
    Vec3 sp1C;
    Vec3 sp10;
    f32 var_f1;
    f32 var_f1_2;
    f32 var_f1_3;

    if (bone != NULL) {
        sp1C.z = 0.0f;
        sp1C.y = 0.0f;
        sp1C.x = 0.0f;
        HSD_JObjGetTranslation(bone, &sp10);
        sp10.x *= item->xCC_item_attr->x60_scale;
        sp10.y *= item->xCC_item_attr->x60_scale;
        sp10.z *= item->xCC_item_attr->x60_scale;
        var_f1 = sp10.x;
        if (var_f1 < 0.0f) {
            var_f1 = -var_f1;
        }
        if (var_f1 < 0.001f) {
            sp10.x = 0.0f;
        }
        var_f1_2 = sp10.y;
        if (var_f1_2 < 0.0f) {
            var_f1_2 = -var_f1_2;
        }
        if (var_f1_2 < 0.001f) {
            sp10.y = 0.0f;
        }
        var_f1_3 = sp10.z;
        if (var_f1_3 < 0.0f) {
            var_f1_3 = -var_f1_3;
        }
        if (var_f1_3 < 0.001f) {
            sp10.z = 0.0f;
        }
        item->xDD4_itemVar.it_279D.x4.x =
            sp10.x - item->xDD4_itemVar.it_279D.x10.x;
        item->xDD4_itemVar.it_279D.x4.y =
            sp10.y - item->xDD4_itemVar.it_279D.x10.y;
        item->xDD4_itemVar.it_279D.x4.z =
            sp10.z - item->xDD4_itemVar.it_279D.x10.z;
        item->xDD4_itemVar.it_279D.x10 = sp10;
        HSD_JObjSetTranslate(bone, &sp1C);
    }
}

void it_8027A344(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->x40_vel.x = item->xDD4_itemVar.it_279D.x4.z * item->facing_dir;
    item->x40_vel.y = item->xDD4_itemVar.it_279D.x4.y;
}

#define PK_START (Pokemon_Tosakinto)
#define PK_END (Pokemon_Tosakinto + 30)

s32 it_8027A364(Item* item)
{
    it_279D_DatAttrs* attr = item->xC4_article_data->x4_specialAttributes;
    int ret_val = 1;
    int i;
    int start = Pokemon_Tosakinto;
    int end = Pokemon_Tosakinto + 30;

    for (i = start; i < end; i++) {
        if (Item_804A0E24.x != i && Item_804A0E24.y != i) {
            ret_val += attr->x3C[i - Pokemon_Tosakinto];
        }
    }

    return ret_val;
}

s32 it_8027A4D4(Item* item)
{
    int rand_int;
    int i;
    int var_r3;

    it_279D_DatAttrs* attr = item->xC4_article_data->x4_specialAttributes;

    if (HSD_Randi(251) == 0 && Item_804A0E24.z == 0 && gm_80165084()) {
        Item_804A0E24.z = 1;
        gm_80172C04();
        return 23;
    }
    if (HSD_Randi(251) == 0 && Item_804A0E24.z == 0 && gm_80164ABC()) {
        Item_804A0E24.z = 1;
        gm_80172BC4();
        return 22;
    }
    rand_int = HSD_Randi(it_8027A364(item));
    var_r3 = 0;
    for (i = PK_START; i < PK_END; i++) {
        int y = Item_804A0E24.y;
        int x = Item_804A0E24.x;
        if (x != i && y != i) {
            var_r3 += attr->x3C[i - Pokemon_Tosakinto];
            if (var_r3 >= rand_int) {
                Item_804A0E24.y = x;
                Item_804A0E24.x = i;
                return i - Pokemon_Tosakinto;
            }
        }
    }
    return 0;
}

s32 it_8027A780(Item* item, void* arg1)
{
    S32Vec2 sp10;
    S32Vec2* var_r4;
    S32Vec2* var_r6;
    s32 temp_r0;
    s32 rand_int;
    s32 chk;
    s32 cnt;
    s32 var_ctr2;
    s32 var_ctr1;
    it_279D_DatAttrs* attr;
    s32 index;
    s32 var_r3;
    s32 var_r4_2;
    s32 var_r5;
    s32 var_r6_2;

    var_r4 = arg1;
    var_r6 = &sp10;
    cnt = 0;
    attr = item->xC4_article_data->x4_specialAttributes;
    var_r3 = 0;
    chk = var_r4->x;
    for (var_ctr1 = 6; var_ctr1 != 0; var_ctr1--) {
        for (var_ctr2 = 0; var_ctr2 < 5; var_ctr2++) {
            if (chk != Pokemon_Chicorita_Leaf) {
                if ((Item_804A0E24.x != chk) && (Item_804A0E24.y != chk)) {
                    var_r6->x = chk;
                    cnt++;
                    var_r6->y = attr->x3C[var_r4->x - Pokemon_Tosakinto];
                    var_r6->x += 2;
                    var_r3 += var_r6->y;
                }
                chk = var_r4->y;
                var_r4->x++;
            }
        }
    }
    rand_int = HSD_Randi(it_8027A364(item));
    var_ctr1 = cnt;
    var_r6_2 = 0;
    var_r5 = Pokemon_Sonans;
    var_r4_2 = 0;
    if (cnt > 0) {
        for (var_ctr1 = cnt; var_ctr1 != 0; var_ctr1--) {
            var_r6_2 += var_r6->y;
            if (rand_int < var_r6_2) {
                var_r5 = sp10.x + (var_r4_2 * 8);
            } else {
                var_r6->x += 2;
                var_r4_2++;
            }
        }
    }
    Item_804A0E24.y = Item_804A0E24.x;
    Item_804A0E24.x = var_r5;
    return var_r5 - Pokemon_Tosakinto;
}

s32 it_8027A9B8(Item* item)
{
    void* vec;

    vec = gm_801BEC54();
    if (vec == NULL) {
        return Pokemon_Sonans;
    }
    if ((HSD_Randi(251U) == 0) && (Item_804A0E24.z == 0) && gm_80165084()) {
        Item_804A0E24.z = 1;
        gm_80172C04();
        return 23U;
    }
    if ((HSD_Randi(251U) == 0) && (Item_804A0E24.z == 0) && gm_80164ABC()) {
        Item_804A0E24.z = 1;
        gm_80172BC4();
        return 22U;
    }
    return it_8027A780(item, vec);
}

void it_8027AAA0(Item_GObj* item1_gobj, Item* item2, s32 arg2)
{
    Item* var_r6;

    Item* it = GET_ITEM(item1_gobj);
    it_279D_DatAttrs* attr = it->xC4_article_data->x4_specialAttributes;
    if (arg2 == Pokemon_Marumine) {
        item2->xDD4_itemVar.it_279D.x1C = 0.0f;
        item2->xDD4_itemVar.it_279D.x20 = 0.0f;
    } else {
        item2->xDD4_itemVar.it_279D.x1C = attr->xC;
        item2->xDD4_itemVar.it_279D.x20 = attr->x10;
    }
    item2->xDD4_itemVar.it_279D.x24 = attr->x14;
    var_r6 = item2;
    item2->xDD4_itemVar.it_279D.x28 = attr->x18;
    item2->xDD4_itemVar.it_279D.x48 =
        (item2->xCC_item_attr->x60_scale - item2->xDD4_itemVar.it_279D.x4C) /
        item2->xDD4_itemVar.it_279D.x28;
    item2->xDD4_itemVar.it_279D.x44 = attr->x34;
    item2->xDD4_itemVar.it_279D.x54 = attr->x38;
    item2->xDD4_itemVar.it_279D.x5C = 0.0f;
    item2->xDD4_itemVar.it_279D.x58 = 0.0f;
    item2->xDD4_itemVar.it_279D.x50 = 0.0f;

    {
        int i;
        for (i = 0; i < attr->x38; i++) {
            item2->xDD4_itemVar.it_279D.x2C[i] =
                attr->x1C[i] * item2->xCC_item_attr->x60_scale;
        }
    }
}

bool it_8027AB64(Item_GObj* item_gobj)
{
    PokemonKind pokemon_kind;
    // Item_GObj* sp20;
    SpawnItem spawn;
    // Article* temp_r4;
    // Item* temp_r28;
    Item* item;
    Item_GObj* spawn_gobj;
    ItemKind it_kind;
    s32 rand_int;
    s32 var_ctr;
    s32 var_r0;
    s32 var_r3;
    s32 var_r4;
    s32 index1;
    s32 index2;
    u32 temp_r3;
    // void* temp_r29;
    it_279D_DatAttrs* attr;
    // PAD_STACK(8);

    item = GET_ITEM((HSD_GObj*) item_gobj);
    // item = item_gobj->user_data;
    temp_r3 = gm_8016AEB8();
    if (temp_r3 != 0U) {
        if (temp_r3 == 1U) {
            pokemon_kind = it_8027A9B8(item);
        } else {
            pokemon_kind = temp_r3 - Pokemon_Tosakinto;
        }
    } else if (gm_8018841C()) {
        if (&it_803F2ED0 == NULL) {
            pokemon_kind = (PokemonKind) Pokemon_Sonans;
        } else {
            pokemon_kind = it_8027A780(item, &it_803F2ED0);
        }
        // pokemon_kind = var_r3;
    } else if (gm_801A4310() == 0x18) {
        // temp_r4 = item->xC4_article_data;
        // temp_r29 = temp_r4->x4_specialAttributes;
        attr = item->xC4_article_data->x4_specialAttributes;

        rand_int = HSD_Randi(it_8027A364(item));
        // var_ctr = 0x1E;
        // var_r6 = temp_r29 + 0x284;
        var_r4 = 0;
        index1 = Pokemon_Tosakinto;

        index2 = Pokemon_Sonans;
        for (var_ctr = 30; var_ctr != 0; var_ctr--) {
            var_r4 += attr->x3C[index1 - Pokemon_Tosakinto];
            if ((Item_804A0E24.x != index2) && (Item_804A0E24.y != index2) &&
                ((var_r4 < rand_int) == 0))
            {
                Item_804A0E24.y = Item_804A0E24.x;
                var_r0 = index2 - Pokemon_Tosakinto;
                Item_804A0E24.x = index2;
                goto block_1;
            } else {
                index1++;
                index2++;
            }
        }
        var_r0 = 0;
    block_1:

        // loop_11:
        //         if (((s32) Item_804A0E24.x != index2) && ((s32)
        //         Item_804A0E24.y != index2) && (var_r4 += var_r6->unk-248,
        //         ((var_r4 < rand_int) == 0))) {
        //             Item_804A0E24.y = Item_804A0E24.x;
        //             var_r0 = index2 - Pokemon_Tosakinto;
        //             Item_804A0E24.x = index2;
        //         } else {
        //             var_r6 += 4;
        //             index2 += 1;
        //             var_ctr -= 1;
        //             if (var_ctr == 0) {
        //                 var_r0 = 0;
        //             } else {
        //                 goto loop_11;
        //             }
        //         }
        pokemon_kind = var_r0;
    } else {
        pokemon_kind = db_GetCurrentlySelectedPokemon();
        if (pokemon_kind == Pokemon_ID_Tosakinto) {
            pokemon_kind = it_8027A4D4(item);
        } else {
            pokemon_kind--;
        }
        if ((pokemon_kind == Pokemon_ID_Metamon) &&
            ((it_8026B3C0(Pokemon_Metamon) != 0) || (ftLib_800860C4() == 4)))
        {
            pokemon_kind = Pokemon_ID_Tosakinto;
        }
    }
    item = item_gobj->user_data;
    spawn.vel.z = 0.0f;
    spawn.vel.x = 0.0f;
    spawn.vel.y =
        ((it_279D_DatAttrs*) item->xC4_article_data->x4_specialAttributes)->x8;
    spawn.prev_pos = item->pos;
    spawn.prev_pos.z = 0.0f;
    it_8026BB88(item_gobj, &spawn.pos);
    spawn.x3C_damage = 0;
    spawn.facing_dir = it_8026B6A8(&spawn.prev_pos, item->owner);
    it_kind = pokemon_kind + Pokemon_Tosakinto;
    spawn.kind = it_kind;
    spawn.x0_parent_gobj = item->owner;
    spawn.x4_parent_gobj2 = (HSD_GObj*) item_gobj;
    spawn.x44_flag.b0 = 1;
    spawn.x40 = 0;
    if (spawn.kind == Pokemon_Cerebi) {
        gm_80172C04();
    }
    if (spawn.kind == Pokemon_Mew) {
        gm_80172BC4();
    }
    spawn_gobj = Item_80268B18(&spawn);
    if (spawn_gobj != NULL) {
        it_8027AAA0(item_gobj, spawn_gobj->user_data, spawn.kind);
        pl_8003E70C(spawn_gobj);
        db_80225DD8(spawn_gobj, (Fighter_GObj*) item->owner);
        it_8027B288(spawn_gobj, (u32) 0x440060);
        it_8027B564(spawn_gobj);
        return true;
    }
    return false;
}

void it_8027ADEC(int arg0, Item_GObj* item_gobj, HSD_JObj* arg2, f32 arg3)
{
    f32 sp1C;
    Item* item = GET_ITEM(item_gobj);
    sp1C = 1.0F;
    sp1C = item->xCC_item_attr->x60_scale * (1.0F / arg3);
    efSync_Spawn(arg0, item_gobj, arg2, &sp1C);
}

bool it_8027AE34(Item_GObj* item_gobj)
{
    Quaternion rotate;
    HSD_JObj* item_jobj;
    Item* item;
    PAD_STACK(4);

    item_jobj = item_gobj->hsd_obj;
    item = GET_ITEM((HSD_GObj*) item_gobj);
    rotate = it_803B8588;
    item->x40_vel.x = -item->x40_vel.x * item->xC70;
    item->facing_dir = -item->facing_dir;
    item->xD44_lifeTimer = item->xD48_halfLifeTimer;
    rotate.y = M_PI_2 * item->facing_dir;
    HSD_JObjSetRotation(item_jobj, &rotate);
    return false;
}

bool it_8027AF50(Item_GObj* item_gobj)
{
    Quaternion rotate;
    Item* item = GET_ITEM(item_gobj);
    HSD_JObj* item_jobj = GET_JOBJ(item_gobj);
    rotate = it_803B8598;
    lbVector_Mirror(&item->x40_vel, &item->xC58);
    it_80272980(item_gobj);
    rotate.y = M_PI_2 * item->facing_dir;
    HSD_JObjSetRotation(item_jobj, &rotate);
    return false;
}

void it_8027B070(Item_GObj* item_gobj, Fighter_GObj* owner_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    Fighter* fighter = GET_FIGHTER(owner_gobj);
    item->xD88_attackID = fighter->x2068_attackID;
    item->xD8C_attack_instance = fighter->x206C_attack_instance;
    item->xD90 = fighter->x2070;
    item->xD94 = fighter->x2074.x2074_vec;
    item->xD9C = fighter->x2074.x207C;
    item->xDA4_word = fighter->x2074.x2084;
    item->xDA8_short = fighter->x2074.x2088;
}

void it_8027B0C4(Item_GObj* item_gobj, SpawnItem* spawn)
{
    u8 _2[8];
    union Struct2070 sp24;

    if (ftLib_80086960(spawn->x0_parent_gobj)) {
        if (ftLib_80086960(spawn->x4_parent_gobj2)) {
            it_8027B070(item_gobj, spawn->x4_parent_gobj2);
        } else {
            Item* owner_item = spawn->x4_parent_gobj2->user_data;
            Item* spawn_item = GET_ITEM(item_gobj);
            spawn_item->xD88_attackID = owner_item->xD88_attackID;
            spawn_item->xD8C_attack_instance =
                owner_item->xD8C_attack_instance;
            spawn_item->xD90 = owner_item->xD90;
            spawn_item->xD94 = owner_item->xD94;
            spawn_item->xD9C = owner_item->xD9C;
            spawn_item->xDA4_word = owner_item->xDA4_word;
            spawn_item->xDA8_short = owner_item->xDA8_short;
        }
    } else {
        Item* spawn_item = GET_ITEM(item_gobj);
        sp24.x2070_int = 0;
        spawn_item->xD88_attackID = 1;
        spawn_item->xD8C_attack_instance = 0;
        spawn_item->xD90 = sp24;
        ft_80089768(&spawn_item->xD94);
        spawn_item->xDA8_short = 0;
    }
}

void it_8027B1F4(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    union Struct2070 sp10;

    sp10.x2070_int = 0;
    item->xD88_attackID = 1;
    item->xD8C_attack_instance = 0;
    item->xD90 = sp10;
    item->xDA8_short = 0;
    if (ftLib_80086960(item->owner)) {
        struct Struct2074* temp_r3 = ft_800898A8((Fighter_GObj*) item->owner);
        item->xD94 = temp_r3->x2074_vec;
        item->xD9C = temp_r3->x207C;
        item->xDA4_word = temp_r3->x2084;
        return;
    }
    ft_80089768(&item->xD94);
}

void it_8027B288(Item_GObj* item_gobj, u32 arg1)
{
    union Struct2070 sp14;
    union Struct2070 spC;
    Item* item;
    struct Struct2074* temp_r3;

    spC.x2070_int = arg1;
    item = item_gobj->user_data;
    sp14 = spC;
    // if ((sp14.flags.x0 == 0) || (sp14.flags.x0 != (u8) item->unkD93)) {
    if ((sp14.x2073 == 0) || (sp14.x2073 != item->xD90.x2073)) {
        item->xDA8_short = plAttack_80037B08();
    }
    item->xD90 = sp14;
    if (ftLib_80086960(item->owner)) {
        temp_r3 = ft_800898A8((Fighter_GObj*) item->owner);
        item->xD94 = temp_r3->x2074_vec;
        item->xD9C = temp_r3->x207C;
        item->xDA4_word = temp_r3->x2084;
        return;
    }
    ft_80089768(&item->xD94);
}

void it_8027B330(Item_GObj* item_gobj, u32 arg1)
{
    Item* item = GET_ITEM(item_gobj);
    if (arg1 == 1 || arg1 != item->xD88_attackID) {
        item->xD88_attackID = arg1;
        item->xD8C_attack_instance = plStale_IncrementAttackInstance();
    }
}

void it_8027B378(Fighter_GObj* fighter_gobj, Item_GObj* item_gobj, f32 arg2)
{
    s32 temp_r31;
    u8 temp_r30;
    u16 temp_r3;
    PAD_STACK(4);

    if (it_8026B6C8(item_gobj)) {
        temp_r30 = ft_80089884(fighter_gobj)->x2073;
        temp_r31 = ftLib_800874BC((HSD_GObj*) fighter_gobj);
        temp_r3 = ftLib_80086BE0((HSD_GObj*) fighter_gobj);
        pl_8003EB30(arg2, temp_r3, temp_r31, 6, 0, temp_r30);
    }
}

void it_8027B408(Item_GObj* item_gobj1, Item_GObj* item_gobj2, f32 arg8)
{
    s32 temp_r31;
    Item* item1;
    u16 temp_r3;

    if (it_8026B6C8(item_gobj2)) {
        item1 = item_gobj1->user_data;
        if (ftLib_80086960(item1->owner)) {
            HSD_GObj* owner = item1->owner;
            temp_r31 = ftLib_800874BC(owner);
            temp_r3 = ftLib_80086BE0(owner);
            pl_8003EB30(arg8, temp_r3, temp_r31, 6, 0, item1->xD90.x2073);
        }
    }
}

void it_8027B4A4(Fighter_GObj* item_gobj1, Item_GObj* item_gobj2)
{
    void* temp_r31;

    if (it_8026B6C8(item_gobj2)) {
        temp_r31 = (void*) ft_800898A8(item_gobj1);
        pl_800384DC((HSD_GObj*) item_gobj1, ft_80089884(item_gobj1)->x2073,
                    temp_r31);
    }
}

void it_8027B508(Item_GObj* item_gobj1, Item_GObj* item_gobj2)
{
    if (it_8026B6C8(item_gobj2)) {
        Item* item1 = GET_ITEM(item_gobj1);
        if (ftLib_80086960(item1->owner)) {
            pl_800384DC((HSD_GObj*) item1->owner, item1->xD90.x2073,
                        &item1->xD94);
        }
    }
}

void it_8027B564(Item_GObj* item_gobj)
{
    union Struct2070 sp10;
    Item* item;

    item = GET_ITEM((HSD_GObj*) item_gobj);
    if (ftLib_80086960(item->owner)) {
        sp10 = item->xD90;
        pl_80037DF4(item->owner, &sp10);
    }
}

Item_GObj* it_8027B5B0(ItemKind kind, Vec3* pos, HSD_JObj* jobj, Vec3* vel,
                       bool chk)
{
    Item* spawn_item;
    SpawnItem spawn;
    Vec3 sp20;
    Item_GObj* spawn_gobj;
    PAD_STACK(4);

    spawn.kind = kind;
    if (pos != NULL) {
        spawn.prev_pos = *pos;
    } else if (jobj != NULL) {
        lb_8000B1CC(jobj, NULL, &sp20);
        spawn.prev_pos = sp20;
    } else {
        OSReport("can t init zako pos\n");
    loop_5:
        goto loop_5;
    }
    spawn.pos = spawn.prev_pos;
    spawn.facing_dir = it_8026B684(&spawn.prev_pos);
    spawn.x3C_damage = 0;
    spawn.x44_flag.b0 = 1;
    if (vel != NULL) {
        spawn.vel = *vel;
    } else {
        spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0f;
    }
    spawn.x0_parent_gobj = NULL;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x40 = 0;
    if (chk == true) {
        spawn_gobj = Item_80268B18(&spawn);
    } else {
        spawn_gobj = Item_80268B5C(&spawn);
    }
    if (spawn_gobj != NULL) {
        spawn_item = spawn_gobj->user_data;
        spawn_item->xDD4_itemVar.it_27B5.x0 = jobj;
        spawn_item->xDD4_itemVar.it_27B5.x4 = -1;
        spawn_item->xDD4_itemVar.it_27B5.x14.z = 0.0f;
        spawn_item->x378_itemColl.x34_flags.b1234 = 3;
    }
    return spawn_gobj;
}

void it_8027B730(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xDD4_itemVar.it_27B5.x0 = 0;
    item->xDD4_itemVar.it_27B5.x4 = -1;
    item->xDD4_itemVar.it_27B5.x8.z = 0.0f;
    item->xDD4_itemVar.it_27B5.x8.x = 0.0f;
    item->xDD4_itemVar.it_27B5.x8.y = 1.0f;
    item->xDD4_itemVar.it_27B5.x14.x = 0;
    item->xDD4_itemVar.it_27B5.x14.y = 0;
    item->xDD4_itemVar.it_27B5.x14.z = 0;
    it_80275228(item_gobj);
    it_80275240(item_gobj);
}

bool it_8027B798(Item_GObj* item_gobj, Vec3* arg1)
{
    Vec3 sp14;
    Item* item;
    Vec3* temp_r31_2;
    f32 temp_f1;
    f32 temp_f2;
    f32 temp_f30;
    f32 temp_f31;
    f32 temp_f3;
    f32 temp_f4;
    f32 temp_f5;
    f32 angle;
    s32 degree_angle;
    bool ret_chk;
    PAD_STACK(8);

    ret_chk = false;
    item = item_gobj->user_data;
    degree_angle = item->xCAC_angle;
    temp_f1 = item->xCC8_knockback;
    temp_f31 = temp_f1 * p_ftCommonData->x100;
    if (degree_angle != 361) {
        angle = 0.0174533f * (f32) degree_angle;
    } else if (item->ground_or_air == GA_Air) {
        angle = p_ftCommonData->x144_radians;
    } else {
        temp_f3 = p_ftCommonData->x14C;
        if (temp_f1 < temp_f3) {
            angle = 0.0f;
        } else {
            temp_f4 = p_ftCommonData->x148;
            temp_f5 = 0.0174533f * temp_f4;
            angle =
                0.0174533f * ((temp_f4 * ((temp_f1 - temp_f3) /
                                          (p_ftCommonData->x150 - temp_f3))) +
                              1.0f);
            if (angle > temp_f5) {
                angle = temp_f5;
            }
        }
    }
    temp_f30 = temp_f31 * cosf(angle);
    temp_f2 = temp_f31 * sinf(angle);
    item->facing_dir = item->xCCC_incDamageDirection;
    if (item->ground_or_air == GA_Air) {
        arg1->x = -temp_f30 * item->facing_dir;
        arg1->y = temp_f2;
        arg1->z = 0.0f;
    } else {
        temp_r31_2 = &item->x378_itemColl.floor.normal;
        sp14.x = -temp_f30 * item->facing_dir;
        sp14.y = temp_f2;
        sp14.z = 0.0f;
        if (lbVector_Angle(temp_r31_2, &sp14) < 1.5708f)
        { // Should this be M_PI_2?
            ret_chk = true;
            arg1->x = sp14.x;
            arg1->y = sp14.y;
            arg1->z = 0.0f;
        } else {
            arg1->x = temp_r31_2->y * sp14.x;
            arg1->y = -temp_r31_2->x * sp14.x;
            arg1->z = 0.0f;
        }
    }
    return ret_chk;
}

void it_8027B964(Item_GObj* item_gobj, bool chk)
{
    Vec3 sp14;
    Item* item;
    f32 scale;

    item = GET_ITEM((HSD_GObj*) item_gobj);
    if (chk != 0) {
        it_8027781C(item_gobj);
    } else {
        it_8027B798(item_gobj, &item->x40_vel);
        if (!item->x40_vel.x && !item->x40_vel.y) {
            item->x40_vel.x = 0.1f * -item->xCCC_incDamageDirection;
            item->x40_vel.y = 0.1f;
        }
        if (!item->x40_vel.y) {
            item->x40_vel.y = 0.1f;
        }
    }
    sp14 = item->x40_vel;
    lbVector_Normalize(&sp14);
    scale = ((float*) it_804D6D40)[1];
    sp14.x *= scale;
    sp14.y *= scale;
    sp14.z *= scale;
    item->x40_vel = sp14;
}

// static inline u32 copy(u32 len, Vec3* src, Vec3* dst) {
//     *dst = *src;
//     return len;
// }

int it_8027BA54(HSD_GObj* item_gobj, Vec3* arg1)
{
    Vec3 sp20;
    Vec3 sp14;
    Item* item;

    item = GET_ITEM((HSD_GObj*) item_gobj);
    Camera_80030788(&sp20);
    sp20.x = ((10.0f * (HSD_Randf() - it_804DC7F8)) + sp20.x);
    sp20.y += 30.0f * HSD_Randf();
    lbVector_Diff(&sp20, &item->pos, &sp14);
    lbVector_Normalize(&sp14);
    sp14.x *= 10.0f;
    sp14.y *= 10.0f;
    sp14.z *= 10.0f;
    // copy(3, &sp14, arg1);
    *arg1 = sp14;
}

void it_8027BB1C(Vec3* arg0, Vec3* arg1)
{
    f32 cos;
    f32 sin;
    f32 t1;
    f32 t2;

    {
        cos = cosf(arg1->x);
        sin = sinf(arg1->x);
        t1 = arg0->y;
        t2 = arg0->z;
        arg0->y = (t1 * cos) - (t2 * sin);
        arg0->z = (t1 * sin) + (t2 * cos);
    }

    {
        cos = cosf(arg1->y);
        sin = sinf(arg1->y);
        t1 = arg0->x;
        t2 = arg0->z;
        arg0->x = (t1 * cos) + (t2 * sin);
        arg0->z = (t2 * cos) - (t1 * sin);
    }

    {
        cos = cosf(arg1->z);
        sin = sinf(arg1->z);
        t1 = (arg0->x * cos) - (arg0->y * sin);
        t2 = (arg0->x * sin) + (arg0->y * cos);
        arg0->x = t1;
        arg0->y = t2;
    }
}

void it_8027BBF4(Item_GObj* item_gobj, bool arg_chk, f64 arg8, f32 arg9)
{
    f32 temp_f1;
    f32 temp_f30;
    f32 var_f29;
    f32 var_f28;
    Vec3 sp74;
    Vec3 sp68;
    Vec3 sp5C;
    Vec3 sp50;
    Vec3 sp44;
    Vec3 sp38;
    HSD_JObj* item_jobj;
    Item* item;
    CollData* coll;

    item = GET_ITEM((HSD_GObj*) item_gobj);
    item_jobj = item_gobj->hsd_obj;
    coll = &item->x378_itemColl;
    sp68 = it_803B85A8[2];
    sp5C = it_803B85A8[3];

    if (!arg_chk) {
        if (coll->env_flags & Collide_FloorMask) {
            sp68 = coll->floor.normal;
            goto block_7;
        }
        return;
    } else if (coll->env_flags & Collide_CeilingMask) {
        sp68 = coll->ceiling.normal;
        goto block_7;
    }
    return;

block_7:

    sp74.x = HSD_JObjGetRotationX(item_jobj);
    sp74.y = HSD_JObjGetRotationY(item_jobj);
    sp74.z = HSD_JObjGetRotationZ(item_jobj);

    it_8027BB1C(&sp5C, &sp74);
    if (lbVector_AngleXY(&item->xDD4_itemVar.it_27B5.x8, &sp68) > deg_to_rad) {
        item->xDD4_itemVar.it_27B5.x8 = sp68;
        item->xDD4_itemVar.it_27B5.x14.x = (s32) arg9;
    }
    temp_f1 = lbVector_AngleXY(&sp5C, &item->xDD4_itemVar.it_27B5.x8);
    if ((temp_f1 < deg_to_rad) || item->xDD4_itemVar.it_27B5.x14.x < 2) {
        var_f29 = sp68.x;
        var_f28 = sp68.y;
    } else {
        var_f29 = temp_f1 / (f32) item->xDD4_itemVar.it_27B5.x14.x;
        item->xDD4_itemVar.it_27B5.x14.x--;
        if (((sp5C.x * sp68.y) - (sp5C.y * sp68.x)) < 0) {
            var_f29 = -var_f29;
        }
        temp_f30 = cosf(var_f29);
        temp_f1 = sinf(var_f29);
        var_f29 = (sp5C.x * temp_f30) - (sp5C.y * temp_f1);
        var_f28 = (sp5C.x * temp_f1) + (sp5C.y * temp_f30);
    }

    sp44 = it_803B85A8[0];
    sp50 = it_803B85A8[1];
    lbVector_Rotate(&sp50, 2, M_PI_2 * arg8);
    lbVector_Rotate(&sp44, 2, M_PI_2 * arg8);

    sp38.x = var_f29;
    sp38.y = var_f28;
    sp38.z = 0.0f;
    lbVector_CrossprodNormalized(&sp38, &sp50, &sp44);
    lbVector_CrossprodNormalized(&sp44, &sp38, &sp50);
    lbVector_EulerAnglesFromONB(&sp74, &sp50, &sp44, &sp38);

    HSD_JObjSetRotationX(item_jobj, sp74.x);
    HSD_JObjSetRotationY(item_jobj, sp74.y);
    HSD_JObjSetRotationZ(item_jobj, sp74.z);
}

// Might take in and pass more vars
void it_8027C0A8(Item_GObj* item_gobj, f32 arg4, f32 arg5)
{
    it_8027BBF4(item_gobj, false, arg4, arg5);
}

// Might take in and pass more vars
void it_8027C0CC(Item_GObj* item_gobj, f32 arg4, f32 arg5)
{
    it_8027BBF4(item_gobj, true, arg4, arg5);
}

void it_8027C0F0(Item_GObj* item_gobj, Vec3* arg1, f64 arg8, f32 arg9)
{
    f32 temp_f1;
    f32 temp_f30;
    f32 var_f29;
    f32 var_f28;
    Vec3 sp74;
    Vec3 sp68;
    Vec3 sp5C;
    Vec3 sp50;
    Vec3 sp44;
    Vec3 sp38;
    Item* item = GET_ITEM((HSD_GObj*) item_gobj);
    HSD_JObj* item_jobj = GET_JOBJ((HSD_GObj*) item_gobj);
    PAD_STACK(4);

    sp68 = it_803B85A8[4];
    sp5C = it_803B85A8[5];

    if (item->x378_itemColl.env_flags & Collide_FloorMask) {
        if (arg1 != NULL) {
            sp68 = *arg1;
        }
        sp74.x = HSD_JObjGetRotationX(item_jobj);
        sp74.y = HSD_JObjGetRotationY(item_jobj);
        sp74.z = HSD_JObjGetRotationZ(item_jobj);
        it_8027BB1C(&sp5C, &sp74);

        if (lbVector_AngleXY(&item->xDD4_itemVar.it_27B5.x8, &sp68) >
            deg_to_rad)
        {
            item->xDD4_itemVar.it_27B5.x8 = sp68;
            item->xDD4_itemVar.it_27B5.x14.x = (s32) arg9;
        }
        temp_f1 = lbVector_AngleXY(&sp5C, &item->xDD4_itemVar.it_27B5.x8);
        if ((temp_f1 < deg_to_rad) || item->xDD4_itemVar.it_27B5.x14.x < 2) {
            var_f29 = sp68.x;
            var_f28 = sp68.y;
        } else {
            var_f29 = temp_f1 / (f32) item->xDD4_itemVar.it_27B5.x14.x;
            item->xDD4_itemVar.it_27B5.x14.x--;
            if (((sp5C.x * sp68.y) - (sp5C.y * sp68.x)) < 0) {
                var_f29 = -var_f29;
            }
            temp_f30 = cosf(var_f29);
            temp_f1 = sinf(var_f29);
            var_f29 = (sp5C.x * temp_f30) - (sp5C.y * temp_f1);
            var_f28 = (sp5C.x * temp_f1) + (sp5C.y * temp_f30);
        }

        sp44 = it_803B85A8[0];
        sp50 = it_803B85A8[1];
        lbVector_Rotate(&sp50, 2, M_PI_2 * arg8);
        lbVector_Rotate(&sp44, 2, M_PI_2 * arg8);
        sp38.x = var_f29;
        sp38.y = var_f28;
        sp38.z = 0.0f;
        lbVector_CrossprodNormalized(&sp38, &sp50, &sp44);
        lbVector_CrossprodNormalized(&sp44, &sp38, &sp50);
        lbVector_EulerAnglesFromONB(&sp74, &sp50, &sp44, &sp38);

        HSD_JObjSetRotationX(item_jobj, sp74.x);
        HSD_JObjSetRotationY(item_jobj, sp74.y);
        HSD_JObjSetRotationZ(item_jobj, sp74.z);
    }
}

void it_8027C56C(Item_GObj* item_gobj, f32 y_rot)
{
    Item* item;
    HSD_JObj* item_jobj;
    // char msg = it_803F5428;

    item_jobj = GET_JOBJ((HSD_GObj*) item_gobj);
    item = GET_ITEM((HSD_GObj*) item_gobj);
    HSD_JObjSetRotationX(item_jobj, 0.0f);
    HSD_JObjSetRotationY(item_jobj, M_PI_2 * y_rot);
    HSD_JObjSetRotationZ(item_jobj, 0.0f);

    item->xDD4_itemVar.it_27B5.x8.z = 0.0f;
    item->xDD4_itemVar.it_27B5.x8.x = 0.0f;
    item->xDD4_itemVar.it_27B5.x8.y = 1.0f;
    item->xDD4_itemVar.it_27B5.x14.x = 0U;
}

bool it_8027C794(Item_GObj* gobj)
{
    return false;
}

bool it_8027C79C(Item_GObj* item_gobj)
{
    Item* item;
    PAD_STACK(4);

    if (it_8026DAA8(item_gobj) & 0xF) {
        item = GET_ITEM((HSD_GObj*) item_gobj);
        it_8027C9D8(item);
        it_8027B964(item_gobj, 1);
        item->xDD4_itemVar.it_27B5.x14.y++;
        // if (item->xDD4_itemVar.it_27B5.x14.y > (f32) (u8) &it_804D6D40) {
        // if (item->xDD4_itemVar.it_27B5.x14.y > ((ItemAttr*) ((Article*)
        // it_804D6D40)->x0_common_attr)->x0_is_heavy) {
        if (item->xDD4_itemVar.it_27B5.x14.y > ((S32Vec3*) it_804D6D40)->x) {
            it_8027CC88(item_gobj);
            return true;
        }
    }
    return false;
}

bool it_8027C824(Item_GObj* item_gobj, s32 (*arg_func)(Item_GObj*))
{
    s32 arg_func_ret_val;

    if (it_8026DAA8(item_gobj) & 0xF) {
        it_8027CC88(item_gobj);
        if (arg_func != NULL) {
            arg_func_ret_val = arg_func(item_gobj);
            if (arg_func_ret_val != 0) {
                it_8027CE44(item_gobj);
            }
            return arg_func_ret_val;
        }
        it_8027CE44(item_gobj);
        return true;
    }
    return false;
}

void it_2725_Logic9_Destroyed(Item_GObj* item_gobj)
{
    grZakoGenerator_801CAC14();
}

static inline float product_xyz(Vec3* a, Vec3* b)
{
    return (a->x * b->x + a->y * b->y + a->z * b->z);
}

static inline float return_sqrt_value3(Vec3* v)
{
    return sqrtf(product_xyz(v, v));
}

void it_8027C8D0(Vec3* arg0, Vec3* arg1, f32 arg8)
{
    f32 dir;
    f32 vec_mag;
    f32 var_f6;
    Vec3 sp1C;

    vec_mag = return_sqrt_value3(arg0);
    sp1C = *arg1;
    if (arg8 > 0.0f) {
        dir = -1.0f;
        var_f6 = 6.8074177e-9f;
    } else if (arg8 < 0.0f) {
        dir = 1.0f;
        var_f6 = 6.8074177e-9f;
    } else {
        arg0->z = 0.0f;
        arg0->y = 0.0f;
        arg0->x = 0.0f;
        return;
    }

    arg0->x = vec_mag * ((sp1C.x * var_f6) - (sp1C.y * dir));
    arg0->y = vec_mag * ((sp1C.x * dir) + (sp1C.y * var_f6));
    arg0->z = 0.0f;
}

void it_8027C9D8(Item* item)
{
    s32 spC[4] = {
        0x131,
        0x132,
        0x133,
        0x134,
    };
    s32 var_r3;

    var_r3 = spC[HSD_Randi(4)];
    while (var_r3 == item->xDD4_itemVar.it_27B5.x14.z) {
        var_r3 = spC[HSD_Randi(4)];
    }
    item->xDD4_itemVar.it_27B5.x14.z = var_r3;
    Item_8026AE84(item, item->xDD4_itemVar.it_27B5.x14.z, 127, 64);
}

bool it_8027CA7C(HSD_GObj* gobj)
{
    bool chk;

    chk = false;
    if (ftLib_80086C0C(gobj) == 0x14E) {
        chk = true;
    }
    if (ftLib_80086C0C(gobj) == 0x14D) {
        chk = true;
    }
    return chk;
}

#pragma push
#pragma dont_inline on

void it_8027CAD8(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->x40_vel.y = 0.0f;
    item->x40_vel.x = 0.0f;
    it_8027542C(item_gobj);
    it_80275444(item_gobj);
    it_80274740(item_gobj);
    item->owner = NULL;
    it_80275270(item_gobj);
}

void it_8027CB3C(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    it_8026C220(item_gobj, item->owner);
    item->facing_dir = ftLib_800865C0(item->owner);
    it_80275414(item_gobj);
    it_80275474(item_gobj);
    it_802762BC(item);
    it_8026B3A8(item_gobj);
}

void it_8027CBA4(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->facing_dir = ftLib_800865C0(item->owner);
    it_802762BC(item);
    it_802754D4(item_gobj);
    it_8026B3A8(item_gobj);
}

#pragma pop

f32 it_8027CBFC(Item_GObj* item_gobj)
{
    s32 ret_val;
    PAD_STACK(4);

    ret_val = 0U;
    switch (GET_ITEM((HSD_GObj*) item_gobj)->xCC4) {
    case 6:
    case 7:
        ret_val = *(f32*) ((u8*) it_804D6D40 + 0xC);
        // ret_val = *(f32*) &((Article*) it_804D6D40)->xC_itemStates;
        break;
    case 9:
        ret_val = *(f32*) ((u8*) it_804D6D40 + 0x10);
        // ret_val = *(f32*) &((Article*) it_804D6D40)->x10_modelDesc;
        break;
    case 4:
    case 5:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
        break;
    }
    return (f32) ret_val;
}

Item_GObj* it_8027CC88(Item_GObj* item_gobj_arg)
{
    s32 temp_r3;
    s32 temp_r3_2;
    s32 var_r30;
    Item_GObj* item_gobj_var;
    Item* var_item;
    u32 pad[20];
    Vec3 sp44;
    u32 sp1C[10];
    u32 pad2[4];

    item_gobj_var = NULL;
    if ((gm_8016B498() != 0) &&
        (HSD_Randi(*(f32*) ((u8*) it_804D6D40 + 0x14)) == 0))
    {
        if (grLib_801C9E40() == 0) {
            var_r30 = Ground_801C5840();
            if (var_r30 != -1) {
                temp_r3 =
                    un_8031C354(var_r30, (s32(*)[]) & sp1C[0], 0xA, 0x63);
                temp_r3_2 =
                    temp_r3 + un_8031C354(var_r30,
                                          (s32(*)[]) & (&sp1C[0])[temp_r3],
                                          0xA, 2);
                if (temp_r3_2 != 0) {
                    var_r30 = (&sp1C[0])[HSD_Randi(temp_r3_2)];
                }
                it_8026BB88(item_gobj_arg, &sp44);
                item_gobj_var = it_802F2094(NULL, &sp44, var_r30, 0);
                if (item_gobj_var != 0) {
                    var_item = item_gobj_var->user_data;
                    var_item->x40_vel.x =
                        ((2.0f * (HSD_Randf() - 0.5f)) *
                         (*((f32*) &it_804D6D28->x54_float)));
                    var_item->x40_vel.y = var_item->xCC_item_attr->x18;
                    var_item->x40_vel.z = 0.0f;
                    grLib_801C9E50(1);
                }
            }
        } else if (grLib_801C9E40() >= *((f32*) it_804D6D40 + 6)) {
            grLib_801C9E50(0);
        } else {
            grLib_801C9E50(grLib_801C9E40() + 1);
        }
    }
    return item_gobj_var;
}

void it_8027CE18(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    pl_8004049C(item->xCB0_source_ply, item->kind);
}

void it_8027CE44(Item_GObj* item_gobj)
{
    grZakoGenerator_801CACB8((Ground_GObj*) item_gobj);
}

#pragma push
#pragma dont_inline on

// Appears to be a function for Game&Watch items
void it_8027CE64(Item_GObj* item_gobj, HSD_GObj* fighter_gobj,
                 void* arg_attr_address)
{
    Item* item;
    GXColor sp18;
    u32 pad[1];

    item = item_gobj->user_data;
    item->xDCF_flag.b3 = true;
    ftLib_8008770C(fighter_gobj, (void*) &sp18);
    it_80278574((HSD_GObj*) item_gobj, &sp18);
    ftLib_80087744(fighter_gobj, &item->xBC8);
    item->x5C8 = ftLib_800870BC(item->owner, (void**) &item->xBC4);
    it_80274594(item_gobj);
    item->xDD4_itemVar.it_27CE.attr = arg_attr_address;
}

#pragma pop
