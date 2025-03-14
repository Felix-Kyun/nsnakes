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
  keypad(stdscr, TRUE);  // enable arrow keys
  box(stdscr, 0, 0);     // draw border

  // init game objects
  Snake *snake = snake_init();
  Treat *treat = treat_init();
  treat_new(treat, snake, stdscr);

  /* game loop */
  int8_t game_over = 0;
  while (!game_over) {
    // input
    int ch = getch();
    switch (ch) {
    case KEY_UP:
      snake_set_direction(snake, UP);
      break;
    case KEY_DOWN:
      snake_set_direction(snake, DOWN);
      break;
    case KEY_LEFT:
      snake_set_direction(snake, LEFT);
      break;
    case KEY_RIGHT:
      snake_set_direction(snake, RIGHT);
      break;
    case 'q':
      game_over = 1;
      break;
    case 'p':
      while (getch() != 'p')
        usleep(100000);
      break;
    }

    // update
    update_snake(snake, stdscr);
    if (check_collision(snake)) {
      game_over = 1;
    }
    if (check_collision_treat(snake, treat)) {
      snake_grow(snake);
      treat_new(treat, snake, stdscr);
    }

    // draw
    wrefresh(stdscr);

    // sleep
    usleep(100000 - snake->body->size * 500);
  }

  /* deinit */
  treat_deinit(treat);
  snake_deinit(snake);
  endwin();
  return 0;
}
