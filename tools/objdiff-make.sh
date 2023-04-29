#!/usr/bin/env bash

make GENERATE_MAP=1 MAX_ERRORS=1 WIP=1 "-j$(nproc)" WINE=wibo "$@"
