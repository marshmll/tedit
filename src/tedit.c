#include "tedit.h"

WinData init_window()
{
    initscr();
    raw();
    noecho();

    WinData winData = (WinData){0, 0, 0, 0};
    getyx(stdscr, winData.height, winData.height);

    return winData;
}

char *read_file(const char *filename)
{
    FILE *f = fopen(filename, "r");

    if (f == NULL)
        return NULL;

    char *str = (char *)calloc(ALLOC_CHUNK_SIZE, sizeof(char));
    char buf;
    int i = 0;

    while (fread(&buf, sizeof(char), 1, f))
    {
        if (i == sizeof(str) - 1)
            str = realloc(str, sizeof(str) + ALLOC_CHUNK_SIZE);

        str[i++] = buf;
    }

    // Terminate string
    str[i] = '\0';

    fclose(f);

    return str;
}