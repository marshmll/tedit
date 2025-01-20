#include "tedit.h"

EditorData init_editor()
{
    initscr();
    raw();
    keypad(stdscr, true);
    noecho();

    EditorData wd = (EditorData){0, 0, 0, 0, 0, 0};
    getmaxyx(stdscr, wd.scr_height, wd.scr_width);
    move(0, 0);

    return wd;
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

void run_editor(EditorData *wd)
{
    bool running = true;
    char ch;

    printw("%s", wd->filestr);
    move(0, 0);

    while (running)
    {
        ch = getch();

        if (ch == (char)KEY_UP)
            skip_cursor_to_prev_line(wd);

        else if (ch == (char)KEY_DOWN)
            skip_cursor_to_next_line(wd);

        else if (ch == (char)KEY_LEFT)
            back_cursor(wd);

        else if (ch == (char)KEY_RIGHT)
            advance_cursor(wd);

        else if (ch == 'q')
            running = false;

        refresh();
    }
}

void move_cursor(const int y, const int x, EditorData *wd)
{
    move(y, x);
    wd->crsr_x = x;
    wd->crsr_y = y;
}

void skip_cursor_to_next_line(EditorData *wd)
{
    int target_x = wd->crsr_x;
    int target_y = wd->crsr_y + 1;

    while (true)
    {
        advance_cursor(wd);

        if (curr_char(wd) == '\n' && wd->crsr_x < target_x && wd->crsr_y == target_y)
            break;
        else if (wd->crsr_x == target_x)
            break;
    }
}

void skip_cursor_to_prev_line(EditorData *wd)
{
    int target_x = wd->crsr_x;
    int target_y = wd->crsr_y - 1;
    back_cursor(wd);

    while (true)
    {
        back_cursor(wd);

        if (target_y == wd->crsr_y && curr_char(wd) == '\n' && wd->crsr_x < target_x)
            break;

        else if (wd->crsr_x == target_x)
            break;
    }
}

bool advance_cursor(EditorData *wd)
{
    char c = curr_char(wd);
    wd->char_i++;

    if (c == EOF)
    {
        return false;
    }
    else if (c == '\n')
    {
        move_cursor(wd->crsr_y + 1, 0, wd);
        return true;
    }
    else
    {
        move_cursor(wd->crsr_y, wd->crsr_x + 1, wd);
        return false;
    }
}

bool back_cursor(EditorData *wd)
{
    wd->char_i--;
    char c = curr_char(wd);

    if (c == EOF)
    {
        return false;
    }
    else if (c == '\n')
    {
        move_cursor(wd->crsr_y - 1, wd->scr_width - 1, wd);

        while ((inch() & A_CHARTEXT) == ' ' && wd->crsr_x > 0)
            move_cursor(wd->crsr_y, wd->crsr_x - 1, wd);

        return true;
    }
    else
    {
        move_cursor(wd->crsr_y, wd->crsr_x - 1, wd);
        return false;
    }
}

char curr_char(EditorData *wd)
{
    if (wd->char_i >= strlen(wd->filestr) || wd->char_i < 0)
        return EOF;

    return wd->filestr[wd->char_i];
}