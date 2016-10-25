/* 
Authors: Daniel Heyman & Carla Noshi
Implements minishell
*/
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include "my.h"

int pid;

void stopFork() {
    kill(pid, SIGINT);
}

int main(int argc, char* argv[])
{
    char cwd[255], buffer[255], ** vect;
    int i;
    
    signal(SIGINT, stopFork);
        
    while(1) {
        getcwd(cwd, PATH_MAX);
        my_str("MINISHELL: ");
        my_str(cwd);
        my_str(" $: ");
        
        if(read(1, buffer, 254) < 0) {
            free(vect);
            my_str("Unable to read input.");
            exit(0);
        }
        
        i = 0;
        while(buffer[i] != '\n' && buffer[i] != '\0') i++;
        buffer[i] = '\0';
        
        
        vect = my_str2vect(buffer);
        if(my_strcmp("cd", vect[0]) == 0) {
            if(chdir(vect[1]) < 0) {
                my_str("Directory does not exist.\n");
            }
        } else if(my_strcmp("exit", vect[0]) == 0) {
            my_str("Bye :)\n");
            free(vect);
            exit(0);
        } else {
            if((pid = fork()) < 0) {
                my_str("Unable to fork.\n");
                exit(0);
            } else if(pid == 0) {
                if(execvp(vect[0], vect) < 0) {
                    my_str("Command does not exist.\n");
                    exit(0);
                }
            } else {
                while(wait(NULL) != pid);
            }
        }
        free(vect);
    }
    return 0;
}
