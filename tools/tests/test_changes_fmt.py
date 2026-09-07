#!/usr/bin/env python3
"""Run with: python -m unittest discover -s tools/tests"""

import json
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest


ROOT = Path(__file__).resolve().parents[2]
SCRIPT = ROOT / "tools" / "changes_fmt.py"


class ChangesFmtTest(unittest.TestCase):
    def test_report_paths(self):
        with tempfile.TemporaryDirectory(prefix="changes fmt ") as directory:
            caller = Path(directory)
            report = caller / "report changes.json"
            report.write_text(
                json.dumps(
                    {
                        "from": {"matched_code_percent": 50.0},
                        "to": {"matched_code_percent": 25.0},
                    }
                ),
                encoding="utf-8",
            )
            cases = [
                (ROOT, report),
                (caller, report),
                (caller, Path(report.name)),
            ]
            for cwd, path in cases:
                with self.subTest(cwd=cwd, path=path):
                    result = subprocess.run(
                        [sys.executable, str(SCRIPT), str(path)],
                        cwd=cwd,
                        capture_output=True,
                        text=True,
                    )
                    self.assertEqual(result.returncode, 0, result.stderr)
                    self.assertIn("Total | matched_code |", result.stdout)
                    self.assertIn("50.00% ->  25.00%", result.stdout)


if __name__ == "__main__":
    unittest.main()
