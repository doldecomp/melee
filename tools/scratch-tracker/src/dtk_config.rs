use crate::parse::hex;
use ahash::AHashMap;
use anyhow::Result;
use nom::{
    bytes::complete::{tag, take_till, take_till1},
    error::{FromExternalError, ParseError},
    sequence::{preceded, separated_pair, terminated},
    IResult,
};
use rayon::prelude::*;
use std::{fs, num::ParseIntError};

pub(crate) fn symbol<'a, E>(
    input: &'a str,
) -> IResult<&'a str, (&'a str, u32), E>
where
    E: ParseError<&'a str> + FromExternalError<&'a str, ParseIntError>,
{
    let (input, (name, (_, addr))) = separated_pair(
        take_till1(|c| c == ' '),
        tag(" = "),
        terminated(
            separated_pair(
                take_till(|c| c == ':'),
                tag(":"),
                preceded(tag("0x"), hex(8)),
            ),
            tag(";"),
        ),
    )(input)?;
    Ok((input, (name, addr)))
}

fn map_symbols() -> Result<Vec<(String, u32)>> {
    let path = &melee_utils::ROOT.join("config/GALE01/symbols.txt");
    fs::read_to_string(path)?
        .par_lines()
        .into_par_iter()
        .map(|line| {
            let (_, (name, addr)) = symbol::<()>(line)
                .map_err(|err| anyhow::anyhow!(format!("{:#?}", err)))?;
            anyhow::Ok((name.to_owned(), addr))
        })
        .collect()
}

pub(crate) fn addr_to_symbol() -> Result<impl Fn(u32) -> Option<String>> {
    let map = map_symbols()?
        .into_iter()
        .map(|(k, v)| (v, k))
        .collect::<AHashMap<_, _>>();
    Ok(move |k: u32| map.get(&k).cloned())
}

pub(crate) fn symbol_to_addr() -> Result<impl Fn(&str) -> Option<u32>> {
    let map = map_symbols()?.into_iter().collect::<AHashMap<_, _>>();
    Ok(move |k: &str| map.get(k).copied())
}
