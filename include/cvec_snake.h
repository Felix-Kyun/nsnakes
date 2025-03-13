#ifndef __NSNAKES_CVEC_SNAKE_H__
#define __NSNAKES_CVEC_SNAKE_H__

#include "vec.h"
#include "coordinate.h"

void snake_vec_push_back(Vec *vec, Coordinate data);
void snake_vec_push_front(Vec *vec, Coordinate data);
Coordinate snake_vec_pop_back(Vec *vec);
Coordinate snake_vec_pop_front(Vec *vec);

Coordinate snake_vec_get(Vec *vec, size_t index);

#endif // __NSNAKES_CVEC_SNAKE_H__
