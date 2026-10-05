/**
 * @file
 * The game's own types through the generated tables: each fighter's
 * `ftData`, read through C's member access, against the archive's bytes at
 * offsets written here by hand rather than from the tables.
 *
 * Usage: types <files dir>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "melee_dat.h"
#include <dat/archive.h>
#include <melee/ft/types.h>
#include <melee/it/it_3F14.h>
#include <melee/it/itCommonItems.h>
#include <melee/it/itemattrs.h>
#include <sysdolphin/baselib/aobj.h>
#include <sysdolphin/baselib/jobj.h>

static int failures;

#define CHECK(cond, ...)                                                      \
    do {                                                                      \
        if (!(cond)) {                                                        \
            printf("%s:%d: failed: %s: ", __FILE__, __LINE__, #cond);         \
            printf(__VA_ARGS__);                                              \
            printf("\n");                                                     \
            failures++;                                                       \
        }                                                                     \
    } while (0)

static uint32_t be32(const uint8_t* p)
{
    return (uint32_t) p[0] << 24 | (uint32_t) p[1] << 16 |
           (uint32_t) p[2] << 8 | p[3];
}

static float befloat(const uint8_t* p)
{
    uint32_t bits = be32(p);
    float f;
    memcpy(&f, &bits, sizeof f);
    return f;
}

static const struct {
    const char* file;
    const char* name;
} fighters[] = {
    { "PlMr.dat", "ftDataMario" },     { "PlFx.dat", "ftDataFox" },
    { "PlCa.dat", "ftDataCaptain" },   { "PlDk.dat", "ftDataDonkey" },
    { "PlKb.dat", "ftDataKirby" },     { "PlKp.dat", "ftDataKoopa" },
    { "PlLk.dat", "ftDataLink" },      { "PlSk.dat", "ftDataSeak" },
    { "PlNs.dat", "ftDataNess" },      { "PlPe.dat", "ftDataPeach" },
    { "PlPp.dat", "ftDataPopo" },      { "PlNn.dat", "ftDataNana" },
    { "PlPk.dat", "ftDataPikachu" },   { "PlSs.dat", "ftDataSamus" },
    { "PlYs.dat", "ftDataYoshi" },     { "PlPr.dat", "ftDataPurin" },
    { "PlMt.dat", "ftDataMewtwo" },    { "PlLg.dat", "ftDataLuigi" },
    { "PlMs.dat", "ftDataMars" },      { "PlZd.dat", "ftDataZelda" },
    { "PlCl.dat", "ftDataClink" },     { "PlDr.dat", "ftDataDrmario" },
    { "PlFc.dat", "ftDataFalco" },     { "PlPc.dat", "ftDataPichu" },
    { "PlGw.dat", "ftDataGamewatch" }, { "PlGn.dat", "ftDataGanon" },
    { "PlFe.dat", "ftDataEmblem" },
};

static unsigned char* read_file(const char* path, size_t* size)
{
    FILE* f = fopen(path, "rb");
    if (f == NULL) {
        return NULL;
    }
    fseek(f, 0, SEEK_END);
    long n = ftell(f);
    fseek(f, 0, SEEK_SET);
    unsigned char* bytes = malloc(n > 0 ? (size_t) n : 1);
    if (bytes == NULL || fread(bytes, 1, (size_t) n, f) != (size_t) n) {
        fclose(f);
        free(bytes);
        return NULL;
    }
    fclose(f);
    *size = (size_t) n;
    return bytes;
}

/// The offset of the public symbol `name` in the archive's file.
static int public_offset(const uint8_t* file, const char* name,
                         uint32_t* offset)
{
    uint32_t data = be32(file + 4), relocs = be32(file + 8),
             publics = be32(file + 12), externs = be32(file + 16);
    const uint8_t* table = file + 0x20 + data + 4 * relocs;
    const char* names = (const char*) table + 8 * publics + 8 * externs;
    for (uint32_t i = 0; i < publics; i++) {
        if (strcmp(names + be32(table + 8 * i + 4), name) == 0) {
            *offset = be32(table + 8 * i);
            return 1;
        }
    }
    return 0;
}

/// Load the item table through its public root so the kind bindings select
/// the food and mushroom views, then check their nested native pointers.
static void test_common_items(const char* dir)
{
    char path[2048];
    snprintf(path, sizeof path, "%s/ItCo.dat", dir);
    size_t size;
    unsigned char* bytes = read_file(path, &size);
    CHECK(bytes != NULL, "%s", path);
    if (bytes == NULL) {
        return;
    }
    uint32_t root;
    if (!public_offset(bytes, "itPublicData", &root)) {
        CHECK(false, "%s: itPublicData missing", path);
        free(bytes);
        return;
    }
    const char* error = NULL;
    DatArchive* a = dat_open(&melee_dat_schema, bytes, size, &error);
    CHECK(a != NULL, "%s: %s", path, error);
    const uint8_t* data = bytes + 0x20;
    uint32_t table = be32(data + root + 4);
    uint32_t article = be32(data + table + 4 * It_Kind_Foods);
    uint32_t attrs = be32(data + article + 4);
    it_804D6D20_t* items =
        a ? dat_public(a, "itPublicData", DAT_TYPE_it_804D6D20_t) : NULL;
    CHECK(items != NULL && items->x4 != NULL, "%s", path);
    Article* food_article =
        items != NULL && items->x4 != NULL ? items->x4[It_Kind_Foods] : NULL;
    itFoodsAttributes* foods =
        food_article != NULL && food_article->x4_specialAttributes != NULL
            ? &food_article->x4_specialAttributes->foods
            : NULL;
    CHECK(foods != NULL, "%s", path);
    if (foods != NULL) {
        CHECK(foods->count == (int32_t) be32(data + attrs), "%s", path);
        CHECK(foods->count > 1, "%s", path);
        for (int32_t i = 0; i < foods->count; i++) {
            const uint8_t* entry = data + attrs + 4 + i * 16;
            CHECK(foods->entries[i].heal_amount == (int32_t) be32(entry + 4),
                  "food %d", i);
            CHECK(foods->entries[i].offset.x == befloat(entry + 8), "food %d",
                  i);
            CHECK(foods->entries[i].offset.y == befloat(entry + 12), "food %d",
                  i);
            CHECK(foods->entries[i].joint != NULL, "food %d", i);
            if (foods->entries[i].joint != NULL) {
                CHECK(foods->entries[i].joint->flags ==
                          be32(data + be32(entry) + 4),
                      "food %d", i);
            }
        }
    }
    if (items != NULL && items->x4 != NULL) {
        static const ItemKind kinds[] = { It_Kind_Kinoko, It_Kind_DKinoko };
        for (size_t i = 0; i < sizeof kinds / sizeof *kinds; i++) {
            ItemKind kind = kinds[i];
            uint32_t offset = be32(data + table + 4 * kind);
            uint32_t special = be32(data + offset + 4);
            Article* mushroom = items->x4[kind];
            CHECK(mushroom != NULL && mushroom->x4_specialAttributes != NULL,
                  "mushroom %u", kind);
            if (mushroom == NULL || mushroom->x4_specialAttributes == NULL) {
                continue;
            }
            const KinokoAttrs* native =
                &mushroom->x4_specialAttributes->kinoko;
            CHECK(native->x0 == befloat(data + special), "mushroom %u", kind);
            CHECK(native->x4 == befloat(data + special + 4), "mushroom %u",
                  kind);
            for (uint32_t j = 0; j < 2; j++) {
                uint32_t anim = be32(data + special + 8 + 4 * j);
                CHECK(native->x8[j] != NULL, "mushroom %u anim %u", kind, j);
                if (native->x8[j] != NULL) {
                    CHECK(native->x8[j]->flags == be32(data + anim + 0x10),
                          "mushroom %u anim %u", kind, j);
                }
            }
        }
    }
    if (a != NULL) {
        CHECK(dat_verify(a, NULL) == 0, "%s", path);
    }
    dat_close(a);
    free(bytes);
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        fprintf(stderr, "usage: %s <files dir>\n", argv[0]);
        return 2;
    }
    test_common_items(argv[1]);
    size_t checked = 0;
    for (size_t i = 0; i < sizeof fighters / sizeof *fighters; i++) {
        char path[2048];
        snprintf(path, sizeof path, "%s/%s", argv[1], fighters[i].file);
        size_t size;
        unsigned char* bytes = read_file(path, &size);
        CHECK(bytes != NULL, "%s", path);
        if (bytes == NULL) {
            continue;
        }
        const uint8_t* data = bytes + 0x20;
        uint32_t root;
        CHECK(public_offset(bytes, fighters[i].name, &root), "%s",
              fighters[i].name);
        const char* error = NULL;
        DatArchive* a = dat_open(&melee_dat_schema, bytes, size, &error);
        CHECK(a != NULL, "%s: %s", path, error);
        ftData* fd =
            a ? dat_public(a, fighters[i].name, DAT_TYPE_ftData) : NULL;
        CHECK(fd != NULL && fd->x0 != NULL, "%s", fighters[i].name);
        if (fd != NULL && fd->x0 != NULL) {
            /* ftData::x0 at +0 points to the attributes, whose walk
               acceleration is at +0, ground friction at +0x18 and initial
               dash velocity at +0x1C */
            const uint8_t* attrs = data + be32(data + root);
            CHECK(fd->x0->walk_accel_mul == befloat(attrs), "%s",
                  fighters[i].name);
            CHECK(fd->x0->ground_friction == befloat(attrs + 0x18), "%s",
                  fighters[i].name);
            CHECK(fd->x0->dash_initial_velocity == befloat(attrs + 0x1C), "%s",
                  fighters[i].name);
            /* The same native object however it's reached */
            CHECK(dat_public(a, fighters[i].name, DAT_TYPE_ftData) == fd, "%s",
                  fighters[i].name);
            checked++;
        }
        dat_close(a);
        free(bytes);
    }
    printf("%s: %zu fighters (%zu-bit %s-endian)\n",
           failures ? "FAILED" : "ok", checked, sizeof(void*) * 8,
           *(const unsigned char*) &(const uint16_t){ 1 } ? "little" : "big");
    return failures ? 1 : 0;
}
