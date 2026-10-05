//! `dat_symbols.txt`: the types of the archive symbols the game looks up by
//! name, which are the roots everything else in an archive is reached from.
//!
//! One line per root, in the style of `symbols.txt`:
//!
//! ```text
//! ftDataMars = PlMs.dat:*; // type:ftData
//! map_head = *:*; // type:MapHead
//! *_figatree = Pl??AJ.dat:*; // type:FigaTree
//! ```
//!
//! The location is `dat:address`. The dat is an archive path relative to
//! the dat base, or `*` for every archive with a public symbol of that name.
//! An address of `*` matches a public symbol by name; names and dats may use
//! `*` and `?` wildcards, and the first line with a matching dat wins, then
//! the first `*` line. An address instead names data no public symbol does,
//! such as a root nothing points to, with a C alias:
//!
//! ```text
//! ftDataEmblem_unused_joint = PlFe.dat:0x3AD70; // type:HSD_Joint
//! ```

use anyhow::{Context, Result, anyhow, bail};
use std::{fmt, str::FromStr};
use winnow::{
    ModalResult, Parser,
    ascii::{digit1, hex_digit1, space0, space1},
    combinator::{alt, cut_err, delimited, eof, opt, preceded, separated},
    token::take_till,
};

#[derive(Debug, Clone, PartialEq, Eq, PartialOrd, Ord, Hash)]
pub enum Location {
    Any,
    Archive(String),
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum Count {
    One,
    Exactly(u64),
    /// As many as fit before the next symbol.
    Unbounded,
}

/// `name = dat:address; // attrs`, like decomp-toolkit's `symbols.txt`
/// with the dat in the section's place. With `*` for the address, `name`
/// is a public symbol's, matched by name (and `*`/`?` globs); with an
/// address, `name` is a C alias for data no public symbol names, such as
/// a root nothing points to.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Entry {
    pub name: String,
    pub location: Location,
    /// Where in the dat's data, for an alias; `None` (`*`) for a public
    /// symbol. In a file packing several archives, in the first.
    pub address: Option<u32>,
    /// `type:T`, like `DAT_TYPE(T)`: the type a root no loader types is.
    pub ty: Option<String>,
    /// How many of the root's type there are, whether its loader or `type:`
    /// gives it: `count:N`, like `DAT_COUNT(N)`, or `extent`, like
    /// `DAT_EXTENT`, for as many as fit before the next symbol or pointer
    /// target.
    pub count: Option<Count>,
    /// Attributes other than `type` and `count`, kept verbatim and in order.
    pub other: Vec<String>,
}

#[derive(Debug, Clone, Default, PartialEq, Eq)]
pub struct SymbolFile {
    pub entries: Vec<Entry>,
}

impl SymbolFile {
    pub fn parse(text: &str) -> Result<Self> {
        let entries = text
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
        Ok(SymbolFile { entries })
    }

    /// Sorted by name, then `*` before archives, so output is stable.
    pub fn sort(&mut self) {
        self.entries.sort_by(|a, b| {
            (&a.name, &a.location).cmp(&(&b.name, &b.location))
        });
    }

    /// The entry that applies to a symbol in an archive, if any.
    /// The aliases for data at addresses in `archive`, by address.
    pub fn aliases(&self, archive: &str) -> Vec<(u32, &Entry)> {
        self.entries
            .iter()
            .filter_map(|e| match (&e.location, e.address) {
                (Location::Archive(a), Some(address)) if glob(a, archive) => {
                    Some((address, e))
                }
                _ => None,
            })
            .collect()
    }

    pub fn lookup(&self, name: &str, archive: &str) -> Option<&Entry> {
        let mut any = None;
        for entry in self
            .entries
            .iter()
            .filter(|e| e.address.is_none() && glob(&e.name, name))
        {
            match &entry.location {
                Location::Archive(a) if glob(a, archive) => {
                    return Some(entry);
                }
                Location::Any => {
                    any.get_or_insert(entry);
                }
                Location::Archive(_) => {}
            }
        }
        any
    }
}

/// Whether `text` matches `pattern`, where `*` is any run of characters and
/// `?` any one character.
fn glob(pattern: &str, text: &str) -> bool {
    let (pattern, text) = (pattern.as_bytes(), text.as_bytes());
    let (mut p, mut t) = (0, 0);
    // Where to resume after the last `*`: its position and the text it took
    let mut star = None;
    while t < text.len() {
        match pattern.get(p) {
            Some(b'*') => {
                star = Some((p, t));
                p += 1;
            }
            Some(&c) if c == b'?' || c == text[t] => {
                p += 1;
                t += 1;
            }
            _ => match star {
                Some((sp, st)) => {
                    star = Some((sp, st + 1));
                    p = sp + 1;
                    t = st + 1;
                }
                None => return false,
            },
        }
    }
    pattern[p..].iter().all(|&c| c == b'*')
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
        let mut other = Vec::new();
        for attr in entry.attrs {
            match attr {
                Attr::Type(spec) => ty = Some(spec),
                Attr::Count(n) => count = Some(n),
                Attr::Other(attr) => other.push(attr.to_owned()),
            }
        }
        // An alias names one place: a C identifier, in a dat, of a type
        if entry.address.is_some() {
            let identifier = entry
                .name
                .chars()
                .next()
                .is_some_and(|c| c.is_ascii_alphabetic() || c == '_')
                && entry.name.chars().all(|c| c.is_ascii_alphanumeric() || c == '_');
            if !identifier {
                bail!("`{}` at an address isn't a C identifier", entry.name);
            }
            if entry.location == Location::Any {
                bail!("`{}` at an address needs a dat", entry.name);
            }
            if ty.is_none() {
                bail!("`{}` at an address needs a `type:`", entry.name);
            }
        }
        Ok(Entry {
            name: entry.name.to_owned(),
            location: entry.location,
            address: entry.address,
            ty,
            count,
            other,
        })
    }
}

/// An entry as written, before its attributes are checked.
struct RawEntry<'i> {
    name: &'i str,
    location: Location,
    address: Option<u32>,
    attrs: Vec<Attr<'i>>,
}

enum Attr<'i> {
    Type(String),
    Count(Count),
    Other(&'i str),
}

/// `name = dat:address; // attr attr ...`, either part `*`.
fn entry<'i>(input: &mut &'i str) -> ModalResult<RawEntry<'i>> {
    let name = preceded(space0, word).parse_next(input)?;
    let (location, address) = delimited(
        (space0, '=', space0),
        (
            alt((
                '*'.value(Location::Any),
                dat.map(|a: &str| Location::Archive(a.to_owned())),
            )),
            preceded(
                cut_err(':'),
                cut_err(alt(('*'.value(None), integer.map(|n| Some(n as u32))))),
            ),
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
        location,
        address,
        attrs,
    })
}

/// A dat's file name, or a glob of them: up to the `:` before the address.
fn dat<'i>(input: &mut &'i str) -> ModalResult<&'i str> {
    take_till(1.., |c: char| c.is_whitespace() || c == ':' || c == ';')
        .parse_next(input)
}

fn attr<'i>(input: &mut &'i str) -> ModalResult<Attr<'i>> {
    alt((
        preceded("type:", cut_err(type_name)).map(Attr::Type),
        preceded("count:", cut_err(integer))
            .map(|n| Attr::Count(Count::Exactly(n))),
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
        let location = match &self.location {
            Location::Any => "*",
            Location::Archive(archive) => archive,
        };
        let address = match self.address {
            Some(address) => format!("{address:#X}"),
            None => "*".to_owned(),
        };
        write!(f, "{} = {location}:{address};", self.name)?;
        let attrs: Vec<String> = self
            .ty
            .iter()
            .map(|ty| format!("type:{ty}"))
            .chain(self.count.map(|count| match count {
                Count::One => "count:1".to_owned(),
                Count::Exactly(n) => format!("count:{n}"),
                Count::Unbounded => "extent".to_owned(),
            }))
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

    const TEXT: &str = "\
ftDataMars = PlMs.dat:*; // type:ftData
map_head = *:*; // type:MapHead extent
grGroundParam = *:*; // type:grGroundParam count:2 data:4byte
itemdata = GrI2.dat:*;
map_plit = *:*; // extent
ScGamRegStaffrollNames_scene_modelset = GmStRoll.dat:*; // count:10
";

    #[test]
    fn round_trip() {
        let file = SymbolFile::parse(TEXT).unwrap();
        assert_eq!(file.to_string(), TEXT);
        assert_eq!(file.entries[1].ty.as_deref(), Some("MapHead"));
        assert_eq!(file.entries[1].count, Some(Count::Unbounded));
        assert_eq!(file.entries[2].count, Some(Count::Exactly(2)));
        assert_eq!(file.entries[2].other, ["data:4byte"]);
        assert_eq!(file.entries[4].count, Some(Count::Unbounded));
        assert_eq!(file.entries[5].count, Some(Count::Exactly(10)));
    }

    #[test]
    fn aliases() {
        let file = SymbolFile::parse(concat!(
            "ftDataEmblem_unused_joint = PlFe.dat:0x3AD70; // type:HSD_Joint\n",
            "ftDataEmblem = PlFe.dat:*; // type:ftData\n",
        ))
        .unwrap();
        assert_eq!(file.to_string().lines().next(), Some(
            "ftDataEmblem_unused_joint = PlFe.dat:0x3AD70; // type:HSD_Joint"
        ));
        let aliases = file.aliases("PlFe.dat");
        assert_eq!(aliases.len(), 1);
        assert_eq!(aliases[0].0, 0x3AD70);
        assert!(file.aliases("PlMs.dat").is_empty());
        // An alias isn't a public symbol's entry
        assert_eq!(
            file.lookup("ftDataEmblem_unused_joint", "PlFe.dat"),
            None
        );
        // An alias needs a dat, a type and a C name
        for bad in [
            "x = *:0x10; // type:T",
            "x = PlFe.dat:0x10;",
            "x_* = PlFe.dat:0x10; // type:T",
        ] {
            assert!(SymbolFile::parse(bad).is_err(), "{bad}");
        }
    }

    #[test]
    fn archive_overrides_any() {
        let file = SymbolFile::parse(
            "map_head = *:*; // type:A\nmap_head = GrNLa.dat:*; // type:B\n",
        )
        .unwrap();
        let ty = |archive| file.lookup("map_head", archive)?.ty.clone();
        assert_eq!(ty("GrNLa.dat").as_deref(), Some("B"));
        assert_eq!(ty("GrMc.dat").as_deref(), Some("A"));
    }

    #[test]
    fn wildcards() {
        let file = SymbolFile::parse(
            "*_figatree = Pl??AJ.dat:*; // type:FigaTree\n\
             *_joint = *:*; // type:HSD_JObjDesc\n",
        )
        .unwrap();
        let ty = |name, archive| file.lookup(name, archive)?.ty.clone();
        assert_eq!(
            ty("PlyCaptain5K_Share_ACTION_Wait1_figatree", "PlCaAJ.dat")
                .as_deref(),
            Some("FigaTree")
        );
        assert_eq!(ty("x_figatree", "PlCaAJx.dat"), None);
        assert_eq!(
            ty("TyMario_joint", "TyMario.dat").as_deref(),
            Some("HSD_JObjDesc")
        );
        assert_eq!(ty("joint", "TyMario.dat"), None);
        assert!(glob("a*b*c", "aXbYbZc"));
        assert!(!glob("a*b", "aXbY"));
    }

    #[test]
    fn rejects_malformed() {
        assert!("foo = ;".parse::<Entry>().is_err());
        assert!("foo = *".parse::<Entry>().is_err());
        assert!("foo = *; // type:A type:B".parse::<Entry>().is_err());
        assert!("foo = *; // type:A[x]".parse::<Entry>().is_err());
    }
}
