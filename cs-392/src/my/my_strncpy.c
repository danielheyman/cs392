#include "my.h"

/* Author: Carla Noshi

  Copies the characters from src into dst overwriting what's already in there.
  Always copies a '\0'
  Assumes dst has enough memory allocated for the new string if it is longer.
  Does not allocate memory*/

  char* my_strncpy(char* dst, char* src, int n){

     int counter;

    if(dst != NULL && src != NULL && n > 0)
    {
        counter = 0;

        for( ; src[counter] && counter < n; counter++)
            dst[counter] = src[counter];

        if(n > my_strlen(src))
            dst[counter] = '\0';
    }

    return dst;
}