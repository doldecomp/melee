---
name: overnight
description: Kill stale processes and sync master with upstream to prepare for the overnight decompilation script.
disable-model-invocation: true
allowed-tools: Bash
---

# Overnight Prep

Kill stale processes from previous runs and sync master with upstream.

## Steps

1. Kill any lingering processes from previous runs:
   ```bash
   pkill -f decomp_overnight 2>/dev/null || true
   pkill -f decomp_helpers 2>/dev/null || true
   pkill -f caffeinate 2>/dev/null || true
   pkill -f ninja 2>/dev/null || true
   pkill -f mwcceppc 2>/dev/null || true
   wineserver -k 2>/dev/null || true
   pkill -9 -f wine-preloader 2>/dev/null || true
   sleep 2
   ```

2. Ensure we're on master and it's clean:
   ```bash
   git checkout master
   git status --short
   ```

3. Sync fork's master with upstream (force-push if diverged from rebase):
   ```bash
   git fetch upstream
   git rebase upstream/master
   git push --force origin master
   ```

4. Print the launch command for the user to run:
   ```
   CONTINUOUS=true SCAN_MODE=all caffeinate ./scripts/decomp_overnight.sh
   ```

If any step fails, stop and report the error — don't blindly continue.
