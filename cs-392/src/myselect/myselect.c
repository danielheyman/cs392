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
#include <curses.h>

int current, count, width, height, columnCount;
bool * selected;
char** files;
int * fileSizes;

void draw() {
  endwin();
  erase();
  refresh();
  getmaxyx(stdscr,height,width);

  columnCount = (count + height + 1) / height;
  int * maxPerCol = malloc(sizeof(int) * columnCount);
  for(int i = 0; i < columnCount; ++i) maxPerCol[i] = 0;
  for(int i = 0; i < count; ++i) {
    if(fileSizes[i] > maxPerCol[i / height]) maxPerCol[i / height] = fileSizes[i];
  }
  int totalWidth = 0;
  for(int i = 0; i < columnCount; ++i) totalWidth += maxPerCol[i];
  
  curs_set(0);
  if(totalWidth >= width) {
    printw("resize window!");
    refresh();
    return;
  }
  
  for(int i = 0; i < height; ++i) {
    for(int j = 0; j < columnCount; ++j) {
      int loc = j * height + i;
      if(loc >= count) continue;
      
      if(selected[loc]) attron(A_STANDOUT);
      if(loc == current) attron(A_UNDERLINE);
      printw("%s", files[loc]);
      if(selected[loc]) attroff(A_STANDOUT);
      if(loc == current) attroff(A_UNDERLINE);
      int size = fileSizes[loc];
      while(size++ <= maxPerCol[j]) printw(" ");
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
  //int c = 0;
  int num_chars;
                
  if (argc < 2) {
      my_str("Invalid arguments");
      exit(0);
  }
  
  count = argc - 1;
  files = &(argv[1]);
  fileSizes = malloc(sizeof(int) * count);
  selected = malloc(sizeof(bool) * count);
  for(int i = 0; i < count; ++i) {
    fileSizes[i] = strlen(files[i]) + 1;
    selected[i] = false;
  }
  current = 0;
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
    if (key[0] == '\015') { // enter
      break;
    }
    else if(strcmp(key, "\040") == 0) { // space
      selected[current] = !selected[current];
      if(selected[current] && ++current >= count) current = 0;
      draw();
    }
    else if (strcmp(&(key[1]), "[A") == 0) { // up
      if(--current < 0) current = count - 1;
      draw();
    }
    else if (strcmp(&(key[1]), "[B") == 0) { // down
      if(++current >= count) current = 0;
      draw();
    }
    else if (strcmp(&(key[1]), "[D") == 0) { // left
      current -= height;
      if(current < 0) current = 0;
      draw();
    }
    else if (strcmp(&(key[1]), "[C") == 0) { // right
      current += height;
      if(current > count - 1) current = count - 1;
      draw();
    }
  }
    
  tcsetattr(fileno(stdin), TCSANOW, &initial_settings);
  endwin();
  
  if (key[0] == '\015') { // enter
    for(int i = 0; i < count; ++i) {
      if(selected[i]) printf("%s ", files[i]);
    }
  }
  
  free(fileSizes);
  free(selected);
  return 0;
}
