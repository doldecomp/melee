//! Read names, sections, addresses and sizes from decomp-toolkit's
//! `symbols.txt`. Other attributes are ignored; this is not a DTK config
//! validator. DOL addresses are absolute, REL addresses section-relative.

use anyhow::{Context, Result, anyhow, ensure};
use winnow::{
    ModalResult, Parser,
    ascii::{digit1, hex_digit1, space0, space1},
    combinator::{alt, cut_err, eof, opt, preceded, separated},
    token::take_till,
};

#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Symbol {
    pub name: String,
    pub section: String,
    pub address: u32,
    pub size: Option<u32>,
}

#[derive(Debug, Clone, Default)]
pub struct SymbolFile {
    pub entries: Vec<Symbol>,
}

impl SymbolFile {
    pub fn parse(text: &str) -> Result<Self> {
        let mut entries = Vec::new();
        for (index, line) in text.lines().enumerate() {
            let line = line.trim();
            if line.is_empty()
                || line.starts_with("//")
                || line.starts_with('#')
            {
                continue;
            }
            let raw = entry
                .parse(line)
                .map_err(|e| anyhow!("line {}: {line}\n{e}", index + 1))?;
            let mut sizes = raw.sizes.into_iter().flatten();
            let size = sizes.next();
            ensure!(
                sizes.next().is_none(),
                "line {}: more than one `size:`",
                index + 1
            );
            entries.push(Symbol {
                name: raw.name.to_owned(),
                section: raw.section.to_owned(),
                address: raw.address,
                size,
            });
        }
        Ok(Self { entries })
    }

    /// Local names may repeat. A lookup by name must be unambiguous.
    pub fn lookup(&self, name: &str) -> Result<&Symbol> {
        let mut matches = self.entries.iter().filter(|s| s.name == name);
        let symbol = matches
            .next()
            .with_context(|| format!("no symbol `{name}`"))?;
        ensure!(matches.next().is_none(), "ambiguous symbol `{name}`");
        Ok(symbol)
    }
}

struct RawSymbol<'i> {
    name: &'i str,
    section: &'i str,
    address: u32,
    sizes: Vec<Option<u32>>,
}

fn entry<'i>(input: &mut &'i str) -> ModalResult<RawSymbol<'i>> {
    let name = preceded(
        space0,
        take_till(1.., |c: char| c.is_whitespace() || c == '='),
    )
    .parse_next(input)?;
    (space0, '=', space0).parse_next(input)?;
    let section =
        take_till(1.., |c: char| c.is_whitespace() || c == ':' || c == ';')
            .parse_next(input)?;
    let address = preceded(':', cut_err(integer)).parse_next(input)?;
    (space0, ';', space0).parse_next(input)?;
    let sizes = opt(preceded(("//", space0), separated(0.., attr, space1)))
        .parse_next(input)?
        .unwrap_or_default();
    (space0, eof).parse_next(input)?;
    Ok(RawSymbol {
        name,
        section,
        address,
        sizes,
    })
}

fn attr(input: &mut &str) -> ModalResult<Option<u32>> {
    alt((
        preceded("size:", cut_err(integer)).map(Some),
        take_till(1.., char::is_whitespace).value(None),
    ))
    .parse_next(input)
}

fn integer(input: &mut &str) -> ModalResult<u32> {
    alt((
        preceded(alt(("0x", "0X")), cut_err(hex_digit1))
            .try_map(|h| u32::from_str_radix(h, 16)),
        digit1.try_map(str::parse),
    ))
    .parse_next(input)
}
