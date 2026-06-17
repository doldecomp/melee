#!/usr/bin/env python3
"""Tests for the jobj-flags check. Run: python3 tools/check/tests/jobj_flags.py"""
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[2]))

from check.main import _HIDDEN_LITERAL, fix_jobj_flags, scan_jobj_flags  # noqa: E402


class JObjFlagsTest(unittest.TestCase):
    def lines(self, source: str) -> list[int]:
        return [f.line for f in scan_jobj_flags(Path("test.c"), source)]

    def test_flags_raw_hidden_literals(self) -> None:
        source = (
            "void f(HSD_JObj* j) {\n"
            "    HSD_JObjSetFlagsAll(j, 0x10);\n"  # 2: hex
            "    HSD_JObjClearFlagsAll(j, 0x10U);\n"  # 3: hex + suffix
            "    HSD_JObjSetFlags(((HSD_JObj**) ud)[7], 16);\n"  # 4: decimal, nested parens
            "    HSD_JObjClearFlags(j, 0x10u);\n"  # 5: lowercase suffix
            "    HSD_JObjClearFlagsAll(child, 16U);\n"  # 6: decimal + suffix
            "}\n"
        )
        self.assertEqual(self.lines(source), [2, 3, 4, 5, 6])

    def test_handles_line_breaks(self) -> None:
        # Break between the name and '(' and between the arguments.
        source = (
            "void f(HSD_JObj* j) {\n"
            "    HSD_JObjSetFlagsAll\n"
            "        (j,\n"
            "         0x10);\n"
            "}\n"
        )
        self.assertEqual(self.lines(source), [2])

    def test_reports_line_and_column(self) -> None:
        source = "void f(HSD_JObj* j) {\n    HSD_JObjSetFlagsAll(j, 0x10);\n}\n"
        (finding,) = list(scan_jobj_flags(Path("test.c"), source))
        self.assertEqual((finding.line, finding.column), (2, 5))

    def test_strings_and_comments_are_ignored(self) -> None:
        source = (
            "void f(HSD_JObj* j) {\n"
            '    HSD_JObjSetFlagsAll(foo("(,", j), 0x10);\n'  # 2: string with paren/comma
            "    /* HSD_JObjSetFlagsAll(j, 0x10); */\n"  # comment
            "    // HSD_JObjSetFlagsAll(j, 0x10);\n"  # comment
            "}\n"
        )
        self.assertEqual(self.lines(source), [2])

    def test_non_matches(self) -> None:
        source = (
            "void f(HSD_JObj* j) {\n"
            "    HSD_JObjSetFlagsAll(j, JOBJ_HIDDEN);\n"  # already named
            "    HSD_JObjSetFlagsAll(j, flags);\n"  # variable
            "    HSD_JObjSetFlagsAll(j, 0x10 | JOBJ_PTCL);\n"  # composite mask
            "    HSD_JObjSetFlagsAll(j, 0x100);\n"  # different value
            "    foo(jobjs[16]);\n"  # not a flag call
            "}\n"
        )
        self.assertEqual(self.lines(source), [])

    def test_literal_regex_matches_value_sixteen_forms(self) -> None:
        for tok in [
            "16",
            "0x10",
            "0X10",
            "0x010",
            "0x10U",
            "0x10u",
            "0x10UL",
            "16U",
            "020",
            "0020",
        ]:
            self.assertTrue(_HIDDEN_LITERAL.fullmatch(tok), tok)

    def test_literal_regex_rejects_other_values(self) -> None:
        for tok in ["0x100", "160", "0x11", "17", "1", "0x1", "JOBJ_HIDDEN"]:
            self.assertIsNone(_HIDDEN_LITERAL.fullmatch(tok), tok)


class JObjFlagsFixTest(unittest.TestCase):
    def fix(self, source: str) -> tuple[str, int]:
        return fix_jobj_flags(Path("test.c"), source)

    def test_replaces_all_literal_forms(self) -> None:
        source = (
            "void f(HSD_JObj* j) {\n"
            "    HSD_JObjSetFlagsAll(j, 0x10);\n"
            "    HSD_JObjClearFlagsAll(j, 0x10U);\n"
            "    HSD_JObjSetFlags(((HSD_JObj**) ud)[7], 16);\n"
            "    HSD_JObjClearFlagsAll(child, 16U);\n"
            "}\n"
        )
        fixed, n = self.fix(source)
        self.assertEqual(n, 4)
        self.assertNotIn("0x10", fixed)
        self.assertNotIn(", 16", fixed)
        self.assertEqual(fixed.count("JOBJ_HIDDEN"), 4)

    def test_preserves_surrounding_text_exactly(self) -> None:
        source = "    HSD_JObjSetFlagsAll(data->jobjs[3], 0x10);\n"
        fixed, n = self.fix(source)
        self.assertEqual(
            (fixed, n), ("    HSD_JObjSetFlagsAll(data->jobjs[3], JOBJ_HIDDEN);\n", 1)
        )

    def test_leaves_non_matches_untouched(self) -> None:
        source = (
            "void f(HSD_JObj* j) {\n"
            "    HSD_JObjSetFlagsAll(j, JOBJ_HIDDEN);\n"
            "    HSD_JObjSetFlagsAll(j, 0x10 | JOBJ_PTCL);\n"
            "    HSD_JObjSetFlagsAll(j, 0x100);\n"
            '    HSD_JObjSetFlagsAll(foo("0x10", j), bar);\n'
            "}\n"
        )
        fixed, n = self.fix(source)
        self.assertEqual((fixed, n), (source, 0))

    def test_idempotent(self) -> None:
        source = "    HSD_JObjSetFlagsAll(j, 0x10);\n"
        once, _ = self.fix(source)
        twice, n = self.fix(once)
        self.assertEqual((twice, n), (once, 0))


if __name__ == "__main__":
    unittest.main()
