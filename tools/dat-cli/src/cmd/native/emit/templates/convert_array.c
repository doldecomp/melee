
int32_t e = dat_reader_resolve(a, t->target);
if (e == DAT_NONE) {
    break;
}
for (uint32_t i = 0; i < t->count; i++) {
    dat_reader_convert(a, offset + i * dat_reader_T(a, e)->size, e,
                       (char*) native +
                           (size_t) i * dat_reader_T(a, e)->native_size);
}
