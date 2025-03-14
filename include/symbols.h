#ifndef __NSNAKES_SYMBOLS_H__
#define __NSNAKES_SYMBOLS_H__

#include <ncurses.h>

// used to draw the snake body
#define SNAKE_BODY L"○"

// snake head
#define SNAKE_HEAD L"●"

// used to draw the treat
// #define TREAT L"\U0001F34E" // 🍎
#define TREAT L"♦" // █

#define UPDATE_PER_SECOND 15
#define DELTA_TIME (1.0 / UPDATE_PER_SECOND * 1000)

#define SPEED_MULTIPLIER 2

#endif // __NSNAKES_SYMBOLS_H__
