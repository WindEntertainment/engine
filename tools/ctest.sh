#!/bin/bash

source "$(dirname "$0")/global.sh"

with_coverage=false

root=""

while [[ "$#" -gt 0 ]]; do
  case $1 in
    -wc|--with-coverage) with_coverage=true; ;;
    --root) root="$2"; shift; ;;
    *) echo "Unknown parameter passed: $1" ;;
  esac
  shift
done

cd "$root" || exit

wm run cmake-build -t native-tests -bt Debug -wt
ctest

if [[ $with_coverage = true ]]; then
  wm run cmake-build -t coverage -bt Debug -sc
fi

cd "$root" || exit
