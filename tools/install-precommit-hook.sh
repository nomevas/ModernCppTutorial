#!/bin/bash -e

cd "$(git rev-parse --show-toplevel)"

if [ ! -f  .git/hooks/pre-commit ]; then
    touch .git/hooks/pre-commit
    chmod +x .git/hooks/pre-commit
fi

echo 'for FILE in $(git diff --cached --name-only | egrep "\.h|\.cpp); do clang-format -dry-run --Werror $FILE; done' >> .git/hooks/pre-commit