#!/bin/bash -e

for FILE in $(git diff --cached --name-only | egrep "\.h|\.cpp"); do clang-format -i $FILE; done