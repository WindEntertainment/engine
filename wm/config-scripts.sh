#!/bin/bash

source "$(dirname "$0")/global.sh"

call_dir=$(pwd)
root=""
name=script

while [[ "$#" -gt 0 ]]; do
  case $1 in
    --root) root="$2"; shift ;;
    *) echo "Unknown parameter passed: $1" ;;
  esac
  shift
done

cd "$root" || exit

scripts_folder="$(get_scripts_folder "$root")"

for file in "$scripts_folder"/*.sh; do
  if [ -f "$file" ]; then
    sudo chmod +x "$file"
    echo "Added execute permission to: $file"
  fi
done

cd "$call_dir" || exit
