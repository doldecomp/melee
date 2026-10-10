
int32_t e = dat_reader_resolve(a, t->target);
if (e == DAT_NONE) {
    break;
}
for (uint32_t i = 0; i < t->count; i++) {
    /* Keep typedef tags, e.g. a counted list in each slot. */
    dat_reader_place_native(
        a, offset + i * dat_reader_T(a, e)->size, e,
        native ? (char*) native + (size_t) i * dat_reader_T(a, e)->native_size
               : NULL);
    dat_reader_layout(a, offset + i * dat_reader_T(a, e)->size, t->target,
                      native ? (char*) native +
                                   (size_t) i * dat_reader_T(a, e)->native_size
                             : NULL,
                      parent);
}
