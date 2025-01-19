#include "tedit.h"

int main(int argc, char **argv)
{
    if (argc != 2)
        error(EXIT_FAILURE, 0, "Usage: %s <file>", argv[0]);

    // Make a copy of argv[1] to avoid messing with argv.
    char filename[strlen(argv[1])];
    strcpy(filename, argv[1]);

    char *filestr = read_file(filename);

    if (filestr == NULL)
        error(EXIT_FAILURE, 0, "Could not read file: %s", filename);

    printf("%s", filestr);

    free(filestr);
    return 0;
}