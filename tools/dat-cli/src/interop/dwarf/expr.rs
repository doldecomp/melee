//! C integer expressions, as found in `dat:if` conditions and macro bodies.
//!
//! Parsing produces an [`Expr`]; evaluating it resolves names through the
//! caller, typically as fields of a record in the data and then as macros
//! from the DWARF macro table.

use std::collections::HashMap;
use winnow::{
    ModalResult, Parser,
    ascii::{digit1, hex_digit1, multispace0, oct_digit1},
    combinator::{
        Infix, Prefix, alt, cut_err, delimited, dispatch, expression, fail,
        opt, peek, preceded, separated,
    },
    token::{any, one_of, take_while},
};

#[derive(Debug, Clone, PartialEq, Eq)]
pub enum Expr {
    Int(u64),
    Name(String),
    Unary(UnaryOp, Box<Expr>),
    Binary(BinaryOp, Box<Expr>, Box<Expr>),
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum UnaryOp {
    Not,
    BitNot,
    Neg,
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum BinaryOp {
    Or,
    And,
    BitOr,
    BitXor,
    BitAnd,
    Eq,
    Ne,
    Lt,
    Gt,
    Le,
    Ge,
    Shl,
    Shr,
    Add,
    Sub,
    Mul,
    Div,
    Rem,
}

impl Expr {
    /// Parse a whole expression; `None` if any of it is not understood.
    pub fn parse(text: &str) -> Option<Self> {
        expr.parse(text).ok()
    }

    /// Evaluate with unsigned 64-bit arithmetic, as flag tests need.
    /// `name` resolves identifiers; `None` if one cannot be resolved or an
    /// operation is undefined.
    pub fn eval(
        &self,
        name: &mut dyn FnMut(&str) -> Option<u64>,
    ) -> Option<u64> {
        Some(match self {
            Expr::Int(value) => *value,
            Expr::Name(ident) => name(ident)?,
            Expr::Unary(op, a) => {
                let a = a.eval(name)?;
                match op {
                    UnaryOp::Not => u64::from(a == 0),
                    UnaryOp::BitNot => !a,
                    UnaryOp::Neg => a.wrapping_neg(),
                }
            }
            Expr::Binary(op, a, b) => {
                let a = a.eval(name)?;
                // Short-circuit like C, so the other side may be unresolved
                match (op, a != 0) {
                    (BinaryOp::Or, true) => return Some(1),
                    (BinaryOp::And, false) => return Some(0),
                    _ => {}
                }
                let b = b.eval(name)?;
                match op {
                    BinaryOp::Or | BinaryOp::And => u64::from(b != 0),
                    BinaryOp::BitOr => a | b,
                    BinaryOp::BitXor => a ^ b,
                    BinaryOp::BitAnd => a & b,
                    BinaryOp::Eq => u64::from(a == b),
                    BinaryOp::Ne => u64::from(a != b),
                    BinaryOp::Lt => u64::from(a < b),
                    BinaryOp::Gt => u64::from(a > b),
                    BinaryOp::Le => u64::from(a <= b),
                    BinaryOp::Ge => u64::from(a >= b),
                    BinaryOp::Shl => a.checked_shl(u32::try_from(b).ok()?)?,
                    BinaryOp::Shr => a.checked_shr(u32::try_from(b).ok()?)?,
                    BinaryOp::Add => a.wrapping_add(b),
                    BinaryOp::Sub => a.wrapping_sub(b),
                    BinaryOp::Mul => a.wrapping_mul(b),
                    BinaryOp::Div => a.checked_div(b)?,
                    BinaryOp::Rem => a.checked_rem(b)?,
                }
            }
        })
    }
}

/// Evaluate `text`, resolving names with `field` first and then as macros,
/// whose bodies are themselves evaluated, to a bounded depth.
pub fn eval(
    macros: &HashMap<String, String>,
    text: &str,
    field: &dyn Fn(&str) -> Option<u64>,
) -> Option<u64> {
    eval_expr(macros, &Expr::parse(text)?, field)
}

/// Like [`eval`], for an expression already parsed.
pub fn eval_expr(
    macros: &HashMap<String, String>,
    expr: &Expr,
    field: &dyn Fn(&str) -> Option<u64>,
) -> Option<u64> {
    eval_depth(macros, expr, field, 0)
}

fn eval_depth(
    macros: &HashMap<String, String>,
    expr: &Expr,
    field: &dyn Fn(&str) -> Option<u64>,
    depth: usize,
) -> Option<u64> {
    if depth > 16 {
        return None;
    }
    expr.eval(&mut |name| {
        field(name).or_else(|| {
            let body = Expr::parse(macros.get(name)?)?;
            eval_depth(macros, &body, field, depth + 1)
        })
    })
}

/// An expression, with any whitespace around it.
pub fn expr(input: &mut &str) -> ModalResult<Expr> {
    delimited(multispace0, parser(0), multispace0).parse_next(input)
}

/// An operand and the operators around it, binding tighter than
/// `precedence`. Binding powers follow C's precedence.
fn parser<'i>(
    precedence: i64,
) -> impl Parser<&'i str, Expr, winnow::error::ErrMode<winnow::error::ContextError>>
{
    move |input: &mut &'i str| {
        use Infix::Left;
        expression(delimited(multispace0, operand, multispace0))
            .current_precedence_level(precedence)
            .prefix(delimited(
                multispace0,
                dispatch! {any;
                    '!' => Prefix(22, |_: &mut _, a| Ok(unary(UnaryOp::Not, a))),
                    '~' => Prefix(22, |_: &mut _, a| Ok(unary(UnaryOp::BitNot, a))),
                    '-' => Prefix(22, |_: &mut _, a| Ok(unary(UnaryOp::Neg, a))),
                    '+' => Prefix(22, |_: &mut _, a| Ok(a)),
                    _ => fail,
                },
                multispace0,
            ))
            .infix(alt((
                // Two-character operators before their one-character prefixes
                "||".value(Left(2, |_: &mut _, a, b| Ok(binary(BinaryOp::Or, a, b)))),
                "&&".value(Left(4, |_: &mut _, a, b| Ok(binary(BinaryOp::And, a, b)))),
                "==".value(Left(12, |_: &mut _, a, b| Ok(binary(BinaryOp::Eq, a, b)))),
                "!=".value(Left(12, |_: &mut _, a, b| Ok(binary(BinaryOp::Ne, a, b)))),
                "<=".value(Left(14, |_: &mut _, a, b| Ok(binary(BinaryOp::Le, a, b)))),
                ">=".value(Left(14, |_: &mut _, a, b| Ok(binary(BinaryOp::Ge, a, b)))),
                "<<".value(Left(16, |_: &mut _, a, b| Ok(binary(BinaryOp::Shl, a, b)))),
                ">>".value(Left(16, |_: &mut _, a, b| Ok(binary(BinaryOp::Shr, a, b)))),
                dispatch! {any;
                    '|' => Left(6, |_: &mut _, a, b| Ok(binary(BinaryOp::BitOr, a, b))),
                    '^' => Left(8, |_: &mut _, a, b| Ok(binary(BinaryOp::BitXor, a, b))),
                    '&' => Left(10, |_: &mut _, a, b| Ok(binary(BinaryOp::BitAnd, a, b))),
                    '<' => Left(14, |_: &mut _, a, b| Ok(binary(BinaryOp::Lt, a, b))),
                    '>' => Left(14, |_: &mut _, a, b| Ok(binary(BinaryOp::Gt, a, b))),
                    '+' => Left(18, |_: &mut _, a, b| Ok(binary(BinaryOp::Add, a, b))),
                    '-' => Left(18, |_: &mut _, a, b| Ok(binary(BinaryOp::Sub, a, b))),
                    '*' => Left(20, |_: &mut _, a, b| Ok(binary(BinaryOp::Mul, a, b))),
                    '/' => Left(20, |_: &mut _, a, b| Ok(binary(BinaryOp::Div, a, b))),
                    '%' => Left(20, |_: &mut _, a, b| Ok(binary(BinaryOp::Rem, a, b))),
                    _ => fail,
                },
            )))
            .parse_next(input)
    }
}

/// A parenthesized expression, a name, an integer literal, or `true` or
/// `false`.
fn operand(input: &mut &str) -> ModalResult<Expr> {
    dispatch! {peek(any);
        '(' => delimited('(', parser(0), cut_err(preceded(multispace0, ')'))),
        '0'..='9' => integer.map(Expr::Int),
        _ => identifier.map(|name: &str| match name {
            // Keywords as of C23
            "true" => Expr::Int(1),
            "false" => Expr::Int(0),
            _ => Expr::Name(name.to_owned()),
        }),
    }
    .parse_next(input)
}

/// A C identifier, or `Type::field` naming a value bound with `DAT_BIND`.
pub fn identifier<'i>(input: &mut &'i str) -> ModalResult<&'i str> {
    separated(1..=2, word, "::")
        .map(|()| ())
        .take()
        .parse_next(input)
}

fn word<'i>(input: &mut &'i str) -> ModalResult<&'i str> {
    (
        one_of(|c: char| c.is_ascii_alphabetic() || c == '_'),
        take_while(0.., |c: char| c.is_ascii_alphanumeric() || c == '_'),
    )
        .take()
        .parse_next(input)
}

/// A decimal, octal or hexadecimal literal, with any `u`/`l` suffixes.
fn integer(input: &mut &str) -> ModalResult<u64> {
    let value = alt((
        preceded(alt(("0x", "0X")), hex_digit1)
            .try_map(|hex| u64::from_str_radix(hex, 16)),
        preceded('0', oct_digit1).try_map(|oct| u64::from_str_radix(oct, 8)),
        digit1.try_map(str::parse),
    ))
    .parse_next(input)?;
    opt(take_while(1.., ['u', 'U', 'l', 'L'])).parse_next(input)?;
    Ok(value)
}

fn unary(op: UnaryOp, a: Expr) -> Expr {
    Expr::Unary(op, Box::new(a))
}

fn binary(op: BinaryOp, a: Expr, b: Expr) -> Expr {
    Expr::Binary(op, Box::new(a), Box::new(b))
}

#[cfg(test)]
mod tests {
    use super::*;

    fn macros() -> HashMap<String, String> {
        [
            ("JOBJ_SPLINE", "(1 << 14)"),
            ("JOBJ_PTCL", "(1 << 5)"),
            ("LOBJ_TYPE_MASK", "(LOBJ_INFINITE | LOBJ_FLAGS_B1)"),
            ("LOBJ_INFINITE", "(1 << 0)"),
            ("LOBJ_FLAGS_B1", "(1 << 1)"),
            ("LOBJ_POINT", "(2 << 0)"),
            ("LOOP", "LOOP"),
        ]
        .into_iter()
        .map(|(k, v)| (k.to_owned(), v.to_owned()))
        .collect()
    }

    fn with_flags(expr: &str, flags: u64) -> Option<u64> {
        eval(&macros(), expr, &|name| (name == "flags").then_some(flags))
    }

    #[test]
    fn precedence() {
        let e = |text| Expr::parse(text).unwrap().eval(&mut |_| None);
        assert_eq!(e("1 + 2 * 3"), Some(7));
        assert_eq!(e("1 << 2 + 1"), Some(8));
        assert_eq!(e("6 & 3 == 3"), Some(0));
        assert_eq!(e("1 | 2 ^ 3 & 4"), Some(3));
        assert_eq!(e("!0 && ~0 != 0"), Some(1));
        assert_eq!(e("0 || 2 < 3"), Some(1));
        assert_eq!(e("(1 + 2) * 3"), Some(9));
        assert_eq!(e("0x10u + 010 + 0"), Some(24));
        assert_eq!(e("true && !false"), Some(1));
        assert_eq!(e("false"), Some(0));
        assert_eq!(
            Expr::parse("Article::kind == 3"),
            Some(binary(
                BinaryOp::Eq,
                Expr::Name("Article::kind".into()),
                Expr::Int(3)
            ))
        );
        assert!(Expr::parse("A::b::c").is_none());
    }

    #[test]
    fn conditions() {
        assert_eq!(with_flags("flags & JOBJ_SPLINE", 1 << 14), Some(1 << 14));
        assert_eq!(
            with_flags("!(flags & (JOBJ_PTCL | JOBJ_SPLINE))", 0),
            Some(1)
        );
        assert_eq!(
            with_flags("!(flags & (JOBJ_PTCL | JOBJ_SPLINE))", 32),
            Some(0)
        );
        assert_eq!(
            with_flags("(flags & LOBJ_TYPE_MASK) == LOBJ_POINT", 2),
            Some(1)
        );
        // The unresolved side of a short-circuit is not evaluated
        assert_eq!(with_flags("flags == 0 && UNKNOWN", 1), Some(0));
    }

    #[test]
    fn rejects() {
        assert_eq!(with_flags("UNKNOWN", 0), None);
        assert_eq!(with_flags("trueish", 0), None);
        assert_eq!(with_flags("LOOP", 0), None);
        assert!(Expr::parse("1 +").is_none());
        assert!(Expr::parse("(1").is_none());
        assert!(Expr::parse("1 2").is_none());
        assert!(Expr::parse("1 ? 2 : 3").is_none());
    }
}
