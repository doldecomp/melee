pub(crate) struct TreeSymbol<'a> {
    pub(crate) name: String,
    pub(crate) r#type: &'a str,
    pub(crate) scope: &'a str,
}

pub(crate) struct TableSymbol<'a> {
    pub(crate) section: &'a str,
    pub(crate) addr: u32,
    pub(crate) size: u32,
    pub(crate) align: Option<u8>,
}

#[derive(Debug)]
pub(crate) struct Split<'a> {
    pub(crate) section: &'a str,
    pub(crate) tu: &'a str,
    pub(crate) start: u32,
    pub(crate) end: Option<u32>,
}
