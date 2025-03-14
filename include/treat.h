#ifndef __NSNAKES_TREAT_H__
#define __NSNAKES_TREAT_H__

#include "coordinate.h"
#include <ncurses.h>

typedef struct Treat {
  Coordinate position;
} Treat;

// initialize treat struct
Treat *treat_init(void);

// create new treat at random position
// void treat_new(Treat *treat, WINDOW *win);

// free treat memory
void treat_deinit(Treat *treat);

#endif // __NSNAKES_TREAT_H__
