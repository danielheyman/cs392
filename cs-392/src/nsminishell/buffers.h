#ifndef _BUFFERRS_H_ 
#define _BUFFERRS_H_

#ifndef NULL 
#define NULL ((void*)0) 
#endif

struct Buffers {
    int length, maxLength, cursorInitialY, cursorInitialX, currentPosition;
    char content[2500], clipboard[2500];
};

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

void bufferReset(struct Buffers * buffer) {
    buffer->length = 0;
    buffer->maxLength = 0;
    buffer->currentPosition = 0;
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
