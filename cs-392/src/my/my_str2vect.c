  #include "my.h"

/* 
Authors: Daniel Heyman & Carla Noshi
Takes a string 
 Allocates a new vector (array of string ended by a NULL), 
 Splits apart the input string x at each space character 
 Returns the newly allocated array of strings
*/

  char** my_str2vect(char* str)
  {

    char** vect;
    int count;
    int num;
    int words;
    char* newstr;

    if(str != NULL)
    {
      newstr = my_strdup(str);
      for(count = 0, num = 0; newstr[count]; count++)
      {
        if(newstr[count - 1] != ' ' && newstr[count - 1] != '\t'
           && (newstr[count] == ' ' || newstr[count] == '\t'))
        {
          newstr[count] = '\0';
          num++;
        }
        else if(count == 0 && newstr[count] != ' ' && newstr[count] != '\t')
          num++;
      }
      vect = (char**) malloc((num + 1) * sizeof(char*));
      
      for(words = num - 1, count = 0, num = 0; num <= words; )
      {
        if(newstr[count] == ' ' || newstr[count] == '\t')
          for( ; newstr[count] == ' ' || newstr[count] == '\t'; count++){
        vect[num++] = my_strdup(newstr + count);
        count += (my_strlen(newstr + count) + 1);
      }
      vect[num] = NULL;
      free(newstr);
    }
  }

  else{
    vect = NULL;
  }


  return vect;
}