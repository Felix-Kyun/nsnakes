#include "misc.h"
#include "symbols.h"
#include <ncurses.h>
#include <stdlib.h>
#include <wchar.h>

cchar_t *get_snake_head_symbol(void) {
  static cchar_t *head = NULL;
  if (head == NULL) {
    head = malloc(sizeof(cchar_t));

    setcchar(head, SNAKE_HEAD, A_BOLD, 1, NULL);
  }
  return head;
}
