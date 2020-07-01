#-------------------------------------------------------------------------------
# Files
#-------------------------------------------------------------------------------

# Inputs
S_FILES := $(wildcard asm/*.s)
C_FILES := $(wildcard src/*.c)
LDSCRIPT := ldscript.lcf

# Outputs
DOL     := main.dol
ELF     := $(DOL:.dol=.elf)
MAP     := ssbm.map
O_FILES := $(S_FILES:.s=.o) $(C_FILES:.c=.o)

#-------------------------------------------------------------------------------
# Tools
#-------------------------------------------------------------------------------

# Programs
WINE    := wine
AS      := $(DEVKITPPC)/bin/powerpc-eabi-as
OBJCOPY := $(DEVKITPPC)/bin/powerpc-eabi-objcopy
CC      := $(WINE) mwcc_compiler/mwcceppc.exe
LD      := $(WINE) mwcc_compiler/mwldeppc.exe
ELF2DOL := tools/elf2dol
SHA1SUM := sha1sum

# Options
ASFLAGS := -mgekko -I include
LDFLAGS := -map $(MAP)
CFLAGS  := -Cpp_exceptions off -proc gekko -fp hard -O2,p -i include

#-------------------------------------------------------------------------------
# Recipes
#-------------------------------------------------------------------------------

.PHONY: tools

$(DOL): $(ELF) | tools
	$(ELF2DOL) $< $@
	$(SHA1SUM) -c ssbm.sha1

clean:
	rm -f $(DOL) $(ELF) $(O_FILES) $(MAP)
	$(MAKE) -C tools clean

tools:
	$(MAKE) -C tools

$(ELF): $(O_FILES) $(LDSCRIPT)
	$(LD) $(LDFLAGS) -o $@ -lcf $(LDSCRIPT) $(O_FILES)
# The Metrowerks linker doesn't generate physical addresses in the ELF program headers. This fixes it somehow.
	$(OBJCOPY) $@ $@

%.o: %.s
	$(AS) $(ASFLAGS) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

