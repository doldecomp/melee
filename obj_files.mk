# Linker order for every file, passed to the Metrowerks linker.

INIT_O_FILES :=\
    $(BUILD_DIR)/src/Runtime/__mem.c.o\
    $(BUILD_DIR)/src/MetroTRK/mem_TRK.c.o\
    $(BUILD_DIR)/asm/init.s.o\
    $(BUILD_DIR)/src/dolphin/os/init/__start.c.o

EXTAB_O_FILES :=\
    $(BUILD_DIR)/asm/extab.s.o

EXTABINDEX_O_FILES :=\
    $(BUILD_DIR)/asm/extabindex.s.o

TEXT_O_FILES :=\
    $(BUILD_DIR)/src/melee/lb/lbcommand.c.o\
    $(BUILD_DIR)/src/melee/lb/lbcollision.c.o\
    $(BUILD_DIR)/asm/melee/lb/lbcollision.s.o\
    $(BUILD_DIR)/src/melee/lb/lblanguage.c.o\
    $(BUILD_DIR)/src/melee/lb/lbtime.c.o\
    $(BUILD_DIR)/src/melee/lb/lb_00B0.c.o\
    $(BUILD_DIR)/asm/melee/lb/lb_00CE.s.o\
    $(BUILD_DIR)/src/melee/lb/lbvector.c.o\
    $(BUILD_DIR)/asm/melee/lb/lbshadow.s.o\
    $(BUILD_DIR)/asm/melee/lb/lb_00F9.s.o\
    $(BUILD_DIR)/asm/melee/lb/lbarq.s.o\
    $(BUILD_DIR)/asm/melee/lb/lbmemory.s.o\
    $(BUILD_DIR)/asm/melee/lb/lbheap.s.o\
    $(BUILD_DIR)/src/melee/lb/lbfile.c.o\
    $(BUILD_DIR)/src/melee/lb/lbarchive.c.o\
    $(BUILD_DIR)/asm/melee/lb/lbarchive.s.o\
    $(BUILD_DIR)/asm/melee/lb/lbdvd.s.o\
    $(BUILD_DIR)/asm/melee/lb/lb_0192.s.o\
    $(BUILD_DIR)/asm/melee/lb/lb_0198.s.o\
    $(BUILD_DIR)/asm/melee/lb/lbsnap.s.o\
    $(BUILD_DIR)/asm/melee/lb/lbgx.s.o\
    $(BUILD_DIR)/asm/melee/lb/lbanim.s.o\
    $(BUILD_DIR)/asm/melee/lb/lbmthp.s.o\
    $(BUILD_DIR)/asm/melee/lb/lbjpeg.s.o\
    $(BUILD_DIR)/asm/melee/lb/lbbgflash.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/asm/melee/lb/lbrefract_data.s.o\
    $(BUILD_DIR)/asm/melee/lb/lbrefract1.s.o\
    $(BUILD_DIR)/asm/melee/lb/lbrefract2.s.o\
    $(BUILD_DIR)/asm/melee/lb/lbrefract3.s.o\
    $(BUILD_DIR)/src/melee/lb/lbrefract3.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/asm/melee/lb/lbaudio_ax.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/asm/melee/cm/camera.s.o\
    $(BUILD_DIR)/src/melee/cm/cmsnap.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/melee/pl/player.c.o\
    $(BUILD_DIR)/asm/melee/pl/pl_0371.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/melee/mp/mpcoll.c.o\
    $(BUILD_DIR)/asm/melee/mp/mpcoll.s.o\
    $(BUILD_DIR)/asm/melee/mp/mplib.s.o\
    $(BUILD_DIR)/asm/melee/mp/mpisland.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/asm/melee/ef/eflib.s.o\
    $(BUILD_DIR)/asm/melee/ef/efsync.s.o\
    $(BUILD_DIR)/asm/melee/ef/ef_061D.s.o\
    $(BUILD_DIR)/asm/melee/ef/efasync.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/melee/ft/fighter.c.o\
    $(BUILD_DIR)/asm/melee/ft/ftanim.s.o\
    $(BUILD_DIR)/src/melee/ft/ftaction.c.o\
    $(BUILD_DIR)/src/melee/ft/ftparts.c.o\
    $(BUILD_DIR)/src/melee/ft/ftcamera.c.o\
    $(BUILD_DIR)/src/melee/ft/ftcoll.c.o\
    $(BUILD_DIR)/asm/melee/ft/ftcoll.s.o\
    $(BUILD_DIR)/src/melee/ft/ft_07C1.c.o\
    $(BUILD_DIR)/src/melee/ft/ft_07C6.c.o\
    $(BUILD_DIR)/src/melee/ft/ftcommon.c.o\
    $(BUILD_DIR)/src/melee/ft/ftdrawcommon.c.o\
    $(BUILD_DIR)/asm/melee/ft/ftdrawcommon_data.s.o\
    $(BUILD_DIR)/src/melee/ft/ftcliffcommon.c.o\
    $(BUILD_DIR)/src/melee/ft/ftwalljump.c.o\
    $(BUILD_DIR)/src/melee/ft/ft_0819.c.o\
    $(BUILD_DIR)/src/melee/ft/ft_081B.c.o\
    $(BUILD_DIR)/asm/melee/ft/ft_0852.s.o\
    $(BUILD_DIR)/src/melee/ft/ftdata.c.o\
    $(BUILD_DIR)/src/melee/ft/ftdata2.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftCommon/ftCo_Init.c.o\
    $(BUILD_DIR)/asm/melee/ft/ftdata.s.o\
    $(BUILD_DIR)/src/melee/ft/ftlib.c.o\
    $(BUILD_DIR)/src/melee/ft/ftwaitanim.c.o\
    $(BUILD_DIR)/src/melee/ft/ft_0877.c.o\
    $(BUILD_DIR)/asm/melee/ft/ft_0877.s.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftCommon/ftCo_Wait.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftCommon/ftCo_08A6.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftCommon/ftCo_Attack1.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftCommon/ftCo_AttackDash.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftCommon/ftCo_AttackS3.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftCommon/ftCo_AttackHi3.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftCommon/ftCo_AttackLw3.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftCommon/ftCo_AttackS4.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftCommon/ftCo_AttackHi4.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftCommon/ftCo_AttackLw4.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftCommon/ftCo_AttackAir.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftCommon/ftCo_LandingAir.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftCommon/ftCo_Damage.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftCommon/ftCo_DamageFall.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftCommon/ftCo_DamageIce.c.o\
    $(BUILD_DIR)/asm/melee/ft/ftCo_DamageIce.s.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftCommon/ftCo_Guard.c.o\
    $(BUILD_DIR)/asm/melee/ft/ftCo_Guard.s.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftCommon/ftCo_ItemGet.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftCommon/ftCo_ItemThrow.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftCommon/ftCo_SpecialS.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftCommon/ftCo_SpecialAir.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftCommon/ftCo_FallSpecial.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftCommon/ftCo_Lift.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftCommon/ftCo_DownBound.c.o\
    $(BUILD_DIR)/asm/melee/ft/ftCo_DownBound.s.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftCommon/ftCo_DownStand.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftCommon/ftCo_Down.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftCommon/ftCo_DownAttack.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftCommon/ftCo_Passive.c.o\
    $(BUILD_DIR)/src/melee/ft/ftdynamics.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftMario/ftMr_Strings.c.o\
    $(BUILD_DIR)/asm/melee/ft/ft_08A4.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/melee/ft/chara/ftDonkey/ftDk_HeavyWait0.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftDonkey/ftDk_HeavyWalk.c.o\
    $(BUILD_DIR)/src/melee/ft/ftwalkcommon.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftDonkey/ftDk_MS_345_0.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftDonkey/ftDk_HeavyTurn.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftDonkey/ftDk_HeavyFall.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftDonkey/ftDk_HeavyJump.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftDonkey/ftDk_HeavyWait1.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftDonkey/ftDk_HeavyLanding.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/melee/ft/chara/ftMario/ftMr_Init.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftMario/ftMr_SpecialN.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftMario/ftMr_SpecialS.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftMario/ftMr_SpecialHi.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftMario/ftMr_SpecialLw.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/melee/ft/chara/ftCaptain/ftCa_Init.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftCaptain/ftCa_SpecialN.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftCaptain/ftCa_SpecialS.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftCaptain/ftCa_SpecialLw.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftCaptain/ftCa_SpecialHi.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/melee/ft/chara/ftFox/ftFx_Init.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftFox/ftFx_AppealS.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftFox/ftFx_SpecialN.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftFox/ftFx_SpecialHi.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftFox/ftFx_SpecialLw.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftFox/ftFx_SpecialS.c.o\


TEXT_O_FILES +=\
    $(BUILD_DIR)/src/melee/ft/chara/ftLink/ftLk_Init.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftLink/ftLk_AttackAir.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftLink/ftLk_SpecialLw.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftLink/ftLk_SpecialHi.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftLink/ftLk_SpecialS.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftLink/ftLk_SpecialN.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/melee/ft/chara/ftKirby/ftKb_Init.c.o\
    $(BUILD_DIR)/asm/melee/ft/chara/ftKb_Init.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/melee/ft/chara/ftDonkey/ftDk_Init.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftDonkey/ftDk_SpecialLw.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftDonkey/ftDk_SpecialS.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftDonkey/ftDk_SpecialN.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftDonkey/ftDk_SpecialHi.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/melee/ft/chara/ftSeak/ftSk_Init.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftSeak/ftSk_SpecialS.c.o\
    $(BUILD_DIR)/asm/melee/ft/chara/ftSeak/ftSk_SpecialN.s.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftSeak/ftSk_SpecialN.c.o\
    $(BUILD_DIR)/asm/melee/ft/chara/ftSeak/ftSk_SpecialHi.s.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftSeak/ftSk_SpecialHi.c.o\
    $(BUILD_DIR)/asm/melee/ft/chara/ftSeak/ftSk_SpecialLw.s.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftSeak/ftSk_SpecialLw.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/melee/ft/chara/ftNess/ftNs_Init.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftNess/ftNs_AttackS4.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftNess/ftNs_AttackHi4.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftNess/ftNs_AttackLw4.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftNess/ftNs_SpecialS.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftNess/ftNs_SpecialN.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftNess/ftNs_SpecialHi.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftNess/ftNs_SpecialLw.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/melee/ft/chara/ftPeach/ftPe_Init.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftPeach/ftPe_Float.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftPeach/ftPe_FloatFall.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftPeach/ftPe_FloatAttack.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftPeach/ftPe_AttackS4.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftPeach/ftPe_SpecialS.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftPeach/ftPe_SpecialLw.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftPeach/ftPe_SpecialHi.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftPeach/ftPe_SpecialN.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/melee/ft/chara/ftPopo/ftPp_Init.c.o\
    $(BUILD_DIR)/asm/melee/ft/chara/ftPp_SpecialS.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/melee/ft/chara/ftNana/ftNn_Init.c.o\
    $(BUILD_DIR)/asm/melee/ft/chara/ftNn_Init.s.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftNana/ftNn_Unk0.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/melee/ft/chara/ftPikachu/ftPk_Init.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftPikachu/ftPk_SpecialN.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftPikachu/ftPk_SpecialS.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftPikachu/ftPk_SpecialHi.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftPikachu/ftPk_SpecialLw.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/melee/ft/chara/ftSamus/ftSs_Init.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftSamus/ftSs_SpecialLw_0.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftSamus/ftSs_SpecialN.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftSamus/ftSs_SpecialS.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftSamus/ftSs_SpecialHi.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftSamus/ftSs_SpecialLw_1.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/melee/ft/chara/ftYoshi/ftYs_Init.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftYoshi/ftYs_Guard.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftYoshi/ftYs_SpecialN.c.o\
    $(BUILD_DIR)/asm/melee/ft/chara/ftYs_SpecialN.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/melee/ft/chara/ftKoopa/ftKp_Init.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftKoopa/ftKp_Unk1.c.o\
    $(BUILD_DIR)/asm/melee/ft/chara/ftKp_SpecialS.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/melee/ft/chara/ftMars/ftMs_Init.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftMars/ftMs_SpecialN.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftMars/ftMs_SpecialS.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftMars/ftMs_SpecialHi.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftMars/ftMs_SpecialLw.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/melee/ft/chara/ftZelda/ftZd_Init.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftZelda/ftZd_SpecialHi.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftZelda/ftZd_SpecialN.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftZelda/ftZd_SpecialLw.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftZelda/ftZd_SpecialS.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/melee/ft/chara/ftPurin/ftPr_Init.c.o\
    $(BUILD_DIR)/asm/melee/ft/chara/ftPr_Init.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/melee/ft/chara/ftLuigi/ftLg_Init.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftLuigi/ftLg_SpecialN.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftLuigi/ftLg_SpecialS.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftLuigi/ftLg_SpecialHi.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftLuigi/ftLg_SpecialLw.c.o\


TEXT_O_FILES +=\
    $(BUILD_DIR)/src/melee/ft/chara/ftMewtwo/ftMt_Init.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftMewtwo/ftMt_SpecialHi.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftMewtwo/ftMt_SpecialLw.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftMewtwo/ftMt_SpecialS.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftMewtwo/ftMt_SpecialN.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/melee/ft/chara/ftCLink/ftCl_Init.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftCLink/ftCl_AppealS.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/melee/ft/chara/ftDrMario/ftDr_Init.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftDrMario/ftDr_AppealS.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/melee/ft/chara/ftFalco/ftFc_Init.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/melee/ft/chara/ftPichu/ftPc_Init.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/melee/ft/chara/ftGameWatch/ftGw_Init.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftGameWatch/ftGw_AttackS4.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftGameWatch/ftGw_AttackLw3.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftGameWatch/ftGw_AttackAir.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftGameWatch/ftGw_Attack11.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftGameWatch/ftGw_Attack100.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftGameWatch/ftGw_SpecialS.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftGameWatch/ftGw_SpecialLw.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftGameWatch/ftGw_SpecialHi.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftGameWatch/ftGw_SpecialN.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/melee/ft/chara/ftGanon/ftGn_Init.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/melee/ft/chara/ftEmblem/ftFe_Init.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/melee/ft/chara/ftZakoBoy/ftBo_Init.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/melee/ft/chara/ftZakoGirl/ftGl_Init.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/melee/ft/chara/ftGigaKoopa/ftGk_Init.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/melee/ft/chara/ftSandbag/ftSb_Init.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMh_Init.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMh_Wait1_0.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMh_Wait1_2.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMh_Entry.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMh_Damage_0.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMh_Sweep.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMh_SweepWait.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMh_Slap.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMh_Walk.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMh_Drill.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMh_RockCrush.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMh_PaperCrush.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMh_Poke.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMh_FingerBeam.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMh_FingerGun.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMh_FingerGun3.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMh_BackAirplane1.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMh_BackAirplane2.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMh_BackAirplane3.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMh_BackCrush_0.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMh_BackCrush_1.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMh_BackDisappear.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMh_Squeeze.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMh_Wait1_1.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMh_Squeezing.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMh_Throw.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMh_Slam.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMh_TagCrush.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMh_TagApplaud.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMh_TagRockPaper.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMh_TagCancel.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMh_CaptureMasterHand.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMh_CaptureDamageMasterHand.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMh_ThrownMasterHand.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/melee/ft/chara/ftCrazyHand/ftCh_Init.c.o\
    $(BUILD_DIR)/src/melee/ft/chara/ftCrazyHand/ftCh_Unk0.c.o\
    $(BUILD_DIR)/asm/melee/ft/chara/ftCh_Init.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/melee/ft/ftbosslib.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/melee/gm/gmmain_lib.c.o\
    $(BUILD_DIR)/asm/melee/gm/gmmain_lib.s.o\
    $(BUILD_DIR)/src/melee/gm/gmmain.c.o\
    $(BUILD_DIR)/asm/melee/gm/gm_1601.s.o\
    $(BUILD_DIR)/asm/melee/gm/gmtitle.s.o\
    $(BUILD_DIR)/asm/melee/gm/gmcamera.s.o\
    $(BUILD_DIR)/asm/melee/gm_1A36.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/melee/gr/ground.c.o\
    $(BUILD_DIR)/asm/melee/gr/ground.s.o\
    $(BUILD_DIR)/asm/melee/gr/grdisplay.s.o\
    $(BUILD_DIR)/src/melee/gr/grdatfiles.c.o\
    $(BUILD_DIR)/asm/melee/gr/granime.s.o\
    $(BUILD_DIR)/asm/melee/gr/grmaterial.s.o\
    $(BUILD_DIR)/src/melee/gr/grlib.c.o\
    $(BUILD_DIR)/src/melee/gr/grdynamicattr.c.o\
    $(BUILD_DIR)/asm/melee/gr/grzakogenerator.s.o\
    $(BUILD_DIR)/asm/melee/gr/grfzerocar.s.o\
    $(BUILD_DIR)/asm/melee/gr/grizumi.s.o\
    $(BUILD_DIR)/asm/melee/gr/grcastle.s.o\
    $(BUILD_DIR)/asm/melee/gr/grstadium.s.o\
    $(BUILD_DIR)/asm/melee/gr/grkongo.s.o\
    $(BUILD_DIR)/asm/melee/gr/grzebes.s.o\
    $(BUILD_DIR)/asm/melee/gr/grcorneria.s.o\
    $(BUILD_DIR)/src/melee/gr/grstory.c.o\
    $(BUILD_DIR)/asm/melee/gr/gronett.s.o\
    $(BUILD_DIR)/asm/melee/gr/grbigblue.s.o\
    $(BUILD_DIR)/asm/melee/gr/grmutecity.s.o\
    $(BUILD_DIR)/asm/melee/gr/grfourside.s.o\
    $(BUILD_DIR)/asm/melee/gr/grgreatbay.s.o\
    $(BUILD_DIR)/asm/melee/gr/gricemt.s.o\
    $(BUILD_DIR)/asm/melee/gr/grinishie1.s.o\
    $(BUILD_DIR)/asm/melee/gr/grinishie2.s.o\
    $(BUILD_DIR)/asm/melee/gr/grkraid.s.o\
    $(BUILD_DIR)/asm/melee/gr/grrcruise.s.o\
    $(BUILD_DIR)/src/melee/gr/grshrine.c.o\
    $(BUILD_DIR)/asm/melee/gr/gryorster.s.o\
    $(BUILD_DIR)/asm/melee/gr/grgarden.s.o\
    $(BUILD_DIR)/asm/melee/gr/grvenom.s.o\
    $(BUILD_DIR)/asm/melee/gr/grtest.s.o\
    $(BUILD_DIR)/asm/melee/gr/grkinokoroute.s.o\
    $(BUILD_DIR)/asm/melee/gr/grshrineroute.s.o\
    $(BUILD_DIR)/asm/melee/gr/grzebesroute.s.o\
    $(BUILD_DIR)/asm/melee/gr/grbigblueroute.s.o\
    $(BUILD_DIR)/src/melee/gr/grfigure1.c.o\
    $(BUILD_DIR)/src/melee/gr/grfigure2.c.o\
    $(BUILD_DIR)/src/melee/gr/grfigure3.c.o\
    $(BUILD_DIR)/asm/melee/gr/groldyoshi.s.o\
    $(BUILD_DIR)/asm/melee/gr/groldkongo.s.o\
    $(BUILD_DIR)/asm/melee/gr/groldpupupu.s.o\
    $(BUILD_DIR)/asm/melee/gr/grpura.s.o\
    $(BUILD_DIR)/asm/melee/gr/grgreens.s.o\
    $(BUILD_DIR)/asm/melee/gr/grflatzone.s.o\
    $(BUILD_DIR)/asm/melee/gr/grpushon.s.o\
    $(BUILD_DIR)/asm/melee/gr/grfigureget.s.o\
    $(BUILD_DIR)/src/melee/gr/grbattle.c.o\
    $(BUILD_DIR)/asm/melee/gr/grlast.s.o\
    $(BUILD_DIR)/asm/melee/gr/grhomerun.s.o\
    $(BUILD_DIR)/asm/melee/gr/grheal.s.o\
    $(BUILD_DIR)/asm/melee/gr/grtmario.s.o\
    $(BUILD_DIR)/src/melee/gr/grtcaptain.c.o\
    $(BUILD_DIR)/asm/melee/gr/grtclink.s.o\
    $(BUILD_DIR)/src/melee/gr/grtdonkey.c.o\
    $(BUILD_DIR)/asm/melee/gr/grtdrmario.s.o\
    $(BUILD_DIR)/src/melee/gr/grtfalco.c.o\
    $(BUILD_DIR)/asm/melee/gr/grtfox.s.o\
    $(BUILD_DIR)/src/melee/gr/grticeclimber.c.o\
    $(BUILD_DIR)/asm/melee/gr/grtkirby.s.o\
    $(BUILD_DIR)/src/melee/gr/grtkoopa.c.o\
    $(BUILD_DIR)/asm/melee/gr/grtlink.s.o\
    $(BUILD_DIR)/src/melee/gr/grtluigi.c.o\
    $(BUILD_DIR)/src/melee/gr/grtmars.c.o\
    $(BUILD_DIR)/asm/melee/gr/grtmewtwo.s.o\
    $(BUILD_DIR)/src/melee/gr/grtness.c.o\
    $(BUILD_DIR)/asm/melee/gr/grtpeach.s.o\
    $(BUILD_DIR)/src/melee/gr/grtpichu.c.o\
    $(BUILD_DIR)/asm/melee/gr/grtpikachu.s.o\
    $(BUILD_DIR)/asm/melee/gr/grtpurin.s.o\
    $(BUILD_DIR)/asm/melee/gr/grtsamus.s.o\
    $(BUILD_DIR)/asm/melee/gr/grtseak.s.o\
    $(BUILD_DIR)/src/melee/gr/grtyoshi.c.o\
    $(BUILD_DIR)/asm/melee/gr/grtzelda.s.o\
    $(BUILD_DIR)/asm/melee/gr/grtgamewatch.s.o\
    $(BUILD_DIR)/asm/melee/gr/grtemblem.s.o\
    $(BUILD_DIR)/asm/melee/gr/grtganon.s.o\
    $(BUILD_DIR)/src/melee/gr/stage.c.o\
    $(BUILD_DIR)/asm/melee/gr/stage.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/asm/melee/db/db_2253.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/asm/melee/mn_2295.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/asm/melee/mn/mnitemsw.s.o\
    $(BUILD_DIR)/asm/melee/mn/mnstagesw.s.o\
    $(BUILD_DIR)/asm/melee/mn/mnname.s.o\
    $(BUILD_DIR)/asm/melee/mn/mnnamenew.s.o\
    $(BUILD_DIR)/asm/melee/mn/mndiagram.s.o\
    $(BUILD_DIR)/asm/melee/mn/mndiagram2.s.o\
    $(BUILD_DIR)/asm/melee/mn/mndiagram3.s.o\
    $(BUILD_DIR)/asm/melee/mn/mnvibration.s.o\
    $(BUILD_DIR)/asm/melee/mn/mnsound.s.o\
    $(BUILD_DIR)/asm/melee/mn/mndeflicker.s.o\
    $(BUILD_DIR)/asm/melee/mn/mnsoundtest.s.o\
    $(BUILD_DIR)/asm/melee/mn/mnlanguage.s.o\
    $(BUILD_DIR)/asm/melee/mn/mnhyaku.s.o\
    $(BUILD_DIR)/asm/melee/mn/mnevent.s.o\
    $(BUILD_DIR)/asm/melee/mn/mndatadel.s.o\
    $(BUILD_DIR)/asm/melee/mn/mncount.s.o\
    $(BUILD_DIR)/asm/melee/mn/mninfo.s.o\
    $(BUILD_DIR)/asm/melee/mn/mninfobonus.s.o\
    $(BUILD_DIR)/asm/melee/mn/mnsnap.s.o\
    $(BUILD_DIR)/asm/melee/mn/mngallery.s.o\
    $(BUILD_DIR)/asm/melee/mn/mnstagesel.s.o\
    $(BUILD_DIR)/src/melee/mn/mncharsel.c.o\
    $(BUILD_DIR)/asm/melee/mn/mncharsel.s.o\
    $(BUILD_DIR)/src/melee/it/item.c.o\
    $(BUILD_DIR)/src/melee/it/it_26B1.c.o\
    $(BUILD_DIR)/asm/melee/it/it_266F.s.o\
    $(BUILD_DIR)/asm/melee/it/it_27CF.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/asm/melee/if/ifall.s.o\
    $(BUILD_DIR)/asm/melee/if/iftime.s.o\
    $(BUILD_DIR)/asm/melee/if/ifstatus_data.s.o\
    $(BUILD_DIR)/src/melee/if/ifstatus.c.o\
    $(BUILD_DIR)/asm/melee/if/if_2F72.s.o\
    $(BUILD_DIR)/asm/melee/if/ifstock.s.o\
    $(BUILD_DIR)/asm/melee/if/ifmagnify.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/asm/melee/un_2FC9.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/Runtime/__va_arg.c.o\
    $(BUILD_DIR)/src/Runtime/global_destructor_chain.c.o\
    $(BUILD_DIR)/src/Runtime/Gecko_ExceptionPPC.c.o\
    $(BUILD_DIR)/src/Runtime/Gecko_setjmp.c.o\
    $(BUILD_DIR)/asm/Runtime/runtime.s.o\
    $(BUILD_DIR)/src/Runtime/__init_cpp_exceptions.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/MSL/abort_exit.c.o\
    $(BUILD_DIR)/asm/MSL/abort_exit.s.o\
    $(BUILD_DIR)/asm/MSL/ansi_fp.s.o\
    $(BUILD_DIR)/src/MSL/buffer_io.c.o\
    $(BUILD_DIR)/src/MSL/PPC_EABI/critical_regions.gamecube.c.o\
    $(BUILD_DIR)/src/MSL/ctype.c.o\
    $(BUILD_DIR)/asm/MSL/direct_io.s.o\
    $(BUILD_DIR)/src/MSL/cstring.c.o\
    $(BUILD_DIR)/asm/MSL/mem_funcs.s.o\
    $(BUILD_DIR)/asm/MSL/printf.s.o\
    $(BUILD_DIR)/src/MSL/rand.c.o\
    $(BUILD_DIR)/src/MSL/string.c.o\
    $(BUILD_DIR)/asm/MSL/strtoul.s.o\
    $(BUILD_DIR)/src/MSL/console_io.c.o\
    $(BUILD_DIR)/src/MSL/wchar_io.c.o\
    $(BUILD_DIR)/src/MSL/math_1.c.o\
    $(BUILD_DIR)/src/MSL/trigf.c.o\
    $(BUILD_DIR)/asm/MSL/math.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/asm/MetroTRK/mainloop.s.o\
    $(BUILD_DIR)/asm/MetroTRK/nubevent.s.o\
    $(BUILD_DIR)/asm/MetroTRK/nubinit.s.o\
    $(BUILD_DIR)/asm/MetroTRK/msg.s.o\
    $(BUILD_DIR)/asm/MetroTRK/msgbuf.s.o\
    $(BUILD_DIR)/asm/MetroTRK/serpoll.s.o\
    $(BUILD_DIR)/asm/MetroTRK/dispatch.s.o\
    $(BUILD_DIR)/asm/MetroTRK/msghndlr.s.o\
    $(BUILD_DIR)/asm/MetroTRK/flush_cache.s.o\
    $(BUILD_DIR)/asm/MetroTRK/mem_TRK.s.o\
    $(BUILD_DIR)/asm/MetroTRK/targimpl.s.o\
    $(BUILD_DIR)/asm/MetroTRK/dolphin_trk.s.o\
    $(BUILD_DIR)/asm/MetroTRK/mpc_7xx_603e.s.o\
    $(BUILD_DIR)/asm/MetroTRK/main_TRK.s.o\
    $(BUILD_DIR)/asm/MetroTRK/dolphin_trk_glue.s.o\
    $(BUILD_DIR)/asm/MetroTRK/targcont.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/dolphin/amcstubs/AmcExi2Stubs.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/asm/dolphin/OdemuExi2/DebuggerDriver.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/asm/dolphin/hio/hio.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/asm/dolphin/mcc/mcc.s.o\
    $(BUILD_DIR)/asm/dolphin/mcc/fio.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/asm/dolphin/thp/THPDec.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/asm/dolphin/jpeg/jpegdec.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/dolphin/base/PPCArch.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/dolphin/db/db.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/dolphin/dsp/dsp.c.o\
    $(BUILD_DIR)/src/dolphin/dsp/dsp_debug.c.o\
    $(BUILD_DIR)/src/dolphin/dsp/dsp_task.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/asm/dolphin/dvd/dvdlow.s.o\
    $(BUILD_DIR)/asm/dolphin/dvd/dvdfs.s.o\
    $(BUILD_DIR)/src/dolphin/dvd/dvd.c.o\
    $(BUILD_DIR)/asm/dolphin/dvd/dvd.s.o\
    $(BUILD_DIR)/src/dolphin/dvd/dvdqueue.c.o\
    $(BUILD_DIR)/asm/dolphin/dvd/dvderror.s.o\
    $(BUILD_DIR)/src/dolphin/dvd/fstload.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/dolphin/gx/GXInit.c.o\
    $(BUILD_DIR)/src/dolphin/gx/GXFifo.c.o\
    $(BUILD_DIR)/src/dolphin/gx/GXAttr.c.o\
    $(BUILD_DIR)/src/dolphin/gx/GXMisc.c.o\
    $(BUILD_DIR)/src/dolphin/gx/GXGeometry.c.o\
    $(BUILD_DIR)/src/dolphin/gx/GXFrameBuf.c.o\
    $(BUILD_DIR)/src/dolphin/gx/GXLight.c.o\
    $(BUILD_DIR)/src/dolphin/gx/GXTexture.c.o\
    $(BUILD_DIR)/src/dolphin/gx/GXBump.c.o\
    $(BUILD_DIR)/src/dolphin/gx/GXTev.c.o\
    $(BUILD_DIR)/src/dolphin/gx/GXPixel.c.o\
    $(BUILD_DIR)/src/dolphin/gx/GXStubs.c.o\
    $(BUILD_DIR)/src/dolphin/gx/GXDisplayList.c.o\
    $(BUILD_DIR)/src/dolphin/gx/GXTransform.c.o\
    $(BUILD_DIR)/src/dolphin/gx/GXPerf.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/asm/dolphin/mtx/mtx.s.o\
    $(BUILD_DIR)/asm/dolphin/mtx/mtxvec.s.o\
    $(BUILD_DIR)/src/dolphin/mtx/mtx44.c.o\
    $(BUILD_DIR)/asm/dolphin/mtx/vec.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/dolphin/os/OSInit.c.o\
    $(BUILD_DIR)/src/dolphin/os/OSAlarm.c.o\
    $(BUILD_DIR)/src/dolphin/os/OSAlloc.c.o\
    $(BUILD_DIR)/src/dolphin/os/OSArena.c.o\
    $(BUILD_DIR)/src/dolphin/os/OSAudioSystem.c.o\
    $(BUILD_DIR)/src/dolphin/os/OSCache.c.o\
    $(BUILD_DIR)/src/dolphin/os/OSContext.c.o\
    $(BUILD_DIR)/src/dolphin/os/OSError.c.o\
    $(BUILD_DIR)/src/dolphin/os/OSExi.c.o\
    $(BUILD_DIR)/src/dolphin/os/OSFont.c.o\
    $(BUILD_DIR)/src/dolphin/os/OSInterrupt.c.o\
    $(BUILD_DIR)/src/dolphin/os/OSLink.c.o\
    $(BUILD_DIR)/src/dolphin/os/OSMemory.c.o\
    $(BUILD_DIR)/src/dolphin/os/OSMutex.c.o\
    $(BUILD_DIR)/src/dolphin/os/OSReboot.c.o\
    $(BUILD_DIR)/src/dolphin/os/OSReset.c.o\
    $(BUILD_DIR)/src/dolphin/os/OSResetSW.c.o\
    $(BUILD_DIR)/src/dolphin/os/OSRtc.c.o\
    $(BUILD_DIR)/src/dolphin/os/OSSerial.c.o\
    $(BUILD_DIR)/asm/dolphin/os/OSSerial_data.s.o\
    $(BUILD_DIR)/src/dolphin/os/OSSync.c.o\
    $(BUILD_DIR)/src/dolphin/os/OSThread.c.o\
    $(BUILD_DIR)/asm/dolphin/os/OSThread_data.s.o\
    $(BUILD_DIR)/src/dolphin/os/OSTime.c.o\
    $(BUILD_DIR)/src/dolphin/os/OSUartExi.c.o\
    $(BUILD_DIR)/asm/dolphin/os/init/__ppc_eabi_init_data.s.o\
    $(BUILD_DIR)/src/dolphin/os/init/__ppc_eabi_init.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/dolphin/pad/PadClamp.c.o\
    $(BUILD_DIR)/src/dolphin/pad/Pad.c.o\
    $(BUILD_DIR)/asm/dolphin/pad/Pad.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/asm/dolphin/vi/vi.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/dolphin/ai/ai.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/dolphin/ar/ar.c.o\
    $(BUILD_DIR)/asm/dolphin/ar/ar.s.o\
    $(BUILD_DIR)/src/dolphin/ar/arq.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/dolphin/card/CARDBios.c.o\
    $(BUILD_DIR)/src/dolphin/card/CARDUnlock.c.o\
    $(BUILD_DIR)/src/dolphin/card/CARDRdwr.c.o\
    $(BUILD_DIR)/src/dolphin/card/CARDBlock.c.o\
    $(BUILD_DIR)/src/dolphin/card/CARDDir.c.o\
    $(BUILD_DIR)/src/dolphin/card/CARDCheck.c.o\
    $(BUILD_DIR)/src/dolphin/card/CARDMount.c.o\
    $(BUILD_DIR)/src/dolphin/card/CARDFormat.c.o\
    $(BUILD_DIR)/src/dolphin/card/CARDOpen.c.o\
    $(BUILD_DIR)/src/dolphin/card/CARDCreate.c.o\
    $(BUILD_DIR)/src/dolphin/card/CARDRead.c.o\
    $(BUILD_DIR)/src/dolphin/card/CARDWrite.c.o\
    $(BUILD_DIR)/src/dolphin/card/CARDDelete.c.o\
    $(BUILD_DIR)/src/dolphin/card/CARDStat.c.o\
    $(BUILD_DIR)/src/dolphin/card/CARDRename.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/dolphin/ax/AX.c.o\
    $(BUILD_DIR)/asm/dolphin/ax/AXAlloc.s.o\
    $(BUILD_DIR)/asm/dolphin/ax/AXAux.s.o\
    $(BUILD_DIR)/asm/dolphin/ax/AXCL.s.o\
    $(BUILD_DIR)/asm/dolphin/ax/AXOut.s.o\
    $(BUILD_DIR)/asm/dolphin/ax/AXSPB.s.o\
    $(BUILD_DIR)/asm/dolphin/ax/AXVPB.s.o\
    $(BUILD_DIR)/asm/dolphin/ax/AXProf.s.o\
    $(BUILD_DIR)/asm/dolphin/ax/DSPCode.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/asm/dolphin/axfx/reverb_hi.s.o\
    $(BUILD_DIR)/asm/dolphin/axfx/reverb_std.s.o\
    $(BUILD_DIR)/asm/dolphin/axfx/chorus.s.o\
    $(BUILD_DIR)/asm/dolphin/axfx/delay.s.o\
    $(BUILD_DIR)/src/dolphin/axfx/axfx.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/sysdolphin/baselib/dobj.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/sysdolphin/baselib/tobj.c.o\
    $(BUILD_DIR)/asm/sysdolphin/baselib/tobj.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/asm/sysdolphin/baselib/state.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/sysdolphin/baselib/tev.c.o\
    $(BUILD_DIR)/asm/sysdolphin/baselib/tev.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/sysdolphin/baselib/mobj.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/sysdolphin/baselib/aobj.c.o\
    $(BUILD_DIR)/asm/sysdolphin/baselib/aobj.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/sysdolphin/baselib/lobj.c.o\
    $(BUILD_DIR)/asm/sysdolphin/baselib/lobj.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/sysdolphin/baselib/cobj.c.o\
    $(BUILD_DIR)/asm/sysdolphin/baselib/cobj.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/sysdolphin/baselib/fobj.c.o\
    $(BUILD_DIR)/asm/sysdolphin/baselib/fobj.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/sysdolphin/baselib/pobj.c.o\
    $(BUILD_DIR)/asm/sysdolphin/baselib/pobj.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/sysdolphin/baselib/jobj.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/sysdolphin/baselib/displayfunc.c.o\
    $(BUILD_DIR)/asm/sysdolphin/baselib/displayfunc.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/sysdolphin/baselib/initialize.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/asm/sysdolphin/baselib/video.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/sysdolphin/baselib/controller.c.o\
    $(BUILD_DIR)/asm/sysdolphin/baselib/controller.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/sysdolphin/baselib/rumble.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/asm/sysdolphin/baselib/spline.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/sysdolphin/baselib/mtx.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/sysdolphin/baselib/util.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/sysdolphin/baselib/objalloc.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/sysdolphin/baselib/robj.c.o\
    $(BUILD_DIR)/asm/sysdolphin/baselib/robj.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/sysdolphin/baselib/id.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/sysdolphin/baselib/wobj.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/sysdolphin/baselib/fog.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/sysdolphin/baselib/perf.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/sysdolphin/baselib/list.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/sysdolphin/baselib/object.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/asm/sysdolphin/baselib/quatlib.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/sysdolphin/baselib/memory.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/sysdolphin/baselib/shadow.c.o\
    $(BUILD_DIR)/asm/sysdolphin/baselib/shadow.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/sysdolphin/baselib/archive.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/sysdolphin/baselib/random.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/asm/sysdolphin/baselib/bytecode.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/sysdolphin/baselib/class.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/asm/sysdolphin/baselib/hash.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/sysdolphin/baselib/texp.c.o\
    $(BUILD_DIR)/asm/sysdolphin/baselib/texp.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/asm/sysdolphin/baselib/texpdag.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/asm/sysdolphin/baselib/leak.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/sysdolphin/baselib/debug.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/asm/sysdolphin/baselib/synth.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/asm/sysdolphin/baselib/AXDriver.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/asm/sysdolphin/baselib/devcom.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/asm/sysdolphin/baselib/gobjproc.s.o\
    $(BUILD_DIR)/src/sysdolphin/baselib/gobjproc.c.o\
    $(BUILD_DIR)/src/sysdolphin/baselib/gobjplink.c.o\
    $(BUILD_DIR)/src/sysdolphin/baselib/gobjgxlink.c.o\
    $(BUILD_DIR)/src/sysdolphin/baselib/gobjobject.c.o\
    $(BUILD_DIR)/src/sysdolphin/baselib/gobjuserdata.c.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/sysdolphin/baselib/gobj.c.o\
    $(BUILD_DIR)/asm/sysdolphin/baselib/gobj.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/asm/sysdolphin/baselib/baselib_shared_data_003.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/asm/sysdolphin/baselib/baselib_unknown_009.s.o\
    $(BUILD_DIR)/asm/sysdolphin/baselib/baselib_unknown_010.s.o\
    $(BUILD_DIR)/asm/sysdolphin/baselib/baselib_unknown_011.s.o\
    $(BUILD_DIR)/asm/sysdolphin/baselib/baselib_unknown_002.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/sysdolphin/baselib/psdisp.c.o\
    $(BUILD_DIR)/asm/sysdolphin/baselib/psdisp.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/sysdolphin/baselib/psdisptev.c.o\
    $(BUILD_DIR)/asm/sysdolphin/baselib/psdisptev.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/sysdolphin/baselib/psappsrt.c.o\
    $(BUILD_DIR)/asm/sysdolphin/baselib/psappsrt.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/src/sysdolphin/baselib/sobjlib.c.o\
    $(BUILD_DIR)/asm/sysdolphin/baselib/sobjlib.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/asm/sysdolphin/baselib/sislib.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/asm/sysdolphin/baselib/baselib_shared_data_001.s.o\
    $(BUILD_DIR)/asm/sysdolphin/baselib/baselib_shared_data_002.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/asm/sysdolphin/baselib/hsd_40FF.s.o\

TEXT_O_FILES +=\
    $(BUILD_DIR)/asm/sysdolphin/baselib/hsd_3A94.s.o\
    $(BUILD_DIR)/asm/sysdolphin/baselib/hsd_3AA7.s.o\
    $(BUILD_DIR)/asm/sysdolphin/baselib/hsd_3B27.s.o\
    $(BUILD_DIR)/asm/sysdolphin/baselib/hsd_3B2B.s.o\
    $(BUILD_DIR)/asm/sysdolphin/baselib/hsd_3B2E.s.o\
    $(BUILD_DIR)/src/sysdolphin/baselib/hsd_3B33.c.o\
    $(BUILD_DIR)/asm/sysdolphin/baselib/hsd_3B34.s.o\
