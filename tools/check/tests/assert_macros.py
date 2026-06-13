#!/usr/bin/env python3
"""Tests for the assert-macros check. Run: python3 tools/check/tests/assert_macros.py"""
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[2]))

from check.main import scan_assert_macros  # noqa: E402


class AssertMacrosTest(unittest.TestCase):
    def lines(self, source: str, name: str = "test.c") -> list[int]:
        return [f.line for f in scan_assert_macros(Path(name), source)]

    def test_file_and_own_basename_flagged(self) -> None:
        source = (
            "void f(void* x) {\n"
            '    if (x == NULL) { __assert(__FILE__, 1, "x"); }\n'  # 2: __FILE__
            '    if (x == NULL) { __assert("test.c", 2, "x"); }\n'  # 3: own basename
            '    if (x == NULL) { __assert("other.c", 3, "x"); }\n'  # foreign name
            "}\n"
        )
        self.assertEqual(self.lines(source), [2, 3])

    def test_todo_annotation_exempts(self) -> None:
        source = (
            "void f(void* x) {\n"
            "    /// @todo Convert to @c HSD_ASSERT once a byte-matching form is found.\n"
            '    if (x == NULL) { __assert(__FILE__, 1, "x"); }\n'
            "}\n"
        )
        self.assertEqual(self.lines(source), [])

    def test_macro_definition_ignored(self) -> None:
        source = (
            "#define MY_ASSERT(line, cond)                                     \\\n"
            "    ((cond) ? ((void) 0) : __assert(__FILE__, line, #cond))\n"
        )
        self.assertEqual(self.lines(source), [])

    def test_call_split_across_lines(self) -> None:
        source = (
            "void f(void* x) {\n"
            "    if (x == NULL) {\n"
            "        __assert(__FILE__,\n"  # 3
            '                 12, "x");\n'
            "    }\n"
            "}\n"
        )
        self.assertEqual(self.lines(source), [3])


if __name__ == "__main__":
    unittest.main()
