# `m2c` Decompiler
`m2c` ("*Machine code to C*") is a decompiler for MIPS and PowerPC assembly that produces C code, with partial support for C++.

This project, initially named `mips_to_c`, has the goal to support decompilation projects, which aim to write source code that yields byte-identical output when compiled with a particular build system.
It originally targeted popular compilers of the late 1990's, but it also works well with newer compilers or hand-written assembly.

`m2c` is often used in decompilation workflows with [`splat`](https://github.com/ethteck/splat), [`asm-differ`](https://github.com/simonlindholm/asm-differ), and [`decomp-permuter`](https://github.com/simonlindholm/decomp-permuter).
Its focus on finding "matching" C source differentiates it from other decompilation suites, such as IDA or Ghidra.
Right now the decompiler is fairly functional, though it sometimes generates suboptimal code (especially for loops).

The input is expected to match a particular assembly format, such as that produced by tools like [`mipsdisasm`](https://github.com/queueRAM/sm64tools).
See the `tests/` directory for some example input and output.

[An online version is also available](https://simonsoftware.se/other/m2c.html).

## Install

This project requires Python 3.6 or later. To install the Python dependencies:
```bash
python3 -m pip install --upgrade pycparser

# Optional: If you are on python3.6, you will also need to install "dataclasses"
python3.6 -m pip install --upgrade dataclasses
```

You might need to install `pip` first; on Ubuntu this can be done with:
```bash
sudo apt update
sudo apt install python3-pip
```

## Usage

```bash
python3 m2c.py [options] [-t <target>] [--context <context file>] [-f <function name>] <asmfile>...
```

Run with `--help` to see which options are available.

Context files provided with `--context` are parsed and cached, so subsequent runs with the same file are faster. The cache for `foo/bar.c` is stored in `foo/bar.m2c`. These files can be ignored (added to `.gitignore`), and are automatically regenerated if context files change. Caching can be disabled with the `--no-cache` argument.

### Target Architecture / Compiler / Language

`m2c` has support for both MIPS and PowerPC assembly.
It also has some compiler-specific heuristics and language-specific behavior.
For example, it can demangle C++ symbol names as used by CodeWarrior.

Collectively, the output's architecture, compiler, and source language are referred to as a *target*.
The following target triples are supported:

- `--target mips-ido-c`: MIPS (with O32 ABI), IDO toolchain, C language
- `--target mips-gcc-c`: MIPS (with O32 ABI), GCC toolchain, C language
- `--target ppc-mwcc-c`: PowerPC, MetroWerks CodeWarrior toolchain (`mwccecpp.exe`), C language
- `--target ppc-mwcc-c++`: PowerPC, MetroWerks CodeWarrior toolchain (`mwccecpp.exe`), C++ language

### Multiple functions

By default, `m2c` decompiles all functions in the text sections from the input assembly files.
`m2c` is able to perform a small amount of cross-function type inference, if the functions call each other.

You can limit the function(s) that decompiled by providing the `-f <function name>` flags (or the "Function" dropdown on the website).

### Global Declarations & Initializers

When provided input files with `data`, `rodata`, and/or `bss` sections, `m2c` can generate the initializers for variables it knows the types of.

Qualifier hints such as `const`, `static`, and `extern` are based on which sections the symbols appear in, or if they aren't provided at all.
The output also includes prototypes for functions not declared in the context.

`m2c` cannot generate initializers for structs with bitfields (e.g. `unsigned foo: 3;`) or for symbols that it cannot infer the type of.
For the latter, you can provide a type for the symbol the context.

This feature is controlled with the `--globals` option (or "Global declarations" on the website):

- `--globals=used` is the default behavior, global declarations are emitted for referenced symbols. Initializers are generated when the data/rodata sections are provided.
- `--globals=none` disables globals entirely; only function definitions are emitted.
- `--globals=all` includes all of the output in `used`, but also includes initializers for unreferenced symbols. This can be used to convert data/rodata files without decompiling any functions.

### Struct Field Inference

By default, `m2c` can use type information from decompiled functions to help fill in unknown struct fields.
This behavior can be disabled with `--no-unk-inference` ("Disable unknown struct/type inference" on the website).

For structs in the context, the following fields treated as "unknown" space that can be inferred:

- `char` arrays with a name starting with `unk_`, e.g. `char unk_10[4];`
- any field with a type that starts with `UNK_` or `MIPS2C_UNK`, e.g. `UNK_TYPE4 foo;`

Currently, struct field inference only works on structs without bitfields or [unnamed union fields](https://gcc.gnu.org/onlinedocs/gcc/Unnamed-Fields.html).

The output will include declarations for any struct with at least one inferred field.

### Specifying stack variables

By default, `m2c` infers the types of stack (local) variables, and names them with the `sp` prefix based on their offset.

Internally, the stack is represented as a struct, so it is possible to manually specify the names & types of stack variables by providing a struct declaration in the context. `m2c` looks in the context for a struct with the tag name `_m2c_stack_<function name>` (e.g. `struct _m2c_stack_test` for a function `test()`).

The size of the stack must exactly match the detected frame size, or `m2c` will return an error.
If you run `m2c` with the `--stack-structs` option ("Stack struct templates" on the website), the output will include the inferred stack declaration, which can then be edited and provided as context by re-running `m2c`.

#### Example

Here is an example for specifying the stack for the `custom_stack` end-to-end test.

First, run `m2c` with the `--stack-structs` option to get the inferred struct for the `test()` function:

<details>
    <summary><code>python3 m2c.py tests/end_to_end/custom_stack/irix-o2.s -f test --stack-structs</code></summary>

```c
struct _m2c_stack_test {
    /* 0x00 */ char pad0[0x20];
    /* 0x20 */ s8 sp20;                             /* inferred */
    /* 0x21 */ char pad21[0x3];                     /* maybe part of sp20[4]? */
    /* 0x24 */ s32 sp24;                            /* inferred */
    /* 0x28 */ s32 sp28;                            /* inferred */
    /* 0x2C */ s8 sp2C;                             /* inferred */
    /* 0x2D */ char pad2D[0x3];                     /* maybe part of sp2C[4]? */
    /* 0x30 */ s8 sp30;                             /* inferred */
    /* 0x31 */ char pad31[0x3];                     /* maybe part of sp30[4]? */
    /* 0x34 */ s8 sp34;                             /* inferred */
    /* 0x35 */ char pad35[0x2];                     /* maybe part of sp34[3]? */
    /* 0x37 */ s8 sp37;                             /* inferred */
};                                                  /* size = 0x38 */

? func_00400090(s8 *);                              /* static */
s32 test(void *arg0);                               /* static */

s32 test(void *arg0) {
    s8 sp37;
    s8 sp34;
    s8 sp30;
    s8 sp2C;
    s32 sp28;
    s32 sp24;
    s8 sp20;
    s32 temp_t4;

    func_00400090(&sp37);
    func_00400090(&sp34);
    func_00400090(&sp30);
    func_00400090(&sp2C);
    func_00400090(&sp20);
    sp37 = arg0->unk0 + arg0->unk4;
    sp34 = arg0->unk0 + arg0->unk8;
    temp_t4 = arg0->unk4 + arg0->unk8;
    sp30 = temp_t4;
    sp20 = arg0->unk0 * sp37;
    sp24 = arg0->unk4 * (s16) sp34;
    sp28 = arg0->unk8 * temp_t4;
    if (sp37 != 0) {
        sp2C = arg0;
    } else {
        sp2C = &sp20;
    }
    return sp37 + (s16) sp34 + (s32) sp30 + *(s32 *) sp2C + sp24;
}
```
</details>

Now, based on the body of the `test()` function, we can make some guesses about the types of these variables, and give them more descriptive names:

```c
// Save this file as `test_context.c`
struct Vec {
    s32 x, y, z;
};

struct _m2c_stack_test {
    char pad0[0x20];
    struct Vec vec;
    struct Vec *vec_ptr;
    s32 scale_z;
    s16 scale_y;
    char pad36[1];
    s8 scale_x;
}; /* size 0x38 */

int test(struct Vec *vec_arg);
```

Finally, re-run `m2c` with our custom stack as part of the `--context`. The `--context` option can be specified multiple times to combine files.

<details>
    <summary><code>python3 m2c.py tests/end_to_end/custom_stack/irix-o2.s -f test --context test_context.c</code></summary>

```c
? func_00400090(s8 *);                              /* static */

s32 test(struct Vec *vec_arg) {
    s8 scale_x;
    s16 scale_y;
    s32 scale_z;
    struct Vec *vec_ptr;
    struct Vec vec;
    s32 temp_t4;

    func_00400090(&scale_x);
    func_00400090((s8 *) &scale_y);
    func_00400090((s8 *) &scale_z);
    func_00400090((s8 *) &vec_ptr);
    func_00400090((s8 *) &vec);
    scale_x = vec_arg->x + vec_arg->y;
    scale_y = vec_arg->x + vec_arg->z;
    temp_t4 = vec_arg->y + vec_arg->z;
    scale_z = temp_t4;
    vec = vec_arg->x * scale_x;
    vec.y = vec_arg->y * scale_y;
    vec.z = vec_arg->z * temp_t4;
    if (scale_x != 0) {
        vec_ptr = vec_arg;
    } else {
        vec_ptr = &vec;
    }
    return scale_x + scale_y + scale_z + vec_ptr->x + vec.y;
}
```
</details>

### Formatting

The following options control the formatting details of the output, such as braces style or numeric format. See `./m2c.py --help` for more details. 

(The option name on the website, if available, is in parentheses.)

- `--valid-syntax`
- `--allman` ("Allman braces")
- `--pointer-style` ("`*` to the left")
- `--unk-underscore`
- `--hex-case`
- `--comment-style {multiline,oneline,none}` ("Comment style")
- `--comment-column N` ("Comment style")
- `--no-casts`
- `--zfill-constants` ("0-fill constants")
- `--deterministic-vars`

Note: `--valid-syntax` is used to produce output that is less human-readable, but is likely to directly compile without edits. This can be used to go directly from assembly to the permuter without human intervention.

### Debugging poor results (Advanced)

There are several options to `m2c` which can be used to troubleshoot poor results. Many of these options produce more "primitive" output or debugging information.

- `--no-andor` ("Disable &&/||"): Disable complex conditional detection, such as `if (a && b)`. Instead, emit each part of the conditional as a separate `if` statement. Ands, ors, nots, etc. are usually represented with `goto`s.
- `--no-switches` ("Disable irregular switch detection"): Disable "irregular" `switch` statements, where the compiler emits a single `switch` as a series of branches and/or jump tables. By default, these are coalesced into a single `switch` and marked with an `/* irregular */` comment.
- `--no-unk-inference` ("Disable unknown struct/type inference"): Disable attempting to infer struct fields/types in unknown struct sections and global symbols. See the [_Struct Field Inference_](#struct-field-inference) section above.
- `--gotos-only` ("Use gotos for everything"): Do not detect loops or complex conditionals. This format is close to a 1-1 translation of the assembly.
    - Note: to use a goto for a single branch, don't use this flag, but add `# GOTO` to the assembly input.
- `--debug` ("Debug info"): include debug information inline with the code, such as basic block boundaries & labels.
- `--void` ("Force void return type"): assume that the decompiled function has return type `void`. Alternatively: provide the function prototype in the context.

#### Visualization

`m2c` can generate an SVG representation of the control flow of a function, which can sometimes be helpful to untangle complex loops or early returns.

Pass `--visualize` on the command line, or use the "Visualize" button on the website. The output will be an SVG file.

Example to produce C & assembly visualizations of `my_fn()`:

```sh
python3 ./m2c.py --visualize=c --context ctx.c -f my_fn my_asm.s > my_fn_c.svg
python3 ./m2c.py --visualize=asm --context ctx.c -f my_fn my_asm.s > my_fn_asm.svg
```

### Migrating from `mips_to_c.py`

This tool was originally known as `mips_to_c`. As part of the rename, deprecated command line arguments were removed.

When migrating to `m2c`, note the following changes to the CLI:

- Entrypoint rename: `./mips_to_c.py` becomes `./m2c.py`
- To limit decompilation to a [single function](#multiple-function): use `-f FN, --function FN`
- `--rodata` is [no longer needed](#multiple-functions): `my_text.s --rodata my_data.s` becomes `my_text.s my_data.s`
- `--compiler` has been replaced by [`--target`](#target-architecture--compiler--language): `--compiler gcc` becomes `--target mips-gcc-c`
- `--structs` is now the [default behavior](#struct-field-inference): remove `--structs` from the arguments

## Contributing

There is much low-hanging fruit still. Take a look at the issues if you want to help out.

We use `black` to auto-format our code and `mypy` for type checking. We recommend using `pre-commit` to ensure only auto-formatted code is committed. To set these up, run:
```bash
pip install pre-commit black mypy
pre-commit install
```

Your commits will then be automatically formatted per commit. You can also manually run `black` on the command-line.

Type annotations are used for all Python code. `mypy` should pass without any errors.

To get pretty graph visualizations, install `graphviz` using `pip` and globally on your system (e.g. `sudo apt install graphviz`), and pass the `--visualize` flag.

## Tests

There is a small test suite, which works as follows:
 - As you develop your commit, occasionally run `./run_tests.py` to see if any tests have changed output.
   These tests run the decompiler on a small corpus of assembly.
 - Before pushing your commit, run `./run_tests.py --overwrite` to write changed tests to disk, and commit resultant changes.

### Running Decompilation Project Tests

It's possible to use the entire corpus of assembly files from decompilation projects as regression tests.

For now, the output of these tests are not tracked in version control.
You need to run `./run_tests.py --overwrite ...` **before** making any code changes to create the baseline output.

As an example, if you have the `oot` project cloned locally in the parent directory containing `m2c`, the following will decompile all of its assembly files.

```bash
./run_tests.py --project ../oot --project-with-context ../oot
```

This has been tested with:
- [zeldaret/oot](https://github.com/zeldaret/oot)
- [zeldaret/mm](https://github.com/zeldaret/mm)
    - See notes below, the repository needs to be partially built
- [pmret/papermario](https://github.com/pmret/papermario)
    - Need to use the `ver/us` or `ver/jp` subfolder, e.g. `--project ../papermario/ver/us`

#### Creating Context Files

The following bash can be used in each decompilation project to create a "universal" context file that can be used for decompiling any assembly file in the project.
This creates `ctx.c` in the project directory.

```bash
cd mm       # Or oot, papermario, etc.
find include/ src/ -type f -name "*.h" | sed -e 's/.*/#include "\0"/' > ctx_includes.c
tools/m2ctx.py ctx_includes.c
```

#### Notes for Majora's Mask

The build system in the MM decompilation project is currently being re-written.
It uses "transient" assembly that is not checked in, and in the normal build process it re-groups `.rodata` sections by function.

To use the MM project, run the following to *just* build the transient assembly files (and avoid running `split_asm.py`).

```bash
cd mm
make distclean
make setup
make asm/disasm.dep
```

The repository should be setup correctly if there are `asm/code`, `asm/boot`, and `asm/overlays` folders with `.asm` files, but there *should not* be an `asm/non_matchings` folder.

### Coverage

Code branch coverage can be computed by running `./run_tests.py --coverage`.
By default, this will generate an HTML coverage report `./htmlcov/index.html`.

### Adding an End-to-End Test

You are encouraged to add new end-to-end tests using the `./tests/add_test.py` script.

You'll need the IDO `cc` compiler and [sm64tools](https://github.com/queueRAM/sm64tools).

A good reference test to base your new test on is [`array-access`](tests/end_to_end/array-access).

Create a new directory in `tests/end_to_end`, and write the `orig.c` test case.
If you want the test to pass in C context, also add `irix-o2-flags.txt` & `irix-g-flags.txt` files.

After writing these files, run `add_test.py` with the path to the new `orig.c` file, as shown below.
This example assumes that sm64tools is cloned & built in your home directory, and that the IDO compiler is available from the OOT decompilation project.
You should change these exported paths to match your system.

```bash
export SM64_TOOLS=$HOME/sm64tools/build/
export IDO_CC=$HOME/oot/tools/ido_recomp/linux/7.1/cc
./tests/add_test.py $PWD/tests/end_to_end/my-new-test/orig.c
```

This should create `irix-o2.s` and `irix-g.s` files in your test directory.

Now, run `./run_tests.py --overwrite` to invoke the decompiler and write the output to `irix-o2-out.c` and `irix-g-out.c`. 
Finally, `git add` your test to track it.

```bash
./run_tests.py --overwrite
git add tests/end_to_end/my-new-test
```
