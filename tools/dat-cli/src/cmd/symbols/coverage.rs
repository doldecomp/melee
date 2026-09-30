//! `symbols coverage`: how much of each archive the walk explains.

use super::{Project, args};
use anyhow::Result;
use globset::{Glob, GlobSetBuilder};
use melee_dat::coverage::{Kind, coverage, family, generic_path};
use serde::Serialize;
use std::{
    collections::BTreeMap,
    io::{self, Write},
};

#[derive(Clone, Copy, Default, clap::ValueEnum)]
pub enum View {
    /// One row per archive family (`Pl`, `Gr`, ...)
    #[default]
    Family,
    /// One row per archive, by gap
    Archive,
    /// Unexplained relocations by the object they follow
    Owner,
    /// Pointer fields the walk could not follow (`void*`)
    Field,
    /// Public symbols with no type
    Public,
}

#[derive(Clone, Copy, Default, clap::ValueEnum)]
pub enum Format {
    #[default]
    Table,
    /// A report shaped like objdiff's `report.json`
    Json,
}

/// Counts shared by the whole report, categories and units.
#[derive(Serialize, Clone, Default)]
struct Measures {
    total_relocations: u64,
    explained_relocations: u64,
    explained_relocations_percent: f32,
    /// Unexplained, inside a typed object or in data a pointer reaches: a
    /// missing or wrong type.
    gap_relocations: u64,
    /// Unexplained, after a typed object's end where nothing points: the
    /// type is too short, or the data after it is unreferenced.
    trailing_relocations: u64,
    /// Unexplained, in data nothing reaches: no type can explain them.
    unreferenced_relocations: u64,
    /// Explained, out of those not unreferenced.
    reachable_relocations_percent: f32,
    total_publics: u64,
    typed_publics: u64,
    typed_publics_percent: f32,
    total_units: u64,
    /// Units with at least one root.
    walked_units: u64,
}

impl Measures {
    fn add(&mut self, other: &Measures) {
        self.total_relocations += other.total_relocations;
        self.explained_relocations += other.explained_relocations;
        self.gap_relocations += other.gap_relocations;
        self.trailing_relocations += other.trailing_relocations;
        self.unreferenced_relocations += other.unreferenced_relocations;
        self.total_publics += other.total_publics;
        self.typed_publics += other.typed_publics;
        self.total_units += other.total_units;
        self.walked_units += other.walked_units;
        self.finish();
    }

    fn finish(&mut self) {
        // Out of those some type could explain
        let percent = |n: u64, d: u64| match d {
            0 => 100.0,
            _ => (n as f64 * 100.0 / d as f64) as f32,
        };
        self.explained_relocations_percent =
            percent(self.explained_relocations, self.total_relocations);
        self.reachable_relocations_percent = percent(
            self.explained_relocations,
            self.total_relocations - self.unreferenced_relocations,
        );
        self.typed_publics_percent =
            percent(self.typed_publics, self.total_publics);
    }
}

#[derive(Serialize)]
struct Report {
    version: u32,
    measures: Measures,
    units: Vec<Unit>,
    categories: Vec<Category>,
}

#[derive(Serialize)]
struct Category {
    id: String,
    name: String,
    measures: Measures,
}

#[derive(Serialize)]
struct Unit {
    /// The archive: its file, with `@0xOFFSET` inside packed files.
    name: String,
    measures: Measures,
    metadata: UnitMetadata,
    /// Unexplained relocations by the object they follow.
    owners: Vec<Owner>,
    untyped_publics: Vec<String>,
    /// Pointer fields the walk could not follow, by path.
    untyped_fields: BTreeMap<String, usize>,
    /// Every unexplained relocation, with `--list`.
    #[serde(skip_serializing_if = "Option::is_none")]
    relocations: Option<Vec<Relocation>>,
}

#[derive(Serialize)]
struct UnitMetadata {
    file: String,
    family: String,
    /// Offset of the archive in its file.
    offset: usize,
}

#[derive(Serialize, Clone)]
struct Owner {
    /// Type of the nearest object the walk typed before the relocations.
    #[serde(rename = "type")]
    ty: String,
    /// Its path from the root, without names and indices.
    path: String,
    gap: u64,
    trailing: u64,
    unreferenced: u64,
}

#[derive(Serialize)]
struct Relocation {
    offset: u32,
    kind: Kind,
    owner_offset: Option<u32>,
    owner_type: Option<String>,
    owner_path: Option<String>,
}

pub fn run(args: args::Coverage) -> Result<()> {
    let project = Project::load(&args.check)?;
    let mut only = GlobSetBuilder::new();
    for glob in &args.archive {
        only.add(Glob::new(glob)?);
    }
    let only = only.build()?;

    let mut units = Vec::new();
    project.walk_all(&only, |w| {
        let cov =
            coverage(&project.graph, &project.canonical, w.archive, &w.result);
        let typed = w
            .archive
            .publics
            .iter()
            .filter(|p| w.result.objects.contains_key(&p.offset))
            .count();
        let mut measures = Measures {
            total_relocations: cov.relocs as u64,
            explained_relocations: cov.explained as u64,
            gap_relocations: cov.count(Kind::Gap) as u64,
            trailing_relocations: cov.count(Kind::Trailing) as u64,
            unreferenced_relocations: cov.count(Kind::Unreferenced) as u64,
            total_publics: w.archive.publics.len() as u64,
            typed_publics: typed as u64,
            total_units: 1,
            walked_units: u64::from(w.rooted),
            ..Default::default()
        };
        measures.finish();

        let owner_of = |offset: Option<u32>| {
            offset.map(|o| {
                let path = w.result.paths.get(&o).map_or("", String::as_str);
                (project.object_type(&w.result, o), generic_path(path))
            })
        };
        let mut owners: BTreeMap<(String, String), Owner> = BTreeMap::new();
        for u in &cov.unexplained {
            let (ty, path) =
                owner_of(u.owner).unwrap_or(("(none)".into(), String::new()));
            let owner =
                owners.entry((ty.clone(), path.clone())).or_insert(Owner {
                    ty,
                    path,
                    gap: 0,
                    trailing: 0,
                    unreferenced: 0,
                });
            match u.kind {
                Kind::Gap => owner.gap += 1,
                Kind::Trailing => owner.trailing += 1,
                Kind::Unreferenced => owner.unreferenced += 1,
            }
        }
        let mut owners: Vec<Owner> = owners.into_values().collect();
        owners.sort_by(|a, b| (b.gap, b.trailing).cmp(&(a.gap, a.trailing)));

        let relocations = args.list.then(|| {
            cov.unexplained
                .iter()
                .map(|u| {
                    let owner = owner_of(u.owner);
                    Relocation {
                        offset: u.at,
                        kind: u.kind,
                        owner_offset: u.owner,
                        owner_type: owner.as_ref().map(|o| o.0.clone()),
                        owner_path: owner.map(|o| o.1),
                    }
                })
                .collect()
        });
        let untyped_publics = w
            .archive
            .named_publics()
            .filter(|(_, p)| !w.result.objects.contains_key(&p.offset))
            .map(|(name, _)| String::from_utf8_lossy(name).into_owned())
            .collect();
        let offset = w
            .name
            .split_once('@')
            .and_then(|(_, o)| usize::from_str_radix(&o[2..], 16).ok())
            .unwrap_or(0);
        units.push(Unit {
            name: w.name,
            measures,
            metadata: UnitMetadata {
                file: w.file.to_owned(),
                family: family(w.file).to_owned(),
                offset,
            },
            owners,
            untyped_publics,
            untyped_fields: w.result.untyped_fields,
            relocations,
        });
        Ok(())
    })?;

    let mut total = Measures::default();
    let mut families: BTreeMap<String, Measures> = BTreeMap::new();
    for unit in &units {
        total.add(&unit.measures);
        families
            .entry(unit.metadata.family.clone())
            .or_default()
            .add(&unit.measures);
    }
    let report = Report {
        version: 1,
        measures: total,
        categories: families
            .into_iter()
            .map(|(id, measures)| Category {
                name: id.clone(),
                id,
                measures,
            })
            .collect(),
        units,
    };

    let mut out = io::stdout().lock();
    match args.format {
        Format::Json => {
            serde_json::to_writer_pretty(&mut out, &report)?;
            writeln!(out)?;
        }
        Format::Table => {
            table(&mut out, &report, args.by, args.top, args.list)?
        }
    }
    Ok(())
}

fn table(
    out: &mut impl Write,
    report: &Report,
    view: View,
    top: usize,
    list: bool,
) -> Result<()> {
    let limit = |n: usize| if top == 0 { n } else { n.min(top) };
    let measures_header = [
        "archives",
        "publics",
        "typed",
        "relocations",
        "explained",
        "gap",
        "trailing",
        "unreferenced",
        "reachable",
    ];
    let measures_row = |m: &Measures| {
        vec![
            format!("{}/{}", m.walked_units, m.total_units),
            m.total_publics.to_string(),
            format!("{:.1}%", m.typed_publics_percent),
            m.total_relocations.to_string(),
            format!("{:.1}%", m.explained_relocations_percent),
            m.gap_relocations.to_string(),
            m.trailing_relocations.to_string(),
            m.unreferenced_relocations.to_string(),
            format!("{:.1}%", m.reachable_relocations_percent),
        ]
    };
    let mut rows: Vec<Vec<String>> = Vec::new();
    match view {
        View::Family => {
            rows.push(
                std::iter::once("family")
                    .chain(measures_header)
                    .map(String::from)
                    .collect(),
            );
            for c in &report.categories {
                let mut row = vec![c.id.clone()];
                row.extend(measures_row(&c.measures));
                rows.push(row);
            }
        }
        View::Archive => {
            rows.push(
                std::iter::once("archive")
                    .chain(measures_header.into_iter().skip(1))
                    .map(String::from)
                    .collect(),
            );
            let mut units: Vec<&Unit> = report.units.iter().collect();
            units.sort_by_key(|u| {
                std::cmp::Reverse(u.measures.gap_relocations)
            });
            for u in &units[..limit(units.len())] {
                let mut row = vec![u.name.clone()];
                row.extend(measures_row(&u.measures).into_iter().skip(1));
                rows.push(row);
            }
        }
        View::Owner => {
            rows.push(
                [
                    "gap",
                    "trailing",
                    "unreferenced",
                    "archives",
                    "type",
                    "path",
                ]
                .map(String::from)
                .to_vec(),
            );
            let mut owners: BTreeMap<(&str, &str), (u64, u64, u64, usize)> =
                BTreeMap::new();
            for u in &report.units {
                for o in &u.owners {
                    let e = owners.entry((&o.ty, &o.path)).or_default();
                    e.0 += o.gap;
                    e.1 += o.trailing;
                    e.2 += o.unreferenced;
                    e.3 += 1;
                }
            }
            let mut owners: Vec<_> = owners.into_iter().collect();
            owners.sort_by_key(|(_, (gap, trailing, _, _))| {
                std::cmp::Reverse((*gap, *trailing))
            });
            for ((ty, path), (gap, trailing, unref, n)) in
                &owners[..limit(owners.len())]
            {
                rows.push(vec![
                    gap.to_string(),
                    trailing.to_string(),
                    unref.to_string(),
                    n.to_string(),
                    ty.to_string(),
                    path.to_string(),
                ]);
            }
        }
        View::Field => {
            rows.push(
                ["pointers", "family", "path"].map(String::from).to_vec(),
            );
            let mut fields: BTreeMap<(&str, &str), usize> = BTreeMap::new();
            for u in &report.units {
                for (path, n) in &u.untyped_fields {
                    *fields.entry((&u.metadata.family, path)).or_default() +=
                        n;
                }
            }
            let mut fields: Vec<_> = fields.into_iter().collect();
            fields.sort_by_key(|(_, n)| std::cmp::Reverse(*n));
            for ((family, path), n) in &fields[..limit(fields.len())] {
                rows.push(vec![
                    n.to_string(),
                    family.to_string(),
                    path.to_string(),
                ]);
            }
        }
        View::Public => {
            rows.push(["archive", "public"].map(String::from).to_vec());
            let publics: Vec<_> = report
                .units
                .iter()
                .flat_map(|u| u.untyped_publics.iter().map(move |p| (u, p)))
                .collect();
            for (u, p) in &publics[..limit(publics.len())] {
                rows.push(vec![u.name.clone(), p.to_string()]);
            }
        }
    }
    if matches!(view, View::Family | View::Archive) {
        let mut row = vec!["total".to_owned()];
        let mut m = measures_row(&report.measures);
        if matches!(view, View::Archive) {
            m.remove(0);
        }
        row.extend(m);
        rows.push(row);
    }
    print_rows(out, &rows)?;

    if list {
        writeln!(out)?;
        let mut rows = vec![
            ["archive", "offset", "status", "after", "type", "path"]
                .map(String::from)
                .to_vec(),
        ];
        for u in &report.units {
            for r in u.relocations.iter().flatten() {
                rows.push(vec![
                    u.name.clone(),
                    format!("0x{:X}", r.offset),
                    serde_json::to_value(r.kind)?
                        .as_str()
                        .unwrap_or_default()
                        .to_owned(),
                    r.owner_offset.map_or("-".into(), |o| format!("0x{o:X}")),
                    r.owner_type.clone().unwrap_or_default(),
                    r.owner_path.clone().unwrap_or_default(),
                ]);
            }
        }
        print_rows(out, &rows)?;
    }
    Ok(())
}

/// Columns padded to their widest cell; numbers right-aligned.
fn print_rows(out: &mut impl Write, rows: &[Vec<String>]) -> Result<()> {
    let columns = rows.iter().map(Vec::len).max().unwrap_or(0);
    let widths: Vec<usize> = (0..columns)
        .map(|c| {
            rows.iter()
                .filter_map(|r| r.get(c))
                .map(|s| s.chars().count())
                .max()
                .unwrap_or(0)
        })
        .collect();
    let numeric = |s: &str| {
        s.starts_with(|c: char| c.is_ascii_digit())
            && s.chars().all(|c| c.is_ascii_digit() || "./%x".contains(c))
    };
    for row in rows {
        let cells: Vec<String> = row
            .iter()
            .zip(&widths)
            .map(|(cell, &w)| match numeric(cell) {
                true => format!("{cell:>w$}"),
                false => format!("{cell:<w$}"),
            })
            .collect();
        writeln!(out, "{}", cells.join("  ").trim_end())?;
    }
    Ok(())
}
