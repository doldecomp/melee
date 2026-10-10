//! Compile each expression as one function, with lazy branches in C.
use super::{Emitter, identifier, int};
use melee_dat::dwarf::expr::{BinaryOp, Expr, UnaryOp};
use std::fmt::Write as _;

impl Emitter<'_, '_> {
    pub(super) fn expr(&mut self, expr: &Expr) -> String {
        let name = self.compile_expression(expr);
        let _ = writeln!(
            self.expression_code,
            "static const DatExpr {name} = {{ .evaluate = {name}_eval }};\n"
        );
        format!("&{name}")
    }

    pub(super) fn fields(&mut self, expr: &Expr) -> String {
        let name = self.compile_expression(expr);
        format!(".evaluate = {name}_eval")
    }

    fn compile_expression(&mut self, expr: &Expr) -> String {
        let name = format!("dat_expression_{}", self.next_expression);
        self.next_expression += 1;
        let mut body = String::new();
        let mut next_value = 0;
        let value = self.expression_value(&mut body, expr, &mut next_value, 1);
        let _ = writeln!(body, "    *out = {value};\n    return 1;");
        let _ = writeln!(
            self.expression_code,
            "static int {name}_eval(const DatArchive* a, const DatContext* c, unsigned depth, uint64_t* out) {{\n{body}}}"
        );
        name
    }

    /// Emit statements that produce a uint64_t, or return failure from the
    /// enclosing evaluator. Branches contain their own operand evaluation.
    fn expression_value(
        &mut self,
        c: &mut String,
        expr: &Expr,
        next: &mut usize,
        indent: usize,
    ) -> String {
        let value = format!("value{}", *next);
        *next += 1;
        let pad = "    ".repeat(indent);
        match expr {
            Expr::Int(n) => {
                let _ = writeln!(c, "{pad}uint64_t {value} = {};", int(*n));
            }
            Expr::Name(name) => {
                let ident = self.name(name);
                let _ = writeln!(c, "{pad}uint64_t {value};");
                let _ = writeln!(
                    c,
                    "{pad}if (!dat_reader_resolve_name(a, c, {ident}, &{value})) {{"
                );
                if self.macro_body(name) {
                    let _ = writeln!(
                        c,
                        "{pad}    if (depth >= MACRO_DEPTH || !dat_reader_eval_at(a, c, &dat_macro_{}, depth + 1, &{value})) return 0;",
                        identifier(name)
                    );
                } else {
                    let _ = writeln!(c, "{pad}    return 0;");
                }
                let _ = writeln!(c, "{pad}}}");
            }
            Expr::Call(function, args) => {
                let args: Vec<String> = args
                    .iter()
                    .map(|arg| self.expression_value(c, arg, next, indent))
                    .collect();
                let _ = writeln!(c, "{pad}uint64_t {value};");
                let call = match (function.as_str(), args.as_slice()) {
                    ("itCommandLength", [command]) => {
                        format!(
                            "dat_reader_it_command_length({command}, &{value})"
                        )
                    }
                    ("colAnimCommandLength", [command]) => {
                        format!(
                            "dat_reader_col_anim_command_length({command}, &{value})"
                        )
                    }
                    ("cpuCommandLength", [command]) => {
                        let _ = writeln!(
                            c,
                            "{pad}{value} = dat_reader_cpu_command_length({command});"
                        );
                        return value;
                    }
                    (
                        "GXGetTexBufferSize",
                        [width, height, format, mipmap, lod],
                    ) => {
                        format!(
                            "dat_reader_gx_get_tex_buffer_size((uint16_t) {width}, (uint16_t) {height}, (uint32_t) {format}, (uint8_t) {mipmap}, (uint8_t) {lod}, &{value})"
                        )
                    }
                    _ => {
                        let _ = writeln!(c, "{pad}return 0;");
                        return value;
                    }
                };
                let _ = writeln!(c, "{pad}if (!{call}) return 0;");
            }
            Expr::Unary(op, arg) => {
                let arg = self.expression_value(c, arg, next, indent);
                let operation = match op {
                    UnaryOp::Not => format!("{arg} == 0"),
                    UnaryOp::BitNot => format!("~{arg}"),
                    UnaryOp::Neg => format!("(uint64_t) 0 - {arg}"),
                };
                let _ = writeln!(c, "{pad}uint64_t {value} = {operation};");
            }
            Expr::Cond(cond, yes, no) => {
                let cond = self.expression_value(c, cond, next, indent);
                let _ = writeln!(
                    c,
                    "{pad}uint64_t {value};\n{pad}if ({cond} != 0) {{"
                );
                let yes = self.expression_value(c, yes, next, indent + 1);
                let _ =
                    writeln!(c, "{pad}    {value} = {yes};\n{pad}}} else {{");
                let no = self.expression_value(c, no, next, indent + 1);
                let _ = writeln!(c, "{pad}    {value} = {no};\n{pad}}}");
            }
            Expr::Binary(op @ (BinaryOp::Or | BinaryOp::And), left, right) => {
                let left = self.expression_value(c, left, next, indent);
                let condition = if *op == BinaryOp::Or { "==" } else { "!=" };
                let _ = writeln!(
                    c,
                    "{pad}uint64_t {value} = {left} != 0;\n{pad}if ({value} {condition} 0) {{"
                );
                let right = self.expression_value(c, right, next, indent + 1);
                let _ =
                    writeln!(c, "{pad}    {value} = {right} != 0;\n{pad}}}");
            }
            Expr::Binary(op, left, right) => {
                let left = self.expression_value(c, left, next, indent);
                let right = self.expression_value(c, right, next, indent);
                match op {
                    BinaryOp::Div | BinaryOp::Rem => {
                        let _ =
                            writeln!(c, "{pad}if ({right} == 0) return 0;");
                    }
                    BinaryOp::Shl | BinaryOp::Shr => {
                        let _ =
                            writeln!(c, "{pad}if ({right} >= 64) return 0;");
                    }
                    _ => {}
                }
                let operator = match op {
                    BinaryOp::BitOr => "|",
                    BinaryOp::BitXor => "^",
                    BinaryOp::BitAnd => "&",
                    BinaryOp::Eq => "==",
                    BinaryOp::Ne => "!=",
                    BinaryOp::Lt => "<",
                    BinaryOp::Gt => ">",
                    BinaryOp::Le => "<=",
                    BinaryOp::Ge => ">=",
                    BinaryOp::Shl => "<<",
                    BinaryOp::Shr => ">>",
                    BinaryOp::Add => "+",
                    BinaryOp::Sub => "-",
                    BinaryOp::Mul => "*",
                    BinaryOp::Div => "/",
                    BinaryOp::Rem => "%",
                    BinaryOp::Or | BinaryOp::And => unreachable!(),
                };
                let _ = writeln!(
                    c,
                    "{pad}uint64_t {value} = {left} {operator} {right};"
                );
            }
        }
        value
    }
}
