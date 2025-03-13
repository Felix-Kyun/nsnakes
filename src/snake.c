#include "snake.h"
#include "cvec_snake.h"
#include "symbols.h"

Snake *snake_init(void) {
  Snake *snake = malloc(sizeof(Snake));
  snake->body = vec_init();
  snake->direction.x = 1;
  snake->direction.y = 0;
  snake_vec_push_back(snake->body, (Coordinate){0, 0});
  return snake;
}

void update_snake(Snake *snake, WINDOW *win) {
  Coordinate head = snake_vec_get(snake->body, 0);
  Coordinate new_head = {head.x + snake->direction.x,
                         head.y + snake->direction.y};

  // add new head
  snake_vec_push_front(snake->body, new_head);

  // remove old tail
  Coordinate old = snake_vec_pop_back(snake->body);
  mvwaddwstr(stdscr, old.y, old.x, L" ");

  for (size_t i = 0; i < snake->body->size; i++) {
    Coordinate body_part = snake_vec_get(snake->body, i);
    mvwaddwstr(win, body_part.y, body_part.x, SNAKE_BODY);
  }
}

// void draw_snake(Snake *snake, WINDOW *win) {
//   for (size_t i = 0; i < snake->body->size; i++) {
//     Coordinate body_part = snake_vec_get(snake->body, i);
//     mvwaddwstr(win, body_part.y, body_part.x, SNAKE_BODY);
//   }
//   wrefresh(win);
// }

void snake_set_direction(Snake *snake, DIRECTION direction) {
  switch (direction) {
  case UP:
    snake->direction.x = 0;
    snake->direction.y = -1;
    break;
  case DOWN:
    snake->direction.x = 0;
    snake->direction.y = 1;
    break;
  case LEFT:
    snake->direction.x = -1;
    snake->direction.y = 0;
    break;
  case RIGHT:
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
