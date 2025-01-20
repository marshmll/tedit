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
    int crsr_x;
    int crsr_y;
    int char_i;
    char *filestr;
} EditorData;

EditorData init_editor();

char *read_file(const char *filename);

void run_editor(EditorData *wd);

void move_cursor(const int y, const int x, EditorData *wd);

void skip_cursor_to_next_line(EditorData *wd);

void skip_cursor_to_prev_line(EditorData *wd);

bool advance_cursor(EditorData *wd);

bool back_cursor(EditorData *wd);

char curr_char(EditorData *wd);