#ifndef __NSNAKES_SNAKE_H__
#define __NSNAKES_SNAKE_H__

#include "cvec_snake.h"
#include <ncurses.h>

typedef struct Direction {
  int x;
  int y;
} Direction;

typedef enum DIRECTION {
  UP,
  DOWN,
  LEFT,
  RIGHT,
} DIRECTION;

typedef struct Snake {
  Vec *body;
  Direction direction;
} Snake;

// initialize snake struct 
Snake *snake_init(void);

// update snake position
void update_snake(Snake *snake, WINDOW *win);

// needed ??
// void draw_snake(Snake *snake, WINDOW *win);

// set snake direction
void snake_set_direction(Snake *snake, DIRECTION direction);

// increase snake size by 1
void snake_grow(Snake *snake);

// free snake memory
void snake_deinit(Snake *snake);

// check if snake is colliding with itself
int check_collision(Snake *snake);

// get the current poition
Coordinate get_snake_head(Snake *snake);

#endif // __NSNAKES_SNAKE_H__
