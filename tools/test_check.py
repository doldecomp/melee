#!/usr/bin/env python3
"""Tests for tools/check.py. Run with ``python3 tools/test_check.py``."""
import unittest
from pathlib import Path

import check


class JObjFlagsTest(unittest.TestCase):
    def lines(self, source: str) -> list[int]:
        return [f.line for f in check.scan_jobj_flags(Path("test.c"), source)]

    def test_flags_raw_hidden_literals(self) -> None:
        source = (
            "void f(HSD_JObj* j) {\n"
            "    HSD_JObjSetFlagsAll(j, 0x10);\n"  # 2: hex
            "    HSD_JObjClearFlagsAll(j, 0x10U);\n"  # 3: hex + suffix
            "    HSD_JObjSetFlags(((HSD_JObj**) ud)[7], 16);\n"  # 4: decimal, nested parens
            "    HSD_JObjClearFlags(j, 0x10u);\n"  # 5: lowercase suffix
            "}\n"
        )
        self.assertEqual(self.lines(source), [2, 3, 4, 5])

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


class LiteralRegexTest(unittest.TestCase):
    def test_matches_value_sixteen_forms(self) -> None:
        for tok in ["16", "0x10", "0X10", "0x010", "0x10U", "0x10u", "0x10UL", "020", "0020"]:
            self.assertTrue(check._HIDDEN_LITERAL.fullmatch(tok), tok)

    def test_rejects_other_values(self) -> None:
        for tok in ["0x100", "160", "0x11", "17", "1", "0x1", "JOBJ_HIDDEN"]:
            self.assertIsNone(check._HIDDEN_LITERAL.fullmatch(tok), tok)


if __name__ == "__main__":
    unittest.main()
