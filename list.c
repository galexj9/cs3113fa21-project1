#include <stdio.h>
#include "list.h"

Process *get(Process **list, int len, int id) {
  if (list == NULL || len < 1 || id < 1)
    return NULL;

  for (int i = 0; i < len; i++)
    if (list[i]->id == id)
      return list[i];

  return NULL;
}

void put(Process **list, int len, Process *element) {
  if (list == NULL || len < 1 || element == NULL)
    return;

  for (int i = 0; i < len; i++)
    if (list[i]->id == -1) {
      list[i] = element;
      return;
    }
}
