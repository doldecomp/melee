//! What commands that walk the archives share.

use super::dwarf_path;
use anyhow::{Context, Result};
use globset::GlobSet;
use melee_dat::{
    config::{gather_files, get_config},
    dwarf::{
        DieId, TypeGraph,
        cache::TypesFile,
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
    /// The compact types file from `types export`, instead of the DWARF
    #[arg(long, conflicts_with = "dwarf")]
    pub types: Option<PathBuf>,
    /// The archives' directory [default: the config's `base`]
    #[arg(long)]
    pub files: Option<PathBuf>,
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
    /// `dat_symbols.txt`: types for names no loader records, and counts and
    /// bindings for any root.
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
        let (graph, macros, root_types) = match &args.types {
            Some(path) => {
                let types = TypesFile::load(path)?;
                (types.graph, types.macros, types.roots)
            }
            None => {
                let graph = TypeGraph::load(dwarf_path(args.dwarf.clone())?)?;
                let canonical = Canonical::new(&graph);
                let macros = macros(&graph);
                let mut root_types = BTreeMap::new();
                for root in roots(&graph, &canonical) {
                    if let (RootName::Literal(name), Some(ty)) =
                        (root.name, root.ty)
                    {
                        root_types.entry(name).or_insert(ty);
                    }
                }
                (graph, macros, root_types)
            }
        };
        let canonical = Canonical::new(&graph);
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
            base: args
                .files
                .clone()
                .unwrap_or_else(|| proj.join(config.base.as_str())),
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
                let (rooted, result) = self.walk(&file, archive)?;
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

    pub fn walk(&self, file: &str, archive: &Archive) -> Result<(bool, Walk)> {
        let mut walker =
            Walker::new(&self.graph, &self.canonical, &self.macros, archive);
        let mut rooted = false;
        for (name, symbol) in archive.named_publics() {
            let name = String::from_utf8_lossy(name);
            let entry = self.symbols.lookup(&name, file);
            let (ty, count) =
                if let Some(&ty) = self.root_types.get(name.as_ref()) {
                    // The loader gives the type; the symbol entry may add a
                    // count and bindings without repeating that type.
                    (ty, entry.and_then(|e| e.count).unwrap_or(Count::One))
                } else if let Some(TypeSpec { name: ty, count }) =
                    entry.and_then(|e| e.ty.as_ref())
                {
                    (self.symbol_types[ty], *count)
                } else {
                    continue;
                };
            let bindings = entry
                .map(|e| e.bindings(&self.macros))
                .transpose()?
                .unwrap_or_default();
            match count {
                Count::One => walker.root(symbol.offset, ty, &name, &bindings),
                Count::Exactly(n) => walker.root_array(
                    symbol.offset,
                    ty,
                    Some(n),
                    &name,
                    &bindings,
                ),
                Count::Unbounded => walker.root_array(
                    symbol.offset,
                    ty,
                    None,
                    &name,
                    &bindings,
                ),
            }
            rooted = true;
        }
        Ok((rooted, walker.finish()))
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

#[cfg(test)]
mod tests {
    use super::*;

    /// Use the real extracted archive and derived types; nothing generated
    /// or copied from the game is committed as a fixture.
    #[test]
    fn samus_root_bindings_select_grapple_for_loader_and_symbol_types() {
        let repo = PathBuf::from(env!("CARGO_MANIFEST_DIR")).join("../..");
        let build = std::env::var_os("MELEE_DAT_BUILD")
            .map(PathBuf::from)
            .unwrap_or_else(|| repo.join("build/GALE01/dat"));
        let files = std::env::var_os("MELEE_DAT_FILES")
            .map(PathBuf::from)
            .unwrap_or_else(|| repo.join("orig/GALE01/files"));
        if (!build.join("types.bin").exists()
            || !files.join("PlSs.dat").exists())
            && std::env::var_os("MELEE_DAT_BUILD").is_none()
            && std::env::var_os("MELEE_DAT_FILES").is_none()
        {
            eprintln!("skipping: no real DAT build and archives found");
            return;
        }
        let mut project = Project::load(&Check {
            cfg_path: "config/GALE01/dat.yml".into(),
            proj_path: Some(repo),
            dwarf: None,
            types: Some(build.join("types.bin")),
            files: Some(files.clone()),
        })
        .unwrap();
        let bytes = fs::read(files.join("PlSs.dat")).unwrap();
        let archive = Archive::parse_packed(&bytes).unwrap().remove(0).1;
        let root = archive
            .named_publics()
            .find(|(name, _)| *name == b"ftDataSamus")
            .unwrap()
            .1
            .offset;
        let word = |at: u32| {
            u32::from_be_bytes(
                archive.data[at as usize..at as usize + 4]
                    .try_into()
                    .unwrap(),
            )
        };
        let items = word(root + 0x48);
        let grapple = word(items + 4 * 4);
        let ty = project.root_types["ftDataSamus"];
        project.symbol_types.insert("ftData".into(), ty);

        for loader in [true, false] {
            if !loader {
                project.root_types.remove("ftDataSamus");
            }
            for count in [Count::One, Count::Exactly(1), Count::Unbounded] {
                let entry = project
                    .symbols
                    .entries
                    .iter_mut()
                    .find(|e| e.name == "ftDataSamus")
                    .unwrap();
                entry.count = Some(count);
                entry.ty = Some(TypeSpec {
                    name: "ftData".into(),
                    count,
                });
                let (rooted, walk) =
                    project.walk("PlSs.dat", &archive).unwrap();
                assert!(rooted);
                let union = *walk.objects[&grapple].first().unwrap();
                assert_eq!(
                    walk.choices.get(&(grapple, union)),
                    Some(&0),
                    "Samus slot 4 must select the grapple accessory (loader={loader}, count={count:?})"
                );
                assert!(
                    walk.issues.iter().all(|issue| {
                        !issue.path().starts_with("ftDataSamus.x48_items->[4]")
                    }),
                    "grapple walk has issues: {:?}",
                    walk.issues
                );
                // Other slots still choose Article: the per-element binding
                // must shadow the index used for the grapple slot.
                for index in 0..4 {
                    let at = word(items + index * 4);
                    assert_eq!(walk.choices.get(&(at, union)), Some(&1));
                }
            }
        }

        // A root's scope cannot carry over to another root, even after
        // following pointers from an array root.
        let union =
            project.canonical.lookup(&project.graph, "ftData_ItemData")[0];
        let mut walker = Walker::new(
            &project.graph,
            &project.canonical,
            &project.macros,
            &archive,
        );
        walker.root_array(
            grapple,
            union,
            Some(1),
            "grapple",
            &[("ftData::kind".into(), 13), ("ftData::item".into(), 4)],
        );
        walker.root(word(items), union, "unbound", &[]);
        assert!(walker.finish().issues.iter().any(|issue| {
            matches!(issue, melee_dat::walk::Issue::AmbiguousUnion { path, .. } if path == "unbound")
        }));
    }
}
