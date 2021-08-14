# Linker order for every file, passed to the Metrowerks linker.

INIT_O_FILES := 						            \
	$(BUILD_DIR)/src/runtime/__mem.o	            \
    $(BUILD_DIR)/asm/init.o

EXTAB_O_FILES :=                                    \
    $(BUILD_DIR)/asm/extab.o

EXTABINDEX_O_FILES :=                               \
    $(BUILD_DIR)/asm/extabindex.o

TEXT_O_FILES := 						            \
	$(BUILD_DIR)/src/melee/lib/lbcommands.o			\
	$(BUILD_DIR)/asm/lbcommands_asm.o  	            \
	$(BUILD_DIR)/asm/code_80005BB0.o  	            \
	$(BUILD_DIR)/asm/code_80008D30.o  	            \
	$(BUILD_DIR)/asm/code_8000B1CC.o  	            \
	$(BUILD_DIR)/asm/code_8000CE50.o  	            \
	$(BUILD_DIR)/asm/lbvector.o		 	            \
	$(BUILD_DIR)/asm/text_1.o 		 	            \
	$(BUILD_DIR)/asm/player.o 		 	            \
	$(BUILD_DIR)/asm/text_2.o 		 	            \
	$(BUILD_DIR)/asm/text_3.o 		 	            \
	$(BUILD_DIR)/asm/ftdonkey_1.o 		            \
	$(BUILD_DIR)/asm/ftmario.o 			            \
	$(BUILD_DIR)/asm/ftfalcon.o 		            \
	$(BUILD_DIR)/asm/ftfox.o 			            \
	$(BUILD_DIR)/asm/ftlink.o 			            \
	$(BUILD_DIR)/asm/ftkirby.o 			            \
	$(BUILD_DIR)/asm/ftdonkey_2.o 		            \
	$(BUILD_DIR)/asm/ftseak.o 			            \
	$(BUILD_DIR)/asm/ftness.o 			            \
	$(BUILD_DIR)/asm/ftpeach.o 			            \
	$(BUILD_DIR)/asm/fticeclimber.o 	            \
	$(BUILD_DIR)/asm/ftpikachu.o 		            \
	$(BUILD_DIR)/asm/ftsamus.o 		 	            \
	$(BUILD_DIR)/asm/ftyoshi.o 		 	            \
	$(BUILD_DIR)/asm/ftkoopa.o 		 	            \
	$(BUILD_DIR)/asm/ftmars.o 		 	            \
	$(BUILD_DIR)/asm/ftzelda.o 		 	            \
	$(BUILD_DIR)/asm/ftpurin.o 		 	            \
	$(BUILD_DIR)/asm/ftluigi.o 		 	            \
	$(BUILD_DIR)/asm/ftmewtwo.o 		            \
	$(BUILD_DIR)/asm/ftclink.o 			            \
	$(BUILD_DIR)/asm/ftdrmario.o 		            \
	$(BUILD_DIR)/asm/ftfalco.o 			            \
	$(BUILD_DIR)/asm/ftpichu.o 			            \
	$(BUILD_DIR)/asm/ftgamewatch.o 		            \
	$(BUILD_DIR)/asm/ftganon.o 			            \
	$(BUILD_DIR)/asm/ftemblem.o 		            \
	$(BUILD_DIR)/asm/ftzakoboy.o 		            \
	$(BUILD_DIR)/asm/ftzakogirl.o 		            \
	$(BUILD_DIR)/asm/ftgigakoopa.o 		            \
	$(BUILD_DIR)/asm/ftsandbag.o 		            \
	$(BUILD_DIR)/asm/ftmasterhand.o 	            \
	$(BUILD_DIR)/asm/ftcrazyhand.o 		            \
	$(BUILD_DIR)/asm/ftbosslib.o 		            \
	$(BUILD_DIR)/asm/text_4.o 		 	            \
	$(BUILD_DIR)/asm/grfzerocar.o 		            \
	$(BUILD_DIR)/asm/grizumi.o 		 	            \
	$(BUILD_DIR)/asm/grcastle.o 		            \
	$(BUILD_DIR)/asm/grstadium.o 	 	            \
	$(BUILD_DIR)/asm/grkongo.o 		 	            \
	$(BUILD_DIR)/asm/grzebes.o 		 	            \
	$(BUILD_DIR)/asm/grcorneria.o 	 	            \
	$(BUILD_DIR)/asm/grstory.o 		 	            \
	$(BUILD_DIR)/asm/gronett.o 		 	            \
	$(BUILD_DIR)/asm/grbigblue.o 	 	            \
	$(BUILD_DIR)/asm/grmutecity.o 	 	            \
	$(BUILD_DIR)/asm/grfourside.o 	 	            \
	$(BUILD_DIR)/asm/grgreatbay.o 	 	            \
	$(BUILD_DIR)/asm/gricemt.o 		 	            \
	$(BUILD_DIR)/asm/grinishie1.o 		            \
	$(BUILD_DIR)/asm/grinishie2.o 	 	            \
	$(BUILD_DIR)/asm/grkraid_.o 		            \
	$(BUILD_DIR)/asm/grrcruise.o 	 	            \
	$(BUILD_DIR)/asm/grshrine.o 		            \
	$(BUILD_DIR)/asm/gryorster.o 	 	            \
	$(BUILD_DIR)/asm/grgarden.o 		            \
	$(BUILD_DIR)/asm/grvenom.o 		 	            \
	$(BUILD_DIR)/asm/grtest.o 		 	            \
	$(BUILD_DIR)/asm/grkinokoroute.o  	            \
	$(BUILD_DIR)/asm/grshrineroute.o  	            \
	$(BUILD_DIR)/asm/grzebesroute.o   	            \
	$(BUILD_DIR)/asm/grbigblueroute.o 	            \
	$(BUILD_DIR)/asm/grfigure1.o 	 	            \
	$(BUILD_DIR)/asm/grfigure2.o 	 	            \
	$(BUILD_DIR)/asm/grfigure3.o		            \
	$(BUILD_DIR)/asm/groldyoshi.o 		            \
	$(BUILD_DIR)/asm/groldkongo.o 		            \
	$(BUILD_DIR)/asm/groldpupupu.o 		            \
	$(BUILD_DIR)/asm/grpura.o 			            \
	$(BUILD_DIR)/asm/grgreens.o 		            \
	$(BUILD_DIR)/asm/grflatzone.o 		            \
	$(BUILD_DIR)/asm/grpushon.o 		            \
	$(BUILD_DIR)/asm/grfigureget.o 		            \
	$(BUILD_DIR)/asm/grbattle.o 		            \
	$(BUILD_DIR)/asm/grlast.o 			            \
	$(BUILD_DIR)/asm/grhomerun.o 		            \
	$(BUILD_DIR)/asm/grheal.o 			            \
	$(BUILD_DIR)/asm/grtmario.o 		            \
	$(BUILD_DIR)/asm/grtfalcon.o 		            \
	$(BUILD_DIR)/asm/grtclink.o 		            \
	$(BUILD_DIR)/asm/grtdonkey.o 		            \
	$(BUILD_DIR)/asm/grtdrmario.o 		            \
	$(BUILD_DIR)/asm/grtfalco.o 		            \
	$(BUILD_DIR)/asm/grtfox.o 			            \
	$(BUILD_DIR)/asm/grticeclimber.o 	            \
	$(BUILD_DIR)/asm/grtkirby.o 		            \
	$(BUILD_DIR)/asm/grtkoopa.o 		            \
	$(BUILD_DIR)/asm/grtlink.o 			            \
	$(BUILD_DIR)/asm/grtluigi.o 		            \
	$(BUILD_DIR)/asm/grtmars.o 			            \
	$(BUILD_DIR)/asm/grtmewtwo.o 		            \
	$(BUILD_DIR)/asm/grtness.o 			            \
	$(BUILD_DIR)/asm/grtpeach.o 		            \
	$(BUILD_DIR)/asm/grtpichu.o 		            \
	$(BUILD_DIR)/asm/grtpikachu.o 		            \
	$(BUILD_DIR)/asm/grtpurin.o 		            \
	$(BUILD_DIR)/asm/grtsamus.o 		            \
	$(BUILD_DIR)/asm/grtseak.o 			            \
	$(BUILD_DIR)/asm/grtyoshi.o 		            \
	$(BUILD_DIR)/asm/grtzelda.o 		            \
	$(BUILD_DIR)/asm/grtgamewatch.o 	            \
	$(BUILD_DIR)/asm/grtemblem.o 		            \
	$(BUILD_DIR)/asm/grtganon.o 		            \
	$(BUILD_DIR)/asm/code_80224A54.o 	            \
	$(BUILD_DIR)/asm/text_5.o                       \
                                                    \
	$(BUILD_DIR)/asm/__va_arg.o                     \
	$(BUILD_DIR)/asm/NMWException.o                 \
	$(BUILD_DIR)/asm/Gecko_setjmp.o                 \
	$(BUILD_DIR)/asm/runtime.o                      \
	$(BUILD_DIR)/src/runtime/__init_cpp_exceptions.o 		  \
	$(BUILD_DIR)/asm/abort_exit.o                   \
	$(BUILD_DIR)/asm/ansi_fp.o                      \
	$(BUILD_DIR)/asm/buffer_io.o                    \
	$(BUILD_DIR)/src/msl/ppc_eabi/critical_regions.gamecube.o \
	$(BUILD_DIR)/asm/ctype.o                        \
	$(BUILD_DIR)/asm/direct_io.o                    \
	$(BUILD_DIR)/asm/cstring.o                      \
	$(BUILD_DIR)/asm/mem_funcs.o                    \
	$(BUILD_DIR)/asm/printf.o                       \
	$(BUILD_DIR)/src/msl/rand.o                     \
	$(BUILD_DIR)/asm/string.o                       \
	$(BUILD_DIR)/asm/strtoul.o                      \
	$(BUILD_DIR)/asm/console_io.o                   \
	$(BUILD_DIR)/asm/wchar_io.o                     \
	$(BUILD_DIR)/asm/math.o                         \
                                                    \
	$(BUILD_DIR)/asm/mainloop.o                     \
	$(BUILD_DIR)/asm/nubevent.o                     \
	$(BUILD_DIR)/asm/nubinit.o                      \
	$(BUILD_DIR)/asm/msg.o                          \
	$(BUILD_DIR)/asm/msgbuf.o                       \
	$(BUILD_DIR)/asm/serpoll.o                      \
	$(BUILD_DIR)/asm/dispatch.o                     \
	$(BUILD_DIR)/asm/msghndlr.o                     \
	$(BUILD_DIR)/asm/flush_cache.o                  \
	$(BUILD_DIR)/asm/mem_TRK.o                      \
	$(BUILD_DIR)/asm/targimpl.o                     \
	$(BUILD_DIR)/asm/dolphin_trk.o                  \
	$(BUILD_DIR)/asm/mpc_7xx_603e.o                 \
	$(BUILD_DIR)/asm/main_TRK.o                     \
	$(BUILD_DIR)/asm/dolphin_trk_glue.o             \
	$(BUILD_DIR)/asm/targcont.o                     \
	$(BUILD_DIR)/asm/AmcExi2Stubs.o                 \
	$(BUILD_DIR)/asm/DebuggerDriver.o               \
                                                    \
	$(BUILD_DIR)/asm/hio.o                          \
	$(BUILD_DIR)/asm/mcc.o                          \
	$(BUILD_DIR)/asm/fio.o                          \
	$(BUILD_DIR)/asm/THPDec.o                       \
	$(BUILD_DIR)/asm/jpegdec.o                      \
	$(BUILD_DIR)/asm/PPCArch.o                      \
	$(BUILD_DIR)/asm/db.o                           \
	$(BUILD_DIR)/asm/dsp.o                          \
	$(BUILD_DIR)/asm/dsp_debug.o                    \
	$(BUILD_DIR)/asm/dsp_task.o                     \
	$(BUILD_DIR)/asm/dvdlow.o                       \
	$(BUILD_DIR)/asm/dvdqueue.o                     \
	$(BUILD_DIR)/asm/dvderror.o                     \
	$(BUILD_DIR)/asm/fstload.o                      \
	$(BUILD_DIR)/asm/GXInit.o                       \
	$(BUILD_DIR)/asm/GXFifo.o                       \
	$(BUILD_DIR)/asm/mtxvec.o                       \
                                                    \
	$(BUILD_DIR)/asm/dolphin_sdk_1.o                \
                                                    \
	$(BUILD_DIR)/asm/__ppc_eabi_init.o              \
                                                    \
	$(BUILD_DIR)/asm/Padclamp.o                     \
                                                    \
	$(BUILD_DIR)/asm/dolphin_sdk_2.o                \
                                                    \
	$(BUILD_DIR)/asm/vi.o                           \
	$(BUILD_DIR)/asm/ai.o                           \
	$(BUILD_DIR)/asm/ar.o                           \
	$(BUILD_DIR)/asm/arq.o                          \
                                                    \
	$(BUILD_DIR)/asm/CARD.o 					    \
                                                    \
	$(BUILD_DIR)/asm/AX.o 					        \
                                                    \
	$(BUILD_DIR)/asm/dobj.o						    \
	$(BUILD_DIR)/asm/tobj.o						    \
	$(BUILD_DIR)/asm/state.o					    \
	$(BUILD_DIR)/src/sysdolphin/tev.o				\
	$(BUILD_DIR)/asm/tev.o						    \
	$(BUILD_DIR)/asm/mobj.o						    \
	$(BUILD_DIR)/src/sysdolphin/aobj.o	            \
	$(BUILD_DIR)/asm/lobj.o						    \
	$(BUILD_DIR)/asm/cobj.o						    \
	$(BUILD_DIR)/src/sysdolphin/fobj.o              \
	$(BUILD_DIR)/asm/fobj_asm.o					    \
	$(BUILD_DIR)/src/sysdolphin/pobj.o              \
	$(BUILD_DIR)/asm/pobj.o						    \
	$(BUILD_DIR)/asm/jobj.o						    \
	$(BUILD_DIR)/src/sysdolphin/displayfunc.o       \
	$(BUILD_DIR)/asm/displayfunc_asm.o			    \
	$(BUILD_DIR)/src/sysdolphin/initialize.o 	    \
	$(BUILD_DIR)/asm/initialize.o				    \
	$(BUILD_DIR)/asm/video.o					    \
	$(BUILD_DIR)/asm/pad.o						    \
	$(BUILD_DIR)/asm/spline.o					    \
	$(BUILD_DIR)/asm/mtx.o						    \
	$(BUILD_DIR)/asm/util.o						    \
	$(BUILD_DIR)/src/sysdolphin/objalloc.o          \
	$(BUILD_DIR)/asm/objalloc_asm.o				    \
	$(BUILD_DIR)/src/sysdolphin/robj.o			    \
	$(BUILD_DIR)/asm/robj.o						    \
	$(BUILD_DIR)/src/sysdolphin/id.o                \
	$(BUILD_DIR)/src/sysdolphin/wobj.o              \
	$(BUILD_DIR)/asm/wobj_asm.o					    \
	$(BUILD_DIR)/asm/fog.o						    \
	$(BUILD_DIR)/asm/perf.o						    \
	$(BUILD_DIR)/asm/list.o						    \
	$(BUILD_DIR)/src/sysdolphin/object.o            \
	$(BUILD_DIR)/asm/quatlib.o                      \
	$(BUILD_DIR)/asm/memory.o			            \
	$(BUILD_DIR)/asm/shadow.o			            \
	$(BUILD_DIR)/asm/archive.o				        \
	$(BUILD_DIR)/src/sysdolphin/random.o			\
	$(BUILD_DIR)/asm/bytecode.o					    \
	$(BUILD_DIR)/asm/class.o					    \
	$(BUILD_DIR)/asm/hash.o					        \
	$(BUILD_DIR)/asm/texp.o				            \
	$(BUILD_DIR)/asm/texpdag.o					    \
	$(BUILD_DIR)/asm/leak.o						    \
	$(BUILD_DIR)/asm/debug.o					    \
	$(BUILD_DIR)/asm/synth.o					    \
	$(BUILD_DIR)/asm/AXDriver.o					    \
	$(BUILD_DIR)/asm/devcom.o					    \
	$(BUILD_DIR)/asm/gobjproc.o					    \
	$(BUILD_DIR)/asm/gobjplink.o				    \
	$(BUILD_DIR)/asm/gobjgxlink.o				    \
	$(BUILD_DIR)/asm/gobjobject_.o				    \
	$(BUILD_DIR)/asm/gobjuserdata.o				    \
	$(BUILD_DIR)/src/sysdolphin/gobj.o			    \
	$(BUILD_DIR)/asm/gobj.o						    \
	$(BUILD_DIR)/asm/code_80391580.o			    \
	$(BUILD_DIR)/asm/psdisp.o					    \
	$(BUILD_DIR)/asm/psdisptev.o				    \
	$(BUILD_DIR)/asm/psappsrt.o					    \
	$(BUILD_DIR)/asm/sobj.o						    \
	$(BUILD_DIR)/asm/sislib.o					    \
	$(BUILD_DIR)/asm/code_803A949C.o

CTORS_O_FILES :=                                    \
    $(BUILD_DIR)/asm/ctors.o

DTORS_O_FILES :=                                    \
    $(BUILD_DIR)/asm/dtors.o

RODATA_O_FILES :=                                   \
    $(BUILD_DIR)/asm/rodata.o

DATA_O_FILES :=                                     \
    $(BUILD_DIR)/asm/data.o

BSS_O_FILES :=                                      \
    $(BUILD_DIR)/asm/bss.o

SDATA_O_FILES :=                                    \
    $(BUILD_DIR)/asm/sdata.o

# Previously defined in bss.o
SBSS_O_FILES :=

SDATA2_O_FILES :=                                   \
    $(BUILD_DIR)/asm/sdata2.o
