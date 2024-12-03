#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    // Open syslog with LOG_USER facility
    openlog(NULL, 0, LOG_USER);

    // Check if the correct number of arguments is provided
    if (argc != 3) {
        syslog(LOG_ERR, "Error: Two arguments are required: <file path> <text string>");
        fprintf(stderr, "Usage: %s <file path> <text string>\n", argv[0]);
        closelog();
        return 1;
    }

    const char *filename = argv[1];
    const char *writestr = argv[2];

    // Open the file for writing
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        syslog(LOG_ERR, "Error: Could not open file %s for writing: %s", filename, strerror(errno));
        fprintf(stderr, "Error: Could not open file %s for writing: %s\n", filename, strerror(errno));
        closelog();
        return 1;
    }

    // Write the string to the file
    if (fprintf(file, "%s", writestr) < 0) {
        syslog(LOG_ERR, "Value of errno attempting to open file %s: %d\n", filename, errno);
        fprintf(stderr, "Value of errno attempting to open file %s: %d\n", filename, errno);
        perror("perror returned");
        syslog(LOG_ERR, "Error opening file %s: %s\n", filename, strerror(errno));
        fprintf(stderr, "Error opening file %s: %s\n", filename, strerror(errno));
        fclose(file);
        closelog();
        return 1;
    }

    // Log the successful write operation
    syslog(LOG_DEBUG, "Writing '%s' to '%s'", writestr, filename);
    fclose(file);

    // Close syslog
    closelog();
    return 0;
}
