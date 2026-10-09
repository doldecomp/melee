//! `dat_symbols.txt`: explicit types and counts for public symbols and
//! aliases. See `tools/dat-cli/symbols.md` for the format.

use crate::dwarf::annotation::{DatTag, Script};
use crate::hsd::Archive;
use anyhow::{Context, Result, anyhow, bail};
use std::{
    collections::{BTreeMap, BTreeSet},
    fmt,
    str::FromStr,
};
use winnow::{
    ModalResult, Parser,
    ascii::{digit1, hex_digit1, space0, space1},
    combinator::{alt, cut_err, delimited, eof, opt, preceded, separated},
    token::take_till,
};

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum Count {
    One,
    Exactly(u64),
    /// As many as fit before the next symbol.
    Unbounded,
    /// Up to and including the first element whose first word (or whole
    /// value, if smaller) is this and not a relocated pointer, like
    /// `DAT_TERMINATED`.
    Terminated(u64),
}

/// `name = archive:address; // attrs`. A public symbol matches by name and
/// address; another name gives a C alias for data no public symbol names.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Entry {
    pub name: String,
    /// File relative to the archive base, with `@0xOFFSET` for a packed
    /// archive after the first.
    pub archive: String,
    /// Offset from the start of this archive's data, after its header.
    pub address: u32,
    /// `type:T`, like `DAT_TYPE(T)`: the type a root no loader types is.
    pub ty: Option<String>,
    /// How many of the root's type there are, whether its loader or `type:`
    /// gives it: `count:N`, like `DAT_COUNT(N)`, or `extent`, like
    /// `DAT_EXTENT`, for as many as fit before the next symbol or pointer
    /// target.
    pub count: Option<Count>,
    /// `script:S`, like `DAT_SCRIPT(S)`: the root is a command script, its
    /// commands from opcode 10 as long as the table or expression `S` says.
    pub script: Option<String>,
    /// Attributes other than `type` and `count`, kept verbatim and in order.
    pub other: Vec<String>,
}

#[derive(Debug, Clone, Default, PartialEq, Eq)]
pub struct SymbolFile {
    entries: Vec<Entry>,
    by_archive: BTreeMap<String, Vec<usize>>,
}

impl SymbolFile {
    pub fn parse(text: &str) -> Result<Self> {
        let entries: Vec<Entry> = text
            .lines()
            .enumerate()
            .filter(|(_, line)| {
                let line = line.trim();
                !line.is_empty() && !line.starts_with("//")
            })
            .map(|(index, line)| {
                line.parse()
                    .with_context(|| format!("line {}: {line}", index + 1))
            })
            .collect::<Result<_>>()?;
        let mut by_archive: BTreeMap<String, Vec<usize>> = BTreeMap::new();
        let mut names = BTreeSet::new();
        for (index, entry) in entries.iter().enumerate() {
            if !names.insert((&entry.archive, &entry.name)) {
                bail!("{}: duplicate symbol `{}`", entry.archive, entry.name);
            }
            by_archive
                .entry(entry.archive.clone())
                .or_default()
                .push(index);
        }
        Ok(SymbolFile {
            entries,
            by_archive,
        })
    }

    pub fn entries(&self) -> impl Iterator<Item = &Entry> {
        self.entries.iter()
    }

    fn in_archive(&self, archive: &str) -> impl Iterator<Item = &Entry> {
        self.by_archive
            .get(archive)
            .into_iter()
            .flatten()
            .map(|&index| &self.entries[index])
    }

    /// Entries that do not name a public symbol in this archive.
    pub fn aliases(
        &self,
        name: &str,
        archive: &Archive,
    ) -> Vec<(u32, &Entry)> {
        let publics: BTreeSet<_> = archive
            .named_publics()
            .map(|(name, symbol)| (name, symbol.offset))
            .collect();
        self.in_archive(name)
            .filter(|entry| {
                !publics.contains(&(entry.name.as_bytes(), entry.address))
            })
            .map(|entry| (entry.address, entry))
            .collect()
    }

    pub fn lookup(
        &self,
        name: &str,
        archive: &str,
        address: u32,
    ) -> Option<&Entry> {
        self.in_archive(archive)
            .find(|entry| entry.name == name && entry.address == address)
    }
}

impl fmt::Display for SymbolFile {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        for entry in &self.entries {
            writeln!(f, "{entry}")?;
        }
        Ok(())
    }
}

impl FromStr for Entry {
    type Err = anyhow::Error;

    fn from_str(line: &str) -> Result<Self> {
        let entry = entry.parse(line).map_err(|e| anyhow!("\n{e}"))?;
        let types = entry.attrs.iter().filter(|a| matches!(a, Attr::Type(_)));
        if types.count() > 1 {
            bail!("more than one `type`");
        }
        let mut ty = None;
        let mut count = None;
        let mut script = None;
        let mut other = Vec::new();
        for attr in entry.attrs {
            match attr {
                Attr::Type(spec) => ty = Some(spec),
                Attr::Count(n) => count = Some(n),
                Attr::Script(table) => script = Some(table.to_owned()),
                Attr::Other(attr) => other.push(attr.to_owned()),
            }
        }
        let identifier = entry
            .name
            .chars()
            .next()
            .is_some_and(|c| c.is_ascii_alphabetic() || c == '_')
            && entry
                .name
                .chars()
                .all(|c| c.is_ascii_alphanumeric() || c == '_');
        if !identifier {
            bail!("`{}` isn't a C identifier", entry.name);
        }
        if entry.archive.contains(['*', '?']) {
            bail!("`{}` needs an explicit archive", entry.name);
        }
        Ok(Entry {
            name: entry.name.to_owned(),
            archive: entry.archive.to_owned(),
            address: entry.address,
            ty,
            count,
            script,
            other,
        })
    }
}

impl Entry {
    /// `script:`'s argument, as `DAT_SCRIPT` takes it.
    pub fn script(&self) -> Option<Script> {
        let script = self.script.as_ref()?;
        match DatTag::parse(&format!("dat:script({script})"))? {
            DatTag::Script(script) => Some(script),
            _ => None,
        }
    }
}

/// An entry as written, before its attributes are checked.
struct RawEntry<'i> {
    name: &'i str,
    archive: &'i str,
    address: u32,
    attrs: Vec<Attr<'i>>,
}

enum Attr<'i> {
    Type(String),
    Count(Count),
    Script(&'i str),
    Other(&'i str),
}

/// `name = archive:address; // attr attr ...`.
fn entry<'i>(input: &mut &'i str) -> ModalResult<RawEntry<'i>> {
    let name = preceded(space0, word).parse_next(input)?;
    let (archive, address) = delimited(
        (space0, '=', space0),
        (
            dat,
            preceded(cut_err(':'), cut_err(integer.try_map(u32::try_from))),
        ),
        (space0, cut_err(';'), space0),
    )
    .parse_next(input)?;
    let attrs = opt(preceded(("//", space0), separated(0.., attr, space1)))
        .parse_next(input)?
        .unwrap_or_default();
    (space0, eof).parse_next(input)?;
    Ok(RawEntry {
        name,
        archive,
        address,
        attrs,
    })
}

/// An archive name, up to the `:` before the address.
fn dat<'i>(input: &mut &'i str) -> ModalResult<&'i str> {
    take_till(1.., |c: char| c.is_whitespace() || c == ':' || c == ';')
        .parse_next(input)
}

fn attr<'i>(input: &mut &'i str) -> ModalResult<Attr<'i>> {
    alt((
        preceded("type:", cut_err(type_name)).map(Attr::Type),
        preceded("count:", cut_err(integer))
            .map(|n| Attr::Count(Count::Exactly(n))),
        preceded("terminated:", cut_err(integer))
            .map(|v| Attr::Count(Count::Terminated(v))),
        preceded("script:", cut_err(take_till(1.., char::is_whitespace)))
            .map(Attr::Script),
        take_till(1.., char::is_whitespace).map(|word| match word {
            "extent" => Attr::Count(Count::Unbounded),
            word => Attr::Other(word),
        }),
    ))
    .parse_next(input)
}

/// A token up to whitespace, `=` or `;`.
fn word<'i>(input: &mut &'i str) -> ModalResult<&'i str> {
    take_till(1.., |c: char| c.is_whitespace() || c == '=' || c == ';')
        .parse_next(input)
}

/// A type name, as `DAT_TYPE` takes it: `HSD_Joint`, `u8*`. A count is
/// its own attribute, so `[` isn't part of one.
fn type_name(input: &mut &str) -> ModalResult<String> {
    take_till(1.., |c: char| c.is_whitespace() || c == '[')
        .map(str::to_owned)
        .parse_next(input)
}

fn integer(input: &mut &str) -> ModalResult<u64> {
    alt((
        preceded("0x", hex_digit1).try_map(|h| u64::from_str_radix(h, 16)),
        digit1.try_map(str::parse),
    ))
    .parse_next(input)
}

impl fmt::Display for Entry {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "{} = {}:{:#X};", self.name, self.archive, self.address)?;
        let attrs: Vec<String> = self
            .ty
            .iter()
            .map(|ty| format!("type:{ty}"))
            .chain(self.count.map(|count| match count {
                Count::One => "count:1".to_owned(),
                Count::Exactly(n) => format!("count:{n}"),
                Count::Unbounded => "extent".to_owned(),
                Count::Terminated(v) => format!("terminated:{v:#X}"),
            }))
            .chain(self.script.iter().map(|table| format!("script:{table}")))
            .chain(self.other.iter().cloned())
            .collect();
        if !attrs.is_empty() {
            write!(f, " // {}", attrs.join(" "))?;
        }
        Ok(())
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::hsd::{ArchiveHeader, NamedSymbol, archive_name};

    const TEXT: &str = "\
ftDataMars = PlMs.dat:0x10; // type:ftData
map_head = GrNLa.dat:0x20; // type:MapHead extent
grGroundParam = GrNLa.dat:0x30; // type:grGroundParam count:2 data:4byte
itemdata = GrI2.dat:0x0;
map_plit = GrNLa.dat:0x40; // terminated:0x0
ScGamRegStaffrollNames_scene_modelset = GmStRoll.dat:0x50; // count:10
PlCo_unused_x10 = PlCo.dat:0x10; // type:CmdUnion script:ftAction_803C0870
";

    fn archive() -> Archive<'static> {
        Archive {
            header: ArchiveHeader {
                file_size: 80,
                data_size: 32,
                reloc_count: 0,
                public_count: 1,
                extern_count: 0,
                version: [0; 12],
            },
            data: &[0; 32],
            relocs: Vec::new(),
            publics: vec![NamedSymbol {
                offset: 0x10,
                symbol: 0,
            }],
            externs: Vec::new(),
            symbols: b"root\0",
        }
    }

    #[test]
    fn round_trip() {
        let file = SymbolFile::parse(TEXT).unwrap();
        assert_eq!(file.to_string(), TEXT);
        let entries: Vec<_> = file.entries().collect();
        assert_eq!(entries[1].ty.as_deref(), Some("MapHead"));
        assert_eq!(entries[1].count, Some(Count::Unbounded));
        assert_eq!(entries[2].count, Some(Count::Exactly(2)));
        assert_eq!(entries[2].other, ["data:4byte"]);
        assert_eq!(entries[3].address, 0);
        assert_eq!(entries[3].ty, None);
        assert_eq!(entries[4].count, Some(Count::Terminated(0)));
        assert_eq!(entries[5].count, Some(Count::Exactly(10)));
        assert_eq!(entries[6].script.as_deref(), Some("ftAction_803C0870"));
    }

    #[test]
    fn aliases_preserve_order_and_exclude_publics() {
        let file = SymbolFile::parse(concat!(
            "last = PlCo.dat:0x18; // type:T\n",
            "root = PlCo.dat:0x10; // count:2\n",
            "first = PlCo.dat:0x8; // type:T\n",
            "other = PlMs.dat:0x4; // type:T\n",
        ))
        .unwrap();
        let archive = archive();
        let aliases = file.aliases("PlCo.dat", &archive);
        assert_eq!(
            aliases
                .iter()
                .map(|(at, entry)| (*at, entry.name.as_str()))
                .collect::<Vec<_>>(),
            [(0x18, "last"), (8, "first")]
        );
        assert!(file.aliases("PlFe.dat", &archive).is_empty());
        assert_eq!(
            file.lookup("root", "PlCo.dat", 0x10).unwrap().count,
            Some(Count::Exactly(2))
        );
    }

    #[test]
    fn exact_names_and_addresses() {
        let file = SymbolFile::parse(TEXT).unwrap();
        assert!(file.lookup("map_head", "GrNLa.dat", 0x20).is_some());
        assert!(file.lookup("map_head", "GrMc.dat", 0x20).is_none());
        assert!(file.lookup("map_head", "GrNLa.dat", 0x24).is_none());
        assert!(file.lookup("map_head_extra", "GrNLa.dat", 0x20).is_none());
    }

    #[test]
    fn packed_archives_keep_separate_entries_at_the_same_local_offset() {
        let file = SymbolFile::parse(concat!(
            "root = PlCoAJ.dat:0x10; // type:A count:1\n",
            "root = PlCoAJ.dat@0x80:0x10; // type:B count:2\n",
            "unused = PlCoAJ.dat@0x80:0x8; // type:C\n",
        ))
        .unwrap();
        let first = archive_name("PlCoAJ.dat", 0);
        let next = archive_name("PlCoAJ.dat", 0x80);
        assert_eq!(
            file.lookup("root", &first, 0x10).unwrap().ty.as_deref(),
            Some("A")
        );
        assert_eq!(
            file.lookup("root", &next, 0x10).unwrap().ty.as_deref(),
            Some("B")
        );
        assert!(file.lookup("unused", &first, 8).is_none());
        assert!(file.aliases(&first, &archive()).is_empty());
        assert_eq!(file.aliases(&next, &archive())[0].1.name, "unused");
    }

    #[test]
    fn rejects_wildcards_overflow_and_duplicate_names() {
        for bad in [
            "foo = ;",
            "foo = *",
            "foo = *:0x10; // type:T",
            "foo = Pl??.dat:0x10; // type:T",
            "foo = PlCo.dat:*; // type:T",
            "foo_* = PlCo.dat:0x10; // type:T",
            "1foo = PlCo.dat:0x10; // type:T",
            "foo = PlCo.dat:0x100000000; // type:T",
            "foo = PlCo.dat:4294967296; // type:T",
            "foo = PlCo.dat:0x10; // type:A type:B",
            "foo = PlCo.dat:0x10; // type:A[x]",
            "foo = PlCo.dat:0x10;\nfoo = PlCo.dat:0x20;",
        ] {
            assert!(SymbolFile::parse(bad).is_err(), "{bad}");
        }
        assert_eq!(
            "foo = PlCo.dat:16; // count:0"
                .parse::<Entry>()
                .unwrap()
                .address,
            16
        );
    }
}
