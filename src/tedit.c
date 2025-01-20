#include "tedit.h"

EditorData init_editor()
{
    initscr();
    raw();
    keypad(stdscr, true);
    noecho();

    EditorData ed = (EditorData){0, 0, 0, 0, 0, -1, NULL};
    getmaxyx(stdscr, ed.scr_height, ed.scr_width);
    move(0, 0);

    return ed;
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

void run_editor(EditorData *ed)
{
    bool running = true;
    char ch;

    printw("%s", ed->filestr);
    move(0, 0);

    while (running)
    {
        ch = getch();

        if (ch == (char)KEY_UP)
            skip_cursor_to_prev_line(ed);

        else if (ch == (char)KEY_DOWN)
            skip_cursor_to_next_line(ed);

        else if (ch == (char)KEY_LEFT)
            back_cursor(ed);

        else if (ch == (char)KEY_RIGHT)
            advance_cursor(ed);

        else if (ch == 'q')
            running = false;

        refresh();
    }
}

void move_cursor(const int y, const int x, EditorData *ed)
{
    move(y, x);
    ed->crsr_x = x;
    ed->crsr_y = y;
}

void skip_cursor_to_next_line(EditorData *ed)
{
    if (ed->crsr_y == ed->scr_height)
        return;

    int target_x = ed->trgt_x != (-1) ? ed->trgt_x : ed->crsr_x;
    int target_y = ed->crsr_y + 1;
    bool advancing = advance_cursor(ed);

    while (advancing)
    {
        if (target_y == ed->crsr_y && curr_char(ed) == '\n' && ed->crsr_x < target_x)
        {
            ed->trgt_x = target_x;
            break;
        }
        else if (ed->crsr_x == target_x)
        {
            ed->trgt_x = -1;
            break;
        }

        advancing = advance_cursor(ed);
    }
}

void skip_cursor_to_prev_line(EditorData *ed)
{
    if (ed->crsr_y == 0)
        return;

    int target_x = ed->trgt_x != (-1) ? ed->trgt_x : ed->crsr_x;
    int target_y = ed->crsr_y - 1;
    bool backing = back_cursor(ed);

    while (backing)
    {
        if (target_y == ed->crsr_y && curr_char(ed) == '\n' && ed->crsr_x < target_x)
        {
            ed->trgt_x = target_x;
            break;
        }
        else if (ed->crsr_x == target_x)
        {
            ed->trgt_x = -1;
            break;
        }

        backing = back_cursor(ed);
    }
}

bool advance_cursor(EditorData *ed)
{
    char c = curr_char(ed);
    ed->char_i++;

    if (c == EOF)
    {
        ed->char_i--;
        return false;
    }
    else if (c == '\n')
    {
        move_cursor(ed->crsr_y + 1, 0, ed);
        return true;
    }
    else
    {
        move_cursor(ed->crsr_y, ed->crsr_x + 1, ed);
        return true;
    }
}

bool back_cursor(EditorData *ed)
{
    ed->char_i--;
    char c = curr_char(ed);

    if (c == EOF)
    {
        ed->char_i++;
        return false;
    }
    else if (c == '\n')
    {
        move_cursor(ed->crsr_y - 1, ed->scr_width - 1, ed);

        while ((inch() & A_CHARTEXT) == ' ' && ed->crsr_x != 0)
            move_cursor(ed->crsr_y, ed->crsr_x - 1, ed);

        return true;
    }
    else
    {
        move_cursor(ed->crsr_y, ed->crsr_x - 1, ed);
        return true;
    }
}

char curr_char(EditorData *ed)
{
    if (ed->char_i >= strlen(ed->filestr) || ed->char_i < 0)
        return EOF;

    return ed->filestr[ed->char_i];
}