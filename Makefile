ifneq ($(findstring MINGW,$(shell uname)),)
  WINDOWS := 1
endif
ifneq ($(findstring MSYS,$(shell uname)),)
  WINDOWS := 1
endif

GENERATE_MAP ?= 0
NON_MATCHING ?= 0
EPILOGUE_PROCESS ?= 1
SKIP_CHECK ?= 0

VERBOSE ?= 0
MAX_ERRORS ?= 0     # 0 = no maximum

ifeq ($(VERBOSE),0)
  QUIET := @
endif

#-------------------------------------------------------------------------------
# Files
#-------------------------------------------------------------------------------

TARGET := ssbm.us.1.2

BUILD_DIR := build/$(TARGET)
VANILLA_DIR := $(BUILD_DIR)/vanilla
PROFILE_DIR := $(BUILD_DIR)/profile

# Inputs
LDSCRIPT := ldscript.lcf

# Outputs
DOL     := $(BUILD_DIR)/main.dol
ELF     := $(DOL:.dol=.elf)
MAP     := $(BUILD_DIR)/GALE01.map

include obj_files.mk

O_FILES := $(INIT_O_FILES) $(EXTAB_O_FILES) $(EXTABINDEX_O_FILES) $(TEXT_O_FILES)

DEP_FILES := $(O_FILES:.o=.dep)

#-------------------------------------------------------------------------------
# Tools
#-------------------------------------------------------------------------------

MWCC_VERSION := 1.2.5
ifeq ($(EPILOGUE_PROCESS),1)
MWCC_EPI_VERSION := 1.2.5e
MWCC_EPI_EXE := mwcceppc.exe
endif
MWCC_LD_VERSION := 1.1

# Programs
ifeq ($(WINDOWS),1)
  WINE :=
else
  WINE ?= wine
  # Disable wine debug output for cleanliness
  export WINEDEBUG ?= -all
  # Default devkitPPC path
  DEVKITPPC ?= /opt/devkitpro/devkitPPC
endif
ifeq ($(shell uname),Darwin)
  SHA1SUM := shasum
else
  SHA1SUM := sha1sum
endif
AS      := $(DEVKITPPC)/bin/powerpc-eabi-as
CC      := $(WINE) tools/mwcc_compiler/$(MWCC_VERSION)/mwcceppc.exe
ifeq ($(EPILOGUE_PROCESS),1)
CC_EPI   = $(WINE) tools/mwcc_compiler/$(MWCC_EPI_VERSION)/$(MWCC_EPI_EXE)
endif
LD      := $(WINE) tools/mwcc_compiler/$(MWCC_LD_VERSION)/mwldeppc.exe
ELF2DOL := tools/elf2dol
HOSTCC  := cc
PYTHON  := python3

FRANK := tools/frank.py

# Options
INCLUDE_DIRS = $(*D)
SYSTEM_INCLUDE_DIRS := include include/dolphin src
#INCLUDES = -i $(*D) -I- -i include -i include/dolphin/ -i include/dolphin/mtx/ -i src
INCLUDES = $(addprefix -i ,$(INCLUDE_DIRS)) -I- $(addprefix -i ,$(SYSTEM_INCLUDE_DIRS))


ASFLAGS := -mgekko -I include
LDFLAGS := -fp hard -nodefaults
ifeq ($(GENERATE_MAP),1)
  LDFLAGS += -map $(MAP)
endif
CFLAGS  = -cwd source -Cpp_exceptions off -proc gekko -fp hard -fp_contract on -O4,p -enum int -nodefaults -inline auto $(INCLUDES) -maxerrors $(MAX_ERRORS)
ifeq ($(NON_MATCHING),1)
CFLAGS += -DNON_MATCHING
endif


$(BUILD_DIR)/src/melee/pl/player.c.o: CC_EPI := $(CC)
$(BUILD_DIR)/src/melee/lb/lbtime.c.o: CC_EPI := $(CC)

HOSTCFLAGS := -Wall -O3 -s

#-------------------------------------------------------------------------------
# Recipes
#-------------------------------------------------------------------------------

# Remove all built-in rules
.SUFFIXES:

.PHONY: default

### Default target ###

default: $(DOL)
ifeq ($(NON_MATCHING),1)
	@echo "Skipping checksum for non-matching build."
else ifeq ($(SKIP_CHECK),1)
	@echo "Skipping checksum for this build."
else
	$(QUIET) $(SHA1SUM) -c $(TARGET).sha1
endif

ALL_DIRS := $(sort $(dir $(O_FILES)))
ALL_DIRS += $(patsubst $(BUILD_DIR)/%,$(VANILLA_DIR)/%,$(ALL_DIRS)) \
            $(patsubst $(BUILD_DIR)/%,$(PROFILE_DIR)/%,$(ALL_DIRS))

# Make sure build directory exists before compiling anything
DUMMY != mkdir -p $(ALL_DIRS)

%.dol: %.elf $(ELF2DOL)
	@echo Converting $< to $@
	$(QUIET) $(ELF2DOL) $< $@
ifeq ($(GENERATE_MAP),1)
	$(QUIET) $(PYTHON) tools/calcprogress/calcprogress.py --dol $(DOL) --map $(MAP) --asm-obj-ext .s.o --old-map true
endif

clean:
	rm -f -d -r build $(ELF2DOL)

# ELF creation makefile instructions
$(ELF): $(O_FILES) $(LDSCRIPT)
	@echo Linking ELF $@
	$(QUIET) echo $(O_FILES) > build/o_files
	$(QUIET) $(LD) $(LDFLAGS) -o $@ -lcf $(LDSCRIPT) @build/o_files

$(BUILD_DIR)/%.s.o: %.s
	@echo Assembling $<
	$(QUIET) $(AS) $(ASFLAGS) -o $@ $<

$(BUILD_DIR)/%.c.dep: %.c
	$(QUIET) $(HOSTCC) -E $(addprefix -I ,$(INCLUDE_DIRS) $(SYSTEM_INCLUDE_DIRS)) -MMD -MF $(@:.o=.dep) \
		-MT "$(VANILLA_DIR)/$<.o $(PROFILE_DIR)/$<.o" $< >/dev/null

$(BUILD_DIR)/%.c.o: $(VANILLA_DIR)/%.c.o
	cp $< $@

$(VANILLA_DIR)/%.c.o: %.c $(BUILD_DIR)/%.c.dep
	@echo "Compiling (vanilla)" $<
	$(QUIET) $(CC) $(CFLAGS) -c -o $@ $<

# Overrides for targets using frank to simulate patched MWCC 1.2.5
ifeq ($(EPILOGUE_PROCESS),1)
$(PROFILE_DIR)/%.c.o: %.c $(BUILD_DIR)/%.c.dep
	@echo "Compiling (profile)" $<
	$(QUIET) $(CC_EPI) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/src/melee/%.c.o: $(VANILLA_DIR)/src/melee/%.c.o $(PROFILE_DIR)/src/melee/%.c.o $(FRANK)
	@echo Frank is fixing $@
	$(QUIET) $(PYTHON) $(FRANK) $(word 1,$^) $(word 2,$^) $@

$(BUILD_DIR)/src/sysdolphin/%.c.o: $(VANILLA_DIR)/src/sysdolphin/%.c.o $(PROFILE_DIR)/src/sysdolphin/%.c.o $(FRANK)
	@echo Frank is fixing $@
	$(QUIET) $(PYTHON) $(FRANK) $(word 1,$^) $(word 2,$^) $@
endif

-include $(DEP_FILES)

#-------------------------------------------------------------------------------
# Tool Recipes
#-------------------------------------------------------------------------------

$(ELF2DOL): tools/elf2dol.c
	@echo Building tool $@
	$(QUIET) $(HOSTCC) $(HOSTCFLAGS) -o $@ $^

### Debug Print ###

print-% : ; $(info $* is a $(flavor $*) variable set to [$($*)]) @true
