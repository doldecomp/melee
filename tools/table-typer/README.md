# table-typer

Given a C type name, this tool:
1. Looks for `extern` declarations of that type
2. Locates the data corresponding to the declaration in asm files
3. Parses the data to extract functions with known types
4. Rewrites .c and .h files to use the correct types for those functions

Currently the tool works for these types:
- `ItemStateTable`
- `ItemLogicTable`

In theory, it can support other table types, but you'll have to add them to
`tableTypes` and possibly do a bit of touching up in other places.

Example usage:

```
go run . ItemStateTable ../../
```

## Known bugs

The tool cannot add `#include` statements, so rewritten files may fail to
compile if they reference a type that requires a missing `#include`.
