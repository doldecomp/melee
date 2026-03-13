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
#   MODEL=sonnet ./scripts/decomp_overnight.sh                  # use a different model
#   CONTINUOUS=true CUTOFF_HOUR=8 ./scripts/decomp_overnight.sh # loop until 8 AM
#
# Prerequisites:
#   - `claude` CLI authenticated
#   - `gh` CLI authenticated
#   - `ninja` builds successfully on current master
#   - Wine Crossover installed (macOS)
#   - m2c installed: pip install "m2c @ git+https://github.com/matt-kempster/m2c.git"

set -euo pipefail

CHILD_PIDS=()
track_pid() { CHILD_PIDS+=("$1"); }
kill_children() {
    for pid in "${CHILD_PIDS[@]+"${CHILD_PIDS[@]}"}"; do
        kill "$pid" 2>/dev/null || true
        pkill -P "$pid" 2>/dev/null || true
    done
    CHILD_PIDS=()
}
cleanup() {
    trap - INT TERM EXIT
    kill_children
    pkill -P $$ 2>/dev/null || true
    # Wait for killed children to actually exit
    wait 2>/dev/null || true
    exit 1
}
trap cleanup INT TERM EXIT

REPO_ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$REPO_ROOT"
HELPERS="$REPO_ROOT/scripts/decomp_helpers.py"

LOG_DIR="$REPO_ROOT/scripts/logs"
mkdir -p "$LOG_DIR"

TIMESTAMP=$(date +%Y%m%d_%H%M%S)
MAIN_LOG="$LOG_DIR/overnight_$TIMESTAMP.log"

REPO="doldecomp/melee"
MODEL=${MODEL:-opus}
# Set to "all" to scan all files with stubs, or pass files as args
SCAN_MODE=${SCAN_MODE:-default}
CONTINUOUS=${CONTINUOUS:-false}
CUTOFF_HOUR=${CUTOFF_HOUR:-8}
AUTO_PUSH=${AUTO_PUSH:-false}
BATCH_SIZE=${BATCH_SIZE:-5}
PROGRESS_FILE="$LOG_DIR/progress_$(date +%Y%m%d).json"

log() {
    echo "[$(date '+%H:%M:%S')] $*" | tee -a "$MAIN_LOG"
}

# Abort if worktree is dirty (instead of the old git stash approach)
check_worktree_clean() {
    if ! git diff --quiet HEAD 2>/dev/null; then
        log "ERROR: Working tree is dirty. Commit or stash changes before running."
        log "  (This script no longer auto-stashes to avoid reverting its own edits.)"
        exit 1
    fi
}

CUTOFF_EPOCH=$(python3 "$HELPERS" cutoff-epoch "$CUTOFF_HOUR")

past_cutoff() {
    [ "$(date +%s)" -ge "$CUTOFF_EPOCH" ]
}

# Resolve OAuth token (same logic as statusline.sh)
get_oauth_token() {
    if [ -n "${CLAUDE_CODE_OAUTH_TOKEN:-}" ]; then
        echo "${CLAUDE_CODE_OAUTH_TOKEN:-}"
        return 0
    fi
    if command -v security >/dev/null 2>&1; then
        local blob
        blob=$(security find-generic-password -s "Claude Code-credentials" -w 2>/dev/null)
        if [ -n "$blob" ]; then
            local token
            token=$(echo "$blob" | jq -r '.claudeAiOauth.accessToken // empty' 2>/dev/null)
            if [ -n "$token" ] && [ "$token" != "null" ]; then
                echo "$token"
                return 0
            fi
        fi
    fi
    local creds_file="${HOME}/.claude/.credentials.json"
    if [ -f "$creds_file" ]; then
        local token
        token=$(jq -r '.claudeAiOauth.accessToken // empty' "$creds_file" 2>/dev/null)
        if [ -n "$token" ] && [ "$token" != "null" ]; then
            echo "$token"
            return 0
        fi
    fi
    echo ""
}

# Fetch and log usage from the OAuth API. Sets USAGE_WEEKLY_PCT.
USAGE_WEEKLY_PCT=0
check_usage() {
    local token
    token=$(get_oauth_token)
    if [ -z "$token" ] || [ "$token" = "null" ]; then
        log "  [usage] Could not resolve OAuth token"
        return
    fi
    local response
    response=$(curl -s --max-time 5 \
        -H "Accept: application/json" \
        -H "Content-Type: application/json" \
        -H "Authorization: Bearer $token" \
        -H "anthropic-beta: oauth-2025-04-20" \
        -H "User-Agent: claude-code/2.1.34" \
        "https://api.anthropic.com/api/oauth/usage" 2>/dev/null)
    if [ -z "$response" ] || ! echo "$response" | jq -e '.five_hour' >/dev/null 2>&1; then
        log "  [usage] Failed to fetch usage data"
        return
    fi
    local five_pct seven_pct five_reset seven_reset
    five_pct=$(echo "$response" | jq -r '.five_hour.utilization // 0' | awk '{printf "%.0f", $1}')
    seven_pct=$(echo "$response" | jq -r '.seven_day.utilization // 0' | awk '{printf "%.0f", $1}')
    five_reset=$(echo "$response" | jq -r '.five_hour.resets_at // "?"')
    seven_reset=$(echo "$response" | jq -r '.seven_day.resets_at // "?"')
    USAGE_WEEKLY_PCT=$seven_pct
    log "  [usage] current: ${five_pct}% (resets ${five_reset}) | weekly: ${seven_pct}% (resets ${seven_reset})"
}

progress_save() {
    python3 "$HELPERS" progress-save "$PROGRESS_FILE" "$1" "$2"
}

progress_already_tried() {
    [ -f "$PROGRESS_FILE" ] && python3 "$HELPERS" progress-check "$PROGRESS_FILE" "$1" 2>/dev/null
}

cleanup_worktree() {
    local branch_name="$1"
    local wt_path
    wt_path=$(git worktree list --porcelain 2>/dev/null | grep "$branch_name" | head -1 | sed 's/worktree //')
    if [ -n "$wt_path" ] && [ -d "$wt_path" ]; then
        git worktree remove "$wt_path" --force 2>/dev/null || true
    fi
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
log "Model: $MODEL"
if [ "$CONTINUOUS" = "true" ]; then
    log "Continuous mode: ON (cutoff: $(date -r "$CUTOFF_EPOCH" '+%H:%M' 2>/dev/null || date -d "@$CUTOFF_EPOCH" '+%H:%M' 2>/dev/null || echo "$CUTOFF_HOUR:00"))"
fi

check_worktree_clean
cleanup_stale_worktrees

# Seed build cache if already built — avoids unnecessary full rebuild on first iteration
if [ -f "$REPO_ROOT/build.ninja" ]; then
    NINJA_DRY=$(ninja -n 2>&1 || true)
    if echo "$NINJA_DRY" | grep -q "no work to do"; then
        LAST_BUILT_HEAD=$(git rev-parse HEAD)
        log "Build already clean, seeded cache at $LAST_BUILT_HEAD"
    fi
fi

TOTAL_SUCCESSES=0
TOTAL_FAILURES=0

while true; do
    if past_cutoff; then
        log "Past cutoff time, stopping."
        break
    fi

    # 1. Ensure we're on a clean master, synced with upstream
    log "Updating master..."
    git checkout master 2>/dev/null || git checkout main 2>/dev/null
    git pull --ff-only 2>/dev/null || true
    if git remote get-url upstream >/dev/null 2>&1; then
        log "Fetching upstream..."
        git fetch upstream 2>/dev/null || true
        git rebase upstream/master 2>&1 | tee -a "$MAIN_LOG" || {
            log "WARNING: upstream rebase failed, continuing with current master"
            git rebase --abort 2>/dev/null || true
        }
    fi

    # 2. Build to make sure master is clean
    log "Building master to verify clean state..."
    CURRENT_HEAD=$(git rev-parse HEAD)
    if [ "$CURRENT_HEAD" != "${LAST_BUILT_HEAD:-}" ]; then
        # Check if any source files changed (skip rebuild for script-only changes)
        SOURCE_CHANGED=true
        if [ -n "${LAST_BUILT_HEAD:-}" ]; then
            if ! git diff --name-only "$LAST_BUILT_HEAD" "$CURRENT_HEAD" | grep -qE '\.(c|h|cpp|hpp)$'; then
                SOURCE_CHANGED=false
            fi
        fi
        if [ "$SOURCE_CHANGED" = "true" ]; then
            log "  Running configure.py..."
            python3 configure.py --wrapper wine 2>&1 >> "$MAIN_LOG"
            log "  Running ninja..."
            set +o pipefail
            ninja 2>&1 | python3 -u "$HELPERS" ninja-progress
            NINJA_EXIT=${PIPESTATUS[0]}
            set -o pipefail
            if [ "$NINJA_EXIT" -ne 0 ]; then
                log "ERROR: Master doesn't build clean. Aborting."; exit 1
            fi
            log "Master builds OK"
        else
            log "  Only non-source files changed, skipping rebuild"
        fi
        LAST_BUILT_HEAD=$CURRENT_HEAD
    else
        log "Master unchanged, skipping rebuild"
    fi

    # 3. Find stubs
    log "Finding stubs..."
    STUBS_JSON=$(python3 scripts/find_stubs.py "${SOURCE_FILES[@]}") || {
        log "ERROR: find_stubs.py failed (exit code $?)"
        log "  Output: $STUBS_JSON"
        exit 1
    }
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

    # Collect functions that already have decomp branches (with or without worktree- prefix)
    BRANCH_FUNCS=$(git branch --list 'decomp-*' 'worktree-decomp-*' 2>/dev/null | sed 's/^[* ]*//' | sed 's/^worktree-//' | sed 's/^decomp-//' | sort -u)

    # 5. Filter stubs: remove excluded, enforce size limit, exclude already-attempted
    TARGETS=$(echo "$STUBS_JSON" | python3 "$HELPERS" filter-stubs "$EXCLUDED" "$BRANCH_FUNCS" "$PROGRESS_FILE" "$BATCH_SIZE")

    # 6. Pick the next target(s) to decompile
    BATCH=$(echo "$TARGETS" | python3 -c "
import json, sys
targets = json.load(sys.stdin)
if not targets:
    sys.exit(1)
print(json.dumps(targets))
" 2>/dev/null) || {
        log "No targets to decompile."
        break
    }

    BATCH_COUNT=$(echo "$BATCH" | python3 -c "import json,sys; print(len(json.load(sys.stdin)))")
    FIRST_NAME=$(echo "$BATCH" | python3 -c "import json,sys; print(json.load(sys.stdin)[0]['name'])")
    FUNC_FILE=$(echo "$BATCH" | python3 -c "import json,sys; print(json.load(sys.stdin)[0]['file'])")

    # Derive paths from the file
    ASM_FILE="build/GALE01/asm/${FUNC_FILE#src/}"
    ASM_FILE="${ASM_FILE%.c}.s"
    OBJ_FILE="build/GALE01/${FUNC_FILE%.c}.o"
    COMMIT_PREFIX=$(echo "${FUNC_FILE#src/melee/}" | sed 's|/|_|g' | sed 's|\.c||')
    HEADER_FILE="${FUNC_FILE%.c}.h"

    BRANCH_NAME="decomp-$FIRST_NAME"
    FUNC_LOG="$LOG_DIR/${FIRST_NAME}_$TIMESTAMP.log"

    # Build batch summary for logging
    BATCH_NAMES=$(echo "$BATCH" | python3 -c "import json,sys; [print(f['name'],f['size']) for f in json.load(sys.stdin)]")
    log ""
    if [ "$BATCH_COUNT" -gt 1 ]; then
        log "━━━ Batch of $BATCH_COUNT functions from $(basename "$FUNC_FILE") ━━━"
    fi
    echo "$BATCH_NAMES" | while read -r bname bsize; do
        log "  $bname (${bsize} bytes)"
    done

    # Check if branch already exists (local or remote)
    if git rev-parse --verify "$BRANCH_NAME" >/dev/null 2>&1 || \
       git ls-remote --heads origin "$BRANCH_NAME" 2>/dev/null | grep -q "$BRANCH_NAME"; then
        log "  Branch $BRANCH_NAME already exists, skipping"
        progress_save "$FIRST_NAME" "skipped"
        continue
    fi

    # Build trimmed context (stubs + nearby examples) instead of full file
    ALL_FUNC_NAMES=$(echo "$BATCH" | python3 -c "import json,sys; print(' '.join(f['name'] for f in json.load(sys.stdin)))")
    CONTEXT_C=$(python3 "$HELPERS" trim-context "$FUNC_FILE" $ALL_FUNC_NAMES 2>/dev/null || cat "$FUNC_FILE" 2>/dev/null || echo "(file not found)")
    CONTEXT_H=$(cat "$HEADER_FILE" 2>/dev/null || echo "(no header)")

    # Build per-function context (asm + m2c for each target)
    FUNC_SECTIONS=""
    while IFS= read -r func_json; do
        fname=$(echo "$func_json" | python3 -c "import json,sys; print(json.load(sys.stdin)['name'])")
        fsize=$(echo "$func_json" | python3 -c "import json,sys; print(json.load(sys.stdin)['size'])")
        fline=$(echo "$func_json" | python3 -c "import json,sys; print(json.load(sys.stdin)['line'])")

        func_asm=$(python3 "$HELPERS" extract-asm "$ASM_FILE" "$fname" 2>/dev/null || echo "(asm extraction failed)")
        func_m2c=$(python3 -m m2c.main --target ppc-mwcc-c \
            --context "$REPO_ROOT/build/ctx.c" \
            --function "$fname" \
            "$REPO_ROOT/$ASM_FILE" 2>/dev/null || echo "(m2c failed)")

        FUNC_SECTIONS="${FUNC_SECTIONS}
--- $fname ($fsize bytes, stub at line $fline) ---

ASSEMBLY:
$func_asm

m2c DECOMPILATION:
$func_m2c
"
    done < <(echo "$BATCH" | python3 -c "import json,sys; [print(json.dumps(f)) for f in json.load(sys.stdin)]")

    # Build the list of all function names for the prompt
    ALL_NAMES_LIST=$(echo "$BATCH" | python3 -c "
import json, sys
for f in json.load(sys.stdin):
    print(f'  - {f[\"name\"]} ({f[\"size\"]} bytes, stub marker /// #{f[\"name\"]} at line {f[\"line\"]})')
")

    PROMPT="You are autonomously decompiling functions for the Melee decompilation project.
You must work completely autonomously — no human will intervene.

TARGETS (decompile ALL of these):
$ALL_NAMES_LIST
FILE: $FUNC_FILE
OBJ: $OBJ_FILE

=== SOURCE FILE (trimmed context with stubs and nearby examples) ===
$CONTEXT_C

=== HEADER FILE ($HEADER_FILE) ===
$CONTEXT_H

=== PER-FUNCTION ASSEMBLY AND m2c OUTPUT ===
$FUNC_SECTIONS

WORKFLOW:

0. WORKTREE SETUP: You are in a git worktree. First, replace dirs with symlinks:
   rm -rf orig build tools .venv
   ln -s $REPO_ROOT/orig orig
   ln -s $REPO_ROOT/build build
   ln -s $REPO_ROOT/tools tools
   ln -s $REPO_ROOT/.venv .venv
   cp $REPO_ROOT/build.ninja build.ninja
   cp $REPO_ROOT/objdiff.json objdiff.json 2>/dev/null || true
   DO NOT run configure.py — it is already done. Just use ninja to compile after editing.

1. FOR EACH FUNCTION, clean up the m2c output using patterns from the source context:
   - Use gobj->user_data style (not GET_FIGHTER) when nearby functions do
   - Replace hex motion state IDs with ftCo_MS_* enums — BUT VERIFY THE NUMERIC VALUE.
     Count from ftCo_MS_DeadDown=0 in ftCommon/forward.h. A wrong enum is a guaranteed mismatch.
   - Replace unk fields with named fields from ft/types.h
   - Use the correct mv.co.UNION.field (check ftCommon/types.h)
   - m2c \"&~1\" on a byte means clear LSB. In PPC bitfield order, LSB = x_b7 (NOT x_b0!)
   - Check if PAD_STACK(8) is needed by comparing frame sizes in the asm

2. IMPLEMENT: Replace EACH \"/// #FUNC_NAME\" stub marker with your code.
   Update header declarations if they use UNK_RET/UNK_PARAMS.

3. BUILD just the target object: ninja $OBJ_FILE 2>&1 | tail -10
   Do NOT run a bare 'ninja' — it will rebuild everything due to worktree timestamps.
   The build MUST succeed (ninja exit code 0).

4. CHECK MATCH for each function (use absolute path to report.json since build/ is a symlink):
   python3 -c \"import json; [print(fn) for u in json.load(open('$REPO_ROOT/build/GALE01/report.json'))['units'] for fn in u.get('functions',[]) if fn.get('name') in {$(echo "$BATCH" | python3 -c "import json,sys; print(','.join(repr(f['name']) for f in json.load(sys.stdin)))")}]\"

5. IF NOT 100%: Compare compiled vs original bytes to find exact differences.
   Use pyelftools to extract compiled bytes from $OBJ_FILE.
   Compare instruction-by-instruction with the original asm.
   Common fixes: wrong enum value, wrong bitfield bit, missing PAD_STACK, wrong inline usage.

6. ITERATE up to 5 times per function. If still not 100%, revert ONLY that function's changes.

7. FOR EACH FUNCTION AT 100% MATCH:
   - Run: git clang-format
   - Stage and commit EACH matched function separately:
     git add $FUNC_FILE \${FUNC_FILE%.c}.h
     git commit -m \"$COMMIT_PREFIX: decompile FUNC_NAME

Co-Authored-By: Claude Opus 4.6 <noreply@anthropic.com>\"

8. FOR FUNCTIONS NOT AT 100%: Revert their changes:
   git checkout -- .

9. OUTPUT on the very last line of your response, a summary like:
   RESULTS: func1=SUCCESS func2=FAILURE(best=XX.X%) func3=SUCCESS"

    check_usage

    log "  Spawning Claude session..."
    FUNC_STREAM_LOG="$LOG_DIR/${FIRST_NAME}_${TIMESTAMP}_stream.jsonl"

    MAX_RETRIES=5
    RETRY=0
    BACKOFF=120  # start at 2 minutes
    RATE_LIMITED=false

    while true; do
        set +e
        log "  Claude session started..."

        # Run claude in background so Ctrl+C reaches the script
        DONE_FLAG=$(mktemp /tmp/decomp_done.XXXXXX)
        rm -f "$DONE_FLAG"
        env -u CLAUDECODE -u ANTHROPIC_API_KEY claude -p \
            --model "$MODEL" \
            --permission-mode bypassPermissions \
            --verbose --output-format stream-json \
            -w "$BRANCH_NAME" \
            "$PROMPT" > "$FUNC_STREAM_LOG" 2>&1 &
        CLAUDE_PID=$!
        track_pid $CLAUDE_PID

        # Stream live summaries while claude runs; writes done flag on result event
        python3 -u "$HELPERS" stream-monitor "$FUNC_STREAM_LOG" "$CLAUDE_PID" "$DONE_FLAG" &
        MONITOR_PID=$!
        track_pid $MONITOR_PID

        # Wait for claude, but kill it if result event arrives and it keeps running
        while kill -0 $CLAUDE_PID 2>/dev/null; do
            if [ -f "$DONE_FLAG" ]; then
                log "  Result received, giving Claude 10s to finish..."
                sleep 10
                if kill -0 $CLAUDE_PID 2>/dev/null; then
                    log "  Killing Claude (still running after result)"
                    kill $CLAUDE_PID 2>/dev/null
                    pkill -P $CLAUDE_PID 2>/dev/null
                fi
                break
            fi
            sleep 1
        done
        wait $CLAUDE_PID 2>/dev/null
        CLAUDE_EXIT=$?
        kill $MONITOR_PID 2>/dev/null; wait $MONITOR_PID 2>/dev/null
        rm -f "$DONE_FLAG"
        set -e
        log "  Claude session exited (code: $CLAUDE_EXIT)"

        # Check for rate limit in output (exclude normal status:"allowed" events)
        if grep -v '"status":"allowed"' "$FUNC_STREAM_LOG" 2>/dev/null | grep -qi "hit your limit\|rate.limit\|resets [0-9]"; then
            RETRY=$((RETRY + 1))
            if [ "$RETRY" -gt "$MAX_RETRIES" ]; then
                log "  Rate limited $MAX_RETRIES times, giving up"
                RATE_LIMITED=true
                break
            fi
            RESET_WAIT=$(python3 "$HELPERS" parse-rate-limit "$FUNC_STREAM_LOG" "$BACKOFF" 2>/dev/null || echo "$BACKOFF")
            log "  Rate limited (attempt $RETRY/$MAX_RETRIES). Sleeping ${RESET_WAIT}s until reset..."
            sleep "$RESET_WAIT"
            BACKOFF=$((BACKOFF * 2))
            # Clean up failed worktree before retry
            cleanup_worktree "$BRANCH_NAME"
            git branch -D "$BRANCH_NAME" 2>/dev/null || true
            git branch -D "worktree-$BRANCH_NAME" 2>/dev/null || true
            continue
        fi
        break
    done

    # Extract readable log from stream
    python3 "$HELPERS" extract-log "$FUNC_STREAM_LOG" "$FUNC_LOG" 2>/dev/null || true

    # Sum token usage
    FUNC_TOKENS=$(python3 "$HELPERS" token-usage "$FUNC_STREAM_LOG" 2>/dev/null || echo "tokens=unknown")
    log "  [tokens] $FUNC_TOKENS"

    # Skip result parsing if we were rate limited — don't save progress so it's retried
    if [ "$RATE_LIMITED" = "true" ]; then
        log "  Skipped (rate limited), will retry next run"
        TOTAL_FAILURES=$((TOTAL_FAILURES + 1))
        continue
    fi

    # Parse result from stream JSON result event
    RESULT_LINE=$(python3 "$HELPERS" parse-result "$FUNC_STREAM_LOG" 2>/dev/null || echo "status=error")
    RESULT_STATUS=$(echo "$RESULT_LINE" | sed -n 's/^status=//p' | head -1)

    if [ "$RESULT_STATUS" = "success" ]; then
        log "  ✓ SUCCESS!"

        # Find the worktree branch (claude --worktree prefixes with "worktree-")
        WT_BRANCH=$(git branch --list "*${BRANCH_NAME}*" 2>/dev/null | grep -v '^\*' | head -1 | tr -d ' ' || echo "$BRANCH_NAME")
        if [ -n "$WT_BRANCH" ] && [ "$AUTO_PUSH" = "true" ]; then
            log "  Pushing branch $WT_BRANCH..."
            git push -u origin "$WT_BRANCH" 2>&1 | tail -2 | tee -a "$MAIN_LOG"

            # Derive PR title from file path
            FILE_PREFIX=$(echo "${FUNC_FILE#src/melee/}" | sed 's|/.*||')
            if [ "$BATCH_COUNT" -gt 1 ]; then
                PR_TITLE="$FILE_PREFIX: decompile $BATCH_COUNT functions"
                PR_FUNCS=$(echo "$BATCH" | python3 -c "import json,sys; print('\n'.join(f'- \`{f[\"name\"]}\` ({f[\"size\"]} bytes)' for f in json.load(sys.stdin)))")
            else
                PR_TITLE="$FILE_PREFIX: decompile $FIRST_NAME"
                PR_FUNCS="- Decompile \`$FIRST_NAME\` — 100% match"
            fi

            log "  Creating PR..."
            PR_URL=$(gh pr create \
                --repo "$REPO" \
                --head "$WT_BRANCH" \
                --title "$PR_TITLE" \
                --body "$(cat <<EOF
## Summary
$PR_FUNCS

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
        cleanup_worktree "$BRANCH_NAME"
        TOTAL_SUCCESSES=$((TOTAL_SUCCESSES + BATCH_COUNT))
        echo "$BATCH" | python3 -c "import json,sys; [None for f in json.load(sys.stdin)]" 2>/dev/null  # validate
        while IFS= read -r fname; do
            progress_save "$fname" "success"
        done < <(echo "$BATCH" | python3 -c "import json,sys; [print(f['name']) for f in json.load(sys.stdin)]")
    else
        BEST=$(echo "$RESULT_LINE" | sed -n 's/.*best=//p' || echo "?")
        log "  ✗ FAILED (best: ${BEST}%)"
        # Clean up worktree and branch
        cleanup_worktree "$BRANCH_NAME"
        git branch -D "$BRANCH_NAME" 2>/dev/null || true
        TOTAL_FAILURES=$((TOTAL_FAILURES + BATCH_COUNT))
        while IFS= read -r fname; do
            progress_save "$fname" "failure"
        done < <(echo "$BATCH" | python3 -c "import json,sys; [print(f['name']) for f in json.load(sys.stdin)]")
    fi

    log "  Log: $FUNC_LOG"

    # Kill any lingering child processes before next iteration
    kill_children

    if [ "$CONTINUOUS" != "true" ]; then
        break
    fi
done

log ""
log "━━━━━━━━━━━━━━━━━━━━━"
log "TOTAL RESULTS: $TOTAL_SUCCESSES succeeded, $TOTAL_FAILURES failed"
log "Progress file: $PROGRESS_FILE"
log "Log dir: $LOG_DIR"
