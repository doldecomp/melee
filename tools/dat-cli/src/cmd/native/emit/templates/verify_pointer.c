
const void* p;
memcpy(&p, native, sizeof p);
uint32_t value = dat_reader_word(a, offset);
if (bits_has(&a->archive->reloc, offset, a->archive->size)) {
    uint64_t key;
    bool ok = p == a->archive->data + value ||
              (map_get(&a->offsets, (uint64_t) (uintptr_t) p, &key) &&
               (uint32_t) (key >> 32) == value);
    /* Elements of a native array */
    if (!ok && p != NULL) {
        int32_t e = dat_reader_pointee(a, t->target);
        ok = e != DAT_NONE && dat_reader_native_of(a, value, e) == p;
    }
    if (!ok) {
        int32_t pe = dat_reader_pointee(a, t->target);
        dat_reader_mismatch(v, offset,
                            p == NULL        ? "missing relocated pointer"
                            : pe != DAT_NONE ? dat_reader_T(a, pe)->name
                                             : "pointer",
                            value, (uint64_t) (uintptr_t) p);
        if (v->out != NULL &&
            map_get(&a->offsets, (uint64_t) (uintptr_t) p, &key))
        {
            int32_t e = dat_reader_pointee(a, t->target);
            fprintf(v->out, "  (to %s, which is 0x%X as %s)\n",
                    e != DAT_NONE ? dat_reader_T(a, e)->name : "?",
                    (uint32_t) (key >> 32),
                    dat_reader_type_name(a, (uint32_t) key));
        }
    }
} else if (p != dat_reader_unrelocated_value(a, offset, value)) {
    dat_reader_mismatch(v, offset, "unrelocated pointer", value,
                        (uint64_t) (uintptr_t) p);
}
