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
#include "my.h"

int pid;

void stopFork() {
    kill(pid, SIGINT);
}

void clearLine() {
    printf("\33[2K\r");
}

void clearScreen() {
    //system("@cls||clear");
    endwin();
    erase();
    refresh();
}

int main(int argc, char* argv[])
{
    char cwd[255], buffer[255], ** vect;
    int i, key, x, y, screenx, screeny;
    
    signal(SIGINT, stopFork);
    
    initscr();
    clearScreen();
        
    while(1) {
        refresh();
        getcwd(cwd, 512);
        printw("MINISHELL: ");
        printw("%s", cwd);
        printw(" $: ");
        
        
        i = 0;
        key = 0;
        keypad(stdscr, TRUE);
        noecho();
        while(key != 27) {
          key = getch();
          if(key == 10) break; // enter
          else if (key == 127 || key == 8) {
              if(i == 0) continue;
              getyx(stdscr, y, x);
              getmaxyx(stdscr, screeny, screenx);
              if(x == 0) {
                  y--;
                  x = screenx;
              }
              move(y, x - 1);
              refresh();
              delch();
              i--;
          }
          /*else if(key == 32) { // space
            selected[current] = !selected[current];
            if(selected[current] && ++current >= count) current = 0;
          } else if(key == KEY_UP) {
            if(--current < 0) current = count - 1;
          } else if(key == KEY_DOWN) {
            if(++current >= count) current = 0;
          } else if(key == KEY_LEFT) {
            current -= height;
            if(current < 0) current = 0;
          } else if(key == KEY_RIGHT) {
            current += height;
            if(current > count - 1) current = count - 1;
            }*/
            else {
                printw("%c", key);
                buffer[i++] = key;
            }
        }
        
        printw("\n");
        refresh();
        buffer[i] = '\0';
        vect = my_str2vect(buffer);
        
        if(my_strcmp("cd", vect[0]) == 0) {
            if(chdir(vect[1]) < 0) {
                printw("Directory does not exist.\n");
            }
        } else if(my_strcmp("exit", vect[0]) == 0) {
            printw("Bye :)\n");
            refresh();
            free(vect);
            exit(0);
        } else if(my_strcmp("help", vect[0]) == 0) {
            printw("Built in commands:\ncd [directory]: Changes the current working directory to directory.\n");
            printw("exit: Exits the minishell.\nhelp: Prints a help message listing the built in commands.\n");
        } else {
            FILE* p = popen("ls -la", "r");
            if (!p) return 1;

            char buff[1024];
            while (fgets(buff, sizeof(buff), p)) {
                    printf("%s", buff);
            }
            pclose(p);
            /*int pipefd[2];
            pipe(pipefd);
            
            if((pid = fork()) < 0) {
                printw("Unable to fork.\n");
                exit(0);
            } else if(pid == 0) {
                close(pipefd[0]);
                dup2(pipefd[1], 1);
                dup2(pipefd[1], 2);
                close(pipefd[1]);
                
                if(execvp(vect[0], vect) < 0) {
                    wprintw(stdscr, "Command does not exist.\n");
                    refresh();
                    exit(0);
                }
            } else {
                char buffer[1024];
                close(pipefd[1]);
                while (read(pipefd[0], buffer, sizeof(buffer)) != 0){
                    printw(buffer);
                }
            }*/
        }
        free(vect);
    }
    return 0;
}
