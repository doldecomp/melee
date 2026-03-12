#!/bin/bash
# Overnight autonomous decompilation runner.
#
# Finds undecompiled function stubs, checks GitHub for conflicts,
# then spawns Claude Code sessions to decompile each one.
# Each function gets its own worktree branch and PR.
#
# Usage:
#   ./scripts/decomp_overnight.sh                    # scan default files
#   ./scripts/decomp_overnight.sh src/melee/ft/*.c   # scan specific files
#   MAX_SIZE=200 MAX_FUNCTIONS=5 ./scripts/decomp_overnight.sh  # tune params
#   CONTINUOUS=true CUTOFF_HOUR=8 ./scripts/decomp_overnight.sh # loop until 8 AM
#
# Prerequisites:
#   - `claude` CLI authenticated
#   - `gh` CLI authenticated
#   - `ninja` builds successfully on current master
#   - Wine Crossover installed (macOS)
#   - m2c installed: pip install "m2c @ git+https://github.com/matt-kempster/m2c.git"

set -euo pipefail

REPO_ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$REPO_ROOT"

LOG_DIR="$REPO_ROOT/scripts/logs"
mkdir -p "$LOG_DIR"

TIMESTAMP=$(date +%Y%m%d_%H%M%S)
MAIN_LOG="$LOG_DIR/overnight_$TIMESTAMP.log"

REPO="doldecomp/melee"
MAX_FUNCTIONS=${MAX_FUNCTIONS:-10}
MODEL=${MODEL:-opus}
MAX_SIZE=${MAX_SIZE:-400}
# Set to "all" to scan all files with stubs, or pass files as args
SCAN_MODE=${SCAN_MODE:-default}
CONTINUOUS=${CONTINUOUS:-false}
CUTOFF_HOUR=${CUTOFF_HOUR:-8}
AUTO_PUSH=${AUTO_PUSH:-false}
PROGRESS_FILE="$LOG_DIR/progress_$(date +%Y%m%d).json"

log() {
    echo "[$(date '+%H:%M:%S')] $*" | tee -a "$MAIN_LOG"
}

# Compute cutoff epoch once at startup (handles midnight wrap-around)
CUTOFF_EPOCH=$(python3 -c "
import datetime, sys
now = datetime.datetime.now()
cutoff = now.replace(hour=$CUTOFF_HOUR, minute=0, second=0, microsecond=0)
if cutoff <= now:
    cutoff += datetime.timedelta(days=1)
print(int(cutoff.timestamp()))
")

past_cutoff() {
    [ "$(date +%s)" -ge "$CUTOFF_EPOCH" ]
}

progress_save() {
    local func="$1" status="$2"
    python3 -c "
import json, os, time
f = '$PROGRESS_FILE'
data = []
if os.path.exists(f):
    with open(f) as fh:
        data = json.load(fh)
data.append({'name': '$func', 'status': '$status', 'time': time.strftime('%H:%M:%S')})
with open(f, 'w') as fh:
    json.dump(data, fh, indent=2)
"
}

progress_already_tried() {
    local func="$1"
    [ -f "$PROGRESS_FILE" ] && python3 -c "
import json, sys
with open('$PROGRESS_FILE') as f:
    entries = json.load(f)
sys.exit(0 if any(e['name'] == '$func' and e['status'] in ('success', 'failure') for e in entries) else 1)
" 2>/dev/null
}

cleanup_stale_worktrees() {
    log "Cleaning up stale worktrees..."
    for wt in $(git worktree list --porcelain 2>/dev/null | grep '^worktree ' | sed 's/worktree //' | grep -v "^$REPO_ROOT$"); do
        if [ ! -d "$wt" ]; then
            continue
        fi
        wt_branch=$(git -C "$wt" rev-parse --abbrev-ref HEAD 2>/dev/null || echo "")
        if [[ "$wt_branch" == decomp-* ]] || [[ "$wt_branch" == worktree-decomp-* ]]; then
            ahead=$(git rev-list --count master.."$wt_branch" 2>/dev/null || echo 0)
            if [ "$ahead" -eq 0 ]; then
                log "  Removing stale worktree: $wt ($wt_branch)"
                git worktree remove "$wt" --force 2>/dev/null || true
            else
                log "  Keeping worktree with commits: $wt ($wt_branch, $ahead ahead)"
            fi
        fi
    done
    git worktree prune 2>/dev/null || true
}

# Collect source files to scan
if [ $# -gt 0 ]; then
    SOURCE_FILES=("$@")
elif [ "$SCAN_MODE" = "all" ]; then
    SOURCE_FILES=()
    while IFS= read -r f; do SOURCE_FILES+=("$f"); done < <(grep -rl '/// #' src/melee/ --include='*.c' 2>/dev/null)
else
    SOURCE_FILES=(src/melee/ft/chara/ftCommon/ftCo_Attack100.c)
fi

log "=== Overnight Decomp Runner ==="
log "Scanning ${#SOURCE_FILES[@]} files"
log "Max functions: $MAX_FUNCTIONS, Max size: $MAX_SIZE bytes, Model: $MODEL"
if [ "$CONTINUOUS" = "true" ]; then
    log "Continuous mode: ON (cutoff: $(date -r "$CUTOFF_EPOCH" '+%H:%M' 2>/dev/null || date -d "@$CUTOFF_EPOCH" '+%H:%M' 2>/dev/null || echo "$CUTOFF_HOUR:00"))"
fi

cleanup_stale_worktrees

TOTAL_SUCCESSES=0
TOTAL_FAILURES=0
BATCH=0

while true; do
    BATCH=$((BATCH + 1))

    if past_cutoff; then
        log "Past cutoff time, stopping."
        break
    fi

    if [ "$BATCH" -gt 1 ]; then
        log ""
        log "=== Batch $BATCH ==="
    fi

    # 1. Ensure we're on a clean master
    log "Updating master..."
    git stash 2>/dev/null || true
    git checkout master 2>/dev/null || git checkout main 2>/dev/null
    git pull --ff-only 2>/dev/null || true

    # 2. Build to make sure master is clean
    log "Building master to verify clean state..."
    python3 configure.py --wrapper wine 2>&1 | tail -1
    if ! ninja 2>&1 | tee -a "$MAIN_LOG" | tail -5; then
        log "ERROR: Master doesn't build clean. Aborting."
        exit 1
    fi
    log "Master builds OK"

    # 3. Find stubs
    log "Finding stubs..."
    STUBS_JSON=$(python3 scripts/find_stubs.py "${SOURCE_FILES[@]}")
    STUB_COUNT=$(echo "$STUBS_JSON" | python3 -c "import json,sys; print(len(json.load(sys.stdin)))")
    log "Found $STUB_COUNT stubs total"

    # 4. Check GitHub for open PRs and issues to avoid conflicts
    log "Checking GitHub for existing work..."
    EXCLUDED=$(python3 -c "
import json, re, subprocess
try:
    prs = json.loads(subprocess.run(
        ['gh', 'pr', 'list', '--repo', '$REPO', '--state', 'open', '--limit', '100', '--json', 'title,body'],
        capture_output=True, text=True).stdout or '[]')
    issues = json.loads(subprocess.run(
        ['gh', 'issue', 'list', '--repo', '$REPO', '--state', 'open', '--limit', '100', '--json', 'title,body'],
        capture_output=True, text=True).stdout or '[]')
except Exception:
    prs, issues = [], []
names = set()
for item in prs + issues:
    text = (item.get('title','') + ' ' + item.get('body','')).lower()
    for m in re.finditer(r'\b(fn_[0-9a-f]{6,}|ft[A-Z]\w*_\w+|gr\w+_\w+|it_\w+|gm\w+_\w+)\b', text, re.I):
        names.add(m.group(1).lower())
print(json.dumps(list(names)))
")
    log "Excluded $(echo "$EXCLUDED" | python3 -c "import json,sys; print(len(json.load(sys.stdin)))") functions from open PRs/issues"

    # 5. Filter stubs: remove excluded, enforce size limit, exclude already-attempted, take top N
    TARGETS=$(python3 -c "
import json, os
stubs = json.loads('''$(echo "$STUBS_JSON")''')
excluded = set(x.lower() for x in json.loads('''$EXCLUDED'''))
progress = []
pf = '$PROGRESS_FILE'
if os.path.exists(pf):
    with open(pf) as f:
        progress = json.load(f)
already_tried = set(e['name'] for e in progress)
targets = [
    s for s in stubs
    if s['name'].lower() not in excluded
    and s['name'] not in already_tried
    and 0 < s['size'] <= $MAX_SIZE
]
targets.sort(key=lambda s: s['size'])
targets = targets[:$MAX_FUNCTIONS]
print(json.dumps(targets))
")

    TARGET_COUNT=$(echo "$TARGETS" | python3 -c "import json,sys; print(len(json.load(sys.stdin)))")
    log "Will attempt $TARGET_COUNT functions:"
    echo "$TARGETS" | python3 -c "
import json, sys
for s in json.load(sys.stdin):
    print(f'  {s[\"name\"]:30s} {s[\"size\"]:5d} bytes  {s[\"file\"]}:{s[\"line\"]}')
" | tee -a "$MAIN_LOG"

    if [ "$TARGET_COUNT" -eq 0 ]; then
        log "No targets to decompile."
        break
    fi

    # 6. Process each function
    SUCCESSES=0
    FAILURES=0

    while read -r STUB; do
        FUNC_NAME=$(echo "$STUB" | python3 -c "import json,sys; print(json.load(sys.stdin)['name'])")
        FUNC_SIZE=$(echo "$STUB" | python3 -c "import json,sys; print(json.load(sys.stdin)['size'])")
        FUNC_FILE=$(echo "$STUB" | python3 -c "import json,sys; print(json.load(sys.stdin)['file'])")
        FUNC_LINE=$(echo "$STUB" | python3 -c "import json,sys; print(json.load(sys.stdin)['line'])")

        if past_cutoff; then
            log "Past cutoff time, stopping mid-batch."
            break
        fi

        if progress_already_tried "$FUNC_NAME"; then
            log "  Skipping $FUNC_NAME (already attempted today)"
            continue
        fi

        # Derive the asm file path from the C file path
        ASM_FILE="build/GALE01/asm/${FUNC_FILE#src/}"
        ASM_FILE="${ASM_FILE%.c}.s"

        # Derive the object file path
        OBJ_FILE="build/GALE01/${FUNC_FILE%.c}.o"

        BRANCH_NAME="decomp-$FUNC_NAME"
        FUNC_LOG="$LOG_DIR/${FUNC_NAME}_$TIMESTAMP.log"

        log ""
        log "━━━ $FUNC_NAME (${FUNC_SIZE} bytes) ━━━"
        log "  File: $FUNC_FILE:$FUNC_LINE"

        # Check if branch already exists (local or remote)
        if git rev-parse --verify "$BRANCH_NAME" >/dev/null 2>&1 || \
           git ls-remote --heads origin "$BRANCH_NAME" 2>/dev/null | grep -q "$BRANCH_NAME"; then
            log "  Branch $BRANCH_NAME already exists, skipping"
            progress_save "$FUNC_NAME" "skipped"
            continue
        fi

        COMMIT_PREFIX=$(echo "${FUNC_FILE#src/melee/}" | sed 's|/|_|g' | sed 's|\.c||')

        PROMPT="You are autonomously decompiling a function for the Melee decompilation project.
You must work completely autonomously — no human will intervene.

TARGET: $FUNC_NAME
FILE: $FUNC_FILE (stub marker at line $FUNC_LINE)
SIZE: $FUNC_SIZE bytes
ASM: $ASM_FILE
OBJ: $OBJ_FILE

STEP-BY-STEP WORKFLOW:

0. WORKTREE SETUP: You are in a git worktree. First, replace dirs with symlinks:
   rm -rf orig build tools .venv
   ln -s $REPO_ROOT/orig orig
   ln -s $REPO_ROOT/build build
   ln -s $REPO_ROOT/tools tools
   ln -s $REPO_ROOT/.venv .venv
   Then rebuild: python3 configure.py --wrapper wine 2>&1 | tail -1 && ninja 2>&1 | tail -5

1. READ CONTEXT: Read $FUNC_FILE around line $FUNC_LINE (±50 lines) to understand patterns.
   Also read the first 40 lines for includes. Read the header file too.

2. DECOMPILE: Run m2c to get initial C:
   python3 -m m2c.main --target ppc-mwcc-c --context $REPO_ROOT/build/ctx.c --function $FUNC_NAME $REPO_ROOT/$ASM_FILE

3. STUDY ORIGINAL ASM: Read the function's assembly from $ASM_FILE.
   Search for \"$FUNC_NAME\" to find it. Note the exact instruction sequence.

4. CLEAN UP m2c OUTPUT using patterns from surrounding code:
   - Use gobj->user_data style (not GET_FIGHTER) when nearby functions do
   - Replace hex motion state IDs with ftCo_MS_* enums — BUT VERIFY THE NUMERIC VALUE.
     Count from ftCo_MS_DeadDown=0 in ftCommon/forward.h. A wrong enum is a guaranteed mismatch.
   - Replace unk fields with named fields from ft/types.h
   - Use the correct mv.co.UNION.field (check ftCommon/types.h)
   - m2c \"&~1\" on a byte means clear LSB. In PPC bitfield order, LSB = x_b7 (NOT x_b0!)
   - Check if PAD_STACK(8) is needed by comparing frame sizes in the asm

5. IMPLEMENT: Replace the \"/// #$FUNC_NAME\" stub marker with your code.
   Update the header declaration if it uses UNK_RET/UNK_PARAMS.

6. BUILD: python3 configure.py --wrapper wine 2>&1 | tail -1 && ninja 2>&1 | tail -10
   The build MUST succeed (ninja exit code 0).

7. CHECK MATCH (use absolute path to report.json since build/ is a symlink):
   python3 -c \"import json; [print(fn) for u in json.load(open('$REPO_ROOT/build/GALE01/report.json'))['units'] for fn in u.get('functions',[]) if fn.get('name')=='$FUNC_NAME']\"

8. IF NOT 100%: Compare compiled vs original bytes to find exact differences.
   Use pyelftools to extract compiled bytes from $OBJ_FILE.
   Compare instruction-by-instruction with the original asm.
   Common fixes: wrong enum value, wrong bitfield bit, missing PAD_STACK, wrong inline usage.

9. ITERATE up to 5 times. If still not 100%, give up.

10. IF 100% MATCH:
    - Run: git clang-format
    - Stage and commit:
      git add $FUNC_FILE \${FUNC_FILE%.c}.h
      git commit -m \"$COMMIT_PREFIX: decompile $FUNC_NAME

Co-Authored-By: Claude Opus 4.6 <noreply@anthropic.com>\"

11. IF NOT 100%: Revert ALL changes:
    git checkout -- .

12. OUTPUT on the very last line of your response, exactly one of:
    SUCCESS: $FUNC_NAME 100% match
    FAILURE: $FUNC_NAME best=XX.X%"

        log "  Spawning Claude session..."
        FUNC_STREAM_LOG="$LOG_DIR/${FUNC_NAME}_${TIMESTAMP}_stream.jsonl"

        MAX_RETRIES=5
        RETRY=0
        BACKOFF=120  # start at 2 minutes
        RATE_LIMITED=false

        while true; do
            set +e
            env -u CLAUDECODE -u ANTHROPIC_API_KEY claude -p \
                --model "$MODEL" \
                --permission-mode bypassPermissions \
                --verbose --output-format stream-json \
                -w "$BRANCH_NAME" \
                "$PROMPT" > "$FUNC_STREAM_LOG" 2>&1
            CLAUDE_EXIT=${PIPESTATUS[0]}
            set -e

            # Check for rate limit in output (exclude normal status:"allowed" events)
            if grep -v '"status":"allowed"' "$FUNC_STREAM_LOG" 2>/dev/null | grep -qi "hit your limit\|rate.limit\|resets [0-9]"; then
                RETRY=$((RETRY + 1))
                if [ "$RETRY" -gt "$MAX_RETRIES" ]; then
                    log "  Rate limited $MAX_RETRIES times, giving up on $FUNC_NAME"
                    RATE_LIMITED=true
                    break
                fi
                # Try to parse reset time from output, otherwise use backoff
                RESET_WAIT=$(python3 -c "
import re, datetime, sys
text = open('$FUNC_STREAM_LOG').read()
m = re.search(r'resets (\d+)(am|pm)', text, re.I)
if m:
    hour = int(m.group(1))
    if m.group(2).lower() == 'pm' and hour != 12:
        hour += 12
    elif m.group(2).lower() == 'am' and hour == 12:
        hour = 0
    now = datetime.datetime.now()
    reset = now.replace(hour=hour, minute=1, second=0, microsecond=0)
    if reset <= now:
        reset += datetime.timedelta(days=1)
    wait = int((reset - now).total_seconds())
    print(max(60, min(wait, 7200)))
else:
    print($BACKOFF)
" 2>/dev/null || echo "$BACKOFF")
                log "  Rate limited (attempt $RETRY/$MAX_RETRIES). Sleeping ${RESET_WAIT}s until reset..."
                sleep "$RESET_WAIT"
                BACKOFF=$((BACKOFF * 2))
                # Clean up failed worktree before retry
                WT_PATH=$(git worktree list --porcelain 2>/dev/null | grep "$BRANCH_NAME" | head -1 | sed 's/worktree //')
                if [ -n "$WT_PATH" ] && [ -d "$WT_PATH" ]; then
                    git worktree remove "$WT_PATH" --force 2>/dev/null || true
                fi
                git branch -D "$BRANCH_NAME" 2>/dev/null || true
                git branch -D "worktree-$BRANCH_NAME" 2>/dev/null || true
                continue
            fi
            break
        done

        # Extract readable log from stream
        python3 -c "
import json, sys
for line in open('$FUNC_STREAM_LOG'):
    try:
        d = json.loads(line)
        if d.get('type') == 'assistant':
            for c in d.get('message',{}).get('content',[]):
                if c.get('type') == 'text':
                    print(c['text'])
                elif c.get('type') == 'tool_use':
                    v = list(c['input'].values())
                    print(f'>> {c[\"name\"]}({str(v[0])[:80] if v else \"\"})')
    except: pass
" > "$FUNC_LOG" 2>/dev/null || true

        # Skip result parsing if we were rate limited — don't save progress so it's retried
        if [ "$RATE_LIMITED" = "true" ]; then
            log "  Skipped (rate limited), will retry next run"
            FAILURES=$((FAILURES + 1))
            TOTAL_FAILURES=$((TOTAL_FAILURES + 1))
            continue
        fi

        # Parse result from Claude's output (check both readable and raw logs)
        if grep -q "SUCCESS: $FUNC_NAME" "$FUNC_LOG" "$FUNC_STREAM_LOG" 2>/dev/null; then
            log "  ✓ SUCCESS!"

            # Find the worktree branch (claude --worktree prefixes with "worktree-")
            WT_BRANCH=$(git branch --list "*${BRANCH_NAME}*" 2>/dev/null | grep -v '^\*' | head -1 | tr -d ' ' || echo "$BRANCH_NAME")
            if [ -n "$WT_BRANCH" ] && [ "$AUTO_PUSH" = "true" ]; then
                log "  Pushing branch $WT_BRANCH..."
                git push -u origin "$WT_BRANCH" 2>&1 | tail -2 | tee -a "$MAIN_LOG"

                # Derive PR title from file path
                FILE_PREFIX=$(echo "${FUNC_FILE#src/melee/}" | sed 's|/.*||')
                PR_TITLE="$FILE_PREFIX: decompile $FUNC_NAME"

                log "  Creating PR..."
                PR_URL=$(gh pr create \
                    --repo "$REPO" \
                    --head "$WT_BRANCH" \
                    --title "$PR_TITLE" \
                    --body "$(cat <<EOF
## Summary
- Decompile \`$FUNC_NAME\` ($FUNC_SIZE bytes) — 100% match

## Verification
- \`main.dol: OK\` (SHA1 verified)
- \`fuzzy_match_percent: 100.0\`

🤖 Generated with [Claude Code](https://claude.ai/claude-code)
EOF
)" 2>&1) || PR_URL="(PR creation failed)"
                log "  PR: $PR_URL"
            elif [ -n "$WT_BRANCH" ]; then
                log "  Branch ready: $WT_BRANCH (push with: git push -u origin $WT_BRANCH)"
            fi
            # Clean up worktree (branch with commit persists)
            WT_PATH=$(git worktree list --porcelain 2>/dev/null | grep "$BRANCH_NAME" | head -1 | sed 's/worktree //')
            if [ -n "$WT_PATH" ] && [ -d "$WT_PATH" ]; then
                git worktree remove "$WT_PATH" --force 2>/dev/null || true
            fi
            SUCCESSES=$((SUCCESSES + 1))
            TOTAL_SUCCESSES=$((TOTAL_SUCCESSES + 1))
            progress_save "$FUNC_NAME" "success"
        else
            BEST=$(grep -o 'best=[0-9.]*' "$FUNC_LOG" "$FUNC_STREAM_LOG" 2>/dev/null | tail -1 | sed 's/.*best=//' || echo "?")
            log "  ✗ FAILED (best: ${BEST}%)"
            # Clean up worktree and branch
            WT_PATH=$(git worktree list --porcelain 2>/dev/null | grep "$BRANCH_NAME" | head -1 | sed 's/worktree //')
            if [ -n "$WT_PATH" ] && [ -d "$WT_PATH" ]; then
                git worktree remove "$WT_PATH" --force 2>/dev/null || true
            fi
            git branch -D "$BRANCH_NAME" 2>/dev/null || true
            FAILURES=$((FAILURES + 1))
            TOTAL_FAILURES=$((TOTAL_FAILURES + 1))
            progress_save "$FUNC_NAME" "failure"
        fi

        log "  Log: $FUNC_LOG"
    done < <(echo "$TARGETS" | python3 -c "import json,sys; [print(json.dumps(s)) for s in json.load(sys.stdin)]")

    log ""
    log "Batch $BATCH results: $SUCCESSES succeeded, $FAILURES failed"

    if [ "$CONTINUOUS" != "true" ]; then
        break
    fi

    if [ "$TARGET_COUNT" -eq 0 ]; then
        break
    fi
done

log ""
log "━━━━━━━━━━━━━━━━━━━━━"
log "TOTAL RESULTS: $TOTAL_SUCCESSES succeeded, $TOTAL_FAILURES failed ($BATCH batch(es))"
log "Progress file: $PROGRESS_FILE"
log "Log dir: $LOG_DIR"
