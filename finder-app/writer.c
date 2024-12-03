#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    // Open syslog with LOG_USER facility
    openlog("writer", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_USER);

    // Check if the correct number of arguments is provided
    if (argc != 3) {
        syslog(LOG_ERR, "Error: Two arguments are required: <file path> <text string>");
        fprintf(stderr, "Usage: %s <file path> <text string>\n", argv[0]);
        closelog();
        return 1;
    }

    const char *writefile = argv[1];
    const char *writestr = argv[2];

    // Open the file for writing
    FILE *file = fopen(writefile, "w");
    if (!file) {
        syslog(LOG_ERR, "Error: Could not open file %s for writing: %s", writefile, strerror(errno));
        fprintf(stderr, "Error: Could not open file %s for writing: %s\n", writefile, strerror(errno));
        closelog();
        return 1;
    }

    // Write the string to the file
    if (fprintf(file, "%s", writestr) < 0) {
        syslog(LOG_ERR, "Error: Could not write to file %s: %s", writefile, strerror(errno));
        fprintf(stderr, "Error: Could not write to file %s: %s\n", writefile, strerror(errno));
        fclose(file);
        closelog();
        return 1;
    }

    // Log the successful write operation
    syslog(LOG_DEBUG, "Writing '%s' to '%s'", writestr, writefile);
    fclose(file);

    // Close syslog
    closelog();
    return 0;
}
