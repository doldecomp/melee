/** @file Exercise the TARGET_PC game loader without validation callbacks. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fighters.h"
#include <melee/ft/types.h>
#include <sysdolphin/baselib/archive.h>
#include <sysdolphin/baselib/jobj.h>

#define CHECK(condition)                                                      \
    do {                                                                      \
        if (!(condition)) {                                                   \
            fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, #condition);   \
            abort();                                                          \
        }                                                                     \
    } while (0)

static uint32_t be32(const u8* p)
{
    return (uint32_t) p[0] << 24 | (uint32_t) p[1] << 16 |
           (uint32_t) p[2] << 8 | p[3];
}

static void put32(u8* p, uint32_t value)
{
    p[0] = value >> 24;
    p[1] = value >> 16;
    p[2] = value >> 8;
    p[3] = value;
}

static void test_dispatch(void)
{
    u8 bytes[0x20 + 0x44 + 8 + 16 + 8 + 21] = { 0 };
    put32(bytes, sizeof bytes);
    put32(bytes + 4, 0x44);
    put32(bytes + 8, 2);
    put32(bytes + 12, 2);
    put32(bytes + 16, 1);
    u8* data = bytes + 0x20;
    put32(data, UINT32_MAX);        /* extern chain terminator */
    put32(data + 0x14, 0x3FC00000); /* rotation.x = 1.5 */
    put32(data + 0x44, 8);          /* child points to offset zero */
    put32(data + 0x48, 0x40);       /* links points to offset zero */
    put32(data + 0x54, 0x40);       /* links public */
    put32(data + 0x58, 6);
    put32(data + 0x60, 12); /* external name */
    memcpy(data + 0x64, "joint\0links\0external\0", 21);
    HSD_Archive archive;
    CHECK(HSD_ArchiveParse(&archive, bytes, sizeof bytes) == 0);
    CHECK(archive.header.data_size == 0x44);
    CHECK(archive.public_info[1].offset == 0x40);
    CHECK(strcmp(HSD_ArchiveGetExtern(&archive, 0), "external") == 0);
    CHECK(HSD_ArchiveGetExtern(&archive, 1) == NULL);
    char first[] = "first", second[] = "second";
    HSD_ArchiveLocateExtern(&archive, "external", first);
    HSD_Joint* joint = HSD_ArchiveGetPublicAs(HSD_Joint, &archive, "joint");
    CHECK(joint && joint->child == joint && joint->rotation.x == 1.5f);
    CHECK(joint->class_name == first);
    HSD_Joint** links = HSD_ArchiveGetPublicAs(HSD_Joint*, &archive, "links");
    CHECK(links && *links == joint);
    CHECK(HSD_ArchiveGetPublicAs(HSD_Joint, &archive, "joint") == joint);
    HSD_ArchiveLocateExtern(&archive, "external", second);
    CHECK(joint->class_name == second);
    HSD_ArchiveLocateExtern(&archive, "external", NULL);
    CHECK(joint->class_name == NULL);
    CHECK(HSD_ArchiveGetPublicAs(HSD_Joint, &archive, "missing") == NULL);
    CHECK(HSD_ArchiveGetPublicTyped(&archive, "joint", "unknown") == NULL);
    CHECK(be32(data) == UINT32_MAX); /* input stays serialized */
    HSD_ArchiveReleaseNative(&archive);
    CHECK(HSD_ArchiveParse(&archive, bytes, 8) == -1);
}

static void test_fighters(const char* dir)
{
    for (size_t i = 0; i < sizeof fighters / sizeof *fighters; i++) {
        char path[2048];
        snprintf(path, sizeof path, "%s/%s", dir, fighters[i].file);
        FILE* file = fopen(path, "rb");
        CHECK(file);
        fseek(file, 0, SEEK_END);
        size_t size = (size_t) ftell(file);
        rewind(file);
        u8* bytes = malloc(size);
        CHECK(bytes && fread(bytes, 1, size, file) == size);
        fclose(file);
        HSD_Archive archive;
        CHECK(HSD_ArchiveParse(&archive, bytes, size) == 0);
        ftData* fighter =
            HSD_ArchiveGetPublicAs(ftData, &archive, fighters[i].name);
        CHECK(fighter && fighter->x0);
        /* Read the original archive tables independently of the adapter. */
        const u8* table = bytes + 0x20 + be32(bytes + 4) + 4 * be32(bytes + 8);
        const char* names =
            (const char*) table + 8 * (be32(bytes + 12) + be32(bytes + 16));
        uint32_t root = UINT32_MAX;
        for (uint32_t j = 0; j < be32(bytes + 12); j++) {
            if (!strcmp(names + be32(table + 8 * j + 4), fighters[i].name)) {
                root = be32(table + 8 * j);
            }
        }
        CHECK(root != UINT32_MAX);
        uint32_t bits = be32(bytes + 0x20 + be32(bytes + 0x20 + root));
        float want;
        memcpy(&want, &bits, sizeof want);
        CHECK(fighter->x0->walk_accel_mul == want);
        /* Mario's special attributes require the generated loader binding. */
        if (!strcmp(fighters[i].name, "ftDataMario")) {
            bits = be32(bytes + 0x20 + be32(bytes + 0x20 + root + 4));
            memcpy(&want, &bits, sizeof want);
            CHECK(fighter->ext_attr &&
                  fighter->ext_attr->mario.specials.vel_x_decay == want);
        }
        CHECK(HSD_ArchiveGetPublicAs(ftData, &archive, fighters[i].name) ==
              fighter);
        HSD_ArchiveReleaseNative(&archive);
        free(bytes);
    }
}

int main(int argc, char** argv)
{
    CHECK(argc == 2);
    test_dispatch();
    test_fighters(argv[1]);
    puts("ok: typed HSD dispatch, pointer tokens, cycles, externs and 27 "
         "fighters");
    return 0;
}
