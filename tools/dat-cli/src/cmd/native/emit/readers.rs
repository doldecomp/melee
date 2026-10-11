//! Emit executable conversion and traversal for each DWARF type.
use super::*;
use super::members::native_offset;
use super::super::generator::Kind;

impl Emitter<'_, '_> {
    pub(super) fn readers(
        &mut self,
        c: &mut String,
        index: usize,
        row: &TypeRow,
    ) -> Result<()> {
        let ident = self.idents[index].clone();
        let r = row.resolved;
        let resolved = &self.generator.types[r as usize];
        let rt = self.ty(r);

        for (what, signature) in [
            ("convert", "DatArchive* a, uint32_t offset, void* native"),
            ("fits", "const DatArchive* a, uint32_t offset"),
            (
                "field",
                "const DatArchive* a, uint32_t base, int32_t name, uint64_t* out",
            ),
            (
                "union_field",
                "const DatArchive* a, uint32_t base, int32_t name, uint64_t* out",
            ),
            ("allocation_size", "DatArchive* a, uint32_t offset"),
            (
                "verify",
                "DatVerify* v, uint32_t offset, const void* native, int depth",
            ),
            (
                "read",
                "DatArchive* a, uint32_t offset, void* native, const DatParent* parent_arg",
            ),
        ] {
            let ret = match what {
                "fits" | "field" | "union_field" => "int",
                "allocation_size" => "size_t",
                _ => "void",
            };
            if what == "verify" {
                c.push_str("#ifdef DAT_NATIVE_TESTING\n");
            }
            writeln!(c, "static {ret} {ident}_{what}({signature}) {{")?;
            if what == "verify" {
                c.push_str("    const DatArchive* a = v->a;\n");
            }
            writeln!(
                c,
                "    const int32_t r = {rt};\n    const DatType* t = dat_reader_T(a, r);"
            )?;
            // Storage and readback use the resolved shape. Reading retains
            // the original type so typedef annotations are still applied.
            if r != index as i32
                && matches!(
                    what,
                    "convert" | "fits" | "allocation_size" | "verify"
                )
            {
                let args = match what {
                    "convert" => "a, offset, native",
                    "fits" | "allocation_size" => "a, offset",
                    _ => "v, offset, native, depth",
                };
                let ret = if matches!(what, "fits" | "allocation_size") {
                    "return "
                } else {
                    ""
                };
                writeln!(c, "    {ret}t->{what}({args});\n}}\n")?;
                if what == "verify" {
                    c.push_str("#endif\n");
                }
                continue;
            }
            c.push_str("do {\n");
            match what {
                "convert" => self.convert_reader(c, &ident, resolved)?,
                "fits" => self.fits_reader(c, resolved)?,
                "field" => self.field_reader(c, row)?,
                "union_field" => self.union_field_reader(c, row)?,
                "allocation_size" => self.allocation(c, &ident, resolved)?,
                "verify" => self.verify_reader(c, &ident, resolved)?,
                "read" => self.read_reader(c, index, row)?,
                _ => unreachable!(),
            }
            c.push_str("} while (0);\n}\n\n");
            if what == "verify" {
                c.push_str("#endif\n");
            }
        }
        Ok(())
    }

    fn convert_reader(
        &self,
        c: &mut String,
        ident: &str,
        row: &TypeRow,
    ) -> Result<()> {
        match row.kind {
            Kind::Int => {
                writeln!(
                    c,
                    "dat_reader_integer(a, offset, {}, {}, {}, native);",
                    row.size,
                    row.native_size,
                    u8::from(row.is_signed)
                )?;
            }
            Kind::Float => {
                writeln!(
                    c,
                    "dat_reader_float(a, offset, {}, {}, native);",
                    row.size, row.native_size
                )?;
            }
            Kind::Struct => {
                for m in &row.members {
                    if m.bit_size != 0 {
                        if let Place::Bits { field, .. } = &m.place {
                            writeln!(
                                c,
                                "{ident}_{field}_set(native, dat_reader_extend(dat_reader_bits_at(a, offset, {}, {}), {}, {}));",
                                m.bit_offset,
                                m.bit_size,
                                m.bit_size,
                                self.signed(m.ty)
                            )?;
                        }
                    } else if let Some(at) = m.offset
                        && m.ty != NONE
                    {
                        writeln!(
                            c,
                            "dat_reader_convert(a, offset + {at}, {}, (char*) native + {});",
                            self.ty(m.ty),
                            native_offset(m)
                        )?;
                    }
                }
            }
            Kind::Union => {
                if let Some(i) = largest(self.generator, row) {
                    writeln!(
                        c,
                        "dat_reader_convert(a, offset, {}, native);",
                        self.ty(row.members[i].ty)
                    )?;
                }
            }
            Kind::Array => {
                c.push_str(include_str!("templates/convert_array.c"))
            }
            _ => {}
        }
        Ok(())
    }

    fn fits_reader(&self, c: &mut String, row: &TypeRow) -> Result<()> {
        match row.kind {
            Kind::Pointer => {
                c.push_str(include_str!("templates/fits_pointer.c"))
            }
            Kind::Int | Kind::Float => {
                c.push_str("return !bits_has(&a->archive->reloc, offset, a->archive->size);\n");
            }
            Kind::Struct => {
                for m in &row.members {
                    if m.bit_size == 0
                        && let Some(at) = m.offset
                        && m.ty != NONE
                    {
                        writeln!(
                            c,
                            "if (!dat_reader_fits(a, offset + {at}, {})) return 0;",
                            self.ty(m.ty)
                        )?;
                    }
                }
                c.push_str("return 1;\n");
            }
            Kind::Array => c.push_str(include_str!("templates/fits_array.c")),
            _ => c.push_str("return 1;\n"),
        }
        Ok(())
    }

    fn field_reader(&mut self, c: &mut String, row: &TypeRow) -> Result<()> {
        if matches!(row.kind, Kind::Struct | Kind::Union) {
            for m in &row.members {
                let Some(name) = &m.name else { continue };
                let Some(at) = m.offset else { continue };
                if m.ty == NONE {
                    continue;
                }
                let n = self.name(name);
                let raw = &self.generator.types[m.ty as usize];
                let resolved = &self.generator.types[raw.resolved as usize];
                let floating = u8::from(resolved.kind == Kind::Float);
                writeln!(
                    c,
                    "if (name == {n}) return dat_reader_read_field(a, (uint64_t) base + {at}, {}, {floating}, out);",
                    raw.size
                )?;
                // Preserve the caller's lookup order for nested paths.
                let len = name.len();
                writeln!(
                    c,
                    "if (strncmp(a->s->names[name], {}, {len}) == 0 && a->s->names[name][{len}] == '.') {{",
                    literal(name)
                )?;
                writeln!(
                    c,
                    "for (uint32_t n = 1; n < a->s->nnames; n++) if (strcmp(a->s->names[n], a->s->names[name] + {}) == 0) return dat_reader_field_value(a, {}, base + {at}, n, out);\n}}",
                    len + 1,
                    self.ty(raw.resolved)
                )?;
            }
        }
        c.push_str("return 0;\n");
        Ok(())
    }

    fn union_field_reader(&self, c: &mut String, row: &TypeRow) -> Result<()> {
        if row.kind == Kind::Union {
            for m in &row.members {
                if m.ty != NONE {
                    let r = self.generator.types[m.ty as usize].resolved;
                    writeln!(
                        c,
                        "if (dat_reader_field_value(a, {}, base, name, out)) return 1;",
                        self.ty(r)
                    )?;
                }
            }
        }
        c.push_str("return 0;\n");
        Ok(())
    }

    fn verify_reader(
        &mut self,
        c: &mut String,
        ident: &str,
        row: &TypeRow,
    ) -> Result<()> {
        match row.kind {
            Kind::Int => c.push_str(include_str!("templates/verify_int.c")),
            Kind::Float => {
                c.push_str(include_str!("templates/verify_float.c"))
            }
            Kind::Pointer => {
                c.push_str(include_str!("templates/verify_pointer.c"))
            }
            Kind::Struct => {
                for m in &row.members {
                    self.verify_member(c, ident, m)?;
                }
            }
            Kind::Union => self.verify_union(c, row)?,
            Kind::Array => {
                c.push_str(include_str!("templates/verify_array.c"))
            }
            _ => {}
        }
        Ok(())
    }

    fn read_reader(
        &mut self,
        c: &mut String,
        index: usize,
        row: &TypeRow,
    ) -> Result<()> {
        let ident = self.idents[index].clone();
        let ty = self.ty(index as i32);
        let resolved = &self.generator.types[row.resolved as usize];
        writeln!(
            c,
            "const int32_t type = {ty};\nDatParent parent = *parent_arg;"
        )?;
        // A qualifier ends a typedef annotation search, just as in Rust.
        let mut chain = Vec::new();
        let mut current = index;
        while self.generator.types[current].kind == Kind::Typedef {
            chain.push(current);
            current = self.generator.types[current].target as usize;
            if current == 0 {
                break;
            }
        }
        if let Some(&i) = chain
            .iter()
            .find(|&&i| self.generator.types[i].terminator.is_some())
        {
            let term = self
                .expr(self.generator.types[i].terminator.as_ref().unwrap());
            writeln!(
                c,
                "dat_reader_terminated(a, offset, type, native, {term}, {});\nreturn;",
                self.generator.types[i].terminator_length
            )?;
            return Ok(());
        }
        if let Some(&i) = chain
            .iter()
            .find(|&&i| self.generator.types[i].count_tag.is_some())
        {
            let expr =
                self.expr(self.generator.types[i].count_tag.as_ref().unwrap());
            writeln!(
                c,
                "DatContext ctx = {{ MODE_TERMINATOR, DAT_NONE, 0, DAT_NONE, 0, a->env, 0, 0 }};\nuint64_t n;\nif (dat_reader_eval(a, &ctx, {expr}, &n)) {{ DatParent none = {{ 0 }}; dat_reader_counted(a, offset, type, DAT_NONE, n, NULL, NULL, none, native); return; }}"
            )?;
        }
        if let Some(&i) = chain
            .iter()
            .find(|&&i| self.generator.types[i].type_tag != NONE)
        {
            writeln!(
                c,
                "dat_reader_typed(a, offset, {}, native, dat_reader_native_size(a, type));\nreturn;",
                self.ty(self.generator.types[i].type_tag)
            )?;
            return Ok(());
        }
        if let Some(&i) = chain
            .iter()
            .find(|&&i| self.generator.types[i].script.is_some())
        {
            let script =
                self.script(self.generator.types[i].script.as_ref().unwrap());
            writeln!(
                c,
                "dat_reader_script(a, offset, type, {script}, native);\nreturn;"
            )?;
            return Ok(());
        }
        if resolved.kind != Kind::Void {
            c.push_str("if (!t->conditioned && !t->has_extent && (uint64_t) offset + t->size > a->archive->size) { dat_reader_issue(a, ISSUE_OUT_OF_BOUNDS, offset, 0); return; }\n");
        }
        if matches!(resolved.kind, Kind::Struct | Kind::Union | Kind::Array) {
            c.push_str("dat_reader_place_native(a, offset, r, native);\n");
        }
        if row.resolved != index as i32 {
            c.push_str("dat_reader_layout(a, offset, r, native, parent);\n");
            return Ok(());
        }
        match resolved.kind {
            Kind::Struct => {
                for (i, m) in resolved.members.iter().enumerate() {
                    self.read_member(c, &ident, i, m)?;
                }
            }
            Kind::Union => self.read_union(c, &ident, resolved)?,
            Kind::Array => {
                c.push_str(include_str!("templates/layout_array.c"))
            }
            Kind::Pointer => {
                c.push_str(include_str!("templates/layout_pointer.c"))
            }
            Kind::Int | Kind::Float => {
                c.push_str(include_str!("templates/layout_float.c"))
            }
            _ => {}
        }
        Ok(())
    }

    pub(super) fn selection(
        &mut self,
        c: &mut String,
        row: &TypeRow,
    ) -> Result<()> {
        c.push_str("DatChoiceKind selected = CHOICE_AMBIGUOUS; uint32_t selected_index = 0;\ndo {\n");
        if row.members.len() == 1 {
            c.push_str("selected = CHOICE_MEMBER; break;\n");
        } else {
            for (i, m) in row.members.iter().enumerate() {
                if let Some(expr) = &m.cond {
                    let expr = self.expr(expr);
                    writeln!(
                        c,
                        "{{ DatContext ctx = {{ MODE_IF, parent.some ? parent.record : DAT_NONE, parent.base, r, offset, a->env, 0, 0 }}; uint64_t holds; if (!dat_reader_eval(a, &ctx, {expr}, &holds)) break; if (holds != 0) {{ selected = CHOICE_MEMBER; selected_index = {i}; break; }} }}"
                    )?;
                }
            }
            if row.members.iter().all(|m| m.cond.is_some()) {
                c.push_str("selected = CHOICE_UNUSED;\n");
            }
        }
        c.push_str("} while (0);\n");
        Ok(())
    }

    pub(super) fn binding(
        &mut self,
        c: &mut String,
        ident: &str,
        i: usize,
        m: &MemberRow,
    ) -> Result<()> {
        if m.binds.is_empty() {
            return Ok(());
        }
        writeln!(
            c,
            "static const DatScope* {ident}_bind_{i}(DatArchive* a, const DatScope* outer, const DatParent* parent, uint64_t index, DatScope* storage) {{\nconst DatScope* env = outer;\nDatContext ctx = {{ MODE_BIND, parent->some ? parent->record : DAT_NONE, parent->base, DAT_NONE, 0, outer, index, 0 }};"
        )?;
        for (j, (name, expr)) in m.binds.iter().enumerate() {
            let name = self.name(name);
            let expr = self.expr(expr);
            writeln!(
                c,
                "{{ uint64_t value; if (dat_reader_eval(a, &ctx, {expr}, &value)) {{ DatScope* s = &storage[{j}]; s->name = {name}; s->value = value; s->outer = env; env = s; }} }}"
            )?;
        }
        c.push_str("return env;\n}\n\n");
        Ok(())
    }
}

pub(super) fn largest(generator: &Generator, row: &TypeRow) -> Option<usize> {
    let mut best = None;
    let mut size = 0;
    for (i, m) in row.members.iter().enumerate() {
        let r = generator.types[m.ty as usize].resolved;
        let n = generator.types[r as usize].size;
        if best.is_none() || n > size {
            best = Some(i);
            size = n;
        }
    }
    best
}
