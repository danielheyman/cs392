#include "my.h"

int main(int argc, char* argv[])
{
    int pipe1[2]
    int length = my_strlen(argv[1]);

    if(length <= 0)
    {
        my_str("Error, insert input.");
        return -1;
    }
    
    if(pipe(pipe1) == -1)
    {
        my_str("Error piping.");
        return -1;
    }
    
    return 0;
}