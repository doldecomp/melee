# Files with unscheduled epilogues.

EPILOGUE_UNSCHEDULED:=\
	$(EPILOGUE_DIR)/src/melee/lb/lblanguage.c.o\
	$(EPILOGUE_DIR)/src/melee/lb/lbcommand.c.o\
	$(EPILOGUE_DIR)/src/melee/lb/lbvector.c.o\
	$(EPILOGUE_DIR)/src/melee/lb/lbtime.c.o\
	$(EPILOGUE_DIR)/src/melee/lb/lbfile.c.o\
	$(EPILOGUE_DIR)/src/melee/lb/lbarchive.c.o\
	$(EPILOGUE_DIR)/src/melee/ft/ftcliffcommon.c.o 		\
	$(EPILOGUE_DIR)/src/melee/ft/ftwalljump.c.o\
 	$(EPILOGUE_DIR)/src/melee/ft/chara/ftclink.c.o\
 	$(EPILOGUE_DIR)/src/melee/ft/chara/ftclink_2.c.o\
	$(EPILOGUE_DIR)/src/melee/ft/chara/ftdrmario.c.o\
	$(EPILOGUE_DIR)/src/melee/ft/chara/ftdrmario_2.c.o\
	$(EPILOGUE_DIR)/src/melee/ft/chara/ftemblem.c.o\
	$(EPILOGUE_DIR)/src/melee/ft/chara/ftfalco.c.o\
	$(EPILOGUE_DIR)/src/melee/ft/chara/ftfox.c.o\
	$(EPILOGUE_DIR)/src/melee/ft/chara/ftganon.c.o\
	$(EPILOGUE_DIR)/src/melee/ft/chara/ftgigakoopa.c.o\
	$(EPILOGUE_DIR)/src/melee/ft/chara/ftkoopa.c.o\
	$(EPILOGUE_DIR)/src/melee/ft/chara/ftmario.c.o\
	$(EPILOGUE_DIR)/src/melee/ft/chara/ftmars/ftmars1.c.o\
	$(EPILOGUE_DIR)/src/melee/ft/chara/ftmars/ftmars2_neutralb.c.o\
	$(EPILOGUE_DIR)/src/melee/ft/chara/ftmars/ftmars3_sideb.c.o\
	$(EPILOGUE_DIR)/src/melee/ft/chara/ftmars/ftmars4_upb.c.o\
	$(EPILOGUE_DIR)/src/melee/ft/chara/ftmars/ftmars5_downb.c.o\
	$(EPILOGUE_DIR)/src/melee/ft/chara/ftness.c.o\
	$(EPILOGUE_DIR)/src/melee/ft/chara/ftpeach.c.o\
	$(EPILOGUE_DIR)/src/melee/ft/chara/ftpichu.c.o\
	$(EPILOGUE_DIR)/src/melee/ft/chara/ftsandbag.c.o\
	$(EPILOGUE_DIR)/src/melee/ft/chara/ftzakoboy.c.o\
	$(EPILOGUE_DIR)/src/melee/ft/chara/ftzakogirl.c.o\
	$(EPILOGUE_DIR)/src/melee/gr/grstory.c.o\
	$(EPILOGUE_DIR)/src/melee/gr/stage.c.o\
	$(EPILOGUE_DIR)/src/melee/pl/player.c.o\
	$(EPILOGUE_DIR)/src/sysdolphin/baselib/tobj.c.o\
	$(EPILOGUE_DIR)/src/sysdolphin/baselib/aobj.c.o\
	$(EPILOGUE_DIR)/src/sysdolphin/baselib/fobj.c.o\
	$(EPILOGUE_DIR)/src/sysdolphin/baselib/robj.c.o\
	$(EPILOGUE_DIR)/src/sysdolphin/baselib/wobj.c.o\
	$(EPILOGUE_DIR)/src/sysdolphin/baselib/texp.c.o\
	$(EPILOGUE_DIR)/src/sysdolphin/baselib/list.c.o\
	$(EPILOGUE_DIR)/src/sysdolphin/baselib/archive.c.o\
	$(EPILOGUE_DIR)/src/sysdolphin/baselib/displayfunc.c.o\
	$(EPILOGUE_DIR)/src/sysdolphin/baselib/controller.c.o\
	$(EPILOGUE_DIR)/src/sysdolphin/baselib/rumble.c.o\
	$(EPILOGUE_DIR)/src/sysdolphin/baselib/dobj.c.o\
	$(EPILOGUE_DIR)/src/sysdolphin/baselib/shadow.c.o\
	$(EPILOGUE_DIR)/src/sysdolphin/baselib/class.c.o\
	$(EPILOGUE_DIR)/src/sysdolphin/baselib/pobj.c.o\
	$(EPILOGUE_DIR)/src/sysdolphin/baselib/id.c.o\
	$(EPILOGUE_DIR)/src/sysdolphin/baselib/lobj.c.o\
	$(EPILOGUE_DIR)/src/sysdolphin/baselib/gobjgxlink.c.o\
	$(EPILOGUE_DIR)/src/sysdolphin/baselib/gobjuserdata.c.o\
	$(EPILOGUE_DIR)/src/sysdolphin/baselib/random.c.o\
	$(EPILOGUE_DIR)/src/sysdolphin/baselib/cobj.c.o\
	$(EPILOGUE_DIR)/src/sysdolphin/baselib/mobj.c.o\
