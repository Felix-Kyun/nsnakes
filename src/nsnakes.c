#include "snake.h"
#include "treat.h"
#include <locale.h>
#include <ncurses.h>
#include <stdint.h>
#include <unistd.h>

int main(void) {
  /* init */
  setlocale(LC_ALL, ""); // enable unicode
  initscr();             // init ncurses
  cbreak();              // don't buffer input
  noecho();              // don't echo input
  curs_set(0);           // hide cursor
  nodelay(stdscr, TRUE); // non-blocking input
  // box(stdscr, 0, 0);     // draw border

  // init game objects
  Snake *snake = snake_init();
  Treat *treat = treat_init();
  treat_new(treat, stdscr);

  /* game loop */
  int8_t game_over = 0;
  while (!game_over) {
    // input
    int ch = getch();
    switch (ch) {
    case 'w':
      snake_set_direction(snake, UP);
      break;
    case 's':
      snake_set_direction(snake, DOWN);
      break;
    case 'a':
      snake_set_direction(snake, LEFT);
      break;
    case 'd':
      snake_set_direction(snake, RIGHT);
      break;
    case 'q':
      game_over = 1;
      break;
    }

    // update
    update_snake(snake, stdscr);
    wrefresh(stdscr);

    // sleep
    usleep(100000);
  }

  /* deinit */
  treat_deinit(treat);
  snake_deinit(snake);
  endwin();
  return 0;
}
