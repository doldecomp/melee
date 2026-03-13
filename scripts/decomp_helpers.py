#!/usr/bin/env python3
"""Helper subcommands for decomp_overnight.sh.

Extracts inline python into testable, debuggable functions.

Usage:
    python3 scripts/decomp_helpers.py <subcommand> [args...]

Subcommands:
    ninja-progress              Read ninja stdout, show progress bar
    stream-monitor <log> <pid>  Poll stream JSON, print live summaries
    parse-result <log>          Parse stream JSON result event
    token-usage <log>           Sum token usage from stream JSON
    extract-log <stream> <out>  Extract readable log from stream JSON
    filter-stubs                Filter stubs and pick next target (reads JSON from stdin)
    extract-asm <file> <func>   Extract function assembly from .s file
    cutoff-epoch <hour>         Print cutoff epoch timestamp
    progress-save <file> <func> <status>  Append to progress JSON
    progress-check <file> <func>          Check if function already tried
    parse-rate-limit <log> <backoff>      Parse rate limit reset time
"""

import json
import os
import re
import signal
import sys
import time
from datetime import datetime, timedelta
from pathlib import Path


def cmd_ninja_progress():
    """Read ninja output from stdin, display progress bar."""
    signal.signal(signal.SIGINT, lambda *a: sys.exit(0))
    signal.signal(signal.SIGTERM, lambda *a: sys.exit(0))
    for line in sys.stdin:
        m = re.match(r"\[(\d+)/(\d+)\]", line)
        if m:
            cur, total = int(m.group(1)), int(m.group(2))
            pct = cur * 100 // total
            filled = pct * 30 // 100
            bar = "\u2588" * filled + "\u2591" * (30 - filled)
            print(f"\r  [{bar}] {cur}/{total} ({pct}%)", end="", flush=True)
    print()


def cmd_stream_monitor(log_file, pid_str):
    """Poll stream JSON log, print live summaries, exit when PID dies."""
    signal.signal(signal.SIGINT, lambda *a: sys.exit(0))
    signal.signal(signal.SIGTERM, lambda *a: sys.exit(0))
    pid = int(pid_str)
    pos = 0
    while True:
        try:
            if os.path.exists(log_file):
                with open(log_file) as f:
                    f.seek(pos)
                    for line in f:
                        try:
                            d = json.loads(line)
                            t = d.get("type", "")
                            if t == "assistant":
                                for c in d.get("message", {}).get("content", []):
                                    if c.get("type") == "text" and c["text"].strip():
                                        print(
                                            f"  [claude] {c['text'][:120]}",
                                            flush=True,
                                        )
                                    elif c.get("type") == "tool_use":
                                        inp = c.get("input", {})
                                        name = c["name"]
                                        desc = (
                                            inp.get("description", "")
                                            or inp.get("pattern", "")
                                            or inp.get("file_path", "")
                                            or ""
                                        )
                                        print(
                                            f"  [{name}] {desc[:100]}", flush=True
                                        )
                            elif t == "result":
                                s = d.get("subtype", "")
                                print(f"  [result] {s}", flush=True)
                        except (json.JSONDecodeError, KeyError):
                            pass
                    pos = f.tell()
            os.kill(pid, 0)
            time.sleep(0.5)
        except ProcessLookupError:
            break
        except OSError:
            break


def cmd_parse_result(log_file):
    """Parse stream JSON for the result event. Prints structured output.

    Output format:
        status=success
        status=failure best=XX.X
        status=error

    Uses the `type: "result"` event's `subtype` and `result` fields,
    NOT grep-based text matching on conversational output.
    """
    result_event = None
    try:
        for line in open(log_file):
            try:
                d = json.loads(line)
                if d.get("type") == "result":
                    result_event = d
            except (json.JSONDecodeError, KeyError):
                pass
    except FileNotFoundError:
        print("status=error")
        sys.exit(1)

    if result_event is None:
        print("status=error")
        sys.exit(1)

    subtype = result_event.get("subtype", "")
    result_text = result_event.get("result", "")
    is_error = result_event.get("is_error", False)

    if is_error or subtype == "error":
        print("status=error")
        sys.exit(0)

    # Check the result text for SUCCESS/FAILURE markers
    # The result field contains the last assistant message text
    if re.search(r"\bSUCCESS\b", result_text):
        print("status=success")
    elif re.search(r"\bFAILURE\b", result_text):
        best = "?"
        m = re.search(r"best=([0-9.]+)", result_text)
        if m:
            best = m.group(1)
        print(f"status=failure best={best}")
    else:
        # Subtype from the result event itself
        if subtype == "success":
            print("status=success")
        else:
            print(f"status=failure best=?")


def cmd_token_usage(log_file):
    """Sum token usage across all assistant messages in stream JSON."""
    input_t = output_t = cache_create = cache_read = 0
    try:
        for line in open(log_file):
            try:
                d = json.loads(line)
                if d.get("type") == "assistant":
                    u = d.get("message", {}).get("usage", {})
                    input_t += u.get("input_tokens", 0)
                    output_t += u.get("output_tokens", 0)
                    cache_create += u.get("cache_creation_input_tokens", 0)
                    cache_read += u.get("cache_read_input_tokens", 0)
            except (json.JSONDecodeError, KeyError):
                pass
    except FileNotFoundError:
        print("tokens=unknown")
        return

    total = input_t + output_t + cache_create + cache_read

    def fmt(n):
        return f"{n / 1000:.1f}k" if n >= 1000 else str(n)

    print(
        f"total={fmt(total)} in={fmt(input_t)} out={fmt(output_t)} "
        f"cache_create={fmt(cache_create)} cache_read={fmt(cache_read)}"
    )


def cmd_extract_log(stream_log, output_log):
    """Extract readable log from stream JSON."""
    try:
        with open(output_log, "w") as out:
            for line in open(stream_log):
                try:
                    d = json.loads(line)
                    if d.get("type") == "assistant":
                        for c in d.get("message", {}).get("content", []):
                            if c.get("type") == "text":
                                out.write(c["text"] + "\n")
                            elif c.get("type") == "tool_use":
                                v = list(c["input"].values())
                                out.write(
                                    f">> {c['name']}({str(v[0])[:80] if v else ''})\n"
                                )
                except (json.JSONDecodeError, KeyError):
                    pass
    except FileNotFoundError:
        pass


def cmd_filter_stubs(excluded_json, branch_funcs_str, progress_file):
    """Filter stubs from stdin JSON, remove excluded/tried/branched, pick smallest.

    Reads stubs JSON array from stdin.
    Prints JSON array with at most 1 target.
    """
    stubs = json.load(sys.stdin)
    excluded = set(x.lower() for x in json.loads(excluded_json))

    progress = []
    if os.path.exists(progress_file) and os.path.getsize(progress_file) > 0:
        with open(progress_file) as f:
            progress = json.load(f)
    already_tried = set(e["name"] for e in progress)

    branch_funcs = set(
        line for line in branch_funcs_str.strip().splitlines() if line
    )

    targets = [
        s
        for s in stubs
        if s["name"].lower() not in excluded
        and s["name"] not in already_tried
        and s["name"] not in branch_funcs
        and s["size"] > 0
    ]
    targets.sort(key=lambda s: s["size"])
    targets = targets[:1]
    print(json.dumps(targets))


def cmd_extract_asm(asm_file, func_name):
    """Extract a function's assembly from a .s file."""
    try:
        text = Path(asm_file).read_text()
    except FileNotFoundError:
        print("(asm file not found)")
        return

    # Try .fn/.endfn format first
    pattern = rf"(\.fn {re.escape(func_name)}.*?\.endfn {re.escape(func_name)})"
    m = re.search(pattern, text, re.DOTALL)
    if m:
        print(m.group(1))
        return

    # Fallback: glabel to next glabel
    pattern = rf"(glabel {re.escape(func_name)}\b.*?)(?=\nglabel |\Z)"
    m = re.search(pattern, text, re.DOTALL)
    if m:
        print(m.group(1))
        return

    print("(function not found in asm)")


def cmd_cutoff_epoch(hour_str):
    """Print cutoff epoch timestamp for given hour (handles midnight wrap)."""
    hour = int(hour_str)
    now = datetime.now()
    cutoff = now.replace(hour=hour, minute=0, second=0, microsecond=0)
    if cutoff <= now:
        cutoff += timedelta(days=1)
    print(int(cutoff.timestamp()))


def cmd_progress_save(progress_file, func_name, status):
    """Append an entry to the progress JSON file."""
    data = []
    if os.path.exists(progress_file):
        with open(progress_file) as f:
            data = json.load(f)
    data.append(
        {"name": func_name, "status": status, "time": time.strftime("%H:%M:%S")}
    )
    with open(progress_file, "w") as f:
        json.dump(data, f, indent=2)


def cmd_progress_check(progress_file, func_name):
    """Exit 0 if function was already tried (success or failure), else exit 1."""
    if not os.path.exists(progress_file):
        sys.exit(1)
    with open(progress_file) as f:
        entries = json.load(f)
    if any(
        e["name"] == func_name and e["status"] in ("success", "failure")
        for e in entries
    ):
        sys.exit(0)
    sys.exit(1)


def cmd_parse_rate_limit(log_file, backoff_str):
    """Parse rate limit reset time from log. Prints seconds to wait."""
    backoff = int(backoff_str)
    try:
        text = Path(log_file).read_text()
    except FileNotFoundError:
        print(backoff)
        return

    m = re.search(r"resets (\d+)(am|pm)", text, re.I)
    if m:
        hour = int(m.group(1))
        if m.group(2).lower() == "pm" and hour != 12:
            hour += 12
        elif m.group(2).lower() == "am" and hour == 12:
            hour = 0
        now = datetime.now()
        reset = now.replace(hour=hour, minute=1, second=0, microsecond=0)
        if reset <= now:
            reset += timedelta(days=1)
        wait = int((reset - now).total_seconds())
        print(max(60, min(wait, 7200)))
    else:
        print(backoff)


SUBCOMMANDS = {
    "ninja-progress": (cmd_ninja_progress, 0),
    "stream-monitor": (cmd_stream_monitor, 2),
    "parse-result": (cmd_parse_result, 1),
    "token-usage": (cmd_token_usage, 1),
    "extract-log": (cmd_extract_log, 2),
    "filter-stubs": (cmd_filter_stubs, 3),
    "extract-asm": (cmd_extract_asm, 2),
    "cutoff-epoch": (cmd_cutoff_epoch, 1),
    "progress-save": (cmd_progress_save, 3),
    "progress-check": (cmd_progress_check, 2),
    "parse-rate-limit": (cmd_parse_rate_limit, 2),
}


def main():
    if len(sys.argv) < 2 or sys.argv[1] not in SUBCOMMANDS:
        print(f"Usage: {sys.argv[0]} <subcommand> [args...]", file=sys.stderr)
        print(f"Subcommands: {', '.join(SUBCOMMANDS)}", file=sys.stderr)
        sys.exit(1)

    cmd_name = sys.argv[1]
    func, nargs = SUBCOMMANDS[cmd_name]
    args = sys.argv[2:]

    if len(args) < nargs:
        print(f"Error: {cmd_name} requires {nargs} arguments, got {len(args)}", file=sys.stderr)
        sys.exit(1)

    func(*args[:nargs])


if __name__ == "__main__":
    main()
