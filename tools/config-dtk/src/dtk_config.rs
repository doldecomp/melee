use anyhow::{anyhow, bail, Context, Result};
use cwparse::map::{cpp_name, hex};
use nom::{
    branch::alt,
    bytes::complete::{tag, take_until1, take_while1},
    character::complete::{
        alpha1, alphanumeric1, char, digit1, hex_digit1, line_ending, space0,
        space1,
    },
    combinator::{all_consuming, map, map_res, opt, recognize},
    error::{FromExternalError, ParseError},
    multi::{many_m_n, separated_list0, separated_list1},
    sequence::{preceded, separated_pair, terminated, tuple},
    IResult, Parser,
};
use nom_supreme::error::ErrorTree;
use rayon::{prelude::ParallelIterator, str::ParallelString};
use std::{collections::BTreeMap, fmt::Write, hash::Hash, num::ParseIntError};

#[derive(Debug, Default)]
pub(crate) struct Symbol<'a> {
    pub(crate) name: &'a str,
    pub(crate) addr: u32,
    pub(crate) section: &'a str,
    pub(crate) size: Option<u32>,
    pub(crate) align: Option<u8>,
    pub(crate) r#type: Option<&'a str>,
    pub(crate) data: Option<&'a str>,
    pub(crate) scope: Option<&'a str>,
    pub(crate) hidden: bool,
}

#[derive(Debug, Eq, PartialEq, Hash, Ord, PartialOrd)]
pub(crate) struct SplitKey<'a> {
    pub(crate) tu: &'a str,
    pub(crate) section: &'a str,
}

#[derive(Debug)]
pub(crate) struct SplitValue {
    pub(crate) start: u32,
    pub(crate) end: u32,
}

pub(crate) struct SplitsFile<'a> {
    pub(crate) layout: &'a str,
    pub(crate) splits: BTreeMap<SplitKey<'a>, SplitValue>,
}

impl<'a> Symbol<'a> {
    pub(crate) fn is_named(&self) -> bool {
        const PREFIXES: [&str; 3] = ["fn_", "lbl_", "func_"];
        !PREFIXES.iter().any(|&prefix| self.name.starts_with(prefix))
    }

    fn write_attr<T: std::fmt::Display>(
        s: &mut String,
        label: &str,
        value: Option<T>,
    ) -> std::fmt::Result {
        if let Some(v) = value {
            write!(s, " {}:{}", label, v)?;
        }
        Ok(())
    }

    pub(crate) fn to_txt(&self) -> Result<String, std::fmt::Error> {
        let mut s = String::new();
        write!(
            &mut s,
            "{} = {}:0x{:08X}; //",
            self.name, self.section, self.addr
        )?;
        Self::write_attr(&mut s, "type", self.r#type)?;
        if let Some(v) = self.size {
            write!(&mut s, " size:0x{:X}", v)?;
        }
        Self::write_attr(&mut s, "scope", self.scope)?;
        Self::write_attr(&mut s, "align", self.align)?;
        Self::write_attr(&mut s, "data", self.data)?;
        if self.hidden {
            write!(&mut s, " hidden")?;
        }

        return Ok(s);
    }
}

enum SymbolAttribute<'a> {
    Size(u32),
    Align(u8),
    Type(&'a str),
    Data(&'a str),
    Scope(&'a str),
    Hidden,
}

fn section_name<'a, E>(input: &'a str) -> IResult<&'a str, &'a str, E>
where
    E: ParseError<&'a str>,
{
    recognize(preceded(opt(char('.')), alphanumeric1))(input)
}

fn symbol<'a, E>(input: &'a str) -> IResult<&'a str, Symbol<'a>, E>
where
    E: ParseError<&'a str> + FromExternalError<&'a str, ParseIntError>,
{
    use SymbolAttribute::*;

    let (input, ((name, (section, addr)), attrs)) = all_consuming(
        terminated(
            separated_pair(
                terminated(
                    separated_pair(
                        cpp_name,
                        tag(" = "),
                        separated_pair(
                            section_name,
                            char(':'),
                            preceded(tag("0x"), hex(8)),
                        ),
                    ),
                    char(';'),
                ),
                tag(" // "),
                separated_list1(
                    char(' '),
                    alt((
                        preceded(
                            tag("align:"),
                            map(map_res(digit1, str::parse::<u8>), Align),
                        ),
                        preceded(
                            tag("data:"),
                            map(
                                take_while1(
                                    |c| matches!(c, '0'..='9' | 'a'..='z' | '_'),
                                ),
                                Data,
                            ),
                        ),
                        preceded(tag("scope:"), map(alpha1, Scope)),
                        preceded(
                            tag("size:"),
                            map(
                                alt((
                                    preceded(
                                        tag("0x"),
                                        map_res(hex_digit1, |s| {
                                            u32::from_str_radix(s, 16)
                                        }),
                                    ),
                                    map_res(digit1, str::parse::<u32>),
                                )),
                                Size,
                            ),
                        ),
                        preceded(tag("type:"), map(alpha1, Type)),
                        map(tag("hidden"), |_| Hidden),
                    )),
                ),
            ),
            opt(line_ending),
        ),
    )(input)?;

    let mut sym = Symbol {
        name,
        addr,
        section,
        ..Default::default()
    };

    for attr in attrs {
        match attr {
            Size(v) => sym.size = Some(v),
            Align(v) => sym.align = Some(v),
            Type(v) => sym.r#type = Some(v),
            Data(v) => sym.data = Some(v),
            Scope(v) => sym.scope = Some(v),
            Hidden => sym.hidden = true,
        }
    }

    Ok((input, sym))
}

fn splits_layout<'a, E>(input: &'a str) -> IResult<&'a str, &'a str, E>
where
    E: ParseError<&'a str>,
{
    recognize(tuple((
        tag("Sections:"),
        line_ending,
        separated_list0(
            line_ending,
            tuple((
                space0,
                section_name,
                space1,
                separated_list1(
                    char(' '),
                    separated_pair(alpha1, char(':'), alphanumeric1),
                ),
            )),
        ),
    )))(input)
}

fn split<'a, E>(input: &'a str) -> IResult<&'a str, (&'a str, u32, u32), E>
where
    E: ParseError<&'a str> + FromExternalError<&'a str, ParseIntError>,
{
    tuple((
        preceded(space0, section_name),
        preceded(space1, preceded(tag("start:0x"), hex(8))),
        preceded(space1, preceded(tag("end:0x"), hex(8))),
    ))(input)
}

fn splits_group<'a, E>(
    input: &'a str,
) -> IResult<&'a str, (&'a str, Vec<(&'a str, u32, u32)>), E>
where
    E: ParseError<&'a str> + FromExternalError<&'a str, ParseIntError>,
{
    separated_pair(
        terminated(
            take_until1(":").map(|s: &str| match s.rfind('.') {
                Some(index) => &s[..index],
                None => s,
            }),
            tag(":"),
        ),
        line_ending,
        separated_list0(line_ending, split),
    )(input)
}

fn blank_line<'a, E>(input: &'a str) -> IResult<&'a str, &'a str, E>
where
    E: ParseError<&'a str>,
{
    recognize(many_m_n(2, 2, line_ending))(input)
}

fn splits_file<'a, E>(
    input: &'a str,
) -> IResult<&'a str, (&str, Vec<(&str, Vec<(&str, u32, u32)>)>), E>
where
    E: ParseError<&'a str> + FromExternalError<&'a str, ParseIntError>,
{
    all_consuming(terminated(
        separated_pair(
            splits_layout,
            blank_line,
            separated_list0(blank_line, splits_group),
        ),
        opt(line_ending),
    ))(input)
}

pub(crate) fn parse_symbols<'a>(
    input: &'a str,
) -> Result<BTreeMap<u32, Symbol<'a>>> {
    let mut symbols = BTreeMap::default();
    let lines = input
        .par_lines()
        .map(|line| {
            self::symbol::<ErrorTree<&'a str>>(line)
                .map(|parsed| (line.trim(), parsed.1))
        })
        .collect::<Result<Vec<_>, _>>()
        .map_err(|err| anyhow!(format!("{err:#?}")))
        .context("failed to parse symbols")?;
    for (_, parsed) in lines {
        symbols.insert(parsed.addr, parsed);
    }
    Ok(symbols)
}

pub(crate) fn parse_splits<'a>(input: &'a str) -> Result<SplitsFile<'a>> {
    let (_, (layout, groups)) = splits_file::<ErrorTree<&'a str>>(input)
        .map_err(|err| anyhow!(format!("{err:#?}")))
        .context("failed to parse splits")?;

    let mut map = BTreeMap::default();

    for (tu, splits) in groups {
        for (section, start, end) in splits {
            let key = SplitKey { tu, section };
            if map.contains_key(&key) {
                bail!("duplicate split found for {} {}", key.tu, key.section);
            }
            let value = SplitValue { start, end };
            map.insert(key, value);
        }
    }

    Ok(SplitsFile {
        layout,
        splits: map,
    })
}
