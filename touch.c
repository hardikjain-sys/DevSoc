#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s [-c] <filename>\n", argv[0]);
        return 1;
    }

    int notCreate = 0;
    char *filepath = NULL;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-c") == 0) {
            notCreate = 1;
        } else {
            filepath = argv[i];
        }
    }

    if (!filepath) {
        fprintf(stderr, "no file\n");
        return 1;
    }

    int fd;

    if (notCreate) {
        fd = open(filepath, O_WRONLY | O_APPEND);
        if (fd == -1) {
            fprintf(stderr, "File '%s' does not exist, skipping due to -c\n", filepath);
            return 0;
        }
    } else {
        fd = open(filepath, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd == -1) {
            perror("Error opening/creating file");
            return 1;
        }
    }

    if (close(fd) == -1) {
        perror("Error closing file");
        return 1;
    }

    return 0;
}
