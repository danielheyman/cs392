/* 
Authors: Daniel Heyman & Carla Noshi
Implements a piping process.
*/
#include "my.h"
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h>
#include <curses.h>
#include <signal.h>

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
  initscr();
  draw();
  
  int key = 0;
  keypad(stdscr, TRUE);
  noecho();
  while(key != 27) {
    key = getch();
    if(key == 10) break; // enter
    else if(key == 32) { // space
      selected[current] = !selected[current];
      if(selected[current] && ++current >= count) current = 0;
    } else if(key == KEY_UP) {
      if(--current < 0) current = count - 1;
    } else if(key == KEY_DOWN) {
      if(++current >= count) current = 0;
    } else if(key == KEY_LEFT) {
      current -= height;
      if(current < 0) current = 0;
    } else if(key == KEY_RIGHT) {
      current += height;
      if(current > count - 1) current = count - 1;
    }
    draw();
  }
  
  endwin();
  if (key == 10) { // enter
    for(int i = 0; i < count; ++i) {
      if(selected[i]) printf("%s ", files[i]);
    }
  }
  free(fileSizes);
  free(selected);
  return 0;
}
