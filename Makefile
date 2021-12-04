ifneq ($(findstring MINGW,$(shell uname)),)
  WINDOWS := 1
endif
ifneq ($(findstring MSYS,$(shell uname)),)
  WINDOWS := 1
endif

GENERATE_MAP ?= 1

VERBOSE ?= 0

ifeq ($(VERBOSE),0)
  QUIET := @
endif

#-------------------------------------------------------------------------------
# Files
#-------------------------------------------------------------------------------

TARGET := ssbm.us.1.2

BUILD_DIR := build/$(TARGET)

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
DEP_FILES := $(O_FILES:.o=.dep)

#-------------------------------------------------------------------------------
# Tools
#-------------------------------------------------------------------------------

MWCC_VERSION := 1.1
MWCC_LD_VERSION := 1.1

# Programs
ifeq ($(WINDOWS),1)
  WINE :=
else
  WINE ?= wine
endif
AS      := $(DEVKITPPC)/bin/powerpc-eabi-as
CPP     := cpp -P
CC      := $(WINE) tools/mwcc_compiler/$(MWCC_VERSION)/mwcceppc.exe
LD      := $(WINE) tools/mwcc_compiler/$(MWCC_LD_VERSION)/mwldeppc.exe
ELF2DOL := tools/elf2dol
HOSTCC  := cc
SHA1SUM := sha1sum
PYTHON  := python3

POSTPROC := tools/postprocess.py

# Options
INCLUDE_DIRS = $(*D)
SYSTEM_INCLUDE_DIRS := include include/dolphin include/dolphin/mtx src
#INCLUDES = -i $(*D) -I- -i include -i include/dolphin/ -i include/dolphin/mtx/ -i src
INCLUDES = $(addprefix -i ,$(INCLUDE_DIRS)) -I- $(addprefix -i ,$(SYSTEM_INCLUDE_DIRS))

ASFLAGS := -mgekko -I include
LDFLAGS := -fp hard -nodefaults
ifeq ($(GENERATE_MAP),1)
  LDFLAGS += -map $(MAP)
endif
CFLAGS  = -Cpp_exceptions off -proc gekko -fp hard -O4,p -enum int -nodefaults $(INCLUDES)

# for postprocess.py
PROCFLAGS := -fprologue-fixup=old_stack

HOSTCFLAGS := -Wall -O3 -s

#-------------------------------------------------------------------------------
# Recipes
#-------------------------------------------------------------------------------

# Remove all built-in rules
.SUFFIXES:

.PHONY: default

### Default target ###

default: $(DOL)
	$(QUIET) $(SHA1SUM) -c $(TARGET).sha1

ALL_DIRS := $(sort $(dir $(O_FILES)))

# Make sure build directory exists before compiling anything
DUMMY != mkdir -p $(ALL_DIRS)

$(LDSCRIPT): ldscript.lcf
	$(QUIET) $(CPP) -MMD -MP -MT $@ -MF $@.d -I include/ -I . -DBUILD_DIR=$(BUILD_DIR) -o $@ $<

%.dol: %.elf $(ELF2DOL)
	@echo Converting $< to $@
	$(QUIET) $(ELF2DOL) $< $@

clean:
	rm -f -d -r build $(ELF2DOL)

$(ELF): $(O_FILES) $(LDSCRIPT)
	@echo Linking ELF $@
	$(QUIET) echo $(O_FILES) > build/o_files
	$(QUIET) $(LD) $(LDFLAGS) -o $@ -lcf $(LDSCRIPT) @build/o_files

$(BUILD_DIR)/%.o: %.s
	@echo Assembling $<
	$(QUIET) $(AS) $(ASFLAGS) -o $@ $<

$(BUILD_DIR)/%.o: %.c
	@echo Compiling $<
	$(QUIET) $(HOSTCC) -E $(addprefix -I ,$(INCLUDE_DIRS) $(SYSTEM_INCLUDE_DIRS)) -MMD -MF $(@:.o=.dep) -MT $@ $< >/dev/null
	$(QUIET) $(CC) $(CFLAGS) -c -o $@ $<
	$(QUIET) $(PYTHON) $(POSTPROC) $(PROCFLAGS) $@

$(BUILD_DIR)/src/melee/lb/lbvector.o: CFLAGS += -inline auto -fp_contract on

-include $(DEP_FILES)

#-------------------------------------------------------------------------------
# Tool Recipes
#-------------------------------------------------------------------------------

$(ELF2DOL): tools/elf2dol.c
	@echo Building tool $@
	$(QUIET) $(HOSTCC) $(HOSTCFLAGS) -o $@ $^

### Debug Print ###

print-% : ; $(info $* is a $(flavor $*) variable set to [$($*)]) @true
