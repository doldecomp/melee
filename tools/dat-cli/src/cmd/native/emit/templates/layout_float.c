if (bits_has(&a->archive->reloc, offset, a->archive->size)) {
    dat_reader_issue(a, ISSUE_RELOCATED_SCALAR, offset, 0);
}
dat_reader_convert(a, offset, r, native);
