use internment::Intern;

#[derive(Debug)]
pub enum SymSrc {
    Linker,
    Object {
        file: Intern<String>,
        ext: Intern<String>,
    },
}

#[derive(Default, Debug, PartialEq, Eq, Hash)]
pub enum SymName {
    #[default]
    Unknown,
    Relative {
        label: usize,
    },
    Named {
        name: Intern<String>,
    },
}

#[derive(Default, Debug)]
pub struct LinkerSym {
    depth: usize,
    name: SymName,
    instance: Option<usize>,
    parent: Option<Intern<Sym>>,
    file: String,
    ext: String,
}

#[derive(Default, Debug)]
pub struct SectionSym {
    addr: usize,
    size: usize,
    virt_addr: usize,
    align: Option<usize>,
    name: SymName,
    file: String,
    ext: String,
}

#[derive(Default, Debug)]
pub struct Sym {
    depth: usize,
    addr: usize,
    size: usize,
    virt_addr: usize,
    align: Option<usize>,
    name: SymName,
    instance: Option<usize>,
    parent: Option<Intern<Sym>>,
    file: String,
    ext: String,
}

#[derive(Default, Debug)]
pub struct Section {
    name: Intern<String>,
    syms: Vec<Sym>,
}

#[derive(Default, Debug)]
pub struct Map {
    sections: Vec<Section>,
}
