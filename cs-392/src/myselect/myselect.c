/* 
Authors: Daniel Heyman & Carla Noshi
Implements a piping process.
*/
#include "my.h"
#include <termios.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h>
#include <term.h> 
#include <ncurses.h>

int selected, count;
char** files;

void draw() {
  int width, height;
  setupterm("vt100", fileno(stdout), (int *)0);
  width = tigetnum("cols");
  height = tigetnum("lines");
  setupterm(NULL, fileno(stdout), (int *)0);

  int rows = 0;
  int maxlen = width + 1;
  int numberPerLine;
  while(maxlen > width && rows <= height) {
    rows++;
    maxlen = 0;
    numberPerLine = (count + rows - 1) / rows;
    for(int i = 0; i < rows; ++i) {
      int linelen = 0;
      for(int j = numberPerLine * i; j < numberPerLine * (i + 1) && j < count; ++j) {
        linelen += strlen(files[j]) + 1;
      }
      if(linelen > maxlen) maxlen = linelen;
    }
  }
  
  erase();
  curs_set(0);
  if(maxlen > width) {
    printw("resize window!");
    refresh();
    return;
  }
  
  printw("%d %d", width, height);

  
  int * maxPerCol = malloc(sizeof(int) * numberPerLine);
  for(int i = 0; i < rows; ++i) {
    for(int j = numberPerLine * i; j < numberPerLine * (i + 1) && j < count; ++j) {
      if(strlen(files[j]) > maxPerCol[j - numberPerLine * i]) maxPerCol[j - numberPerLine * i] = strlen(files[j]);
    }
  }
  
  for(int i = 0; i < rows; ++i) {
    for(int j = numberPerLine * i; j < numberPerLine * (i + 1) && j < count; ++j) {
      if(j == selected) attron(A_UNDERLINE);
      printw("%s", files[j]);
      if(j == selected) attroff(A_UNDERLINE);
      int size = strlen(files[j]);
      while(size++ <= maxPerCol[j - numberPerLine * i]) printw(" ");
    }
    printw("\n");
  }
  
  free(maxPerCol);
  refresh();
}

int main(int argc, char* argv[])
{
  struct termios initial_settings, new_settings; 
  char key[6] = "x"; 
  int num_chars;
                
  if (argc < 2) {
      my_str("Invalid arguments");
      exit(0);
  }
  
  count = argc - 1;
  files = &(argv[1]);
  selected = 0;
  signal(SIGWINCH, draw);

  
  // Init
  initscr();
  draw();


  // Input
  tcgetattr(fileno(stdin), &initial_settings); 
  new_settings = initial_settings;
  new_settings.c_lflag &= ~ICANON;
  new_settings.c_lflag &= ~ECHO;
  new_settings.c_cc[VMIN] = 1;
  new_settings.c_cc[VTIME] = 0;
  new_settings.c_iflag &= ~ICRNL;
  
  if (tcsetattr(fileno(stdin), TCSAFLUSH, &new_settings) != 0) {
    fprintf(stderr,"Could not set attributes\n"); 
    exit(1);
  }
    
  while (strcmp(key, "\033") != 0) {
    fflush(stdout);
    num_chars = read(fileno(stdin), key, 3);
    key[num_chars] = '\0';
    if (key[0] == '\015') strcpy(key, "Enter");
    else if (strcmp(key, "^[[A") == 0) strcpy(key, "Up");
    else if (strcmp(key, "^[[B") == 0) strcpy(key, "Down");
    else if (strcmp(key, "^[[D") == 0) strcpy(key, "Left");
    else if (strcmp(key, "^[[C") == 0) strcpy(key, "Right");
  }
    
  tcsetattr(fileno(stdin), TCSANOW, &initial_settings);
  
  endwin();
  return 0;
}
