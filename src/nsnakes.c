#include "snake.h"
#include "symbols.h"
#include "treat.h"
#include <locale.h>
#include <ncurses.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>

double get_delta_time(void);

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

    // mvprintw(0, 0, "dt: %.4f", get_delta_time());

    // draw
    wrefresh(stdscr);

    // sleep
    double delta_time = get_delta_time();
    usleep(
        ((delta_time < DELTA_TIME) ? (DELTA_TIME - delta_time) : DELTA_TIME) *
        1000);
  }

  /* deinit */
  treat_deinit(treat);
  snake_deinit(snake);
  endwin();
  return 0;
}

double get_delta_time(void) { // ms
  static struct timespec prev_time = {0, 0};
  struct timespec current_time;
  clock_gettime(CLOCK_MONOTONIC, &current_time);
  double delta_time = (current_time.tv_sec - prev_time.tv_sec) * 1000 +
                      (current_time.tv_nsec - prev_time.tv_nsec) / 1e6;
  if (prev_time.tv_sec != 0)
    mvprintw(0, 0, "[dt: %7.5f]", delta_time);
  prev_time = current_time;
  return delta_time;
}
