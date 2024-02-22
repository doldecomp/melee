###
# decomp-toolkit project generator
# Generates build.ninja and objdiff.json.
#
# This generator is intentionally project-agnostic
# and shared between multiple projects. Any configuration
# specific to a project should be added to `configure.py`.
#
# If changes are made, please submit a PR to
# https://github.com/encounter/dtk-template
###

import io
import json
import math
import os
import platform
import sys
from pathlib import Path
from typing import Any, Dict, List, Optional, Set, Tuple, Union

from . import ninja_syntax

if sys.platform == "cygwin":
    sys.exit(
        f"Cygwin/MSYS2 is not supported."
        f"\nPlease use native Windows Python instead."
        f"\n(Current path: {sys.executable})"
    )

LibDict = Dict[str, Any]


class Object:
    def __init__(self, completed: bool, name: str, **options: Any) -> None:
        self.name = name
        self.completed = completed
        self.options: Dict[str, Any] = {
            "add_to_all": True,
            "cflags": None,
            "extra_cflags": None,
            "mw_version": None,
            "shiftjis": True,
            "source": name,
        }
        self.options.update(options)


class ProjectConfig:
    def __init__(self) -> None:
        # Paths
        self.build_dir: Path = Path("build")
        self.src_dir: Path = Path("src")
        self.tools_dir: Path = Path("tools")

        # Tooling
        self.dtk_tag: Optional[str] = None  # Git tag
        self.build_dtk_path: Optional[Path] = None  # If None, download
        self.compilers_tag: Optional[str] = None  # 1
        self.compilers_path: Optional[Path] = None  # If None, download
        self.wibo_tag: Optional[str] = None  # Git tag
        self.wrapper: Optional[Path] = None  # If None, download wibo on Linux
        self.sjiswrap_tag: Optional[str] = None  # Git tag
        self.sjiswrap_path: Optional[Path] = None  # If None, download

        # Project config
        self.build_rels: bool = True  # Build REL files
        self.check_sha_path: Optional[Path] = None  # Path to version.sha1
        self.config_path: Optional[Path] = None  # Path to config.yml
        self.debug: bool = False  # Build with debug info
        self.generate_map: bool = False  # Generate map file(s)
        self.ldflags: Optional[List[str]] = None  # Linker flags
        self.libs: Optional[List[Dict[str, Any]]] = None  # List of libraries
        self.linker_version: Optional[str] = None  # mwld version
        self.version: Optional[str] = None  # Version name
        self.warn_missing_config: bool = False  # Warn on missing unit configuration
        self.warn_missing_source: bool = False  # Warn on missing source file
        self.rel_strip_partial: bool = True  # Generate PLFs with -strip_partial
        self.rel_empty_file: Optional[Path] = (
            None  # Path to empty.c for generating empty RELs
        )

        # Progress output and progress.json config
        self.progress_all: bool = True  # Include combined "all" category
        self.progress_modules: bool = True  # Include combined "modules" category
        self.progress_each_module: bool = (
            True  # Include individual modules, disable for large numbers of modules
        )

        # Progress fancy printing
        self.progress_use_fancy: bool = False
        self.progress_code_fancy_frac: int = 0
        self.progress_code_fancy_item: str = ""
        self.progress_data_fancy_frac: int = 0
        self.progress_data_fancy_item: str = ""

    def validate(self) -> None:
        required_attrs = [
            "build_dir",
            "src_dir",
            "tools_dir",
            "check_sha_path",
            "config_path",
            "ldflags",
            "linker_version",
            "libs",
            "version",
        ]
        for attr in required_attrs:
            if getattr(self, attr) is None:
                sys.exit(f"ProjectConfig.{attr} missing")

    def find_object(self, name: str) -> Optional[Tuple[Dict[str, Any], Object]]:
        for lib in self.libs or {}:
            for obj in lib["objects"]:
                if obj.name == name:
                    return lib, obj
        return None

    def out_path(self) -> Path:
        return self.build_dir / str(self.version)


def is_windows() -> bool:
    return os.name == "nt"


# On Windows, we need this to use && in commands
CHAIN = "cmd /c " if is_windows() else ""
# Native executable extension
EXE = ".exe" if is_windows() else ""


# Load decomp-toolkit generated config.json
def load_build_config(
    config: ProjectConfig, build_config_path: Path
) -> Optional[Dict[str, Any]]:
    if not build_config_path.is_file():
        return None

    def versiontuple(v: str) -> Tuple[int, ...]:
        return tuple(map(int, (v.split("."))))

    f = open(build_config_path, "r", encoding="utf-8")
    build_config: Dict[str, Any] = json.load(f)
    config_version = build_config.get("version")
    if not config_version:
        # Invalid config.json
        f.close()
        os.remove(build_config_path)
        return None

    dtk_version = str(config.dtk_tag)[1:]  # Strip v
    if versiontuple(config_version) < versiontuple(dtk_version):
        # Outdated config.json
        f.close()
        os.remove(build_config_path)
        return None

    f.close()
    return build_config


# Generate build.ninja and objdiff.json
def generate_build(config: ProjectConfig) -> None:
    build_config = load_build_config(config, config.out_path() / "config.json")
    generate_build_ninja(config, build_config)
    generate_objdiff_config(config, build_config)


# Generate build.ninja
def generate_build_ninja(
    config: ProjectConfig, build_config: Optional[Dict[str, Any]]
) -> None:
    config.validate()

    out = io.StringIO()
    n = ninja_syntax.Writer(out)
    n.variable("ninja_required_version", "1.3")
    n.newline()

    configure_script = Path(os.path.relpath(os.path.abspath(sys.argv[0])))
    python_lib = Path(os.path.relpath(__file__))
    python_lib_dir = python_lib.parent
    n.comment("The arguments passed to configure.py, for rerunning it.")
    n.variable("configure_args", sys.argv[1:])
    n.variable("python", f'"{sys.executable}"')
    n.newline()

    ###
    # Variables
    ###
    n.comment("Variables")
    ldflags = " ".join(config.ldflags or [])
    if config.generate_map:
        ldflags += " -mapunused"
    if config.debug:
        ldflags += " -g"
    n.variable("ldflags", ldflags)
    n.variable("mw_version", config.linker_version)
    n.newline()

    ###
    # Tooling
    ###
    n.comment("Tooling")

    build_path = config.out_path()
    build_tools_path = config.build_dir / "tools"
    download_tool = config.tools_dir / "download_tool.py"
    n.rule(
        name="download_tool",
        command=f"$python {download_tool} $tool $out --tag $tag",
        description="TOOL $out",
    )

    if config.build_dtk_path:
        dtk = build_tools_path / "release" / f"dtk{EXE}"
        n.rule(
            name="cargo",
            command="cargo build --release --manifest-path $in --bin $bin --target-dir $target",
            description="CARGO $bin",
            depfile=Path("$target") / "release" / "$bin.d",
            deps="gcc",
        )
        n.build(
            outputs=dtk,
            rule="cargo",
            inputs=config.build_dtk_path / "Cargo.toml",
            implicit=config.build_dtk_path / "Cargo.lock",
            variables={
                "bin": "dtk",
                "target": build_tools_path,
            },
        )
    elif config.dtk_tag:
        dtk = build_tools_path / f"dtk{EXE}"
        n.build(
            outputs=dtk,
            rule="download_tool",
            implicit=download_tool,
            variables={
                "tool": "dtk",
                "tag": config.dtk_tag,
            },
        )
    else:
        sys.exit("ProjectConfig.dtk_tag missing")

    if config.sjiswrap_path:
        sjiswrap = config.sjiswrap_path
    elif config.sjiswrap_tag:
        sjiswrap = build_tools_path / "sjiswrap.exe"
        n.build(
            outputs=sjiswrap,
            rule="download_tool",
            implicit=download_tool,
            variables={
                "tool": "sjiswrap",
                "tag": config.sjiswrap_tag,
            },
        )
    else:
        sys.exit("ProjectConfig.sjiswrap_tag missing")

    # Only add an implicit dependency on wibo if we download it
    wrapper = config.wrapper
    wrapper_implicit: Optional[Path] = None
    if (
        config.wibo_tag is not None
        and sys.platform == "linux"
        and platform.machine() in ("i386", "x86_64")
        and config.wrapper is None
    ):
        wrapper = build_tools_path / "wibo"
        wrapper_implicit = wrapper
        n.build(
            outputs=wrapper,
            rule="download_tool",
            implicit=download_tool,
            variables={
                "tool": "wibo",
                "tag": config.wibo_tag,
            },
        )
    if not is_windows() and wrapper is None:
        wrapper = Path("wine")
    wrapper_cmd = f"{wrapper} " if wrapper else ""

    compilers_implicit: Optional[Path] = None
    if config.compilers_path:
        compilers = config.compilers_path
    elif config.compilers_tag:
        compilers = config.build_dir / "compilers"
        compilers_implicit = compilers
        n.build(
            outputs=compilers,
            rule="download_tool",
            implicit=download_tool,
            variables={
                "tool": "compilers",
                "tag": config.compilers_tag,
            },
        )
    else:
        sys.exit("ProjectConfig.compilers_tag missing")

    n.newline()

    ###
    # Build rules
    ###
    compiler_path = compilers / "$mw_version"

    # MWCC
    mwcc = compiler_path / "mwcceppc.exe"
    mwcc_cmd = f"{wrapper_cmd}{mwcc} $cflags -MMD -c $in -o $basedir"
    mwcc_implicit: List[Optional[Path]] = [compilers_implicit or mwcc, wrapper_implicit]

    # MWCC with UTF-8 to Shift JIS wrapper
    mwcc_sjis_cmd = f"{wrapper_cmd}{sjiswrap} {mwcc} $cflags -MMD -c $in -o $basedir"
    mwcc_sjis_implicit: List[Optional[Path]] = [*mwcc_implicit, sjiswrap]

    # MWLD
    mwld = compiler_path / "mwldeppc.exe"
    mwld_cmd = f"{wrapper_cmd}{mwld} $ldflags -o $out @$out.rsp"
    mwld_implicit: List[Optional[Path]] = [compilers_implicit or mwld, wrapper_implicit]

    if os.name != "nt":
        transform_dep = config.tools_dir / "transform_dep.py"
        mwcc_cmd += f" && $python {transform_dep} $basefile.d $basefile.d"
        mwcc_sjis_cmd += f" && $python {transform_dep} $basefile.d $basefile.d"
        mwcc_implicit.append(transform_dep)
        mwcc_sjis_implicit.append(transform_dep)

    n.comment("Link ELF file")
    n.rule(
        name="link",
        command=mwld_cmd,
        description="LINK $out",
        rspfile="$out.rsp",
        rspfile_content="$in_newline",
    )
    n.newline()

    n.comment("Generate DOL")
    n.rule(
        name="elf2dol",
        command=f"{dtk} elf2dol $in $out",
        description="DOL $out",
    )
    n.newline()

    n.comment("Generate REL(s)")
    makerel_rsp = build_path / "makerel.rsp"
    n.rule(
        name="makerel",
        command=f"{dtk} rel make -w -c $config @{makerel_rsp}",
        description="REL",
        rspfile=makerel_rsp,
        rspfile_content="$in_newline",
    )
    n.newline()

    n.comment("MWCC build")
    n.rule(
        name="mwcc",
        command=mwcc_cmd,
        description="MWCC $out",
        depfile="$basefile.d",
        deps="gcc",
    )
    n.newline()

    n.comment("MWCC build (with UTF-8 to Shift JIS wrapper)")
    n.rule(
        name="mwcc_sjis",
        command=mwcc_sjis_cmd,
        description="MWCC $out",
        depfile="$basefile.d",
        deps="gcc",
    )
    n.newline()

    n.comment("Host build")
    n.variable("host_cflags", "-I include -Wno-trigraphs")
    n.variable(
        "host_cppflags",
        "-std=c++98 -I include -fno-exceptions -fno-rtti -D_CRT_SECURE_NO_WARNINGS -Wno-trigraphs -Wno-c++11-extensions",
    )
    n.rule(
        name="host_cc",
        command="clang $host_cflags -c -o $out $in",
        description="CC $out",
    )
    n.rule(
        name="host_cpp",
        command="clang++ $host_cppflags -c -o $out $in",
        description="CXX $out",
    )
    n.newline()

    ###
    # Source files
    ###
    n.comment("Source files")
    build_src_path = build_path / "src"
    build_host_path = build_path / "host"
    build_config_path = build_path / "config.json"

    def map_path(path: Path) -> Path:
        return path.parent / (path.name + ".MAP")

    class LinkStep:
        def __init__(self, config: Dict[str, Any]) -> None:
            self.name: str = config["name"]
            self.module_id: int = config["module_id"]
            self.ldscript: Optional[Path] = config["ldscript"]
            self.entry = config["entry"]
            self.inputs: List[str] = []

        def add(self, obj: str) -> None:
            self.inputs.append(obj)

        def output(self) -> Path:
            if self.module_id == 0:
                return build_path / f"{self.name}.dol"
            else:
                return build_path / self.name / f"{self.name}.rel"

        def partial_output(self) -> Path:
            if self.module_id == 0:
                return build_path / f"{self.name}.elf"
            else:
                return build_path / self.name / f"{self.name}.plf"

        def write(self, n: ninja_syntax.Writer) -> None:
            n.comment(f"Link {self.name}")
            if self.module_id == 0:
                elf_path = build_path / f"{self.name}.elf"
                dol_path = build_path / f"{self.name}.dol"
                elf_ldflags = f"$ldflags -lcf {self.ldscript}"
                if config.generate_map:
                    elf_map = map_path(elf_path)
                    elf_ldflags += f" -map {elf_map}"
                else:
                    elf_map = None
                n.build(
                    outputs=elf_path,
                    rule="link",
                    inputs=self.inputs,
                    implicit=[self.ldscript, *mwld_implicit],
                    implicit_outputs=elf_map,
                    variables={"ldflags": elf_ldflags},
                )
                n.build(
                    outputs=dol_path,
                    rule="elf2dol",
                    inputs=elf_path,
                    implicit=dtk,
                )
            else:
                preplf_path = build_path / self.name / f"{self.name}.preplf"
                plf_path = build_path / self.name / f"{self.name}.plf"
                preplf_ldflags = f"$ldflags -sdata 0 -sdata2 0 -r"
                plf_ldflags = f"$ldflags -sdata 0 -sdata2 0 -r1 -lcf {self.ldscript}"
                if self.entry:
                    plf_ldflags += f" -m {self.entry}"
                    # -strip_partial is only valid with -m
                    if config.rel_strip_partial:
                        plf_ldflags += " -strip_partial"
                if config.generate_map:
                    preplf_map = map_path(preplf_path)
                    preplf_ldflags += f" -map {preplf_map}"
                    plf_map = map_path(plf_path)
                    plf_ldflags += f" -map {plf_map}"
                else:
                    preplf_map = None
                    plf_map = None
                n.build(
                    outputs=preplf_path,
                    rule="link",
                    inputs=self.inputs,
                    implicit=mwld_implicit,
                    implicit_outputs=preplf_map,
                    variables={"ldflags": preplf_ldflags},
                )
                n.build(
                    outputs=plf_path,
                    rule="link",
                    inputs=self.inputs,
                    implicit=[self.ldscript, preplf_path, *mwld_implicit],
                    implicit_outputs=plf_map,
                    variables={"ldflags": plf_ldflags},
                )
            n.newline()

    if build_config:
        link_steps: List[LinkStep] = []
        used_compiler_versions: Set[str] = set()
        source_inputs: List[Path] = []
        host_source_inputs: List[Path] = []
        source_added: Set[Path] = set()

        def make_cflags_str(cflags: Union[str, List[str]]) -> str:
            if isinstance(cflags, list):
                return " ".join(cflags)
            else:
                return cflags

        def add_unit(build_obj: Dict[str, Any], link_step: LinkStep) -> None:
            obj_path, obj_name = build_obj["object"], build_obj["name"]
            result = config.find_object(obj_name)
            if not result:
                if config.warn_missing_config and not build_obj["autogenerated"]:
                    print(f"Missing configuration for {obj_name}")
                link_step.add(obj_path)
                return

            lib, obj = result
            lib_name = lib["lib"]
            src_dir = Path(lib.get("src_dir", config.src_dir))

            options = obj.options
            completed = obj.completed

            unit_src_path = src_dir / str(options["source"])

            if not unit_src_path.exists():
                if config.warn_missing_source or completed:
                    print(f"Missing source file {unit_src_path}")
                link_step.add(obj_path)
                return

            mw_version = options["mw_version"] or lib["mw_version"]
            cflags_str = make_cflags_str(options["cflags"] or lib["cflags"])
            if options["extra_cflags"] is not None:
                extra_cflags_str = make_cflags_str(options["extra_cflags"])
                cflags_str += " " + extra_cflags_str
            used_compiler_versions.add(mw_version)

            base_object = Path(obj.name).with_suffix("")
            src_obj_path = build_src_path / f"{base_object}.o"
            src_base_path = build_src_path / base_object

            if src_obj_path not in source_added:
                source_added.add(src_obj_path)

                n.comment(f"{obj_name}: {lib_name} (linked {completed})")
                n.build(
                    outputs=src_obj_path,
                    rule="mwcc_sjis" if options["shiftjis"] else "mwcc",
                    inputs=unit_src_path,
                    variables={
                        "mw_version": Path(mw_version),
                        "cflags": cflags_str,
                        "basedir": os.path.dirname(src_base_path),
                        "basefile": src_base_path,
                    },
                    implicit=(
                        mwcc_sjis_implicit if options["shiftjis"] else mwcc_implicit
                    ),
                )

                if lib["host"]:
                    host_obj_path = build_host_path / f"{base_object}.o"
                    host_base_path = build_host_path / base_object
                    n.build(
                        outputs=host_obj_path,
                        rule="host_cc" if unit_src_path.suffix == ".c" else "host_cpp",
                        inputs=unit_src_path,
                        variables={
                            "basedir": os.path.dirname(host_base_path),
                            "basefile": host_base_path,
                        },
                    )
                    if options["add_to_all"]:
                        host_source_inputs.append(host_obj_path)
                n.newline()

                if options["add_to_all"]:
                    source_inputs.append(src_obj_path)

            if completed:
                obj_path = src_obj_path
            link_step.add(obj_path)

        # Add DOL link step
        link_step = LinkStep(build_config)
        for unit in build_config["units"]:
            add_unit(unit, link_step)
        link_steps.append(link_step)

        if config.build_rels:
            # Add REL link steps
            for module in build_config["modules"]:
                module_link_step = LinkStep(module)
                for unit in module["units"]:
                    add_unit(unit, module_link_step)
                # Add empty object to empty RELs
                if len(module_link_step.inputs) == 0:
                    if not config.rel_empty_file:
                        sys.exit("ProjectConfig.rel_empty_file missing")
                    add_unit(
                        {
                            "object": None,
                            "name": config.rel_empty_file,
                            "autogenerated": True,
                        },
                        module_link_step,
                    )
                link_steps.append(module_link_step)
        n.newline()

        # Check if all compiler versions exist
        for mw_version in used_compiler_versions:
            mw_path = compilers / mw_version / "mwcceppc.exe"
            if config.compilers_path and not os.path.exists(mw_path):
                sys.exit(f"Compiler {mw_path} does not exist")

        # Check if linker exists
        mw_path = compilers / str(config.linker_version) / "mwldeppc.exe"
        if config.compilers_path and not os.path.exists(mw_path):
            sys.exit(f"Linker {mw_path} does not exist")

        ###
        # Link
        ###
        for step in link_steps:
            step.write(n)
        n.newline()

        ###
        # Generate RELs
        ###
        generated_rels: List[str] = []
        for link in build_config["links"]:
            # Map module names to link steps
            link_steps_local = list(
                filter(
                    lambda step: step.name in link["modules"],
                    link_steps,
                )
            )
            link_steps_local.sort(key=lambda step: step.module_id)
            # RELs can be the output of multiple link steps,
            # so we need to filter out duplicates
            rels_to_generate = list(
                filter(
                    lambda step: step.module_id != 0
                    and not step.name in generated_rels,
                    link_steps_local,
                )
            )
            if len(rels_to_generate) == 0:
                continue
            generated_rels.extend(map(lambda step: step.name, rels_to_generate))
            rel_outputs = list(
                map(
                    lambda step: step.output(),
                    rels_to_generate,
                )
            )
            n.comment("Generate RELs")
            n.build(
                outputs=rel_outputs,
                rule="makerel",
                inputs=list(map(lambda step: step.partial_output(), link_steps_local)),
                implicit=[dtk, config.config_path],
                variables={"config": config.config_path},
            )
            n.newline()

        ###
        # Helper rule for building all source files
        ###
        n.comment("Build all source files")
        n.build(
            outputs="all_source",
            rule="phony",
            inputs=source_inputs,
        )
        n.newline()

        ###
        # Helper rule for building all source files, with a host compiler
        ###
        n.comment("Build all source files with a host compiler")
        n.build(
            outputs="all_source_host",
            rule="phony",
            inputs=host_source_inputs,
        )
        n.newline()

        ###
        # Check hash
        ###
        n.comment("Check hash")
        ok_path = build_path / "ok"
        quiet = "-q " if len(link_steps) > 3 else ""
        n.rule(
            name="check",
            command=f"{dtk} shasum {quiet} -c $in -o $out",
            description="CHECK $in",
        )
        n.build(
            outputs=ok_path,
            rule="check",
            inputs=config.check_sha_path,
            implicit=[dtk, *map(lambda step: step.output(), link_steps)],
        )
        n.newline()

        ###
        # Calculate progress
        ###
        n.comment("Calculate progress")
        progress_path = build_path / "progress.json"
        n.rule(
            name="progress",
            command=f"$python {configure_script} $configure_args progress",
            description="PROGRESS",
        )
        n.build(
            outputs=progress_path,
            rule="progress",
            implicit=[ok_path, configure_script, python_lib, config.config_path],
        )

        ###
        # Helper tools
        ###
        # TODO: make these rules work for RELs too
        dol_link_step = link_steps[0]
        dol_elf_path = dol_link_step.partial_output()
        n.comment("Check for mismatching symbols")
        n.rule(
            name="dol_diff",
            command=f"{dtk} -L error dol diff $in",
            description=f"DIFF {dol_elf_path}",
        )
        n.build(
            inputs=[config.config_path, dol_elf_path],
            outputs="dol_diff",
            rule="dol_diff",
        )
        n.build(
            outputs="diff",
            rule="phony",
            inputs="dol_diff",
        )
        n.newline()

        n.comment("Apply symbols from linked ELF")
        n.rule(
            name="dol_apply",
            command=f"{dtk} dol apply $in",
            description=f"APPLY {dol_elf_path}",
        )
        n.build(
            inputs=[config.config_path, dol_elf_path],
            outputs="dol_apply",
            rule="dol_apply",
            implicit=[ok_path],
        )
        n.build(
            outputs="apply",
            rule="phony",
            inputs="dol_apply",
        )
        n.newline()

    ###
    # Split DOL
    ###
    n.comment("Split DOL into relocatable objects")
    n.rule(
        name="split",
        command=f"{dtk} dol split $in $out_dir",
        description="SPLIT $in",
        depfile="$out_dir/dep",
        deps="gcc",
    )
    n.build(
        inputs=config.config_path,
        outputs=build_config_path,
        rule="split",
        implicit=dtk,
        variables={"out_dir": build_path},
    )
    n.newline()

    ###
    # Regenerate on change
    ###
    n.comment("Reconfigure on change")
    n.rule(
        name="configure",
        command=f"$python {configure_script} $configure_args",
        generator=True,
        description=f"RUN {configure_script}",
    )
    n.build(
        outputs="build.ninja",
        rule="configure",
        implicit=[
            build_config_path,
            configure_script,
            python_lib,
            python_lib_dir / "ninja_syntax.py",
        ],
    )
    n.newline()

    ###
    # Default rule
    ###
    n.comment("Default rule")
    if build_config:
        n.default(progress_path)
    else:
        n.default(build_config_path)

    # Write build.ninja
    with open("build.ninja", "w", encoding="utf-8") as f:
        f.write(out.getvalue())
    out.close()


# Generate objdiff.json
def generate_objdiff_config(
    config: ProjectConfig, build_config: Optional[Dict[str, Any]]
) -> None:
    if not build_config:
        return

    objdiff_config: Dict[str, Any] = {
        "min_version": "0.4.3",
        "custom_make": "ninja",
        "build_target": False,
        "watch_patterns": [
            "*.c",
            "*.cp",
            "*.cpp",
            "*.h",
            "*.hpp",
            "*.inc",
            "*.py",
            "*.yml",
            "*.txt",
            "*.json",
        ],
        "units": [],
    }

    build_path = config.out_path()

    def add_unit(build_obj: Dict[str, Any], module_name: str) -> None:
        if build_obj["autogenerated"]:
            # Skip autogenerated objects
            return

        obj_path, obj_name = build_obj["object"], build_obj["name"]
        base_object = Path(obj_name).with_suffix("")
        unit_config: Dict[str, Any] = {
            "name": Path(module_name) / base_object,
            "target_path": obj_path,
        }

        result = config.find_object(obj_name)
        if not result:
            objdiff_config["units"].append(unit_config)
            return

        lib, obj = result
        src_dir = Path(lib.get("src_dir", config.src_dir))

        unit_src_path = src_dir / str(obj.options["source"])

        if not unit_src_path.exists():
            objdiff_config["units"].append(unit_config)
            return

        cflags = obj.options["cflags"] or lib["cflags"]
        src_obj_path = build_path / "src" / f"{base_object}.o"

        reverse_fn_order = False
        if type(cflags) is list:
            for flag in cflags:
                if not flag.startswith("-inline "):
                    continue
                for value in flag.split(" ")[1].split(","):
                    if value == "deferred":
                        reverse_fn_order = True
                    elif value == "nodeferred":
                        reverse_fn_order = False

        unit_config["base_path"] = src_obj_path
        unit_config["reverse_fn_order"] = reverse_fn_order
        unit_config["complete"] = obj.completed
        objdiff_config["units"].append(unit_config)

    # Add DOL units
    for unit in build_config["units"]:
        add_unit(unit, build_config["name"])

    # Add REL units
    for module in build_config["modules"]:
        for unit in module["units"]:
            add_unit(unit, module["name"])

    # Write objdiff.json
    with open("objdiff.json", "w", encoding="utf-8") as w:
        from .ninja_syntax import serialize_path

        json.dump(objdiff_config, w, indent=4, default=serialize_path)


# Calculate, print and write progress to progress.json
def calculate_progress(config: ProjectConfig) -> None:
    out_path = config.out_path()
    build_config = load_build_config(config, out_path / "config.json")
    if not build_config:
        return

    class ProgressUnit:
        def __init__(self, name: str) -> None:
            self.name: str = name
            self.code_total: int = 0
            self.code_fancy_frac: int = config.progress_code_fancy_frac
            self.code_fancy_item: str = config.progress_code_fancy_item
            self.code_progress: int = 0
            self.data_total: int = 0
            self.data_fancy_frac: int = config.progress_data_fancy_frac
            self.data_fancy_item: str = config.progress_data_fancy_item
            self.data_progress: int = 0
            self.objects_progress: int = 0
            self.objects_total: int = 0
            self.objects: Set[Object] = set()

        def add(self, build_obj: Dict[str, Any]) -> None:
            self.code_total += build_obj["code_size"]
            self.data_total += build_obj["data_size"]

            # Avoid counting the same object in different modules twice
            include_object = build_obj["name"] not in self.objects
            if include_object:
                self.objects.add(build_obj["name"])
                self.objects_total += 1

            if build_obj["autogenerated"]:
                # Skip autogenerated objects
                return

            result = config.find_object(build_obj["name"])
            if not result:
                return

            _, obj = result
            if not obj.completed:
                return

            self.code_progress += build_obj["code_size"]
            self.data_progress += build_obj["data_size"]
            if include_object:
                self.objects_progress += 1

        def code_frac(self) -> float:
            return self.code_progress / self.code_total

        def data_frac(self) -> float:
            return self.data_progress / self.data_total

    # Add DOL units
    all_progress = ProgressUnit("All") if config.progress_all else None
    dol_progress = ProgressUnit("DOL")
    for unit in build_config["units"]:
        if all_progress:
            all_progress.add(unit)
        dol_progress.add(unit)

    # Add REL units
    rels_progress = ProgressUnit("Modules") if config.progress_modules else None
    modules_progress: List[ProgressUnit] = []
    for module in build_config["modules"]:
        progress = ProgressUnit(module["name"])
        modules_progress.append(progress)
        for unit in module["units"]:
            if all_progress:
                all_progress.add(unit)
            if rels_progress:
                rels_progress.add(unit)
            progress.add(unit)

    # Print human-readable progress
    print("Progress:")

    def print_category(unit: Optional[ProgressUnit]) -> None:
        if unit is None:
            return

        code_frac = unit.code_frac()
        data_frac = unit.data_frac()
        print(
            f"  {unit.name}: {code_frac:.2%} code, {data_frac:.2%} data ({unit.objects_progress} / {unit.objects_total} files)"
        )
        print(f"    Code: {unit.code_progress} / {unit.code_total} bytes")
        print(f"    Data: {unit.data_progress} / {unit.data_total} bytes")
        if config.progress_use_fancy:
            code_items = math.floor(code_frac * unit.code_fancy_frac)
            print(
                "\nYou have {} of {} {} and completed {} of {} {}.".format(
                    code_items,
                    unit.code_fancy_frac,
                    unit.code_fancy_item,
                    math.floor(data_frac * unit.data_fancy_frac),
                    unit.data_fancy_frac,
                    unit.data_fancy_item,
                )
            )

            bytes_per_frac = unit.code_total / unit.code_fancy_frac
            bytes_next = math.ceil((code_items + 1) * bytes_per_frac)
            bytes_to_go = bytes_next - unit.code_progress

            print(f"Code bytes to go for next trophy: {bytes_to_go}")

    if all_progress:
        print_category(all_progress)
    print_category(dol_progress)
    module_count = len(build_config["modules"])
    if module_count > 0:
        print_category(rels_progress)
        if config.progress_each_module:
            for progress in modules_progress:
                print_category(progress)

    # Generate and write progress.json
    progress_json: Dict[str, Any] = {}

    def add_category(category: str, unit: ProgressUnit) -> None:
        progress_json[category] = {
            "code": unit.code_progress,
            "code/total": unit.code_total,
            "data": unit.data_progress,
            "data/total": unit.data_total,
        }

    if all_progress:
        add_category("all", all_progress)
    add_category("dol", dol_progress)
    if len(build_config["modules"]) > 0:
        if rels_progress:
            add_category("modules", rels_progress)
        if config.progress_each_module:
            for progress in modules_progress:
                add_category(progress.name, progress)
    with open(out_path / "progress.json", "w", encoding="utf-8") as w:
        json.dump(progress_json, w, indent=4)
