use anyhow::anyhow;
use clap::Parser;
use lazy_static::lazy_static;
use regex::Regex;

#[derive(Parser)]
#[command(author, version, about, long_about = None)]
struct Cli {
    flags: Vec<String>,

    #[arg(short, long)]
    signed: bool,
}

lazy_static! {
    static ref FLAGS_RE: Regex = Regex::new(
        r"(?xi)
            # x flag ignores whitespace and allows comments.
            # i flag matches case-insensitively.

            # Non-capturing group to contain the or's
            ^(?:
                # Each of the following groups begin with a non-capturing
                # group to contain the prefix, then a capturing group
                # containing the value.
                # Groups are in order of precedence (1=highest, 4=lowest).
                # Numbered groups are used to simplify parsing.

                # Group 1: Hexidecimal
                (?:0x([0-9a-f]+)) |

                # Group 2: Binary
                (?:0b([01]+)) |

                # Group 3: Octal
                (?:0([0-7]+)) |

                # Group 4: Decimal
                (?:([0-9]+))
            )$"
    )
    .unwrap();
    static ref FLAGS_RADIX: [u32; 4] = [16, 2, 8, 10];
}

fn parse_input(s: &str) -> anyhow::Result<u64> {
    FLAGS_RE
        .captures(s)
        .map(|c| {
            (0..FLAGS_RADIX.len()).find_map(|i| {
                c.get(i + 1)
                    .map(|g| {
                        let radix = FLAGS_RADIX[i];
                        let str = &g.as_str();
                        let int = u64::from_str_radix(&str, radix);
                        int.ok()
                    })
                    .flatten()
            })
        })
        .flatten()
        .ok_or(anyhow!("Invalid input."))
}

fn format_output(i: usize, flags: &str, signed: bool) -> String {
    match parse_input(flags) {
        Ok(parsed_flags) => {
            const I32_MAX: u64 = i32::MAX as u64;
            const U32_MAX: u64 = u32::MAX as u64;
            const I64_MAX: u64 = i64::MAX as u64;

            let flags_str = if parsed_flags == 0 {
                "0".to_string()
            } else {
                (0..64)
                    .filter_map(|i| {
                        let mask = (1 as u64) << i;

                        if parsed_flags & mask != 0 {
                            let one_str = match mask {
                                0..=I32_MAX => "1",
                                0..=U32_MAX => "1U",
                                0..=I64_MAX => "1L",
                                0..=u64::MAX => "1UL",
                            };
                            Some(format!("({one_str} << {i})").to_string())
                        } else {
                            None
                        }
                    })
                    .collect::<Vec<_>>()
                    .join(" | ")
            };

            let type_str = match (parsed_flags, signed) {
                (0..=I32_MAX, true) => "i32",
                (0..=U32_MAX, _) => "u32",
                (0..=I64_MAX, true) => "i64",
                (0..=u64::MAX, _) => "u64",
            };

            format!(
                r"// {flags}
static {type_str} const flags{i} = {flags_str};"
            )
        }
        Err(err) => format!("/// @warning {}: {}", flags, err.to_string()),
    }
}

fn main() -> anyhow::Result<()> {
    let cli = Cli::parse();

    let output = cli
        .flags
        .iter()
        .enumerate()
        .map(|(i, flags)| format_output(i, &flags, cli.signed))
        .collect::<Vec<_>>()
        .join("\n\n");

    println!("{output}");
    Ok(())
}
