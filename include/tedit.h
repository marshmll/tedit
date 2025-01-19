#include <ctype.h>
#include <error.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALLOC_CHUNK_SIZE 512

typedef struct
{
    int scr_height;
    int scr_width;
    int cursor_x;
    int cursor_y;
    char *filestr;
} EditorData;

EditorData init_editor();

char *read_file(const char *filename);

void run_editor(EditorData *wd);

void move_cursor(const int y, const int x, EditorData *wd);

void advance_cursor(EditorData *wd);

void back_cursor(EditorData *wd);