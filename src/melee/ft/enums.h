#ifndef MELEE_FT_ENUMS_H
#define MELEE_FT_ENUMS_H

enum ftCommonAction {
    ASID_DEADDOWN,
    ASID_DEADLEFT,
    ASID_DEADRIGHT,
    ASID_DEADUP,
    ASID_DEADUPSTAR,
    ASID_DEADUPSTARICE,
    ASID_DEADUPFALL,
    ASID_DEADUPFALLHITCAMERA,
    ASID_DEADUPFALLHITCAMERAFLAT,
    ASID_DEADUPFALLICE,
    ASID_DEADUPFALLHITCAMERAICE,
    ASID_SLEEP,
    ASID_REBIRTH,
    ASID_REBIRTHWAIT,
    ASID_WAIT,
    ASID_WALKSLOW,
    ASID_WALKMIDDLE,
    ASID_WALKFAST,
    ASID_TURN,
    ASID_TURNRUN,
    ASID_DASH,
    ASID_RUN,
    ASID_RUNDIRECT,
    ASID_RUNBRAKE,
    ASID_KNEEBEND,
    ASID_JUMPF,
    ASID_JUMPB,
    ASID_JUMPAERIALF,
    ASID_JUMPAERIALB,
    ASID_FALL,
    ASID_FALLF,
    ASID_FALLB,
    ASID_FALLAERIAL,
    ASID_FALLAERIALF,
    ASID_FALLAERIALB,
    ASID_FALLSPECIAL,
    ASID_FALLSPECIALF,
    ASID_FALLSPECIALB,
    ASID_DAMAGEFALL,
    ASID_SQUAT,
    ASID_SQUATWAIT,
    ASID_SQUATRV,
    ASID_LANDING,
    ASID_LANDINGFALLSPECIAL,
    ASID_ATTACK11,
    ASID_ATTACK12,
    ASID_ATTACK13,
    ASID_ATTACK100START,
    ASID_ATTACK100LOOP,
    ASID_ATTACK100END,
    ASID_ATTACKDASH,
    ASID_ATTACKS3HI,
    ASID_ATTACKS3HIS,
    ASID_ATTACKS3S,
    ASID_ATTACKS3LWS,
    ASID_ATTACKS3LW,
    ASID_ATTACKHI3,
    ASID_ATTACKLW3,
    ASID_ATTACKS4HI,
    ASID_ATTACKS4HIS,
    ASID_ATTACKS4S,
    ASID_ATTACKS4LWS,
    ASID_ATTACKS4LW,
    ASID_ATTACKHI4,
    ASID_ATTACKLW4,
    ASID_ATTACKAIRN,
    ASID_ATTACKAIRF,
    ASID_ATTACKAIRB,
    ASID_ATTACKAIRHI,
    ASID_ATTACKAIRLW,
    ASID_LANDINGAIRN,
    ASID_LANDINGAIRF,
    ASID_LANDINGAIRB,
    ASID_LANDINGAIRHI,
    ASID_LANDINGAIRLW,
    ASID_DAMAGEHI1,
    ASID_DAMAGEHI2,
    ASID_DAMAGEHI3,
    ASID_DAMAGEN1,
    ASID_DAMAGEN2,
    ASID_DAMAGEN3,
    ASID_DAMAGELW1,
    ASID_DAMAGELW2,
    ASID_DAMAGELW3,
    ASID_DAMAGEAIR1,
    ASID_DAMAGEAIR2,
    ASID_DAMAGEAIR3,
    ASID_DAMAGEFLYHI,
    ASID_DAMAGEFLYN,
    ASID_DAMAGEFLYLW,
    ASID_DAMAGEFLYTOP,
    ASID_DAMAGEFLYROLL,
    ASID_LIGHTGET,
    ASID_HEAVYGET,
    ASID_LIGHTTHROWF,
    ASID_LIGHTTHROWB,
    ASID_LIGHTTHROWHI,
    ASID_LIGHTTHROWLW,
    ASID_LIGHTTHROWDASH,
    ASID_LIGHTTHROWDROP,
    ASID_LIGHTTHROWAIRF,
    ASID_LIGHTTHROWAIRB,
    ASID_LIGHTTHROWAIRHI,
    ASID_LIGHTTHROWAIRLW,
    ASID_HEAVYTHROWF,
    ASID_HEAVYTHROWB,
    ASID_HEAVYTHROWHI,
    ASID_HEAVYTHROWLW,
    ASID_LIGHTTHROWF4,
    ASID_LIGHTTHROWB4,
    ASID_LIGHTTHROWHI4,
    ASID_LIGHTTHROWLW4,
    ASID_LIGHTTHROWAIRF4,
    ASID_LIGHTTHROWAIRB4,
    ASID_LIGHTTHROWAIRHI4,
    ASID_LIGHTTHROWAIRLW4,
    ASID_HEAVYTHROWF4,
    ASID_HEAVYTHROWB4,
    ASID_HEAVYTHROWHI4,
    ASID_HEAVYTHROWLW4,
    ASID_SWORDSWING1,
    ASID_SWORDSWING3,
    ASID_SWORDSWING4,
    ASID_SWORDSWINGDASH,
    ASID_BATSWING1,
    ASID_BATSWING3,
    ASID_BATSWING4,
    ASID_BATSWINGDASH,
    ASID_PARASOLSWING1,
    ASID_PARASOLSWING3,
    ASID_PARASOLSWING4,
    ASID_PARASOLSWINGDASH,
    ASID_HARISENSWING1,
    ASID_HARISENSWING3,
    ASID_HARISENSWING4,
    ASID_HARISENSWINGDASH,
    ASID_STARRODSWING1,
    ASID_STARRODSWING3,
    ASID_STARRODSWING4,
    ASID_STARRODSWINGDASH,
    ASID_LIPSTICKSWING1,
    ASID_LIPSTICKSWING3,
    ASID_LIPSTICKSWING4,
    ASID_LIPSTICKSWINGDASH,
    ASID_ITEMPARASOLOPEN,
    ASID_ITEMPARASOLFALL,
    ASID_ITEMPARASOLFALLSPECIAL,
    ASID_ITEMPARASOLDAMAGEFALL,
    ASID_LGUNSHOOT,
    ASID_LGUNSHOOTAIR,
    ASID_LGUNSHOOTEMPTY,
    ASID_LGUNSHOOTAIREMPTY,
    ASID_FIREFLOWERSHOOT,
    ASID_FIREFLOWERSHOOTAIR,
    ASID_ITEMSCREW,
    ASID_ITEMSCREWAIR,
    ASID_DAMAGESCREW,
    ASID_DAMAGESCREWAIR,
    ASID_ITEMSCOPESTART,
    ASID_ITEMSCOPERAPID,
    ASID_ITEMSCOPEFIRE,
    ASID_ITEMSCOPEEND,
    ASID_ITEMSCOPEAIRSTART,
    ASID_ITEMSCOPEAIRRAPID,
    ASID_ITEMSCOPEAIRFIRE,
    ASID_ITEMSCOPEAIREND,
    ASID_ITEMSCOPESTARTEMPTY,
    ASID_ITEMSCOPERAPIDEMPTY,
    ASID_ITEMSCOPEFIREEMPTY,
    ASID_ITEMSCOPEENDEMPTY,
    ASID_ITEMSCOPEAIRSTARTEMPTY,
    ASID_ITEMSCOPEAIRRAPIDEMPTY,
    ASID_ITEMSCOPEAIRFIREEMPTY,
    ASID_ITEMSCOPEAIRENDEMPTY,
    ASID_LIFTWAIT,
    ASID_LIFTWALK1,
    ASID_LIFTWALK2,
    ASID_LIFTTURN,
    ASID_GUARDON,
    ASID_GUARD,
    ASID_GUARDOFF,
    ASID_GUARDSETOFF,
    ASID_GUARDREFLECT,
    ASID_DOWNBOUNDU,
    ASID_DOWNWAITU,
    ASID_DOWNDAMAGEU,
    ASID_DOWNSTANDU,
    ASID_DOWNATTACKU,
    ASID_DOWNFOWARDU,
    ASID_DOWNBACKU,
    ASID_DOWNSPOTU,
    ASID_DOWNBOUNDD,
    ASID_DOWNWAITD,
    ASID_DOWNDAMAGED,
    ASID_DOWNSTANDD,
    ASID_DOWNATTACKD,
    ASID_DOWNFOWARDD,
    ASID_DOWNBACKD,
    ASID_DOWNSPOTD,
    ASID_PASSIVE,
    ASID_PASSIVESTANDF,
    ASID_PASSIVESTANDB,
    ASID_PASSIVEWALL,
    ASID_PASSIVEWALLJUMP,
    ASID_PASSIVECEIL,
    ASID_SHIELDBREAKFLY,
    ASID_SHIELDBREAKFALL,
    ASID_SHIELDBREAKDOWNU,
    ASID_SHIELDBREAKDOWND,
    ASID_SHIELDBREAKSTANDU,
    ASID_SHIELDBREAKSTANDD,
    ASID_FURAFURA,
    ASID_CATCH,
    ASID_CATCHPULL,
    ASID_CATCHDASH,
    ASID_CATCHDASHPULL,
    ASID_CATCHWAIT,
    ASID_CATCHATTACK,
    ASID_CATCHCUT,
    ASID_THROWF,
    ASID_THROWB,
    ASID_THROWHI,
    ASID_THROWLW,
    ASID_CAPTUREPULLEDHI,
    ASID_CAPTUREWAITHI,
    ASID_CAPTUREDAMAGEHI,
    ASID_CAPTUREPULLEDLW,
    ASID_CAPTUREWAITLW,
    ASID_CAPTUREDAMAGELW,
    ASID_CAPTURECUT,
    ASID_CAPTUREJUMP,
    ASID_CAPTURENECK,
    ASID_CAPTUREFOOT,
    ASID_ESCAPEF,
    ASID_ESCAPEB,
    ASID_ESCAPE,
    ASID_ESCAPEAIR,
    ASID_REBOUNDSTOP,
    ASID_REBOUND,
    ASID_THROWNF,
    ASID_THROWNB,
    ASID_THROWNHI,
    ASID_THROWNLW,
    ASID_THROWNLWWOMEN,
    ASID_PASS,
    ASID_OTTOTTO,
    ASID_OTTOTTOWAIT,
    ASID_FLYREFLECTWALL,
    ASID_FLYREFLECTCEIL,
    ASID_STOPWALL,
    ASID_STOPCEIL,
    ASID_MISSFOOT,
    ASID_CLIFFCATCH,
    ASID_CLIFFWAIT,
    ASID_CLIFFCLIMBSLOW,
    ASID_CLIFFCLIMBQUICK,
    ASID_CLIFFATTACKSLOW,
    ASID_CLIFFATTACKQUICK,
    ASID_CLIFFESCAPESLOW,
    ASID_CLIFFESCAPEQUICK,
    ASID_CLIFFJUMPSLOW1,
    ASID_CLIFFJUMPSLOW2,
    ASID_CLIFFJUMPQUICK1,
    ASID_CLIFFJUMPQUICK2,
    ASID_APPEALR,
    ASID_APPEALL,
    ASID_SHOULDEREDWAIT,
    ASID_SHOULDEREDWALKSLOW,
    ASID_SHOULDEREDWALKMIDDLE,
    ASID_SHOULDEREDWALKFAST,
    ASID_SHOULDEREDTURN,
    ASID_THROWNFF,
    ASID_THROWNFB,
    ASID_THROWNFHI,
    ASID_THROWNFLW,
    ASID_CAPTURECAPTAIN,
    ASID_CAPTUREYOSHI,
    ASID_YOSHIEGG,
    ASID_CAPTUREKOOPA,
    ASID_CAPTUREDAMAGEKOOPA,
    ASID_CAPTUREWAITKOOPA,
    ASID_THROWNKOOPAF,
    ASID_THROWNKOOPAB,
    ASID_CAPTUREKOOPAAIR,
    ASID_CAPTUREDAMAGEKOOPAAIR,
    ASID_CAPTUREWAITKOOPAAIR,
    ASID_THROWNKOOPAAIRF,
    ASID_THROWNKOOPAAIRB,
    ASID_CAPTUREKIRBY,
    ASID_CAPTUREWAITKIRBY,
    ASID_THROWNKIRBYSTAR,
    ASID_THROWNCOPYSTAR,
    ASID_THROWNKIRBY,
    ASID_BARRELWAIT,
    ASID_BURY,
    ASID_BURYWAIT,
    ASID_BURYJUMP,
    ASID_DAMAGESONG,
    ASID_DAMAGESONGWAIT,
    ASID_DAMAGESONGRV,
    ASID_DAMAGEBIND,
    ASID_CAPTUREMEWTWO,
    ASID_CAPTUREMEWTWOAIR,
    ASID_THROWNMEWTWO,
    ASID_THROWNMEWTWOAIR,
    ASID_WARPSTARJUMP,
    ASID_WARPSTARFALL,
    ASID_HAMMERWAIT,
    ASID_HAMMERWALK,
    ASID_HAMMERTURN,
    ASID_HAMMERKNEEBEND,
    ASID_HAMMERFALL,
    ASID_HAMMERJUMP,
    ASID_HAMMERLANDING,
    ASID_KINOKOGIANTSTART,
    ASID_KINOKOGIANTSTARTAIR,
    ASID_KINOKOGIANTEND,
    ASID_KINOKOGIANTENDAIR,
    ASID_KINOKOSMALLSTART,
    ASID_KINOKOSMALLSTARTAIR,
    ASID_KINOKOSMALLEND,
    ASID_KINOKOSMALLENDAIR,
    ASID_ENTRY,
    ASID_ENTRYSTART,
    ASID_ENTRYEND,
    ASID_DAMAGEICE,
    ASID_DAMAGEICEJUMP,
    ASID_CAPTUREMASTERHAND,
    ASID_CAPTUREDAMAGEMASTERHAND,
    ASID_CAPTUREWAITMASTERHAND,
    ASID_THROWNMASTERHAND,
    ASID_CAPTUREKIRBYYOSHI,
    ASID_KIRBYYOSHIEGG,
    ASID_CAPTURELEADEAD,
    ASID_CAPTURELIKELIKE,
    ASID_DOWNREFLECT,
    ASID_CAPTURECRAZYHAND,
    ASID_CAPTUREDAMAGECRAZYHAND,
    ASID_CAPTUREWAITCRAZYHAND,
    ASID_THROWNCRAZYHAND,
    ASID_BARREL,
    ASID_MAX
};

#endif
