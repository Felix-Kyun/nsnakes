#include "snake.h"
#include "cvec_snake.h"
#include "symbols.h"
#include "misc.h"
#include <stdlib.h>

Snake *snake_init(void) {
  Snake *snake = malloc(sizeof(Snake));
  snake->body = vec_init();
  snake->direction.x = 1;
  snake->direction.y = 0;
  snake_vec_push_back(snake->body, (Coordinate){1, 1});
  return snake;
}

void update_snake(Snake *snake, WINDOW *win) {
  int y, x;
  getmaxyx(win, y, x);

  Coordinate head = snake_vec_get(snake->body, 0);
  mvwaddwstr(win, head.y, head.x, SNAKE_BODY);

  // mvprintw(0, 0, "snake x: %d, y: %d", head.x, head.y);

  if (head.x <= 1 && snake->direction.x == -1)
    head.x = x - 1;
  if (head.y <= 1 && snake->direction.y == -1)
    head.y = y - 1;
  if (head.x == x - 2 && snake->direction.x == 1)
    head.x = 0;
  if (head.y == y - 2 && snake->direction.y == 1)
    head.y = 0;

  Coordinate new_head = {head.x + snake->direction.x,
                         head.y + snake->direction.y};

  // add new head
  snake_vec_push_front(snake->body, new_head);

  // remove old tail
  Coordinate old = snake_vec_pop_back(snake->body);
  mvwaddwstr(stdscr, old.y, old.x, L" ");

  // draw new head
  // mvwaddwstr(win, new_head.y, new_head.x, SNAKE_HEAD);
  mvadd_wch(new_head.y, new_head.x, get_snake_head_symbol());
}

void snake_set_direction(Snake *snake, DIRECTION direction) {
  switch (direction) {
  case UP:
    if (snake->direction.y == 1)
      break;
    snake->direction.x = 0;
    snake->direction.y = -1;
    break;
  case DOWN:
    if (snake->direction.y == -1)
      break;
    snake->direction.x = 0;
    snake->direction.y = 1;
    break;
  case LEFT:
    if (snake->direction.x == 1)
      break;
    snake->direction.x = -1;
    snake->direction.y = 0;
    break;
  case RIGHT:
    if (snake->direction.x == -1)
      break;
    snake->direction.x = 1;
    snake->direction.y = 0;
    break;
  }
}

void snake_grow(Snake *snake) {
  Coordinate head = snake_vec_get(snake->body, 0);
  Coordinate new_head = {head.x + snake->direction.x,
                         head.y + snake->direction.y};
  snake_vec_push_front(snake->body, new_head);
}

void snake_deinit(Snake *snake) {
  vec_destroy(snake->body);
  free(snake);
}

Coordinate get_snake_head(Snake *snake) {
  return snake_vec_get(snake->body, 0);
}

int check_collision(Snake *snake) {
  Coordinate head = get_snake_head(snake);
  for (size_t i = 1; i < snake->body->size; i++) {
    Coordinate body_part = snake_vec_get(snake->body, i);
    if (head.x == body_part.x && head.y == body_part.y) {
      return 1;
    }
  }
  return 0;
}

int check_collision_treat(Snake *snake, Treat *treat) {
  Coordinate head = get_snake_head(snake);
  if (head.x == treat->position.x && head.y == treat->position.y) {
    return 1;
  }

  return 0;
}

void treat_new(Treat *treat, Snake *snake, WINDOW *win) {
  int y, x;
  getmaxyx(win, y, x);

  int new_x = rand() % (x - 2);
  int new_y = rand() % (y - 2);

  treat->position.x = (new_x == 0) ? 1 : new_x;
  treat->position.y = (new_y == 0) ? 1 : new_y;

  for (size_t i = 0; i < snake->body->size; i++) {
    Coordinate body_part = snake_vec_get(snake->body, i);
    if (treat->position.x == body_part.x && treat->position.y == body_part.y) {
      treat_new(treat, snake, win);
      return;
    }
  }

  mvwaddwstr(win, treat->position.y, treat->position.x, TREAT);
}
