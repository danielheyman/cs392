#include "my.h"

/* Authors: Carla Noshi and Daniel Heyman

 Compares strings by ascii value
 If a and b are identical, return 0. 
 if a < b, return negative number 
 if a > b, return positive number
 Two NULL are equal.
 NULL is always less than a normal string */

int my_strcmp(char* a, char* b){

		if(a == NULL && b == NULL){
       		return 0;
	    }

	    if(a == NULL){
	        return -1;
	    }

	    else if(b == NULL){
	        return 1;

	    for( ; *a && *b && (*a == *b); a++, b++);
	    
	}
	return *a - *b;
}