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

struct Buffers {
    int length, maxLength, cursorInitialY, cursorInitialX, currentPosition;
    char content[255];
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

struct Buffers buffer;
int pid;

void stopFork() {
    if(pid) kill(pid, SIGINT);
}

void ctrly() {
    
}

void clearScreen() {
    endwin();
    erase();
    refresh();
}

int main(int argc, char* argv[])
{
    char cwd[255], ** vect;
    int i, key;
    
    signal(SIGINT, stopFork);
    signal(SIGTSTP, ctrly);
    
    initscr();
    clearScreen();
    scrollok(stdscr,TRUE);
    keypad(stdscr, TRUE);
    noecho();
        
    while(1) {
        refresh();
        getcwd(cwd, 512);
        printw("MINISHELL: ");
        printw("%s", cwd);
        printw(" $: ");
        
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
            else if(key == 12) continue; // ctrl+l
            else if(key == 1) continue; // ctrl+a
            else if(key == 5) continue; // ctrl+e
            else if(key == 23) continue; // ctrl+w
            else if(key == 21) continue; // ctrl+u
            else if(key == 25) continue; // ctrl+y
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
