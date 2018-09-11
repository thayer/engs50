#!/bin/bash
#
# File: guessprimefunction.sh (variant of guessprime.sh)
# 
# Description: The user tries to guess a prime between 1-100 
# This is not a good program. There is no check on what the
# user enters; it may not be a prime, or might be outside the range.
# Heck - it might not even be a number and might be empty!
# Some defensive programming would check the input.
# 
# Input: The user enters a guess
#
# Output: Status on the guess

# Ask the user to guess, and fill global variable $guess with result.
# usage: askguess low high
#   where [low, high] is the range of numbers in which they should guess.
function askguess() {
    echo -n "Enter a prime between $1-$2: "
    read guess
}

# Program defines a variable called prime and set it to a value.

prime=31

# ask them once
askguess 1 100

while [ $guess != $prime ]; do
    # ask again
    askguess 1 100
done
exit 0
