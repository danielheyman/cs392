#include "my.h"

/* Authors: Carla Noshi and Daniel Heyman

  Returns a pointer to the last char in the string which matches.
  Return NULL if the letter is not found. */

char* my_strrfind(char* String1, char c){

	char* last = NULL;

	 if(String1 != NULL && c != '\0')
    {
        for( ; *String1; String1++)
        {
            if(*String1 == c)
                last = String1;
        }
        if(last != NULL){
        	String1 = last;
        	return String1;
        }
    }

    return NULL;
}
