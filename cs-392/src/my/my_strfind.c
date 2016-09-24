#include "my.h"

/* Authors: Carla Noshi and Daniel Heyman

  Returns a pointer to the first char in the string which matches.
  Return NULL if the letter is not found. */

char* my_strfind(char* String1, char c){

	 if(String1 != NULL && c != '\0')
    {
        for( ; *String1; String1++)
        {
            if(*String1 == c)
                return String1;
        }
    }

    return NULL;
}