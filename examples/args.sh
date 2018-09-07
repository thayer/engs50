#!/bin/bash

echo $# arguments to $0

# loop through all the arguments, in four different ways
echo 'for arg in $*'
for arg in $*; do echo "$arg"; done

echo
echo 'for arg in "$*"'
for arg in "$*"; do echo "$arg"; done

echo
echo 'for arg in $@'
for arg in $@; do echo "$arg"; done

echo
echo 'for arg in "$@"'
for arg in "$@"; do echo "$arg"; done

exit 0
