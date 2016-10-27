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

  int len = 0;
  int strnum = 0;
  char **fullstr;
  int index = 0;
  int size = 0;
  int inword = 0;
  int startindex = -1;
  int endindex = -1;
  
  if(str == NULL && *str == '\0')
    return NULL;
  if(*str == '\0')
  {
    fullstr = malloc(sizeof(char *) * 0);
    fullstr[0] = malloc(0);
    return fullstr;
  }
  
  len = my_strlen(str);
    
  for(index = 0; index < len; index++)
  {
    if(!(str[index] == ' ' || str[index] == '\t' || str[index] == '\n') && (inword == 0))
    {
      strnum++;
      inword = 1;
    }
    else if((str[index] == ' ' || str[index] == '\t' || str[index] == '\n') && (inword == 1))
      inword = 0;
    
  }
  
  fullstr = malloc(sizeof(char *) * (strnum) + 1);
  inword = 0;   
  strnum = 0;
  
  startindex = -1;
  endindex = -1;
  
  for(index = 0; index <= len; index++)
  {
    if(!(str[index] == ' ' || str[index] == '\t' || str[index] == '\n') && (inword == 0))
    {
      startindex = index;
      inword = 1;
    }
    else if((str[index] == ' ' || str[index] == '\t' || str[index] == '\n' || str[index] == '\0') && (inword == 1))
    {
      endindex = index;
      inword = 0;
    }
    if((startindex != -1) && (endindex != -1))
    {
      size = (endindex - startindex);
      fullstr[strnum] = malloc(size * sizeof(char) + 1);
      my_strncpy(fullstr[strnum], &(str[startindex]), size);
      fullstr[strnum][startindex + size] = '\0';
      strnum++;
      startindex = -1;
      endindex = -1;
    }
  }
  
  fullstr[strnum] = NULL;
  
  return fullstr;
}