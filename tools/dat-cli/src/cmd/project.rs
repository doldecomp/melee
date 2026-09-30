//! What commands that walk the archives share.

use super::dwarf_path;
use anyhow::{Context, Result};
use globset::GlobSet;
use melee_dat::{
    config::{gather_files, get_config},
    dwarf::{
        DieId, TypeGraph,
        canonical::Canonical,
        render::Renderer,
        roots::{RootName, roots},
    },
    hsd::Archive,
    symbols::{Count, SymbolFile, TypeSpec},
    walk::{Walk, Walker, macros},
};
use std::{
    collections::{BTreeMap, HashMap},
    fs,
    path::PathBuf,
};

#[derive(clap::Args)]
pub struct Check {
    /// Project config
    #[arg(default_value = "config/GALE01/dat.yml")]
    pub cfg_path: PathBuf,
    #[arg(short = 'p', long)]
    pub proj_path: Option<PathBuf>,
    /// ELF or object with DWARF [default: $MELEE_DWARF_ELF]
    #[arg(long)]
    pub dwarf: Option<PathBuf>,
}

/// Everything a walk needs, loaded once.
pub struct Project {
    pub base: PathBuf,
    pub include: Vec<String>,
    pub graph: TypeGraph,
    pub canonical: Canonical,
    pub macros: HashMap<String, String>,
    /// Types of the root names loaders record; one type per name.
    pub root_types: BTreeMap<String, DieId>,
    /// `dat_symbols.txt`, for names no loader records.
    pub symbols: SymbolFile,
    pub symbol_types: BTreeMap<String, DieId>,
}

/// One archive's walk: a whole file, or one of a packed file's archives.
pub struct Walked<'a> {
    /// The file relative to the base, e.g. `PlMr.dat`.
    pub file: &'a str,
    /// `file`, with `@0xOFFSET` for packed archives after the first.
    pub name: String,
    pub archive: &'a Archive<'a>,
    /// Whether any root was found in it.
    pub rooted: bool,
    pub result: Walk,
}

impl Project {
    pub fn load(args: &Check) -> Result<Self> {
        let config = get_config(args.proj_path.as_ref(), &args.cfg_path)?;
        let proj = args.proj_path.clone().unwrap_or_default();
        let graph = TypeGraph::load(dwarf_path(args.dwarf.clone())?)?;
        let canonical = Canonical::new(&graph);
        let macros = macros(&graph);

        let mut root_types = BTreeMap::new();
        for root in roots(&graph, &canonical) {
            if let (RootName::Literal(name), Some(ty)) = (root.name, root.ty) {
                root_types.entry(name).or_insert(ty);
            }
        }
        let symbols_path = proj.join(config.symbols.as_str());
        let symbols =
            SymbolFile::parse(&fs::read_to_string(&symbols_path)?)
                .with_context(|| format!("{}", symbols_path.display()))?;
        let mut symbol_types = BTreeMap::new();
        for entry in &symbols.entries {
            let Some(spec) = &entry.ty else { continue };
            let die = canonical
                .lookup(&graph, &spec.name)
                .first()
                .copied()
                .with_context(|| {
                    format!("{entry}: no type `{}`", spec.name)
                })?;
            symbol_types.insert(spec.name.clone(), die);
        }
        Ok(Project {
            base: proj.join(config.base.as_str()),
            include: config.include,
            graph,
            canonical,
            macros,
            root_types,
            symbols,
            symbol_types,
        })
    }

    /// Walk every archive whose file matches `only` (all if empty), in
    /// file order.
    pub fn walk_all(
        &self,
        only: &GlobSet,
        mut each: impl FnMut(Walked) -> Result<()>,
    ) -> Result<()> {
        let mut paths = gather_files(&self.base, &self.include)?;
        paths.sort();
        for path in paths {
            let file = path
                .strip_prefix(&self.base)?
                .to_string_lossy()
                .into_owned();
            if !only.is_empty() && !only.is_match(&file) {
                continue;
            }
            let bytes = fs::read(&path)?;
            let archives = Archive::parse_packed(&bytes)
                .with_context(|| format!("{}", path.display()))?;
            for (at, archive) in &archives {
                let name = match at {
                    0 => file.clone(),
                    _ => format!("{file}@{at:#X}"),
                };
                let (rooted, result) = self.walk(&file, archive);
                each(Walked {
                    file: &file,
                    name,
                    archive,
                    rooted,
                    result,
                })?;
            }
        }
        Ok(())
    }

    pub fn walk(&self, file: &str, archive: &Archive) -> (bool, Walk) {
        let mut walker =
            Walker::new(&self.graph, &self.canonical, &self.macros, archive);
        let mut rooted = false;
        for (name, symbol) in archive.named_publics() {
            let name = String::from_utf8_lossy(name);
            if let Some(&ty) = self.root_types.get(name.as_ref()) {
                walker.root(symbol.offset, ty, &name);
                rooted = true;
            } else if let Some(TypeSpec { name: ty, count }) =
                self.symbols.lookup(&name, file).and_then(|e| e.ty.as_ref())
            {
                let ty = self.symbol_types[ty];
                let offset = symbol.offset;
                match *count {
                    Count::One => walker.root(offset, ty, &name),
                    Count::Exactly(n) => {
                        walker.root_array(offset, ty, Some(n), &name)
                    }
                    Count::Unbounded => {
                        walker.root_array(offset, ty, None, &name)
                    }
                }
                rooted = true;
            }
        }
        (rooted, walker.finish())
    }

    /// The type of the object at `offset`, for display.
    pub fn object_type(&self, walk: &Walk, offset: u32) -> String {
        let renderer = Renderer::new(&self.graph, &self.canonical);
        walk.objects
            .get(&offset)
            .and_then(|types| types.first())
            .map_or_else(
                || "?".to_owned(),
                |&id| renderer.declare(Some(self.canonical.get(id).rep), ""),
            )
    }
}
