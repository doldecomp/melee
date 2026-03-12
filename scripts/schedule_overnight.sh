#!/bin/bash
# Set up or remove the overnight decomp schedule using launchd (macOS).
#
# Usage:
#   ./scripts/schedule_overnight.sh install   # Schedule for 2 AM daily
#   ./scripts/schedule_overnight.sh remove    # Remove schedule
#   ./scripts/schedule_overnight.sh status    # Check if scheduled
#   ./scripts/schedule_overnight.sh run       # Run immediately (foreground)

set -euo pipefail

REPO_ROOT="$(cd "$(dirname "$0")/.." && pwd)"
LABEL="com.melee.decomp-overnight"
PLIST="$HOME/Library/LaunchAgents/$LABEL.plist"
SCRIPT="$REPO_ROOT/scripts/decomp_overnight.sh"

case "${1:-help}" in
    install)
        # Default: 2 AM, scan all files, attempt up to 10 functions
        HOUR=${HOUR:-2}
        cat > "$PLIST" <<EOF
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
    <key>Label</key>
    <string>$LABEL</string>
    <key>ProgramArguments</key>
    <array>
        <string>/bin/bash</string>
        <string>$SCRIPT</string>
    </array>
    <key>WorkingDirectory</key>
    <string>$REPO_ROOT</string>
    <key>StartCalendarInterval</key>
    <dict>
        <key>Hour</key>
        <integer>$HOUR</integer>
        <key>Minute</key>
        <integer>0</integer>
    </dict>
    <key>EnvironmentVariables</key>
    <dict>
        <key>PATH</key>
        <string>/usr/local/bin:/usr/bin:/bin:/opt/homebrew/bin:$HOME/.local/bin:$HOME/miniconda3/bin</string>
        <key>HOME</key>
        <string>$HOME</string>
        <key>SCAN_MODE</key>
        <string>all</string>
        <key>MAX_FUNCTIONS</key>
        <string>10</string>
        <key>MAX_SIZE</key>
        <string>400</string>
        <key>CONTINUOUS</key>
        <string>true</string>
        <key>CUTOFF_HOUR</key>
        <string>8</string>
    </dict>
    <key>StandardOutPath</key>
    <string>$REPO_ROOT/scripts/logs/launchd_stdout.log</string>
    <key>StandardErrorPath</key>
    <string>$REPO_ROOT/scripts/logs/launchd_stderr.log</string>
</dict>
</plist>
EOF
        launchctl load "$PLIST"
        echo "Scheduled overnight decomp at ${HOUR}:00 AM daily"
        echo "Plist: $PLIST"
        echo "To change time: HOUR=3 $0 install"
        ;;

    remove)
        if [ -f "$PLIST" ]; then
            launchctl unload "$PLIST" 2>/dev/null || true
            rm "$PLIST"
            echo "Removed overnight schedule"
        else
            echo "Not currently scheduled"
        fi
        ;;

    status)
        if launchctl list | grep -q "$LABEL"; then
            echo "Active: overnight decomp is scheduled"
            echo "Plist: $PLIST"
            launchctl list "$LABEL" 2>/dev/null || true
        else
            echo "Not scheduled"
        fi
        ;;

    run)
        echo "Running overnight decomp now (foreground)..."
        export CONTINUOUS=${CONTINUOUS:-false}
        export CUTOFF_HOUR=${CUTOFF_HOUR:-8}
        exec "$SCRIPT"
        ;;

    *)
        echo "Usage: $0 {install|remove|status|run}"
        echo ""
        echo "Environment variables:"
        echo "  HOUR=2          Hour to run (24h, default: 2)"
        echo "  MAX_FUNCTIONS=10 Max functions per run"
        echo "  MAX_SIZE=400     Max function size in bytes"
        echo "  MAX_BUDGET=5.00  Max API spend per function"
        echo "  SCAN_MODE=all    Scan all files (default: ftCo_Attack100.c only)"
        echo "  CONTINUOUS=true  Loop until cutoff hour (default: false)"
        echo "  CUTOFF_HOUR=8    Stop after this hour, 24h (default: 8)"
        ;;
esac
