#ifndef _BUFFERRS_H_ 
#define _BUFFERRS_H_

#ifndef NULL 
#define NULL ((void*)0) 
#endif

struct Buffers {
    int length, maxLength, cursorInitialY, cursorInitialX, currentPosition, currentHistoryPosition;
    char * content, clipboard[1000], * originalHistory, * dir;
    struct s_node * history;
};

char * bufferHistoryFile(struct Buffers * buffer) {
    if(buffer->dir == NULL) {
        struct passwd *pw = getpwuid(getuid());
        buffer->dir = pw->pw_dir;
        my_strcat(buffer->dir, my_strdup("/.nsmshistory"));
    }
    return buffer->dir;
}

void bufferSaveHistory(struct Buffers * buffer) {
    FILE *fp;
    fp = fopen(bufferHistoryFile(buffer),"w");
    for(int i = 1; i < count_s_nodes(buffer->history) && i < 50; i++) {
        fprintf(fp,"%s\n", (char *) elem_at(buffer->history, i));
    }
    fclose(fp);
}

void bufferLoadHistory(struct Buffers * buffer) {
    FILE* fp = fopen(bufferHistoryFile(buffer), "r");
    if (fp == NULL) return;
    char line[1000];

    while (fgets(line, sizeof(line), fp)) {
        if(line[0] == '\n') continue;
        strtok(line, "\n");
        append(new_node(my_strdup(line), NULL, NULL), &buffer->history);
    }
    fclose(fp);
}

void bufferMoveCursor(struct Buffers * buffer, int currentPosition) {
    int screenx, screeny, lines, x, y;
    x = buffer->cursorInitialX;
    y = buffer->cursorInitialY;
    getmaxyx(stdscr, screeny, screenx);
    lines = (x + buffer->maxLength - 1) / (screenx) + 1;
    if(lines + y >= screeny) {
        y = screeny - lines;
    }
    x += currentPosition;
    y += x / screenx;
    x %= screenx;
    move(y, x);
    refresh();
}

void bufferResetOriginalHistory(struct Buffers * buffer) {
    if(buffer->currentHistoryPosition == 0) return;
    remove_node_at(&buffer->history, buffer->currentHistoryPosition);
    add_node_at(new_node(my_strdup(buffer->originalHistory), NULL, NULL), &buffer->history, buffer->currentHistoryPosition);
    buffer->originalHistory = my_strdup("");
    buffer->content = elem_at(buffer->history, buffer->currentHistoryPosition);
}

void bufferReset(struct Buffers * buffer) {
    if(buffer->history == NULL) {
        add_node_at(new_node(my_strdup(""), NULL, NULL), &buffer->history, 1);
        bufferLoadHistory(buffer);
    }
    if(buffer->length != 0) {
        add_node_at(new_node(my_strdup(buffer->content), NULL, NULL), &buffer->history, 1);
        if(buffer->currentHistoryPosition++ != 0) bufferResetOriginalHistory(buffer);
    }
    buffer->content = elem_at(buffer->history, 0);
    buffer->content[0] = '\0';
    buffer->length = 0;
    buffer->maxLength = 0;
    buffer->currentPosition = 0;
    buffer->currentHistoryPosition = 0;
    buffer->clipboard[0] = '\0';
    getyx(stdscr, buffer->cursorInitialY, buffer->cursorInitialX);
}

void bufferBackspace(struct Buffers * buffer) {
    if(buffer->currentPosition == 0) return;
    buffer->currentPosition--;
    memmove(&buffer->content[buffer->currentPosition], &buffer->content[buffer->currentPosition + 1], strlen(buffer->content) - buffer->currentPosition);
    delch();
    bufferMoveCursor(buffer, 0);
    buffer->content[--buffer->length] = '\0';
    printw(buffer->content);
    addch(' ');
    bufferMoveCursor(buffer, buffer->currentPosition);
}

void bufferLeft(struct Buffers * buffer) {
    if(buffer->currentPosition == 0) return;
    buffer->currentPosition--;
    bufferMoveCursor(buffer, buffer->currentPosition);
}

void bufferRight(struct Buffers * buffer) {
    if(buffer->currentPosition == buffer->length) return;
    buffer->currentPosition++;
    bufferMoveCursor(buffer, buffer->currentPosition);
}

void bufferAddChar(struct Buffers * buffer, char key) {
    for(int i = buffer->length - 1; i >= buffer->currentPosition; --i) buffer->content[i + 1] = buffer->content[i];
    buffer->content[buffer->currentPosition++] = key;
    buffer->length++;
    if(buffer->length > buffer->maxLength) buffer->maxLength = buffer->length;
    bufferMoveCursor(buffer, 0);
    buffer->content[buffer->length] = '\0';
    printw(buffer->content);
    bufferMoveCursor(buffer, buffer->currentPosition);
}

void bufferMoveStart(struct Buffers * buffer) {
    bufferMoveCursor(buffer, 0);
}

void bufferMoveEnd(struct Buffers * buffer) {
    bufferMoveCursor(buffer, buffer->length);
}

void bufferCutCommand(struct Buffers * buffer) {
    my_strncpy(buffer->clipboard, buffer->content, buffer->length);
    buffer->currentPosition = 0;
    buffer->content[0] = '\0';
    for(int i = 0; i < buffer->length; i++) {
        bufferMoveCursor(buffer, i);
        addch(' ');
    }
    bufferMoveCursor(buffer, 0);
    buffer->length = 0;
    refresh();
}

void bufferPasteCommand(struct Buffers * buffer) {
    for(int i = 0; buffer->clipboard[i] != '\0'; ++i) {
        bufferAddChar(buffer, buffer->clipboard[i]);
    }
}

void bufferChangeCommand(struct Buffers * buffer, char * contentPointer) {
    for(int i = my_strlen(contentPointer); i < buffer->length; i++) {
        bufferMoveCursor(buffer, i);
        addch(' ');
    }
    
    buffer->length = my_strlen(contentPointer);
    buffer->currentPosition = buffer->length;
    buffer->content = contentPointer;
    if(buffer->length > buffer->maxLength) buffer->maxLength = buffer->length;
    bufferMoveCursor(buffer, 0);
    printw(buffer->content);
}

void bufferHistoryUp(struct Buffers * buffer) {
    if(buffer->currentHistoryPosition == count_s_nodes(buffer->history) - 1) return;
    bufferResetOriginalHistory(buffer);
    buffer->originalHistory = my_strdup(elem_at(buffer->history, ++buffer->currentHistoryPosition));
    bufferChangeCommand(buffer, elem_at(buffer->history, buffer->currentHistoryPosition));
}

void bufferHistoryDown(struct Buffers * buffer) {
    if(buffer->currentHistoryPosition == 0) return;
    bufferResetOriginalHistory(buffer);
    buffer->originalHistory = my_strdup(elem_at(buffer->history, --buffer->currentHistoryPosition));
    bufferChangeCommand(buffer, elem_at(buffer->history, buffer->currentHistoryPosition));
}

void printDirectory() {
    char cwd[255];
    refresh();
    getcwd(cwd, 512);
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    attron(COLOR_PAIR(1)); 
    printw("MINISHELL: ");
    attroff(COLOR_PAIR(1)); 
    attron(COLOR_PAIR(2)); 
    printw("%s", cwd);
    attroff(COLOR_PAIR(2)); 
    attron(COLOR_PAIR(1)); 
    printw(" $: ");
    attroff(COLOR_PAIR(1)); 
}

void bufferClearScreen(struct Buffers * buffer) {
    endwin();
    erase();
    refresh();
    
    if(buffer) {
        printDirectory();
        getyx(stdscr, buffer->cursorInitialY, buffer->cursorInitialX);
        bufferMoveCursor(buffer, 0);
        printw(buffer->content);
        bufferMoveCursor(buffer, buffer->currentPosition);
    }
}

#endif
