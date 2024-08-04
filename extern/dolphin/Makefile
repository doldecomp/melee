#################################################################
#              Dolphin SDK 2001 Libraries Makefile              #
#################################################################

ifneq (,$(findstring Windows,$(OS)))
  EXE := .exe
else
  WINE ?=
endif

# If 0, tells the console to chill out. (Quiets the make process.)
VERBOSE ?= 0

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
  HOST_OS := linux
else ifeq ($(UNAME_S),Darwin)
  HOST_OS := macos
else
  $(error Unsupported host/building OS <$(UNAME_S)>)
endif

BUILD_DIR := build
TOOLS_DIR := $(BUILD_DIR)/tools
BASEROM_DIR := baserom
TARGET_LIBS := G2D              \
               ai               \
               amcnotstub       \
               amcstubs         \
               ar               \
               ax               \
               axfx             \
               base             \
               card             \
               db               \
               demo             \
               dolformat        \
               dsp              \
               dtk              \
               dvd              \
               fileCache        \
               gx               \
               hio              \
               mcc              \
               mix              \
               mtx              \
               odemustubs       \
               odenotstub       \
               os               \
               pad              \
               perf             \
               seq              \
               support          \
               syn              \
               texPalette       \
               vi

VERIFY_LIBS := $(filter-out amcstubs dsp odemustubs,$(TARGET_LIBS))

ifeq ($(VERBOSE),0)
  QUIET := @
endif

PYTHON := python3

# Every file has a debug version. Append D to the list.
TARGET_LIBS_DEBUG := $(addsuffix D,$(TARGET_LIBS))

# TODO, decompile
SRC_DIRS := $(shell find src -type d)

###################### Other Tools ######################

C_FILES := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
S_FILES := $(foreach dir,$(SRC_DIRS) $(ASM_DIRS),$(wildcard $(dir)/*.s))
DATA_FILES := $(foreach dir,$(DATA_DIRS),$(wildcard $(dir)/*.bin))
BASEROM_FILES := $(foreach dir,$(BASEROM_DIRS)\,$(wildcard $(dir)/*.s))

# Object files
O_FILES := $(foreach file,$(C_FILES),$(BUILD_DIR)/$(file:.c=.c.o)) \
           $(foreach file,$(S_FILES),$(BUILD_DIR)/$(file:.s=.s.o)) \
           $(foreach file,$(DATA_FILES),$(BUILD_DIR)/$(file:.bin=.bin.o)) \

DEP_FILES := $(O_FILES:.o=.d) $(DECOMP_C_OBJS:.o=.asmproc.d)

##################### Compiler Options #######################
findcmd = $(shell type $(1) >/dev/null 2>/dev/null; echo $$?)

# todo, please, better CROSS than this.
CROSS := powerpc-linux-gnu-

COMPILER_VERSION ?= 1.2.5

COMPILER_DIR := mwcc_compiler/GC/$(COMPILER_VERSION)
AS = $(CROSS)as
MWCC    := $(WINE) $(COMPILER_DIR)/mwcceppc.exe
AR = $(CROSS)ar
LD = $(CROSS)ld
OBJDUMP = $(CROSS)objdump
OBJCOPY = $(CROSS)objcopy
ifeq ($(HOST_OS),macos)
  CPP := clang -E -P -x c
else
  CPP := cpp
endif
DTK     := $(TOOLS_DIR)/dtk
DTK_VERSION := 0.7.4

CC        = $(MWCC)

######################## Flags #############################

CHARFLAGS := -char unsigned

CFLAGS = $(CHARFLAGS) -nodefaults -proc gekko -fp hard -Cpp_exceptions off -enum int -warn pragmas -requireprotos -pragma 'cats off'
INCLUDES := -Iinclude -Iinclude/libc -ir src

ASFLAGS = -mgekko -I src -I include

######################## Targets #############################

$(foreach dir,$(SRC_DIRS) $(ASM_DIRS) $(DATA_DIRS),$(shell mkdir -p build/release/$(dir) build/debug/$(dir)))

# why. Did some SDK libs (like CARD) prefer char signed over unsigned? TODO: Figure out consistency behind this.
build/debug/src/card/CARDRename.o: CHARFLAGS := -char signed
build/release/src/card/CARDRename.o: CHARFLAGS := -char signed
build/debug/src/card/CARDOpen.o: CHARFLAGS := -char signed
build/release/src/card/CARDOpen.o: CHARFLAGS := -char signed
build/debug/src/dvd/%.o: CFLAGS += -char signed
build/release/src/dvd/%.o: CFLAGS += -char signed

build/debug/src/demo/%.o: CFLAGS += -char signed
build/release/src/demo/%.o: CFLAGS += -char signed

build/debug/src/mtx/%.o: CFLAGS += -char signed
build/release/src/mtx/%.o: CFLAGS += -char signed

%/stub.o: CFLAGS += -warn off

######################## Build #############################

A_FILES := $(foreach dir,$(BASEROM_DIR),$(wildcard $(dir)/*.a))

TARGET_LIBS := $(addprefix baserom/,$(addsuffix .a,$(TARGET_LIBS)))
TARGET_LIBS_DEBUG := $(addprefix baserom/,$(addsuffix .a,$(TARGET_LIBS_DEBUG)))

default: all

all: $(DTK) ai.a aiD.a amcnotstub.a amcnotstubD.a amcstubs.a amcstubsD.a db.a dbD.a demo.a demoD.a dolformat.a dolformatD.a dsp.a dspD.a dtk.a dtkD.a fileCache.a fileCacheD.a gx.a gxD.a hio.a hioD.a odemustubs.a odemustubsD.a odenotstub.a odenotstubD.a os.a osD.a support.a supportD.a texPalette.a texPaletteD.a card.a cardD.a pad.a padD.a perf.a perfD.a dvd.a dvdD.a vi.a viD.a syn.a synD.a base.a baseD.a mtx.a mtxD.a mcc.a mccD.a ax.a axD.a axfx.a axfxD.a G2D.a G2DD.a ar.a arD.a seq.a seqD.a mix.a mixD.a

verify: build/release/test.bin build/debug/test.bin build/verify.sha1
	@sha1sum -c build/verify.sha1

extract: $(DTK)
	$(info Extracting files...)
	@$(DTK) ar extract $(TARGET_LIBS) --out baserom/release/src
	@$(DTK) ar extract $(TARGET_LIBS_DEBUG) --out baserom/debug/src
    # Thank you GPT, very cool. Temporary hack to remove D off of inner src folders to let objdiff work.
	@for dir in $$(find baserom/debug/src -type d -name 'src'); do \
		find "$$dir" -mindepth 1 -maxdepth 1 -type d | while read subdir; do \
			mv "$$subdir" "$${subdir%?}"; \
		done \
	done
	# Disassemble the objects and extract their dwarf info.
	find baserom -name '*.o' | while read i; do \
		$(DTK) elf disasm $$i $${i%.o}.s ; \
		$(DTK) dwarf dump $$i -o $${i%.o}_DWARF.c ; \
	done

# clean extraction so extraction can be done again.
distclean:
	rm -rf $(BASEROM_DIR)/release
	rm -rf $(BASEROM_DIR)/debug
	make clean

clean:
	rm -rf $(BUILD_DIR)
	rm -rf *.a

$(TOOLS_DIR):
	$(QUIET) mkdir -p $(TOOLS_DIR)

.PHONY: check-dtk

check-dtk: $(TOOLS_DIR)
	@version=$$($(DTK) --version | awk '{print $$2}'); \
	if [ "$(DTK_VERSION)" != "$$version" ]; then \
		$(PYTHON) tools/download_dtk.py dtk $(DTK) --tag "v$(DTK_VERSION)"; \
	fi

$(DTK): check-dtk

build/debug/src/%.o: src/%.c
	@echo 'Compiling $< (debug)'
	$(QUIET)$(CC) -c -opt level=0 -inline off -schedule off -sym on $(CFLAGS) -I- $(INCLUDES) -DDEBUG $< -o $@

build/release/src/%.o: src/%.c
	@echo 'Compiling $< (release)'
	$(QUIET)$(CC) -c -O4,p -inline auto -sym on $(CFLAGS) -I- $(INCLUDES) -DRELEASE $< -o $@

################################ Build AR Files ###############################

ai_c_files := $(wildcard src/ai/*.c)
ai.a  : $(addprefix $(BUILD_DIR)/release/,$(ai_c_files:.c=.o))
aiD.a : $(addprefix $(BUILD_DIR)/debug/,$(ai_c_files:.c=.o))

amcnotstub_c_files := $(wildcard src/amcnotstub/*.c)
amcnotstub.a  : $(addprefix $(BUILD_DIR)/release/,$(amcnotstub_c_files:.c=.o))
amcnotstubD.a : $(addprefix $(BUILD_DIR)/debug/,$(amcnotstub_c_files:.c=.o))

amcstubs_c_files := $(wildcard src/amcstubs/*.c)
amcstubs.a  : $(addprefix $(BUILD_DIR)/release/,$(amcstubs_c_files:.c=.o))
amcstubsD.a : $(addprefix $(BUILD_DIR)/debug/,$(amcstubs_c_files:.c=.o))

ar_c_files := $(wildcard src/ar/*.c)
ar.a  : $(addprefix $(BUILD_DIR)/release/,$(ar_c_files:.c=.o))
arD.a : $(addprefix $(BUILD_DIR)/debug/,$(ar_c_files:.c=.o))

ax_c_files := \
	src/ax/AX.c \
	src/ax/AXAlloc.c \
	src/ax/AXAux.c \
	src/ax/AXCL.c \
	src/ax/AXOut.c \
	src/ax/AXSPB.c \
	src/ax/AXVPB.c \
	src/ax/AXProf.c \
	src/ax/DSPCode.c
ax.a  : $(addprefix $(BUILD_DIR)/release/,$(ax_c_files:.c=.o))
axD.a : $(addprefix $(BUILD_DIR)/debug/,$(ax_c_files:.c=.o))

axfx_c_files := \
	src/axfx/reverb_hi.c \
	src/axfx/reverb_std.c \
	src/axfx/chorus.c \
	src/axfx/delay.c
axfx.a  : $(addprefix $(BUILD_DIR)/release/,$(axfx_c_files:.c=.o))
axfxD.a : $(addprefix $(BUILD_DIR)/debug/,$(axfx_c_files:.c=.o))

base_c_files := $(wildcard src/base/*.c)
base.a  : $(addprefix $(BUILD_DIR)/release/,$(base_c_files:.c=.o))
baseD.a : $(addprefix $(BUILD_DIR)/debug/,$(base_c_files:.c=.o))

card_c_files := \
	src/card/CARDBios.c \
	src/card/CARDUnlock.c \
	src/card/CARDRdwr.c \
	src/card/CARDBlock.c \
	src/card/CARDDir.c \
	src/card/CARDCheck.c \
	src/card/CARDMount.c \
	src/card/CARDFormat.c \
	src/card/CARDOpen.c \
	src/card/CARDCreate.c \
	src/card/CARDRead.c \
	src/card/CARDWrite.c \
	src/card/CARDDelete.c \
	src/card/CARDStat.c \
	src/card/CARDRename.c \
	src/card/CARDStatEx.c \
	src/card/CARDRaw.c
card.a  : $(addprefix $(BUILD_DIR)/release/,$(card_c_files:.c=.o))
cardD.a : $(addprefix $(BUILD_DIR)/debug/,$(card_c_files:.c=.o))

db_c_files := $(wildcard src/db/*.c)
db.a  : $(addprefix $(BUILD_DIR)/release/,$(db_c_files:.c=.o))
dbD.a : $(addprefix $(BUILD_DIR)/debug/,$(db_c_files:.c=.o))

demo_c_files := \
	src/demo/DEMOInit.c \
	src/demo/DEMOPuts.c \
	src/demo/DEMOFont.c \
	src/demo/DEMOPad.c \
	src/demo/DEMOStats.c \
	src/demo/DEMOWin.c
demo.a  : $(addprefix $(BUILD_DIR)/release/,$(demo_c_files:.c=.o))
demoD.a : $(addprefix $(BUILD_DIR)/debug/,$(demo_c_files:.c=.o))

dolformat_c_files := $(wildcard src/dolformat/*.c)
dolformat.a  : $(addprefix $(BUILD_DIR)/release/,$(dolformat_c_files:.c=.o))
dolformatD.a : $(addprefix $(BUILD_DIR)/debug/,$(dolformat_c_files:.c=.o))

dsp_c_files := $(wildcard src/dsp/*.c)
dsp.a  : $(addprefix $(BUILD_DIR)/release/,$(dsp_c_files:.c=.o))
dspD.a : $(addprefix $(BUILD_DIR)/debug/,$(dsp_c_files:.c=.o))

dtk_c_files := $(wildcard src/dtk/*.c)
dtk.a  : $(addprefix $(BUILD_DIR)/release/,$(dtk_c_files:.c=.o))
dtkD.a : $(addprefix $(BUILD_DIR)/debug/,$(dtk_c_files:.c=.o))

dvd_c_files := \
	src/dvd/dvdlow.c \
	src/dvd/dvdfs.c \
	src/dvd/dvd.c \
	src/dvd/dvdqueue.c \
	src/dvd/fstload.c
dvd.a  : $(addprefix $(BUILD_DIR)/release/,$(dvd_c_files:.c=.o))
dvdD.a : $(addprefix $(BUILD_DIR)/debug/,$(dvd_c_files:.c=.o))

fileCache_c_files := $(wildcard src/fileCache/*.c)
fileCache.a  : $(addprefix $(BUILD_DIR)/release/,$(fileCache_c_files:.c=.o))
fileCacheD.a : $(addprefix $(BUILD_DIR)/debug/,$(fileCache_c_files:.c=.o))

gx_c_files := \
	src/gx/GXInit.c \
	src/gx/GXFifo.c \
	src/gx/GXAttr.c \
	src/gx/GXMisc.c \
	src/gx/GXGeometry.c \
	src/gx/GXFrameBuf.c \
	src/gx/GXLight.c \
	src/gx/GXTexture.c \
	src/gx/GXBump.c \
	src/gx/GXTev.c \
	src/gx/GXPixel.c \
	src/gx/GXDraw.c \
	src/gx/GXStubs.c \
	src/gx/GXDisplayList.c \
	src/gx/GXVert.c \
	src/gx/GXTransform.c \
	src/gx/GXVerify.c \
	src/gx/GXVerifXF.c \
	src/gx/GXVerifRAS.c \
	src/gx/GXSave.c \
	src/gx/GXPerf.c
gx.a  : $(addprefix $(BUILD_DIR)/release/,$(gx_c_files:.c=.o))
gxD.a : $(addprefix $(BUILD_DIR)/debug/,$(gx_c_files:.c=.o))

hio_c_files := $(wildcard src/hio/*.c)
hio.a  : $(addprefix $(BUILD_DIR)/release/,$(hio_c_files:.c=.o))
hioD.a : $(addprefix $(BUILD_DIR)/debug/,$(hio_c_files:.c=.o))

mcc_c_files := \
	src/mcc/mcc.c \
	src/mcc/fio.c \
	src/mcc/tty.c
mcc.a  : $(addprefix $(BUILD_DIR)/release/,$(mcc_c_files:.c=.o))
mccD.a : $(addprefix $(BUILD_DIR)/debug/,$(mcc_c_files:.c=.o))

mix_c_files := $(wildcard src/mix/*.c)
mix.a  : $(addprefix $(BUILD_DIR)/release/,$(mix_c_files:.c=.o))
mixD.a : $(addprefix $(BUILD_DIR)/debug/,$(mix_c_files:.c=.o))

mtx_c_files := \
	src/mtx/mtx.c \
	src/mtx/mtx44.c \
	src/mtx/vec.c \
	src/mtx/mtxvec.c \
	src/mtx/mtxstack.c \
	src/mtx/psmtx.c
mtx.a  : $(addprefix $(BUILD_DIR)/release/,$(mtx_c_files:.c=.o))
mtxD.a : $(addprefix $(BUILD_DIR)/debug/,$(mtx_c_files:.c=.o))

odemustubs_c_files := $(wildcard src/odemustubs/*.c)
odemustubs.a  : $(addprefix $(BUILD_DIR)/release/,$(odemustubs_c_files:.c=.o))
odemustubsD.a : $(addprefix $(BUILD_DIR)/debug/,$(odemustubs_c_files:.c=.o))

odenotstub_c_files := $(wildcard src/odenotstub/*.c)
odenotstub.a  : $(addprefix $(BUILD_DIR)/release/,$(odenotstub_c_files:.c=.o))
odenotstubD.a : $(addprefix $(BUILD_DIR)/debug/,$(odenotstub_c_files:.c=.o))

os_c_files := \
	src/os/OS.c \
	src/os/OSAddress.c \
	src/os/OSAlarm.c \
	src/os/OSAlloc.c \
	src/os/OSArena.c \
	src/os/OSAudioSystem.c \
	src/os/OSCache.c \
	src/os/OSContext.c \
	src/os/OSError.c \
	src/os/OSExi.c \
	src/os/OSExiAd16.c \
	src/os/OSFont.c \
	src/os/OSInterrupt.c \
	src/os/OSLink.c \
	src/os/OSMessage.c \
	src/os/OSMemory.c \
	src/os/OSMutex.c \
	src/os/OSReset.c \
	src/os/OSResetSW.c \
	src/os/OSRtc.c \
	src/os/OSSerial.c \
	src/os/OSStopwatch.c \
	src/os/OSSync.c \
	src/os/OSThread.c \
	src/os/OSTime.c \
	src/os/OSTimer.c \
	src/os/OSUartExi.c \
	src/os/time.dolphin.c \
	src/os/__start.c \
	src/os/__ppc_eabi_init.c
os.a  : $(addprefix $(BUILD_DIR)/release/,$(os_c_files:.c=.o))
osD.a : $(addprefix $(BUILD_DIR)/debug/,$(os_c_files:.c=.o))

pad_c_files := src/pad/Padclamp.c src/pad/Pad.c
pad.a  : $(addprefix $(BUILD_DIR)/release/,$(pad_c_files:.c=.o))
padD.a : $(addprefix $(BUILD_DIR)/debug/,$(pad_c_files:.c=.o))

perf_c_files := $(wildcard src/perf/*.c)
perf.a  : $(addprefix $(BUILD_DIR)/release/,$(perf_c_files:.c=.o))
perfD.a : $(addprefix $(BUILD_DIR)/debug/,$(perf_c_files:.c=.o))

seq_c_files := $(wildcard src/seq/*.c)
seq.a  : $(addprefix $(BUILD_DIR)/release/,$(seq_c_files:.c=.o))
seqD.a : $(addprefix $(BUILD_DIR)/debug/,$(seq_c_files:.c=.o))

support_c_files := \
	src/support/List.c \
	src/support/string.c \
	src/support/Tree.c \
	src/support/HTable.c
support.a  : $(addprefix $(BUILD_DIR)/release/,$(support_c_files:.c=.o))
supportD.a : $(addprefix $(BUILD_DIR)/debug/,$(support_c_files:.c=.o))

syn_c_files := $(wildcard src/syn/*.c)
syn.a  : $(addprefix $(BUILD_DIR)/release/,$(syn_c_files:.c=.o))
synD.a : $(addprefix $(BUILD_DIR)/debug/,$(syn_c_files:.c=.o))

texPalette_c_files := $(wildcard src/texPalette/*.c)
texPalette.a  : $(addprefix $(BUILD_DIR)/release/,$(texPalette_c_files:.c=.o))
texPaletteD.a : $(addprefix $(BUILD_DIR)/debug/,$(texPalette_c_files:.c=.o))

vi_c_files := \
	src/vi/vi.c \
	src/vi/i2c.c \
	src/vi/initphilips.c \
	src/vi/gpioexi.c
vi.a  : $(addprefix $(BUILD_DIR)/release/,$(vi_c_files:.c=.o))
viD.a : $(addprefix $(BUILD_DIR)/debug/,$(vi_c_files:.c=.o))

G2D_c_files := $(wildcard src/G2D/*.c)
G2D.a  : $(addprefix $(BUILD_DIR)/release/,$(G2D_c_files:.c=.o))
G2DD.a : $(addprefix $(BUILD_DIR)/debug/,$(G2D_c_files:.c=.o))

build/release/baserom.elf: build/release/src/stub.o $(foreach l,$(VERIFY_LIBS),baserom/$(l).a)
build/release/test.elf:    build/release/src/stub.o $(foreach l,$(VERIFY_LIBS),$(l).a)
build/debug/baserom.elf:   build/release/src/stub.o $(foreach l,$(VERIFY_LIBS),baserom/$(l)D.a)
build/debug/test.elf:      build/release/src/stub.o $(foreach l,$(VERIFY_LIBS),$(l)D.a)

%.bin: %.elf
	$(OBJCOPY) -O binary $< $@

%.elf:
	@echo Linking ELF $@
	$(QUIET)$(LD) -T gcn.ld --whole-archive $(filter %.o,$^) $(filter %.a,$^) -o $@ -Map $(@:.elf=.map)

%.a:
	@ test ! -z '$?' || { echo 'no object files for $@'; return 1; }
	@echo 'Creating static library $@'
	$(QUIET)$(AR) -v -r $@ $(filter %.o,$?)

# generate baserom hashes
build/verify.sha1: build/release/baserom.bin build/debug/baserom.bin
	sha1sum $^ | sed 's/baserom/test/' > $@

# ------------------------------------------------------------------------------

.PHONY: all clean distclean default split setup extract

print-% : ; $(info $* is a $(flavor $*) variable set to [$($*)]) @true

-include $(DEP_FILES)
