#include <ctype.h>
#include <error.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALLOC_CHUNK_SIZE 1024

typedef struct
{
    int height;
    int width;
    int cursor_x;
    int cursor_y;
} WinData;

WinData init_window();

char *read_file(const char *filename);