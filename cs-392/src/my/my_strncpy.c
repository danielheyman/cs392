#include "my.h"

/* Authors: Carla Noshi and Daniel Heyman

  Copies the characters from src into dst overwriting what's already in there.
  Always copies a '\0'
  Assumes dst has enough memory allocated for the new string if it is longer.
  Does not allocate memory */

  char *my_strncpy(char *a, char *b, int n)
  {
    int counter = 0;

    if(a == NULL){

      return NULL;
    }

    if(b == NULL){

      return a;
    }

    if(n < 0){
      n = 0;
    }

    while((b != NULL) && (b[counter] != '\0') && (counter < n))
    {
      a[counter] = b[counter];
      counter++;
    }
    
    a[counter] = '\0';
    
    return a;
  }