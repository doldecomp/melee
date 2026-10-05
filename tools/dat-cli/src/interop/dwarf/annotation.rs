//! The `dat:` annotations `dat_macros.h` emits as `btf_decl_tag` values.

use super::expr::{Expr, expr, identifier};
use winnow::{
    ModalResult, Parser,
    ascii::{dec_uint, multispace0, multispace1},
    combinator::{
        alt, cut_err, delimited, dispatch, empty, eof, fail, opt, peek, preceded,
        repeat, separated, terminated,
    },
    token::{any, rest, take_while},
};

/// A parsed `dat:` annotation.
#[derive(Debug, Clone, PartialEq, Eq)]
pub enum DatTag {
    /// `DAT_COUNT`: the pointer refers to this many elements.
    Count(Expr),
    /// `DAT_TERMINATED`: the pointer refers to
    /// elements up to the first whose first word is this value and isn't a
    /// relocated pointer, then as many more as make the terminator this many
    /// elements long.
    Terminated(Expr, u64),
    /// `DAT_EXTENT`: the array holds as many elements as the data does.
    Extent,
    /// `DAT_BLOB`: the typedef names a format of opaque bytes.
    Blob,
    /// `DAT_IF`: the union member is valid when this holds.
    If(Expr),
    /// `DAT_TYPE`: the untyped pointer refers to this type, as written.
    Type(String),
    /// A `DAT_ROOTS` witness: the name argument of a loader call.
    Root(RootName),
    /// `DAT_BIND`: a name given a value for everything reached through the
    /// member.
    Bind(String, Expr),
    /// `DAT_SCRIPT`: the pointer refers to a command script.
    Script(Script),
}

/// How long a `DAT_SCRIPT` command script's own commands are: those from
/// opcode 10, after the generic ones every script shares
/// (`Command_Execute`).
#[derive(Debug, Clone, PartialEq, Eq)]
pub enum Script {
    /// `table`: an array in the code of their lengths in words, from
    /// opcode 10.
    Table(String),
    /// `length`: an expression in `_command`, the command's first word,
    /// e.g. a helper's call.
    Length(Expr),
}

/// The name argument of an archive loader call.
#[derive(Debug, Clone, PartialEq, Eq, PartialOrd, Ord, Hash)]
pub enum RootName {
    /// String literals, decoded and cut at the first NUL like a C string.
    Literal(String),
    /// Any other expression, as written.
    Expr(String),
}

impl DatTag {
    /// Parse an annotation value; `None` if it is not a `dat:` annotation
    /// this understands.
    pub fn parse(value: &str) -> Option<Self> {
        preceded("dat:", tag).parse(value).ok()
    }
}

fn tag(input: &mut &str) -> ModalResult<DatTag> {
    dispatch! {take_while(1.., |c: char| c.is_ascii_alphabetic());
        "count" => args(expr).map(DatTag::Count),
        "terminated" => args(terminator)
            .map(|(value, length)| DatTag::Terminated(value, length)),
        "extent" => eof.value(DatTag::Extent),
        "blob" => eof.value(DatTag::Blob),
        "if" => args(expr).map(DatTag::If),
        "type" => raw_args.map(|t: &str| DatTag::Type(t.trim().to_owned())),
        "root" => root.map(DatTag::Root),
        "bind" => args(bind).map(|(name, value)| DatTag::Bind(name, value)),
        "script" => args(script).map(DatTag::Script),
        _ => fail,
    }
    .parse_next(input)
}

/// `(...)` closing the annotation.
fn args<'i, O>(
    inner: impl Parser<
        &'i str,
        O,
        winnow::error::ErrMode<winnow::error::ContextError>,
    >,
) -> impl Parser<&'i str, O, winnow::error::ErrMode<winnow::error::ContextError>>
{
    delimited('(', inner, cut_err((')', eof)))
}

/// A table's name, or else a length expression.
fn script(input: &mut &str) -> ModalResult<Script> {
    alt((
        terminated(
            delimited(multispace0, identifier, multispace0),
            peek(')'),
        )
        .map(|table: &str| Script::Table(table.to_owned())),
        expr.map(Script::Length),
    ))
    .parse_next(input)
}

/// `name, expr`.
/// A terminator's value, then optionally how many elements it takes.
fn terminator(input: &mut &str) -> ModalResult<(Expr, u64)> {
    let value = expr.parse_next(input)?;
    let length = opt(preceded(
        ',',
        delimited(multispace0, dec_uint::<_, u64, _>, multispace0),
    ))
    .parse_next(input)?;
    Ok((value, length.unwrap_or(1)))
}

fn bind(input: &mut &str) -> ModalResult<(String, Expr)> {
    let name =
        delimited(multispace0, identifier, multispace0).parse_next(input)?;
    let value = preceded(',', expr).parse_next(input)?;
    Ok((name.to_owned(), value))
}

/// Everything between the opening parenthesis and the final one.
fn raw_args<'i>(input: &mut &'i str) -> ModalResult<&'i str> {
    preceded('(', rest)
        .verify(|s: &str| s.ends_with(')'))
        .map(|s: &str| &s[..s.len() - 1])
        .parse_next(input)
}

fn root(input: &mut &str) -> ModalResult<RootName> {
    alt((
        delimited(
            '(',
            delimited(multispace0, strings, multispace0),
            (')', eof),
        )
        .map(|bytes| {
            let end =
                bytes.iter().position(|&b| b == 0).unwrap_or(bytes.len());
            RootName::Literal(
                String::from_utf8_lossy(&bytes[..end]).into_owned(),
            )
        }),
        raw_args.map(|e: &str| RootName::Expr(e.trim().to_owned())),
    ))
    .parse_next(input)
}

/// Adjacent string literals, concatenated like C does.
fn strings(input: &mut &str) -> ModalResult<Vec<u8>> {
    separated(1.., string, multispace1)
        .map(|parts: Vec<Vec<u8>>| parts.concat())
        .parse_next(input)
}

/// A C string literal's bytes, with escapes decoded.
fn string(input: &mut &str) -> ModalResult<Vec<u8>> {
    delimited('"', repeat(0.., character), '"')
        .map(|chunks: Vec<Vec<u8>>| chunks.concat())
        .parse_next(input)
}

fn character(input: &mut &str) -> ModalResult<Vec<u8>> {
    alt((
        preceded('\\', escape).map(|b| vec![b]),
        any.verify(|&c: &char| c != '"' && c != '\\')
            .map(|c: char| c.to_string().into_bytes()),
    ))
    .parse_next(input)
}

fn escape(input: &mut &str) -> ModalResult<u8> {
    alt((
        take_while(1..=3, |c: char| c.is_digit(8))
            .try_map(|oct| u8::from_str_radix(oct, 8)),
        preceded('x', take_while(1..=2, |c: char| c.is_ascii_hexdigit()))
            .try_map(|hex| u8::from_str_radix(hex, 16)),
        dispatch! {any;
            'n' => empty.value(b'\n'),
            't' => empty.value(b'\t'),
            'r' => empty.value(b'\r'),
            'a' => empty.value(7),
            'b' => empty.value(8),
            'f' => empty.value(12),
            'v' => empty.value(11),
            '\\' => empty.value(b'\\'),
            '\'' => empty.value(b'\''),
            '"' => empty.value(b'"'),
            '?' => empty.value(b'?'),
            _ => fail,
        },
    ))
    .parse_next(input)
}

#[cfg(test)]
mod tests {
    use super::*;

    fn root(value: &str) -> Option<RootName> {
        match DatTag::parse(value)? {
            DatTag::Root(name) => Some(name),
            _ => None,
        }
    }

    #[test]
    fn roots() {
        let literal = |s: &str| Some(RootName::Literal(s.to_owned()));
        let expr = |s: &str| Some(RootName::Expr(s.to_owned()));
        assert_eq!(
            root(r#"dat:root("MenMainBack_Top_joint")"#),
            literal("MenMainBack_Top_joint")
        );
        assert_eq!(root(r#"dat:root("Top_joint\0\0")"#), literal("Top_joint"));
        assert_eq!(root(r#"dat:root("a" "b")"#), literal("ab"));
        assert_eq!(root(r#"dat:root("\x41\101\n")"#), literal("AA\n"));
        assert_eq!(
            root("dat:root(_Toy_803FE108[0])"),
            expr("_Toy_803FE108[0]")
        );
        assert_eq!(
            root(r#"dat:root((page_name = "MenMainPhotoSn_Top_joint"))"#),
            expr(r#"(page_name = "MenMainPhotoSn_Top_joint")"#)
        );
    }

    #[test]
    fn tags() {
        assert!(matches!(
            DatTag::parse("dat:terminated(GX_VA_NULL)"),
            Some(DatTag::Terminated(_, 1))
        ));
        assert!(matches!(
            DatTag::parse("dat:terminated(0x83D60, 2)"),
            Some(DatTag::Terminated(Expr::Int(0x83D60), 2))
        ));
        assert_eq!(
            DatTag::parse("dat:script( lengths )"),
            Some(DatTag::Script(Script::Table("lengths".into())))
        );
        assert_eq!(
            DatTag::parse("dat:script(itCommandLength(_command))"),
            Some(DatTag::Script(Script::Length(Expr::Call(
                "itCommandLength".into(),
                vec![Expr::Name("_command".into())],
            ))))
        );
        assert_eq!(DatTag::parse("dat:extent"), Some(DatTag::Extent));
        assert_eq!(DatTag::parse("dat:blob"), Some(DatTag::Blob));
        assert_eq!(
            DatTag::parse("dat:count(n)"),
            Some(DatTag::Count(Expr::Name("n".into())))
        );
        assert!(matches!(
            DatTag::parse("dat:if(!(flags & (JOBJ_PTCL | JOBJ_SPLINE)))"),
            Some(DatTag::If(_))
        ));
        assert_eq!(
            DatTag::parse("dat:type(HSD_Joint)"),
            Some(DatTag::Type("HSD_Joint".into()))
        );
        assert!(matches!(
            DatTag::parse("dat:bind(Article::kind, _index + It_Kind_Section_Monster_Character_Misc_Start)"),
            Some(DatTag::Bind(name, _)) if name == "Article::kind"
        ));
        assert_eq!(DatTag::parse("dat:bind(kind)"), None);
        assert_eq!(DatTag::parse("dat:if(1 +)"), None);
        assert_eq!(DatTag::parse("dat:bogus(1)"), None);
        assert_eq!(DatTag::parse("other"), None);
    }
}
