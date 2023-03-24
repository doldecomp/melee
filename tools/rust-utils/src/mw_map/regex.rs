use lazy_static::lazy_static;
use regex::Regex;

macro_rules! create_regex {
    ($name:ident, $regex:expr) => {
        lazy_static! {
            pub(crate) static ref $name: Regex = Regex::new($regex)
                .expect(&format!("Failed to compile {}.", stringify!($name)));
        }
    };
}

create_regex!(EMPTY_RE, "^$");

create_regex!(
    LINKER_SYM_RE,
    r"(?xm) # Ignore whitespace, multiline
        # Start of line with leading spaces
        ^\x20*

        # Linker depth
        (?P<depth>[[:digit:]]+)\]\x20

        # Name of the symbol (word with dots allowed, or @ + number)
        (?:
            (?P<name>[\.[:word:]]+) |
            @(?P<label>[[:digit:]]+)
        )
        # Data symbols can be instanced with $ and then a number
        (?:\$(?P<instance>[[:digit:]]+))?
        \x20

        # Source of a symbol is either the linker or a file
        (?:
            found\x20as\x20(?P<linker>linker)\x20generated\x20symbol |

            # Non-linker symbols have a type and a scope
            \(
            (?P<type>section|object|func|notype),
            (?P<scope>global|local|weak)
            \)\x20found\x20in\x20
            (?P<file>[\.[:word:]]+?)
            \.(?P<ext>\w+)\.o\x20
        )$"
);

create_regex!(
    SECTION_SYM_RE,
    r"(?xm) # Ignore whitespace, multiline

        # Start of line with two spaces
        ^\x20{2}

        # Starting address (8-digit hex)
        (?P<addr>[[:xdigit:]]{8})

        \x20

        # Size (6-digit hex)
        (?P<size>[[:xdigit:]]{6})


        \x20

        # Virtual address (8-digit hex)
        (?P<virt_addr>[[:xdigit:]]{8})

        # Optional alignment value
        (?:
           \x20{2}
           (?P<align>[[:digit:]])
        )?

        \x20

        # Name of the symbol (word with dots allowed, optional @ prefix)
        (?P<name>
            @?[\.[:word:]]+
        )

        # Parent symbol or section (optional)
        (?:
            \x20\(entry\x20of\x20(?P<parent>
                @?[\.\w]+?
            )
            \)
        )?

        \x20\t

        # Filename with .o extension
        (?P<file>
            [[:word:]\x20\.]+
        )

        # Source file extension
        \.
        (?P<ext>
            \w+
        )

        # Don't capture .o extension
        \.o
        \x20

        # End of line
        $"
);
