ifneq ($(findstring MINGW,$(shell uname)),)
  WINDOWS := 1
endif
ifneq ($(findstring MSYS,$(shell uname)),)
  WINDOWS := 1
endif

#-------------------------------------------------------------------------------
# Files
#-------------------------------------------------------------------------------

TARGET := ssbm.us.1.2

BUILD_DIR := build/$(TARGET)

SRC_DIRS := $(shell find src/ -type f -name '*.c')
ASM_DIRS := $(shell find asm/ -type f -name '*.s')

# Inputs
S_FILES := $(wildcard asm/*.s)
C_FILES := $(wildcard src/*.c)
LDSCRIPT := $(BUILD_DIR)/ldscript.lcf

# Outputs
DOL     := $(BUILD_DIR)/main.dol
ELF     := $(DOL:.dol=.elf)
MAP     := $(BUILD_DIR)/GALE01.map

include obj_files.mk

O_FILES := $(INIT_O_FILES) $(EXTAB_O_FILES) $(EXTABINDEX_O_FILES) $(TEXT_O_FILES) $(RODATA_O_FILES) $(DATA_O_FILES)    \
           $(BSS_O_FILES) $(SDATA_O_FILES) $(SBSS_O_FILES) $(SDATA2_O_FILES)

#-------------------------------------------------------------------------------
# Tools
#-------------------------------------------------------------------------------

MWCC_VERSION := 1.0
MWCC_LD_VERSION := 1.3.2

# Programs
ifeq ($(WINDOWS),1)
  WINE :=
else
  WINE := wine
endif
AS      := $(DEVKITPPC)/bin/powerpc-eabi-as
CPP     := cpp -P
CC      := $(WINE) tools/mwcc_compiler/$(MWCC_VERSION)/mwcceppc.exe
LD      := $(WINE) tools/mwcc_compiler/$(MWCC_LD_VERSION)/mwldeppc.exe
ELF2DOL := tools/elf2dol
SHA1SUM := sha1sum
PYTHON  := python3

POSTPROC := tools/postprocess.py

# Options
INCLUDES := -i include -i include/dolphin/ -i include/dolphin/mtx/ -i src -i src/msl -i src/msl/ppc_eabi -i src/dolphin/os/init/ -i src/runtime/ -i src/sysdolphin/ -i src/sysdolphin/baselib/ -i src/melee/ -i src/melee/gr/ -i src/melee/lb/

ASFLAGS := -mgekko -I include
LDFLAGS := -map $(MAP) -fp hard -nodefaults
CFLAGS  := -Cpp_exceptions off -proc gekko -fp hard -O4,p -enum int -nodefaults -msgstyle gcc $(INCLUDES)

# for postprocess.py
PROCFLAGS := -fprologue-fixup=old_stack

#-------------------------------------------------------------------------------
# Recipes
#-------------------------------------------------------------------------------

### Default target ###

default: all

all: $(DOL)

ALL_DIRS := build $(BUILD_DIR) $(addprefix $(BUILD_DIR)/,$(SRC_DIRS) $(ASM_DIRS))

# Make sure build directory exists before compiling anything
DUMMY != mkdir -p $(ALL_DIRS)

.PHONY: tools

$(LDSCRIPT): ldscript.lcf
	$(CPP) -MMD -MP -MT $@ -MF $@.d -I include/ -I . -DBUILD_DIR=$(BUILD_DIR) -o $@ $<

$(DOL): $(ELF) | tools
	$(ELF2DOL) $< $@
	$(SHA1SUM) -c $(TARGET).sha1

clean:
	rm -f -d -r build
	$(MAKE) -C tools clean

tools:
	$(MAKE) -C tools

$(ELF): $(O_FILES) $(LDSCRIPT)
	@echo $(O_FILES) > build/o_files
	$(LD) $(LDFLAGS) -o $@ -lcf $(LDSCRIPT) @build/o_files

$(BUILD_DIR)/%.o: %.s
	$(AS) $(ASFLAGS) -o $@ $<

$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
	$(PYTHON) $(POSTPROC) $(PROCFLAGS) $@

### Debug Print ###

print-% : ; $(info $* is a $(flavor $*) variable set to [$($*)]) @true
