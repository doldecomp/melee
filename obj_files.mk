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
	$(BUILD_DIR)/asm/melee/lb/lbcollision.s.o\
	$(BUILD_DIR)/src/melee/lb/lblanguage.c.o\
	$(BUILD_DIR)/src/melee/lb/lbtime.c.o\
	$(BUILD_DIR)/src/melee/lb/lbunknown_001.c.o\
	$(BUILD_DIR)/asm/melee/lb/lbunknown_002.s.o\
	$(BUILD_DIR)/src/melee/lb/lbvector.c.o\
	$(BUILD_DIR)/asm/melee/lb/lbshadow.s.o\
	$(BUILD_DIR)/asm/melee/lb/lbunknown_003.s.o\
	$(BUILD_DIR)/asm/melee/lb/lbarq.s.o\
	$(BUILD_DIR)/asm/melee/lb/lbmemory.s.o\
	$(BUILD_DIR)/asm/melee/lb/lbheap.s.o\
	$(BUILD_DIR)/src/melee/lb/lbfile.c.o\
	$(BUILD_DIR)/asm/melee/lb/lbfile.s.o\
	$(BUILD_DIR)/src/melee/lb/lbarchive.c.o\
	$(BUILD_DIR)/asm/melee/lb/lbarchive.s.o\
	$(BUILD_DIR)/asm/melee/lb/lbdvd.s.o\
	$(BUILD_DIR)/asm/melee/lb/lbunknown_004.s.o\
	$(BUILD_DIR)/asm/melee/lb/lbunknown_005.s.o\
	$(BUILD_DIR)/asm/melee/lb/lbsnap.s.o\
	$(BUILD_DIR)/asm/melee/lb/lbgx.s.o\
	$(BUILD_DIR)/asm/melee/lb/lbanim.s.o\
	$(BUILD_DIR)/asm/melee/lb/lbmthp.s.o\
	$(BUILD_DIR)/asm/melee/lb/lbjpeg.s.o\
	$(BUILD_DIR)/asm/melee/lb/lbbgflash.s.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/asm/melee/lb/lbrefract_shared_data.s.o\
	$(BUILD_DIR)/asm/melee/lb/lbrefract_001.s.o\
	$(BUILD_DIR)/asm/melee/lb/lbrefract_002.s.o\
	$(BUILD_DIR)/asm/melee/lb/lbrefract_003_data.s.o\
	$(BUILD_DIR)/src/melee/lb/lbrefract_003.c.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/asm/melee/lb/lbaudio_ax.s.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/asm/melee/cm/camera.s.o\
	$(BUILD_DIR)/src/melee/cm/cmsnap.c.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/src/melee/pl/player.c.o\
	$(BUILD_DIR)/asm/melee/pl/pl_unknown_001.s.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/src/melee/mp/mpcoll.c.o\
	$(BUILD_DIR)/asm/melee/mp/mpcoll.s.o\
	$(BUILD_DIR)/asm/melee/mp/mplib.s.o\
	$(BUILD_DIR)/asm/melee/mp/mpisland.s.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/asm/melee/ef/eflib.s.o\
	$(BUILD_DIR)/asm/melee/ef/efsync.s.o\
	$(BUILD_DIR)/asm/melee/ef/code_80061D70.s.o\
	$(BUILD_DIR)/asm/melee/ef/efasync.s.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/src/melee/ft/fighter.c.o\
	$(BUILD_DIR)/asm/melee/ft/ftanim.s.o\
	$(BUILD_DIR)/asm/melee/ft/ftaction.s.o\
	$(BUILD_DIR)/asm/melee/ft/ftparts.s.o\
	$(BUILD_DIR)/src/melee/ft/ftcamera.c.o\
	$(BUILD_DIR)/asm/melee/ft/ftcoll.s.o\
	$(BUILD_DIR)/src/melee/ft/code_8007C114.c.o\
	$(BUILD_DIR)/src/melee/ft/code_8007C630.c.o\
	$(BUILD_DIR)/src/melee/ft/ftcommon.c.o\
	$(BUILD_DIR)/src/melee/ft/ftdrawcommon.c.o\
	$(BUILD_DIR)/asm/melee/ft/ftdrawcommon_data.s.o\
	$(BUILD_DIR)/src/melee/ft/ftcliffcommon.c.o\
	$(BUILD_DIR)/src/melee/ft/ftwalljump.c.o\
	$(BUILD_DIR)/src/melee/ft/code_80081938.c.o\
	$(BUILD_DIR)/src/melee/ft/code_80081B38.c.o\
	$(BUILD_DIR)/asm/melee/ft/ft_unknown_005.s.o\
	$(BUILD_DIR)/asm/melee/ft/ftdata.s.o\
	$(BUILD_DIR)/src/melee/ft/ftlib.c.o\
	$(BUILD_DIR)/src/melee/ft/ft_unknown_006.c.o\
	$(BUILD_DIR)/asm/melee/ft/ft_unknown_006.s.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/src/melee/ft/chara/ftDonkey/ftdonkey1.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftDonkey/ftdonkey_walk.c.o\
	$(BUILD_DIR)/src/melee/ft/ftwalkcommon.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftDonkey/ftdonkey4.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftDonkey/ftdonkey5.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftDonkey/ftdonkey6.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftDonkey/ftdonkey7.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftDonkey/ftdonkey8.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftDonkey/ftdonkey9.c.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/src/melee/ft/chara/ftMario/ftmario.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftMario/ftMario_SpecialN.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftMario/ftMario_SpecialS.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftMario/ftMario_SpecialHi.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftMario/ftMario_SpecialLw.c.o\
	$(BUILD_DIR)/asm/melee/ft/chara/ftmario.s.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/src/melee/ft/chara/ftCaptain/ftCaptain.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftCaptain/ftCaptain_SpecialN.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftCaptain/ftCaptain_SpecialS.c.o\
	$(BUILD_DIR)/asm/melee/ft/chara/ftCaptain/ftfalcon_3.s.o\
	$(BUILD_DIR)/asm/melee/ft/chara/ftCaptain/ftfalcon_4.s.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/asm/melee/ft/chara/ftfox.s.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftFox/ftfox.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftFox/ftFox_AppealS.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftFox/ftFox_SpecialN.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftFox/ftFox_SpecialHi.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftFox/ftFox_SpecialLw.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftFox/ftFox_SpecialS.c.o\


TEXT_O_FILES +=\
	$(BUILD_DIR)/src/melee/ft/chara/ftLink/ftlink.c.o\
	$(BUILD_DIR)/asm/melee/ft/chara/ftlink.s.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/src/melee/ft/chara/ftKirby/ftkirby.c.o\
	$(BUILD_DIR)/asm/melee/ft/chara/ftkirby.s.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/src/melee/ft/chara/ftDonkey/ftdonkey_callbacks.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftDonkey/ftdonkey_SpecialLw.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftDonkey/ftdonkey_SpecialS.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftDonkey/ftdonkey_SpecialN.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftDonkey/ftdonkey_SpecialHi.c.o\
	$(BUILD_DIR)/asm/melee/ft/chara/ftdonkey_2.s.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/src/melee/ft/chara/ftSeak/ftseak.c.o\
	$(BUILD_DIR)/asm/melee/ft/chara/ftseak.s.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/src/melee/ft/chara/ftNess/ftNess.c.o\
	$(BUILD_DIR)/asm/melee/ft/chara/ftNess/ftNess_data.s.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftNess/ftNess_AttackS4.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftNess/ftNess_AttackHi4.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftNess/ftNess_AttackLw4.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftNess/ftNess_SpecialS.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftNess/ftNess_SpecialN.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftNess/ftNess_SpecialHi.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftNess/ftNess_SpecialLw.c.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/src/melee/ft/chara/ftPeach/ftpeach.c.o\
	$(BUILD_DIR)/asm/melee/ft/chara/ftpeach.s.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/src/melee/ft/chara/ftIceClimber/fticeclimber1.c.o\
	$(BUILD_DIR)/asm/melee/ft/chara/fticeclimber.s.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftIceClimber/fticeclimber2_nana.c.o\
	$(BUILD_DIR)/asm/melee/ft/chara/fticeclimber2_nana.s.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/src/melee/ft/chara/ftPikachu/ftpikachu1.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftPikachu/ftpikachu2.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftPikachu/ftpikachu3.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftPikachu/ftpikachu4.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftPikachu/ftpikachu5.c.o\
	$(BUILD_DIR)/asm/melee/ft/chara/ftpikachu.s.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/src/melee/ft/chara/ftSamus/ftsamus1.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftSamus/ftsamus2.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftSamus/ftsamus3.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftSamus/ftsamus4.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftSamus/ftsamus5.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftSamus/ftsamus6.c.o\
	$(BUILD_DIR)/asm/melee/ft/chara/ftsamus.s.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/src/melee/ft/chara/ftYoshi/ftyoshi.c.o\
	$(BUILD_DIR)/asm/melee/ft/chara/ftyoshi.s.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/src/melee/ft/chara/ftKoopa/ftkoopa.c.o\
	$(BUILD_DIR)/asm/melee/ft/chara/ftkoopa.s.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/src/melee/ft/chara/ftMars/ftMars.c.o\
	$(BUILD_DIR)/asm/melee/ft/chara/ftmars.s.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftMars/ftMarsSpecialN.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftMars/ftMarsSpecialS.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftMars/ftMarsSpecialHi.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftMars/ftMarsSpecialLw.c.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/src/melee/ft/chara/ftZelda/ftzelda1.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftZelda/ftzelda2.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftZelda/ftzelda3.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftZelda/ftzelda4.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftZelda/ftzelda5.c.o\
	$(BUILD_DIR)/asm/melee/ft/chara/ftzelda.s.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/src/melee/ft/chara/ftPurin/ftpurin.c.o\
	$(BUILD_DIR)/asm/melee/ft/chara/ftpurin.s.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/src/melee/ft/chara/ftLuigi/ftluigi.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftLuigi/ftLuigi_SpecialN.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftLuigi/ftLuigi_SpecialS.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftLuigi/ftLuigi_SpecialHi.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftLuigi/ftLuigi_SpecialLw.c.o\
	$(BUILD_DIR)/asm/melee/ft/chara/ftluigi.s.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/asm/melee/ft/chara/ftmewtwo.s.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftMewtwo/ftmewtwo.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftMewtwo/ftMewtwo_SpecialHi.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftMewtwo/ftMewtwo_SpecialLw.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftMewtwo/ftMewtwo_SpecialS.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftMewtwo/ftMewtwo_SpecialN.c.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/src/melee/ft/chara/ftCLink/ftclink.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftCLink/ftclink_2.c.o\
	$(BUILD_DIR)/asm/melee/ft/chara/ftclink.s.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/src/melee/ft/chara/ftDrMario/ftdrmario.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftDrMario/ftdrmario_2.c.o\
	$(BUILD_DIR)/asm/melee/ft/chara/ftdrmario.s.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/src/melee/ft/chara/ftFalco/ftfalco.c.o\
	$(BUILD_DIR)/asm/melee/ft/chara/ftfalco.s.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/src/melee/ft/chara/ftPichu/ftpichu.c.o\
	$(BUILD_DIR)/asm/melee/ft/chara/ftpichu.s.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/src/melee/ft/chara/ftGameWatch/ftgamewatch.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftGameWatch/ftGameWatch_AttackS4.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftGameWatch/ftGameWatch_AttackLw3.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftGameWatch/ftGameWatch_AttackAir.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftGameWatch/ftGameWatch_Attack11.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftGameWatch/ftGameWatch_Attack100.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftGameWatch/ftGameWatch_SpecialS.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftGameWatch/ftGameWatch_SpecialLw.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftGameWatch/ftGameWatch_SpecialHi.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftGameWatch/ftGameWatch_SpecialN.c.o\
	$(BUILD_DIR)/asm/melee/ft/chara/ftgamewatch.s.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/src/melee/ft/chara/ftGanon/ftganon.c.o\
	$(BUILD_DIR)/asm/melee/ft/chara/ftganon.s.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/src/melee/ft/chara/ftEmblem/ftemblem.c.o\
	$(BUILD_DIR)/asm/melee/ft/chara/ftemblem.s.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/src/melee/ft/chara/ftZakoBoy/ftzakoboy.c.o\
	$(BUILD_DIR)/asm/melee/ft/chara/ftzakoboy.s.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/src/melee/ft/chara/ftZakoGirl/ftzakogirl.c.o\
	$(BUILD_DIR)/asm/melee/ft/chara/ftzakogirl.s.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/src/melee/ft/chara/ftGigaKoopa/ftgigakoopa.c.o\
	$(BUILD_DIR)/asm/melee/ft/chara/ftgigakoopa.s.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/src/melee/ft/chara/ftSandbag/ftsandbag.c.o\
	$(BUILD_DIR)/asm/melee/ft/chara/ftsandbag.s.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/asm/melee/ft/chara/ftmasterhand.s.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMasterHand_1.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMasterHand_2.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMasterHand_3.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMasterHand_4.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMasterHand_5.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMasterHand_6.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMasterHand_7.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMasterHand_8.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMasterHand_9.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMasterHand_10.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMasterHand_11.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMasterHand_12.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMasterHand_13.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMasterHand_14.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMasterHand_15.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMasterHand_16.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMasterHand_17.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMasterHand_18.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMasterHand_19.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMasterHand_20.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMasterHand_21.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMasterHand_22.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMasterHand_23.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMasterHand_24.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMasterHand_25.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMasterHand_26.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMasterHand_27.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMasterHand_28.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMasterHand_29.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMasterHand_30.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMasterHand_31.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMasterHand_32.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMasterHand_33.c.o\
	$(BUILD_DIR)/src/melee/ft/chara/ftMasterHand/ftMasterHand_34.c.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/src/melee/ft/chara/ftCrazyHand/ftcrazyhand.c.o\
	$(BUILD_DIR)/asm/melee/ft/chara/ftcrazyhand.s.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/src/melee/ft/ftbosslib.c.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/src/melee/gm/gmmain_lib.c.o\
	$(BUILD_DIR)/asm/melee/gm/gmmain_lib.s.o\
	$(BUILD_DIR)/src/melee/gm/gmmain.c.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/asm/melee/gm/code_801601C4.s.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/asm/melee/gm/gmtitle.s.o\
	$(BUILD_DIR)/asm/melee/gm/gmcamera.s.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/asm/melee/text_2.s.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/src/melee/gr/ground.c.o\
	$(BUILD_DIR)/asm/melee/gr/ground.s.o\
	$(BUILD_DIR)/asm/melee/gr/grdisplay.s.o\
	$(BUILD_DIR)/src/melee/gr/grdatfiles.c.o\
	$(BUILD_DIR)/asm/melee/gr/granime.s.o\
	$(BUILD_DIR)/asm/melee/gr/grmaterial.s.o\
	$(BUILD_DIR)/src/melee/gr/grlib.c.o\
	$(BUILD_DIR)/asm/melee/gr/grdynamicattr.s.o\
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
	$(BUILD_DIR)/asm/melee/gr/grfigure1.s.o\
	$(BUILD_DIR)/asm/melee/gr/grfigure2.s.o\
	$(BUILD_DIR)/asm/melee/gr/grfigure3.s.o\
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
	$(BUILD_DIR)/asm/melee/gr/grtfalcon.s.o\
	$(BUILD_DIR)/asm/melee/gr/grtclink.s.o\
	$(BUILD_DIR)/asm/melee/gr/grtdonkey.s.o\
	$(BUILD_DIR)/asm/melee/gr/grtdrmario.s.o\
	$(BUILD_DIR)/asm/melee/gr/grtfalco.s.o\
	$(BUILD_DIR)/asm/melee/gr/grtfox.s.o\
	$(BUILD_DIR)/asm/melee/gr/grticeclimber.s.o\
	$(BUILD_DIR)/asm/melee/gr/grtkirby.s.o\
	$(BUILD_DIR)/asm/melee/gr/grtkoopa.s.o\
	$(BUILD_DIR)/asm/melee/gr/grtlink.s.o\
	$(BUILD_DIR)/asm/melee/gr/grtluigi.s.o\
	$(BUILD_DIR)/src/melee/gr/grtmars.c.o\
	$(BUILD_DIR)/asm/melee/gr/grtmewtwo.s.o\
	$(BUILD_DIR)/src/melee/gr/grtness.c.o\
	$(BUILD_DIR)/asm/melee/gr/grtpeach.s.o\
	$(BUILD_DIR)/asm/melee/gr/grtpichu.s.o\
	$(BUILD_DIR)/asm/melee/gr/grtpikachu.s.o\
	$(BUILD_DIR)/asm/melee/gr/grtpurin.s.o\
	$(BUILD_DIR)/asm/melee/gr/grtsamus.s.o\
	$(BUILD_DIR)/asm/melee/gr/grtseak.s.o\
	$(BUILD_DIR)/asm/melee/gr/grtyoshi.s.o\
	$(BUILD_DIR)/asm/melee/gr/grtzelda.s.o\
	$(BUILD_DIR)/asm/melee/gr/grtgamewatch.s.o\
	$(BUILD_DIR)/asm/melee/gr/grtemblem.s.o\
	$(BUILD_DIR)/asm/melee/gr/grtganon.s.o\
	$(BUILD_DIR)/src/melee/gr/stage.c.o\
	$(BUILD_DIR)/asm/melee/gr/stage.s.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/asm/melee/db/db_unknown_001.s.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/asm/melee/text_3.s.o\

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
	$(BUILD_DIR)/src/melee/it/item2.c.o\
	$(BUILD_DIR)/asm/melee/it/code_80266F3C.s.o\
	$(BUILD_DIR)/asm/melee/it/code_8027CF30.s.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/asm/melee/if/ifall.s.o\
	$(BUILD_DIR)/asm/melee/if/iftime.s.o\
	$(BUILD_DIR)/asm/melee/if/ifstatus_data.s.o\
	$(BUILD_DIR)/src/melee/if/ifstatus.c.o\
	$(BUILD_DIR)/asm/melee/if/if_unknown_001.s.o\
	$(BUILD_DIR)/asm/melee/if/ifstock.s.o\
	$(BUILD_DIR)/asm/melee/if/ifmagnify.s.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/asm/melee/text_4.s.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/src/Runtime/__va_arg.c.o\
	$(BUILD_DIR)/asm/Runtime/NMWException.s.o\
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
	$(BUILD_DIR)/asm/dolphin/dsp/dsp.s.o\
	$(BUILD_DIR)/src/dolphin/dsp/dsp_debug.c.o\
	$(BUILD_DIR)/asm/dolphin/dsp/dsp_task.s.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/asm/dolphin/dvd/dvdlow.s.o\
	$(BUILD_DIR)/asm/dolphin/dvd/dvdfs.s.o\
	$(BUILD_DIR)/asm/dolphin/dvd/dvd.s.o\
	$(BUILD_DIR)/src/dolphin/dvd/dvdqueue.c.o\
	$(BUILD_DIR)/asm/dolphin/dvd/dvderror.s.o\
	$(BUILD_DIR)/src/dolphin/dvd/fstload.c.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/asm/dolphin/gx/GXInit.s.o\
	$(BUILD_DIR)/src/dolphin/gx/GXFifo.c.o\
	$(BUILD_DIR)/asm/dolphin/gx/GXAttr.s.o\
	$(BUILD_DIR)/src/dolphin/gx/GXMisc.c.o\
	$(BUILD_DIR)/src/dolphin/gx/GXGeometry.c.o\
	$(BUILD_DIR)/asm/dolphin/gx/GXFrameBuf.s.o\
	$(BUILD_DIR)/src/dolphin/gx/GXLight.c.o\
	$(BUILD_DIR)/asm/dolphin/gx/GXTexture.s.o\
	$(BUILD_DIR)/asm/dolphin/gx/GXBump.s.o\
	$(BUILD_DIR)/src/dolphin/gx/GXTev.c.o\
	$(BUILD_DIR)/asm/dolphin/gx/GXPixel.s.o\
	$(BUILD_DIR)/asm/dolphin/gx/GXStubs.s.o\
	$(BUILD_DIR)/src/dolphin/gx/GXDisplayList.c.o\
	$(BUILD_DIR)/asm/dolphin/gx/GXTransform.s.o\
	$(BUILD_DIR)/asm/dolphin/gx/GXPerf.s.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/asm/dolphin/mtx/mtx.s.o\
	$(BUILD_DIR)/asm/dolphin/mtx/mtxvec.s.o\
	$(BUILD_DIR)/src/dolphin/mtx/mtx44.c.o\
	$(BUILD_DIR)/asm/dolphin/mtx/vec.s.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/asm/dolphin/os/OS.s.o\
	$(BUILD_DIR)/asm/dolphin/os/OSAlarm.s.o\
	$(BUILD_DIR)/src/dolphin/os/OSAlloc.c.o\
	$(BUILD_DIR)/src/dolphin/os/OSArena.c.o\
	$(BUILD_DIR)/src/dolphin/os/OSAudioSystem.c.o\
	$(BUILD_DIR)/asm/dolphin/os/OSCache.s.o\
	$(BUILD_DIR)/asm/dolphin/os/OSContext.s.o\
	$(BUILD_DIR)/src/dolphin/os/OSError.c.o\
	$(BUILD_DIR)/asm/dolphin/os/OSError.s.o\
	$(BUILD_DIR)/asm/dolphin/os/OSExi.s.o\
	$(BUILD_DIR)/asm/dolphin/os/OSFont.s.o\
	$(BUILD_DIR)/asm/dolphin/os/OSInterrupt.s.o\
	$(BUILD_DIR)/src/dolphin/os/OSLink.c.o\
	$(BUILD_DIR)/src/dolphin/os/OSMemory.c.o\
	$(BUILD_DIR)/asm/dolphin/os/OSMemory.s.o\
	$(BUILD_DIR)/src/dolphin/os/OSMutex.c.o\
	$(BUILD_DIR)/asm/dolphin/os/OSReboot.s.o\
	$(BUILD_DIR)/asm/dolphin/os/OSReset.s.o\
	$(BUILD_DIR)/asm/dolphin/os/OSResetSW.s.o\
	$(BUILD_DIR)/asm/dolphin/os/OSRtc.s.o\
	$(BUILD_DIR)/asm/dolphin/os/OSSerial.s.o\
	$(BUILD_DIR)/src/dolphin/os/OSSync.c.o\
	$(BUILD_DIR)/asm/dolphin/os/OSThread.s.o\
	$(BUILD_DIR)/asm/dolphin/os/OSTime.s.o\
	$(BUILD_DIR)/asm/dolphin/os/OSUartExi.s.o\
	$(BUILD_DIR)/asm/dolphin/os/init/__ppc_eabi_init.s.o\
	$(BUILD_DIR)/src/dolphin/os/init/__ppc_eabi_init.c.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/asm/dolphin/pad/Padclamp.s.o\
	$(BUILD_DIR)/asm/dolphin/pad/Pad.s.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/asm/dolphin/vi/vi.s.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/asm/dolphin/ai/ai.s.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/asm/dolphin/ar/ar.s.o\
	$(BUILD_DIR)/asm/dolphin/ar/arq.s.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/asm/dolphin/card/CARDBios.s.o\
	$(BUILD_DIR)/asm/dolphin/card/CARDUnlock.s.o\
	$(BUILD_DIR)/asm/dolphin/card/CARDRdrw.s.o\
	$(BUILD_DIR)/asm/dolphin/card/CARDBlock.s.o\
	$(BUILD_DIR)/asm/dolphin/card/CARDDir.s.o\
	$(BUILD_DIR)/asm/dolphin/card/CARDCheck.s.o\
	$(BUILD_DIR)/asm/dolphin/card/CARDMount.s.o\
	$(BUILD_DIR)/asm/dolphin/card/CARDFormat.s.o\
	$(BUILD_DIR)/asm/dolphin/card/CARDOpen.s.o\
	$(BUILD_DIR)/asm/dolphin/card/CARDCreate.s.o\
	$(BUILD_DIR)/asm/dolphin/card/CARDRead.s.o\
	$(BUILD_DIR)/asm/dolphin/card/CARDWrite.s.o\
	$(BUILD_DIR)/asm/dolphin/card/CARDDelete.s.o\
	$(BUILD_DIR)/asm/dolphin/card/CARDStat.s.o\
	$(BUILD_DIR)/asm/dolphin/card/CARDRename.s.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/asm/dolphin/ax/AX.s.o\
	$(BUILD_DIR)/asm/dolphin/ax/AXAlloc.s.o\

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
	$(BUILD_DIR)/asm/sysdolphin/baselib/mobj.s.o\

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
	$(BUILD_DIR)/asm/sysdolphin/baselib/objalloc.s.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/src/sysdolphin/baselib/robj.c.o\
	$(BUILD_DIR)/asm/sysdolphin/baselib/robj.s.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/src/sysdolphin/baselib/id.c.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/src/sysdolphin/baselib/wobj.c.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/asm/sysdolphin/baselib/fog.s.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/asm/sysdolphin/baselib/perf.s.o\

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
	$(BUILD_DIR)/asm/sysdolphin/baselib/gobjplink.s.o\
	$(BUILD_DIR)/src/sysdolphin/baselib/gobjgxlink.c.o\
	$(BUILD_DIR)/asm/sysdolphin/baselib/gobjgxlink.s.o\
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
	$(BUILD_DIR)/src/sysdolphin/baselib/baselib_unknown_002.c.o\
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
	$(BUILD_DIR)/src/sysdolphin/baselib/sislib.c.o\
	$(BUILD_DIR)/asm/sysdolphin/baselib/sislib.s.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/asm/sysdolphin/baselib/baselib_shared_data_001.s.o\
	$(BUILD_DIR)/asm/sysdolphin/baselib/baselib_shared_data_002.s.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/asm/melee/db/db_data.s.o\
	$(BUILD_DIR)/asm/sysdolphin/baselib/baselib_unknown_003.s.o\
	$(BUILD_DIR)/asm/sysdolphin/baselib/baselib_unknown_004.s.o\
	$(BUILD_DIR)/asm/sysdolphin/baselib/baselib_unknown_005.s.o\
	$(BUILD_DIR)/asm/sysdolphin/baselib/baselib_unknown_006.s.o\
	$(BUILD_DIR)/asm/sysdolphin/baselib/baselib_unknown_007.s.o\
	$(BUILD_DIR)/src/sysdolphin/baselib/baselib_unknown_008.c.o\

TEXT_O_FILES +=\
	$(BUILD_DIR)/src/sysdolphin/baselib/baselib_unknown_001.c.o\
	$(BUILD_DIR)/asm/sysdolphin/baselib/baselib_unknown_001.s.o\
