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
#include <pwd.h>
#include "my.h"
#include "list.h"
#include "buffers.h"

/*
    TODO
    CTRL + "W": Cut a word into the clipboard. You should be abe to cut multiple words. (Try using it in bash!)
    CTRL + "U": Cut a line into the clipboard. It should be able to work with the above commend. (Once again, try using it in bash!)
    
    Saved History: load the command history when you start - save to home directory
    Dollar Sign: Program the ability to use the $() to pass output from one program into another (i.e. more $(myselect *.c))
*/

int pid;
struct Buffers buffer;
char ** vect;

void stopFork() {
    if(pid) kill(pid, SIGINT);
}

void ctrly() {
    bufferPasteCommand(&buffer);
}

void end() {
    refresh();
    free(vect);
    endwin();
    bufferSaveHistory(&buffer);
    exit(0);
}

int main(int argc, char* argv[])
{
    int i, key;
    
    signal(SIGINT, stopFork);
    signal(SIGTSTP, ctrly);
    
    initscr();
    start_color();
    init_color(COLOR_RED, 900, 100, 100);
    init_color(COLOR_BLUE, 100, 100, 900);
    init_color(COLOR_BLACK, 74, 152, 219);
    bufferClearScreen(NULL);
    scrollok(stdscr,TRUE);
    keypad(stdscr, TRUE);
    noecho();
        
    while(1) {
        printDirectory();
        
        bufferReset(&buffer);
        while(1) {
            key = getch();
            //printw("%d\n", key);
            //continue;
            
            if(key == 10) break; // enter
            else if(key == 127 || key == 8 || key == KEY_BACKSPACE) bufferBackspace(&buffer);
            else if(key == KEY_UP) bufferHistoryUp(&buffer);
            else if(key == KEY_DOWN) bufferHistoryDown(&buffer);
            else if(key == KEY_LEFT) bufferLeft(&buffer);
            else if(key == KEY_RIGHT) bufferRight(&buffer);
            else if(key == 12) bufferClearScreen(&buffer); // ctrl+l
            else if(key == 1) bufferMoveStart(&buffer); // ctrl+a
            else if(key == 5) bufferMoveEnd(&buffer); // ctrl+e
            else if(key == 23) continue; // ctrl+w
            else if(key == 21) bufferCutCommand(&buffer); // ctrl+u
            else if(key == 25) bufferPasteCommand(&buffer); // ctrl+y
            else bufferAddChar(&buffer, key);
        }
        
        bufferMoveCursor(&buffer, buffer.length);
        buffer.content[buffer.length] = '\0';
        printw("\n");
        vect = my_str2vect(buffer.content);
        
        if(my_strcmp("cd", vect[0]) == 0) {
            if(chdir(vect[1]) < 0) {
                printw("Directory does not exist.\n");
            }
        } else if(my_strcmp("exit", vect[0]) == 0) {
            printw("Bye :)\n");
            end();
        } else if(my_strcmp("help", vect[0]) == 0) {
            printw("Built in commands:\ncd [directory]: Changes the current working directory to directory.\n");
            printw("exit: Exits the minishell.\nhelp: Prints a help message listing the built in commands.\n");
        } else {
            int pipefd[2];
            pipe(pipefd);
            
            if((pid = fork()) < 0) {
                printw("Unable to fork.\n");
                end();
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
