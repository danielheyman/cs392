#include "my.h"

/* Author: Carla Noshi

  Compares strings by ascii value
  If a and b are identical, return 0. 
  if a < b, return negative number 
  if a > b, return positive number
  Two NULL are equal.
  NULL is always less than a normal string
  BUT  Only compares n chars or until the end of a string */

int my_strncmp(char* a, char* b, int n){

    if((a == NULL && b == NULL) || n <= 0){
        return 0;
    }

    if(a == NULL){
        return -1;
    }

    else if(b == NULL){
    	return 1;
    }

    while(*a != '\0' && *b != '\0' && (*a == *b) && --n > 0) {
        a++;
        b++;
    }

    return *a - *b;
}
