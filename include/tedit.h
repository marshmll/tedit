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
    int trgt_x;
    char *filestr;
} EditorData;

EditorData init_editor();

char *read_file(const char *filename);

void run_editor(EditorData *ed);

void move_cursor(const int y, const int x, EditorData *ed);

void skip_cursor_to_next_line(EditorData *ed);

void skip_cursor_to_prev_line(EditorData *ed);

bool advance_cursor(EditorData *ed);

bool back_cursor(EditorData *ed);

char curr_char(EditorData *ed);