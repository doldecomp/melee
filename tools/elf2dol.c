#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <sys/param.h>

#ifndef MAX
//! Get the maximum of two values
#define MAX(a, b)	(((a) > (b)) ? (a) : (b))
#endif

#ifndef MIN
//! Get the minimum of two values
#define MIN(a, b)	(((a) < (b)) ? (a) : (b))
#endif

#define ARRAY_COUNT(arr) (sizeof(arr)/sizeof((arr)[0]))

#define EI_NIDENT       16

typedef struct {
	unsigned char	e_ident[EI_NIDENT];
	uint16_t		e_type;
	uint16_t		e_machine;
	uint32_t		e_version;
	uint32_t		e_entry;
	uint32_t		e_phoff;
	uint32_t		e_shoff;
	uint32_t		e_flags;
	uint16_t		e_ehsize;
	uint16_t		e_phentsize;
	uint16_t		e_phnum;
	uint16_t		e_shentsize;
	uint16_t		e_shnum;
	uint16_t		e_shstrndx;
} Elf32_Ehdr;

#define EI_CLASS	4
#define EI_DATA	    5
#define EI_VERSION	6
#define EI_PAD		7
#define EI_NIDENT	16

#define ELFCLASS32	1
#define ELFDATA2MSB	2
#define EV_CURRENT	1

#define ET_EXEC		2
#define EM_PPC		20

typedef struct {
	uint32_t	p_type;
	uint32_t	p_offset;
	uint32_t	p_vaddr;
	uint32_t	p_paddr;
	uint32_t	p_filesz;
	uint32_t	p_memsz;
	uint32_t	p_flags;
	uint32_t	p_align;
} Elf32_Phdr;

#define PT_LOAD	1
#define PF_R	4
#define PF_W	2
#define PF_X	1

int verbosity = 0;

#if BYTE_ORDER == BIG_ENDIAN

#define swap32(x) (x)
#define swap16(x) (x)

#else

static inline uint32_t swap32(uint32_t v)
{
	return (v >> 24) |
	       ((v >> 8)  & 0x0000FF00) |
	       ((v << 8)  & 0x00FF0000) |
	       (v << 24);
}

static inline uint16_t swap16(uint16_t v)
{
	return (v >> 8) | (v << 8);
}

#endif /* BIG_ENDIAN */

typedef struct {

	uint32_t text_off[7];
	uint32_t data_off[11];
	uint32_t text_addr[7];
	uint32_t data_addr[11];
	uint32_t text_size[7];
	uint32_t data_size[11];
	uint32_t bss_addr;
	uint32_t bss_size;
	uint32_t entry;
	uint32_t pad[7];
} DOL_hdr;

#define HAVE_BSS 1

#define MAX_TEXT_SEGMENTS 7
#define MAX_DATA_SEGMENTS 11

#define DOL_ALIGNMENT 32

#define DOL_ALIGN(x) (((x) + DOL_ALIGNMENT - 1) & ~(DOL_ALIGNMENT - 1))

typedef struct {
	DOL_hdr header;
	int text_cnt;
	int data_cnt;
	uint32_t text_elf_off[7];
	uint32_t data_elf_off[11];
	uint32_t flags;
	FILE *elf;
} DOL_map;

void usage(const char *name)
{
	fprintf(stderr, "Usage: %s [-h] [-v] [--] elf-file dol-file\n", name);
	fprintf(stderr, " Convert an ELF file to a DOL file (by segments)\n");
	fprintf(stderr, " Options:\n");
	fprintf(stderr, "  -h    Show this help\n");
	fprintf(stderr, "  -v    Be more verbose (twice for even more)\n");
}

#define die(x) { fprintf(stderr, x "\n"); exit(1); }
#define perrordie(x) { perror(x); exit(1); }

void ferrordie(FILE *f, const char *str)
{
	if(ferror(f)) {
		fprintf(stderr, "Error while ");
		perrordie(str);
	} else if(feof(f)) {
		fprintf(stderr, "EOF while %s\n", str);
		exit(1);
	} else {
		fprintf(stderr, "Unknown error while %s\n", str);
		exit(1);
	}
}

void add_bss(DOL_map *map, uint32_t paddr, uint32_t memsz)
{
	if(map->flags & HAVE_BSS) {
		uint32_t curr_start = swap32(map->header.bss_addr);
		uint32_t curr_size = swap32(map->header.bss_size);
		if (paddr < curr_start)
			map->header.bss_addr = swap32(paddr);
		// Total BSS size should be the end of the last bss section minus the
		// start of the first bss section.
		if (paddr + memsz > curr_start + curr_size)
			map->header.bss_size = swap32(paddr + memsz - curr_start);
	} else {
		map->header.bss_addr = swap32(paddr);
		map->header.bss_size = swap32(memsz);
		map->flags |= HAVE_BSS;
	}
}

void read_elf_segments(DOL_map *map, const char *elf)
{
	int read, i;
	Elf32_Ehdr ehdr;
	
	if(verbosity >= 2)
		fprintf(stderr, "Reading ELF file...\n");
	
	map->elf = fopen(elf, "rb");
	if(!map->elf)
		perrordie("Could not open ELF file");
	
	read = fread(&ehdr, sizeof(ehdr), 1, map->elf);
	if(read != 1)
		ferrordie(map->elf, "reading ELF header");
	
	if(memcmp(&ehdr.e_ident[0], "\177ELF", 4))
		die("Invalid ELF header");
	if(ehdr.e_ident[EI_CLASS] != ELFCLASS32)
		die("Invalid ELF class");
	if(ehdr.e_ident[EI_DATA] != ELFDATA2MSB)
		die("Invalid ELF byte order");
	if(ehdr.e_ident[EI_VERSION] != EV_CURRENT)
		die("Invalid ELF ident version");
	if(swap32(ehdr.e_version) != EV_CURRENT)
		die("Invalid ELF version");
	if(swap16(ehdr.e_type) != ET_EXEC)
		die("ELF is not an executable");
	if(swap16(ehdr.e_machine) != EM_PPC)
		die("Machine is not PowerPC");
	if(!swap32(ehdr.e_entry))
		die("ELF has no entrypoint");
		
	map->header.entry = ehdr.e_entry;
	
	if(verbosity >= 2)
		fprintf(stderr, "Valid ELF header found\n");
	
	uint16_t phnum = swap16(ehdr.e_phnum);
	uint32_t phoff = swap32(ehdr.e_phoff);
	Elf32_Phdr *phdrs;
	
	if(!phnum || !phoff)
		die("ELF has no program headers");
	
	if(swap16(ehdr.e_phentsize) != sizeof(Elf32_Phdr))
		die("Invalid program header entry size");
	
	phdrs = malloc(phnum * sizeof(Elf32_Phdr));
	
	if(fseek(map->elf, phoff, SEEK_SET) < 0)
		ferrordie(map->elf, "reading ELF program headers");
	read = fread(phdrs, sizeof(Elf32_Phdr), phnum, map->elf);
	if(read != phnum)
		ferrordie(map->elf, "reading ELF program headers");
	
	for(i=0; i<phnum; i++) {
		if(swap32(phdrs[i].p_type) == PT_LOAD) {
			uint32_t offset = swap32(phdrs[i].p_offset);
			uint32_t paddr = swap32(phdrs[i].p_vaddr);
			uint32_t filesz = swap32(phdrs[i].p_filesz);
			uint32_t memsz = swap32(phdrs[i].p_memsz);
			uint32_t flags = swap32(phdrs[i].p_flags);
			if(memsz) {
				if(verbosity >= 2)
					fprintf(stderr, "PHDR %d: 0x%x [0x%x] -> 0x%08x [0x%x] flags 0x%x\n",
					        i, offset, filesz, paddr, memsz, flags);
				if(flags & PF_X) {
					// TEXT segment
					if(!(flags & PF_R))
						fprintf(stderr, "Warning: non-readable segment %d\n", i);
					if(flags & PF_W)
						fprintf(stderr, "Warning: writable and executable segment %d\n", i);
					if(filesz > memsz) {
							fprintf(stderr, "Error: TEXT segment %d memory size (0x%x) smaller than file size (0x%x)\n",
							                i, memsz, filesz);
							exit(1);
					} else if (memsz > filesz) {
						add_bss(map, paddr + filesz, memsz - filesz);
					}
					if(map->text_cnt >= MAX_TEXT_SEGMENTS) {
						die("Error: Too many TEXT segments");
					}
					map->header.text_addr[map->text_cnt] = swap32(paddr);
					map->header.text_size[map->text_cnt] = swap32(filesz);
					map->text_elf_off[map->text_cnt] = offset;
					map->text_cnt++;
				} else {
					// DATA or BSS segment
					if(!(flags & PF_R))
						fprintf(stderr, "Warning: non-readable segment %d\n", i);
					if(filesz == 0) {
						// BSS segment
						add_bss(map, paddr, memsz);
					} else {
						// DATA segment
						if(filesz > memsz) {
							fprintf(stderr, "Error: segment %d memory size (0x%x) is smaller than file size (0x%x)\n",
							        i, memsz, filesz);
							exit(1);
						}
						if(map->data_cnt >= MAX_DATA_SEGMENTS) {
							die("Error: Too many DATA segments");
						}
						map->header.data_addr[map->data_cnt] = swap32(paddr);
						map->header.data_size[map->data_cnt] = swap32(filesz);
						map->data_elf_off[map->data_cnt] = offset;
						map->data_cnt++;
					}
				}
			
			} else {
				if(verbosity >= 1)
					fprintf(stderr, "Skipping empty program header %d\n", i);
			}
		} else if(verbosity >= 1) {
			fprintf(stderr, "Skipping program header %d of type %d\n", i, swap32(phdrs[i].p_type));
		}
	}
	if(verbosity >= 2) {
		fprintf(stderr, "Segments:\n");
		for(i=0; i<map->text_cnt; i++) {
			fprintf(stderr, " TEXT %d: 0x%08x [0x%x] from ELF offset 0x%x\n",
			        i, swap32(map->header.text_addr[i]), swap32(map->header.text_size[i]),
			        map->text_elf_off[i]);
		}
		for(i=0; i<map->data_cnt; i++) {
			fprintf(stderr, " DATA %d: 0x%08x [0x%x] from ELF offset 0x%x\n",
			        i, swap32(map->header.data_addr[i]), swap32(map->header.data_size[i]),
			        map->data_elf_off[i]);
		}
		if(map->flags & HAVE_BSS)
			fprintf(stderr, " BSS segment: 0x%08x [0x%x]\n", swap32(map->header.bss_addr),
			        swap32(map->header.bss_size));
	}
}

void map_dol(DOL_map *map)
{
	uint32_t fpos;
	int i;
	
	if(verbosity >= 2)
		fprintf(stderr, "Laying out DOL file...\n");
	
	fpos = DOL_ALIGN(sizeof(DOL_hdr));
	
	for(i=0; i<map->text_cnt; i++) {
		if(verbosity >= 2)
			fprintf(stderr, " TEXT segment %d at 0x%x\n", i, fpos);
		map->header.text_off[i] = swap32(fpos);
		fpos = DOL_ALIGN(fpos + swap32(map->header.text_size[i]));
	}
	for(i=0; i<map->data_cnt; i++) {
		if(verbosity >= 2)
			fprintf(stderr, " DATA segment %d at 0x%x\n", i, fpos);
		map->header.data_off[i] = swap32(fpos);
		fpos = DOL_ALIGN(fpos + swap32(map->header.data_size[i]));
	}
	
	if(map->text_cnt == 0) {
		if(verbosity >= 1)
			fprintf(stderr, "Note: adding dummy TEXT segment to work around IOS bug\n");
		map->header.text_off[0] = swap32(DOL_ALIGN(sizeof(DOL_hdr)));
	}
	if(map->data_cnt == 0) {
		if(verbosity >= 1)
			fprintf(stderr, "Note: adding dummy DATA segment to work around IOS bug\n");
		map->header.data_off[0] = swap32(DOL_ALIGN(sizeof(DOL_hdr)));
	}
}

#define BLOCK (1024*1024)

void fcpy(FILE *dst, FILE *src, uint32_t dst_off, uint32_t src_off, uint32_t size)
{
	int left = size;
	int read;
	int written;
	int block;
	void *blockbuf;

	if(fseek(src, src_off, SEEK_SET) < 0)
		ferrordie(src, "reading ELF segment data");
	if(fseek(dst, dst_off, SEEK_SET) < 0)
		ferrordie(dst, "writing DOL segment data");
	
	blockbuf = malloc(MIN(BLOCK, left));
	
	while(left) {
		block = MIN(BLOCK, left);
		read = fread(blockbuf, 1, block, src);
		if(read != block) {
			free(blockbuf);
			ferrordie(src, "reading ELF segment data");
		}
		written = fwrite(blockbuf, 1, block, dst);
		if(written != block) {
			free(blockbuf);
			ferrordie(dst, "writing DOL segment data");
		}
		left -= block;
	}
	free(blockbuf);
}

void fpad(FILE *dst, uint32_t dst_off, uint32_t size)
{
	uint32_t i;

	if(fseek(dst, dst_off, SEEK_SET) < 0)
		ferrordie(dst, "writing DOL segment data");
	for(i=0; i<size; i++)
		fputc(0, dst);
}

void write_dol(DOL_map *map, const char *dol)
{
	FILE *dolf;
	int written;
	int i;

	if(verbosity >= 2)
		fprintf(stderr, "Writing DOL file...\n");
		
	dolf = fopen(dol, "wb");
	if(!dolf)
		perrordie("Could not open DOL file");
	
	if(verbosity >= 2) {
		fprintf(stderr, "DOL header:\n");
		for(i=0; i<MAX(1,map->text_cnt); i++)
			fprintf(stderr, " TEXT %d @ 0x%08x [0x%x] off 0x%x\n", i,
			        swap32(map->header.text_addr[i]), swap32(map->header.text_size[i]),
			        swap32(map->header.text_off[i]));
		for(i=0; i<MAX(1,map->data_cnt); i++)
			fprintf(stderr, " DATA %d @ 0x%08x [0x%x] off 0x%x\n", i,
			        swap32(map->header.data_addr[i]), swap32(map->header.data_size[i]),
			        swap32(map->header.data_off[i]));
		if(swap32(map->header.bss_addr) && swap32(map->header.bss_size))
			fprintf(stderr, " BSS @ 0x%08x [0x%x]\n", swap32(map->header.bss_addr),
			        swap32(map->header.bss_size));
		fprintf(stderr, " Entry: 0x%08x\n", swap32(map->header.entry));
		fprintf(stderr, "Writing DOL header...\n");
	}
	
	// Write DOL header with aligned text and data section sizes
	DOL_hdr aligned_header = map->header;
	for(i=0; i<ARRAY_COUNT(aligned_header.text_size); i++)
		aligned_header.text_size[i] = swap32(DOL_ALIGN(swap32(aligned_header.text_size[i])));
	for(i=0; i<ARRAY_COUNT(aligned_header.data_size); i++)
		aligned_header.data_size[i] = swap32(DOL_ALIGN(swap32(aligned_header.data_size[i])));
	written = fwrite(&aligned_header, sizeof(DOL_hdr), 1, dolf);
	if(written != 1)
		ferrordie(dolf, "writing DOL header");
	
	for(i=0; i<map->text_cnt; i++) {
		uint32_t size = swap32(map->header.text_size[i]);
		uint32_t padded_size = DOL_ALIGN(size);
		if(verbosity >= 2)
			fprintf(stderr, "Writing TEXT segment %d...\n", i);
		fcpy(dolf, map->elf, swap32(map->header.text_off[i]), map->text_elf_off[i], size);
		if (padded_size > size)
			fpad(dolf, swap32(map->header.text_off[i]) + size, padded_size - size);
	}
	for(i=0; i<map->data_cnt; i++) {
		uint32_t size = swap32(map->header.data_size[i]);
		uint32_t padded_size = DOL_ALIGN(size);
		if(verbosity >= 2)
			fprintf(stderr, "Writing DATA segment %d...\n", i);
		fcpy(dolf, map->elf, swap32(map->header.data_off[i]), map->data_elf_off[i], size);
		if (padded_size > size)
			fpad(dolf, swap32(map->header.data_off[i]) + size, padded_size - size);
	}
	
	if(verbosity >= 2)
		fprintf(stderr, "All done!\n");
	
	fclose(map->elf);
	fclose(dolf);
}

int main(int argc, char **argv)
{
	char **arg;

	if(argc < 2) {
		usage(argv[0]);
		return 1;
	}
	arg = &argv[1];
	argc--;

	while(argc && *arg[0] == '-') {
		if(!strcmp(*arg, "-h")) {
			usage(argv[0]);
			return 1;
		} else if(!strcmp(*arg, "-v")) {
			verbosity++;
		} else if(!strcmp(*arg, "--")) {
			arg++;
			argc--;
			break;
		} else {
			fprintf(stderr, "Unrecognized option %s\n", *arg);
			usage(argv[0]);
			return 1;
		}
		arg++;
		argc--;
	}
	if(argc < 2) {
		usage(argv[0]);
		exit(1);
	}

	const char *elf_file = arg[0];
	const char *dol_file = arg[1];

	DOL_map map;

	memset(&map, 0, sizeof(map));

	read_elf_segments(&map, elf_file);
	map_dol(&map);
	write_dol(&map, dol_file);
	
	return 0;
}
