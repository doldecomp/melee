use crate::parse::hex;
use anyhow::Result;
use dashmap::DashMap;
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

pub(crate) fn read_symbols() -> Result<impl Fn(&str) -> Option<u32>> {
    let map = DashMap::<String, u32>::new();
    let path = &melee_utils::ROOT.join("config/GALE01/symbols.txt");
    let input = fs::read_to_string(path)?;
    input.par_lines().into_par_iter().try_for_each(|line| {
        let (_, (name, addr)) = symbol::<()>(line)
            .map_err(|err| anyhow::anyhow!(format!("{:#?}", err)))?;
        map.insert(name.to_owned(), addr);
        anyhow::Ok(())
    })?;
    Ok(move |k: &str| map.get(k).map(|r| *r.value()))
}
