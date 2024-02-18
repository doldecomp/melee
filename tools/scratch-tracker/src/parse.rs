use nom::{
    bytes::complete::take_while_m_n,
    combinator::map_res,
    error::{FromExternalError, ParseError},
    AsChar, IResult,
};
use std::num::ParseIntError;

pub(crate) fn hex<'a, E>(
    count: usize,
) -> impl FnMut(&'a str) -> IResult<&'a str, u32, E>
where
    E: ParseError<&'a str> + FromExternalError<&'a str, ParseIntError>,
{
    let mut parser = map_res(
        take_while_m_n(count, count, |c: char| c.is_hex_digit()),
        |x| u32::from_str_radix(x, 16),
    );
    move |input: &'a str| parser(input)
}
