use anyhow::{anyhow, Context, Result};
use cwparse::map::{cpp_name, hex};
use nom::{
    branch::alt,
    bytes::complete::{tag, take_while1},
    character::complete::{
        alpha1, alphanumeric1, char, digit1, hex_digit1, line_ending,
    },
    combinator::{all_consuming, map, map_res, opt, recognize},
    error::{FromExternalError, ParseError},
    multi::separated_list1,
    sequence::{preceded, separated_pair, terminated},
    IResult,
};
use nom_supreme::error::ErrorTree;
use rayon::{prelude::ParallelIterator, str::ParallelString};
use std::{collections::BTreeMap, fmt::Write, num::ParseIntError};

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

fn line<'a, E>(input: &'a str) -> IResult<&'a str, Symbol<'a>, E>
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
                            recognize(preceded(opt(char('.')), alphanumeric1)),
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

pub(crate) fn parse_symbols<'a>(
    input: &'a str,
) -> Result<BTreeMap<u32, Symbol<'a>>> {
    let mut symbols = BTreeMap::default();
    let lines = input
        .par_lines()
        .map(|line| {
            self::line::<ErrorTree<&'a str>>(line)
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
