#!/bin/bash
#
# backup-diff.sh - compare all the .c files in current directory with backup
#
# usage: backup-diff.sh
# (no arguments)
#
# input: none
# output: a line of information for each file, and diffs where they differ
# exit status: non-zero if any differences found, or any missing backups.
#
# David Kotz, March 2017

differs=0

for i in *.c
do
    if [ ! -r "$i.bak" ]
    then
	echo "$i" - no backup 
	differs=1
    else
	if cmp --quiet "$i.bak" "$i" 
	then
	    echo "$i" unchanged
	else
	    echo "$i" differences:
	    diff "$i.bak" "$i" 
	    differs=1
	fi
    fi
    
    echo
done

# exit with non-zero status if we found any differences
exit $differs

