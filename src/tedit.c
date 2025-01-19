#include "tedit.h"

EditorData init_editor()
{
    initscr();
    raw();
    keypad(stdscr, true);
    noecho();

    EditorData wd = (EditorData){0, 0, 0, 0, 0};
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
            move_cursor(wd->cursor_y - 1, wd->cursor_x, wd);

        else if (ch == (char)KEY_DOWN)
            move_cursor(wd->cursor_y + 1, wd->cursor_x, wd);

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
    wd->cursor_x = x;
    wd->cursor_y = y;
}

void advance_cursor(EditorData *wd)
{
    if (inch() == '\n')
    {
        move_cursor(wd->cursor_y + 1, 0, wd);
    }
    else
    {
        move_cursor(wd->cursor_y, wd->cursor_x + 1, wd);
    }
}

void back_cursor(EditorData *wd)
{
    if (wd->cursor_x == 0)
    {
        if (wd->cursor_y == 0)
            return;

        // Move cursor to end of the screen in previous line
        move_cursor(wd->cursor_y - 1, wd->scr_width - 1, wd);

        // Put in the beginning of line
        while ((inch() & A_CHARTEXT) == ' ' && wd->cursor_x > 0)
            move_cursor(wd->cursor_y, wd->cursor_x - 1, wd);
    }
    else
    {
        move_cursor(wd->cursor_y, wd->cursor_x - 1, wd);
    }
}