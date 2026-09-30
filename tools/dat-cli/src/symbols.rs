//! `dat_symbols.txt`: the types of the archive symbols the game looks up by
//! name, which are the roots everything else in an archive is reached from.
//!
//! One line per root, in the style of `symbols.txt`:
//!
//! ```text
//! ftDataMars = PlMs.dat; // type:ftData
//! map_head = *; // type:MapHead
//! ```
//!
//! The location is an archive path relative to the assets base, or `*` for
//! every archive with a public symbol of that name. An archive-specific line
//! overrides a `*` line of the same name.

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

#[derive(Debug, Clone, PartialEq, Eq)]
pub struct TypeSpec {
    pub name: String,
    pub count: Count,
}

#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Entry {
    pub name: String,
    pub location: Location,
    pub ty: Option<TypeSpec>,
    /// Attributes other than `type`, kept verbatim and in order.
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
    pub fn lookup(&self, name: &str, archive: &str) -> Option<&Entry> {
        let mut any = None;
        for entry in self.entries.iter().filter(|e| e.name == name) {
            match &entry.location {
                Location::Archive(a) if a == archive => return Some(entry),
                Location::Any => any = Some(entry),
                Location::Archive(_) => {}
            }
        }
        any
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
        let mut other = Vec::new();
        for attr in entry.attrs {
            match attr {
                Attr::Type(spec) => ty = Some(spec),
                Attr::Other(attr) => other.push(attr.to_owned()),
            }
        }
        Ok(Entry {
            name: entry.name.to_owned(),
            location: entry.location,
            ty,
            other,
        })
    }
}

/// An entry as written, before its attributes are checked.
struct RawEntry<'i> {
    name: &'i str,
    location: Location,
    attrs: Vec<Attr<'i>>,
}

enum Attr<'i> {
    Type(TypeSpec),
    Other(&'i str),
}

/// `name = location; // attr attr ...`
fn entry<'i>(input: &mut &'i str) -> ModalResult<RawEntry<'i>> {
    let name = preceded(space0, word).parse_next(input)?;
    let location = delimited(
        (space0, '=', space0),
        alt((
            '*'.value(Location::Any),
            word.map(|a: &str| Location::Archive(a.to_owned())),
        )),
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
        attrs,
    })
}

fn attr<'i>(input: &mut &'i str) -> ModalResult<Attr<'i>> {
    alt((
        preceded("type:", cut_err(type_spec)).map(Attr::Type),
        take_till(1.., char::is_whitespace).map(Attr::Other),
    ))
    .parse_next(input)
}

/// A token up to whitespace, `=` or `;`.
fn word<'i>(input: &mut &'i str) -> ModalResult<&'i str> {
    take_till(1.., |c: char| c.is_whitespace() || c == '=' || c == ';')
        .parse_next(input)
}

/// `T`, `T[N]` or `T[]`.
fn type_spec(input: &mut &str) -> ModalResult<TypeSpec> {
    let name = take_till(1.., |c: char| c.is_whitespace() || c == '[')
        .parse_next(input)?;
    let count =
        opt(delimited('[', opt(integer), cut_err(']'))).parse_next(input)?;
    Ok(TypeSpec {
        name: name.to_owned(),
        count: match count {
            None => Count::One,
            Some(None) => Count::Unbounded,
            Some(Some(n)) => Count::Exactly(n),
        },
    })
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
        write!(f, "{} = {location};", self.name)?;
        let attrs: Vec<String> = self
            .ty
            .iter()
            .map(|ty| format!("type:{ty}"))
            .chain(self.other.iter().cloned())
            .collect();
        if !attrs.is_empty() {
            write!(f, " // {}", attrs.join(" "))?;
        }
        Ok(())
    }
}

impl FromStr for TypeSpec {
    type Err = anyhow::Error;

    fn from_str(spec: &str) -> Result<Self> {
        type_spec.parse(spec).map_err(|e| anyhow!("\n{e}"))
    }
}

impl fmt::Display for TypeSpec {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self.count {
            Count::One => write!(f, "{}", self.name),
            Count::Exactly(n) => write!(f, "{}[{n}]", self.name),
            Count::Unbounded => write!(f, "{}[]", self.name),
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    const TEXT: &str = "\
ftDataMars = PlMs.dat; // type:ftData
map_head = *; // type:MapHead[]
grGroundParam = *; // type:grGroundParam[2] data:4byte
itemdata = GrI2.dat;
";

    #[test]
    fn round_trip() {
        let file = SymbolFile::parse(TEXT).unwrap();
        assert_eq!(file.to_string(), TEXT);
        assert_eq!(
            file.entries[1].ty,
            Some(TypeSpec {
                name: "MapHead".into(),
                count: Count::Unbounded
            })
        );
        assert_eq!(file.entries[2].other, ["data:4byte"]);
    }

    #[test]
    fn archive_overrides_any() {
        let file = SymbolFile::parse(
            "map_head = *; // type:A\nmap_head = GrNLa.dat; // type:B\n",
        )
        .unwrap();
        let ty = |archive| file.lookup("map_head", archive)?.ty.clone();
        assert_eq!(ty("GrNLa.dat").unwrap().name, "B");
        assert_eq!(ty("GrMc.dat").unwrap().name, "A");
    }

    #[test]
    fn rejects_malformed() {
        assert!("foo = ;".parse::<Entry>().is_err());
        assert!("foo = *".parse::<Entry>().is_err());
        assert!("foo = *; // type:A type:B".parse::<Entry>().is_err());
        assert!("foo = *; // type:A[x]".parse::<Entry>().is_err());
    }
}
