 #include "my.h"

 /*
 Authors: Carla Noshi & Daniel Heyman
 Takes a xtor (array of string ended by a NULL)
 Allocates a new string and copies each string from the array into new string separated by a single space, until NULL pointer to string is found
 Returns new string 
 */


char *my_vect2str(char **x){

	int lengthrows = 0;
	char *fullstr;
	int indexrow = 0;
	int indexcol = 0;
	int size = 0;
	
	if (x == NULL)
   	 	return NULL;
	
	while(x[indexrow] != NULL) 
	{
		lengthrows++;
		indexrow++;
	}

	for(indexrow = 0 ; indexrow < lengthrows; indexrow++){
		for(indexcol = 0; x[indexrow][indexcol] != '\0'; indexcol++){
			size++;
		}

		size++;
	}

	fullstr = (char*)malloc(size);
	size = 0;

	for(indexrow = 0 ; indexrow < lengthrows; indexrow++){
		for(indexcol = 0; x[indexrow][indexcol] != '\0'; indexcol++){
			fullstr[size] = x[indexrow][indexcol];
			size++;
		}
		fullstr[size] = ' ';
		size++;
	}

	return fullstr;

}

