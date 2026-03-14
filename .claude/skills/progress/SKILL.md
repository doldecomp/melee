---
name: progress
description: Show decompilation progress — unpushed branches, matched functions, and overnight script results.
disable-model-invocation: true
allowed-tools: Bash, Read, Grep
---

# Decomp Progress

Show the status of decompiled functions from overnight runs.

## Steps

1. Count matched functions from progress files (the authoritative source):
   ```bash
   echo "=== Today ==="
   if [ -f scripts/logs/progress_$(date +%Y%m%d).json ]; then
       python3 -c "
   import json
   data = json.load(open('scripts/logs/progress_$(date +%Y%m%d).json'))
   successes = [d for d in data if d['status'] == 'success']
   failures = [d for d in data if d['status'] == 'failure']
   print(f'  {len(successes)} functions matched, {len(failures)} failed')
   for s in successes:
       print(f'    ✓ {s[\"name\"]} ({s[\"time\"]})')
   for f in failures:
       print(f'    ✗ {f[\"name\"]} ({f[\"time\"]})')
   "
   else
       echo "  (no progress file for today)"
   fi
   echo ""
   echo "=== All time (from progress files) ==="
   python3 -c "
   import json, glob
   total_s, total_f = 0, 0
   for f in sorted(glob.glob('scripts/logs/progress_*.json')):
       data = json.load(open(f))
       s = sum(1 for d in data if d['status'] == 'success')
       fl = sum(1 for d in data if d['status'] == 'failure')
       day = f.split('progress_')[1].split('.')[0]
       total_s += s
       total_f += fl
       print(f'  {day}: {s} matched, {fl} failed')
   print(f'  TOTAL: {total_s} matched, {total_f} failed')
   "
   ```

2. List unpushed branches with commits:
   ```bash
   for branch in $(git branch --list 'decomp-*' 'worktree-decomp-*' | sed 's/^[* ]*//'); do
       commits=$(git log --oneline master.."$branch" 2>/dev/null | wc -l | tr -d ' ')
       [ "$commits" -eq 0 ] && continue
       pushed=$(git ls-remote --heads origin "$branch" 2>/dev/null | wc -l | tr -d ' ')
       echo "$branch | $commits commits | $([ "$pushed" -gt 0 ] && echo 'pushed' || echo 'NOT PUSHED')"
   done
   ```

3. Summarize the latest overnight log:
   ```bash
   ls -t scripts/logs/overnight_*.log 2>/dev/null | head -1 | xargs grep -E 'SUCCESS|FAILURE|RESULTS:|tokens' 2>/dev/null | tail -20
   ```

4. Present a concise summary to the user:
   - Total functions matched (today + all time)
   - Unpushed branches ready to PR
   - Any failures worth retrying
