#!/usr/bin/bash

# Accepts the following arguments: 
#     the first argument is a full path to a file (including filename) on the filesystem, referred to below as writefile; 
#     the second argument is a text string which will be written within this file, referred to below as writestr
# Exits with value 1 error and print statements if any of the arguments above were not specified
# Creates a new file with name and path writefile with content writestr, overwriting any existing file and creating the path if it doesn’t exist. 
# Exits with value 1 and error print statement if the file could not be created.

set -e
set -u

FILEPATH=""
WRITESTR=""

usage() {
    echo "
    The script \"$0\" allows users to create/overwrite a specified file.
    
    Usage: $0 <path to file> <write string>
    where:
        <path to file> is the path to the file to write
        <write string> is the string to write within the file
    "
}

writer() {
    if ! mkdir -p "$(dirname "$FILEPATH")"; then
        echo "Error: Could not create directory for '$FILEPATH'"
        exit 1
    fi

    if ! echo "$WRITESTR" > "$FILEPATH"; then
        echo "Error: Could not write to file '$FILEPATH'"
        exit 1
    fi
}

main() {
    if [ $# -ne 2 ]; then
        echo "Error: Two parameters required - file path and write string"
        usage
        exit 1
    fi

    FILEPATH=$1
    WRITESTR=$2

    writer
}

main "$@"
