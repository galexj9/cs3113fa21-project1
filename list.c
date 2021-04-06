#include "list.h"

int contains(int *list, int len, int el) {
  for (int i = 0; i < len; i++)
    if (list[i] == el)
      return 1;
  return -1;
}

void put(int *list, int len, int el) {
  for (int i = 0; i < len; i++) {
    if (list[i] == -1) {
      list[i] = el;
      break;
    }
  }
}