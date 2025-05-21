GENERATE_MAP ?= 0
SKIP_CHECK ?= 0
REQUIRE_PROTOS ?= 1
MSG_STYLE ?= gcc
WARN_ERROR ?= 1

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
MWCC_TRK_VERSION := 1.1p1
MWCC_EPI_VERSION := 1.2.5n
MWCC_LD_VERSION := 1.3.2

# Programs
ifeq ($(OS),Windows_NT)
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

ifeq ($(OS),Windows_NT)
	AS := $(WINE) tools/mwcc_compiler/powerpc-eabi-as.exe
else
	AS := $(DEVKITPPC)/bin/powerpc-eabi-as
endif

CC      := $(WINE) tools/mwcc_compiler/$(MWCC_VERSION)/mwcceppc.exe
CC_TRK  := $(WINE) tools/mwcc_compiler/$(MWCC_TRK_VERSION)/mwcceppc.exe
CC_EPI  := $(WINE) tools/mwcc_compiler/$(MWCC_EPI_VERSION)/mwcceppc.exe
LD      := $(WINE) tools/mwcc_compiler/$(MWCC_LD_VERSION)/mwldeppc.exe
ELF2DOL := tools/elf2dol
HOSTCC  := gcc
PYTHON  := python
FORMAT  := clang-format -i -style=file

# Options
INCLUDE_DIRS = src/melee src/melee/ft/chara
# TODO dolphin and sysdolphin as system includes
#      Then fix include statements to use quotes for other paths
#      And make sure that all tools understand this distinction.
SYSTEM_INCLUDE_DIRS := src src/MSL src/Runtime src/sysdolphin
INCLUDES = $(addprefix -i ,$(INCLUDE_DIRS)) -I- $(addprefix -i ,$(SYSTEM_INCLUDE_DIRS))


ASFLAGS := -mgekko -I src
LDFLAGS := -fp hard -nodefaults
ifeq ($(GENERATE_MAP),1)
	LDFLAGS += -map $(MAP)
endif

# TODO:-W all

CFLAGS = -msgstyle $(MSG_STYLE) \
		-nowraplines \
		-cwd source \
		-Cpp_exceptions off \
		-proc gekko \
		-fp hardware \
		-align powerpc \
		-fp_contract on \
		-O4,p \
		-enum int \
		-nodefaults \
		-inline auto \
		-pragma "cats off" \
		-pragma "warn_notinlined off" \
		-RTTI off \
		-str reuse \
		-maxerrors $(MAX_ERRORS) \
		$(INCLUDES)

ifeq ($(REQUIRE_PROTOS),1)
	CFLAGS += -requireprotos
endif

ifeq ($(MAX_ERRORS),0)
	CFLAGS += -nofail
endif

ifeq ($(WARN_ERROR),1)
	CFLAGS += -warn iserror
endif

ifeq ($(VERBOSE),1)
	CFLAGS += -verbose
endif

HOSTCFLAGS := -Wall -O3 -s

#-------------------------------------------------------------------------------
# Recipes
#-------------------------------------------------------------------------------

# Remove all built-in rules
.SUFFIXES:

.PHONY: default format clean

### Default target ###

default: $(DOL)
ifeq ($(SKIP_CHECK),1)
	@echo "Skipping checksum for this build."
else
	$(QUIET) $(SHA1SUM) -c $(TARGET).sha1
endif

# clang-format all source files
format:
	$(QUIET) find src -type f \( -name '*.c' -o -name '*.h' \) -exec $(FORMAT) {} +
	$(QUIET) tools/newlines.sh

clean:
	rm -f -d -r $(BUILD_DIR) build/o_files $(ELF2DOL)

ALL_DIRS := $(sort $(dir $(O_FILES)))

# Make sure build directory exists before compiling anything
DUMMY != mkdir -p $(ALL_DIRS)

%.dol: %.elf $(ELF2DOL)
	@echo Converting $< to $@
	$(QUIET) $(ELF2DOL) $< $@
ifeq ($(GENERATE_MAP),1)
	$(QUIET) $(PYTHON) tools/calcprogress/calcprogress.py --dol $(DOL) --map $(MAP) --asm-obj-ext .s.o --old-map true
endif

# ELF creation makefile instructions
$(ELF): $(O_FILES) $(LDSCRIPT) obj_files.mk
	@echo Linking ELF $@
	$(file >build/o_files, $(O_FILES))
	$(QUIET) $(LD) $(LDFLAGS) -o $@ -lcf $(LDSCRIPT) @build/o_files

$(BUILD_DIR)/%.s.o: %.s
	@echo Assembling $<
	$(QUIET) $(AS) $(ASFLAGS) -o $@ $<

$(BUILD_DIR)/%.c.dep: %.c
	$(QUIET) $(HOSTCC) -E $(addprefix -I ,$(INCLUDE_DIRS) $(SYSTEM_INCLUDE_DIRS)) -MMD -MF $(@:.o=.dep) \
		-MT "$(BUILD_DIR)/$<.o" $< >/dev/null

$(BUILD_DIR)/%.c.o: %.c $(BUILD_DIR)/%.c.dep
	@echo "Compiling " $<
	$(QUIET) $(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/src/melee/%.c.o: CC := $(CC_EPI)
$(BUILD_DIR)/src/sysdolphin/%.c.o: CC := $(CC_EPI)
$(BUILD_DIR)/src/dolphin/card/%.c.o: CC := $(CC_EPI)
$(BUILD_DIR)/src/dolphin/hio/%.c.o: CC := $(CC_EPI)
$(BUILD_DIR)/src/dolphin/pad/%.c.o: CC := $(CC_EPI)
$(BUILD_DIR)/src/MetroTRK/%.c.o: CC := $(CC_TRK)

-include $(DEP_FILES)

#-------------------------------------------------------------------------------
# Tool Recipes
#-------------------------------------------------------------------------------

$(ELF2DOL): tools/elf2dol.c
	@echo Building tool $@
	$(QUIET) $(HOSTCC) $(HOSTCFLAGS) -o $@ $^

### Debug Print ###

print-% : ; $(info $* is a $(flavor $*) variable set to [$($*)]) @true
