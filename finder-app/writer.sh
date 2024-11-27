#!/bin/bash

# Check if the correct number of arguments is provided
if [ $# -ne 2 ]; then
    echo "Error: Two arguments are required: <file path> <text string>"
    exit 1
fi

# Assign arguments to variables
writefile=$1
writestr=$2

# Extract the directory path from the provided file path
# i.e., dirname provides the directory where writefile is
# located without the filename.
writedir=$(dirname "$writefile")

# Create the directory if it doesn't exist.
# The option -p (--parents) creates also the parent directories
# if they do not exist.
if ! mkdir -p "$writedir"; then
    echo "Error: Could not create directory $writedir."
    exit 1
fi

# Write the string to the file (overwrite if it exists using
# redirection with >)
if ! echo "$writestr" > "$writefile"; then
    echo "Error: Could not write to file $writefile."
    exit 1
fi

exit 0
