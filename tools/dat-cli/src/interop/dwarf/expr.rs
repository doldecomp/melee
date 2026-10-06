//! C integer expressions and tuple matches in annotations and macro bodies.
//!
//! Parsing produces an [`Expr`]; evaluating it resolves names through the
//! caller, typically as fields of a record in the data and then as macros
//! from the DWARF macro table. Calls are to the functions of the code that
//! [`call`] ports, such as `GXGetTexBufferSize`. Values are integers, or
//! the bytes a counted pointer field points to ([`Value`]), which only
//! calls take.

use std::collections::HashMap;
use winnow::{
    ModalResult, Parser,
    ascii::{digit1, hex_digit1, multispace0, oct_digit1},
    combinator::{
        Infix, Prefix, alt, cut_err, delimited, dispatch, expression, fail,
        opt, peek, preceded, repeat, separated,
    },
    token::{any, one_of, take_while},
};

#[derive(Debug, Clone, PartialEq, Eq)]
pub enum Expr {
    Int(u64),
    Name(String),
    Call(String, Vec<Expr>),
    Unary(UnaryOp, Box<Expr>),
    Binary(BinaryOp, Box<Expr>, Box<Expr>),
    /// `a ? b : c`.
    Cond(Box<Expr>, Box<Expr>, Box<Expr>),
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

/// What an expression evaluates to.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum Value<'d> {
    Int(u64),
    /// The data a pointer field whose annotation gives its length
    /// (`DAT_COUNT`, `DAT_TERMINATED`) points to.
    Bytes(&'d [u8]),
}

impl Value<'_> {
    pub fn int(self) -> Option<u64> {
        match self {
            Value::Int(value) => Some(value),
            Value::Bytes(_) => None,
        }
    }
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
        self.value(&mut |n| name(n).map(Value::Int))?.int()
    }

    /// Like [`Expr::eval`], with names that may resolve to bytes. Only
    /// calls take bytes; operators fail on them.
    pub fn value<'d>(
        &self,
        name: &mut dyn FnMut(&str) -> Option<Value<'d>>,
    ) -> Option<Value<'d>> {
        fn int<'d>(
            e: &Expr,
            name: &mut dyn FnMut(&str) -> Option<Value<'d>>,
        ) -> Option<u64> {
            e.value(name)?.int()
        }
        Some(Value::Int(match self {
            Expr::Int(value) => *value,
            Expr::Name(ident) => return name(ident),
            Expr::Call(function, args) => {
                let args = args
                    .iter()
                    .map(|a| a.value(name))
                    .collect::<Option<Vec<_>>>()?;
                return call(function, &args);
            }
            Expr::Unary(op, a) => {
                let a = int(a, name)?;
                match op {
                    UnaryOp::Not => u64::from(a == 0),
                    UnaryOp::BitNot => !a,
                    UnaryOp::Neg => a.wrapping_neg(),
                }
            }
            Expr::Cond(a, b, c) => match int(a, name)? {
                0 => return c.value(name),
                _ => return b.value(name),
            },
            Expr::Binary(op, a, b) => {
                let a = int(a, name)?;
                // Short-circuit like C, so the other side may be unresolved
                match (op, a != 0) {
                    (BinaryOp::Or, true) => return Some(Value::Int(1)),
                    (BinaryOp::And, false) => return Some(Value::Int(0)),
                    _ => {}
                }
                let b = int(b, name)?;
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
        }))
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
    eval_value(macros, expr, &|name| field(name).map(Value::Int))?.int()
}

/// Like [`eval_expr`], with names that may resolve to bytes.
pub fn eval_value<'d>(
    macros: &HashMap<String, String>,
    expr: &Expr,
    field: &dyn Fn(&str) -> Option<Value<'d>>,
) -> Option<Value<'d>> {
    eval_depth(macros, expr, field, 0)
}

fn eval_depth<'d>(
    macros: &HashMap<String, String>,
    expr: &Expr,
    field: &dyn Fn(&str) -> Option<Value<'d>>,
    depth: usize,
) -> Option<Value<'d>> {
    if depth > 16 {
        return None;
    }
    expr.value(&mut |name| {
        field(name).or_else(|| {
            let body = Expr::parse(macros.get(name)?)?;
            eval_depth(macros, &body, field, depth + 1)
        })
    })
}

/// An expression, with any whitespace around it.
pub fn expr(input: &mut &str) -> ModalResult<Expr> {
    delimited(multispace0, conditional, multispace0).parse_next(input)
}

/// `a ? b : c`, right-associative and binding loosest, or an expression of
/// the other operators.
fn conditional(input: &mut &str) -> ModalResult<Expr> {
    let a = parser(0).parse_next(input)?;
    let branches = opt((
        preceded((multispace0, '?'), cut_err(expr)),
        preceded(
            ':',
            cut_err(delimited(multispace0, conditional, multispace0)),
        ),
    ))
    .parse_next(input)?;
    Ok(match branches {
        Some((b, c)) => Expr::Cond(Box::new(a), Box::new(b), Box::new(c)),
        None => a,
    })
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

/// A parenthesized expression, a name, a call, a tuple match, an integer
/// literal, or `true` or `false`.
fn operand(input: &mut &str) -> ModalResult<Expr> {
    dispatch! {peek(any);
        '(' => delimited('(', expr, cut_err(')')),
        '0'..='9' => integer.map(Expr::Int),
        _ => named_operand,
    }
    .parse_next(input)
}

fn named_operand(input: &mut &str) -> ModalResult<Expr> {
    let name = name.parse_next(input)?;
    if name == "match" {
        return cut_err(tuple_match).parse_next(input);
    }
    let args = opt(preceded(multispace0, arguments)).parse_next(input)?;
    Ok(match (name, args) {
        (_, Some(args)) => Expr::Call(name.to_owned(), args),
        // Keywords as of C23
        ("true", None) => Expr::Int(1),
        ("false", None) => Expr::Int(0),
        (_, None) => Expr::Name(name.to_owned()),
    })
}

/// A tuple component: `None` is `_`, otherwise the alternatives to compare.
type Pattern = Option<Vec<Expr>>;

/// `match (a, b) { (A | B, 0): x, (_, 1): y, _: z }`.
/// Patterns are integers or names, alternatives (`|`), or a wildcard.
/// Lower to the existing operators so both walkers use the same semantics:
/// cases are tried in order and only the selected result is evaluated.
fn tuple_match(input: &mut &str) -> ModalResult<Expr> {
    let subjects = preceded(multispace0, arguments).parse_next(input)?;
    let mut arms: Vec<(Option<Vec<Pattern>>, Expr)> = delimited(
        (multispace0, '{', multispace0),
        separated(
            1..,
            (
                preceded(
                    multispace0,
                    alt((
                        '_'.value(None),
                        delimited(
                            '(',
                            separated(1.., pattern, ','),
                            cut_err((multispace0, ')')),
                        )
                        .map(Some),
                    )),
                ),
                preceded((multispace0, ':'), expr),
            ),
            ',',
        ),
        (opt(','), multispace0, '}'),
    )
    .parse_next(input)?;
    let Some((None, mut result)) = arms.pop() else {
        return fail.parse_next(input);
    };
    if subjects.is_empty() {
        return fail.parse_next(input);
    }
    for (patterns, value) in arms.into_iter().rev() {
        let Some(patterns) = patterns else {
            return fail.parse_next(input);
        };
        if patterns.len() != subjects.len() {
            return fail.parse_next(input);
        }
        let condition = patterns
            .into_iter()
            .zip(&subjects)
            .filter_map(|(pattern, subject)| {
                let values = pattern?;
                values
                    .into_iter()
                    .map(|value| binary(BinaryOp::Eq, subject.clone(), value))
                    .reduce(|a, b| binary(BinaryOp::Or, a, b))
            })
            .reduce(|a, b| binary(BinaryOp::And, a, b))
            .unwrap_or(Expr::Int(1));
        result =
            Expr::Cond(Box::new(condition), Box::new(value), Box::new(result));
    }
    Ok(result)
}

fn pattern(input: &mut &str) -> ModalResult<Pattern> {
    let values: Vec<Expr> = separated(
        1..,
        delimited(
            multispace0,
            alt((
                integer.map(Expr::Int),
                name.map(|n: &str| Expr::Name(n.into())),
            )),
            multispace0,
        ),
        '|',
    )
    .parse_next(input)?;
    let wildcard = |v: &Expr| matches!(v, Expr::Name(n) if n == "_");
    if values.len() == 1 && wildcard(&values[0]) {
        return Ok(None);
    }
    if values.iter().any(wildcard) {
        return fail.parse_next(input);
    }
    Ok(Some(values))
}

/// A call's parenthesized, comma-separated arguments.
fn arguments(input: &mut &str) -> ModalResult<Vec<Expr>> {
    delimited(
        '(',
        separated(0.., delimited(multispace0, parser(0), multispace0), ','),
        cut_err(')'),
    )
    .parse_next(input)
}

/// Call a function of the code, ported, or a tool-side helper. Arguments
/// are converted to the parameter types as C would; `None` for a function
/// not ported, the wrong number or kind of arguments, or an argument the
/// function rejects.
pub fn call<'d>(function: &str, args: &[Value<'d>]) -> Option<Value<'d>> {
    use Value::{Bytes, Int};
    Some(Int(match (function, args) {
        ("itCommandLength", &[Int(command)]) => it_command_length(command)?,
        ("colAnimCommandLength", &[Int(command)]) => {
            col_anim_command_length(command)?
        }
        ("cpuCommandLength", &[Int(command)]) => Some(cpu_command_length(command)),
        (
            "GXGetTexBufferSize",
            &[
                Int(width),
                Int(height),
                Int(format),
                Int(mipmap),
                Int(max_lod),
            ],
        ) => gx_get_tex_buffer_size(
            width as u16,
            height as u16,
            format as u32,
            mipmap as u8,
            max_lod as u8,
        )
        .map(u64::from)?,
        ("GXMaxIndex", &[Bytes(dl), Bytes(descs), Int(attr)]) => {
            gx_max_index(dl, descs, attr)?
        }
        _ => return None,
    }))
}

/// The largest index the display list `dl` gives the attribute `attr`, as
/// the GameCube reads it, with the vertex descriptors `descs` (an
/// `HSD_VtxDescList` list, up to `GX_VA_NULL`) describing each vertex. A
/// tool-side helper, not a port: it sizes the vertex arrays the display
/// list indexes. Primitives are an opcode, a `u16` vertex count, then each
/// vertex's attributes in the order the hardware takes them (by `GXAttr`,
/// `GX_VA_NBT` as the normal); the list ends at a 0 opcode (`GX_NOP`, its
/// padding) or its end. `None` for anything else, an attribute that isn't
/// indexed, or one no vertex uses.
fn gx_max_index(dl: &[u8], descs: &[u8], attr: u64) -> Option<u64> {
    const DESC_SIZE: usize = 0x18;
    const GX_VA_NULL: u32 = 0xFF;
    let word = |b: &[u8], at: usize| {
        u32::from_be_bytes(b[at..at + 4].try_into().unwrap())
    };
    // Each attribute present: its place in a vertex, its bytes in a
    // vertex, and its indices' width and number, if indexed
    let mut attrs = Vec::new();
    for desc in descs.chunks_exact(DESC_SIZE) {
        let (a, ty, cnt, comp) =
            (word(desc, 0), word(desc, 4), word(desc, 8), word(desc, 12));
        if a == GX_VA_NULL {
            break;
        }
        let order = if a == 25 { 10 } else { a };
        let indices = match (a, cnt) {
            // GX_NRM_NBT3: an index each for the normal, binormal and tangent
            (10 | 25, 2) => 3,
            _ => 1,
        };
        let (width, count) = match ty {
            // GX_NONE
            0 => continue,
            // GX_DIRECT
            1 => (gx_direct_size(a, cnt, comp)?, 0),
            // GX_INDEX8, GX_INDEX16
            2 => (1, indices),
            3 => (2, indices),
            _ => return None,
        };
        attrs.push((order, u64::from(a) == attr, width, count));
    }
    attrs.sort_by_key(|&(order, ..)| order);
    let mut max = None;
    let mut at = 0;
    while let Some(&opcode) = dl.get(at) {
        // GX_NOP
        if opcode == 0 {
            break;
        }
        // GX_QUADS to GX_POINTS, with any vertex format
        if !matches!(
            opcode & 0xF8,
            0x80 | 0x90 | 0x98 | 0xA0 | 0xA8 | 0xB0 | 0xB8
        ) {
            return None;
        }
        let vertices =
            u16::from_be_bytes(dl.get(at + 1..at + 3)?.try_into().ok()?);
        at += 3;
        for _ in 0..vertices {
            for &(_, target, width, count) in &attrs {
                let bytes = dl.get(at..at + width * count.max(1))?;
                if target {
                    for index in bytes.chunks_exact(width).take(count) {
                        let index = index
                            .iter()
                            .fold(0, |v, &b| v << 8 | u64::from(b));
                        max = max.max(Some(index));
                    }
                }
                at += bytes.len();
            }
        }
    }
    max
}

/// The bytes a direct attribute takes in a vertex, by its `GXCompCnt` and
/// `GXCompType`.
fn gx_direct_size(attr: u32, cnt: u32, comp: u32) -> Option<usize> {
    let scalar = || match comp {
        // GX_U8, GX_S8, GX_U16, GX_S16, GX_F32
        0 | 1 => Some(1),
        2 | 3 => Some(2),
        4 => Some(4),
        _ => None,
    };
    Some(match attr {
        // GX_VA_PNMTXIDX, GX_VA_TEX0MTXIDX to GX_VA_TEX7MTXIDX
        0..=8 => 1,
        // GX_VA_POS: GX_POS_XY or GX_POS_XYZ
        9 => scalar()? * if cnt == 0 { 2 } else { 3 },
        // GX_VA_NRM, GX_VA_NBT: GX_NRM_XYZ, or the NBT forms
        10 | 25 => scalar()? * if cnt == 0 { 3 } else { 9 },
        // GX_VA_CLR0, GX_VA_CLR1: RGB565, RGB8, RGBX8, RGBA4, RGBA6, RGBA8
        11 | 12 => [2, 3, 4, 2, 3, 4].get(comp as usize).copied()?,
        // GX_VA_TEX0 to GX_VA_TEX7: GX_TEX_S or GX_TEX_ST
        13..=20 => scalar()? * if cnt == 0 { 1 } else { 2 },
        _ => return None,
    })
}

/// How many words an item's own script command is (from opcode 10), from
/// its first word: as far as the handlers `it_802799E4` calls
/// (`it_803F22A8`) advance. A tool-side helper, not a port: the game has no
/// such table. Opcode 16 is three words for its sub-commands 0-2, 10 and
/// 11 (`it_8027978C`), two for the others.
fn it_command_length(command: u64) -> Option<u64> {
    let opcode = (command >> 26) & 0x3F;
    let sub = (command >> 18) & 0xFF;
    Some(match opcode {
        10 => 5,
        11 => 6,
        16 => match sub {
            0..=2 | 10 | 11 => 3,
            _ => 2,
        },
        12..=25 => 1,
        _ => return None,
    })
}

/// How many words a color animation's own command is (from opcode 10), from
/// its first word: as far as `lb_803BA248`'s handlers advance, and for
/// opcodes 21-23, which `ftCo_803C6AD0` hands to subaction commands, as long
/// as those are (`ftAction_803C0870`). Opcode 10 stops the animation
/// (`lb_80013BB0`): 0, the script's end. A tool-side helper, not a port.
fn col_anim_command_length(command: u64) -> Option<u64> {
    const OWN: [u64; 11] = [0, 1, 1, 2, 2, 2, 1, 1, 2, 2, 1];
    let opcode = (command >> 26) & 0x3F;
    Some(match opcode {
        10..=20 => OWN[opcode as usize - 10],
        21 => 5,
        22 => 3,
        23 => 1,
        _ => return None,
    })
}

/// Return a CPU command's length in bytes, following `ftCo_800B3E04`.
/// Commands 0x80-0xBF take one argument byte; 0xC0-0xFF take two.
/// `CpuCmd_Done` (0x7F) returns 0 to mark the script's end. This helper is
/// used by the DAT tools.
fn cpu_command_length(command: u64) -> u64 {
    match command & 0xFF {
        0x7F => 0,
        0xC0.. => 3,
        0x80.. => 2,
        _ => 1,
    }
}

/// `GXGetTexBufferSize` (`GXTexture.c`): the bytes a texture of `format`
/// takes in memory, in whole tiles, with every mipmap level up to
/// `max_lod` levels if `mipmap` is 1.
fn gx_get_tex_buffer_size(
    mut width: u16,
    mut height: u16,
    format: u32,
    mipmap: u8,
    max_lod: u8,
) -> Option<u32> {
    // `__GXGetTexTileShift`: a tile's width and height, as shifts
    let (shift_x, shift_y) = match format {
        // I4, C4, CMPR, CTF_R4, CTF_Z4
        0x0 | 0x8 | 0xE | 0x20 | 0x30 => (3, 3),
        // I8, IA4, C8, Z8, CTF_RA4, A8, CTF_R8, G8, B8, Z8M, Z8L
        0x1 | 0x2 | 0x9 | 0x11 | 0x22 | 0x27 | 0x28 | 0x29 | 0x2A | 0x39
        | 0x3A => (3, 2),
        // IA8, RGB565, RGB5A3, RGBA8, C14X2, Z16, Z24X8, CTF_RA8, RG8, GB8,
        // Z16L
        0x3 | 0x4 | 0x5 | 0x6 | 0xA | 0x13 | 0x16 | 0x23 | 0x2B | 0x2C
        | 0x3C => (2, 2),
        _ => return None,
    };
    // RGBA8 and Z24X8
    let tile_bytes = if matches!(format, 0x6 | 0x16) { 64 } else { 32 };
    let tiles = |width: u16, height: u16| {
        let nx = (u32::from(width) + (1 << shift_x) - 1) >> shift_x;
        let ny = (u32::from(height) + (1 << shift_y) - 1) >> shift_y;
        tile_bytes * nx * ny
    };
    if mipmap != 1 {
        return Some(tiles(width, height));
    }
    let mut size = 0;
    for _ in 0..max_lod {
        size += tiles(width, height);
        if width == 1 && height == 1 {
            break;
        }
        width = (width >> 1).max(1);
        height = (height >> 1).max(1);
    }
    Some(size)
}

/// A C identifier, or `Type::field` naming a value bound with `DAT_BIND`.
pub fn identifier<'i>(input: &mut &'i str) -> ModalResult<&'i str> {
    separated(1..=2, word, "::")
        .map(|()| ())
        .take()
        .parse_next(input)
}

/// An expression's name: an identifier, or a member of a nested record,
/// `x0.count`.
fn name<'i>(input: &mut &'i str) -> ModalResult<&'i str> {
    (identifier, repeat(0.., ('.', word)).map(|()| ()))
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
        assert_eq!(
            Expr::parse("x0.dynamicsNum"),
            Some(Expr::Name("x0.dynamicsNum".into()))
        );
    }

    #[test]
    fn conditional() {
        let e = |text| Expr::parse(text).unwrap().eval(&mut |_| None);
        assert_eq!(e("1 ? 2 : 3"), Some(2));
        assert_eq!(e("0 ? 2 : 3"), Some(3));
        assert_eq!(e("0 ? 1 : 0 ? 2 : 3"), Some(3));
        assert_eq!(e("1 ? 0 ? 4 : 5 : 6"), Some(5));
        assert_eq!(e("1 + 1 == 2 ? 7 : 8"), Some(7));
        assert_eq!(e("(0 ? 1 : 2) * 3"), Some(6));
        assert_eq!(e("0 ? UNKNOWN : 9"), Some(9));
        assert!(Expr::parse("1 ? 2").is_none());
        assert!(Expr::parse("1 ? : 3").is_none());
    }

    #[test]
    fn tuple_matches() {
        let text = "match (kind, _index) {
            (A | B, 0): 10,
            (_, 1 | 2): 20,
            (B, _): 30,
            _: 40,
        }";
        let expression = Expr::parse(text).unwrap();
        let e = |kind, index| {
            expression.eval(&mut |name| match name {
                "A" => Some(3),
                "B" => Some(4),
                "kind" => Some(kind),
                "_index" => Some(index),
                _ => None,
            })
        };
        assert_eq!(e(3, 0), Some(10));
        assert_eq!(e(4, 0), Some(10));
        assert_eq!(e(4, 2), Some(20));
        assert_eq!(e(4, 3), Some(30));
        assert_eq!(e(5, 0), Some(40));
        // Lowering uses the existing tree, including first-case precedence.
        assert_eq!(
            expression,
            Expr::parse(
                "(kind == A || kind == B) && _index == 0 ? 10 :
                (_index == 1 || _index == 2) ? 20 : kind == B ? 30 : 40"
            )
            .unwrap()
        );
        assert_eq!(
            Expr::parse("1 + (match (0) { (1): 8, _: 2 }) * 3")
                .unwrap()
                .eval(&mut |_| None),
            Some(7)
        );
    }

    #[test]
    fn tuple_matches_short_circuit() {
        let e = |text| Expr::parse(text).unwrap().eval(&mut |_| None);
        assert_eq!(
            e("match (0, UNKNOWN) {
            (1, 2): UNKNOWN, (0, _): 7, _: UNKNOWN
        }"),
            Some(7)
        );
        assert_eq!(e("match (0) { (0 | UNKNOWN): 8, _: UNKNOWN }"), Some(8));
        assert_eq!(e("match (0) { (0): UNKNOWN, _: 8 }"), None);
        assert_eq!(e("match (UNKNOWN) { (0): 7, _: 8 }"), None);
        assert_eq!(
            e("match (0) {
            (0): match (1) { (1): 9, _: UNKNOWN }, _: UNKNOWN
        }"),
            Some(9)
        );
    }

    #[test]
    fn tuple_match_results() {
        let e = |text| Expr::parse(text).unwrap().eval(&mut |_| None);
        assert_eq!(
            e("match (0) {
                (0): 1 ? 7 : UNKNOWN,
                _: UNKNOWN
            }"),
            Some(7)
        );
        assert_eq!(
            e("match (0) {
                (0): GXGetTexBufferSize(8, 8, 0, 0, 0),
                _: 0
            }"),
            Some(32)
        );
    }

    #[test]
    fn rejects_invalid_tuple_matches() {
        for text in [
            "match () { _: 0 }",
            "match (0) {}",
            "match (0) { (0): 1 }",
            "match (0) { _: 0, (0): 1 }",
            "match (0) { _: 0, _: 1 }",
            "match (0, 1) { (0): 1, _: 0 }",
            "match (0) { (0, 1): 1, _: 0 }",
            "match (0) { (0 |): 1, _: 0 }",
            "match (0) { (_ | 1): 1, _: 0 }",
            "match (0) { (0) => 1, _ => 0 }",
            "match (0) { (0): 1 _: 0 }",
            "match (0) { (0): 1; _: 0; }",
            "match (0) { (0): 1, _: 0",
            "match (0) { (0): {}, _: 0 }",
            "match (0) { (0): { 1 }, _: 0 }",
            "match (0) { (0): { 1; 2; }, _: 0 }",
            "match (0) { (0): 1; break, _: 0 }",
            "match (0) { (0): 1, _: 0 } break",
        ] {
            assert!(Expr::parse(text).is_none(), "{text}");
        }
    }

    #[test]
    fn item_command_lengths() {
        let e = |text| Expr::parse(text).unwrap().eval(&mut |_| None);
        // Opcode 11, a hitbox, and opcode 16 with sub-commands 2 and 3
        assert_eq!(e("itCommandLength(0x2C000000)"), Some(6));
        assert_eq!(e("itCommandLength(0x40080000)"), Some(3));
        assert_eq!(e("colAnimCommandLength(0x28000000)"), Some(0));
        assert_eq!(e("colAnimCommandLength(0x54020000)"), Some(5));
        assert_eq!(e("itCommandLength(0x400C0000)"), Some(2));
        assert_eq!(e("itCommandLength(0x68000000)"), None);
        assert_eq!(e("cpuCommandLength(0x7F)"), Some(0));
        assert_eq!(e("cpuCommandLength(0x19)"), Some(1));
        assert_eq!(e("cpuCommandLength(0x8E)"), Some(2));
        assert_eq!(e("cpuCommandLength(0xC2)"), Some(3));
    }

    #[test]
    fn calls() {
        let e = |text| Expr::parse(text).unwrap().eval(&mut |_| None);
        // CMPR, 8x8 tiles of 32 bytes
        assert_eq!(e("GXGetTexBufferSize(64, 64, 14, 0, 0)"), Some(2048));
        // RGBA8, 4x4 tiles of 64 bytes, rounded up
        assert_eq!(e("GXGetTexBufferSize(5, 4, 6, 0, 0)"), Some(128));
        // I8 with three levels: 32x32, 16x16, 8x8
        assert_eq!(
            e("GXGetTexBufferSize(32, 32, 1, 1, 3)"),
            Some(1024 + 256 + 64)
        );
        assert_eq!(e("1 + GXGetTexBufferSize( 8 , 8 , 0 , 0 , 1 )"), Some(33));
        assert_eq!(e("GXGetTexBufferSize(8, 8, 0x40, 0, 0)"), None);
        assert_eq!(e("Unknown(1)"), None);
    }

    /// `HSD_VtxDescList`s of (attr, attr_type, comp_cnt, comp_type), up to
    /// `GX_VA_NULL`.
    fn descs(attrs: &[(u32, u32, u32, u32)]) -> Vec<u8> {
        let mut bytes = Vec::new();
        for &(attr, ty, cnt, comp) in attrs.iter().chain(&[(0xFF, 0, 0, 0)]) {
            for word in [attr, ty, cnt, comp, 0, 0] {
                bytes.extend(word.to_be_bytes());
            }
        }
        bytes
    }

    #[test]
    fn vertex_indices() {
        // Out of the hardware's order: TEX0 (GX_INDEX16), NRM (GX_INDEX8),
        // POS (GX_INDEX16), PNMTXIDX (GX_DIRECT)
        let descs =
            descs(&[(13, 3, 1, 3), (10, 2, 0, 1), (9, 3, 1, 3), (0, 1, 0, 0)]);
        // Triangles of 2 vertices, each matrix, position, normal and
        // texture coordinate, then a strip of 1, then padding
        #[rustfmt::skip]
        let dl = [
            0x90, 0, 2,
            0x1E, 0, 7, 3, 0, 1,
            0x21, 1, 2, 9, 0, 0,
            0x98, 0, 1,
            0x00, 0, 4, 4, 0, 2,
            0, 0, 0,
        ];
        let max = |attr| {
            call(
                "GXMaxIndex",
                &[Value::Bytes(&dl), Value::Bytes(&descs), Value::Int(attr)],
            )
        };
        assert_eq!(max(9), Some(Value::Int(0x102)));
        assert_eq!(max(10), Some(Value::Int(9)));
        assert_eq!(max(13), Some(Value::Int(2)));
        // Direct, and absent
        assert_eq!(max(0), None);
        assert_eq!(max(11), None);
        // A vertex past the end, and an opcode that isn't a primitive
        assert_eq!(gx_max_index(&dl[..10], &descs, 9), None);
        assert_eq!(gx_max_index(&[0x61, 0, 0], &descs, 9), None);
        // Bytes only as arguments
        let e = |text| {
            Expr::parse(text)
                .unwrap()
                .value(&mut |name| (name == "dl").then_some(Value::Bytes(&dl)))
        };
        assert_eq!(e("dl + 1"), None);
        assert_eq!(e("dl"), Some(Value::Bytes(&dl)));
        assert_eq!(e("GXMaxIndex(1, dl, 9)"), None);
    }

    #[test]
    fn nbt3_uses_three_indices_for_both_normal_attributes() {
        for attr in [10, 25] {
            let descs = descs(&[(attr, 2, 2, 1), (13, 2, 1, 3)]);
            let dl = [0x90, 0, 2, 1, 9, 3, 4, 2, 5, 8, 6, 0];
            assert_eq!(gx_max_index(&dl, &descs, attr.into()), Some(9));
            assert_eq!(gx_max_index(&dl, &descs, 13), Some(6));
        }
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
    }
}
