#include "cvec_snake.h"

// alloc: int -> void *
static void *alloc_Coordinate(Coordinate data) {
  Coordinate *data_ptr = (Coordinate *)malloc(sizeof(Coordinate));
  *data_ptr = data;
  return data_ptr;
}

// dealloc: void * -> Coordinate , Vec* for error handling
static Coordinate dealloc_Coordinate(void *data) {
  Coordinate data_val = *(Coordinate *)data;  
  free(data);
  return data_val;
}

void snake_vec_push_back(Vec *vec, Coordinate data) {
  vec_push_back(vec, alloc_Coordinate(data));
}

Coordinate snake_vec_get(Vec *vec, size_t index) {
  Coordinate *data_ptr = (Coordinate *)vec_get(vec, index);
  return *data_ptr;
}

void snake_vec_push_front(Vec *vec, Coordinate data) {
  vec_push_front(vec, alloc_Coordinate(data));
}

Coordinate snake_vec_pop_front(Vec *vec) {
  return dealloc_Coordinate(vec_pop_front(vec));
}

Coordinate snake_vec_pop_back(Vec *vec) {
  return dealloc_Coordinate(vec_pop_back(vec));
}
