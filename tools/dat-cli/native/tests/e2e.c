/**
 * @file
 * End to end: walk every archive `melee-dat native expect` lists, from the
 * game's files, and compare what this library reaches with what
 * `melee-dat`'s walker does. Every object converted is then read back and
 * checked against the data it came from.
 *
 * Usage: e2e <expect.txt> <files dir> [max mismatches to print]
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tables.h"
#include <dat/archive.h>

#define MAX_ARCHIVES 256

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

/// A line, without its newline, in a buffer that grows; `NULL` at the end.
static char* read_line(FILE* f, char** buf, size_t* cap)
{
    size_t len = 0;
    int c;
    while ((c = fgetc(f)) != EOF && c != '\n') {
        if (len + 1 >= *cap) {
            *cap = *cap ? *cap * 2 : 256;
            *buf = realloc(*buf, *cap);
        }
        (*buf)[len++] = (char) c;
    }
    if (c == EOF && len == 0) {
        return NULL;
    }
    if (*cap == 0) {
        *cap = 256;
        *buf = realloc(*buf, *cap);
    }
    (*buf)[len] = '\0';
    return *buf;
}

typedef struct Lines {
    char** items;
    size_t len, cap;
} Lines;

static void push_line(Lines* l, const char* line)
{
    if (l->len == l->cap) {
        l->cap = l->cap ? l->cap * 2 : 64;
        l->items = realloc(l->items, l->cap * sizeof(char*));
    }
    l->items[l->len++] = strcpy(malloc(strlen(line) + 1), line);
}

static void clear_lines(Lines* l)
{
    for (size_t i = 0; i < l->len; i++) {
        free(l->items[i]);
    }
    l->len = 0;
}

typedef struct Totals {
    size_t archives, failed, mismatched, unverified, missing;
    long budget;
} Totals;

/// Compare one archive's trace with what was expected of it.
static void check(Totals* t, const char* name, const Lines* want,
                  const char* dir)
{
    char file[1024];
    size_t at = 0;
    const char* sep = strchr(name, '@');
    size_t len = sep ? (size_t) (sep - name) : strlen(name);
    snprintf(file, sizeof file, "%.*s", (int) len, name);
    if (sep != NULL) {
        at = strtoull(sep + 1, NULL, 16);
    }
    char path[2048];
    snprintf(path, sizeof path, "%s/%s", dir, file);
    size_t size;
    unsigned char* bytes = read_file(path, &size);
    if (bytes == NULL) {
        printf("%s: can't read %s\n", name, path);
        t->missing++;
        return;
    }
    DatArchive* archives[MAX_ARCHIVES];
    size_t offsets[MAX_ARCHIVES];
    const char* error = NULL;
    int n = dat_open_packed(&melee_dat_schema, bytes, size, archives, offsets,
                            MAX_ARCHIVES, &error);
    free(bytes);
    if (n < 0) {
        printf("%s: %s\n", name, error);
        t->failed++;
        return;
    }
    t->archives++;
    for (int i = 0; i < n; i++) {
        if (offsets[i] != at) {
            continue;
        }
        dat_load_roots(archives[i], file, (uint32_t) i);
        FILE* out = tmpfile();
        dat_trace(archives[i], out, DAT_TRACE_ALL);
        rewind(out);
        Lines got = { 0 };
        char* buf = NULL;
        size_t cap = 0;
        for (char* line; (line = read_line(out, &buf, &cap)) != NULL;) {
            push_line(&got, line);
        }
        fclose(out);
        free(buf);
        /* Both are sorted the same way, line by line */
        size_t w = 0, g = 0;
        bool differs = false;
        while (w < want->len || g < got.len) {
            int cmp = w == want->len ? 1
                      : g == got.len ? -1
                                     : strcmp(want->items[w], got.items[g]);
            if (cmp == 0) {
                w++, g++;
                continue;
            }
            differs = true;
            if (t->budget-- > 0) {
                printf("%s: %s %s\n", name, cmp < 0 ? "missing" : "extra",
                       cmp < 0 ? want->items[w] : got.items[g]);
            }
            if (cmp < 0) {
                w++;
            } else {
                g++;
            }
        }
        if (differs) {
            t->mismatched++;
        }
        size_t bad = dat_verify(archives[i], t->budget > 0 ? stdout : NULL);
        if (bad > 0) {
            printf("%s: %zu don't read back\n", name, bad);
            t->unverified++;
            t->budget -= (long) bad;
        }
        clear_lines(&got);
        free(got.items);
    }
    for (int i = 0; i < n; i++) {
        dat_close(archives[i]);
    }
}

int main(int argc, char** argv)
{
    if (argc < 3) {
        fprintf(stderr, "usage: %s <expect.txt> <files dir> [max]\n", argv[0]);
        return 2;
    }
    FILE* expect = fopen(argv[1], "r");
    if (expect == NULL) {
        perror(argv[1]);
        return 2;
    }
    Totals t = { 0 };
    t.budget = argc > 3 ? atol(argv[3]) : 50;
    Lines want = { 0 };
    char name[1024] = "";
    char* buf = NULL;
    size_t cap = 0;
    for (char* line; (line = read_line(expect, &buf, &cap)) != NULL;) {
        if (strncmp(line, "archive ", 8) == 0) {
            if (name[0] != '\0') {
                check(&t, name, &want, argv[2]);
            }
            clear_lines(&want);
            snprintf(name, sizeof name, "%s", line + 8);
        } else {
            push_line(&want, line);
        }
    }
    if (name[0] != '\0') {
        check(&t, name, &want, argv[2]);
    }
    fclose(expect);
    free(buf);
    printf("%zu archives: %zu differ from the walker, %zu don't read back, "
           "%zu failed to open, %zu missing (%zu-bit %s-endian)\n",
           t.archives, t.mismatched, t.unverified, t.failed, t.missing,
           sizeof(void*) * 8,
           *(const unsigned char*) &(const uint16_t){ 1 } ? "little" : "big");
    return t.mismatched || t.unverified || t.failed || t.missing ? 1 : 0;
}
