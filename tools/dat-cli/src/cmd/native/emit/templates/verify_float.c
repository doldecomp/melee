if (t->size == 4 && t->native_size == 4) {
    uint32_t want = (uint32_t) dat_reader_bytes_at(a, offset, 4);
    uint32_t got = (uint32_t) dat_reader_load_uint(native, 4);
    if (got != want) {
        dat_reader_mismatch(v, offset, t->name, want, got);
    }
}
