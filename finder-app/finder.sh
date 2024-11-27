#!/bin/bash

# Check if the correct number of arguments is provided
if [ $# -ne 2 ]; then
    echo "Error: Two arguments are required: <directory> <search string>"
    exit 1
fi

# Assign arguments to variables
filesdir=$1
searchstr=$2

# Check if the first argument is a valid directory
if [ ! -d "$filesdir" ]; then
    echo "Error: $filesdir is not a valid directory."
    exit 1
fi

# Count the number of files using a subshell using word count (wc).
# wc a Unix/Linux utility used to count lines, words, and characters in a text. 
# The -l flag specifically instructs wc to count the number of lines in a text. 
# So, I piped the output of find, which is a list of files into wc and tell wc
# to give the number of lines.
file_count=$(find "$filesdir" -type f | wc -l)
echo "current file_count is $file_count"

# Count the number of matching lines
# 2>/dev/null is used to redirect any error messages 
# (standard error output) to /dev/null. /dev/null is a special file in Unix/Linux 
# systems that discards all data written to it, effectively acting as a "black hole."
# The  number 2 refers to file descriptor 2, which is the standard error (stderr). 
# In Unix/Linux systems, there are three standard file descriptors:
#   0 - Standard Input (stdin)
#   1 - Standard Output (stdout)
#   2 - Standard Error (stderr)
# Source: https://linuxhint.com/what_is_dev_null/
match_count=$(grep -r "$searchstr" "$filesdir"| wc -l)

# Print the result
echo "The number of files are $file_count and the number of matching lines are $match_count"

exit 0
