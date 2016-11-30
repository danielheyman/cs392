/* 
Authors: Daniel Heyman & Carla Noshi
Implements minishell
*/
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <limits.h>
#include <sys/wait.h>
#include <curses.h>
#include <string.h>
#include "my.h"

/*
    TODO
    Up and Down Arrow Keys: Should swap between previous and the current command. For this feature you will most likely need to use your linked list
    
    CTRL + "W": Cut a word into the clipboard. You should be abe to cut multiple words. (Try using it in bash!)
    CTRL + "U": Cut a line into the clipboard. It should be able to work with the above commend. (Once again, try using it in bash!)
    
    Saved History: When you exit, save your command history to a file called .nsmshistory and load the command history when you start - save to home directory
    Dollar Sign: Program the ability to use the $() to pass output from one program into another (i.e. more $(myselect *.c))
*/

struct Buffers {
    int length, maxLength, cursorInitialY, cursorInitialX, currentPosition;
    char content[2500], clipboard[2500];
};

void moveCursor(struct Buffers * buffer, int currentPosition) {
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

void resetBuffer(struct Buffers * buffer) {
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
    moveCursor(buffer, 0);
    buffer->content[--buffer->length] = '\0';
    printw(buffer->content);
    addch(' ');
    moveCursor(buffer, buffer->currentPosition);
}

void bufferLeft(struct Buffers * buffer) {
    if(buffer->currentPosition == 0) return;
    buffer->currentPosition--;
    moveCursor(buffer, buffer->currentPosition);
}

void bufferRight(struct Buffers * buffer) {
    if(buffer->currentPosition == buffer->length) return;
    buffer->currentPosition++;
    moveCursor(buffer, buffer->currentPosition);
}

void bufferAddChar(struct Buffers * buffer, char key) {
    for(int i = buffer->length - 1; i >= buffer->currentPosition; --i) buffer->content[i + 1] = buffer->content[i];
    buffer->content[buffer->currentPosition++] = key;
    buffer->length++;
    if(buffer->length > buffer->maxLength) buffer->maxLength = buffer->length;
    moveCursor(buffer, 0);
    buffer->content[buffer->length] = '\0';
    printw(buffer->content);
    moveCursor(buffer, buffer->currentPosition);
}

void bufferMoveStart(struct Buffers * buffer) {
    moveCursor(buffer, 0);
}

void bufferMoveEnd(struct Buffers * buffer) {
    moveCursor(buffer, buffer->length);
}

void bufferCutCommand(struct Buffers * buffer) {
    my_strncpy(buffer->clipboard, buffer->content, buffer->length);
    buffer->currentPosition = 0;
    buffer->content[0] = '\0';
    for(int i = 0; i < buffer->length; i++) {
        moveCursor(buffer, i);
        addch(' ');
    }
    moveCursor(buffer, 0);
    buffer->length = 0;
    refresh();
}

void bufferPasteCommand(struct Buffers * buffer) {
    for(int i = 0; buffer->clipboard[i] != '\0'; ++i) {
        bufferAddChar(buffer, buffer->clipboard[i]);
    }
}

int pid;
struct Buffers buffer;

void stopFork() {
    if(pid) kill(pid, SIGINT);
}

void ctrly() {
    bufferPasteCommand(&buffer);
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

void clearScreen(struct Buffers * buffer) {
    endwin();
    erase();
    refresh();
    
    if(buffer) {
        printDirectory();
        getyx(stdscr, buffer->cursorInitialY, buffer->cursorInitialX);
        moveCursor(buffer, 0);
        printw(buffer->content);
        moveCursor(buffer, buffer->currentPosition);
    }
}

int main(int argc, char* argv[])
{
    char ** vect;
    int i, key;
    
    signal(SIGINT, stopFork);
    signal(SIGTSTP, ctrly);
    
    initscr();
    start_color();
    init_color(COLOR_RED, 900, 100, 100);
    init_color(COLOR_BLUE, 100, 100, 900);
    init_color(COLOR_BLACK, 74, 152, 219);
    clearScreen(NULL);
    scrollok(stdscr,TRUE);
    keypad(stdscr, TRUE);
    noecho();
        
    while(1) {
        printDirectory();
        
        resetBuffer(&buffer);
        while(1) {
            key = getch();
            //printw("%d\n", key);
            //continue;
            
            if(key == 10) break; // enter
            else if(key == 127 || key == 8) bufferBackspace(&buffer);
            else if(key == KEY_UP) continue;
            else if(key == KEY_DOWN) continue;
            else if(key == KEY_LEFT) bufferLeft(&buffer);
            else if(key == KEY_RIGHT) bufferRight(&buffer);
            else if(key == 12) clearScreen(&buffer); // ctrl+l
            else if(key == 1) bufferMoveStart(&buffer); // ctrl+a
            else if(key == 5) bufferMoveEnd(&buffer); // ctrl+e
            else if(key == 23) continue; // ctrl+w
            else if(key == 21) bufferCutCommand(&buffer); // ctrl+u
            else if(key == 25) bufferPasteCommand(&buffer); // ctrl+y
            else bufferAddChar(&buffer, key);
        }
        
        moveCursor(&buffer, buffer.length);
        buffer.content[buffer.length] = '\0';
        printw("\n");
        vect = my_str2vect(buffer.content);
        
        if(my_strcmp("cd", vect[0]) == 0) {
            if(chdir(vect[1]) < 0) {
                printw("Directory does not exist.\n");
            }
        } else if(my_strcmp("exit", vect[0]) == 0) {
            printw("Bye :)\n");
            refresh();
            free(vect);
            endwin();
            exit(0);
        } else if(my_strcmp("help", vect[0]) == 0) {
            printw("Built in commands:\ncd [directory]: Changes the current working directory to directory.\n");
            printw("exit: Exits the minishell.\nhelp: Prints a help message listing the built in commands.\n");
        } else {
            int pipefd[2];
            pipe(pipefd);
            
            if((pid = fork()) < 0) {
                printw("Unable to fork.\n");
                refresh();
                exit(0);
            } else if(pid == 0) {
                close(pipefd[0]);
                dup2(pipefd[1], 1);
                dup2(pipefd[1], 2);
                close(pipefd[1]);
                
                if(execvp(vect[0], vect) < 0) {
                    printf("Command does not exist.\n");
                    exit(0);
                }
            } else {
                char buffer[1024];
                close(pipefd[1]);
                while ((i = read(pipefd[0], buffer, sizeof(buffer))) != 0){
                    buffer[i] = '\0';
                    printw(buffer);
                    refresh();
                }
            }
        }
        free(vect);
    }
    return 0;
}
