
uint32_t ns = t->native_size ? t->native_size : t->size;
uint64_t want = dat_reader_extend(dat_reader_bytes_at(a, offset, t->size),
                                  8 * t->size, t->is_signed);
if (ns < 8) {
    want &= (1ull << (8 * ns)) - 1;
}
uint64_t got = dat_reader_load_uint(native, ns);
if (got != want) {
    dat_reader_mismatch(v, offset, t->name, want, got);
}
