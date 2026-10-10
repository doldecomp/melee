//! The schema as C, a directory of it:
//!
//! - `melee_dat.h`: the schema and the types' indices, `DAT_TYPE_*`
//! - `types/<header>.c`: compiled readers for the types a game header
//!   declares, with what refers to them (pointers, arrays, qualifiers);
//!   `types/base.c` those of the types no header declares
//! - `roots/<module>.c`: the roots of the archives of a module, the first two
//!   letters of their names (`Pl`, `Gr`)
//! - `macros.c`, `scripts.c`: the macros the annotations' expressions use,
//!   and the scripts' command length tables
//! - `schema.c`: the schema, every type and name by index
//! - `melee_dat_internal.h`: what the files share, `DAT_NAME_*`

use super::generator::{
    FileRow, Generator, MemberRow, NONE, Place, ScriptRow, TypeRow, source,
};
use anyhow::{Result, bail};
use melee_dat::{
    dwarf::{DieId, TypeKind, expr::Expr},
    symbols::Count,
};
use std::{
    collections::{BTreeMap, BTreeSet, HashMap},
    fmt::Write as _,
    fs,
    path::Path,
};

/// The public header's name.
pub const HEADER: &str = "melee_dat.h";
const INTERNAL: &str = "melee_dat_internal.h";

/// How long a member's descriptor gets before it is split over lines.
const LINE: usize = 100;

/// The files, by path in the output directory.
pub type Output = BTreeMap<String, String>;

mod expressions;
mod members;
mod readers;

struct Emitter<'g, 'a> {
    generator: &'g Generator<'a>,
    /// Each type's identifier, by index.
    idents: Vec<String>,
    /// The names expressions and members refer to.
    names: BTreeSet<String>,
    /// Macros' bodies, by name, where they parse.
    macros: HashMap<String, Option<Expr>>,
    /// The macros referred to, which `macros.c` defines.
    used_macros: BTreeSet<String>,
    scripts: BTreeMap<String, Vec<u8>>,
    expression_code: String,
    next_expression: usize,
}

pub fn emit(generator: &Generator, files: &[FileRow]) -> Result<Output> {
    let mut e = Emitter {
        generator,
        idents: idents(generator),
        names: BTreeSet::new(),
        macros: HashMap::new(),
        used_macros: BTreeSet::new(),
        scripts: BTreeMap::new(),
        expression_code: String::new(),
        next_expression: 0,
    };
    let mut out = Output::new();
    let mut declared: BTreeMap<String, Vec<String>> = BTreeMap::new();

    // The types, by the header that declares them
    let mut homes: BTreeMap<String, Vec<usize>> = BTreeMap::new();
    for (index, row) in generator.types.iter().enumerate().skip(1) {
        let home = row
            .die
            .map_or_else(|| "base".into(), |d| home(generator, d));
        homes.entry(home).or_default().push(index);
    }
    for (home, indices) in &homes {
        let path = format!("types/{home}.c");
        let mut body = String::new();
        let mut headers = BTreeSet::new();
        for &index in indices {
            let row = &generator.types[index];
            headers.extend(row.headers.iter().cloned());
            e.descriptor(&mut body, index, row)?;
        }
        let what = match home.as_str() {
            "base" => "The types no header of the game's declares".to_owned(),
            _ => format!("The types `{home}` declares"),
        };
        let mut c = preamble(&what);
        writeln!(c, "#include \"{INTERNAL}\"\n")?;
        for header in &headers {
            writeln!(c, "#include <{header}>")?;
        }
        if !headers.is_empty() {
            c.push('\n');
        }
        c.push_str(&std::mem::take(&mut e.expression_code));
        c.push_str(&body);
        declared.insert(
            path.clone(),
            indices
                .iter()
                .map(|&i| {
                    format!("extern const DatType dat_type_{};", e.idents[i])
                })
                .collect(),
        );
        out.insert(path, c);
    }

    // The roots, by module
    let mut modules: BTreeMap<String, Vec<&FileRow>> = BTreeMap::new();
    for file in files {
        modules.entry(module(&file.file)).or_default().push(file);
    }
    for (module, files) in &modules {
        let path = format!("roots/{module}.c");
        let mut c = preamble(&format!(
            "The roots of the archives of the `{module}` files"
        ));
        writeln!(c, "#include \"{INTERNAL}\"")?;
        let mut body = String::new();
        let mut arrays = Vec::new();
        let mut used = BTreeSet::new();
        for file in files {
            let mut array = identifier(&file.file);
            if file.archive > 0 {
                write!(array, "_{}", file.archive)?;
            }
            while !used.insert(array.clone()) {
                array.push('_');
            }
            writeln!(body, "\nstatic const DatRoot {array}[] = {{")?;
            for root in &file.roots {
                let parts = e.root(root);
                body.push_str(&initializer(&parts, "    ", ","));
            }
            body.push_str("};\n");
            arrays.push((file, array));
        }
        writeln!(body, "\nconst DatFileRoots dat_files_{module}[] = {{")?;
        for (file, array) in &arrays {
            let mut parts = vec![format!(".file = {}", literal(&file.file))];
            if file.archive > 0 {
                parts.push(format!(".archive = {}", file.archive));
            }
            parts.push(format!("DAT_FILE_ROOTS({array})"));
            body.push_str(&initializer(&parts, "    ", ","));
        }
        body.push_str("};\n");
        declared.insert(
            path.clone(),
            vec![format!(
                "extern const DatFileRoots dat_files_{module}[{}];",
                files.len()
            )],
        );
        c.push_str(&std::mem::take(&mut e.expression_code));
        c.push_str(&body);
        out.insert(path, c);
    }

    // The macros the expressions use, and those theirs use
    let mut defined = BTreeSet::new();
    let mut macros = String::new();
    loop {
        let pending: Vec<String> =
            e.used_macros.difference(&defined).cloned().collect();
        if pending.is_empty() {
            break;
        }
        for name in pending {
            let body = e.macros[&name].clone().expect("only parsed are used");
            let fields = e.fields(&body);
            writeln!(
                macros,
                "const DatExpr dat_macro_{} = {{ {fields} }};",
                identifier(&name)
            )?;
            defined.insert(name);
        }
    }
    if !defined.is_empty() {
        let mut c = preamble("The macros the annotations' expressions use");
        writeln!(c, "#include \"{INTERNAL}\"\n")?;
        c.push_str(&std::mem::take(&mut e.expression_code));
        c.push_str(&macros);
        declared.insert(
            "macros.c".into(),
            defined
                .iter()
                .map(|m| {
                    format!(
                        "extern const DatExpr dat_macro_{};",
                        identifier(m)
                    )
                })
                .collect(),
        );
        out.insert("macros.c".into(), c);
    }

    if !e.scripts.is_empty() {
        let mut c = preamble(
            "The lengths of scripts' commands, from the code's tables",
        );
        writeln!(c, "#include \"{INTERNAL}\"")?;
        for (table, bytes) in &e.scripts {
            writeln!(
                c,
                "\nconst DatScript dat_script_{} = {{",
                identifier(table)
            )?;
            c.push_str("    .table = (const uint8_t[]) {");
            if bytes.is_empty() {
                c.push_str(" 0 },\n");
            } else {
                for chunk in bytes.chunks(16) {
                    c.push_str("\n        ");
                    let line: Vec<String> =
                        chunk.iter().map(u8::to_string).collect();
                    c.push_str(&line.join(", "));
                    c.push(',');
                }
                c.push_str("\n    },\n");
            }
            writeln!(c, "    .table_size = {},\n}};", bytes.len())?;
        }
        declared.insert(
            "scripts.c".into(),
            e.scripts
                .keys()
                .map(|t| {
                    format!(
                        "extern const DatScript dat_script_{};",
                        identifier(t)
                    )
                })
                .collect(),
        );
        out.insert("scripts.c".into(), c);
    }

    let names = name_idents(&e.names)?;
    out.insert(HEADER.into(), e.header());
    out.insert(INTERNAL.into(), internal(&names, &declared));
    out.insert("schema.c".into(), e.schema(&names, modules.keys()));
    Ok(out)
}

impl Emitter<'_, '_> {
    fn ty(&self, index: i32) -> String {
        match index {
            NONE => "DAT_NONE".into(),
            i => format!("DAT_TYPE_{}", self.idents[i as usize]),
        }
    }

    fn name(&mut self, name: &str) -> String {
        // A nested member's path: the walk looks up each remainder
        for (i, _) in name.match_indices('.') {
            self.names.insert(name[i + 1..].to_owned());
        }
        self.names.insert(name.to_owned());
        format!("DAT_NAME_{}", identifier(name))
    }

    /// A type's callbacks, native bitfield accessors and storage metadata.
    fn descriptor(
        &mut self,
        c: &mut String,
        index: usize,
        row: &TypeRow,
    ) -> Result<()> {
        let ident = self.idents[index].clone();
        if !row.members.is_empty() {
            for m in &row.members {
                if let (Place::Bits { record, field }, Some(_)) =
                    (&m.place, &m.name)
                {
                    writeln!(
                        c,
                        "static void {ident}_{field}_set(void* o, uint64_t v) {{ (({record}*) o)->{field} = v; }}"
                    )?;
                    writeln!(
                        c,
                        "#ifdef DAT_NATIVE_TESTING\nstatic uint64_t {ident}_{field}_get(const void* o) {{ return (uint64_t) ((const {record}*) o)->{field}; }}\n#endif\n"
                    )?;
                }
            }
            for (i, m) in row.members.iter().enumerate() {
                self.binding(c, &ident, i, m)?;
            }
        }
        self.readers(c, index, row)?;
        writeln!(c, "const DatType dat_type_{ident} = {{")?;
        let mut fields = vec![
            format!(".name = {}", literal(&row.name)),
            format!(".id = {}", row.id),
            format!(
                ".kind = {}",
                self.generator.types[row.resolved as usize].kind.c()
            ),
        ];
        for callback in [
            "read",
            "convert",
            "fits",
            "field",
            "union_field",
            "allocation_size",
            "verify",
        ] {
            if callback != "verify" {
                fields.push(format!(".{callback} = {ident}_{callback}"));
            }
        }
        if row.members.iter().any(|m| m.cond.is_some()) {
            fields.push(".conditioned = 1".into());
        }
        for (set, field) in [
            (row.has_pointers, "has_pointers"),
            (row.has_extent, "has_extent"),
            (row.unbounded, "unbounded"),
        ] {
            if set {
                fields.push(format!(".{field} = 1"));
            }
        }
        let mut current = index;
        while current != NONE as usize {
            let ty = &self.generator.types[current];
            if ty.raw || ty.blob {
                fields.push(".opaque = 1".into());
                break;
            }
            if !matches!(
                ty.kind,
                super::generator::Kind::Typedef
                    | super::generator::Kind::Qualifier
            ) {
                break;
            }
            current = ty.target as usize;
        }
        if row.size != 0 {
            fields.push(format!(".size = 0x{:X}", row.size));
        }
        if row.native_size != "0" {
            fields.push(format!(".native_size = {}", row.native_size));
        }
        if row.target != NONE {
            fields.push(format!(".target = {}", self.ty(row.target)));
        }
        if row.resolved != NONE {
            fields.push(format!(".resolved = {}", self.ty(row.resolved)));
        }
        if row.count != 0 {
            fields.push(format!(".count = {}", row.count));
        }
        writeln!(
            c,
            "#ifdef DAT_NATIVE_TESTING\n    .verify = {ident}_verify,"
        )?;
        if row.is_signed {
            c.push_str("    .is_signed = 1,\n");
        }
        if row.raw {
            c.push_str("    .raw = 1,\n");
        }
        c.push_str("#endif\n");
        for field in fields {
            writeln!(c, "    {field},")?;
        }
        c.push_str("};\n\n");
        Ok(())
    }

    /// A C expression pointing to a script descriptor.
    fn script(&mut self, script: &ScriptRow) -> String {
        match script {
            ScriptRow::Table(table, bytes) => {
                self.scripts.insert(table.clone(), bytes.clone());
                format!("&dat_script_{}", identifier(table))
            }
            ScriptRow::Length(length) => {
                let length = self.expr(length);
                format!("&(const DatScript) {{ .length = {length} }}")
            }
            ScriptRow::Bytes(length) => {
                let length = self.expr(length);
                format!(
                    "&(const DatScript) {{ .length = {length}, .bytes = 1 }}"
                )
            }
        }
    }

    fn root(&mut self, root: &super::generator::RootRow) -> Vec<String> {
        let mut parts = vec![format!(".name = {}", literal(&root.name))];
        if root.alias {
            parts.push(".alias = 1".into());
            parts.push(format!(".address = 0x{:X}", root.address));
        }
        parts.push(format!(".type = {}", self.ty(root.ty)));
        match root.count {
            Count::One => {}
            Count::Exactly(n) => {
                parts.push(".count_kind = DAT_COUNT_EXACTLY".into());
                parts.push(format!(".count = {n}"));
            }
            Count::Unbounded => {
                parts.push(".count_kind = DAT_COUNT_EXTENT".into());
            }
            Count::Terminated(value) => {
                parts.push(".count_kind = DAT_COUNT_TERMINATED".into());
                parts.push(format!(".count = {}", int(value)));
            }
        }
        if let Some(script) = &root.script {
            parts.push(format!(".script = {}", self.script(script)));
        }
        if !root.binds.is_empty() {
            let mut env = "NULL".to_owned();
            for (name, value) in &root.binds {
                env = format!(
                    "&(const DatScope) {{ {}, {value}, {env} }}",
                    self.name(name)
                );
            }
            parts.push(format!(".env = {env}"));
        }
        parts
    }

    /// Whether a name has a macro to fall back on, noting it if so.
    fn macro_body(&mut self, name: &str) -> bool {
        let project = self.generator.project;
        let has = self
            .macros
            .entry(name.to_owned())
            .or_insert_with(|| {
                project.macros.get(name).and_then(|body| Expr::parse(body))
            })
            .is_some();
        if has {
            self.used_macros.insert(name.to_owned());
        }
        has
    }

    fn header(&self) -> String {
        let mut h = preamble(
            "The schema of the game's archives, and their types' indices",
        );
        h.push_str(concat!(
            "#ifndef MELEE_DAT_H\n",
            "#define MELEE_DAT_H\n\n",
            "#include <dat/archive.h>\n\n",
            "/// The types, by index into melee_dat_schema.types.\n",
            "typedef enum MeleeDatType {\n",
        ));
        for (index, ident) in self.idents.iter().enumerate().skip(1) {
            let _ = writeln!(h, "    DAT_TYPE_{ident} = {index},");
        }
        h.push_str(concat!(
            "    DAT_TYPE_COUNT\n",
            "} MeleeDatType;\n\n",
            "extern const DatSchema melee_dat_schema;\n",
            "int32_t melee_dat_type(const char* spelling);\n\n",
            "#endif\n",
        ));
        h
    }

    fn schema<'m>(
        &self,
        names: &[(String, String)],
        modules: impl Iterator<Item = &'m String>,
    ) -> String {
        let mut c = preamble("The schema: every type and name, by index");
        let _ = writeln!(c, "#include \"{INTERNAL}\"\n");
        let mut dispatch = BTreeMap::new();
        for (index, row) in self.generator.types.iter().enumerate().skip(1) {
            if row.native_size != "0"
                && let Some(spelling) = row
                    .die
                    .and_then(|die| self.generator.dispatch_spelling(die))
            {
                dispatch.entry(spelling).or_insert(index as i32);
            }
        }
        c.push_str("static const struct { const char* name; int32_t type; } dispatch[] = {\n");
        for (name, index) in dispatch {
            let _ = writeln!(
                c,
                "    {{ {}, {} }},",
                literal(&name),
                self.ty(index)
            );
        }
        c.push_str("};\n\n");
        c.push_str(include_str!("emit/templates/dispatch.c"));
        c.push_str("static const DatType* const types[DAT_TYPE_COUNT] = {\n");
        for ident in self.idents.iter().skip(1) {
            let _ = writeln!(c, "    [DAT_TYPE_{ident}] = &dat_type_{ident},");
        }
        c.push_str(
            "};\n\nstatic const char* const names[DAT_NAME_COUNT] = {\n",
        );
        for (name, ident) in names {
            let _ = writeln!(c, "    [DAT_NAME_{ident}] = {},", literal(name));
        }
        c.push_str("};\n\nstatic const DatModule modules[] = {\n");
        for module in modules {
            let _ = writeln!(c, "    DAT_MODULE(dat_files_{module}),");
        }
        c.push_str(concat!(
            "};\n\n",
            "const DatSchema melee_dat_schema = {\n",
            "    .types = types,\n",
            "    .ntypes = DAT_TYPE_COUNT,\n",
            "    .names = names,\n",
            "    .nnames = DAT_NAME_COUNT,\n",
            "    .modules = modules,\n",
            "    .nmodules = DAT_COUNTOF(modules),\n",
            "};\n",
        ));
        c
    }
}

fn internal(
    names: &[(String, String)],
    declared: &BTreeMap<String, Vec<String>>,
) -> String {
    let mut h = preamble("What the schema's files share");
    h.push_str(concat!(
        "#ifndef MELEE_DAT_INTERNAL_H\n",
        "#define MELEE_DAT_INTERNAL_H\n\n",
        "#include <stddef.h>\n",
        "#include <stdint.h>\n\n",
        "#include <dat/reader-internal.h>\n\n",
        "#include \"melee_dat.h\"\n\n",
        "/// The names members and expressions refer to, by index into\n",
        "/// melee_dat_schema.names.\n",
        "typedef enum MeleeDatName {\n",
    ));
    for (index, (_, ident)) in names.iter().enumerate() {
        let _ = writeln!(h, "    DAT_NAME_{ident} = {},", index + 1);
    }
    h.push_str("    DAT_NAME_COUNT\n} MeleeDatName;\n");
    for (file, lines) in declared {
        let _ = writeln!(h, "\n/* {file} */");
        for line in lines {
            let _ = writeln!(h, "{line}");
        }
    }
    h.push_str("\n#endif\n");
    h
}

fn preamble(what: &str) -> String {
    format!(
        "/**\n * @file\n * {what}, for the native archive interface.\n * Generated by `melee-dat native codegen`.\n */\n\n"
    )
}

/// A designated initializer of `parts`, on one line if it fits.
fn initializer(parts: &[String], indent: &str, end: &str) -> String {
    let line = format!("{indent}{{ {} }}{end}\n", parts.join(", "));
    if line.len() <= LINE + 1 {
        return line;
    }
    let mut out = format!("{indent}{{\n");
    for part in parts {
        let _ = writeln!(out, "{indent}    {part},");
    }
    let _ = writeln!(out, "{indent}}}{end}");
    out
}

/// Each type's identifier, by index: as C spells it where it can, unique.
fn idents(generator: &Generator) -> Vec<String> {
    let mut used = HashMap::new();
    let mut idents = vec![String::new()];
    for row in generator.types.iter().skip(1) {
        let base = identifier(
            &row.die
                .map_or_else(|| "void".into(), |d| spelled(generator, d)),
        );
        let n = used.entry(base.clone()).or_insert(0);
        *n += 1;
        idents.push(match *n {
            1 => base,
            n => format!("{base}_{n}"),
        });
    }
    idents
}

/// A name for a type, as C would spell it, which [`identifier`] makes one.
fn spelled(generator: &Generator, die: DieId) -> String {
    let ty = generator.ty(die);
    let name = ty.name.map(|n| generator.str(n));
    let target = |t: &Option<DieId>| {
        t.map_or_else(|| "void".into(), |t| spelled(generator, t))
    };
    match &ty.kind {
        TypeKind::Base { .. } | TypeKind::Typedef { .. } => {
            name.unwrap_or("anonymous").to_owned()
        }
        TypeKind::Unspecified => name.unwrap_or("void").to_owned(),
        TypeKind::Record { union, .. } => format!(
            "{} {}",
            if *union { "union" } else { "struct" },
            generator.name_of(die)
        ),
        TypeKind::Enum { .. } => format!("enum {}", generator.name_of(die)),
        TypeKind::Pointer { target: t } => format!("{}_ptr", target(t)),
        TypeKind::Const { target: t } => format!("const {}", target(t)),
        TypeKind::Volatile { target: t } => format!("volatile {}", target(t)),
        TypeKind::Restrict { target: t } => format!("restrict {}", target(t)),
        TypeKind::Array { element, dims } => {
            let dims: Vec<String> = dims
                .iter()
                .map(|d| d.map_or_else(|| "n".into(), |d| d.to_string()))
                .collect();
            format!("{}_{}", target(element), dims.join("x"))
        }
        TypeKind::Subroutine { .. } => "function".into(),
    }
}

/// The file of the game's that declares a type, without its extension:
/// that of what it refers to for those no file declares (pointers,
/// arrays), and `base` for those no file of the game's does.
fn home(generator: &Generator, die: DieId) -> String {
    let ty = generator.ty(die);
    if let Some(path) = ty.decl_file.and_then(|f| source(generator.str(f))) {
        return match path.rsplit_once('.') {
            Some((stem, _)) => stem.to_owned(),
            None => path,
        };
    }
    match &ty.kind {
        TypeKind::Typedef { target: Some(t) }
        | TypeKind::Pointer { target: Some(t) }
        | TypeKind::Const { target: Some(t) }
        | TypeKind::Volatile { target: Some(t) }
        | TypeKind::Restrict { target: Some(t) }
        | TypeKind::Array {
            element: Some(t), ..
        } => home(generator, *t),
        _ => "base".into(),
    }
}

/// A file's module: the first two letters of its name.
fn module(file: &str) -> String {
    let name = file.rsplit('/').next().unwrap_or(file);
    identifier(&name.chars().take(2).collect::<String>())
}

/// The names' identifiers, which must be unique.
fn name_idents(names: &BTreeSet<String>) -> Result<Vec<(String, String)>> {
    let mut seen = HashMap::new();
    let mut out = Vec::new();
    for name in names {
        let ident = identifier(name);
        if let Some(other) = seen.insert(ident.clone(), name) {
            bail!(
                "the names `{other}` and `{name}` are both DAT_NAME_{ident}"
            );
        }
        out.push((name.clone(), ident));
    }
    Ok(out)
}

/// A C identifier from a name.
fn identifier(name: &str) -> String {
    let mut id = String::new();
    for c in name.trim().chars() {
        if c.is_ascii_alphanumeric() || c == '_' {
            id.push(c);
        } else if !id.ends_with('_') {
            id.push('_');
        }
    }
    let id = id.trim_end_matches('_').to_owned();
    match id.chars().next() {
        None => "_".into(),
        Some(c) if c.is_ascii_digit() => format!("_{id}"),
        Some(_) => id,
    }
}

/// A C string literal.
fn literal(s: &str) -> String {
    let mut out = String::from("\"");
    for c in s.bytes() {
        match c {
            b'"' => out.push_str("\\\""),
            b'\\' => out.push_str("\\\\"),
            0x20..=0x7E => out.push(c as char),
            _ => {
                let _ = write!(out, "\\{c:03o}");
            }
        }
    }
    out.push('"');
    out
}

fn int(value: u64) -> String {
    match value {
        0..=9 => value.to_string(),
        _ if value > i64::MAX as u64 => format!("0x{value:X}ull"),
        _ => format!("0x{value:X}"),
    }
}

/// Write the files to `dir`, each only if it changed, so that what didn't
/// isn't rebuilt, and remove the sources it had that are no longer
/// generated.
pub fn write(dir: &Path, output: &Output) -> Result<()> {
    for (path, contents) in output {
        let path = dir.join(path);
        if fs::read_to_string(&path).is_ok_and(|old| old == *contents) {
            continue;
        }
        if let Some(parent) = path.parent() {
            fs::create_dir_all(parent)?;
        }
        fs::write(&path, contents)?;
    }
    let mut stack = vec![dir.to_path_buf()];
    while let Some(at) = stack.pop() {
        for entry in fs::read_dir(&at)? {
            let path = entry?.path();
            if path.is_dir() {
                stack.push(path);
                continue;
            }
            let generated = matches!(
                path.extension().and_then(|e| e.to_str()),
                Some("c" | "h")
            );
            let relative =
                path.strip_prefix(dir)?.to_string_lossy().replace('\\', "/");
            if generated && !output.contains_key(&relative) {
                fs::remove_file(&path)?;
            }
        }
    }
    Ok(())
}

/// Generate the independent fixture schemas with the same compiled readers.
pub(super) fn fixture(groups: &[(String, Generator)]) -> Result<String> {
    let mut names = BTreeSet::new();
    let mut body = String::new();
    let mut declarations = String::new();
    let mut enumerators = String::new();
    let mut next_expression = 0;
    for (group, generator) in groups {
        let idents = (0..generator.types.len())
            .map(|i| format!("fixture_{group}_{i}"))
            .collect::<Vec<_>>();
        let mut e = Emitter {
            generator,
            idents,
            names: BTreeSet::new(),
            macros: HashMap::new(),
            used_macros: BTreeSet::new(),
            scripts: BTreeMap::new(),
            expression_code: String::new(),
            next_expression,
        };
        let mut types = String::new();
        for (i, row) in generator.types.iter().enumerate().skip(1) {
            writeln!(enumerators, "DAT_TYPE_{} = {i},", e.idents[i])?;
            writeln!(
                declarations,
                "extern const DatType dat_type_{};",
                e.idents[i]
            )?;
            e.descriptor(&mut types, i, row)?;
        }
        body.push_str(&e.expression_code);
        body.push_str(&types);
        let table = if group == "base" {
            "types".to_owned()
        } else {
            format!("fixture_{group}_types")
        };
        writeln!(body, "static const DatType* const {table}[] = {{ NULL,")?;
        for ident in e.idents.iter().skip(1) {
            writeln!(body, "&dat_type_{ident},")?;
        }
        body.push_str("};\n");
        let schema = if group == "base" {
            "schema".to_owned()
        } else {
            format!("fixture_{group}_schema")
        };
        writeln!(
            body,
            "static const DatSchema {schema} = {{ .types = {table}, .ntypes = DAT_COUNTOF({table}), .names = names, .nnames = DAT_NAME_COUNT }};\n"
        )?;
        names.extend(e.names);
        next_expression = e.next_expression;
    }
    let names = name_idents(&names)?;
    let mut out = preamble("Synthetic fixture readers");
    out.push_str("#include <dat/reader-internal.h>\nenum {\n");
    out.push_str(&enumerators);
    out.push_str("};\nenum {\n");
    for (i, (_, ident)) in names.iter().enumerate() {
        writeln!(out, "DAT_NAME_{ident} = {},", i + 1)?;
    }
    out.push_str("DAT_NAME_COUNT };\nstatic const char* const names[DAT_NAME_COUNT] = {\n");
    for (name, ident) in names {
        writeln!(out, "[DAT_NAME_{ident}] = {},", literal(&name))?;
    }
    out.push_str("};\n");
    out.push_str(&declarations);
    out.push_str(&body);
    Ok(out)
}
