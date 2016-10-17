/* 
Authors: Daniel Heyman & Carla Noshi
Implements a piping process.
*/
#include "my.h"

int main(int argc, char* argv[])
{
    char buffer[100];
    int fd[2], fd2[2];
    int pid;
    char * input = my_vect2str(&argv[1]);
    pipe(fd);
    
    if(my_strlen(input) <= 0) {
        my_str("Error, insert input.");
        return -1;
    } else if((pid = fork()) == -1) {
        my_str("Error forking child");
    } else if(pid == 0) {
        close(fd[1]);
		read(fd[0], buffer, 99);
        pipe(fd2);

        if((pid = fork()) == -1) {
            my_str("Error forking grandchild");
        } else if(pid == 0) {
            // Granchild
            close(fd2[1]);
            read(fd2[0], buffer, 99);
            my_str("Grandchild: ");
            my_str(buffer);
            my_char('\n');
        } else {
            // Child
            my_str("Child: ");
            my_str(buffer);
            my_char('\n');
        }
        
    } else {
        // parent
        my_str("Parent: ");
        my_str(input);
        my_char('\n');
        
        close(fd[0]);
        write(fd[1], input, 99);
    }
    free(input);
    
    return 0;
}
