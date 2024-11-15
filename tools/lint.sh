#!/bin/bash

source "$(dirname "$0")/global.sh"

root=""

while [[ "$#" -gt 0 ]]; do
  case $1 in
    --root) root="$2"; shift; ;;
    *) echo "Unknown parameter passed: $1" ;;
  esac
  shift
done

cd "$root" || exit

COMPILATION_DB=$(find ./build -name "compile_commands.json" -print -quit)

if [ ! -f "$COMPILATION_DB" ]; then
  echo "Error: compile_commands.json not found in ./build!"
  exit 1
fi

cp "$COMPILATION_DB" compile_commands.json

SOURCE_FILES=$(find "$(pwd)" -type f \( -name '*.cpp' -o -name '*.h' -o -name '*.hpp' -o -name '*.c' -o -name '*.cc' \) \
  -not -path './tools/*' \
  -not -path './wm/*' \
  -not -path './ImGuiFileDialog/*' \
  -not -path './.git/*' \
  -not -path './tests/*' \
  -not -path './build/*' \
  -not -path './.github/*' \
  -not -path './editor/include/bindings/*' | xargs)

# shellcheck disable=SC2086
python3 "clang-tidy.py" -p "build" -fix -format -style=file -exclude-header-filter="(tools|wm|ImGuiFileDialog|\.git|tests|build|\.github|editor/include/bindings).*" $SOURCE_FILES

cd "$root" || exit
