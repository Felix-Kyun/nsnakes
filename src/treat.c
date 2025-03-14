#include "treat.h"
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

Treat *treat_init(void) {
  // seed RNG
  srand((unsigned int)time(NULL));

  Treat *treat = (Treat *)malloc(sizeof(Treat));
  treat->position.x = 0;
  treat->position.y = 0;
  return treat;
}

// TODO: fix the border check after adding border
// TODO: fix the treat_new function to not place treat on snake
//
// void treat_new(Treat *treat, WINDOW *win) {
//   treat->position.x = rand() % (COLS - 2) + 1;
//   treat->position.y = rand() % (LINES - 2) + 1;
//   mvwaddwstr(win, treat->position.y, treat->position.x, L"🍎");
// }

void treat_deinit(Treat *treat) { free(treat); }

