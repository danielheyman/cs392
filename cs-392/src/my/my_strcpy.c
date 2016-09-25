#include "my.h"

/* Authors: Carla Noshi and Daniel Heyman

  Copies the characters from src into dst overwriting what's already in there.
  Always copies a '\0'
  Assumes dst has enough memory allocated for the new string if it is longer.
  Does not allocate memory */

char* my_strcpy(char* dst, char* src){
	char* dstStart = dst;

    if(dst != NULL && src != NULL)
    {
        for( ; *src; src++, dst++)
            *dst = *src;

        *dst = '\0';
    }

    return dstStart;
}
