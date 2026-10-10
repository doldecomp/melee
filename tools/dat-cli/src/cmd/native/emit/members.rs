//! Field operations are selected during generation, not from runtime tags.
use super::*;
use super::super::generator::Kind;

impl Emitter<'_, '_> {
    pub(super) fn read_member(
        &mut self,
        c: &mut String,
        ident: &str,
        i: usize,
        m: &MemberRow,
    ) -> Result<()> {
        for annotation in &m.annotations {
            writeln!(c, "/* {annotation} */")?;
        }
        if m.bit_size != 0 {
            if let Place::Bits { field, .. } = &m.place {
                let signed = self.signed(m.ty);
                writeln!(
                    c,
                    "if (native) {ident}_{field}_set(native, dat_reader_extend(dat_reader_bits_at(a, offset, {}, {}), {}, {signed}));",
                    m.bit_offset, m.bit_size, m.bit_size
                )?;
            }
            return Ok(());
        }
        let Some(offset) = m.offset else {
            return Ok(());
        };
        if m.ty == NONE {
            return Ok(());
        }
        writeln!(
            c,
            "{{ uint32_t at = offset + 0x{offset:X}; void* field = native ? (char*) native + {} : NULL; DatParent here = {{ r, offset, 1 }}; const DatScope* outer = a->env;",
            native_offset(m)
        )?;
        let binding = self.member_binding(ident, i, m);
        if !m.binds.is_empty() {
            writeln!(
                c,
                "a->env = dat_reader_bind_scope(a, outer, {binding}, here, 0);"
            )?;
        }
        let count = m.count.as_ref().map(|e| self.expr(e));
        if let Some(expr) = &count {
            writeln!(
                c,
                "uint64_t count; DatContext ctx = {{ MODE_COUNT, r, offset, DAT_NONE, 0, a->env, 0, 0 }}; if (dat_reader_eval(a, &ctx, {expr}, &count)) {{ dat_reader_counted(a, at, {}, {}, count, {binding}, here, field); }} else {{",
                self.ty(m.ty),
                self.ty(m.type_tag)
            )?;
        }
        if m.type_tag != NONE {
            writeln!(
                c,
                "dat_reader_typed(a, at, {}, field, {});",
                self.ty(m.type_tag),
                native_size(m)
            )?;
        } else if let Some(script) = &m.script {
            let script = self.script(script);
            writeln!(
                c,
                "dat_reader_script(a, at, {}, {}, field);",
                self.ty(m.ty),
                script.strip_prefix(".script = ").unwrap()
            )?;
        } else if m.extent {
            writeln!(
                c,
                "dat_reader_extent(a, at, {}, {binding}, here, field);",
                self.ty(m.ty)
            )?;
        } else if let Some(expr) = &m.terminator {
            let expr = self.expr(expr);
            writeln!(
                c,
                "dat_reader_terminated(a, at, {}, field, {expr}, {});",
                self.ty(m.ty),
                m.terminator_length
            )?;
        } else {
            let arr = self.generator.types[m.ty as usize].resolved;
            let row = &self.generator.types[arr as usize];
            if !m.binds.is_empty()
                && row.kind == Kind::Array
                && row.target != NONE
            {
                let raw = row.target;
                let e = self.generator.types[raw as usize].resolved;
                if e != NONE {
                    writeln!(
                        c,
                        "for (uint32_t j = 0; j < {}; j++) {{ a->env = dat_reader_bind_scope(a, outer, {binding}, here, j); uint32_t pos = at + j * dat_reader_T(a, {})->size; void* element = field ? (char*) field + (size_t) j * dat_reader_T(a, {})->native_size : NULL; dat_reader_place_native(a, pos, {}, element); dat_reader_layout(a, pos, {}, element, here); }}",
                        row.count,
                        self.ty(e),
                        self.ty(e),
                        self.ty(e),
                        self.ty(raw)
                    )?;
                }
            } else {
                writeln!(
                    c,
                    "dat_reader_layout(a, at, {}, field, here);",
                    self.ty(m.ty)
                )?;
            }
        }
        if count.is_some() {
            c.push_str("}\n");
        }
        c.push_str("a->env = outer; }\n");
        Ok(())
    }

    pub(super) fn verify_member(
        &self,
        c: &mut String,
        ident: &str,
        m: &MemberRow,
    ) -> Result<()> {
        if m.bit_size != 0 {
            if let Place::Bits { field, .. } = &m.place {
                let signed = self.signed(m.ty);
                writeln!(
                    c,
                    "{{ uint64_t want = dat_reader_extend(dat_reader_bits_at(a, offset, {}, {}), {}, {signed}); uint64_t got = dat_reader_extend({ident}_{field}_get(native), {}, {signed}); if (want != got) dat_reader_mismatch(v, offset, \"bitfield\", want, got); }}",
                    m.bit_offset, m.bit_size, m.bit_size, m.bit_size
                )?;
            }
            return Ok(());
        }
        let Some(at) = m.offset else {
            return Ok(());
        };
        if m.ty == NONE || m.type_tag != NONE || m.script.is_some() || m.extent
        {
            return Ok(());
        }
        let native = native_offset(m);
        let arr = self.generator.types[m.ty as usize].resolved;
        let array = &self.generator.types[arr as usize];
        if m.count.is_some() && array.kind == Kind::Array {
            let e = self.generator.types[array.target as usize].resolved;
            if e != NONE {
                writeln!(
                    c,
                    "{{ uint64_t count; if (map_get(&a->array_counts, key2(offset + {at}, dat_reader_T(a, {})->id), &count)) {{ for (uint64_t j = 0; j < count; j++) dat_reader_verify(v, offset + {at} + j * dat_reader_T(a, {})->size, {}, (const char*) native + {native} + j * dat_reader_T(a, {})->native_size, depth + 1); }} else {{ dat_reader_verify(v, offset + {at}, {}, (const char*) native + {native}, depth + 1); }} }}",
                    self.ty(arr),
                    self.ty(e),
                    self.ty(e),
                    self.ty(e),
                    self.ty(m.ty)
                )?;
                return Ok(());
            }
        }
        writeln!(
            c,
            "dat_reader_verify(v, offset + {at}, {}, (const char*) native + {native}, depth + 1);",
            self.ty(m.ty)
        )?;
        Ok(())
    }

    pub(super) fn member_binding(
        &self,
        ident: &str,
        i: usize,
        m: &MemberRow,
    ) -> String {
        if m.binds.is_empty() {
            "NULL".into()
        } else {
            format!("{ident}_bind_{i}")
        }
    }
    pub(super) fn signed(&self, ty: i32) -> u8 {
        let r = self.generator.types[ty as usize].resolved;
        u8::from(self.generator.types[r as usize].is_signed)
    }
}
pub(super) fn native_offset(m: &MemberRow) -> String {
    match &m.place {
        Place::Field { record, field } => {
            format!("offsetof({record}, {field})")
        }
        Place::At { offset, .. } => offset.clone(),
        _ => "0".into(),
    }
}
pub(super) fn native_size(m: &MemberRow) -> String {
    match &m.place {
        Place::Field { record, field } => {
            format!("sizeof((({record}*) 0)->{field})")
        }
        Place::At { size, .. } => size.clone(),
        _ => "0".into(),
    }
}

impl Emitter<'_, '_> {
    pub(super) fn allocation(
        &mut self,
        c: &mut String,
        ident: &str,
        row: &TypeRow,
    ) -> Result<()> {
        let size = "t->native_size";
        if let Some((i, m)) = row.members.iter().enumerate().next_back()
            && (m.extent || m.count.is_some())
            && m.ty != NONE
        {
            let arr = self.generator.types[m.ty as usize].resolved;
            let array = &self.generator.types[arr as usize];
            let raw = array.target;
            let e = self.generator.types[raw as usize].resolved;
            if array.kind == Kind::Array && e != NONE {
                let at = m.offset.unwrap_or(0);
                let elem = self.ty(e);
                let array_ty = self.ty(arr);
                if let Some(expr) = &m.count {
                    let expr = self.expr(expr);
                    let binding = self.member_binding(ident, i, m);
                    writeln!(
                        c,
                        "DatParent here = {{ r, offset, 1 }}; const DatScope* env = dat_reader_bind_scope(a, a->env, {binding}, here, 0); DatContext ctx = {{ MODE_COUNT, r, offset, DAT_NONE, 0, env, 0, 0 }}; uint64_t n; if (!dat_reader_eval(a, &ctx, {expr}, &n)) n = {}; if (!dat_reader_array_count_fits(a, offset + {at}, {array_ty}, {elem}, n)) return {size};",
                        array.count
                    )?;
                } else {
                    writeln!(
                        c,
                        "uint64_t n = dat_reader_extent_bound(a, offset + {at}, dat_reader_T(a, {elem})->size);"
                    )?;
                }
                writeln!(
                    c,
                    "size_t end = {} + (size_t) n * dat_reader_T(a, {elem})->native_size; return end > {size} ? end : {size};",
                    native_offset(m)
                )?;
                return Ok(());
            }
        }
        writeln!(c, "return {size};")?;
        Ok(())
    }
    pub(super) fn read_union(
        &mut self,
        c: &mut String,
        ident: &str,
        row: &TypeRow,
    ) -> Result<()> {
        let plain = !row.has_pointers;
        if plain && row.members.iter().all(|m| m.cond.is_none()) {
            c.push_str("dat_reader_relocated_words(a, offset, (uint64_t) offset + t->size); dat_reader_convert(a, offset, r, native);\n");
            return Ok(());
        }
        self.selection(c, row)?;
        if plain {
            c.push_str("if (selected == CHOICE_AMBIGUOUS) { if ((uint64_t) offset + t->size > a->archive->size) { dat_reader_issue(a, ISSUE_OUT_OF_BOUNDS, offset, 0); break; } dat_reader_record_extent(a, offset, (uint64_t) offset + t->size); dat_reader_relocated_words(a, offset, (uint64_t) offset + t->size); dat_reader_convert(a, offset, r, native); break; }\n");
        }
        c.push_str("if (selected == CHOICE_MEMBER) { dat_reader_record_choice(a, offset, r, selected_index); switch (selected_index) {\n");
        for (i, m) in row.members.iter().enumerate() {
            writeln!(c, "case {i}: {{")?;
            if m.ty != NONE {
                let binding = self.member_binding(ident, i, m);
                let ty = self.ty(m.ty);
                writeln!(
                    c,
                    "dat_reader_typed_extent(a, offset, {ty}, 1); const DatScope* outer = a->env; a->env = dat_reader_bind_scope(a, outer, {binding}, parent, 0);"
                )?;
                if let Some(script) = &m.script {
                    let script = self.script(script);
                    writeln!(
                        c,
                        "dat_reader_script(a, offset, {ty}, {}, native);",
                        script.strip_prefix(".script = ").unwrap()
                    )?;
                } else if let Some(expr) = &m.terminator {
                    let expr = self.expr(expr);
                    writeln!(
                        c,
                        "dat_reader_terminated(a, offset, {ty}, native, {expr}, {});",
                        m.terminator_length
                    )?;
                } else {
                    writeln!(
                        c,
                        "dat_reader_layout(a, offset, {ty}, native, parent);"
                    )?;
                }
                c.push_str("a->env = outer;\n");
            }
            c.push_str("break; }\n");
        }
        c.push_str("} } else if (selected == CHOICE_AMBIGUOUS) { dat_reader_issue(a, ISSUE_AMBIGUOUS_UNION, offset, 0); }\n");
        Ok(())
    }
    pub(super) fn verify_union(
        &self,
        c: &mut String,
        row: &TypeRow,
    ) -> Result<()> {
        let fallback = if row.has_pointers {
            0
        } else {
            super::readers::largest(self.generator, row).map_or(0, |i| i + 1)
        };
        writeln!(
            c,
            "uint64_t index = {fallback}; map_get(&a->choices, key2(offset, t->id), &index); switch (index) {{"
        )?;
        for (i, m) in row.members.iter().enumerate() {
            if m.ty != NONE && m.script.is_none() {
                writeln!(
                    c,
                    "case {}: dat_reader_verify(v, offset, {}, native, depth + 1); break;",
                    i + 1,
                    self.ty(m.ty)
                )?;
            }
        }
        c.push_str("}\n");
        Ok(())
    }
}
