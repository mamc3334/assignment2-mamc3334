// assignment2-mamc3334/finder-app/writer.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>

/**
* This function can be used as an alternative to the “writer.sh” test script created in assignment1 using File IO as described in LSP chapter 2.:
*   1) Accepts the following arguments: 
*        a) a full path to a file (including filename) on the filesystem, referred to below as writefile; 
*        b) a text string which will be written within this file, referred to below as writestr
*   2) Exits with value 1 error and print statements if any of the arguments above were not specified
*   3) Creates a new file with name and path writefile with content writestr, overwriting any existing file and creating the path if it doesn’t exist. 
*   4) Exits with value 1 and error print statement if the file could not be created.
*
*   5) One difference from the write.sh instructions in Assignment 1:  You do not need to make your "writer" utility create directories which do not exist.  You can assume the directory is created by the caller.
*   6) Setup syslog logging for your utility using the LOG_USER facility
*   7) Use the syslog capability to write a message “Writing <string> to <file>” where <string> is the text string written to file (second argument) and <file> is the file created by the script.  This should be written with LOG_DEBUG level.
*   8) Use the syslog capability to log any unexpected errors with LOG_ERR level.
*/

static const char *progname = "writer";

void usage()
{
    fprintf(stdout, "\nThe program \"writer.c\" allows users to create/overwrite a specified file.\n"
                    "However, it does not create any directories that do not already exist.\n"
                    "\nUsage: %s <path to file> <write string>\n"
                    "where:\n"
                    "\t<path to file> is the path to the file to write\n"
                    "\t<write string> is the string to write within the file\n", progname);
}

void writer(const char *filepath, const char *writestr)
{
    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        syslog(LOG_ERR, "Could not create file '%s'", filepath);
        fprintf(stderr, "Error: Could not create file '%s'\n", filepath);
        closelog();
        usage();

        exit(1);
    }
    
    if (fputs(writestr, file) == EOF) {
        syslog(LOG_ERR, "Could not write to file '%s'", filepath);
        fprintf(stderr, "Error: Could not write to file '%s'\n", filepath);
        fclose(file);
        closelog();
        usage();

        exit(1);
    }
    
    syslog(LOG_DEBUG, "Writing %s to %s", writestr, filepath);
    fclose(file);
    closelog();
}

int main(int argc, char *argv[]) {
    openlog(progname, 0, LOG_USER);
    
    if (argc != 3) {
        syslog(LOG_ERR, "Error: Two parameters required - file path and write string");
        fprintf(stderr, "Error: Two parameters required - file path and write string\n");
        closelog();
        usage();
        
        exit(1);
    }
    
    const char *filepath = argv[1];
    const char *writestr = argv[2];
    
    writer(filepath, writestr);
    
    return 0;
}