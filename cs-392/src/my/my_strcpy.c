#include "my.h"

/* Author: Carla Noshi

  Copies the characters from src into dst overwriting what's already in there.
  Always copies a '\0'
  Assumes dst has enough memory allocated for the new string if it is longer.
  Does not allocate memory */

char* my_strcpy(char* dst, char* src){
	char* dstStart;

    if(dst != NULL && src != NULL)
    {
        dstStart = dst;

        for( ; *src; src++, dst++)
            *dst = *src;

        *dst = '\0';
        dst = dstStart;
    }

    return dst;
}